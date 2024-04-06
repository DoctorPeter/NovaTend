/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmPresetHookup.cs
///   Description :  preset hookup settings
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

using DataModule;
using Encryption;

namespace ManagementTool
{
    public partial class fmPresetHookup : Form
    {

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

        #region Construction

        /// <summary>
        /// Create filter string for users.
        /// Remove supervisors
        /// </summary>
        /// <returns>Filter string</returns>
        private string CreateSupevisorsFilterString(string colName)
        {
            string filterString = "";
            DataRow[] userPermissionsRows = dbManager.dataSet.UserPermissions.Select("PermissionID = 0");
            if ((userPermissionsRows != null) && (userPermissionsRows.Length > 0))
            {
                foreach (DataRow row in userPermissionsRows)
                {
                    int userID = (int)row["userID", DataRowVersion.Original];
                    filterString = filterString + "(" + colName + " <> " + userID.ToString() + ") AND";
                }

                if (filterString.Length > 0)
                    filterString = filterString.Substring(0, filterString.Length - 4);
            }

            return filterString;
        }

        // Decrypted user names list
        Dictionary<int, string> decUsers;

        // Decrypted user group names list
        Dictionary<int, string> decUserGroups;

        // Supervisor flag
        bool supervisor;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="dbManager">DB manager instance</param>
        /// <param name="encryptor">Encryptor instance</param>
        /// <param name="supervisor">Supervisor flag</param>
        public fmPresetHookup(DataBaseManager dbManager, Encryptor encryptor, bool supervisor)
        {
            this.dbManager = dbManager;
            this.encryptor = encryptor;
            this.supervisor = supervisor;

            InitializeComponent();
        }

        /// <summary>
        /// Form load event handler
        /// </summary>
        private void fmPresetHookup_Load(object sender, EventArgs e)
        {
            // Set preset binding navigator
            presetBindingNavigator.BindingSource = dbManager.presetHookupPresetsBindingSource;

            // Customize preset names data grid view
            presetDataGridView.AutoGenerateColumns = false;
            presetDataGridView.DataSource = dbManager.presetHookupPresetsBindingSource;
            presetNameColumn.DataPropertyName = "Name";
                        
            // Set preset hookup binding navigator binding source
            presetHookupBindingNavigator.BindingSource = dbManager.fkPresetHookupPresetBindingSource;

            // Customize preset hookup grid view
            presetHookupDataGridView.AutoGenerateColumns = false;
            presetHookupDataGridView.DataSource = dbManager.fkPresetHookupPresetBindingSource;
            userIDColumn.DataPropertyName = "UserID";
            userGroupIDColumn.DataPropertyName = "GroupID";

            computerNameColumn.DataSource = dbManager.presetHookupComputersBindingSource;
            computerNameColumn.DataPropertyName = "ComputerID";
            computerNameColumn.DisplayMember = "Name";
            computerNameColumn.ValueMember = "ID";

            osTypeColumn.DataSource = dbManager.presetHookupOSTypesBindingSource;
            osTypeColumn.DataPropertyName = "OSTypeID";
            osTypeColumn.DisplayMember = "Name";
            osTypeColumn.ValueMember = "ID";

            // Check supervisor
            if (!supervisor)
            {
                dbManager.fkPresetHookupPresetBindingSource.Filter += "(UserID is NULL) OR " + CreateSupevisorsFilterString("UserID");
                dbManager.presetHookupUsersBindingSource.Filter = CreateSupevisorsFilterString("ID");
            }

            // Decrypt user names
            decUsers = new Dictionary<int, string>();

            if (userNameColumn.Items.Count <= 0)
            {
                dbManager.presetHookupUsersBindingSource.MoveFirst();
                for (int i = 0; i < dbManager.presetHookupUsersBindingSource.Count; i++)
                {
                    int key = (int)(dbManager.presetHookupUsersBindingSource.Current as DataRowView).Row["ID"];
                    string userName = encryptor.DecryptString((byte[])(dbManager.presetHookupUsersBindingSource.Current as DataRowView).Row["UserName"]);
                    userNameColumn.Items.Add(userName);
                    decUsers.Add(key, userName);
                    dbManager.presetHookupUsersBindingSource.MoveNext();
                }

                dbManager.presetHookupUsersBindingSource.MoveFirst();
            }

            // Decrypt user group names
            decUserGroups = new Dictionary<int, string>();

            if (groupNameColumn.Items.Count <= 0)
            {
                dbManager.presetHookupUserGroupsBindingSource.MoveFirst();
                for (int i = 0; i < dbManager.presetHookupUserGroupsBindingSource.Count; i++)
                {
                    int key = (int)(dbManager.presetHookupUserGroupsBindingSource.Current as DataRowView).Row["ID"];
                    string userGroupName = encryptor.DecryptString((byte[])(dbManager.presetHookupUserGroupsBindingSource.Current as DataRowView).Row["Name"]);
                    groupNameColumn.Items.Add(userGroupName);
                    decUserGroups.Add(key, userGroupName);
                    dbManager.presetHookupUserGroupsBindingSource.MoveNext();
                }

                dbManager.presetHookupUserGroupsBindingSource.MoveFirst();
            }
        }


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
                return dictionary.FirstOrDefault(x => x.Value.Contains(value)).Key;
            else
                return -1;
        }
        
        #endregion

        #region Buttons

        /// <summary>
        /// Refresh preset names button click
        /// </summary>
        private void presetBindingNavigatorRefreshIntem_Click(object sender, EventArgs e)
        {
            dbManager.presetTableAdapter.Fill(dbManager.dataSet.Preset);
        }

        /// <summary>
        /// Refresh preset hookup button click
        /// </summary>
        private void presetHookupBindingNavigatorRefreshItem_Click(object sender, EventArgs e)
        {
            dbManager.presetHookupTableAdapter.Fill(dbManager.dataSet.PresetHookup);
        }

        /// <summary>
        /// Save preset hookup button click
        /// </summary>
        private void presetHookupBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            if (!this.Validate()) return;
            dbManager.fkPresetHookupPresetBindingSource.EndEdit();
            dbManager.UpdatePresetHookup();
        }

        #endregion

        #region Events

        /// <summary>
        /// Preset hookup cell value changed event handler
        /// </summary>
        private void presetHookupDataGridView_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0))
            {
                if ((dataGridView.Columns[e.ColumnIndex].Name == "userNameColumn") && (userNameColumn.Items.Count > 0))
                {
                    // Set decrypted rule name
                    string userName = "";
                    int userID = -1;

                    if (!(dataGridView.Rows[e.RowIndex].Cells["userNameColumn"].Value is DBNull))
                    {
                        userName = dataGridView.Rows[e.RowIndex].Cells["userNameColumn"].Value as string;
                        userID = GetDictionaryIDByValue(userName, decUsers);

                        if (userID != -1)
                            dataGridView.Rows[e.RowIndex].Cells["userIDColumn"].Value = userID;
                        else
                            dataGridView.Rows[e.RowIndex].Cells["userIDColumn"].Value = DBNull.Value;
                    }
                    else
                        dataGridView.Rows[e.RowIndex].Cells["userIDColumn"].Value = DBNull.Value;
                }
                else
                    if ((dataGridView.Columns[e.ColumnIndex].Name == "groupNameColumn") && (groupNameColumn.Items.Count > 0))
                    {
                        // Set decrypted group name
                        string groupName = "";
                        int groupID = -1;

                        if (!(dataGridView.Rows[e.RowIndex].Cells["groupNameColumn"].Value is DBNull))
                        {
                            groupName = dataGridView.Rows[e.RowIndex].Cells["groupNameColumn"].Value as string;
                            groupID = GetDictionaryIDByValue(groupName, decUserGroups);

                            if (groupID != -1)
                                dataGridView.Rows[e.RowIndex].Cells["userGroupIDColumn"].Value = groupID;
                            else
                                dataGridView.Rows[e.RowIndex].Cells["userGroupIDColumn"].Value = DBNull.Value;
                        }
                        else
                            dataGridView.Rows[e.RowIndex].Cells["userGroupIDColumn"].Value = DBNull.Value;
                    }
                    else
                        if ((dataGridView.Columns[e.ColumnIndex].Name != "userGroupIDColumn") &&
                            (dataGridView.Columns[e.ColumnIndex].Name != "userIDColumn") &&
                            (((dataGridView[e.ColumnIndex, e.RowIndex].Value as string) == String.Empty) || 
                             (dataGridView[e.ColumnIndex, e.RowIndex].Value is DBNull)))
                                dataGridView[e.ColumnIndex, e.RowIndex].Value = System.DBNull.Value;
            }
        }

        /// <summary>
        /// Preset hookup cell formating event handler
        /// </summary>
        private void presetHookupDataGridView_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            // Get sender
            DataGridView dataGridView = (DataGridView)sender;

            // Check column
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) && (e.RowIndex < dbManager.fkPresetHookupPresetBindingSource.Count) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "userNameColumn") &&
                (userNameColumn.Items.Count > 0) &&
                (dataGridView["userIDColumn", e.RowIndex].Value != null) &&
                (!(dataGridView["userIDColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Set decrypted user name
                e.Value = GetDictionaryValueByID((int)dataGridView.Rows[e.RowIndex].Cells["userIDColumn"].Value, decUsers);
                e.FormattingApplied = true;
            }

            // Check column
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0) && (e.RowIndex < dbManager.fkPresetHookupPresetBindingSource.Count) &&
                (dataGridView.Columns[e.ColumnIndex].Name == "groupNameColumn") &&
                (groupNameColumn.Items.Count > 0) &&
                (dataGridView["userGroupIDColumn", e.RowIndex].Value != null) &&
                (!(dataGridView["userGroupIDColumn", e.RowIndex].Value is System.DBNull)))
            {
                // Set decrypted user group name
                e.Value = GetDictionaryValueByID((int)dataGridView.Rows[e.RowIndex].Cells["userGroupIDColumn"].Value, decUserGroups);
                e.FormattingApplied = true;
            }
        }

        /// <summary>
        /// Data grid view data error event handler
        /// </summary>
        private void presetDataGridView_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            DataGridView dataGridView = (DataGridView)sender;
            if ((e.ColumnIndex >= 0) && (e.RowIndex >= 0))
            {
                string errorText = dataGridView[e.ColumnIndex, e.RowIndex].ErrorText;
            }
        }

        /// <summary>
        /// Preset hookup data grid view editing control showing event handler
        /// </summary>
        private void presetHookupDataGridView_EditingControlShowing(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            ComboBox c = e.Control as ComboBox;
            if (c != null)
            {
                c.DropDownStyle = ComboBoxStyle.DropDown;
            }
        }

        /// <summary>
        /// Preset hookup data grid view cell validating event handler
        /// </summary>
        private void presetHookupDataGridView_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
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

        #endregion

    }
}
