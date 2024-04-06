/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmADSettings.cs
///   Description :  active directory accounts settings module
/// </summary>

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using ADAccountManagement;
using WriteLog;

namespace ManagementTool
{
    /// <summary>
    /// AD settings window
    /// </summary>
    public partial class fmADSettings : Form
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

        #region Variables

        // Settings string
        private string _settingsString;

        public string settingsString
        {
            get
            {
                return _settingsString;
            }
            set
            {
                _settingsString = value;
            }
        }

        #endregion

        #region Constructor

        // Supervisor flag
        private bool supervisor;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="setStr">settings string</param>
        public fmADSettings(string setStr, bool supervisor, LogWriter logWriter)
        {
            InitializeComponent();

            settingsString = setStr;

            this.supervisor = supervisor;

            this.logWriter = logWriter;

            // Parse input settings string
            ADSettingsParser settingsParser = new ADSettingsParser();

            defaultOUTextBox.Text = settingsParser.GetDefaultOU(settingsString);
            domainTextBox.Text = settingsParser.GetDomainName(settingsString);
            serviceUserNameTextBox.Text = settingsParser.GetServiceUserName(settingsString);
            defaultRootOUTextBox.Text = settingsParser.GetDefaultRootOU(settingsString);
            serviceUserPasswordTextBox.Text = settingsParser.GetServiceUserPassword(settingsString);

            logWriter.WriteToLog("Active directory settings management --> Trying to edit AD settings string");
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Save button click
        /// </summary>
        private void btnSave_Click(object sender, EventArgs e)
        {
            settingsString = "<domain:" + domainTextBox.Text + ">" +
                "<defaultOU:" + defaultOUTextBox.Text + ">" +
                "<defaultRootOU:" + defaultRootOUTextBox.Text + ">" +
                "<sUserName:" + serviceUserNameTextBox.Text + ">" +
                "<sUserPassword:" + serviceUserPasswordTextBox.Text + ">";

            logWriter.WriteToLog("Active directory settings management --> AD settings string was changed: [" +
                "<domain:" + domainTextBox.Text + ">" +
                "<defaultOU:" + defaultOUTextBox.Text + ">" +
                "<defaultRootOU:" + defaultRootOUTextBox.Text + ">" +
                "<sUserName:" + serviceUserNameTextBox.Text + ">" +
                "<sUserPassword:" + new String('*',serviceUserPasswordTextBox.Text.Length) + "> ]");

            Close();
        }

        /// <summary>
        /// Cancel button click
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Active directory settings management --> AD settings string changes were canceled!");
            Close();
        }

        /// <summary>
        /// Key down event handler
        /// </summary>
        private void serviceUserPasswordTextBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == System.Windows.Forms.Keys.Enter) btnSave_Click(sender, null);
            else
                if (e.KeyCode == System.Windows.Forms.Keys.Escape) btnCancel_Click(sender, null);
        }

        /// <summary>
        /// Change password click
        /// </summary>
        private void changePwdLabel_Click(object sender, EventArgs e)
        {
            fmChangePassword fmChangePwd = new fmChangePassword(supervisor);
            fmChangePwd.ShowDialog();

            if (fmChangePwd.PasswordChanged)
            {
                serviceUserPasswordTextBox.Text = fmChangePwd.Password;
            }
        }

        #endregion

        #region Events

        /// <summary>
        /// Mouse hover event handler
        /// </summary>
        private void serviceUserPasswordTextBox_MouseHover(object sender, EventArgs e)
        {
            if (supervisor)
                pwdToolTip.SetToolTip(serviceUserPasswordTextBox, serviceUserPasswordTextBox.Text);
            else
                pwdToolTip.SetToolTip(serviceUserPasswordTextBox, "");
        }

        #endregion
    }
}
