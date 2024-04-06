/// <summary>
///   Solution : NovaTend
///   Project : SettingsManagement.dll
///   Module : SettingsManager.cs
///   Description :  implements the methods of class SettingsManager
/// </summary>

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Win32;

using Encryption;
using SystemData;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;

namespace SettingsManagement
{
    /// <summary>
    /// Class : SettingsManager
    /// Description : Responsible for settings management
    /// </summary>
    public class SettingsManager
    {
        #region Encryption

        // Encryptor instance
        private Encryptor _encryptor;

        // Encryptor property
        public Encryptor encryptor
        {
            get
            {
                if (_encryptor == null)
                {
                    _encryptor = new Encryptor();
                }

                return _encryptor;
            }

            set
            {
                _encryptor = value;
            }
        }

        #endregion

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
        public bool SetBinaryValue(string regKeyName, string regValueName, byte [] value)
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

        #region Encrypted string 

        /// <summary>
        /// Get encrypted string value from Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <returns>encrypted string value</returns>
        private byte[] GetEncryptedStringValue(string regKeyName, string regValueName)
        {
            return GetBinaryValue(regKeyName, regValueName);
        }

        /// <summary>
        /// Set encrypted string value to Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <param name="value">encrypted string value</param>
        /// <returns>TRUE - if success</returns>
        public bool SetEncryptedStringValue(string regKeyName, string regValueName, byte[] value)
        {
            return SetBinaryValue(regKeyName, regValueName, value);
        }

        /// <summary>
        /// Get encrypted string value from Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <returns>decrypted string</returns>
        private string GetDecryptedStringValue(string regKeyName, string regValueName)
        {
            RegistryKey key = Registry.LocalMachine.OpenSubKey(regKeyName);

            if (key != null)
            {
                System.Object value = key.GetValue(regValueName);
                key.Close();

                if (value != null)
                    return encryptor.DecryptString(value as byte[]);
                else
                    return String.Empty;
            }
            else
                return String.Empty;
        }

        /// <summary>
        /// Set encrypted string value to Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="regValueName">Regitry value name</param>
        /// <param name="value">decrypted string value</param>
        /// <returns>TRUE - if success</returns>
        public bool SetEncryptedStringValue(string regKeyName, string regValueName, string value)
        {
            RegistryKey key = Registry.LocalMachine.CreateSubKey(regKeyName);

            if (key != null)
            {
                try
                {
                    byte[] encData = encryptor.EncryptString(value);
                    key.SetValue(regValueName, encData, RegistryValueKind.Binary);
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
        
        #region IPC

        /// <summary>
        /// Get server description from Windows registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="serverID">Server ID</param>
        /// <returns>server description</returns>
        public SERVER_DESCRIPTION GetServerDescription(string regKeyName, string serverID)
        {
            string regPath = regKeyName + "\\" + serverID;

            try
            {
                SERVER_DESCRIPTION server = new SERVER_DESCRIPTION();
                server.serverID = (uint)GetIntegerValue(regPath, "SRVID");
                server.serverType = GetIntegerValue(regPath, "SRVTYPE");
                server.serverPriority = GetIntegerValue(regPath, "SRVPRIOR");
                server.port = (uint)GetIntegerValue(regPath, "SRVPORT");
                server.ipAddress = GetStringValue(regPath, "SRVADR");
                server.serverName = GetStringValue(regPath, "SRVNAME");

                return server;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Set server description to registry
        /// </summary>
        /// <param name="regKeyName">Registry key name</param>
        /// <param name="serverID">Server ID</param>
        /// <param name="server">Server description</param>
        /// <returns>TRUE - if success</returns>
        public bool SetServerDescription(string regKeyName, string serverID, SERVER_DESCRIPTION server)
        {
            if (server == null)
                return false;

            string regPath = regKeyName + "\\" + serverID;

            try
            {
                bool result = true;

                result = result && SetIntegerValue(regPath, "SRVID", (int)server.serverID) &&
                                   SetIntegerValue(regPath, "SRVTYPE", server.serverType) &&
                                   SetIntegerValue(regPath, "SRVPRIOR", server.serverPriority) &&
                                   SetIntegerValue(regPath, "SRVPORT", (int)server.port) &&
                                   SetStringValue(regPath, "SRVADR", server.ipAddress) &&
                                   SetStringValue(regPath, "SRVNAME", server.serverName);
                
                return result;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Get server description list
        /// </summary>
        /// <param name="regKeyName">registry path</param>
        /// <returns>server description list</returns>
        public SERVER_DESCRIPTION_LIST GetServerDescriptionList(string regKeyName)
        {
            try
            {
                RegistryKey key = Registry.LocalMachine.OpenSubKey(regKeyName);
                            
                SERVER_DESCRIPTION_LIST serverList = new SERVER_DESCRIPTION_LIST();

                foreach (string subKeyName in key.GetSubKeyNames())
                {
                    SERVER_DESCRIPTION server = new SERVER_DESCRIPTION();
                    server.serverID = (uint)GetIntegerValue(regKeyName + '\\' + subKeyName, "SRVID");
                    server.serverType = GetIntegerValue(regKeyName + '\\' + subKeyName, "SRVTYPE");
                    server.serverPriority = GetIntegerValue(regKeyName + '\\' + subKeyName, "SRVPRIOR");
                    server.port = (uint)GetIntegerValue(regKeyName + '\\' + subKeyName, "PORT");
                    server.ipAddress = GetStringValue(regKeyName + '\\' + subKeyName, "SRVADR");
                    server.serverName = GetStringValue(regKeyName + '\\' + subKeyName, "SRVNAME");

                    serverList.Add(server);
                }

                return serverList;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Set server description list
        /// </summary>
        /// <param name="regKeyName">registry path</param>
        /// <returns>TRUE - if success</returns>
        public bool SetServerDescriptionList(string regKeyName, SERVER_DESCRIPTION_LIST serverList)
        {
            try
            {
                RegistryKey key = Registry.LocalMachine.OpenSubKey(regKeyName);

                bool result = true;

                foreach (SERVER_DESCRIPTION server in serverList)
                {
                    string regPath = regKeyName + "\\" + server.serverID.ToString() + "-" + server.serverName;
                    result = result && SetIntegerValue(regPath, "SRVID", (int)server.serverID) &&
                                       SetIntegerValue(regPath, "SRVTYPE", server.serverType) &&
                                       SetIntegerValue(regPath, "SRVPRIOR", server.serverPriority) &&
                                       SetIntegerValue(regPath, "PORT", (int)server.port) &&
                                       SetStringValue(regPath, "SRVADR", server.ipAddress) &&
                                       SetStringValue(regPath, "SRVNAME", server.serverName);
                }
                
                return result;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Get GLOBAL-server description
        /// </summary>
        /// <returns>GLOBAL-server description</returns>
        public SERVER_DESCRIPTION GetGlobalServer()
        {
            return GetServerDescription(@"SOFTWARE\NovaTend\IPC", "GLOBAL");
        }

        /// <summary>
        /// Set GLOBAL-server description
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool SetGlobalServer(SERVER_DESCRIPTION server)
        {
            return SetServerDescription(@"SOFTWARE\NovaTend\IPC", "GLOBAL", server);
        }

        /// <summary>
        /// Get HOST-server description
        /// </summary>
        /// <returns>HOST-server description</returns>
        public SERVER_DESCRIPTION GetHostServer()
        {
            return GetServerDescription(@"SOFTWARE\NovaTend\IPC", "HOST");
        }

        /// <summary>
        /// Set HOST-server description
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool SetHostServer(SERVER_DESCRIPTION server)
        {
            return SetServerDescription(@"SOFTWARE\NovaTend\IPC", "HOST", server);
        }

        /// <summary>
        /// Get HUB-server description
        /// </summary>
        /// <returns>HUB-server description</returns>
        public SERVER_DESCRIPTION GetHubServer()
        {
            return GetServerDescription(@"SOFTWARE\NovaTend\IPC", "HUB");
        }

        /// <summary>
        /// Set HUB-server description
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool SetHubServer(SERVER_DESCRIPTION server)
        {
            return SetServerDescription(@"SOFTWARE\NovaTend\IPC", "HUB", server);
        }

        /// <summary>
        /// Get DESKTOP-server description
        /// </summary>
        /// <returns>DESKTOP-server description</returns>
        public SERVER_DESCRIPTION GetDesktopServer()
        {
            return GetServerDescription(@"SOFTWARE\NovaTend\IPC", "DESKTOP");
        }

        /// <summary>
        /// Set DESKTOP-server description
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool SetDesktopServer(SERVER_DESCRIPTION server)
        {
            return SetServerDescription(@"SOFTWARE\NovaTend\IPC", "DESKTOP", server);
        }

        /// <summary>
        /// Get alternative HOST-servers
        /// </summary>
        /// <returns>HOST-server description list</returns>
        public SERVER_DESCRIPTION_LIST GetAlternativeHostServers()
        {
            return GetServerDescriptionList(@"SOFTWARE\NovaTend\IPC\Alternative");
        }

        /// <summary>
        /// Set alternative HOST-servers
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool SetAlternativeHostServers(SERVER_DESCRIPTION_LIST serverList)
        {
            return SetServerDescriptionList(@"SOFTWARE\NovaTend\IPC\Alternative", serverList);
        }

        /// <summary>
        /// Get HOST-server starting flag
        /// </summary>
        /// <returns>Starting flag</returns>
        public bool GetHostServerStartingFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\IPC\HOST", "START");
        }

        /// <summary>
        /// Set HOST-server starting flag
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool SetHostServerStartingFlag(bool flag)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\IPC\HOST", "START", flag);
        }

        /// <summary>
        /// Get HUB-server starting flag
        /// </summary>
        /// <returns>Starting flag</returns>
        public bool GetHubServerStartingFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\IPC\HUB", "START");
        }

        /// <summary>
        /// Set HUB-server starting flag
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool SetHubServerStartingFlag(bool flag)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\IPC\HUB", "START", flag);
        }

        /// <summary>
        /// Get DESKTOP-server starting flag
        /// </summary>
        /// <returns>Starting flag</returns>
        public bool GetDesktopServerStartingFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\IPC\DESKTOP", "START");
        }

        /// <summary>
        /// Set DESKTOP-server starting flag
        /// </summary>
        /// <returns>TRUE - if success</returns>
        public bool SetDesktopServerStartingFlag(bool flag)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\IPC\DESKTOP", "START", flag);
        }

        #endregion

        #region Database

        /// <summary>
        /// Get database server name from windows registry
        /// </summary>
        /// <returns>DB server name</returns>
        public string GetDBServerName()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\Database", "SRV");
        }

        /// <summary>
        /// Set DB server name to windows registry
        /// </summary>
        /// <param name="dbServer">DB server name</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetDBServerName(string dbServer)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\Database", "SRV", dbServer);
        }

        /// <summary>
        /// Get database name from windows registry
        /// </summary>
        /// <returns>DB name</returns>
        public string GetDBName()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\Database", "DSN");
        }

        /// <summary>
        /// Set DB name to windows registry
        /// </summary>
        /// <param name="dsn">DB name</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetDBName(string dsn)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\Database", "DSN", dsn);
        }

        /// <summary>
        /// Get database user name from windows registry
        /// </summary>
        /// <returns>DB user name</returns>
        public string GetDBUserName()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\Database", "USR");
        }

        /// <summary>
        /// Set DB name user to windows registry
        /// </summary>
        /// <param name="user">DB user name</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetDBUserName(string user)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\Database", "USR", user);
        }

        /// <summary>
        /// Get database password from windows registry
        /// </summary>
        /// <returns>DB password</returns>
        public string GetDBPassword()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\Database", "PWD");
        }

        /// <summary>
        /// Set DB password to windows registry
        /// </summary>
        /// <param name="pwd">DB password</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetDBPassword(string pwd)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\Database", "PWD", pwd);
        }


        /// <summary>
        /// Get action for user account deleting from windows registry
        /// </summary>
        /// <returns>Action code</returns>
        public int GetUserAccountDeleteDBAction()
        {
            return GetIntegerValue(@"Software\NovaTend\Database", "UADELACT");
        }

        /// <summary>
        /// Set action for user account deleting to windows registry
        /// </summary>
        /// <param name="actionCode">action code</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetUserAccountDeleteDBAction(int actionCode)
        {
            return SetIntegerValue(@"Software\NovaTend\Database", "UADELACT", actionCode);
        }

        #endregion

        #region E-Mail
        
        /// <summary>
        /// Get E-mail host address from windows registry
        /// </summary>
        /// <returns>E-mail host</returns>
        public string GetEmailHost()
        {
            return GetStringValue(@"Software\NovaTend\EMail", "HOST");
        }

        /// <summary>
        /// Set E-mail host address to windows registry
        /// </summary>
        /// <param name="host">E-mail host</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetEmailHost(string host)
        {
            return SetStringValue(@"Software\NovaTend\EMail", "HOST", host);
        }

        /// <summary>
        /// Get E-mail server port from windows registry
        /// </summary>
        /// <returns> E-mail server port</returns>
        public int GetEmailPort()
        {
            return GetIntegerValue(@"Software\NovaTend\EMail", "PORT");
        }

        /// <summary>
        /// Set E-mail server port to windows registry
        /// </summary>
        /// <param name="port">E-mail server port</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetEmailPort(int port)
        {
            return SetIntegerValue(@"Software\NovaTend\EMail", "PORT", port);
        }

        /// <summary>
        /// Get E-mail security type from windows registry
        /// </summary>
        /// <returns> E-mail security type</returns>
        public int GetEmailSecurityType()
        {
            return GetIntegerValue(@"Software\NovaTend\EMail", "SECTYPE");
        }

        /// <summary>
        /// Set E-mail security type to windows registry
        /// </summary>
        /// <param name="securityType">E-mail security type</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetEmailSecurityType(int securityType)
        {
            return SetIntegerValue(@"Software\NovaTend\EMail", "SECTYPE", securityType);
        }

        /// <summary>
        /// Get E-mail authentication flag from windows registry
        /// </summary>
        /// <returns> E-mail authentication flag</returns>
        public bool GetEmailAuthFlag()
        {
            return GetBoolValue(@"Software\NovaTend\EMail", "AUTH");
        }

        /// <summary>
        /// Set E-mail authentication flag to windows registry
        /// </summary>
        /// <param name="auth">E-mail authentication flag</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetEmailAuthFlag(bool auth)
        {
            return SetBoolValue(@"Software\NovaTend\EMail", "AUTH", auth);
        }

        /// <summary>
        /// Get E-Mail login from windows registry
        /// </summary>
        /// <returns>E-mail login</returns>
        public string GetEmailLogin()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\EMail", "LOGIN");
        }

        /// <summary>
        /// Set E-Mail login to windows registry
        /// </summary>
        /// <param name="login">E-mail login</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetEmailLogin(string login)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\EMail", "LOGIN", login);
        }

        /// <summary>
        /// Get E-Mail password from windows registry
        /// </summary>
        /// <returns>E-mail password</returns>
        public string GetEmailPassword()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\EMail", "PASSWORD");
        }

        /// <summary>
        /// Set E-Mail password to windows registry
        /// </summary>
        /// <param name="login">E-mail password</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetEmailPassword(string password)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\EMail", "PASSWORD", password);
        }

        /// <summary>
        /// Get E-Mail sender from windows registry
        /// </summary>
        /// <returns>E-mail sender</returns>
        public string GetEmailSender()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\EMail", "SENDER");
        }

        /// <summary>
        /// Set E-Mail sender to windows registry
        /// </summary>
        /// <param name="login">E-mail sender</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetEmailSender(string sender)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\EMail", "SENDER", sender);
        }

        /// <summary>
        /// Get E-Mail recipient from windows registry
        /// </summary>
        /// <returns>E-mail recipient</returns>
        public string GetEmailRecipient()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\EMail", "RECIPIENT");
        }

        /// <summary>
        /// Set E-Mail recipient to windows registry
        /// </summary>
        /// <param name="login">E-mail recipient</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetEmailRecipient(string recipient)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\EMail", "RECIPIENT", recipient);
        }

        #endregion

        #region Google Voice

        /// <summary>
        /// Get google voice login from windows registry
        /// </summary>
        /// <returns>Google voice login</returns>
        public string GetGoogleVoiceLogin()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\SMS", "LOGIN");
        }

        /// <summary>
        /// Set google voice login to windows registry
        /// </summary>
        /// <param name="login">Google voice login</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetGoogleVoiceLogin(string login)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\SMS", "LOGIN", login);
        }

        /// <summary>
        /// Get google voice password from windows registry
        /// </summary>
        /// <returns>Google voice password</returns>
        public string GetGoogleVoicePassword()
        {
            return GetDecryptedStringValue(@"Software\NovaTend\SMS", "PWD");
        }

        /// <summary>
        /// Set Google voice password to windows registry
        /// </summary>
        /// <param name="login">Google Voice password</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetGoogleVoicePassword(string password)
        {
            return SetEncryptedStringValue(@"Software\NovaTend\SMS", "PWD", password);
        }
        
        #endregion

        #region LOG

        /// <summary>
        /// Get LOG-files encription flag from windows registry
        /// </summary>
        /// <returns> LOG-files encription flag</returns>
        public bool GetLogEncFlag()
        {
            return GetBoolValue(@"Software\NovaTend\LOG", "ENC");
        }

        /// <summary>
        /// Set LOG-files encription flag to windows registry
        /// </summary>
        /// <param name="auth">LOG-files encription flag</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetLogEncFlag(bool enc)
        {
            return SetBoolValue(@"Software\NovaTend\LOG", "ENC", enc);
        }

        /// <summary>
        /// Get LOG-files e-mail sending flag from windows registry
        /// </summary>
        /// <returns> LOG-files e-mail sending flag</returns>
        public bool GetLogEmailFlag()
        {
            return GetBoolValue(@"Software\NovaTend\LOG", "EMAIL");
        }

        /// <summary>
        /// Set LOG-files e-mail sending flag to windows registry
        /// </summary>
        /// <param name="eMail">LOG-files e-mail sending flag</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetLogEmailFlag(bool eMail)
        {
            return SetBoolValue(@"Software\NovaTend\LOG", "EMAIL", eMail);
        }
        
        /// <summary>
        /// Get LOG-file fixed size flag from windows registry
        /// </summary>
        /// <returns>LOG-file fixed size flag</returns>
        public bool GetLogFixedSizeFlag()
        {
            return GetBoolValue(@"Software\NovaTend\LOG", "FIXED");
        }

        /// <summary>
        /// Set LOG-file fixed size flag to windows registry
        /// </summary>
        /// <param name="fixedFlag">LOG -file fixed size flag</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetLogFixedSizeFlag(bool fixedFlag)
        {
            return SetBoolValue(@"Software\NovaTend\LOG", "FIXED", fixedFlag);
        }

        /// <summary>
        /// Get LOG-file fixed size value from windows registry
        /// </summary>
        /// <returns>LOG-file fixed size value</returns>
        public int GetLogFixedSizeValue()
        {
            return GetIntegerValue(@"Software\NovaTend\LOG", "FIXED_SIZE");
        }

        /// <summary>
        /// Set LOG-file fixed size value to windows registry
        /// </summary>
        /// <param name="fixedSize">LOG-file fixed size value</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetLogFixedSizeValue(int fixedSize)
        {
            return SetIntegerValue(@"Software\NovaTend\LOG", "FIXED_SIZE", fixedSize);
        }

        /// <summary>
        /// Get LOG-files store path from windows registry
        /// </summary>
        /// <returns>LOG-files store path</returns>
        public string GetLogPath()
        {
            return GetStringValue(@"Software\NovaTend\LOG", "LOG_PATH");
        }

        /// <summary>
        /// Set LOG-files store path from windows registry
        /// </summary>
        /// <param name="logPath">LOG-files store path</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetLogPath(string logPath)
        {
            return SetStringValue(@"Software\NovaTend\LOG", "LOG_PATH", logPath);
        }


        #endregion

        #region Synchronization

        /// <summary>
        /// Get periodic user accounts synchronization on/off flag
        /// </summary>
        /// <returns>Sync flag</returns>
        public bool GetPeriodicSyncOnOffFlag()
        {
            return GetBoolValue(@"Software\NovaTend\Sync", "PERIODON");
        }

        /// <summary>
        /// Set periodic user accounts synchronization on/off flag
        /// </summary>
        /// <param name="syncFlag">sync flag</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetPeriodicSyncOnOffFlag(bool syncFlag)
        {
            return SetBoolValue(@"Software\NovaTend\Sync", "PERIODON", syncFlag);
        }

        /// <summary>
        /// Get logon user accounts synchronization on/off flag
        /// </summary>
        /// <returns>Sync flag</returns>
        public bool GetLogonSyncOnOffFlag()
        {
            return GetBoolValue(@"Software\NovaTend\Sync", "LOGON");
        }

        /// <summary>
        /// Set logon user accounts synchronization on/off flag
        /// </summary>
        /// <param name="syncFlag">sync flag</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetLogonSyncOnOffFlag(bool syncFlag)
        {
            return SetBoolValue(@"Software\NovaTend\Sync", "LOGON", syncFlag);
        }

        /// <summary>
        /// Get synchronization period
        /// </summary>
        /// <returns>Period code</returns>
        public int GetSyncPeriod()
        {
            return GetIntegerValue(@"Software\NovaTend\Sync", "PERIOD");
        }

        /// <summary>
        /// Set synchronization period
        /// </summary>
        /// <param name="period">period code</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetSyncPeriod(int period)
        {
            return SetIntegerValue(@"Software\NovaTend\Sync", "PERIOD", period);
        }

        /// <summary>
        /// Get last sync time
        /// </summary>
        /// <returns>Last sync time</returns>
        public string GetLastSyncTime()
        {
            return GetStringValue(@"Software\NovaTend\Sync", "LASTSYNC");
        }

        /// <summary>
        /// Set last sync time
        /// </summary>
        /// <param name="lastSync">Last sync time string</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetLastSyncTime(string lastSync)
        {
            return SetStringValue(@"Software\NovaTend\Sync", "LASTSYNC", lastSync);
        }

        #endregion

        #region Post login

        /// <summary>
        /// Get post login process user ID from windows registry
        /// </summary>
        /// <returns>user ID</returns>
        public int GetPostLoginUserID()
        {
            return GetIntegerValue(@"SOFTWARE\NovaTend\PostLogin", "LGDUID");
        }

        /// <summary>
        /// Set post login process user ID to windows registry
        /// </summary>
        /// <param name="userID">user ID</param>
        /// <returns>true, if successful, false - otherwise.</returns>
        public bool SetPostLoginUserID(int userID)
        {
            return SetIntegerValue(@"SOFTWARE\NovaTend\PostLogin", "LGDUID", userID);
        }

        /// <summary>
        /// Get post login process file path
        /// </summary>
        /// <returns>Post login process file path</returns>
        public string GetPostLoginProcessPath()
        {
            return GetDecryptedStringValue(@"SOFTWARE\NovaTend\PostLogin", "PSTLGN");
        }

        /// <summary>
        /// Set post login process file path
        /// </summary>
        /// <param name="postLoginPath">Post login process file path</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetPostLoginProcessPath(string postLoginPath)
        {
            return SetEncryptedStringValue(@"SOFTWARE\NovaTend\PostLogin", "PSTLGN", postLoginPath);
        }

        /// <summary>
        /// Get post login process periodic flag
        /// </summary>
        /// <returns>Post login process periodic flag</returns>
        public bool GetPostLoginPeriodicFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\PostLogin", "PERIODIC");
        }

        /// <summary>
        /// Set post login process periodic flag
        /// </summary>
        /// <param name="periodic">Post login process periodic flag</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetPostLoginPeriodicFlag(bool periodic)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\PostLogin", "PERIODIC", periodic);
        }

        /// <summary>
        /// Get post login process period
        /// </summary>
        /// <returns>Post login process period</returns>
        public int GetPostLoginPeriod()
        {
            return GetIntegerValue(@"SOFTWARE\NovaTend\PostLogin", "PERIOD");
        }

        /// <summary>
        /// Set post login process period
        /// </summary>
        /// <param name="periodic">Post login process period</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetPostLoginPeriod(int period)
        {
            return SetIntegerValue(@"SOFTWARE\NovaTend\PostLogin", "PERIOD", period);
        }

        #endregion

        #region Programs control

        /// <summary>
        /// Get programs control enable flag
        /// </summary>
        /// <returns>programs control enable flag</returns>
        public bool GetProgramsControlFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\ProgramControl", "PRGCTRLON");
        }

        /// <summary>
        /// Set programs control enable flag
        /// </summary>
        /// <param name="flag">programs control enable flag</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetProgramsControlFlag(bool flag)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\ProgramControl", "PRGCTRLON", flag);
        }

        #endregion

        #region Commands history

        /// <summary>
        /// Get command history file path
        /// </summary>
        /// <returns>Post login process file path</returns>
        public string GetCommandHistoryPath()
        {
            return GetDecryptedStringValue(@"SOFTWARE\NovaTend\CommandHistory", "HUBHIST");
        }

        /// <summary>
        /// Set command history file path
        /// </summary>
        /// <param name="dbPath">database file path</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetCommandHistoryPath(string dbPath)
        {
            return SetEncryptedStringValue(@"SOFTWARE\NovaTend\CommandHistory", "HUBHIST", dbPath);
        }

        /// <summary>
        /// Get command historian process periodic flag
        /// </summary>
        /// <returns>Command historian process periodic flag</returns>
        public bool GetCommandHistorianPeriodicFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "PERIODIC");
        }

        /// <summary>
        /// Set command historian process periodic flag
        /// </summary>
        /// <param name="periodic">command historian process periodic flag</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetCommandHistorianPeriodicFlag(bool periodic)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "PERIODIC", periodic);
        }

        /// <summary>
        /// Get command historian process period
        /// </summary>
        /// <returns>command historian process period</returns>
        public int GetCommandHistorianPeriod()
        {
            return GetIntegerValue(@"SOFTWARE\NovaTend\CommandHistory", "PERIOD");
        }

        /// <summary>
        /// Set command historian process period
        /// </summary>
        /// <param name="periodic">command historian process period</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetCommandHistorianPeriod(int period)
        {
            return SetIntegerValue(@"SOFTWARE\NovaTend\CommandHistory", "PERIOD", period);
        }

        /// <summary>
        /// Get user enviroment command flag
        /// </summary>
        /// <returns>run command flag</returns>
        public bool GetUserEnvironmentCommandFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "USERENV");
        }

        /// <summary>
        /// Set user enviroment command flag
        /// </summary>
        /// <param name="flag">run command flag</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetUserEnvironmentCommandFlag(bool flag)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "USERENV", flag);
        }

        /// <summary>
        /// Get logged user name command flag
        /// </summary>
        /// <returns>run command flag</returns>
        public bool GetLoggedUserNameCommandFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "USRNAME");
        }

        /// <summary>
        /// Set logged user name command flag
        /// </summary>
        /// <param name="flag">run command flag</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetLoggedUserNameCommandFlag(bool flag)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "USRNAME", flag);
        }

        /// <summary>
        /// Get screenshot command flag
        /// </summary>
        /// <returns>run command flag</returns>
        public bool GetScreenshotCommandFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "SCRSHT");
        }

        /// <summary>
        /// Set screenshot command flag
        /// </summary>
        /// <param name="flag">run command flag</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetScreenshotCommandFlag(bool flag)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "SCRSHT", flag);
        }

        /// <summary>
        /// Get snapshot command flag
        /// </summary>
        /// <returns>run command flag</returns>
        public bool GetCamSnapshotCommandFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "SNPSHT");
        }

        /// <summary>
        /// Set snapshot command flag
        /// </summary>
        /// <param name="flag">run command flag</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetCamSnapshotCommandFlag(bool flag)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\CommandHistory", "SNPSHT", flag);
        }

        #endregion

        #region File transfer

        /// <summary>
        /// Get upload directory
        /// </summary>
        /// <returns>upload directory</returns>
        public string GetUploadDirectory()
        {
            return GetStringValue(@"SOFTWARE\NovaTend\Files", "UPLOADDIR");
        }

        /// <summary>
        /// Set upload directory
        /// </summary>
        /// <param name="dir">upload directory</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetUploadDirectory(string dir)
        {
            return SetStringValue(@"SOFTWARE\NovaTend\Files", "UPLOADDIR", dir);
        }

        /// <summary>
        /// Get download directory
        /// </summary>
        /// <returns>download directory</returns>
        public string GetDownloadDirectory()
        {
            return GetStringValue(@"SOFTWARE\NovaTend\Files", "DOWNLOADDIR");
        }

        /// <summary>
        /// Set download directory
        /// </summary>
        /// <param name="dir">download directory</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetDownloadDirectory(string dir)
        {
            return SetStringValue(@"SOFTWARE\NovaTend\Files", "DOWNLOADDIR", dir);
        }

        /// <summary>
        /// Get temp directory
        /// </summary>
        /// <returns>temp directory</returns>
        public string GetTempDirectory()
        {
            return GetStringValue(@"SOFTWARE\NovaTend\Files", "TEMPDIR");
        }

        /// <summary>
        /// Set temp directory
        /// </summary>
        /// <param name="dir">temp directory</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetTempDirectory(string dir)
        {
            return SetStringValue(@"SOFTWARE\NovaTend\Files", "TEMPDIR", dir);
        }

        #endregion

        #region Update settings

        /// <summary>
        /// Get update directory path
        /// </summary>
        /// <returns>update directory path</returns>
        public string GetUpdateDirPath()
        {
            return GetStringValue(@"SOFTWARE\NovaTend\Update", "UPDATEDIR");
        }

        /// <summary>
        /// Set update directory path
        /// </summary>
        /// <param name="upPath">update directory path</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetUpdateDirPath(string upPath)
        {
            return SetStringValue(@"SOFTWARE\NovaTend\Update", "UPDATEDIR", upPath);
        }

        /// <summary>
        /// Get updater file path
        /// </summary>
        /// <returns>Updater file path</returns>
        public string GetUpdaterPath()
        {
            return GetStringValue(@"SOFTWARE\NovaTend\Update", "UPPATH");
        }

        /// <summary>
        /// Set updater file path
        /// </summary>
        /// <param name="upPath">updater file path</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetUpdaterPath(string upPath)
        {
            return SetStringValue(@"SOFTWARE\NovaTend\Update", "UPPATH", upPath);
        }

        /// <summary>
        /// Get update process periodic flag
        /// </summary>
        /// <returns>update process periodic flag</returns>
        public bool GetUpdatePeriodicFlag()
        {
            return GetBoolValue(@"SOFTWARE\NovaTend\Update", "PERIODIC");
        }

        /// <summary>
        /// Set update process periodic flag
        /// </summary>
        /// <param name="periodic">update process periodic flag</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetUpdatePeriodicFlag(bool periodic)
        {
            return SetBoolValue(@"SOFTWARE\NovaTend\Update", "PERIODIC", periodic);
        }

        /// <summary>
        /// Get update process period
        /// </summary>
        /// <returns>update process period</returns>
        public int GetUpdatePeriod()
        {
            return GetIntegerValue(@"SOFTWARE\NovaTend\Update", "PERIOD");
        }

        /// <summary>
        /// Set update process period
        /// </summary>
        /// <param name="periodic">update process period</param>
        /// <returns>true, if successful, false - otherwise</returns>
        public bool SetUpdatePeriod(int period)
        {
            return SetIntegerValue(@"SOFTWARE\NovaTend\Update", "PERIOD", period);
        }

        #endregion
    }
}
