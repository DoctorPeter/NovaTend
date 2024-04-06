using System;
using System.Text;

namespace SystemData.Message
{
    /// <summary>
    /// The message which is transmitted between client and server
    /// </summary>
    public class Message
    {
        /// <summary>
        /// message header
        /// </summary>
        public MessageHeader HEADER { get; set; }
        
        /// <summary>
        /// list of mesage parameters
        /// </summary>
        public MessageParametersList LISTOFPARAMETERS { get; set; }

        /// <summary>
        /// Creates empty Message
        /// </summary>
        public Message()
        {

        }

        /// <summary>
        /// Creates Message object from existing header and list of parameters
        /// </summary>
        public Message(MessageHeader header, MessageParametersList listOfParameters)
        {
            if (header == null)
                throw new ArgumentNullException("header");
            if (listOfParameters == null)
                throw new ArgumentNullException("list of parameters");

            this.HEADER = header;
            this.LISTOFPARAMETERS = listOfParameters;
        }

        public override string ToString()
        {
            StringBuilder res = new StringBuilder();
            
            if (HEADER == null || LISTOFPARAMETERS == null)
                return String.Empty;

            res.Append(HEADER.ToString());
            res.Append(String.Empty);
            res.Append(LISTOFPARAMETERS.ToString());

            return res.ToString();
        }

    }

}
