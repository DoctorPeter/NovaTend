
namespace SystemData
{
    /// <summary>
    /// Possible values for command type
    /// </summary>
    public enum CommandTypeEnum
    {
        REQUEST = 1,
        RESPONSE = 2
    }

    /// <summary>
    /// Possible values for parameter type
    /// </summary>
    public enum ParameterTypeEnum
    {
        INPUTPARAMETER = 1,
        OUTPUTPARAMETER = 2
    }

    /// <summary>
    /// Possible values for parameter data type
    /// </summary>
    public enum ParameterDataTypeEnum
    {
        /// <summary>
        /// Wrong data (NULL)
        /// </summary>
        WRONG_DATA = 0,
        /// <summary>
        /// One byte number (byte)
        /// </summary>
        BYTE_DATA = 1,
        /// <summary>
        /// Two bytes number (short)
        /// </summary>
        WORD_DATA = 2,
        /// <summary>
        /// Four bytes number (int)
        /// </summary>
        DWORD_DATA = 3,
        /// <summary>
        /// Eight bytes number (long)
        /// </summary>
        LONG_DATA = 4,
        /// <summary>
        /// Byte array (byte [])
        /// </summary>
        BINARY_DATA = 5,
        /// <summary>
        /// String of symbols (string) – null terminated multi-byte string (ANSI)
        /// </summary>
        STRING_DATA = 6,
        /// <summary>
        /// Byte array (byte [])
        /// </summary>
        ENCRYPTED_DATA = 7,
        /// <summary>
        /// Client description structure (CLIENT_DESCRIPTION)
        /// </summary>
        CLIENT_DESCRIPTION_DATA = 8,
        /// <summary>
        /// List of client description structures (CLIENT_DESCRIPTION_LIST)
        /// </summary>
        CLIENT_DESCRIPTION_LIST_DATA = 9,
        /// <summary>
        /// Server description structure (SERVER_DESCRIPTION)
        /// </summary>
        SERVER_DESCRIPTION_DATA = 10,
        /// <summary>
        /// List of server description structures (SERVER_DESCRIPTION_LIST)
        /// </summary>
        SERVER_DESCRIPTION_LIST_DATA = 11,
        /// <summary>
        /// Structure of user screen (PRESET_CONTAINER)
        /// </summary>
        PRESET_CONTAINER_DATA = 12,
        /// <summary>
        /// List of users (USER_LIST)
        /// </summary>
        USER_LIST_DATA = 13,
        /// <summary>
        /// User descriptor (USER_DECRIPTOR)
        /// </summary>
        USER_DESCRIPTOR_DATA = 14,
        /// <summary>
        /// Package of authentication data (AUTH_CONTAINER)
        /// </summary>
        AUTH_CONTAINER_DATA = 15,
        /// <summary>
        /// Package with user answers (ANSWER_CONTAINER)
        /// </summary>
        ANSWER_CONTAINER_DATA = 16,
        /// <summary>
        /// Time data (TIMEINFO)
        /// </summary>
        TIMEINFO_DATA = 17,
        /// <summary>
        /// List of symbol boxes(UTF8_STRINGS_MATRIX_LIST) 
        /// </summary>
        SYMBOL_BOXES_DATA = 18,
        /// <summary>
        /// Package of user security data (USER_SECURITY_DATA)
        /// </summary>
        USER_PRIVATE_DATA = 19,
        /// <summary>
        /// Package of data for DB connection (USER_DB_ACCESS_INFO)
        /// </summary>
        USER_DB_ACCESS_DATA = 20,
        /// <summary>
        /// Package with user environment data (ENVIROMENT_INFO_CONTAINER)
        /// </summary>
        ENVIROMENT_INFO_CONTAINER_DATA = 21,
    }
}
