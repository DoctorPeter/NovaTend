using System;
using SystemData;

namespace SystemData.Message
{
    /// <summary>
    /// header to pass with message
    /// </summary>
    public class MessageHeader
    {
        /// <summary>
        /// Command Type
        /// </summary>
        public CommandTypeEnum CommandType { get; set; }

        /// <summary>
        /// Command Code
        /// </summary>
        public int CommandCode { get; set; }

        public uint senderID { get; set; }

        public uint recipientID { get; set; } 

        /// <summary>
        /// creates empty message header object
        /// </summary>
        public MessageHeader()
        {

        }

        /// <summary>
        /// create message header object from existing code and type
        /// </summary>
        /// <param name="code">Command Code</param>
        /// <param name="type">Command Type</param>
        public MessageHeader(int code, CommandTypeEnum type, uint p_senderID, uint p_recepientID)
        {
            CommandCode = code;
            CommandType = type;
            this.senderID = p_senderID;
            this.recipientID = p_recepientID;
        }

        public int GetBytesLength()
        {
            return sizeof(int) * 2 + sizeof(uint) * 2;
        }

        public override string ToString()
        {
            return String.Format("type: {0}, code: {1}, senderID: {2}, recepientID: {3}", (int)this.CommandType, this.CommandCode, this.senderID, this.recipientID);
        }
    }
}
