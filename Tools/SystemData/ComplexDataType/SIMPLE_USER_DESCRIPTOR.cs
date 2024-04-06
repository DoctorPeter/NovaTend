using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class SIMPLE_USER_DESCRIPTOR : ISerializableObject
    {
        public int UserID { get; set; }

        private byte[] _EncodedUserName;
        public byte[] EncodedUserName
        {
            get
            {
                return (byte[])_EncodedUserName.Clone();
            }
            set { _EncodedUserName = value; }
        }
        

        public SIMPLE_USER_DESCRIPTOR()
        { }


    }
}
