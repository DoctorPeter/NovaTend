using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading;

namespace ManagementTool
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            fmAbout aboutBox = new fmAbout();
            aboutBox.FormBorderStyle = FormBorderStyle.None;
            aboutBox.HideOKButton();
            aboutBox.Show();
            aboutBox.Refresh();
            Thread.Sleep(2000);
            aboutBox.Dispose();

            Application.Run(new fmMain());
        }
    }
}
