/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmUserAccountsArchive.cs
///   Description :  user accounts archive module
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
using Synchronization;
using WriteLog;

namespace ManagementTool
{

    /// <summary>
    /// User acocunts archive form
    /// </summary>
    public partial class fmUserAccountsArchive : Form
    {
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

        /// <summary>
        /// Encrypt string
        /// </summary>
        /// <param name="str">Input string</param>
        /// <returns>Encrypted data. Array of bytes</returns>
        public byte[] EncryptString(string str)
        {
            byte[] decData = System.Text.Encoding.ASCII.GetBytes(str);
            byte[] encData = null;
            encryptor.EncryptAndPackSecurityData(decData, ref encData);
            return encData;
        }

        /// <summary>
        /// Decrypt string
        /// </summary>
        /// <param name="bytes">Input array of bytes</param>
        /// <returns>Decrypted string</returns>
        public string DecryptString(byte[] bytes)
        {
            byte[] encData = bytes;
            byte[] decData = null;
            encryptor.UnPackAndDecryptSecurityData(encData, ref decData);
            return System.Text.Encoding.ASCII.GetString(decData);
        }

        #endregion

        #region Database

        // Database manager instance
        private DataBaseManager dbManager;

        #endregion

        #region Constructor

        // Supervisor flag
        private bool supervisor;

        /// <summary>
        /// Form constructor
        /// </summary>
        /// <param name="dbManager">Database manager instance</param>
        public fmUserAccountsArchive(DataBaseManager dbManager, bool supervisor, LogWriter logWriter)
        {
            InitializeComponent();

            this.dbManager = dbManager;

            this.supervisor = supervisor;

            this.logWriter = logWriter;

            CustomizeControls();
        }

        /// <summary>
        /// Customize form controls
        /// </summary>
        private void CustomizeControls()
        {
            // Binding navigator
            usersBindingNavigator.BindingSource = dbManager.userAccountsArchiveUsersBindingSource;

            // Users data grid view
            userNamesDataGridView.AutoGenerateColumns = false;
            userNamesDataGridView.DataSource = dbManager.userAccountsArchiveUsersBindingSource;
            userNameColumn.DataPropertyName = "Name";

            // User accounts values
            userAccountsDataGridView.AutoGenerateColumns = false;
            userAccountsDataGridView.DataSource = dbManager.fkUserAccountsArchiveUsersBindingSource;
            authSystemTypeNameColumn.DataSource = dbManager.userAccontsArchiveAuthSystemsBindingSource;
            authSystemTypeNameColumn.DataPropertyName = "AuthSystemID";
            authSystemTypeNameColumn.DisplayMember = "Name";
            authSystemTypeNameColumn.ValueMember = "ID";
            accountUserNameColumn.DataPropertyName = "UserName";
            accountPasswordColumn.DataPropertyName = "Password";
            lastSignInDateColumn.DataPropertyName = "LastSignInDate";
            passThruColumn.DataPropertyName = "PassThru";

            dbManager.userAccountsArchiveTableAdapter.Fill(dbManager.dataSet.UserAccountsArchive);
        }
                
        #endregion

        #region Events

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
                e.Value = DecryptString((byte[])dataGridView["userNameColumn", e.RowIndex].Value);
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
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) && (dataGridView.Columns[e.ColumnIndex].Name == "userNameColumn"))
            {
                // Encrypt data
                dataGridView[e.ColumnIndex, e.RowIndex].Value = EncryptString(e.Value.ToString());
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
                e.Value = DecryptString((byte[])dataGridView["accountUserNameColumn", e.RowIndex].Value);
                e.FormattingApplied = true;
            }

            if ((e.ColumnIndex >= 0) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "accountPasswordColumn") &&
                (e.RowIndex >= 0) &&
                (dataGridView["accountPasswordColumn", e.RowIndex].Value is byte[]) &&
                (!(dataGridView["accountPasswordColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Decrypt data
                string pwdStr = DecryptString((byte[])dataGridView["accountPasswordColumn", e.RowIndex].Value);
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
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) && (dataGridView.Columns[e.ColumnIndex].Name == "accountUserNameColumn")/* || (dataGridView.Columns[e.ColumnIndex].Name == "accountPasswordColumn")*/)
            {
                // Encrypt data
                dataGridView[e.ColumnIndex, e.RowIndex].Value = EncryptString(e.Value.ToString());
                dataGridView.RefreshEdit();
                e.ParsingApplied = true;
            }
        }

        /// <summary>
        /// Grid view data error event handler
        /// </summary>
        private void userAccountsDataGridView_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            DataGridView dataGridView = (DataGridView)sender;
            string errorText = dataGridView[e.ColumnIndex, e.RowIndex].ErrorText;
        }

        
        private void userNamesDataGridView_Enter(object sender, EventArgs e)
        {
            usersBindingNavigator.BindingSource = userNamesDataGridView.DataSource as BindingSource;
            bindingNavigatorDeleteItem.Enabled = false;
        }

        /// <summary>
        /// User accounts data grid view enter event handler
        /// </summary>
        private void userAccountsDataGridView_Enter(object sender, EventArgs e)
        {
            usersBindingNavigator.BindingSource = userAccountsDataGridView.DataSource as BindingSource;
            bindingNavigatorDeleteItem.Enabled = true;
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Save button click
        /// </summary>
        private void usersBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.userAccountsArchiveUsersBindingSource.EndEdit();
            dbManager.fkUserAccountsArchiveUsersBindingSource.EndEdit();

            dbManager.UpdateUserAccountsArchive();
        }

        /// <summary>
        /// Restore button click
        /// </summary>
        private void usersBindingNavigatorRestoreItem_Click(object sender, EventArgs e)
        {
            DataRow uaDataRow = dbManager.dataSet.UserAccountsArchive.Rows[dbManager.fkUserAccountsArchiveUsersBindingSource.Position];

            string message = String.Format("User account archive --> Trying to restore account of user ID '{0}'", DecryptString(uaDataRow["UserName", DataRowVersion.Original] as byte[]));
            logWriter.WriteToLog(message);

            if (!dbManager.GetUserAccountFromArchive(uaDataRow))
            {
                MessageBox.Show("Can not to restore accounts from archive!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                logWriter.WriteToLog("User account archive --> Can not to restore accounts from archive!");
            }
            else
            {
                // Sync inserted accounts
                if (uaDataRow != null)
                {
                    UserAccountsSynchronizer userAccountsSynchronizer = new UserAccountsSynchronizer(dbManager);
                    userAccountsSynchronizer.SyncADAccountOnInsert(uaDataRow);
                }

                dbManager.UpdateUserAccountsArchive();

                logWriter.WriteToLog("User account archive --> User account successfully restored!");

                usersBindingNavigatorRefreshItem_Click(null, null);
            }
        }

        /// <summary>
        /// Refresh button click
        /// </summary>
        private void usersBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.userAccountsArchiveTableAdapter.Fill(dbManager.dataSet.UserAccountsArchive);
            dbManager.userAccountsTableAdapter.Fill(dbManager.dataSet.UserAccounts);
        }

        #endregion
    }
}
