using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_GET_DB_ACCESS : WDCCommand
    {
        //User permissions

        // System supervisor
        public const int DB_ACCESS_SUPERVISOR = 0;

        // System admininstrator
        public const int DB_ACCESS_SYS_ADMIN = 1;

        // Screen designer
        public const int DB_ACCESS_SCREEN_DESIGNER = 2;

        // Education manager
        public const int DB_ACCESS_EDU_MANAGER = 3;

        // Notification manager
        public const int DB_ACCESS_NOTICE_MANAGER = 4;

        // License manager
        public const int DB_ACCESS_LICENSE_MANAGER = 5;

        // Dashboard manager
        public const int DASHBOARD_ACCESS_MANAGER = 6;

        // Schedule manager
        public const int SCHEDULE_MANAGER = 7;

        // Maximum permisions count
        public const int MAX_PERMISSIONS_COUNT = 32;

        public CMD_GET_DB_ACCESS()
            : base(WDCCommandType.CMD_GET_DB_ACCESS)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input != null &&
                input.Count == 4 &&
                input[0].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA &&
                input[1].ParameterDataType == ParameterDataTypeEnum.ENCRYPTED_DATA &&
                input[2].ParameterDataType == ParameterDataTypeEnum.TIMEINFO_DATA &&
                input[3].ParameterDataType == ParameterDataTypeEnum.SYMBOL_BOXES_DATA
               )
                return true;

            return false;
        }

        internal override bool ValidateResult(MessageParametersList result)
        {
            if (result != null &&
                result.Count == 1 &&
                result[0].ParameterDataType == ParameterDataTypeEnum.USER_DB_ACCESS_DATA)
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
