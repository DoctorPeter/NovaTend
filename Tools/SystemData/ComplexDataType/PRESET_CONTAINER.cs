using SystemData.SerializableObject;
using SystemData.ComplexDataType.List;

namespace SystemData.ComplexDataType
{
    public class PRESET_CONTAINER :  ISerializableObject
    {
        public int presetID { get; set; }

        /// <summary>
        /// For serializing: need to specify string length in the begin of serialized value (4 bytes)
        /// </summary>
        public string presetName { get; set; }

        public USER_SCREEN_LIST UserScreens { get; set; }

        public PRESET_CONTAINER()
        { }

    }
}
