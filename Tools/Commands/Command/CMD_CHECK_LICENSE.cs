using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_CHECK_LICENSE: WDCCommand
    {
        public CMD_CHECK_LICENSE()
            : base(WDCCommandType.CMD_CHECK_LICENSE)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input != null &&
                input.Count == 1 &&
                input[0].ParameterDataType == ParameterDataTypeEnum.CLIENT_DESCRIPTION_DATA)
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

