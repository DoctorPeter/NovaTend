using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using WriteLog;
using ADAccountManagement;

namespace ManagementTool
{
    public partial class fmADGroupSettings : Form
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

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="setStr">settings string</param>
        /// <param name="logWriter">LOG-writer</param>
        public fmADGroupSettings(string setStr, LogWriter logWriter)
        {
            InitializeComponent();

            settingsString = setStr;
            this.logWriter = logWriter;

            // Parse input settings string
            ADSettingsParser settingsParser = new ADSettingsParser();

            groupScopeComboBox.SelectedIndex = groupScopeComboBox.FindString(settingsParser.GetGroupScope(settingsString));
            groupTypeComboBox.SelectedIndex = groupTypeComboBox.FindString(settingsParser.GetGroupTypeName(settingsString));
            
            logWriter.WriteToLog("Active directory group settings management --> Trying to edit AD group settings string");
        }

        #endregion

        #region Buttons

        /// <summary>
        /// Save button click
        /// </summary>
        private void btnSave_Click(object sender, EventArgs e)
        {
            settingsString = "<groupScope:" + groupScopeComboBox.Text + ">" +
                             "<groupType:" + groupTypeComboBox.Text + ">";

            logWriter.WriteToLog("Active directory settings management --> Settings string of AD group was changed: [" +
                "<groupScope:" + groupScopeComboBox.Text + ">" +
                "<groupType:" + groupTypeComboBox.Text + "> ]");

            Close();
        }

        /// <summary>
        /// Cancel button click
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            logWriter.WriteToLog("Active directory settings management --> Settings string of AD group changes were canceled!");
            Close();
        }

        /// <summary>
        /// Key down event handler
        /// </summary>
        private void groupScopeComboBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == System.Windows.Forms.Keys.Enter) btnSave_Click(sender, null);
            else
                if (e.KeyCode == System.Windows.Forms.Keys.Escape) btnCancel_Click(sender, null);
        }

        #endregion
    }
}
