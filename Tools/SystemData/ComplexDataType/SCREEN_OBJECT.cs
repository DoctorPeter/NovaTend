using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class SCREEN_OBJECT : ISerializableObject
    {
        public int objID { get; set; }

        public int objTypeId { get; set; }

        public int objScope { get; set; }

        /// <summary>
        /// For serializing: need to specify string length in the begin of serialized value (4 bytes)
        /// </summary>
        public string objName { get; set; }

        /// <summary>
        /// For serializing: need to specify string length in the begin of serialized value (4 bytes)
        /// </summary>
        public string objCaption { get; set; }

        public int heightPers { get; set; }

        public int heightPix { get; set; }

        public int widthPers { get; set; }

        public int widthPix { get; set; }

        public int locationX { get; set; }

        public int locationXPers { get; set; }

        public int locationY { get; set; }

        public int locationYPers { get; set; }

        public int order { get; set; }

        public uint backgroundColor { get; set; }

        public uint textColor { get; set; }

        public int fontSize { get; set; }

        public int lessonID { get; set; }

        public int questionID { get; set; }

        public int rightAnswerID { get; set; }

        /// <summary>
        /// For serializing: need to specify string length in the begin of serialized value (4 bytes)
        /// </summary>
        public string strValue { get; set; }

        private byte[] _imgValue;

        /// <summary>
        /// For serializing: need to specify string length in the begin of serialized value (4 bytes)
        /// </summary>
        public byte[] imgValue
        {
            get
            {
                return (byte[])_imgValue.Clone();
            }
            set { _imgValue = value; }
        }

        /// <summary>
        /// For serializing: need to specify string length in the begin of serialized value (4 bytes)
        /// </summary>
        public string textValue { get; set; }

        private string[] _listValuesSet;

        /// <summary>
        /// For serializing: need to specify 1-byte value to define is this array empty.
        /// then need to insert array length in the begin of serialized data (4 bytes) and  for each string need to specify it's length in the begin of it's serialized value (4 bytes)
        /// </summary>
        public string[] listValuesSet
        {
            get
            {
                return (string[])_listValuesSet.Clone();
            }
            set { _listValuesSet = value; }
        }

        public SCREEN_OBJECT()
        { }

    }
}
