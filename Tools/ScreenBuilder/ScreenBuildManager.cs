/// <summary>
///   Solution : NovaTend
///   Project : ScreenBuilder.dll
///   Module : ScreenBuilder.cs
///   Description :  Screen building manager module
/// </summary>

using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

using SystemData;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;


namespace ScreenBuilder
{
    /// <summary>
    /// Screen building manager
    /// </summary>
    public class ScreenBuildManager
    {

        #region Constants

        // Screen object types definition

        // User screen types ([0..255])

        // Main user screen
        public const int SOT_MAIN_SCREEN                            = 0;

        // Additional user sub screen
        public const int SOT_SUB_SCREEN                             = 1;

        // Sub window for studying
        public const int SOT_STUDY_SCREEN                           = 2;

        // Sub window for user notification
        public const int SOT_NOTIFICATION_SCREEN                    = 3;

        // Sub window for legal disclaimer
        public const int SOT_LEGAL_DISCLAIMER_SCREEN                = 4;

        // Sub window for symbol boxes password
        public const int SOT_SYMBOL_BOXES_PWD_SCREEN                = 5;

        // Post login process main screen
        public const int SOT_POST_LOGIN_MAIN_SCREEN                 = 6;

        
        // User screen objects ([256..511])

        // Picture
        public const int SOT_IMAGE                                  = 256;

        // Lagre text (font size = 14)
        public const int SOT_LARGE_TEXT                             = 257;

        // Small text (font size = 12)
        public const int SOT_SMALL_TEXT                             = 258;

        // Big text block
        public const int SOT_BIG_TEXT_BLOCK                         = 259;

        // Text box
        public const int SOT_TEXT_BOX                               = 260;

        // Text box with password
        public const int SOT_PASSWORD_BOX                           = 261;

        // Submit button
        public const int SOT_BUTTON                                 = 262;

        // Check box
        public const int SOT_CHECKBOX                               = 263;

        // Combo box
        public const int SOT_COMBOBOX                               = 264;

        // Command link
        public const int SOT_COMMAND_LINK                           = 265;

        // Small text with current date and time
        public const int SOT_DATE_TIME_TEXT                         = 266;

        // Text box for user name
        public const int SOT_USER_NAME_BOX                          = 267;

        // Combo box for list of domain names
        public const int SOT_DOMAIN_NAME_BOX                        = 268;

        // Lagre text for study questions
        public const int SOT_EDU_QUESTION_TEXT                      = 269;

        // Combo box for study answers
        public const int SOT_EDU_ANSWER_BOX                         = 270;

        // Small text for education
        public const int SOT_EDUCATION_LABEL                        = 271;

        // Text block for lesson text
        public const int SOT_EDU_LESSON_TEXT                        = 272;

        // Picture for lesson
        public const int SOT_EDU_LESSON_IMAGE                       = 273;

        // Lagre text for legal disclaimer
        public const int SOT_LEGAL_DISCLAIMER_TEXT                  = 274;

        // Picture for legal disclaimer
        public const int SOT_LEGAL_DISCLAIMER_IMAGE                 = 275;

        // Small text for legal disclaimer
        public const int SOT_LEGAL_DISCLAIMER_LABEL                 = 276;

        // Combo box for legal disclaimer
        public const int SOT_LEGAL_DISCLAIMER_COMBOBOX              = 277;

        // Large text for simple notification
        public const int SOT_SIMPLE_NOTICE_TEXT                     = 278;

        // Large text for warning notification
        public const int SOT_WARNING_NOTICE_TEXT                    = 279;

        // Password reset button
        public const int SOT_PASSWORD_RESET_BUTTON                  = 280;


        // Screen objects scopes

        // Screen object for logon screen
        public const int SO_SCOPE_LOGON_SCREEN                      = 1;

        // Screen object for post login process
        public const int SO_SCOPE_POST_LOGIN_SCREEN                 = 2;

        // Screen object for bith process
        public const int SO_SCOPE_BOTH                              = 3;


        // Notification types definition

        // Simple notification
        public const int NT_SIMPLE_NOTICE                           = 1;

        // Simple notification
        public const int NT_WARNING_NOTICE                          = 2;

        // Legal disclaimer
        public const int NT_LEGAL_DISCLAIMER                        = 3;
        

        // Notification display types definition

        // Show notice only once
        public const int NDT_SHOW_ONLY_ONCE                         = 1;

        // Show notice one time per day
        public const int NDT_SHOW_ONCE_PER_DAY                      = 2;

        // Always show notice
        public const int NDT_ALWAYS_SHOW                            = 3;

        
        // Notification scopes definition

        // Private notice
        public const int NS_PRIVATE                                 = 1;

        // Public notice
        public const int NS_PUBLIC                                  = 2;

        #endregion

        #region Internal variables

        // Main screen instance
        public UserScreen mainUserScreen;

        // Main screen panel
        public Panel mainUserScreenPanel;
        
        // User preset container structure
        private PRESET_CONTAINER userPreset;

        // List of sub screen
        public List<UserScreen> subScreensList;

        // Index of submit button
        public int submitButtonIndex;

        // Index of cancel button
        public int cancelButtonIndex;
        
        #endregion

        #region Construction

        /// <summary>
        /// Constructor
        /// </summary>
        public ScreenBuildManager(Panel mainUserScreenPanel, PRESET_CONTAINER userPreset)
        {
            subScreensList = new List<UserScreen>();

            this.mainUserScreenPanel = mainUserScreenPanel;
            
            this.userPreset = userPreset;

            mainUserScreen = null;

            submitButtonIndex = -1;

            cancelButtonIndex = -1;
        }

        #endregion

        #region Load screen objects

        /// <summary>
        /// Clear user screen
        /// </summary>
        public void ClearUserScreen()
        {
            if (mainUserScreen != null)
            {
                mainUserScreen.ClearScreen();
                subScreensList.Clear();
            }

            mainUserScreenPanel.Controls.Clear();
        }

        /// <summary>
        /// Create user screen according to 
        /// user preset container
        /// </summary>
        public void CreateUserScreen()
        {
            ClearUserScreen();

            USER_SCREEN postLoginMainScreen = FindScreenByType(SOT_POST_LOGIN_MAIN_SCREEN);
            if (postLoginMainScreen.screenTypeID == SOT_POST_LOGIN_MAIN_SCREEN)
            {
                mainUserScreen = new UserScreen(postLoginMainScreen, mainUserScreenPanel);
            }
            else
            {
                mainUserScreen = new UserScreen(postLoginMainScreen, mainUserScreenPanel, SOT_POST_LOGIN_MAIN_SCREEN, "PostLogin", "Post login main screen");
            }

            AddButtons();
            LoadScreens(userPreset.UserScreens);
        }

        /// <summary>
        /// Find screen
        /// </summary>
        /// <returns>Screen structure</returns>
        private USER_SCREEN FindScreenByType(int typeID)
        {
            if (userPreset.UserScreens != null)
            {
                foreach (USER_SCREEN userScreen in userPreset.UserScreens)
                {
                    if (userScreen.screenTypeID == typeID)
                        return userScreen;
                }
            }

            USER_SCREEN notFoundScreen = new USER_SCREEN();
            notFoundScreen.screenTypeID = -1;
            
            return notFoundScreen;
        }


        /// <summary>
        /// Load screens from user preset
        /// </summary>
        /// <param name="userScreens">user screens structures list</param>
        /// <returns>TRUE - if success</returns>
        private bool LoadScreens(USER_SCREEN_LIST userScreens)
        {
            if (userScreens == null)
                return false;

            subScreensList.Clear();

            foreach (USER_SCREEN screen in userScreens)
            {
                if (((screen.screenTypeID == SOT_SUB_SCREEN) ||
                     (screen.screenTypeID == SOT_STUDY_SCREEN) ||
                     (screen.screenTypeID == SOT_NOTIFICATION_SCREEN) ||
                     (screen.screenTypeID == SOT_LEGAL_DISCLAIMER_SCREEN)) &&
                    ((screen.screenScope == SO_SCOPE_POST_LOGIN_SCREEN) ||
                     (screen.screenScope == SO_SCOPE_BOTH)))
                {
                    UserScreen ctrlScreen = new UserScreen(screen, mainUserScreen.screenPanel.Width, mainUserScreen.screenPanel.Height);
                    mainUserScreen.screenPanel.Controls.Add(ctrlScreen.screenPanel);
                    subScreensList.Add(ctrlScreen);
                }
            }

            return true;
        }

        /// <summary>
        /// Check buttons on main screen
        /// </summary>
        private void AddButtons()
        {
            submitButtonIndex = FindButton("Submit");
            cancelButtonIndex = FindButton("Cancel");

            if (submitButtonIndex < 0)
            {
                Button btn = new Button();
                btn.Size = new Size(100, 25);
                btn.Name = "submitButton";
                btn.Text = "Submit";
                btn.FlatStyle = FlatStyle.Flat;
                btn.Location = new Point(mainUserScreenPanel.Width - 230, mainUserScreenPanel.Height - 60);

                UserScreenObject userScreenObject = new UserScreenObject(btn, mainUserScreenPanel.Width, mainUserScreenPanel.Height, SOT_BUTTON);
                mainUserScreenPanel.Controls.Add(userScreenObject.screenObjectControl);
                mainUserScreen.screenObjectsList.Add(userScreenObject);
                submitButtonIndex = mainUserScreen.screenObjectsList.Count - 1;
            }

            if (cancelButtonIndex < 0)
            {
                Button btn = new Button();
                btn.Size = new Size(100, 25);
                btn.Name = "cancelButton";
                btn.Text = "Cancel";
                btn.FlatStyle = FlatStyle.Flat;
                btn.Location = new Point(mainUserScreenPanel.Width - 120, mainUserScreenPanel.Height - 60);

                UserScreenObject userScreenObject = new UserScreenObject(btn, mainUserScreenPanel.Width, mainUserScreenPanel.Height, SOT_BUTTON);
                mainUserScreenPanel.Controls.Add(userScreenObject.screenObjectControl);
                mainUserScreen.screenObjectsList.Add(userScreenObject);
                cancelButtonIndex = mainUserScreen.screenObjectsList.Count - 1;
            }
        }

        /// <summary>
        /// Find button by caption
        /// </summary>
        /// <param name="caption">caption string</param>
        /// <returns>button index in list of screen objects</returns>
        private int FindButton(string caption)
        {
            for (int i = 0; i < mainUserScreen.screenObjectsList.Count; i++)
            {
                if ((mainUserScreen.screenObjectsList[i].screenObjectType == SOT_BUTTON) &&
                    (mainUserScreen.screenObjectsList[i].objectCaption == caption))
                {
                    return i;
                }
            }

            return -1;
        }
    
        #endregion

        #region Check screen objects

        /// <summary>
        /// Validate screen for screen objects count
        /// </summary>
        /// <returns>TRUE - if screen is empty</returns>
        public bool CheckEmptyScreen()
        {
            if (subScreensList.Count == 0)
            {
                if (mainUserScreen.screenObjectsList.Count <= 2)
                    return true;
                else
                    return false;
            }
            else
                return false;
        }

        #endregion

        #region Control customization

        /// <summary>
        /// Create screen control
        /// </summary>
        /// <param name="screenObject">screen object structure</param>
        /// <returns>Control instance</returns>
        static public Control CreateControl(SCREEN_OBJECT screenObject)
        {
            Control resultControl = null;

            switch (screenObject.objTypeId)
            {
                // Picture
                case SOT_IMAGE:
                case SOT_EDU_LESSON_IMAGE:
                case SOT_LEGAL_DISCLAIMER_IMAGE:
                    {
                        resultControl = new PictureBox();
                        (resultControl as PictureBox).SizeMode = PictureBoxSizeMode.CenterImage;
                        break;
                    }

                // Big text block
                case SOT_BIG_TEXT_BLOCK:
                case SOT_EDU_QUESTION_TEXT:
                case SOT_EDU_LESSON_TEXT:
                case SOT_LEGAL_DISCLAIMER_TEXT:
                case SOT_SIMPLE_NOTICE_TEXT:
                case SOT_WARNING_NOTICE_TEXT:
                    {
                        resultControl = new TextBox();
                        (resultControl as TextBox).Multiline = true;
                        (resultControl as TextBox).ScrollBars = ScrollBars.Vertical;
                        Color backColor = (resultControl as TextBox).BackColor;
                        (resultControl as TextBox).ReadOnly = true;
                        (resultControl as TextBox).BackColor = backColor;
                        break;
                    }

                // Text label
                case SOT_LARGE_TEXT:
                case SOT_SMALL_TEXT:
                case SOT_EDUCATION_LABEL:
                case SOT_LEGAL_DISCLAIMER_LABEL:
                case SOT_DATE_TIME_TEXT:
                    {
                        resultControl = new Label();
                        break;
                    }

                // Checkbox
                case SOT_CHECKBOX:
                    {
                        resultControl = new CheckBox();
                        break;
                    }

                // Command link
                case SOT_COMMAND_LINK:
                    {
                        resultControl = new Label();
                        resultControl.Font = new Font(resultControl.Font, FontStyle.Underline);
                        break;
                    }

                // Buttons
                case SOT_BUTTON:
                case SOT_PASSWORD_RESET_BUTTON:
                    {
                        resultControl = new Button();
                        (resultControl as Button).FlatStyle = FlatStyle.Flat;
                        break;
                    }


                // Text box
                case SOT_TEXT_BOX:
                case SOT_USER_NAME_BOX:
                    {
                        resultControl = new TextBox();
                        break;
                    }

                // Hidden text box
                case SOT_PASSWORD_BOX:
                    {
                        resultControl = new TextBox();
                        (resultControl as TextBox).PasswordChar = '*';
                        break;
                    }

                // Combo box
                case SOT_COMBOBOX:
                case SOT_DOMAIN_NAME_BOX:
                case SOT_EDU_ANSWER_BOX:
                case SOT_LEGAL_DISCLAIMER_COMBOBOX:
                    {
                        resultControl = new ComboBox();
                        break;
                    }
            }

            return resultControl;
        }

        /// <summary>
        /// Set screen object size
        /// </summary>
        /// <param name="widthPix">width in pixels</param>
        /// <param name="heightPix">height inpixels</param>
        /// <param name="widthPers">width in percents</param>
        /// <param name="heightPers">height in percents</param>
        /// <param name="parentWidth">parent screen width</param>
        /// <param name="parentHeight">parent screen height</param>
        public static void SetScreenObjectSize(ref int widthPix, ref int heightPix, int widthPers, int heightPers, int parentWidth, int parentHeight)
        {
            if ((widthPix == 0) && (widthPers != 0))
                widthPix = (parentWidth * widthPers) / 100;

            if ((widthPix != 0) && (widthPix > parentWidth))
                widthPix = parentWidth;

            if ((heightPix == 0) && (heightPers != 0))
                heightPix = (parentHeight * heightPers) / 100;

            if ((heightPix != 0) && (heightPix > parentHeight))
                heightPix = parentHeight;
        }

        /// <summary>
        /// Set screen object location
        /// </summary>
        /// <param name="locationX">X coord in pixels</param>
        /// <param name="locationY">Y coord in pixels</param>
        /// <param name="locationXPers">X coord in percents</param>
        /// <param name="locationYPers">Y coord in percents</param>
        /// <param name="parentWidth">parent screen width</param>
        /// <param name="parentHeight">parent screen height</param>
        public static void SetScreenObjectLocation(ref int locationX, ref int locationY, int locationXPers, int locationYPers, int parentWidth, int parentHeight)
        {
            if (locationXPers > 0)
                locationX = (parentWidth * locationXPers) / 100;

            if (locationX > parentWidth)
                locationX = parentWidth - 5;

            if (locationYPers > 0)
                locationY = (parentHeight * locationYPers) / 100;

            if (locationY > parentHeight)
                locationY = parentHeight - 5;
        }


        /// <summary>
        /// Convert uint ot Color
        /// </summary>
        public static Color UIntToColor(uint color)
        {
            byte[] colorBytes = BitConverter.GetBytes(color);
            return Color.FromArgb(colorBytes[3], colorBytes[0], colorBytes[1], colorBytes[2]);
        }

        /// <summary>
        /// Set user control value
        /// </summary>
        /// <param name="screenObject">screen object structure</param>
        /// <param name="userScreenObject">screen object instance</param>
        public static bool SetUserControlValue(SCREEN_OBJECT screenObject, UserScreenObject userScreenObject)
        {
            if (userScreenObject == null)
                return false;

            try
            {
                switch (screenObject.objTypeId)
                {
                    case SOT_DATE_TIME_TEXT:
                        {
                            userScreenObject.screenObjectControl.Text = DateTime.Now.ToString("dddd, MM/dd/yy, HH:mm:ss");
                            break;
                        }

                    case SOT_LARGE_TEXT:
                    case SOT_SMALL_TEXT:
                    case SOT_CHECKBOX:
                    case SOT_COMMAND_LINK:
                    case SOT_EDUCATION_LABEL:
                    case SOT_LEGAL_DISCLAIMER_LABEL:
                    case SOT_PASSWORD_RESET_BUTTON:
                    case SOT_BUTTON:
                        {
                            userScreenObject.screenObjectControl.Text = userScreenObject.objectCaption;
                            break;
                        }

                    case SOT_IMAGE:
                    case SOT_EDU_LESSON_IMAGE:
                    case SOT_LEGAL_DISCLAIMER_IMAGE:
                        {
                            // Get image value
                            if (screenObject.imgValue != null)
                            {
                                MemoryStream stream = new MemoryStream(screenObject.imgValue);
                                Bitmap image = new Bitmap(stream);
                                (userScreenObject.screenObjectControl as PictureBox).Image = image;
                            }
                            break;
                        }

                    case SOT_BIG_TEXT_BLOCK:
                    case SOT_EDU_QUESTION_TEXT:
                    case SOT_EDU_LESSON_TEXT:
                    case SOT_LEGAL_DISCLAIMER_TEXT:
                    case SOT_SIMPLE_NOTICE_TEXT:
                    case SOT_WARNING_NOTICE_TEXT:
                        {
                            // Get big text value
                            if (screenObject.textValue != null)
                                (userScreenObject.screenObjectControl as TextBox).Text = screenObject.textValue;
                            break;
                        }

                    case SOT_TEXT_BOX:
                    case SOT_USER_NAME_BOX:
                    case SOT_PASSWORD_BOX:
                        {
                            (userScreenObject.screenObjectControl as TextBox).Text = "";
                            break;
                        }

                    case SOT_COMBOBOX:
                    case SOT_DOMAIN_NAME_BOX:
                    case SOT_EDU_ANSWER_BOX:
                    case SOT_LEGAL_DISCLAIMER_COMBOBOX:
                        {
                            // Combo box values
                            for (int i = 0; i < screenObject.listValuesSet.Length; i++)
                            {
                                if (screenObject.listValuesSet[i] == null)
                                {
                                    (userScreenObject.screenObjectControl as ComboBox).Items.Add("");
                                }
                                else
                                {
                                    (userScreenObject.screenObjectControl as ComboBox).Items.Add(screenObject.listValuesSet[i]);
                                }
                            }

                            break;
                        }

                    default:
                        {
                            // Default actions
                            userScreenObject.screenObjectControl.Text = userScreenObject.objectCaption;
                            break;
                        }
                }

                return true;
            }
            catch
            {
                return false;
            }
        }

        #endregion

        #region Screen

        /// <summary>
        /// Class of user screen (window panel)
        /// </summary>
        public class UserScreen
        {
            // Window panel
            public Panel screenPanel;

            // Screen ID
            public int screenID;

            // Screen type
            public int screenType;

            // Name of screen
            public string windowName;

            // Caption of screen
            public string windowCaption;

            // Parent width
            public int parentWidth;

            // Parent height
            public int parentHeight;

            // List of screen objects
            public List<UserScreenObject> screenObjectsList;

            /// <summary>
            /// Constructor
            /// </summary>
            public UserScreen(USER_SCREEN screen, int parentWidth, int parentHeight)
            {
                screenObjectsList = new List<UserScreenObject>();

                this.parentWidth = parentWidth;
                this.parentHeight = parentHeight;

                screenPanel = new Panel();

                int screenX = screen.locationX;
                int screenY = screen.locationY;
                int screenW = screen.widthPix;
                int screenH = screen.heightPix;

                SetScreenObjectLocation(ref screenX, ref screenY, screen.locationXPers, screen.locationYPers, parentWidth, parentHeight);
                SetScreenObjectSize(ref screenW, ref screenH, screen.widthPers, screen.heightPers, parentWidth, parentHeight);

                screen.locationX = screenX;
                screen.locationY = screenY;
                screen.widthPix = screenW;
                screen.heightPix = screenH;

                screenPanel.Location = new Point(screen.locationX, screen.locationY);
                screenPanel.Width = screen.widthPix;
                screenPanel.Height = screen.heightPix;
                screenPanel.BackColor = UIntToColor(screen.color);
                screenPanel.BorderStyle = BorderStyle.FixedSingle;

                screenID = screen.screenID;
                screenType = screen.screenTypeID;
                windowName = screen.Name;
                windowCaption = screen.screenCaption;

                LoadScreenObjects(screen.ScreenObjects);
            }

            /// <summary>
            /// Constructor
            /// </summary>
            public UserScreen(USER_SCREEN screen, Panel userScreenPanel)
            {
                screenObjectsList = new List<UserScreenObject>();

                parentWidth = userScreenPanel.Width;
                parentHeight = userScreenPanel.Height;

                screenPanel = userScreenPanel;

                screenID = screen.screenID;
                screenType = screen.screenTypeID;
                windowName = screen.Name;
                windowCaption = screen.screenCaption;

                LoadScreenObjects(screen.ScreenObjects);
            }

            /// <summary>
            /// Constructor
            /// </summary>
            public UserScreen(USER_SCREEN screen, Panel userScreenPanel, int screenType, string name, string caption)
            {
                screenObjectsList = new List<UserScreenObject>();

                parentWidth = userScreenPanel.Width;
                parentHeight = userScreenPanel.Height;

                screenPanel = userScreenPanel;
                
                this.screenID = screen.screenID;
                this.screenType = screenType;
                windowName = name;
                windowCaption = caption;
            }

            /// <summary>
            /// Load screen objects for some screen
            /// </summary>
            /// <param name="screenObjects">screen objects list</param>
            /// <returns>TRUE - if success</returns>
            public bool LoadScreenObjects(SCREEN_OBJECT_LIST screenObjects)
            {
                if (screenObjects == null)
                    return false;
                
                ClearScreen();

                foreach (SCREEN_OBJECT screenObject in screenObjects)
                {
                    if ((screenObject.objTypeId >= SOT_IMAGE) &&
                        (screenObject.objTypeId <= SOT_PASSWORD_RESET_BUTTON) &&
                        ((screenObject.objScope == SO_SCOPE_POST_LOGIN_SCREEN) ||
                        (screenObject.objScope == SO_SCOPE_BOTH)))
                    {
                        UserScreenObject ctrlScreenObject = new UserScreenObject(screenObject, screenPanel.Width, screenPanel.Height);
                        screenPanel.Controls.Add(ctrlScreenObject.screenObjectControl);
                        screenObjectsList.Add(ctrlScreenObject);
                    }
                }

                return true;
            }

            /// <summary>
            /// Clear screen
            /// </summary>
            public void ClearScreen()
            {
                screenPanel.Controls.Clear();
                screenObjectsList.Clear();
            }
        }

        #endregion

        #region Screen object

        /// <summary>
        /// User acreen object class
        /// </summary>
        public class UserScreenObject
        {
            // Screen object control
            public Control screenObjectControl;

            // Screen object ID
            public int screenObjectID;

            // Screen object type
            public int screenObjectType;

            // Object name string
            public string objectName;

            // Object caption string
            public string objectCaption;

            // ID of right answer (for SOT_EDU_QUESTION_TEXT)
            public int rightAnswerID;
	
	        // ID of question (for SOT_EDU_QUESTION_TEXT)
            public int questionID;

	        // Object string value
	        public string strValue;

            // Parent width
            public int parentWidth;

            // Parent height
            public int parentHeight;

            /// <summary>
            /// Constructor
            /// </summary>
            public UserScreenObject(SCREEN_OBJECT screenObject, int parentWidth, int parentHeight)
            {
                this.parentWidth = parentWidth;
                this.parentHeight = parentHeight;

                screenObjectID = screenObject.objID;
                screenObjectType = screenObject.objTypeId;
                screenObjectControl = CreateControl(screenObject);

                int screenX = screenObject.locationX;
                int screenY = screenObject.locationY;
                int screenW = screenObject.widthPix;
                int screenH = screenObject.heightPix;

                SetScreenObjectLocation(ref screenX, ref screenY, screenObject.locationXPers, screenObject.locationYPers, parentWidth, parentHeight);
                SetScreenObjectSize(ref screenW, ref screenH, screenObject.widthPers, screenObject.heightPers, parentWidth, parentHeight);

                screenObject.locationX = screenX;
                screenObject.locationY = screenY;
                screenObject.widthPix = screenW;
                screenObject.heightPix = screenH;

                screenObjectControl.Location = new Point(screenObject.locationX, screenObject.locationY);
                screenObjectControl.Width = screenObject.widthPix;
                screenObjectControl.Height = screenObject.heightPix;

                try
                {
                    screenObjectControl.BackColor = UIntToColor(screenObject.backgroundColor);
                }
                catch
                {
                    //screenObjectControl.BackColor = SystemColors.Control;
                }

                screenObjectControl.ForeColor = UIntToColor(screenObject.textColor);
                screenObjectControl.Font = new Font(screenObjectControl.Font.FontFamily, screenObject.fontSize);

                if (screenObject.objName == null)
                    objectName = "";
                else
                    objectName = screenObject.objName;

                if (screenObject.objCaption == null)
                    objectCaption = "";
                else
                    objectCaption = screenObject.objCaption;

                rightAnswerID = screenObject.rightAnswerID;
	            questionID = screenObject.questionID;

                if (screenObject.strValue == null)
                    strValue = "";
                else
                    strValue = screenObject.strValue;

                SetUserControlValue(screenObject, this);
            }
     
            /// <summary>
            /// Constructor
            /// </summary>
            public UserScreenObject(Control screenObjectControl, int parentWidth, int parentHeight, int screenObjectType)
            {
                this.screenObjectControl = screenObjectControl;
                this.parentWidth = parentWidth;
                this.parentHeight = parentHeight;
                this.screenObjectType = screenObjectType;
                objectName = screenObjectControl.Name;
                objectCaption = screenObjectControl.Text;

                rightAnswerID = -1;
                questionID = -1;
                strValue = objectCaption;
            }
        }

        #endregion

    }
}
