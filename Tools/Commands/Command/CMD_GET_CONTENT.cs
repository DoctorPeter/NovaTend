﻿using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_GET_CONTENT : WDCCommand
    {
        public CMD_GET_CONTENT()
            : base(WDCCommandType.CMD_GET_CONTENT)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input == null || 
                (input != null &&
                 input.Count == 3 &&
                 input[0].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                 input[1].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA &&
                 input[2].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA
                )
               )
                return true;

            return false;
        }

        internal override bool ValidateResult(MessageParametersList result)
        {
            if (result != null &&
                result.Count == 1 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.PRESET_CONTAINER_DATA)
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
