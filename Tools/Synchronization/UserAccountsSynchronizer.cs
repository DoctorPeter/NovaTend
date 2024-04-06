/// <summary>
///   Solution : NovaTend
///   Project : Synchronization.dll
///   Module : UserAccountsSynchronizer.cs
///   Description :  implements the methods of class UserAccountsSynchronizer
/// </summary>
 
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using System.DirectoryServices.AccountManagement;

using ADAccountManagement;
using Encryption;
using DataModule;

namespace Synchronization
{
    /// <summary>
    /// Class for user accounts synchronization
    /// </summary>
    public class UserAccountsSynchronizer
    {
        #region Constants

        // Authentication systems types
        public const int UAC_AD = 1;

        // Actions types
        public const int ACTION_DO_NOTHING   = 1;
        public const int ACTION_DO_DISABLE   = 2;
        public const int ACTION_DO_DELETE    = 3;
        public const int ACTION_DO_INSERT    = 4;
        public const int ACTION_DO_UPDATE    = 5;

        // Operation types
        public const int UA_SYNC_DELETE = 1;
        public const int UA_SYNC_INSERT = 2;
        public const int UA_SYNC_UPDATE = 3;

        #endregion

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

        #region Database

        // Database manager instance
        private DataBaseManager dbManager;

        #endregion

        #region Constructor

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="dbManager">Database manager instance</param>
        public UserAccountsSynchronizer(DataBaseManager dbManager)
        {
            this.dbManager = dbManager;
        }

        #endregion

        #region Active directory

        #region Active directory manager

        /// <summary>
        /// Parse settings string and create AD account manager instance
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <returns>AD account manager instance</returns>
        private ADAccountManager GetADAccountManager(string settingsString)
        {
            ADSettingsParser adSettingsParser = new ADSettingsParser();

            // Get AD service username and password (it could be admin)
            string serviceUserName = adSettingsParser.GetServiceUserName(settingsString);
            string serviceUserPassword = adSettingsParser.GetServiceUserPassword(settingsString);

            // Get OU settings for users accounts
            string defaultOU = adSettingsParser.GetDefaultOU(settingsString);
            string defaultRootOU = adSettingsParser.GetDefaultRootOU(settingsString);

            // Get domain name
            string domainName = adSettingsParser.GetDomainName(settingsString);

            // Return AD account manager instance
            return new ADAccountManager(domainName, defaultOU, defaultRootOU, serviceUserName, serviceUserPassword);
        }

        #endregion

        #region User accounts

        /// <summary>
        /// Synchronize user accounts on delete 
        /// user account record from database
        /// </summary>
        /// <param name="userName">user name</param>
        /// <param name="action">action on delete</param>
        /// <param name="settingsString">settings string</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccountOnDelete(string userName, int action, string settingsString)
        {
            // Check action
            switch (action)
            {
                case ACTION_DO_DELETE:
                    {
                        // Delete user from AD
                            
                        // Get AD manager
                        ADAccountManager adAccountManager = GetADAccountManager(settingsString);

                        // Check input user
                        if (adAccountManager.IsUserExisiting(userName))
                            return adAccountManager.DeleteUser(userName);
                        else
                            return true;
                    }
                case ACTION_DO_DISABLE:
                    {
                        // Disable AD user account

                        // Get AD manager
                        ADAccountManager adAccountManager = GetADAccountManager(settingsString);

                        return (!adAccountManager.DisableUserAccount(userName));
                    }

                default: return false;
            }
         }
            

        /// <summary>
        /// Synchronize user accounts on insert 
        /// new user account record to database
        /// </summary>
        /// <param name="userName">user name</param>
        /// <param name="userPassword">password</param>
        /// <param name="action">action on insert</param>
        /// <param name="settingsString">settings string</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccountOnInsert(string userName, string userPassword, int action, string settingsString)
        {
            // Check action
            if (action == ACTION_DO_NOTHING)
                return true;

                        
            // Check action and input user
            if (action == ACTION_DO_INSERT)
            {
                ADAccountManager adAccountManager = GetADAccountManager(settingsString);

                // Create new AD user
                if (!adAccountManager.IsUserExisiting(userName))
                    return (adAccountManager.CreateNewUser(adAccountManager.sDefaultOU, userName, userPassword, userName, userName) != null);
                else
                {
                    if (adAccountManager.EnableUserAccount(userName))
                    {
                        return adAccountManager.SetUserPassword(userName, userPassword);
                    }
                    else
                        return false;
                }
            }
            else
                return false;
        }
        
        /// <summary>
        /// Synchronize user accounts on update 
        /// user account record in database
        /// </summary>
        /// <param name="userName">user name </param>
        /// <param name="userPassword">password</param>
        /// <param name="newUserName">new user name</param>
        /// <param name="newUserPassword">new user password</param>
        /// <param name="action">action</param>
        /// <param name="settingsString">settings string</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccountOnUpdate(string userName, string userPassword, string newUserName, string newUserPassword, int action, string settingsString)
        {
            // Check action
            if (action == ACTION_DO_NOTHING)
                return true;
                      

            // Check action and input user
            if (action == ACTION_DO_UPDATE)
            {
                ADAccountManager adAccountManager = GetADAccountManager(settingsString);

                if (adAccountManager.IsUserExisiting(userName))
                {
                    if (adAccountManager.EnableUserAccount(userName))
                    {
                        bool result = true;

                        // Change user name
                        if (userName != newUserName)
                        {
                            result = adAccountManager.ChangeUserName(userName, newUserName, newUserName, newUserName) && result;
                        }

                        // Set new password
                        if (userPassword != newUserPassword)
                        {
                            result = adAccountManager.SetUserPassword(userName, newUserPassword) && result;
                        }

                        return result;
                    }
                    else
                        return false;
                }
                else
                    // Create new AD account
                    return (adAccountManager.CreateNewUser(adAccountManager.sDefaultOU, newUserName, newUserPassword, newUserName, newUserName) != null);
            }
            else
                return false;
        }

        /// <summary>
        /// Synchronize user account on delete 
        /// user account record from database
        /// </summary>
        /// <param name="uaDataRow">user account data row</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccountOnDelete(DataRow uaDataRow)
        {
            try
            {
                // Get authentication system ID
                int authSystemID = (int)uaDataRow["AuthSystemID", DataRowVersion.Original];

                // Get ancrypted user name
                byte[] encUserName = uaDataRow["UserName", DataRowVersion.Original] as byte[];

                // Select authentication system data
                string filterExpr = "ID = " + authSystemID.ToString();
                DataRow[] selRows = dbManager.dataSet.AuthSystems.Select(filterExpr);

                // Get encrypted settings string
                byte[] encSettingsString = selRows[0]["SettingsString", DataRowVersion.Original] as byte[];

                // Get action on delete
                int action = (int)selRows[0]["OnDeleteAction", DataRowVersion.Original];

                // Decrypt user name
                string decUserName = encryptor.DecryptString(encUserName);

                // Decrypt settings string
                string decSettingsString = encryptor.DecryptString(encSettingsString);

                // Sync on delete
                return SyncADAccountOnDelete(decUserName, action, decSettingsString);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Synchronize user account on insert 
        /// new user account record to database
        /// </summary>
        /// <param name="uaDataRow">user account data row</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccountOnInsert(DataRow uaDataRow)
        {
            try
            {
                // Get authentication system ID
                int authSystemID = (int)uaDataRow["AuthSystemID", DataRowVersion.Current];

                // Get encrypted user name and password
                byte[] encUserName = uaDataRow["UserName", DataRowVersion.Current] as byte[];
                byte[] encUserPassword = uaDataRow["Password", DataRowVersion.Current] as byte[];

                // Select authentication system data
                string filterExpr = "ID = " + authSystemID.ToString();
                DataRow[] selRows = dbManager.dataSet.AuthSystems.Select(filterExpr);
                
                // Get encrypted settings string
                byte[] encSettingsString = selRows[0]["SettingsString", DataRowVersion.Original] as byte[];

                // Get action on insert
                int action = (int)selRows[0]["OnInsertAction", DataRowVersion.Original];

                // Decrypt user name and password
                string decUserName = encryptor.DecryptString(encUserName);
                string decUserPassword = encryptor.DecryptString(encUserPassword);

                // Decrypt settings string
                string decSettingsString = encryptor.DecryptString(encSettingsString);

                // Sync on insert
                return SyncADAccountOnInsert(decUserName, decUserPassword, action, decSettingsString);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Synchronize user account on update 
        /// user account record in database
        /// </summary>
        /// <param name="uaDataRow">user account data row</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccountOnUpdate(DataRow uaDataRow)
        {
            try
            {
                // Get authentication system ID
                int authSystemID = (int)uaDataRow["AuthSystemID", DataRowVersion.Original];

                // Get encrypted user name and password
                byte[] encUserName = uaDataRow["UserName", DataRowVersion.Original] as byte[];
                byte[] encUserPassword = uaDataRow["Password", DataRowVersion.Original] as byte[];

                // Get encrypted new user name and password
                byte[] encNewUserName = uaDataRow["UserName", DataRowVersion.Current] as byte[];
                byte[] encNewUserPassword = uaDataRow["Password", DataRowVersion.Current] as byte[];

                // Select authentication system data
                string filterExpr = "ID = " + authSystemID.ToString();
                DataRow[] selRows = dbManager.dataSet.AuthSystems.Select(filterExpr);

                // Get encrypted settings string
                byte[] encSettingsString = selRows[0]["SettingsString", DataRowVersion.Original] as byte[];

                // Get action on update
                int action = (int)selRows[0]["OnUpdateAction", DataRowVersion.Original];

                // Decrypt user name and password
                string decUserName = encryptor.DecryptString(encUserName);
                string decUserPassword = encryptor.DecryptString(encUserPassword);

                // Decrypt new user name and password
                string decNewUserName = encryptor.DecryptString(encNewUserName);
                string decNewUserPassword = encryptor.DecryptString(encNewUserPassword);

                // Decrypt settings string
                string decSettingsString = encryptor.DecryptString(encSettingsString);

                // Sync on update
                return SyncADAccountOnUpdate(decUserName, decUserPassword, decNewUserName, decNewUserPassword, action, decSettingsString);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Synchronize user accounts on delete 
        /// user account record from database
        /// </summary>
        /// <param name="uaDataRows">user accounts data rows list</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccountsOnDelete(DataRow[] uaDataRows)
        {
            bool result = true;

            // Sync all accounts in list
            for (int i = 0; i < uaDataRows.Length; i++)
                result = SyncADAccountOnDelete(uaDataRows[i]) && result;

                return result;
        }

        /// <summary>
        /// Synchronize user accounts on insert 
        /// new user account record to database
        /// </summary>
        /// <param name="uaDataRows">user accounts data rows list</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccountsOnInsert(DataRow[] uaDataRows)
        {
            bool result = true;

            // Sync all accounts in list
            for (int i = 0; i < uaDataRows.Length; i++)
                result = SyncADAccountOnInsert(uaDataRows[i]) && result;

            return result;
        }

        /// <summary>
        /// Synchronize user accounts on update 
        /// user account record in database
        /// </summary>
        /// <param name="uaDataRows">user accounts data rows list</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccountsOnUpdate(DataRow[] uaDataRows)
        {
            bool result = true;

            // Sync all accounts in list
            for (int i = 0; i < uaDataRows.Length; i++)
                result = SyncADAccountOnUpdate(uaDataRows[i]) && result;

            return result;
        }

        /// <summary>
        /// Synchronize AD user accounts
        /// </summary>
        /// <param name="uaDataRows">user accounts data rows list</param>
        /// <param name="operation">operation (delete/insert/update) </param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADAccounts(DataRow [] uaDataRows, int operation)
        {
            switch (operation)
            {
                case UA_SYNC_DELETE: return SyncADAccountsOnDelete(uaDataRows);
                case UA_SYNC_INSERT: return SyncADAccountsOnInsert(uaDataRows);
                case UA_SYNC_UPDATE: return SyncADAccountsOnUpdate(uaDataRows);
                default: return false;
            }
        }

        /// <summary>
        /// Enumerate AD user accounts
        /// </summary>
        /// <returns>List of user names</returns>
        public List<string> EnumerateADUserAcccounts(string settingsString)
        {
            try
            {
                return GetADAccountManager(settingsString).EnumerateUserAcccounts();
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Enumerate AD user accounts
        /// </summary>
        /// <returns>List of user names</returns>
        public List<string> EnumerateADUsersOfSomeGroup(string settingsString, string groupName)
        {
            try
            {
                return GetADAccountManager(settingsString).EnumerateUsersOfSomeGroup(groupName);
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Enumerate AD user accounts
        /// </summary>
        /// <returns>List of user names</returns>
        public List<string> EnumerateADUserAcccountsWithoutGroup(string settingsString, string groupName)
        {
            try
            {
                ADAccountManager adManager = GetADAccountManager(settingsString);
                List<string> users = adManager.EnumerateUserAcccounts();
                List<string> groupUsers = adManager.EnumerateUsersOfSomeGroup(groupName);

                return (new List<string>(users.Except(groupUsers)));
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Check links of user names and system 
        /// user accounts
        /// </summary>
        /// <param name="userName">user name</param>
        /// <param name="authSystemID">authentication system ID</param>
        /// <returns>TRUE - if linked</returns>
        public bool UserNameLinked(string userName, int authSystemID)
        {
            string filterExpr = "AuthSystemID = " + authSystemID.ToString();
            DataRow[] uaRows = dbManager.dataSet.UserAccounts.Select(filterExpr);

            if ((uaRows != null) && (uaRows.Length > 0))
            {
                for (int i = 0; i < uaRows.Length; i++)
                {
                    byte[] encUserName = uaRows[i]["UserName", DataRowVersion.Original] as byte[];
                    string uaUserName = encryptor.DecryptString(encUserName);

                    if (userName == uaUserName) return true;
                }
            }

            return false;
        }

        #endregion

        #region User goups

        /// <summary>
        /// Synchronize user group on delete 
        /// user group record from database
        /// </summary>
        /// <param name="groupName">group name</param>
        /// <param name="action">action on delete</param>
        /// <param name="settingsString">settings string</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroupOnDelete(string groupName, int action, string settingsString)
        {
            // Check action
            if ((action == ACTION_DO_NOTHING) || (action == ACTION_DO_DISABLE))
                return true;
            
            // Check action
            if (action == ACTION_DO_DELETE)
            {
                // Delete user group from AD

                // Get AD manager
                ADAccountManager adAccountManager = GetADAccountManager(settingsString);

                // Check input user
                if (adAccountManager.IsUserGroupExisiting(groupName))
                    return adAccountManager.DeleteUserGroup(groupName);
                else
                    return true;
            }
            else
                return false;
        }

        /// <summary>
        /// Synchronize user group on insert 
        /// new user group record to database
        /// </summary>
        /// <param name="groupName">group name</param>
        /// <param name="groupSettings">group settings string</param>
        /// <param name="groupDescription">group description</param>
        /// <param name="action">action on insert</param>
        /// <param name="settingsString">settings string</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroupOnInsert(string groupName, string groupSettings, string groupDescription, int action, string settingsString)
        {
            // Check action
            if (action == ACTION_DO_NOTHING)
                return true;


            // Check action and input user
            if (action == ACTION_DO_INSERT)
            {
                // Get AD account manager
                ADAccountManager adAccountManager = GetADAccountManager(settingsString);

                // Get AD settings parser
                ADSettingsParser adSettingsParser = new ADSettingsParser();

                // Get group scope
                GroupScope groupScope = GroupScope.Global;
                switch (adSettingsParser.GetGroupScope(groupSettings))
                {
                    case "Global" :
                        {
                            groupScope = GroupScope.Global;
                            break;
                        }
                    case "Local" :
                        {
                            groupScope = GroupScope.Local;
                            break;
                        }
                    case "Universal" :
                        {
                            groupScope = GroupScope.Universal;
                            break;
                        }
                }

                // Get group type
                bool isGroupSecurity = true;
                if (adSettingsParser.GetGroupTypeName(groupSettings) != "Security")
                    isGroupSecurity = false;

                // Create new AD group
                if (!adAccountManager.IsUserGroupExisiting(groupName))
                {
                    return (adAccountManager.CreateNewGroup(adAccountManager.sDefaultOU, groupName, groupDescription, groupScope, isGroupSecurity) != null);
                }
                else
                {
                    return (adAccountManager.ChangeGroupParameters(groupName, groupDescription, groupScope, isGroupSecurity) != null);
                }
            }
            else
                return false;
        }

        /// <summary>
        /// Synchronize user group on update 
        /// user group record in database
        /// </summary>
        /// <param name="groupName">group name </param>
        /// <param name="groupSettings">group settings string</param>
        /// <param name="groupDescription">group description</param>
        /// <param name="newGroupName">new group name </param>
        /// <param name="newGroupSettings">new group settings string</param>
        /// <param name="newGroupDescription">new group description</param>
        /// <param name="action">action</param>
        /// <param name="settingsString">settings string</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroupOnUpdate(string groupName, string groupSettings, string groupDescription, 
                                          string newGroupName, string newGroupSettings, string newGroupDescription, 
                                          int action, string settingsString)
        {
            // Check action
            if (action == ACTION_DO_NOTHING)
                return true;


            // Check action and input user
            if (action == ACTION_DO_UPDATE)
            {
                ADAccountManager adAccountManager = GetADAccountManager(settingsString);
                // Get AD settings parser
                ADSettingsParser adSettingsParser = new ADSettingsParser();

                //// Get group scope
                //GroupScope groupScope = GroupScope.Global;
                //switch (adSettingsParser.GetGroupScope(groupSettings))
                //{
                //    case "Global":
                //        {
                //            groupScope = GroupScope.Global;
                //            break;
                //        }
                //    case "Local":
                //        {
                //            groupScope = GroupScope.Local;
                //            break;
                //        }
                //    case "Universal":
                //        {
                //            groupScope = GroupScope.Universal;
                //            break;
                //        }
                //}

                //// Get group type
                //bool isGroupSecurity = true;
                //if (adSettingsParser.GetGroupTypeName(groupSettings) != "Security")
                //    isGroupSecurity = false;

                // Get group scope
                GroupScope newGroupScope = GroupScope.Global;
                switch (adSettingsParser.GetGroupScope(newGroupSettings))
                {
                    case "Global":
                        {
                            newGroupScope = GroupScope.Global;
                            break;
                        }
                    case "Local":
                        {
                            newGroupScope = GroupScope.Local;
                            break;
                        }
                    case "Universal":
                        {
                            newGroupScope = GroupScope.Universal;
                            break;
                        }
                }

                // Get group type
                bool newIsGroupSecurity = true;
                if (adSettingsParser.GetGroupTypeName(newGroupSettings) != "Security")
                    newIsGroupSecurity = false;
                
                if (adAccountManager.IsUserGroupExisiting(groupName))
                {
                    bool result = true;

                    // Change group parameters
                    if ((groupSettings != newGroupSettings) || (groupDescription != newGroupDescription))
                    {
                        result = (adAccountManager.ChangeGroupParameters(groupName, newGroupDescription, newGroupScope, newIsGroupSecurity) != null) && result;
                    }
                    
                    // Change group name
                    if (groupName != newGroupName)
                    {
                        result = adAccountManager.ChangeGroupName(groupName, newGroupName) && result;
                    }
                    
                    return result;
                }
                else
                    // Create new AD account
                    return (adAccountManager.CreateNewGroup(adAccountManager.sDefaultOU, newGroupName, newGroupDescription, newGroupScope, newIsGroupSecurity) != null);
            }
            else
                return false;
        }

        /// <summary>
        /// Synchronize user group on delete 
        /// user group record from database
        /// </summary>
        /// <param name="uaDataRow">user group data row</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroupOnDelete(DataRow uaDataRow)
        {
            try
            {
                // Get authentication system ID
                int authSystemID = (int)uaDataRow["AuthSystemID", DataRowVersion.Original];

                // Get ancrypted group name
                byte[] encGroupName = uaDataRow["GroupName", DataRowVersion.Original] as byte[];

                // Select authentication system data
                string filterExpr = "ID = " + authSystemID.ToString();
                DataRow[] selRows = dbManager.dataSet.AuthSystems.Select(filterExpr);

                // Get encrypted settings string
                byte[] encSettingsString = selRows[0]["SettingsString", DataRowVersion.Original] as byte[];

                // Get action on delete
                int action = (int)selRows[0]["OnDeleteAction", DataRowVersion.Original];

                // Decrypt group name
                string decGroupName = encryptor.DecryptString(encGroupName);

                // Decrypt settings string
                string decSettingsString = encryptor.DecryptString(encSettingsString);

                // Sync on delete
                return SyncADGroupOnDelete(decGroupName, action, decSettingsString);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Synchronize user group on insert 
        /// new user group record to database
        /// </summary>
        /// <param name="uaDataRow">user group data row</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroupOnInsert(DataRow uaDataRow)
        {
            try
            {
                // Get authentication system ID
                int authSystemID = (int)uaDataRow["AuthSystemID", DataRowVersion.Current];

                // Get group ID
                int groupID = (int)uaDataRow["GroupID", DataRowVersion.Current];

                // Get encrypted group name
                byte[] encGroupName = uaDataRow["GroupName", DataRowVersion.Current] as byte[];

                // Get encrypted group settings
                byte[] encGroupSettings = uaDataRow["GroupSettings", DataRowVersion.Current] as byte[];

                // Select authentication system data
                string filterExpr = "ID = " + authSystemID.ToString();
                DataRow[] selRows = dbManager.dataSet.AuthSystems.Select(filterExpr);

                // Get encrypted settings string
                byte[] encSettingsString = selRows[0]["SettingsString", DataRowVersion.Original] as byte[];

                // Get action on insert
                int action = (int)selRows[0]["OnInsertAction", DataRowVersion.Original];

                // Select group description
                filterExpr = "ID = " + groupID.ToString();
                selRows = dbManager.dataSet.UserGroups.Select(filterExpr);

                // Get encrypted group description
                byte[] encGroupDescription = selRows[0]["Description", DataRowVersion.Current] as byte[];

                // Decrypt group data
                string decGroupName = encryptor.DecryptString(encGroupName);
                string decGroupSettings = encryptor.DecryptString(encGroupSettings);
                string decGroupDescription = encryptor.DecryptString(encGroupDescription);

                // Decrypt settings string
                string decSettingsString = encryptor.DecryptString(encSettingsString);

                // Sync on insert
                return SyncADGroupOnInsert(decGroupName, decGroupSettings, decGroupDescription, action, decSettingsString);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Synchronize user group on update 
        /// user group record in database
        /// </summary>
        /// <param name="uaDataRow">user group data row</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroupOnUpdate(DataRow uaDataRow)
        {
            try
            {
                // Get authentication system ID
                int authSystemID = (int)uaDataRow["AuthSystemID", DataRowVersion.Current];

                // Get group ID
                int groupID = (int)uaDataRow["GroupID", DataRowVersion.Current];

                // Get encrypted group name
                byte[] encGroupName = uaDataRow["GroupName", DataRowVersion.Original] as byte[];
                byte[] encNewGroupName = uaDataRow["GroupName", DataRowVersion.Current] as byte[];

                // Get encrypted group settings
                byte[] encGroupSettings = uaDataRow["GroupSettings", DataRowVersion.Original] as byte[];
                byte[] encNewGroupSettings = uaDataRow["GroupSettings", DataRowVersion.Current] as byte[];

                // Select authentication system data
                string filterExpr = "ID = " + authSystemID.ToString();
                DataRow[] selRows = dbManager.dataSet.AuthSystems.Select(filterExpr);

                // Get encrypted settings string
                byte[] encSettingsString = selRows[0]["SettingsString", DataRowVersion.Original] as byte[];

                // Get action on insert
                int action = (int)selRows[0]["OnUpdateAction", DataRowVersion.Original];

                // Select group description
                filterExpr = "ID = " + groupID.ToString();
                selRows = dbManager.dataSet.UserGroups.Select(filterExpr);

                // Get encrypted group description
                byte[] encGroupDescription = selRows[0]["Description", DataRowVersion.Original] as byte[];
                byte[] encNewGroupDescription = selRows[0]["Description", DataRowVersion.Current] as byte[];

                // Decrypt group data
                string decGroupName = encryptor.DecryptString(encGroupName);
                string decGroupSettings = encryptor.DecryptString(encGroupSettings);
                string decGroupDescription = encryptor.DecryptString(encGroupDescription);
                string decNewGroupName = encryptor.DecryptString(encNewGroupName);
                string decNewGroupSettings = encryptor.DecryptString(encNewGroupSettings);
                string decNewGroupDescription = encryptor.DecryptString(encNewGroupDescription);

                // Decrypt settings string
                string decSettingsString = encryptor.DecryptString(encSettingsString);

                // Sync on update
                return SyncADGroupOnUpdate(decGroupName, decGroupSettings, decGroupDescription, decNewGroupName, decNewGroupSettings, decNewGroupDescription, action, decSettingsString);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Synchronize user group on delete 
        /// user group record from database
        /// </summary>
        /// <param name="uaDataRows">user group data rows list</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroupsOnDelete(DataRow[] uaDataRows)
        {
            bool result = true;

            // Sync all accounts in list
            for (int i = 0; i < uaDataRows.Length; i++)
                result = SyncADGroupOnDelete(uaDataRows[i]) && result;

            return result;
        }

        /// <summary>
        /// Synchronize user group on insert 
        /// new user group record to database
        /// </summary>
        /// <param name="uaDataRows">user group data rows list</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroupsOnInsert(DataRow[] uaDataRows)
        {
            bool result = true;

            // Sync all accounts in list
            for (int i = 0; i < uaDataRows.Length; i++)
                result = SyncADGroupOnInsert(uaDataRows[i]) && result;

            return result;
        }

        /// <summary>
        /// Synchronize user group on update 
        /// user group record in database
        /// </summary>
        /// <param name="uaDataRows">user group data rows list</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroupsOnUpdate(DataRow[] uaDataRows)
        {
            bool result = true;

            // Sync all accounts in list
            for (int i = 0; i < uaDataRows.Length; i++)
                result = SyncADGroupOnUpdate(uaDataRows[i]) && result;

            return result;
        }

        /// <summary>
        /// Synchronize AD user groups
        /// </summary>
        /// <param name="uaDataRows">user groups data rows list</param>
        /// <param name="operation">operation (delete/insert/update) </param>
        /// <returns>TRUE - if success</returns>
        public bool SyncADGroups(DataRow[] uaDataRows, int operation)
        {
            switch (operation)
            {
                case UA_SYNC_DELETE: return SyncADGroupsOnDelete(uaDataRows);
                case UA_SYNC_INSERT: return SyncADGroupsOnInsert(uaDataRows);
                case UA_SYNC_UPDATE: return SyncADGroupsOnUpdate(uaDataRows);
                default: return false;
            }
        }

        /// <summary>
        /// Enumerate AD user groups
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <returns>List of group names</returns>
        public List<string> EnumerateADGroups(string settingsString)
        {
            try
            {
                return GetADAccountManager(settingsString).EnumerateUserGroups();
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        ///  Enumerate AD user groups
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <param name="userName">user name</param>
        /// <returns>List of group names</returns>
        public List<string> EnumerateADUserGroups(string settingsString, string userName)
        {
            try
            {
                return GetADAccountManager(settingsString).GetUserGroups(userName);
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        ///  Enumerate AD user groups
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <param name="userName">user name</param>
        /// <returns>List of group names</returns>
        public List<string> EnumerateADGroupsWithoutUser(string settingsString, string userName)
        {
            try
            {
                ADAccountManager adManager = GetADAccountManager(settingsString);
                List<string> groups = adManager.EnumerateUserGroups();
                List<string> userGroups = adManager.GetUserGroups(userName);

                return (new List<string>(groups.Except(userGroups)));
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        ///  Enumerate AD user authorization groups
        /// </summary>
        /// <param name="settingsString">settings string</param>
        /// <param name="userName">user name</param>
        /// <returns>List of group names</returns>
        public List<string> EnumerateADUserAuthorizationGroups(string settingsString, string userName)
        {
            try
            {
                return GetADAccountManager(settingsString).GetUserAuthorizationGroups(userName);
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Add AD user to group
        /// </summary>
        /// <param name="settingsString">setting string</param>
        /// <param name="userName">user name</param>
        /// <param name="groupName">group name</param>
        /// <returns>TRUE if success</returns>
        public bool AddADUserToGroup(string settingsString, string userName, string groupName)
        {
            try
            {
                return GetADAccountManager(settingsString).AddUserToGroup(userName, groupName);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Remove AD user from group
        /// </summary>
        /// <param name="settingsString">setting string</param>
        /// <param name="userName">user name</param>
        /// <param name="groupName">group name</param>
        /// <returns>TRUE if success</returns>
        public bool RemoveADUserFromGroup(string settingsString, string userName, string groupName)
        {
            try
            {
                return GetADAccountManager(settingsString).RemoveUserFromGroup(userName, groupName);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Checks if user is a member of a given group
        /// </summary>
        /// <param name="settingsString">setting string</param>
        /// <param name="userName">user name</param>
        /// <param name="groupName">group name</param>
        /// <returns>Returns true if user is a group member</returns>
        public bool IsUserGroupMember(string settingsString, string userName, string groupName)
        {
            try
            {
                return GetADAccountManager(settingsString).IsUserGroupMember(userName, groupName);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Check links of user groups and system user group
        /// </summary>
        /// <param name="groupName">group name</param>
        /// <param name="authSystemID">authentication system ID</param>
        /// <returns>TRUE - if linked</returns>
        public bool UserGroupLinked(string groupName, int authSystemID)
        {
            string filterExpr = "AuthSystemID = " + authSystemID.ToString();
            DataRow[] uaRows = dbManager.dataSet.UserGroupAuthSystems.Select(filterExpr);

            if ((uaRows != null) && (uaRows.Length > 0))
            {
                for (int i = 0; i < uaRows.Length; i++)
                {
                    byte[] encGroupName = uaRows[i]["GroupName", DataRowVersion.Original] as byte[];
                    string uaGroupName = encryptor.DecryptString(encGroupName);

                    if (groupName == uaGroupName) return true;
                }
            }

            return false;
        }

        /// <summary>
        /// Get settings string of AD group
        /// </summary>
        /// <param name="settingsString">AD settings string</param>
        /// <param name="groupName">group name</param>
        /// <returns>group settings string</returns>
        public string GetADGroupSettingsString(string settingsString, string groupName)
        {
            try
            {
                return GetADAccountManager(settingsString).GetGroupSettingsString(groupName);
            }
            catch
            {
                return String.Empty;
            }
        }

        /// <summary>
        /// Find user account
        /// </summary>
        /// <param name="userName">user name</param>
        /// <param name="authSystemID">authentication system ID</param>
        /// <returns>user ID</returns>
        private int FindUserAccount(string userName, int authSystemID)
        {
            try
            {
                string filter = "AuthSystemID = " + authSystemID.ToString();
                DataRow[] userAccountsRows = dbManager.dataSet.UserAccounts.Select(filter, null, DataViewRowState.CurrentRows);

                foreach (DataRow row in userAccountsRows)
                {
                    byte[] encUserName = row["UserName"] as byte[];
                    string decUserName = encryptor.DecryptString(encUserName);
                    int userID = (int)row["UserID"];

                    if (userName == decUserName)
                        return userID;
                }

                return -1;
            }
            catch
            {
                return -1;
            }
        }

        /// <summary>
        /// Find user group account
        /// </summary>
        /// <param name="groupName">group name</param>
        /// <param name="authSystemID">authentication system ID</param>
        /// <returns>group ID</returns>
        private int FindUserGroupAccount(string groupName, int authSystemID)
        {
            try
            {
                string filter = "AuthSystemID = " + authSystemID.ToString();
                DataRow[] groupAccountsRows = dbManager.dataSet.UserGroupAuthSystems.Select(filter, null, DataViewRowState.CurrentRows);

                foreach (DataRow row in groupAccountsRows)
                {
                    byte[] encGroupName = row["GroupName"] as byte[];
                    string decGroupName = encryptor.DecryptString(encGroupName);
                    int groupID = (int)row["GroupID"];

                    if (groupName == decGroupName)
                        return groupID;
                }

                return -1;
            }
            catch
            {
                return -1;
            }
        }

        /// <summary>
        /// Sync user accounts and gruops on add
        /// </summary>
        /// <param name="groupName">group name</param>
        /// <param name="userName">user name</param>
        /// <param name="authSystemID">authentication system ID</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncAddUserAccountsGroups(string groupName, string userName, int authSystemID)
        {
            try
            {
                int userID = FindUserAccount(userName, authSystemID);
                int groupID = FindUserGroupAccount(groupName, authSystemID);

                if ((userID != -1) && (groupID != -1))
                {
                    dbManager.userGroupUsersTableAdapter.Insert(groupID, userID);
                    return true;
                }
                else
                    return false;
            }
            catch
            {
                return false;
            }
        }
        
        /// <summary>
        /// Sync user accounts and groups on delete
        /// </summary>
        /// <param name="groupName">group name</param>
        /// <param name="userName">user name</param>
        /// <param name="authSystemID">authentication system ID</param>
        /// <returns>TRUE - if success</returns>
        public bool SyncRemoveUserAccountsGroups(string groupName, string userName, int authSystemID)
        {
            try
            {
                int userID = FindUserAccount(userName, authSystemID);
                int groupID = FindUserGroupAccount(groupName, authSystemID);

                if ((userID != -1) && (groupID != -1))
                {
                    dbManager.userGroupUsersTableAdapter.Delete(userID, groupID);
                    return true;
                }
                else
                    return false;
            }
            catch
            {
                return false;
            }
        }

        #endregion

        #endregion
        
    }
}
