using System;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;

namespace SystemData
{
    public static class TypeMapper
    {
        /// <summary>
        /// exstension method to define actual type of message parameter
        /// </summary>
        /// <param name="messageParameter"></param>
        /// <returns></returns>
        public static ParameterDataTypeEnum GetDataType(this object Parameter, bool isEncrypted = false)
        {
            try
            {
                if (Parameter == null)
                    return ParameterDataTypeEnum.WRONG_DATA;

                var actualType = Parameter.GetType();

                if (actualType == typeof(String))
                    return ParameterDataTypeEnum.STRING_DATA;

                if (actualType == typeof(byte))
                    return ParameterDataTypeEnum.BYTE_DATA;

                if (actualType == typeof(byte[]))
                    return
                        (isEncrypted) ?
                            ParameterDataTypeEnum.ENCRYPTED_DATA :
                            ParameterDataTypeEnum.BINARY_DATA;

                if (actualType == typeof(UInt32))
                    return ParameterDataTypeEnum.DWORD_DATA;

                if (actualType == typeof(long))
                    return ParameterDataTypeEnum.LONG_DATA;

                if (actualType == typeof(CLIENT_DESCRIPTION))
                    return ParameterDataTypeEnum.CLIENT_DESCRIPTION_DATA;

                if (actualType == typeof(CLIENT_DESCRIPTION_LIST))
                    return ParameterDataTypeEnum.CLIENT_DESCRIPTION_LIST_DATA;

                if (actualType == typeof(PRESET_CONTAINER))
                    return ParameterDataTypeEnum.PRESET_CONTAINER_DATA;

                if (actualType == typeof(USER_LIST))
                    return ParameterDataTypeEnum.USER_LIST_DATA;

                if (actualType == typeof(USER_DESCRIPTOR))
                    return ParameterDataTypeEnum.USER_DESCRIPTOR_DATA;

                if (actualType == typeof(AUTH_CONTAINER))
                    return ParameterDataTypeEnum.AUTH_CONTAINER_DATA;

                if (actualType == typeof(ANSWER_CONTAINER))
                    return ParameterDataTypeEnum.ANSWER_CONTAINER_DATA;

                if (actualType == typeof(TIME_INFO))
                    return ParameterDataTypeEnum.TIMEINFO_DATA;

                if (actualType == typeof(UTF8_STRINGS_MATRIX_LIST))
                    return ParameterDataTypeEnum.SYMBOL_BOXES_DATA;

                if (actualType == typeof(USER_SECURITY_DATA))
                    return ParameterDataTypeEnum.USER_PRIVATE_DATA;

                if (actualType == typeof(USER_DB_ACCESS_INFO))
                    return ParameterDataTypeEnum.USER_DB_ACCESS_DATA;

                if (actualType == typeof(SERVER_DESCRIPTION))
                    return ParameterDataTypeEnum.SERVER_DESCRIPTION_DATA;

                if (actualType == typeof(SERVER_DESCRIPTION_LIST))
                    return ParameterDataTypeEnum.SERVER_DESCRIPTION_LIST_DATA;

                if (actualType == typeof(ENVIROMENT_INFO_CONTAINER))
                    return ParameterDataTypeEnum.ENVIROMENT_INFO_CONTAINER_DATA;
                
                return ParameterDataTypeEnum.WRONG_DATA;
            }
            catch (Exception)
            {
                return ParameterDataTypeEnum.WRONG_DATA;
            }
        }
    }
}
