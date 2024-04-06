/// <summary>
///   Solution : NovaTend
///   Project : ContentManagemet.dll
///   Module : ContentManager.cs
///   Description :  implements the methods of class ContentManager
/// </summary>
/// 
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Linq;
using System.Text;

using Serialization;
using ScreenBuilder;
using Encryption;

using CommandClient;
using SystemData;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;

namespace ContentManagement
{
    public class ContentManager
    {

        #region Constants

        // Success
        public const int RES_SUCCESS = 0;

        // Can't prepare user content
        public const int RES_NO_USER_CONTENT = -1;

        // Empty user screen
        public const int RES_EMPTY_SCREEN = -2;

        
        
        // Action types

        // Allow
        public const int  ALLOW_ACTION = 1;

        // Deny
        public const int  DENY_ACTION =	2;

        // Ignore
        public const int  IGNORE_ACTION = 4;

        // Restrict
        public const int RESTRICT_ACTION = 8;


        // Function types

        // Log in
        public const int  LOG_IN_FUNCTION		=		1;

        // Post log in
        public const int  POST_LOG_IN_FUNCTION	=	2;

        // Education
        public const int  EDUCATION_FUNCTION	=		3;

        // Notification
        public const int  NOTIFICATION_FUNCTION	=	4;

        // Legal disclaimer
        public const int  LEGAL_DISCLAIMER_FUNCTION =	5;

        // Client machine monitoring
        public const int  MONITORING_FUNCTION	=		6;

        // Progm running control
        public const int PROGRAM_CONTROL_FUNCTION = 7;


        #endregion

        #region Encryption

        // Encryptor instance
        private Encryptor _encryptor;

        // Encryptor property
        public Encryptor encryptor
        {
            get
            {
                if (_encryptor == null)
                {
                    _encryptor = new Encryptor();
                }

                return _encryptor;
            }

            set
            {
                _encryptor = value;
            }
        }

        #endregion

        #region WD client

        // WD client instance
        private WDClient _wdClient;

        // WD client property
        public WDClient wdClient
        {
            get
            {
                return _wdClient;
            }

            set
            {
                _wdClient = value;
            }
        }

        // OS verions 

        // Unknown OS
        public const int OS_UNKNOWN = 0;

        // Windows 7 (x32)
        public const int OS_WINDOWS_7_X32 = 1;

        // Windows 7 (x64)
        public const int OS_WINDOWS_7_X64 = 2;

        // Windows 8 (x32)
        public const int OS_WINDOWS_8_X32 = 3;

        // Windows 8 (x64)
        public const int OS_WINDOWS_8_X64 = 4;

        // Windows XP (x32)
        public const int OS_WINDOWS_10_X32 = 5;

        // Windows XP (x64)
        public const int OS_WINDOWS_10_X64 = 6;

        /// <summary>
        /// Get OS version
        /// </summary>
        /// <returns>OS version code</returns>
        public static int GetOSVersion()
        {
            if ((Environment.OSVersion.Version.Major == 10) &&
               (Environment.OSVersion.Version.Minor == 0) &&
               (!Environment.Is64BitOperatingSystem))
                return OS_WINDOWS_10_X32;

            if ((Environment.OSVersion.Version.Major == 10) &&
               (Environment.OSVersion.Version.Minor == 0) &&
               (Environment.Is64BitOperatingSystem))
                return OS_WINDOWS_10_X64;

            if ((Environment.OSVersion.Version.Major == 6) &&
               (Environment.OSVersion.Version.Minor == 1) &&
               (!Environment.Is64BitOperatingSystem))
                return OS_WINDOWS_7_X32;

            if ((Environment.OSVersion.Version.Major == 6) &&
               (Environment.OSVersion.Version.Minor == 1) &&
               (Environment.Is64BitOperatingSystem))
                return OS_WINDOWS_7_X64;

            if ((Environment.OSVersion.Version.Major == 6) &&
               (Environment.OSVersion.Version.Minor == 2) &&
               (!Environment.Is64BitOperatingSystem))
                return OS_WINDOWS_8_X32;

            if ((Environment.OSVersion.Version.Major == 6) &&
               (Environment.OSVersion.Version.Minor == 2) &&
               (Environment.Is64BitOperatingSystem))
                return OS_WINDOWS_8_X64;

            return OS_UNKNOWN;
        }

        #endregion

        #region Constructing

        /// <summary>
        /// Constructor
        /// </summary>
        public ContentManager(WDClient wdClient)
        {
            this.wdClient = wdClient;
        }

        #endregion

        #region Containers

        /// <summary>
        /// Create authentication container
        /// </summary>
        /// <param name="mainScreen">main screen instance</param>
        /// <returns>list of auth elements</returns>
        private AUTH_CONTAINER CreateAuthContainer(ScreenBuildManager.UserScreen mainScreen)
        {
            if (mainScreen == null)
                return null;

            AUTH_CONTAINER authContainer = new AUTH_CONTAINER();

            for (int i = 0; i < mainScreen.screenObjectsList.Count; i++)
            {
                if ((mainScreen.screenObjectsList[i].screenObjectType == ScreenBuildManager.SOT_COMBOBOX) ||
                    (mainScreen.screenObjectsList[i].screenObjectType == ScreenBuildManager.SOT_TEXT_BOX))
                {
                    authContainer.Add(new AUTH_ELEMENT()
                                        {
                                            objectID = mainScreen.screenObjectsList[i].screenObjectID,
                                            objectTypeID = mainScreen.screenObjectsList[i].screenObjectType,
                                            objectName = encryptor.EncryptString(mainScreen.screenObjectsList[i].objectName),
                                            objectValue = encryptor.EncryptString(mainScreen.screenObjectsList[i].screenObjectControl.Text)
                                        }
                                     );
                }
            }

            if (authContainer.Count > 0)
                return authContainer;
            else
                return null;
        }

        /// <summary>
        /// Create education container
        /// </summary>
        /// <param name="mainScreen">main screen instance</param>
        /// <returns>list of education answers descriptor</returns>
        private ANSWER_CONTAINER CreateEducationContainer(ScreenBuildManager.UserScreen mainScreen)
        {
            if (mainScreen == null)
                return null;

            ANSWER_CONTAINER eduContainer = new ANSWER_CONTAINER();

            for (int i = 0; i < mainScreen.screenObjectsList.Count; i++)
            {
                if (mainScreen.screenObjectsList[i].screenObjectType == ScreenBuildManager.SOT_EDU_ANSWER_BOX)
                {
                    eduContainer.Add(new ANSWER_DESCRIPTOR()
                                        {
                                            questionID = mainScreen.screenObjectsList[i].questionID,
                                            rightAnswerID = mainScreen.screenObjectsList[i].rightAnswerID,
                                            answerValue = mainScreen.screenObjectsList[i].screenObjectControl.Text
                                        }
                                     );
                }
            }

            if (eduContainer.Count > 0)
                return eduContainer;
            else
                return null;
        }

        #endregion

        #region Screen building

        /// <summary>
        /// Get user preset
        /// </summary>
        /// <param name="userID">user ID</param>
        /// <returns>preset container</returns>
        public PRESET_CONTAINER GetUserPreset(int userID)
        {
            return wdClient.GET_CONTENT(Environment.MachineName, (uint)userID, (uint)GetOSVersion());
        }


        /// <summary>
        /// Build user screen (post login)
        /// </summary>
        /// <param name="userID">user ID</param>
        /// <param name="mainPanel">panel of main fom</param>
        /// <param name="submitButtonClickEvent">submit button click event handler</param>
        /// <param name="cancelButtonClickEvent">cancel button click event handler</param>
        /// <param name="resultCode">result code</param>
        /// <returns>screen builder instance</returns>
        public ScreenBuildManager BuildUserScreen(int userID, Panel mainPanel, EventHandler submitButtonClickEvent, EventHandler cancelButtonClickEvent, ref int resultCode)
        {
            // Get preset
            PRESET_CONTAINER userPreset = GetUserPreset(userID);
            if (userPreset == null)
            {
                resultCode = RES_NO_USER_CONTENT;
                return null;
            }

            // Create screen builder
            ScreenBuildManager screenBuilder = new ScreenBuildManager(mainPanel, userPreset);

            // Create screen structure
            screenBuilder.CreateUserScreen();
            
            // Check for empty
            if (screenBuilder.CheckEmptyScreen())
            {
                resultCode = RES_EMPTY_SCREEN;
                return null;
            }

            // Set events handlers
            if (screenBuilder.submitButtonIndex >= 0)
                screenBuilder.mainUserScreen.screenObjectsList[screenBuilder.submitButtonIndex].screenObjectControl.Click += submitButtonClickEvent;

            if (screenBuilder.cancelButtonIndex >= 0)
                screenBuilder.mainUserScreen.screenObjectsList[screenBuilder.cancelButtonIndex].screenObjectControl.Click += cancelButtonClickEvent;

            resultCode = RES_SUCCESS;
            return screenBuilder;
        }

        #endregion

        #region Validation

        /// <summary>
        /// Validate parameters
        /// </summary>
        /// <param name="userID">user ID</param>
        /// <param name="mainScreen">main screen instance</param>
        /// <returns>TRUE - if success</returns>
        public bool ValidateParams(int userID, string compName, ScreenBuildManager.UserScreen mainScreen)
        {
            AUTH_CONTAINER authContainer = CreateAuthContainer(mainScreen);

            if (authContainer == null)
                return true;

            bool? result = wdClient.VALIDATE_PARAMS((uint)userID, compName, authContainer);

            return ((result == null) || (result == false)) ? false : true;
        }

        /// <summary>
        /// Validate answers
        /// </summary>
        /// <param name="userID">user ID</param>
        /// <param name="mainScreen">main screen instance</param>
        /// <returns>TRUE - if success</returns>
        public bool ValidateAnswers(int userID, string compName, ScreenBuildManager.UserScreen mainScreen)
        {
            ANSWER_CONTAINER eduContainer = CreateEducationContainer(mainScreen);

            if (eduContainer == null)
                return true;

            bool? result = wdClient.VALIDATE_ANSWERS((uint)userID, compName, eduContainer);

            return ((result == null) || (result == false)) ? false : true;
        }

        #endregion

        #region Notification history

        /// <summary>
        /// Confirm legal disclaimer
        /// </summary>
        /// <param name="userID">user ID</param>
        /// <param name="mainScreen">main screen instance</param>
        /// <param name="subScreensList">sub windows list</param>
        /// <returns>TRUE - if success</returns>
        public bool ConfirmLegalDisclaimer(int userID, ScreenBuildManager.UserScreen mainScreen, List<ScreenBuildManager.UserScreen> subScreensList)
        {
            if (mainScreen == null)
                return false;

            for (int i = 0; i < subScreensList.Count; i++)
            {
                if (subScreensList[i].screenType == ScreenBuildManager.SOT_LEGAL_DISCLAIMER_SCREEN)
                {
                     // Get action code
			        uint? actionCode = wdClient.CHECK_SCHEDULE((uint)userID, Environment.MachineName, LEGAL_DISCLAIMER_FUNCTION);

                    if ((actionCode == null) || ((actionCode & DENY_ACTION) == DENY_ACTION))
                        return false;

                    if ((actionCode & IGNORE_ACTION) == IGNORE_ACTION)
                        return true;
                }
            }

            for (int i = 0; i < mainScreen.screenObjectsList.Count; i++)
            {
                if ((mainScreen.screenObjectsList[i].screenObjectType == ScreenBuildManager.SOT_LEGAL_DISCLAIMER_COMBOBOX) &&
                   ((mainScreen.screenObjectsList[i].screenObjectControl as ComboBox).SelectedIndex != 2))
                    return false;
            }

            for(int i = 0; i < subScreensList.Count; i++)
            {
                if (subScreensList[i].screenType == ScreenBuildManager.SOT_LEGAL_DISCLAIMER_SCREEN)
                {
                    for(int j = 0; j < subScreensList[i].screenObjectsList.Count; j++)
                    {
                        if (subScreensList[i].screenObjectsList[j].screenObjectType == ScreenBuildManager.SOT_LEGAL_DISCLAIMER_TEXT)
                        {
                            bool? result = wdClient.SAVE_NOTIFICATION_HISTORY((uint)userID, (uint)subScreensList[i].screenObjectsList[j].questionID);
                            return ((result == null) || (result == false)) ? false : true;
                        }
                    }
                }
            }

            return true;
        }

        #endregion

    }
}
