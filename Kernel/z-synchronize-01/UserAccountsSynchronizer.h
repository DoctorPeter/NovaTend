/****************************************************************

   Solution : NovaTend

   Project : z-synchronize-01.dll

   Module : UserAccountsSynchronizer.h

   Description :  this module defines interface of
				  class UserAccountsSynchronizer

*****************************************************************/

#include <LogWriter.h>
#include <DatabaseManager.h>
#include <Encryptor.h>
#include <ContentDataDef.h>
#include <ADAccountManager.h>

#ifdef ZSYNCHRONIZE01_EXPORTS
#define SYNCHRONIZER_API __declspec(dllexport)
#else
#define SYNCHRONIZER_API __declspec(dllimport)
#endif


#ifndef USER_ACCOUNTS_SYNCHRONIZER_H
#define USER_ACCOUNTS_SYNCHRONIZER_H

// Sync action types

// No action
#define ACTION_DO_NOTHING		1

// Disable account
#define ACTION_DO_DISABLE		2

// Delete account
#define ACTION_DO_DELETE		3

// Insert account
#define ACTION_DO_INSERT		4

// Update account
#define ACTION_DO_UPDATE		5


// User accounts operations types

// Delete  user account
#define UA_SYNC_DELETE			1

// Insert user account
#define UA_SYNC_INSERT			2

// Update user account
#define UA_SYNC_UPDATE			3


// Authentication systems types

// Active Directory
#define UAC_AD					1

/****************************************************************

   Class : UserAccountsSynchronizer

   Description : synchronize user accounts

*****************************************************************/
class SYNCHRONIZER_API UserAccountsSynchronizer : public SystemBase
{
	private:
		// Log writer instance
		LogWriter * logWriter;

		// Database manager instance
		DatabaseManager * dbManager;

		// Encryptor instance
		Encryptor * encryptor;


		// Connect to database
		bool DatabaseConnect(void);

		// Disconnect from database
		bool DatabaseDisconnect(void);


		// Get account manager instance
		ADAccountManager * GetADAccountManager(char * settingsString);

	public:

		// Constructor
		UserAccountsSynchronizer(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~UserAccountsSynchronizer(void);
		
		
		// Synchronize user accounts on delete user account record from database
		bool SyncADAccountOnDelete(char * userName, int action, char * settingsString);

		// Synchronize user accounts on insert user account record to the database
		bool SyncADAccountOnInsert(char * userName, char * userPassword, int action, char * settingsString);

		// Synchronize user accounts on update user account record in the database
		bool SyncADAccountOnUpdate(char * userName, char * userPassword, char * newUserName, char * newUserPassword, int action, char * settingsString);


		// Synchronize user group on delete user group record from database
		bool SyncADGroupOnDelete(char * groupName, int action, char * settingsString);

		// Synchronize user group on insert user group record to the database
		bool SyncADGroupOnInsert(char * groupName, char * groupSettings, char * groupDescription, int action, char * settingsString);

		// Synchronize user group on update user group record in the database
		bool SyncADGroupOnUpdate(char * groupName, char * groupSettings, char * groupDescription, char * newGroupName, char * newGroupSettings, char * newGroupDescription, int action, char * settingsString);


		// Synchronize user/group membership
		bool SyncUserGroupMember(int userID, int groupID);

		// Synchronize user/group membership
		bool SyncUserGroupMembers(void);


		// Validation of AD user account
		bool ValidateADAccount(char * userName, char * userPassword, char * settingsString);



		// General forces synchronization
		bool ForcedSynchronization(void);

		// Forced synchronization of users
		bool ForcedUsersSynchronization(void);

		// Forced synchronization of groups
		bool ForcedGroupsSynchronization(void);

		
		// Reverse synchronization of user acocunt
		bool ReverseSyncAccount(char * userName, char * userPassword, int authSystemID);

		// Reverse synchronization of user acocunt
		bool ReverseSyncAccount(unsigned char * encUserName, int encUserNameLen, unsigned char * encUserPassword, int encUserPasswordLen, int authSystemID);

		// Write message to Log-file
		int WriteToLog(char * message);
};

#endif