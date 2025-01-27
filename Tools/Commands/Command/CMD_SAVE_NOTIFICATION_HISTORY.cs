﻿using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_SAVE_NOTIFICATION_HISTORY : WDCCommand
    {
        public CMD_SAVE_NOTIFICATION_HISTORY()
            : base(WDCCommandType.CMD_SAVE_NOTIFICATION_HISTORY)
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
