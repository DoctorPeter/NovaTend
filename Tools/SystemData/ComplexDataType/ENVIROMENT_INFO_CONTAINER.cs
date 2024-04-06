using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class ENVIROMENT_INFO_CONTAINER : ISerializableObject
    {
        public string activeProgramName { get; set; }

        public int userDowntime { get; set; }
        
        private string[] _programNamesList;

        public string[] programNamesList
        {
            get
            {
                return (string[])_programNamesList.Clone();
            }
            set { _programNamesList = value; }
        }

    }
}
