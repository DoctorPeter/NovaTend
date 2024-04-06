using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_SET_USER_SIGNIN_DATE : WDCCommand
    {
        public CMD_SET_USER_SIGNIN_DATE()
            : base(WDCCommandType.CMD_SET_USER_SIGNIN_DATE)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input != null &&
                 input.Count == 2 &&
                 input[0].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA &&
                 input[1].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA
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
