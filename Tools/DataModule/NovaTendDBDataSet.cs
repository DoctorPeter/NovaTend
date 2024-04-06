/// <summary>
///   Solution : NovaTend
///   Project : NovaTend
///   Module : NovaTendDBDataSet.cs
///   Description :  extends functionality of data access classes
/// </summary>
/// 

using System;
using System.Data;
using System.Data.SqlClient;

using System.Windows.Forms;

namespace DataModule
{

    /// <summary>
    /// NovaTend database dataset
    /// </summary>
    public partial class NovaTendDBDataSet
    {

    }
}

namespace DataModule.NovaTendDBDataSetTableAdapters
{

    /// <summary>
    /// License table adapter
    /// </summary>
    partial class LicenseTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        ///  connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }
        
        /// <summary>
        /// License table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public LicenseTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
           
        }
    }

    /// <summary>
    /// Password construction rules table adapter
    /// </summary>
    partial class PasswordConstructionRulesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Password construction rules table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public PasswordConstructionRulesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Password construction rules types table adapter
    /// </summary>
    partial class PasswordConstructionRulesTypesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Password construction rules types table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public PasswordConstructionRulesTypesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User password construction rules table adapter
    /// </summary>
    partial class UserPasswordConstructionRulesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User password construction rules table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserPasswordConstructionRulesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User temp password construction rules table adapter
    /// </summary>
    partial class TmpUserPasswordConstructionRulesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User password construction rules table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public TmpUserPasswordConstructionRulesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User notification history table adapter
    /// </summary>
    partial class UserNotificationsHistoryTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// Connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        ///  User notification history table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserNotificationsHistoryTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Notification types table adapter
    /// </summary>
    partial class NotificationTypesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Notification types table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public NotificationTypesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Notification scopes table adapter
    /// </summary>
    partial class NotificationScopesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Notification scopes table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public NotificationScopesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Notification table adapter
    /// </summary>
    partial class NotificationsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Notification table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public NotificationsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Notification display types table adapter
    /// </summary>
    partial class NotificationDisplayTypesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// otification display types table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public NotificationDisplayTypesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User notifications table adapter
    /// </summary>
    partial class UserNotificationsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User notifications table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserNotificationsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Education question answers table adapter
    /// </summary>
    partial class EducationQuestionAnswersTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Education question answers table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public EducationQuestionAnswersTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Education answers table adapter
    /// </summary>
    partial class EducationAnswersTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Education answers table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public EducationAnswersTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Education questions table adapter
    /// </summary>
    partial class EducationQuestionsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Education questions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public EducationQuestionsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User education answers table adapter
    /// </summary>
    partial class UserEducationAnswersTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User education answers table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserEducationAnswersTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Education lessons table adapter
    /// </summary>
    partial class EducationLessonsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Education lessons table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public EducationLessonsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Education categories table adapter
    /// </summary>
    partial class EducationCategoriesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Education categories table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public EducationCategoriesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User education table adapter
    /// </summary>
    partial class UserEducationTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User education table adapter
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserEducationTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User check values table adapter
    /// </summary>
    partial class UserCheckValuesTableAdapter
    {
        // connection string
        private string _connectionString;
        
        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User check values table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserCheckValuesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }
    
    /// <summary>
    /// Screen object list values table adapter
    /// </summary>
    partial class ScreenObjectListValuesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Screen object list values table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScreenObjectListValuesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Screen object types table adapter
    /// </summary>
    partial class ScreenObjectTypesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Screen object types table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScreenObjectTypesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Screen object scopes table adapter
    /// </summary>
    partial class ScreenObjectScopesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Screen object scopes table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScreenObjectScopesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Screen objects table adapter
    /// </summary>
    partial class ScreenObjectsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Screen objects table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScreenObjectsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }
    
    /// <summary>
    /// Preset details table adapter
    /// </summary>
    partial class PresetDetailsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Preset details table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public PresetDetailsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }
    
    /// <summary>
    /// Preset table adapter
    /// </summary>
    partial class PresetTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string proeprty
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Preset table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public PresetTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Preset hookup table adapter
    /// </summary>
    partial class PresetHookupTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string proeprty
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Preset hookup table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public PresetHookupTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Computers table adapter
    /// </summary>
    partial class ComputersTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Computers table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ComputersTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }
    
    /// <summary>
    /// Users table adapter
    /// </summary>
    public partial class UsersTableAdapter {

        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Users table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UsersTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }

    }

    /// <summary>
    /// User check values screen objects table adapter
    /// </summary>
    public partial class UserCheckValuesScreenObjectsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User check values screen objects table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserCheckValuesScreenObjectsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Screens preset details table adapter
    /// </summary>
    public partial class ScreensPresetDetailsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Screens preset details table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScreensPresetDetailsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Screens table adapter
    /// </summary>
    public partial class ScreensTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Screens table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScreensTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Screen types table adapter
    /// </summary>
    public partial class ScreenTypesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Screen types table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScreenTypesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// OS types table adapter
    /// </summary>
    public partial class OSTypesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// OS types table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public OSTypesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Permissions table adapter
    /// </summary>
    public partial class PermissionsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Permissions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public PermissionsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User permissions table adapter
    /// </summary>
    public partial class UserPermissionsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User permissions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserPermissionsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Authentication systems types table adapter
    /// </summary>
    public partial class AuthSystemTypesTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Authentication systems types table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public AuthSystemTypesTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Authentication systems table adapter
    /// </summary>
    public partial class AuthSystemsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Authentication systems table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public AuthSystemsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }


    /// <summary>
    /// User accounts table adapter
    /// </summary>
    public partial class UserAccountsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User accounts table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserAccountsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User accounts archive table adapter
    /// </summary>
    public partial class UserAccountsArchiveTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User accounts archive table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserAccountsArchiveTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User accounts actions table adapter
    /// </summary>
    public partial class UserAccountActionsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User accounts actions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserAccountActionsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User accounts actions table adapter
    /// </summary>
    public partial class UserAccountActionsOnDeleteTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User accounts actions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserAccountActionsOnDeleteTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User accounts actions table adapter
    /// </summary>
    public partial class UserAccountActionsOnInsertTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User accounts actions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserAccountActionsOnInsertTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User accounts actions table adapter
    /// </summary>
    public partial class UserAccountActionsOnUpdateTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User accounts actions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserAccountActionsOnUpdateTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User groups table adapter
    /// </summary>
    public partial class UserGroupsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User groups table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserGroupsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User groups authentication systems table adapter
    /// </summary>
    public partial class UserGroupAuthSystemsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User groups authentication systems table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserGroupAuthSystemsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User group education table adapter
    /// </summary>
    public partial class UserGroupEducationTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User group education table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserGroupEducationTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User group notification table adapter
    /// </summary>
    public partial class UserGroupNotificationsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User group notification table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserGroupNotificationsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User group permissions table adapter
    /// </summary>
    public partial class UserGroupPermissionsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User group permissions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserGroupPermissionsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// User group users table adapter
    /// </summary>
    public partial class UserGroupUsersTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// User group users table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public UserGroupUsersTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Controlled programs table adapter
    /// </summary>
    public partial class ControlledProgramsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Controlled programs table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ControlledProgramsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Schedule functions table adapter
    /// </summary>
    public partial class ScheduleFunctionsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Schedule functions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScheduleFunctionsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Schedule actions table adapter
    /// </summary>
    public partial class ScheduleActionsTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Schedule actions table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScheduleActionsTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }

    /// <summary>
    /// Schedule table adapter
    /// </summary>
    public partial class ScheduleTableAdapter
    {
        // connection string
        private string _connectionString;

        /// <summary>
        /// connection string property
        /// </summary>
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        /// <summary>
        /// Schedule table adapter constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public ScheduleTableAdapter(string conStr)
        {
            this.ClearBeforeFill = true;
            connectionString = conStr;
        }
    }
}

