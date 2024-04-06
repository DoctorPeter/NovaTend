using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_LOCK_USER_CAD_ACTIONS : WDCCommand
    {
        public CMD_LOCK_USER_CAD_ACTIONS()
            : base(WDCCommandType.CMD_LOCK_USER_CAD_ACTIONS)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input != null &&
                 input.Count == 2 &&
                 input[0].ParameterDataType == ParameterDataTypeEnum.BYTE_DATA &&
                 input[1].ParameterDataType == ParameterDataTypeEnum.STRING_DATA
               )
                return true;

            return false;
        }

        internal override bool ValidateResult(MessageParametersList result)
        {
            if (result != null &&
                result.Count == 1 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.BYTE_DATA)
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