/****************************************************************

   Solution : NovaTend

   Project : z-adman-01.dll

   Module : ADAccountManager.h

   Description : this module defines interface of
				  class ADAccountManager

*****************************************************************/

#include "stdafx.h"
#include <LogWriter.h>

#ifdef ZADMAN01_EXPORTS
#define ADMANAGER_API __declspec(dllexport)
#else
#define ADMANAGER_API __declspec(dllimport)
#endif

#ifndef ADACCOUNTMANAGER_H
#define ADACCOUNTMANAGER_H

// Define restrictions

// Maximum length of domain name
#define DOMAIN_NAME_LEN			255

// Maximum length of OU name
#define OU_NAME_LEN				255

// Maximum length of user name
#define USER_NAME_LEN			255

// Maximum length of password
#define PWD_LEN					255

// Maximum length of group description
#define GROUP_DESCRIPTION_LEN	1024

// Size of list
#define MAX_NAMES_COUNT			1024

// Object names list
typedef struct _namesList
{
	int itemsCount;
	WCHAR items[MAX_NAMES_COUNT][USER_NAME_LEN];
} NAMES_LIST, *PNAMES_LIST;


/****************************************************************

   Class : ADAccountManager 

   Description : responsible for management
				 of AD user accounts.

				 This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class ADMANAGER_API ADAccountManager : public SystemBase
{
	private:

		// Log writer instance
		LogWriter * logWriter;

		// Domain name
		WCHAR _sDomain[DOMAIN_NAME_LEN];

		// Default OU
		WCHAR _sDefaultOU[OU_NAME_LEN];

		// Default Root OU
		WCHAR _sDefaultRootOU[OU_NAME_LEN];

		// Admin user name
		WCHAR _sServiceUser[USER_NAME_LEN];

		// Admin password
		WCHAR _sServicePassword[PWD_LEN];

		// COM initialization flag
		bool comInit;

		// Get user
		HRESULT GetUser(IDirectorySearch * pSearchBase, WCHAR * userName, IADs ** ppUser);

		// Get user
		HRESULT GetUser(WCHAR * userName, IADsUser **pUser);

		// Get group
		HRESULT GetGroup(IDirectorySearch * pSearchBase, WCHAR * groupName, IADs ** ppGroup);

		// Get group
		HRESULT GetGroup(WCHAR * groupName, IADsGroup **pGroup);


		// Write message to Log-file
		int WriteToLog(char * message);

	public:

		// Constructor
		ADAccountManager(unsigned long dllUserID, LogWriter * logWriter, WCHAR * domain, WCHAR * defaultOU, WCHAR * defaultRootOU, WCHAR * serviceUser, WCHAR * servicePassword);

		// Destructor
		~ADAccountManager(void);

		// Validate user credentials
		bool ValidateCredentials(WCHAR * userName, WCHAR * password);

		// Check user expiration date
		bool IsUserExpired(WCHAR * userName);

		// Check if user exsists on AD
		bool IsUserExisting(WCHAR * userName);

		// Check if group exsists on AD
		bool IsGroupExisting(WCHAR * groupName);

		// Check if user account locked
		bool IsAccountLocked(WCHAR * userName);

		// Check if user account enabled
		bool IsAccountEnabled(WCHAR * userName);

		// Set user password
		bool SetUserPassword(WCHAR * userName, WCHAR * password);

		// Change user name
		bool ChangeUserName(WCHAR * userName, WCHAR * newUserName);

		// Change group name
		bool ChangeGroupName(WCHAR * groupName, WCHAR * newGroupName);

		// Change group parameters
		bool ChangeGroupParameters(WCHAR * wGroupName, WCHAR * wGroupDescription, WCHAR * wGroupScopeName, WCHAR * wGroupTypeName);

		// Enable account
		bool EnableAccount(WCHAR * userName);

		// Disable account
		bool DisableAccount(WCHAR * userName);

		// Lock account
		bool LockAccount(WCHAR * userName);

		// Unlock account
		bool UnLockAccount(WCHAR * userName);

		// Create new user
		bool CreateNewUser(WCHAR * userName, WCHAR * password);

		// Create new group
		bool CreateNewGroup(WCHAR * groupName, WCHAR * groupDescription, WCHAR * groupScopeName, WCHAR * groupTypeName);

		// Delete user
		bool DeleteUser(WCHAR * userName);

		// Delete group
		bool DeleteGroup(WCHAR * groupName);

		// Enumerate users
		bool EnumUserAccounts(PNAMES_LIST userList);

		// Check if the user belongs to some group
		bool IsUserGroupMember(WCHAR * userName, WCHAR * groupName);

		// Add user to group
		bool AddUserToGroup(WCHAR * userName, WCHAR * groupName);

		// Remove user from group
		bool RemoveUserFromGroup(WCHAR * userName, WCHAR * groupName);
};

#endif