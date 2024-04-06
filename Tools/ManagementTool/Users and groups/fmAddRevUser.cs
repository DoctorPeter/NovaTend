/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmAddRevUser.cs
///   Description :  user accounts linking module
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
    /// User accounts linking window
    /// </summary>
    public partial class fmAddRevUser : Form
    {

        #region Result

        // Selected user ID
        public int userID;

        // Selected user name
        public string userName;

        // Entered user password
        public string userPassword;

        // User ID list
        private List<int> userIDs;

        #endregion

        #region Constructor
        
        // Supervisor flag
        private bool supervisor;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="userNames">user names list</param>
        /// <param name="userIDs">user ID list</param>
        public fmAddRevUser(List<string> userNames, List<int> userIDs, string authSystemName, string userName, bool supervisor)
        {
            InitializeComponent();

            lblAuthSystem.Text = "Authentication system: " + authSystemName;
            lblServiceUserName.Text = "System user name: " + userName;

            // Get user names
            if (userNames != null)
            {
                for (int i = 0; i < userNames.Count; i++)
                    userNameComboBox.Items.Add(userNames[i]);

                if (userNameComboBox.Items.Count > 0)
                    userNameComboBox.SelectedIndex = 0;
            }

            // Copy user ID list
            this.userIDs = new List<int>();

            if (userIDs != null)
            {
                this.userIDs.AddRange(userIDs);
            }

            userID = -1;
            userPassword = "";

            this.supervisor = supervisor;
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Cancel button click
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            userID = -1;
            userName = "";
            userPassword = "";
            
            Close();
        }

        /// <summary>
        /// OK button click
        /// </summary>
        private void btnOK_Click(object sender, EventArgs e)
        {
            if (passwordTextBox.Text == confirmPasswordTextBox.Text)
            {
                userID = userIDs[userNameComboBox.SelectedIndex];
                userName = userNameComboBox.Text;
                userPassword = passwordTextBox.Text;
                Close();
            }
            else
            {
                MessageBox.Show("The entered passwords do not match", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                userID = -1;
                userName = "";
                userPassword = "";
            }
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

        #region Events

        /// <summary>
        /// Mouse hover event handler
        /// </summary>
        private void passwordTextBox_MouseHover(object sender, EventArgs e)
        {
            TextBox textBox = sender as TextBox;
            if (supervisor)
                pwdToolTip.SetToolTip(textBox, textBox.Text);
            else
                pwdToolTip.SetToolTip(textBox, "");
        }

        #endregion

    }
}
