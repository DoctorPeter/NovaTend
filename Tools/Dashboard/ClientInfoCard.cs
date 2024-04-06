/// <summary>
///   Solution : NovaTend
///   Project : Dashboard.exe
///   Module : ClientInfoCard.cs
///   Description :  User control. Resposible for showing of client machine information
/// </summary>
/// 

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Dashboard
{
    /// <summary>
    /// User control. Resposible for showing of client machine information
    /// </summary>
    public partial class ClientInfoCard : UserControl
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public ClientInfoCard()
        {
            InitializeComponent();
        }

        // Client ID
        public int clientID { get; set; }

        // Checked property
        public bool Checked
        {
            get
            {
                return clientIDCheckBox.Checked;
            }
        }
        /// <summary>
        /// Set information about client machine
        /// </summary>
        /// <param name="clientID">client ID</param>
        /// <param name="computerName">computer name</param>
        /// <param name="ipAddress">IP</param>
        public void SetComputerInfo(int clientID, string computerName, string ipAddress)
        {
            this.clientID = clientID;
            clientIDCheckBox.Text = "Client ID: " + clientID.ToString() + "   " + "Computer name: " + computerName + "   " + "IP: " + ipAddress;
        }

        /// <summary>
        /// Set user info
        /// </summary>
        /// <param name="userName">user name</param>
        /// <param name="fullUserName">full user name</param>
        /// <param name="sysUserName">system user name</param>
        /// <param name="authSysName">authentication system name</param>
        /// <param name="userDownTime">user downtime</param>
        public void SetUserInfo(string userName, string fullUserName, string sysUserName, string authSysName, int userDownTime)
        {
            userNameLabel.Text = "User name: " + userName;
            fullUserNameLabel.Text = "Full user name: " + fullUserName;
            sysUserNameLabel.Text = "System user name: " + sysUserName;
            authSystemNameLabel.Text = "Authentication system name: " + authSysName;
            userDowntimeLabel.Text = "User downtime: " + (TimeSpan.FromSeconds(userDownTime)).ToString();
        }

        /// <summary>
        /// Set software info
        /// </summary>
        /// <param name="foregroundWindow">foreground window name</param>
        /// <param name="programs">programs list</param>
        public void SetSoftwareInfo(string foregroundWindow, string [] programs)
        {
            softwareInfoTextBox.Text = "Foreground window: " + foregroundWindow + Environment.NewLine + 
                                        Environment.NewLine + "List of programs:" + Environment.NewLine;

            for (int i = 0; i < programs.Length; i++)
                softwareInfoTextBox.Text = softwareInfoTextBox.Text + "   " + (i + 1).ToString() + ". " + programs[i] + Environment.NewLine;
        }

        /// <summary>
        /// Set hardware info
        /// </summary>
        /// <param name="OSversion">OS version</param>
        /// <param name="CPUname">CPU name</param>
        /// <param name="amountOfPhysicalMemory">Total RAM</param>
        /// <param name="amountOfUsedPhysicalMemory">Used RAM</param>
        /// <param name="amountOfVirtualMemory">Total virtual memory</param>
        /// <param name="amountOfUsedVirtualMemory">Used virtual memory</param>
        /// <param name="motherboardManufacturerName">Motherboard manufacturer</param>
        /// <param name="motherboarProductName">Motherboard version</param>
        /// <param name="BIOSManufacturerName">BIOS manufacturer</param>
        /// <param name="BIOSVersionName">BIOS version</param>
        /// <param name="chipsetName">Chipset name</param>
        /// <param name="videoAdapterName">Video adapter name</param>
        /// <param name="monitorName">Monitor name</param>
        /// <param name="amountOfVideoMemory">Video RAM</param>
        public void SetHardwareInfo(string OSversion, 
                                    string CPUname, 
                                    long amountOfPhysicalMemory, 
                                    long amountOfUsedPhysicalMemory, 
                                    long amountOfVirtualMemory, 
                                    long amountOfUsedVirtualMemory, 
                                    string motherboardManufacturerName, 
                                    string motherboarProductName, 
                                    string BIOSManufacturerName, 
                                    string BIOSVersionName, 
                                    string chipsetName, 
                                    string videoAdapterName, 
                                    string monitorName, 
                                    long amountOfVideoMemory)
        {
            hardwareInfoTextBox.Text = "OS version: " + OSversion + Environment.NewLine +
                                       "CPU name: " + CPUname + Environment.NewLine +
                                        "Amount of physical memory: " + amountOfPhysicalMemory.ToString() + " MB" + Environment.NewLine +
                                        "Amount of used physical memory: " + amountOfUsedPhysicalMemory.ToString() + " MB" + Environment.NewLine +
                                        "Amount of virtual memory: " + amountOfVirtualMemory.ToString() + " MB" + Environment.NewLine +
                                        "Amount of used virtual memory: " + amountOfUsedVirtualMemory.ToString() + " MB" + Environment.NewLine +
                                        "Motherboard manufacturer name: " + motherboardManufacturerName + Environment.NewLine +
                                        "Motherboard product name: " + motherboarProductName + Environment.NewLine +
                                        "BIOS manufacturer name: " + BIOSManufacturerName + Environment.NewLine +
                                        "BIOS version name: " + BIOSVersionName + Environment.NewLine +
                                        "Chipset name: " + chipsetName + Environment.NewLine +
                                        "Video adapter name: " + videoAdapterName + Environment.NewLine +
                                        "Video display name: " + monitorName + Environment.NewLine +
                                        "Amount of video memory: " + amountOfVideoMemory.ToString() + " MB";
        }
    }
}
