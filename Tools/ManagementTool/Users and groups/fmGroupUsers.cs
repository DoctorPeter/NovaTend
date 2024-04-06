/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmGroupUsers.cs
///   Description :  Editiong of members of some group
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

namespace ManagementTool
{
    /// <summary>
    /// Editting of user groups list
    /// </summary>
    public partial class fmGroupUsers : Form
    {
        #region Variables

        // Save results flag
        public bool saveResults;

        // Final user groups list
        public List<string> groupUsersToRemove;
        public List<string> groupUsersToAdd;

        private List<string> _beginGroupUsers;
        private List<string> _endGroupUsers;

        #endregion

        #region Construction

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="groupUsers">users of current group</param>
        /// <param name="users">general list of users</param>
        /// <param name="authSystemName">authentication system name</param>
        /// <param name="groupName">group name</param>
        public fmGroupUsers(List<string> groupUsers, List<string> users, string authSystemName, string groupName)
        {
            InitializeComponent();

            // Get authentication system name
            lblAuthSystem.Text = "Authentication system: " + authSystemName;

            // Get group name
            lblServiceGroupName.Text = "The group \"" + groupName + "\" has the following list of users: ";

            _beginGroupUsers = new List<string>();

            // Fill group users list View
            if (groupUsers != null)
            {
                for (int i = 0; i < groupUsers.Count; i++)
                {
                    ListViewItem listViewItem = new ListViewItem(groupUsers[i]);
                    listViewItem.ImageIndex = 0;
                    groupUsersListView.Items.Add(listViewItem);

                    _beginGroupUsers.Add(groupUsers[i]);
                }
            }

            // Fill users list view
            if (users != null)
            {
                for (int i = 0; i < users.Count; i++)
                {
                    ListViewItem listViewItem = new ListViewItem(users[i]);
                    listViewItem.ImageIndex = 0;
                    usersListView.Items.Add(listViewItem);
                }
            }

            GetItemsCount();

            saveResults = false;

            _endGroupUsers = null;
            groupUsersToAdd = null;
            groupUsersToRemove = null;
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Button "Cancel" click event handler
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            saveResults = false;

            Close();
        }

        /// <summary>
        /// Button "OK" click event handler
        /// </summary>
        private void btnOK_Click(object sender, EventArgs e)
        {
            _endGroupUsers = new List<string>();

            for (int i = 0; i < groupUsersListView.Items.Count; i++)
            {
                _endGroupUsers.Add(groupUsersListView.Items[i].Text);
            }

            groupUsersToRemove = new List<string>(_beginGroupUsers.Except(_endGroupUsers));
            groupUsersToAdd = new List<string>(_endGroupUsers.Except(_beginGroupUsers));

            saveResults = true;

            Close();
        }

        /// <summary>
        /// Button "Left" click event handler
        /// </summary>
        private void moveLeftButton_Click(object sender, EventArgs e)
        {
            MoveItems(usersListView, groupUsersListView);
            GetItemsCount();
        }

        /// <summary>
        /// Button "Right" click event handler
        /// </summary>
        private void moveRightButton_Click(object sender, EventArgs e)
        {
            MoveItems(groupUsersListView, usersListView);
            GetItemsCount();
        }

        #endregion

        #region Helper

        /// <summary>
        /// Move selected items from one list view to another
        /// </summary>
        /// <param name="listViewSource">source list view</param>
        /// <param name="listViewDest">destinate list view</param>
        private void MoveItems(ListView listViewSource, ListView listViewDest)
        {
            if ((listViewSource.SelectedItems != null) && (listViewSource.SelectedItems.Count > 0))
            {
                foreach (ListViewItem listViewItem in listViewSource.SelectedItems)
                {
                    listViewSource.Items.Remove(listViewItem);
                    listViewDest.Items.Add(listViewItem);
                }
            }
        }

        /// <summary>
        /// Get count of items in both lists
        /// </summary>
        private void GetItemsCount()
        {
            lblGroupUsersCount.Text = "Count: " + groupUsersListView.Items.Count.ToString();
            lblUsersCount.Text = "Count: " + usersListView.Items.Count.ToString();
        }

        #endregion

    }
}
