using System;
using System.Collections;
using System.Linq;
using System.Reflection;
using SystemData;
using SystemData.Common;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;
using SystemData.Message;
using SystemData.SerializableObject;

namespace Serialization
{
    /// <summary>
    /// Class contains methods for serialization and deserialization of objects
    /// </summary>
    public static partial class SerializationManager
    {
        /// <summary>
        /// Serialize Message to array of bytes
        /// </summary>
        /// <param name="message">source message to serialize</param>
        /// <returns>byte array</returns>
        public static byte[] Serialize(Message message)
        {
            try
            {
                var headerBytes = message.HEADER.Serialize();
                var paramListBytes = message.LISTOFPARAMETERS.Serialize();

                if (headerBytes == null || paramListBytes == null)
                    return null;

                //not forget to add length in the begining
                return headerBytes.Concat(paramListBytes).ToArray().PrepareAsMessageToServer();
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        #region internal methods
        /// <summary>
        /// exstension method for serializing MessageHeader to array of bytes
        /// </summary>
        /// <param name="messageHeader"></param>
        /// <returns></returns>
        internal static byte[] Serialize(this MessageHeader messageHeader)
        {
            try
            {
                var res = new byte[messageHeader.GetBytesLength()];

                Array.Copy(BitConverter.GetBytes(messageHeader.CommandCode), 0, res, 0, sizeof(int));
                Array.Copy(BitConverter.GetBytes((int)messageHeader.CommandType), 0, res, sizeof(int), sizeof(int));
                Array.Copy(BitConverter.GetBytes(messageHeader.senderID), 0, res, sizeof(int) * 2, sizeof(uint));
                Array.Copy(BitConverter.GetBytes(messageHeader.recipientID), 0, res, sizeof(int) * 2 + sizeof(uint), sizeof(uint));

                return res;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// exstension method for serializing MessageParameter to array of bytes
        /// </summary>
        /// <param name="messageHeader"></param>
        /// <returns></returns>
        internal static byte[] Serialize(this MessageParameter parameter)
        {
            try
            {
                byte[] res;

                if (parameter.Parameter != null)
                {
                    //actual parameter is not empty

                    var serializedParam = parameter.Parameter.Serialize(parameter.ParameterDataType);

                    res = new byte[12 + serializedParam.Length];

                    Array.Copy(BitConverter.GetBytes((int)parameter.ParameterType), 0, res, 0, sizeof(int));
                    Array.Copy(BitConverter.GetBytes((int)parameter.ParameterDataType), 0, res, sizeof(int), sizeof(int));

                    Array.Copy(BitConverter.GetBytes(serializedParam.Length), 0, res, sizeof(int) * 2, sizeof(int));
                    Array.Copy(serializedParam, 0, res, sizeof(int) * 3, serializedParam.Length);
                }
                else
                {
                    //actual parameter is empty (null)

                    res = new byte[12];

                    Array.Copy(BitConverter.GetBytes((int)parameter.ParameterType), 0, res, 0, sizeof(int));
                    Array.Copy(BitConverter.GetBytes((int)parameter.ParameterDataType), 0, res, sizeof(int), sizeof(int));
                    Array.Copy(BitConverter.GetBytes(0), 0, res, sizeof(int) * 2, sizeof(int));
                }

                return res;

            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// serialize MessageParametersList to array of bytes
        /// </summary>
        /// <param name="messageHeader"></param>
        /// <returns></returns>
        internal static byte[] Serialize(this MessageParametersList messageParameterList)
        {
            try
            {
                if (messageParameterList == null)
                    throw new ArgumentNullException("messageParameterList");

                var res = BitConverter.GetBytes(messageParameterList.Count);

                messageParameterList.ForEach((param) =>
                {
                    var paramBytes = param.Serialize();
                    if (paramBytes != null)
                        res = res.Concat(paramBytes).ToArray();
                    else
                        throw new Exception("failed to serialize list");
                });

                return res;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// exstension method for serializing ISerializableObject to array of bytes
        /// uses reflection inside to switch trough properties
        /// </summary>
        /// <param name="messageHeader"></param>
        /// <returns></returns>
        internal static byte[] Serialize(this ISerializableObject serObject)
        {
            try
            {
                if (serObject == null)
                    throw new ArgumentNullException("serObjcet");

                byte[] res = new byte[0];
                var properties = serObject.GetType().GetProperties(BindingFlags.Public | BindingFlags.Instance);

                //for cases where list is list of list (e.t.c) happen
                if (serObject.GetType().IsAssignableFrom(typeof(IList)) || (serObject.GetType().GetInterfaces().Contains(typeof(IList))))
                {
                    return res.Concat((serObject as IList).SerializeUnknownGenericList()).ToArray();
                }

                foreach (PropertyInfo property in properties)
                {
                    var propType = property.PropertyType;
                    var typeCode = System.Type.GetTypeCode(propType);

                    switch (typeCode)
                    {
                        case TypeCode.Boolean:
                            res = res.Concat(BitConverter.GetBytes((bool)property.GetValue(serObject, null))).ToArray();
                            break;

                        case TypeCode.Int32:
                            res = res.Concat(BitConverter.GetBytes((int)property.GetValue(serObject, null))).ToArray();
                            break;

                        case TypeCode.UInt32:
                            res = res.Concat(BitConverter.GetBytes((uint)property.GetValue(serObject, null))).ToArray();
                            break;

                        case TypeCode.String:
                            {
                                bool isFixedSize = false;
                                int size = 0;

                                isFixedSize = new SerializationAttributeHelper().TryGetFixedSizeSerializationAttribute(property, out size);

                                if (isFixedSize)
                                    res = res.Concat(((string)property.GetValue(serObject, null)).ToArray(size)).ToArray();
                                else
                                    res = res.Concat(((string)property.GetValue(serObject, null)).ToArray()).ToArray();

                                break;
                            }

                        case TypeCode.Object:
                            {
                                if (propType == typeof(byte[]))
                                {
                                    var propValue = (byte[])property.GetValue(serObject, null);

                                    bool isLimitedSize = false;
                                    int size = 0;

                                    isLimitedSize = new SerializationAttributeHelper().TryGetMaxSizeSerializationAttribute(property, out size);

                                    if (isLimitedSize && propValue.Length > size)
                                    {
                                        res = res.Concat(BitConverter.GetBytes(propValue.Length)).ToArray();
                                        res = res.Concat(new ArraySegment<byte>(propValue, 0, size).ToArray()).ToArray();
                                    }
                                    else
                                    {
                                        res = res.Concat(BitConverter.GetBytes(propValue.Length)).ToArray();
                                        res = res.Concat(propValue).ToArray();
                                    }

                                    break;
                                }

                                if (propType == typeof(int[]))
                                {
                                    var propValue = (int[])property.GetValue(serObject, null);
                                    var propValueBytes = propValue.ToArray();

                                    res = res.Concat(BitConverter.GetBytes(propValueBytes.Length)).ToArray();
                                    res = res.Concat(propValueBytes).ToArray();

                                    break;
                                }

                                if (propType == typeof(string[]))
                                {
                                    var propValue = (string[])property.GetValue(serObject, null);

                                    var exist = (propValue != null) && (propValue.Length > 0);
                                    res = res.Concat(BitConverter.GetBytes(!exist)).ToArray();
                                    if (exist)
                                    {
                                        res = res.Concat(BitConverter.GetBytes(propValue.Length)).ToArray();
                                        res = res.Concat(propValue.ToArray()).ToArray();
                                    }

                                    break;
                                }

                                if (propType.IsAssignableFrom(typeof(IList)) || (propType.GetInterfaces().Contains(typeof(IList))))
                                {
                                    var propValue = (IList)property.GetValue(serObject, null);

                                    res = res.Concat(propValue.SerializeUnknownGenericList()).ToArray();

                                    break;
                                }

                                //var ins = propType.GetInterfaces();
                                //var flag = propType.IsAssignableFrom(typeof(ISerializableObject));
                                if (propType.IsAssignableFrom(typeof(ISerializableObject)) || (propType.GetInterfaces().Contains(typeof(ISerializableObject))))
                                {
                                    var propValue = (ISerializableObject)property.GetValue(serObject, null);

                                    res = res.Concat(propValue.Serialize()).ToArray();

                                    break;
                                }

                                throw new ArgumentOutOfRangeException("type not expected");
                            }

                        default:
                            throw new ArgumentOutOfRangeException("type not expected");
                    }
                }

                return res;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// generic exstension method for serializing SerializableList of ISerializableObject to array of bytes
        /// </summary>
        /// <param name="messageHeader"></param>
        /// <returns></returns>
        internal static byte[] Serialize<T>(this SerializableList<T> serList)
            where T : ISerializableObject
        {
            try
            {
                if (serList == null)
                    throw new ArgumentNullException("serList");

                var res = BitConverter.GetBytes(serList.Count);

                serList.ForEach((param) =>
                {
                    var paramBytes = param.Serialize();
                    if (paramBytes != null)
                        res = res.Concat(paramBytes).ToArray();
                    else
                        throw new Exception("failed to serialize list");
                });

                return res;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// generic exstension method for serializing SerializableListFixedItems of ISerializableObjectFixedSize to array of bytes
        /// </summary>
        /// <param name="messageHeader"></param>
        /// <returns></returns>
        internal static byte[] Serialize<T>(this SerializableListFixedItems<T> serList)
             where T : ISerializableObjectFixedSize
        {
            try
            {
                if (serList == null)
                    throw new ArgumentNullException("serList");

                var res = BitConverter.GetBytes(serList.Count);

                serList.ForEach((param) =>
                {
                    var paramBytes = param.Serialize();
                    if (paramBytes != null)
                        res = res.Concat(paramBytes).ToArray();
                    else
                        throw new Exception("failed to serialize list");
                });

                return res;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Extension method to convert object to byte[]. Type of objects defined by ParameterDataTypeEnum
        /// </summary>
        /// <param name="param"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        internal static byte[] Serialize(this object param, ParameterDataTypeEnum type)
        {
            try
            {
                switch (type)
                {
                    case ParameterDataTypeEnum.WRONG_DATA:
                        return new byte[0];

                    case ParameterDataTypeEnum.BYTE_DATA:
                        return new byte[1] { (byte)param };

                    case ParameterDataTypeEnum.DWORD_DATA:
                        return BitConverter.GetBytes((uint)param);

                    case ParameterDataTypeEnum.LONG_DATA:
                        return BitConverter.GetBytes((long)param);

                    case ParameterDataTypeEnum.STRING_DATA:
                        return System.Text.Encoding.UTF8.GetBytes(String.Format("{0}{1}", param, Char.MinValue));

                    case ParameterDataTypeEnum.BINARY_DATA:
                    case ParameterDataTypeEnum.ENCRYPTED_DATA:
                        return (byte[])param;

                    case ParameterDataTypeEnum.ANSWER_CONTAINER_DATA:
                        return (param as SerializableList<ANSWER_DESCRIPTOR>).Serialize();
                    case ParameterDataTypeEnum.AUTH_CONTAINER_DATA:
                        return (param as SerializableList<AUTH_ELEMENT>).Serialize();
                    case ParameterDataTypeEnum.CLIENT_DESCRIPTION_LIST_DATA:
                        return (param as SerializableListFixedItems<CLIENT_DESCRIPTION>).Serialize();
                    case ParameterDataTypeEnum.USER_LIST_DATA:
                        return (param as SerializableList<SIMPLE_USER_DESCRIPTOR>).Serialize();
                    case ParameterDataTypeEnum.SYMBOL_BOXES_DATA:
                        return (param as SerializableList<UTF8_STRINGS_MATRIX>).Serialize();
                    case ParameterDataTypeEnum.SERVER_DESCRIPTION_LIST_DATA:
                        return (param as SerializableListFixedItems<SERVER_DESCRIPTION>).Serialize();

                    default:
                        if (param is ISerializableObject)
                            //all complex param types goes here
                            return Serialize(param as ISerializableObject);
                        return null;
                }

            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// private method to handle generic lists props in reflection
        /// </summary>
        /// <param name="genericList"></param>
        /// <returns></returns>
        private static byte[] SerializeUnknownGenericList(this IList genericList)
        {
            try
            {
                if (genericList is SerializableList<ANSWER_DESCRIPTOR>)
                    return (genericList as SerializableList<ANSWER_DESCRIPTOR>).Serialize();

                if (genericList is SerializableList<AUTH_ELEMENT>)
                    return (genericList as SerializableList<AUTH_ELEMENT>).Serialize();

                if (genericList is SerializableList<CLIENT_DESCRIPTION>)
                    return (genericList as SerializableList<CLIENT_DESCRIPTION>).Serialize();

                if (genericList is SerializableList<SERVER_DESCRIPTION>)
                    return (genericList as SerializableList<SERVER_DESCRIPTION>).Serialize();

                if (genericList is SerializableList<SCREEN_OBJECT>)
                    return (genericList as SerializableList<SCREEN_OBJECT>).Serialize();

                if (genericList is SerializableList<SIMPLE_USER_DESCRIPTOR>)
                    return (genericList as SerializableList<SIMPLE_USER_DESCRIPTOR>).Serialize();

                if (genericList is SerializableList<USER_SCREEN>)
                    return (genericList as SerializableList<USER_SCREEN>).Serialize();

                if (genericList is SerializableList<UTF8_CHAR>)
                    return (genericList as SerializableList<UTF8_CHAR>).Serialize();

                if (genericList is SerializableList<UTF8_STRING>)
                    return (genericList as SerializableList<UTF8_STRING>).Serialize();

                if (genericList is SerializableList<UTF8_STRING_LIST>)
                    return (genericList as SerializableList<UTF8_STRING_LIST>).Serialize();

                if (genericList is SerializableList<UTF8_STRINGS_MATRIX>)
                    return (genericList as SerializableList<UTF8_STRINGS_MATRIX>).Serialize();

                return null;
            }
            catch (Exception ex)
            {
                return null;
            }
        }
        #endregion
    }

}
