/// <summary>
///   Solution : NovaTend
///   Project : PostLogin.exe
///   Module : mainForm.cs
///   Description :  implements the methods of class mainForm
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
using Microsoft.Win32;
using System.Threading;
using System.Net;
using System.Net.Sockets;

using SettingsManagement;
using ScreenBuilder;
using ContentManagement;
using Serialization;
using Encryption;

using SystemData;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;

using Communication;
using Communication.Client;

using Commands;
using CommandClient;

using License;

namespace PostLogin
{
    /// <summary>
    /// Post login process main form
    /// </summary>
    public partial class mainForm : Form
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
                    _settingsManager = new SettingsManager();
                return _settingsManager;
            }

            set
            {
                _settingsManager = value;
            }
        }

        #endregion

        #region Server connection

        // Server description
        private SERVER_DESCRIPTION serverDescr;

        // Client descirption
        private CLIENT_DESCRIPTION clientDescr;

        // Socket client instance
        private IPCClient _ipcClient;

        // Socket client property
        public IPCClient ipcClient
        {
            get
            {
                if (_ipcClient == null)
                {
                    // Prepare client description
                    clientDescr = new CLIENT_DESCRIPTION();
                    clientDescr.ClientType = 6; // Post login process
                    clientDescr.ClientName = "Post Login Process";
                    clientDescr.Version = 0x00010000;
                    clientDescr.OSVersion = ContentManager.GetOSVersion();
                    clientDescr.PrivateIP = LocalIPAddress();

                    // Get server description
                    serverDescr = settingsManager.GetHubServer();

                    _ipcClient = new IPCClient(clientDescr, serverDescr, null, TimeSpan.FromSeconds(60));
                }

                return _ipcClient;
            }

            set
            {
                _ipcClient = value;
            }
        }

        /// <summary>
        /// Get IP address
        /// </summary>
        public string LocalIPAddress()
        {
            IPHostEntry host;
            string localIP = "";
            host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (IPAddress ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    localIP = ip.ToString();
                    break;
                }
            }
            return localIP;
        }

        /// <summary>
        /// Connect to server
        /// </summary>
        /// <returns>TRUE - if success</returns>
        private bool ConnectToServer()
        {
            // Add client to connection list
            return ConnectionManager.Instance.Add(ipcClient);
        }

        /// <summary>
        /// Disconnect from server
        /// </summary>
        void DisconnectFromServer()
        {
            //socketClient.Disconnect();
            ConnectionManager.Instance.Remove(ipcClient);
            ipcClient = null;
        }

        // WD client instance
        private WDClient _wdClient;

        // WD client property
        public WDClient wdClient
        {
            get
            {
                if (_wdClient == null)
                    _wdClient = new WDClient();

                return _wdClient;
            }

            set
            {
                _wdClient = value;
            }
        }

        #endregion

        #region Key blocker

        // Key blocker instance
        private KeyBlocker _keyBlocker;

        // Key blocker property
        public KeyBlocker keyBlocker
        {
            get
            {
                if (_keyBlocker == null)
                    _keyBlocker = new KeyBlocker(wdClient);
                return _keyBlocker;
            }

            set
            {
                _keyBlocker = value;
            }
        }

        #endregion

        #region Content management

        // Content manager instance
        private ContentManager _contentManager;

        // Content maganer property
        public ContentManager contentManager
        {
            get
            {
                if (_contentManager == null)
                    _contentManager = new ContentManager(wdClient);

                return _contentManager;
            }

            set
            {
                _contentManager = value;
            }
        }

        #endregion

        #region Screen building

        // Screen builder instance
        private ScreenBuildManager _screenBuilder;

        // Screen builder property
        public ScreenBuildManager screenBuilder
        {
            get
            {
                return _screenBuilder;
            }

            set
            {
                _screenBuilder = value;
            }
        }

        // user ID
        private int userID;

        /// <summary>
        /// Create user screen
        /// </summary>
        private int CreateUserScreen()
        {
            int resCode = ContentManager.RES_NO_USER_CONTENT;
            userID = settingsManager.GetPostLoginUserID();
            screenBuilder = contentManager.BuildUserScreen(userID, mainPanel, new EventHandler(submitButton_Click), new EventHandler(cancelButton_Click), ref resCode);
            return resCode;
        }

        #endregion

        #region Validation

        /// <summary>
        /// Validate parameters
        /// </summary>
        private bool ValidateParams()
        {
            if (screenBuilder != null)
                return contentManager.ValidateParams(userID, Environment.MachineName, screenBuilder.mainUserScreen);
            else
                return false;
        }

        /// <summary>
        /// Validate answers
        /// </summary>
        private bool ValidateAnswers()
        {
            if (screenBuilder != null)
                return contentManager.ValidateAnswers(userID, Environment.MachineName, screenBuilder.mainUserScreen);
            else
                return false;
        }

        #endregion

        #region Legal disclaimer

        /// <summary>
        /// Confirm legal disclaimer
        /// </summary>
        private bool ConfirmLegalDisclaimer()
        {
            if (screenBuilder != null)
                return contentManager.ConfirmLegalDisclaimer(userID, screenBuilder.mainUserScreen, screenBuilder.subScreensList);
            else
                return false;
        }

        #endregion

        #region Constructing

        /// <summary>
        /// Constructor
        /// </summary>
        public mainForm()
        {
            InitializeComponent();
            settingsManager = null;
            contentManager = null;
            screenBuilder = null;
            ipcClient = null;
            wdClient = null;
            keyBlocker = null;
        }
        
        /// <summary>
        /// Main form load event handler
        /// </summary>
        private void mainForm_Load(object sender, EventArgs e)
        {
            // Set main window on top
            this.Top = 0;
            this.Left = 0;
            this.Height = SystemInformation.PrimaryMonitorSize.Height;
            this.Width = SystemInformation.PrimaryMonitorSize.Width;
            this.TopMost = true;

            // Connect to server
            ConnectToServer();

            // Block keys
            keyBlocker.BlockKeys();

            encryptor.Init();

            // Create screen
            int createScreenResult = CreateUserScreen();
            if ((createScreenResult == ContentManager.RES_EMPTY_SCREEN) ||
                (createScreenResult == ContentManager.RES_NO_USER_CONTENT))
                CancelLoading();
        }

        // Invoke delegate
        private delegate void InvokeDelegate();

        /// <summary>
        /// Cancel loading (close during loading)
        /// </summary>
        private void CancelLoading()
        {    
            // Will cancel loading this form
            this.DialogResult = DialogResult.Cancel;
            this.BeginInvoke(new InvokeDelegate(CloseMainForm));
        }

        /// <summary>
        /// Function of form closing
        /// </summary>
        private void CloseMainForm()
        {
            this.Close();
        }

        /// <summary>
        /// Main form close event handler
        /// </summary>
        private void mainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Unblock keys
            keyBlocker.UnBlockKeys();

            // Disconnect from server
            DisconnectFromServer();

            encryptor.Cleanup();
        }
                
        #endregion

        #region Buttons

        /// <summary>
        /// Submit button click event handler
        /// </summary>
        private void submitButton_Click(object sender, EventArgs e)
        {
            if (!ConfirmLegalDisclaimer())
            {
                MessageBox.Show("You can use the system only if you agree with the legal disclaimer!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                cancelButton_Click(null, null);
                return;
            }

            if (!ValidateParams())
            {
                MessageBox.Show("Invalid parameters values!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                cancelButton_Click(null, null);
                return;
            }

            if (!ValidateAnswers())
            {
                MessageBox.Show("You enter wrong answer!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                cancelButton_Click(null, null);
                return;
            }
                       
            this.Close();
        }

        /// <summary>
        /// Cancel button click event handler
        /// </summary>
        private void cancelButton_Click(object sender, EventArgs e)
        {
            keyBlocker.WindowsLogOff();
            Close();
        }

        #endregion

    }

}
