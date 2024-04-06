using System;
using SystemData;
using SystemData.SerializableObject;

namespace SystemData.Message
{
    /// <summary>
    /// parameter list to pass with message
    /// </summary>
    public class MessageParametersList: SerializableList<MessageParameter>
    {
        public MessageParametersList()
        {

        }

        public override string ToString()
        {
            return String.Format("parameter list. Count of params: {0}", this.Count);
        }
    }
}
