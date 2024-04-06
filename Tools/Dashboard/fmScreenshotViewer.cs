/// <summary>
///   Solution : NovaTend
///   Project : Dashboard.exe
///   Module : fmScreenshotViewer.cs
///   Description :  screenshot viewer UI module
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

namespace Dashboard
{
    /// <summary>
    /// Screenshot viewer window class 
    /// </summary>
    public partial class fmScreenshotViewer : Form
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public fmScreenshotViewer(byte [] imageBuffer)
        {
            InitializeComponent();

            imgSizeModeComboBox.SelectedIndex = 4;

            if (imageBuffer != null)
            {
                screenshotPictureBox.Image = new Bitmap(new MemoryStream(imageBuffer));
            }
        }

        /// <summary>
        /// Button OK click
        /// </summary>
        private void btnClose_Click(object sender, EventArgs e)
        {
            Close();
        }

        /// <summary>
        /// Save button click
        /// </summary>
        private void btnSave_Click(object sender, EventArgs e)
        {
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                screenshotPictureBox.Image.Save(saveFileDialog.FileName, System.Drawing.Imaging.ImageFormat.Bmp);
            }
        }

        /// <summary>
        /// Selected item changed event handler
        /// </summary>
        private void imgSizeModeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (imgSizeModeComboBox.SelectedIndex)
            {
                case 0 :
                    {
                        screenshotPictureBox.SizeMode = PictureBoxSizeMode.Normal;
                        break;
                    }

                case 1 :
                    {
                        screenshotPictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
                        break;
                    }

                case 2 :
                    {
                        screenshotPictureBox.SizeMode = PictureBoxSizeMode.AutoSize;
                        break;
                    }

                case 3 :
                    {
                        screenshotPictureBox.SizeMode = PictureBoxSizeMode.CenterImage;
                        break;
                    }

                case 4:
                    {
                        screenshotPictureBox.SizeMode = PictureBoxSizeMode.Zoom;
                        break;
                    }
            }

            screenshotPictureBox.Refresh();
        }


    }
}
