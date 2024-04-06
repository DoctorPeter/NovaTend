using SystemData;
using SystemData.Message;


namespace Commands
{
    public class CMD_GET_FULL_CLIENT_INFO : WDCCommand
    {
        public CMD_GET_FULL_CLIENT_INFO()
            : base(WDCCommandType.CMD_GET_FULL_CLIENT_INFO)
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
                result.Count == 20 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA &&
                result[1].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA &&
                result[2].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[3].ParameterDataType == ParameterDataTypeEnum.ENVIROMENT_INFO_CONTAINER_DATA &&
                result[4].ParameterDataType == ParameterDataTypeEnum.BINARY_DATA &&
                result[5].ParameterDataType == ParameterDataTypeEnum.BINARY_DATA &&
                result[6].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[7].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[8].ParameterDataType == ParameterDataTypeEnum.LONG_DATA &&
                result[9].ParameterDataType == ParameterDataTypeEnum.LONG_DATA &&
                result[10].ParameterDataType == ParameterDataTypeEnum.LONG_DATA &&
                result[11].ParameterDataType == ParameterDataTypeEnum.LONG_DATA &&
                result[12].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[13].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[14].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[15].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[16].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[17].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[18].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[19].ParameterDataType == ParameterDataTypeEnum.LONG_DATA)
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
