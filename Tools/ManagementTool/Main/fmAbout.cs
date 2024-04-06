/// <summary>
///   Solution : NovaTend
///   Project : ManagementTool.exe
///   Module : fmAbout.cs
///   Description :  about box form class
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

namespace ManagementTool
{
    public partial class fmAbout : Form
    {
        public fmAbout()
        {
            InitializeComponent();
            lblProductName.Parent = pictureBox;
            lblVersion.Parent = pictureBox;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            Close();
        }

        public void HideOKButton()
        {
            btnOK.Hide();
        }

        
    }
}
