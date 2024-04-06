/// <summary>
///   Solution : NovaTend
///   Project : DataModule.dll
///   Module : DataBaseManager.cs
///   Description :  implements the methods of class DataBaseManager
/// </summary>
/// 
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using DataModule.NovaTendDBDataSetTableAdapters;

using WriteLog;
using Encryption;

namespace DataModule
{
    /// <summary>
    /// NovaTend database management
    /// </summary>
    public class DataBaseManager
    {

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

        #region Private

        // NovaTend database data set instance
        private NovaTendDBDataSet _dataSet;

        // Connection string
        private string _connectionString;

        // SQL connection instance
        private IDbConnection _connection;

        // Table adapters manager
        private TableAdapterManager _tableAdapterManager;

        // Authentication systems table
        private AuthSystemTypesTableAdapter _authSystemTypesTableAdapter;
        private BindingSource _authSystemTypesBindingSource;
        private AuthSystemsTableAdapter _authSystemsTableAdapter;
        private BindingSource _authSystemsBindingSource;
        private BindingSource _authSystemsSynchronizeBindingSource;

        // Users table
        private UsersTableAdapter _usersTableAdapter;
        private BindingSource _usersBindingSource;
        private BindingSource _fkUserPasswordConstructionRulesUsersBindingSource;
        private BindingSource _fkTmpUserPasswordConstructionRulesUsersBindingSource;
        private BindingSource _fkUserCheckValuesUsersBindingSource;

        // User groups
        private UserGroupsTableAdapter _userGroupsTableAdapter;
        private BindingSource _userGroupsBindingSource;
        private UserGroupUsersTableAdapter _userGroupUsersTableAdapter;
        private BindingSource _userGroupUsersBindingSource;
        private UserGroupAuthSystemsTableAdapter _userGroupAuthSystemsTableAdapter;
        private BindingSource _userGroupAuthSystemsBindingSource;
        private UserGroupEducationTableAdapter _userGroupEducationTableAdapter;
        private BindingSource _userGroupEducationBindingSource;
        private UserGroupNotificationsTableAdapter _userGroupNotificationsTableAdapter;
        private BindingSource _userGroupNotificationsBindingSource;
        private UserGroupPermissionsTableAdapter _userGroupPermissionsTableAdapter;
        private BindingSource _userGroupPermissionsBindingSource;
        private BindingSource _userGroupsAuthSystemsBindingSource;
        private BindingSource _fkUserGroupsUsersBindingSource;
        private BindingSource _fkUserGroupsUsersGroupPermissionsBindingSource;
        private BindingSource _fkUserGroupsUsersGroupAuthSystemsBindingSource;
        private BindingSource _fkUsersUserGroupsBindingSource;
        private BindingSource _fkUserGroupsUsersGroupEducationBindingSource;
        private BindingSource _fkUserGroupsUsersGroupNotificationsBindingSource;

        // User accounts table
        private UserAccountsTableAdapter _userAccountsTableAdapter;
        private BindingSource _userAccountsBindingSource;
        private BindingSource _fkUserAccountsUsersBindingSource;
        private BindingSource _userAccontsAuthSystemsBindingSource;
        private UserAccountsArchiveTableAdapter _userAccountsArchiveTableAdapter;
        private BindingSource _userAccountsArchiveBindingSource;
        private BindingSource _userAccountsArchiveUsersBindingSource;
        private BindingSource _fkUserAccountsArchiveUsersBindingSource;
        private BindingSource _userAccontsArchiveAuthSystemsBindingSource;
        
        // Personal user data
        private BindingSource _personalUsersBindingSource;
        private BindingSource _fkPersonalUserPasswordConstructionRulesUsersBindingSource;
        private BindingSource _fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource;
        private BindingSource _fkPersonalUserCheckValuesUsersBindingSource;
        private BindingSource _fkPersonalUserAccountsUsersBindingSource;
        private BindingSource _fkPersonalUserPermissionsUsersBindingSource;
        private BindingSource _fkPersonalUsersUserGroupsBindingSource;
        private BindingSource _personalPermissionsBindingSource;
        private BindingSource _personalUserAccountAuthSystemsBindingSource;
        private BindingSource _personalUserCheckValuesScreenObjectsBindingSource;
        private BindingSource _personalUserGroupsBindingSource;

        // Controlled programs
        private ControlledProgramsTableAdapter _controlledProgramsTableAdapter;
        private BindingSource _controlledProgramsBindingSource;

        // Schedule
        private ScheduleActionsTableAdapter _scheduleActionsTableAdapter;
        private BindingSource _scheduleActionsBindingSource;
        private ScheduleFunctionsTableAdapter _scheduleFunctionsTableAdapter;
        private BindingSource _scheduleFunctionsBindingSource;
        private ScheduleTableAdapter _scheduleTableAdapter;
        private BindingSource _scheduleBindingSource;
        private BindingSource _scheduleComputersBindindSource;
        private BindingSource _scheduleProgramsBindindSource;

        // User accounts actions
        private UserAccountActionsOnDeleteTableAdapter _userAccountActionsOnDeleteTableAdapter;
        private BindingSource _userAccountActionsOnDeleteBindingSource;
        private UserAccountActionsOnInsertTableAdapter _userAccountActionsOnInsertTableAdapter;
        private BindingSource _userAccountActionsOnInsertBindingSource;
        private UserAccountActionsOnUpdateTableAdapter _userAccountActionsOnUpdateTableAdapter;
        private BindingSource _userAccountActionsOnUpdateBindingSource;
        
        // Computers table
        private ComputersTableAdapter _computersTableAdapter;
        private BindingSource _computersBindingSource;

        // Preset table
        private PresetTableAdapter _presetTableAdapter;
        private BindingSource _presetBindingSource;
        private BindingSource _presetScreensBindingSource;

        // Preset details table
        private PresetDetailsTableAdapter _presetDetailsTableAdapter;
        private BindingSource _presetDetailsBindingSource;
        private ScreensPresetDetailsTableAdapter _screensPresetDetailsTableAdapter;
        private BindingSource _screensPresetDetailsBindingSource;
        private BindingSource _fkScreensPresetDetailsPresetBindingSource;
        private BindingSource _presetDetailsScreenObjectsBindingSource;
        private BindingSource _fkPresetDetailsScreensPresetDetailsBindingSource;
        private BindingSource _fkPresetDetailsScreensScreenObjectsBindingSource;
        private BindingSource _fkPresetDetailsPresetBindingSource;
        private BindingSource _presetDetailsScreensBindingSource;

        // Preset hookup
        private PresetHookupTableAdapter _presetHookupTableAdapter;
        private BindingSource _presetHookupBindingSource;
        private BindingSource _presetHokupPresetsBindingSource;
        private BindingSource _presetHokupUsersBindingSource;
        private BindingSource _presetHookupUserGroupsBindingSource;
        private BindingSource _presetHokupComputersBindingSource;
        private BindingSource _presetHokupOSTypesBindingSource;
        private BindingSource _fkPresetHookupPresetBindingSource;

        // Screen objects table
        private ScreensTableAdapter _screensTableAdapter;
        private BindingSource _screensBindingSource;
        private ScreenObjectsTableAdapter _screenObjectsTableAdapter;
        private BindingSource _screenObjectsBindingSource;
        private BindingSource _fkScreenObjectsScreenObjectsBindingSource;
        private BindingSource _fkScreensScreenObjectsBindingSource;
        private BindingSource _fkScreenObjectListValuesScreenObjectsBindingSource;
        
        // Screen objects types table
        private ScreenObjectTypesTableAdapter _screenObjectsTypesTableAdapter;
        private BindingSource _screenObjectsTypesBindingSource;
        private ScreenTypesTableAdapter _screenTypesTableAdapter;
        private BindingSource _screenTypesBindingSource;

        // Screen object scopes table
        private ScreenObjectScopesTableAdapter _screenObjectScopesTableAdapter;
        private BindingSource _screenObjectScopesScreensBindingSource;
        private BindingSource _screenObjectScopesScreenObjectsBindingSource;

        // Screen object list values table
        private ScreenObjectListValuesTableAdapter _screenObjectListValuesTableAdapter;
        private BindingSource _screenObjectListValuesBindingSource;

        // User check values table
        private UserCheckValuesTableAdapter _userCheckValuesTableAdapter;
        private BindingSource _userCheckValuesBindingSource;
        private UserCheckValuesScreenObjectsTableAdapter _userCheckValuesScreenObjectsTableAdapter;
        private BindingSource _userCheckValuesScreenObjectsBindingSource;

        // Password construction rules table
        private PasswordConstructionRulesTableAdapter _passwordConstructionRulesTableAdapter;
        private BindingSource _passwordConstructionRulesBindingSource;

        // Password construction rules types table
        private PasswordConstructionRulesTypesTableAdapter _passwordConstructionRulesTypesTableAdapter;
        private BindingSource _passwordConstructionRulesTypesBindingSource;

        // User password construction rules table
        private UserPasswordConstructionRulesTableAdapter _userPasswordConstructionRulesTableAdapter;
        private BindingSource _userPasswordConstructionRulesBindingSource;
        private TmpUserPasswordConstructionRulesTableAdapter _tmpUserPasswordConstructionRulesTableAdapter;
        private BindingSource _tmpUserPasswordConstructionRulesBindingSource;

        // Education lessons table
        private EducationLessonsTableAdapter _educationLessonsTableAdapter;
        private BindingSource _educationLessonsBindingSource;
        private BindingSource _fkEducationLessonsEducationCategoriesBindingSource;
        private BindingSource _importEduLessonsBindingSource;

        // Education categories table
        private EducationCategoriesTableAdapter _educationCategoriesTableAdapter;
        private BindingSource _educationCategoriesBindingSource;
        private BindingSource _importEduCategoriesBindingSource;

        // Education answers table
        private EducationAnswersTableAdapter _educationAnswersTableAdapter;
        private BindingSource _educationAnswersBindingSource;
        private BindingSource _importEduAnswersBindingSource;

        // Education questions table
        private EducationQuestionsTableAdapter _educationQuestionsTableAdapter;
        private BindingSource _educationQuestionsBindingSource;
        private BindingSource _fkEducationQuestionsEducationLessonsBindingSource;
        private BindingSource _fkEducationQuestionAnswersEducationQuestionsBindingSource;
        private BindingSource _rightQuestionAnswerBindingSource;
        private BindingSource _questionAnswerBindingSource;
        private BindingSource _importEduQuestionsBindingSource;
        
        // Education question answers table
        private EducationQuestionAnswersTableAdapter _educationQuestionAnswersTableAdapter;
        private BindingSource _educationQuestionAnswersBindingSource;

        // Users education table
        private UserEducationTableAdapter _userEducationTableAdapter;
        private BindingSource _userEducationBindingSource;
        private BindingSource _userEducationUsersBindingSource;
        private BindingSource _userEducationCategoriesBindingSource;
        private BindingSource _fkUserEducationUsersBindingSource;

        // User group education
        private BindingSource _userEducationUserGroupsBindingSource;
        private BindingSource _userGroupEducationCategoriesBindingSource;

        // User group notification
        private BindingSource _userGroupNotificationNoticesBindingSource;
        private BindingSource _userGroupNotificationDisplayTypesBindingSource;

        // Users education answers table
        private UserEducationAnswersTableAdapter _userEducationAnswersTableAdapter;
        private BindingSource _userEducationAnswersBindingSource;
        private BindingSource _fkUserEducationAnswersUsersBindingSource;
        private BindingSource _userEducationAnswersQuestionsBindingSource;
        private BindingSource _userEducationAnswersAnswersBindingSource;

        // Notification table
        private NotificationsTableAdapter _notificationsTableAdapter;
        private BindingSource _notificationsBindingSource;
        
        // Notification display types table
        private NotificationDisplayTypesTableAdapter _notificationDisplayTypesTableAdapter;
        private BindingSource _notificationDisplayTypesBindingSource;

        // Notification scopes table
        private NotificationScopesTableAdapter _notificationScopesTableAdapter;
        private BindingSource _notificationScopesBindingSource;

        // Notification types table
        private NotificationTypesTableAdapter _notificationTypesTableAdapter;
        private BindingSource _notificationTypesBindingSource;

        // User notification table
        private UserNotificationsTableAdapter _userNotificationsTableAdapter;
        private BindingSource _userNotificationsBindingSource;
        private BindingSource _notificationsUsersBindingSource;
        private BindingSource _notificationsUserGroupsBindingSource;
        private BindingSource _userNotificationNoticesBindingSource;
        private BindingSource _userNotificationDisplayTypesBindingSource;
        private BindingSource _fkUserNotificationsUsersBindingSource;

        // User notification history table
        private UserNotificationsHistoryTableAdapter _userNotificationsHistoryTableAdapter;
        private BindingSource _userNotificationsHistoryBindingSource;
        private BindingSource _fkUserNotificationsHistoryUsersBindingSource;
        private BindingSource _userNotificationHistoryNoticesBindingSource;

        // License table
        private LicenseTableAdapter _licenseTableAdapter;
        private BindingSource _licenseBindingSource;

        // OS types table
        private OSTypesTableAdapter _osTypesTableAdapter;
        private BindingSource _osTypesBindingSource;
        private BindingSource _osPresetsBindingSource;

        // Permissions table
        private PermissionsTableAdapter _permissionsTableAdapter;
        private BindingSource _permissionsBindingSource;

        // User permissions table
        private UserPermissionsTableAdapter _userPermissionsTableAdapter;
        private BindingSource _userPermissionsBindingSource;
        private BindingSource _fkUserPermissionsUsersBindingSource;


        #endregion

        #region Data access properties

        #region Dataset

        /// <summary>
        /// DataSet property
        /// </summary>
        public NovaTendDBDataSet dataSet
        {
            get
            {
                if (_dataSet == null)
                {
                    _dataSet = new NovaTendDBDataSet();
                    _dataSet.DataSetName = "NovaTendDBDataSet";
                    _dataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
                }

                return _dataSet;
            }

            set
            {
                _dataSet = value;
            }
        }

        #endregion

        #region Connection

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
        /// Connection property
        /// </summary>
        public IDbConnection connection
        {
            get
            {
                if (_connection != null)
                    return _connection;

                if (tableAdapterManager.Connection != null)
                    return tableAdapterManager.Connection;

                return null;
            }

            set
            {
                _connection = value;
            }
        }

        #endregion

        #region Authentication systems

        /// <summary>
        /// Authentication systems types adatper property
        /// </summary>
        public AuthSystemTypesTableAdapter authSystemTypesTableAdapter
        {
            get
            {
                if (_authSystemTypesTableAdapter == null)
                {
                    _authSystemTypesTableAdapter = new AuthSystemTypesTableAdapter(connectionString);
                    _authSystemTypesTableAdapter.Fill(dataSet.AuthSystemTypes);

                    tableAdapterManager.AuthSystemTypesTableAdapter = _authSystemTypesTableAdapter;
                }

                return _authSystemTypesTableAdapter;
            }
            set
            {
                _authSystemTypesTableAdapter = value;
            }
        }

        /// <summary>
        ///  Authentication systems types table bindign source property
        /// </summary>
        public BindingSource authSystemTypesBindingSource
        {
            get
            {
                if (_authSystemTypesBindingSource == null)
                {
                    authSystemTypesTableAdapter.ClearBeforeFill = true;

                    _authSystemTypesBindingSource = new BindingSource();
                    _authSystemTypesBindingSource.DataMember = "AuthSystemTypes";
                    _authSystemTypesBindingSource.DataSource = dataSet;
                }

                return _authSystemTypesBindingSource;
            }
            set
            {
                _authSystemTypesBindingSource = value;
            }
        }

        /// <summary>
        /// Authentication systems adatper property
        /// </summary>
        public AuthSystemsTableAdapter authSystemsTableAdapter
        {
            get
            {
                if (_authSystemsTableAdapter == null)
                {
                    _authSystemsTableAdapter = new AuthSystemsTableAdapter(connectionString);
                    _authSystemsTableAdapter.Fill(dataSet.AuthSystems);

                    tableAdapterManager.AuthSystemsTableAdapter = _authSystemsTableAdapter;
                }

                return _authSystemsTableAdapter;
            }
            set
            {
                _authSystemsTableAdapter = value;
            }
        }

        /// <summary>
        ///  Authentication systems table bindign source property
        /// </summary>
        public BindingSource authSystemsBindingSource
        {
            get
            {
                if (_authSystemsBindingSource == null)
                {
                    authSystemsTableAdapter.ClearBeforeFill = true;

                    _authSystemsBindingSource = new BindingSource();
                    _authSystemsBindingSource.DataMember = "AuthSystems";
                    _authSystemsBindingSource.DataSource = dataSet;
                }

                return _authSystemsBindingSource;
            }
            set
            {
                _authSystemsBindingSource = value;
            }
        }


        /// <summary>
        ///  Authentication systems table bindign source property
        /// </summary>
        public BindingSource authSystemsSynchronizeBindingSource
        {
            get
            {
                if (_authSystemsSynchronizeBindingSource == null)
                {
                    authSystemsTableAdapter.ClearBeforeFill = true;

                    _authSystemsSynchronizeBindingSource = new BindingSource();
                    _authSystemsSynchronizeBindingSource.DataMember = "AuthSystems";
                    _authSystemsSynchronizeBindingSource.DataSource = dataSet;
                }

                return _authSystemsSynchronizeBindingSource;
            }
            set
            {
                _authSystemsSynchronizeBindingSource = value;
            }
        }

        #endregion

        #region User accounts 

        /// <summary>
        /// User accounts table adatper property
        /// </summary>
        public UserAccountsTableAdapter userAccountsTableAdapter
        {
            get
            {
                if (_userAccountsTableAdapter == null)
                {
                    _userAccountsTableAdapter = new UserAccountsTableAdapter(connectionString);
                    _userAccountsTableAdapter.Fill(dataSet.UserAccounts);

                    tableAdapterManager.UserAccountsTableAdapter = _userAccountsTableAdapter;
                }

                return _userAccountsTableAdapter;
            }
            set
            {
                _userAccountsTableAdapter = value;
            }
        }


        /// <summary>
        /// User accounts table bindign source property
        /// </summary>
        public BindingSource userAccountsBindingSource
        {
            get
            {
                if (_userAccountsBindingSource == null)
                {
                    userAccountsTableAdapter.ClearBeforeFill = true;

                    _userAccountsBindingSource = new BindingSource();
                    _userAccountsBindingSource.DataMember = "UserAccounts";
                    _userAccountsBindingSource.DataSource = dataSet;
                }

                return _userAccountsBindingSource;
            }
            set
            {
                _userAccountsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between Users and User accounts
        /// </summary>
        public BindingSource fkUserAccountsUsersBindingSource
        {
            get
            {
                if (_fkUserAccountsUsersBindingSource == null)
                {
                    userAccountsTableAdapter.ClearBeforeFill = true;

                    _fkUserAccountsUsersBindingSource = new BindingSource();
                    _fkUserAccountsUsersBindingSource.DataMember = "FK_UserAccounts_Users";
                    _fkUserAccountsUsersBindingSource.DataSource = usersBindingSource;
                }

                return _fkUserAccountsUsersBindingSource;
            }
            set
            {
                _fkUserAccountsUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between Users and User accounts archive
        /// </summary>
        public BindingSource fkUserAccountsArchiveUsersBindingSource
        {
            get
            {
                if (_fkUserAccountsArchiveUsersBindingSource == null)
                {
                    userAccountsArchiveTableAdapter.ClearBeforeFill = true;

                    _fkUserAccountsArchiveUsersBindingSource = new BindingSource();
                    _fkUserAccountsArchiveUsersBindingSource.DataMember = "FK_UserAccountsArchive_Users";
                    _fkUserAccountsArchiveUsersBindingSource.DataSource = userAccountsArchiveUsersBindingSource;
                }

                return _fkUserAccountsArchiveUsersBindingSource;
            }
            set
            {
                _fkUserAccountsArchiveUsersBindingSource = value;
            }
        }

        /// <summary>
        /// User accounts archive table adatper property
        /// </summary>
        public UserAccountsArchiveTableAdapter userAccountsArchiveTableAdapter
        {
            get
            {
                if (_userAccountsArchiveTableAdapter == null)
                {
                    _userAccountsArchiveTableAdapter = new UserAccountsArchiveTableAdapter(connectionString);
                    _userAccountsArchiveTableAdapter.Fill(dataSet.UserAccountsArchive);

                    tableAdapterManager.UserAccountsArchiveTableAdapter = _userAccountsArchiveTableAdapter;
                }

                return _userAccountsArchiveTableAdapter;
            }
            set
            {
                _userAccountsArchiveTableAdapter = value;
            }
        }
                
        /// <summary>
        /// User accounts table bindign source property
        /// </summary>
        public BindingSource userAccountsArchiveBindingSource
        {
            get
            {
                if (_userAccountsArchiveBindingSource == null)
                {
                    userAccountsArchiveTableAdapter.ClearBeforeFill = true;

                    _userAccountsArchiveBindingSource = new BindingSource();
                    _userAccountsArchiveBindingSource.DataMember = "UserAccountsArchive";
                    _userAccountsArchiveBindingSource.DataSource = dataSet;
                }

                return _userAccountsArchiveBindingSource;
            }
            set
            {
                _userAccountsArchiveBindingSource = value;
            }
        }

   
        /// <summary>
        /// Users bindign source property for user accounts archive
        /// </summary>
        public BindingSource userAccountsArchiveUsersBindingSource
        {
            get
            {
                if (_userAccountsArchiveUsersBindingSource == null)
                {
                    usersTableAdapter.ClearBeforeFill = true;

                    _userAccountsArchiveUsersBindingSource = new BindingSource();
                    _userAccountsArchiveUsersBindingSource.DataMember = "Users";
                    _userAccountsArchiveUsersBindingSource.DataSource = dataSet;
                }

                return _userAccountsArchiveUsersBindingSource;
            }
            set
            {
                _userAccountsArchiveUsersBindingSource = value;
            }
        }

        /// <summary>
        /// User accounts actions table adatper property
        /// </summary>
        public UserAccountActionsOnDeleteTableAdapter userAccountActionsOnDeleteTableAdapter
        {
            get
            {
                if (_userAccountActionsOnDeleteTableAdapter == null)
                {
                    _userAccountActionsOnDeleteTableAdapter = new UserAccountActionsOnDeleteTableAdapter(connectionString);
                    _userAccountActionsOnDeleteTableAdapter.Fill(dataSet.UserAccountActionsOnDelete);

                    tableAdapterManager.UserAccountActionsOnDeleteTableAdapter = _userAccountActionsOnDeleteTableAdapter;
                }

                return _userAccountActionsOnDeleteTableAdapter;
            }
            set
            {
                _userAccountActionsOnDeleteTableAdapter = value;
            }
        }

        /// <summary>
        /// User accounts actions table bindign source property
        /// </summary>
        public BindingSource userAccountActionsOnDeleteBindingSource
        {
            get
            {
                if (_userAccountActionsOnDeleteBindingSource == null)
                {
                    userAccountActionsOnDeleteTableAdapter.ClearBeforeFill = true;

                    _userAccountActionsOnDeleteBindingSource = new BindingSource();
                    _userAccountActionsOnDeleteBindingSource.DataMember = "UserAccountActionsOnDelete";
                    _userAccountActionsOnDeleteBindingSource.DataSource = dataSet;
                }

                return _userAccountActionsOnDeleteBindingSource;
            }
            set
            {
                _userAccountActionsOnDeleteBindingSource = value;
            }
        }

        /// <summary>
        /// User accounts actions table adatper property
        /// </summary>
        public UserAccountActionsOnInsertTableAdapter userAccountActionsOnInsertTableAdapter
        {
            get
            {
                if (_userAccountActionsOnInsertTableAdapter == null)
                {
                    _userAccountActionsOnInsertTableAdapter = new UserAccountActionsOnInsertTableAdapter(connectionString);
                    _userAccountActionsOnInsertTableAdapter.Fill(dataSet.UserAccountActionsOnInsert);

                    tableAdapterManager.UserAccountActionsOnInsertTableAdapter = _userAccountActionsOnInsertTableAdapter;
                }

                return _userAccountActionsOnInsertTableAdapter;
            }
            set
            {
                _userAccountActionsOnInsertTableAdapter = value;
            }
        }

        /// <summary>
        /// User accounts actions table bindign source property
        /// </summary>
        public BindingSource userAccountActionsOnInsertBindingSource
        {
            get
            {
                if (_userAccountActionsOnInsertBindingSource == null)
                {
                    userAccountActionsOnInsertTableAdapter.ClearBeforeFill = true;

                    _userAccountActionsOnInsertBindingSource = new BindingSource();
                    _userAccountActionsOnInsertBindingSource.DataMember = "UserAccountActionsOnInsert";
                    _userAccountActionsOnInsertBindingSource.DataSource = dataSet;
                }

                return _userAccountActionsOnInsertBindingSource;
            }
            set
            {
                _userAccountActionsOnInsertBindingSource = value;
            }
        }

        /// <summary>
        /// User accounts actions table adatper property
        /// </summary>
        public UserAccountActionsOnUpdateTableAdapter userAccountActionsOnUpdateTableAdapter
        {
            get
            {
                if (_userAccountActionsOnUpdateTableAdapter == null)
                {
                    _userAccountActionsOnUpdateTableAdapter = new UserAccountActionsOnUpdateTableAdapter(connectionString);
                    _userAccountActionsOnUpdateTableAdapter.Fill(dataSet.UserAccountActionsOnUpdate);

                    tableAdapterManager.UserAccountActionsOnUpdateTableAdapter = _userAccountActionsOnUpdateTableAdapter;
                }

                return _userAccountActionsOnUpdateTableAdapter;
            }
            set
            {
                _userAccountActionsOnUpdateTableAdapter = value;
            }
        }

        /// <summary>
        /// User accounts actions table bindign source property
        /// </summary>
        public BindingSource userAccountActionsOnUpdateBindingSource
        {
            get
            {
                if (_userAccountActionsOnUpdateBindingSource == null)
                {
                    userAccountActionsOnUpdateTableAdapter.ClearBeforeFill = true;

                    _userAccountActionsOnUpdateBindingSource = new BindingSource();
                    _userAccountActionsOnUpdateBindingSource.DataMember = "UserAccountActionsOnUpdate";
                    _userAccountActionsOnUpdateBindingSource.DataSource = dataSet;
                }

                return _userAccountActionsOnUpdateBindingSource;
            }
            set
            {
                _userAccountActionsOnUpdateBindingSource = value;
            }
        }

        /// <summary>
        ///  Authentication systems table bindign source property for user accounts table
        /// </summary>
        public BindingSource userAccontsAuthSystemsBindingSource
        {
            get
            {
                if (_userAccontsAuthSystemsBindingSource == null)
                {
                    authSystemsTableAdapter.ClearBeforeFill = true;

                    _userAccontsAuthSystemsBindingSource = new BindingSource();
                    _userAccontsAuthSystemsBindingSource.DataMember = "AuthSystems";
                    _userAccontsAuthSystemsBindingSource.DataSource = dataSet;
                }

                return _userAccontsAuthSystemsBindingSource;
            }
            set
            {
                _userAccontsAuthSystemsBindingSource = value;
            }
        }

        /// <summary>
        ///  Authentication systems table bindign source property for user accounts archive table
        /// </summary>
        public BindingSource userAccontsArchiveAuthSystemsBindingSource
        {
            get
            {
                if (_userAccontsArchiveAuthSystemsBindingSource == null)
                {
                    authSystemsTableAdapter.ClearBeforeFill = true;

                    _userAccontsArchiveAuthSystemsBindingSource = new BindingSource();
                    _userAccontsArchiveAuthSystemsBindingSource.DataMember = "AuthSystems";
                    _userAccontsArchiveAuthSystemsBindingSource.DataSource = dataSet;
                }

                return _userAccontsArchiveAuthSystemsBindingSource;
            }
            set
            {
                _userAccontsArchiveAuthSystemsBindingSource = value;
            }
        }
        
        #endregion

        #region Users

        /// <summary>
        /// Users table adatper property
        /// </summary>
        public UsersTableAdapter usersTableAdapter
        {
            get
            {
                if (_usersTableAdapter == null)
                {
                    _usersTableAdapter = new UsersTableAdapter(connectionString);
                    _usersTableAdapter.Fill(dataSet.Users);

                    tableAdapterManager.UsersTableAdapter = _usersTableAdapter;
                }

                return _usersTableAdapter;
            }
            set 
            {
                _usersTableAdapter = value;
            }
        }

        /// <summary>
        /// Users table bindign source property
        /// </summary>
        public BindingSource usersBindingSource
        {
            get
            {
                if (_usersBindingSource == null)
                {
                    usersTableAdapter.ClearBeforeFill = true;

                    _usersBindingSource = new BindingSource();
                    _usersBindingSource.DataMember = "Users";
                    _usersBindingSource.DataSource = dataSet;
                }

                return _usersBindingSource;
            }
            set
            {
                _usersBindingSource = value;
            }
        }
                
        /// <summary>
        /// Binding source for relation between tables Users and UserPasswordConstructionRules
        /// </summary>
        public BindingSource fkUserPasswordConstructionRulesUsersBindingSource
        {
            get
            {
                if (_fkUserPasswordConstructionRulesUsersBindingSource == null)
                {
                    userPasswordConstructionRulesTableAdapter.ClearBeforeFill = true;

                    _fkUserPasswordConstructionRulesUsersBindingSource = new BindingSource();
                    _fkUserPasswordConstructionRulesUsersBindingSource.DataMember = "FK_UserPasswordConstructionRules_Users";
                    _fkUserPasswordConstructionRulesUsersBindingSource.DataSource = usersBindingSource;
                }

                return _fkUserPasswordConstructionRulesUsersBindingSource;
            }
            set
            {
                _fkUserPasswordConstructionRulesUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between tables Users and TmpUserPasswordConstructionRules
        /// </summary>
        public BindingSource fkTmpUserPasswordConstructionRulesUsersBindingSource
        {
            get
            {
                if (_fkTmpUserPasswordConstructionRulesUsersBindingSource == null)
                {
                    tmpUserPasswordConstructionRulesTableAdapter.ClearBeforeFill = true;

                    _fkTmpUserPasswordConstructionRulesUsersBindingSource = new BindingSource();
                    _fkTmpUserPasswordConstructionRulesUsersBindingSource.DataMember = "FK_TmpUserPasswordConstructionRules_Users";
                    _fkTmpUserPasswordConstructionRulesUsersBindingSource.DataSource = usersBindingSource;
                }

                return _fkTmpUserPasswordConstructionRulesUsersBindingSource;
            }
            set
            {
                _fkTmpUserPasswordConstructionRulesUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between tables Users and UserCheckValues
        /// </summary>
        public BindingSource fkUserCheckValuesUsersBindingSource
        {
            get
            {
                if (_fkUserCheckValuesUsersBindingSource == null)
                {
                    userCheckValuesTableAdapter.ClearBeforeFill = true;

                    _fkUserCheckValuesUsersBindingSource = new BindingSource();
                    _fkUserCheckValuesUsersBindingSource.DataMember = "FK_UserCheckValues_Users";
                    _fkUserCheckValuesUsersBindingSource.DataSource = usersBindingSource;
                }

                return _fkUserCheckValuesUsersBindingSource;
            }
            set
            {
                _fkUserCheckValuesUsersBindingSource = value;
            }
        }

        #endregion

        #region User groups

        /// <summary>
        /// User groups table adapter property
        /// </summary>
        public UserGroupsTableAdapter userGroupsTableAdapter
        {
            get
            {
                if (_userGroupsTableAdapter == null)
                {
                    _userGroupsTableAdapter = new UserGroupsTableAdapter(connectionString);
                    _userGroupsTableAdapter.Fill(dataSet.UserGroups);

                    tableAdapterManager.UserGroupsTableAdapter = _userGroupsTableAdapter;
                }

                return _userGroupsTableAdapter;
            }
            set
            {
                _userGroupsTableAdapter = value;
            }
        }

        /// <summary>
        ///  Authentication systems table bindign source property for user groups table
        /// </summary>
        public BindingSource userGroupsAuthSystemsBindingSource
        {
            get
            {
                if (_userGroupsAuthSystemsBindingSource == null)
                {
                    authSystemsTableAdapter.ClearBeforeFill = true;

                    _userGroupsAuthSystemsBindingSource = new BindingSource();
                    _userGroupsAuthSystemsBindingSource.DataMember = "AuthSystems";
                    _userGroupsAuthSystemsBindingSource.DataSource = dataSet;
                }

                return _userGroupsAuthSystemsBindingSource;
            }
            set
            {
                _userGroupsAuthSystemsBindingSource = value;
            }
        }

        /// <summary>
        /// User groups table binding source property
        /// </summary>
        public BindingSource userGroupsBindingSource
        {
            get
            {
                if (_userGroupsBindingSource == null)
                {
                    userGroupsTableAdapter.ClearBeforeFill = true;

                    _userGroupsBindingSource = new BindingSource();
                    _userGroupsBindingSource.DataMember = "UserGroups";
                    _userGroupsBindingSource.DataSource = dataSet;
                }

                return _userGroupsBindingSource;
            }
            set
            {
                _userGroupsBindingSource = value;
            }
        }

        /// <summary>
        /// User group users table adapter property
        /// </summary>
        public UserGroupUsersTableAdapter userGroupUsersTableAdapter
        {
            get
            {
                if (_userGroupUsersTableAdapter == null)
                {
                    _userGroupUsersTableAdapter = new UserGroupUsersTableAdapter(connectionString);
                    _userGroupUsersTableAdapter.Fill(dataSet.UserGroupUsers);

                    tableAdapterManager.UserGroupUsersTableAdapter = _userGroupUsersTableAdapter;
                }

                return _userGroupUsersTableAdapter;
            }
            set
            {
                _userGroupUsersTableAdapter = value;
            }
        }

        /// <summary>
        /// User group users table binding source property
        /// </summary>
        public BindingSource userGroupUsersBindingSource
        {
            get
            {
                if (_userGroupUsersBindingSource == null)
                {
                    userGroupUsersTableAdapter.ClearBeforeFill = true;

                    _userGroupUsersBindingSource = new BindingSource();
                    _userGroupUsersBindingSource.DataMember = "UserGroupUsers";
                    _userGroupUsersBindingSource.DataSource = dataSet;
                }

                return _userGroupUsersBindingSource;
            }
            set
            {
                _userGroupUsersBindingSource = value;
            }
        }


        /// <summary>
        /// User group authentication systems table adapter property
        /// </summary>
        public UserGroupAuthSystemsTableAdapter userGroupAuthSystemsTableAdapter
        {
            get
            {
                if (_userGroupAuthSystemsTableAdapter == null)
                {
                    _userGroupAuthSystemsTableAdapter = new UserGroupAuthSystemsTableAdapter(connectionString);
                    _userGroupAuthSystemsTableAdapter.Fill(dataSet.UserGroupAuthSystems);

                    tableAdapterManager.UserGroupAuthSystemsTableAdapter = _userGroupAuthSystemsTableAdapter;
                }

                return _userGroupAuthSystemsTableAdapter;
            }
            set
            {
                _userGroupAuthSystemsTableAdapter = value;
            }
        }

        /// <summary>
        /// User group authentication systems table binding source property
        /// </summary>
        public BindingSource userGroupAuthSystemsBindingSource
        {
            get
            {
                if (_userGroupAuthSystemsBindingSource == null)
                {
                    userGroupAuthSystemsTableAdapter.ClearBeforeFill = true;

                    _userGroupAuthSystemsBindingSource = new BindingSource();
                    _userGroupAuthSystemsBindingSource.DataMember = "UserGroupAuthSystems";
                    _userGroupAuthSystemsBindingSource.DataSource = dataSet;
                }

                return _userGroupAuthSystemsBindingSource;
            }
            set
            {
                _userGroupAuthSystemsBindingSource = value;
            }
        }

        /// <summary>
        /// User group education table adapter property
        /// </summary>
        public UserGroupEducationTableAdapter userGroupEducationTableAdapter
        {
            get
            {
                if (_userGroupEducationTableAdapter == null)
                {
                    _userGroupEducationTableAdapter = new UserGroupEducationTableAdapter(connectionString);
                    _userGroupEducationTableAdapter.Fill(dataSet.UserGroupEducation);

                    tableAdapterManager.UserGroupEducationTableAdapter = _userGroupEducationTableAdapter;
                }

                return _userGroupEducationTableAdapter;
            }
            set
            {
                _userGroupEducationTableAdapter = value;
            }
        }

        /// <summary>
        /// User group education table binding source property
        /// </summary>
        public BindingSource userGroupEducationBindingSource
        {
            get
            {
                if (_userGroupEducationBindingSource == null)
                {
                    userGroupEducationTableAdapter.ClearBeforeFill = true;

                    _userGroupEducationBindingSource = new BindingSource();
                    _userGroupEducationBindingSource.DataMember = "UserGroupEducation";
                    _userGroupEducationBindingSource.DataSource = dataSet;
                }

                return _userGroupEducationBindingSource;
            }
            set
            {
                _userGroupEducationBindingSource = value;
            }
        }

        /// <summary>
        /// User group notifications table adapter property
        /// </summary>
        public UserGroupNotificationsTableAdapter userGroupNotificationsTableAdapter
        {
            get
            {
                if (_userGroupNotificationsTableAdapter == null)
                {
                    _userGroupNotificationsTableAdapter = new UserGroupNotificationsTableAdapter(connectionString);
                    _userGroupNotificationsTableAdapter.Fill(dataSet.UserGroupNotifications);

                    tableAdapterManager.UserGroupNotificationsTableAdapter = _userGroupNotificationsTableAdapter;
                }

                return _userGroupNotificationsTableAdapter;
            }
            set
            {
                _userGroupNotificationsTableAdapter = value;
            }
        }

        /// <summary>
        /// User group notifications table binding source property
        /// </summary>
        public BindingSource userGroupNotifictionsBindingSource
        {
            get
            {
                if (_userGroupNotificationsBindingSource == null)
                {
                    userGroupNotificationsTableAdapter.ClearBeforeFill = true;

                    _userGroupNotificationsBindingSource = new BindingSource();
                    _userGroupNotificationsBindingSource.DataMember = "UserGroupNotifications";
                    _userGroupNotificationsBindingSource.DataSource = dataSet;
                }

                return _userGroupNotificationsBindingSource;
            }
            set
            {
                _userGroupNotificationsBindingSource = value;
            }
        }

        /// <summary>
        /// User group permissions table adapter property
        /// </summary>
        public UserGroupPermissionsTableAdapter userGroupPermissionsTableAdapter
        {
            get
            {
                if (_userGroupPermissionsTableAdapter == null)
                {
                    _userGroupPermissionsTableAdapter = new UserGroupPermissionsTableAdapter(connectionString);
                    _userGroupPermissionsTableAdapter.Fill(dataSet.UserGroupPermissions);

                    tableAdapterManager.UserGroupPermissionsTableAdapter = _userGroupPermissionsTableAdapter;
                }

                return _userGroupPermissionsTableAdapter;
            }
            set
            {
                _userGroupPermissionsTableAdapter = value;
            }
        }

        /// <summary>
        /// User group permisions table binding source property
        /// </summary>
        public BindingSource userGroupPermissionsBindingSource
        {
            get
            {
                if (_userGroupPermissionsBindingSource == null)
                {
                    userGroupPermissionsTableAdapter.ClearBeforeFill = true;

                    _userGroupPermissionsBindingSource = new BindingSource();
                    _userGroupPermissionsBindingSource.DataMember = "UserGroupPermissions";
                    _userGroupPermissionsBindingSource.DataSource = dataSet;
                }

                return _userGroupPermissionsBindingSource;
            }
            set
            {
                _userGroupPermissionsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between user groups and users
        /// </summary>
        public BindingSource fkUserGroupsUsersBindingSource
        {
            get
            {
                if (_fkUserGroupsUsersBindingSource == null)
                {
                    userGroupUsersTableAdapter.ClearBeforeFill = true;

                    _fkUserGroupsUsersBindingSource = new BindingSource();
                    _fkUserGroupsUsersBindingSource.DataMember = "FK_UserGroupUsers_Users";
                    _fkUserGroupsUsersBindingSource.DataSource = usersBindingSource;
                }

                return _fkUserGroupsUsersBindingSource;
            }
            set
            {
                _fkUserGroupsUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between user groups permissions and user groups
        /// </summary>
        public BindingSource fkUserGroupsUsersGroupPermissionsBindingSource
        {
            get
            {
                if (_fkUserGroupsUsersGroupPermissionsBindingSource == null)
                {
                    userGroupPermissionsTableAdapter.ClearBeforeFill = true;

                    _fkUserGroupsUsersGroupPermissionsBindingSource = new BindingSource();
                    _fkUserGroupsUsersGroupPermissionsBindingSource.DataMember = "FK_UserGroupPermissions_UserGroups";
                    _fkUserGroupsUsersGroupPermissionsBindingSource.DataSource = userGroupsBindingSource;
                }

                return _fkUserGroupsUsersGroupPermissionsBindingSource;
            }
            set
            {
                _fkUserGroupsUsersGroupPermissionsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between user groups auth systems and user groups
        /// </summary>
        public BindingSource fkUserGroupsUsersGroupAuthSystemsBindingSource
        {
            get
            {
                if (_fkUserGroupsUsersGroupAuthSystemsBindingSource == null)
                {
                    userGroupAuthSystemsTableAdapter.ClearBeforeFill = true;

                    _fkUserGroupsUsersGroupAuthSystemsBindingSource = new BindingSource();
                    _fkUserGroupsUsersGroupAuthSystemsBindingSource.DataMember = "FK_UserGroupAuthSystems_UserGroups";
                    _fkUserGroupsUsersGroupAuthSystemsBindingSource.DataSource = userGroupsBindingSource;
                }

                return _fkUserGroupsUsersGroupAuthSystemsBindingSource;
            }
            set
            {
                _fkUserGroupsUsersGroupAuthSystemsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between users and user groups
        /// </summary>
        public BindingSource fkUsersUserGroupsBindingSource
        {
            get
            {
                if (_fkUsersUserGroupsBindingSource == null)
                {
                    userGroupUsersTableAdapter.ClearBeforeFill = true;

                    _fkUsersUserGroupsBindingSource = new BindingSource();
                    _fkUsersUserGroupsBindingSource.DataMember = "FK_UserGroupUsers_UserGroups";
                    _fkUsersUserGroupsBindingSource.DataSource = userGroupsBindingSource;
                }

                return _fkUsersUserGroupsBindingSource;
            }
            set
            {
                _fkUsersUserGroupsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between user groups education and user groups
        /// </summary>
        public BindingSource fkUserGroupsUsersGroupEducationBindingSource
        {
            get
            {
                if (_fkUserGroupsUsersGroupEducationBindingSource == null)
                {
                    userGroupEducationTableAdapter.ClearBeforeFill = true;

                    _fkUserGroupsUsersGroupEducationBindingSource = new BindingSource();
                    _fkUserGroupsUsersGroupEducationBindingSource.DataMember = "FK_UserGroupEducation_UserGroups";
                    _fkUserGroupsUsersGroupEducationBindingSource.DataSource = userEducationUserGroupsBindingSource;
                }

                return _fkUserGroupsUsersGroupEducationBindingSource;
            }
            set
            {
                _fkUserGroupsUsersGroupEducationBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between user groups notifications and user groups
        /// </summary>
        public BindingSource fkUserGroupsUsersGroupNotificationsBindingSource
        {
            get
            {
                if (_fkUserGroupsUsersGroupNotificationsBindingSource == null)
                {
                    userGroupNotificationsTableAdapter.ClearBeforeFill = true;

                    _fkUserGroupsUsersGroupNotificationsBindingSource = new BindingSource();
                    _fkUserGroupsUsersGroupNotificationsBindingSource.DataMember = "FK_UserGroupNotifications_UserGroups";
                    _fkUserGroupsUsersGroupNotificationsBindingSource.DataSource = notificationsUserGroupsBindingSource;
                }

                return _fkUserGroupsUsersGroupNotificationsBindingSource;
            }
            set
            {
                _fkUserGroupsUsersGroupNotificationsBindingSource = value;
            }
        }

        #endregion

        #region User personal data

        /// <summary>
        /// Users table bindign source property for personal page
        /// </summary>
        public BindingSource personalUsersBindingSource
        {
            get
            {
                if (_personalUsersBindingSource == null)
                {
                    usersTableAdapter.ClearBeforeFill = true;

                    _personalUsersBindingSource = new BindingSource();
                    _personalUsersBindingSource.DataMember = "Users";
                    _personalUsersBindingSource.DataSource = dataSet;
                }

                return _personalUsersBindingSource;
            }
            set
            {
                _personalUsersBindingSource = value;
            }
        }


        /// <summary>
        /// Binding source for relation between tables Users and UserPasswordConstructionRules for personal page
        /// </summary>
        public BindingSource fkPersonalUserPasswordConstructionRulesUsersBindingSource
        {
            get
            {
                if (_fkPersonalUserPasswordConstructionRulesUsersBindingSource == null)
                {
                    userPasswordConstructionRulesTableAdapter.ClearBeforeFill = true;

                    _fkPersonalUserPasswordConstructionRulesUsersBindingSource = new BindingSource();
                    _fkPersonalUserPasswordConstructionRulesUsersBindingSource.DataMember = "FK_UserPasswordConstructionRules_Users";
                    _fkPersonalUserPasswordConstructionRulesUsersBindingSource.DataSource = personalUsersBindingSource;
                }

                return _fkPersonalUserPasswordConstructionRulesUsersBindingSource;
            }
            set
            {
                _fkPersonalUserPasswordConstructionRulesUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between tables Users and TmpUserPasswordConstructionRules for personal page
        /// </summary>
        public BindingSource fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource
        {
            get
            {
                if (_fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource == null)
                {
                    tmpUserPasswordConstructionRulesTableAdapter.ClearBeforeFill = true;

                    _fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource = new BindingSource();
                    _fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.DataMember = "FK_TmpUserPasswordConstructionRules_Users";
                    _fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.DataSource = personalUsersBindingSource;
                }

                return _fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource;
            }
            set
            {
                _fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between tables Users and UserCheckValues for personal page
        /// </summary>
        public BindingSource fkPersonalUserCheckValuesUsersBindingSource
        {
            get
            {
                if (_fkPersonalUserCheckValuesUsersBindingSource == null)
                {
                    userCheckValuesTableAdapter.ClearBeforeFill = true;

                    _fkPersonalUserCheckValuesUsersBindingSource = new BindingSource();
                    _fkPersonalUserCheckValuesUsersBindingSource.DataMember = "FK_UserCheckValues_Users";
                    _fkPersonalUserCheckValuesUsersBindingSource.DataSource = personalUsersBindingSource;
                }

                return _fkPersonalUserCheckValuesUsersBindingSource;
            }
            set
            {
                _fkPersonalUserCheckValuesUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between Users and User accounts for personal page
        /// </summary>
        public BindingSource fkPersonalUserAccountsUsersBindingSource
        {
            get
            {
                if (_fkPersonalUserAccountsUsersBindingSource == null)
                {
                    userAccountsTableAdapter.ClearBeforeFill = true;

                    _fkPersonalUserAccountsUsersBindingSource = new BindingSource();
                    _fkPersonalUserAccountsUsersBindingSource.DataMember = "FK_UserAccounts_Users";
                    _fkPersonalUserAccountsUsersBindingSource.DataSource = personalUsersBindingSource;
                }

                return _fkPersonalUserAccountsUsersBindingSource;
            }
            set
            {
                _fkPersonalUserAccountsUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between user permissions and users for personal page
        /// </summary>
        public BindingSource fkPersonalUserPermissionsUsersBindingSource
        {
            get
            {
                if (_fkPersonalUserPermissionsUsersBindingSource == null)
                {
                    userPermissionsTableAdapter.ClearBeforeFill = true;

                    _fkPersonalUserPermissionsUsersBindingSource = new BindingSource();
                    _fkPersonalUserPermissionsUsersBindingSource.DataMember = "FK_UserPermissions_Users";
                    _fkPersonalUserPermissionsUsersBindingSource.DataSource = personalUsersBindingSource;
                }

                return _fkPersonalUserPermissionsUsersBindingSource;
            }
            set
            {
                _fkPersonalUserPermissionsUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between user groups and users for personal page
        /// </summary>
        public BindingSource fkPersonalUsersUserGroupsBindingSource
        {
            get
            {
                if (_fkPersonalUsersUserGroupsBindingSource == null)
                {
                    userGroupUsersTableAdapter.ClearBeforeFill = true;

                    _fkPersonalUsersUserGroupsBindingSource = new BindingSource();
                    _fkPersonalUsersUserGroupsBindingSource.DataMember = "FK_UserGroupUsers_Users";
                    _fkPersonalUsersUserGroupsBindingSource.DataSource = personalUsersBindingSource;
                }

                return _fkPersonalUsersUserGroupsBindingSource;
            }
            set
            {
                _fkPersonalUsersUserGroupsBindingSource = value;
            }
        }

        /// <summary>
        /// Permissions bindindg source property for personal page
        /// </summary>
        public BindingSource personalPermissionsBindingSource
        {
            get
            {
                if (_personalPermissionsBindingSource == null)
                {
                    permissionsTableAdapter.ClearBeforeFill = true;

                    _personalPermissionsBindingSource = new BindingSource();
                    _personalPermissionsBindingSource.DataMember = "Permissions";
                    _personalPermissionsBindingSource.DataSource = dataSet;
                }

                return _personalPermissionsBindingSource;
            }
            set
            {
                _personalPermissionsBindingSource = value;
            }
        }


        /// <summary>
        /// User groups binding source property for personal page
        /// </summary>
        public BindingSource personalUserGroupsBindingSource
        {
            get
            {
                if (_personalUserGroupsBindingSource == null)
                {
                    userGroupsTableAdapter.ClearBeforeFill = true;

                    _personalUserGroupsBindingSource = new BindingSource();
                    _personalUserGroupsBindingSource.DataMember = "UserGroups";
                    _personalUserGroupsBindingSource.DataSource = dataSet;
                }

                return _personalUserGroupsBindingSource;
            }
            set
            {
                _personalUserGroupsBindingSource = value;
            }
        }
        /// <summary>
        ///  Authentication systems table bindign source property for user accounts table for personal page
        /// </summary>
        public BindingSource personalUserAccountAuthSystemsBindingSource
        {
            get
            {
                if (_personalUserAccountAuthSystemsBindingSource == null)
                {
                    authSystemsTableAdapter.ClearBeforeFill = true;

                    _personalUserAccountAuthSystemsBindingSource = new BindingSource();
                    _personalUserAccountAuthSystemsBindingSource.DataMember = "AuthSystems";
                    _personalUserAccountAuthSystemsBindingSource.DataSource = dataSet;
                }

                return _personalUserAccountAuthSystemsBindingSource;
            }
            set
            {
                _personalUserAccountAuthSystemsBindingSource = value;
            }
        }

        /// <summary>
        /// User check values screen objects binding source property for personal page
        /// </summary>
        public BindingSource personalUserCheckValuesScreenObjectsBindingSource
        {
            get
            {
                if (_personalUserCheckValuesScreenObjectsBindingSource == null)
                {
                    userCheckValuesScreenObjectsTableAdapter.ClearBeforeFill = true;

                    _personalUserCheckValuesScreenObjectsBindingSource = new BindingSource();
                    _personalUserCheckValuesScreenObjectsBindingSource.DataMember = "UserCheckValuesScreenObjects";
                    _personalUserCheckValuesScreenObjectsBindingSource.DataSource = dataSet;
                }

                return _personalUserCheckValuesScreenObjectsBindingSource;
            }
            set
            {
                _personalUserCheckValuesScreenObjectsBindingSource = value;
            }
        }

        #endregion

        #region Controlled programs

        /// <summary>
        /// Controlled programs table adapter property
        /// </summary>
        public ControlledProgramsTableAdapter controlledProgramsTableAdapter
        {
            get
            {
                if (_controlledProgramsTableAdapter == null)
                {
                    _controlledProgramsTableAdapter = new ControlledProgramsTableAdapter(connectionString);
                    _controlledProgramsTableAdapter.Fill(dataSet.ControlledPrograms);

                    tableAdapterManager.ControlledProgramsTableAdapter = _controlledProgramsTableAdapter;
                }

                return _controlledProgramsTableAdapter;
            }
            set
            {
                _controlledProgramsTableAdapter = value;
            }
        }

        /// <summary>
        /// Controlled programs table binding source property
        /// </summary>
        public BindingSource controlledProgramsBindingSource
        {
            get
            {
                if (_controlledProgramsBindingSource == null)
                {
                    controlledProgramsTableAdapter.ClearBeforeFill = true;

                    _controlledProgramsBindingSource = new BindingSource();
                    _controlledProgramsBindingSource.DataMember = "ControlledPrograms";
                    _controlledProgramsBindingSource.DataSource = dataSet;
                }

                return _controlledProgramsBindingSource;
            }
            set
            {
                _controlledProgramsBindingSource = value;
            }
        }

        #endregion

        #region Schedule

        /// <summary>
        /// Schedule actions table adapter property
        /// </summary>
        public ScheduleActionsTableAdapter scheduleActionsTableAdapter
        {
            get
            {
                if (_scheduleActionsTableAdapter == null)
                {
                    _scheduleActionsTableAdapter = new ScheduleActionsTableAdapter(connectionString);
                    _scheduleActionsTableAdapter.Fill(dataSet.ScheduleActions);

                    tableAdapterManager.ScheduleActionsTableAdapter = _scheduleActionsTableAdapter;
                }

                return _scheduleActionsTableAdapter;
            }
            set
            {
                _scheduleActionsTableAdapter = value;
            }
        }

        /// <summary>
        /// Schedule actions table binding source property
        /// </summary>
        public BindingSource scheduleActionsBindingSource
        {
            get
            {
                if (_scheduleActionsBindingSource == null)
                {
                    scheduleActionsTableAdapter.ClearBeforeFill = true;

                    _scheduleActionsBindingSource = new BindingSource();
                    _scheduleActionsBindingSource.DataMember = "ScheduleActions";
                    _scheduleActionsBindingSource.DataSource = dataSet;
                }

                return _scheduleActionsBindingSource;
            }
            set
            {
                _scheduleActionsBindingSource = value;
            }
        }

        /// <summary>
        /// Schedule functions table adapter property
        /// </summary>
        public ScheduleFunctionsTableAdapter scheduleFunctionsTableAdapter
        {
            get
            {
                if (_scheduleFunctionsTableAdapter == null)
                {
                    _scheduleFunctionsTableAdapter = new ScheduleFunctionsTableAdapter(connectionString);
                    _scheduleFunctionsTableAdapter.Fill(dataSet.ScheduleFunctions);

                    tableAdapterManager.ScheduleFunctionsTableAdapter = _scheduleFunctionsTableAdapter;
                }

                return _scheduleFunctionsTableAdapter;
            }
            set
            {
                _scheduleFunctionsTableAdapter = value;
            }
        }

        /// <summary>
        /// Schedule functions table binding source property
        /// </summary>
        public BindingSource scheduleFunctionsBindingSource
        {
            get
            {
                if (_scheduleFunctionsBindingSource == null)
                {
                    scheduleFunctionsTableAdapter.ClearBeforeFill = true;

                    _scheduleFunctionsBindingSource = new BindingSource();
                    _scheduleFunctionsBindingSource.DataMember = "ScheduleFunctions";
                    _scheduleFunctionsBindingSource.DataSource = dataSet;
                }

                return _scheduleFunctionsBindingSource;
            }
            set
            {
                _scheduleFunctionsBindingSource = value;
            }
        }

        /// <summary>
        /// Schedule table adapter property
        /// </summary>
        public ScheduleTableAdapter scheduleTableAdapter
        {
            get
            {
                if (_scheduleTableAdapter == null)
                {
                    _scheduleTableAdapter = new ScheduleTableAdapter(connectionString);
                    _scheduleTableAdapter.Fill(dataSet.Schedule);

                    tableAdapterManager.ScheduleTableAdapter = _scheduleTableAdapter;
                }

                return _scheduleTableAdapter;
            }
            set
            {
                _scheduleTableAdapter = value;
            }
        }

        /// <summary>
        /// Schedule binding source property
        /// </summary>
        public BindingSource scheduleBindingSource
        {
            get
            {
                if (_scheduleBindingSource == null)
                {
                    scheduleTableAdapter.ClearBeforeFill = true;

                    _scheduleBindingSource = new BindingSource();
                    _scheduleBindingSource.DataMember = "Schedule";
                    _scheduleBindingSource.DataSource = dataSet;
                }

                return _scheduleBindingSource;
            }
            set
            {
                _scheduleBindingSource = value;
            }
        }

        /// <summary>
        /// Computers binding source property for schedule
        /// </summary>
        public BindingSource scheduleComputersBindindSource
        {
            get
            {
                if (_scheduleComputersBindindSource == null)
                {
                    computersTableAdapter.ClearBeforeFill = true;

                    _scheduleComputersBindindSource = new BindingSource();
                    _scheduleComputersBindindSource.DataMember = "Computers";
                    _scheduleComputersBindindSource.DataSource = dataSet;
                }

                return _scheduleComputersBindindSource;
            }
            set
            {
                _scheduleComputersBindindSource = value;
            }
        }

        /// <summary>
        /// Contolled programs binding source property for schedule
        /// </summary>
        public BindingSource scheduleProgramsBindindSource
        {
            get
            {
                if (_scheduleProgramsBindindSource == null)
                {
                    controlledProgramsTableAdapter.ClearBeforeFill = true;

                    _scheduleProgramsBindindSource = new BindingSource();
                    _scheduleProgramsBindindSource.DataMember = "ControlledPrograms";
                    _scheduleProgramsBindindSource.DataSource = dataSet;
                }

                return _scheduleProgramsBindindSource;
            }
            set
            {
                _scheduleProgramsBindindSource = value;
            }
        }

        #endregion
        
        #region Computers

        /// <summary>
        /// Computers table adapter property
        /// </summary>
        public ComputersTableAdapter computersTableAdapter
        {
            get
            {
                if (_computersTableAdapter == null)
                {
                    _computersTableAdapter = new ComputersTableAdapter(connectionString);
                    _computersTableAdapter.Fill(dataSet.Computers);

                    tableAdapterManager.ComputersTableAdapter = _computersTableAdapter;
                }

                return _computersTableAdapter;
            }
            set
            {
                _computersTableAdapter = value;
            }
        }

        /// <summary>
        /// Computers table binding source property
        /// </summary>
        public BindingSource computersBindingSource
        {
            get
            {
                if (_computersBindingSource == null)
                {
                    computersTableAdapter.ClearBeforeFill = true;

                    _computersBindingSource = new BindingSource();
                    _computersBindingSource.DataMember = "Computers";
                    _computersBindingSource.DataSource = dataSet;
                }

                return _computersBindingSource;
            }
            set
            {
                _computersBindingSource = value;
            }
        }

        #endregion

        #region Preset

        /// <summary>
        /// Preset table adapter property
        /// </summary>
        public PresetTableAdapter presetTableAdapter
        {
            get
            {
                if (_presetTableAdapter == null)
                {
                    _presetTableAdapter = new PresetTableAdapter(connectionString);
                    _presetTableAdapter.Fill(dataSet.Preset);

                    tableAdapterManager.PresetTableAdapter = _presetTableAdapter;
                }

                return _presetTableAdapter;
            }
            set
            {
                _presetTableAdapter = value;
            }
        }

        /// <summary>
        /// Preset binding source property
        /// </summary>
        public BindingSource presetBindingSource
        {
            get
            {
                if (_presetBindingSource == null)
                {
                    presetTableAdapter.ClearBeforeFill = true;

                    _presetBindingSource = new BindingSource();
                    _presetBindingSource.DataMember = "Preset";
                    _presetBindingSource.DataSource = dataSet;
                }

                return _presetBindingSource;
            }
            set
            {
                _presetBindingSource = value;
            }
        }

        /// <summary>
        /// Screens binding source for table Presets
        /// </summary>
        public BindingSource presetScreensBindingSource
        {
            get
            {
                if (_presetScreensBindingSource == null)
                {
                    screensTableAdapter.ClearBeforeFill = true;

                    _presetScreensBindingSource = new BindingSource();
                    _presetScreensBindingSource.DataMember = "Screens";
                    _presetScreensBindingSource.DataSource = dataSet;
                }

                return _presetScreensBindingSource;
            }
            set
            {
                _presetScreensBindingSource = value;
            }
        }

        /// <summary>
        /// Preset details table adapter property
        /// </summary>
        public PresetDetailsTableAdapter presetDetailsTableAdapter
        {
            get
            {
                if (_presetDetailsTableAdapter == null)
                {
                    _presetDetailsTableAdapter = new PresetDetailsTableAdapter(connectionString);
                    
                    if (presetBindingSource.Current != null)
                        _presetDetailsTableAdapter.Fill(dataSet.PresetDetails, (int)(presetBindingSource.Current as DataRowView).Row["ID"]);

                    tableAdapterManager.PresetDetailsTableAdapter = _presetDetailsTableAdapter;
                }

                return _presetDetailsTableAdapter;
            }
            set
            {
                _presetDetailsTableAdapter = value;
            }
        }

        /// <summary>
        /// Preset details binding source property
        /// </summary>
        public BindingSource presetDetailsBindingSource
        {
            get
            {
                if (_presetDetailsBindingSource == null)
                {
                    presetDetailsTableAdapter.ClearBeforeFill = true;

                    _presetDetailsBindingSource = new BindingSource();
                    _presetDetailsBindingSource.DataMember = "PresetDetails";
                    _presetDetailsBindingSource.DataSource = dataSet;
                }

                return _presetDetailsBindingSource;
            }
            set
            {
                _presetDetailsBindingSource = value;
            }
        }

        /// <summary>
        /// Screen objects binding source for table PresetDetails
        /// </summary>
        public BindingSource presetDetailsScreenObjectsBindingSource
        {
            get
            {
                if (_presetDetailsScreenObjectsBindingSource == null)
                {
                    screenObjectsTableAdapter.ClearBeforeFill = true;

                    _presetDetailsScreenObjectsBindingSource = new BindingSource();
                    _presetDetailsScreenObjectsBindingSource.DataMember = "ScreenObjects";
                    _presetDetailsScreenObjectsBindingSource.DataSource = dataSet;
                }

                return _presetDetailsScreenObjectsBindingSource;
            }
            set
            {
                _presetDetailsScreenObjectsBindingSource = value;
            }
        }

        /// <summary>
        /// ScreensPresetDetails table adapter property
        /// </summary>
        public ScreensPresetDetailsTableAdapter screensPresetDetailsTableAdapter
        {
            get
            {
                if (_screensPresetDetailsTableAdapter == null)
                {
                    _screensPresetDetailsTableAdapter = new ScreensPresetDetailsTableAdapter(connectionString);
                    _screensPresetDetailsTableAdapter.Fill(dataSet.ScreensPresetDetails);

                    tableAdapterManager.ScreensPresetDetailsTableAdapter = _screensPresetDetailsTableAdapter;
                }

                return _screensPresetDetailsTableAdapter;
            }
            set
            {
                _screensPresetDetailsTableAdapter = value;
            }
        }

        /// <summary>
        /// ScreensPresetDetails binding source property
        /// </summary>
        public BindingSource screensPresetDetailsBindingSource
        {
            get
            {
                if (_screensPresetDetailsBindingSource == null)
                {
                    screensPresetDetailsTableAdapter.ClearBeforeFill = true;

                    _screensPresetDetailsBindingSource = new BindingSource();
                    _screensPresetDetailsBindingSource.DataMember = "ScreensPresetDetails";
                    _screensPresetDetailsBindingSource.DataSource = dataSet;
                }

                return _screensPresetDetailsBindingSource;
            }
            set
            {
                _screensPresetDetailsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between tables ScreenPresetDetails and Preset
        /// </summary>
        public BindingSource fkScreensPresetDetailsPresetBindingSource
        {
            get
            {
                if (_fkScreensPresetDetailsPresetBindingSource == null)
                {
                    screensPresetDetailsTableAdapter.ClearBeforeFill = true;

                    _fkScreensPresetDetailsPresetBindingSource = new BindingSource();
                    _fkScreensPresetDetailsPresetBindingSource.DataMember = "FK_ScreenPresetDetails_Preset";
                    _fkScreensPresetDetailsPresetBindingSource.DataSource = presetBindingSource;
                }

                return _fkScreensPresetDetailsPresetBindingSource;
            }
            set
            {
                _fkScreensPresetDetailsPresetBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between tables ScreenPresetDetails and PresetDetails
        /// </summary>
        public BindingSource fkPresetDetailsScreensPresetDetailsBindingSource
        {
            get
            {
                if (_fkPresetDetailsScreensPresetDetailsBindingSource == null)
                {
                    presetDetailsTableAdapter.ClearBeforeFill = true;

                    _fkPresetDetailsScreensPresetDetailsBindingSource = new BindingSource();
                    _fkPresetDetailsScreensPresetDetailsBindingSource.DataMember = "FK_ScreensPresetDetails_PresetDetails";
                    _fkPresetDetailsScreensPresetDetailsBindingSource.DataSource = fkScreensPresetDetailsPresetBindingSource;
                }

                return _fkPresetDetailsScreensPresetDetailsBindingSource;
            }
            set
            {
                _fkPresetDetailsScreensPresetDetailsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between tables Screens and ScreenObjects. Created for PresetDetails table.
        /// </summary>
        public BindingSource fkPresetDetailsScreensScreenObjectsBindingSource
        {
            get
            {
                if (_fkPresetDetailsScreensScreenObjectsBindingSource == null)
                {
                    screenObjectsTableAdapter.ClearBeforeFill = true;

                    _fkPresetDetailsScreensScreenObjectsBindingSource = new BindingSource();
                    _fkPresetDetailsScreensScreenObjectsBindingSource.DataMember = "FK_Screens_ScreenObjects";
                    _fkPresetDetailsScreensScreenObjectsBindingSource.DataSource = presetDetailsScreensBindingSource;
                }

                return _fkPresetDetailsScreensScreenObjectsBindingSource;
            }
            set
            {
                _fkPresetDetailsScreensScreenObjectsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between Presets and Preset details
        /// </summary>
        public BindingSource fkPresetDetailsPresetBindingSource
        {
            get
            {
                if (_fkPresetDetailsPresetBindingSource == null)
                {
                    presetDetailsTableAdapter.ClearBeforeFill = true;

                    _fkPresetDetailsPresetBindingSource = new BindingSource();
                    _fkPresetDetailsPresetBindingSource.DataMember = "FK_PresetDetails_Preset";
                    _fkPresetDetailsPresetBindingSource.DataSource = presetBindingSource;
                }

                return _fkPresetDetailsPresetBindingSource;
            }
            set
            {
                _fkPresetDetailsPresetBindingSource = value;
            }
        }

        /// <summary>
        /// Screens binding source for table PresetDetails
        /// </summary>
        public BindingSource presetDetailsScreensBindingSource
        {
            get
            {
                if (_presetDetailsScreensBindingSource == null)
                {
                    screensTableAdapter.ClearBeforeFill = true;

                    _presetDetailsScreensBindingSource = new BindingSource();
                    _presetDetailsScreensBindingSource.DataMember = "Screens";
                    _presetDetailsScreensBindingSource.DataSource = dataSet;
                }

                return _presetDetailsScreensBindingSource;
            }
            set
            {
                _presetDetailsScreensBindingSource = value;
            }
        }

        /// <summary>
        /// PresetHookupTableAdapter table adapter property
        /// </summary>
        public PresetHookupTableAdapter presetHookupTableAdapter
        {
            get
            {
                if (_presetHookupTableAdapter == null)
                {
                    _presetHookupTableAdapter = new PresetHookupTableAdapter(connectionString);
                    _presetHookupTableAdapter.Fill(dataSet.PresetHookup);

                    tableAdapterManager.PresetHookupTableAdapter = _presetHookupTableAdapter;
                }

                return _presetHookupTableAdapter;
            }
            set
            {
                _presetHookupTableAdapter = value;
            }
        }

        /// <summary>
        /// Preset hookup binding source property
        /// </summary>
        public BindingSource presetHookupBindingSource
        {
            get
            {
                if (_presetHookupBindingSource == null)
                {
                    presetHookupTableAdapter.ClearBeforeFill = true;

                    _presetHookupBindingSource = new BindingSource();
                    _presetHookupBindingSource.DataMember = "PresetHookup";
                    _presetHookupBindingSource.DataSource = dataSet;
                }

                return _presetHookupBindingSource;
            }
            set
            {
                _presetHookupBindingSource = value;
            }
        }

        /// <summary>
        /// Presets binding source for table PresetHookup
        /// </summary>
        public BindingSource presetHookupPresetsBindingSource
        {
            get
            {
                if (_presetHokupPresetsBindingSource == null)
                {
                    presetTableAdapter.ClearBeforeFill = true;

                    _presetHokupPresetsBindingSource = new BindingSource();
                    _presetHokupPresetsBindingSource.DataMember = "Preset";
                    _presetHokupPresetsBindingSource.DataSource = dataSet;
                }

                return _presetHokupPresetsBindingSource;
            }
            set
            {
                _presetHokupPresetsBindingSource = value;
            }
        }

        /// <summary>
        /// Users binding source for table PresetHookup
        /// </summary>
        public BindingSource presetHookupUsersBindingSource
        {
            get
            {
                if (_presetHokupUsersBindingSource == null)
                {
                    usersTableAdapter.ClearBeforeFill = true;

                    _presetHokupUsersBindingSource = new BindingSource();
                    _presetHokupUsersBindingSource.DataMember = "Users";
                    _presetHokupUsersBindingSource.DataSource = dataSet;
                }

                return _presetHokupUsersBindingSource;
            }
            set
            {
                _presetHokupUsersBindingSource = value;
            }       
        }

        /// <summary>
        /// User groups binding source for table PresetHookup
        /// </summary>
        public BindingSource presetHookupUserGroupsBindingSource
        {
            get
            {
                if (_presetHookupUserGroupsBindingSource == null)
                {
                    userGroupsTableAdapter.ClearBeforeFill = true;

                    _presetHookupUserGroupsBindingSource = new BindingSource();
                    _presetHookupUserGroupsBindingSource.DataMember = "UserGroups";
                    _presetHookupUserGroupsBindingSource.DataSource = dataSet;
                }

                return _presetHookupUserGroupsBindingSource;
            }
            set
            {
                _presetHookupUserGroupsBindingSource = value;
            }
        }

        /// <summary>
        /// Computers binding source for table PresetHookup
        /// </summary>
        public BindingSource presetHookupComputersBindingSource
        {
            get
            {
                if (_presetHokupComputersBindingSource == null)
                {
                    computersTableAdapter.ClearBeforeFill = true;

                    _presetHokupComputersBindingSource = new BindingSource();
                    _presetHokupComputersBindingSource.DataMember = "Computers";
                    _presetHokupComputersBindingSource.DataSource = dataSet;
                }

                return _presetHokupComputersBindingSource;
            }
            set
            {
                _presetHokupComputersBindingSource = value;
            }       
        }

        /// <summary>
        /// OSTypes binding source for table PresetHookup
        /// </summary>
        public BindingSource presetHookupOSTypesBindingSource
        {
            get
            {
                if (_presetHokupOSTypesBindingSource == null)
                {
                    osTypesTableAdapter.ClearBeforeFill = true;

                    _presetHokupOSTypesBindingSource = new BindingSource();
                    _presetHokupOSTypesBindingSource.DataMember = "OSTypes";
                    _presetHokupOSTypesBindingSource.DataSource = dataSet;
                }

                return _presetHokupOSTypesBindingSource;
            }
            set
            {
                _presetHokupOSTypesBindingSource = value;
            }       
        }

        /// <summary>
        /// Binding source for relation between tables PresetHookup and Preset
        /// </summary>
        public BindingSource fkPresetHookupPresetBindingSource
        {
            get
            {
                if (_fkPresetHookupPresetBindingSource == null)
                {
                    presetHookupTableAdapter.ClearBeforeFill = true;

                    _fkPresetHookupPresetBindingSource = new BindingSource();
                    _fkPresetHookupPresetBindingSource.DataMember = "FK_PresetHookup_Preset";
                    _fkPresetHookupPresetBindingSource.DataSource = presetHookupPresetsBindingSource;
                }

                return _fkPresetHookupPresetBindingSource;
            }
            set
            {
                _fkPresetHookupPresetBindingSource = value;
            }
        }

        #endregion

        #region Screen objects

        /// <summary>
        /// Screen objects table adapter property
        /// </summary>
        public ScreenObjectScopesTableAdapter screenObjectScopesTableAdapter
        {
            get
            {
                if (_screenObjectScopesTableAdapter == null)
                {
                    _screenObjectScopesTableAdapter = new ScreenObjectScopesTableAdapter(connectionString);
                    _screenObjectScopesTableAdapter.Fill(dataSet.ScreenObjectScopes);

                    tableAdapterManager.ScreenObjectScopesTableAdapter = _screenObjectScopesTableAdapter;
                }

                return _screenObjectScopesTableAdapter;
            }
            set
            {
                _screenObjectScopesTableAdapter = value;
            }
        }

        /// <summary>
        /// Screen object scopes binding source for table PresetDetaisScreens
        /// </summary>
        public BindingSource screenObjectScopesScreensBindingSource
        {
            get
            {
                if (_screenObjectScopesScreensBindingSource == null)
                {
                    screenObjectScopesTableAdapter.ClearBeforeFill = true;

                    _screenObjectScopesScreensBindingSource = new BindingSource();
                    _screenObjectScopesScreensBindingSource.DataMember = "ScreenObjectScopes";
                    _screenObjectScopesScreensBindingSource.DataSource = dataSet;
                }

                return _screenObjectScopesScreensBindingSource;
            }
            set
            {
                _screenObjectScopesScreensBindingSource = value;
            }
        }

        /// <summary>
        /// Screen object scopes binding source for table PresetDetails
        /// </summary>
        public BindingSource screenObjectScopesScreenObjectsBindingSource
        {
            get
            {
                if (_screenObjectScopesScreenObjectsBindingSource == null)
                {
                    screenObjectScopesTableAdapter.ClearBeforeFill = true;

                    _screenObjectScopesScreenObjectsBindingSource = new BindingSource();
                    _screenObjectScopesScreenObjectsBindingSource.DataMember = "ScreenObjectScopes";
                    _screenObjectScopesScreenObjectsBindingSource.DataSource = dataSet;
                }

                return _screenObjectScopesScreenObjectsBindingSource;
            }
            set
            {
                _screenObjectScopesScreenObjectsBindingSource = value;
            }
        }

        /// <summary>
        /// Screen objects table adapter property
        /// </summary>
        public ScreenObjectsTableAdapter screenObjectsTableAdapter
        {
            get
            {
                if (_screenObjectsTableAdapter == null)
                {
                    _screenObjectsTableAdapter = new ScreenObjectsTableAdapter(connectionString);
                    _screenObjectsTableAdapter.Fill(dataSet.ScreenObjects);

                    tableAdapterManager.ScreenObjectsTableAdapter = _screenObjectsTableAdapter;
                }

                return _screenObjectsTableAdapter;
            }
            set
            {
                _screenObjectsTableAdapter = value;
            }
        }

        /// <summary>
        /// Screen objects binding source property
        /// </summary>
        public BindingSource screenObjectsBindingSource
        {
            get
            {
                if (_screenObjectsBindingSource == null)
                {
                    screenObjectsTableAdapter.ClearBeforeFill = true;

                    _screenObjectsBindingSource = new BindingSource();
                    _screenObjectsBindingSource.DataMember = "ScreenObjects";
                    _screenObjectsBindingSource.DataSource = dataSet;
                }

                return _screenObjectsBindingSource;
            }
            set
            {
                _screenObjectsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between tables ScreenObjects and ScreenObjects
        /// </summary>
        public BindingSource fkScreenObjectsScreenObjectsBindingSource
        {
            get
            {
                if (_fkScreenObjectsScreenObjectsBindingSource == null)
                {
                    screenObjectsTableAdapter.ClearBeforeFill = true;

                    _fkScreenObjectsScreenObjectsBindingSource = new BindingSource();
                    _fkScreenObjectsScreenObjectsBindingSource.DataMember = "FK_ScreenObjects_ScreenObjects";
                    _fkScreenObjectsScreenObjectsBindingSource.DataSource = screenObjectsBindingSource;
                }

                return _fkScreenObjectsScreenObjectsBindingSource;
            }
            set
            {
                _fkScreenObjectsScreenObjectsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between tables Screens and ScreenObjects
        /// </summary>
        public BindingSource fkScreensScreenObjectsBindingSource
        {
             get
            {
                if (_fkScreensScreenObjectsBindingSource == null)
                {
                    screenObjectsTableAdapter.ClearBeforeFill = true;

                    _fkScreensScreenObjectsBindingSource = new BindingSource();
                    _fkScreensScreenObjectsBindingSource.DataMember = "FK_Screens_ScreenObjects";
                    _fkScreensScreenObjectsBindingSource.DataSource = screensBindingSource;
                }

                return _fkScreensScreenObjectsBindingSource;
            }
            set
            {
                _fkScreensScreenObjectsBindingSource = value;
            }
        }

        /// <summary>
        /// Screens table adapter property
        /// </summary>
        public ScreensTableAdapter screensTableAdapter
        {
            get
            {
                if (_screensTableAdapter == null)
                {
                    _screensTableAdapter = new ScreensTableAdapter(connectionString);
                    _screensTableAdapter.Fill(dataSet.Screens);

                    tableAdapterManager.ScreensTableAdapter = _screensTableAdapter;
                }

                return _screensTableAdapter;
            }
            set
            {
                _screensTableAdapter = value;
            }
        }

        /// <summary>
        /// Screens binding source property
        /// </summary>
        public BindingSource screensBindingSource
        {
            get
            {
                if (_screensBindingSource == null)
                {
                    screensTableAdapter.ClearBeforeFill = true;

                    _screensBindingSource = new BindingSource();
                    _screensBindingSource.DataMember = "Screens";
                    _screensBindingSource.DataSource = dataSet;
                }

                return _screensBindingSource;
            }
            set
            {
                _screensBindingSource = value;
            }
        }

        /// <summary>
        /// Screen objects types table adapter property
        /// </summary>
        public ScreenObjectTypesTableAdapter screenObjectsTypesTableAdapter
        {
            get
            {
                if (_screenObjectsTypesTableAdapter == null)
                {
                    _screenObjectsTypesTableAdapter = new ScreenObjectTypesTableAdapter(connectionString);
                    _screenObjectsTypesTableAdapter.Fill(dataSet.ScreenObjectTypes);

                    tableAdapterManager.ScreenObjectTypesTableAdapter = _screenObjectsTypesTableAdapter;
                }

                return _screenObjectsTypesTableAdapter;
            }
            set
            {
                _screenObjectsTypesTableAdapter = value;
            }
        }

        /// <summary>
        /// Screen objects types binding source property
        /// </summary>
        public BindingSource screenObjectsTypesBindingSource
        {
            get
            {
                if (_screenObjectsTypesBindingSource == null)
                {
                    screenObjectsTypesTableAdapter.ClearBeforeFill = true;

                    _screenObjectsTypesBindingSource = new BindingSource();
                    _screenObjectsTypesBindingSource.DataMember = "ScreenObjectTypes";
                    _screenObjectsTypesBindingSource.DataSource = dataSet;
                }

                return _screenObjectsTypesBindingSource;
            }
            set
            {
                _screenObjectsTypesBindingSource = value;
            }
        }

        /// <summary>
        /// Screen types table adapter property
        /// </summary>
        public ScreenTypesTableAdapter screenTypesTableAdapter
        {
            get
            {
                if (_screenTypesTableAdapter == null)
                {
                    _screenTypesTableAdapter = new ScreenTypesTableAdapter(connectionString);
                    _screenTypesTableAdapter.Fill(dataSet.ScreenTypes);

                    tableAdapterManager.ScreenTypesTableAdapter = _screenTypesTableAdapter;
                }

                return _screenTypesTableAdapter;
            }
            set
            {
                _screenTypesTableAdapter = value;
            }
        }

        /// <summary>
        /// Screen types binding source property
        /// </summary>
        public BindingSource screenTypesBindingSource
        {
            get
            {
                if (_screenTypesBindingSource == null)
                {
                    screenTypesTableAdapter.ClearBeforeFill = true;

                    _screenTypesBindingSource = new BindingSource();
                    _screenTypesBindingSource.DataMember = "ScreenTypes";
                    _screenTypesBindingSource.DataSource = dataSet;
                }

                return _screenTypesBindingSource;
            }
            set
            {
                _screenTypesBindingSource = value;
            }
        }

        /// <summary>
        /// Screen object list values table adapter property
        /// </summary>
        public ScreenObjectListValuesTableAdapter screenObjectListValuesTableAdapter
        {
            get
            {
                if (_screenObjectListValuesTableAdapter == null)
                {
                    _screenObjectListValuesTableAdapter = new ScreenObjectListValuesTableAdapter(connectionString);
                    _screenObjectListValuesTableAdapter.Fill(dataSet.ScreenObjectListValues);

                    tableAdapterManager.ScreenObjectListValuesTableAdapter = _screenObjectListValuesTableAdapter;
                }

                return _screenObjectListValuesTableAdapter;
            }
            set
            {
                _screenObjectListValuesTableAdapter = value;
            }
        }

        /// <summary>
        /// Screen objects list values binding source property
        /// </summary>
        public BindingSource screenObjectListValuesBindingSource
        {
            get
            {
                if (_screenObjectListValuesBindingSource == null)
                {
                    screenObjectListValuesTableAdapter.ClearBeforeFill = true;

                    _screenObjectListValuesBindingSource = new BindingSource();
                    _screenObjectListValuesBindingSource.DataMember = "ScreenObjectListValues";
                    _screenObjectListValuesBindingSource.DataSource = dataSet;
                }

                return _screenObjectListValuesBindingSource;
            }
            set
            {
                _screenObjectListValuesBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between screen objects list values and screen objects
        /// </summary>
        public BindingSource fkScreenObjectListValuesScreenObjectsBindingSource
        {
            get
            {
                if (_fkScreenObjectListValuesScreenObjectsBindingSource == null)
                {
                    screenObjectListValuesTableAdapter.ClearBeforeFill = true;

                    _fkScreenObjectListValuesScreenObjectsBindingSource = new BindingSource();
                    _fkScreenObjectListValuesScreenObjectsBindingSource.DataMember = "FK_ScreenObjectListValues_ScreenObjects";
                    _fkScreenObjectListValuesScreenObjectsBindingSource.DataSource = fkScreensScreenObjectsBindingSource;
                }

                return _fkScreenObjectListValuesScreenObjectsBindingSource;
            }
            set
            {
                _fkScreenObjectListValuesScreenObjectsBindingSource = value;
            }
        }
              
        #endregion

        #region User check values 

        /// <summary>
        /// User check values table adapetr property
        /// </summary>
        public UserCheckValuesTableAdapter userCheckValuesTableAdapter
        {
            get
            {
                if (_userCheckValuesTableAdapter == null)
                {
                    _userCheckValuesTableAdapter = new UserCheckValuesTableAdapter(connectionString);
                    _userCheckValuesTableAdapter.Fill(dataSet.UserCheckValues);

                    tableAdapterManager.UserCheckValuesTableAdapter = _userCheckValuesTableAdapter;
                }

                return _userCheckValuesTableAdapter;
            }
            set
            {
                _userCheckValuesTableAdapter = value;
            }
        }

        /// <summary>
        /// User check values binding source property
        /// </summary>
        public BindingSource userCheckValuesBindingSource
        {
            get
            {
                if (_userCheckValuesBindingSource == null)
                {
                    userCheckValuesTableAdapter.ClearBeforeFill = true;

                    _userCheckValuesBindingSource = new BindingSource();
                    _userCheckValuesBindingSource.DataMember = "UserCheckValues";
                    _userCheckValuesBindingSource.DataSource = dataSet;
                }

                return _userCheckValuesBindingSource;
            }
            set
            {
                _userCheckValuesBindingSource = value;
            }
        }

        /// <summary>
        /// User check values screen objects table adapter property
        /// </summary>
        public UserCheckValuesScreenObjectsTableAdapter userCheckValuesScreenObjectsTableAdapter
        {
            get
            {
                if (_userCheckValuesScreenObjectsTableAdapter == null)
                {
                    _userCheckValuesScreenObjectsTableAdapter = new UserCheckValuesScreenObjectsTableAdapter(connectionString);
                    _userCheckValuesScreenObjectsTableAdapter.Fill(dataSet.UserCheckValuesScreenObjects);

                    tableAdapterManager.UserCheckValuesScreenObjectsTableAdapter = _userCheckValuesScreenObjectsTableAdapter;
                }

                return _userCheckValuesScreenObjectsTableAdapter;
            }
            set
            {
                _userCheckValuesScreenObjectsTableAdapter = value;
            }
        }

        /// <summary>
        /// User check values screen objects binding source property
        /// </summary>
        public BindingSource userCheckValuesScreenObjectsBindingSource
        {
            get
            {
                if (_userCheckValuesScreenObjectsBindingSource == null)
                {
                    userCheckValuesScreenObjectsTableAdapter.ClearBeforeFill = true;

                    _userCheckValuesScreenObjectsBindingSource = new BindingSource();
                    _userCheckValuesScreenObjectsBindingSource.DataMember = "UserCheckValuesScreenObjects";
                    _userCheckValuesScreenObjectsBindingSource.DataSource = dataSet;
                }

                return _userCheckValuesScreenObjectsBindingSource;
            }
            set
            {
                _userCheckValuesScreenObjectsBindingSource = value;
            }
        }

        #endregion

        #region Password

        /// <summary>
        /// Password construction rules table adaper property
        /// </summary>
        public PasswordConstructionRulesTableAdapter passwordConstructionRulesTableAdapter
        {
            get
            {
                if (_passwordConstructionRulesTableAdapter == null)
                {
                    _passwordConstructionRulesTableAdapter = new PasswordConstructionRulesTableAdapter(connectionString);
                    _passwordConstructionRulesTableAdapter.Fill(dataSet.PasswordConstructionRules);

                    tableAdapterManager.PasswordConstructionRulesTableAdapter = _passwordConstructionRulesTableAdapter;
                }

                return _passwordConstructionRulesTableAdapter;
            }
            set
            {
                _passwordConstructionRulesTableAdapter = value;
            }
        }

        /// <summary>
        /// Password construction rules binding source property
        /// </summary>
        public BindingSource passwordConstructionRulesBindingSource
        {
            get
            {
                if (_passwordConstructionRulesBindingSource == null)
                {
                    passwordConstructionRulesTableAdapter.ClearBeforeFill = true;

                    _passwordConstructionRulesBindingSource = new BindingSource();
                    _passwordConstructionRulesBindingSource.DataMember = "PasswordConstructionRules";
                    _passwordConstructionRulesBindingSource.DataSource = dataSet;
                }

                return _passwordConstructionRulesBindingSource;
            }
            set
            {
                _passwordConstructionRulesBindingSource = value;
            }
        }

        /// <summary>
        /// Password construction rules types table adapter property
        /// </summary>
        public PasswordConstructionRulesTypesTableAdapter passwordConstructionRulesTypesTableAdapter
        {
            get
            {
                if (_passwordConstructionRulesTypesTableAdapter == null)
                {
                    _passwordConstructionRulesTypesTableAdapter = new PasswordConstructionRulesTypesTableAdapter(connectionString);
                    _passwordConstructionRulesTypesTableAdapter.Fill(dataSet.PasswordConstructionRulesTypes);

                    tableAdapterManager.PasswordConstructionRulesTypesTableAdapter = _passwordConstructionRulesTypesTableAdapter;
                }

                return _passwordConstructionRulesTypesTableAdapter;
            }
            set
            {
                _passwordConstructionRulesTypesTableAdapter = value;
            }
        }

        /// <summary>
        /// Password construction rules types binding source property
        /// </summary>
        public BindingSource passwordConstructionRulesTypesBindingSource
        {
            get
            {
                if (_passwordConstructionRulesTypesBindingSource == null)
                {
                    passwordConstructionRulesTypesTableAdapter.ClearBeforeFill = true;

                    _passwordConstructionRulesTypesBindingSource = new BindingSource();
                    _passwordConstructionRulesTypesBindingSource.DataMember = "PasswordConstructionRulesTypes";
                    _passwordConstructionRulesTypesBindingSource.DataSource = dataSet;
                }

                return _passwordConstructionRulesTypesBindingSource;
            }
            set
            {
                _passwordConstructionRulesTypesBindingSource = value;
            }
        }


        /// <summary>
        /// User password construction rules table adapter property
        /// </summary>
        public UserPasswordConstructionRulesTableAdapter userPasswordConstructionRulesTableAdapter
        {
            get
            {
                if (_userPasswordConstructionRulesTableAdapter == null)
                {
                    _userPasswordConstructionRulesTableAdapter = new UserPasswordConstructionRulesTableAdapter(connectionString);
                    _userPasswordConstructionRulesTableAdapter.Fill(dataSet.UserPasswordConstructionRules);

                    tableAdapterManager.UserPasswordConstructionRulesTableAdapter = _userPasswordConstructionRulesTableAdapter;
                }

                return _userPasswordConstructionRulesTableAdapter;
            }
            set
            {
                _userPasswordConstructionRulesTableAdapter = value;
            }
        }

        /// <summary>
        /// User password construction rules binding source property
        /// </summary>
        public BindingSource userPasswordConstructionRulesBindingSource
        {
            get
            {
                if (_userPasswordConstructionRulesBindingSource == null)
                {
                    userPasswordConstructionRulesTableAdapter.ClearBeforeFill = true;

                    _userPasswordConstructionRulesBindingSource = new BindingSource();
                    _userPasswordConstructionRulesBindingSource.DataMember = "UserPasswordConstructionRules";
                    _userPasswordConstructionRulesBindingSource.DataSource = dataSet;
                }

                return _userPasswordConstructionRulesBindingSource;
            }
            set
            {
                _userPasswordConstructionRulesBindingSource = value;
            }
        }
                
        /// <summary>
        /// User temp password construction rules table adapter property
        /// </summary>
        public TmpUserPasswordConstructionRulesTableAdapter tmpUserPasswordConstructionRulesTableAdapter
        {
            get
            {
                if (_tmpUserPasswordConstructionRulesTableAdapter == null)
                {
                    _tmpUserPasswordConstructionRulesTableAdapter = new TmpUserPasswordConstructionRulesTableAdapter(connectionString);
                    _tmpUserPasswordConstructionRulesTableAdapter.Fill(dataSet.TmpUserPasswordConstructionRules);

                    tableAdapterManager.TmpUserPasswordConstructionRulesTableAdapter = _tmpUserPasswordConstructionRulesTableAdapter;
                }

                return _tmpUserPasswordConstructionRulesTableAdapter;
            }
            set
            {
                _tmpUserPasswordConstructionRulesTableAdapter = value;
            }
        }

        /// <summary>
        /// User temp password construction rules binding source property
        /// </summary>
        public BindingSource tmpUserPasswordConstructionRulesBindingSource
        {
            get
            {
                if (_tmpUserPasswordConstructionRulesBindingSource == null)
                {
                    tmpUserPasswordConstructionRulesTableAdapter.ClearBeforeFill = true;

                    _tmpUserPasswordConstructionRulesBindingSource = new BindingSource();
                    _tmpUserPasswordConstructionRulesBindingSource.DataMember = "TmpUserPasswordConstructionRules";
                    _tmpUserPasswordConstructionRulesBindingSource.DataSource = dataSet;
                }

                return _tmpUserPasswordConstructionRulesBindingSource;
            }
            set
            {
                _tmpUserPasswordConstructionRulesBindingSource = value;
            }
        }

        #endregion

        #region Education

        /// <summary>
        /// Education lessons table adapetr property 
        /// </summary>
        public EducationLessonsTableAdapter educationLessonsTableAdapter
        {
            get
            {
                if (_educationLessonsTableAdapter == null)
                {
                    _educationLessonsTableAdapter = new EducationLessonsTableAdapter(connectionString);
                    _educationLessonsTableAdapter.Fill(dataSet.EducationLessons);

                    tableAdapterManager.EducationLessonsTableAdapter = _educationLessonsTableAdapter;
                }

                return _educationLessonsTableAdapter;
            }
            set
            {
                _educationLessonsTableAdapter = value;
            }
        }

        /// <summary>
        /// Education lessons binding source property 
        /// </summary>
        public BindingSource educationLessonsBindingSource
        {
            get
            {
                if (_educationLessonsBindingSource == null)
                {
                    educationLessonsTableAdapter.ClearBeforeFill = true;

                    _educationLessonsBindingSource = new BindingSource();
                    _educationLessonsBindingSource.DataMember = "EducationLessons";
                    _educationLessonsBindingSource.DataSource = dataSet;
                }

                return _educationLessonsBindingSource;
            }
            set
            {
                _educationLessonsBindingSource = value;
            }
        }
                
        /// <summary>
        /// Binding source for relation between edication lessons and education categories
        /// </summary>
        public BindingSource fkEducationLessonsEducationCategoriesBindingSource
        {
            get
            {
                if (_fkEducationLessonsEducationCategoriesBindingSource == null)
                {
                    educationLessonsTableAdapter.ClearBeforeFill = true;

                    _fkEducationLessonsEducationCategoriesBindingSource = new BindingSource();
                    _fkEducationLessonsEducationCategoriesBindingSource.DataMember = "FK_EducationLessons_EducationCatgories";
                    _fkEducationLessonsEducationCategoriesBindingSource.DataSource = educationCategoriesBindingSource;
                }

                return _fkEducationLessonsEducationCategoriesBindingSource;
            }
            set
            {
                _fkEducationLessonsEducationCategoriesBindingSource = value;
            }
        }

        /// <summary>
        /// Education categories table adapter property
        /// </summary>
        public EducationCategoriesTableAdapter educationCategoriesTableAdapter
        {
            get
            {
                if (_educationCategoriesTableAdapter == null)
                {
                    _educationCategoriesTableAdapter = new EducationCategoriesTableAdapter(connectionString);
                    _educationCategoriesTableAdapter.Fill(dataSet.EducationCategories);

                    tableAdapterManager.EducationCategoriesTableAdapter = _educationCategoriesTableAdapter;
                }

                return _educationCategoriesTableAdapter;
            }
            set
            {
                _educationCategoriesTableAdapter = value;
            }
        }

        /// <summary>
        /// Education categories binding source property
        /// </summary>
        public BindingSource educationCategoriesBindingSource
        {
            get
            {
                if (_educationCategoriesBindingSource == null)
                {
                    educationCategoriesTableAdapter.ClearBeforeFill = true;

                    _educationCategoriesBindingSource = new BindingSource();
                    _educationCategoriesBindingSource.DataMember = "EducationCategories";
                    _educationCategoriesBindingSource.DataSource = dataSet;
                }

                return _educationCategoriesBindingSource;
            }
            set
            {
                _educationCategoriesBindingSource = value;
            }
        }

        /// <summary>
        /// Education answers table adapetr property
        /// </summary>
        public EducationAnswersTableAdapter educationAnswersTableAdapter
        {
            get
            {
                if (_educationAnswersTableAdapter == null)
                {
                    _educationAnswersTableAdapter = new EducationAnswersTableAdapter(connectionString);
                    _educationAnswersTableAdapter.Fill(dataSet.EducationAnswers);

                    tableAdapterManager.EducationAnswersTableAdapter = _educationAnswersTableAdapter;
                }

                return _educationAnswersTableAdapter;
            }
            set
            {
                _educationAnswersTableAdapter = value;
            }
        }

        /// <summary>
        /// Education answers binding source property
        /// </summary>
        public BindingSource educationAnswersBindingSource
        {
            get
            {
                if (_educationAnswersBindingSource == null)
                {
                    educationAnswersTableAdapter.ClearBeforeFill = true;

                    _educationAnswersBindingSource = new BindingSource();
                    _educationAnswersBindingSource.DataMember = "EducationAnswers";
                    _educationAnswersBindingSource.DataSource = dataSet;
                }

                return _educationAnswersBindingSource;
            }
            set
            {
                _educationAnswersBindingSource = value;
            }
        }

        /// <summary>
        /// Education questions table adapter property
        /// </summary>
        public EducationQuestionsTableAdapter educationQuestionsTableAdapter
        {
            get
            {
                if (_educationQuestionsTableAdapter == null)
                {
                    _educationQuestionsTableAdapter = new EducationQuestionsTableAdapter(connectionString);
                    _educationQuestionsTableAdapter.Fill(dataSet.EducationQuestions);

                    tableAdapterManager.EducationQuestionsTableAdapter = _educationQuestionsTableAdapter;
                }

                return _educationQuestionsTableAdapter;
            }
            set
            {
                _educationQuestionsTableAdapter = value;
            }
        }

        /// <summary>
        /// Education questions binding source property
        /// </summary>
        public BindingSource educationQuestionsBindingSource
        {
            get
            {
                if (_educationQuestionsBindingSource == null)
                {
                    educationQuestionsTableAdapter.ClearBeforeFill = true;

                    _educationQuestionsBindingSource = new BindingSource();
                    _educationQuestionsBindingSource.DataMember = "EducationQuestions";
                    _educationQuestionsBindingSource.DataSource = dataSet;
                }

                return _educationQuestionsBindingSource;
            }
            set
            {
                _educationQuestionsBindingSource = value;
            }
        }

        /// <summary>
        /// Right answer binding source
        /// </summary>
        public BindingSource rightQuestionAnswerBindingSource
        {
            get
            {
                if (_rightQuestionAnswerBindingSource == null)
                {
                    educationAnswersTableAdapter.ClearBeforeFill = true;

                    _rightQuestionAnswerBindingSource = new BindingSource();
                    _rightQuestionAnswerBindingSource.DataMember = "EducationAnswers";
                    _rightQuestionAnswerBindingSource.DataSource = dataSet;
                }

                return _rightQuestionAnswerBindingSource;
            }
            set
            {
                _rightQuestionAnswerBindingSource = value;
            }
        }

        /// <summary>
        /// Question answers list binding source
        /// </summary>
        public BindingSource questionAnswerBindingSource
        {
            get
            {
                if (_questionAnswerBindingSource == null)
                {
                    educationAnswersTableAdapter.ClearBeforeFill = true;

                    _questionAnswerBindingSource = new BindingSource();
                    _questionAnswerBindingSource.DataMember = "EducationAnswers";
                    _questionAnswerBindingSource.DataSource = dataSet;
                }

                return _questionAnswerBindingSource;
            }
            set
            {
                _questionAnswerBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between education questions and education lessons
        /// </summary>
        public BindingSource fkEducationQuestionsEducationLessonsBindingSource
        {
            get
            {
                if (_fkEducationQuestionsEducationLessonsBindingSource == null)
                {
                    educationQuestionsTableAdapter.ClearBeforeFill = true;

                    _fkEducationQuestionsEducationLessonsBindingSource = new BindingSource();
                    _fkEducationQuestionsEducationLessonsBindingSource.DataMember = "FK_EducationQuestions_EducationLessons";
                    _fkEducationQuestionsEducationLessonsBindingSource.DataSource = fkEducationLessonsEducationCategoriesBindingSource;
                }

                return _fkEducationQuestionsEducationLessonsBindingSource;
            }
            set
            {
                _fkEducationQuestionsEducationLessonsBindingSource = value;
            }
        
        }

        /// <summary>
        /// Education question answers table adapter property
        /// </summary>
        public EducationQuestionAnswersTableAdapter educationQuestionAnswersTableAdapter
        {
            get
            {
                if (_educationQuestionAnswersTableAdapter == null)
                {
                    _educationQuestionAnswersTableAdapter = new EducationQuestionAnswersTableAdapter(connectionString);
                    _educationQuestionAnswersTableAdapter.Fill(dataSet.EducationQuestionAnswers);

                    tableAdapterManager.EducationQuestionAnswersTableAdapter = _educationQuestionAnswersTableAdapter;
                }

                return _educationQuestionAnswersTableAdapter;
            }
            set
            {
                _educationQuestionAnswersTableAdapter = value;
            }
        }

        /// <summary>
        /// Education question answers binding source property
        /// </summary>
        public BindingSource educationQuestionAnswersBindingSource
        {
            get
            {
                if (_educationQuestionAnswersBindingSource == null)
                {
                    educationQuestionAnswersTableAdapter.ClearBeforeFill = true;

                    _educationQuestionAnswersBindingSource = new BindingSource();
                    _educationQuestionAnswersBindingSource.DataMember = "EducationQuestionAnswers";
                    _educationQuestionAnswersBindingSource.DataSource = dataSet;
                }

                return _educationQuestionAnswersBindingSource;
            }
            set
            {
                _educationQuestionAnswersBindingSource = value;
            }
        }


        public BindingSource fkEducationQuestionAnswersEducationQuestionsBindingSource
        {
            get
            {
                if (_fkEducationQuestionAnswersEducationQuestionsBindingSource == null)
                {
                    educationQuestionAnswersTableAdapter.ClearBeforeFill = true;

                    _fkEducationQuestionAnswersEducationQuestionsBindingSource = new BindingSource();
                    _fkEducationQuestionAnswersEducationQuestionsBindingSource.DataMember = "FK_EducationQuestionAnswers_EducationQuestions";
                    _fkEducationQuestionAnswersEducationQuestionsBindingSource.DataSource = fkEducationQuestionsEducationLessonsBindingSource;
                }

                return _fkEducationQuestionAnswersEducationQuestionsBindingSource;
            }
            set
            {
                _fkEducationQuestionAnswersEducationQuestionsBindingSource = value;
            }
        }

        /// <summary>
        /// Users education table adapetr property
        /// </summary>
        public UserEducationTableAdapter userEducationTableAdapter
        {
            get
            {
                if (_userEducationTableAdapter == null)
                {
                    _userEducationTableAdapter = new UserEducationTableAdapter(connectionString);
                    _userEducationTableAdapter.Fill(dataSet.UserEducation);

                    tableAdapterManager.UserEducationTableAdapter = _userEducationTableAdapter;
                }

                return _userEducationTableAdapter;
            }
            set
            {
                _userEducationTableAdapter = value;
            }
        }

        /// <summary>
        /// Users education binding source property
        /// </summary>
        public BindingSource userEducationBindingSource
        {
            get
            {
                if (_userEducationBindingSource == null)
                {
                    userEducationTableAdapter.ClearBeforeFill = true;

                    _userEducationBindingSource = new BindingSource();
                    _userEducationBindingSource.DataMember = "UserEducation";
                    _userEducationBindingSource.DataSource = dataSet;
                }

                return _userEducationBindingSource;
            }
            set
            {
                _userEducationBindingSource = value;
            }
        }

        /// <summary>
        /// Users binding source for user education
        /// </summary>
        public BindingSource userEducationUsersBindingSource
        {
            get
            {
                if (_userEducationUsersBindingSource == null)
                {
                    usersTableAdapter.ClearBeforeFill = true;

                    _userEducationUsersBindingSource = new BindingSource();
                    _userEducationUsersBindingSource.DataMember = "Users";
                    _userEducationUsersBindingSource.DataSource = dataSet;
                }

                return _userEducationUsersBindingSource;
            }
            set
            {
                _userEducationUsersBindingSource = value;
            }
        }

        /// <summary>
        /// User groups binding source for user education
        /// </summary>
        public BindingSource userEducationUserGroupsBindingSource
        {
            get
            {
                if (_userEducationUserGroupsBindingSource == null)
                {
                    userGroupsTableAdapter.ClearBeforeFill = true;

                    _userEducationUserGroupsBindingSource = new BindingSource();
                    _userEducationUserGroupsBindingSource.DataMember = "UserGroups";
                    _userEducationUserGroupsBindingSource.DataSource = dataSet;
                }

                return _userEducationUserGroupsBindingSource;
            }
            set
            {
                _userEducationUserGroupsBindingSource = value;
            }
        }

        /// <summary>
        /// Eduacation categories binding source for user education
        /// </summary>
        public BindingSource userEducationCategoriesBindingSource
        {
            get
            {
                if (_userEducationCategoriesBindingSource == null)
                {
                    educationCategoriesTableAdapter.ClearBeforeFill = true;

                    _userEducationCategoriesBindingSource = new BindingSource();
                    _userEducationCategoriesBindingSource.DataMember = "EducationCategories";
                    _userEducationCategoriesBindingSource.DataSource = dataSet;
                }

                return _userEducationCategoriesBindingSource;
            }
            set
            {
                _userEducationCategoriesBindingSource = value;
            }
        }

        /// <summary>
        /// Eduacation categories binding source for user group education
        /// </summary>
        public BindingSource userGroupEducationCategoriesBindingSource
        {
            get
            {
                if (_userGroupEducationCategoriesBindingSource == null)
                {
                    educationCategoriesTableAdapter.ClearBeforeFill = true;

                    _userGroupEducationCategoriesBindingSource = new BindingSource();
                    _userGroupEducationCategoriesBindingSource.DataMember = "EducationCategories";
                    _userGroupEducationCategoriesBindingSource.DataSource = dataSet;
                }

                return _userGroupEducationCategoriesBindingSource;
            }
            set
            {
                _userGroupEducationCategoriesBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between User education and Users
        /// </summary>
        public BindingSource fkUserEducationUsersBindingSource
        {
             get
            {
                if (_fkUserEducationUsersBindingSource == null)
                {
                    userEducationTableAdapter.ClearBeforeFill = true;

                    _fkUserEducationUsersBindingSource = new BindingSource();
                    _fkUserEducationUsersBindingSource.DataMember = "FK_UserEducation_Users";
                    _fkUserEducationUsersBindingSource.DataSource = userEducationUsersBindingSource;
                }

                return _fkUserEducationUsersBindingSource;
            }
            set
            {
                _fkUserEducationUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Users education answers table adapter property
        /// </summary>
        public UserEducationAnswersTableAdapter userEducationAnswersTableAdapter
        {
            get
            {
                if (_userEducationAnswersTableAdapter == null)
                {
                    _userEducationAnswersTableAdapter = new UserEducationAnswersTableAdapter(connectionString);
                    _userEducationAnswersTableAdapter.Fill(dataSet.UserEducationAnswers);

                    tableAdapterManager.UserEducationAnswersTableAdapter = _userEducationAnswersTableAdapter;
                }

                return _userEducationAnswersTableAdapter;
            }
            set
            {
                _userEducationAnswersTableAdapter = value;
            }
        }

        /// <summary>
        /// Users education answers binding source property
        /// </summary>
        public BindingSource userEducationAnswersBindingSource
        {
            get
            {
                if (_userEducationAnswersBindingSource == null)
                {
                    userEducationAnswersTableAdapter.ClearBeforeFill = true;

                    _userEducationAnswersBindingSource = new BindingSource();
                    _userEducationAnswersBindingSource.DataMember = "UserEducationAnswers";
                    _userEducationAnswersBindingSource.DataSource = dataSet;
                }

                return _userEducationAnswersBindingSource;
            }
            set
            {
                _userEducationAnswersBindingSource = value;
            }
        }

        /// <summary>
        /// Questions binding source for user answers history
        /// </summary>
        public BindingSource userEducationAnswersQuestionsBindingSource
        {
            get
            {
                if (_userEducationAnswersQuestionsBindingSource == null)
                {
                    educationQuestionsTableAdapter.ClearBeforeFill = true;

                    _userEducationAnswersQuestionsBindingSource = new BindingSource();
                    _userEducationAnswersQuestionsBindingSource.DataMember = "EducationQuestions";
                    _userEducationAnswersQuestionsBindingSource.DataSource = dataSet;
                }

                return _userEducationAnswersQuestionsBindingSource;
            }
            set
            {
                _userEducationAnswersQuestionsBindingSource = value;
            }
        }

        /// <summary>
        /// Answers binding source for user answers history
        /// </summary>
        public BindingSource userEducationAnswersAnswersBindingSource
        {
            get
            {
                if (_userEducationAnswersAnswersBindingSource == null)
                {
                    educationAnswersTableAdapter.ClearBeforeFill = true;

                    _userEducationAnswersAnswersBindingSource = new BindingSource();
                    _userEducationAnswersAnswersBindingSource.DataMember = "EducationAnswers";
                    _userEducationAnswersAnswersBindingSource.DataSource = dataSet;
                }

                return _userEducationAnswersAnswersBindingSource;
            }
            set
            {
                _userEducationAnswersAnswersBindingSource = value;
            }
        }


        /// <summary>
        /// Binding source for relation between user education answrs and users
        /// </summary>
        public BindingSource fkUserEducationAnswersUsersBindingSource
        {
            get
            {
                if (_fkUserEducationAnswersUsersBindingSource == null)
                {
                    userEducationAnswersTableAdapter.ClearBeforeFill = true;

                    _fkUserEducationAnswersUsersBindingSource = new BindingSource();
                    _fkUserEducationAnswersUsersBindingSource.DataMember = "FK_UserEducationAnswers_Users";
                    _fkUserEducationAnswersUsersBindingSource.DataSource = userEducationUsersBindingSource;
                }

                return _fkUserEducationAnswersUsersBindingSource;
            }
            set
            {
                _fkUserEducationAnswersUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Education lessons binding source property for import
        /// </summary>
        public BindingSource importEduLessonsBindingSource
        {
            get
            {
                if (_importEduLessonsBindingSource == null)
                {
                    educationLessonsTableAdapter.ClearBeforeFill = true;

                    _importEduLessonsBindingSource = new BindingSource();
                    _importEduLessonsBindingSource.DataMember = "EducationLessons";
                    _importEduLessonsBindingSource.DataSource = dataSet;
                }

                return _importEduLessonsBindingSource;
            }
            set
            {
                _importEduLessonsBindingSource = value;
            }
        }

        /// <summary>
        /// Education categories binding source property for import
        /// </summary>
        public BindingSource importEduCategoriesBindingSource
        {
            get
            {
                if (_importEduCategoriesBindingSource == null)
                {
                    educationCategoriesTableAdapter.ClearBeforeFill = true;

                    _importEduCategoriesBindingSource = new BindingSource();
                    _importEduCategoriesBindingSource.DataMember = "EducationCategories";
                    _importEduCategoriesBindingSource.DataSource = dataSet;
                }

                return _importEduCategoriesBindingSource;
            }
            set
            {
                _importEduCategoriesBindingSource = value;
            }
        }

        /// <summary>
        /// Education questions binding source property for import
        /// </summary>
        public BindingSource importEduQuestionsBindingSource
        {
            get
            {
                if (_importEduQuestionsBindingSource == null)
                {
                    educationQuestionsTableAdapter.ClearBeforeFill = true;

                    _importEduQuestionsBindingSource = new BindingSource();
                    _importEduQuestionsBindingSource.DataMember = "EducationQuestions";
                    _importEduQuestionsBindingSource.DataSource = dataSet;
                }

                return _importEduQuestionsBindingSource;
            }
            set
            {
                _importEduQuestionsBindingSource = value;
            }
        }

        /// <summary>
        /// Education answers binding source property for import
        /// </summary>
        public BindingSource importEduAnswersBindingSource
        {
            get
            {
                if (_importEduAnswersBindingSource == null)
                {
                    educationAnswersTableAdapter.ClearBeforeFill = true;

                    _importEduAnswersBindingSource = new BindingSource();
                    _importEduAnswersBindingSource.DataMember = "EducationAnswers";
                    _importEduAnswersBindingSource.DataSource = dataSet;
                }

                return _importEduAnswersBindingSource;
            }
            set
            {
                _importEduAnswersBindingSource = value;
            }
        }

        #endregion

        #region Notification

        /// <summary>
        /// Notification table adapter property
        /// </summary>
        public NotificationsTableAdapter notificationsTableAdapter
        {
            get
            {
                if (_notificationsTableAdapter == null)
                {
                    _notificationsTableAdapter = new NotificationsTableAdapter(connectionString);
                    _notificationsTableAdapter.Fill(dataSet.Notifications);

                    tableAdapterManager.NotificationsTableAdapter = _notificationsTableAdapter;
                }

                return _notificationsTableAdapter;
            }
            set
            {
                _notificationsTableAdapter = value;
            }
        }

        /// <summary>
        /// Notification binding source property
        /// </summary>
        public BindingSource notificationsBindingSource
        {
            get
            {
                if (_notificationsBindingSource == null)
                {
                    notificationsTableAdapter.ClearBeforeFill = true;

                    _notificationsBindingSource = new BindingSource();
                    _notificationsBindingSource.DataMember = "Notifications";
                    _notificationsBindingSource.DataSource = dataSet;
                }

                return _notificationsBindingSource;
            }
            set
            {
                _notificationsBindingSource = value;
            }
        }

        /// <summary>
        /// Notification display types table adapter property
        /// </summary>
        public NotificationDisplayTypesTableAdapter notificationDisplayTypesTableAdapter
        {
            get
            {
                if (_notificationDisplayTypesTableAdapter == null)
                {
                    _notificationDisplayTypesTableAdapter = new NotificationDisplayTypesTableAdapter(connectionString);
                    _notificationDisplayTypesTableAdapter.Fill(dataSet.NotificationDisplayTypes);

                    tableAdapterManager.NotificationDisplayTypesTableAdapter = _notificationDisplayTypesTableAdapter;
                }

                return _notificationDisplayTypesTableAdapter;
            }
            set
            {
                _notificationDisplayTypesTableAdapter = value;
            }
        }

        /// <summary>
        /// Notification display types binding source property
        /// </summary>
        public BindingSource notificationDisplayTypesBindingSource
        {
            get
            {
                if (_notificationDisplayTypesBindingSource == null)
                {
                    notificationDisplayTypesTableAdapter.ClearBeforeFill = true;

                    _notificationDisplayTypesBindingSource = new BindingSource();
                    _notificationDisplayTypesBindingSource.DataMember = "NotificationDisplayTypes";
                    _notificationDisplayTypesBindingSource.DataSource = dataSet;
                }

                return _notificationDisplayTypesBindingSource;
            }
            set
            {
                _notificationDisplayTypesBindingSource = value;
            }
        }

        /// <summary>
        /// Notification scopes table adapter property
        /// </summary>
        public NotificationScopesTableAdapter notificationScopesTableAdapter
        {
            get
            {
                if (_notificationScopesTableAdapter == null)
                {
                    _notificationScopesTableAdapter = new NotificationScopesTableAdapter(connectionString);
                    _notificationScopesTableAdapter.Fill(dataSet.NotificationScopes);

                    tableAdapterManager.NotificationScopesTableAdapter = _notificationScopesTableAdapter;
                }

                return _notificationScopesTableAdapter;
            }
            set
            {
                _notificationScopesTableAdapter = value;
            }
        }

        /// <summary>
        /// Notification scopes binding source property
        /// </summary>
        public BindingSource notificationScopesBindingSource
        {
            get
            {
                if (_notificationScopesBindingSource == null)
                {
                    notificationScopesTableAdapter.ClearBeforeFill = true;

                    _notificationScopesBindingSource = new BindingSource();
                    _notificationScopesBindingSource.DataMember = "NotificationScopes";
                    _notificationScopesBindingSource.DataSource = dataSet;
                }

                return _notificationScopesBindingSource;
            }
            set
            {
                _notificationScopesBindingSource = value;
            }
        }

        /// <summary>
        /// Notification types table adapter property
        /// </summary>
        public NotificationTypesTableAdapter notificationTypesTableAdapter
        {
            get
            {
                if (_notificationTypesTableAdapter == null)
                {
                    _notificationTypesTableAdapter = new NotificationTypesTableAdapter(connectionString);
                    _notificationTypesTableAdapter.Fill(dataSet.NotificationTypes);

                    tableAdapterManager.NotificationTypesTableAdapter = _notificationTypesTableAdapter;
                }

                return _notificationTypesTableAdapter;
            }
            set
            {
                _notificationTypesTableAdapter = value;
            }
        }

        /// <summary>
        /// Notification types binding source property
        /// </summary>
        public BindingSource notificationTypesBindingSource
        {
            get
            {
                if (_notificationTypesBindingSource == null)
                {
                    notificationTypesTableAdapter.ClearBeforeFill = true;

                    _notificationTypesBindingSource = new BindingSource();
                    _notificationTypesBindingSource.DataMember = "NotificationTypes";
                    _notificationTypesBindingSource.DataSource = dataSet;
                }

                return _notificationTypesBindingSource;
            }
            set
            {
                _notificationTypesBindingSource = value;
            }
        }

        /// <summary>
        /// User notification table adapter property 
        /// </summary>
        public UserNotificationsTableAdapter userNotificationsTableAdapter
        {
            get
            {
                if (_userNotificationsTableAdapter == null)
                {
                    _userNotificationsTableAdapter = new UserNotificationsTableAdapter(connectionString);
                    _userNotificationsTableAdapter.Fill(dataSet.UserNotifications);

                    tableAdapterManager.UserNotificationsTableAdapter = _userNotificationsTableAdapter;
                }

                return _userNotificationsTableAdapter;
            }
            set
            {
                _userNotificationsTableAdapter = value;
            }
        }

        /// <summary>
        /// User notification binding source property 
        /// </summary>
        public BindingSource userNotificationsBindingSource
        {
            get
            {
                if (_userNotificationsBindingSource == null)
                {
                    userNotificationsTableAdapter.ClearBeforeFill = true;

                    _userNotificationsBindingSource = new BindingSource();
                    _userNotificationsBindingSource.DataMember = "UserNotifications";
                    _userNotificationsBindingSource.DataSource = dataSet;
                }

                return _userNotificationsBindingSource;
            }
            set
            {
                _userNotificationsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between user notifications and users
        /// </summary>
        public BindingSource fkUserNotificationsUsersBindingSource
        {
            get
            {
                if (_fkUserNotificationsUsersBindingSource == null)
                {
                    userNotificationsTableAdapter.ClearBeforeFill = true;

                    _fkUserNotificationsUsersBindingSource = new BindingSource();
                    _fkUserNotificationsUsersBindingSource.DataMember = "FK_UserNotifications_Users";
                    _fkUserNotificationsUsersBindingSource.DataSource = notificationsUsersBindingSource;
                }

                return _fkUserNotificationsUsersBindingSource;
            }
            set
            {
                _fkUserNotificationsUsersBindingSource = value;
            }
        }

        /// <summary>
        /// User notification history table adapter property
        /// </summary>
        public UserNotificationsHistoryTableAdapter userNotificationsHistoryTableAdapter
        {
            get
            {
                if (_userNotificationsHistoryTableAdapter == null)
                {
                    _userNotificationsHistoryTableAdapter = new UserNotificationsHistoryTableAdapter(connectionString);
                    _userNotificationsHistoryTableAdapter.Fill(dataSet.UserNotificationsHistory);

                    tableAdapterManager.UserNotificationsHistoryTableAdapter = _userNotificationsHistoryTableAdapter;
                }

                return _userNotificationsHistoryTableAdapter;
            }
            set
            {
                _userNotificationsHistoryTableAdapter = value;
            }
        }

        /// <summary>
        /// User notification history binding source property
        /// </summary>
        public BindingSource userNotificationsHistoryBindingSource
        {
            get
            {
                if (_userNotificationsHistoryBindingSource == null)
                {
                    userNotificationsHistoryTableAdapter.ClearBeforeFill = true;

                    _userNotificationsHistoryBindingSource = new BindingSource();
                    _userNotificationsHistoryBindingSource.DataMember = "UserNotificationsHistory";
                    _userNotificationsHistoryBindingSource.DataSource = dataSet;
                }

                return _userNotificationsHistoryBindingSource;
            }
            set
            {
                _userNotificationsHistoryBindingSource = value;
            }
        }

        /// <summary>
        /// Users for user notifications
        /// </summary>
        public BindingSource notificationsUsersBindingSource
        {
            get
            {
                if (_notificationsUsersBindingSource == null)
                {
                    usersTableAdapter.ClearBeforeFill = true;

                    _notificationsUsersBindingSource = new BindingSource();
                    _notificationsUsersBindingSource.DataMember = "Users";
                    _notificationsUsersBindingSource.DataSource = dataSet;
                }

                return _notificationsUsersBindingSource;
            }
            set
            {
                _notificationsUsersBindingSource = value;
            }
        }


        /// <summary>
        /// User groups for user notifications
        /// </summary>
        public BindingSource notificationsUserGroupsBindingSource
        {
            get
            {
                if (_notificationsUserGroupsBindingSource == null)
                {
                    userGroupsTableAdapter.ClearBeforeFill = true;

                    _notificationsUserGroupsBindingSource = new BindingSource();
                    _notificationsUserGroupsBindingSource.DataMember = "UserGroups";
                    _notificationsUserGroupsBindingSource.DataSource = dataSet;
                }

                return _notificationsUserGroupsBindingSource;
            }
            set
            {
                _notificationsUserGroupsBindingSource = value;
            }
        }

        /// <summary>
        /// Notices for user notifications
        /// </summary>
        public BindingSource userNotificationNoticesBindingSource
        {
            get
            {
                if (_userNotificationNoticesBindingSource == null)
                {
                    notificationsTableAdapter.ClearBeforeFill = true;

                    _userNotificationNoticesBindingSource = new BindingSource();
                    _userNotificationNoticesBindingSource.DataMember = "Notifications";
                    _userNotificationNoticesBindingSource.DataSource = dataSet;
                }

                return _userNotificationNoticesBindingSource;
            }
            set
            {
                _userNotificationNoticesBindingSource = value;
            }
        }

        /// <summary>
        /// Notices for user group notifications
        /// </summary>
        public BindingSource userGroupNotificationNoticesBindingSource
        {
            get
            {
                if (_userGroupNotificationNoticesBindingSource == null)
                {
                    notificationsTableAdapter.ClearBeforeFill = true;

                    _userGroupNotificationNoticesBindingSource = new BindingSource();
                    _userGroupNotificationNoticesBindingSource.DataMember = "Notifications";
                    _userGroupNotificationNoticesBindingSource.DataSource = dataSet;
                }

                return _userGroupNotificationNoticesBindingSource;
            }
            set
            {
                _userGroupNotificationNoticesBindingSource = value;
            }
        }

        /// <summary>
        /// Display types for user notifications
        /// </summary>
        public BindingSource userNotificationDisplayTypesBindingSource
        {
            get
            {
                if (_userNotificationDisplayTypesBindingSource == null)
                {
                    notificationDisplayTypesTableAdapter.ClearBeforeFill = true;

                    _userNotificationDisplayTypesBindingSource = new BindingSource();
                    _userNotificationDisplayTypesBindingSource.DataMember = "NotificationDisplayTypes";
                    _userNotificationDisplayTypesBindingSource.DataSource = dataSet;
                }

                return _userNotificationDisplayTypesBindingSource;
            }
            set
            {
                _userNotificationDisplayTypesBindingSource = value;
            }
        }

        /// <summary>
        /// Display types for user group notifications
        /// </summary>
        public BindingSource userGroupNotificationDisplayTypesBindingSource
        {
            get
            {
                if (_userGroupNotificationDisplayTypesBindingSource == null)
                {
                    notificationDisplayTypesTableAdapter.ClearBeforeFill = true;

                    _userGroupNotificationDisplayTypesBindingSource = new BindingSource();
                    _userGroupNotificationDisplayTypesBindingSource.DataMember = "NotificationDisplayTypes";
                    _userGroupNotificationDisplayTypesBindingSource.DataSource = dataSet;
                }

                return _userGroupNotificationDisplayTypesBindingSource;
            }
            set
            {
                _userGroupNotificationDisplayTypesBindingSource = value;
            }
        }


        /// <summary>
        /// Binding source for relation between user notification history and users
        /// </summary>
        public BindingSource fkUserNotificationsHistoryUsersBindingSource
        {
            get
            {
                if (_fkUserNotificationsHistoryUsersBindingSource == null)
                {
                    userNotificationsHistoryTableAdapter.ClearBeforeFill = true;

                    _fkUserNotificationsHistoryUsersBindingSource = new BindingSource();
                    _fkUserNotificationsHistoryUsersBindingSource.DataMember = "FK_UserNotificationsHistory_Users";
                    _fkUserNotificationsHistoryUsersBindingSource.DataSource = notificationsUsersBindingSource;
                }

                return _fkUserNotificationsHistoryUsersBindingSource;
            }
            set
            {
                _fkUserNotificationsHistoryUsersBindingSource = value;
            }
        }

        /// <summary>
        /// Notices for user notifications history
        /// </summary>
        public BindingSource userNotificationHistoryNoticesBindingSource
        {
            get
            {
                if (_userNotificationHistoryNoticesBindingSource == null)
                {
                    notificationsTableAdapter.ClearBeforeFill = true;

                    _userNotificationHistoryNoticesBindingSource = new BindingSource();
                    _userNotificationHistoryNoticesBindingSource.DataMember = "Notifications";
                    _userNotificationHistoryNoticesBindingSource.DataSource = dataSet;
                }

                return _userNotificationHistoryNoticesBindingSource;
            }
            set
            {
                _userNotificationHistoryNoticesBindingSource = value;
            }
        }

        #endregion

        #region Licanse

        /// <summary>
        /// License table adapter property
        /// </summary>
        public LicenseTableAdapter licenseTableAdapter
        {
            get
            {
                if (_licenseTableAdapter == null)
                {
                    _licenseTableAdapter = new LicenseTableAdapter(connectionString);
                    _licenseTableAdapter.Fill(dataSet.License);

                    tableAdapterManager.LicenseTableAdapter = _licenseTableAdapter;
                }

                return _licenseTableAdapter;
            }
            set
            {
                _licenseTableAdapter = value;
            }
        }

        /// <summary>
        /// License binding source property
        /// </summary>
        public BindingSource licenseBindingSource
        {
            get
            {
                if (_licenseBindingSource == null)
                {
                    licenseTableAdapter.ClearBeforeFill = true;

                    _licenseBindingSource = new BindingSource();
                    _licenseBindingSource.DataMember = "License";
                    _licenseBindingSource.DataSource = dataSet;
                }

                return _licenseBindingSource;
            }
            set
            {
                _licenseBindingSource = value;
            }
        }

        #endregion

        #region OS types

        /// <summary>
        /// OS types table adapter property
        /// </summary>
        public OSTypesTableAdapter osTypesTableAdapter
        {
            get
            {
                if (_osTypesTableAdapter == null)
                {
                    _osTypesTableAdapter = new OSTypesTableAdapter(connectionString);
                    _osTypesTableAdapter.Fill(dataSet.OSTypes);

                    tableAdapterManager.OSTypesTableAdapter = _osTypesTableAdapter;
                }

                return _osTypesTableAdapter;
            }
            set
            {
                _osTypesTableAdapter = value;
            }
        }

        /// <summary>
        /// OS types binding source property
        /// </summary>
        public BindingSource osTypesBindingSource
        {
            get
            {
                if (_osTypesBindingSource == null)
                {
                    osTypesTableAdapter.ClearBeforeFill = true;

                    _osTypesBindingSource = new BindingSource();
                    _osTypesBindingSource.DataMember = "OSTypes";
                    _osTypesBindingSource.DataSource = dataSet;
                }

                return _osTypesBindingSource;
            }
            set
            {
                _osTypesBindingSource = value;
            }
        }

        /// <summary>
        /// Preset binding source for OS types
        /// </summary>
        public BindingSource osPresetsBindingSource
        {
            get
            {
                if (_osPresetsBindingSource == null)
                {
                    presetTableAdapter.ClearBeforeFill = true;

                    _osPresetsBindingSource = new BindingSource();
                    _osPresetsBindingSource.DataMember = "Preset";
                    _osPresetsBindingSource.DataSource = dataSet;
                }

                return _osPresetsBindingSource;
            }
            set
            {
                _osPresetsBindingSource = value;
            }

        }

        #endregion

        #region Permissions

        /// <summary>
        /// Permissions table adapter property
        /// </summary>
        public PermissionsTableAdapter permissionsTableAdapter
        {
            get
            {
                if (_permissionsTableAdapter == null)
                {
                    _permissionsTableAdapter = new PermissionsTableAdapter(connectionString);
                    _permissionsTableAdapter.Fill(dataSet.Permissions);

                    tableAdapterManager.PermissionsTableAdapter = _permissionsTableAdapter;
                }

                return _permissionsTableAdapter;
            }
            set
            {
                _permissionsTableAdapter = value;
            }
        }

        /// <summary>
        /// Permissions bindindg source property
        /// </summary>
        public BindingSource permissionsBindingSource
        {
            get
            {
                if (_permissionsBindingSource == null)
                {
                    permissionsTableAdapter.ClearBeforeFill = true;

                    _permissionsBindingSource = new BindingSource();
                    _permissionsBindingSource.DataMember = "Permissions";
                    _permissionsBindingSource.DataSource = dataSet;
                }

                return _permissionsBindingSource;
            }
            set
            {
                _permissionsBindingSource = value;
            }
        }

        /// <summary>
        /// User permissions table adapter property
        /// </summary>
        public UserPermissionsTableAdapter userPermissionsTableAdapter
        {
            get
            {
                if (_userPermissionsTableAdapter == null)
                {
                    _userPermissionsTableAdapter = new UserPermissionsTableAdapter(connectionString);
                    _userPermissionsTableAdapter.Fill(dataSet.UserPermissions);

                    tableAdapterManager.UserPermissionsTableAdapter = _userPermissionsTableAdapter;
                }

                return _userPermissionsTableAdapter;
            }
            set
            {
                _userPermissionsTableAdapter = value;
            }
        }

        /// <summary>
        /// User permissions binding source property
        /// </summary>
        public BindingSource userPermissionsBindingSource
        {
            get
            {
                if (_userPermissionsBindingSource == null)
                {
                    userPermissionsTableAdapter.ClearBeforeFill = true;

                    _userPermissionsBindingSource = new BindingSource();
                    _userPermissionsBindingSource.DataMember = "UserPermissions";
                    _userPermissionsBindingSource.DataSource = dataSet;
                }

                return _userPermissionsBindingSource;
            }
            set
            {
                _userPermissionsBindingSource = value;
            }
        }

        /// <summary>
        /// Binding source for relation between user permissions and users
        /// </summary>
        public BindingSource fkUserPermissionsUsersBindingSource
        {
            get
            {
                if (_fkUserPermissionsUsersBindingSource == null)
                {
                    userPermissionsTableAdapter.ClearBeforeFill = true;

                    _fkUserPermissionsUsersBindingSource = new BindingSource();
                    _fkUserPermissionsUsersBindingSource.DataMember = "FK_UserPermissions_Users";
                    _fkUserPermissionsUsersBindingSource.DataSource = usersBindingSource;
                }

                return _fkUserPermissionsUsersBindingSource;
            }
            set
            {
                _fkUserPermissionsUsersBindingSource = value;
            }
        }

        #endregion

        #endregion

        #region Table adapters manager

        /// <summary>
        /// Table adapters manager
        /// </summary>
        public TableAdapterManager tableAdapterManager
        {
            get
            {
                if (_tableAdapterManager == null)
                {
                    _tableAdapterManager = new TableAdapterManager();

                    _tableAdapterManager.BackupDataSetBeforeUpdate = false;
                    _tableAdapterManager.UpdateOrder = TableAdapterManager.UpdateOrderOption.InsertUpdateDelete;

                    _tableAdapterManager.AuthSystemTypesTableAdapter = null;
                    _tableAdapterManager.AuthSystemsTableAdapter = null;
                    _tableAdapterManager.UserAccountActionsTableAdapter = null;
                    _tableAdapterManager.UserAccountActionsOnDeleteTableAdapter = null;
                    _tableAdapterManager.UserAccountActionsOnInsertTableAdapter = null;
                    _tableAdapterManager.UserAccountActionsOnUpdateTableAdapter = null;
                    _tableAdapterManager.OSTypesTableAdapter = null;
                    _tableAdapterManager.ComputersTableAdapter = null;
                    _tableAdapterManager.EducationAnswersTableAdapter = null;
                    _tableAdapterManager.EducationCategoriesTableAdapter = null;
                    _tableAdapterManager.EducationLessonsTableAdapter = null;
                    _tableAdapterManager.EducationQuestionAnswersTableAdapter = null;
                    _tableAdapterManager.EducationQuestionsTableAdapter = null;
                    _tableAdapterManager.LicenseTableAdapter = null;
                    _tableAdapterManager.NotificationDisplayTypesTableAdapter = null;
                    _tableAdapterManager.NotificationScopesTableAdapter = null;
                    _tableAdapterManager.NotificationsTableAdapter = null;
                    _tableAdapterManager.NotificationTypesTableAdapter = null;
                    _tableAdapterManager.PasswordConstructionRulesTableAdapter = null;
                    _tableAdapterManager.PasswordConstructionRulesTypesTableAdapter = null;
                    _tableAdapterManager.PresetDetailsTableAdapter = null;
                    _tableAdapterManager.PresetHookupTableAdapter = null;
                    _tableAdapterManager.PresetTableAdapter = null;
                    _tableAdapterManager.ScreensTableAdapter = null;
                    _tableAdapterManager.ScreensPresetDetailsTableAdapter = null;
                    _tableAdapterManager.ScreenTypesTableAdapter = null;
                    _tableAdapterManager.ScreenObjectScopesTableAdapter = null;
                    _tableAdapterManager.ScreenObjectListValuesTableAdapter = null;
                    _tableAdapterManager.ScreenObjectsTableAdapter = null;
                    _tableAdapterManager.ScreenObjectTypesTableAdapter = null;
                    _tableAdapterManager.UserCheckValuesTableAdapter = null;
                    _tableAdapterManager.UserCheckValuesScreenObjectsTableAdapter = null;
                    _tableAdapterManager.UserEducationAnswersTableAdapter = null;
                    _tableAdapterManager.UserEducationTableAdapter = null;
                    _tableAdapterManager.UserNotificationsHistoryTableAdapter = null;
                    _tableAdapterManager.UserNotificationsTableAdapter = null;
                    _tableAdapterManager.UserPasswordConstructionRulesTableAdapter = null;
                    _tableAdapterManager.TmpUserPasswordConstructionRulesTableAdapter = null;
                    _tableAdapterManager.UsersTableAdapter = null;
                    _tableAdapterManager.UserAccountsTableAdapter = null;
                    _tableAdapterManager.UserAccountsArchiveTableAdapter = null;
                    _tableAdapterManager.UserPermissionsTableAdapter = null;
                    _tableAdapterManager.UserGroupAuthSystemsTableAdapter = null;
                    _tableAdapterManager.UserGroupEducationTableAdapter = null;
                    _tableAdapterManager.UserGroupNotificationsTableAdapter = null;
                    _tableAdapterManager.UserGroupPermissionsTableAdapter = null;
                    _tableAdapterManager.UserGroupsTableAdapter = null;
                    _tableAdapterManager.UserGroupUsersTableAdapter = null;
                    _tableAdapterManager.ControlledProgramsTableAdapter = null;
                    _tableAdapterManager.ScheduleActionsTableAdapter = null;
                    _tableAdapterManager.ScheduleFunctionsTableAdapter = null;
                    _tableAdapterManager.ScheduleTableAdapter = null;
                }

                return _tableAdapterManager;
            }
            set
            {
                _tableAdapterManager = value;
            }
        }

        /// <summary>
        /// Update all table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateAll()
        {
            try
            {
                tableAdapterManager.UpdateAll(dataSet);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the database!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the database!");
                return false;
            }
        }

        /// <summary>
        /// Update auth systems table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateAuthSystems()
        {
            try
            {
                WriteToLogAuthSystems();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Authentication Systems updating information for logging!");
            }
            
            try
            {
                authSystemsTableAdapter.Update(dataSet.AuthSystems);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Authentication Systems data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Authentication Systems data!");
                return false;
            }
        }

        /// <summary>
        /// Update computers table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateComputers()
        {
            try
            {
                WriteToLogComputers();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Computers updating information for logging!");
            }

            try
            {
                computersTableAdapter.Update(dataSet.Computers);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Computers data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Computers data!");
                return false;
            }
        }

        /// <summary>
        /// Update education answers table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateEducationAnswers()
        {
            try
            {
                WriteToLogEducationAnswers();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Education Answers updating information for logging!");
            }

            try
            {
                educationAnswersTableAdapter.Update(dataSet.EducationAnswers);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Education Answers data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Education Answers data!");
                return false;
            }
        }

        /// <summary>
        /// Update education lessons table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateEducationLessons()
        {
            try
            {
                WriteToLogEducationLessons();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Education Lessons updating information for logging!");
            }
            
            try
            {
                educationLessonsTableAdapter.Update(dataSet.EducationLessons);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Education Lessons data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Education Lessons data!");
                return false;
            }
        }

        /// <summary>
        /// Update education questions table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateEducationQuestions()
        {
            try
            {
                WriteToLogEducationQuestions();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Education Questions updating information for logging!");
            }
            
            try
            {
                educationQuestionsTableAdapter.Update(dataSet.EducationQuestions);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Education Questions data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Education Questions data!");
                return false;
            }
        }

        /// <summary>
        /// Update education question answers table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateEducationQuestionAnswers()
        {
            try
            {
                WriteToLogEducationQuestionAnswers();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Education Question Answers updating information for logging!");
            }
            
            try
            {
                educationQuestionAnswersTableAdapter.Update(dataSet.EducationQuestionAnswers);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Education Question Answers data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Education Question Answers data!");
                return false;
            }
        }

        /// <summary>
        /// Update education categories table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateEducationCategories()
        {
            try
            {
                WriteToLogEducationCategories();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Education Categories updating information for logging!");
            }
             
            try
            {
                educationCategoriesTableAdapter.Update(dataSet.EducationCategories);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Education Categories data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Education Categories data!");
                return false;
            }
        }

        /// <summary>
        /// Update license table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateLicense()
        {
            try
            {
                WriteToLogLicense();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare License updating information for logging!");
            }
            
            try
            {
                licenseTableAdapter.Update(dataSet.License);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the License data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the License data!");
                return false;
            }
        }

        /// <summary>
        /// Update notifications table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateNotifications()
        {
            try
            {
                WriteToLogNotifications();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Notifications updating information for logging!");
            }
            
            try
            {
                notificationsTableAdapter.Update(dataSet.Notifications);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Notifications data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Notifications data!");
                return false;
            }
        }

        /// <summary>
        /// Update OSTypes table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateOSTypes()
        {
            try
            {
                WriteToLogOSTypes();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare OS Types updating information for logging!");
            }

            try
            {
                osTypesTableAdapter.Update(dataSet.OSTypes);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the OS types data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the OS types data!");
                return false;
            }
        }

        /// <summary>
        /// Update perset table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdatePreset()
        {
            try
            {
                WriteToLogPresets();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Preset updating information for logging!");
            }

            try
            {
                presetTableAdapter.Update(dataSet.Preset);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Preset data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Preset data!");
                return false;
            }
        }

        /// <summary>
        /// Update perset details table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdatePresetDetails()
        {
            try
            {
                WriteToLogPresetDetails();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Preset Details updating information for logging!");
            }

            try
            {
                presetDetailsTableAdapter.Update(dataSet.PresetDetails);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Preset details data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Preset details data!");
                return false;
            }
        }

        /// <summary>
        /// Update perset hookup table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdatePresetHookup()
        {
            try
            {
                WriteToLogPresetHookup();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Preset Hookup updating information for logging!");
            }

            try
            {
                presetHookupTableAdapter.Update(dataSet.PresetHookup);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Preset Hookup data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Preset Hookup data!");
                return false;
            }
        }

        /// <summary>
        /// Update screen objects table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateScreenObjects()
        {
            try
            {
                WriteToLogScreenObjects();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Screen Objects updating information for logging!");
            }

            try
            {
                screenObjectsTableAdapter.Update(dataSet.ScreenObjects);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Screen Objects data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Screen Objects data!");
                return false;
            }
        }

        /// <summary>
        /// Update screen objects list values table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateScreenObjectsListValues()
        {
            try
            {
                WriteToLogScreenObjectListValues();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Screen Object List Values updating information for logging!");
            }
            
            try
            {
                screenObjectListValuesTableAdapter.Update(dataSet.ScreenObjectListValues);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Screen Objects List Values data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Screen Objects List Values data!");
                return false;
            }
        }

        /// <summary>
        /// Update user accounts table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserAccounts()
        {
            try
            {
                WriteToLogUserAccounts();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User Accounts updating information for logging!");
            }

            try
            {
                userAccountsTableAdapter.Update(dataSet.UserAccounts);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the user accounts data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the user accounts data!");
                return false;
            }
        }

        /// <summary>
        /// Update user accounts archive table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserAccountsArchive()
        {
            try
            {
                WriteToLogUserAccountsArchive();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User accounts archive updating information for logging!");
            }

            try
            {
                userAccountsArchiveTableAdapter.Update(dataSet.UserAccountsArchive);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the user accounts archive data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the user accounts archive data!");
                return false;
            }
        }

        /// <summary>
        /// Update user check values table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserCheckValues()
        {
            try
            {
                WriteToLogUserCheckValues();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User Parameters for Checking updating information for logging!");
            }

            try
            {
                userCheckValuesTableAdapter.Update(dataSet.UserCheckValues);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the user check values data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the user check values data!");
                return false;
            }
        }

        /// <summary>
        /// Update user education table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserEducation()
        {
            try
            {
                WriteToLogUserEducation();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User Education updating information for logging!");
            }
            
            try
            {
                userEducationTableAdapter.Update(dataSet.UserEducation);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the user education data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the user education data!");
                return false;
            }
        }

        /// <summary>
        /// Update user education answers table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserEducationAnswers()
        {
            try
            {
                WriteToLogUserEducationAnswers();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User Education Answers updating information for logging!");
            }

            try
            {
                userEducationAnswersTableAdapter.Update(dataSet.UserEducationAnswers);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the user education answers data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the user education answers data!");
                return false;
            }
        }

        /// <summary>
        /// Update user notifications table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserNotifications()
        {
            try
            {
                WriteToLogUserNotifications();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User Notifications updating information for logging!");
            }
            
            try
            {
                userNotificationsTableAdapter.Update(dataSet.UserNotifications);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the user notifications data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the user notifications data!");
                return false;
            }
        }

        /// <summary>
        /// Update user notifications history table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserNotificationsHistory()
        {
            try
            {
                WriteToLogUserNotificationsHistory();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User Notifications History updating information for logging!");
            }
            
            try
            {
                userNotificationsHistoryTableAdapter.Update(dataSet.UserNotificationsHistory);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the user notifications history data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the user notifications history data!");
                return false;
            }
        }

        /// <summary>
        /// Update user password construction rules table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserPasswordConstructionRules()
        {
            try
            {
                userPasswordConstructionRulesTableAdapter.Update(dataSet.UserPasswordConstructionRules);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the user password construction rules data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the user password construction rules data!");
                return false;
            }
        }

        /// <summary>
        /// Update temp user password construction rules table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateTempUserPasswordConstructionRules()
        {
            try
            {
                tmpUserPasswordConstructionRulesTableAdapter.Update(dataSet.TmpUserPasswordConstructionRules);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the temporary user password construction rules data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the temporary user password construction rules data!");
                return false;
            }
        }

        /// <summary>
        /// Update user groups table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserGroups()
        {
            try
            {
                WriteToLogUserGroups();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User groups updating information for logging!");
            }

            try
            {
                userGroupsTableAdapter.Update(dataSet.UserGroups);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the User groups data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the User groups data!");
                return false;
            }
        }

        /// <summary>
        /// Update user groups table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserGroupUsers()
        {
            try
            {
                WriteToLogUserGroupUsers();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User groups updating information for logging!");
            }

            try
            {
                userGroupUsersTableAdapter.Update(dataSet.UserGroupUsers);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the User group users data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the User group users data!");
                return false;
            }
        }

        /// <summary>
        /// Update user group auth systems table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserGroupAuthSystems()
        {
            try
            {
                WriteToLogUserGroupAuthSystems();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User group auth systems updating information for logging!");
            }

            try
            {
                userGroupAuthSystemsTableAdapter.Update(dataSet.UserGroupAuthSystems);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the User group auth systems data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the User group auth systems data!");
                return false;
            }
        }

        /// <summary>
        /// Update user group education table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserGroupEducation()
        {
            try
            {
                WriteToLogUserGroupEducation();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User group education updating information for logging!");
            }

            try
            {
                userGroupEducationTableAdapter.Update(dataSet.UserGroupEducation);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the User group education data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the User group education data!");
                return false;
            }
        }

        /// <summary>
        /// Update user group notifications table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserGroupNotifications()
        {
            try
            {
                WriteToLogUserGroupNotifications();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User group notifications updating information for logging!");
            }

            try
            {
                userGroupNotificationsTableAdapter.Update(dataSet.UserGroupNotifications);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the User group notifications data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the User group notifications data!");
                return false;
            }
        }

        /// <summary>
        /// Update user group permissions table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserGroupPermissions()
        {
            try
            {
                WriteToLogUserGroupPermissions();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User group permissions updating information for logging!");
            }

            try
            {
                userGroupPermissionsTableAdapter.Update(dataSet.UserGroupPermissions);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the User group permissions data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the User group permissions data!");
                return false;
            }
        }
        /// <summary>
        /// Update user permissions table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUserPermissions()
        {
            try
            {
                WriteToLogUserPermissions();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare User Permissions updating information for logging!");
            }

            try
            {
                userPermissionsTableAdapter.Update(dataSet.UserPermissions);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the User Permissions data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the User Permissions data!");
                return false;
            }
        }

        /// <summary>
        /// Update users table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateUsers()
        {
            try
            {
                WriteToLogUsers();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Users updating information for logging!");
            }

            try
            {
                usersTableAdapter.Update(dataSet.Users);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Users data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Users data!");
                return false;
            }
        }

        /// <summary>
        /// Update screens table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateScreens()
        {
            try
            {
                WriteToLogScreens();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Screens updating information for logging!");
            }

            try
            {
                screensTableAdapter.Update(dataSet.Screens);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Screens data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Screens data!");
                return false;
            }
        }
                     

        /// <summary>
        /// Update screens preset details table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateScreensPresetDetails()
        {
            try
            {
                WriteToLogScreensPresetDetails();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Preset Screens updating information for logging!");
            }

            try
            {
                screensPresetDetailsTableAdapter.Update(dataSet.ScreensPresetDetails);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Screens Preset Details data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Screens Preset Details data!");
                return false;
            }
        }

        /// <summary>
        /// Update controlled programs table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateControlledPrograms()
        {
            try
            {
                WriteToLogControlledPrograms();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Controlled Programs updating information for logging!");
            }

            try
            {
                controlledProgramsTableAdapter.Update(dataSet.ControlledPrograms);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Controlled Programs data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Controlled Programs data!");
                return false;
            }
        }

        /// <summary>
        /// Update schedule actions table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateScheduleActions()
        {
            try
            {
                WriteToLogScheduleActions();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Schedule Actions updating information for logging!");
            }

            try
            {
                scheduleActionsTableAdapter.Update(dataSet.ScheduleActions);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Schedule Actions data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Schedule Actions data!");
                return false;
            }
        }

        /// <summary>
        /// Update schedule functions table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateScheduleFunctions()
        {
            try
            {
                WriteToLogScheduleFunctions();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Schedule Functions updating information for logging!");
            }

            try
            {
                scheduleFunctionsTableAdapter.Update(dataSet.ScheduleFunctions);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Schedule Functions data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Schedule Functions data!");
                return false;
            }
        }

        /// <summary>
        /// Update schedule table adapters
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool UpdateSchedule()
        {
            try
            {
                WriteToLogSchedule();
            }
            catch
            {
                logWriter.WriteToLog("Database manager --> Can't prepare Schedule updating information for logging!");
            }

            try
            {
                scheduleTableAdapter.Update(dataSet.Schedule);
                return true;
            }
            catch (DBConcurrencyException dbEx)
            {
                HandleConcurrencyException(dbEx);
                return false;
            }
            catch
            {
                MessageBox.Show("An error was thrown while attempting to update the Schedule data!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Database manager --> An error was thrown while attempting to update the Schedule data!");
                return false;
            }
        }

        /// <summary>
        /// Update table by table name
        /// </summary>
        /// <param name="tableName">table name</param>
        /// <returns>TRUE - if success</returns>
        public bool Update(string tableName)
        {
            switch (tableName)
            {
                case "AuthSystems"                              : return UpdateAuthSystems();
                case "Computers"                                : return UpdateComputers();
                case "EducationAnswers"                         : return UpdateEducationAnswers();
                case "EducationCategories"                      : return UpdateEducationCategories();
                case "EducationLessons"                         : return UpdateEducationLessons();
                case "EducationQuestionAnswers"                 : return UpdateEducationQuestionAnswers();
                case "EducationQuestions"                       : return UpdateEducationQuestions();
                case "License"                                  : return UpdateLicense();
                case "Notifications"                            : return UpdateNotifications();
                case "OSTypes"                                  : return UpdateOSTypes();
                case "Preset"                                   : return UpdatePreset();
                case "PresetDetails"                            : return UpdatePresetDetails();
                case "PresetHookup"                             : return UpdatePresetHookup();
                case "ScreenObjectListValues"                   : return UpdateScreenObjectsListValues();
                case "ScreenObjects"                            : return UpdateScreenObjects();
                case "Screens"                                  : return UpdateScreens();
                case "ScreenPresetDetails"                      : return UpdateScreensPresetDetails();
                case "UserAccounts"                             : return UpdateUserAccounts();
                case "UserAccountsArchive"                      : return UpdateUserAccountsArchive();
                case "UserCheckValues"                          : return UpdateUserCheckValues();
                case "UserEducation"                            : return UpdateUserEducation();
                case "UserEducationAnswers"                     : return UpdateUserEducationAnswers();
                case "UserNotifications"                        : return UpdateUserNotifications();
                case "UserNotificationsHistory"                 : return UpdateUserNotificationsHistory();
                case "UserPasswordConstructionRules"            : return UpdateUserPasswordConstructionRules();
                case "TmpUserPasswordConstructionRules"         : return UpdateTempUserPasswordConstructionRules();
                case "UserPermissions"                          : return UpdateUserPermissions();
                case "Users"                                    : return UpdateUsers();
                case "UserGroupUsers"                           : return UpdateUserGroupUsers();
                case "UserGroupAuthSystems"                     : return UpdateUserGroupAuthSystems();
                case "UserGroupEducation"                       : return UpdateUserGroupEducation();
                case "UserGroupNotifications"                   : return UpdateUserGroupNotifications();
                case "UserGroupPermissions"                     : return UpdateUserGroupPermissions();
                case "ControlledPrograms"                       : return UpdateControlledPrograms();
                case "ScheduleActions"                          : return UpdateScheduleActions();
                case "ScheduleFunctions"                        : return UpdateScheduleFunctions();
                case "Schedule"                                 : return UpdateSchedule();
            }

            return false;
        }

        /// <summary>
        /// Processing DB concurrency violation
        /// </summary>
        /// <param name="dbcx">DB concurrency exception instance</param>
        private void HandleConcurrencyException(DBConcurrencyException dbcx)
        {
            // Two possibilities come to mind:
            //   (1) someone else edited the record behind our back, so that the Version number does not match.
            //   (2) someone else deleted the record behind our back, so that there is no record to update.
            //
            // Let's determine which.

            DataRow ourRow = dbcx.Row;
            DataTable dt = GetConcurrencyDataTable(ourRow);

            if (dt != null)
            {
                DataRow dbRow = GetCurrentRowInDB(dt);
                if (dbRow == null) HandleDbDeletion(ourRow);
                else HandleDbUpdate(ourRow, dbRow, dt);
            }
            else
                MessageBox.Show("Database concurrency violation! Please refresh data and try again!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        /// <summary>
        /// Get data table with data that throw concurrency exception
        /// </summary>
        /// <param name="ourRow">concurrency exception row</param>
        /// <returns>table with data that throw concurrency exception</returns>
        private DataTable GetConcurrencyDataTable(DataRow ourRow)
        {
            switch (ourRow.Table.TableName)
            {
                case "AuthSystems"                      : return authSystemsTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "Computers"                        : return computersTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "EducationAnswers"                 : return educationAnswersTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "EducationCategories"              : return educationCategoriesTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "EducationLessons"                 : return educationLessonsTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "EducationQuestionAnswers"         : return educationQuestionAnswersTableAdapter.GetDataByID((int)ourRow["QuestionID"], (int)ourRow["AnswerID"]);
                case "EducationQuestions"               : return educationQuestionsTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "License"                          : return licenseTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "Notifications"                    : return notificationsTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "OSTypes"                          : return osTypesTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "Preset"                           : return presetTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "PresetDetails"                    : return presetDetailsTableAdapter.GetDataByParams((int)ourRow["PresetID"], (int)ourRow["ScreenObjectID"], (int?)ourRow["ParentID"], (int?)ourRow["ScreenObjectOrder"]);
                case "PresetHookup"                     : return presetHookupTableAdapter.GetDataByParams((int)ourRow["PresetID"], (int?)ourRow["UserID"], (int?)ourRow["ComputerID"], (int?)ourRow["OSTypeID"], (int?)ourRow["GroupID"]);
                case "ScreenObjectListValues"           : return screenObjectListValuesTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "ScreenObjects"                    : return screenObjectsTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "Screens"                          : return screensTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "ScreenPresetDetails"              : return screensPresetDetailsTableAdapter.GetDataByParams((int)ourRow["ScreenObjectID"], (int)ourRow["PresetID"], (int?)ourRow["ScreenObjectOrder"]);
                case "UserAccounts"                     : return userAccountsTableAdapter.GetDataByID((int)ourRow["UserID"], (int)ourRow["authSystemID"]);
                case "UserAccountsArchive"              : return userAccountsArchiveTableAdapter.GetDataByID((int)ourRow["UserID"], (int)ourRow["authSystemID"]);
                case "UserCheckValues"                  : return userCheckValuesTableAdapter.GetDataByID((int)ourRow["UserID"], (int)ourRow["screenObjectID"]);
                case "UserEducation"                    : return userEducationTableAdapter.GetDataByID((int)ourRow["UserID"], (int)ourRow["EduCategID"]);
                case "UserEducationAnswers"             : return userEducationAnswersTableAdapter.GetDataByParams((int)ourRow["UserID"], (int)ourRow["QuestionID"], (int)ourRow["AnswerID"], (short)ourRow["CorrectAnswerSign"], (DateTime)ourRow["Date"]);
                case "UserNotifications"                : return userNotificationsTableAdapter.GetDataByID((int)ourRow["UserID"], (int)ourRow["NoticeID"]);
                case "UserNotificationsHistory"         : return userNotificationsHistoryTableAdapter.GetDataByParams((int)ourRow["UserID"], (int)ourRow["NoticeID"], (string)ourRow["NoticeDate"]);
                case "UserPasswordConstructionRules"    : return userPasswordConstructionRulesTableAdapter.GetDataByParams((int)ourRow["UserID"], (int)ourRow["RuleID"], (int?)ourRow["RulesOrder"]);
                case "TmpUserPasswordConstructionRules" : return tmpUserPasswordConstructionRulesTableAdapter.GetDataByParams((int)ourRow["UserID"], (int)ourRow["RuleID"], (int?)ourRow["RulesOrder"]);
                case "UserPermissions"                  : return userPermissionsTableAdapter.GetDataByID((int)ourRow["UserID"], (int)ourRow["PermissionID"]);
                case "Users"                            : return usersTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "UserGroupUsers"                   : return userGroupUsersTableAdapter.GetDataByID((int)ourRow["UserID"], (int)ourRow["GroupID"]);
                case "UserGroupAuthSystems"             : return userGroupAuthSystemsTableAdapter.GetDataByID((int)ourRow["GroupID"], (int)ourRow["AuthSystemID"]);
                case "UserGroupEducation"               : return userGroupEducationTableAdapter.GetDataByID((int)ourRow["GroupID"], (int)ourRow["EduCategID"]);
                case "UserGroupNotifications"           : return userGroupNotificationsTableAdapter.GetDataByID((int)ourRow["GroupID"], (int)ourRow["NoticeID"]);
                case "UserGroupPermissions"             : return userGroupPermissionsTableAdapter.GetDataByID((int)ourRow["GroupID"], (int)ourRow["PermissionID"]);
                case "ControlledPrograms"               : return controlledProgramsTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "ScheduleActions"                  : return scheduleActionsTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "ScheduleFunctions"                : return scheduleFunctionsTableAdapter.GetDataByID((int)ourRow["ID"]);
                case "Schedule"                         : return scheduleTableAdapter.GetDataByID((int)ourRow["ID"]);
            }

            return null;
        }

        /// <summary>
        /// Get data table by table name
        /// </summary>
        /// <param name="tableName">table name</param>
        /// <returns>data table instance</returns>
        private DataTable GetDataTableByName(string tableName)
        {
            switch (tableName)
            {
                case "AuthSystems"                      : return dataSet.AuthSystems;
                case "Computers"                        : return dataSet.Computers;
                case "EducationAnswers"                 : return dataSet.EducationAnswers;
                case "EducationCategories"              : return dataSet.EducationCategories;
                case "EducationLessons"                 : return dataSet.EducationLessons;
                case "EducationQuestionAnswers"         : return dataSet.EducationQuestionAnswers;
                case "EducationQuestions"               : return dataSet.EducationQuestions;
                case "License"                          : return dataSet.License;
                case "Notifications"                    : return dataSet.Notifications;
                case "OSTypes"                          : return dataSet.OSTypes;
                case "Preset"                           : return dataSet.Preset;
                case "PresetDetails"                    : return dataSet.PresetDetails;
                case "PresetHookup"                     : return dataSet.PresetHookup;
                case "ScreenObjectListValues"           : return dataSet.ScreenObjectListValues;
                case "ScreenObjects"                    : return dataSet.ScreenObjects;
                case "Screens"                          : return dataSet.Screens;
                case "ScreenPresetDetails"              : return dataSet.ScreensPresetDetails;
                case "UserAccounts"                     : return dataSet.UserAccounts;
                case "UserAccountsArchive"              : return dataSet.UserAccountsArchive;
                case "UserCheckValues"                  : return dataSet.UserCheckValues;
                case "UserEducation"                    : return dataSet.UserEducation;
                case "UserEducationAnswers"             : return dataSet.UserEducationAnswers;
                case "UserNotifications"                : return dataSet.UserNotifications;
                case "UserNotificationsHistory"         : return dataSet.UserNotificationsHistory;
                case "UserPasswordConstructionRules"    : return dataSet.UserPasswordConstructionRules;
                case "TmpUserPasswordConstructionRules" : return dataSet.TmpUserPasswordConstructionRules;
                case "UserPermissions"                  : return dataSet.UserPermissions;
                case "Users"                            : return dataSet.Users;
                case "UserGroupUsers"                   : return dataSet.UserGroupUsers;
                case "UserGroupAuthSystems"             : return dataSet.UserGroupAuthSystems;
                case "UserGroupEducation"               : return dataSet.UserGroupEducation;
                case "UserGroupNotifications"           : return dataSet.UserGroupNotifications;
                case "UserGroupPermissions"             : return dataSet.UserGroupPermissions;
                case "ControlledPrograms"               : return dataSet.ControlledPrograms;
                case "ScheduleActions"                  : return dataSet.ScheduleActions;
                case "ScheduleFunctions"                : return dataSet.ScheduleFunctions;
                case "Schedule"                         : return dataSet.Schedule;
            }

            return null;
        }

        /// <summary>
        /// Get concurrency exception row
        /// from DB
        /// </summary>
        /// <param name="dt">Data table instance</param>
        /// <returns>data row instance</returns>
        private DataRow GetCurrentRowInDB(DataTable dt)
        {
            if ((dt == null) || (dt.Rows.Count == 0))
                return null;
            else
                return dt.Rows[0];
        }

        /// <summary>
        /// Processing of DB update concurrency violation
        /// </summary>
        /// <param name="ourRow">our concurrency exception data row</param>
        /// <param name="dbRow">DB concurrency exception data row</param>
        /// <param name="dt">concurrency exception data table</param>
        private void HandleDbUpdate(DataRow ourRow, DataRow dbRow, DataTable dt)
        {
            DataTable currTable = GetDataTableByName(ourRow.Table.TableName);

            if (currTable != null)
            {
                string msg = "While you are editing, the corresponding record in the database has been updated! Do you want to update the database with the values that you are proposing?";

                DialogResult response = MessageBox.Show(msg, "Concurrency Exception", MessageBoxButtons.YesNo, MessageBoxIcon.Error);

                switch (response)
                {
                    case DialogResult.Yes:
                        currTable.Merge(dt, true);
                        Update(currTable.TableName);
                        break;

                    case DialogResult.No:
                        currTable.Merge(dt, false);
                        break;
                }
            }
        }

        /// <summary>
        /// Processing of DB delete concurrency violation
        /// </summary>
        /// <param name="ourRow">our concurrency exception data row</param>
        private void HandleDbDeletion(DataRow ourRow)
        {
            DataTable currTable = GetDataTableByName(ourRow.Table.TableName);

            if (currTable != null)
            {
                string msg = "While you are editing, the corresponding record in the database has been deleted! Do you want to re-insert the data record with the values that you are proposing?";

                DialogResult response = MessageBox.Show(msg, "Concurrency Exception", MessageBoxButtons.YesNo, MessageBoxIcon.Error);

                switch (response)
                {
                    case DialogResult.Yes:
                        AddDuplicateRow(ourRow);
                        Update(currTable.TableName);
                        break;

                    case DialogResult.No:
                        ourRow.Delete();
                        ourRow.AcceptChanges();
                        break;
                }
            }
        }

        /// <summary>
        /// Create duplicate of data row and 
        /// ADD it to the data table
        /// </summary>
        /// <param name="ourRow">our concurrency exception data row</param>
        private void AddDuplicateRow(DataRow ourRow)
        {
            DataTable currTable = GetDataTableByName(ourRow.Table.TableName);

            if (currTable != null)
            {
                DataRow newRow = currTable.NewRow();
               
                newRow.ItemArray = ourRow.ItemArray;
                ourRow.Delete();
                ourRow.AcceptChanges();

                currTable.Rows.Add(newRow);
            }
        }

        #endregion
        
        #region Constructor
        
        /// <summary>
        /// Database manager constructor
        /// </summary>
        /// <param name="conStr">connection string</param>
        public DataBaseManager(string conStr, LogWriter logWriter)
        {
            this.logWriter = logWriter;

            connectionString = conStr;

            // NovaTend database data set instance
            dataSet = null;

            // SQL connection instance
            connection = null;

            // Table adapters manager
            tableAdapterManager = null;

            // Authentication systems table
            authSystemsTableAdapter = null;
            authSystemsBindingSource = null;
            authSystemTypesTableAdapter = null;
            authSystemTypesBindingSource = null;
            authSystemsSynchronizeBindingSource = null;

            // Users table
            usersTableAdapter = null;
            usersBindingSource = null;
            fkUserPasswordConstructionRulesUsersBindingSource = null;
            fkUserCheckValuesUsersBindingSource = null;
            
            // User groups
            userGroupsTableAdapter = null;
            userGroupsTableAdapter = null;
            userGroupsBindingSource = null;
            userGroupUsersTableAdapter = null;
            userGroupUsersBindingSource = null;
            fkUserGroupsUsersBindingSource = null;

            //User personal data
            personalUsersBindingSource = null;
            fkPersonalUserPasswordConstructionRulesUsersBindingSource = null;
            fkPersonalUserCheckValuesUsersBindingSource = null;
            fkPersonalUserAccountsUsersBindingSource = null;
            fkPersonalUserPermissionsUsersBindingSource = null;
            personalPermissionsBindingSource = null;
            personalUserAccountAuthSystemsBindingSource = null;
            personalUserCheckValuesScreenObjectsBindingSource = null;

            // User accounts table
            userAccountsTableAdapter = null;
            userAccountsBindingSource = null;
            userAccountsArchiveTableAdapter = null;
            userAccountsArchiveBindingSource = null;
            fkUserAccountsUsersBindingSource = null;
            userAccontsAuthSystemsBindingSource = null;
            userAccountActionsOnDeleteTableAdapter = null;
            userAccountActionsOnDeleteBindingSource = null;
            userAccountActionsOnInsertTableAdapter = null;
            userAccountActionsOnInsertBindingSource = null;
            userAccountActionsOnUpdateTableAdapter = null;
            userAccountActionsOnUpdateBindingSource = null;
            userAccountsArchiveUsersBindingSource = null;
            fkUserAccountsArchiveUsersBindingSource = null;
            userAccontsArchiveAuthSystemsBindingSource = null;

            // Computers table
            computersTableAdapter = null;
            computersBindingSource = null;

            // Preset table
            presetTableAdapter = null;
            presetBindingSource = null;
            presetScreensBindingSource = null;

            // Preset details table
            presetDetailsTableAdapter = null;
            presetDetailsBindingSource = null;
            screensPresetDetailsTableAdapter = null;
            screensPresetDetailsBindingSource = null;
            fkScreensPresetDetailsPresetBindingSource = null;
            presetDetailsScreenObjectsBindingSource = null;
            fkPresetDetailsScreensPresetDetailsBindingSource = null;
            fkPresetDetailsScreensScreenObjectsBindingSource = null;
            fkPresetDetailsPresetBindingSource = null;
            presetDetailsScreensBindingSource = null;

            // Preset hookup
            presetHookupTableAdapter = null;
            presetHookupBindingSource = null;
            presetHookupPresetsBindingSource = null;
            presetHookupUsersBindingSource = null;
            presetHookupComputersBindingSource = null;
            presetHookupOSTypesBindingSource = null;
            fkPresetHookupPresetBindingSource = null;

            // Screen objects table
            screensTableAdapter = null;
            screensBindingSource = null;
            screenObjectsTableAdapter = null;
            screenObjectsBindingSource = null;
            fkScreenObjectsScreenObjectsBindingSource = null;
            fkScreensScreenObjectsBindingSource = null;
            fkScreenObjectListValuesScreenObjectsBindingSource = null;

            // Screen objects types table
            screenObjectsTypesTableAdapter = null;
            screenObjectsTypesBindingSource = null;
            screenTypesTableAdapter = null;
            screenTypesBindingSource = null;

            // Screen object scopes table
            screenObjectScopesTableAdapter = null;
            screenObjectScopesScreensBindingSource = null;
            screenObjectScopesScreenObjectsBindingSource = null;

            // Screen object list values table
            screenObjectListValuesTableAdapter = null;
            screenObjectListValuesBindingSource = null;

            // User check values table
            userCheckValuesTableAdapter = null;
            userCheckValuesBindingSource = null;
            userCheckValuesScreenObjectsTableAdapter = null;
            userCheckValuesScreenObjectsBindingSource = null;

            // Password construction rules table
            passwordConstructionRulesTableAdapter = null;
            passwordConstructionRulesBindingSource = null;

            // Password construction rules types table
            passwordConstructionRulesTypesTableAdapter = null;
            passwordConstructionRulesTypesBindingSource = null;

            // User password construction rules table
            userPasswordConstructionRulesTableAdapter = null;
            userPasswordConstructionRulesBindingSource = null;
            tmpUserPasswordConstructionRulesTableAdapter = null;
            tmpUserPasswordConstructionRulesBindingSource = null;

            // Education lessons table
            educationLessonsTableAdapter = null;
            educationLessonsBindingSource = null;
            fkEducationLessonsEducationCategoriesBindingSource = null;

            // Education categories table
            educationCategoriesTableAdapter = null;
            educationCategoriesBindingSource = null;

            // Education answers table
            educationAnswersTableAdapter = null;
            educationAnswersBindingSource = null;

            // Education questions table
            educationQuestionsTableAdapter = null;
            educationQuestionsBindingSource = null;
            fkEducationQuestionsEducationLessonsBindingSource = null;
            fkEducationQuestionAnswersEducationQuestionsBindingSource = null;
            rightQuestionAnswerBindingSource = null;
            questionAnswerBindingSource = null;
        
            // Education question answers table
            educationQuestionAnswersTableAdapter = null;
            educationQuestionAnswersBindingSource = null;

            // Users education table
            userEducationTableAdapter = null;
            userEducationBindingSource = null;
            userEducationUsersBindingSource = null;
            userEducationCategoriesBindingSource = null;
            fkUserEducationUsersBindingSource = null;

            // Users education answers table
            userEducationAnswersTableAdapter = null;
            userEducationAnswersBindingSource = null;
            fkUserEducationAnswersUsersBindingSource = null;
            userEducationAnswersQuestionsBindingSource = null;
            userEducationAnswersAnswersBindingSource = null;

            // Notification table
            notificationsTableAdapter = null;
            notificationsBindingSource = null;
        
            // Notification display types table
            notificationDisplayTypesTableAdapter = null;
            notificationDisplayTypesBindingSource = null;

            // Notification scopes table
            notificationScopesTableAdapter = null;
            notificationScopesBindingSource = null;

            // Notification types table
            notificationTypesTableAdapter = null;
            notificationTypesBindingSource = null;

            // User notification table
            userNotificationsTableAdapter = null;
            userNotificationsBindingSource = null;
            notificationsUsersBindingSource = null;
            userNotificationNoticesBindingSource = null;
            userNotificationDisplayTypesBindingSource = null;
            fkUserNotificationsUsersBindingSource = null;

            // User notification history table
            userNotificationsHistoryTableAdapter = null;
            userNotificationsHistoryBindingSource = null;
            fkUserNotificationsHistoryUsersBindingSource = null;
            userNotificationHistoryNoticesBindingSource = null;

            // License table
            licenseTableAdapter = null;
            licenseBindingSource = null;

            // OS types table
            osTypesTableAdapter = null;
            osTypesBindingSource = null;
            osPresetsBindingSource = null;

            // Permissions table
            permissionsTableAdapter = null;
            permissionsBindingSource = null;

            // User permissions table
            userPermissionsTableAdapter = null;
            userPermissionsBindingSource = null;
            fkUserPermissionsUsersBindingSource = null;        

        }

        #endregion

        #region User accounts archive
        
        /// <summary>
        /// Put user account to archive
        /// </summary>
        /// <param name="uaDataRow">user account datarow</param>
        /// <returns>TRUE - if success</returns>
        public bool PutUserAccountToArchive(DataRow uaDataRow)
        {
            if (uaDataRow != null)
            {
                int userID = (int)uaDataRow["UserID", DataRowVersion.Original];
                int authSystemID = (int)uaDataRow["AuthSystemID", DataRowVersion.Original];
                byte[] userName = uaDataRow["UserName", DataRowVersion.Original] as byte[];
                byte[] userPassword = uaDataRow["Password", DataRowVersion.Original] as byte[];
                DateTime? lastSignInDate = uaDataRow["LastSignInDate", DataRowVersion.Original] as DateTime?;
                short? passThru = uaDataRow["PassThru", DataRowVersion.Original] as short?;

                try
                {
                    userAccountsArchiveTableAdapter.Insert(userID, authSystemID, userName, userPassword, lastSignInDate, passThru);
                }
                catch
                {
                    return false;
                }
                
                return true;
            }
            else
                return false;
        }

        /// <summary>
        /// Put user accounts to archive
        /// </summary>
        /// <param name="uaDataRow">user account data rows</param>
        /// <returns>TRUE - if success</returns>
        public bool PutUserAccountsToArchive(DataRow[] uaDataRows)
        {
            if (uaDataRows != null)
            {
                bool result = true;

                for (int i = 0; i < uaDataRows.Length; i++)
                    result = PutUserAccountToArchive(uaDataRows[i]);

                return result;
            }
            else
                return false;
        }

        /// <summary>
        /// Get user account from archive
        /// </summary>
        /// <param name="uaDataRow">user account data row</param>
        /// <returns>TRUE - if success</returns>
        public bool GetUserAccountFromArchive(DataRow uaDataRow)
        {
            if (uaDataRow != null)
            {
                int userID = (int)uaDataRow["UserID", DataRowVersion.Original];
                int authSystemID = (int)uaDataRow["AuthSystemID", DataRowVersion.Original];
                byte[] userName = uaDataRow["UserName", DataRowVersion.Original] as byte[];
                byte[] userPassword = uaDataRow["Password", DataRowVersion.Original] as byte[];
                DateTime? lastSignInDate = uaDataRow["LastSignInDate", DataRowVersion.Original] as DateTime?;
                short? passThru = uaDataRow["PassThru", DataRowVersion.Original] as short?;

                try
                {
                    userAccountsTableAdapter.Insert(userID, authSystemID, userName, userPassword, lastSignInDate, passThru);
                    userAccountsArchiveTableAdapter.Delete(userID, authSystemID, userName, userPassword, lastSignInDate, passThru);
                }
                catch
                {
                    return false;
                }

                return true;
            }
            else
                return false;

        }

        #endregion

        #region Import

        /// <summary>
        /// Import education categories
        /// </summary>
        /// <param name="eduCategNamesList">list of education categories names</param>
        /// <returns>TRUE - if success</returns>
        public bool ImportEduCategories(List<string> eduCategNamesList)
        {
            if ((eduCategNamesList != null) && (eduCategNamesList.Count > 0))
            {
                try
                {
                    for (int i = 0; i < eduCategNamesList.Count; i++)
                        educationCategoriesTableAdapter.Insert(eduCategNamesList[i]);

                    educationCategoriesTableAdapter.Fill(dataSet.EducationCategories);
                    return true;
                }
                catch
                {
                    return false;
                }
            }
            else
                return false;
        }

        /// <summary>
        /// Import education lessons
        /// </summary>
        /// <param name="eduLessonsList">lessons list</param>
        /// <returns>TRUE - if success</returns>
        public bool ImportEduLessons(List<ExternEduDataExtractor.TextAndImageValue> eduLessonsList)
        {
            if ((eduLessonsList != null) && (eduLessonsList.Count > 0))
            {
                try
                {
                    int ? categID = (int ?)((importEduCategoriesBindingSource.Current as DataRowView).Row["ID"]);

                    for (int i = 0; i < eduLessonsList.Count; i++)
                        educationLessonsTableAdapter.Insert(categID, eduLessonsList[i].text, eduLessonsList[i].image, i + 1);

                    educationLessonsTableAdapter.Fill(dataSet.EducationLessons);
                    return true;
                }
                catch
                {
                    return false;
                }
            }
            else
                return false;
        }

        /// <summary>
        /// Import education questions
        /// </summary>
        /// <param name="eduQuestList">questions list</param>
        /// <returns>TRUE - if success</returns>
        public bool ImportEduQuestions(List<string> eduQuestList)
        {
            if ((eduQuestList != null) && (eduQuestList.Count > 0))
            {
                try
                {
                    int? lessonID = (int?)((importEduLessonsBindingSource.Current as DataRowView).Row["ID"]);
                    int? rightAnswerID = (int?)((importEduAnswersBindingSource.Current as DataRowView).Row["ID"]);

                    for (int i = 0; i < eduQuestList.Count; i++)
                        educationQuestionsTableAdapter.Insert(lessonID, eduQuestList[i], rightAnswerID, i + 1);

                    educationQuestionsTableAdapter.Fill(dataSet.EducationQuestions);
                    return true;
                }
                catch
                {
                    return false;
                }
            }
            else
                return false;
        }

        /// <summary>
        /// Import education answers
        /// </summary>
        /// <param name="eduAnswersList">answers list</param>
        /// <returns>TRUE - if success</returns>
        public bool ImportEduAnswers(List<string> eduAnswersList)
        {
            if ((eduAnswersList != null) && (eduAnswersList.Count > 0))
            {
                try
                {
                    int questID = (int)((importEduQuestionsBindingSource.Current as DataRowView).Row["ID"]);

                    for (int i = 0; i < eduAnswersList.Count; i++)
                    {
                        educationAnswersTableAdapter.Insert(eduAnswersList[i]);

                        string filterString = "AnswerText  = " + eduAnswersList[i];
                        DataRow[] ansRows = dataSet.EducationAnswers.Select(filterString);
                        int answerID = (int)ansRows[0]["ID", DataRowVersion.Original];

                        educationQuestionAnswersTableAdapter.Insert(questID, answerID, i + 1);
                    }

                    educationAnswersTableAdapter.Fill(dataSet.EducationAnswers);
                    educationQuestionAnswersTableAdapter.Fill(dataSet.EducationQuestionAnswers);
                    return true;
                }
                catch
                {
                    return false;
                }
            }
            else
                return false;
        }

        #endregion

        #region LOG

        // Log writer instance
        private LogWriter _logWriter;

        // Log writer property
        public LogWriter logWriter
        {
            get
            {
                return _logWriter;
            }

            set
            {
                _logWriter = value;
            }
        }


        /// <summary>
        /// Get authentication system name
        /// </summary>
        /// <param name="uaDataRow">Data row of user account</param>
        /// <returns>Authentication system name</returns>
        private string GetAuthSystemName(int authSystemID, DataRowVersion version)
        {
            try
            {
                DataRow[] authSysRows = dataSet.AuthSystems.Select("ID = " + authSystemID.ToString());
                if ((authSysRows != null) && (authSysRows.Length > 0))
                {
                    return authSysRows[0]["Name", version] as string;
                }
                else
                    return String.Empty;
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of user account to log-file
        /// </summary>
        public void WriteToLogUserAccounts()
        {
            DataRow[] delRows = dataSet.UserAccounts.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserAccounts.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserAccounts.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserAccounts.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Data base manager --> To the user accounts was added record: [Authentication system: {0}, User name: {1}, Password: {2}, Password through: {3}, Date of last logon: {4}]",
                            GetAuthSystemName((int)addRow["AuthSystemID", DataRowVersion.Current], DataRowVersion.Current),
                            encryptor.DecryptString(addRow["UserName", DataRowVersion.Current] as byte[]),
                            new String('*', encryptor.DecryptString(addRow["Password", DataRowVersion.Current] as byte[]).Length),
                            (addRow["PassThru", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            addRow["LastSignInDate", DataRowVersion.Current] as DateTime?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Data base manager --> From user accounts was deleted record: [UserID: '{0}'; Authentication system: '{1}']", 
                        encryptor.DecryptString(delRow["UserName", DataRowVersion.Original] as byte[]),
                        GetAuthSystemName((int)delRow["AuthSystemID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Data base manager --> Record of user account '{0}' was modified!", encryptor.DecryptString(updOrigRow["UserName", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);

                    message = String.Format("User account values before editing: [Authentication system: {0}, User name: {1}, Password: {2}, Password through: {3}, Date of last logon: {4}]",
                        GetAuthSystemName((int)updOrigRow["AuthSystemID", DataRowVersion.Original], DataRowVersion.Original),
                        encryptor.DecryptString(updOrigRow["UserName", DataRowVersion.Original] as byte[]),
                        new String('*', encryptor.DecryptString(updOrigRow["Password", DataRowVersion.Original] as byte[]).Length),
                        (updOrigRow["PassThru", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                        updOrigRow["LastSignInDate", DataRowVersion.Original] as DateTime?);
                    logWriter.WriteToLog(message);

                    message = String.Format("User account values after editing: [Authentication system: {0}, User name: {1}, Password: {2}, Password through: {3}, Date of last logon: {4}]",
                        GetAuthSystemName((int)updCurrRow["AuthSystemID", DataRowVersion.Current], DataRowVersion.Current),
                        encryptor.DecryptString(updCurrRow["UserName", DataRowVersion.Current] as byte[]),
                        new String('*', encryptor.DecryptString(updCurrRow["Password", DataRowVersion.Current] as byte[]).Length),
                        (updCurrRow["PassThru", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                        updCurrRow["LastSignInDate", DataRowVersion.Current] as DateTime?);
                    logWriter.WriteToLog(message);

                }
            }

        }

        /// <summary>
        /// Write changes of user account archive to log-file
        /// </summary>
        public void WriteToLogUserAccountsArchive()
        {
            DataRow[] delRows = dataSet.UserAccountsArchive.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserAccountsArchive.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserAccountsArchive.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserAccountsArchive.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the user accounts archive was added record: [Authentication system: {0}, User name: {1}, Password: {2}, Password through: {3}, Date of last logon: {4}]",
                            GetAuthSystemName((int)addRow["AuthSystemID", DataRowVersion.Current], DataRowVersion.Current),
                            encryptor.DecryptString(addRow["UserName", DataRowVersion.Current] as byte[]),
                            new String('*', encryptor.DecryptString(addRow["Password", DataRowVersion.Current] as byte[]).Length),
                            (addRow["PassThru", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            addRow["LastSignInDate", DataRowVersion.Current] as DateTime?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From user accounts archive was deleted record: [UserID: '{0}'; Authentication system: '{1}']", 
                        encryptor.DecryptString(delRow["UserName", DataRowVersion.Original] as byte[]),
                        GetAuthSystemName((int)delRow["AuthSystemID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }

            
            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++ )
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Data base manager --> Archive record of user account '{0}' was modified!", encryptor.DecryptString(updOrigRow["UserName", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);
                    
                    message = String.Format("User account values before editing: [Authentication system: {0}, User name: {1}, Password: {2}, Password through: {3}, Date of last logon: {4}]",
                        GetAuthSystemName((int)updOrigRow["AuthSystemID", DataRowVersion.Original], DataRowVersion.Original),
                        encryptor.DecryptString(updOrigRow["UserName", DataRowVersion.Original] as byte[]),
                        new String('*', encryptor.DecryptString(updOrigRow["Password", DataRowVersion.Original] as byte[]).Length),
                        (updOrigRow["PassThru", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                        updOrigRow["LastSignInDate", DataRowVersion.Original] as DateTime?);
                    logWriter.WriteToLog(message);

                    message = String.Format("User account values after editing: [Authentication system: {0}, User name: {1}, Password: {2}, Password through: {3}, Date of last logon: {4}]",
                        GetAuthSystemName((int)updCurrRow["AuthSystemID", DataRowVersion.Current], DataRowVersion.Current),
                        encryptor.DecryptString(updCurrRow["UserName", DataRowVersion.Current] as byte[]),
                        new String('*', encryptor.DecryptString(updCurrRow["Password", DataRowVersion.Current] as byte[]).Length),
                        (updCurrRow["PassThru", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                        updCurrRow["LastSignInDate", DataRowVersion.Current] as DateTime?);
                    logWriter.WriteToLog(message);

                }
            }
            
        }


        /// <summary>
        /// Get preset name
        /// </summary>
        /// <param name="presetID">Preset ID</param>
        /// <returns>Preset name</returns>
        private string GetPresetName(int ? presetID, DataRowVersion version)
        {
            try
            {
                if (presetID == null) return "No preset";

                DataRow[] presetRows = dataSet.Preset.Select("ID = " + presetID.ToString());
                if ((presetRows != null) && (presetRows.Length > 0))
                {
                    return presetRows[0]["Name", version] as string;
                }
                else
                    return "No preset";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get password type name
        /// </summary>
        /// <param name="passwordTypeID">password type ID</param>
        /// <returns>Password type name</returns>
        private string GetPasswordTypeName(int? passwordTypeID, DataRowVersion version)
        {
            try
            {
                if (passwordTypeID == null) return "Unknown";

                DataRow[] pwdRows = dataSet.PasswordConstructionRulesTypes.Select("ID = " + passwordTypeID.ToString());
                if ((pwdRows != null) && (pwdRows.Length > 0))
                {
                    return encryptor.DecryptString(pwdRows[0]["Name", version] as byte[]);
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of users to log-file
        /// </summary>
        public void WriteToLogUsers()
        {
            DataRow[] delRows = dataSet.Users.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.Users.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.Users.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.Users.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the Users was added record: [Name: {0}, User name: {1}, Password attempts count: {2}, Max password attempts count: {3}, Password type : {4}, Education program: {5}, Random education category: {6}, Last sign in date: {7}, Email: {8}, Phone number: {9}, Password reset by email: {10}, Password reset by SMS: {11}, Password reseted: {12}, Password reset date: {13}, Password reset period: {14}, Locked: {15}]",
                            encryptor.DecryptString(addRow["Name", DataRowVersion.Current] as byte[]),
                            encryptor.DecryptString(addRow["UserName", DataRowVersion.Current] as byte[]),
                            addRow["PwdAttemptsCount", DataRowVersion.Current] as int?,
                            addRow["MaxPwdAttemptsCount", DataRowVersion.Current] as int?,
                            GetPasswordTypeName(addRow["PwdTypeID", DataRowVersion.Current] as int?, DataRowVersion.Current),
                            (addRow["NeedStudy", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            (addRow["RandomEduCateg", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            addRow["LastSignInDate", DataRowVersion.Current] as DateTime?,
                            encryptor.DecryptString(addRow["Email", DataRowVersion.Current] as byte[]),
                            encryptor.DecryptString(addRow["Phone", DataRowVersion.Current] as byte[]),
                            (addRow["EmailPwdReset", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            (addRow["SmsPwdReset", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            (addRow["PwdResetted", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            addRow["PwdResetDate", DataRowVersion.Current] as DateTime?,
                            addRow["PwdResetPeriod", DataRowVersion.Current] as int?,
                            (addRow["Locked", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO");
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From DB was deleted user '{0}'", encryptor.DecryptString(delRow["Name", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> User '{0}' was modified!", encryptor.DecryptString(updOrigRow["Name", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);

                    message = String.Format("User personal data before editing: [Name: {0}, User name: {1}, Password attempts count: {2}, Max password attempts count: {3}, Password type : {4}, Education program: {5}, Random education category: {6}, Last sign in date: {7}, Email: {8}, Phone number: {9}, Password reset by email: {10}, Password reset by SMS: {11}, Password reseted: {12}, Password reset date: {13}, Password reset period: {14}, Locked: {15}]",
                            encryptor.DecryptString(updOrigRow["Name", DataRowVersion.Original] as byte[]),
                            encryptor.DecryptString(updOrigRow["UserName", DataRowVersion.Original] as byte[]),
                            updOrigRow["PwdAttemptsCount", DataRowVersion.Original] as int?,
                            updOrigRow["MaxPwdAttemptsCount", DataRowVersion.Original] as int?,
                            GetPasswordTypeName(updOrigRow["PwdTypeID", DataRowVersion.Original] as int?, DataRowVersion.Original),
                            (updOrigRow["NeedStudy", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                            (updOrigRow["RandomEduCateg", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                            updOrigRow["LastSignInDate", DataRowVersion.Original] as DateTime?,
                            encryptor.DecryptString(updOrigRow["Email", DataRowVersion.Original] as byte[]),
                            encryptor.DecryptString(updOrigRow["Phone", DataRowVersion.Original] as byte[]),
                            (updOrigRow["EmailPwdReset", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                            (updOrigRow["SmsPwdReset", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                            (updOrigRow["PwdResetted", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                            updOrigRow["PwdResetDate", DataRowVersion.Original] as DateTime?,
                            updOrigRow["PwdResetPeriod", DataRowVersion.Original] as int?,
                            (updOrigRow["Locked", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO");

                    logWriter.WriteToLog(message);

                    message = String.Format("User personal data after editing: [Name: {0}, User name: {1}, Password attempts count: {2}, Max password attempts count: {3}, Password type : {4}, Education program: {5}, Random education category: {6}, Last sign in date: {7}, Email: {8}, Phone number: {9}, Password reset by email: {10}, Password reset by SMS: {11}, Password reseted: {12}, Password reset date: {13}, Password reset period: {14}, Locked: {15}]",
                            encryptor.DecryptString(updCurrRow["Name", DataRowVersion.Current] as byte[]),
                            encryptor.DecryptString(updCurrRow["UserName", DataRowVersion.Current] as byte[]),
                            updCurrRow["PwdAttemptsCount", DataRowVersion.Current] as int?,
                            updCurrRow["MaxPwdAttemptsCount", DataRowVersion.Current] as int?,
                            GetPasswordTypeName(updCurrRow["PwdTypeID", DataRowVersion.Original] as int?, DataRowVersion.Current),
                            (updCurrRow["NeedStudy", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            (updCurrRow["RandomEduCateg", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            updCurrRow["LastSignInDate", DataRowVersion.Current] as DateTime?,
                            encryptor.DecryptString(updCurrRow["Email", DataRowVersion.Current] as byte[]),
                            encryptor.DecryptString(updCurrRow["Phone", DataRowVersion.Current] as byte[]),
                            (updCurrRow["EmailPwdReset", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            (updCurrRow["SmsPwdReset", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            (updCurrRow["PwdResetted", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                            updCurrRow["PwdResetDate", DataRowVersion.Current] as DateTime?,
                            updCurrRow["PwdResetPeriod", DataRowVersion.Current] as int?,
                            (updCurrRow["Locked", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO");
                    logWriter.WriteToLog(message);

                }
            }
        }

        /// <summary>
        /// Get user name
        /// </summary>
        /// <param name="userID">user ID</param>
        /// <returns>User name</returns>
        private string GetUserName(int userID, DataRowVersion version)
        {
            try
            {
                DataRow[] userRows = dataSet.Users.Select("ID = " + userID.ToString());
                if ((userRows != null) && (userRows.Length > 0))
                {
                    return encryptor.DecryptString(userRows[0]["Name", version] as byte[]);
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get user group name
        /// </summary>
        /// <param name="groupID">group ID</param>
        /// <returns>Group name</returns>
        private string GetUserGroupName(int groupID, DataRowVersion version)
        {
            try
            {
                DataRow[] groupRows = dataSet.UserGroups.Select("ID = " + groupID.ToString());
                if ((groupRows != null) && (groupRows.Length > 0))
                {
                    return encryptor.DecryptString(groupRows[0]["Name", version] as byte[]);
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get permission name
        /// </summary>
        /// <param name="permissionID">Permission ID</param>
        /// <returns>Permission name</returns>
        private string GetPermissionName(int permissionID, DataRowVersion version)
        {
            try
            {
                DataRow[] permRows = dataSet.Permissions.Select("ID = " + permissionID.ToString());
                if ((permRows != null) && (permRows.Length > 0))
                {
                    return encryptor.DecryptString(permRows[0]["Name", version] as byte[]);
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of user groups to log-file
        /// </summary>
        public void WriteToLogUserGroups()
        {
            DataRow[] delRows = dataSet.UserGroups.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserGroups.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserGroups.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserGroups.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> Added new user group '{0}'", GetUserGroupName((int)addRow["ID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> The user group '{0}' was removed", GetUserGroupName((int)delRow["ID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> User group '{0}' was modified!", GetUserGroupName((int)updOrigRow["ID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("User group before editing: '{0}'", GetUserGroupName((int)updOrigRow["ID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("User group after editing: '{0}'", GetUserGroupName((int)updCurrRow["ID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of user group users to log-file
        /// </summary>
        public void WriteToLogUserGroupUsers()
        {
            DataRow[] delRows = dataSet.UserGroupUsers.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserGroupUsers.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserGroupUsers.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserGroupUsers.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> The user '{0}' was added to group '{1}'",
                        GetUserName((int)addRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetUserGroupName((int)addRow["GroupID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> The user '{0}' was removed from group '{1}'",
                        GetUserName((int)delRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetUserGroupName((int)delRow["GroupID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Group of the user '{0}' was modified!", GetUserName((int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("User group before editing: '{0}'", GetUserGroupName((int)updOrigRow["GroupID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("User group after editing: '{0}'", GetUserGroupName((int)updCurrRow["GroupID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of user group auth systems to log-file
        /// </summary>
        public void WriteToLogUserGroupAuthSystems()
        {
            DataRow[] delRows = dataSet.UserGroupAuthSystems.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserGroupAuthSystems.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserGroupAuthSystems.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserGroupAuthSystems.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> Added reference between group '{0}' and auth system '{1}' group '{2}'. Group settings: '{3}'",
                        GetUserGroupName((int)addRow["GroupID", DataRowVersion.Current], DataRowVersion.Current),
                        GetAuthSystemName((int)addRow["AuthSystemID", DataRowVersion.Current], DataRowVersion.Current),
                        encryptor.DecryptString(addRow["GroupName", DataRowVersion.Current] as byte[]),
                        encryptor.DecryptString(addRow["GroupSettings", DataRowVersion.Current] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> Removed reference between group '{0}' and auth system '{1}' group '{2}'. Group settings: '{3}'",
                        GetUserGroupName((int)delRow["GroupID", DataRowVersion.Original], DataRowVersion.Original),
                        GetAuthSystemName((int)delRow["AuthSystemID", DataRowVersion.Original], DataRowVersion.Original),
                        encryptor.DecryptString(delRow["GroupName", DataRowVersion.Original] as byte[]),
                        encryptor.DecryptString(delRow["GroupSettings", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> References of user group '{0}' was modified!", GetUserGroupName((int)updOrigRow["GroupID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Before editing: Auth system '{0}' group {1}. Group settings: '{2}'", 
                        GetAuthSystemName((int)updOrigRow["AuthSystemID", DataRowVersion.Original], DataRowVersion.Original), 
                        encryptor.DecryptString(updOrigRow["GroupName", DataRowVersion.Original] as byte[]),
                        encryptor.DecryptString(updOrigRow["GroupSettings", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);

                    message = String.Format("After editing: Auth system '{0}' group {1}. Group settings: '{2}'", 
                        GetAuthSystemName((int)updCurrRow["AuthSystemID", DataRowVersion.Current], DataRowVersion.Current), 
                        encryptor.DecryptString(updCurrRow["GroupName", DataRowVersion.Current] as byte[]),
                        encryptor.DecryptString(updCurrRow["GroupSettings", DataRowVersion.Current] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of user group education to log-file
        /// </summary>
        public void WriteToLogUserGroupEducation()
        {
            DataRow[] delRows = dataSet.UserGroupEducation.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserGroupEducation.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserGroupEducation.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserGroupEducation.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> For the user group '{0}' was added education category '{1}'. (Random questions: {2}, Category order: {3})",
                        GetUserGroupName((int)addRow["GroupID", DataRowVersion.Current], DataRowVersion.Current),
                        GetEducationCategoryName((int)addRow["EduCategID", DataRowVersion.Current], DataRowVersion.Current),
                        (addRow["RandomQuestion", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                        addRow["EduCategOrder", DataRowVersion.Current] as int?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> For the user group '{0}' was removed education category '{1}'",
                        GetUserGroupName((int)delRow["GroupID", DataRowVersion.Original], DataRowVersion.Original),
                        GetEducationCategoryName((int)delRow["EduCategID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Education program of user group '{0}' was modified!", GetUserGroupName((int)updOrigRow["GroupID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Before editing: [Education category: '{0}', Random questions: {1}, Category order: {2}]",
                        GetEducationCategoryName((int)updOrigRow["EduCategID", DataRowVersion.Original], DataRowVersion.Original),
                        (updOrigRow["RandomQuestion", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                        updOrigRow["EduCategOrder", DataRowVersion.Original] as int?);
                    logWriter.WriteToLog(message);

                    message = String.Format("After editing: [Education category: '{0}', Random questions: {1}, Category order: {2}]",
                        GetEducationCategoryName((int)updCurrRow["EduCategID", DataRowVersion.Current], DataRowVersion.Current),
                        (updCurrRow["RandomQuestion", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                        updCurrRow["EduCategOrder", DataRowVersion.Current] as int?);

                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of user gruop notification to log-file
        /// </summary>
        public void WriteToLogUserGroupNotifications()
        {
            DataRow[] delRows = dataSet.UserGroupNotifications.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserGroupNotifications.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserGroupNotifications.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserGroupNotifications.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> For the user group '{0}' was added notification '{1}'. Display type: {2}",
                        GetUserGroupName((int)addRow["GroupID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNotificationText((int)addRow["NoticeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNoticeDisplayTypeName((int)addRow["DispTypeID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> For the user group '{0}' was removed notification '{1}'",
                        GetUserGroupName((int)delRow["GroupID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNotificationText((int)delRow["NoticeID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Notification list of user group '{0}' was modified!", GetUserGroupName((int)updOrigRow["GroupID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Before editing: [Notice: '{0}', Display type: {1}]",
                        GetNotificationText((int)updOrigRow["NoticeID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNoticeDisplayTypeName((int)updOrigRow["DispTypeID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("After editing: [Notice: '{0}', Display type: {1}]",
                        GetNotificationText((int)updCurrRow["NoticeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNoticeDisplayTypeName((int)updCurrRow["DispTypeID", DataRowVersion.Current], DataRowVersion.Current));

                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of user group permissions to log-file
        /// </summary>
        public void WriteToLogUserGroupPermissions()
        {
            DataRow[] delRows = dataSet.UserGroupPermissions.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserGroupPermissions.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserGroupPermissions.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserGroupPermissions.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> For the user group '{0}' was established permission '{1}'",
                        GetUserGroupName((int)addRow["GroupID", DataRowVersion.Current], DataRowVersion.Current),
                        GetPermissionName((int)addRow["PermissionID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> User group '{0}' lost permission '{1}'",
                        GetUserGroupName((int)delRow["GroupID", DataRowVersion.Original], DataRowVersion.Original),
                        GetPermissionName((int)delRow["PermissionID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Permission of the user group '{0}' was modified!", GetUserGroupName((int)updOrigRow["GroupID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("User permission before editing: '{0}'", GetPermissionName((int)updOrigRow["PermissionID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("User permission after editing: '{0}'", GetPermissionName((int)updCurrRow["PermissionID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }
        }
 
        /// <summary>
        /// Write changes of user permissions to log-file
        /// </summary>
        public void WriteToLogUserPermissions()
        {
            DataRow[] delRows = dataSet.UserPermissions.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserPermissions.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserPermissions.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserPermissions.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> For the user '{0}' was established permission '{1}'",
                        GetUserName((int)addRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetPermissionName((int)addRow["PermissionID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> User '{0}' lost permission '{1}'",
                        GetUserName((int)delRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetPermissionName((int)delRow["PermissionID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Permission of the user '{0}' was modified!", GetUserName((int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("User permission before editing: '{0}'", GetPermissionName((int)updOrigRow["PermissionID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("User permission after editing: '{0}'", GetPermissionName((int)updCurrRow["PermissionID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Get permission name
        /// </summary>
        /// <param name="permissionID">Permission ID</param>
        /// <returns>Permission name</returns>
        private string GetParameterForCheackingName(int paramID, DataRowVersion version)
        {
            try
            {
                DataRow[] paramRows = dataSet.UserCheckValuesScreenObjects.Select("ID = " + paramID.ToString());
                if ((paramRows != null) && (paramRows.Length > 0))
                {
                    return paramRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of user check values to log-file
        /// </summary>
        public void WriteToLogUserCheckValues()
        {
            DataRow[] delRows = dataSet.UserCheckValues.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserCheckValues.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserCheckValues.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserCheckValues.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> For the user '{0}' was established parameter for cheaking '{1}' with value '{2}'", 
                        GetUserName((int)addRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetParameterForCheackingName((int)addRow["ScreenObjectID", DataRowVersion.Current], DataRowVersion.Current),
                        encryptor.DecryptString(addRow["Value", DataRowVersion.Current] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> User '{0}' was deleted cheacking parameter: [Object: '{1}', Value: '{2}']",
                        GetUserName((int)delRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetParameterForCheackingName((int)delRow["ScreenObjectID", DataRowVersion.Original], DataRowVersion.Original),
                        encryptor.DecryptString(delRow["Value", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Parameter for cheacking of the user '{0}' was modified!", GetUserName((int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Parameter for checking before editing: [Object: '{1}', Value: '{2}']",
                        GetParameterForCheackingName((int)updOrigRow["ScreenObjectID", DataRowVersion.Original], DataRowVersion.Original),
                        encryptor.DecryptString(updOrigRow["Value", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);

                    message = String.Format("Parameter for checking after editing: [Object: '{1}', Value: '{2}']",
                        GetParameterForCheackingName((int)updCurrRow["ScreenObjectID", DataRowVersion.Current], DataRowVersion.Current),
                        encryptor.DecryptString(updCurrRow["Value", DataRowVersion.Current] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }
        }


        /// <summary>
        /// Write changes of computers to log-file
        /// </summary>
        public void WriteToLogComputers()
        {
            DataRow[] delRows = dataSet.Computers.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.Computers.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.Computers.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.Computers.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new computer record [Name: '{0}', Description:'{1}']", addRow["Name", DataRowVersion.Current] as string, addRow["Description", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed computer record [Name: '{0}', Description:'{1}']", delRow["Name", DataRowVersion.Original] as string, delRow["Description", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Information about computer '{0}' was modified!", updOrigRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Information about computer before editing: [Name: '{0}', Description:'{1}']", updOrigRow["Name", DataRowVersion.Original] as string, updOrigRow["Description", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Information about computer after editing: [Name: '{0}', Description:'{1}']", updCurrRow["Name", DataRowVersion.Current] as string, updCurrRow["Description", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of OS types to log-file
        /// </summary>
        public void WriteToLogOSTypes()
        {
            DataRow[] delRows = dataSet.OSTypes.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.OSTypes.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.OSTypes.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.OSTypes.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new OS types record [Name: '{0}']", addRow["Name", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed OS type record [Name: '{0}']", delRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Information OS type '{0}' was modified!", updOrigRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Information about OS type before editing: [Name: '{0}']", updOrigRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Information about OS type after editing: [Name: '{0}']", updCurrRow["Name", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Get authentiocation system type name
        /// <param name="permissionID">type ID</param>
        /// <returns>Authentiocation system type name</returns>
        private string GetAuthSystemTypeName(int typeID, DataRowVersion version)
        {
            try
            {
                DataRow[] authTypesRows = dataSet.AuthSystemTypes.Select("ID = " + typeID.ToString());
                if ((authTypesRows != null) && (authTypesRows.Length > 0))
                {
                    return authTypesRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get action name
        /// <param name="permissionID">action ID</param>
        /// <returns>Action name</returns>
        private string GetActionName(int actionID, DataRowVersion version)
        {
            try
            {
                DataRow[] actionRows = dataSet.UserAccountActionsOnDelete.Select("ID = " + actionID.ToString());
                if ((actionRows != null) && (actionRows.Length > 0))
                {
                    return actionRows[0]["Name", version] as string;
                }
                else
                {
                    actionRows = dataSet.UserAccountActionsOnInsert.Select("ID = " + actionID.ToString());
                    if ((actionRows != null) && (actionRows.Length > 0))
                    {
                        return actionRows[0]["Name", version] as string;
                    }
                    else
                    {
                        actionRows = dataSet.UserAccountActionsOnUpdate.Select("ID = " + actionID.ToString());
                        if ((actionRows != null) && (actionRows.Length > 0))
                        {
                            return actionRows[0]["Name", version] as string;
                        }
                        else
                            return "Unknown";
                    }
                }
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of authentication systems to log-file
        /// </summary>
        public void WriteToLogAuthSystems()
        {
            DataRow[] delRows = dataSet.AuthSystems.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.AuthSystems.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.AuthSystems.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.AuthSystems.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new Authentication System record [Name: '{0}', Type: '{1}', Settings string: hidden, Action on delete: {2}, Action on insert: {3}, Action on update: {4}, Move users in groups: {5}]", 
                        addRow["Name", DataRowVersion.Current] as string,
                        GetAuthSystemTypeName((int)addRow["AuthSystemTypeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetActionName((int)addRow["OnDeleteAction", DataRowVersion.Current], DataRowVersion.Current),
                        GetActionName((int)addRow["OnInsertAction", DataRowVersion.Current], DataRowVersion.Current),
                        GetActionName((int)addRow["OnUpdateAction", DataRowVersion.Current], DataRowVersion.Current),
                        (addRow["MoveGroupUsers", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO");
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> Authentication System '{0}' was removed from database", delRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Authentication System '{0}' was modified!", updOrigRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Information about Authentication System before editing: [Name: '{0}', Type: '{1}', Settings string: hidden, Action on delete: {2}, Action on insert: {3}, Action on update: {4}, Move users in groups: {5}]",
                        updOrigRow["Name", DataRowVersion.Original] as string,
                        GetAuthSystemTypeName((int)updOrigRow["AuthSystemTypeID", DataRowVersion.Original], DataRowVersion.Original),
                        GetActionName((int)updOrigRow["OnDeleteAction", DataRowVersion.Original], DataRowVersion.Original),
                        GetActionName((int)updOrigRow["OnInsertAction", DataRowVersion.Original], DataRowVersion.Original),
                        GetActionName((int)updOrigRow["OnUpdateAction", DataRowVersion.Original], DataRowVersion.Original),
                        (updOrigRow["MoveGroupUsers", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO");
                    logWriter.WriteToLog(message);

                    message = String.Format("Information about Authentication System before editing: [Name: '{0}', Type: '{1}', Settings strings: hidden, Action on delete: {2}, Action on insert: {3}, Action on update: {4}, Move users in groups: {5}]",
                        updCurrRow["Name", DataRowVersion.Current] as string,
                        GetAuthSystemTypeName((int)updCurrRow["AuthSystemTypeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetActionName((int)updCurrRow["OnDeleteAction", DataRowVersion.Current], DataRowVersion.Current),
                        GetActionName((int)updCurrRow["OnInsertAction", DataRowVersion.Current], DataRowVersion.Current),
                        GetActionName((int)updCurrRow["OnUpdateAction", DataRowVersion.Current], DataRowVersion.Current),
                        (updCurrRow["MoveGroupUsers", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO");
                    logWriter.WriteToLog(message);
                }
            }
        }


        /// <summary>
        /// Write changes of preset to log-file
        /// </summary>
        public void WriteToLogPresets()
        {
            DataRow[] delRows = dataSet.Preset.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.Preset.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.Preset.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.Preset.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new preset [Name: '{0}', Creation date: '{1}', Description: '{2}']",
                        addRow["Name", DataRowVersion.Current] as string,
                        addRow["Date", DataRowVersion.Current] as DateTime?,
                        addRow["Description", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> Preset '{0}' was removed from database", delRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Preset '{0}' was modified!", updOrigRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Information about preset before editing: [Name: '{0}', Creation date: '{1}', Description: '{2}']",
                        updOrigRow["Name", DataRowVersion.Original] as string,
                        updOrigRow["Date", DataRowVersion.Original] as DateTime?,
                        updOrigRow["Description", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Information about preset after editing: [Name: '{0}', Creation date: '{1}', Description: '{2}']",
                        updCurrRow["Name", DataRowVersion.Current] as string,
                        updCurrRow["Date", DataRowVersion.Current] as DateTime?,
                        updCurrRow["Description", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Get screen name
        /// </summary>
        /// <param name="scrID">screen ID</param>
        /// <param name="version">data row version</param>
        /// <returns>screen name</returns>
        private string GetScreenName(int scrID, DataRowVersion version)
        {
            try
            {
                DataRow[] scrRows = dataSet.Screens.Select("ID = " + scrID.ToString());
                if ((scrRows != null) && (scrRows.Length > 0))
                {
                    return scrRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get screen object name
        /// </summary>
        /// <param name="scrObjID">screen object ID</param>
        /// <param name="version">data row version</param>
        /// <returns>screen object name</returns>
        private string GetScreenObjectName(int scrObjID, DataRowVersion version)
        {
            try
            {
                DataRow[] scrRows = dataSet.ScreenObjects.Select("ID = " + scrObjID.ToString());
                if ((scrRows != null) && (scrRows.Length > 0))
                {
                    return scrRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get screen object scope name
        /// </summary>
        /// <param name="scrScopeID">scope ID</param>
        /// <param name="version">data row version</param>
        /// <returns>screen object scope name</returns>
        private string GetScreenObjectScopeName(int scrScopeID, DataRowVersion version)
        {
            try
            {
                DataRow[] scrRows = dataSet.ScreenObjectScopes.Select("ID = " + scrScopeID.ToString());
                if ((scrRows != null) && (scrRows.Length > 0))
                {
                    return scrRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of screens preset details to log-file
        /// </summary>
        public void WriteToLogScreensPresetDetails()
        {
            DataRow[] delRows = dataSet.ScreensPresetDetails.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.ScreensPresetDetails.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.ScreensPresetDetails.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.ScreensPresetDetails.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the preset '{0}' was added new screen '{1}' with scope '{2}'",
                        GetPresetName(addRow["PresetID", DataRowVersion.Current] as int?, DataRowVersion.Current),
                        GetScreenName((int)addRow["ScreenObjectID", DataRowVersion.Current], DataRowVersion.Current),
                        GetScreenObjectScopeName((int)addRow["ScreenObjectScopeID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> Screen '{0}' was removed from preset '{1}'",
                        GetScreenName((int)delRow["ScreenObjectID", DataRowVersion.Original], DataRowVersion.Original),
                        GetPresetName(delRow["PresetID", DataRowVersion.Original] as int?, DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Preset '{0}' was modified!", GetPresetName(updOrigRow["PresetID", DataRowVersion.Original] as int?, DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Preset screen before editing: [Name: '{0}', Scope: '{1}']",
                        GetScreenName((int)updOrigRow["ScreenObjectID", DataRowVersion.Original], DataRowVersion.Original),
                        GetScreenObjectScopeName((int)updOrigRow["ScreenObjectScopeID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Preset screen after editing: [Name: '{0}', Scope: '{1}']",
                        GetScreenName((int)updCurrRow["ScreenObjectID", DataRowVersion.Current], DataRowVersion.Current),
                        GetScreenObjectScopeName((int)updCurrRow["ScreenObjectScopeID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of preset details to log-file
        /// </summary>
        public void WriteToLogPresetDetails()
        {
            DataRow[] delRows = dataSet.PresetDetails.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.PresetDetails.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.PresetDetails.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.PresetDetails.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the preset '{0}' was added new screen object '{1}' with scope '{2}'",
                        GetPresetName(addRow["PresetID", DataRowVersion.Current] as int?, DataRowVersion.Current),
                        GetScreenObjectName((int)addRow["ScreenObjectID", DataRowVersion.Current], DataRowVersion.Current),
                        GetScreenObjectScopeName((int)addRow["ScreenObjectScopeID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> Screen object '{0}' was removed from the preset '{1}'",
                        GetScreenObjectName((int)delRow["ScreenObjectID", DataRowVersion.Original], DataRowVersion.Original),
                        GetPresetName(delRow["PresetID", DataRowVersion.Original] as int?, DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Preset '{0}' was modified!", GetPresetName(updOrigRow["PresetID", DataRowVersion.Original] as int?, DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Preset screen object before editing: [Name: '{0}', Order: '{1}', Scope: '{2}']",
                        GetScreenObjectName((int)updOrigRow["ScreenObjectID", DataRowVersion.Original], DataRowVersion.Original),
                        updOrigRow["ScreenObjectOrder", DataRowVersion.Original] as int?,
                        GetScreenObjectScopeName((int)updOrigRow["ScreenObjectScopeID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Preset screen object after editing: [Name: '{0}', Order: '{1}', Scope: '{2}']",
                        GetScreenObjectName((int)updCurrRow["ScreenObjectID", DataRowVersion.Current], DataRowVersion.Current),
                        updCurrRow["ScreenObjectOrder", DataRowVersion.Current] as int?,
                        GetScreenObjectScopeName((int)updCurrRow["ScreenObjectScopeID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Get computer name
        /// </summary>
        /// <param name="compID">user ID</param>
        /// <returns>Computer name</returns>
        private string GetComputerName(int compID, DataRowVersion version)
        {
            try
            {
                DataRow[] compRows = dataSet.Computers.Select("ID = " + compID.ToString());
                if ((compRows != null) && (compRows.Length > 0))
                {
                    return compRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get OS type name
        /// </summary>
        /// <param name="osTypeID">OS type ID</param>
        /// <returns>OS type name</returns>
        private string GetOSTypeName(int osTypeID, DataRowVersion version)
        {
            try
            {
                DataRow[] osRows = dataSet.OSTypes.Select("ID = " + osTypeID.ToString());
                if ((osRows != null) && (osRows.Length > 0))
                {
                    return osRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of preset hookup to log-file
        /// </summary>
        public void WriteToLogPresetHookup()
        {
            DataRow[] delRows = dataSet.PresetHookup.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.PresetHookup.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.PresetHookup.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.PresetHookup.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the database was added hookup: preset -> '{0}', user -> '{1}', computer -> '{2}', OS -> '{3}', Group -> '{4}'",
                        GetPresetName(addRow["PresetID", DataRowVersion.Current] == System.DBNull.Value ? -1 : addRow["PresetID", DataRowVersion.Current] as int?, DataRowVersion.Current),
                        GetUserName(addRow["UserID", DataRowVersion.Current] == System.DBNull.Value ? -1 : (int)addRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetComputerName(addRow["ComputerID", DataRowVersion.Current] == System.DBNull.Value ? -1 : (int)addRow["ComputerID", DataRowVersion.Current], DataRowVersion.Current),
                        GetOSTypeName(addRow["OSTypeID", DataRowVersion.Current] == System.DBNull.Value ? -1 : (int)addRow["OSTypeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetUserGroupName(addRow["GroupID", DataRowVersion.Current] == System.DBNull.Value ? -1 : (int)addRow["GroupID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the database was removed hookup: preset -> '{0}', user -> '{1}', computer -> '{2}', OS -> '{3}', Group -> '{4}'",
                        GetPresetName(delRow["PresetID", DataRowVersion.Original] == System.DBNull.Value ? -1 : delRow["PresetID", DataRowVersion.Original] as int?, DataRowVersion.Original),
                        GetUserName(delRow["UserID", DataRowVersion.Original] == System.DBNull.Value ? -1 : (int)delRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetComputerName(delRow["ComputerID", DataRowVersion.Original] == System.DBNull.Value ? -1 : (int)delRow["ComputerID", DataRowVersion.Original], DataRowVersion.Original),
                        GetOSTypeName(delRow["OSTypeID", DataRowVersion.Original] == System.DBNull.Value ? -1 : (int)delRow["OSTypeID", DataRowVersion.Original], DataRowVersion.Original),
                        GetUserGroupName(delRow["GroupID", DataRowVersion.Original] == System.DBNull.Value ? -1 : (int)delRow["GroupID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Preset hookup was modified!");
                    logWriter.WriteToLog(message);

                    message = String.Format("Preset hookup before editing: [Preset: '{0}', User: '{1}', Computer: '{2}', OS: '{3}', Group: '{4}']",
                        GetPresetName(updOrigRow["PresetID", DataRowVersion.Original] == System.DBNull.Value ? -1 : updOrigRow["PresetID", DataRowVersion.Original] as int?, DataRowVersion.Original),
                        GetUserName(updOrigRow["UserID", DataRowVersion.Original] == System.DBNull.Value ? -1 : (int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetComputerName(updOrigRow["ComputerID", DataRowVersion.Original] == System.DBNull.Value ? -1 : (int)updOrigRow["ComputerID", DataRowVersion.Original], DataRowVersion.Original),
                        GetOSTypeName(updOrigRow["OSTypeID", DataRowVersion.Original] == System.DBNull.Value ? -1 : (int)updOrigRow["OSTypeID", DataRowVersion.Original], DataRowVersion.Original),
                        GetUserGroupName(updOrigRow["GroupID", DataRowVersion.Original] == System.DBNull.Value ? -1 : (int)updOrigRow["GroupID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Preset hookup after editing: [Preset: '{0}', User: '{1}', Computer: '{2}', OS: '{3}', Group: '{4}']",
                        GetPresetName(updCurrRow["PresetID", DataRowVersion.Current] == System.DBNull.Value ? -1 : updCurrRow["PresetID", DataRowVersion.Current] as int?, DataRowVersion.Current),
                        GetUserName(updCurrRow["UserID", DataRowVersion.Current] == System.DBNull.Value ? -1 : (int)updCurrRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetComputerName(updCurrRow["ComputerID", DataRowVersion.Current] == System.DBNull.Value ? -1 : (int)updCurrRow["ComputerID", DataRowVersion.Current], DataRowVersion.Current),
                        GetOSTypeName(updCurrRow["OSTypeID", DataRowVersion.Current] == System.DBNull.Value ? -1 : (int)updCurrRow["OSTypeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetUserGroupName(updCurrRow["GroupID", DataRowVersion.Current] == System.DBNull.Value ? -1 : (int)updCurrRow["GroupID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Get screen type name
        /// </summary>
        /// <param name="scrID">screen type ID</param>
        /// <param name="version">data row version</param>
        /// <returns>screen name</returns>
        private string GetScreenTypeName(int scrID, DataRowVersion version)
        {
            try
            {
                DataRow[] scrRows = dataSet.ScreenTypes.Select("ID = " + scrID.ToString());
                if ((scrRows != null) && (scrRows.Length > 0))
                {
                    return scrRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get screen object type name
        /// </summary>
        /// <param name="scrID">screen object type ID</param>
        /// <param name="version">data row version</param>
        /// <returns>screen name</returns>
        private string GetScreenObjectTypeName(int scrID, DataRowVersion version)
        {
            try
            {
                DataRow[] scrRows = dataSet.ScreenObjectTypes.Select("ID = " + scrID.ToString());
                if ((scrRows != null) && (scrRows.Length > 0))
                {
                    return scrRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of screens to log-file
        /// </summary>
        public void WriteToLogScreens()
        {
            DataRow[] delRows = dataSet.Screens.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.Screens.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.Screens.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.Screens.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new screen: [Name: {0}, Caption: {1}, Type: {2}, Location X: {3}, Location Y: {4}, Location X(%): {5}, Location Y(%): {6}, Width: {7}, Height: {8}, Width(%): {9}, Height(%): {10}, Font size: {11}, Text color: {12}, Background color: {13}, String value: {14}, Image value: (binary), Text value: {15}]",
                        addRow["Name", DataRowVersion.Current] as string,
                        addRow["Caption", DataRowVersion.Current] as string,
                        GetScreenTypeName((int)addRow["TypeID", DataRowVersion.Current], DataRowVersion.Current),
                        addRow["LocationX", DataRowVersion.Current] as int?,
                        addRow["LocationY", DataRowVersion.Current] as int?,
                        addRow["LocationXPers", DataRowVersion.Current] as int?,
                        addRow["LocationYPers", DataRowVersion.Current] as int?,
                        addRow["WidthPix", DataRowVersion.Current] as int?,
                        addRow["HeightPix", DataRowVersion.Current] as int?,
                        addRow["WidthPers", DataRowVersion.Current] as int?,
                        addRow["HeightPers", DataRowVersion.Current] as int?,
                        addRow["FontSize", DataRowVersion.Current] as int?,
                        addRow["TextColor", DataRowVersion.Current] as int?,
                        addRow["BackGrColor", DataRowVersion.Current] as int?,
                        addRow["StrValue", DataRowVersion.Current] as string,
                        addRow["TextValue", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From DB was removed screen '{0}'", delRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Screen '{0}' was modified!", updOrigRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Screen before editing: [Name: {0}, Caption: {1}, Type: {2}, Location X: {3}, Location Y: {4}, Location X(%): {5}, Location Y(%): {6}, Width: {7}, Height: {8}, Width(%): {9}, Height(%): {10}, Font size: {11}, Text color: {12}, Background color: {13}, String value: {14}, Image value: (binary), Text value: {15}]",
                        updOrigRow["Name", DataRowVersion.Original] as string,
                        updOrigRow["Caption", DataRowVersion.Original] as string,
                        GetScreenTypeName((int)updOrigRow["TypeID", DataRowVersion.Original], DataRowVersion.Original),
                        updOrigRow["LocationX", DataRowVersion.Original] as int?,
                        updOrigRow["LocationY", DataRowVersion.Original] as int?,
                        updOrigRow["LocationXPers", DataRowVersion.Original] as int?,
                        updOrigRow["LocationYPers", DataRowVersion.Original] as int?,
                        updOrigRow["WidthPix", DataRowVersion.Original] as int?,
                        updOrigRow["HeightPix", DataRowVersion.Original] as int?,
                        updOrigRow["WidthPers", DataRowVersion.Original] as int?,
                        updOrigRow["HeightPers", DataRowVersion.Original] as int?,
                        updOrigRow["FontSize", DataRowVersion.Original] as int?,
                        updOrigRow["TextColor", DataRowVersion.Original] as int?,
                        updOrigRow["BackGrColor", DataRowVersion.Original] as int?,
                        updOrigRow["StrValue", DataRowVersion.Original] as string,
                        updOrigRow["TextValue", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Screen after editing: [Name: {0}, Caption: {1}, Type: {2}, Location X: {3}, Location Y: {4}, Location X(%): {5}, Location Y(%): {6}, Width: {7}, Height: {8}, Width(%): {9}, Height(%): {10}, Font size: {11}, Text color: {12}, Background color: {13}, String value: {14}, Image value: (binary), Text value: {15}]",
                        updCurrRow["Name", DataRowVersion.Current] as string,
                        updCurrRow["Caption", DataRowVersion.Current] as string,
                        GetScreenTypeName((int)updCurrRow["TypeID", DataRowVersion.Current], DataRowVersion.Current),
                        updCurrRow["LocationX", DataRowVersion.Current] as int?,
                        updCurrRow["LocationY", DataRowVersion.Current] as int?,
                        updCurrRow["LocationXPers", DataRowVersion.Current] as int?,
                        updCurrRow["LocationYPers", DataRowVersion.Current] as int?,
                        updCurrRow["WidthPix", DataRowVersion.Current] as int?,
                        updCurrRow["HeightPix", DataRowVersion.Current] as int?,
                        updCurrRow["WidthPers", DataRowVersion.Current] as int?,
                        updCurrRow["HeightPers", DataRowVersion.Current] as int?,
                        updCurrRow["FontSize", DataRowVersion.Current] as int?,
                        updCurrRow["TextColor", DataRowVersion.Current] as int?,
                        updCurrRow["BackGrColor", DataRowVersion.Current] as int?,
                        updCurrRow["StrValue", DataRowVersion.Current] as string,
                        updCurrRow["TextValue", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of screen objects to log-file
        /// </summary>
        public void WriteToLogScreenObjects()
        {
            DataRow[] delRows = dataSet.ScreenObjects.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.ScreenObjects.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.ScreenObjects.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.ScreenObjects.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the screen '{0}' was added new screen object: [Name: {1}, Caption: {2}, Type: {3}, Location X: {4}, Location Y: {5}, Location X(%): {6}, Location Y(%): {7}, Width: {8}, Height: {9}, Width(%): {10}, Height(%): {11}, Font size: {12}, Text color: {13}, Background color: {14}, String value: {15}, Image value: (binary), Text value: {16}]",
                        GetScreenName((int)addRow["ParentID", DataRowVersion.Current], DataRowVersion.Current),
                        addRow["Name", DataRowVersion.Current] as string,
                        addRow["Caption", DataRowVersion.Current] as string,
                        GetScreenObjectTypeName((int)addRow["TypeID", DataRowVersion.Current], DataRowVersion.Current),
                        addRow["LocationX", DataRowVersion.Current] as int?,
                        addRow["LocationY", DataRowVersion.Current] as int?,
                        addRow["LocationXPers", DataRowVersion.Current] as int?,
                        addRow["LocationYPers", DataRowVersion.Current] as int?,
                        addRow["WidthPix", DataRowVersion.Current] as int?,
                        addRow["HeightPix", DataRowVersion.Current] as int?,
                        addRow["WidthPers", DataRowVersion.Current] as int?,
                        addRow["HeightPers", DataRowVersion.Current] as int?,
                        addRow["FontSize", DataRowVersion.Current] as int?,
                        addRow["TextColor", DataRowVersion.Current] as int?,
                        addRow["BackGrColor", DataRowVersion.Current] as int?,
                        addRow["StrValue", DataRowVersion.Current] as string,
                        addRow["TextValue", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the screen '{0}' was removed screen object '{1}'", 
                        GetScreenName((int)delRow["ParentID", DataRowVersion.Original], DataRowVersion.Original), 
                        delRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Screen '{0}' was modified!", GetScreenName((int)updOrigRow["ParentID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Screen object before editing: [Name: {0}, Caption: {1}, Type: {2}, Location X: {3}, Location Y: {4}, Location X(%): {5}, Location Y(%): {6}, Width: {7}, Height: {8}, Width(%): {9}, Height(%): {10}, Font size: {11}, Text color: {12}, Background color: {13}, String value: {14}, Image value: (binary), Text value: {15}]",
                        updOrigRow["Name", DataRowVersion.Original] as string,
                        updOrigRow["Caption", DataRowVersion.Original] as string,
                        GetScreenObjectTypeName((int)updOrigRow["TypeID", DataRowVersion.Original], DataRowVersion.Original),
                        updOrigRow["LocationX", DataRowVersion.Original] as int?,
                        updOrigRow["LocationY", DataRowVersion.Original] as int?,
                        updOrigRow["LocationXPers", DataRowVersion.Original] as int?,
                        updOrigRow["LocationYPers", DataRowVersion.Original] as int?,
                        updOrigRow["WidthPix", DataRowVersion.Original] as int?,
                        updOrigRow["HeightPix", DataRowVersion.Original] as int?,
                        updOrigRow["WidthPers", DataRowVersion.Original] as int?,
                        updOrigRow["HeightPers", DataRowVersion.Original] as int?,
                        updOrigRow["FontSize", DataRowVersion.Original] as int?,
                        updOrigRow["TextColor", DataRowVersion.Original] as int?,
                        updOrigRow["BackGrColor", DataRowVersion.Original] as int?,
                        updOrigRow["StrValue", DataRowVersion.Original] as string,
                        updOrigRow["TextValue", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Screen object after editing: [Name: {0}, Caption: {1}, Type: {2}, Location X: {3}, Location Y: {4}, Location X(%): {5}, Location Y(%): {6}, Width: {7}, Height: {8}, Width(%): {9}, Height(%): {10}, Font size: {11}, Text color: {12}, Background color: {13}, String value: {14}, Image value: (binary), Text value: {15}]",
                        updCurrRow["Name", DataRowVersion.Current] as string,
                        updCurrRow["Caption", DataRowVersion.Current] as string,
                        GetScreenObjectTypeName((int)updCurrRow["TypeID", DataRowVersion.Current], DataRowVersion.Current),
                        updCurrRow["LocationX", DataRowVersion.Current] as int?,
                        updCurrRow["LocationY", DataRowVersion.Current] as int?,
                        updCurrRow["LocationXPers", DataRowVersion.Current] as int?,
                        updCurrRow["LocationYPers", DataRowVersion.Current] as int?,
                        updCurrRow["WidthPix", DataRowVersion.Current] as int?,
                        updCurrRow["HeightPix", DataRowVersion.Current] as int?,
                        updCurrRow["WidthPers", DataRowVersion.Current] as int?,
                        updCurrRow["HeightPers", DataRowVersion.Current] as int?,
                        updCurrRow["FontSize", DataRowVersion.Current] as int?,
                        updCurrRow["TextColor", DataRowVersion.Current] as int?,
                        updCurrRow["BackGrColor", DataRowVersion.Current] as int?,
                        updCurrRow["StrValue", DataRowVersion.Current] as string,
                        updCurrRow["TextValue", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of screen object list values to log-file
        /// </summary>
        public void WriteToLogScreenObjectListValues()
        {
            DataRow[] delRows = dataSet.ScreenObjectListValues.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.ScreenObjectListValues.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.ScreenObjectListValues.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.ScreenObjectListValues.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the screen screen object '{0}' was added new list value '{1}'",
                        GetScreenObjectName((int)addRow["ScreenObjectID", DataRowVersion.Current], DataRowVersion.Current),
                        addRow["Value", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the screen object '{0}' was removed list value '{1}'",
                        GetScreenObjectName((int)delRow["ScreenObjectID", DataRowVersion.Original], DataRowVersion.Original),
                        delRow["Value", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Screen object'{0}' was modified!", GetScreenObjectName((int)updOrigRow["ScreenObjectID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Screen object list value before editing: {0}", updOrigRow["Value", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Screen object list value after editing: {0}", updCurrRow["Value", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }
        }


        /// <summary>
        /// Write changes of education categories to log-file
        /// </summary>
        public void WriteToLogEducationCategories()
        {
            DataRow[] delRows = dataSet.EducationCategories.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.EducationCategories.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.EducationCategories.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.EducationCategories.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new education category: {0}",
                        addRow["Name", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed education category '{0}'",
                        delRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Education category'{0}' was modified!", updOrigRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Education category before editing: [Name : {0}]", updOrigRow["Name", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Education category after editing: [Name : {0}]", updCurrRow["Name", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }
        }


        /// <summary>
        /// Get education category name
        /// </summary>
        /// <param name="eduID">education category ID</param>
        /// <param name="version">data row version</param>
        /// <returns>education category name</returns>
        private string GetEducationCategoryName(int eduID, DataRowVersion version)
        {
            try
            {
                DataRow[] eduRows = dataSet.EducationCategories.Select("ID = " + eduID.ToString());
                if ((eduRows != null) && (eduRows.Length > 0))
                {
                    return eduRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of education lessons to log-file
        /// </summary>
        public void WriteToLogEducationLessons()
        {
            DataRow[] delRows = dataSet.EducationLessons.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.EducationLessons.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.EducationLessons.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.EducationLessons.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the education category '{0}' was added new lesson: [Text: {1}, Image: (binary), Order: {2}]",
                        GetEducationCategoryName((int)addRow["CategoryID", DataRowVersion.Current], DataRowVersion.Current),
                        addRow["LessonText", DataRowVersion.Current] as string,
                        addRow["LessonOrder", DataRowVersion.Current] as int?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the education category '{0}' was removed lesson: [Text: {1}, Image: (binary), Order: {2}]",
                         GetEducationCategoryName((int)delRow["CategoryID", DataRowVersion.Original], DataRowVersion.Original),
                        delRow["LessonText", DataRowVersion.Original] as string,
                        delRow["LessonOrder", DataRowVersion.Original] as int?);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Education category '{0}' was modified!", GetEducationCategoryName((int)updOrigRow["CategoryID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Education lesson before editing: [Text: {0}, Image: (binary), Order: {1}]",
                        updOrigRow["LessonText", DataRowVersion.Original] as string,
                        updOrigRow["LessonOrder", DataRowVersion.Original] as int?);
                    logWriter.WriteToLog(message);

                    message = String.Format("Education lesson after editing: [Text: {0}, Image: (binary), Order: {1}]",
                        updCurrRow["LessonText", DataRowVersion.Current] as string,
                        updCurrRow["LessonOrder", DataRowVersion.Current] as int?);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of education answers to log-file
        /// </summary>
        public void WriteToLogEducationAnswers()
        {
            DataRow[] delRows = dataSet.EducationAnswers.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.EducationAnswers.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.EducationAnswers.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.EducationAnswers.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new education answer type: {0}",
                        addRow["AnswerText", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed education answer type: {0}",
                        delRow["AnswerText", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Education answer type '{0}' was modified!", updOrigRow["AnswerText", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Education answer type before editing: [Text: {0}]", updOrigRow["AnswerText", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Education answer type after editing: [Text: {0}]", updCurrRow["AnswerText", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Get education lesson text
        /// </summary>
        /// <param name="eduID">education lesson ID</param>
        /// <param name="version">data row version</param>
        /// <returns>education lesson text</returns>
        private string GetEducationLessonText(int eduID, DataRowVersion version)
        {
            try
            {
                DataRow[] eduRows = dataSet.EducationLessons.Select("ID = " + eduID.ToString());
                if ((eduRows != null) && (eduRows.Length > 0))
                {
                    return eduRows[0]["LessonText", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get education question text
        /// </summary>
        /// <param name="eduID">education question ID</param>
        /// <param name="version">data row version</param>
        /// <returns>education question text</returns>
        private string GetEducationQuestionText(int eduID, DataRowVersion version)
        {
            try
            {
                DataRow[] eduRows = dataSet.EducationQuestions.Select("ID = " + eduID.ToString());
                if ((eduRows != null) && (eduRows.Length > 0))
                {
                    return eduRows[0]["QuestionText", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get education answer text
        /// </summary>
        /// <param name="eduID">education answer ID</param>
        /// <param name="version">data row version</param>
        /// <returns>education answer text</returns>
        private string GetEducationAnswerText(int eduID, DataRowVersion version)
        {
            try
            {
                DataRow[] eduRows = dataSet.EducationAnswers.Select("ID = " + eduID.ToString());
                if ((eduRows != null) && (eduRows.Length > 0))
                {
                    return eduRows[0]["AnswerText", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of education questions to log-file
        /// </summary>
        public void WriteToLogEducationQuestions()
        {
            DataRow[] delRows = dataSet.EducationQuestions.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.EducationQuestions.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.EducationQuestions.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.EducationQuestions.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the education lesson '{0}' was added new question: [Text: {1}, Right answer: {2}, Order: {3}]",
                        GetEducationLessonText((int)addRow["LessonID", DataRowVersion.Current], DataRowVersion.Current),
                        addRow["QuestionText", DataRowVersion.Current] as string,
                        GetEducationAnswerText((int)addRow["RightAnswerID", DataRowVersion.Current], DataRowVersion.Current),
                        addRow["QuestionOrder", DataRowVersion.Current] as int?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the education lesson '{0}' was removed question: [Text: {1}, Right answer: {2}, Order: {3}]",
                        GetEducationLessonText((int)delRow["LessonID", DataRowVersion.Original], DataRowVersion.Original),
                        delRow["QuestionText", DataRowVersion.Original] as string,
                        GetEducationAnswerText((int)delRow["RightAnswerID", DataRowVersion.Original], DataRowVersion.Original),
                        delRow["QuestionOrder", DataRowVersion.Original] as int?);
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Education lesson '{0}' was modified!", GetEducationLessonText((int)updOrigRow["LessonID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Education question before editing: [Text: {0}, Right answer: {1}, Order: {2}]",
                        updOrigRow["QuestionText", DataRowVersion.Original] as string,
                        GetEducationAnswerText((int)updOrigRow["RightAnswerID", DataRowVersion.Original], DataRowVersion.Original),
                        updOrigRow["QuestionOrder", DataRowVersion.Original] as int?);
                    logWriter.WriteToLog(message);

                    message = String.Format("Education question after editing: [Text: {0}, Right answer: {1}, Order: {2}]",
                        updCurrRow["QuestionText", DataRowVersion.Current] as string,
                        GetEducationAnswerText((int)updCurrRow["RightAnswerID", DataRowVersion.Current], DataRowVersion.Current),
                        updCurrRow["QuestionOrder", DataRowVersion.Current] as int?);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of education question answers to log-file
        /// </summary>
        public void WriteToLogEducationQuestionAnswers()
        {
            DataRow[] delRows = dataSet.EducationQuestionAnswers.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.EducationQuestionAnswers.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.EducationQuestionAnswers.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.EducationQuestionAnswers.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the question '{0}' was added answer '{1}'. Answer order: {2}",
                        GetEducationQuestionText((int)addRow["QuestionID", DataRowVersion.Current], DataRowVersion.Current),
                        GetEducationAnswerText((int)addRow["AnswerID", DataRowVersion.Current], DataRowVersion.Current),
                        addRow["AnswerOrder", DataRowVersion.Current] as int?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the question '{0}' was removed answer '{1}'",
                        GetEducationQuestionText((int)delRow["QuestionID", DataRowVersion.Original], DataRowVersion.Original),
                        GetEducationAnswerText((int)delRow["AnswerID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }


            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Education question '{0}' was modified!", GetEducationQuestionText((int)updOrigRow["QuestionID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Before editing: [Question text: '{0}', Answer text: '{1}', Answer order: {2}]",
                        GetEducationQuestionText((int)updOrigRow["QuestionID", DataRowVersion.Original], DataRowVersion.Original),
                        GetEducationAnswerText((int)updOrigRow["AnswerID", DataRowVersion.Original], DataRowVersion.Original),
                        updOrigRow["AnswerOrder", DataRowVersion.Original] as int?);
                    logWriter.WriteToLog(message);

                    message = String.Format("After editing: [Question text: '{0}', Answer text: '{1}', Answer order: {2}]",
                        GetEducationQuestionText((int)updCurrRow["QuestionID", DataRowVersion.Current], DataRowVersion.Current),
                        GetEducationAnswerText((int)updCurrRow["AnswerID", DataRowVersion.Current], DataRowVersion.Current),
                        updCurrRow["AnswerOrder", DataRowVersion.Current] as int?);

                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of user education to log-file
        /// </summary>
        public void WriteToLogUserEducation()
        {
            DataRow[] delRows = dataSet.UserEducation.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserEducation.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserEducation.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserEducation.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> For the user '{0}' was added education category '{1}'. (Random questions: {2}, Category order: {3})",
                        GetUserName((int)addRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetEducationCategoryName((int)addRow["EduCategID", DataRowVersion.Current], DataRowVersion.Current),
                        (addRow["RandomQuestion", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                        addRow["EduCategOrder", DataRowVersion.Current] as int?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> For the user '{0}' was removed education category '{1}'",
                        GetUserName((int)delRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetEducationCategoryName((int)delRow["EduCategID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }
            
            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Education program of user '{0}' was modified!", GetUserName((int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Before editing: [Education category: '{0}', Random questions: {1}, Category order: {2}]",
                        GetEducationCategoryName((int)updOrigRow["EduCategID", DataRowVersion.Original], DataRowVersion.Original),
                        (updOrigRow["RandomQuestion", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                        updOrigRow["EduCategOrder", DataRowVersion.Original] as int?);
                    logWriter.WriteToLog(message);

                    message = String.Format("After editing: [Education category: '{0}', Random questions: {1}, Category order: {2}]",
                        GetEducationCategoryName((int)updCurrRow["EduCategID", DataRowVersion.Current], DataRowVersion.Current),
                        (updCurrRow["RandomQuestion", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                        updCurrRow["EduCategOrder", DataRowVersion.Current] as int?);

                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of user education history to log-file
        /// </summary>
        public void WriteToLogUserEducationAnswers()
        {
            DataRow[] delRows = dataSet.UserEducationAnswers.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserEducationAnswers.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserEducationAnswers.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserEducationAnswers.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new record of user education history: [User: '{0}', Question: '{1}', Answer: '{2}', Correct: {3}, Date: {4}]",
                        GetUserName((int)addRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetEducationQuestionText((int)addRow["QuestionID", DataRowVersion.Current], DataRowVersion.Current),
                        GetEducationAnswerText((int)addRow["AnswerID", DataRowVersion.Current], DataRowVersion.Current),
                        (addRow["CorrectAnswerSign", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                        addRow["Date", DataRowVersion.Current] as DateTime?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed record of user education history: [User: '{0}', Question: '{1}', Answer: '{2}', Correct: {3}, Date: {4}]",
                        GetUserName((int)delRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetEducationQuestionText((int)delRow["QuestionID", DataRowVersion.Original], DataRowVersion.Original),
                        GetEducationAnswerText((int)delRow["AnswerID", DataRowVersion.Original], DataRowVersion.Original),
                        (delRow["CorrectAnswerSign", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                        delRow["Date", DataRowVersion.Original] as DateTime?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Education history of user '{0}' was modified!", GetUserName((int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Before editing: [User: '{0}', Question: '{1}', Answer: '{2}', Correct: {3}, Date: {4}]",
                        GetUserName((int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetEducationQuestionText((int)updOrigRow["QuestionID", DataRowVersion.Original], DataRowVersion.Original),
                        GetEducationAnswerText((int)updOrigRow["AnswerID", DataRowVersion.Original], DataRowVersion.Original),
                        (updOrigRow["CorrectAnswerSign", DataRowVersion.Original] as short?) == 1 ? "YES" : "NO",
                        updOrigRow["Date", DataRowVersion.Original] as DateTime?);
                    logWriter.WriteToLog(message);

                    message = String.Format("After editing: [User: '{0}', Question: '{1}', Answer: '{2}', Correct: {3}, Date: {4}]",
                        GetUserName((int)updCurrRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetEducationQuestionText((int)updCurrRow["QuestionID", DataRowVersion.Current], DataRowVersion.Current),
                        GetEducationAnswerText((int)updCurrRow["AnswerID", DataRowVersion.Current], DataRowVersion.Current),
                        (updCurrRow["CorrectAnswerSign", DataRowVersion.Current] as short?) == 1 ? "YES" : "NO",
                        updCurrRow["Date", DataRowVersion.Current] as DateTime?);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Get notice type name
        /// </summary>
        /// <param name="notID">notice type ID</param>
        /// <param name="version">data row version</param>
        /// <returns>snotice type name</returns>
        private string GetNoticeTypeName(int notID, DataRowVersion version)
        {
            try
            {
                DataRow[] notRows = dataSet.NotificationTypes.Select("ID = " + notID.ToString());
                if ((notRows != null) && (notRows.Length > 0))
                {
                    return notRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get notice display type name
        /// </summary>
        /// <param name="notID">notice display type ID</param>
        /// <param name="version">data row version</param>
        /// <returns>snotice display type name</returns>
        private string GetNoticeDisplayTypeName(int notID, DataRowVersion version)
        {
            try
            {
                DataRow[] notRows = dataSet.NotificationDisplayTypes.Select("ID = " + notID.ToString());
                if ((notRows != null) && (notRows.Length > 0))
                {
                    return notRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get notice scope name
        /// </summary>
        /// <param name="notID">notice scope ID</param>
        /// <param name="version">data row version</param>
        /// <returns>snotice scope name</returns>
        private string GetNoticeScopeName(int notID, DataRowVersion version)
        {
            try
            {
                DataRow[] notRows = dataSet.NotificationScopes.Select("ID = " + notID.ToString());
                if ((notRows != null) && (notRows.Length > 0))
                {
                    return notRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of notifications to log-file
        /// </summary>
        public void WriteToLogNotifications()
        {
            DataRow[] delRows = dataSet.Notifications.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.Notifications.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.Notifications.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.Notifications.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new notification: [Text: '{0}', Notice type: '{1}', Display type: '{2}', Scope: {3}, Image: (binary)]",
                        addRow["NoticeText", DataRowVersion.Current] as string,
                        GetNoticeTypeName((int)addRow["NoticeTypeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNoticeDisplayTypeName((int)addRow["DispTypeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNoticeScopeName((int)addRow["ScopeID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed notification: [Text: '{0}', Notice type: '{1}', Display type: '{2}', Scope: {3}, Image: (binary)]",
                        delRow["NoticeText", DataRowVersion.Original] as string,
                        GetNoticeTypeName((int)delRow["NoticeTypeID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNoticeDisplayTypeName((int)delRow["DispTypeID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNoticeScopeName((int)delRow["ScopeID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Notification '{0}' was modified!", updOrigRow["NoticeText", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format("Before editing: [Text: '{0}', Notice type: '{1}', Display type: '{2}', Scope: {3}, Image: (binary)]",
                        updOrigRow["NoticeText", DataRowVersion.Original] as string,
                        GetNoticeTypeName((int)updOrigRow["NoticeTypeID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNoticeDisplayTypeName((int)updOrigRow["DispTypeID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNoticeScopeName((int)updOrigRow["ScopeID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("After editing: [Text: '{0}', Notice type: '{1}', Display type: '{2}', Scope: {3}, Image: (binary)]",
                        updCurrRow["NoticeText", DataRowVersion.Current] as string,
                        GetNoticeTypeName((int)updCurrRow["NoticeTypeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNoticeDisplayTypeName((int)updCurrRow["DispTypeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNoticeScopeName((int)updCurrRow["ScopeID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Get notification text
        /// </summary>
        /// <param name="notID">notice ID</param>
        /// <param name="version">data row version</param>
        /// <returns>snotice text</returns>
        private string GetNotificationText(int notID, DataRowVersion version)
        {
            try
            {
                DataRow[] notRows = dataSet.Notifications.Select("ID = " + notID.ToString());
                if ((notRows != null) && (notRows.Length > 0))
                {
                    return notRows[0]["NoticeText", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of user notification to log-file
        /// </summary>
        public void WriteToLogUserNotifications()
        {
            DataRow[] delRows = dataSet.UserNotifications.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserNotifications.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserNotifications.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserNotifications.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> For the user '{0}' was added notification '{1}'. Display type: {2}",
                        GetUserName((int)addRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNotificationText((int)addRow["NoticeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNoticeDisplayTypeName((int)addRow["DispTypeID", DataRowVersion.Current], DataRowVersion.Current));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> For the user '{0}' was removed notification '{1}'",
                        GetUserName((int)delRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNotificationText((int)delRow["NoticeID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Notification list of user '{0}' was modified!", GetUserName((int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Before editing: [Notice: '{0}', Display type: {1}]",
                        GetNotificationText((int)updOrigRow["NoticeID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNoticeDisplayTypeName((int)updOrigRow["DispTypeID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("After editing: [Notice: '{0}', Display type: {1}]",
                        GetNotificationText((int)updCurrRow["NoticeID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNoticeDisplayTypeName((int)updCurrRow["DispTypeID", DataRowVersion.Current], DataRowVersion.Current));

                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of user notifications history to log-file
        /// </summary>
        public void WriteToLogUserNotificationsHistory()
        {
            DataRow[] delRows = dataSet.UserNotificationsHistory.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.UserNotificationsHistory.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.UserNotificationsHistory.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.UserNotificationsHistory.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new record of user notification history: [User: '{0}', Notice: '{1}', Date: {2}]",
                        GetUserName((int)addRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNotificationText((int)addRow["NoticeID", DataRowVersion.Current], DataRowVersion.Current),
                        addRow["NoticeDate", DataRowVersion.Current] as DateTime?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed record of user notification history: [User: '{0}', Notice: '{1}', Date: {2}]",
                        GetUserName((int)delRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNotificationText((int)delRow["NoticeID", DataRowVersion.Original], DataRowVersion.Original),
                        delRow["NoticeDate", DataRowVersion.Original] as DateTime?);
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = String.Format("Database manager --> Notification history of user '{0}' was modified!", GetUserName((int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original));
                    logWriter.WriteToLog(message);

                    message = String.Format("Before editing: [User: '{0}', Notice: '{1}', Date: {2}]",
                        GetUserName((int)updOrigRow["UserID", DataRowVersion.Original], DataRowVersion.Original),
                        GetNotificationText((int)updOrigRow["NoticeID", DataRowVersion.Original], DataRowVersion.Original),
                        updOrigRow["NoticeDate", DataRowVersion.Original] as DateTime?);
                    logWriter.WriteToLog(message);

                    message = String.Format("After editing: [User: '{0}', Notice: '{1}', Date: {2}]",
                        GetUserName((int)updCurrRow["UserID", DataRowVersion.Current], DataRowVersion.Current),
                        GetNotificationText((int)updCurrRow["NoticeID", DataRowVersion.Current], DataRowVersion.Current),
                        updCurrRow["NoticeDate", DataRowVersion.Current] as DateTime?);
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of license to log-file
        /// </summary>
        public void WriteToLogLicense()
        {
            DataRow[] delRows = dataSet.License.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.License.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.License.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.License.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new record of license. License string: {0} ", encryptor.DecryptString(addRow["LicenseString", DataRowVersion.Current] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed record of license. License string: {0} ", encryptor.DecryptString(delRow["LicenseString", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = "Database manager --> License record was modified!";
                    logWriter.WriteToLog(message);

                    message = String.Format("License string before editing: {0}", encryptor.DecryptString(updOrigRow["LicenseString", DataRowVersion.Original] as byte[]));
                    logWriter.WriteToLog(message);

                    message = String.Format("License string after editing: {0}", encryptor.DecryptString(updCurrRow["LicenseString", DataRowVersion.Current] as byte[]));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of controlled programs to log-file
        /// </summary>
        public void WriteToLogControlledPrograms()
        {
            DataRow[] delRows = dataSet.ControlledPrograms.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.ControlledPrograms.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.ControlledPrograms.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.ControlledPrograms.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new record of controlled programs. Program name: {0}. Allowed : {1}", (addRow["Name", DataRowVersion.Current] as string), (addRow["Allowed", DataRowVersion.Current] as bool?));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed record of controlled programs. Program name: {0}. Allowed : {1}", (delRow["Name", DataRowVersion.Original] as string), (delRow["Allowed", DataRowVersion.Original] as bool?));
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = "Database manager --> Controlled programs record was modified!";
                    logWriter.WriteToLog(message);

                    message = String.Format(" Controlled program before editing: Name: {0}, Allowed: {1}", (updOrigRow["Name", DataRowVersion.Original] as string), (updOrigRow["Allowed", DataRowVersion.Original] as bool?));
                    logWriter.WriteToLog(message);

                    message = String.Format(" Controlled program after editing: Name: {0}, Allowed: {1}", (updCurrRow["Name", DataRowVersion.Current] as string), (updCurrRow["Allowed", DataRowVersion.Current] as bool?));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of schedule actions to log-file
        /// </summary>
        public void WriteToLogScheduleActions()
        {
            DataRow[] delRows = dataSet.ScheduleActions.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.ScheduleActions.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.ScheduleActions.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.ScheduleActions.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new record of schedule actions. Name: {0}", (addRow["Name", DataRowVersion.Current] as string));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed record of schedule actions. Name: {0}", (delRow["Name", DataRowVersion.Original] as string));
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = "Database manager --> Schedule actions record was modified!";
                    logWriter.WriteToLog(message);

                    message = String.Format(" Schedule action before editing: Name: {0}", (updOrigRow["Name", DataRowVersion.Original] as string));
                    logWriter.WriteToLog(message);

                    message = String.Format(" Schedule action after editing: Name: {0}", (updCurrRow["Name", DataRowVersion.Current] as string));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Write changes of schedule functions to log-file
        /// </summary>
        public void WriteToLogScheduleFunctions()
        {
            DataRow[] delRows = dataSet.ScheduleFunctions.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.ScheduleFunctions.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.ScheduleFunctions.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.ScheduleFunctions.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new record of schedule functions. Name: {0}", (addRow["Name", DataRowVersion.Current] as string));
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed record of schedule functions. Name: {0}", (delRow["Name", DataRowVersion.Original] as string));
                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = "Database manager --> Schedule functions record was modified!";
                    logWriter.WriteToLog(message);

                    message = String.Format(" Schedule function before editing: Name: {0}", (updOrigRow["Name", DataRowVersion.Original] as string));
                    logWriter.WriteToLog(message);

                    message = String.Format(" Schedule function after editing: Name: {0}", (updCurrRow["Name", DataRowVersion.Current] as string));
                    logWriter.WriteToLog(message);
                }
            }
        }

        /// <summary>
        /// Get program name
        /// </summary>
        /// <param name="prgID">program ID</param>
        /// <param name="version">data row version</param>
        /// <returns>program name</returns>
        private string GetControlledProgramName(int prgID, DataRowVersion version)
        {
            try
            {
                DataRow[] prgRows = dataSet.ControlledPrograms.Select("ID = " + prgID.ToString());
                if ((prgRows != null) && (prgRows.Length > 0))
                {
                    return prgRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get schedule actions name
        /// </summary>
        /// <param name="schID">schedule action ID</param>
        /// <param name="version">data row version</param>
        /// <returns>schedule action name</returns>
        private string GetScheduleActionName(int schID, DataRowVersion version)
        {
            try
            {
                DataRow[] schRows = dataSet.ScheduleActions.Select("ID = " + schID.ToString());
                if ((schRows != null) && (schRows.Length > 0))
                {
                    return schRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Get schedule function name
        /// </summary>
        /// <param name="schID">schedule function ID</param>
        /// <param name="version">data row version</param>
        /// <returns>schedule function name</returns>
        private string GetScheduleFunctionName(int schID, DataRowVersion version)
        {
            try
            {
                DataRow[] schRows = dataSet.ScheduleFunctions.Select("ID = " + schID.ToString());
                if ((schRows != null) && (schRows.Length > 0))
                {
                    return schRows[0]["Name", version] as string;
                }
                else
                    return "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Write changes of schedule to log-file
        /// </summary>
        public void WriteToLogSchedule()
        {
            DataRow[] delRows = dataSet.Schedule.Select(null, null, DataViewRowState.Deleted);
            DataRow[] updOrigRows = dataSet.Schedule.Select(null, null, DataViewRowState.ModifiedOriginal);
            DataRow[] updCurrRows = dataSet.Schedule.Select(null, null, DataViewRowState.ModifiedCurrent);
            DataRow[] addRows = dataSet.Schedule.Select(null, null, DataViewRowState.Added);

            if ((addRows != null) && (addRows.Length > 0))
            {
                foreach (DataRow addRow in addRows)
                {
                    string message = String.Format("Database manager --> To the DB was added new record of schedule. User name: {0} Computer name: {1} Group name: {2} Action: {3} Function: {4} Program: {5} Increment: {6} Condition: {7}", 
                                                     GetUserName((int)(addRow["UserID", DataRowVersion.Current]), DataRowVersion.Current),
                                                     GetComputerName((int)(addRow["CompID", DataRowVersion.Current]), DataRowVersion.Current),
                                                     GetUserGroupName((int)(addRow["GroupID", DataRowVersion.Current]), DataRowVersion.Current),
                                                     GetScheduleActionName((int)(addRow["ActionID", DataRowVersion.Current]), DataRowVersion.Current),
                                                     GetScheduleFunctionName((int)(addRow["FuncID", DataRowVersion.Current]), DataRowVersion.Current),
                                                     GetControlledProgramName((int)(addRow["ProgramID", DataRowVersion.Current]), DataRowVersion.Current),
                                                     (short)(addRow["incCountValues", DataRowVersion.Current]),
                                                     addRow["incCountValues", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }

            if ((delRows != null) && (delRows.Length > 0))
            {
                foreach (DataRow delRow in delRows)
                {
                    string message = String.Format("Database manager --> From the DB was removed record of schedule. User name: {0} Computer name: {1} Group name: {2} Action: {3} Function: {4} Program: {5} Increment: {6} Condition: {7}",
                                                     GetUserName((int)(delRow["UserID", DataRowVersion.Original]), DataRowVersion.Original),
                                                     GetComputerName((int)(delRow["CompID", DataRowVersion.Original]), DataRowVersion.Original),
                                                     GetUserGroupName((int)(delRow["GroupID", DataRowVersion.Original]), DataRowVersion.Original),
                                                     GetScheduleActionName((int)(delRow["ActionID", DataRowVersion.Original]), DataRowVersion.Original),
                                                     GetScheduleFunctionName((int)(delRow["FuncID", DataRowVersion.Original]), DataRowVersion.Original),
                                                     GetControlledProgramName((int)(delRow["ProgramID", DataRowVersion.Original]), DataRowVersion.Original),
                                                     (short)(delRow["incCountValues", DataRowVersion.Original]),
                                                     delRow["incCountValues", DataRowVersion.Original] as string);

                    logWriter.WriteToLog(message);
                }
            }

            if ((updOrigRows != null) && (updCurrRows != null) && (updOrigRows.Length > 0) && (updCurrRows.Length > 0) && (updOrigRows.Length == updCurrRows.Length))
            {
                for (int i = 0; i < updCurrRows.Length; i++)
                {
                    DataRow updCurrRow = updCurrRows[i];
                    DataRow updOrigRow = updOrigRows[i];

                    string message = "Database manager --> Schedule record was modified!";
                    logWriter.WriteToLog(message);

                    message = String.Format(" Schedule record before editing: User name: {0} Computer name: {1} Group name: {2} Action: {3} Function: {4} Program: {5} Increment: {6} Condition: {7}", 
                                            GetUserName((int)(updOrigRow["UserID", DataRowVersion.Original]), DataRowVersion.Original),
                                            GetComputerName((int)(updOrigRow["CompID", DataRowVersion.Original]), DataRowVersion.Original),
                                            GetUserGroupName((int)(updOrigRow["GroupID", DataRowVersion.Original]), DataRowVersion.Original),
                                            GetScheduleActionName((int)(updOrigRow["ActionID", DataRowVersion.Original]), DataRowVersion.Original),
                                            GetScheduleFunctionName((int)(updOrigRow["FuncID", DataRowVersion.Original]), DataRowVersion.Original),
                                            GetControlledProgramName((int)(updOrigRow["ProgramID", DataRowVersion.Original]), DataRowVersion.Original),
                                            (short)(updOrigRow["incCountValues", DataRowVersion.Original]),
                                            updOrigRow["incCountValues", DataRowVersion.Original] as string);
                    logWriter.WriteToLog(message);

                    message = String.Format(" Schedule record after editing: User name: {0} Computer name: {1} Group name: {2} Action: {3} Function: {4} Program: {5} Increment: {6} Condition: {7}", 
                                            GetUserName((int)(updCurrRow["UserID", DataRowVersion.Current]), DataRowVersion.Current),
                                            GetComputerName((int)(updCurrRow["CompID", DataRowVersion.Current]), DataRowVersion.Current),
                                            GetUserGroupName((int)(updCurrRow["GroupID", DataRowVersion.Current]), DataRowVersion.Current),
                                            GetScheduleActionName((int)(updCurrRow["ActionID", DataRowVersion.Current]), DataRowVersion.Current),
                                            GetScheduleFunctionName((int)(updCurrRow["FuncID", DataRowVersion.Current]), DataRowVersion.Current),
                                            GetControlledProgramName((int)(updCurrRow["ProgramID", DataRowVersion.Current]), DataRowVersion.Current),
                                            (short)(updCurrRow["incCountValues", DataRowVersion.Current]),
                                            updCurrRow["incCountValues", DataRowVersion.Current] as string);
                    logWriter.WriteToLog(message);
                }
            }
        }

        #endregion

    }
}