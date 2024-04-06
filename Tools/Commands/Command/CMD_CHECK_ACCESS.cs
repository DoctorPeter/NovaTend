using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_CHECK_ACCESS : WDCCommand
    {
        public CMD_CHECK_ACCESS()
            : base(WDCCommandType.CMD_CHECK_ACCESS)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input == null)
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
