using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class USER_DB_ACCESS_INFO : ISerializableObject
    {
        private byte[] _dbServerName;
        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary>
        public byte[] dbServerName
        {
            get
            {
                return (byte[])_dbServerName.Clone();
            }
            set { _dbServerName = value; }
        }

        private byte[] _dbName;
        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public byte[] dbName
        {
            get
            {
                return (byte[])_dbName.Clone();
            }
            set { _dbName = value; }
        }

        private byte[] _dbUserName;
        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public byte[] dbUserName
        {
            get
            {
                return (byte[])_dbUserName.Clone();
            }
            set { _dbUserName = value; }
        }

        private byte[] _dbPassword;
        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public byte[] dbPassword
        {
            get
            {
                return (byte[])_dbPassword.Clone();
            }
            set { _dbPassword = value; }
        }

        private int[] _userPermissions;
        /// <summary>
        /// For serializing: Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public int[] userPermissions
        {
            get
            {
                return (int[])_userPermissions.Clone();
            }
            set { _userPermissions = value; }
        }

        public USER_DB_ACCESS_INFO()
        { }

    }
}
