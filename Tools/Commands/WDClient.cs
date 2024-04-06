using System;
using System.Linq;

using Commands;
using SystemData;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;
using SystemData.Message;


namespace CommandClient
{
    /// <summary>
    /// Windows desktop client (main client to perform operations)
    /// </summary>
    public class WDClient : IWDClient
    {
        public WDClient()
        {

        }

        /// <summary>
        /// Execute CMD_CHECK_LICENSE
        /// </summary>
        /// <param name="clientDescription">
        /// CLIENT_DESCRIPTION
        /// </param>
        /// <returns>
        /// false - license not valid
        /// true - license valid
        /// null - if error
        /// </returns>
        public bool? CHECK_LICENSE(CLIENT_DESCRIPTION clientDescription,
            uint? recepientID = null)
        {
            try
            {
                if (clientDescription == null)
                    throw new ArgumentNullException("clientDescription");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, clientDescription)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_CHECK_LICENSE).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (byte)result.First().Parameter != 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_CONTENT
        /// </summary>
        /// <returns>
        /// PRESET_CONTAINER object
        /// null - if error
        /// </returns>
        public PRESET_CONTAINER GET_CONTENT(
            uint? recepientID = null)
        {
            try
            {
                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_CONTENT).Execute(null, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as PRESET_CONTAINER;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_CONTENT
        /// </summary>
        /// <param name="computerName"></param>
        /// <param name="userID"></param>
        /// <param name="OSID"></param>
        /// <returns>
        /// PRESET_CONTAINER object
        /// null - if error
        /// </returns>
        public PRESET_CONTAINER GET_CONTENT(string computerName, uint userID, uint OSID,
            uint? recepientID = null)
        {
            try
            {
                if (String.IsNullOrEmpty(computerName))
                    throw new ArgumentNullException("computerName");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, computerName),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, OSID),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_CONTENT).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as PRESET_CONTAINER;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_USER_LIST
        /// </summary>
        /// <returns>
        /// USER_LIST object
        /// null - if error
        /// </returns>
        public USER_LIST GET_USER_LIST(
            uint? recepientID = null)
        {
            try
            {
                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_USER_LIST).Execute(null, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as USER_LIST;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_USER_DESCRIPTOR
        /// </summary>
        /// <param name="userID"></param>
        /// <returns>
        /// USER_DESCRIPTOR object
        /// null - if error
        /// </returns>
        public USER_DESCRIPTOR GET_USER_DESCRIPTOR(uint userID,
            uint? recepientID = null)
        {
            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_USER_DESCRIPTOR).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as USER_DESCRIPTOR;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_USER_DESCRIPTOR
        /// </summary>
        /// <param name="encryptedUserName"></param>
        /// <returns>
        /// USER_DESCRIPTOR object
        /// null - if error
        /// </returns>
        public USER_DESCRIPTOR GET_USER_DESCRIPTOR(byte[] encryptedUserName,
            uint? recepientID = null)
        {
            try
            {
                if (encryptedUserName == null || encryptedUserName.Length == 0)
                    throw new ArgumentNullException("encryptedUserName");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, encryptedUserName, true)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_USER_DESCRIPTOR).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as USER_DESCRIPTOR;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_USER_DESCRIPTOR
        /// </summary>
        /// <param name="encryptedUserName"></param>
        /// <param name="authenticationSystemID"></param>
        /// <returns>
        /// USER_DESCRIPTOR object
        /// null - if error
        /// </returns>
        public USER_DESCRIPTOR GET_USER_DESCRIPTOR(byte[] encryptedUserName, uint authenticationSystemID,
            uint? recepientID = null)
        {
            try
            {
                if (encryptedUserName == null || encryptedUserName.Length == 0)
                    throw new ArgumentNullException("encryptedUserName");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, encryptedUserName, true),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, authenticationSystemID)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_USER_DESCRIPTOR).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as USER_DESCRIPTOR;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute CHECK_ACCESS
        /// </summary>
        /// <returns>
        /// false - there is no access to DB server
        /// true - DB server is available
        /// null - if error
        /// </returns>
        public bool? CHECK_ACCESS(
            uint? recepientID = null)
        {
            try
            {
                var result = CommandFactory.GetCommand(WDCCommandType.CMD_CHECK_ACCESS).Execute(null, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (byte)result.First().Parameter != 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute VALIDATE_PARAMS
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="compName"></param>
        /// <param name="authenticationContainer"></param>
        /// <returns>
        /// false - validation failed
        /// true - validation successfully completed
        /// null - if error
        /// </returns>
        public bool? VALIDATE_PARAMS(uint userID, string compName, AUTH_CONTAINER authenticationContainer,
            uint? recepientID = null)
        {
            try
            {
                if (authenticationContainer == null)
                    throw new ArgumentNullException("authenticationContainer");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, compName),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, authenticationContainer)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_VALIDATE_PARAMS).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (uint)result.First().Parameter == 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute VALIDATE_ANSWERS
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="userAnswersContainer"></param>
        /// <returns>
        /// false - validation failed
        /// true - validation successfully completed
        /// null - if error
        /// </returns>
        public bool? VALIDATE_ANSWERS(uint userID, string compName, ANSWER_CONTAINER userAnswersContainer,
            uint? recepientID = null)
        {
            try
            {
                if (userAnswersContainer == null)
                    throw new ArgumentNullException("authenticationContainer");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, compName),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userAnswersContainer)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_VALIDATE_ANSWERS).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (uint)result.First().Parameter == 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute VALIDATE_USER_CUSTOM_PASSWORDS
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="authenticationSystemID"></param>
        /// <param name="encryptedStringUserPassword"></param>
        /// <param name="timeStructure"></param>
        /// <param name="listOfSymbolBoxes"></param>
        /// <param name="validationResult">
        /// 0 – validation successfully completed
        /// (-1) – wrong password
        /// (-2) – password expired
        /// (-3) – user account locked
        /// </param>
        /// <param name="userSecurityData">USER_SECURITY_DATA</param>
        /// <returns>
        /// false - validation failed
        /// true - validation successfully completed
        /// null - if error
        /// </returns>
        public bool? VALIDATE_USER_CUSTOM_PASSWORDS(uint userID, uint authenticationSystemID, byte[] encryptedStringUserPassword, TIME_INFO timeStructure, UTF8_STRINGS_MATRIX_LIST listOfSymbolBoxes,
            out uint validationResult, out USER_SECURITY_DATA userSecurityData,
            uint? recepientID = null)
        {
            validationResult = 0;
            userSecurityData = null;

            try
            {
                if (encryptedStringUserPassword == null || encryptedStringUserPassword.Length == 0)
                    throw new ArgumentNullException("encryptedStringUserPassword");
                if (timeStructure == null)
                    throw new ArgumentNullException("timeStructure");
                if (listOfSymbolBoxes == null)
                    throw new ArgumentNullException("listOfSymbolBoxes");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, authenticationSystemID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, encryptedStringUserPassword, true),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, timeStructure),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, listOfSymbolBoxes),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_VALIDATE_USER_CUSTOM_PASSWORDS).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                validationResult = (uint)result.First().Parameter;
                userSecurityData = result[1].Parameter as USER_SECURITY_DATA;

                return validationResult == 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute SET_USER_SIGNIN_DATE
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="authenticationSystemID"></param>
        /// <param name="errorFlag">
        /// 0 – can’t save user date of user log in
        /// other value – date when user logged in is successfully saved
        /// </param>
        /// <returns>
        /// false - if can’t save user date of user log in
        /// true - user logged in is successfully saved
        /// null - if error
        /// </returns>
        public bool? SET_USER_SIGNIN_DATE(uint userID, uint authenticationSystemID,
            out byte errorFlag,
            uint? recepientID = null)
        {
            errorFlag = byte.MinValue;

            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, authenticationSystemID)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_SET_USER_SIGNIN_DATE).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                errorFlag = (byte)result.First().Parameter;

                return errorFlag != 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute SAVE_NOTIFICATION_HISTORY
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="noticeID"></param>
        /// <returns>
        /// false - can’t save user notification history
        /// true - user notification history is successfully saved
        /// null - if error
        /// </returns>
        public bool? SAVE_NOTIFICATION_HISTORY(uint userID, uint noticeID,
            uint? recepientID = null)
        {
            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, noticeID)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_SAVE_NOTIFICATION_HISTORY).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (byte)result.First().Parameter != 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_DB_ACCESS
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="authenticationSystemID"></param>
        /// <param name="encryptedStringUserPassword"></param>
        /// <param name="timeStructure"></param>
        /// <param name="listOfSymbolBoxes"></param>
        /// <returns>
        /// USER_DB_ACCESS_INFO container with DB connection data
        /// null if error
        /// </returns>
        public USER_DB_ACCESS_INFO GET_DB_ACCESS(uint userID, byte[] encryptedStringUserPassword, TIME_INFO timeStructure, UTF8_STRINGS_MATRIX_LIST listOfSymbolBoxes,
            uint? recepientID = null)
        {
            try
            {
                if (encryptedStringUserPassword == null || encryptedStringUserPassword.Length == 0)
                    throw new ArgumentNullException("encryptedStringUserPassword");
                if (timeStructure == null)
                    throw new ArgumentNullException("timeStructure");
                if (listOfSymbolBoxes == null)
                    throw new ArgumentNullException("listOfSymbolBoxes");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, encryptedStringUserPassword, true),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, timeStructure),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, listOfSymbolBoxes)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_DB_ACCESS).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as USER_DB_ACCESS_INFO;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_AUTH_SYSTEM
        /// </summary>
        /// <param name="encryptedAuthenticationSystemSettingsString"></param>
        /// <param name="authenticationSystemType"></param>
        /// <returns>
        /// - authentication system ID
        /// - null if error
        /// </returns>
        public uint? GET_AUTH_SYSTEM(byte[] encryptedAuthenticationSystemSettingsString, uint authenticationSystemType,
            uint? recepientID = null)
        {
            try
            {
                if (encryptedAuthenticationSystemSettingsString == null || encryptedAuthenticationSystemSettingsString.Length == 0)
                    throw new ArgumentNullException("encryptedAuthenticationSystemSettingsString");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, encryptedAuthenticationSystemSettingsString, true),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, authenticationSystemType)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_AUTH_SYSTEM).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (uint)result.First().Parameter;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute CHECK_SCHEDULE
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="compName"></param>
        /// <param name="funcID"></param>
        /// <param name="recepientID"></param>
        /// <returns>
        /// - action code
        /// - null if error
        /// </returns>
        public uint? CHECK_SCHEDULE(uint userID, string compName, uint funcID,
            uint? recepientID = null)
        {
            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, compName),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, funcID)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_CHECK_SCHEDULE).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (uint)result.First().Parameter;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute CHECK_SIGN_IN_DATE
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="authenticationSystemID"></param>
        /// <returns>
        /// false - user tries to log in the first time
        /// true - user is already logged in today
        /// null - if error
        /// </returns>
        public bool? CHECK_SIGN_IN_DATE(uint userID, uint authenticationSystemID,
            uint? recepientID = null)
        {
            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, authenticationSystemID)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_CHECK_SIGN_IN_DATE).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (byte)result.First().Parameter == 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute VALIDATE_USER_ACCOUNT
        /// </summary>
        /// <param name="encryptedStringUserName"></param>
        /// <param name="encryptedStringUserPassword"></param>
        /// <param name="authenticationSystemID"></param>
        /// <returns>
        /// false - validation failed
        /// true - validation successfully completed
        /// null - if error
        /// </returns>
        public bool? VALIDATE_USER_ACCOUNT(byte[] encryptedStringUserName, byte[] encryptedStringUserPassword, uint authenticationSystemID,
            uint? recepientID = null)
        {
            try
            {
                if (encryptedStringUserName == null || encryptedStringUserName.Length == 0)
                    throw new ArgumentNullException("encryptedStringUserName");
                if (encryptedStringUserPassword == null || encryptedStringUserPassword.Length == 0)
                    throw new ArgumentNullException("encryptedStringUserPassword");


                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, encryptedStringUserName, true),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, encryptedStringUserPassword, true),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, authenticationSystemID)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_VALIDATE_USER_ACCOUNT).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (byte)result.First().Parameter != 0;

            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute RESET_USER_PASSWORD
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="passwordResetResul">
        /// (-1) – can’t reset password for this user
        /// (-3) – user account locked
        /// (-4) – user ID not found
        /// (-5) – password has been reset already
        /// (-6) – wrong email address
        /// (-7) – wrong phone number
        /// (-8) – error of email sending
        /// (-9) – error of SMS sending 
        /// </param>
        /// <returns>
        /// false - password isn't reseted
        /// true - password has been successfully reset
        /// null - if error 
        /// </returns>
        public bool? RESET_USER_PASSWORD(uint userID,
            out uint passwordResetResult,
            uint? recepientID = null)
        {
            passwordResetResult = uint.MinValue;

            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_RESET_USER_PASSWORD).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                passwordResetResult = (uint)result.First().Parameter;

                return passwordResetResult == 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute LOCK_USER_CAD_ACTIONS
        /// </summary>
        /// <param name="lockFlag">
        /// lock flag (BYTE_DATA) (1 – lock CTRL+ALT+DEL, 0 – unlock CTRL+ALT+DEL)
        /// </param>
        /// <param name="userName"></param>
        /// <returns>
        /// false - fail
        /// true - sucess
        /// null - if error 
        /// </returns>
        public bool? LOCK_USER_CAD_ACTIONS(byte lockFlag, string userName,
            uint? recepientID = null)
        {
            try
            {
                if (String.IsNullOrEmpty(userName))
                    throw new ArgumentNullException("userName");

                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, lockFlag),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userName)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_LOCK_USER_CAD_ACTIONS).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (byte)result.First().Parameter != 0;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_HUB_SERVERS_LIST
        /// </summary>
        /// <returns>
        /// SERVER_DESCRIPTION_LIST - list of HUB-server descriptions
        /// null - if error
        /// </returns>
        public SERVER_DESCRIPTION_LIST GET_HUB_SERVERS_LIST(
            uint? recepientID = null)
        {
            try
            {
                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_HUB_SERVERS_LIST).Execute(null, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as SERVER_DESCRIPTION_LIST;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_CLIENT_SCREEN_SHOT
        /// </summary>
        /// <returns>
        /// byte[] - BMP image
        /// null - if error
        /// </returns>
        public byte[] GET_CLIENT_SCREEN_SHOT(uint userID,
            uint? recepientID = null)
        {
            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_CLIENT_SCREEN_SHOT).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (byte[])result.First().Parameter;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_CLIENT_CAM_SNAPSHOT
        /// </summary>
        /// <returns>
        /// byte[] - BMP image
        /// null - if error
        /// </returns>
        public byte[] GET_CLIENT_CAM_SNAPSHOT(uint userID,
            uint? recepientID = null)
        {
            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_CLIENT_CAM_SNAPSHOT).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return (byte[])result.First().Parameter;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_USER_ENV_INFO
        /// </summary>
        /// <param name="foregroundWindowName"></param>
        /// <param name="listOfApplications"></param>
        /// <returns>
        /// true - get sucess
        /// false - if error
        /// </returns>
        public ENVIROMENT_INFO_CONTAINER GET_USER_ENV_INFO(uint userID, uint? recepientID = null)
        {
            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_USER_ENV_INFO).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as ENVIROMENT_INFO_CONTAINER;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_COMPUTER_NAME
        /// </summary>
        public string GET_COMPUTER_NAME(uint userID, uint? recepientID = null)
        {
            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_COMPUTER_NAME).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return null;

                return result.First().Parameter as string;
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Execute GET_AUTH_SYS_USER_INFO
        /// </summary>
        public bool GET_AUTH_SYS_USER_INFO(uint userID, 
                                            uint authSystemID,
                                            out byte[] encAuthSystemName,
                                            out byte[] encUserName,
                                            out byte[] encSysUserName,
                                            out byte[] encFullUserName,
                                            uint? recepientID = null)
        {
            encAuthSystemName = null;
            encUserName = null;
            encSysUserName = null;
            encFullUserName = null;

            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, authSystemID)
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_AUTH_SYS_USER_INFO).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return false;

                if (result.Count == 4)
                {
                   encAuthSystemName = (byte[])result[0].Parameter;
                   encUserName = (byte[])result[1].Parameter;
                   encSysUserName = (byte[])result[2].Parameter;
                   encFullUserName = (byte[])result[3].Parameter;

                   return true;
                }
                else
                    return false;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        /// <summary>
        /// Execute GET_HARDWARE_INFO
        /// </summary>
        /// <param name="OSversion"></param>
        /// <param name="CPUname"></param>
        /// <param name="amountOfPhysicalMemory"></param>
        /// <param name="amountOfUsedPhysicalMemory"></param>
        /// <param name="amountOfVirtualMemory"></param>
        /// <param name="amountOfUsedVirtualMemory"></param>
        /// <param name="motherboardManufacturerName"></param>
        /// <param name="motherboarProductName"></param>
        /// <param name="BIOSVersionName"></param>
        /// <param name="chipsetName"></param>
        /// <param name="videoAdapterName"></param>
        /// <param name="monitorName"></param>
        /// <param name="amountOfVideoMemory"></param>
        /// <returns>
        /// true - get sucess, 
        /// false - if error
        /// </returns>
        public bool GET_HARDWARE_INFO(uint userID,
            out string OSversion, out string CPUname, out long amountOfPhysicalMemory, out long amountOfUsedPhysicalMemory, out long amountOfVirtualMemory, out long amountOfUsedVirtualMemory, out string motherboardManufacturerName, out string motherboarProductName, out string BIOSManufacturerName, out string BIOSVersionName, out string chipsetName, out string videoAdapterName, out string monitorName, out long amountOfVideoMemory,
            uint? recepientID = null)
        {
            OSversion = String.Empty;
            CPUname = String.Empty;
            amountOfPhysicalMemory = long.MinValue;
            amountOfUsedPhysicalMemory = long.MinValue;
            amountOfVirtualMemory = long.MinValue;
            amountOfUsedVirtualMemory = long.MinValue;
            motherboardManufacturerName = String.Empty;
            motherboarProductName = String.Empty;
            BIOSManufacturerName = String.Empty;
            BIOSVersionName = String.Empty;
            chipsetName = String.Empty;
            videoAdapterName = String.Empty;
            monitorName = String.Empty;
            amountOfVideoMemory = long.MinValue;

            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, userID),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_HARDWARE_INFO).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return false;

                OSversion = (string)result[0].Parameter;
                CPUname = (string)result[1].Parameter;
                amountOfPhysicalMemory = (long)result[2].Parameter;
                amountOfUsedPhysicalMemory = (long)result[3].Parameter;
                amountOfVirtualMemory = (long)result[4].Parameter;
                amountOfUsedVirtualMemory = (long)result[5].Parameter;
                motherboardManufacturerName = (string)result[6].Parameter;
                motherboarProductName = (string)result[7].Parameter;
                BIOSManufacturerName = (string)result[8].Parameter;
                BIOSVersionName = (string)result[9].Parameter;
                chipsetName = (string)result[10].Parameter;
                videoAdapterName = (string)result[11].Parameter;
                monitorName = (string)result[12].Parameter;
                amountOfVideoMemory = (long)result[13].Parameter;

                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        /// <summary>
        /// /// Execute GET_LOGGED_USER_ID
        /// </summary>
        /// <param name="userID"></param>
        /// <param name="authenticationSystemID"></param>
        /// <returns>
        /// true - get sucess
        /// false - if error
        /// </returns>
        public bool GET_LOGGED_USER_ID(uint vUserID,
            out uint userID, out uint authenticationSystemID,
            uint? recepientID = null)
        {
            userID = uint.MinValue;
            authenticationSystemID = uint.MinValue;

            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, vUserID),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_LOGGED_USER_ID).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return false;

                userID = (uint)result[0].Parameter;
                authenticationSystemID = (uint)result[1].Parameter;

                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        /// <summary>
        /// /// Execute GET_FULL_CLIENT_INFO
        /// </summary>
        public bool GET_FULL_CLIENT_INFO(
            uint vUserID,
            out uint userID, 
            out uint authenticationSystemID,
            out string computerName,
            out ENVIROMENT_INFO_CONTAINER envContainer,
            out byte[] screenShot,
            out byte[] camSnapShot,
            out string OSversion, 
            out string CPUname, 
            out long amountOfPhysicalMemory, 
            out long amountOfUsedPhysicalMemory, 
            out long amountOfVirtualMemory, 
            out long amountOfUsedVirtualMemory, 
            out string motherboardManufacturerName, 
            out string motherboarProductName, 
            out string BIOSManufacturerName, 
            out string BIOSVersionName, 
            out string chipsetName, 
            out string videoAdapterName, 
            out string monitorName, 
            out long amountOfVideoMemory,
            uint? recepientID = null)
        {
            userID = uint.MinValue;
            authenticationSystemID = uint.MinValue;
            computerName = String.Empty; ;
            envContainer = null;
            screenShot = null;
            camSnapShot = null;
            OSversion = String.Empty;
            CPUname = String.Empty;
            amountOfPhysicalMemory = long.MinValue;
            amountOfUsedPhysicalMemory = long.MinValue;
            amountOfVirtualMemory = long.MinValue;
            amountOfUsedVirtualMemory = long.MinValue;
            motherboardManufacturerName = String.Empty;
            motherboarProductName = String.Empty;
            BIOSManufacturerName = String.Empty;
            BIOSVersionName = String.Empty;
            chipsetName = String.Empty;
            videoAdapterName = String.Empty;
            monitorName = String.Empty;
            amountOfVideoMemory = long.MinValue;

            try
            {
                var input = new MessageParametersList()
                {
                    new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, vUserID),
                };

                var result = CommandFactory.GetCommand(WDCCommandType.CMD_GET_FULL_CLIENT_INFO).Execute(input, recepientID);

                if (result == null || result.Count == 0)
                    return false;

                userID = (uint)result[0].Parameter;
                authenticationSystemID = (uint)result[1].Parameter;
                computerName = (string)result[2].Parameter;
                envContainer = result[3].Parameter as ENVIROMENT_INFO_CONTAINER;
                screenShot = (byte[])result[4].Parameter;
                camSnapShot = (byte[])result[5].Parameter;
                OSversion = (string)result[6].Parameter;
                CPUname = (string)result[7].Parameter;
                amountOfPhysicalMemory = (long)result[8].Parameter;
                amountOfUsedPhysicalMemory = (long)result[9].Parameter;
                amountOfVirtualMemory = (long)result[10].Parameter;
                amountOfUsedVirtualMemory = (long)result[11].Parameter;
                motherboardManufacturerName = (string)result[12].Parameter;
                motherboarProductName = (string)result[13].Parameter;
                BIOSManufacturerName = (string)result[14].Parameter;
                BIOSVersionName = (string)result[15].Parameter;
                chipsetName = (string)result[16].Parameter;
                videoAdapterName = (string)result[17].Parameter;
                monitorName = (string)result[18].Parameter;
                amountOfVideoMemory = (long)result[19].Parameter;

                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }


    }
}
