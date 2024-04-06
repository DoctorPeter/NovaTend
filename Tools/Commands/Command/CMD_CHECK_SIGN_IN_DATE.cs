using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_CHECK_SIGN_IN_DATE : WDCCommand
    {
        public CMD_CHECK_SIGN_IN_DATE()
            : base(WDCCommandType.CMD_CHECK_SIGN_IN_DATE)
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
