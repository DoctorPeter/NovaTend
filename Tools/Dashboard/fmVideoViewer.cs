/// <summary>
///   Solution : NovaTend
///   Project : Dashboard.exe
///   Module : fmScreenshotViewer.cs
///   Description :  video stream viewer UI module
/// </summary>
/// 
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Threading;

using Commands;
using CommandClient;

namespace Dashboard
{
    /// <summary>
    /// Video viewer window class 
    /// </summary>
    public partial class fmVideoViewer : Form
    {
        #region Connection

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

        #endregion

        #region Parameters

        // Receiver ID
        public uint receiverID { set; get; }

        // Command code
        public int commandCode { set; get; }

        // Current user ID
        public int currentUserID { set; get; }

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

        // Video thread object
        private Thread videoThread;


        /// <summary>
        /// Video thread function
        /// </summary>
        private void videoThreadFunction()
        {
            while (!threadDone)
            {
                try
                {
                    byte[] imageBytes = null;

                    switch (commandCode)
                    {
                        case 0:
                            {
                                imageBytes = wdClient.GET_CLIENT_SCREEN_SHOT((uint)currentUserID, receiverID);
                                break;
                            }

                        case 1:
                            {
                                imageBytes = wdClient.GET_CLIENT_CAM_SNAPSHOT((uint)currentUserID, receiverID);
                                break;
                            }
                    }

                    if ((imageBytes != null) && (imageBytes.Length > 0))
                    {
                        if (InvokeRequired)
                        {
                            Invoke(new MethodInvoker(delegate
                            {
                                pictureBox.Image = new Bitmap(new MemoryStream(imageBytes));
                                pictureBox.SizeMode = PictureBoxSizeMode.Zoom;
                                pictureBox.Refresh();
                            }));
                        }
                        else
                        {
                            pictureBox.Image = new Bitmap(new MemoryStream(imageBytes));
                            pictureBox.SizeMode = PictureBoxSizeMode.Zoom;
                            pictureBox.Refresh();
                        }

                    }
                }
                catch (Exception ex)
                {
                    //----
                }

                Thread.Sleep(1000);
            }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Constructor
        /// </summary>
        public fmVideoViewer(WDClient wdClient, uint receiverID, int currentUserID, int commandCode)
        {
            InitializeComponent();

            this.wdClient = wdClient;
            this.receiverID = receiverID;
            this.commandCode = commandCode;
            this.currentUserID = currentUserID;

            threadDone = false;
            videoThread = new Thread(this.videoThreadFunction);
            videoThread.Start();
        }

        #endregion
               
        #region Buttons

        /// <summary>
        /// Button OK click
        /// </summary>
        private void btnClose_Click(object sender, EventArgs e)
        {
            threadDone = true;
            videoThread.Join();
            Close();
        }

        #endregion

    }
}
