/// <summary>
///   Solution : NovaTend
///   Project : ADAccountManager.dll
///   Module : ADAccountManager.cs
///   Description :  implements the methods of class ADAccountManager
/// </summary>

using System;
using System.Collections;
using System.Text;
using System.DirectoryServices;
using System.DirectoryServices.AccountManagement;
using System.Collections.Generic;
using System.Data;
using System.Configuration;

namespace ADAccountManagement
{
    /// <summary>
    /// Active directory account manager
    /// </summary>
    public class ADAccountManager
    {
        
        #region Variables

        private string _sDomain;
        private string _sDefaultOU;
        private string _sDefaultRootOU;
        private string _sServiceUser;
        private string _sServicePassword;

        public string sDomain
        {
            get 
            {
                return _sDomain;
            }

            set
            {
                _sDomain = value;
            }
        }


        public string sDefaultOU
        {
            get
            {
                return _sDefaultOU;
            }

            set
            {
                _sDefaultOU = value;
            }
        }

        public string sDefaultRootOU
        {
            get
            {
                return _sDefaultRootOU;
            }

            set
            {
                _sDefaultRootOU = value;
            }
        }

        public string sServiceUser
        {
            get
            {
                return _sServiceUser;
            }

            set
            {
                _sServiceUser = value;
            }
        }

        public string sServicePassword
        {
            get
            {
                return _sServicePassword;
            }

            set
            {
                _sServicePassword = value;
            }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// AD account manager constructor
        /// </summary>
        /// <param name="domain">Domain mane</param>
        /// <param name="defaultOU">Default organization unit</param>
        /// <param name="defaultRootOU">Default root organization unit</param>
        /// <param name="serviceUser">AD service user name</param>
        /// <param name="servicePassword">AD service user password</param>
        public ADAccountManager(string domain, string defaultOU, string defaultRootOU, string serviceUser, string servicePassword)
        {
            sDomain = domain;
            sDefaultOU = defaultOU;
            sDefaultRootOU = defaultRootOU;
            sServiceUser = serviceUser;
            sServicePassword = servicePassword;
        }

        #endregion

        #region Validate Methods

        /// <summary>
        /// Validates the username and password of a given user
        /// </summary>
        /// <param name="sUserName">The username to validate</param>
        /// <param name="sPassword">The password of the username to validate</param>
        /// <returns>Returns TRUE of user is valid</returns>
        public bool ValidateCredentials(string sUserName, string sPassword)
        {
            try
            {
                return GetPrincipalContext().ValidateCredentials(sUserName, sPassword);
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Checks if the User Account is Expired
        /// </summary>
        /// <param name="sUserName">The username to check</param>
        /// <returns>Returns TRUE if expired</returns>
        public bool IsUserExpired(string sUserName)
        {
            try
            {
                return GetUser(sUserName).AccountExpirationDate != null ? false : true;
            }
            catch
            {
                return true;
            }
        }

        /// <summary>
        /// Checks if user exsists on AD
        /// </summary>
        /// <param name="sUserName">The username to check</param>
        /// <returns>Returns true if username exists</returns>
        public bool IsUserExisiting(string sUserName)
        {
            return GetUser(sUserName) == null ? false : true;
        }

        /// <summary>
        /// Checks if user group exsists on AD
        /// </summary>
        /// <param name="sUserName">The user group name to check</param>
        /// <returns>Returns true if user group exists</returns>
        public bool IsUserGroupExisiting(string sUserGroupName)
        {
            return GetGroup(sUserGroupName) == null ? false : true;
        }

        /// <summary>
        /// Checks if user accoung is locked
        /// </summary>
        /// <param name="sUserName">The username to check</param>
        /// <returns>Retruns true of Account is locked</returns>
        public bool IsAccountLocked(string sUserName)
        {
            try
            {
                return GetUser(sUserName).IsAccountLockedOut();
            }
            catch
            {
                return true;
            }
        }

        /// <summary>
        /// Checks if user accoung is enabled
        /// </summary>
        /// <param name="sUserName">The username to check</param>
        /// <returns>Retruns true of account is enabled</returns>
        public bool IsAccountEnabled(string sUserName)
        {
            try
            {
                UserPrincipal oUserPrincipal = GetUser(sUserName);
                bool? enabled = oUserPrincipal.Enabled;

                return (enabled == null) ? false : (bool)enabled;
            }
            catch
            {
                return false;
            }
        }


        #endregion

        #region Search Methods

        /// <summary>
        /// Gets a certain user on Active Directory
        /// </summary>
        /// <param name="sUserName">The username to get</param>
        /// <returns>Returns the UserPrincipal Object</returns>
        public UserPrincipal GetUser(string sUserName)
        {
             PrincipalContext oPrincipalContext = GetPrincipalContext();
             return UserPrincipal.FindByIdentity(oPrincipalContext, IdentityType.SamAccountName, sUserName);
        }

        /// <summary>
        /// Gets a certain group on Active Directory
        /// </summary>
        /// <param name="sGroupName">The group to get</param>
        /// <returns>Returns the GroupPrincipal Object</returns>
        public GroupPrincipal GetGroup(string sGroupName)
        {
            PrincipalContext oPrincipalContext = GetPrincipalContext();
            return GroupPrincipal.FindByIdentity(oPrincipalContext, sGroupName);
        }

        #endregion

        #region User Account Methods

        /// <summary>
        /// Sets the user password
        /// </summary>
        /// <param name="sUserName">The username to set</param>
        /// <param name="sNewPassword">The new password to use</param>
        public bool SetUserPassword(string sUserName, string sNewPassword)
        {
            try
            {
                GetUser(sUserName).SetPassword(sNewPassword);
                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Change user name
        /// </summary>
        /// <param name="sUserName">user name</param>
        /// <param name="newUserName">new user name</param>
        /// <param name="newGivenName">new given user name</param>
        /// <param name="newSurname">new user surname</param>
        /// <returns>TRUE if success</returns>
        public bool ChangeUserName(string sUserName, string newUserName, string newGivenName, string newSurname)
        {
            UserPrincipal oUserPrincipal = GetUser(sUserName);

            try
            {
                oUserPrincipal.UserPrincipalName = newUserName;
                oUserPrincipal.SamAccountName = newUserName;
                oUserPrincipal.DisplayName = newUserName;
                oUserPrincipal.GivenName = newGivenName;
                oUserPrincipal.Surname = newSurname;

                DirectoryEntry dirEntry = (DirectoryEntry)oUserPrincipal.GetUnderlyingObject();
                dirEntry.Rename("CN=" + newUserName); 
                dirEntry.CommitChanges();
                
                oUserPrincipal.Save();

                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Enumerate user accounts
        /// </summary>
        /// <returns>List of user names</returns>
        public List<string> EnumerateUserAcccounts()
        {
            try
            {
                List<string> userAccountsList = new List<string>();
                PrincipalSearcher searcher = new PrincipalSearcher(new UserPrincipal(GetPrincipalContext()));

                foreach (Principal result in searcher.FindAll())
                {
                    DirectoryEntry de = result.GetUnderlyingObject() as DirectoryEntry;
                    userAccountsList.Add(de.Properties["samAccountName"].Value.ToString());
                }

                return userAccountsList;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Enables a disabled user account
        /// </summary>
        /// <param name="sUserName">The username to enable</param>
        public bool EnableUserAccount(string sUserName)
        {
            UserPrincipal oUserPrincipal = GetUser(sUserName);

            if (oUserPrincipal != null)
            {
                oUserPrincipal.Enabled = true;
                oUserPrincipal.Save();
            }

            return IsAccountEnabled(sUserName);
        }

        /// <summary>
        /// Force disbaling of a user account
        /// </summary>
        /// <param name="sUserName">The username to disable</param>
        public bool DisableUserAccount(string sUserName)
        {
            UserPrincipal oUserPrincipal = GetUser(sUserName);

            if (oUserPrincipal != null)
            {
                oUserPrincipal.Enabled = false;
                oUserPrincipal.Save();
            }

            return IsAccountEnabled(sUserName);
        }

        /// <summary>
        /// Force expire password of a user
        /// </summary>
        /// <param name="sUserName">The username to expire the password</param>
        public bool ExpireUserPassword(string sUserName)
        {
            UserPrincipal oUserPrincipal = GetUser(sUserName);

            if (oUserPrincipal != null)
            {
                oUserPrincipal.ExpirePasswordNow();
                oUserPrincipal.Save();
            }

            return IsUserExpired(sUserName);
        }

        /// <summary>
        /// Unlocks a locked user account
        /// </summary>
        /// <param name="sUserName">The username to unlock</param>
        public bool UnlockUserAccount(string sUserName)
        {
            UserPrincipal oUserPrincipal = GetUser(sUserName);

            if (oUserPrincipal != null)
            {
                oUserPrincipal.UnlockAccount();
                oUserPrincipal.Save();
            }

            return IsAccountLocked(sUserName);
        }

        /// <summary>
        /// Creates a new user on Active Directory
        /// </summary>
        /// <param name="sOU">The OU location you want to save your user</param>
        /// <param name="sUserName">The username of the new user</param>
        /// <param name="sPassword">The password of the new user</param>
        /// <param name="sGivenName">The given name of the new user</param>
        /// <param name="sSurname">The surname of the new user</param>
        /// <returns>returns the UserPrincipal object</returns>
        public UserPrincipal CreateNewUser(string sOU, string sUserName, string sPassword, string sGivenName, string sSurname)
        {
            if (IsUserExisiting(sUserName))
                return GetUser(sUserName);
            else
            {
                try
                {
                    PrincipalContext oPrincipalContext = GetPrincipalContext(sOU);

                    UserPrincipal oUserPrincipal = new UserPrincipal(oPrincipalContext, sUserName, sPassword, true)
                    {
                        DisplayName = sUserName,
                        UserPrincipalName = sUserName,
                        SamAccountName = sUserName,
                        GivenName = sGivenName,
                        Surname = sSurname,
                        PasswordNeverExpires = true
                    };

                    oUserPrincipal.Save();

                    return oUserPrincipal;
                }
                catch
                {
                    return null;
                }
            }
        }

        /// <summary>
        /// Deletes a user in Active Directory
        /// </summary>
        /// <param name="sUserName">The username you want to delete</param>
        /// <returns>Returns true if successfully deleted</returns>
        public bool DeleteUser(string sUserName)
        {
            try
            {
                UserPrincipal oUserPrincipal = GetUser(sUserName);
                oUserPrincipal.Delete();
                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Get list of users of some group
        /// </summary>
        /// <param name="groupName">group name</param>
        /// <returns>user list</returns>
        public List <string> EnumerateUsersOfSomeGroup(string groupName)
        {
            try
            {
                GroupPrincipal oGroupPrincipalContext = GetGroup(groupName);
                List<string> userAccountsList = new List<string>();

                foreach (Principal member in oGroupPrincipalContext.GetMembers())
                {
                    UserPrincipal oUserPrincipal = GetUser(member.SamAccountName);
                    if (oUserPrincipal != null)
                        userAccountsList.Add(oUserPrincipal.SamAccountName);
                }

                return userAccountsList;
            }
            catch
            {
                return null;
            }
        }

        #endregion

        #region Group Methods

        /// <summary>
        /// Creates a new group in Active Directory
        /// </summary>
        /// <param name="sOU">The OU location you want to save your new Group</param>
        /// <param name="sGroupName">The name of the new group</param>
        /// <param name="sDescription">The description of the new group</param>
        /// <param name="oGroupScope">The scope of the new group</param>
        /// <param name="bSecurityGroup">True is you want this group to be a security group, false if you want this as a distribution group</param>
        /// <returns>Retruns the GroupPrincipal object</returns>
        public GroupPrincipal CreateNewGroup(string sOU, string sGroupName, string sDescription, GroupScope oGroupScope, bool bSecurityGroup)
        {
            try
            {
                PrincipalContext oPrincipalContext = GetPrincipalContext(sOU);

                GroupPrincipal oGroupPrincipal = new GroupPrincipal(oPrincipalContext, sGroupName);
                oGroupPrincipal.Description = sDescription;
                oGroupPrincipal.GroupScope = oGroupScope;
                oGroupPrincipal.IsSecurityGroup = bSecurityGroup;
                oGroupPrincipal.Save();

                return oGroupPrincipal;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Change Active Directory group parameters
        /// </summary>
        /// <param name="sGroupName">The name of the new group</param>
        /// <param name="sDescription">The description of the new group</param>
        /// <param name="oGroupScope">The scope of the new group</param>
        /// <param name="bSecurityGroup">True is you want this group to be a security group, false if you want this as a distribution group</param>
        /// <returns>Retruns the GroupPrincipal object</returns>
        public GroupPrincipal ChangeGroupParameters(string sGroupName, string sDescription, GroupScope oGroupScope, bool bSecurityGroup)
        {
            try
            {
                GroupPrincipal oGroupPrincipal = GetGroup(sGroupName);
                oGroupPrincipal.Description = sDescription;
                oGroupPrincipal.GroupScope = oGroupScope;
                oGroupPrincipal.IsSecurityGroup = bSecurityGroup;
                oGroupPrincipal.Save();

                return oGroupPrincipal;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Rename AD group
        /// </summary>
        /// <param name="sGroupName"> group name </param>
        /// <param name="sNewGroupName">new group name</param>
        /// <returns>TRUE - if success</returns>
        public bool ChangeGroupName(string sGroupName, string sNewGroupName)
        {
            try
            {
                GroupPrincipal oGroupPrincipal = GetGroup(sGroupName);
                DirectoryEntry groupEntry = (DirectoryEntry)oGroupPrincipal.GetUnderlyingObject();
                groupEntry.Rename(sNewGroupName);
                groupEntry.CommitChanges();

                return true;
            }
            catch
            {
                return false;
            }
        }
        
        /// <summary>
        /// Deletes a user group in Active Directory
        /// </summary>
        /// <param name="sUserGroupName">The user group name you want to delete</param>
        /// <returns>Returns true if successfully deleted</returns>
        public bool DeleteUserGroup(string sUserGroupName)
        {
            try
            {
                GroupPrincipal oGroupPrincipal = GetGroup(sUserGroupName);
                oGroupPrincipal.Delete();
                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Adds the user for a given group
        /// </summary>
        /// <param name="sUserName">The user you want to add to a group</param>
        /// <param name="sGroupName">The group you want the user to be added in</param>
        /// <returns>Returns true if successful</returns>
        public bool AddUserToGroup(string sUserName, string sGroupName)
        {
            try
            {
                UserPrincipal oUserPrincipal = GetUser(sUserName);
                GroupPrincipal oGroupPrincipal = GetGroup(sGroupName);

                if (oUserPrincipal != null && oGroupPrincipal != null)
                {
                    if (!IsUserGroupMember(sUserName, sGroupName))
                    {
                        oGroupPrincipal.Members.Add(oUserPrincipal);
                        oGroupPrincipal.Save();
                    }

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
        /// Removes user from a given group
        /// </summary>
        /// <param name="sUserName">The user you want to remove from a group</param>
        /// <param name="sGroupName">The group you want the user to be removed from</param>
        /// <returns>Returns true if successful</returns>
        public bool RemoveUserFromGroup(string sUserName, string sGroupName)
        {
            try
            {
                UserPrincipal oUserPrincipal = GetUser(sUserName);
                GroupPrincipal oGroupPrincipal = GetGroup(sGroupName);

                if (oUserPrincipal != null && oGroupPrincipal != null)
                {
                    if (IsUserGroupMember(sUserName, sGroupName))
                    {
                        oGroupPrincipal.Members.Remove(oUserPrincipal);
                        oGroupPrincipal.Save();
                        return true;
                    }
                    else
                        return false;
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
        /// Checks if user is a member of a given group
        /// </summary>
        /// <param name="sUserName">The user you want to validate</param>
        /// <param name="sGroupName">The group you want to check the membership of the user</param>
        /// <returns>Returns true if user is a group member</returns>
        public bool IsUserGroupMember(string sUserName, string sGroupName)
        {
            UserPrincipal oUserPrincipal = GetUser(sUserName);
            GroupPrincipal oGroupPrincipal = GetGroup(sGroupName);

            if (oUserPrincipal != null && oGroupPrincipal != null)
            {
                return oGroupPrincipal.Members.Contains(oUserPrincipal);
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Gets a list of the users groups
        /// </summary>
        /// <returns>Returns an arraylist of groups</returns>
        public List<string> EnumerateUserGroups()
        {
            try
            {
                List<string> myItems = new List<string>();

                GroupPrincipal groupPrincipal = new GroupPrincipal(GetPrincipalContext());

                PrincipalSearcher principalSearcher = new PrincipalSearcher(groupPrincipal);
                PrincipalSearchResult<Principal> oPrincipalSearchResult = principalSearcher.FindAll();
                foreach (Principal oResult in oPrincipalSearchResult)
                {
                    myItems.Add(oResult.Name);
                }
                
                return myItems;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Gets a list of the users group memberships
        /// </summary>
        /// <param name="sUserName">The user you want to get the group memberships</param>
        /// <returns>Returns an arraylist of group memberships</returns>
        public List<string> GetUserGroups(string sUserName)
        {
            try
            {
                List<string> myItems = new List<string>();
                UserPrincipal oUserPrincipal = GetUser(sUserName);

                using (PrincipalSearchResult<Principal> oPrincipalSearchResult = oUserPrincipal.GetGroups())
                {
                    foreach (Principal oResult in oPrincipalSearchResult)
                    {
                        myItems.Add(oResult.Name);
                    }
                }

                return myItems;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Gets a list of the users authorization groups
        /// </summary>
        /// <param name="sUserName">The user you want to get authorization groups</param>
        /// <returns>Returns an arraylist of group authorization memberships</returns>
        public List<string> GetUserAuthorizationGroups(string sUserName)
        {
            try
            {
                List<string> myItems = new List<string>();
                UserPrincipal oUserPrincipal = GetUser(sUserName);

                using (PrincipalSearchResult<Principal> oPrincipalSearchResult = oUserPrincipal.GetAuthorizationGroups())
                {
                    foreach (Principal oResult in oPrincipalSearchResult)
                    {
                        myItems.Add(oResult.Name);
                    }
                }

                return myItems;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Get settings string of user group
        /// </summary>
        /// <param name="groupName">group name</param>
        /// <returns>settings string</returns>
        public string GetGroupSettingsString(string groupName)
        {
            try
            {
                GroupPrincipal oGroupPrincipal = GetGroup(groupName);

                string settingsString = "<groupScope: ";

                switch(oGroupPrincipal.GroupScope)
                {
                    case GroupScope.Global :
                        {
                            settingsString = settingsString + "Global>" ;
                            break;
                        }

                    case GroupScope.Local :
                        {
                            settingsString = settingsString + "Local>" ;
                            break;
                        }

                    case GroupScope.Universal :
                        {
                            settingsString = settingsString + "Universal>" ;
                            break;
                        }

                    default:
                        {
                            settingsString = settingsString + "none>" ;
                            break;
                        }
                }

                settingsString = settingsString + "<groupType: ";

                if (oGroupPrincipal.IsSecurityGroup == true)
                    settingsString = settingsString + "Security>";
                else
                    settingsString = settingsString + "Distribution>";

                return settingsString;
            }
            catch
            {
                return String.Empty;
            }
        }

        
        #endregion

        #region Helper Methods

        /// <summary>
        /// Gets the base principal context
        /// </summary>
        /// <returns>Retruns the PrincipalContext object</returns>
        public PrincipalContext GetPrincipalContext()
        {
            return new PrincipalContext(ContextType.Domain, sDomain, sDefaultRootOU, sServiceUser, sServicePassword);
        }

        /// <summary>
        /// Gets the principal context on specified OU
        /// </summary>
        /// <param name="sOU">The OU you want your Principal Context to run on</param>
        /// <returns>Retruns the PrincipalContext object</returns>
        public PrincipalContext GetPrincipalContext(string sOU)
        {
            return new PrincipalContext(ContextType.Domain, sDomain, string.IsNullOrEmpty(sOU) ? sDefaultOU : sOU, sServiceUser, sServicePassword);
        }

        #endregion
    }
}
