/// <summary>
///   Solution : NovaTend
///   Project : ServerConnector.dll
///   Module : fmConnect.cs
///   Description :  connection window module
/// </summary>

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Net;
using System.Net.Sockets;

using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;

using Communication;
using Communication.Client;

using Commands;
using CommandClient;

using Encryption;
using SettingsManagement;
using SymbolBoxes;
using WriteLog;

namespace ServerConnector
{
    /// <summary>
    /// Connection form class
    /// </summary>
    public partial class fmConnect : Form
    {

        #region DB connection properties

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

        #endregion

        #region User permissions properties

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

        // User name from text box
        public string enteredUserName
        {
            get
            {
                return tbUserID.Text;
            }
        }


        #endregion

        #region Passwords types

        // Cascade string password
        public const int CASCADE_STRING_PWD = 1;

        // Symbol boxes password (one symbol)
        public const int ONE_SYMBOL_BOX_PWD = 3;

        // Symbol boxes password (two symbols)
        public const int TWO_SYMBOL_BOX_PWD = 2;

        #endregion

        #region Password symbol boxes

        // Internal symbol boxes list
        private UTF8_STRINGS_MATRIX_LIST _symbolBoxesList;

        // Symbol boxes list property
        public UTF8_STRINGS_MATRIX_LIST symbolBoxesList
        {
            get
            {
                return _symbolBoxesList;
            }

            set
            {
                _symbolBoxesList = value;
            }
        }

        /// <summary>
        /// Generate new symbol boxes list
        /// </summary>
        /// <param name="symbolBoxType">type of symbol boxes</param>
        /// <returns>symbol boxes list</returns>
        public UTF8_STRINGS_MATRIX_LIST GetSymbolBoxesList(int symbolBoxType)
        {
            
            SymbolBoxesManager symbolBoxesManager = new SymbolBoxesManager();

            // Get random symbols list
            string sCharList = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#$%*~+-(){}[]<=>^;:|?!@";
            byte[] bCharList = System.Text.Encoding.UTF8.GetBytes(sCharList);
            
            UTF8_STRING charList;
            switch (symbolBoxType)
            {
                case SymbolBoxesManager.ONE_SYMBOL_BOX:
                    {
                        charList = symbolBoxesManager.GetRandomCharList(bCharList, 8);
                        break;
                    }

                case SymbolBoxesManager.TWO_SYMBOL_BOX:
                    {
                        charList = symbolBoxesManager.GetRandomCharList(bCharList, 8);
                        break;
                    }

                default:
                    {
                        symbolBoxesList = new UTF8_STRINGS_MATRIX_LIST();
                        return symbolBoxesList;
                    }
            }

            // generate symbol boxes
            symbolBoxesList = symbolBoxesManager.GenerateSymbolBoxes(charList, symbolBoxType);

            // Put symbols to buttons
            for (int i = 0; i < charList.Count; i++)
            {
                /*byte[] charBytes = new byte[charList.chars[i].bytesCount + 1];
                Array.Copy(charList.chars[i].bytes, charBytes, charList.chars[i].bytesCount);
                charBytes[charList.chars[i].bytesCount] = 0;*/

                byte[] charBytes = new byte[charList[i].bytesCount];
                Array.Copy(charList[i].bytes, charBytes, charList[i].bytesCount);
                
                string charString = Encoding.UTF8.GetString(charBytes);

                switch (i)
                {
                    case 0:
                        {
                            symbol1Button.Text = charString;
                            break;
                        }

                    case 1:
                        {
                            symbol2Button.Text = charString;
                            break;
                        }

                    case 2:
                        {
                            symbol3Button.Text = charString;
                            break;
                        }

                    case 3:
                        {
                            symbol4Button.Text = charString;
                            break;
                        }

                    case 4:
                        {
                            symbol5Button.Text = charString;
                            break;
                        }

                    case 5:
                        {
                            symbol6Button.Text = charString;
                            break;
                        }

                    case 6:
                        {
                            symbol7Button.Text = charString;
                            break;
                        }

                    case 7:
                        {
                            symbol8Button.Text = charString;
                            break;
                        }
                }

            }

            return symbolBoxesList;
        }

        /// <summary>
        /// Draw symbol boxes to graphocal files
        /// </summary>
        /// <param name="imageSize">image size</param>
        /// <returns>TRUE - if success</returns>
        bool DrawSymbolBoxes(int imageSize)
        {
            return new SymbolBoxesManager().DrawSymbolBoxes(symbolBoxesList, imageSize);
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

        #region Constructing

        /// <summary>
        /// Constructor
        /// </summary>
        public fmConnect(int clientType, string clientName, Encryptor encryptor, LogWriter logWriter)
        {
            connectionString = "";
            userPermissions = null;
            ipcClient = null;
            wdClient = null;
            userList = null;

            clientDescr = new CLIENT_DESCRIPTION();
            clientDescr.ClientType = clientType;
            clientDescr.ClientName = clientName;
            clientDescr.Version = 0x00010000;
            clientDescr.OSVersion = 2;
            clientDescr.PrivateIP = LocalIPAddress();
            
            this.encryptor = encryptor;
            this.logWriter = logWriter;
            
            currentUserID = -1;
            currentUserPwdType = -1;

            Connected = false;

            InitializeComponent();

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

        // Current time
        private DateTime currentTime;

        /// <summary>
        /// Connection form load handler
        /// </summary>
        private void fmConnect_Load(object sender, EventArgs e)
        {
            SetStringPasswordScreen();

            SettingsManager settingsManager = new SettingsManager();
            remoteServerDescr = settingsManager.GetHostServer();
            globalServerDescr = settingsManager.GetGlobalServer();

            if (remoteServerDescr != null)
            {
                remoteServerIDTextBox.Text = remoteServerDescr.serverID.ToString();
                remoteServerTypeComboBox.SelectedIndex = remoteServerDescr.serverType;
                remoteServerPortTextBox.Text = remoteServerDescr.port.ToString();
                remoteServerAddressTextBox.Text = remoteServerDescr.ipAddress;

                globalServerIDTextBox.Text = globalServerDescr.serverID.ToString();
                globalServerTypeComboBox.SelectedIndex = globalServerDescr.serverType;
                globalServerPortTextBox.Text = globalServerDescr.port.ToString();
                globalServerAddressTextBox.Text = globalServerDescr.ipAddress;
            }

            currentTime = DateTime.Now;
            string timeString = currentTime.ToString("dddd, MM/dd/yy, HH:mm:ss");
            timeLabel.Text = timeString;
                        
            tbUserID.Select();

            //if (ConnectToServer()) GetUserList();
        }

        /// <summary>
        /// Connection form closing handler
        /// </summary>
        private void fmConnect_FormClosing(object sender, FormClosingEventArgs e)
        {
            ClearAllPictureBoxes();
        }

        #endregion

        #region User list

        // User list
        private Dictionary <int, string> userList;

        /// <summary>
        /// Get user names list
        /// </summary>
        private bool GetUserList()
        {
            try
            {
                USER_LIST uList = wdClient.GET_USER_LIST();

                if ((uList != null))
                {
                    userList = new Dictionary<int, string>();
                    for (int i = 0; i < uList.Count; i++)
                    {
                        userList.Add(uList[i].UserID, encryptor.DecryptString(uList[i].EncodedUserName));
                    }
                }
                else
                {
                    MessageBox.Show("Server is unavailable!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }

                return true;
            }
            catch
            {
                MessageBox.Show("Server communication error!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
        }

        /// <summary>
        /// Find user by name
        /// </summary>
        /// <param name="userName">user name</param>
        /// <returns>user ID</returns>
        private int FindUserInList(string userName)
        {
            int userID = -1;

            if (userList != null)
            {
                foreach (KeyValuePair<int, string> pair in userList)
                {
                    if (pair.Value == userName)
                    {
                        userID = pair.Key;
                        break;
                    }
                }
            }

            return userID;
        }

        #endregion

        #region User descriptor

        // Current user ID
        private int currentUserID;

        public int CurrentUserID
        {
            get
            {
                return currentUserID;
            }
        }

        // Current user password ID
        private int currentUserPwdType;

        /// <summary>
        /// Get user descriptor data
        /// </summary>
        /// <param name="userName">user name</param>
        /// <returns>True - if success</returns>
        private bool GetUserDescriptor(string userName)
        {
            try
            {
                USER_DESCRIPTOR userDescriptor = wdClient.GET_USER_DESCRIPTOR(encryptor.EncryptString(userName));

                if (userDescriptor != null)
                {
                    currentUserID = userDescriptor.userID;
                    currentUserPwdType = userDescriptor.pwdType;
                    return true;
                }
                else
                {
                    currentUserID = -1;
                    currentUserPwdType = -1;

                    MessageBox.Show("Server is unavailable!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);

                    return false;
                }
            }
            catch
            {
                MessageBox.Show("Server communication error!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
        }
        
        #endregion

        #region Server connection

        // IPC client instance
        private IPCClient _ipcClient;

        // IPC client property
        public IPCClient ipcClient
        {
            get
            {
                return _ipcClient;
            }

            set
            {
                _ipcClient = value;
            }
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

        // Server description
        private SERVER_DESCRIPTION remoteServerDescr;

        // Server description
        private SERVER_DESCRIPTION globalServerDescr;

        // Client descirption
        private CLIENT_DESCRIPTION clientDescr;

        // Connected to server
        bool Connected;

        /// <summary>
        /// Connect to application server
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool ConnectToServer()
        {
            if (!Connected)
            {
                if (remoteServerDescr == null)
                    remoteServerDescr = new SERVER_DESCRIPTION();

                if (globalServerDescr == null)
                    globalServerDescr = new SERVER_DESCRIPTION();

                remoteServerDescr.serverID = Convert.ToUInt32(remoteServerIDTextBox.Text);
                remoteServerDescr.serverType = remoteServerTypeComboBox.SelectedIndex;
                remoteServerDescr.port = Convert.ToUInt32(remoteServerPortTextBox.Text);
                remoteServerDescr.ipAddress = remoteServerAddressTextBox.Text;

                globalServerDescr.serverID = Convert.ToUInt32(globalServerIDTextBox.Text);
                globalServerDescr.serverType = globalServerTypeComboBox.SelectedIndex;
                globalServerDescr.port = Convert.ToUInt32(globalServerPortTextBox.Text);
                globalServerDescr.ipAddress = globalServerAddressTextBox.Text;

                // Create socket client
                if (ipcClient == null)
                {
                    ipcClient = new IPCClient(clientDescr, remoteServerDescr, globalServerDescr, TimeSpan.FromSeconds(60));
                }

                // Add client to connection list
                Connected = ConnectionManager.Instance.Add(ipcClient);
            }

            return Connected;
        }

        /// <summary>
        /// Disconnect from server
        /// </summary>
        public void DisconnectFromServer()
        {
            // Remove client from connection list
            ConnectionManager.Instance.Remove(ipcClient);
            ipcClient = null;
            Connected = false;
            userList = null;
            currentUserID = -1;
            currentUserPwdType = -1;
        }

        /// <summary>
        /// Check entered username and password
        /// </summary>
        void CheckUserNameAndPassword()
        {
            //connectionString = @"Data Source=black\sqlexpress;Initial Catalog=NovaTendDB;Persist Security Info=True;User ID=nova_db;Password=NovaTendDataBase";
            //////connectionString = @"Data Source=DOMENDC;Initial Catalog=NovaTendDB;Persist Security Info=True;User ID=siw;Password=NovaTendAdmin";
            //userPermissions = new int[1];
            //userPermissions[0] = 0;
            //tbUserID.Text = "pet";

            try
            {
                // Try connect to server
                if (!ConnectToServer())
                {
                    MessageBox.Show("Server is unavailable!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    logWriter.WriteToLog("Connection to the NovaTend application server --> Server is unavailable!");
                    return;
                }

                if (currentUserID != -1)
                {
                    string message = String.Format("Connection to the NovaTend application server --> Trying to connect user: {0}", enteredUserName);
                    logWriter.WriteToLog(message);

                    USER_DB_ACCESS_INFO dbAccessInfo = wdClient.GET_DB_ACCESS((uint)currentUserID, encryptor.EncryptString(tbUserPWD.Text), DateTimeToTimeInfo(currentTime), symbolBoxesList);

                    if (dbAccessInfo != null)
                    {
                        // Decrypt db access data
                        string dbServerName = encryptor.DecryptString(dbAccessInfo.dbServerName);
                        string dbName = encryptor.DecryptString(dbAccessInfo.dbName);
                        string dbUserName = encryptor.DecryptString(dbAccessInfo.dbUserName);
                        string dbPassword = encryptor.DecryptString(dbAccessInfo.dbPassword);

                        // Get connection string
                        connectionString = "Data Source = " + dbServerName +
                                           ";Initial Catalog = " + dbName +
                                           ";Persist Security Info = True;" +
                                           "User ID = " + dbUserName +
                                           ";Password = " + dbPassword +
                                           ";";

                        userPermissions = dbAccessInfo.userPermissions;

                        message = String.Format("Connection to the NovaTend application server --> User {0} successfully connected to the NovaTend application server", enteredUserName);
                        logWriter.WriteToLog(message);
                    }
                    else
                    {
                        logWriter.WriteToLog("Connection to the NovaTend application server --> Connection failed! Wrong user ID or password!");
                        MessageBox.Show("Connection failed! Wrong user ID or password!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        DisconnectFromServer();
                        connectionString = "";
                        userPermissions = null;
                    }
                }
                else
                {
                    logWriter.WriteToLog("Connection to the NovaTend application server --> Wrong user ID or password!");
                    MessageBox.Show("Wrong user ID or password!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    DisconnectFromServer();
                    connectionString = "";
                    userPermissions = null;
                }
            }
            catch
            {
                MessageBox.Show("Server communication error!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Reset user password
        /// </summary>
        /// <param name="userID">user ID</param>
        public void ResetUserPassword(int userID)
        {
            try
            {
                // Try connect to server
                if (ConnectToServer() && (userID != -1))
                {
                    uint resetCode = 0;
                    bool? resetResult = wdClient.RESET_USER_PASSWORD((uint)userID, out resetCode);

                    if (resetResult == null)
                    {
                        MessageBox.Show("Server is unavailable!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        logWriter.WriteToLog("Reset password --> Server is unavailable!");
                    }
                    else
                    {

                        // Reset user password
                        switch ((int)resetCode)
                        {
                            case CMD_RESET_USER_PASSWORD.RESPONSE_OK:
                                {
                                    logWriter.WriteToLog("Reset password --> Password successfuly reseted! Please folow the instructions that were sent to you by EMAIL(SMS)");
                                    MessageBox.Show("Password successfuly reseted! Please folow the instructions that were sent to you by EMAIL(SMS).", "Information", MessageBoxButtons.OK, MessageBoxIcon.Information);
                                    break;
                                }

                            case CMD_RESET_USER_PASSWORD.RESPONSE_BAD:
                                {
                                    logWriter.WriteToLog("Reset password --> Password was not reseted! Please try again later!");
                                    MessageBox.Show("Password was not reseted! Please try again later!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    break;
                                }

                            case CMD_RESET_USER_PASSWORD.RESET_PWD_USER_NOT_FOUND:
                                {
                                    logWriter.WriteToLog("Reset password --> Wrong user ID! The system cannot find user with that user ID");
                                    MessageBox.Show("Wrong user ID! The system cannot find user with that user ID.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    break;
                                }

                            case CMD_RESET_USER_PASSWORD.RESET_PWD_WRONG_EMAIL_ADDRESS:
                                {
                                    logWriter.WriteToLog("Reset password --> Email sending error! The system can't send password reset instructions to your email box. Your email address is wrong");
                                    MessageBox.Show("Email sending error! The system can't send password reset instructions to your email box. Your email address is wrong.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    break;
                                }

                            case CMD_RESET_USER_PASSWORD.RESET_PWD_WRONG_PHONE_NUMBER:
                                {
                                    logWriter.WriteToLog("Reset password --> SMS sending error! The system can't send password reset instructions to your phone. Your phone number is wrong");
                                    MessageBox.Show("SMS sending error! The system can't send password reset instructions to your phone. Your phone number is wrong.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    break;
                                }

                            case CMD_RESET_USER_PASSWORD.RESET_PWD_EMAIL_SEND_ERROR:
                                {
                                    logWriter.WriteToLog("Reset password --> Email sending error! The system can't send password reset instructions to your email box");
                                    MessageBox.Show("Email sending error! The system can't send password reset instructions to your email box.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    break;
                                }

                            case CMD_RESET_USER_PASSWORD.RESET_PWD_SMS_SEND_ERROR:
                                {
                                    logWriter.WriteToLog("Reset password --> SMS sending error! The system can't send password reset instructions to your phone");
                                    MessageBox.Show("SMS sending error! The system can't send password reset instructions to your phone.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    break;
                                }

                            default:
                                {
                                    logWriter.WriteToLog("Reset password --> Password was not reseted! Please try again later!");
                                    MessageBox.Show("Password was not reseted! Please try again later!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    break;
                                }
                        }

                    }
                }
                else
                {
                    logWriter.WriteToLog("Reset password --> Wrong user ID! Please check server connection and try again!");
                    MessageBox.Show("Wrong user ID! Please check server connection and try again!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch
            {
                MessageBox.Show("Server communication error!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Convert DateTime to tm
        /// </summary>
        /// <param name="dateTime">DateTime value</param>
        /// <returns>tm value</returns>
        public TIME_INFO DateTimeToTimeInfo(DateTime dateTime)
        {
            TIME_INFO timeinfo = new TIME_INFO();

            timeinfo.tm_sec = dateTime.Second;
            timeinfo.tm_min = dateTime.Minute;
            timeinfo.tm_hour = dateTime.Hour;
            timeinfo.tm_mday = dateTime.Day;
            timeinfo.tm_mon = dateTime.Month - 1;
            timeinfo.tm_year = dateTime.Year;
            timeinfo.tm_wday = (int)dateTime.DayOfWeek;
            timeinfo.tm_yday = dateTime.DayOfYear;
            timeinfo.tm_isdst = -1;

            return timeinfo;
        }

        #endregion

        #region Buttons

        /// <summary>
        /// OK Button click handler
        /// </summary>
        private void btnOK_Click(object sender, EventArgs e)
        {
            // Check entered user credentials
            CheckUserNameAndPassword();

            // Close window
            Close();
            
        }

        /// <summary>
        /// Cancel button click handler
        /// </summary>
        private void btnCancel_Click(object sender, EventArgs e)
        {
            DisconnectFromServer();
            connectionString = "";
            userPermissions = null;
            Close();
        }

        /// <summary>
        /// Reset button click
        /// </summary>
        private void resetRwdButtonLabel_Click(object sender, EventArgs e)
        {
            ResetUserPassword(currentUserID);
        }

        /// <summary>
        /// Symbol button click
        /// </summary>
        private void symbol8Button_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;
            tbUserPWD.Text = tbUserPWD.Text + btn.Text;
        }

        /// <summary>
        /// Backspace button click
        /// </summary>
        private void backSpaceButton_Click(object sender, EventArgs e)
        {
            if (tbUserPWD.Text.Length > 0)
                tbUserPWD.Text = tbUserPWD.Text.Substring(0, tbUserPWD.Text.Length - 1);
        }

        /// <summary>
        /// Refresh button click
        /// </summary>
        private void refreshButton_Click(object sender, EventArgs e)
        {
            RebuildScreen();
        }

        #endregion

        #region Controls

        /// <summary>
        /// Clear image of picture box
        /// </summary>
        /// <param name="pictureBox">picture box instance</param>
        private void ClearPictureBox(PictureBox pictureBox)
        {
            if (pictureBox.Image != null)
            {
                pictureBox.Image.Dispose();
                pictureBox.Image = null;
            }
        }

        /// <summary>
        /// Clear all 5 picture boxes
        /// </summary>
        private void ClearAllPictureBoxes()
        {
            ClearPictureBox(pictureBox1);
            ClearPictureBox(pictureBox2);
            ClearPictureBox(pictureBox3);
            ClearPictureBox(pictureBox4);
            ClearPictureBox(pictureBox5);
            ClearPictureBox(pictureBox6);
            ClearPictureBox(pictureBox7);
            ClearPictureBox(pictureBox8);
            ClearPictureBox(pictureBox9);
            ClearPictureBox(pictureBox10);
        }

        /// <summary>
        /// Set string password screen settings
        /// </summary>
        private void SetStringPasswordScreen()
        {
            if (symbolBoxesPanel.Visible)
            {
                symbolBoxesPanel.Visible = false;
                this.Width = 330;
                this.Height = 270;
                tbUserPWD.Text = "";
                tbUserPWD.PasswordChar = '*';

                GetSymbolBoxesList(-1);
                ClearAllPictureBoxes();
            }
        }

        /// <summary>
        /// Set symbol boxes password screen settings
        /// </summary>
        private void SetSymbolBoxesPasswordScreen()
        {
            ClearAllPictureBoxes();

            switch (currentUserPwdType)
            {
                case SymbolBoxesManager.ONE_SYMBOL_BOX:
                    {
                        this.Width = 555;
                        this.Height = 553;
                        tbUserPWD.Text = "";
                        tbUserPWD.PasswordChar = '\0';

                        symbol1Button.Visible = true;
                        symbol2Button.Visible = true;
                        symbol3Button.Visible = true;
                        symbol4Button.Visible = true;
                        symbol5Button.Visible = true;
                        symbol6Button.Visible = true;
                        symbol7Button.Visible = true;
                        symbol8Button.Visible = true;

                        pictureBox1.Visible = true;
                        pictureBox2.Visible = true;
                        pictureBox3.Visible = true;
                        pictureBox4.Visible = true;
                        pictureBox5.Visible = true;
                        pictureBox6.Visible = true;
                        pictureBox7.Visible = true;
                        pictureBox8.Visible = true;
                        pictureBox9.Visible = true;
                        pictureBox10.Visible = true;

                        symbol1Button.Location = new Point(25, 225);
                        symbol2Button.Location = new Point(symbol1Button.Left + symbol1Button.Width + 6, 225);
                        symbol3Button.Location = new Point(symbol2Button.Left + symbol2Button.Width + 6, 225);
                        symbol4Button.Location = new Point(symbol3Button.Left + symbol3Button.Width + 6, 225);
                        symbol5Button.Location = new Point(symbol4Button.Left + symbol4Button.Width + 6, 225);
                        symbol6Button.Location = new Point(symbol5Button.Left + symbol5Button.Width + 6, 225);
                        symbol7Button.Location = new Point(symbol6Button.Left + symbol6Button.Width + 6, 225);
                        symbol8Button.Location = new Point(symbol7Button.Left + symbol7Button.Width + 6, 225);
                        backSpaceButton.Location = new Point(symbol8Button.Left + symbol8Button.Width + 6, 225);

                        GetSymbolBoxesList(currentUserPwdType);
                        if (DrawSymbolBoxes(pictureBox1.Width))
                        {
                            pictureBox1.Image = Image.FromFile("pwdSymBox1.bmp");
                            pictureBox2.Image = Image.FromFile("pwdSymBox2.bmp");
                            pictureBox3.Image = Image.FromFile("pwdSymBox3.bmp");
                            pictureBox4.Image = Image.FromFile("pwdSymBox4.bmp");
                            pictureBox5.Image = Image.FromFile("pwdSymBox5.bmp");
                            pictureBox6.Image = Image.FromFile("pwdSymBox6.bmp");
                            pictureBox7.Image = Image.FromFile("pwdSymBox7.bmp");
                            pictureBox8.Image = Image.FromFile("pwdSymBox8.bmp");
                            pictureBox9.Image = Image.FromFile("pwdSymBox9.bmp");
                            pictureBox10.Image = Image.FromFile("pwdSymBox10.bmp");
                        }

                        break;
                    }

                case SymbolBoxesManager.TWO_SYMBOL_BOX:
                    {
                        this.Width = 555;
                        this.Height = 448;
                        tbUserPWD.Text = "";
                        tbUserPWD.PasswordChar = '\0';

                        symbol1Button.Visible = true;
                        symbol2Button.Visible = true;
                        symbol3Button.Visible = true;
                        symbol4Button.Visible = true;
                        symbol5Button.Visible = true;
                        symbol6Button.Visible = true;
                        symbol7Button.Visible = true;
                        symbol8Button.Visible = true;

                        pictureBox1.Visible = true;
                        pictureBox2.Visible = true;
                        pictureBox3.Visible = true;
                        pictureBox4.Visible = true;
                        pictureBox5.Visible = true;
                        pictureBox6.Visible = false;
                        pictureBox7.Visible = false;
                        pictureBox8.Visible = false;
                        pictureBox9.Visible = false;
                        pictureBox10.Visible = false;

                        symbol1Button.Location = new Point(25, 120);
                        symbol2Button.Location = new Point(symbol1Button.Left + symbol1Button.Width + 6, 120);
                        symbol3Button.Location = new Point(symbol2Button.Left + symbol2Button.Width + 6, 120);
                        symbol4Button.Location = new Point(symbol3Button.Left + symbol3Button.Width + 6, 120);
                        symbol5Button.Location = new Point(symbol4Button.Left + symbol4Button.Width + 6, 120);
                        symbol6Button.Location = new Point(symbol5Button.Left + symbol5Button.Width + 6, 120);
                        symbol7Button.Location = new Point(symbol6Button.Left + symbol6Button.Width + 6, 120);
                        symbol8Button.Location = new Point(symbol7Button.Left + symbol7Button.Width + 6, 120);
                        backSpaceButton.Location = new Point(symbol8Button.Left + symbol8Button.Width + 6, 120);

                        GetSymbolBoxesList(currentUserPwdType);
                        if (DrawSymbolBoxes(pictureBox1.Width))
                        {
                            pictureBox1.Image = Image.FromFile("pwdSymBox1.bmp");
                            pictureBox2.Image = Image.FromFile("pwdSymBox2.bmp");
                            pictureBox3.Image = Image.FromFile("pwdSymBox3.bmp");
                            pictureBox4.Image = Image.FromFile("pwdSymBox4.bmp");
                            pictureBox5.Image = Image.FromFile("pwdSymBox5.bmp");
                        }

                        break;
                    }
            }

            symbolBoxesPanel.Visible = true;
        }


        /// <summary>
        /// Rebuild user screen
        /// according to the password dtype
        /// </summary>
        private void RebuildScreen()
        {
            currentTime = DateTime.Now;
            string timeString = currentTime.ToString("dddd, MM/dd/yy, HH:mm:ss");
            timeLabel.Text = timeString;

            switch (currentUserPwdType)
            {
                case CASCADE_STRING_PWD:
                    {
                        SetStringPasswordScreen();
                        break;
                    }

                case ONE_SYMBOL_BOX_PWD:
                case TWO_SYMBOL_BOX_PWD:
                    {
                        SetSymbolBoxesPasswordScreen();
                        break;
                    }
            }
        }

        /// <summary>
        /// Key down handler
        /// </summary>
        private void tbUserPWD_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == System.Windows.Forms.Keys.Enter) btnOK_Click(sender, null);
            else
                if (e.KeyCode == System.Windows.Forms.Keys.Escape) btnCancel_Click(sender, null);
        }

        /// <summary>
        /// Text chaged event handler
        /// </summary>
        private void tbUserID_TextChanged(object sender, EventArgs e)
        {
            if (userList == null)
            {
                if (ConnectToServer()) GetUserList();
            }

            if (FindUserInList(tbUserID.Text) != -1)
            {
                if (GetUserDescriptor(tbUserID.Text))
                    RebuildScreen();
            }
            else
            {
                SetStringPasswordScreen();
                currentUserID = -1;
                currentUserPwdType = -1;
            }
        }

        /// <summary>
        /// Text chaged event handler
        /// </summary>
        private void serverIDTextBox_TextChanged(object sender, EventArgs e)
        {
            DisconnectFromServer();
        }
        
        #endregion
            
    }
}
