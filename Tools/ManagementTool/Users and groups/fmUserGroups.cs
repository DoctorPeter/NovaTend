/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmUserGroups.cs
///   Description :  user groups editing
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
    public partial class fmUserGroups : Form
    {
        #region Variables

        // Save results flag
        public bool saveResults;

        // Final user groups list
        public List<string> userGroupsToRemove;
        public List<string> userGroupsToAdd;

        private List<string> _beginUserGroups;
        private List<string> _endUserGroups;

        #endregion

        #region Construction

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="userGroups"> list of user groups</param>
        /// <param name="groups">general list of groups</param>
        /// <param name="authSystemName">name of authentication system</param>
        /// <param name="userName">user name</param>
        public fmUserGroups(List<string> userGroups, List<string> groups, string authSystemName, string userName)
        {
            InitializeComponent();

            // Get authentication system name
            lblAuthSystem.Text = "Authentication system: " + authSystemName;

            // Get user name
            lblServiceUserName.Text = "The user \"" + userName + "\" belongs to the following groups: ";

            _beginUserGroups = new List<string>();

            // Fill user groups list View
            if (userGroups != null)
            {
                for (int i = 0; i < userGroups.Count; i++)
                {
                    ListViewItem listViewItem = new ListViewItem(userGroups[i]);
                    listViewItem.ImageIndex = 0;
                    userGroupsListView.Items.Add(listViewItem);
                    
                    _beginUserGroups.Add(userGroups[i]);
                }
            }

            // Fill groups list view
            if (groups != null)
            {
                for (int i = 0; i < groups.Count; i++)
                {
                    ListViewItem listViewItem = new ListViewItem(groups[i]);
                    listViewItem.ImageIndex = 0;
                    groupsListView.Items.Add(listViewItem);
                }
            }

            GetItemsCount();

            saveResults = false;
            
            _endUserGroups = null;
            userGroupsToAdd = null;
            userGroupsToRemove = null;
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
            _endUserGroups = new List<string>();

            for(int i = 0; i < userGroupsListView.Items.Count; i++)
            {
                _endUserGroups.Add(userGroupsListView.Items[i].Text);
            }

            userGroupsToRemove = new List<string>(_beginUserGroups.Except(_endUserGroups));
            userGroupsToAdd = new List<string>(_endUserGroups.Except(_beginUserGroups));

            saveResults = true;

            Close();
        }

        /// <summary>
        /// Button "Left" click event handler
        /// </summary>
        private void moveLeftButton_Click(object sender, EventArgs e)
        {
            MoveItems(groupsListView, userGroupsListView);
            GetItemsCount();
        }

        /// <summary>
        /// Button "Right" click event handler
        /// </summary>
        private void moveRightButton_Click(object sender, EventArgs e)
        {
            MoveItems(userGroupsListView, groupsListView);
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
            lblUserGroupsCount.Text = "Count: " + userGroupsListView.Items.Count.ToString();
            lblGroupsCount.Text = "Count: " + groupsListView.Items.Count.ToString();
        }

        #endregion

    }
}
