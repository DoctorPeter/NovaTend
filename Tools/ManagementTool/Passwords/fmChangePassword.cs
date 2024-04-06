/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmChangePassword.cs
///   Description :  change password window module
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
    /// Change password window class
    /// </summary>
    public partial class fmChangePassword : Form
    {
        // Password string
        private string _password;

        // Password property
        public string Password
        {
            get
            {
                return _password;
            }
        }

        // Password changed flag
        private bool _changed;

        public bool PasswordChanged
        {
            get
            {
                return _changed;
            }
        }

        // Supervisor flag
        private bool supervisor;

        /// <summary>
        /// Constructor
        /// </summary>
        public fmChangePassword(bool supervisor)
        {
            InitializeComponent();

            _password = "";

            this.supervisor = supervisor;
        }

        /// <summary>
        /// Button OK click
        /// </summary>
        private void btnOK_Click(object sender, EventArgs e)
        {
            if (newPwdTextBox.Text == confirmPwdTextBox.Text)
            {
                _password = newPwdTextBox.Text;
                _changed = true;
                Close();
            }
            else
            {
                MessageBox.Show("The entered passwords do not match", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                _changed = false;
                _password = "";
            }
        }

        /// <summary>
        /// Button Cancel click
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            _changed = false;
            _password = "";
            Close();

        }

        /// <summary>
        /// Key down event handler
        /// </summary>
        private void newPwdTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == System.Windows.Forms.Keys.Enter) btnOK_Click(sender, null);
            else
                if (e.KeyCode == System.Windows.Forms.Keys.Escape) btnCancel_Click(sender, null);
        }

        /// <summary>
        /// Mouse hover event handler
        /// </summary>
        private void newPwdTextBox_MouseHover(object sender, EventArgs e)
        {
            TextBox textBox = sender as TextBox;
            if (supervisor)
                pwdToolTip.SetToolTip(textBox, textBox.Text);
            else
                pwdToolTip.SetToolTip(textBox, "");
        }
    }
}
