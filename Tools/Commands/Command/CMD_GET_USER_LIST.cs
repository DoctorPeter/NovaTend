using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_GET_USER_LIST : WDCCommand
    {
        public CMD_GET_USER_LIST()
            : base(WDCCommandType.CMD_GET_USER_LIST)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if ((input == null) || (input.Count == 0))
                return true;

            return false;
        }

        internal override bool ValidateResult(MessageParametersList result)
        {
            if (result != null &&
                result.Count == 1 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.USER_LIST_DATA)
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