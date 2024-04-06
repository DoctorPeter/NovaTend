using SystemData.SerializableObject;
using SystemData.ComplexDataType.List;

namespace SystemData.ComplexDataType
{
    public class USER_SCREEN : ISerializableObject
    {
        public int screenID { get; set; }

        public int screenTypeID { get; set; }

        public int screenScope { get; set; }

        /// <summary>
        /// For serializing: need to specify string length in the begin of serialized value (4 bytes)
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// For serializing: need to specify string length in the begin of serialized value (4 bytes)
        /// </summary>
        public string screenCaption { get; set; }

        public uint color { get; set; }

        public int heightPers { get; set; }

        public int heightPix { get; set; }

        public int widthPers { get; set; }

        public int widthPix { get; set; }

        public int locationX { get; set; }

        public int locationY { get; set; }

        public int locationXPers { get; set; }
                
        public int locationYPers { get; set; }

        public SCREEN_OBJECT_LIST ScreenObjects { get; set; }

        public USER_SCREEN()
        {

        }

    }

}
