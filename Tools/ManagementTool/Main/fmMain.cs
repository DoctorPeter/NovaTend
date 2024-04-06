/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmMain.cs
///   Description :  main window module
/// </summary>
/// 
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Globalization;
using System.IO;
using System.ServiceProcess;
using System.Threading;

using SystemData;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;

using System.Data.SqlClient;

using Communication;
using Communication.Client;

using Commands;
using CommandClient;

using DataModule;
using Encryption;
using SettingsManagement;
using Synchronization;
using WriteLog;
using ServerConnector;
using License;
using Scheduler;

namespace ManagementTool
{
    /// <summary>
    /// Main window class
    /// </summary>
    public partial class fmMain : Form
    {
     
        #region Connection

        // Connection string
        private string _connectionString;

        // Connection string property
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

        // User permissions
        private int[] _userPermissions;

        // User permissions property
        public int[] userPermissions
        {
            get
            {
                return _userPermissions;
            }

            set
            {
                _userPermissions = value;
            }
        }
        
        #endregion

        #region DB manager

        // Database manager instance
        private DataBaseManager _dbManager;

        // Database manager property
        public DataBaseManager dbManager
        {
            get
            {
                if (_dbManager == null)
                {
                    _dbManager = new DataBaseManager(connectionString, logWriter);
                }

                return _dbManager;
            }

            set
            {
                _dbManager = value;
            }
        }

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
                
        #region Synchronization

        // User accounts synchronizer instance
        private UserAccountsSynchronizer _userAccountsSynchronizer;

        // User account synchronizer property
        public UserAccountsSynchronizer userAccountsSynchronizer
        {
            get
            {
                if (_userAccountsSynchronizer == null)
                {
                    _userAccountsSynchronizer = new UserAccountsSynchronizer(dbManager);
                }

                return _userAccountsSynchronizer;
            }

            set
            {
                _userAccountsSynchronizer = value;
            }
        }

        #endregion

        #region Settings management

        // Settings manager instance
        private SettingsManager _settingsManager;

        // Settings manager property
        public SettingsManager settingsManager
        {
            get
            {
                if (_settingsManager == null)
                {
                    _settingsManager = new SettingsManager();
                }

                return _settingsManager;
            }

            set
            {
                _settingsManager = value;
            }
        }

        #endregion

        #region Construction

        // current user name
        private string currentUserName;

        /// <summary>
        /// Constructor
        /// </summary>
        public fmMain()
        {
            _dbManager = null;
            _encryptor = null;
            _logWriter = null;
            _settingsManager = null;
            _serverConnector = null;
  
            encryptor.Init();

            logWriter.WriteToLog(" ------ New NovaTend management tool session ------ ");

            InitializeComponent();
        }

        /// <summary>
        /// Main window show event handler
        /// </summary>
        private void fmMain_Shown(object sender, EventArgs e)
        {
            disconnectToolStripMenuItem_Click(null, null);
            connectToolStripMenuItem_Click(null, null);
        }

        /// <summary>
        /// Main window load event handler
        /// </summary>
        private void fmMain_Load(object sender, EventArgs e)
        {
            // Set controls customizing flags
            _usersContorlsCustomized = false;
            _computersContorlsCustomized = false;
            _authSystemsContorlsCustomized = false;
            _presetsContorlsCustomized = false;
            _educationContorlsCustomized = false;
            _notificationContorlsCustomized = false;
            _licenseContorlsCustomized = false;
            _logFilesContorlsCustomized = false;
            _confManagemengCustomized = false;
            _personalPageContorlsCustomized = false;
            _userGroupsContorlsCustomized = false;
            _scheduleContorlsCustomized = false;
        }

        /// <summary>
        /// Main window closing event handler
        /// </summary>
        private void fmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            disconnectToolStripMenuItem_Click(null, null);
            logWriter.WriteToLog(" ------ Close NovaTend management tool session ------ ");
            encryptor.Cleanup();
        }

        #endregion

        #region Personal page
        
        // Personal user data settings controls flag
        private bool _personalPageContorlsCustomized;

        /// <summary>
        /// Customize personal page controls
        /// </summary>
        private void CustomizePersonalPageControls()
        {
            // Find user in database
            bool found = false;
            int _count = dbManager.personalUsersBindingSource.Count;
            dbManager.personalUsersBindingSource.MoveFirst();

            while (_count > 0)
            {
                string tmpUsrName = "";

                if ((dbManager.personalUsersBindingSource.Current != null) &&
                    (!((dbManager.personalUsersBindingSource.Current as DataRowView).Row["UserName"] is System.DBNull)))
                        tmpUsrName = encryptor.DecryptString((byte[])(dbManager.personalUsersBindingSource.Current as DataRowView).Row["UserName"]);

                if (tmpUsrName == currentUserName)
                {
                    found = true;
                    break;
                }
                else
                    dbManager.personalUsersBindingSource.MoveNext();
                    
                _count--;
            }
                

            // Check result
            if (!found)
            {
                MessageBox.Show("User \"" + currentUserName + "\" not found!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Personal page --> User \"" + currentUserName + "\" not found!");
                disconnectToolStripMenuItem_Click(null, null);
                return;
            }

            // User personal data
            personalUserNameTextBox.Text = currentUserName;

            // Check column
            if ((dbManager.personalUsersBindingSource.Current != null) &&
                (!((dbManager.personalUsersBindingSource.Current as DataRowView).Row["Name"] is System.DBNull)))
            {
                // Decrypt user full name
                personalFullNameTextBox.Text = encryptor.DecryptString((byte[])(dbManager.personalUsersBindingSource.Current as DataRowView).Row["Name"]);
            }
            else
                personalFullNameTextBox.Text = "";


            // Check column
            if ((dbManager.personalUsersBindingSource.Current != null) &&
                (!((dbManager.personalUsersBindingSource.Current as DataRowView).Row["Email"] is System.DBNull)))
            {
                // Decrypt user email
                personalUserEmailTextBox.Text = encryptor.DecryptString((byte[])(dbManager.personalUsersBindingSource.Current as DataRowView).Row["Email"]);
            }
            else
                personalUserEmailTextBox.Text = "";

            // Check column
            if ((dbManager.personalUsersBindingSource.Current != null) &&
                (!((dbManager.personalUsersBindingSource.Current as DataRowView).Row["Phone"] is System.DBNull)))
            {
                // Decrypt user phone
                personalUserPhoneTextBox.Text = encryptor.DecryptString((byte[])(dbManager.personalUsersBindingSource.Current as DataRowView).Row["Phone"]);
            }
            else
                personalUserPhoneTextBox.Text = "";

            personalLogonDateLabel.Text = "Date of last log on: " + (dbManager.personalUsersBindingSource.Current as DataRowView).Row["LastSignInDate"].ToString();
            personalPwdAttemptsLabel.Text = "Number of attempts to enter the correct password: " + (dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdAttemptsCount"].ToString();
            personalMaxPwdAttemptsLabel.Text = "Maximum number of attempts to enter the correct password: " + (dbManager.personalUsersBindingSource.Current as DataRowView).Row["MaxPwdAttemptsCount"].ToString();
                
            short eduFlag = (short)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["NeedStudy"];

            if (eduFlag != 0) personalEducationLabel.Text = "You participate in education program";
            else personalEducationLabel.Text = "You do not participate in education program";

            short pwdReseted = (short)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdResetted"];

            if (pwdReseted != 0)
            {
                personalPwdResetDateLabel.Text = "ATTENTION! Your password was reseted " + (dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdResetDate"].ToString();
                personalPwdResetPeriodLabel.Text = "Period of temporary password use is " + (dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdResetPeriod"].ToString() + " hour(s)";
                personalPwdResetPanel.Visible = true;
            }
            else
            {
                personalPwdResetPanel.Visible = false;
            }
            
            // Get groups list
            if (dbManager.personalUserGroupsBindingSource.Count > 0)
            {
                GetUserGroupsNames(userGroupNameColumn);
                personalGroupsListView.Items.Clear();

                _count = dbManager.fkPersonalUsersUserGroupsBindingSource.Count;
                dbManager.fkPersonalUsersUserGroupsBindingSource.MoveFirst();

                while (_count > 0)
                {
                    int groupID = (int)(dbManager.fkPersonalUsersUserGroupsBindingSource.Current as DataRowView).Row["GroupID"];

                    string groupName = GetDictionaryValueByID(groupID, userGroupNames);
                    ListViewItem item = new ListViewItem();
                    item.Text = groupName;
                    item.ImageIndex = 1;
                    personalGroupsListView.Items.Add(item);

                    dbManager.fkPersonalUsersUserGroupsBindingSource.MoveNext();
                    _count--;
                }
            }
                     
            // Check flag
            if (!_personalPageContorlsCustomized)
             {
                // Pwd reset check boxes
                personalEmailResetCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("CheckState", dbManager.personalUsersBindingSource, "EmailPwdReset", true));
                personalSMSResetCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("CheckState", dbManager.personalUsersBindingSource, "SmsPwdReset", true));
                           
                // User accounts values
                personalAccountsBindingNavigator.BindingSource = dbManager.fkPersonalUserAccountsUsersBindingSource;
                personalAccountsDataGridView.AutoGenerateColumns = false;
                personalAccountsDataGridView.DataSource = dbManager.fkPersonalUserAccountsUsersBindingSource;
                personalAuthSystemNameColumn.DataSource = dbManager.personalUserAccountAuthSystemsBindingSource;
                personalAuthSystemNameColumn.DataPropertyName = "AuthSystemID";
                personalAuthSystemNameColumn.DisplayMember = "Name";
                personalAuthSystemNameColumn.ValueMember = "ID";
                personalUserNameColumn.DataPropertyName = "UserName";
                personalUserPasswordColumn.DataPropertyName = "Password";
                personalLastLogonDateColumn.DataPropertyName = "LastSignInDate";
                personalPassThruPwdColumn.DataPropertyName = "PassThru";

                // Parameters for checking
                personalParametersBindingNavigator.BindingSource = dbManager.fkPersonalUserCheckValuesUsersBindingSource;
                personalParametersDataGridView.AutoGenerateColumns = false;
                personalParametersDataGridView.DataSource = dbManager.fkPersonalUserCheckValuesUsersBindingSource;
                personalParameterValueColumn.DataPropertyName = "Value";
                personalParameterNameColumn.DataSource = dbManager.personalUserCheckValuesScreenObjectsBindingSource;
                personalParameterNameColumn.DataPropertyName = "ScreenObjectID";
                personalParameterNameColumn.DisplayMember = "Name";
                personalParameterNameColumn.ValueMember = "ID";

                // User password type
                GetPasswordTypeNames();

                _personalPageContorlsCustomized = true;
            }

            personalPwdTypeComboBox.Text = GetDictionaryValueByID((int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdTypeID"], passwordTypeNames);
        }

        /// <summary>
        /// Password type changed event handler
        /// </summary>
        private void personalPwdTypeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            int pwdTypeID = GetDictionaryIDByValue(personalPwdTypeComboBox.Text, passwordTypeNames);
            if (pwdTypeID != -1)
            {
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdTypeID"] = pwdTypeID;
            }
        }

        /// <summary>
        /// Change password button click
        /// </summary>
        private void changePasswordButton_Click(object sender, EventArgs e)
        {
            int pwdType = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdTypeID"];
            bool isOK = false;

            switch (pwdType)
            {
                case fmConnect.CASCADE_STRING_PWD:
                    {
                        fmCascadeStringPwdSettings fmPwd = new fmCascadeStringPwdSettings(dbManager, encryptor, true);
                        fmPwd.ShowDialog();

                        isOK = fmPwd.Commited;

                        break;
                    }

                case fmConnect.ONE_SYMBOL_BOX_PWD:
                case fmConnect.TWO_SYMBOL_BOX_PWD:
                    {
                        fmSymbolBoxesPwdSettings fmPwd = new fmSymbolBoxesPwdSettings(dbManager, encryptor, true);
                        fmPwd.ShowDialog();

                        isOK = fmPwd.Commited;

                        break;
                    }
            }

            if (isOK)
            {
               (dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdResetted"] = 0;
               saveUserButton_Click(sender, e);
               personalPwdResetPanel.Visible = false;
               logWriter.WriteToLog("Personal page --> User's password was changed!");
            }

        }

        /// <summary>
        /// Parameters for checking cell formatting
        /// </summary>
        private void personalParametersDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "personalParameterValueColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["personalParameterValueColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["personalParameterValueColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["personalParameterValueColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Parameters for checking cell parsing
        /// </summary>
        private void personalParametersDataGridView_CellParsing(object sender, DataGridViewCellParsingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "personalParameterValueColumn"))
            {
                // Encrypt data
                dataGridView[e.ColumnIndex, e.RowIndex].Value = encryptor.EncryptString(e.Value.ToString());
                dataGridView.RefreshEdit();
                e.ParsingApplied = true;
            }
        }

        /// <summary>
        /// User accounts data cell formatting
        /// </summary>
        private void personalAccountsDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "personalUserNameColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["personalUserNameColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["personalUserNameColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["personalUserNameColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }

            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "personalUserPasswordColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["personalUserPasswordColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["personalUserPasswordColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                string pwdStr = encryptor.DecryptString((byte[])dataGridView["personalUserPasswordColumn", e.RowIndex].Value);
                DataGridViewCell cell = dataGridView.Rows[e.RowIndex].Cells[e.ColumnIndex];
                if (pwdStr.Length > 0)
                {
                    e.Value = new string('*', pwdStr.Length);
                    if (supervisor) cell.ToolTipText = pwdStr;
                    else cell.ToolTipText = "";
                }
                else
                {
                    e.Value = "";
                    cell.ToolTipText = "";
                }

                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Change current account password button click
        /// </summary>
        private void personalAccountsBindingNavigatorChangePwdItem_Click(object sender, EventArgs e)
        {
            if (dbManager.fkPersonalUserAccountsUsersBindingSource.Current != null)
            {
                fmChangePassword fmChangePwd = new fmChangePassword(supervisor);
                fmChangePwd.ShowDialog();

                if (fmChangePwd.PasswordChanged)
                {
                    string uaName = encryptor.DecryptString((dbManager.fkPersonalUserAccountsUsersBindingSource.Current as DataRowView).Row["UserName"] as byte[]);

                    if (fmChangePwd.Password.Length > 0)
                    {

                        logWriter.WriteToLog("Personal page --> Password for user account with user ID '" + uaName + "' was changed!");
                        (dbManager.fkPersonalUserAccountsUsersBindingSource.Current as DataRowView).Row["Password"] = encryptor.EncryptString(fmChangePwd.Password);
                    }
                    else
                    {
                        logWriter.WriteToLog("Personal page --> Password for user account with user ID '" + uaName + "' was deleted!");
                        (dbManager.fkPersonalUserAccountsUsersBindingSource.Current as DataRowView).Row["Password"] = null;
                    }
                }
            }
        }

        /// <summary>
        /// User accounts data cell parsing
        /// </summary>
        private void personalAccountsDataGridView_CellParsing(object sender, DataGridViewCellParsingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) && (dataGridView.Columns[e.ColumnIndex].Name == "personalUserNameColumn") /*|| (dataGridView.Columns[e.ColumnIndex].Name == "personalUserPasswordColumn")*/)
            {
                // Encrypt data
                dataGridView[e.ColumnIndex, e.RowIndex].Value = encryptor.EncryptString(e.Value.ToString());
                dataGridView.RefreshEdit();
                e.ParsingApplied = true;
            }
        }

        /// <summary>
        /// Save button click
        /// </summary>
        private void saveUserButton_Click(object sender, EventArgs e)
        {
            if (personalFullNameTextBox.Text != "")
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["Name"] = encryptor.EncryptString(personalFullNameTextBox.Text);
            else
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["Name"] = System.DBNull.Value;

            if (personalUserNameTextBox.Text != "")
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["UserName"] = encryptor.EncryptString(personalUserNameTextBox.Text);
            else
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["UserName"] = System.DBNull.Value;

            if (personalUserEmailTextBox.Text != "")
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["Email"] = encryptor.EncryptString(personalUserEmailTextBox.Text);
            else
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["Email"] = System.DBNull.Value;

            if (personalUserPhoneTextBox.Text != "")
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["Phone"] = encryptor.EncryptString(personalUserPhoneTextBox.Text);
            else
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["Phone"] = System.DBNull.Value;

            if (!this.Validate()) return;

            dbManager.personalUsersBindingSource.EndEdit();

            dbManager.UpdateUsers();
        }

        /// <summary>
        /// Refresh button click
        /// </summary>
        private void refreshUserButton_Click(object sender, EventArgs e)
        {
            dbManager.usersTableAdapter.Fill(dbManager.dataSet.Users);
            dbManager.userPermissionsTableAdapter.Fill(dbManager.dataSet.UserPermissions);
            dbManager.permissionsTableAdapter.Fill(dbManager.dataSet.Permissions);
            CustomizePersonalPageControls();
        }
                       
        /// <summary>
        /// Save user accounts
        /// </summary>
        private void personalAccountsBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkPersonalUserAccountsUsersBindingSource.EndEdit();

            SyncUserAccountOnEdit();

            dbManager.UpdateUserAccounts();
        }

        /// <summary>
        /// Refresh button click
        /// </summary>
        private void personalAccountsBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.authSystemsTableAdapter.Fill(dbManager.dataSet.AuthSystems);
            dbManager.userAccountsTableAdapter.Fill(dbManager.dataSet.UserAccounts);
        }

        /// <summary>
        /// Save parameters for checking
        /// </summary>
        private void personalParametersBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkPersonalUserCheckValuesUsersBindingSource.EndEdit();
            dbManager.UpdateUserCheckValues();
        }

        /// <summary>
        /// Refresh button click
        /// </summary>
        private void personalParametersBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userCheckValuesTableAdapter.Fill(dbManager.dataSet.UserCheckValues);
            dbManager.userCheckValuesScreenObjectsTableAdapter.Fill(dbManager.dataSet.UserCheckValuesScreenObjects);
        }

        #endregion

        #region Users management

        // User settings controls flag
        private bool _usersContorlsCustomized;

        /// <summary>
        /// Create filetr string for users data source.
        /// Remove supervisors
        /// </summary>
        /// <returns>Filter string</returns>
        private string CreateSupevisorsFilterString()
        {
            string filterString = "";
            DataRow[] userPermissionsRows = dbManager.dataSet.UserPermissions.Select("PermissionID = 0");
            if ((userPermissionsRows != null) && (userPermissionsRows.Length > 0))
            {
                foreach (DataRow row in userPermissionsRows)
                {
                    int userID = (int)row["userID", DataRowVersion.Original];
                    filterString = filterString + "(ID <> " + userID.ToString() + ") AND";
                }

                if (filterString.Length > 0)
                    filterString = filterString.Substring(0, filterString.Length - 4);
            }

            return filterString;
        }

        /// <summary>
        /// Customize controls for supervisor - sysadmin
        /// </summary>
        private void CustomizeSupervisorControls()
        {
            if (supervisor)
            {
                changePwdSettingsButton.Visible = true;

                if (!userDetailsTabControl.TabPages.Contains(usrPermissionsPage))
                    userDetailsTabControl.TabPages.Add(usrPermissionsPage);

                dbManager.permissionsBindingSource.Filter = "";
                dbManager.usersBindingSource.Filter = "";
            }
            else
            {
                changePwdSettingsButton.Visible = false;
                
                if (userDetailsTabControl.TabPages.Contains(usrPermissionsPage))
                    userDetailsTabControl.TabPages.Remove(usrPermissionsPage);

                dbManager.permissionsBindingSource.Filter = "ID > 0";
                dbManager.usersBindingSource.Filter = CreateSupevisorsFilterString();
            }
        }

        /// <summary>
        /// Customize users controls
        /// </summary>
        private void CustomizeUsersControls()
        {
            // Prepare supervisor
            CustomizeSupervisorControls();

             // Check flag
            if (!_usersContorlsCustomized)
            {
                // Change position handler
                dbManager.usersBindingSource.PositionChanged += new System.EventHandler(usersBindingSource_PositionChanged);

                // Binding navigator
                usersBindingNavigator.BindingSource = dbManager.usersBindingSource;

                // Users data grid view
                userNamesDataGridView.AutoGenerateColumns = false;
                userNamesDataGridView.DataSource = dbManager.usersBindingSource;
                userNameColumn.DataPropertyName = "Name";
                
                // User check values data grid view
                userCheckValuesDataGridView.AutoGenerateColumns = false;
                userCheckValuesDataGridView.DataSource = dbManager.fkUserCheckValuesUsersBindingSource;
                userCheckValueColumn.DataPropertyName = "Value";
                userCheckValueObjectIDColumn.DataSource = dbManager.userCheckValuesScreenObjectsBindingSource;
                userCheckValueObjectIDColumn.DataPropertyName = "ScreenObjectID";
                userCheckValueObjectIDColumn.DisplayMember = "Name";
                userCheckValueObjectIDColumn.ValueMember = "ID";

                // User permissions values
                userPermissionsDataGridView.AutoGenerateColumns = false;
                userPermissionsDataGridView.DataSource = dbManager.fkUserPermissionsUsersBindingSource;
                userPermissionIDColumn.DataPropertyName = "PermissionID";

                // User groups values
                userGroupsDataGridView.AutoGenerateColumns = false;
                userGroupsDataGridView.DataSource = dbManager.fkUserGroupsUsersBindingSource;
                userGroupIDColumn.DataPropertyName = "GroupID";
                
                // User accounts values
                userAccountsDataGridView.AutoGenerateColumns = false;
                userAccountsDataGridView.DataSource = dbManager.fkUserAccountsUsersBindingSource;
                authSystemTypeNameColumn.DataSource = dbManager.userAccontsAuthSystemsBindingSource;
                authSystemTypeNameColumn.DataPropertyName = "AuthSystemID";
                authSystemTypeNameColumn.DisplayMember = "Name";
                authSystemTypeNameColumn.ValueMember = "ID";
                accountUserNameColumn.DataPropertyName = "UserName";
                accountPasswordColumn.DataPropertyName = "Password";
                lastSignInDateColumn.DataPropertyName = "LastSignInDate";
                passThruColumn.DataPropertyName = "PassThru";

                // Users customize controls
                userPwdAttemptsCountTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.usersBindingSource, "PwdAttemptsCount", true));
                userMaxPwdAttemptsCountTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.usersBindingSource, "MaxPwdAttemptsCount", true));
                userNeedStudyCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("CheckState", dbManager.usersBindingSource, "NeedStudy", true));
                userRandomEduCategCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("CheckState", dbManager.usersBindingSource, "RandomEduCateg", true));
                lastLogOnDateTimePicker.DataBindings.Add(new System.Windows.Forms.Binding("Value", dbManager.usersBindingSource, "LastSignInDate", true));
                userLockedCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("CheckState", dbManager.usersBindingSource, "Locked", true));
                userPwdResetedCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("CheckState", dbManager.usersBindingSource, "PwdResetted", true));
                userEmailPwdResetCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("CheckState", dbManager.usersBindingSource, "EmailPwdReset", true));
                userSMSPwdResetCheckBox.DataBindings.Add(new System.Windows.Forms.Binding("CheckState", dbManager.usersBindingSource, "SmsPwdReset", true));
                userPwdResetDateTimePicker.DataBindings.Add(new System.Windows.Forms.Binding("Value", dbManager.usersBindingSource, "PwdResetDate", true));
                userPwdResetPeriodTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.usersBindingSource, "PwdResetPeriod", true));

                // User password type
                GetPasswordTypeNames();

                // Get user permissions
                GetUserPermissionNames();
    
                dbManager.usersTableAdapter.Fill(dbManager.dataSet.Users);

                // Set flag
                _usersContorlsCustomized = true;
            }

            // Decrypt encrypted data
            usersBindingSource_PositionChanged(null, null);
        }

        // Password types names
        private Dictionary<int, string> passwordTypeNames;

        // User group names
        private Dictionary<int, string> userGroupNames;

        // User permission names
        private Dictionary<int, string> userPermissionNames;

        // User names
        private Dictionary<int, string> userNames;

        /// <summary>
        /// Get value by ID
        /// </summary>
        /// <param name="ID">value ID</param>
        /// <param name="dictionary">dictionary</param>
        /// <returns>dictionary value</returns>
        private string GetDictionaryValueByID(int ID, Dictionary<int, string> dictionary)
        {
            return dictionary.ContainsKey(ID) ? dictionary[ID] : String.Empty;
        }
        
        /// <summary>
        /// Get dictionary key by value
        /// </summary>
        /// <param name="value">dictionary value</param>
        /// <param name="dictionary">dictionary</param>
        /// <returns>dictionary value</returns>
        private int GetDictionaryIDByValue(string value, Dictionary<int, string> dictionary)
        {
            if ((value != null) && (value != String.Empty))
                return dictionary.FirstOrDefault(x => x.Value.Equals(value)).Key;
            else
                return -1;
        }

        /// <summary>
        /// Get password types
        /// </summary>
        private void GetPasswordTypeNames()
        {
            // User password type
            if (passwordTypeNames == null)
                passwordTypeNames = new Dictionary<int, string>();
            else
                passwordTypeNames.Clear();

            userPwdTypeComboBox.Items.Clear();
            personalPwdTypeComboBox.Items.Clear();
            for (int i = 0; i < dbManager.passwordConstructionRulesTypesBindingSource.Count; i++)
            {
                int pwdTypeID = (int)dbManager.dataSet.PasswordConstructionRulesTypes.Rows[i]["ID"];
                string pwdTypeName = encryptor.DecryptString((byte[])dbManager.dataSet.PasswordConstructionRulesTypes.Rows[i]["Name"]);
                passwordTypeNames.Add(pwdTypeID, pwdTypeName);
                userPwdTypeComboBox.Items.Add(pwdTypeName);
                personalPwdTypeComboBox.Items.Add(pwdTypeName);
            }
        }

        /// <summary>
        /// Get user groups names
        /// </summary>
        private void GetUserGroupsNames(DataGridViewComboBoxColumn groupNameColumn)
        {
            // User group names
            if (userGroupNames == null)
                userGroupNames = new Dictionary<int, string>();
            else
                userGroupNames.Clear();

            groupNameColumn.Items.Clear();
            for (int i = 0; i < dbManager.dataSet.UserGroups.Rows.Count; i++)
            {
                int userGroupID = (int)dbManager.dataSet.UserGroups.Rows[i]["ID"];
                string userGroupName = encryptor.DecryptString((byte[])dbManager.dataSet.UserGroups.Rows[i]["Name"]);
                userGroupNames.Add(userGroupID, userGroupName);
                groupNameColumn.Items.Add(userGroupName);
            }
        }

        /// <summary>
        /// Get user names
        /// </summary>
        private void GetUserNames(DataGridViewComboBoxColumn userNameColumn)
        {
            // User names
            if (userNames == null)
                userNames = new Dictionary<int, string>();
            else
                userNames.Clear();

            userNameColumn.Items.Clear();
            for (int i = 0; i < dbManager.dataSet.Users.Rows.Count; i++)
            {
                int userID = (int)dbManager.dataSet.Users.Rows[i]["ID"];
                string userName = encryptor.DecryptString((byte[])dbManager.dataSet.Users.Rows[i]["Name"]);
                userNames.Add(userID, userName);
                userNameColumn.Items.Add(userName);
            }
        }

        /// <summary>
        /// Get user permission names
        /// </summary>
        private void GetUserPermissionNames()
        {
            // User group names
            if (userPermissionNames == null)
                userPermissionNames = new Dictionary<int, string>();
            else
                userPermissionNames.Clear();

            userPermissionNameColumn.Items.Clear();
            groupPermissionsColumn.Items.Clear();
            for (int i = 0; i < dbManager.dataSet.Permissions.Rows.Count; i++)
            {
                int permissionID = (int)dbManager.dataSet.Permissions.Rows[i]["ID"];
                string permissionName = encryptor.DecryptString((byte[])dbManager.dataSet.Permissions.Rows[i]["Name"]);
                userPermissionNames.Add(permissionID, permissionName);
                userPermissionNameColumn.Items.Add(permissionName);
                groupPermissionsColumn.Items.Add(permissionName);
            }
        }

        /// <summary>
        /// User groups data grid view cell formatting event handler
        /// </summary>
        private void userGroupsDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "userGroupNameColumn") &&
                (e.RowIndex >= 0) &&
                (e.RowIndex < dbManager.fkUserGroupsUsersBindingSource.Count) &&
                (!(dataGridView.Rows[e.RowIndex].Cells["userGroupIDColumn"].Value is System.DBNull)) &&
                (userGroupNameColumn.Items.Count > 0) &&
                (userGroupNames != null) && (userGroupNames.Count > 0))
            {
                // Set decrypted rule name
                e.Value = GetDictionaryValueByID((int)dataGridView.Rows[e.RowIndex].Cells["userGroupIDColumn"].Value, userGroupNames);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// User groups data grid view cell value changed event handler
        /// </summary>
        private void userGroupsDataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "userGroupNameColumn") &&
                (userGroupNameColumn.Items.Count > 0))
            {
                int ruleID = GetDictionaryIDByValue((string)dataGridView.Rows[e.RowIndex].Cells["userGroupNameColumn"].Value, userGroupNames);
                if (ruleID != 0) dataGridView.Rows[e.RowIndex].Cells["userGroupIDColumn"].Value = ruleID;
            }
        }

        /// <summary>
        /// User permissions data grid view cell formatting event handler
        /// </summary>
        private void userPermissionsDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "userPermissionNameColumn") &&
                (e.RowIndex >= 0) &&
                (e.RowIndex < dbManager.fkUserPermissionsUsersBindingSource.Count) &&
                (!(dataGridView.Rows[e.RowIndex].Cells["userPermissionIDColumn"].Value is System.DBNull)) &&
                (userPermissionNameColumn.Items.Count > 0) &&
                (userPermissionNames != null) && (userPermissionNames.Count > 0))
            {
                // Set decrypted rule name
                e.Value = GetDictionaryValueByID((int)dataGridView.Rows[e.RowIndex].Cells["userPermissionIDColumn"].Value, userPermissionNames);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// User permissions data grid view cell value changed event handler
        /// </summary>
        private void userPermissionsDataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "userPermissionNameColumn") &&
                (userPermissionNameColumn.Items.Count > 0))
            {
                int ID = GetDictionaryIDByValue((string)dataGridView.Rows[e.RowIndex].Cells["userPermissionNameColumn"].Value, userPermissionNames);
                if (ID != 0) dataGridView.Rows[e.RowIndex].Cells["userPermissionIDColumn"].Value = ID;
            }
        }

        /// <summary>
        /// User groups information page enter event handler
        /// </summary>
        private void usrGroupsInfoPage_Enter(object sender, EventArgs e)
        {
            GetUserGroupsNames(userGroupNameColumn);
        }

        /// <summary>
        /// User password types combo box selected item changed event handler
        /// </summary>
        private void userPwdTypeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            int pwdTypeID = GetDictionaryIDByValue(userPwdTypeComboBox.Text, passwordTypeNames);
            if ((pwdTypeID != -1) && (dbManager.usersBindingSource.Current != null))
            {
                (dbManager.usersBindingSource.Current as DataRowView).Row["PwdTypeID"] = pwdTypeID;
            }
        }

        /// <summary>
        /// User check values grid view cell formating event handler
        /// </summary>
         private void userCheckValuesDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
         {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "userCheckValueColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["userCheckValueColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["userCheckValueColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["userCheckValueColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }
         }

         /// <summary>
         /// User check values grid view cell parsing event handler
         /// </summary>
         private void userCheckValuesDataGridView_CellParsing(object sender, DataGridViewCellParsingEventArgs e)
         {
             // Get sender
             DataGridView dataGridView = (DataGridView)sender;

             // Check column
             if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) &&
                 (dataGridView.Columns[e.ColumnIndex].Name == "userCheckValueColumn"))
             {
                 // Encrypt data
                 dataGridView[e.ColumnIndex, e.RowIndex].Value = encryptor.EncryptString(e.Value.ToString());
                 dataGridView.RefreshEdit();
                 e.ParsingApplied = true;
             }
         }

         /// <summary>
         /// User names grid view cell formating event handler
         /// </summary>
         private void userNamesDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
         {
             // Get sender
             DataGridView dataGridView = (DataGridView)sender;

             // Check column
             if ((e.ColumnIndex >= 0) &&
                 (dataGridView.Columns[e.ColumnIndex].Name == "userNameColumn") &&
                 (e.RowIndex >= 0) &&
                 (dataGridView["userNameColumn", e.RowIndex].Value is byte[]) &&
                 (!(dataGridView["userNameColumn", e.RowIndex].Value is System.DBNull)))
             {
                 // Decrypt data
                 e.Value = encryptor.DecryptString((byte[])dataGridView["userNameColumn", e.RowIndex].Value);
                 e.FormattingApplied = true;
             }
         }

        /// <summary>
         /// User names grid view cell parsing event handler
        /// </summary>
         private void userNamesDataGridView_CellParsing(object sender, DataGridViewCellParsingEventArgs e)
         {
             // Get sender
             DataGridView dataGridView = (DataGridView)sender;

             // Check column
             if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) &&
                 (dataGridView.Columns[e.ColumnIndex].Name == "userNameColumn"))
             {
                 // Encrypt data
                 dataGridView[e.ColumnIndex, e.RowIndex].Value = encryptor.EncryptString(e.Value.ToString());
                 dataGridView.RefreshEdit();
                 e.ParsingApplied = true;
             }
         }

         /// <summary>
         /// User accounts grid view cell formating event handler
         /// </summary>
         private void userAccountsDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
         {
             // Get sender
             DataGridView dataGridView = (DataGridView)sender;

             // Check column
             if ((e.ColumnIndex >= 0) &&
                 (dataGridView.Columns[e.ColumnIndex].Name == "accountUserNameColumn") &&
                 (e.RowIndex >= 0) &&
                 (dataGridView["accountUserNameColumn", e.RowIndex].Value is byte[]) &&
                 (!(dataGridView["accountUserNameColumn", e.RowIndex].Value is System.DBNull)))
             {
                 // Decrypt data
                 e.Value = encryptor.DecryptString((byte[])dataGridView["accountUserNameColumn", e.RowIndex].Value);
                 e.FormattingApplied = true;
             }

             if ((e.ColumnIndex >= 0) &&
                 (dataGridView.Columns[e.ColumnIndex].Name == "accountPasswordColumn") &&
                 (e.RowIndex >= 0) &&
                 (dataGridView["accountPasswordColumn", e.RowIndex].Value is byte[]) &&
                 (!(dataGridView["accountPasswordColumn", e.RowIndex].Value is System.DBNull)))
             {
                 // Decrypt data
                 string pwdStr = encryptor.DecryptString((byte[])dataGridView["accountPasswordColumn", e.RowIndex].Value);
                 DataGridViewCell cell = dataGridView.Rows[e.RowIndex].Cells[e.ColumnIndex];
                 if (pwdStr.Length > 0)
                 {
                     e.Value = new string('*', pwdStr.Length);
                     if (supervisor) cell.ToolTipText = pwdStr;
                     else cell.ToolTipText = "";
                 }
                 else
                 {
                     e.Value = "";
                     cell.ToolTipText = "";
                 }
                 
                 e.FormattingApplied = true;
             }
         }

         /// <summary>
         /// User accounts grid view cell parsing event handler
         /// </summary>
         private void userAccountsDataGridView_CellParsing(object sender, DataGridViewCellParsingEventArgs e)
         {
             // Get sender
             DataGridView dataGridView = (DataGridView)sender;

             // Check column
             if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) && 
                 (dataGridView.Columns[e.ColumnIndex].Name == "accountUserNameColumn") /*|| (dataGridView.Columns[e.ColumnIndex].Name == "accountPasswordColumn")*/)
             {
                 // Encrypt data
                 dataGridView[e.ColumnIndex, e.RowIndex].Value = encryptor.EncryptString(e.Value.ToString());
                 dataGridView.RefreshEdit();
                 e.ParsingApplied = true;
             }
         }

        /// <summary>
        /// Change user account password button click
        /// </summary>
        private void usersBindingNavigatorChangeUsrAccountPasswordItem_Click(object sender, EventArgs e)
        {
            if (dbManager.fkUserAccountsUsersBindingSource.Current != null)
            {
                fmChangePassword fmChangePwd = new fmChangePassword(supervisor);
                fmChangePwd.ShowDialog();

                if (fmChangePwd.PasswordChanged)
                {
                    string uaName = encryptor.DecryptString((dbManager.fkUserAccountsUsersBindingSource.Current as DataRowView).Row["UserName"] as byte[]);

                    if (fmChangePwd.Password.Length > 0)
                    {
                        logWriter.WriteToLog("User management --> Password for account of user '" + userNameTextBox.Text + "' with user ID '" + uaName + "' was changed!");
                        (dbManager.fkUserAccountsUsersBindingSource.Current as DataRowView).Row["Password"] = encryptor.EncryptString(fmChangePwd.Password);
                    }
                    else
                    {
                        logWriter.WriteToLog("User management --> Password for account of user '" + userNameTextBox.Text + "' with user ID '" + uaName + "' was deleted!");
                        (dbManager.fkUserAccountsUsersBindingSource.Current as DataRowView).Row["Password"] = null;
                    }
                }
            }
        }

         /// <summary>
         /// User check values grid view data error event handler
         /// </summary>
         private void userCheckValuesDataGridView_DataError(object sender, DataGridViewDataErrorEventArgs e)
         {
             DataGridView dataGridView = (DataGridView)sender;
             if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0))
             {
                 string errorText = dataGridView[e.ColumnIndex, e.RowIndex].ErrorText;
             }
         }

         /// <summary>
         /// Users binding navigator password settings button click
         /// </summary>
         private void usersBindingNavigatorChangePasswordItem_Click(object sender, EventArgs e)
         {
             int pwdType = -1;
             if (dbManager.usersBindingSource.Current != null)
                 pwdType = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["PwdTypeID"];

             bool isOK = false;

             switch (pwdType)
             {
                 case fmConnect.CASCADE_STRING_PWD:
                     {
                         fmCascadeStringPwdSettings fmPwd = new fmCascadeStringPwdSettings(dbManager, encryptor, false);
                         fmPwd.ShowDialog();

                         isOK = fmPwd.Commited;

                         break;
                     }

                 case fmConnect.ONE_SYMBOL_BOX_PWD:
                 case fmConnect.TWO_SYMBOL_BOX_PWD:
                     {
                         fmSymbolBoxesPwdSettings fmPwd = new fmSymbolBoxesPwdSettings(dbManager, encryptor, false);
                         fmPwd.ShowDialog();

                         isOK = fmPwd.Commited;

                         break;
                     }
             }

             if (isOK)
             {
                 logWriter.WriteToLog("User management --> Password for user '" + userNameTextBox.Text + "' was changed!");
             }
         }

        /// <summary>
        /// Reset password button click 
        /// </summary>
         private void usersBindingNavigatorPasswordResetItem_Click(object sender, EventArgs e)
         {
             if (dbManager.usersBindingSource.Current != null)
             {
                 string message = String.Format("User {0} tries to reset password for user {1}", currentUserName, userNameTextBox.Text);
                 logWriter.WriteToLog(message);

                 int userID = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["ID"];
                 if (_serverConnector != null)
                     _serverConnector.ResetUserPassword(userID);
             }
         }

        /// <summary>
        /// Users binding navigator save button click
        /// </summary>
        private void usersBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.usersBindingSource.EndEdit();
            dbManager.fkUserCheckValuesUsersBindingSource.EndEdit();
            dbManager.fkUserPermissionsUsersBindingSource.EndEdit();
            dbManager.fkUserAccountsUsersBindingSource.EndEdit();
            dbManager.fkUserGroupsUsersBindingSource.EndEdit();

            SyncUserAccountOnEdit();
            SyncUserGroupOnEdit();
            SyncUserGroupMembers();

            dbManager.UpdateUsers();
            dbManager.UpdateUserGroupUsers();
            dbManager.UpdateUserPermissions();
            dbManager.UpdateUserCheckValues();
            dbManager.UpdateUserAccounts();
        }

        /// <summary>
        /// Users binding navigator refresh button click
        /// </summary>
        private void usersBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            // Fill data adapters
            dbManager.usersTableAdapter.Fill(dbManager.dataSet.Users);
            dbManager.userGroupUsersTableAdapter.Fill(dbManager.dataSet.UserGroupUsers);
            dbManager.userCheckValuesTableAdapter.Fill(dbManager.dataSet.UserCheckValues);
            dbManager.userAccountsTableAdapter.Fill(dbManager.dataSet.UserAccounts);
            dbManager.userAccountsArchiveTableAdapter.Fill(dbManager.dataSet.UserAccountsArchive);
            dbManager.userPermissionsTableAdapter.Fill(dbManager.dataSet.UserPermissions);
            dbManager.permissionsTableAdapter.Fill(dbManager.dataSet.Permissions);
            dbManager.userCheckValuesScreenObjectsTableAdapter.Fill(dbManager.dataSet.UserCheckValuesScreenObjects);
            dbManager.presetTableAdapter.Fill(dbManager.dataSet.Preset);
        }

        /// <summary>
        /// Users binding navigator position changed event handler
        /// </summary>
        private void usersBindingSource_PositionChanged(object sender, EventArgs e)
        {
            userNameTextBox_Leave(null, null);
            userEmailTextBox_Leave(null, null);
            userPhoneTextBox_Leave(null, null);

            // Check column
            if ((dbManager.usersBindingSource.Current != null) &&
                (!((dbManager.usersBindingSource.Current as DataRowView).Row["UserName"] is System.DBNull)))
            {
                // Decrypt user name
                userNameTextBox.Text = encryptor.DecryptString((byte[])(dbManager.usersBindingSource.Current as DataRowView).Row["UserName"]);
            }
            else
                userNameTextBox.Text = "";

            // Check column
            if ((dbManager.usersBindingSource.Current != null) &&
                (!((dbManager.usersBindingSource.Current as DataRowView).Row["Email"] is System.DBNull)))
            {
                // Decrypt user email
                userEmailTextBox.Text = encryptor.DecryptString((byte[])(dbManager.usersBindingSource.Current as DataRowView).Row["Email"]);
            }
            else
                userEmailTextBox.Text = "";

            // Check column
            if ((dbManager.usersBindingSource.Current != null) &&
                (!((dbManager.usersBindingSource.Current as DataRowView).Row["Phone"] is System.DBNull)))
            {
                // Decrypt user email
                userPhoneTextBox.Text = encryptor.DecryptString((byte[])(dbManager.usersBindingSource.Current as DataRowView).Row["Phone"]);
            }
            else
                userPhoneTextBox.Text = "";

            // Password type
            if ((dbManager.usersBindingSource.Current != null) &&
                (!((dbManager.usersBindingSource.Current as DataRowView).Row["PwdTypeID"] is System.DBNull)))
                userPwdTypeComboBox.Text = GetDictionaryValueByID((int)(dbManager.usersBindingSource.Current as DataRowView).Row["PwdTypeID"], passwordTypeNames);
            else
                userPwdTypeComboBox.Text = "";
        }

        /// <summary>
        /// User names data grid view sorted event handler
        /// </summary>
        private void userNamesDataGridView_Sorted(object sender, EventArgs e)
        {
            usersBindingSource_PositionChanged(null, null);
        }

        /// <summary>
        /// User system password text box leave event handler
        /// </summary>
        private void userNameTextBox_Leave(object sender, EventArgs e)
        {
            // Check modified flag
            if ((userNameTextBox.Modified) && (dbManager.usersBindingSource.Current != null))
            {
                // Check text box value
                if (userNameTextBox.Text != "")
                {
                    // Encrypt user name
                    (dbManager.usersBindingSource.Current as DataRowView).Row["UserName"] = encryptor.EncryptString(userNameTextBox.Text);
                }
                else
                    (dbManager.usersBindingSource.Current as DataRowView).Row["UserName"] = System.DBNull.Value;

                userNameTextBox.Modified = false;
            }
         }

        /// <summary>
        /// User email text box leave event handler
        /// </summary>
        private void userEmailTextBox_Leave(object sender, EventArgs e)
        {
            // Check modified flag
            if ((userEmailTextBox.Modified) && (dbManager.usersBindingSource.Current != null))
            {
                // Check text box value
                if (userEmailTextBox.Text != "")
                {
                    // Encrypt user email
                    (dbManager.usersBindingSource.Current as DataRowView).Row["Email"] = encryptor.EncryptString(userEmailTextBox.Text);
                }
                else
                    (dbManager.usersBindingSource.Current as DataRowView).Row["Email"] = System.DBNull.Value;

                userEmailTextBox.Modified = false;
            }
        }

        /// <summary>
        /// User Phone text box leave event handler
        /// </summary>
        private void userPhoneTextBox_Leave(object sender, EventArgs e)
        {
            // Check modified flag
            if ((userPhoneTextBox.Modified) && (dbManager.usersBindingSource.Current != null))
            {
                // Check text box value
                if (userPhoneTextBox.Text != "")
                {
                    // Encrypt user phone
                    (dbManager.usersBindingSource.Current as DataRowView).Row["Phone"] = encryptor.EncryptString(userPhoneTextBox.Text);
                }
                else
                    (dbManager.usersBindingSource.Current as DataRowView).Row["Phone"] = System.DBNull.Value;

                userPhoneTextBox.Modified = false;
            }
        }
                
        /// <summary>
        /// User names data grid view enter event handler
        /// </summary>
        private void userNamesDataGridView_Enter(object sender, EventArgs e)
        {
            usersBindingNavigator.BindingSource = dbManager.usersBindingSource;
        }
           
        /// <summary>
        /// User check values data grid view enter event handler
        /// </summary>
        private void userCheckValuesDataGridView_Enter(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.usersBindingSource.EndEdit();
            if (dbManager.dataSet.Users.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateUsers();

            usersBindingNavigator.BindingSource = dbManager.fkUserCheckValuesUsersBindingSource;
        }

        /// <summary>
        /// User permissions data grim view enter event handler
        /// </summary>
        private void userPermissionsDataGridView_Enter(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.usersBindingSource.EndEdit();
            if (dbManager.dataSet.Users.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateUsers();

            usersBindingNavigator.BindingSource = dbManager.fkUserPermissionsUsersBindingSource;
        }

        /// <summary>
        /// User group users data grid view enter event handler
        /// </summary>
        private void userGroupsDataGridView_Enter(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.usersBindingSource.EndEdit();
            if (dbManager.dataSet.Users.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateUsers();

            usersBindingNavigator.BindingSource = dbManager.fkUserGroupsUsersBindingSource;
        }

        /// <summary>
        /// User accounts data grim view enter event handler
        /// </summary>
        private void userAccountsDataGridView_Enter(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            
            dbManager.usersBindingSource.EndEdit();
            if (dbManager.dataSet.Users.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateUsers();

            dbManager.authSystemsBindingSource.EndEdit();
            if (dbManager.dataSet.AuthSystems.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateAuthSystems();
                        
            usersBindingNavigator.BindingSource = dbManager.fkUserAccountsUsersBindingSource;
        }

        /// <summary>
        /// Users achive button click
        /// </summary>
        private void usersBindingNavigatorArchiveItem_Click(object sender, EventArgs e)
        {
            // Create connection window
            fmUserAccountsArchive _fmUserAccountsArchive = new fmUserAccountsArchive(dbManager, supervisor, logWriter);
            _fmUserAccountsArchive.ShowDialog();
        }

        /// <summary>
        /// User groups button click
        /// </summary>
        private void usersBindingNavigatorGroupsItem_Click(object sender, EventArgs e)
        {
            if (dbManager.fkUserAccountsUsersBindingSource.Current != null)
            {
                int authSystemID = (int)(dbManager.fkUserAccountsUsersBindingSource.Current as DataRowView).Row["AuthSystemID"];
                byte[] encUserName = (dbManager.fkUserAccountsUsersBindingSource.Current as DataRowView).Row["UserName"] as byte[];
                string decUserName = encryptor.DecryptString(encUserName);
                string filterExpr = "ID = " + authSystemID.ToString();
                DataRow[] selRows = dbManager.dataSet.AuthSystems.Select(filterExpr);
                byte[] encSettingsString = selRows[0]["SettingsString", DataRowVersion.Original] as byte[];
                string decSettingsString = encryptor.DecryptString(encSettingsString);
                string authSystemName = selRows[0]["Name", DataRowVersion.Original].ToString();
                int authSystemType = (int)(selRows[0]["AuthSystemTypeID", DataRowVersion.Original]);
                short moveGroupUsers = (short)(selRows[0]["MoveGroupUsers", DataRowVersion.Original]);

                List<string> userGroupsList = null;
                List<string> groupsList = null;

                switch (authSystemType)
                {
                    case UserAccountsSynchronizer.UAC_AD:
                        {
                            userGroupsList = userAccountsSynchronizer.EnumerateADUserGroups(decSettingsString, decUserName);
                            groupsList = userAccountsSynchronizer.EnumerateADGroupsWithoutUser(decSettingsString, decUserName);

                            break;
                        }
                }

                fmUserGroups _fmUserGroups = new fmUserGroups(userGroupsList, groupsList, authSystemName, decUserName);
                _fmUserGroups.ShowDialog();

                bool addResult = true;
                bool removeResult = true;

                if (_fmUserGroups.saveResults)
                {
                    switch (authSystemType)
                    {
                        case UserAccountsSynchronizer.UAC_AD:
                            {
                                if ((_fmUserGroups.userGroupsToAdd.Count > 0) || (_fmUserGroups.userGroupsToRemove.Count > 0))
                                    logWriter.WriteToLog("User management --> Management of user accounts groups");

                                for (int i = 0; i < _fmUserGroups.userGroupsToAdd.Count; i++)
                                {
                                    addResult = userAccountsSynchronizer.AddADUserToGroup(decSettingsString, decUserName, _fmUserGroups.userGroupsToAdd[i]) && addResult;
                                    logWriter.WriteToLog("User management --> Account of user '" + userNameTextBox.Text + "' with  user ID '" + decUserName + "' was added to group '" + _fmUserGroups.userGroupsToAdd[i] + "'");
                                    if (moveGroupUsers != 0)
                                        addResult = userAccountsSynchronizer.SyncAddUserAccountsGroups(_fmUserGroups.userGroupsToAdd[i], decUserName, authSystemID) && addResult;
                                }

                                for (int i = 0; i < _fmUserGroups.userGroupsToRemove.Count; i++)
                                {
                                    removeResult = userAccountsSynchronizer.RemoveADUserFromGroup(decSettingsString, decUserName, _fmUserGroups.userGroupsToRemove[i]) && removeResult;
                                    logWriter.WriteToLog("User management --> Account of user '" + userNameTextBox.Text + "' with  user ID '" + decUserName + "' was removed from group '" + _fmUserGroups.userGroupsToRemove[i] + "'");
                                    if (moveGroupUsers != 0)
                                        removeResult = userAccountsSynchronizer.SyncRemoveUserAccountsGroups(_fmUserGroups.userGroupsToRemove[i], decUserName, authSystemID) && removeResult;
                                }

                                break;
                            }
                    }
                }

                if (!addResult)
                {
                    MessageBox.Show("Addition the user to the some group was finished with error!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("User management --> Addition the user to the some group was finished with error!");
                }

                if (!removeResult)
                {
                    MessageBox.Show("Removing the user from the some group was finished with error!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("User management --> Removing the user from the some group was finished with error!");
                }
            }
        }

        /// <summary>
        /// Sync on edit
        /// </summary>
        private void SyncUserAccountOnEdit()
        {
            // Get deleted rows
            DataRow[] userAccountsDeletedRows = dbManager.dataSet.UserAccounts.Select(null, null, DataViewRowState.Deleted);
            // Get inserted rows
            DataRow[] userAccountsInsertedRows = dbManager.dataSet.UserAccounts.Select(null, null, DataViewRowState.Added);
            // Get updated rows
            DataRow[] userAccountsUpdatedRows = dbManager.dataSet.UserAccounts.Select(null, null, DataViewRowState.ModifiedCurrent);

            if (userAccountsDeletedRows != null)
            {
                // Move user accounts to archive
                if (settingsManager.GetUserAccountDeleteDBAction() == 1)
                    dbManager.PutUserAccountsToArchive(userAccountsDeletedRows);

                // Sync deleted accounts
                userAccountsSynchronizer.SyncADAccounts(userAccountsDeletedRows, UserAccountsSynchronizer.UA_SYNC_DELETE);
            }

            // Sync insertrted accounts
            if (userAccountsInsertedRows != null)
                userAccountsSynchronizer.SyncADAccounts(userAccountsInsertedRows, UserAccountsSynchronizer.UA_SYNC_INSERT);

            // Sync updated accounts
            if (userAccountsUpdatedRows != null)
                userAccountsSynchronizer.SyncADAccounts(userAccountsUpdatedRows, UserAccountsSynchronizer.UA_SYNC_UPDATE);
        }

        

        #endregion

        #region User groups management

        // User groups settings controls flag
        private bool _userGroupsContorlsCustomized;

        /// <summary>
        /// Customize user groups controls
        /// </summary>
        private void CustomizeUserGroupsControls()
        {
            // Check flag
            if(!_userGroupsContorlsCustomized)
            {
                // User groups binding navigator
                groupsBindingNavigator.BindingSource = dbManager.userGroupsBindingSource;

                // Customize user groups list data grid view
                groupsDataGridView.AutoGenerateColumns = false;
                groupsDataGridView.DataSource = dbManager.userGroupsBindingSource;
                groupNameColumn.DataPropertyName = "Name";
                groupDescriptionColumn.DataPropertyName = "Description";
                
                // User group permissions values
                groupPermissionsDataGridView.AutoGenerateColumns = false;
                groupPermissionsDataGridView.DataSource = dbManager.fkUserGroupsUsersGroupPermissionsBindingSource;
                groupPermissionIDColumn.DataPropertyName = "PermissionID";

                // User group users values
                usersGroupDataGridView.AutoGenerateColumns = false;
                usersGroupDataGridView.DataSource = dbManager.fkUsersUserGroupsBindingSource;
                groupUserIDColumn.DataPropertyName = "UserID";

                // User group auth systems values
                groupGroupAuthSystemsDataGridView.AutoGenerateColumns = false;
                groupGroupAuthSystemsDataGridView.DataSource = dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource;
                groupAuthSystemColumn.DataSource = dbManager.userGroupsAuthSystemsBindingSource;
                groupAuthSystemColumn.DataPropertyName = "AuthSystemID";
                groupAuthSystemColumn.DisplayMember = "Name";
                groupAuthSystemColumn.ValueMember = "ID";
                authGroupNameColumn.DataPropertyName = "GroupName";

                _userGroupsContorlsCustomized = true;
            }

            // Get user names
            GetUserNames(groupUserNameColumn);
        }

        /// <summary>
        /// User groups data grid view cell formating event handler
        /// </summary>
        private void groupsDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "groupNameColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["groupNameColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["groupNameColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["groupNameColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }

            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "groupDescriptionColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["groupDescriptionColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["groupDescriptionColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["groupDescriptionColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// User groups data grid view cell parsing event handler
        /// </summary>
        private void groupsDataGridView_CellParsing(object sender, DataGridViewCellParsingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) &&
                ((dataGridView.Columns[e.ColumnIndex].Name == "groupNameColumn") || (dataGridView.Columns[e.ColumnIndex].Name == "groupDescriptionColumn")))
            {
                // Encrypt data
                dataGridView[e.ColumnIndex, e.RowIndex].Value = encryptor.EncryptString(e.Value.ToString());
                dataGridView.RefreshEdit();
                e.ParsingApplied = true;
            }
        }

        /// <summary>
        /// User group permissions data grid view cell formatting event handler
        /// </summary>
        private void groupPermissionsDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "groupPermissionsColumn") &&
                (e.RowIndex >= 0) &&
                (e.RowIndex < dbManager.fkUserGroupsUsersGroupPermissionsBindingSource.Count) &&
                (!(dataGridView.Rows[e.RowIndex].Cells["groupPermissionIDColumn"].Value is System.DBNull)) &&
                (groupPermissionsColumn.Items.Count > 0) &&
                (userPermissionNames != null) && (userPermissionNames.Count > 0))
            {
                // Set decrypted rule name
                e.Value = GetDictionaryValueByID((int)dataGridView.Rows[e.RowIndex].Cells["groupPermissionIDColumn"].Value, userPermissionNames);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// User group permissions data grid view cell value changed event handler
        /// </summary>
        private void groupPermissionsDataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "groupPermissionsColumn") &&
                (groupPermissionsColumn.Items.Count > 0))
            {
                int ID = GetDictionaryIDByValue((string)dataGridView.Rows[e.RowIndex].Cells["groupPermissionsColumn"].Value, userPermissionNames);
                if (ID != 0) dataGridView.Rows[e.RowIndex].Cells["groupPermissionIDColumn"].Value = ID;
            }
        }

        /// <summary>
        /// Group users data grid view cell formatting event handler
        /// </summary>
        private void usersGroupDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "groupUserNameColumn") &&
                (e.RowIndex >= 0) &&
                (e.RowIndex < dbManager.fkUsersUserGroupsBindingSource.Count) &&
                (!(dataGridView.Rows[e.RowIndex].Cells["groupUserIDColumn"].Value is System.DBNull)) &&
                (groupUserNameColumn.Items.Count > 0) &&
                (userNames != null) && (userNames.Count > 0))
            {
                // Set decrypted rule name
                e.Value = GetDictionaryValueByID((int)dataGridView.Rows[e.RowIndex].Cells["groupUserIDColumn"].Value, userNames);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Group users data grid view cell value changed event handler
        /// </summary>
        private void usersGroupDataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "groupUserNameColumn") &&
                (groupUserNameColumn.Items.Count > 0))
            {
                int ID = GetDictionaryIDByValue((string)dataGridView.Rows[e.RowIndex].Cells["groupUserNameColumn"].Value, userNames);
                if (ID != 0) dataGridView.Rows[e.RowIndex].Cells["groupUserIDColumn"].Value = ID;
            }
        }

        /// <summary>
        /// User groups auth systems data grid view cell formating event handler
        /// </summary>
        private void groupGroupAuthSystemsDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "authGroupNameColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["authGroupNameColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["authGroupNameColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["authGroupNameColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// User groups auth systems data grid view cell parsing event handler
        /// </summary>
        private void groupGroupAuthSystemsDataGridView_CellParsing(object sender, DataGridViewCellParsingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "authGroupNameColumn"))
            {
                // Encrypt data
                dataGridView[e.ColumnIndex, e.RowIndex].Value = encryptor.EncryptString(e.Value.ToString());
                dataGridView.RefreshEdit();
                e.ParsingApplied = true;
            }
        }

        /// <summary>
        /// User groups data grid view enter event handler
        /// </summary>
        private void groupsDataGridView_Enter(object sender, EventArgs e)
        {
            groupsBindingNavigator.BindingSource = dbManager.userGroupsBindingSource;
        }

        /// <summary>
        /// User group permissions data grid view enter event handler
        /// </summary>
        private void groupPermissionsDataGridView_Enter(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.userGroupsBindingSource.EndEdit();

            if (dbManager.dataSet.UserGroups.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateUserGroups();

            groupsBindingNavigator.BindingSource = dbManager.fkUserGroupsUsersGroupPermissionsBindingSource;
        }

        /// <summary>
        /// User group auth systems data grid view enter event handler
        /// </summary>
        private void groupGroupAuthSystemsDataGridView_Enter(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.userGroupsBindingSource.EndEdit();

            if (dbManager.dataSet.UserGroups.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateUserGroups();

            dbManager.authSystemsBindingSource.EndEdit();
            if (dbManager.dataSet.AuthSystems.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateAuthSystems();

            groupsBindingNavigator.BindingSource = dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource;
        }

        /// <summary>
        /// User group users data grid view enter event handler
        /// </summary>
        private void usersGroupDataGridView_Enter(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.userGroupsBindingSource.EndEdit();

            if (dbManager.dataSet.UserGroups.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateUserGroups();

            groupsBindingNavigator.BindingSource = dbManager.fkUsersUserGroupsBindingSource;
        }

        /// <summary>
        /// User group save item click
        /// </summary>
        private void groupsBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.userGroupsBindingSource.EndEdit();
            dbManager.fkUserGroupsUsersGroupPermissionsBindingSource.EndEdit();
            dbManager.fkUsersUserGroupsBindingSource.EndEdit();
            dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.EndEdit();

            SyncUserGroupOnEdit();
            SyncUserGroupMembers();

            dbManager.UpdateUserGroups();
            dbManager.UpdateUserGroupPermissions();
            dbManager.UpdateUserGroupAuthSystems();
            dbManager.UpdateUserGroupUsers();
        }

        /// <summary>
        /// User group refresh item click
        /// </summary>
        private void groupsBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            // Fill data adapters
            dbManager.userGroupsTableAdapter.Fill(dbManager.dataSet.UserGroups);
            dbManager.userGroupUsersTableAdapter.Fill(dbManager.dataSet.UserGroupUsers);
            dbManager.userGroupAuthSystemsTableAdapter.Fill(dbManager.dataSet.UserGroupAuthSystems);
            dbManager.userGroupEducationTableAdapter.Fill(dbManager.dataSet.UserGroupEducation);
            dbManager.userGroupNotificationsTableAdapter.Fill(dbManager.dataSet.UserGroupNotifications);
            dbManager.userGroupPermissionsTableAdapter.Fill(dbManager.dataSet.UserGroupPermissions);
        }

        /// <summary>
        /// Group settings button click
        /// </summary>
        private void userGroupSettingsButton_Click(object sender, EventArgs e)
        {
            if (dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.Current != null)
            {
                int authSystemID = (int)(dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.Current as DataRowView).Row["AuthSystemID"];
                DataRow[] selRows = dbManager.dataSet.AuthSystems.Select("ID = " + authSystemID.ToString());
                int authSystemType = ((selRows != null) && (selRows.Length > 0)) ? (int)selRows[0]["AuthSystemTypeID", DataRowVersion.Original] : -1;

                logWriter.WriteToLog("Authentication systems management --> Trying to change user group settings");

                switch (authSystemType)
                {
                    case UserAccountsSynchronizer.UAC_AD:
                        {
                            logWriter.WriteToLog("Authentication systems management --> Type of current authentication system is AD");

                            string setStr = "";

                            if (!((dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.Current as DataRowView).Row["GroupSettings"] is System.DBNull))
                            {
                                // Decrypt settings string
                                setStr = encryptor.DecryptString((byte[])(dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.Current as DataRowView).Row["GroupSettings"]);
                            }

                            // Create AD settings window
                            fmADGroupSettings _fmADGroupSettings = new fmADGroupSettings(setStr, logWriter);
                            _fmADGroupSettings.ShowDialog();

                            setStr = _fmADGroupSettings.settingsString;

                            if (setStr != "")
                            {
                                // Encrypt user name
                                (dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.Current as DataRowView).Row["GroupSettings"] = encryptor.EncryptString(setStr);
                            }
                            else
                                (dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.Current as DataRowView).Row["GroupSettings"] = System.DBNull.Value;

                            break;
                        }
                }
            }
        }

        /// <summary>
        /// Group users button click
        /// </summary>
        private void groupUsersButton_Click(object sender, EventArgs e)
        {
            if (dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.Current != null)
            {
                int authSystemID = (int)(dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.Current as DataRowView).Row["AuthSystemID"];
                byte[] encGroupName = (dbManager.fkUserGroupsUsersGroupAuthSystemsBindingSource.Current as DataRowView).Row["GroupName"] as byte[];
                string decGroupName = encryptor.DecryptString(encGroupName);
                string filterExpr = "ID = " + authSystemID.ToString();
                DataRow[] selRows = dbManager.dataSet.AuthSystems.Select(filterExpr);
                byte[] encSettingsString = selRows[0]["SettingsString", DataRowVersion.Original] as byte[];
                string decSettingsString = encryptor.DecryptString(encSettingsString);
                string authSystemName = selRows[0]["Name", DataRowVersion.Original].ToString();
                int authSystemType = (int)(selRows[0]["AuthSystemTypeID", DataRowVersion.Original]);
                short moveGroupUsers = (short)(selRows[0]["MoveGroupUsers", DataRowVersion.Original]);

                List<string> groupUsersList = null;
                List<string> usersList = null;

                switch (authSystemType)
                {
                    case UserAccountsSynchronizer.UAC_AD:
                        {
                            groupUsersList = userAccountsSynchronizer.EnumerateADUsersOfSomeGroup(decSettingsString, decGroupName);
                            usersList = userAccountsSynchronizer.EnumerateADUserAcccountsWithoutGroup(decSettingsString, decGroupName);
                            break;
                        }
                }

                fmGroupUsers _fmGroupUsers = new fmGroupUsers(groupUsersList, usersList, authSystemName, decGroupName);
                _fmGroupUsers.ShowDialog();

                bool addResult = true;
                bool removeResult = true;

                if (_fmGroupUsers.saveResults)
                {
                    switch (authSystemType)
                    {
                        case UserAccountsSynchronizer.UAC_AD:
                            {
                                if ((_fmGroupUsers.groupUsersToAdd.Count > 0) || (_fmGroupUsers.groupUsersToRemove.Count > 0))
                                    logWriter.WriteToLog("User management --> Management of user accounts groups");

                                for (int i = 0; i < _fmGroupUsers.groupUsersToAdd.Count; i++)
                                {
                                    addResult = userAccountsSynchronizer.AddADUserToGroup(decSettingsString, _fmGroupUsers.groupUsersToAdd[i], decGroupName) && addResult;
                                 
                                    logWriter.WriteToLog("User management --> Account of user '" + _fmGroupUsers.groupUsersToAdd[i] + "' was added to group '" + decGroupName + "'");
                                    if (moveGroupUsers != 0)
                                        addResult = userAccountsSynchronizer.SyncAddUserAccountsGroups(decGroupName, _fmGroupUsers.groupUsersToAdd[i], authSystemID) && addResult;
                                }

                                for (int i = 0; i < _fmGroupUsers.groupUsersToRemove.Count; i++)
                                {
                                    removeResult = userAccountsSynchronizer.RemoveADUserFromGroup(decSettingsString, _fmGroupUsers.groupUsersToRemove[i], decGroupName) && removeResult;
                                    logWriter.WriteToLog("User management --> Account of user '" + _fmGroupUsers.groupUsersToRemove[i] + "' was removed from group '" + decGroupName + "'");
                                    if (moveGroupUsers != 0)
                                        removeResult = userAccountsSynchronizer.SyncRemoveUserAccountsGroups(decGroupName, _fmGroupUsers.groupUsersToRemove[i], authSystemID) && removeResult;
                                }

                                break;
                            }
                    }
                }

                if (!addResult)
                {
                    MessageBox.Show("Addition of some user to the group was finished with error!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("User management --> Addition of some user to the group was finished with error!");
                }

                if (!removeResult)
                {
                    MessageBox.Show("Removing of some user from the group was finished with error!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("User management --> Removing of some user from the group was finished with error!");
                }
            }
        }

        /// <summary>
        /// Sync on edit
        /// </summary>
        private void SyncUserGroupOnEdit()
        {
            // Get deleted rows
            DataRow[] userGroupsDeletedRows = dbManager.dataSet.UserGroupAuthSystems.Select(null, null, DataViewRowState.Deleted);
            // Get inserted rows
            DataRow[] userGroupsInsertedRows = dbManager.dataSet.UserGroupAuthSystems.Select(null, null, DataViewRowState.Added);
            // Get updated rows
            DataRow[] userGroupsUpdatedRows = dbManager.dataSet.UserGroupAuthSystems.Select(null, null, DataViewRowState.ModifiedCurrent);

            // Sync deleted groups
            if (userGroupsDeletedRows != null)
                userAccountsSynchronizer.SyncADGroups(userGroupsDeletedRows, UserAccountsSynchronizer.UA_SYNC_DELETE);

            // Sync insertrted groups
            if (userGroupsInsertedRows != null)
                userAccountsSynchronizer.SyncADGroups(userGroupsInsertedRows, UserAccountsSynchronizer.UA_SYNC_INSERT);

            // Sync updated groups
            if (userGroupsUpdatedRows != null)
                userAccountsSynchronizer.SyncADGroups(userGroupsUpdatedRows, UserAccountsSynchronizer.UA_SYNC_UPDATE);
        }

        /// <summary>
        /// Sync user group membership
        /// </summary>
        private void SyncUserGroupMembers()
        {
            DataRow[] userGroupUsersRows = dbManager.dataSet.UserGroupUsers.Select(null, null, DataViewRowState.CurrentRows);

            if (userGroupUsersRows != null)
            {
                foreach (DataRow row in userGroupUsersRows)
                {
                    int userID = (int)row["UserID"];
                    int groupID = (int)row["GroupID"];
                    SyncUserGroupMember(userID, groupID);
                }
            }
        }

        /// <summary>
        /// Sync user group membership
        /// </summary>
        /// <param name="userID">user ID</param>
        /// <param name="groupID">group ID</param>
        private void SyncUserGroupMember(int userID, int groupID)
        {
            
            string queryString = "SELECT UserGroupAuthSystems.GroupName, UserAccounts.UserName, AuthSystems.AuthSystemTypeID, AuthSystems.SettingsString, AuthSystems.MoveGroupUsers " +
                                    "FROM UserGroupAuthSystems, UserAccounts, AuthSystems " +
                                    "WHERE ((UserGroupAuthSystems.GroupID = @group_ID) AND " +
                                    "(UserAccounts.UserID = @user_ID) AND " +
                                    "(UserGroupAuthSystems.AuthSystemID = UserAccounts.AuthSystemID) AND " +
                                    "(UserGroupAuthSystems.AuthSystemID = AuthSystems.ID) AND " +
                                    "(UserAccounts.AuthSystemID = AuthSystems.ID))";

            SqlConnection connection = dbManager.connection as SqlConnection;
            connection.Open();

            SqlCommand command = new SqlCommand(queryString, connection);
            command.Parameters.AddWithValue("@user_ID", userID);
            command.Parameters.AddWithValue("@group_ID", groupID);

            SqlDataReader reader = command.ExecuteReader();

            try
            {
                while (reader.Read())
                {
                    byte[] encGroupName = reader["GroupName"] as byte[];
                    string decGroupName = encryptor.DecryptString(encGroupName);
                    byte[] encUserName = reader["UserName"] as byte[];
                    string decUserName = encryptor.DecryptString(encUserName);
                    byte[] encSettingsString = reader["SettingsString"] as byte[];
                    string decSettinsgString = encryptor.DecryptString(encSettingsString);
                    int authSystemTypeID = (int)reader["AuthSystemTypeID"];
                    short moveGroupUsers = (short)reader["MoveGroupUsers"];

                    if (moveGroupUsers != 0)
                    {
                        switch (authSystemTypeID)
                        {
                            case UserAccountsSynchronizer.UAC_AD:
                                {
                                    if (!(userAccountsSynchronizer.IsUserGroupMember(decSettinsgString, decUserName, decGroupName)))
                                        userAccountsSynchronizer.AddADUserToGroup(decSettinsgString, decUserName, decGroupName);

                                    break;
                                }
                        }
                    }
                }
            }
            finally
            {
                reader.Close();
                connection.Close();
            }
        }

        #endregion

        #region Computers management

        // Computers settings controls flag
        private bool _computersContorlsCustomized;

        /// <summary>
        /// Customize computers controls
        /// </summary>
        private void CustomizeComputersContols()
        {
            // Check flag
            if (!_computersContorlsCustomized)
            {
                // Computers binding navigator
                computersBindingNavigator.BindingSource = dbManager.computersBindingSource;

                // Customize computers data grid view
                computersDataGridView.AutoGenerateColumns = false;
                computersDataGridView.DataSource = dbManager.computersBindingSource;

                computerNameColumn.DataPropertyName = "Name";
                computerDescriptionColumn.DataPropertyName = "Description";

                _computersContorlsCustomized = true;
            }
        }

        /// <summary>
        /// Computers binding source save button
        /// </summary>
        private void computersBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.computersBindingSource.EndEdit();
            dbManager.UpdateComputers();
        }

        /// <summary>
        /// Computers binding source refresh button
        /// </summary>
        private void computersBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            // Fill data adapter
            dbManager.presetTableAdapter.Fill(dbManager.dataSet.Preset);
            dbManager.computersTableAdapter.Fill(dbManager.dataSet.Computers);
        }

        #endregion

        #region Authentication systems management

        // Auth systems settings controls flag
        private bool _authSystemsContorlsCustomized;

        /// <summary>
        /// Customize auth systems controls
        /// </summary>
        private void CustomizeAuthSystemsContols()
        {
            // Check flag
            if (!_authSystemsContorlsCustomized)
            {
                // Auth systems binding navigator
                authSystemsBindingNavigator.BindingSource = dbManager.authSystemsBindingSource;

                // Auth systems data grid view
                authSystemsDataGridView.AutoGenerateColumns = false;
                authSystemsDataGridView.DataSource = dbManager.authSystemsBindingSource;

                authSystemTypeColumn.DataSource = dbManager.authSystemTypesBindingSource;
                authSystemTypeColumn.DataPropertyName = "AuthSystemTypeID";
                authSystemTypeColumn.DisplayMember = "Name";
                authSystemTypeColumn.ValueMember = "ID";

                onDeleteActionColumn.DataSource = dbManager.userAccountActionsOnDeleteBindingSource;
                onDeleteActionColumn.DataPropertyName = "OnDeleteAction";
                onDeleteActionColumn.DisplayMember = "Name";
                onDeleteActionColumn.ValueMember = "ID";

                onInsertActionColumn.DataSource = dbManager.userAccountActionsOnInsertBindingSource;
                onInsertActionColumn.DataPropertyName = "OnInsertAction";
                onInsertActionColumn.DisplayMember = "Name";
                onInsertActionColumn.ValueMember = "ID";

                onUpdateActionColumn.DataSource = dbManager.userAccountActionsOnUpdateBindingSource;
                onUpdateActionColumn.DataPropertyName = "OnUpdateAction";
                onUpdateActionColumn.DisplayMember = "Name";
                onUpdateActionColumn.ValueMember = "ID";

                moveGroupUsersColumn.DataPropertyName = "MoveGroupUsers";

                authSystemNameColumn.DataPropertyName = "Name";

                _authSystemsContorlsCustomized = true;
            }
        }

        /// <summary>
        /// Auth systems save button click
        /// </summary>
        private void authSystemsBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.authSystemsBindingSource.EndEdit();
            dbManager.UpdateAuthSystems();
        }

        /// <summary>
        /// Auth systems refresh button click
        /// </summary>
        private void authSystemsBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            // Fill data adapter
            dbManager.authSystemsTableAdapter.Fill(dbManager.dataSet.AuthSystems);
            dbManager.authSystemTypesTableAdapter.Fill(dbManager.dataSet.AuthSystemTypes);
            dbManager.userAccountActionsOnDeleteTableAdapter.Fill(dbManager.dataSet.UserAccountActionsOnDelete);
            dbManager.userAccountActionsOnInsertTableAdapter.Fill(dbManager.dataSet.UserAccountActionsOnInsert);
            dbManager.userAccountActionsOnUpdateTableAdapter.Fill(dbManager.dataSet.UserAccountActionsOnUpdate);
        }

        /// <summary>
        /// Authentication settings strings button
        /// </summary>
        private void btnSettingsString_Click(object sender, EventArgs e)
        {
            if (dbManager.authSystemsBindingSource.Current != null)
            {
                int authSystemType = (int)(dbManager.authSystemsBindingSource.Current as DataRowView).Row["AuthSystemTypeID"];

                logWriter.WriteToLog("Authentication systems management --> Trying to change authentication system settings");

                switch (authSystemType)
                {
                    case UserAccountsSynchronizer.UAC_AD:
                        {
                            logWriter.WriteToLog("Authentication systems management --> Type of current authentication system is AD");

                            string setStr = "";

                            if (!((dbManager.authSystemsBindingSource.Current as DataRowView).Row["SettingsString"] is System.DBNull))
                            {
                                // Decrypt settings string
                                setStr = encryptor.DecryptString((byte[])(dbManager.authSystemsBindingSource.Current as DataRowView).Row["SettingsString"]);
                            }

                            // Create AD settings window
                            fmADSettings _fmADSettings = new fmADSettings(setStr, supervisor, logWriter);
                            _fmADSettings.ShowDialog();

                            setStr = _fmADSettings.settingsString;

                            if (setStr != "")
                            {
                                // Encrypt user name
                                (dbManager.authSystemsBindingSource.Current as DataRowView).Row["SettingsString"] = encryptor.EncryptString(setStr);
                            }
                            else
                                (dbManager.authSystemsBindingSource.Current as DataRowView).Row["SettingsString"] = System.DBNull.Value;

                            break;
                        }
                }
            }
        }

        #endregion

        #region Presets

        // Preset settings controls flag
        private bool _presetsContorlsCustomized;

        /// <summary>
        /// Customize presets controls
        /// </summary>
        private void CustomizePresetControls()
        {
            // Check preset settings controls flag
            if (!_presetsContorlsCustomized)
            {
                // Set preset binding source position changed handler
                dbManager.presetBindingSource.PositionChanged += new System.EventHandler(presetBindingSource_PositionChanged);

                // Set preset binding navigator
                presetBindingNavigator.BindingSource = dbManager.presetBindingSource;

                // Customize preset names data grid view
                presetNamesDataGridView.AutoGenerateColumns = false;
                presetNamesDataGridView.DataSource = dbManager.presetBindingSource;
                presetNameColumn.DataPropertyName = "Name";
                presetDateColumn.DataPropertyName = "Date";
                presetDescriptionColumn.DataPropertyName = "Description";

                // Set preset details screens position changed handler
                dbManager.fkScreensPresetDetailsPresetBindingSource.PositionChanged += new System.EventHandler(fkScreensPresetDetailsPresetBindingSource_PositionChanged);

                // Customize preset screens data grid view
                presetScreensDataGridView.AutoGenerateColumns = false;
                presetScreensDataGridView.DataSource = dbManager.fkScreensPresetDetailsPresetBindingSource;
                presetScreenNameColumn.DataSource = dbManager.presetScreensBindingSource;
                presetScreenNameColumn.DataPropertyName = "ScreenObjectID";
                presetScreenNameColumn.DisplayMember = "Name";
                presetScreenNameColumn.ValueMember = "ID";
                presetScreenScopeColumn.DataSource = dbManager.screenObjectScopesScreensBindingSource;
                presetScreenScopeColumn.DataPropertyName = "ScreenObjectScopeID";
                presetScreenScopeColumn.DisplayMember = "Name";
                presetScreenScopeColumn.ValueMember = "ID";


                // Set preset details position changed handler
                dbManager.fkPresetDetailsScreensPresetDetailsBindingSource.PositionChanged += new System.EventHandler(fkPresetDetailsScreensPresetDetailsBindingSource_PositionChanged);

                // Customize preset screen objects data grid view
                presetScreenObjectsDataGridView.AutoGenerateColumns = false;
                presetScreenObjectsDataGridView.DataSource = dbManager.fkPresetDetailsScreensPresetDetailsBindingSource;
                presetScreenObjectNameColumn.DataSource = dbManager.fkPresetDetailsScreensScreenObjectsBindingSource;
                presetScreenObjectNameColumn.DataPropertyName = "ScreenObjectID";
                presetScreenObjectNameColumn.DisplayMember = "Name";
                presetScreenObjectNameColumn.ValueMember = "ID";
                presetScreenObjectOrderColumn.DataPropertyName = "ScreenObjectOrder";
                presetScreenObjectScopeColumn.DataSource = dbManager.screenObjectScopesScreenObjectsBindingSource;
                presetScreenObjectScopeColumn.DataPropertyName = "ScreenObjectScopeID";
                presetScreenObjectScopeColumn.DisplayMember = "Name";
                presetScreenObjectScopeColumn.ValueMember = "ID";
                
                // Set screen objects binding navigator binding source
                screenObjectsBindingNavigator.BindingSource = dbManager.screensBindingSource;

                // Customize screens data grid view
                screensDataGridView.AutoGenerateColumns = false;
                screensDataGridView.DataSource = dbManager.screensBindingSource;
                screenNameColumn.DataPropertyName = "Name";
                screenCaptionColumn.DataPropertyName = "Caption";
                screenTypeIDColumn.DataPropertyName = "TypeID";
                screenTypeIDColumn.DataSource = dbManager.screenTypesBindingSource;
                screenTypeIDColumn.DisplayMember = "Name";
                screenTypeIDColumn.ValueMember = "ID";
                screenLocationXColumn.DataPropertyName = "LocationX";
                screenLocationYColumn.DataPropertyName = "LocationY";
                screenLocationXPersColumn.DataPropertyName = "LocationXPers";
                screenLocationYPersColumn.DataPropertyName = "LocationYPers";
                screenWidthColumn.DataPropertyName = "WidthPix";
                screenHeightColumn.DataPropertyName = "HeightPix";
                screenWidthPersColumn.DataPropertyName = "WidthPers";
                screenHeightPersColumn.DataPropertyName = "HeightPers";
                screenColorColumn.DataPropertyName = "BackGrColor";
                screenFontSizeColumn.DataPropertyName = "FontSize";
                screenTextColorColumn.DataPropertyName = "TextColor";

                // Customize screen objects data grid view
                screenObjectsDataGridView.AutoGenerateColumns = false;
                screenObjectsDataGridView.DataSource = dbManager.fkScreensScreenObjectsBindingSource;
                screenObjectNameColumn.DataPropertyName = "Name";
                screenObjectCaptionColumn.DataPropertyName = "Caption";
                screenObjectTypeIDColumn.DataPropertyName = "TypeID";
                screenObjectTypeIDColumn.DataSource = dbManager.screenObjectsTypesBindingSource;
                screenObjectTypeIDColumn.DisplayMember = "Name";
                screenObjectTypeIDColumn.ValueMember = "ID";
                screenObjectLocationXColumn.DataPropertyName = "LocationX";
                screenObjectLocationYColumn.DataPropertyName = "LocationY";
                screenObjectLocationXPersColumn.DataPropertyName = "LocationXPers";
                screenObjectLocationYPersColumn.DataPropertyName = "LocationYPers";
                screenObjectWidthColumn.DataPropertyName = "WidthPix";
                screenObjectHeightColumn.DataPropertyName = "HeightPix";
                screenObjectWidthPersColumn.DataPropertyName = "WidthPers";
                screenObjectHeightPersColumn.DataPropertyName = "HeightPers";
                screenObjectColorColumn.DataPropertyName = "BackGrColor";
                screenObjectFontSizeColumn.DataPropertyName = "FontSize";
                screenObjectTextColorColumn.DataPropertyName = "TextColor";
                screenObjectStrValueColumn.DataPropertyName = "StrValue";
                screenObjectPictureBox.DataBindings.Add(new System.Windows.Forms.Binding("Image", dbManager.fkScreensScreenObjectsBindingSource, "ImgValue", true));
                screenObjectRichTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.fkScreensScreenObjectsBindingSource, "TextValue", true));

                // Customize screen objects list data grid view
                screenObjectListValuesDataGridView.AutoGenerateColumns = false;
                screenObjectListValuesDataGridView.DataSource = dbManager.fkScreenObjectListValuesScreenObjectsBindingSource;
                screenObjectListValuesColumn.DataPropertyName = "Value";

                // Set flag value
                _presetsContorlsCustomized = true;
            }
        }

        /// <summary>
        /// Preset binding source position changed event handler
        /// </summary>
        private void presetBindingSource_PositionChanged(object sender, EventArgs e)
        {
            // Fill preset details
            if (dbManager.presetBindingSource.Current != null)
                dbManager.presetDetailsTableAdapter.Fill(dbManager.dataSet.PresetDetails, (int)(dbManager.presetBindingSource.Current as DataRowView).Row["ID"]);

            // Reload data
            fkScreensPresetDetailsPresetBindingSource_PositionChanged(null, null);
        }
        
        /// <summary>
        /// Screens preset details binding source position changed event handler
        /// </summary>
        private void fkScreensPresetDetailsPresetBindingSource_PositionChanged(object sender, EventArgs e)
        {
            // Fill preset details
            if (dbManager.presetBindingSource.Current != null)
                dbManager.presetDetailsTableAdapter.Fill(dbManager.dataSet.PresetDetails, (int)(dbManager.presetBindingSource.Current as DataRowView).Row["ID"]);

            // Check screen object ID
            if ((dbManager.fkScreensPresetDetailsPresetBindingSource.Current != null) &&
                (!((dbManager.fkScreensPresetDetailsPresetBindingSource.Current as DataRowView).Row["ScreenObjectID"] is System.DBNull)))
            {
                // Set position of screen
                int screenID = (int)(dbManager.fkScreensPresetDetailsPresetBindingSource.Current as DataRowView).Row["ScreenObjectID"];
                int position = dbManager.screensBindingSource.Find("ID", screenID);
                if (position >= 0)
                {
                    dbManager.screensBindingSource.Position = position;
                    dbManager.presetDetailsScreensBindingSource.Position = position;
                }
            }

            // Reload data
            fkPresetDetailsScreensPresetDetailsBindingSource_PositionChanged(null, null);
        }

        /// <summary>
        /// Preset details binding source position changed event handler
        /// </summary>
        private void fkPresetDetailsScreensPresetDetailsBindingSource_PositionChanged(object sender, EventArgs e)
        {
            // Check screen objects ID
            if ((dbManager.fkPresetDetailsScreensPresetDetailsBindingSource.Current != null) &&
                (!((dbManager.fkPresetDetailsScreensPresetDetailsBindingSource.Current as DataRowView).Row["ScreenObjectID"] is System.DBNull)))
            {
                // Set screen object position
                int screenID = (int)(dbManager.fkPresetDetailsScreensPresetDetailsBindingSource.Current as DataRowView).Row["ScreenObjectID"];
                int position = dbManager.fkScreensScreenObjectsBindingSource.Find("ID", screenID);
                if (position >= 0)
                {
                    dbManager.fkScreensScreenObjectsBindingSource.Position = position;
                }
            }
            else
            {
                // Set preset ID
                if ((dbManager.presetBindingSource.Current != null) &&
                    (dbManager.fkPresetDetailsScreensPresetDetailsBindingSource.Current != null) &&
                    (!((dbManager.presetBindingSource.Current as DataRowView).Row["ID"] is System.DBNull)))
                        (dbManager.fkPresetDetailsScreensPresetDetailsBindingSource.Current as DataRowView).Row["PresetID"] = (dbManager.presetBindingSource.Current as DataRowView).Row["ID"];
            }
        }

        /// <summary>
        /// Presets binding navigator save button click
        /// </summary>
        private void presetsBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.presetBindingSource.EndEdit();
            dbManager.fkScreensPresetDetailsPresetBindingSource.EndEdit();

            // Get deleted rows
            DataRow[] deletedRows = dbManager.dataSet.ScreensPresetDetails.Select(null, null, DataViewRowState.Deleted);

            if (deletedRows != null)
            {
                for (int i = 0; i < deletedRows.Length; i++)
                {
                    // Get child screen objects
                    string filterExpr = "ParentID = " + deletedRows[i]["ScreenObjectID", DataRowVersion.Original].ToString();
                    DataRow[] toDelRows = dbManager.dataSet.PresetDetails.Select(filterExpr);

                    if (toDelRows != null)
                    {
                        for (int j = 0; j < toDelRows.Length; j++)
                        {
                            // Delete all childs
                            dbManager.presetDetailsTableAdapter.Delete((int)toDelRows[j]["PresetID"],
                                (int)toDelRows[j]["ScreenObjectID"],
                                (toDelRows[j]["ScreenObjectOrder"] == System.DBNull.Value) ? null : (toDelRows[j]["ScreenObjectOrder"] as int?),
                                (toDelRows[j]["ScreenObjectScopeID"] == System.DBNull.Value) ? null : (toDelRows[j]["ScreenObjectScopeID"] as int?));
                        }
                    }
                }
            }

            dbManager.fkPresetDetailsScreensPresetDetailsBindingSource.EndEdit();

            dbManager.UpdatePreset();
            dbManager.UpdateScreensPresetDetails();
            dbManager.UpdatePresetDetails();
        }

        /// <summary>
        /// Preset hookup button click
        /// </summary>
        private void presetBindingNavigatorHookupIten_Click(object sender, EventArgs e)
        {
            fmPresetHookup _fmPresetHookup = new fmPresetHookup(dbManager, encryptor, supervisor);
            _fmPresetHookup.ShowDialog();
        }

        /// <summary>
        /// Presets binding navigator refresh button click
        /// </summary>
        private void presetBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            // Fill data adapters
            dbManager.presetTableAdapter.Fill(dbManager.dataSet.Preset);
            if (dbManager.presetBindingSource.Current != null)
                dbManager.presetDetailsTableAdapter.Fill(dbManager.dataSet.PresetDetails, (int)(dbManager.presetBindingSource.Current as DataRowView).Row["ID"]);
        }

        /// <summary>
        /// Screen objects binding navigator save button click
        /// </summary>
        private void screenObjectsBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.screensBindingSource.EndEdit();

            // Get deleted rows
            DataRow [] deletedRows = dbManager.dataSet.Screens.Select(null, null, DataViewRowState.Deleted);

            if (deletedRows != null)
            {
                for (int i = 0; i < deletedRows.Length; i++)
                {
                    // Get child screen objects
                    string filterExpr = "ParentID = " + deletedRows[i]["ID", DataRowVersion.Original].ToString();
                    DataRow[] toDelRows = dbManager.dataSet.ScreenObjects.Select(filterExpr);

                    if (toDelRows != null)
                    {
                        for (int j = 0; j < toDelRows.Length; j++)
                        {
                            // Delete all childs
                            dbManager.screenObjectsTableAdapter.Delete((int)toDelRows[j]["ID"],
                                (toDelRows[j]["Name"] == System.DBNull.Value) ? null : (string)toDelRows[j]["Name"],
                                (toDelRows[j]["Caption"] == System.DBNull.Value) ? null : (string)toDelRows[j]["Caption"],
                                (toDelRows[j]["TypeID"] == System.DBNull.Value) ? 0 : (int)toDelRows[j]["TypeID"],
                                (toDelRows[j]["ParentID"] == System.DBNull.Value) ? null : (toDelRows[j]["ParentID"] as int?),
                                (toDelRows[j]["LocationX"] == System.DBNull.Value) ? null : (toDelRows[j]["LocationX"] as int?),
                                (toDelRows[j]["LocationY"] == System.DBNull.Value) ? null : (toDelRows[j]["LocationY"] as int?),
                                (toDelRows[j]["LocationXPers"] == System.DBNull.Value) ? null : (toDelRows[j]["LocationXPers"] as int?),
                                (toDelRows[j]["LocationYPers"] == System.DBNull.Value) ? null : (toDelRows[j]["LocationYPers"] as int?),
                                (toDelRows[j]["WidthPix"] == System.DBNull.Value) ? null : (toDelRows[j]["WidthPix"] as int?),
                                (toDelRows[j]["HeightPix"] == System.DBNull.Value) ? null : (toDelRows[j]["HeightPix"] as int?),
                                (toDelRows[j]["WidthPers"] == System.DBNull.Value) ? null : (toDelRows[j]["WidthPers"] as int?),
                                (toDelRows[j]["HeightPers"] == System.DBNull.Value) ? null : (toDelRows[j]["HeightPers"] as int?),
                                (toDelRows[j]["FontSize"] == System.DBNull.Value) ? null : (toDelRows[j]["FontSize"] as int?),
                                (toDelRows[j]["TextColor"] == System.DBNull.Value) ? null : (toDelRows[j]["TextColor"] as int?),
                                (toDelRows[j]["BackGrColor"] == System.DBNull.Value) ? null : (toDelRows[j]["BackGrColor"] as int?),
                                (toDelRows[j]["StrValue"] == System.DBNull.Value) ? null : (string)toDelRows[j]["StrValue"]);
                        }
                    }
                }
            }

            dbManager.fkScreensScreenObjectsBindingSource.EndEdit();
            dbManager.fkScreenObjectListValuesScreenObjectsBindingSource.EndEdit();

            dbManager.UpdateScreens();
            dbManager.UpdateScreenObjects();
            dbManager.UpdateScreenObjectsListValues();
        }

        /// <summary>
        /// Screen objects binding navigator refresh button click
        /// </summary>
        private void screenObjectsBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.screenTypesTableAdapter.Fill(dbManager.dataSet.ScreenTypes);
            dbManager.screensTableAdapter.Fill(dbManager.dataSet.Screens);
            dbManager.screenObjectsTypesTableAdapter.Fill(dbManager.dataSet.ScreenObjectTypes);
            dbManager.screenObjectsTableAdapter.Fill(dbManager.dataSet.ScreenObjects);
            dbManager.screenObjectListValuesTableAdapter.Fill(dbManager.dataSet.ScreenObjectListValues);
        }

        /// <summary>
        /// Preset names data grid view enter event handler
        /// </summary>
        private void presetNamesDataGridView_Enter(object sender, EventArgs e)
        {
            DataGridView dataGridView = (DataGridView)sender;
            presetBindingNavigator.BindingSource = (BindingSource)dataGridView.DataSource;
        }

        /// <summary>
        /// Preset names data grid view leave event handler
        /// </summary>
        private void presetNamesDataGridView_Leave(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.presetBindingSource.EndEdit();
            if (dbManager.dataSet.Preset.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdatePreset();
        }

        /// <summary>
        /// Preset screens data grid view leave event handler
        /// </summary>
        private void presetScreensDataGridView_Leave(object sender, EventArgs e)
        {
            try
            {
                if (!this.Validate()) return;
                dbManager.fkScreensPresetDetailsPresetBindingSource.EndEdit();
                if (dbManager.dataSet.ScreensPresetDetails.Select(null, null, DataViewRowState.Added).Length > 0)
                    dbManager.UpdateScreensPresetDetails();
            }
            catch (System.Data.NoNullAllowedException)
            {
                dbManager.fkScreensPresetDetailsPresetBindingSource.CancelEdit();
                MessageBox.Show("You have to select screen in drop down list!", "Error",  MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        /// <summary>
        /// Preset screen objects data grid view enter event handler
        /// </summary>
        private void presetScreenObjectsDataGridView_Enter(object sender, EventArgs e)
        {
            DataGridView dataGridView = (DataGridView)sender;
            presetBindingNavigator.BindingSource = (BindingSource)dataGridView.DataSource;

            fkScreensPresetDetailsPresetBindingSource_PositionChanged(null, null);
        }

        /// <summary>
        /// Preset screen objects data grid view leave event handler
        /// </summary>
        private void presetScreenObjectsDataGridView_Leave(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkPresetDetailsScreensPresetDetailsBindingSource.EndEdit();
            if (dbManager.dataSet.PresetDetails.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdatePresetDetails();
        }

        /// <summary>
        /// Preset screens data grid view rows removed event handler
        /// </summary>
        private void presetScreensDataGridView_RowsRemoved(object sender, DataGridViewRowsRemovedEventArgs e)
        {
            fkScreensPresetDetailsPresetBindingSource_PositionChanged(null, null);
        }

        /// <summary>
        /// Screens data grid view enter event handler
        /// </summary>
        private void screensDataGridView_Enter(object sender, EventArgs e)
        {
            DataGridView dataGridView = (DataGridView)sender;
            screenObjectsBindingNavigator.BindingSource = (BindingSource)dataGridView.DataSource;
        }

        /// <summary>
        /// Screens data grid view leave event handler
        /// </summary>
        private void screensDataGridView_Leave(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.screensBindingSource.EndEdit();
            if (dbManager.dataSet.Screens.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateScreens();
        }

        /// <summary>
        /// Screen objects list values data grid view enter event handler
        /// </summary>
        private void screenObjectListValuesDataGridView_Enter(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkScreensScreenObjectsBindingSource.EndEdit();
            if (dbManager.dataSet.ScreenObjects.Select(null, null, DataViewRowState.Added).Length > 0)
                dbManager.UpdateScreenObjects();
                        
            screenObjectsBindingNavigator.BindingSource = dbManager.fkScreenObjectListValuesScreenObjectsBindingSource;
        }

        /// <summary>
        /// Screen object rich text box enter event handler
        /// </summary>
        private void screenObjectRichTextBox_Enter(object sender, EventArgs e)
        {
            screenObjectsBindingNavigator.BindingSource = (BindingSource)screenObjectRichTextBox.DataBindings[0].DataSource;
        }

        /// <summary>
        /// Screen object picture box click event handler
        /// </summary>
        private void screenObjectPictureBox_Click(object sender, EventArgs e)
        {
            screenObjectsBindingNavigator.BindingSource = (BindingSource)screenObjectPictureBox.DataBindings[0].DataSource;
        }

        /// <summary>
        /// Load screen object image button click event handler
        /// </summary>
        private void loadscreenObjectImageButton_Click(object sender, EventArgs e)
        {
            if (openImageDialog.ShowDialog() == DialogResult.OK)
            {
                screenObjectPictureBox.Image = new Bitmap(openImageDialog.FileName);
            }
        }

        /// <summary>
        /// Load screen object text button click event handler
        /// </summary>
        private void loadscreenObjecTextButton_Click(object sender, EventArgs e)
        {
            if (openTextFileDialog.ShowDialog() == DialogResult.OK)
            {
                screenObjectRichTextBox.LoadFile(openTextFileDialog.FileName, RichTextBoxStreamType.PlainText);
            }
        }

        /// <summary>
        /// Clear screen object image button click event handler
        /// </summary>
        private void scrennObjectImageClearButton_Click(object sender, EventArgs e)
        {
            screenObjectPictureBox.Image = null;
        }

        /// <summary>
        /// Clear screen object text button click event handler
        /// </summary>
        private void scrennObjectTextClearButton_Click(object sender, EventArgs e)
        {
            screenObjectRichTextBox.Clear();
        }

        #endregion

        #region Education

        // Education settings controls flag
        private bool _educationContorlsCustomized;


        /// <summary>
        /// Education controls customizing
        /// </summary>
        private void CustomizeEducationControls()
        {
            // Check supervisor flag
            if (supervisor)
            {
                dbManager.userEducationUsersBindingSource.Filter = "";
            }
            else
            {
                dbManager.userEducationUsersBindingSource.Filter = CreateSupevisorsFilterString();
            }

            // Check education settings controls flag
            if (!_educationContorlsCustomized)
            {
                // Set education categories binding navigator binding source
                eduCategoriesBindingNavigator.BindingSource = dbManager.educationCategoriesBindingSource;

                // Customize education categories data grid view
                eduCategoriesDataGridView.AutoGenerateColumns = false;
                eduCategoriesDataGridView.DataSource = dbManager.educationCategoriesBindingSource;
                eduCategoriesNameColumn.DataPropertyName = "Name";

                // Set education lessons binding navigator binding source
                eduLessonsBindingNavigator.BindingSource = dbManager.fkEducationLessonsEducationCategoriesBindingSource;

                // Set pictures and rich text box binding sources
                eduLessonOrderTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.fkEducationLessonsEducationCategoriesBindingSource, "LessonOrder", true));
                eduLessonPictureBox.DataBindings.Add(new System.Windows.Forms.Binding("Image", dbManager.fkEducationLessonsEducationCategoriesBindingSource, "LessonImage", true));
                eduLessonRichTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.fkEducationLessonsEducationCategoriesBindingSource, "LessonText", true));

                // Education questions binding navigator binding source
                eduQuestionsBindingNavigator.BindingSource = dbManager.fkEducationQuestionsEducationLessonsBindingSource;

                // Set rich text box binding sources
                eduQuestionOrderTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.fkEducationQuestionsEducationLessonsBindingSource, "QuestionOrder", true));
                eduQuestionRichTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.fkEducationQuestionsEducationLessonsBindingSource, "QuestionText", true));

                // Bind right answer combo box
                rightAnswerComboBox.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", dbManager.fkEducationQuestionsEducationLessonsBindingSource, "RightAnswerID", true));
                rightAnswerComboBox.DataSource = dbManager.rightQuestionAnswerBindingSource;
                rightAnswerComboBox.DisplayMember = "AnswerText";
                rightAnswerComboBox.FormattingEnabled = true;
                rightAnswerComboBox.ValueMember = "ID";

                dbManager.educationQuestionsTableAdapter.Fill(dbManager.dataSet.EducationQuestions);

                // Education questions binding navigator binding source
                eduAnswersBindingNavigator.BindingSource = dbManager.fkEducationQuestionAnswersEducationQuestionsBindingSource;
                
                // Customize education answers data grid view
                eduAnswersDataGridView.AutoGenerateColumns = false;
                eduAnswersDataGridView.DataSource = dbManager.fkEducationQuestionAnswersEducationQuestionsBindingSource;
                eduQuestionAnswerOrderColumn.DataPropertyName = "AnswerOrder";
                eduQuestionAnswerTextColumn.DataSource = dbManager.questionAnswerBindingSource;
                eduQuestionAnswerTextColumn.DataPropertyName = "AnswerID";
                eduQuestionAnswerTextColumn.DisplayMember = "AnswerText";
                eduQuestionAnswerTextColumn.ValueMember = "ID";

                // Education general list of questions binding navigator binding source
                eduAllAnswersBindingNavigator.BindingSource = dbManager.educationAnswersBindingSource;

                // Customize general education answers data grid view
                generalAnswersListDataGridView.AutoGenerateColumns = false;
                generalAnswersListDataGridView.DataSource = dbManager.educationAnswersBindingSource;
                eduGeneralAnswerTextColumn.DataPropertyName = "AnswerText";
                               
                // Set education users binding navigator binding source
                eduUsersBindingNavigator.BindingSource = dbManager.userEducationUsersBindingSource;

                // Customize education users data grid view
                eduUsersDataGridView.AutoGenerateColumns = false;
                eduUsersDataGridView.DataSource = dbManager.userEducationUsersBindingSource;
                eduUserNameColumn.DataPropertyName = "Name";

                // Set education users categories binding navigator binding source
                eduUserCategoriesBindingNavigator.BindingSource = dbManager.fkUserEducationUsersBindingSource;

                // Customize education users categories data grid view
                eduUserCategoriesDataGridView.AutoGenerateColumns = false;
                eduUserCategoriesDataGridView.DataSource = dbManager.fkUserEducationUsersBindingSource;
                eduUserCategOrderColumn.DataPropertyName = "EduCategOrder";
                eduRandomCategoryQuestionsColumn.DataPropertyName = "RandomQuestion";
                eduUserCategoryNameColumn.DataSource = dbManager.userEducationCategoriesBindingSource;
                eduUserCategoryNameColumn.DataPropertyName = "EduCategID";
                eduUserCategoryNameColumn.DisplayMember = "Name";
                eduUserCategoryNameColumn.ValueMember = "ID";

                // Set education users history binding navigator binding source
                eduUserHistoryBindingNavigator.BindingSource = dbManager.fkUserEducationAnswersUsersBindingSource;

                // Customize education users history data grid view
                eduUserHistoryDataGridView.AutoGenerateColumns = false;
                eduUserHistoryDataGridView.DataSource = dbManager.fkUserEducationAnswersUsersBindingSource;
                eduUserAnswerTextColumn.DataSource = dbManager.userEducationAnswersAnswersBindingSource;
                eduUserAnswerTextColumn.DataPropertyName = "AnswerID";
                eduUserAnswerTextColumn.DisplayMember = "AnswerText";
                eduUserAnswerTextColumn.ValueMember = "ID";
                eduUserQuestionTextColumn.DataSource = dbManager.userEducationAnswersQuestionsBindingSource;
                eduUserQuestionTextColumn.DataPropertyName = "QuestionID";
                eduUserQuestionTextColumn.DisplayMember = "QuestionText";
                eduUserQuestionTextColumn.ValueMember = "ID";
                eduUserCorrectAnswerColumn.DataPropertyName = "CorrectAnswerSign";
                eduUserAnswerDateColumn.DataPropertyName = "Date";

                // Set education user groups binding navigator binding source
                eduUserGroupsBindingNavigator.BindingSource = dbManager.userEducationUserGroupsBindingSource;

                // Customize education user groups data grid view
                eduUserGroupsDataGridView.AutoGenerateColumns = false;
                eduUserGroupsDataGridView.DataSource = dbManager.userEducationUserGroupsBindingSource;
                eduGroupNameColumn.DataPropertyName = "Name";
                eduGroupDescriptionColumn.DataPropertyName = "Description";

                // Set education user groups categories binding navigator binding source
                eduUserGroupCategoriesBindingNavigator.BindingSource = dbManager.fkUserGroupsUsersGroupEducationBindingSource;

                // Customize education users categories data grid view
                eduUserGroupCategoriesDataGridView.AutoGenerateColumns = false;
                eduUserGroupCategoriesDataGridView.DataSource = dbManager.fkUserGroupsUsersGroupEducationBindingSource;
                eduUserGroupCategOrderColumn.DataPropertyName = "EduCategOrder";
                eduUserGroupRandomCategoryQuestionsColumn.DataPropertyName = "RandomQuestion";
                eduUserGroupCategoryNameColumn.DataSource = dbManager.userGroupEducationCategoriesBindingSource;
                eduUserGroupCategoryNameColumn.DataPropertyName = "EduCategID";
                eduUserGroupCategoryNameColumn.DisplayMember = "Name";
                eduUserGroupCategoryNameColumn.ValueMember = "ID";

                // Set flag value
                _educationContorlsCustomized = true;
            }
        }

        /// <summary>
        /// User names grid view cell formating event handler
        /// </summary>
        private void eduUsersDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "eduUserNameColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["eduUserNameColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["eduUserNameColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["eduUserNameColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Education user group data grid view cell formatting event handler
        /// </summary>
        private void eduUserGroupsDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "eduGroupNameColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["eduGroupNameColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["eduGroupNameColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["eduGroupNameColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }

            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "eduGroupDescriptionColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["eduGroupDescriptionColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["eduGroupDescriptionColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["eduGroupDescriptionColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Education categories binding navigator save button click
        /// </summary>
        private void eduCategoriesBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.educationCategoriesBindingSource.EndEdit();
            dbManager.UpdateEducationCategories();
        }

        /// <summary>
        /// Education categories binding navigator refresh button click
        /// </summary>
        private void eduCategoriesBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.educationCategoriesTableAdapter.Fill(dbManager.dataSet.EducationCategories);
        }

        /// <summary>
        /// Education lessons binding navigator save button click
        /// </summary>
        private void eduLessonsBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkEducationLessonsEducationCategoriesBindingSource.EndEdit();
            dbManager.UpdateEducationLessons();
        }

        /// <summary>
        /// Education lessons binding navigator refresh button click
        /// </summary>
        private void eduLessonsBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.educationLessonsTableAdapter.Fill(dbManager.dataSet.EducationLessons);
        }

        /// <summary>
        /// Education questions binding navigator save button click
        /// </summary>
        private void eduQuestionsBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkEducationQuestionsEducationLessonsBindingSource.EndEdit();
            dbManager.UpdateEducationQuestions();
        }

        /// <summary>
        /// Education questions binding navigator refresh button click
        /// </summary>
        private void eduQuestionsBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.educationQuestionsTableAdapter.Fill(dbManager.dataSet.EducationQuestions);
        }

        /// <summary>
        /// Education answers binding navigator save button click
        /// </summary>
        private void eduAnswersBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkEducationQuestionAnswersEducationQuestionsBindingSource.EndEdit();
            dbManager.UpdateEducationQuestionAnswers();
        }

        /// <summary>
        /// Education answers binding navigator refresh button click
        /// </summary>
        private void eduAnswersBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.educationQuestionAnswersTableAdapter.Fill(dbManager.dataSet.EducationQuestionAnswers);
        }

        /// <summary>
        /// Education all answers binding navigator save button click
        /// </summary>
        private void eduAllAnswersBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.educationAnswersBindingSource.EndEdit();
            dbManager.UpdateEducationAnswers();
        }

        /// <summary>
        /// Education all answers binding navigator refresh button click
        /// </summary>
        private void eduAllAnswersBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.educationAnswersTableAdapter.Fill(dbManager.dataSet.EducationAnswers);
        }

        /// <summary>
        /// Education users refresh button click
        /// </summary>
        private void eduUsersBindingNavigatorRefreshIntem_Click(object sender, EventArgs e)
        {
            dbManager.usersTableAdapter.Fill(dbManager.dataSet.Users);
        }

        /// <summary>
        /// Education user groups refresh
        /// </summary>
        private void eduUserGroupsBindingNavigatorRefreshIntem_Click(object sender, EventArgs e)
        {
            dbManager.userGroupsTableAdapter.Fill(dbManager.dataSet.UserGroups);
        }

        /// <summary>
        /// User group education refresh
        /// </summary>
        private void eduUserGroupCategoriesBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userGroupEducationTableAdapter.Fill(dbManager.dataSet.UserGroupEducation);
        }

        /// <summary>
        /// Education users categories binding navigator save button click
        /// </summary>
        private void eduUserCategoriesBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkUserEducationUsersBindingSource.EndEdit();
            dbManager.UpdateUserEducation();
        }

        /// <summary>
        /// User groups education save button click
        /// </summary>
        private void eduUserGroupCategoriesBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkUserGroupsUsersGroupEducationBindingSource.EndEdit();
            dbManager.UpdateUserGroupEducation();
        }

        /// <summary>
        /// Education users categories binding navigator save button click
        /// </summary>
        private void eduUserCategoriesBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userEducationTableAdapter.Fill(dbManager.dataSet.UserEducation);
       
        }

        /// <summary>
        /// Education users history binding navigator save button click
        /// </summary>
        private void eduUserHistoryBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkUserEducationAnswersUsersBindingSource.EndEdit();
            dbManager.UpdateUserEducationAnswers();
        }

        /// <summary>
        /// Education users history binding navigator refresh button click
        /// </summary>
        private void eduUserHistoryBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userEducationAnswersTableAdapter.Fill(dbManager.dataSet.UserEducationAnswers);
        }
        
        /// <summary>
        /// Education lesson image button clear click
        /// </summary>
        private void eduLessonImageClearButton_Click(object sender, EventArgs e)
        {
            eduLessonPictureBox.Image = null;
        }

        /// <summary>
        /// Education lesson image button open click
        /// </summary>
        private void eduLessonImageOpenButton_Click(object sender, EventArgs e)
        {
            if (openImageDialog.ShowDialog() == DialogResult.OK)
            {
                eduLessonPictureBox.Image = new Bitmap(openImageDialog.FileName);
            }
        }

        /// <summary>
        /// Education lesson text button clear click
        /// </summary>
        private void eduLessonTextClearButton_Click(object sender, EventArgs e)
        {
            eduLessonRichTextBox.Clear();
        }

        /// <summary>
        /// Education lesson text button open click
        /// </summary>
        private void eduLessonTextOpenButton_Click(object sender, EventArgs e)
        {
            if (openTextFileDialog.ShowDialog() == DialogResult.OK)
            {
                eduLessonRichTextBox.LoadFile(openTextFileDialog.FileName, RichTextBoxStreamType.PlainText);
            }
        }

        /// <summary>
        /// Education question text button clear click
        /// </summary>
        private void eduQuestionTextClearButton_Click(object sender, EventArgs e)
        {
            eduQuestionRichTextBox.Clear();
        }

        /// <summary>
        /// Education question text button open click
        /// </summary>
        private void eduQuestionTextOpenButton_Click(object sender, EventArgs e)
        {
            if (openTextFileDialog.ShowDialog() == DialogResult.OK)
            {
                eduQuestionRichTextBox.LoadFile(openTextFileDialog.FileName, RichTextBoxStreamType.PlainText);
            }
        }

        /// <summary>
        /// Import button click
        /// </summary>
        private void eduImportFromDBButton_Click(object sender, EventArgs e)
        {
            fmEduDBImport _fmEduDBImport = new fmEduDBImport(dbManager);
            _fmEduDBImport.ShowDialog();
        }

        /// <summary>
        /// Lessons tab control selected item changed 
        /// </summary>
        private void eduLessonsTabControl_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (eduLessonsTabControl.SelectedTab != null)
                switch (eduLessonsTabControl.SelectedTab.Name)
                {
                    case "tabLessons":
                        {
                            eduCategoriesBindingNavigatorSaveItem_Click(null, null);
                            break;
                        }

                    case "tabQuestions":
                        {
                            eduLessonsBindingNavigatorSaveItem_Click(null, null);
                            eduAllAnswersBindingNavigatorSaveItem_Click(null, null);
                            break;
                        }
                }
        }

        #endregion

        #region Notification

        // Notification settings controls flag
        private bool _notificationContorlsCustomized;

        /// <summary>
        /// Notification controls customizing
        /// </summary>
        private void CustomizeNotificationControls()
        {
            // Check supervisor flag
            if (supervisor)
            {
                dbManager.notificationsUsersBindingSource.Filter = "";
            }
            else
            {
                dbManager.notificationsUsersBindingSource.Filter = CreateSupevisorsFilterString();
            }

            // Check notification settings controls flag
            if (!_notificationContorlsCustomized)
            {
                // Set notification binding navigator binding source
                notificationBindingNavigator.BindingSource = dbManager.notificationsBindingSource;

                // Bind notice type combo box
                noticeTypeComboBox.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", dbManager.notificationsBindingSource, "NoticeTypeID", true));
                noticeTypeComboBox.DataSource = dbManager.notificationTypesBindingSource;
                noticeTypeComboBox.DisplayMember = "Name";
                noticeTypeComboBox.FormattingEnabled = true;
                noticeTypeComboBox.ValueMember = "ID";

                // Bind display type combo box
                noticeDisplayTypeComboBox.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", dbManager.notificationsBindingSource, "DispTypeID", true));
                noticeDisplayTypeComboBox.DataSource = dbManager.notificationDisplayTypesBindingSource;
                noticeDisplayTypeComboBox.DisplayMember = "Name";
                noticeDisplayTypeComboBox.FormattingEnabled = true;
                noticeDisplayTypeComboBox.ValueMember = "ID";

                // Bind notice scopes combo box
                noticeScopesComboBox.DataBindings.Add(new System.Windows.Forms.Binding("SelectedValue", dbManager.notificationsBindingSource, "ScopeID", true));
                noticeScopesComboBox.DataSource = dbManager.notificationScopesBindingSource;
                noticeScopesComboBox.DisplayMember = "Name";
                noticeScopesComboBox.FormattingEnabled = true;
                noticeScopesComboBox.ValueMember = "ID";

                // Bind notice picture box
                notificationPictureBox.DataBindings.Add(new System.Windows.Forms.Binding("Image", dbManager.notificationsBindingSource, "NoticeImage", true));

                // Bind notice rich text box
                notificationRichTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.notificationsBindingSource, "NoticeText", true));

                dbManager.notificationsTableAdapter.Fill(dbManager.dataSet.Notifications);

                // Set notification users binding navigator binding source
                notificationUsersBindingNavigator.BindingSource = dbManager.notificationsUsersBindingSource;

                // Customize notification users data grid view
                notificationUsersDataGridView.AutoGenerateColumns = false;
                notificationUsersDataGridView.DataSource = dbManager.notificationsUsersBindingSource;
                notificationUsersUserNameTextBoxColumn.DataPropertyName = "Name";

                // Set user notification binding navigator binding source
                userNotificationBindingNavigator.BindingSource = dbManager.fkUserNotificationsUsersBindingSource;

                // Customize user notification data grid view
                userNotificationDataGridView.AutoGenerateColumns = false;
                userNotificationDataGridView.DataSource = dbManager.fkUserNotificationsUsersBindingSource;
                userNotificationNoticeTextColumn.DataSource = dbManager.userNotificationNoticesBindingSource;
                userNotificationNoticeTextColumn.DataPropertyName = "NoticeID";
                userNotificationNoticeTextColumn.DisplayMember = "NoticeText";
                userNotificationNoticeTextColumn.ValueMember = "ID";
                userNotificationDisplayTypeColumn.DataSource = dbManager.userNotificationDisplayTypesBindingSource;
                userNotificationDisplayTypeColumn.DataPropertyName = "DispTypeID";
                userNotificationDisplayTypeColumn.DisplayMember = "Name";
                userNotificationDisplayTypeColumn.ValueMember = "ID";

                // User notification history binding navigator binding source
                userNotificationHistoryBindingNavigator.BindingSource = dbManager.fkUserNotificationsHistoryUsersBindingSource;

                // Customize user notification history data grid view
                userNotificationHistoryDataGridView.AutoGenerateColumns = false;
                userNotificationHistoryDataGridView.DataSource = dbManager.fkUserNotificationsHistoryUsersBindingSource;
                userNotificationHistoryNoticeTextColumn.DataSource = dbManager.userNotificationHistoryNoticesBindingSource;
                userNotificationHistoryNoticeTextColumn.DataPropertyName = "NoticeID";
                userNotificationHistoryNoticeTextColumn.DisplayMember = "NoticeText";
                userNotificationHistoryNoticeTextColumn.ValueMember = "ID";
                userNotificationHistoryDateColumn.DataPropertyName = "NoticeDate";

                // Set notification user groups binding navigator binding source
                notificationUserGroupsBindingNavigator.BindingSource = dbManager.notificationsUserGroupsBindingSource;

                // Customize notification user groups data grid view
                notificationUserGroupsDataGridView.AutoGenerateColumns = false;
                notificationUserGroupsDataGridView.DataSource = dbManager.notificationsUserGroupsBindingSource;
                notificationGroupNameColumn.DataPropertyName = "Name";
                notificationGroupDescriptionColumn.DataPropertyName = "Description";

                // Set user group notification binding navigator binding source
                userGroupsNotificationBindingNavigator.BindingSource = dbManager.fkUserGroupsUsersGroupNotificationsBindingSource;

                // Customize user group notification data grid view
                userGroupNotificationDataGridView.AutoGenerateColumns = false;
                userGroupNotificationDataGridView.DataSource = dbManager.fkUserGroupsUsersGroupNotificationsBindingSource;
                userGroupNotificationNoticeTextColumn.DataSource = dbManager.userGroupNotificationNoticesBindingSource;
                userGroupNotificationNoticeTextColumn.DataPropertyName = "NoticeID";
                userGroupNotificationNoticeTextColumn.DisplayMember = "NoticeText";
                userGroupNotificationNoticeTextColumn.ValueMember = "ID";
                userGroupNotificationDisplayTypeColumn.DataSource = dbManager.userGroupNotificationDisplayTypesBindingSource;
                userGroupNotificationDisplayTypeColumn.DataPropertyName = "DispTypeID";
                userGroupNotificationDisplayTypeColumn.DisplayMember = "Name";
                userGroupNotificationDisplayTypeColumn.ValueMember = "ID";

                // Set flag value
                _notificationContorlsCustomized = true;
            }
        }

        /// <summary>
        /// User names grid view cell formating event handler
        /// </summary>
        private void notificationUsersDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "notificationUsersUserNameTextBoxColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["notificationUsersUserNameTextBoxColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["notificationUsersUserNameTextBoxColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["notificationUsersUserNameTextBoxColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Notification users cell formatting event data handler
        /// </summary>
        private void notificationUserGroupsDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "notificationGroupNameColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["notificationGroupNameColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["notificationGroupNameColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["notificationGroupNameColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }

            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "notificationGroupDescriptionColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["notificationGroupDescriptionColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["notificationGroupDescriptionColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                e.Value = encryptor.DecryptString((byte[])dataGridView["notificationGroupDescriptionColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Notice image clear button click
        /// </summary>
        private void noticesImageClearBtn_Click(object sender, EventArgs e)
        {
            notificationPictureBox.Image = null;
        }

        /// <summary>
        /// Notice text clear button click
        /// </summary>
        private void noticesTextClearBtn_Click(object sender, EventArgs e)
        {
            notificationRichTextBox.Clear();
        }

        /// <summary>
        /// Notice image open button click
        /// </summary>
        private void noticesImageOpenBtn_Click(object sender, EventArgs e)
        {
            if (openImageDialog.ShowDialog() == DialogResult.OK)
            {
                notificationPictureBox.Image = new Bitmap(openImageDialog.FileName);
            }
        }

        /// <summary>
        /// Notice text open button click
        /// </summary>
        private void noticesTextOpenBtn_Click(object sender, EventArgs e)
        {
            if (openTextFileDialog.ShowDialog() == DialogResult.OK)
            {
                notificationRichTextBox.LoadFile(openTextFileDialog.FileName, RichTextBoxStreamType.PlainText);
            }
        }

        /// <summary>
        /// Notification binding navigator save button click
        /// </summary>
        private void notificationBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.notificationsBindingSource.EndEdit();
            dbManager.UpdateNotifications();
        }

        /// <summary>
        /// Notification binding navigator save button click
        /// </summary>
        private void notificationBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.notificationDisplayTypesTableAdapter.Fill(dbManager.dataSet.NotificationDisplayTypes);
            dbManager.notificationScopesTableAdapter.Fill(dbManager.dataSet.NotificationScopes);
            dbManager.notificationTypesTableAdapter.Fill(dbManager.dataSet.NotificationTypes);
            dbManager.notificationsTableAdapter.Fill(dbManager.dataSet.Notifications);
        }

        /// <summary>
        /// User notification binding navigator save button click
        /// </summary>
        private void userNotificationBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkUserNotificationsUsersBindingSource.EndEdit();
            dbManager.UpdateUserNotifications();
        }

        /// <summary>
        /// User notification binding navigator refresh button click
        /// </summary>
        private void userNotificationBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userNotificationsTableAdapter.Fill(dbManager.dataSet.UserNotifications);
        }

        /// <summary>
        /// User notification history binding navigator save button click
        /// </summary>
        private void userNotificationHistoryBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkUserNotificationsHistoryUsersBindingSource.EndEdit();
            dbManager.UpdateUserNotificationsHistory();
        }

        /// <summary>
        /// User notification history binding navigator refresh button click
        /// </summary>
        private void userNotificationHistoryBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userNotificationsHistoryTableAdapter.Fill(dbManager.dataSet.UserNotificationsHistory);
        }

        /// <summary>
        /// Notifications user group refresh item click
        /// </summary>
        private void notificationUserGroupsBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userGroupsTableAdapter.Fill(dbManager.dataSet.UserGroups);
        }

        /// <summary>
        /// User groups notifications refresh item click
        /// </summary>
        private void userGroupNotificationBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userNotificationsTableAdapter.Fill(dbManager.dataSet.UserNotifications);
        }

        /// <summary>
        /// User groups save item click
        /// </summary>
        private void userGroupNotificationBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkUserGroupsUsersGroupNotificationsBindingSource.EndEdit();
            dbManager.UpdateUserGroupNotifications();
        }
        #endregion
      
        #region License management
        
        // License settings controls flag
        private bool _licenseContorlsCustomized;

        // License manager instance
        private License.LicenseManager _licenseManager;

        // License manager property
        public License.LicenseManager licenseManager
        {
            get
            {
                if (_licenseManager == null)
                {
                    _licenseManager = new License.LicenseManager();
                }

                return _licenseManager;
            }

            set
            {
                _licenseManager = value;
            }
        }

        /// <summary>
        /// License controls customizing
        /// </summary>
        private void CustomizeLicenseControls()
        {
            // Check license settings controls flag
            if (!_licenseContorlsCustomized)
            {
                // Get encrypted license string
                string licStr = "";

                if ((dbManager.licenseBindingSource.Current != null) &&
                    (!((dbManager.licenseBindingSource.Current as DataRowView).Row["LicenseString"] is System.DBNull)))
                {
                    // Decrypt license string
                    licStr = encryptor.DecryptString((byte[])(dbManager.licenseBindingSource.Current as DataRowView).Row["LicenseString"]);
                }

                // Read license
                licenseManager.ParseLicenseString(licStr);

                licensePointsPanel.Controls.Clear();

                foreach (LicensePoint licensePoint in licenseManager.licensePoints)
                    AddLicensePointCard(new LicensePointCard(licensePoint));
                
                licensePointsPanel.VerticalScroll.Value = 0;
                
                // Set flag values
                _licenseContorlsCustomized = true;
            }
        }

        /// <summary>
        /// Save license information button click
        /// </summary>
        private void btnSaveLicenseInfo_Click(object sender, EventArgs e)
        {
            // Get license point list
            List<LicensePoint> licensePointList = new List<LicensePoint>();

            foreach (Control ctrl in licensePointsPanel.Controls)
                if (ctrl is LicensePointCard)
                    licensePointList.Add((ctrl as LicensePointCard).licensePoint);

            // Create license information string
            licenseManager.licensePoints = licensePointList;
            
            // Save license information string
            if (dbManager.licenseBindingSource.Current != null)
                (dbManager.licenseBindingSource.Current as DataRowView).Row["LicenseString"] = encryptor.EncryptString(licenseManager.MakeLicenseString());

            if (!this.Validate()) return;
            dbManager.licenseBindingSource.EndEdit();
            dbManager.UpdateLicense();
        }

        /// <summary>
        /// Refresh license information button click
        /// </summary>
        private void btnRefreshLicenseInfo_Click(object sender, EventArgs e)
        {
            dbManager.licenseTableAdapter.Fill(dbManager.dataSet.License);
            _licenseContorlsCustomized = false;
            CustomizeLicenseControls();
        }

        /// <summary>
        /// Add license point button click
        /// </summary>
        private void btnAddLicInfoRecord_Click(object sender, EventArgs e)
        {
            LicensePoint licensePoint = new LicensePoint();
            LicensePointCard newCard = new LicensePointCard(licensePoint);
            AddLicensePointCard(newCard);
            licensePointsPanel.VerticalScroll.Value = licensePointsPanel.VerticalScroll.Maximum;
        }

        /// <summary>
        /// Clear license points list button click
        /// </summary>
        private void btnClearLicenseInfo_Click(object sender, EventArgs e)
        {
            licensePointsPanel.Controls.Clear();
        }

        /// <summary>
        /// Add license point card to panel
        /// </summary>
        /// <param name="newCard">license point card</param>
        private void AddLicensePointCard(LicensePointCard newCard)
        {
            newCard.Width = licensePointsPanel.Width - 2;
            newCard.Anchor = (System.Windows.Forms.AnchorStyles)(System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right);
            newCard.Location = GetLicensePointCardLocation();
            licensePointsPanel.Controls.Add(newCard);
            newCard.Dock = DockStyle.Top;
            newCard.BringToFront();
        }

        /// <summary>
        /// Get location of new license point card
        /// </summary>
        private Point GetLicensePointCardLocation()
        {
            Point result = new Point(0, 0);
            LicensePointCard licensePointCard = null;

            for (int i = licensePointsPanel.Controls.Count - 1; i >= 0; i--)
            {
                if (licensePointsPanel.Controls[i] is LicensePointCard)
                    licensePointCard = (licensePointsPanel.Controls[i] as LicensePointCard);
            }

            for (int i = licensePointsPanel.Controls.Count - 1; i >= 0; i--)
            {
                if ((licensePointsPanel.Controls[i] is LicensePointCard) && 
                    (licensePointsPanel.Controls[i].Location.Y > licensePointCard.Location.Y))
                        licensePointCard = (licensePointsPanel.Controls[i] as LicensePointCard);
            }

            if (licensePointCard != null)
            {
                result = licensePointCard.Location;
                result.Y += licensePointCard.Height;
            }

            return result;
        }

        #endregion

        #region Schedule

        // Schedule customized fag
         bool _scheduleContorlsCustomized;

        /// <summary>
        /// Customize schedule controls
        /// </summary>
        void CustomizeScheduleControls()
        {
            if (!_scheduleContorlsCustomized)
            {
                // Binding navigator
                controlledProgramsBindingNavigator.BindingSource = dbManager.controlledProgramsBindingSource;

                // Controlled programs data grid view
                controlledProgramsDataGridView.AutoGenerateColumns = false;
                controlledProgramsDataGridView.DataSource = dbManager.controlledProgramsBindingSource;
                controlledProgramNameColumn.DataPropertyName = "Name";
                controlledProgramAllowedColumn.DataPropertyName = "Allowed";

                // Binding navigator
                scheduleBindingNavigator.BindingSource = dbManager.scheduleBindingSource;
                
                // Schedule data grid view
                scheduleDataGridView.AutoGenerateColumns = false;
                scheduleDataGridView.DataSource = dbManager.scheduleBindingSource;

                scheduleUserIDColumn.DataPropertyName = "UserID";
                scheduleGroupIDColumn.DataPropertyName = "GroupID";
                scheduleIncrementValuesColumn.DataPropertyName = "incCountValues";
                scheduleConditionStringColumn.DataPropertyName = "ConditionString";

                scheduleComputerNameColumn.DataSource = dbManager.scheduleComputersBindindSource;
                scheduleComputerNameColumn.DataPropertyName = "CompID";
                scheduleComputerNameColumn.DisplayMember = "Name";
                scheduleComputerNameColumn.ValueMember = "ID";

                scheduleFunctionNameColumn.DataSource = dbManager.scheduleFunctionsBindingSource;
                scheduleFunctionNameColumn.DataPropertyName = "FuncID";
                scheduleFunctionNameColumn.DisplayMember = "Name";
                scheduleFunctionNameColumn.ValueMember = "ID";

                scheduleActionNameColumn.DataSource = dbManager.scheduleActionsBindingSource;
                scheduleActionNameColumn.DataPropertyName = "ActionID";
                scheduleActionNameColumn.DisplayMember = "Name";
                scheduleActionNameColumn.ValueMember = "ID";

                scheduleProgramNameColumn.DataSource = dbManager.scheduleProgramsBindindSource;
                scheduleProgramNameColumn.DataPropertyName = "ProgramID";
                scheduleProgramNameColumn.DisplayMember = "Name";
                scheduleProgramNameColumn.ValueMember = "ID";

                _scheduleContorlsCustomized = true;
            }

            GetUserNames(scheduleUserNameColumn);
            GetUserGroupsNames(scheduleGroupNameColumn);
        }

        /// <summary>
        /// Controlled programs save click
        /// </summary>
        private void controlledProgramsBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.controlledProgramsBindingSource.EndEdit();
            dbManager.UpdateControlledPrograms();
        }

        /// <summary>
        /// Controlled programs refresh button click
        /// </summary>
        private void controlledProgramsBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.controlledProgramsTableAdapter.Fill(dbManager.dataSet.ControlledPrograms);
        }

        /// <summary>
        /// Schedule save button click
        /// </summary>
        private void scheduleBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.scheduleBindingSource.EndEdit();
            dbManager.UpdateSchedule();
        }

        /// <summary>
        /// Schedule refresh button click
        /// </summary>
        private void scheduleBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.scheduleTableAdapter.Fill(dbManager.dataSet.Schedule);
            GetUserNames(scheduleUserNameColumn);
            GetUserGroupsNames(scheduleGroupNameColumn);
        }
        
        /// <summary>
        /// Schedule data grid view cell formating event handler
        /// </summary>
        private void scheduleDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "scheduleUserNameColumn") &&
                (e.RowIndex >= 0) &&
                (e.RowIndex < dbManager.scheduleBindingSource.Count) && 
                (!(dataGridView.Rows[e.RowIndex].Cells["scheduleUserIDColumn"].Value is System.DBNull)) &&
                (scheduleUserNameColumn.Items.Count > 0) &&
                (userNames != null) && (userNames.Count > 0))
            {
                // Set decrypted rule name
                e.Value = GetDictionaryValueByID((int)dataGridView.Rows[e.RowIndex].Cells["scheduleUserIDColumn"].Value, userNames);
                e.FormattingApplied = true;
            }

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "scheduleGroupNameColumn") &&
                (e.RowIndex >= 0) &&
                (e.RowIndex < dbManager.scheduleBindingSource.Count) && 
                (!(dataGridView.Rows[e.RowIndex].Cells["scheduleGroupIDColumn"].Value is System.DBNull)) &&
                (scheduleGroupNameColumn.Items.Count > 0) &&
                (userGroupNames != null) && (userGroupNames.Count > 0))
            {
                // Set decrypted rule name
                e.Value = GetDictionaryValueByID((int)dataGridView.Rows[e.RowIndex].Cells["scheduleGroupIDColumn"].Value, userGroupNames);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Schedule data grid view cell value changed event handler
        /// </summary>
        private void scheduleDataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0))
            {
                if ((dataGridView.Columns[e.ColumnIndex].Name == "scheduleUserNameColumn") && (scheduleUserNameColumn.Items.Count > 0))
                {
                    // Set decrypted rule name
                    string userName = "";
                    int userID = -1;

                    if (!(dataGridView.Rows[e.RowIndex].Cells["scheduleUserNameColumn"].Value is DBNull))
                    {
                        userName = dataGridView.Rows[e.RowIndex].Cells["scheduleUserNameColumn"].Value as string;
                        userID = GetDictionaryIDByValue(userName, userNames);

                        if (userID != -1)
                            dataGridView.Rows[e.RowIndex].Cells["scheduleUserIDColumn"].Value = userID;
                        else
                            dataGridView.Rows[e.RowIndex].Cells["scheduleUserIDColumn"].Value = DBNull.Value;
                    }
                    else
                        dataGridView.Rows[e.RowIndex].Cells["scheduleUserIDColumn"].Value = DBNull.Value;
                }
                else
                    if ((dataGridView.Columns[e.ColumnIndex].Name == "scheduleGroupNameColumn") && (scheduleGroupNameColumn.Items.Count > 0))
                    {
                        // Set decrypted group name
                        string groupName = "";
                        int groupID = -1;

                        if (!(dataGridView.Rows[e.RowIndex].Cells["scheduleGroupNameColumn"].Value is DBNull))
                        {
                            groupName = dataGridView.Rows[e.RowIndex].Cells["scheduleGroupNameColumn"].Value as string;
                            groupID = GetDictionaryIDByValue(groupName, userGroupNames);

                            if (groupID != -1)
                                dataGridView.Rows[e.RowIndex].Cells["scheduleGroupIDColumn"].Value = groupID;
                            else
                                dataGridView.Rows[e.RowIndex].Cells["scheduleGroupIDColumn"].Value = DBNull.Value;
                        }
                        else
                            dataGridView.Rows[e.RowIndex].Cells["scheduleGroupIDColumn"].Value = DBNull.Value;
                    }
                    else
                        if ((dataGridView.Columns[e.ColumnIndex].Name == "scheduleComputerNameColumn") &&
                            (dataGridView.Columns[e.ColumnIndex].Name == "scheduleProgramNameColumn") &&
                            (((dataGridView[e.ColumnIndex, e.RowIndex].Value as string) == String.Empty) ||
                             (dataGridView[e.ColumnIndex, e.RowIndex].Value is DBNull)))
                                dataGridView[e.ColumnIndex, e.RowIndex].Value = System.DBNull.Value;
            }
        }

        /// <summary>
        /// Schedule data grid view cell validating event handler
        /// </summary>
        private void scheduleDataGridView_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
        {
            DataGridView dataGridView = (DataGridView)sender;
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0))
            {
                DataGridViewComboBoxCell cBoxCell = dataGridView.Rows[e.RowIndex].Cells[e.ColumnIndex] as DataGridViewComboBoxCell;
                if ((cBoxCell != null) && ((e.FormattedValue as string) == String.Empty))
                {
                    cBoxCell.Value = DBNull.Value;
                }
            }
        }

        /// <summary>
        /// Schedule data grid view editing control showing event handler
        /// </summary>
        private void scheduleDataGridView_EditingControlShowing(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            ComboBox c = e.Control as ComboBox;
            if (c != null)
            {
                c.DropDownStyle = ComboBoxStyle.DropDown;
            }
        }

        /// <summary>
        /// Condition builder button click
        /// </summary>
        private void scheduleConditionBuilderItem_Click(object sender, EventArgs e)
        {
            if (dbManager.scheduleBindingSource.Current != null)
            {
                // Get condition string
                string condStr = "";
                if (!((dbManager.scheduleBindingSource.Current as DataRowView).Row["ConditionString"] is System.DBNull))
                    condStr = (dbManager.scheduleBindingSource.Current as DataRowView).Row["ConditionString"].ToString();

                // Show schedule condition editor
                BuildScheduleConditionForm scheduleConditionEditor = new BuildScheduleConditionForm(condStr);
                scheduleConditionEditor.ShowDialog();

                if (scheduleConditionEditor.Accepted)
                {
                    (dbManager.scheduleBindingSource.Current as DataRowView).Row["ConditionString"] = scheduleConditionEditor.ScheduleConditionString;
                }

            }
        }

        #endregion

        #region Log-files

        // internal LOG-writer instance
        private LogWriter _logWriter;

        //LOG-writer prorepty
        public LogWriter logWriter
        {
            get
            {
                if (_logWriter == null)
                {
                    string logPath = settingsManager.GetLogPath();
                    string timeString = DateTime.Now.ToString("MM.dd.yy");
                    string logFileName = "NovaTend_Admin_Tool_" + timeString + ".log";
                    logFileName = Path.Combine(logPath, logFileName);

                    _logWriter = new LogWriter(logFileName);
                    if (settingsManager.GetLogEncFlag())
                        _logWriter.AddMode(LogWriter.LOG_MODE_ENCRYPT_MESSAGES);
                }

                return _logWriter;
            }

            set
            {
                _logWriter = value;
            }
        }


        // Log-files reading controls flag
        private bool _logFilesContorlsCustomized;


        /// <summary>
        /// Log-files controls customizing
        /// </summary>
        private void CustomizeLogFilesControls()
        {
            // Check  Log-files reading controls flag
            if (!_logFilesContorlsCustomized)
            {
                logFileClearButton_Click(null, null);

                _logFilesContorlsCustomized = true;
            }
        }

        /// <summary>
        /// Log-files clear button click
        /// </summary>
        private void logFileClearButton_Click(object sender, EventArgs e)
        {
            logFileRichTextBox.Clear();
            logFilePathLabel.Text = "";
        }

        /// <summary>
        /// Log-files open button click
        /// </summary>
        private void logFileOpenButton_Click(object sender, EventArgs e)
        {
            if (openLogFileDialog.ShowDialog() == DialogResult.OK)
            {
                MemoryStream memoryStream = ReadLogFile(openLogFileDialog.FileName);
                if (memoryStream != null)
                {
                    memoryStream.Seek(0, SeekOrigin.Begin);
                    logFileRichTextBox.LoadFile(memoryStream, RichTextBoxStreamType.PlainText);
                    logFilePathLabel.Text = openLogFileDialog.FileName;
                    memoryStream.Close();
                }
            }
        }

        /// <summary>
        /// Read end decrypt log-file
        /// </summary>
        /// <param name="fileName">File name</param>
        /// <returns>Memory stream with readed log-file data</returns>
        private MemoryStream ReadLogFile(string fileName)
        {
            try
            {
                // Preapare output memory stream
                MemoryStream memoryStream = new MemoryStream();
                BinaryWriter binaryWriter = new BinaryWriter(memoryStream);

                // Prepare input file stream
                FileStream fileStream = new FileStream(fileName, FileMode.Open);
                BinaryReader binaryReader = new BinaryReader(fileStream);

                // Read data from file stream
                long pos = 0;
                while (pos < fileStream.Length)
                {
                    byte x = binaryReader.ReadByte();
                    pos += sizeof(byte);

                    // Decrypt encrypted part
                    if (x == 0xFF)
                    {
                        int encBufLen = binaryReader.ReadInt32();
                        pos += sizeof(int);

                        byte[] encBuf = binaryReader.ReadBytes(encBufLen);
                        byte[] decBuf = null;
                        pos += encBufLen;

                        encryptor.UnPackAndDecryptSecurityData(encBuf, ref decBuf);

                        binaryWriter.Write(decBuf);
                    }
                    else
                        binaryWriter.Write(x);
                }

                // Close file stream
                fileStream.Close();

                return memoryStream;
            }
            catch(Exception ex) // Error processing
            {
                logWriter.WriteToLog(ex.Message);
                MessageBox.Show("Log-file reading error!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return null;
            }
        }

        #endregion

        #region Configuration management

        // Configuration management controls flag
        private bool _confManagemengCustomized;
                
        /// <summary>
        /// Configuration management controls customizing
        /// </summary>
        private void CustomizeConfigurationManagementControls()
        {
            // Check configuration management controls flag
            if (!_confManagemengCustomized)
            {
                confTabControl.Hide();

                confTabControl.DrawMode = TabDrawMode.OwnerDrawFixed;
                confTabControl.Appearance = TabAppearance.Buttons;
                confTabControl.ItemSize = new System.Drawing.Size(0, 1);
                confTabControl.SizeMode = TabSizeMode.Fixed;
                confTabControl.TabStop = false;

                confTabControl.Show();

                confTreeView.ExpandAll();

                serviceControllers = new List<ServiceController>();
                serviceDescriptions = new List<string>();
                                
                /*if (GetService("NovaTend_Server", "NovaTend authentication system. Application server.") == null)
                {
                    confTabControl.TabPages.Remove(tabDatabaseSettings);
                    confTabControl.TabPages.Remove(tabSynchronization);
                    confTreeView.Nodes.Remove(confTreeView.Nodes.Find("nodeDatabase", true)[0]);
                    confTreeView.Nodes.Remove(confTreeView.Nodes.Find("nodeSynchronization", true)[0]);
                }*/
                
                confTabControl_SelectedIndexChanged(null, null);

                _confManagemengCustomized = true;
            }
        }


        /// <summary>
        /// Configuration management tab control selected index changed
        /// </summary>
        private void confTabControl_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (confTabControl.SelectedTab != null)
            {
                switch (confTabControl.SelectedTab.Name)
                {
                    case "tabServiceControl":
                        {
                            // Services contol
                            ServicesControlManagement();
                            break;
                        }

                    case "tabIPCSettings":
                        {
                            // IPC settings
                            GetIPCSettings();
                            break;
                        }

                    case "tabDatabaseSettings":
                        {
                            // DB settings
                            GetDatabaseSettings();
                            break;
                        }

                    case "tabMessagesSettings":
                        {
                            // Email settings
                            GetMessagingSettings();
                            break;
                        }

                    case "tabLOGSettings":
                        {
                            // Log-files settings
                            GetLOGSettings();
                            break;
                        }

                    case "tabPostLoginSettings":
                        {
                            // Post login settings
                            GetPostLoginSettings();
                            break;
                        }

                    case "tabSynchronization":
                        {
                            // Sync settings
                            GetSyncSettings();
                            break;
                        }

                    case "tabProgramsControlSettings":
                        {
                            // Programs control settinsg
                            GetProgramsControlSettings();
                            break;
                        }

                    case "tabCommandsHistory":
                        {
                            // Commands history settinsg
                            GetCommandsHistorySettings();
                            break;
                        }

                    case "tabFileTransferSettings":
                        {
                            // File transfer settings
                            GetFileTransferSettings();
                            break;
                        }

                    case "tabUpdateSettings":
                        {
                            // Update settings
                            GetUpdateSettings();
                            break;
                        }
                }
            }
        }

        /// <summary>
        /// Configuration management tree view after node select
        /// </summary>
        private void confTreeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            confTreeView.SelectedImageIndex = e.Node.ImageIndex;
            confTreeView.ExpandAll();

            if (e.Node.ForeColor != Color.Gray)
            {
                switch (e.Node.Name)
                {
                    case "nodeServicesControl":
                        {
                            // Services controll
                            confTabControl.SelectedTab = tabServiceControl;
                            break;
                        }

                    case "nodeSettings":
                        {
                            // Services configuration
                            confTabControl.SelectedTab = tabServicesConfiguration;
                            break;
                        }

                    case "nodeIPC":
                        {
                            // IPC settings
                            confTabControl.SelectedTab = tabIPCSettings;
                            break;
                        }

                    case "nodeDatabase":
                        {
                            // Database settings
                            confTabControl.SelectedTab = tabDatabaseSettings;
                            break;
                        }

                    case "nodeMessages":
                        {
                            // Email settings
                            confTabControl.SelectedTab = tabMessagesSettings;
                            break;
                        }

                    case "nodeLOG":
                        {
                            // LOG file settings
                            confTabControl.SelectedTab = tabLOGSettings;
                            break;
                        }

                    case "nodePostLogin":
                        {
                            // Post login settings
                            confTabControl.SelectedTab = tabPostLoginSettings;
                            break;
                        }

                    case "nodeSynchronization":
                        {
                            // Sync settings
                            confTabControl.SelectedTab = tabSynchronization;
                            break;
                        }

                    case "nodeProgramsControl":
                        {
                            // Programs control settinsg
                            confTabControl.SelectedTab = tabProgramsControlSettings;
                            break;
                        }

                    case "nodeCommandsHistory":
                        {
                            // Commands history settinsg
                            confTabControl.SelectedTab = tabCommandsHistory;
                            break;
                        }

                    case "nodeFileTransferSettings":
                        {
                            // File transfer settinsg
                            confTabControl.SelectedTab = tabFileTransferSettings;
                            break;
                        }

                    case "nodeUpdateSettings":
                        {
                            // Update settinsg
                            confTabControl.SelectedTab = tabUpdateSettings;
                            break;
                        }
                }
            }
        }

        #region Services configuration

        /// <summary>
        /// Services configuration labels click
        /// </summary>
        private void ipcSettingsLabel_Click(object sender, EventArgs e)
        {
            string lbl = (sender as Label).Tag.ToString();
            
            switch (lbl)
            {
                case "1":
                    {
                        confTreeView.SelectedNode = confTreeView.Nodes.Find("nodeIPC", true)[0];
                        break;
                    }

                case "2":
                    {
                        confTreeView.SelectedNode = confTreeView.Nodes.Find("nodeDatabase", true)[0];
                        break;
                    }

                case "3":
                    {
                        confTreeView.SelectedNode = confTreeView.Nodes.Find("nodeMessages", true)[0];
                        break;
                    }

                case "4":
                    {
                        confTreeView.SelectedNode = confTreeView.Nodes.Find("nodeLOG", true)[0];
                        break;
                    }

                case "5":
                    {
                        confTreeView.SelectedNode = confTreeView.Nodes.Find("nodePostLogin", true)[0];
                        break;
                    }

                case "6":
                    {
                        confTreeView.SelectedNode = confTreeView.Nodes.Find("nodeProgramsControl", true)[0];
                        break;
                    }

                case "7":
                    {
                        confTreeView.SelectedNode = confTreeView.Nodes.Find("nodeCommandsHistory", true)[0];
                        break;
                    }

                case "8":
                    {
                        confTreeView.SelectedNode = confTreeView.Nodes.Find("nodeFileTransferSettings", true)[0];
                        break;
                    }

                case "9":
                    {
                        confTreeView.SelectedNode = confTreeView.Nodes.Find("nodeUpdateSettings", true)[0];
                        break;
                    }
            }
        }

        #endregion

        #region Services control

        // Services list
        List<ServiceController> serviceControllers;

        // Service descriptions list
        List<string> serviceDescriptions;

        /// <summary>
        /// Convert service status to string value
        /// </summary>
        /// <param name="status">Service status</param>
        /// <returns>service ststus as string</returns>
        private string ServiceStatusText(ServiceControllerStatus status)
        {
            switch (status)
            {
                case ServiceControllerStatus.Running: return "Running";
                case ServiceControllerStatus.StartPending: return "Start pending";
                case ServiceControllerStatus.Stopped: return "Stopped";
                case ServiceControllerStatus.StopPending: return "Stop pending";
                case ServiceControllerStatus.Paused: return "Paused";
                case ServiceControllerStatus.PausePending: return "Pause pending";
                case ServiceControllerStatus.ContinuePending: return "Continue pending";
                default: return "Unknown";
            }
        }

        /// <summary>
        /// Get service by name and put it to
        /// the services list
        /// </summary>
        /// <param name="serviceName">service name</param>
        /// <param name="serviceDescription">service description</param>
        private ServiceController GetService(string serviceName, string serviceDescription)
        {
            ServiceController svc;
            
            try
            {
                // Call SCM and get service
                svc = ServiceController.GetServices().FirstOrDefault(x => x.ServiceName == serviceName); ;
            }
            catch (InvalidOperationException)
            {
                svc = null;
            }
            
            if (svc != null)
            {
                // Fill all service depended lists
                ListViewItem lvItem = new ListViewItem(svc.DisplayName);
                lvItem.SubItems.Add(ServiceStatusText(svc.Status));
                lvItem.ImageIndex = 8;

                servicesListView.Items.Add(lvItem);

                serviceDescriptions.Add(serviceDescription);

                serviceControllers.Add(svc);
            }

            return svc;
        }

        /// <summary>
        /// Services control management page settings
        /// </summary>
        private void ServicesControlManagement()
        {
            // Get selected item index
            int selIndex = -1;
            if (servicesListView.SelectedIndices.Count == 1)
                selIndex = servicesListView.SelectedIndices[0];

            // Clear all
            serviceControllers.Clear();
            serviceDescriptions.Clear();
            servicesListView.Items.Clear();
            serviceDescriptionTextBox.Text = "";

            // Disable all buttons
            SetServiceControlButtons(null);

            /*
            // Get all services
            ServiceController svc = GetService("NovaTend_Server", "NovaTend authentication system. Application server.");
            if (svc != null)
            {
                // Fill all service depended lists
                ListViewItem lvItem = new ListViewItem(svc.DisplayName);
                lvItem.SubItems.Add(ServiceStatusText(svc.Status));
                lvItem.ImageIndex = 8;

                servicesListView.Items.Add(lvItem);
                serviceDescriptions.Add("NovaTend authentication system. Application server.");
                serviceControllers.Add(svc);
            }

            svc = GetService("NovaTend_Client", "NovaTend authentication system. Application client.");
            if (svc != null)
            {
                // Fill all service depended lists
                ListViewItem lvItem = new ListViewItem(svc.DisplayName);
                lvItem.SubItems.Add(ServiceStatusText(svc.Status));
                lvItem.ImageIndex = 8;

                servicesListView.Items.Add(lvItem);
                serviceDescriptions.Add("NovaTend authentication system. Application client.");
                serviceControllers.Add(svc);
            }
            */

            // Get all services
            ServiceController svc = GetService("NovaTend_HOST_Server", "NovaTend authentication system. HOST-server.");
            
            if (svc == null)
            {
                tabDatabaseSettings.Enabled = false;
                tabSynchronization.Enabled = false;

                dbSettingsPictureBox.Enabled = false;
                dbSettingsLabel.Enabled = false;

                confTreeView.Nodes.Find("nodeDatabase", true)[0].ForeColor = Color.Gray;
                confTreeView.Nodes.Find("nodeSynchronization", true)[0].ForeColor = Color.Gray;
            }
            else
            {
                tabDatabaseSettings.Enabled = true;
                tabSynchronization.Enabled = true;

                dbSettingsPictureBox.Enabled = true;
                dbSettingsLabel.Enabled = true;

                confTreeView.Nodes.Find("nodeDatabase", true)[0].ForeColor = Color.Empty;
                confTreeView.Nodes.Find("nodeSynchronization", true)[0].ForeColor = Color.Empty;

                logWriter.WriteToLog("Service control --> On this PC the NovaTend HOST-server is installed");
                logWriter.WriteToLog("Service control --> Application Server status: " + ServiceStatusText(svc.Status));
            }


            svc = GetService("NovaTend_HUB_Server", "NovaTend authentication system. HUB-server.");

            if (svc != null)
            {
                logWriter.WriteToLog("Service control --> On this PC the NovaTend HUB-server is installed");
                logWriter.WriteToLog("Service control --> Application Client status: " + ServiceStatusText(svc.Status));
            }

            svc = GetService("NovaTend_Update_Service", "NovaTend service that implements all system component updating functionality");

            if (svc != null)
            {
                logWriter.WriteToLog("Service control --> On this PC the NovaTend HUB-server is installed");
                logWriter.WriteToLog("Service control --> Application Client status: " + ServiceStatusText(svc.Status));
            }

            // Restore selection
            if ((selIndex > -1) && (selIndex < servicesListView.Items.Count))
            {
                servicesListView.Focus();
                servicesListView.Items[selIndex].Selected = true;
                servicesListView.Items[selIndex].Focused = true;
                servicesListView.Refresh();
            }
        }

        /// <summary>
        /// Set service control buttons
        /// </summary>
        /// <param name="service">selected service</param>
        private void SetServiceControlButtons(ServiceController service)
        {
            if (service != null)
            {
                switch (service.Status)
                {
                        
                    // Running
                    case ServiceControllerStatus.Running:
                        {
                            btnStart.Enabled = false;
                            btnStop.Enabled = true;
                            btnRestart.Enabled = true;
                            btnPause.Enabled = true;
                            break;
                        }
                        
                    // Start pending
                    case ServiceControllerStatus.StartPending:
                        {
                            btnStart.Enabled = false;
                            btnStop.Enabled = false;
                            btnRestart.Enabled = false;
                            btnPause.Enabled = false;
                            break;
                        }

                    // Stopped
                    case ServiceControllerStatus.Stopped:
                        {
                            btnStart.Enabled = true;
                            btnStop.Enabled = false;
                            btnRestart.Enabled = false;
                            btnPause.Enabled = false;
                            break;
                        }

                    // Stop pending
                    case ServiceControllerStatus.StopPending:
                        {
                            btnStart.Enabled = false;
                            btnStop.Enabled = false;
                            btnRestart.Enabled = false;
                            btnPause.Enabled = false;
                            break;
                        }

                    // Paused
                    case ServiceControllerStatus.Paused:
                        {
                            btnStart.Enabled = true;
                            btnStop.Enabled = true;
                            btnRestart.Enabled = true;
                            btnPause.Enabled = false;
                            break;
                        }

                    // Pause pending
                    case ServiceControllerStatus.PausePending:
                        {
                            btnStart.Enabled = false;
                            btnStop.Enabled = false;
                            btnRestart.Enabled = false;
                            btnPause.Enabled = false;
                            break;
                        }

                    // Continue pending
                    case ServiceControllerStatus.ContinuePending:
                        {
                            btnStart.Enabled = false;
                            btnStop.Enabled = false;
                            btnRestart.Enabled = false;
                            btnPause.Enabled = false;
                            break;
                        }
                }
            }
            else
            {
                // No service selected
                btnStart.Enabled = false;
                btnStop.Enabled = false;
                btnRestart.Enabled = false;
                btnPause.Enabled = false;
            }
        }
        
        /// <summary>
        /// Services list selected index changed
        /// </summary>
        private void servicesListView_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (servicesListView.SelectedIndices.Count == 1)
            {
                int index = servicesListView.SelectedIndices[0];
                if (index >= 0)
                {
                    serviceDescriptionTextBox.Text = serviceDescriptions[index];
                    SetServiceControlButtons(serviceControllers[index]);
                }
            }
        }

        /// <summary>
        /// Refresh services list button click
        /// </summary>
        private void btnRefreshServicesList_Click(object sender, EventArgs e)
        {
            ServicesControlManagement();
        }

        /// <summary>
        /// Start service button click
        /// </summary>
        private void btnStart_Click(object sender, EventArgs e)
        {
            if (servicesListView.SelectedIndices.Count == 1)
            {
                int index = servicesListView.SelectedIndices[0];
                if (index >= 0)
                {
                    try
                    {
                        ServiceController service = serviceControllers[index];

                        logWriter.WriteToLog("Service control --> Trying to start service " + service.DisplayName);
                        
                        // If service paused then continue
                        if (service.Status == ServiceControllerStatus.Paused)
                        {
                            if (service.CanPauseAndContinue)
                            {
                                service.Continue();
                            }
                            else
                            {
                                MessageBox.Show("Can't continue this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                logWriter.WriteToLog("Service control --> This service was paused.  Can't continue this service!");
                            }

                            service.Refresh();

                            // Wait when service run
                            while (service.Status == ServiceControllerStatus.ContinuePending)
                            {
                                service.Refresh();
                                Thread.Sleep(100);
                            }

                            // Update service status info
                            if (service.Status == ServiceControllerStatus.Running)
                            {
                                servicesListView.Items[index].SubItems[1].Text = ServiceStatusText(service.Status);
                                servicesListView.Refresh();
                            }
                            else
                            {
                                MessageBox.Show("Can't continue this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                logWriter.WriteToLog("Service control --> This service was paused.  Can't continue this service!");
                            }
                        }

                        // If service stopped then start
                        if (service.Status == ServiceControllerStatus.Stopped)
                        {

                            service.Start();
                            service.Refresh();

                            // Wait when service run
                            while (service.Status == ServiceControllerStatus.StartPending)
                            {
                                service.Refresh();
                                Thread.Sleep(100);
                            }

                            // Update service status info
                            if (service.Status == ServiceControllerStatus.Running)
                            {
                                servicesListView.Items[index].SubItems[1].Text = ServiceStatusText(service.Status);
                                servicesListView.Refresh();
                            }
                            else
                            {
                                MessageBox.Show("Can't start this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                logWriter.WriteToLog("Service control --> Can't start this service!");
                            }
                        }

                        logWriter.WriteToLog("Service control --> Service successfully started!");

                        // Set buttons
                        SetServiceControlButtons(service);
                    }
                    catch
                    {
                        MessageBox.Show("Can't start this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        logWriter.WriteToLog("Service control --> Can't start this service!");
                    }
                }
            }
        }

        /// <summary>
        /// Stop service button click
        /// </summary>
        private void btnStop_Click(object sender, EventArgs e)
        {
            if (servicesListView.SelectedIndices.Count == 1)
            {
                int index = servicesListView.SelectedIndices[0];
                if (index >= 0)
                {
                    try
                    {
                        ServiceController service = serviceControllers[index];
                        logWriter.WriteToLog("Service control --> Trying to stop service " + service.DisplayName);

                        // Stop selected service
                        if (service.CanStop)
                            service.Stop();
                        else
                        {
                            MessageBox.Show("Can't stop this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            logWriter.WriteToLog("Service control --> Can't stop this service!");
                        }

                        service.Refresh();
                        
                        // Wait when service stop
                        while (service.Status == ServiceControllerStatus.StopPending)
                        {
                            service.Refresh();
                            Thread.Sleep(5);
                        }

                        // Update service status info
                        if (service.Status == ServiceControllerStatus.Stopped)
                        {
                            servicesListView.Items[index].SubItems[1].Text = ServiceStatusText(service.Status);
                            servicesListView.Refresh();
                        }
                        else
                        {
                            MessageBox.Show("Can't stop this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            logWriter.WriteToLog("Service control --> Can't stop this service!");
                        }

                        logWriter.WriteToLog("Service control --> Service successfully stoped!");

                        // Set buttons
                        SetServiceControlButtons(service);
                    }
                    catch
                    {
                        MessageBox.Show("Can't stop this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        logWriter.WriteToLog("Service control --> Can't stop this service!");
                    }
                }
            }
        }

        /// <summary>
        /// Pause service button click
        /// </summary>
        private void btnPause_Click(object sender, EventArgs e)
        {
            if (servicesListView.SelectedIndices.Count == 1)
            {
                int index = servicesListView.SelectedIndices[0];
                if (index >= 0)
                {
                    try
                    {
                        ServiceController service = serviceControllers[index];
                        logWriter.WriteToLog("Service control --> Trying to pause service " + service.DisplayName);

                        // Pause selected service
                        if (service.CanPauseAndContinue)
                            service.Pause();
                        else
                        {
                            MessageBox.Show("Can't pause this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            logWriter.WriteToLog("Service control --> Can't pause this service!");
                        }

                        service.Refresh();

                        // Wait when service pause
                        while (service.Status == ServiceControllerStatus.PausePending)
                        {
                            service.Refresh();
                            Thread.Sleep(5);
                        }

                        // Update service status info
                        if (service.Status == ServiceControllerStatus.Paused)
                        {
                            servicesListView.Items[index].SubItems[1].Text = ServiceStatusText(service.Status);
                            servicesListView.Refresh();
                        }
                        else
                        {
                            MessageBox.Show("Can't pause this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            logWriter.WriteToLog("Service control --> Can't pause this service!");
                        }

                        logWriter.WriteToLog("Service control --> Service successfully paused!");

                        // Set buttons
                        SetServiceControlButtons(service);
                    }
                    catch
                    {
                        MessageBox.Show("Can't pause this service!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        logWriter.WriteToLog("Service control --> Can't pause this service!");
                    }
                }
            }
        }

        /// <summary>
        /// Restart service button click
        /// </summary>
        private void btnRestart_Click(object sender, EventArgs e)
        {
            // Stop service
            btnStop_Click(sender, e);

            // Start service
            btnStart_Click(sender, e);
        }

        /// <summary>
        /// Restart all services after settings saving
        /// </summary>
        private void ServicesRestartConfirm()
        {
            int count = 0;
            for (int i = 0; i < serviceControllers.Count; i++)
                if (serviceControllers[i].Status == ServiceControllerStatus.Running)
                    count++;

            if (count > 0)
            {
                if (MessageBox.Show("Settings will take effect only after restarting services. Restart the services now?", "Attention", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == System.Windows.Forms.DialogResult.Yes)
                {
                    for (int i = 0; i < serviceControllers.Count; i++)
                    {
                        if (serviceControllers[i].Status == ServiceControllerStatus.Running)
                        {
                            servicesListView.SelectedIndices.Clear();
                            servicesListView.SelectedIndices.Add(i);
                            btnRestart_Click(null, null);
                        }
                    }
                }
            }

        }

        #endregion

        #region IPC settings

        // HOST-server settings
        private SERVER_DESCRIPTION hostServerSettings;

        // HUB-server settings
        private SERVER_DESCRIPTION hubServerSettings;

        // DESKTOP-server settings
        private SERVER_DESCRIPTION desktopServerSettings;

        // GLOBAL-server settings
        private SERVER_DESCRIPTION globalServerSettings;

        // Alternative servers settings
        private SERVER_DESCRIPTION_LIST alternativeServersSettings;

        // Current alternative server
        private int currentAltServerIndex;

        /// <summary>
        /// Get IPC settings
        /// </summary>
        private void GetIPCSettings()
        {
            // Load settings from registry
            hostServerSettings = settingsManager.GetHostServer();
            hubServerSettings = settingsManager.GetHubServer();
            desktopServerSettings = settingsManager.GetDesktopServer();
            globalServerSettings = settingsManager.GetGlobalServer();

            alternativeServersSettings = settingsManager.GetAlternativeHostServers();

            // Put HOST-server values to controls
            hostServerIDTextBox.Text = hostServerSettings.serverID.ToString();
            hostServerTypeComboBox.SelectedIndex = hostServerSettings.serverType;
            hostServerNameTextBox.Text = hostServerSettings.serverName;
            hostServerPortTextBox.Text = hostServerSettings.port.ToString();
            hostServerAddressTextBox.Text = hostServerSettings.ipAddress;
            hostServerPriorityNud.Value = hostServerSettings.serverPriority;
            hostStartingCheckBox.Checked = settingsManager.GetHostServerStartingFlag();

            // Put HUB-server values to controls
            hubServerIDTextBox.Text = hubServerSettings.serverID.ToString();
            hubServerTypeComboBox.SelectedIndex = hubServerSettings.serverType;
            hubServerNameTextBox.Text = hubServerSettings.serverName;
            hubServerPortTextBox.Text = hubServerSettings.port.ToString();
            hubServerAddressTextBox.Text = hubServerSettings.ipAddress;
            hubServerPriorityNud.Value = hubServerSettings.serverPriority;
            hubStartingCheckBox.Checked = settingsManager.GetHubServerStartingFlag();

            // Put DESKTOP-server values to controls
            desktopServerIDTextBox.Text = desktopServerSettings.serverID.ToString();
            desktopServerTypeComboBox.SelectedIndex = desktopServerSettings.serverType;
            desktopServerNameTextBox.Text = desktopServerSettings.serverName;
            desktopServerPortTextBox.Text = desktopServerSettings.port.ToString();
            desktopServerAddressTextBox.Text = desktopServerSettings.ipAddress;
            desktopServerPriorityNud.Value = desktopServerSettings.serverPriority;
            desktopStartingCheckBox.Checked = settingsManager.GetDesktopServerStartingFlag();

            // Put GLOBAL-server values to controls
            globalServerIDTextBox.Text = globalServerSettings.serverID.ToString();
            globalServerTypeComboBox.SelectedIndex = globalServerSettings.serverType;
            globalServerNameTextBox.Text = globalServerSettings.serverName;
            globalServerPortTextBox.Text = globalServerSettings.port.ToString();
            globalServerAddressTextBox.Text = globalServerSettings.ipAddress;
            globalServerPriorityNud.Value = globalServerSettings.serverPriority;

            // Load alternative servers
            currentAltServerIndex = -1;
            btnFirstServer_Click(null, null);
        }

        /// <summary>
        /// Get alternative server data
        /// </summary>
        void GetAlternativeServerData()
        {
            if ((alternativeServersSettings != null) && (alternativeServersSettings.Count > 0) &&
                (currentAltServerIndex >= 0) && (currentAltServerIndex <= alternativeServersSettings.Count))
            {
                serverIDTextBox.Text = alternativeServersSettings[currentAltServerIndex].serverID.ToString();
                serverTypeComboBox.SelectedIndex = alternativeServersSettings[currentAltServerIndex].serverType;
                serverNameTextBox.Text = alternativeServersSettings[currentAltServerIndex].serverName;
                serverPortTextBox.Text = alternativeServersSettings[currentAltServerIndex].port.ToString();
                serverAddressTextBox.Text = alternativeServersSettings[currentAltServerIndex].ipAddress;
                serverPriorityNud.Value = alternativeServersSettings[currentAltServerIndex].serverPriority;

                btnDelServer.Enabled = true;

                if (currentAltServerIndex == 0)
                {
                    btnFirstServer.Enabled = false;
                    btnPrevServer.Enabled = false;
                }
                else
                {
                    btnFirstServer.Enabled = true;
                    btnPrevServer.Enabled = true;
                }

                if (currentAltServerIndex == alternativeServersSettings.Count - 1)
                {
                    btnLastServer.Enabled = false;
                    btnNextServer.Enabled = false;
                }
                else
                {
                    btnLastServer.Enabled = true;
                    btnNextServer.Enabled = true;
                }
            }
            else
            {
                btnFirstServer.Enabled = false;
                btnLastServer.Enabled = false;
                btnPrevServer.Enabled = false;
                btnNextServer.Enabled = false;
                btnDelServer.Enabled = false;
            }
        }

        /// <summary>
        /// Set alternative server data
        /// </summary>
        void SetAlternativeServerData()
        {
            try
            {
                if ((alternativeServersSettings != null) &&
                    (alternativeServersSettings.Count > 0) &&
                    (currentAltServerIndex >= 0) && (currentAltServerIndex <= alternativeServersSettings.Count))
                {
                    alternativeServersSettings[currentAltServerIndex].serverID = Convert.ToUInt32(serverIDTextBox.Text);
                    alternativeServersSettings[currentAltServerIndex].serverType = serverTypeComboBox.SelectedIndex;
                    alternativeServersSettings[currentAltServerIndex].serverName = serverNameTextBox.Text;
                    alternativeServersSettings[currentAltServerIndex].port = Convert.ToUInt32(serverPortTextBox.Text);
                    alternativeServersSettings[currentAltServerIndex].ipAddress = serverAddressTextBox.Text;
                    alternativeServersSettings[currentAltServerIndex].serverPriority = Convert.ToInt32(serverPriorityNud.Value);
                }
            }
            catch
            {
                MessageBox.Show("Error of alternative server settings!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        
        /// <summary>
        /// First server button click
        /// </summary>
        private void btnFirstServer_Click(object sender, EventArgs e)
        {
            SetAlternativeServerData();
            currentAltServerIndex = 0;
            GetAlternativeServerData();
        }

        /// <summary>
        /// Last server button click
        /// </summary>
        private void btnLastServer_Click(object sender, EventArgs e)
        {
            SetAlternativeServerData();
            currentAltServerIndex = alternativeServersSettings.Count - 1;
            GetAlternativeServerData();
        }

        /// <summary>
        /// Previous server button click
        /// </summary>
        private void btnPrevServer_Click(object sender, EventArgs e)
        {
            SetAlternativeServerData();
            currentAltServerIndex -= 1;
            GetAlternativeServerData();
        }

        /// <summary>
        /// Next server button click
        /// </summary>
        private void btnNextServer_Click(object sender, EventArgs e)
        {
            SetAlternativeServerData();
            currentAltServerIndex += 1;
            GetAlternativeServerData();
        }

        /// <summary>
        /// Add server button click
        /// </summary>
        private void btnAddServer_Click(object sender, EventArgs e)
        {
            if (alternativeServersSettings == null)
                alternativeServersSettings = new SERVER_DESCRIPTION_LIST();

            SERVER_DESCRIPTION server = new SERVER_DESCRIPTION();
            server.serverID = 0;
            server.serverType = 0;
            server.serverPriority = 0;
            server.port = 0;
            server.ipAddress = "127.0.0.1";
            server.serverName = "New server";

            alternativeServersSettings.Add(server);

            if (alternativeServersSettings.Count == 1)
                currentAltServerIndex = - 1;

            btnLastServer_Click(null, null);
        }

        /// <summary>
        /// Delete server button click
        /// </summary>
        private void btnDelServer_Click(object sender, EventArgs e)
        {
            if ((alternativeServersSettings != null) && (alternativeServersSettings.Count > 0))
            {
                alternativeServersSettings.Remove(alternativeServersSettings[currentAltServerIndex]);
                if (currentAltServerIndex > alternativeServersSettings.Count - 1)
                    currentAltServerIndex = alternativeServersSettings.Count - 1;
                GetAlternativeServerData();
            }
        }

        /// <summary>
        /// Save IPC settings button click
        /// </summary>
        private void btnSaveIPCSettings_Click(object sender, EventArgs e)
        {
            try
            {
                logWriter.WriteToLog("Configuration management --> Trying to save IPC settings ");

                // Save HOST-server settings
                hostServerSettings.serverID = Convert.ToUInt32(hostServerIDTextBox.Text);
                hostServerSettings.serverType = hostServerTypeComboBox.SelectedIndex;
                hostServerSettings.serverName = hostServerNameTextBox.Text;
                hostServerSettings.port = Convert.ToUInt32(hostServerPortTextBox.Text);
                hostServerSettings.ipAddress = hostServerAddressTextBox.Text;
                hostServerSettings.serverPriority = Convert.ToInt32(hostServerPriorityNud.Value);

                if ((!settingsManager.SetHostServer(hostServerSettings)) || (!settingsManager.SetHostServerStartingFlag(hostStartingCheckBox.Checked)))
                {
                    MessageBox.Show("Can't save HOST-server settings!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("Configuration management --> Can't save HOST-server settings!");
                    return;
                }

                // Save HUB-server settings
                hubServerSettings.serverID = Convert.ToUInt32(hubServerIDTextBox.Text);
                hubServerSettings.serverType = hubServerTypeComboBox.SelectedIndex;
                hubServerSettings.serverName = hubServerNameTextBox.Text;
                hubServerSettings.port = Convert.ToUInt32(hubServerPortTextBox.Text);
                hubServerSettings.ipAddress = hubServerAddressTextBox.Text;
                hubServerSettings.serverPriority = Convert.ToInt32(hubServerPriorityNud.Value);

                if ((!settingsManager.SetHubServer(hubServerSettings)) || (!settingsManager.SetHubServerStartingFlag(hubStartingCheckBox.Checked)))
                {
                    MessageBox.Show("Can't save HUB-server settings!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("Configuration management --> Can't save HUB-server settings!");
                    return;
                }

                // Save DESKTOP-server settings
                desktopServerSettings.serverID = Convert.ToUInt32(desktopServerIDTextBox.Text);
                desktopServerSettings.serverType = desktopServerTypeComboBox.SelectedIndex;
                desktopServerSettings.serverName = desktopServerNameTextBox.Text;
                desktopServerSettings.port = Convert.ToUInt32(desktopServerPortTextBox.Text);
                desktopServerSettings.ipAddress = desktopServerAddressTextBox.Text;
                desktopServerSettings.serverPriority = Convert.ToInt32(desktopServerPriorityNud.Value);

                if ((!settingsManager.SetDesktopServer(desktopServerSettings)) || (!settingsManager.SetDesktopServerStartingFlag(desktopStartingCheckBox.Checked)))
                {
                    MessageBox.Show("Can't save DESKTOP-server settings!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("Configuration management --> Can't save DESKTOP-server settings!");
                    return;
                }

                // Save GLOBAL-server settings
                globalServerSettings.serverID = Convert.ToUInt32(globalServerIDTextBox.Text);
                globalServerSettings.serverType = globalServerTypeComboBox.SelectedIndex;
                globalServerSettings.serverName = globalServerNameTextBox.Text;
                globalServerSettings.port = Convert.ToUInt32(globalServerPortTextBox.Text);
                globalServerSettings.ipAddress = globalServerAddressTextBox.Text;
                globalServerSettings.serverPriority = Convert.ToInt32(globalServerPriorityNud.Value);

                if (!settingsManager.SetGlobalServer(globalServerSettings))
                {
                    MessageBox.Show("Can't save GLOBAL-server settings!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("Configuration management --> Can't save GLOBAL-server settings!");
                    return;
                }

                // Save alternative servers settings
                if (!settingsManager.SetAlternativeHostServers(alternativeServersSettings))
                {
                    MessageBox.Show("Can't save alternative HOST-servers settings!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("Configuration management --> Can't save alternative HOST-servers settings!");
                    return;
                }

                logWriter.WriteToLog("Configuration management --> IPC settings saved");

                ServicesRestartConfirm();
            }
            catch
            {
                MessageBox.Show("Error of IPC settings saving!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        #endregion

        #region Database settings

        /// <summary>
        /// Get DB settings
        /// </summary>
        private void GetDatabaseSettings()
        {
            string dbServerName = settingsManager.GetDBServerName();
            string dbName = settingsManager.GetDBName();
            string dbUserName = settingsManager.GetDBUserName();
            string dbPassword = settingsManager.GetDBPassword();

            if (dbServerName != null)
                dbServerTextBox.Text = dbServerName;
            else
                dbServerTextBox.Text = "";

            if (dbName != null)
                dbNameTextBox.Text = dbName;
            else
                dbNameTextBox.Text = "";

            if (dbUserName != null)
                dbUserNameTextBox.Text = dbUserName;
            else
                dbUserNameTextBox.Text = "";

            if (dbPassword != null)
                dbPasswordTextBox.Text = dbPassword;
            else
                dbPasswordTextBox.Text = "";

            onDelUserAccActionComboBox.SelectedIndex = settingsManager.GetUserAccountDeleteDBAction();
        }

        /// <summary>
        /// Save DB settings button click
        /// </summary>
        private void btnDataBaseAccessSettingsSave_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Configuration management --> Trying to save DB settings ");

            if (!settingsManager.SetDBServerName(dbServerTextBox.Text))
            {
                MessageBox.Show("Can't save database server name!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save database server name!");
                return;
            }

            if (!settingsManager.SetDBName(dbNameTextBox.Text))
            {
                MessageBox.Show("Can't save database name!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save database name!");
                return;
            }

            if (!settingsManager.SetDBUserName(dbUserNameTextBox.Text))
            {
                MessageBox.Show("Can't save database user name!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save database user name!");
                return;
            }

            if (!settingsManager.SetDBPassword(dbPasswordTextBox.Text))
            {
                MessageBox.Show("Can't save database password!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save database password!");
                return;
            }

            if (!settingsManager.SetUserAccountDeleteDBAction(onDelUserAccActionComboBox.SelectedIndex))
            {
                MessageBox.Show("Can't save on delete user account action!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save on delete user account action!");
                return;
            }
            
            logWriter.WriteToLog("Configuration management --> DB settings saved");
            ServicesRestartConfirm();
        }

        /// <summary>
        /// Change DB password
        /// </summary>
        private void changeDBPwdLabel_Click(object sender, EventArgs e)
        {
            fmChangePassword fmChangePwd = new fmChangePassword(supervisor);
            fmChangePwd.ShowDialog();

            if (fmChangePwd.PasswordChanged)
            {
                logWriter.WriteToLog("Configuration management --> DB password changed");
                dbPasswordTextBox.Text = fmChangePwd.Password;
            }
        }

        /// <summary>
        /// Mouse hover event handler
        /// </summary>
        private void dbPasswordTextBox_MouseHover(object sender, EventArgs e)
        {
            TextBox textBox = sender as TextBox;
            if (supervisor)
                pwdToolTip.SetToolTip(textBox, textBox.Text);
            else
                pwdToolTip.SetToolTip(textBox, "");
        }

        #endregion

        #region Messaging settings

        /// <summary>
        /// Get messaging settings
        /// </summary>
        private void GetMessagingSettings()
        {
            string host = settingsManager.GetEmailHost();

            if (host != null)
                emailHostTextBox.Text = host;
            else
                emailHostTextBox.Text = "";


            int port = settingsManager.GetEmailPort();

            if (port > 0)
                emailPortTextBox.Text = port.ToString();
            else
                emailPortTextBox.Text = "";

            emailSecTypeComboBox.SelectedIndex = settingsManager.GetEmailSecurityType();

            emailAuthCheckBox.Checked = settingsManager.GetEmailAuthFlag();

            string emailLogin = settingsManager.GetEmailLogin();

            if (emailLogin != null)
                emailLoginTextBox.Text = emailLogin;
            else
                emailLoginTextBox.Text = "";

            string emailPassword = settingsManager.GetEmailPassword();

            if (emailPassword != null)
                emailPasswordTextBox.Text = emailPassword;
            else
                emailPasswordTextBox.Text = "";

            string sender = settingsManager.GetEmailSender();

            if (sender != null)
                emailSenderTextBox.Text = sender;
            else
                emailSenderTextBox.Text = "";

            string recipient = settingsManager.GetEmailRecipient();

            if (recipient != null)
                emailRecipientTextBox.Text = recipient;
            else
                emailRecipientTextBox.Text = "";

            string gvLogin = settingsManager.GetGoogleVoiceLogin();

            if (gvLogin != null)
                gvLoginTextBox.Text = gvLogin;
            else
                gvLoginTextBox.Text = "";

            string gvPassword = settingsManager.GetGoogleVoicePassword();

            if (gvPassword != null)
                gvPasswordTextBox.Text = gvPassword;
            else
                gvPasswordTextBox.Text = "";

            emailAuthCheckBox_CheckedChanged(null, null);
        }

        /// <summary>
        /// Email authentication check box checked changed
        /// </summary>
        private void emailAuthCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (emailAuthCheckBox.Checked)
            {
                emailLoginTextBox.Enabled = true;
                emailPasswordTextBox.Enabled = true;
            }
            else
            {
                emailLoginTextBox.Enabled = false;
                emailPasswordTextBox.Enabled = false;
            }
        }

        /// <summary>
        /// Messaging settings save button click
        /// </summary>
        private void btnMessagingSettingsSave_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Configuration management --> Trying to save messaging settings ");

            if (!settingsManager.SetEmailHost(emailHostTextBox.Text))
            {
                MessageBox.Show("Can't save SMTP host!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save SMTP host!");
                return;
            }

            int port;

            if (int.TryParse(emailPortTextBox.Text, out port))
            {
                if (!settingsManager.SetEmailPort(port))
                {
                    MessageBox.Show("Can't save SMTP server port!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("Configuration management --> Can't save SMTP server port!");
                    return;
                }
            }
            else
            {
                MessageBox.Show("Wrong SMTP server port!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Wrong SMTP server port!");
                return;
            }
                        
            if (!settingsManager.SetEmailSecurityType(emailSecTypeComboBox.SelectedIndex))
            {
                MessageBox.Show("Can't save security type!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save security type!");
                return;
            }

            if (!settingsManager.SetEmailAuthFlag(emailAuthCheckBox.Checked))
            {
                MessageBox.Show("Can't save authentication flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save authentication flag!");
                return;
            }

            if (!settingsManager.SetEmailLogin(emailLoginTextBox.Text))
            {
                MessageBox.Show("Can't save SMTP login!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save SMTP login!");
                return;
            }

            if (!settingsManager.SetEmailPassword(emailPasswordTextBox.Text))
            {
                MessageBox.Show("Can't save SMTP password!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save SMTP password!");
                return;
            }

            if (!settingsManager.SetEmailSender(emailSenderTextBox.Text))
            {
                MessageBox.Show("Can't save sender address!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (!settingsManager.SetEmailRecipient(emailRecipientTextBox.Text))
            {
                MessageBox.Show("Can't save recipient address!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save recipient address!");
                return;
            }

            if (!settingsManager.SetGoogleVoiceLogin(gvLoginTextBox.Text))
            {
                MessageBox.Show("Can't save Google Voice login!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save Google Voice login!");
                return;
            }

            if (!settingsManager.SetGoogleVoicePassword(gvPasswordTextBox.Text))
            {
                MessageBox.Show("Can't save Google Voice password!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save Google Voice password!");
                return;
            }

            logWriter.WriteToLog("Configuration management --> Messaging settings saved");

            ServicesRestartConfirm();
        }

        /// <summary>
        /// Change email password
        /// </summary>
        private void changeEmailPwdLabel_Click(object sender, EventArgs e)
        {
            fmChangePassword fmChangePwd = new fmChangePassword(supervisor);
            fmChangePwd.ShowDialog();

            if (fmChangePwd.PasswordChanged)
            {
                logWriter.WriteToLog("Configuration management --> Email password changed");
                emailPasswordTextBox.Text = fmChangePwd.Password;
            }
        }

        /// <summary>
        /// Change google voice password
        /// </summary>
        private void changeGVoicePwdLabel_Click(object sender, EventArgs e)
        {
            fmChangePassword fmChangePwd = new fmChangePassword(supervisor);
            fmChangePwd.ShowDialog();

            if (fmChangePwd.PasswordChanged)
            {
                logWriter.WriteToLog("Configuration management --> Google Voice password changed");
                gvPasswordTextBox.Text = fmChangePwd.Password;
            }
        }

        #endregion

        #region LOG-files settings

        /// <summary>
        /// Get LOG settings
        /// </summary>
        private void GetLOGSettings()
        {
            logEncryptionCheckBox.Checked = settingsManager.GetLogEncFlag();
            logEmailCheckBox.Checked = settingsManager.GetLogEmailFlag();
            logPathTextBox.Text = settingsManager.GetLogPath();
            fixedSizeCheckBox.Checked = settingsManager.GetLogFixedSizeFlag();
            fixedSizeNumUpDown.Value = settingsManager.GetLogFixedSizeValue();
            fixedSizeCheckBox_CheckedChanged(null, null);
        }

        /// <summary>
        /// Save LOG settings button click
        /// </summary>
        private void btnLogSettingsSave_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Configuration management --> Trying to save LOG-files settings ");

            if (!settingsManager.SetLogEncFlag(logEncryptionCheckBox.Checked))
            {
                MessageBox.Show("Can't save encryption flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save encryption flag!");
                return;
            }

            if (!settingsManager.SetLogEmailFlag(logEmailCheckBox.Checked))
            {
                MessageBox.Show("Can't save email sending flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save email sending flag!");
                return;
            }

            if (!settingsManager.SetLogPath(logPathTextBox.Text))
            {
                MessageBox.Show("Can't save log-files stogare path!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save log-files stogare path!");
                return;
            }

            if (!settingsManager.SetLogFixedSizeFlag(fixedSizeCheckBox.Checked))
            {
                MessageBox.Show("Can't save fixed size flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't fixed size flag!");
                return;
            }

            if (!settingsManager.SetLogFixedSizeValue((int)fixedSizeNumUpDown.Value))
            {
                MessageBox.Show("Can't save fixed size value!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't fixed size value!");
                return;
            }

            if (logEncryptionCheckBox.Checked)
                logWriter.AddMode(LogWriter.LOG_MODE_ENCRYPT_MESSAGES);
            else
                logWriter.RemoveMode(LogWriter.LOG_MODE_ENCRYPT_MESSAGES);

            if (logEmailCheckBox.Checked)
                logWriter.AddMode(LogWriter.LOG_MODE_SEND_MAIL);
            else
                logWriter.RemoveMode(LogWriter.LOG_MODE_SEND_MAIL);

            logWriter.WriteToLog("Configuration management --> LOG-files settings saved");

            ServicesRestartConfirm();
        }

        /// <summary>
        /// LOG path button click
        /// </summary>
        private void logPathButton_Click(object sender, EventArgs e)
        {
            if (logPathTextBox.Text != "")
                logFilesFolderBrowserDialog.SelectedPath = logPathTextBox.Text;

            if (logFilesFolderBrowserDialog.ShowDialog() == DialogResult.OK)
            {
                logPathTextBox.Text = logFilesFolderBrowserDialog.SelectedPath;
            }
        }

        /// <summary>
        /// LOG fixed size check box changed
        /// </summary>
        private void fixedSizeCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (fixedSizeCheckBox.Checked)
                fixedSizeNumUpDown.Enabled = true;
            else
                fixedSizeNumUpDown.Enabled = false;
        }

        #endregion

        #region Post login settings

        /// <summary>
        /// Get post login settings
        /// </summary>
        private void GetPostLoginSettings()
        {
            postLoginPathTextBox.Text = settingsManager.GetPostLoginProcessPath();
            postLoginPeriodicCheckBox.Checked = settingsManager.GetPostLoginPeriodicFlag();
            postLoginPeriodNumUpDown.Value = settingsManager.GetPostLoginPeriod();

            postLoginPeriodicCheckBox_CheckedChanged(null, null);
        }

        /// <summary>
        /// Post login periodic flag check box changed
        /// </summary>
        private void postLoginPeriodicCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (postLoginPeriodicCheckBox.Checked)
                postLoginPeriodNumUpDown.Enabled = true;
            else
                postLoginPeriodNumUpDown.Enabled = false;
        }

        /// <summary>
        /// Post login path button click
        /// </summary>
        private void postLoginPathButton_Click(object sender, EventArgs e)
        {
            if (postLoginOpenFileDialog.ShowDialog() == DialogResult.OK)
            {
                postLoginPathTextBox.Text = postLoginOpenFileDialog.FileName;
            }
        }

        /// <summary>
        /// Save post login settings button click
        /// </summary>
        private void btnPostLoginSettingsSave_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Configuration management --> Trying to save POST LOGIN settings ");

            if (!settingsManager.SetPostLoginProcessPath(postLoginPathTextBox.Text))
            {
                MessageBox.Show("Can't save post login path!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save post login path!");
                return;
            }

            if (!settingsManager.SetPostLoginPeriodicFlag(postLoginPeriodicCheckBox.Checked))
            {
                MessageBox.Show("Can't save post login periodic flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save post login periodic flag!");
                return;
            }

            if (!settingsManager.SetPostLoginPeriod((int)postLoginPeriodNumUpDown.Value))
            {
                MessageBox.Show("Can't save post login period!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save post login period!");
                return;
            }

            logWriter.WriteToLog("Configuration management --> POST LOGIN settings saved");

            ServicesRestartConfirm();
        }

        #endregion

        #region Programs control

        /// <summary>
        /// Get programs control settings
        /// </summary>
        private void GetProgramsControlSettings()
        {
            chbProgramsControlEnabled.Checked = settingsManager.GetProgramsControlFlag();
        }

        /// <summary>
        /// Save settings button click
        /// </summary>
        private void btnProgramsControlSettingsSave_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Configuration management --> Trying to save PROGRAMS CONTROL settings ");

            if (!settingsManager.SetProgramsControlFlag(chbProgramsControlEnabled.Checked))
            {
                MessageBox.Show("Can't save PROGRAMS CONTROL enable flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save PROGRAMS CONTROL enable flag!");
                return;
            }

            logWriter.WriteToLog("Configuration management --> PROGRAMS CONTROL settings saved");

            ServicesRestartConfirm();
        }

        #endregion
        
        #region Synchronization settings

        /// <summary>
        /// Get synchronization settings
        /// </summary>
        private void GetSyncSettings()
        {
            periodicSyncOnOffCheckBox.Checked = settingsManager.GetPeriodicSyncOnOffFlag();
            syncLogonCheckBox.Checked = settingsManager.GetLogonSyncOnOffFlag();
            syncPeriodComboBox.SelectedIndex = settingsManager.GetSyncPeriod();
            lblSyncTime.Text = "Last synchronization: " + settingsManager.GetLastSyncTime();

            revSyncAuthSystemsComboBox.DataSource = dbManager.authSystemsSynchronizeBindingSource;
            revSyncAuthSystemsComboBox.DisplayMember = "Name";
            revSyncAuthSystemsComboBox.ValueMember = "ID";

            revSyncAuthSystemsComboBox_SelectedIndexChanged(null, null);
        }

        /// <summary>
        /// Save sync setting button click
        /// </summary>
        private void btnSaveSyncSettings_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Configuration management --> Trying to save synchronization settings ");

            if (!settingsManager.SetPeriodicSyncOnOffFlag(periodicSyncOnOffCheckBox.Checked))
            {
                MessageBox.Show("Can't save periodic synchronization flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save periodic synchronization flag!");
                return;
            }

            if (!settingsManager.SetLogonSyncOnOffFlag(syncLogonCheckBox.Checked))
            {
                MessageBox.Show("Can't save logon synchronization flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save logon synchronization flag!");
                return;
            }

            if (!settingsManager.SetSyncPeriod(syncPeriodComboBox.SelectedIndex))
            {
                MessageBox.Show("Can't save synchronization period!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save synchronization period!");
                return;
            }

            logWriter.WriteToLog("Configuration management --> Synchronization settings saved");

            ServicesRestartConfirm();

        }

        /// <summary>
        /// Synchronize accounts button click
        /// </summary>
        private void btnForcedSync_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Configuration management --> Forced user accounts synchronization");

            DataRow[] authSystemRows = dbManager.dataSet.AuthSystems.Select();

            if ((authSystemRows != null) && (authSystemRows.Length > 0))
            {
                for (int i = 0; i < authSystemRows.Length; i++)
                {
                    int authSystemID = (int)authSystemRows[i]["ID", DataRowVersion.Original];
                    int authSystemType = (int)authSystemRows[i]["AuthSystemTypeID", DataRowVersion.Original];

                    string filterExpr = "AuthSystemID = " + authSystemID.ToString();
                    DataRow[] uaRows = dbManager.dataSet.UserAccounts.Select(filterExpr);
                    DataRow[] ugRows = dbManager.dataSet.UserGroupAuthSystems.Select(filterExpr);

                    switch (authSystemType)
                    {
                        case UserAccountsSynchronizer.UAC_AD:
                            {
                                // Sync AD accounts
                                if (uaRows != null)
                                    userAccountsSynchronizer.SyncADAccounts(uaRows, UserAccountsSynchronizer.UA_SYNC_INSERT);

                                // Sync AD groups
                                if (ugRows != null)
                                    userAccountsSynchronizer.SyncADGroups(ugRows, UserAccountsSynchronizer.UA_SYNC_INSERT);

                                break;
                            }
                    }
                }
            }

            // Sync group members
            SyncUserGroupMembers();

            string lastSyncStr = DateTime.Now.ToString("G", DateTimeFormatInfo.InvariantInfo);

            if (!settingsManager.SetLastSyncTime(lastSyncStr))
            {
                MessageBox.Show("Can't save last synchronization time!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save last synchronization time!");
                return;
            }

            lblSyncTime.Text = "Last synchronization: " + lastSyncStr;
        }

        /// <summary>
        /// Synchronization authentication systems combo box 
        /// selected index changed event handler
        /// </summary>
        private void revSyncAuthSystemsComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            accountsListView.Items.Clear();
            groupsListView.Items.Clear();

            if (dbManager.authSystemsSynchronizeBindingSource.Current != null)
            {
                int authSystemID = (int)(dbManager.authSystemsSynchronizeBindingSource.Current as DataRowView).Row["ID"];

                byte[] encSettingsString = (dbManager.authSystemsSynchronizeBindingSource.Current as DataRowView).Row["SettingsString"] as byte[];
                string decSettingsString = encryptor.DecryptString(encSettingsString);

                if (decSettingsString != null)
                {
                    List<string> accountsList = userAccountsSynchronizer.EnumerateADUserAcccounts(decSettingsString);
                    List<string> groupsList = userAccountsSynchronizer.EnumerateADGroups(decSettingsString);

                    if (accountsList != null)
                    {
                        for (int i = 0; i < accountsList.Count; i++)
                        {
                            if (!(userAccountsSynchronizer.UserNameLinked(accountsList[i], authSystemID)))
                            {
                                ListViewItem listViewItem = new ListViewItem(accountsList[i]);
                                listViewItem.ImageIndex = 0;
                                accountsListView.Items.Add(listViewItem);
                            }
                        }
                    }

                    if (groupsList != null)
                    {
                        for (int i = 0; i < groupsList.Count; i++)
                        {
                            if (!(userAccountsSynchronizer.UserGroupLinked(groupsList[i], authSystemID)))
                            {
                                ListViewItem listViewItem = new ListViewItem(groupsList[i]);
                                listViewItem.ImageIndex = 1;
                                groupsListView.Items.Add(listViewItem);
                            }
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Refresh users list button click
        /// </summary>
        private void btnRefreshRevUsersList_Click(object sender, EventArgs e)
        {
            revSyncAuthSystemsComboBox_SelectedIndexChanged(null, null);
        }

        /// <summary>
        /// Link account button click
        /// </summary>
        private void btnReverseLink_Click(object sender, EventArgs e)
        {
            if ((accountsListView.SelectedItems != null) && (accountsListView.SelectedItems.Count > 0))
            {

                List<string> userNames = new List<string>();
                List<int> userIDs = new List<int>();
            
                DataRow[] usersRows = dbManager.dataSet.Users.Select();

                if (usersRows != null)
                {
                    for (int i = 0; i < usersRows.Length; i++)
                    {
                        int userID = (int)usersRows[i]["ID", DataRowVersion.Original];
                        byte [] encUserName = usersRows[i]["Name", DataRowVersion.Original] as byte [];
                        string decUserName = encryptor.DecryptString(encUserName);

                        userIDs.Add(userID);
                        userNames.Add(decUserName);
                    }
                }

                fmAddRevUser _fmAddRevUser = new fmAddRevUser(userNames, userIDs, revSyncAuthSystemsComboBox.Text, accountsListView.SelectedItems[0].Text, supervisor);
                _fmAddRevUser.ShowDialog();

                if ((_fmAddRevUser.userID != -1) && (_fmAddRevUser.userPassword != "") && (dbManager.authSystemsSynchronizeBindingSource.Current != null))
                {
                    logWriter.WriteToLog("Configuration management --> Reverse user account synchronization.");
                    logWriter.WriteToLog("Configuration management --> User '" + accountsListView.SelectedItems[0].Text + "' linked with user account '" + _fmAddRevUser.userName + "' of authentication system " + revSyncAuthSystemsComboBox.Text);

                    try
                    {
                        int authSystemID = (int)(dbManager.authSystemsSynchronizeBindingSource.Current as DataRowView).Row["ID"];
                        byte[] userName = encryptor.EncryptString(accountsListView.SelectedItems[0].Text);
                        byte[] userPassword = encryptor.EncryptString(_fmAddRevUser.userPassword);
                        int userID = _fmAddRevUser.userID;

                        dbManager.userAccountsTableAdapter.Insert(userID, authSystemID, userName, userPassword, null, null);
                        dbManager.UpdateUserAccounts();

                        dbManager.userAccountsTableAdapter.Fill(dbManager.dataSet.UserAccounts);

                        string filterExpr = "((AuthSystemID = " + authSystemID.ToString() + ") AND (UserID = " + userID.ToString() + "))";
                        DataRow[] uaRows = dbManager.dataSet.UserAccounts.Select(filterExpr);

                        userAccountsSynchronizer.SyncADAccounts(uaRows, UserAccountsSynchronizer.UA_SYNC_INSERT);
                        
                        btnRefreshRevUsersList_Click(null, null);
                    }
                    catch
                    {
                        MessageBox.Show("Can't link user accounts!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        logWriter.WriteToLog("Configuration management --> Reverse user account synchronization. Can't link user accounts!");
                    }
                }
            }
        }

        /// <summary>
        /// Reverse link of user groups button click
        /// </summary>
        private void btnReverseGroupLink_Click(object sender, EventArgs e)
        {
            if ((groupsListView.SelectedItems != null) && (groupsListView.SelectedItems.Count > 0))
            {

                List<string> groupNames = new List<string>();
                List<int> groupIDs = new List<int>();

                DataRow[] groupsRows = dbManager.dataSet.UserGroups.Select();

                if (groupsRows != null)
                {
                    for (int i = 0; i < groupsRows.Length; i++)
                    {
                        int groupID = (int)groupsRows[i]["ID", DataRowVersion.Original];
                        byte[] encGroupName = groupsRows[i]["Name", DataRowVersion.Original] as byte[];
                        string decGroupName = encryptor.DecryptString(encGroupName);

                        groupIDs.Add(groupID);
                        groupNames.Add(decGroupName);
                    }
                }

                fmAddRevGroup _fmAddRevGroup = new fmAddRevGroup(groupNames, groupIDs, revSyncAuthSystemsComboBox.Text, groupsListView.SelectedItems[0].Text);
                _fmAddRevGroup.ShowDialog();

                if ((_fmAddRevGroup.groupID != -1) && (_fmAddRevGroup.groupName != "") && (dbManager.authSystemsSynchronizeBindingSource.Current != null))
                {
                    logWriter.WriteToLog("Configuration management --> Reverse user group synchronization.");
                    logWriter.WriteToLog("Configuration management --> System group '" + groupsListView.SelectedItems[0].Text + "' linked with group '" + _fmAddRevGroup.groupName + "' of authentication system " + revSyncAuthSystemsComboBox.Text);

                    try
                    {
                        int authSystemID = (int)(dbManager.authSystemsSynchronizeBindingSource.Current as DataRowView).Row["ID"];
                        int authSystemType = (int)(dbManager.authSystemsSynchronizeBindingSource.Current as DataRowView).Row["AuthSystemTypeID"];
                        byte[] groupName = encryptor.EncryptString(groupsListView.SelectedItems[0].Text);
                        int groupID = _fmAddRevGroup.groupID;
                        byte[] groupSettings = null;

                        switch (authSystemType)
                        {
                            case UserAccountsSynchronizer.UAC_AD:
                                {
                                    byte[] encAuthSysSetStr = (dbManager.authSystemsSynchronizeBindingSource.Current as DataRowView).Row["SettingsString"] as byte[];
                                    string decAuthSysSetStr = encryptor.DecryptString(encAuthSysSetStr);
                                    groupSettings = encryptor.EncryptString(userAccountsSynchronizer.GetADGroupSettingsString(decAuthSysSetStr, groupsListView.SelectedItems[0].Text));
                                    break;
                                }
                        }

                        dbManager.userGroupAuthSystemsTableAdapter.Insert(groupID, authSystemID, groupName, groupSettings);
                        dbManager.UpdateUserGroupAuthSystems();

                        dbManager.userGroupAuthSystemsTableAdapter.Fill(dbManager.dataSet.UserGroupAuthSystems);

                        btnRefreshRevUsersList_Click(null, null);
                    }
                    catch
                    {
                        MessageBox.Show("Can't link user group!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        logWriter.WriteToLog("Configuration management --> Reverse user group synchronization. Can't link user groups!");
                    }
                }
            }
        }

        #endregion

        #region Commands history

        /// <summary>
        /// Get commands history settings
        /// </summary>
        private void GetCommandsHistorySettings()
        {
            commandsHistoryPathTextBox.Text = settingsManager.GetCommandHistoryPath();
            commandsHistoryPeriodCheckBox.Checked = settingsManager.GetCommandHistorianPeriodicFlag();
            commandsHistoryPeriodNumUpDown.Value = settingsManager.GetCommandHistorianPeriod();

            currentUserNameCheckBox.Checked = settingsManager.GetLoggedUserNameCommandFlag();
            userEnviromentCheckBox.Checked = settingsManager.GetUserEnvironmentCommandFlag();
            screenshotCheckBox.Checked = settingsManager.GetScreenshotCommandFlag();
            snapshotCheckBox.Checked = settingsManager.GetCamSnapshotCommandFlag();

            commandsHistoryPeriodCheckBox_CheckedChanged(null, null);
        }
        
        /// <summary>
        /// Commands history period check box changed event handler
        /// </summary>
        private void commandsHistoryPeriodCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (commandsHistoryPeriodCheckBox.Checked)
                commandsHistoryPeriodNumUpDown.Enabled = true;
            else
                commandsHistoryPeriodNumUpDown.Enabled = false;
        }

        /// <summary>
        /// Commands history path button click
        /// </summary>
        private void commandsHistoryPathButton_Click(object sender, EventArgs e)
        {
            if (commandHistoryOpenFileDialog.ShowDialog() == DialogResult.OK)
            {
                commandsHistoryPathTextBox.Text = commandHistoryOpenFileDialog.FileName;
            }
        }

        /// <summary>
        /// Save commands history settings button click
        /// </summary>
        private void btnCommandsHistorySettingsSave_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Configuration management --> Trying to save commands history settings ");

            if (!settingsManager.SetCommandHistoryPath(commandsHistoryPathTextBox.Text))
            {
                MessageBox.Show("Can't save commands history file path!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save commands history file!");
                return;
            }

            if (!settingsManager.SetCommandHistorianPeriodicFlag(commandsHistoryPeriodCheckBox.Checked))
            {
                MessageBox.Show("Can't save commands history periodic flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save commands history periodic flag!");
                return;
            }

            if (!settingsManager.SetCommandHistorianPeriod((int)commandsHistoryPeriodNumUpDown.Value))
            {
                MessageBox.Show("Can't save commands history period!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save commands history period!");
                return;
            }

            if (!settingsManager.SetUserEnvironmentCommandFlag(userEnviromentCheckBox.Checked))
            {
                MessageBox.Show("Can't save user environment flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save user environment flag!");
                return;
            }

            if (!settingsManager.SetLoggedUserNameCommandFlag(currentUserNameCheckBox.Checked))
            {
                MessageBox.Show("Can't save current user name flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save current user name flag!");
                return;
            }

            if (!settingsManager.SetScreenshotCommandFlag(screenshotCheckBox.Checked))
            {
                MessageBox.Show("Can't save screenshot flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save screenshot flag!");
                return;
            }

            if (!settingsManager.SetCamSnapshotCommandFlag(snapshotCheckBox.Checked))
            {
                MessageBox.Show("Can't save camera snapshot flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save camera snapshot flag!");
                return;
            }

            logWriter.WriteToLog("Configuration management --> command history settings saved");

            ServicesRestartConfirm();
        }

        #endregion

        #region File transfer

        /// <summary>
        /// Get file transfer settings
        /// </summary>
        private void GetFileTransferSettings()
        {
            uploadDirectoryTextBox.Text = settingsManager.GetUploadDirectory();
            downloadDirectoryTextBox.Text = settingsManager.GetDownloadDirectory();
            tempDirectoryTextBox.Text = settingsManager.GetTempDirectory();
        }

        /// <summary>
        /// Upload directory button click
        /// </summary>
        private void uploadDirectoryButton_Click(object sender, EventArgs e)
        {

            string btnTag = (sender as Button).Tag.ToString();
            
            switch (btnTag)
            {
                case "1":
                    {
                        if (uploadDirectoryTextBox.Text != "")
                            directoriesBrowserDialog.SelectedPath = uploadDirectoryTextBox.Text;

                        if (directoriesBrowserDialog.ShowDialog() == DialogResult.OK)
                        {
                            uploadDirectoryTextBox.Text = directoriesBrowserDialog.SelectedPath;
                        }
                        
                        break;
                    }

                case "2":
                    {
                        if (downloadDirectoryTextBox.Text != "")
                            directoriesBrowserDialog.SelectedPath = downloadDirectoryTextBox.Text;

                        if (directoriesBrowserDialog.ShowDialog() == DialogResult.OK)
                        {
                            downloadDirectoryTextBox.Text = directoriesBrowserDialog.SelectedPath;
                        }

                        break;
                    }

                case "3":
                    {
                        if (tempDirectoryTextBox.Text != "")
                            directoriesBrowserDialog.SelectedPath = tempDirectoryTextBox.Text;

                        if (directoriesBrowserDialog.ShowDialog() == DialogResult.OK)
                        {
                            tempDirectoryTextBox.Text = directoriesBrowserDialog.SelectedPath;
                        }

                        break;
                    }
            }
        }

        /// <summary>
        /// Save file transfer settings button click
        /// </summary>
        private void btnFileTransferSettings_Click(object sender, EventArgs e)
        {
            if (!settingsManager.SetUploadDirectory(uploadDirectoryTextBox.Text))
            {
                MessageBox.Show("Can't save upload directory!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save upload directory!");
                return;
            }

            if (!settingsManager.SetDownloadDirectory(downloadDirectoryTextBox.Text))
            {
                MessageBox.Show("Can't save download directory!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save download directory!");
                return;
            }

            if (!settingsManager.SetTempDirectory(tempDirectoryTextBox.Text))
            {
                MessageBox.Show("Can't save temp directory!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save temp directory!");
                return;
            }

            ServicesRestartConfirm();
        }

        #endregion

        #region Update settings

        /// <summary>
        /// Get update settings
        /// </summary>
        private void GetUpdateSettings()
        {
            updatesEnableCheckBox.Checked = settingsManager.GetUpdatePeriodicFlag();
            updatesPeriodNumericUpDown.Value = settingsManager.GetUpdatePeriod();
            updaterPathTextBox.Text = settingsManager.GetUpdaterPath();
            updateDirPathTextBox.Text = settingsManager.GetUpdateDirPath();
        }

        /// <summary>
        /// Get updater file name button click
        /// </summary>
        private void updaterPathButton_Click(object sender, EventArgs e)
        {
            if (openUpdaterFileDialog.ShowDialog() == DialogResult.OK)
            {
                updaterPathTextBox.Text = openUpdaterFileDialog.FileName;
            }
        }

        /// <summary>
        /// Get update directory name button click
        /// </summary>
        private void updateDirPathButton_Click(object sender, EventArgs e)
        {
            if (updateDirPathTextBox.Text != "")
                updateDirBrowserDialog.SelectedPath = updateDirPathTextBox.Text;

            if (updateDirBrowserDialog.ShowDialog() == DialogResult.OK)
            {
                updateDirPathTextBox.Text = updateDirBrowserDialog.SelectedPath;
            }
        }

        /// <summary>
        /// Save update settings button click
        /// </summary>
        private void btnUpdateSettingsSave_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Configuration management --> Trying to save update settings ");

            if (!settingsManager.SetUpdaterPath(updaterPathTextBox.Text))
            {
                MessageBox.Show("Can't save updater file path!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save updater file!");
                return;
            }

            if (!settingsManager.SetUpdateDirPath(updateDirPathTextBox.Text))
            {
                MessageBox.Show("Can't save update directory path!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save update dir name!");
                return;
            }

            if (!settingsManager.SetUpdatePeriodicFlag(updatesEnableCheckBox.Checked))
            {
                MessageBox.Show("Can't save update periodic flag!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save update periodic flag!");
                return;
            }

            if (!settingsManager.SetUpdatePeriod((int)updatesPeriodNumericUpDown.Value))
            {
                MessageBox.Show("Can't save update period!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("Configuration management --> Can't save update period!");
                return;
            }
                        
            logWriter.WriteToLog("Configuration management --> update settings saved");

            ServicesRestartConfirm();
        }

        /// <summary>
        /// Update period check box changed event handler
        /// </summary>
        private void updatesEnableCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (updatesEnableCheckBox.Checked)
                updatesPeriodNumericUpDown.Enabled = true;
            else
                updatesPeriodNumericUpDown.Enabled = false;
        }

        #endregion

        #endregion

        #region Main window

        /// <summary>
        /// Main tab control selected index changed event handler
        /// </summary>
        private void mainTabControl_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (mainTabControl.SelectedTab != null)
                switch (mainTabControl.SelectedTab.Name)
                {
                    case "personalTabPage":
                        {
                            // Personal page
                            CustomizePersonalPageControls();
                            break;
                        }

                    case "usersTabPage":
                        {
                            // Users
                            CustomizeUsersControls();
                            CustomizeUserGroupsControls();
                            CustomizeComputersContols();
                            CustomizeAuthSystemsContols();
                            break;
                        }

                    case "presetTabPage":
                        {
                            // Presets
                            CustomizePresetControls();
                            break;
                        }

                    case "educationTabPage":
                        {
                            // Education
                            CustomizeEducationControls();
                            break;
                        }

                    case "notificationTabPage":
                        {
                            // Notification
                            CustomizeNotificationControls();
                            break;
                        }

                    case "licenseTabPage":
                        {
                            // License
                            CustomizeLicenseControls();
                            break;
                        }

                    case "logFilesTabPage":
                        {
                            // Log-files
                            CustomizeLogFilesControls();
                            break;
                        }

                    case "confTabPage":
                        {
                            // Configuration management
                            CustomizeConfigurationManagementControls();
                            break;
                        }

                    case "scheduleTabPage":
                        {
                            // Schedule management
                            CustomizeScheduleControls();
                            break;
                        }
                }
        }

        #endregion

        #region Main menu

        // Supervisor flag
        public bool supervisor;

        /// <summary>
        /// Exit main menu item click
        /// </summary>
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        // Server connector
        private fmConnect _serverConnector;

        /// <summary>
        /// Connect main menu item click
        /// </summary>
        private void connectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            supervisor = false;

            mainPanel.Visible = false;

            // Create connection window
            if (_serverConnector != null)
                _serverConnector.DisconnectFromServer();

            _serverConnector = new fmConnect(3 /*MANAGEMENT TOOL*/, "Management tool", encryptor, logWriter);

            _serverConnector.ShowDialog();

            // Get connection string
            connectionString = _serverConnector.connectionString;
            userPermissions = _serverConnector.userPermissions;
            
            if ((connectionString != "") && (userPermissions != null))
            {
                mainPanel.Visible = true;
                currentUserName = _serverConnector.enteredUserName;

                this.Text = "NovaTend management tool - [ " + currentUserName + " ]";

                SetUserPermissionsFunctions();
                mainTabControl_SelectedIndexChanged(sender, null);

                connectToolStripMenuItem.Enabled = false;
                disconnectToolStripMenuItem.Enabled = true;
            }
            else
            {
                mainPanel.Visible = false;
                disconnectToolStripMenuItem_Click(null, null);
                MessageBox.Show("Database connection not established!!!", "Database connection", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        /// <summary>
        /// Set UI functionallity according user permissions
        /// </summary>
        private void SetUserPermissionsFunctions()
        {
            if (!mainTabControl.TabPages.Contains(personalTabPage))
                mainTabControl.TabPages.Add(personalTabPage);
            
            foreach (int p in userPermissions)
            {
                switch (p)
                {
                    case CMD_GET_DB_ACCESS.DB_ACCESS_SUPERVISOR:
                        {
                            if (!mainTabControl.TabPages.Contains(usersTabPage))
                                mainTabControl.TabPages.Add(usersTabPage);
                            if (!mainTabControl.TabPages.Contains(presetTabPage))
                                mainTabControl.TabPages.Add(presetTabPage);
                            if (!mainTabControl.TabPages.Contains(educationTabPage))
                                mainTabControl.TabPages.Add(educationTabPage);
                            if (!mainTabControl.TabPages.Contains(notificationTabPage))
                                mainTabControl.TabPages.Add(notificationTabPage);
                            if (!mainTabControl.TabPages.Contains(scheduleTabPage))
                                mainTabControl.TabPages.Add(scheduleTabPage);
                            if (!mainTabControl.TabPages.Contains(licenseTabPage))
                                mainTabControl.TabPages.Add(licenseTabPage);
                            if (!mainTabControl.TabPages.Contains(confTabPage))
                                mainTabControl.TabPages.Add(confTabPage);
                            if (!mainTabControl.TabPages.Contains(logFilesTabPage))
                                mainTabControl.TabPages.Add(logFilesTabPage);

                            supervisor = true;

                            string message = String.Format("User {0} has permission of super user", currentUserName);
                            logWriter.WriteToLog(message);

                            break;
                        }

                    case CMD_GET_DB_ACCESS.DB_ACCESS_SYS_ADMIN:
                        {
                            if (!mainTabControl.TabPages.Contains(usersTabPage))
                                mainTabControl.TabPages.Add(usersTabPage);
                            if (!mainTabControl.TabPages.Contains(presetTabPage))
                                mainTabControl.TabPages.Add(presetTabPage);
                            if (!mainTabControl.TabPages.Contains(educationTabPage))
                                mainTabControl.TabPages.Add(educationTabPage);
                            if (!mainTabControl.TabPages.Contains(notificationTabPage))
                                mainTabControl.TabPages.Add(notificationTabPage);
                            if (!mainTabControl.TabPages.Contains(scheduleTabPage))
                                mainTabControl.TabPages.Add(scheduleTabPage);
                            if (!mainTabControl.TabPages.Contains(licenseTabPage))
                                mainTabControl.TabPages.Add(licenseTabPage);
                            if (!mainTabControl.TabPages.Contains(confTabPage))
                                mainTabControl.TabPages.Add(confTabPage);
                            if (!mainTabControl.TabPages.Contains(logFilesTabPage))
                                mainTabControl.TabPages.Add(logFilesTabPage);

                            string message = String.Format("User {0} has permission of system administrator", currentUserName);
                            logWriter.WriteToLog(message);

                            break;
                        }

                    case CMD_GET_DB_ACCESS.DB_ACCESS_SCREEN_DESIGNER:
                        {
                            if (!mainTabControl.TabPages.Contains(presetTabPage))
                                mainTabControl.TabPages.Add(presetTabPage);

                            string message = String.Format("User {0} has permission of screen designer", currentUserName);
                            logWriter.WriteToLog(message);

                            break;
                        }

                    case CMD_GET_DB_ACCESS.DB_ACCESS_EDU_MANAGER:
                        {
                            if (!mainTabControl.TabPages.Contains(educationTabPage)) 
                                mainTabControl.TabPages.Add(educationTabPage);

                            string message = String.Format("User {0} has permission of education manager", currentUserName);
                            logWriter.WriteToLog(message);

                            break;
                        }

                    case CMD_GET_DB_ACCESS.DB_ACCESS_NOTICE_MANAGER:
                        {
                            if (!mainTabControl.TabPages.Contains(notificationTabPage)) 
                                mainTabControl.TabPages.Add(notificationTabPage);

                            string message = String.Format("User {0} has permission of notification manager", currentUserName);
                            logWriter.WriteToLog(message);

                            break;
                        }

                    case CMD_GET_DB_ACCESS.DB_ACCESS_LICENSE_MANAGER:
                        {
                            if (!mainTabControl.TabPages.Contains(licenseTabPage)) 
                                mainTabControl.TabPages.Add(licenseTabPage);

                            string message = String.Format("User {0} has permission of license manager", currentUserName);
                            logWriter.WriteToLog(message);

                            break;
                        }

                    case CMD_GET_DB_ACCESS.SCHEDULE_MANAGER:
                        {
                            if (!mainTabControl.TabPages.Contains(scheduleTabPage))
                                mainTabControl.TabPages.Add(scheduleTabPage);

                            string message = String.Format("User {0} has permission of schedule manager", currentUserName);
                            logWriter.WriteToLog(message);

                            break;
                        }

                }
            }
        }

        /// <summary>
        /// Disconnect main menu item click
        /// </summary>
        private void disconnectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            supervisor = false;
            mainPanel.Visible = false;
            mainTabControl.TabPages.Clear();
            this.Text = "NovaTend management tool - [ DISCONNECTED ]";
            currentUserName = "";
            connectToolStripMenuItem.Enabled = true;
            disconnectToolStripMenuItem.Enabled = false;

            if (_serverConnector != null)
                _serverConnector.DisconnectFromServer();

            logWriter.WriteToLog("NovaTend management tool connection --> Current user disconnected from NovaTend management tool");
        }

        /// <summary>
        /// About main menu item click
        /// </summary>
        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fmAbout aboutBox = new fmAbout();
            aboutBox.ShowDialog();
            aboutBox.Dispose();
        }





        #endregion

        
    }
}