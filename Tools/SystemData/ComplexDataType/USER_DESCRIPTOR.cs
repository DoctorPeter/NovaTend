using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class USER_DESCRIPTOR : ISerializableObject
    {
        public int userID { get; set; }

        private byte[] _encName;
        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public byte[] encName
        {
            get
            {
                return (byte[])_encName.Clone();
            }
            set { _encName = value; }
        }

        private byte[] _encUserName;
        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public byte[] encUserName
        {
            get
            {
                return (byte[])_encUserName.Clone();
            }
            set { _encUserName = value; }
        }

        private byte[] _encEmailAddress;
        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public byte[] encEmailAddress
        {
            get
            {
                return (byte[])_encEmailAddress.Clone();
            }
            set
            {
                _encEmailAddress = value;
            }
        }

        private byte[] _encPhoneNumber;
        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public byte[] encPhoneNumber
        {
            get
            {
                return (byte[])_encPhoneNumber.Clone();
            }
            set { _encPhoneNumber = value; }
        }

        [FixedSizeSerializationAttribute(32)]
        public string lastLogOnDate { get; set; }

        /// <summary>
        /// For serializing: 1-byte value after serialization
        /// </summary
        public bool needStudy { get; set; }

        public int eduCategotyID { get; set; }

        /// <summary>
        /// For serializing: 1-byte value after serialization
        /// </summary
        public bool eduQuestionRandom { get; set; }

        /// <summary>
        /// For serializing: 1-byte value after serialization
        /// </summary
        public bool randomEduCateg { get; set; }

        public int pwdType { get; set; }

        public int pwdAttemptsCount { get; set; }

        public int maxPwdAttemptsCount { get; set; }

        /// <summary>
        /// For serializing: 1-byte value after serialization
        /// </summary
        public bool locked { get; set; }

        /// <summary>
        /// For serializing: 1-byte value after serialization
        /// </summary
        public bool pwdReseted { get; set; }

        /// <summary>
        /// For serializing: 1-byte value after serialization
        /// </summary
        public bool emailPwdReset { get; set; }

        /// <summary>
        /// For serializing: 1-byte value after serialization
        /// </summary
        public bool smsPwdReset { get; set; }

        public int pwdResetPeriod { get; set; }

        [FixedSizeSerializationAttribute(32)]
        public string pwdResetDate { get; set; }

        public USER_DESCRIPTOR()
        {

        }

    }
}
