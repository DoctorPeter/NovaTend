using SystemData;
using SystemData.Message;

namespace Commands
{
    public class CMD_RESET_USER_PASSWORD : WDCCommand
    {
        // Responce error codes

        // Successful response validation
        public const int RESPONSE_OK = 0;

        // Fail response validation
        public const int RESPONSE_BAD = -1;

        // Password expired
        public const int RESPONSE_PWD_EXPIRED = -2;

        // Account locked
        public const int RESPONSE_ACCOUNT_LOCKED = -3;

        // User not found
        public const int RESET_PWD_USER_NOT_FOUND = -4;

        // User password already resetted
        public const int RESET_PWD_ALREADY_RESETTED = -5;

        // Wrong user email address
        public const int RESET_PWD_WRONG_EMAIL_ADDRESS = -6;

        // Wrong user phone number
        public const int RESET_PWD_WRONG_PHONE_NUMBER = -7;

        // Email sending error
        public const int RESET_PWD_EMAIL_SEND_ERROR = -8;

        // SMS sending error
        public const int RESET_PWD_SMS_SEND_ERROR = -9;

        public CMD_RESET_USER_PASSWORD()
            : base(WDCCommandType.CMD_RESET_USER_PASSWORD)
        {

        }

        internal override bool ValidateInput(MessageParametersList input)
        {
            if (input != null &&
                input.Count == 1 &&
                input[0].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA)
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