/// <summary>
///   Solution : NovaTend
///   Project : PostLogin.exe
///   Module : KeyBlocker.cs
///   Description :  implements the methods of class KeyBlocker
/// </summary>
/// 

using System;
using System.Runtime.InteropServices;
using System.Security.Principal;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;
using Microsoft.Win32;

using CommandClient;

namespace PostLogin
{

    /// <summary>
    /// Blocker of key combinations CTRL+ALT+DEL, Alt + F4, Alt+Tab, etc.
    /// </summary>
    public class KeyBlocker
    {
        #region DLL import

        // Import of API function SetWindowsHookExA
        [DllImport("user32", EntryPoint = "SetWindowsHookExA", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        private static extern int SetWindowsHookEx(int idHook, LowLevelKeyboardProcDelegate lpfn, int hMod, int dwThreadId);

        // Import of API function UnhookWindowsHookEx
        [DllImport("user32", EntryPoint = "UnhookWindowsHookEx", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        private static extern int UnhookWindowsHookEx(int hHook);

        // Definition of delegate function
        private delegate int LowLevelKeyboardProcDelegate(int nCode, int wParam, ref KBDLLHOOKSTRUCT lParam);

        // Import of API function CallNextHookEx
        [DllImport("user32", EntryPoint = "CallNextHookEx", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        private static extern int CallNextHookEx(int hHook, int nCode, int wParam, ref KBDLLHOOKSTRUCT lParam);

        // Get module handle
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern int GetModuleHandle(string lpModuleName);

        // Keyboard hooks
        private const int WH_KEYBOARD_LL = 13;

        // Import of API function LoadLibrary
        [DllImport("kernel32", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern IntPtr LoadLibrary(string lpFileName);

        // Import exit Windows
        [DllImport("user32.dll", SetLastError = true)]
        private static extern bool ExitWindowsEx(uint uFlags, uint dwReason);

        // Hook structure
        private struct KBDLLHOOKSTRUCT
        {
            public int vkCode;
            public int scanCode;
            public int flags;
            public int time;
            public int dwExtraInfo;
        }

        #endregion

        #region WD client

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

        #region Constructing

        /// <summary>
        /// Constructor
        /// </summary>
        public KeyBlocker(WDClient wdClient)
        {
            this.wdClient = wdClient;
        }
                
        #endregion

        #region Block key combos

        // Hook handler
        private static int intLLKey;

        /// <summary>
        /// Keybord hook callback function
        /// </summary>
        /// <param name="nCode">code the hook procedure uses to determine how to process the message</param>
        /// <param name="wParam">identifier of the keyboard message</param>
        /// <param name="lParam">pointer to a KBDLLHOOKSTRUCT structure</param>
        /// <returns>Error code</returns>
        private static int LowLevelKeyboardProc(int nCode, int wParam, ref KBDLLHOOKSTRUCT lParam)
        {
            if (nCode < 0)
                return CallNextHookEx(0, nCode, wParam, ref lParam);
            
            bool blnEat = false;

            switch (wParam)
            {
                case 256:
                case 257:
                case 260:
                case 261:
                    blnEat = ((lParam.vkCode == 115) && (lParam.flags == 32)) || // Alt + F4
                             ((lParam.vkCode == 9)   && (lParam.flags == 32)) || // Alt + Tab
                             ((lParam.vkCode == 27)  && (lParam.flags == 32)) || // Alt + Esc
                             ((lParam.vkCode == 27)  && (lParam.flags == 0)) ||  // Ctrl + Esc
                             ((lParam.vkCode == 91)  && (lParam.flags == 1)) ||  // Left Win
                             ((lParam.vkCode == 92)  && (lParam.flags == 1)) ||  // Right Win
                             ((lParam.vkCode == 32)  && (lParam.flags == 32));   // Alt + Space
                    break;
            }

            if (blnEat == true)
            {
                return 1;
            }
            else
            {
                return CallNextHookEx(0, nCode, wParam, ref lParam);
            }
        }

        private LowLevelKeyboardProcDelegate keyboardProc;

        /// <summary>
        /// Block key combinations
        /// </summary>
        public void BlockKeys()
        {
            Process curProcess = Process.GetCurrentProcess();
            ProcessModule curModule = curProcess.MainModule;
            int moduleHandle = GetModuleHandle(curModule.ModuleName);

            keyboardProc = new LowLevelKeyboardProcDelegate(LowLevelKeyboardProc);

            intLLKey = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, moduleHandle, 0);

            DisableCtrlAltDelete();
        }

        /// <summary>
        /// Unblock key combinations
        /// </summary>
        public void UnBlockKeys()
        {
            UnhookWindowsHookEx(intLLKey);
            EnableCTRLALTDEL();
        }
                

        #endregion

        #region CTRL + ALT + DEL

        /// <summary>
        /// Disable CTRL+ALT+DEL combo
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool DisableCtrlAltDelete()
        {
            string userName = Environment.UserDomainName + "\\" + Environment.UserName;
            bool? result = wdClient.LOCK_USER_CAD_ACTIONS(1, userName);

            return ((result == null) || (result == false)) ? false : true;
        }

        /// <summary>
        /// Enable CTRL+ALT+DEL combo
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool EnableCTRLALTDEL()
        {
            string userName = Environment.UserDomainName + "\\" + Environment.UserName;
            bool? result = wdClient.LOCK_USER_CAD_ACTIONS(0, userName);

            return ((result == null) || (result == false)) ? false : true;
        }

        #endregion

        #region Windows LOG OFF

        /// <summary>
        /// Windows LOG off
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool WindowsLogOff()
        {
            return ExitWindowsEx(0, 0);
        }

        #endregion
    }
}
