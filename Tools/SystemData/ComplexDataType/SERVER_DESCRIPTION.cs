using System;
using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class SERVER_DESCRIPTION : ISerializableObjectFixedSize
    {
        /// <summary>
        /// Server ID
        /// </summary>
        public uint serverID { get; set; }

        /// <summary>
        /// Type of server
        /// </summary>
        public int serverType { get; set; }

        /// <summary>
        /// Priority of server
        /// </summary>
        public int serverPriority { get; set; }

        /// <summary>
        /// IP
        /// </summary>
        [FixedSizeSerializationAttribute(16)]
        public string ipAddress { get; set; }

        /// <summary>
        /// Port
        /// </summary>
        public uint port { get; set; }

        /// <summary>
        /// Server name
        /// </summary>
        [FixedSizeSerializationAttribute(64)]
        public string serverName { get; set; }

        public SERVER_DESCRIPTION()
        { }

        public int GetBytesLength()
        {
            return sizeof(int) * 2 + sizeof(uint) * 2 + 16 + 64;
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            if (obj is SERVER_DESCRIPTION)
            {
                var server = obj as SERVER_DESCRIPTION;

                return ((server.ipAddress == ipAddress) &&
                    (server.port == port) &&
                    (server.serverID == serverID) &&
                    (server.serverName == serverName) &&
                    (server.serverPriority == serverPriority) &&
                    (server.serverType == serverType));
            }

            return base.Equals(obj);
        }

    }
}
