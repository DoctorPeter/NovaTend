using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_VALIDATE_USER_CUSTOM_PASSWORDS : WDCCommand
    {
        public CMD_VALIDATE_USER_CUSTOM_PASSWORDS()
            : base(WDCCommandType.CMD_VALIDATE_USER_CUSTOM_PASSWORDS)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input != null &&
                input.Count == 5 &&
                input[0].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA &&
                input[1].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA &&
                input[2].ParameterDataType == ParameterDataTypeEnum.ENCRYPTED_DATA &&
                input[3].ParameterDataType == ParameterDataTypeEnum.TIMEINFO_DATA &&
                input[4].ParameterDataType == ParameterDataTypeEnum.SYMBOL_BOXES_DATA
               )
                return true;

            return false;
        }

        internal override bool ValidateResult(MessageParametersList result)
        {
            if (result != null &&
                result.Count == 2 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA &&
                result[1].ParameterDataType == ParameterDataTypeEnum.USER_PRIVATE_DATA)
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
