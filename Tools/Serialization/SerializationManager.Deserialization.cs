using System;
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
        /// deserialize Message from byte array
        /// </summary>
        /// <param name="array">sourcebyte array</param>
        /// <returns>Message object instance or null if error</returns>
        public static Message Deserialize(byte[] array)
        {
            try
            {
                if (array == null)
                    throw new ArgumentNullException("array");

                if (BitConverter.IsLittleEndian)
                    array.Reverse();

                //not forget to extract array length from begin
                array = array.PrepareAsMessageFromServer();

                var res = new Message();
                var headerOffset = new MessageHeader().GetBytesLength();

                res.HEADER = new ArraySegment<byte>(array, 0, headerOffset).Deserialize_MessageHeader();
                res.LISTOFPARAMETERS = new ArraySegment<byte>(array, headerOffset, array.Length - headerOffset).Deserialize_MessageParametersList();

                return res;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        #region internal methods
        /// <summary>
        /// exstension method to deserialize ArraySegment to MessageHeader
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static MessageHeader Deserialize_MessageHeader(this ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new MessageHeader();
                byte[] headerInBytes = arrSegment.ToArray();

                res.CommandCode = BitConverter.ToInt32(new ArraySegment<byte>(headerInBytes, 0, sizeof(int)).ToArray(), 0);
                res.CommandType = (CommandTypeEnum)BitConverter.ToInt32(new ArraySegment<byte>(headerInBytes, sizeof(int), sizeof(int)).ToArray(), 0);
                res.senderID = BitConverter.ToUInt32(new ArraySegment<byte>(headerInBytes, sizeof(int) * 2, sizeof(uint)).ToArray(), 0);
                res.recipientID = BitConverter.ToUInt32(new ArraySegment<byte>(headerInBytes, sizeof(int) * 2 + sizeof(uint), sizeof(uint)).ToArray(), 0);

                return res;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// exstension method to deserialize ArraySegment to MessageParameter
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static MessageParameter Deserialize_MessageParameter(this ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new MessageParameter();
                byte[] parameterInBytes = arrSegment.ToArray();

                res.ParameterType = (ParameterTypeEnum)BitConverter.ToInt32(new ArraySegment<byte>(parameterInBytes, 0, sizeof(int)).ToArray(), 0);

                var parameterDataType = (ParameterDataTypeEnum)BitConverter.ToInt32(new ArraySegment<byte>(parameterInBytes, sizeof(int), sizeof(int)).ToArray(), 0);
                if (parameterDataType == ParameterDataTypeEnum.ENCRYPTED_DATA)
                    res._IsEncrypted = true;

                var bufferSize = BitConverter.ToInt32(new ArraySegment<byte>(parameterInBytes, sizeof(int) * 2, sizeof(int)).ToArray(), 0);

                res.Parameter = new ArraySegment<byte>(parameterInBytes, sizeof(int) * 3, bufferSize).ToArray().Deserialize(parameterDataType);

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// exstension method to deserialize ArraySegment to MessageParametersList
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static MessageParametersList Deserialize_MessageParametersList(this ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new MessageParametersList();
                byte[] parameterListInBytes = arrSegment.ToArray();

                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, 4).ToArray(), 0);

                int currentIndex = 4;

                for (int i = 0; i < count; i++)
                {
                    var length = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, currentIndex + 8, 4).ToArray(), 0);
                    var offset = 12 + length;

                    var deserializedParam = new ArraySegment<byte>(
                            parameterListInBytes,
                            currentIndex,
                            offset).Deserialize_MessageParameter();

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    currentIndex = currentIndex + offset;
                }

                return res;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// generic exstension method to deserialize ArraySegment to ISerializableObject
        /// uses reflection internally to switch between actual types
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static T Deserialize<T>(this ArraySegment<byte> arrSegment)
            where T : ISerializableObject
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                //check this is list
                var type = typeof(T);

                if (type == typeof(SerializableList<ISerializableObject>))
                    return DeserializeList<T>(arrSegment);

                if (type == typeof(SerializableListFixedItems<ISerializableObjectFixedSize>))
                    return DeserializeFixedList<T, ISerializableObjectFixedSize>(arrSegment);

                //deserialization
                var res = Activator.CreateInstance(typeof(T));

                byte[] objectBytes = arrSegment.ToArray();

                var properties = res.GetType().GetProperties(BindingFlags.Public | BindingFlags.Instance);
                var offset = 0;

                foreach (PropertyInfo property in properties)
                {
                    var propType = property.PropertyType;
                    var typeCode = System.Type.GetTypeCode(propType);

                    switch (typeCode)
                    {
                        case TypeCode.Boolean:
                            {
                                var valueBoolean = BitConverter.ToBoolean(new ArraySegment<byte>(objectBytes, offset, sizeof(bool)).ToArray(), 0);
                                property.SetValue(res, valueBoolean, null);
                                offset += sizeof(bool);
                                break;
                            }

                        case TypeCode.Int32:
                            {
                                var valueInt32 = BitConverter.ToInt32(new ArraySegment<byte>(objectBytes, offset, sizeof(int)).ToArray(), 0);
                                property.SetValue(res, valueInt32, null);
                                offset += sizeof(int);
                                break;
                            }

                        case TypeCode.String:
                            {
                                bool isFixedSize = false;
                                int size = 0;

                                isFixedSize = new SerializationAttributeHelper().TryGetFixedSizeSerializationAttribute(property, out size);

                                if (isFixedSize)
                                {
                                    var valueString = System.Text.Encoding.UTF8.GetString(new ArraySegment<byte>(objectBytes, offset, size).ToArray());
                                    property.SetValue(res, valueString, null);
                                    offset += size;
                                }
                                else
                                {
                                    var stringLength = BitConverter.ToInt32(new ArraySegment<byte>(objectBytes, offset, sizeof(int)).ToArray(), 0);
                                    var valueString = System.Text.Encoding.UTF8.GetString(new ArraySegment<byte>(objectBytes, offset + sizeof(int), stringLength).ToArray());
                                    property.SetValue(res, valueString, null);

                                    offset += sizeof(int) + stringLength;
                                }
                                break;
                            }

                        case TypeCode.UInt32:
                            {
                                var valueUInt32 = BitConverter.ToUInt32(new ArraySegment<byte>(objectBytes, offset, sizeof(uint)).ToArray(), 0);
                                property.SetValue(res, valueUInt32, null);
                                offset += sizeof(uint);
                                break;
                            }

                        case TypeCode.Object:
                            {
                                if (propType == typeof(byte[]))
                                {
                                    var arrayLength = BitConverter.ToInt32(new ArraySegment<byte>(objectBytes, offset, sizeof(int)).ToArray(), 0);
                                    var value = new ArraySegment<byte>(objectBytes, offset + sizeof(int), arrayLength).ToArray();
                                    property.SetValue(res, value, null);

                                    offset += sizeof(int) + arrayLength;

                                    break;
                                }

                                if (propType == typeof(int[]))
                                {
                                    var arrayLength = BitConverter.ToInt32(new ArraySegment<byte>(objectBytes, offset, sizeof(int)).ToArray(), 0);
                                    var byteValue = new ArraySegment<byte>(objectBytes, offset + sizeof(int), arrayLength).ToArray();
                                    int[] value = byteValue.ToIntArray();

                                    property.SetValue(res, value, null);

                                    offset += sizeof(int) + arrayLength;

                                    break;
                                }

                                if (propType == typeof(string[]))
                                {
                                    var arrayExist = BitConverter.ToBoolean(new ArraySegment<byte>(objectBytes, offset, sizeof(bool)).ToArray(), 0);
                                    offset += sizeof(bool);

                                    if (!arrayExist)
                                    {
                                        var arrayLength = BitConverter.ToInt32(new ArraySegment<byte>(objectBytes, offset, sizeof(int)).ToArray(), 0);
                                        offset += sizeof(int);


                                        var strRes = new string[arrayLength];

                                        for (int i = 0; i < arrayLength; i++)
                                        {
                                            var itemLength = BitConverter.ToInt32(new ArraySegment<byte>(objectBytes, offset, sizeof(int)).ToArray(), 0);
                                            offset += sizeof(int);

                                            var str = System.Text.Encoding.UTF8.GetString(new ArraySegment<byte>(objectBytes, offset, itemLength).ToArray(), 0, itemLength);
                                            strRes[i] = str;

                                            offset += itemLength;
                                        }

                                        property.SetValue(res, strRes, null);
                                    }
                                    else
                                    {
                                        property.SetValue(res, null, null);
                                    }

                                    break;
                                }

                                //if (propType == typeof(ISerializable))
                                if (propType.GetInterfaces().Contains(typeof(ISerializableObject)))
                                {
                                    //Мы можем сделать так только потому что св-во одно и в конце
                                    var paramBytes = new ArraySegment<byte>(objectBytes, offset, objectBytes.Length - offset).ToArray();
                                    var value = paramBytes.Deserialize(propType);
                                    property.SetValue(res, value, null);

                                    offset += paramBytes.Length;

                                    break;
                                }

                                throw new ArgumentOutOfRangeException("type not expected");
                            }

                        default:
                            throw new ArgumentOutOfRangeException("type not expected");
                    }

                }

                return (T)res;
            }
            catch (Exception)
            {
                return default(T);
            }
        }

        /// <summary>
        /// generic exstension method to deserialize ArraySegment to ISerializableObject
        /// conceeded that item is ISerializableObjectFixedSize under SerializableListFixedSize
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static T DeserializeFixedList<T, T1>(this ArraySegment<byte> arrSegment)
            where T : ISerializableObject
            where T1 : ISerializableObjectFixedSize
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = Activator.CreateInstance(typeof(T)) as SerializableListFixedItems<ISerializableObjectFixedSize>;

                byte[] parameterListInBytes = arrSegment.ToArray();

                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);
                var itemLength = (Activator.CreateInstance(typeof(T1)) as ISerializableObjectFixedSize).GetBytesLength();

                for (int i = 0; i < count; i++)
                {
                    //var deserializedParam = Activator.CreateInstance(typeof(T1));
                    var deserializedParam
                        = Deserialize<T1>(new ArraySegment<byte>(
                            parameterListInBytes,
                            sizeof(int) + i * itemLength,
                            itemLength));

                    if (deserializedParam != null)
                        res.Add((T1)deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }
                }

                return (T)(res as ISerializableObject);
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// generic exstension method to deserialize ArraySegment to ISerializableObject
        /// conceeded that item is ISerializableObject under SerializableList
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static T DeserializeList<T>(this ArraySegment<byte> arrSegment)
            where T : ISerializableObject
        {
            try
            {
                var type = typeof(T);

                if (type == typeof(ANSWER_CONTAINER))
                    return (T)(Deserialize_ANSWER_CONTAINER(arrSegment) as ISerializableObject);

                if (type == typeof(AUTH_CONTAINER))
                    return (T)(Deserialize_AUTH_CONTAINER(arrSegment) as ISerializableObject);

                if (type == typeof(SCREEN_OBJECT_LIST))
                    return (T)(Deserialize_SCREEN_OBJECT_LIST(arrSegment) as ISerializableObject);

                if (type == typeof(USER_LIST))
                    return (T)(Deserialize_USER_LIST(arrSegment) as ISerializableObject);

                if (type == typeof(USER_SCREEN_LIST))
                    return (T)(Deserialize_USER_SCREEN_LIST(arrSegment) as ISerializableObject);

                if (type == typeof(UTF8_STRING))
                    return (T)(Deserialize_UTF8_STRING(arrSegment) as ISerializableObject);

                if (type == typeof(UTF8_STRING_LIST))
                    return (T)(Deserialize_UTF8_STRING_LIST(arrSegment) as ISerializableObject);

                if (type == typeof(UTF8_STRINGS_MATRIX))
                    return (T)(Deserialize_UTF8_STRINGS_MATRIX(arrSegment) as ISerializableObject);

                if (type == typeof(UTF8_STRINGS_MATRIX_LIST))
                    return (T)(Deserialize_UTF8_STRINGS_MATRIX_LIST(arrSegment) as ISerializableObject);

                throw new NotSupportedException("unknown type");
            }
            catch (Exception ex)
            {
                return default(T);
            }
        }

        /// <summary>
        /// Extension method to convert byte[] to object. Type of objects defined by ParameterDataTypeEnum
        /// </summary>
        /// <param name="byteArray"></param>
        /// <param name="type"></param>
        /// <returns></returns>
        internal static object Deserialize(this byte[] byteArray, ParameterDataTypeEnum type)
        {
            try
            {
                switch (type)
                {
                    case ParameterDataTypeEnum.WRONG_DATA:
                        return null;

                    case ParameterDataTypeEnum.BYTE_DATA:
                        return byteArray[0];

                    case ParameterDataTypeEnum.DWORD_DATA:
                        return BitConverter.ToUInt32(byteArray, 0);

                    case ParameterDataTypeEnum.LONG_DATA:
                        return BitConverter.ToInt64(byteArray, 0);

                    case ParameterDataTypeEnum.STRING_DATA:
                        return System.Text.Encoding.UTF8.GetString(byteArray, 0, byteArray.Length - 1);

                    case ParameterDataTypeEnum.BINARY_DATA:
                    case ParameterDataTypeEnum.ENCRYPTED_DATA:
                        return byteArray;

                    case ParameterDataTypeEnum.CLIENT_DESCRIPTION_DATA:
                        return new ArraySegment<byte>(byteArray).Deserialize<CLIENT_DESCRIPTION>();

                    case ParameterDataTypeEnum.PRESET_CONTAINER_DATA:
                        return new ArraySegment<byte>(byteArray).Deserialize<PRESET_CONTAINER>();

                    case ParameterDataTypeEnum.USER_DESCRIPTOR_DATA:
                        return new ArraySegment<byte>(byteArray).Deserialize<USER_DESCRIPTOR>();

                    case ParameterDataTypeEnum.TIMEINFO_DATA:
                        return new ArraySegment<byte>(byteArray).Deserialize<TIME_INFO>();

                    case ParameterDataTypeEnum.USER_PRIVATE_DATA:
                        return new ArraySegment<byte>(byteArray).Deserialize<USER_SECURITY_DATA>();

                    case ParameterDataTypeEnum.USER_DB_ACCESS_DATA:
                        return new ArraySegment<byte>(byteArray).Deserialize<USER_DB_ACCESS_INFO>();

                    case ParameterDataTypeEnum.SERVER_DESCRIPTION_DATA:
                        return new ArraySegment<byte>(byteArray).Deserialize<SERVER_DESCRIPTION>();

                    case ParameterDataTypeEnum.ENVIROMENT_INFO_CONTAINER_DATA:
                        return new ArraySegment<byte>(byteArray).Deserialize<ENVIROMENT_INFO_CONTAINER>();
                        
                    case ParameterDataTypeEnum.AUTH_CONTAINER_DATA:
                        return Deserialize_AUTH_CONTAINER(new ArraySegment<byte>(byteArray));

                    case ParameterDataTypeEnum.ANSWER_CONTAINER_DATA:
                        return Deserialize_ANSWER_CONTAINER(new ArraySegment<byte>(byteArray));

                    case ParameterDataTypeEnum.SYMBOL_BOXES_DATA:
                        return Deserialize_UTF8_STRINGS_MATRIX_LIST(new ArraySegment<byte>(byteArray));

                    case ParameterDataTypeEnum.USER_LIST_DATA:
                        return Deserialize_USER_LIST(new ArraySegment<byte>(byteArray));

                    case ParameterDataTypeEnum.CLIENT_DESCRIPTION_LIST_DATA:
                        return Deserialize_CLIENT_DESCRIPTION_LIST(new ArraySegment<byte>(byteArray));

                    case ParameterDataTypeEnum.SERVER_DESCRIPTION_LIST_DATA:
                        return Deserialize_SERVER_DESCRIPTION_LIST(new ArraySegment<byte>(byteArray));

                    default:
                        return null;
                }
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Extension method to convert byte[] to SerializableList; if T isn't serializable list returns null;
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="byteArray"></param>
        /// <returns></returns>
        internal static object Deserialize(this byte[] byteArray, Type type)
        {
            try
            {
                if (type == typeof(SCREEN_OBJECT_LIST))
                    return Deserialize_SCREEN_OBJECT_LIST(new ArraySegment<byte>(byteArray));

                if (type == typeof(USER_SCREEN_LIST))
                    return Deserialize_USER_SCREEN_LIST(new ArraySegment<byte>(byteArray));

                if (type == typeof(UTF8_STRING_LIST))
                    return Deserialize_UTF8_STRING_LIST(new ArraySegment<byte>(byteArray));

                if (type == typeof(UTF8_STRINGS_MATRIX))
                    return Deserialize_UTF8_STRINGS_MATRIX(new ArraySegment<byte>(byteArray));

                if (type == typeof(UTF8_STRINGS_MATRIX_LIST))
                    return Deserialize_UTF8_STRINGS_MATRIX_LIST(new ArraySegment<byte>(byteArray));

                //...
                //need to fill if other types can be properties of complextypes

                return null;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to ANSWER_CONTAINER
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static ANSWER_CONTAINER Deserialize_ANSWER_CONTAINER(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new ANSWER_CONTAINER();

                byte[] parameterListInBytes = arrSegment.ToArray();
                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);

                int paramOffset = sizeof(int);

                for (int i = 0; i < count; i++)
                {
                    var itemStringLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset, sizeof(int)).ToArray(), 0);
                    var itemLength = sizeof(int) + itemStringLength + sizeof(int) * 2;

                    var deserializedParam =
                            new ArraySegment<byte>(
                            parameterListInBytes,
                            paramOffset,
                            itemLength).Deserialize<ANSWER_DESCRIPTOR>();

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    paramOffset = paramOffset + itemLength;
                }

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to AUTH_CONTAINER
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static AUTH_CONTAINER Deserialize_AUTH_CONTAINER(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new AUTH_CONTAINER();

                byte[] parameterListInBytes = arrSegment.ToArray();
                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);

                int paramOffset = sizeof(int);

                for (int i = 0; i < count; i++)
                {
                    var innerOffset = sizeof(int) * 2;

                    var itemByteArrayLength1 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                    var itemByteArrayLength2 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset + sizeof(int) + itemByteArrayLength1, sizeof(int)).ToArray(), 0);
                    var itemLength = innerOffset + sizeof(int) * 2 + itemByteArrayLength1 + itemByteArrayLength2;

                    var deserializedParam =
                            new ArraySegment<byte>(
                            parameterListInBytes,
                            paramOffset,
                            itemLength).Deserialize<AUTH_ELEMENT>();

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    paramOffset = paramOffset + itemLength;
                }

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to SCREEN_OBJECT_LIST
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static SCREEN_OBJECT_LIST Deserialize_SCREEN_OBJECT_LIST(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new SCREEN_OBJECT_LIST();

                byte[] parameterListInBytes = arrSegment.ToArray();
                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);

                int paramOffset = sizeof(int);
                for (int i = 0; i < count; i++)
                {
                    var innerOffset = sizeof(int) * 3;

                    var itemStringLength1 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                    innerOffset += sizeof(int) + itemStringLength1;

                    var itemStringLength2 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                    innerOffset += sizeof(int) + itemStringLength2;

                    innerOffset += sizeof(int) * 13 + sizeof(uint) * 2;

                    var itemStringLength3 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                    innerOffset += sizeof(int) + itemStringLength3;

                    var itemByteArrayLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                    innerOffset += sizeof(int) + itemByteArrayLength;

                    var itemStringLength4 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                    innerOffset += sizeof(int) + itemStringLength4;

                    var itemExist = BitConverter.ToBoolean(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(bool)).ToArray(), 0);
                    innerOffset += sizeof(bool);

                    if (!itemExist)
                    {
                        //then continue to all elements
                        var itemStringArrayCount = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                        innerOffset += sizeof(int);

                        for (int j = 0; j < itemStringArrayCount; j++)
                        {
                            var itemStringLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                            innerOffset += sizeof(int) + itemStringLength;
                        }
                    }

                    var deserializedParam =
                            new ArraySegment<byte>(
                            parameterListInBytes,
                            paramOffset,
                            innerOffset).Deserialize<SCREEN_OBJECT>();

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    paramOffset = paramOffset + innerOffset;
                }

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to USER_LIST
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static USER_LIST Deserialize_USER_LIST(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new USER_LIST();

                byte[] parameterListInBytes = arrSegment.ToArray();
                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);

                int paramOffset = sizeof(int);
                int byteArrayOffsetInParam = sizeof(int);

                for (int i = 0; i < count; i++)
                {

                    var itemByteArrLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + byteArrayOffsetInParam, sizeof(int)).ToArray(), 0);
                    var itemLength = sizeof(int) * 2 + itemByteArrLength;

                    var deserializedParam =
                            new ArraySegment<byte>(
                            parameterListInBytes,
                            paramOffset,
                            itemLength).Deserialize<SIMPLE_USER_DESCRIPTOR>();

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    paramOffset = paramOffset + itemLength;
                }

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to USER_SCREEN_LIST
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static USER_SCREEN_LIST Deserialize_USER_SCREEN_LIST(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new USER_SCREEN_LIST();

                byte[] parameterListInBytes = arrSegment.ToArray();
                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);

                int paramOffset = sizeof(int);

                for (int i = 0; i < count; i++)
                {
                    var innerOffset = sizeof(int) * 3;

                    var itemStringLength1 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                    innerOffset += sizeof(int) + itemStringLength1;

                    var itemStringLength2 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                    innerOffset += sizeof(int) + itemStringLength2;

                    innerOffset += sizeof(int) * 8 + sizeof(uint);

                    #region innerlist
                    var itemSCREEN_OBJECT_LISTCount = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                    innerOffset += sizeof(int);

                    var innerOffsetJ = 0;
                    var innerParamOffset = paramOffset + innerOffset;
                    var itemSCREEN_OBJECT_LISTlength = 0;

                    for (int j = 0; j < itemSCREEN_OBJECT_LISTCount; j++)
                    {
                        innerOffsetJ = sizeof(int) * 3;

                        var itemStringLengthJ1 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, innerParamOffset + innerOffsetJ, sizeof(int)).ToArray(), 0);
                        innerOffsetJ += sizeof(int) + itemStringLengthJ1;

                        var itemStringLengthK2 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, innerParamOffset + innerOffsetJ, sizeof(int)).ToArray(), 0);
                        innerOffsetJ += sizeof(int) + itemStringLengthK2;

                        innerOffsetJ += sizeof(int) * 13 + sizeof(uint) * 2;

                        var itemStringLength3 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, innerParamOffset + innerOffsetJ, sizeof(int)).ToArray(), 0);
                        innerOffsetJ += sizeof(int) + itemStringLength3;

                        var itemByteArrayLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, innerParamOffset + innerOffsetJ, sizeof(int)).ToArray(), 0);
                        innerOffsetJ += sizeof(int) + itemByteArrayLength;

                        var itemStringLength4 = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, innerParamOffset + innerOffsetJ, sizeof(int)).ToArray(), 0);
                        innerOffsetJ += sizeof(int) + itemStringLength4;

                        var itemExist = BitConverter.ToBoolean(new ArraySegment<byte>(parameterListInBytes, innerParamOffset + innerOffsetJ, sizeof(bool)).ToArray(), 0);
                        innerOffsetJ += sizeof(bool);

                        if (!itemExist)
                        {
                            var itemStringArrayCount = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, innerParamOffset + innerOffsetJ, sizeof(int)).ToArray(), 0);
                            innerOffsetJ += sizeof(int);

                            for (int k = 0; k < itemStringArrayCount; k++)
                            {
                                var itemStringLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, innerParamOffset + innerOffsetJ, sizeof(int)).ToArray(), 0);
                                innerOffsetJ += sizeof(int) + itemStringLength;
                            }
                        }

                        //whole calculation
                        //innerOffset = innerOffset + innerOffsetJ;
                        innerParamOffset = innerParamOffset + innerOffsetJ;
                        itemSCREEN_OBJECT_LISTlength += innerOffsetJ;
                    }
                    #endregion

                    var deserializedParam =
                            new ArraySegment<byte>(
                            parameterListInBytes,
                            paramOffset,
                            innerOffset + itemSCREEN_OBJECT_LISTlength).Deserialize<USER_SCREEN>();

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    paramOffset = paramOffset + innerOffset + itemSCREEN_OBJECT_LISTlength;
                }

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to UTF8_STRING
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static UTF8_STRING Deserialize_UTF8_STRING(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new UTF8_STRING();

                byte[] parameterListInBytes = arrSegment.ToArray();
                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);

                int paramOffset = sizeof(int);

                for (int i = 0; i < count; i++)
                {
                    var itemByteArrLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset, sizeof(int)).ToArray(), 0);
                    var itemLength = sizeof(int) + itemByteArrLength;

                    var deserializedParam =
                            new ArraySegment<byte>(
                            parameterListInBytes,
                            paramOffset,
                            itemLength).Deserialize<UTF8_CHAR>();

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    paramOffset = paramOffset + itemLength;
                }

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to UTF8_STRING_LIST
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static UTF8_STRING_LIST Deserialize_UTF8_STRING_LIST(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new UTF8_STRING_LIST();

                byte[] parameterListInBytes = arrSegment.ToArray();
                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);

                int paramOffset = sizeof(int);

                for (int i = 0; i < count; i++)
                {
                    var itemsCount = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset, sizeof(int)).ToArray(), 0);
                    var innerOffset = sizeof(int);

                    for (int j = 0; j < itemsCount; j++)
                    {
                        var itemsLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                        innerOffset += itemsLength + sizeof(int);
                    }

                    var deserializedParam = Deserialize_UTF8_STRING(new ArraySegment<byte>(
                            parameterListInBytes,
                            paramOffset,
                            innerOffset));

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    paramOffset = paramOffset + innerOffset;
                }

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to UTF8_STRINGS_MATRIX
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static UTF8_STRINGS_MATRIX Deserialize_UTF8_STRINGS_MATRIX(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new UTF8_STRINGS_MATRIX();

                byte[] parameterListInBytes = arrSegment.ToArray();
                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);

                int paramOffset = sizeof(int);

                for (int i = 0; i < count; i++)
                {
                    var itemsCount = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset, sizeof(int)).ToArray(), 0);
                    var innerOffset = sizeof(int);

                    for (int j = 0; j < itemsCount; j++)
                    {
                        var innerItemsCount = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                        var innerInnerOffset = sizeof(int);

                        for (int k = 0; k < innerItemsCount; k++)
                        {
                            var itemsLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset + innerInnerOffset, sizeof(int)).ToArray(), 0);
                            innerInnerOffset += itemsLength + sizeof(int);
                        }

                        innerOffset += innerInnerOffset;
                    }

                    var deserializedParam = Deserialize_UTF8_STRING_LIST(new ArraySegment<byte>(
                            parameterListInBytes,
                            paramOffset,
                            innerOffset));

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    paramOffset = paramOffset + innerOffset;
                }

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to UTF8_STRINGS_MATRIX_LIST
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static UTF8_STRINGS_MATRIX_LIST Deserialize_UTF8_STRINGS_MATRIX_LIST(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new UTF8_STRINGS_MATRIX_LIST();

                byte[] parameterListInBytes = arrSegment.ToArray();
                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);

                int paramOffset = sizeof(int);

                for (int i = 0; i < count; i++)
                {
                    var itemsCount = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset, sizeof(int)).ToArray(), 0);
                    var innerOffset = sizeof(int);

                    for (int j = 0; j < itemsCount; j++)
                    {
                        var innerItemsCount = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset, sizeof(int)).ToArray(), 0);
                        var innerInnerOffset = sizeof(int);

                        for (int k = 0; k < innerItemsCount; k++)
                        {
                            var innerInnerItemsCount = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset + innerInnerOffset, sizeof(int)).ToArray(), 0);
                            var innerInnerInnerOffset = sizeof(int);

                            for (int l = 0; l < innerInnerItemsCount; l++)
                            {
                                var itemsLength = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, paramOffset + innerOffset + innerInnerOffset + innerInnerInnerOffset, sizeof(int)).ToArray(), 0);
                                innerInnerInnerOffset += itemsLength + sizeof(int);
                            }

                            innerInnerOffset += innerInnerInnerOffset;
                        }

                        innerOffset += innerInnerOffset;
                    }

                    var deserializedParam = Deserialize_UTF8_STRINGS_MATRIX(new ArraySegment<byte>(
                            parameterListInBytes,
                            paramOffset,
                            innerOffset));

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }

                    paramOffset = paramOffset + innerOffset;
                }

                return res;

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to CLIENT_DESCRIPTION_LIST
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static CLIENT_DESCRIPTION_LIST Deserialize_CLIENT_DESCRIPTION_LIST(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new CLIENT_DESCRIPTION_LIST();

                byte[] parameterListInBytes = arrSegment.ToArray();

                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);
                var itemLength = new CLIENT_DESCRIPTION().GetBytesLength();

                for (int i = 0; i < count; i++)
                {
                    var deserializedParam
                        = Deserialize<CLIENT_DESCRIPTION>(new ArraySegment<byte>(
                            parameterListInBytes,
                            sizeof(int) + i * itemLength,
                            itemLength));

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }
                }

                return res;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// implements deserialization from ArraySegment to SERVER_DESCRIPTION_LIST
        /// </summary>
        /// <param name="arrSegment"></param>
        /// <returns></returns>
        internal static SERVER_DESCRIPTION_LIST Deserialize_SERVER_DESCRIPTION_LIST(ArraySegment<byte> arrSegment)
        {
            try
            {
                if (arrSegment == null)
                    throw new ArgumentNullException("arrSegment");

                var res = new SERVER_DESCRIPTION_LIST();

                byte[] parameterListInBytes = arrSegment.ToArray();

                var count = BitConverter.ToInt32(new ArraySegment<byte>(parameterListInBytes, 0, sizeof(int)).ToArray(), 0);
                var itemLength = new SERVER_DESCRIPTION().GetBytesLength();

                for (int i = 0; i < count; i++)
                {
                    var deserializedParam
                        = Deserialize<SERVER_DESCRIPTION>(new ArraySegment<byte>(
                            parameterListInBytes,
                            sizeof(int) + i * itemLength,
                            itemLength));

                    if (deserializedParam != null)
                        res.Add(deserializedParam);
                    else
                    {
                        //one of parameters was deserialized with errors
                        //therefore whole list deserialization fails
                        res.Clear();
                        break;
                    }
                }

                return res;
            }
            catch (Exception ex)
            {
                throw;
            }
        }
        #endregion
    }

}
