using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_GET_COMPUTER_NAME : WDCCommand
    {
        public CMD_GET_COMPUTER_NAME()
            : base(WDCCommandType.CMD_GET_COMPUTER_NAME)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if ((input == null) || 
                (input != null) && 
                ((input.Count == 0) || 
                 (input.Count == 1) &&
                 (input[0].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA)))
                return true;

            return false;
        }

        internal override bool ValidateResult(MessageParametersList result)
        {
            if (result != null &&
                result.Count == 1 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.STRING_DATA)
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
