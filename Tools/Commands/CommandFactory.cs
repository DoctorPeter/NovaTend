namespace Commands
{
    /// <summary>
    /// factory to produce commands from parameter command type
    /// </summary>
    public static class CommandFactory
    {
        /// <summary>
        /// Produce command from parameter type
        /// </summary>
        /// <param name="type">type of command</param>
        /// <returns>
        /// concrete command for valid type.
        /// null for unrecognized type.
        /// </returns>
        public static IWDCCommand GetCommand(WDCCommandType type)
        {
            switch (type)
            {

                case WDCCommandType.CMD_CHECK_ACCESS:
                    return new CMD_CHECK_ACCESS();
                case WDCCommandType.CMD_CHECK_LICENSE:
                    return new CMD_CHECK_LICENSE();
                case WDCCommandType.CMD_GET_CONTENT:
                    return new CMD_GET_CONTENT();
                case WDCCommandType.CMD_GET_USER_LIST:
                    return new CMD_GET_USER_LIST();
                case WDCCommandType.CMD_GET_USER_DESCRIPTOR:
                    return new CMD_GET_USER_DESCRIPTOR();
                case WDCCommandType.CMD_VALIDATE_PARAMS:
                    return new CMD_VALIDATE_PARAMS();
                case WDCCommandType.CMD_VALIDATE_ANSWERS:
                    return new CMD_VALIDATE_ANSWERS();
                case WDCCommandType.CMD_VALIDATE_USER_CUSTOM_PASSWORDS:
                    return new CMD_VALIDATE_USER_CUSTOM_PASSWORDS();
                case WDCCommandType.CMD_SET_USER_SIGNIN_DATE:
                    return new CMD_SET_USER_SIGNIN_DATE();
                case WDCCommandType.CMD_SAVE_NOTIFICATION_HISTORY:
                    return new CMD_SAVE_NOTIFICATION_HISTORY();
                case WDCCommandType.CMD_GET_DB_ACCESS:
                    return new CMD_GET_DB_ACCESS();
                case WDCCommandType.CMD_GET_AUTH_SYSTEM:
                    return new CMD_GET_AUTH_SYSTEM();
                case WDCCommandType.CMD_CHECK_SIGN_IN_DATE:
                    return new CMD_CHECK_SIGN_IN_DATE();
                case WDCCommandType.CMD_VALIDATE_USER_ACCOUNT:
                    return new CMD_VALIDATE_USER_ACCOUNT();
                case WDCCommandType.CMD_RESET_USER_PASSWORD:
                    return new CMD_RESET_USER_PASSWORD();
                case WDCCommandType.CMD_LOCK_USER_CAD_ACTIONS:
                    return new CMD_LOCK_USER_CAD_ACTIONS();
                case WDCCommandType.CMD_GET_HUB_SERVERS_LIST:
                    return new CMD_GET_HUB_SERVERS_LIST();
                case WDCCommandType.CMD_GET_CLIENT_SCREEN_SHOT:
                    return new CMD_GET_CLIENT_SCREEN_SHOT();
                case WDCCommandType.CMD_GET_CLIENT_CAM_SNAPSHOT:
                    return new CMD_GET_CLIENT_CAM_SNAPSHOT();
                case WDCCommandType.CMD_GET_USER_ENV_INFO:
                    return new CMD_GET_USER_ENV_INFO();
                case WDCCommandType.CMD_GET_HARDWARE_INFO:
                    return new CMD_GET_HARDWARE_INFO();
                case WDCCommandType.CMD_GET_LOGGED_USER_ID:
                    return new CMD_GET_LOGGED_USER_ID();
                case WDCCommandType.CMD_GET_COMPUTER_NAME:
                    return new CMD_GET_COMPUTER_NAME();
                case WDCCommandType.CMD_GET_AUTH_SYS_USER_INFO:
                    return new CMD_GET_AUTH_SYS_USER_INFO();
                case WDCCommandType.CMD_GET_FULL_CLIENT_INFO:
                    return new CMD_GET_FULL_CLIENT_INFO();
                case WDCCommandType.CMD_CHECK_SCHEDULE:
                    return new CMD_CHECK_SCHEDULE();

                default:
                    return null;
            }

            return null;
        }
    }
}
