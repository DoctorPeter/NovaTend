/// <summary>
///   Solution : NovaTend
///   Project : Updater.exe
///   Module : mainForm.cs
///   Description :  main window module
/// </summary>

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.IO;
using System.ServiceProcess;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Updater
{
    /// <summary>
    /// Main window of updater program
    /// </summary>
    public partial class mainForm : Form
    {
        // Options manager
        private OptionsManager optionsManager;


        // Services list
        private List<ServiceController> serviceControllers;
        
        /// <summary>
        /// Constructor
        /// </summary>
        public mainForm()
        {
            InitializeComponent();

            optionsManager = new OptionsManager();
            serviceControllers = new List<ServiceController>();

            mainTabControl.Hide();

            mainTabControl.DrawMode = TabDrawMode.OwnerDrawFixed;
            mainTabControl.Appearance = TabAppearance.Buttons;
            mainTabControl.ItemSize = new System.Drawing.Size(0, 1);
            mainTabControl.SizeMode = TabSizeMode.Fixed;
            mainTabControl.TabStop = false;

            mainTabControl.Show();
        }

        /// <summary>
        /// Load event handler
        /// </summary>
        private void mainForm_Load(object sender, EventArgs e)
        {
            this.TopMost = true;
            
            // Check installation flag
            if (optionsManager.GetUpdateInstalledFlag())
            {
                startLabel.Text = "No new updates to install !!!";
                yesButton.Hide();
                noButton.Text = "Close";
            }
        }

        /// <summary>
        /// Get service controller
        /// </summary>
        /// <param name="serviceName">service name</param>
        /// <returns>service controller</returns>
        private ServiceController GetService(string serviceName)
        {
            try
            {
                // Call SCM and get service
                return ServiceController.GetServices().FirstOrDefault(x => x.ServiceName == serviceName); ;
            }
            catch (InvalidOperationException)
            {
                return null;
            }
        }

        /// <summary>
        /// Stop system services
        /// </summary>
        /// <returns>true - if success</returns>
        bool StopServices()
        {
            try
            {
                // Clear services list
                serviceControllers.Clear();

                // Get HOST-server service
                ServiceController srv = GetService("NovaTend_HOST_Server");
                if (srv != null) serviceControllers.Add(srv);

                // Get HUB-server service
                srv = GetService("NovaTend_HUB_Server");
                if (srv != null) serviceControllers.Add(srv);

                // Get update service
                srv = GetService("NovaTend_Update_Service");
                if (srv != null) serviceControllers.Add(srv);

                // Stop services
                foreach (ServiceController service in serviceControllers)
                {
                    if ((!(service.Status.Equals(ServiceControllerStatus.Stopped))) &&
                        (!(service.Status.Equals(ServiceControllerStatus.StopPending))))
                            service.Stop();
                }

                // Stop DESKTOP-server
                foreach (var process in Process.GetProcessesByName("z-desktopsrv-01.exe"))
                {
                    process.Kill();
                }

                return true;

            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Start system services
        /// </summary>
        /// <returns>true - if success</returns>
        bool StartServices()
        {
            try
            {
                // Start services
                foreach (ServiceController service in serviceControllers)
                {
                    if ((service.Status.Equals(ServiceControllerStatus.Stopped)) ||
                        (service.Status.Equals(ServiceControllerStatus.StopPending)))
                        service.Start();
                }

                // Start DESKTOP-server
                Process[] processes = Process.GetProcessesByName("z-desktopsrv-01.exe");
                if (processes.Length == 0)
                {
                    string desktopServerPath = optionsManager.GetDesktopServerExe();
                    ProcessStartInfo info = new ProcessStartInfo(desktopServerPath);
                    info.UseShellExecute = true;
                    info.Verb = "runas";
                    Process.Start(info);
                }

                return true;

            }
            catch
            {
                return false;
            }
        }
        
        /// <summary>
        /// NO button on click event handler
        /// </summary>
        private void noButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        /// <summary>
        /// YES button on click event handler
        /// </summary>
        private void yesButton_Click(object sender, EventArgs e)
        {
            // Clear log
            logTextBox.Clear();

            mainTabControl.SelectedTab = processPage;

            // Check installation flag
            if (!optionsManager.GetUpdateInstalledFlag())
            {
                // Get files list
                List<FileInfoContainer> sourceFilesList = optionsManager.GetFileInfoContainerList();

                if ((sourceFilesList == null) || (sourceFilesList.Count <= 0))
                {
                    logTextBox.AppendText("WARNING : There are no files to install!" + Environment.NewLine);
                }
                else
                {
                    logTextBox.AppendText("Stopping of NovaTend services..." + Environment.NewLine);

                    // Stop services
                    if (!StopServices())
                    {
                        logTextBox.AppendText("ERROR : Can't stop NovaTend services!" + Environment.NewLine);
                    }
                    else
                    {
                        Thread.Sleep(2000);
                        
                        logTextBox.AppendText("NovaTend services stopped!" + Environment.NewLine);

                        // Count progress increment
                        int progressBarIncrement = 100 / sourceFilesList.Count;
                        closeButton.Enabled = false;

                        // Install files
                        foreach (FileInfoContainer fileInfo in sourceFilesList)
                        {
                            try
                            {
                                // Prepare file names
                                string fileName = Path.GetFileName(fileInfo.fileName);
                                string downloadedFileName = optionsManager.GetUpdateDirectory() + "\\" + fileName;

                                // Check file
                                if (File.Exists(downloadedFileName))
                                {
                                    // Copy file
                                    File.Copy(downloadedFileName, fileInfo.fileName, true);
                                    File.Delete(downloadedFileName);
                                    logTextBox.AppendText("File " + fileName + " successfully installed" + Environment.NewLine);
                                }
                                else
                                {
                                    logTextBox.AppendText("WARNING : No new version of file: " + fileName + Environment.NewLine);
                                }

                                progressBar.Increment(progressBarIncrement);
                                Thread.Sleep(100);
                            }
                            catch
                            {
                                logTextBox.AppendText("ERROR : An error occurred while installing a file: " + fileInfo.fileName + Environment.NewLine);
                            }
                        }

                        closeButton.Enabled = true;
                        logTextBox.AppendText("Installation of the updates is finished" + Environment.NewLine);
                        optionsManager.SetUpdateInstalledFlag(true);
                    }

                    logTextBox.AppendText("Starting of NovaTend services..." + Environment.NewLine);

                    // Start services
                    if (!StartServices())
                    {
                        logTextBox.AppendText("ERROR : Can't start some NovaTend services!" + Environment.NewLine);
                    }
                    else
                        logTextBox.AppendText("NovaTend services started!" + Environment.NewLine);
                }
            }
            else
            {
                logTextBox.AppendText("All updates are already installed!" + Environment.NewLine);
            }
        }

        
    }
}
