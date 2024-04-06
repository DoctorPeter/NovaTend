/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmAddRevGroup.cs
///   Description :  user group linking module
/// </summary>

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
    /// User group linking window
    /// </summary>
    public partial class fmAddRevGroup : Form
    {
        #region Result

        // Selected group ID
        public int groupID;

        // Selected group name
        public string groupName;

        // Group ID list
        private List<int> groupIDs;

        #endregion

        #region Constructor

        /// <summary>
        /// Constructor
        /// </summary>
        public fmAddRevGroup(List<string> groupNames, List<int> groupIDs, string authSystemName, string groupName)
        {
            InitializeComponent();

            lblAuthSystem.Text = "Authentication system: " + authSystemName;
            lblServiceGroupName.Text = "System group name: " + groupName;

            // Get group names
            if (groupNames != null)
            {
                for (int i = 0; i < groupNames.Count; i++)
                    groupNameComboBox.Items.Add(groupNames[i]);

                if (groupNameComboBox.Items.Count > 0)
                    groupNameComboBox.SelectedIndex = 0;
            }

            // Copy user ID list
            this.groupIDs = new List<int>();

            if (groupIDs != null)
            {
                this.groupIDs.AddRange(groupIDs);
            }

            groupID = -1;
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Cancel button click
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            groupID = -1;
            groupName = "";
            Close();
        }

        /// <summary>
        /// OK button click
        /// </summary>
        private void btnOK_Click(object sender, EventArgs e)
        {
            groupID = groupIDs[groupNameComboBox.SelectedIndex];
            groupName = groupNameComboBox.Text;
            Close();
        }

        /// <summary>
        /// Key down event handler
        /// </summary>
        private void btnOK_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == System.Windows.Forms.Keys.Enter) btnOK_Click(sender, null);
            else
                if (e.KeyCode == System.Windows.Forms.Keys.Escape) btnCancel_Click(sender, null);
        }


        #endregion
    }
}
