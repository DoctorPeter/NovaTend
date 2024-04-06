/// <summary>
///   Solution : NovaTend
///   Project : Dashboard.exe
///   Module : CommandManager.cs
///   Description :  command manager module
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

using DataModule;
using Encryption;
using SettingsManagement;
using Serialization;
using WriteLog;

using Commands;
using CommandClient;

using SystemData;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;

namespace Dashboard
{
    /// <summary>
    /// Clients commands manager
    /// </summary>
    public class DashboardManager
    {
        #region Connection

        // Connection string
        private string _connectionString;

        // Connection string property
        public string connectionString
        {
            get
            {
                return _connectionString;
            }

            set
            {
                _connectionString = value;
            }
        }

        // User permissions
        private int[] _userPermissions;

        // User permissions property
        public int[] userPermissions
        {
            get
            {
                return _userPermissions;
            }

            set
            {
                _userPermissions = value;
            }
        }

        // Current user ID
        private int _currentUserID;

        // Current user ID property
        public int currentUserID
        {
            set
            {
                _currentUserID = value;
            }

            get
            {
                return _currentUserID;
            }
        }

        // WD client instance
        private WDClient _wdClient;

        // WD client property
        public WDClient wdClient
        {
            get
            {
                return _wdClient;
            }

            set
            {
                _wdClient = value;
            }
        }
        
        /// <summary>
        /// Check user permissions and connect to server
        /// </summary>
        public bool CheckUserPermissions()
        {
            // Check permissions
            bool canRun = false;
            foreach (int p in userPermissions)
            {
                if ((p == CMD_GET_DB_ACCESS.DB_ACCESS_SUPERVISOR) ||
                    (p == CMD_GET_DB_ACCESS.DB_ACCESS_SYS_ADMIN) ||
                    (p == CMD_GET_DB_ACCESS.DASHBOARD_ACCESS_MANAGER))
                {
                    canRun = true;
                }
            }

            if (!canRun)
            {
                MessageBox.Show("You have no permissions for using NovaTend dashboard!!!", "User permissions", MessageBoxButtons.OK, MessageBoxIcon.Information);
                logWriter.WriteToLog("NovaTend dashboard connection --> Current user have no permissions for using NovaTend dashboard!!!");
            }
           

            return canRun;
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
                if (_dbManager == null)
                {
                    _dbManager = new DataBaseManager(connectionString, logWriter);
                }

                return _dbManager;
            }

            set
            {
                _dbManager = value;
            }
        }

        #endregion

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

        #region Settings management

        // Settings manager instance
        private SettingsManager _settingsManager;

        // Settings manager property
        public SettingsManager settingsManager
        {
            get
            {
                return _settingsManager;
            }

            set
            {
                _settingsManager = value;
            }
        }

        #endregion

        #region Command buttons list

        #region Buttons list

        // Command buttons list
        private List<Button> _cmdButtonsList;

        // Command buttons list property
        public List<Button> cmdButtonsList
        {
            get
            {
                if (_cmdButtonsList == null)
                {
                    _cmdButtonsList = new List<Button>();
                }

                return _cmdButtonsList;
            }

            set
            {
                _cmdButtonsList = value;
            }
        }

        #endregion

        #region Image list

        // Buttons icons image list 
        private ImageList _btnImagesList;

        // Buttons icons image list property
        public ImageList btnImageList
        {
            get
            {
                return _btnImagesList;
            }

            set
            {
                _btnImagesList = value;
            }
        }

        #endregion

        #region Buttons creation

        /// <summary>
        /// Create new command button
        /// </summary>
        /// <param name="btnName">Name</param>
        /// <param name="captionText">Caption</param>
        /// <param name="imgIndex">image index</param>
        /// <param name="onButtonClick">onClick event handler</param>
        /// <returns>Button instance</returns>
        private Button CreateCmdButton(string btnName, string captionText, int imgIndex, EventHandler onButtonClick)
        {
            // Create new button
            Button newButton = new Button();

            // Configure button
            newButton.Text = captionText;
            newButton.Anchor = ((AnchorStyles)(((AnchorStyles.Top | AnchorStyles.Left) | AnchorStyles.Right)));
            newButton.BackColor = SystemColors.Control;
            newButton.FlatStyle = FlatStyle.Flat;
            newButton.ImageAlign = ContentAlignment.MiddleLeft;
            newButton.ImageIndex = imgIndex;
            newButton.ImageList = btnImageList;
            newButton.Name = btnName;
            newButton.Size = new Size(180, 40);
            newButton.UseVisualStyleBackColor = false;
            newButton.Click += onButtonClick;

            return newButton;
        }

        /// <summary>
        /// Create list of command buttons
        /// </summary>
        private void CreateCmdButtonsList()
        {
            // Screenshot button
            Button screenshotButton = CreateCmdButton("screenshotButton", "Get screenshot", 0, new EventHandler(getScreenshotButton_Click));
            screenshotButton.Location = new Point(10, 15);
            cmdButtonsList.Add(screenshotButton);

            // Snapshot button
            Button snapshotButton = CreateCmdButton("snapshotButton", "Get cam snapshot", 1, new EventHandler(getSnapshotButton_Click));
            snapshotButton.Location = new Point(10, 65);
            cmdButtonsList.Add(snapshotButton);

            // Grab desktop button
            Button grabDesktopButton = CreateCmdButton("grabDesktopButton", "Get desktop video", 2, new EventHandler(grabDesktopButton_Click));
            grabDesktopButton.Location = new Point(10, 115);
            cmdButtonsList.Add(grabDesktopButton);

            // Grab video button
            Button grabCamVideoButton = CreateCmdButton("grabCamVideoButton", "Get cam video", 3, new EventHandler(grabCamVideoButton_Click));
            grabCamVideoButton.Location = new Point(10, 165);
            cmdButtonsList.Add(grabCamVideoButton);
        }

        #endregion

        #region On click event handlers

        /// <summary>
        /// Get schreenshot button click event handler
        /// </summary>
        private void getScreenshotButton_Click(object sender, EventArgs e)
        {
            try
            {
                for (int i = clientsInfoPanel.Controls.Count - 1; i >= 0; i--)
                {
                    if (clientsInfoPanel.Controls[i] is ClientInfoCard)
                    {
                        ClientInfoCard clientCard = clientsInfoPanel.Controls[i] as ClientInfoCard;
                        if (clientCard.Checked)
                        {
                            uint receiverID = Convert.ToUInt32(clientCard.clientID);
                            byte[] imageBytes = wdClient.GET_CLIENT_SCREEN_SHOT((uint)currentUserID, receiverID);

                            if ((imageBytes != null) && (imageBytes.Length > 0))
                            {
                                fmScreenshotViewer _fmScreenshotViewer = new fmScreenshotViewer(imageBytes);
                                _fmScreenshotViewer.Show();
                            }
                            else
                                MessageBox.Show("Can't get client screenshot!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }
                    }
                }
            }
            catch
            {
                MessageBox.Show("Server communication error!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Get cam snapshot click event handler
        /// </summary>
        private void getSnapshotButton_Click(object sender, EventArgs e)
        {
            try
            {
                for (int i = clientsInfoPanel.Controls.Count - 1; i >= 0; i--)
                {
                    if (clientsInfoPanel.Controls[i] is ClientInfoCard)
                    {
                        ClientInfoCard clientCard = clientsInfoPanel.Controls[i] as ClientInfoCard;
                        if (clientCard.Checked)
                        {
                            uint receiverID = Convert.ToUInt32(clientCard.clientID);
                            byte[] imageBytes = wdClient.GET_CLIENT_CAM_SNAPSHOT((uint)currentUserID, receiverID);

                            if ((imageBytes != null) && (imageBytes.Length > 0))
                            {
                                fmScreenshotViewer _fmScreenshotViewer = new fmScreenshotViewer(imageBytes);
                                _fmScreenshotViewer.Show();
                            }
                            else
                                MessageBox.Show("Can't get client cam snapshot!", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }
                    }
                }
            }
            catch
            {
                MessageBox.Show("Server communication error!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Grab desktop click event handler
        /// </summary>
        private void grabDesktopButton_Click(object sender, EventArgs e)
        {
            for (int i = clientsInfoPanel.Controls.Count - 1; i >= 0; i--)
            {
                if (clientsInfoPanel.Controls[i] is ClientInfoCard)
                {
                    ClientInfoCard clientCard = clientsInfoPanel.Controls[i] as ClientInfoCard;
                    if (clientCard.Checked)
                    {
                        uint receiverID = Convert.ToUInt32(clientCard.clientID);
                        fmVideoViewer _fmVideoViewer = new fmVideoViewer(wdClient, receiverID, currentUserID, 0);
                        _fmVideoViewer.Show();
                    }
                }
                    
            }
        }

        /// <summary>
        /// Grab video click event handler
        /// </summary>
        private void grabCamVideoButton_Click(object sender, EventArgs e)
        {
            for (int i = clientsInfoPanel.Controls.Count - 1; i >= 0; i--)
            {
                if (clientsInfoPanel.Controls[i] is ClientInfoCard)
                {
                    ClientInfoCard clientCard = clientsInfoPanel.Controls[i] as ClientInfoCard;
                    if (clientCard.Checked)
                    {
                        uint receiverID = Convert.ToUInt32(clientCard.clientID);
                        fmVideoViewer _fmVideoViewer = new fmVideoViewer(wdClient, receiverID, currentUserID, 1);
                        _fmVideoViewer.Show();
                    }
                }

            }
        }

        #endregion

        #endregion

        #region Clients list

        // Clients list view
        private Panel _clientsInfoPanel;

        // Clients list view property
        public Panel clientsInfoPanel
        {
            get
            {
                return _clientsInfoPanel;
            }

            set
            {
                _clientsInfoPanel = value;
            }
        }

        /// <summary>
        /// Get location of new client card
        /// </summary>
        public Point GetClientInfoCardLocation()
        {
            Point result = new Point(0, 0);
            ClientInfoCard clientCard = null;

            for (int i = clientsInfoPanel.Controls.Count - 1; i >= 0; i--)
            {
                if (clientsInfoPanel.Controls[i] is ClientInfoCard)
                {
                   clientCard = clientsInfoPanel.Controls[i] as ClientInfoCard;
                }
            }

            if (clientCard != null)
            {
                result = clientCard.Location;
                result.Y += clientCard.Height;
            }

            return result;
        }

        /// <summary>
        /// Fill client card
        /// </summary>
        public void FillClientCard(ClientInfoCard clientCard, SERVER_DESCRIPTION hub)
        {
            uint userID = 0, authSysID = 0;
            byte[] encAuthSystemName = null;
            byte[] encUserName = null;
            byte[] encSysUserName = null;
            byte[] encFullUserName = null;

            string osVersion = String.Empty;
            string cpuName = String.Empty;
            long amountOfPhysicalMemory = 0;
            long amountOfUsedPhysicalMemory = 0;
            long amountOfVirtualMemory = 0;
            long amountOfUsedVirtualMemory = 0;
            string motherboardManufacturerName = String.Empty;
            string motherboarProductName = String.Empty;
            string BIOSManufacturerName = String.Empty;
            string BIOSVersionName = String.Empty;
            string chipsetName = String.Empty;
            string videoAdapterName = String.Empty;
            string monitorName = String.Empty;
            long amountOfVideoMemory = 0;

            // Get computer name
            string computerName = wdClient.GET_COMPUTER_NAME((uint)currentUserID, hub.serverID);

            if (computerName != String.Empty)
            {
                int zeroInd = hub.ipAddress.Length - 1;
                while ((hub.ipAddress[zeroInd] != '\0') && (zeroInd > 0)) zeroInd--;
                clientCard.SetComputerInfo((int)hub.serverID, computerName, hub.ipAddress.Substring(0, zeroInd + 1));
            }
            else
                clientCard.SetComputerInfo((int)hub.serverID, "Unavailable", "Unavailable");

            // Get user info
            if (wdClient.GET_LOGGED_USER_ID((uint)currentUserID, out userID, out authSysID, hub.serverID) &&
                wdClient.GET_AUTH_SYS_USER_INFO(userID, authSysID, out encAuthSystemName, out encUserName, out encSysUserName, out encFullUserName))
            {
                string userName;
                if (encUserName.Length > 0)
                    userName = encryptor.DecryptString(encUserName);
                else
                    userName = "LOG OFF";

                string fullUserName;
                if (encFullUserName.Length > 0)
                    fullUserName = encryptor.DecryptString(encFullUserName);
                else
                    fullUserName = "LOG OFF";

                string sysUserName;
                if (encSysUserName.Length > 0)
                    sysUserName = encryptor.DecryptString(encSysUserName);
                else
                    sysUserName = "LOG OFF";

                string authSystemName;
                if (encAuthSystemName.Length > 0)
                    authSystemName = encryptor.DecryptString(encAuthSystemName);
                else
                    authSystemName = "LOG OFF";

                // Get environment info
                ENVIROMENT_INFO_CONTAINER envContainer = wdClient.GET_USER_ENV_INFO((uint)currentUserID, hub.serverID);

                if (envContainer != null)
                {
                    clientCard.SetUserInfo(userName, fullUserName, sysUserName, authSystemName, envContainer.userDowntime);
                    if ((envContainer.activeProgramName.Length > 0) &&
                        (envContainer.programNamesList != null) &&
                        (envContainer.programNamesList.Length > 0))
                            clientCard.SetSoftwareInfo(envContainer.activeProgramName, envContainer.programNamesList);
                    else
                        clientCard.SetSoftwareInfo("...", new string[0]);
                }
                else
                {
                    clientCard.SetUserInfo("Unavailable", "Unavailable", "Unavailable", "Unavailable", 0);
                    clientCard.SetSoftwareInfo("...", new string[0]);
                }
            }
            else
            {
                clientCard.SetUserInfo("Unavailable", "Unavailable", "Unavailable", "Unavailable", 0);
            }

            // Get hardware info
            if (wdClient.GET_HARDWARE_INFO((uint)currentUserID, 
                                           out osVersion, out cpuName, out amountOfPhysicalMemory, out amountOfUsedPhysicalMemory, out amountOfVirtualMemory,
                                           out amountOfUsedVirtualMemory, out motherboardManufacturerName, out motherboarProductName, out BIOSManufacturerName,
                                           out BIOSVersionName, out chipsetName, out videoAdapterName, out monitorName, out amountOfVideoMemory, hub.serverID))
            {
                clientCard.SetHardwareInfo(osVersion, cpuName, amountOfPhysicalMemory, amountOfUsedPhysicalMemory, amountOfVirtualMemory,
                                           amountOfUsedVirtualMemory, motherboardManufacturerName, motherboarProductName, BIOSManufacturerName,
                                           BIOSVersionName, chipsetName, videoAdapterName, monitorName, amountOfVideoMemory);
            }
            else
            {
                clientCard.SetHardwareInfo("Unavailable", "Unavailable", 0, 0, 0, 0, "Unavailable",
                                           "Unavailable", "Unavailable", "Unavailable", "Unavailable",
                                           "Unavailable", "Unavailable", 0);
            }
        }

        /// <summary>
        /// Fill clients list
        /// </summary>
        public void FillClientsList()
        {
                // Socket client description list
                SERVER_DESCRIPTION_LIST hubServersList  = wdClient.GET_HUB_SERVERS_LIST();

                if (hubServersList != null)
                {
                    // Check and update list view
                    for (int i = clientsInfoPanel.Controls.Count - 1; i >= 0; i--)
                    {
                        if (clientsInfoPanel.Controls[i] is ClientInfoCard)
                        {
                            ClientInfoCard clientCard = clientsInfoPanel.Controls[i] as ClientInfoCard;

                            bool found = false;
                            foreach (SERVER_DESCRIPTION hub in hubServersList)
                            {
                                // Check client ID
                                if (clientCard.clientID == hub.serverID)
                                {
                                    FillClientCard(clientCard, hub);
                                    found = true;
                                    break;
                                 }
                               }

                                if (!found)
                                {
                                    clientsInfoPanel.Controls.Remove(clientCard);
                                }
                            }
                        }

                        // Add new items
                        foreach (SERVER_DESCRIPTION hub in hubServersList)
                        {
                            bool found = false;
                            
                            for (int i = clientsInfoPanel.Controls.Count - 1; i >= 0; i--)
                            {
                                if (clientsInfoPanel.Controls[i] is ClientInfoCard)
                                {
                                    ClientInfoCard clientCard = clientsInfoPanel.Controls[i] as ClientInfoCard;

                                    if (clientCard.clientID == hub.serverID)
                                    {
                                        found = true;
                                        break;
                                    }
                                }
                            }

                            if (!found)
                            {
                                ClientInfoCard clientCard = new ClientInfoCard();
                                clientCard.Width = clientsInfoPanel.Width - 2;
                                clientCard.Anchor = (System.Windows.Forms.AnchorStyles)(System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right);
                                clientCard.Location = GetClientInfoCardLocation();
                                FillClientCard(clientCard, hub);
                                clientsInfoPanel.Controls.Add(clientCard);
                                clientsInfoPanel.VerticalScroll.Value = 0;
                            }
                        }
                }
        }
                

        #endregion
        
        #region Construction

        /// <summary>
        /// Constructor
        /// </summary>
        public DashboardManager(ImageList btnImageList, Panel clientsInfoPanel, SettingsManager settingsManager, Encryptor encryptor, LogWriter logWriter)
        {
            cmdButtonsList = null;
            dbManager = null;
            wdClient = null;

            this.btnImageList = btnImageList;
            this.settingsManager = settingsManager;
            this.encryptor = encryptor;
            this.logWriter = logWriter;
            this.clientsInfoPanel = clientsInfoPanel;

            CreateCmdButtonsList();
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
                return _logWriter;
            }

            set
            {
                _logWriter = value;
            }
        }

        #endregion
    }
}
