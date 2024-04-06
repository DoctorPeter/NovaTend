using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class USER_SECURITY_DATA : ISerializableObject
    {
        public int userID { get; set; }

        public int authSystemID { get; set; }

        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public byte[] encSystemUserName { get; set; }

        /// <summary>
        /// For serializing: encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public byte[] encSystemPassword { get; set; }

        /// <summary>
        /// For serializing: 1-byte value after serialization
        /// </summary
        public bool passThru { get; set; }

        [FixedSizeSerializationAttribute(32)]
        public string lastLogOnDate { get; set; }

        public int userToken { get; set; }

        public int tmpUserToken { get; set; }

        public int pwdType { get; set; }

        /// <summary>
        /// For serializing: Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public int[] pwdConstRules { get; set; }

        /// <summary>
        /// For serializing: Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary
        public int[] tmpPwdConstRules { get; set; }

        public USER_SECURITY_DATA()
        { }

    }
}
