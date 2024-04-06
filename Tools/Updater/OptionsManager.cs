/// <summary>
///   Solution : NovaTend
///   Project : Updater.exe
///   Module : OptionsManager.cs
///   Description : implements the methods of class OptionsManager
/// </summary>
/// 
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32;

namespace Updater
{

    #region File info container

    /// <summary>
    /// File info container structure
    /// </summary>
    class FileInfoContainer
    {
        // File name
        public string fileName {get; set;}

        // File time 
        public DateTime updateTime { get; set; }

        // File size
        public ulong fileSize { get; set; }

        // Directory flag
        public bool isDir { get; set; }

        // Constructor
        public FileInfoContainer(string fileName, DateTime updateTime, ulong fileSize, bool isDir)
        {
            this.fileName = fileName;
            this.updateTime = updateTime;
            this.fileSize = fileSize;
            this.isDir = isDir;
        }
    }


    #endregion

    /// <summary>
    /// Class : OptionsManager
    /// Description : Responsible for settings management
    /// </summary>
    class OptionsManager
    {
        #region Helper

        #region Binary

        /// <summary>
        /// Get binary value from Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <returns>binary value</returns>
        private byte[] GetBinaryValue(string regKeyName, string regValueName)
        {
            RegistryKey key = Registry.LocalMachine.OpenSubKey(regKeyName);

            if (key != null)
            {
                System.Object value = key.GetValue(regValueName);
                key.Close();

                if (value != null)
                    return (value as byte[]);
                else
                    return null;
            }
            else
                return null;
        }

        /// <summary>
        /// Set binary value to Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <param name="value">binary value</param>
        /// <returns>TRUE - if success</returns>
        public bool SetBinaryValue(string regKeyName, string regValueName, byte[] value)
        {
            RegistryKey key = Registry.LocalMachine.CreateSubKey(regKeyName);

            if (key != null)
            {
                try
                {
                    key.SetValue(regValueName, value, RegistryValueKind.Binary);
                    key.Close();

                    return true;
                }
                catch
                {
                    return false;
                }
            }
            else
                return false;
        }

        #endregion

        #region String

        /// <summary>
        /// Get string value from Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <returns>string</returns>
        private string GetStringValue(string regKeyName, string regValueName)
        {
            RegistryKey key = Registry.LocalMachine.OpenSubKey(regKeyName);

            if (key != null)
            {
                System.Object value = key.GetValue(regValueName);
                key.Close();

                if (value != null)
                    return value.ToString();
                else
                    return null;
            }
            else
                return null;
        }

        /// <summary>
        /// Set string value to Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <param name="value">string value</param>
        /// <returns>TRUE - if success</returns>
        public bool SetStringValue(string regKeyName, string regValueName, string value)
        {
            RegistryKey key = Registry.LocalMachine.CreateSubKey(regKeyName);

            if (key != null)
            {
                try
                {
                    key.SetValue(regValueName, value, RegistryValueKind.String);
                    key.Close();

                    return true;
                }
                catch
                {
                    return false;
                }
            }
            else
                return false;
        }

        #endregion

        #region Integer

        /// <summary>
        /// Get integer value from Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <returns>integer value</returns>
        public int GetIntegerValue(string regKeyName, string regValueName)
        {
            RegistryKey key = Registry.LocalMachine.OpenSubKey(regKeyName);
            if (key != null)
            {
                System.Object value = key.GetValue(regValueName);
                key.Close();

                if (value != null)
                    return Convert.ToInt32(value);
                else
                    return -1;
            }
            else
                return -1;
        }

        /// <summary>
        /// Set integer value to Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <param name="value">integer value</param>
        /// <returns>TRUE - if success</returns>
        public bool SetIntegerValue(string regKeyName, string regValueName, int value)
        {
            RegistryKey key = Registry.LocalMachine.CreateSubKey(regKeyName);
            if (key != null)
            {
                try
                {
                    key.SetValue(regValueName, value, RegistryValueKind.DWord);
                    key.Close();

                    return true;
                }
                catch
                {
                    return false;
                }
            }
            else
                return false;
        }

        #endregion

        #region Bool

        /// <summary>
        /// Get bool value from Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <returns>bool value</returns>
        public bool GetBoolValue(string regKeyName, string regValueName)
        {
            RegistryKey key = Registry.LocalMachine.OpenSubKey(regKeyName);
            if (key != null)
            {
                System.Object value = key.GetValue(regValueName);
                key.Close();

                if (value != null)
                    return Convert.ToBoolean(value);
                else
                    return false;
            }
            else
                return false;
        }

        /// <summary>
        /// Set bool value to Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <param name="value">bool value</param>
        /// <returns>TRUE - if success</returns>
        public bool SetBoolValue(string regKeyName, string regValueName, bool value)
        {
            RegistryKey key = Registry.LocalMachine.CreateSubKey(regKeyName);
            if (key != null)
            {
                try
                {
                    key.SetValue(regValueName, Convert.ToInt32(value), RegistryValueKind.DWord);
                    key.Close();

                    return true;
                }
                catch
                {
                    return false;
                }
            }
            else
                return false;
        }

        #endregion

        #endregion

        #region Update directory

        /// <summary>
        /// Get update directory
        /// </summary>
        /// <returns>update directory</returns>
        public string GetUpdateDirectory()
        {
            return GetStringValue(@"SOFTWARE\NovaTend\Update", "UPDATEDIR");
        }

        #endregion

        #region Files list

        /// <summary>
        /// Get file info container
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="fileID">file ID</param>
        /// <returns>file info container</returns>
        public FileInfoContainer GetFileInfoContainer(string regKeyName, string fileID)
        {
            string regPath = regKeyName + "\\" + fileID;

            try
            {
                string fileName = GetStringValue(regPath, "FNAME");
                string fileTime = GetStringValue(regPath, "FTIME");
                ulong fileSize = (ulong)GetIntegerValue(regPath, "FSIZE");
                bool isDir = GetBoolValue(regPath, "FDIRF");

                DateTime fileDateTime = Convert.ToDateTime(fileTime);

                FileInfoContainer fileInfo = new FileInfoContainer(fileName, fileDateTime, fileSize, isDir);
                return fileInfo;
            }
            catch
            {
                return null;
            }
        }
        
        /// <summary>
        /// Get file info container list
        /// </summary>
        /// <returns>file info container list</returns>
        public List<FileInfoContainer> GetFileInfoContainerList()
        {
            try
            {
                RegistryKey key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\NovaTend\Update");

                List<FileInfoContainer> fileList = new List<FileInfoContainer>();

                foreach (string subKeyName in key.GetSubKeyNames())
                {
                    FileInfoContainer fileInfo = GetFileInfoContainer(@"SOFTWARE\NovaTend\Update", subKeyName);
                    fileList.Add(fileInfo);
                }

                return fileList;
            }
            catch
            {
                return null;
            }
        }

        #endregion

        #region Installation

        /// <summary>
        /// Get update installed flag from windows registry
        /// </summary>
        /// <returns>update installed flag</returns>
        public bool GetUpdateInstalledFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\Update", "INSTALLED");
        }

        /// <summary>
        /// Set update installed flag from windows registry
        /// </summary>
        /// <param name="flag">installation flag</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetUpdateInstalledFlag(bool flag)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\Update", "INSTALLED", flag);
        }

        #endregion

        #region Desktop
        
        /// <summary>
        /// Get path to desktop server executeble file
        /// </summary>
        /// <returns>download directory</returns>
        public string GetDesktopServerExe()
        {
            return GetStringValue(@"SOFTWARE\NovaTend\Update\z-desktopsrv-01.exe", "FNAME");
        }

        #endregion
    }
}
