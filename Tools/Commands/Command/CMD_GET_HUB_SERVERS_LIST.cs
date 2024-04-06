using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_GET_HUB_SERVERS_LIST : WDCCommand
    {
        public CMD_GET_HUB_SERVERS_LIST()
            : base(WDCCommandType.CMD_GET_HUB_SERVERS_LIST)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input == null)
                return true;

            return false;
        }

        internal override bool ValidateResult(MessageParametersList result)
        {
            if (result != null &&
                result.Count == 1 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.SERVER_DESCRIPTION_LIST_DATA)
                return true;

            return false;
        }

        internal override void PreExecute()
        {
            return;
        }

        internal override void PostExecute()
        {
            return;
        }
    }
}