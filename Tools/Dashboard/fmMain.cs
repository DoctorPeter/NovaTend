/// <summary>
///   Solution : NovaTend
///   Project : Dashboard.exe
///   Module : fmMain.cs
///   Description :  main window module
/// </summary>
/// 
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

using SystemData;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;

using Communication;
using Communication.Client;

using Commands;
using CommandClient;

using DataModule;
using Encryption;
using SettingsManagement;
using Serialization;
using WriteLog;
using ServerConnector;

namespace Dashboard
{
    /// <summary>
    /// Main window class
    /// </summary>
    public partial class fmMain : Form
    {
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

        #region Settings management

        // Settings manager instance
        private SettingsManager _settingsManager;

        // Settings manager property
        public SettingsManager settingsManager
        {
            get
            {
                if (_settingsManager == null)
                {
                    _settingsManager = new SettingsManager();
                }

                return _settingsManager;
            }

            set
            {
                _settingsManager = value;
            }
        }

        #endregion

        #region Dashboard manager

        // Command manager instance
        private DashboardManager _dashboradManager;

        // Command manager property
        public DashboardManager dashboardManager
        {
            get
            {
                if (_dashboradManager == null)
                {
                    _dashboradManager = new DashboardManager(cmdImageList, clientsInfoPanel, settingsManager, encryptor, logWriter);
                }

                return _dashboradManager;
            }

            set
            {
                _dashboradManager = value;
            }
        }

        #endregion

        #region LOG

        // internal LOG-writer instance
        private LogWriter _logWriter;

        //LOG-writer prorepty
        public LogWriter logWriter
        {
            get
            {
                if (_logWriter == null)
                {
                    string logPath = settingsManager.GetLogPath();
                    string timeString = DateTime.Now.ToString("MM.dd.yy");
                    string logFileName = "NovaTend_Dashboard_" + timeString + ".log";
                    logFileName = Path.Combine(logPath, logFileName);

                    _logWriter = new LogWriter(logFileName);
                    if (settingsManager.GetLogEncFlag())
                        _logWriter.AddMode(LogWriter.LOG_MODE_ENCRYPT_MESSAGES);
                }

                return _logWriter;
            }

            set
            {
                _logWriter = value;
            }
        }

        #endregion

        #region Construction
        
        // current user name
        private string currentUserName;

        /// <summary>
        /// Constructor
        /// </summary>
        public fmMain()
        {
            _encryptor = null;
            _logWriter = null;
            _settingsManager = null;
            _dashboradManager = null;

            encryptor.Init();

            logWriter.WriteToLog(" ------ New NovaTend dashboard session ------ ");

            InitializeComponent();

            foreach (Button cmdBtn in dashboardManager.cmdButtonsList)
            {
                cmdPanel.Controls.Add(cmdBtn);
            }

            threadDone = true;
            timerThread = null;
        }

        /// <summary>
        /// Main window show event handler
        /// </summary>
        private void fmMain_Shown(object sender, EventArgs e)
        {
            disconnectButton_Click(null, null);
            connectButton_Click(null, null);
        }

        /// <summary>
        /// Main window closing event handler
        /// </summary>
        private void fmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            disconnectButton_Click(null, null);
            encryptor.Cleanup();
            logWriter.WriteToLog(" ------ Close NovaTend dashboard session ------ ");
        }

        #endregion

        #region Tool box and main menu

        // Supervisor flag
        public bool supervisor;

        /// <summary>
        /// Button "About" click
        /// </summary>
        private void aboutButton_Click(object sender, EventArgs e)
        {
            fmAbout aboutBox = new fmAbout();
            aboutBox.ShowDialog();
            aboutBox.Dispose();
        }

        // Server connector
        private fmConnect _serverConnector;

        /// <summary>
        /// Connect button click
        /// </summary>
        private void connectButton_Click(object sender, EventArgs e)
        {
            supervisor = false;

            mainPanel.Visible = false;

            // Create connection window
            if (_serverConnector != null)
                _serverConnector.DisconnectFromServer();

            _serverConnector = new fmConnect(7 /*Dashboard*/, "Dashboard", encryptor, logWriter);
            _serverConnector.ShowDialog();

            // Get connection string
            dashboardManager.connectionString = _serverConnector.connectionString;
            dashboardManager.userPermissions = _serverConnector.userPermissions;
            dashboardManager.currentUserID = _serverConnector.CurrentUserID;

            if ((dashboardManager.connectionString != "") &&
                (dashboardManager.userPermissions != null))
            {
                mainPanel.Visible = true;
                currentUserName = _serverConnector.enteredUserName;
                dashboardManager.wdClient = _serverConnector.wdClient;

                this.Text = "NovaTend dashboard - [ " + currentUserName + " ]";
                      
                connectToolStripMenuItem.Enabled = false;
                disconnectToolStripMenuItem.Enabled = true;
                connectButton.Enabled = false;
                disconnectButton.Enabled = true;

                if (!dashboardManager.CheckUserPermissions())
                    disconnectButton_Click(null, null);
                else
                {
                    TimerThreadStop();
                    threadDone = false;
                    timerThread = new Thread(this.timerThreadFunction);
                    timerThread.Start();
                }
            }
            else
            {
                disconnectButton_Click(null, null);
                MessageBox.Show("Application server connection not established!!!", "Server connection", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        /// <summary>
        /// Connect button click
        /// </summary>
        private void disconnectButton_Click(object sender, EventArgs e)
        {
            supervisor = false;
            mainPanel.Visible = false;
            clientsInfoPanel.Controls.Clear();
            this.Text = "NovaTend dashboard - [ DISCONNECTED ]";
            currentUserName = "";

            TimerThreadStop();

            connectToolStripMenuItem.Enabled = true;
            disconnectToolStripMenuItem.Enabled = false;
            connectButton.Enabled = true;
            disconnectButton.Enabled = false;

            if (_serverConnector != null)
                _serverConnector.DisconnectFromServer();

            logWriter.WriteToLog("NovaTend dashboard connection --> Current user disconnected from NovaTend application server");
        }
        
        /// <summary>
        /// Exit main menu item click
        /// </summary>
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        #endregion

        #region Threading

        // Locker object
        static object locker = new object();

        // Thread done flag
        private bool _threadDone;

        // Thread done property
        public bool threadDone
        {
            set
            {
                lock (locker)
                {
                    _threadDone = value;
                }
            }
            get
            {
                lock (locker)
                {
                    return _threadDone;
                }
            }
        }

        /// <summary>
        /// Stop timer thread
        /// </summary>
        private void TimerThreadStop()
        {
            try
            {
                threadDone = true;
                timerThread.Join();
            }
            catch
            {
                return;
            }
        }

        // Video thread object
        private Thread timerThread;


        /// <summary>
        /// Video thread function
        /// </summary>
        private void timerThreadFunction()
        {
            while (!threadDone)
            {
                try
                {
                    if (InvokeRequired)
                        Invoke(new MethodInvoker(delegate
                        {
                            dashboardManager.FillClientsList();
                        }));
                    else
                        dashboardManager.FillClientsList();
                }
                catch (Exception ex)
                {
                    //----
                }

                Thread.Sleep(15000);
            }
        }

        #endregion
        
    }
}
