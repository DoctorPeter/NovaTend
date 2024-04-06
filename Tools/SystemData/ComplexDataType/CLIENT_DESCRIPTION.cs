using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class CLIENT_DESCRIPTION : ISerializableObjectFixedSize
    {
        public uint ClientID { get; set; }

        public uint OwnClientID { get; set; }

        public int ClientType { get; set; }

        public int OSVersion { get; set; }

        [FixedSizeSerializationAttribute(16)]
        public string PrivateIP { get; set; }

        public uint PrivatePort { get; set; }

        [FixedSizeSerializationAttribute(16)]
        public string PublicIP { get; set; }

        public uint PublicPort { get; set; }

        public int Version { get; set; }

        [FixedSizeSerializationAttribute(64)]
        public string ClientName { get; set; }

        public CLIENT_DESCRIPTION()
        { }

        public int GetBytesLength()
        {
            return sizeof(int) * 3 + sizeof(uint) * 4 + 16 + 16 + 64;
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            if (obj is CLIENT_DESCRIPTION)
            {
                var client = obj as CLIENT_DESCRIPTION;

                return ((client.ClientID == ClientID) &&
                        (client.OwnClientID == OwnClientID) &&
                        (client.ClientType == ClientType) &&
                        (client.OSVersion == OSVersion) &&
                        (client.PrivateIP == PrivateIP) &&
                        (client.PrivatePort == PrivatePort) &&
                        (client.PublicIP == PublicIP) &&
                        (client.PublicPort == PublicPort) &&
                        (client.ClientName == ClientName) &&
                        (client.Version == Version));
            }

            return base.Equals(obj);
        }
    }
}
