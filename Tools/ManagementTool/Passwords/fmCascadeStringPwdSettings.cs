/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmCascadeStringPwdSettings.cs
///   Description :  Cascade string password settings window module
/// </summary>

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using DataModule;
using Encryption;

namespace ManagementTool
{
    /// <summary>
    /// Cascade string password settings window class
    /// </summary>
    public partial class fmCascadeStringPwdSettings : Form
    {
        #region DB manager

        // Database manager instance
        private DataBaseManager _dbManager;

        // Database manager property
        public DataBaseManager dbManager
        {
            get
            {
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
                return _encryptor;
            }

            set
            {
                _encryptor = value;
            }
        }

        #endregion

        #region Constants

        // Cascade string password rule range
        public const int CASCADE_STRING_PWD_MIN = 1;
        public const int CASCADE_STRING_PWD_MAX = 10;

        #endregion

        #region Constructing

        /// <summary>
        /// Constructor
        /// </summary>
        public fmCascadeStringPwdSettings(DataBaseManager dbManager, Encryptor encryptor, bool personalPage)
        {
            this.dbManager = dbManager;
            this.encryptor = encryptor;

            _personalPage = personalPage;
            _commited = false;

            InitializeComponent();

            
        }

        /// <summary>
        /// Load form event handler
        /// </summary>
        private void fmCascadeStringPwdSettings_Load(object sender, EventArgs e)
        {
            GetRuleNames();
            CustomizeControls();
        }

        #endregion

        #region Customize

        // Personal page flag
        private bool _personalPage;


        // User token buffers
        private int _begUserToken, _begUserTmpToken;


        // rules names list
        private Dictionary<int, string> ruleNames;

        // Commit flag
        private bool _commited;

        public bool Commited
        {
            get
            {
                return _commited;
            }
        }

        // Pwd reseted flag
        private short _pwdReseted;

        /// <summary>
        /// Get list of rules names
        /// </summary>
        private void GetRuleNames()
        {
            ruleNames = new Dictionary<int, string>();

            // Decrypt password construction rules names
            if (dbManager.passwordConstructionRulesBindingSource.Count > 0)
            {
                for (int i = CASCADE_STRING_PWD_MIN; i <= CASCADE_STRING_PWD_MAX; i++)
                {
                    string filterExpr = "ID = " + i.ToString();
                    DataRow[] selRows = dbManager.dataSet.PasswordConstructionRules.Select(filterExpr);
                    if ((selRows != null) && (selRows.Length > 0))
                    {
                        byte[] encName = selRows[0]["Name", DataRowVersion.Original] as byte[];
                        string decName = encryptor.DecryptString(encName);

                        ruleNames.Add(i, decName);
                    }
                }
            }
        }

        /// <summary>
        /// Get rule name by ID
        /// </summary>
        /// <param name="ID">rule ID</param>
        /// <returns>rule name</returns>
        private string GetRuleNameByID(int ID)
        {
            return ruleNames.ContainsKey(ID) ? ruleNames[ID] : String.Empty;
        }

        /// <summary>
        /// Get rule ID by name
        /// </summary>
        /// <param name="name">rule name</param>
        /// <returns>rule ID</returns>
        private int GetRuleIDByName(string name)
        {
            return ruleNames.FirstOrDefault(x => x.Value.Contains(name)).Key;
        }

        /// <summary>
        /// Customize temp password controls
        /// </summary>
        private void CustomizeTempPassword()
        {
            if (_personalPage)
            {
                // Temp password data grid view
                dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + CASCADE_STRING_PWD_MIN.ToString() + ") AND (RuleID <= " + CASCADE_STRING_PWD_MAX.ToString() + ")";

                tmpPwdConstructionRulesBindingNavigator.BindingSource = dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource;
                tmpPwdConstructionRulesDataGridView.AutoGenerateColumns = false;
                tmpPwdConstructionRulesDataGridView.DataSource = dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource;
                tmpRuleIDColumn.DataPropertyName = "RuleID";
                tmpRuleOrderColumn.DataPropertyName = "RulesOrder";

                // User token
                tmpUserTokenTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.personalUsersBindingSource, "TmpUserToken", true));
                _begUserTmpToken = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["TmpUserToken"];
            }
            else
            {
                // Temp passwords data grid view
                dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + CASCADE_STRING_PWD_MIN.ToString() + ") AND (RuleID <= " + CASCADE_STRING_PWD_MAX.ToString() + ")";

                tmpPwdConstructionRulesBindingNavigator.BindingSource = dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource;
                tmpPwdConstructionRulesDataGridView.AutoGenerateColumns = false;
                tmpPwdConstructionRulesDataGridView.DataSource = dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource;
                tmpRuleIDColumn.DataPropertyName = "RuleID";
                tmpRuleOrderColumn.DataPropertyName = "RulesOrder";

                // User token
                tmpUserTokenTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.usersBindingSource, "TmpUserToken", true));
                _begUserTmpToken = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["TmpUserToken"];
            }

            // Fill rule names list column
            if (tmpRuleNameColumn.Items.Count <= 0)
            {
                foreach (KeyValuePair<int, string> pair in ruleNames)
                {
                    tmpRuleNameColumn.Items.Add(pair.Value);
                }
            }
        }

        /// <summary>
        /// Customize main password controls
        /// </summary>
        private void CustomizeMainPassword()
        {
            if (_personalPage)
            {
                // Passwords data grid view
                dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + CASCADE_STRING_PWD_MIN.ToString() + ") AND (RuleID <= " + CASCADE_STRING_PWD_MAX.ToString() + ")";

                mainPwdConstructionRulesBindingNavigator.BindingSource = dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource;
                mainPwdConstructionRulesDataGridView.AutoGenerateColumns = false;
                mainPwdConstructionRulesDataGridView.DataSource = dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource;
                mainRuleIDColumn.DataPropertyName = "RuleID";
                mainRuleOrderColumn.DataPropertyName = "RulesOrder";

                // User token
                userTokenTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.personalUsersBindingSource, "UserToken", true));
                _begUserToken = (int)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["UserToken"];
            }
            else
            {
                // Passwords data grid view
                dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Filter = "(RuleID >= " + CASCADE_STRING_PWD_MIN.ToString() + ") AND (RuleID <= " + CASCADE_STRING_PWD_MAX.ToString() + ")"; ;

                mainPwdConstructionRulesBindingNavigator.BindingSource = dbManager.fkUserPasswordConstructionRulesUsersBindingSource;
                mainPwdConstructionRulesDataGridView.AutoGenerateColumns = false;
                mainPwdConstructionRulesDataGridView.DataSource = dbManager.fkUserPasswordConstructionRulesUsersBindingSource;
                mainRuleIDColumn.DataPropertyName = "RuleID";
                mainRuleOrderColumn.DataPropertyName = "RulesOrder";

                // User token
                userTokenTextBox.DataBindings.Add(new System.Windows.Forms.Binding("Text", dbManager.usersBindingSource, "UserToken", true));
                _begUserToken = (int)(dbManager.usersBindingSource.Current as DataRowView).Row["UserToken"];
            }

            // Fill rule names list column
            if (mainRuleNameColumn.Items.Count <= 0)
            {
                foreach (KeyValuePair<int, string> pair in ruleNames)
                {
                    mainRuleNameColumn.Items.Add(pair.Value);
                }
            }
        }

        /// <summary>
        /// Customize controls
        /// </summary>
        private void CustomizeControls()
        {
            // Check password reseted flag
            if (_personalPage)
            {
                _pwdReseted = (short)(dbManager.personalUsersBindingSource.Current as DataRowView).Row["PwdResetted"];
                if (_pwdReseted != 0)
                {
                    tmpPwdConstructionRulesBindingNavigatorSaveItem.Visible = false;
                    tmpPwdConstructionRulesBindingNavigatorAddNewItem.Visible = false;
                    tmpPwdConstructionRulesBindingNavigatorDeleteItem.Visible = false;
                    tmpPwdConstructionRulesDataGridView.AllowUserToAddRows = false;
                    tmpPwdConstructionRulesDataGridView.AllowUserToDeleteRows = false;
                    tmpPwdConstructionRulesDataGridView.ReadOnly = true;
                    tmpUserTokenTextBox.ReadOnly = true;
                }
            }
            else
            {
                _pwdReseted = (short)(dbManager.usersBindingSource.Current as DataRowView).Row["PwdResetted"];
            }

            // Clear tab pages
            passwordSettingsTabControl.TabPages.Clear();
                        
            // Customize main password
            passwordSettingsTabControl.TabPages.Add(mainPasswordTabPage);
            CustomizeMainPassword();

            // Customize temp password if needed
            if (_pwdReseted != 0)
            {
                passwordSettingsTabControl.TabPages.Add(tmpPasswordTabPage);
                CustomizeTempPassword();
            }
        }

        #endregion

        #region Events

        /// <summary>
        /// Temp password data grid view cell formating event handler
        /// </summary>
        private void tmpPwdConstructionRulesDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;
            
            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "tmpRuleNameColumn") &&
                (((_personalPage) && (e.RowIndex >= 0) &&
                  (e.RowIndex < dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.Count)) ||
                 ((!_personalPage) && (e.RowIndex >= 0) &&
                  (e.RowIndex < dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.Count))) &&
                 (!(dataGridView.Rows[e.RowIndex].Cells["tmpRuleIDColumn"].Value is System.DBNull)) &&
                 (tmpRuleNameColumn.Items.Count > 0) &&
                 (ruleNames != null) && (ruleNames.Count > 0))
            {
                // Set decrypted rule name
                e.Value = GetRuleNameByID((int)dataGridView.Rows[e.RowIndex].Cells["tmpRuleIDColumn"].Value);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Temp password data grid view cell value changed event handler
        /// </summary>
        private void tmpPwdConstructionRulesDataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "tmpRuleNameColumn") &&
                (tmpRuleNameColumn.Items.Count > 0))
            {
                int ruleID = GetRuleIDByName((string)dataGridView.Rows[e.RowIndex].Cells["tmpRuleNameColumn"].Value);
                if (ruleID != 0) dataGridView.Rows[e.RowIndex].Cells["tmpRuleIDColumn"].Value = ruleID;
            }
        }

        /// <summary>
        /// Main password data grid view cell formating event handler
        /// </summary>
        private void mainPwdConstructionRulesDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "mainRuleNameColumn") &&
                (((_personalPage) && (e.RowIndex >= 0) &&
                  (e.RowIndex < dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.Count)) ||
                 ((!_personalPage) && (e.RowIndex >= 0) &&
                  (e.RowIndex < dbManager.fkUserPasswordConstructionRulesUsersBindingSource.Count))) &&
                 (!(dataGridView.Rows[e.RowIndex].Cells["mainRuleIDColumn"].Value is System.DBNull)) &&
                 (mainRuleNameColumn.Items.Count > 0) &&
                 (ruleNames != null) && (ruleNames.Count > 0))
            {
                // Set decrypted rule name
                e.Value = GetRuleNameByID((int)dataGridView.Rows[e.RowIndex].Cells["mainRuleIDColumn"].Value);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Temp password data grid view cell value changed event handler
        /// </summary>
        private void mainPwdConstructionRulesDataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((dataGridView.Columns[e.ColumnIndex].Name == "mainRuleNameColumn") &&
                (mainRuleNameColumn.Items.Count > 0))
            {
                int ruleID = GetRuleIDByName((string)dataGridView.Rows[e.RowIndex].Cells["mainRuleNameColumn"].Value);
                if (ruleID != 0) dataGridView.Rows[e.RowIndex].Cells["mainRuleIDColumn"].Value = ruleID;
            }
        }

        /// <summary>
        /// Data error event handler
        /// </summary>
        private void tmpPwdConstructionRulesDataGridView_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            DataGridView dataGridView = (DataGridView)sender;
            string errorText = dataGridView[e.ColumnIndex, e.RowIndex].ErrorText;
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Save temp password button click
        /// </summary>
        private void tmpPwdConstructionRulesBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (_personalPage)
            {
                dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.EndEdit();
                dbManager.personalUsersBindingSource.EndEdit();
            }
            else
            {
                dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.EndEdit();
                dbManager.usersBindingSource.EndEdit();
            }

            dbManager.UpdateAll();
        }

        /// <summary>
        /// Save main password button click
        /// </summary>
        private void mainPwdConstructionRulesBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (_personalPage)
            {
                dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.EndEdit();
                dbManager.personalUsersBindingSource.EndEdit();
            }
            else
            {
                dbManager.fkUserPasswordConstructionRulesUsersBindingSource.EndEdit();
                dbManager.usersBindingSource.EndEdit();
            }

            dbManager.UpdateAll();
        }

        /// <summary>
        /// Refresh temp password button click
        /// </summary>
        private void tmpPwdConstructionRulesBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.tmpUserPasswordConstructionRulesTableAdapter.Fill(dbManager.dataSet.TmpUserPasswordConstructionRules);
        }

        /// <summary>
        /// Refresh main password button click
        /// </summary>
        private void mainPwdConstructionRulesBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userPasswordConstructionRulesTableAdapter.Fill(dbManager.dataSet.UserPasswordConstructionRules);
        }

        /// <summary>
        /// Button OK click
        /// </summary>
        private void btnOK_Click(object sender, EventArgs e)
        {
            tmpPwdConstructionRulesBindingNavigatorSaveItem_Click(null, null);
            mainPwdConstructionRulesBindingNavigatorSaveItem_Click(null, null);
            _commited = true;
            Close();
        }

        /// <summary>
        /// Button Cancel click
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            if (_personalPage)
            {
                dbManager.fkPersonalTmpUserPasswordConstructionRulesUsersBindingSource.CancelEdit();
                dbManager.fkPersonalUserPasswordConstructionRulesUsersBindingSource.CancelEdit();
                (dbManager.personalUsersBindingSource.Current as DataRowView).Row["UserToken"] = _begUserToken;
                if (_pwdReseted != 0) (dbManager.personalUsersBindingSource.Current as DataRowView).Row["TmpUserToken"] = _begUserTmpToken;
            }
            else
            {
                dbManager.fkTmpUserPasswordConstructionRulesUsersBindingSource.CancelEdit();
                dbManager.fkUserPasswordConstructionRulesUsersBindingSource.CancelEdit();
                (dbManager.usersBindingSource.Current as DataRowView).Row["UserToken"] = _begUserToken;
                if (_pwdReseted != 0) (dbManager.usersBindingSource.Current as DataRowView).Row["TmpUserToken"] = _begUserTmpToken;
            }

            _commited = false;

            Close();
        }

        #endregion
    }
}
