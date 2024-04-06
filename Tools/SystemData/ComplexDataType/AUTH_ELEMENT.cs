using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class AUTH_ELEMENT : ISerializableObject
    {
        public int objectID { get; set; }

        /// <summary>
        /// Encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary>
        public byte[] objectName { get; set; }

        public int objectTypeID { get; set; }

        /// <summary>
        /// Encrypted value. Need to insert array length in the begin of serialized data (4 bytes)
        /// </summary>
        public byte[] objectValue { get; set; }

        public AUTH_ELEMENT()
        { }

    }

}
