using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_GET_HARDWARE_INFO : WDCCommand
    {
        public CMD_GET_HARDWARE_INFO()
            : base(WDCCommandType.CMD_GET_HARDWARE_INFO)
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
                result.Count == 14 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[1].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[2].ParameterDataType == ParameterDataTypeEnum.LONG_DATA &&
                result[3].ParameterDataType == ParameterDataTypeEnum.LONG_DATA &&
                result[4].ParameterDataType == ParameterDataTypeEnum.LONG_DATA &&
                result[5].ParameterDataType == ParameterDataTypeEnum.LONG_DATA &&
                result[6].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[7].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[8].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[9].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[10].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[11].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[12].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                result[13].ParameterDataType == ParameterDataTypeEnum.LONG_DATA)
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
