using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class ANSWER_DESCRIPTOR : ISerializableObject
    {

        public int questionID { get; set; }

        public int rightAnswerID { get; set; }

        /// <summary>
        /// For serializing: need to specify string length in the begin of serialized value (4 bytes)
        /// </summary>
        public string answerValue { get; set; }

        public ANSWER_DESCRIPTOR()
        { }

    }

}
