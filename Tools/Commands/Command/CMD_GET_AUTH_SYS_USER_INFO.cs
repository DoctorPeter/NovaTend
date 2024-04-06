using SystemData;
using SystemData.Message;


namespace Commands
{
    public class CMD_GET_AUTH_SYS_USER_INFO : WDCCommand
    {
        public CMD_GET_AUTH_SYS_USER_INFO()
            : base(WDCCommandType.CMD_GET_AUTH_SYS_USER_INFO)
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
                result.Count == 4 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.ENCRYPTED_DATA &&
                result[1].ParameterDataType == ParameterDataTypeEnum.ENCRYPTED_DATA &&
                result[2].ParameterDataType == ParameterDataTypeEnum.ENCRYPTED_DATA &&
                result[3].ParameterDataType == ParameterDataTypeEnum.ENCRYPTED_DATA)
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
