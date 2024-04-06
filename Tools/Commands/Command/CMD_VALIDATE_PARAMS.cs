﻿using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_VALIDATE_PARAMS : WDCCommand
    {
        public CMD_VALIDATE_PARAMS()
            : base(WDCCommandType.CMD_VALIDATE_PARAMS)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input != null &&
                 input.Count == 3 &&
                 input[0].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA &&
                 input[1].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                 input[2].ParameterDataType == ParameterDataTypeEnum.AUTH_CONTAINER_DATA
               )
                return true;

            return false;
        }

        internal override bool ValidateResult(MessageParametersList result)
        {
            if (result != null &&
                result.Count == 1 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA)
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
