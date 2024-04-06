using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class UTF8_CHAR : ISerializableObject
    {
        [MaxSizeSerializationAttribute(6)]
        /// <summary>
        /// Maximum 6 bytes
        /// </summary>
        public byte[] bytes { get; set; }

        public int bytesCount;

        public UTF8_CHAR()
        { }

    }
}
