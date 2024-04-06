/****************************************************************

   Solution : NovaTend

   Project : z-synchronize-01.dll

   Module : UserAccountsSynchronizer.cpp

   Description :  this module implements methods of
				  class UserAccountsSynchronizer

*****************************************************************/

#include "stdafx.h"

#include "UserAccountsSynchronizer.h"
#include <ODBCDatabaseManager.h>
#include <ADSettingsParser.h>
#include <SettingsManager.h>
#include <time.h>


// z-synchronize-01.dll definition structure
extern DLL_COMMON_DEFINITION zSynchronizeDllDefinition;

#pragma region Constructor

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
UserAccountsSynchronizer :: UserAccountsSynchronizer(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zSynchronizeDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : constructor");
	#endif

	dbManager = new ODBCDatabaseManager(zSynchronizeDllDefinition.dllID, logWriter);
	encryptor = new Encryptor(zSynchronizeDllDefinition.dllID);

	DatabaseConnect();
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : Destructor

*****************************************************************/
UserAccountsSynchronizer :: ~UserAccountsSynchronizer(void)
{
	DatabaseDisconnect();

	delete dbManager;
	delete encryptor;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : destructor");
	#endif
}

#pragma endregion

#pragma region Database

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : DatabaseConnect

   Return : Connection state

   Description :  Connect to database

*****************************************************************/
bool UserAccountsSynchronizer :: DatabaseConnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : DatabaseConnect. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Check connection
		if (!(dbManager -> Opened()))
		{
			// Data source name
			char dsn[NAME_LEN];

			// Name of database user
			char dbUser[NAME_LEN];

			// Password for database access
			char dbPassword[STR_VALUE_LEN];

			SettingsManager * settingsManager = new SettingsManager(zSynchronizeDllDefinition.dllID);

			if (settingsManager -> GetDatabaseSourceName(dsn) != ERROR_SUCCESS)
				WriteToLog("Response validator : Connect to DB --> Can't get DSN ");

			if (settingsManager -> GetDatabaseUserName(dbUser) != ERROR_SUCCESS)
				WriteToLog("Response validator :  Connect to DB --> Can't get db user name ");

			if (settingsManager -> GetDatabasePassword(dbPassword) != ERROR_SUCCESS)
				WriteToLog("Response validator :  Connect to DB --> Can't get db password ");

			delete settingsManager;
		
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : DatabaseConnect. Connecting...");
			#endif

			// Connect
			dbManager -> Connect(dsn, dbUser, dbPassword);
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			else
				WriteToLog("UserAccountsSynchronizer : DatabaseConnect. Already connected!");

			WriteToLog("UserAccountsSynchronizer : DatabaseConnect. Done");
		#endif

		// Return connection state
		return dbManager -> Opened();
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : DatabaseDisconnect

   Return : Connection state

   Description :  Disconnect from database

*****************************************************************/
bool UserAccountsSynchronizer :: DatabaseDisconnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : DatabaseDisconnect. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Check connection
		if (dbManager -> Opened())
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : DatabaseDisconnect. Disconnecting...");
			#endif

			// Disconnect
			dbManager -> Disconnect();
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			else
				WriteToLog("UserAccountsSynchronizer : DatabaseDisconnect. Already disconnected!");

			WriteToLog("UserAccountsSynchronizer : DatabaseDisconnect. Done");
		#endif

		// Return connection state
		return dbManager -> Opened();
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return true;
	}
}

#pragma endregion

#pragma region Active Directory

#pragma region Active Directory manager

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : GetADAccountManager

   Parameters :
			Input : 
				settingsString - settings string

	Return : pointer to the account manager instance

	Description :  Get account manager instance

*****************************************************************/
ADAccountManager * UserAccountsSynchronizer :: GetADAccountManager(char * settingsString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : GetADAccountManager. Start");
	#endif

	ADSettingsParser * parser = new ADSettingsParser(zSynchronizeDllDefinition.dllID, logWriter);
	
	char userName[USER_NAME_LEN];
	char userPassword[PWD_LEN];
	char domainName[DOMAIN_NAME_LEN];
	char defaultOU[OU_NAME_LEN];
	char defaultRootOU[OU_NAME_LEN];

	parser -> GetServiceUserName(settingsString, userName);
	parser -> GetServiceUserPassword(settingsString, userPassword);
	parser -> GetDomainName(settingsString, domainName);
	parser -> GetDefaultOU(settingsString, defaultOU);
	parser -> GetDefaultRootOU(settingsString, defaultRootOU);

	delete parser;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		char msg[1024];

		sprintf(msg, "UserAccountsSynchronizer : GetADAccountManager. Service user name: %s", userName);
		WriteToLog(msg);

		sprintf(msg, "UserAccountsSynchronizer : GetADAccountManager. Service user password: %s", userPassword);
		WriteToLog(msg);

		sprintf(msg, "UserAccountsSynchronizer : GetADAccountManager. Domain: %s", domainName);
		WriteToLog(msg);

		sprintf(msg, "UserAccountsSynchronizer : GetADAccountManager. Default OU: %s", defaultOU);
		WriteToLog(msg);

		sprintf(msg, "UserAccountsSynchronizer : GetADAccountManager. Default root OU: %s", defaultRootOU);
		WriteToLog(msg);
	#endif


	WCHAR wUserName[USER_NAME_LEN];
	WCHAR wUserPassword[PWD_LEN];
	WCHAR wDomainName[DOMAIN_NAME_LEN];
	WCHAR wDefaultOU[OU_NAME_LEN];
	WCHAR wDefaultRootOU[OU_NAME_LEN];

	mbstowcs(wUserName, userName, USER_NAME_LEN);
	mbstowcs(wUserPassword, userPassword, PWD_LEN);
	mbstowcs(wDomainName, domainName, DOMAIN_NAME_LEN);
	mbstowcs(wDefaultOU, defaultOU, OU_NAME_LEN);
	mbstowcs(wDefaultRootOU, defaultRootOU, OU_NAME_LEN);

	ADAccountManager * adManager = new ADAccountManager(zSynchronizeDllDefinition.dllID, logWriter, wDomainName, wDefaultOU, wDefaultRootOU, wUserName, wUserPassword);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : GetADAccountManager. Done");
	#endif

	return adManager;
}

#pragma endregion

#pragma region Users

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : SyncADAccountOnDelete

   Parameters :
			Input : 
				userName - user name
				action - action on delete
				settingsString - settings string

	Return : TRUE - if success

	Description :  Synchronize user accounts on delete user 
				   account record from database

*****************************************************************/
bool UserAccountsSynchronizer :: SyncADAccountOnDelete(char * userName, int action, char * settingsString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. Start");
	#endif

	// Get account manager
	ADAccountManager * adAccountManager = GetADAccountManager(settingsString);

	// Convert to wide string
	WCHAR wUserName[USER_NAME_LEN];
	mbstowcs(wUserName, userName, USER_NAME_LEN);

	// result flag
	bool operationResult = false;

    // Check input user
	if (adAccountManager -> IsUserExisting(wUserName))
    {
		// Check action
        switch (action)
        {
			case ACTION_DO_DELETE:
            {
				// Delete user from AD
				operationResult = adAccountManager -> DeleteUser(wUserName);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					if (operationResult)
						WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. User deleted!");
					else
						WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. Can't delete user!");

					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. Done");
				#endif

				delete adAccountManager;
				return operationResult;
            }

            case ACTION_DO_DISABLE:
            {
				// Disable AD user account
				operationResult = adAccountManager -> DisableAccount(wUserName);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					if (operationResult)
						WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. User disabled!");
					else
						WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. Can't disable user!");

					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. Done");
				#endif

				delete adAccountManager;
				return operationResult;
			}
			
			default: 
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. Do nothing");
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. Done");
				#endif

				delete adAccountManager;
				return true;
			}
		}
	}
    else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. User does not exist!");
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnDelete. Done");
		#endif

		delete adAccountManager;
		return false;
	}
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : SyncADAccountOnInsert

   Parameters :
			Input : 
				userName - user name
				userPassword - password
				action - action on delete
				settingsString - settings string

	Return : TRUE - if success

	Description :  Synchronize user accounts on insert user 
	               account record to the database

*****************************************************************/
bool UserAccountsSynchronizer :: SyncADAccountOnInsert(char * userName, char * userPassword, int action, char * settingsString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Start");
	#endif

	// Check action
    if (action == ACTION_DO_NOTHING)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Do nothing");
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Done");
		#endif

		return true;
	}
	
	// result flag
	bool operationResult = false;
	            
	// Check action and input user
	if (action == ACTION_DO_INSERT)
    {
		ADAccountManager * adAccountManager = GetADAccountManager(settingsString);

		WCHAR wUserName[USER_NAME_LEN];
		WCHAR wUserPassword[PWD_LEN];
		
		mbstowcs(wUserName, userName, USER_NAME_LEN);
		mbstowcs(wUserPassword, userPassword, PWD_LEN);

        // Create new AD user
		if (!adAccountManager -> IsUserExisting(wUserName))
		{
			operationResult = adAccountManager -> CreateNewUser(wUserName, wUserPassword);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. User does not exist");

				if (operationResult)
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Created new user account");
				else
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Can't create new user account");

				WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Done");
			#endif
			
			delete adAccountManager;
			return operationResult;
		}
		else
        {
			operationResult = adAccountManager -> EnableAccount(wUserName);
			
			if (operationResult)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Account enabled");
				#endif

				operationResult = adAccountManager -> SetUserPassword(wUserName, wUserPassword);
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Can't enable user account");
				#endif
			}
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Done");
			#endif
			
			delete adAccountManager;
			return operationResult;
		}
    }
    else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Do nothing");
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnInsert. Done");
		#endif
				
		return false;
	}
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : SyncADAccountOnUpdate

   Parameters :
			Input : 
				userName - user name
				userPassword - password
				newUserName - new user name
				newUserPassword - new password
				action - action on delete
				settingsString - settings string

	Return : TRUE - if success

	Description :  Synchronize user accounts on update user 
	               account record in the database

*****************************************************************/
bool UserAccountsSynchronizer :: SyncADAccountOnUpdate(char * userName, char * userPassword, char * newUserName, char * newUserPassword, int action, char * settingsString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Start");
	#endif

	// Check action
    if (action == ACTION_DO_NOTHING)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Do nothing");
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Done");
		#endif

		return true;
	}
	
	// result flag
	bool operationResult = false;

	WCHAR wUserName[USER_NAME_LEN];
	WCHAR wUserPassword[PWD_LEN];
	WCHAR wNewUserName[USER_NAME_LEN];
	WCHAR wNewUserPassword[PWD_LEN];
		
	mbstowcs(wUserName, userName, USER_NAME_LEN);
	mbstowcs(wUserPassword, userPassword, PWD_LEN);
	mbstowcs(wNewUserName, newUserName, USER_NAME_LEN);
	mbstowcs(wNewUserPassword, newUserPassword, PWD_LEN);

	// Check action and input user
    if (action == ACTION_DO_UPDATE)
	{
		ADAccountManager * adAccountManager = GetADAccountManager(settingsString);

		if (adAccountManager -> IsUserExisting(wUserName))
        {
			operationResult = adAccountManager -> EnableAccount(wUserName);

			// Set new password
			if (operationResult)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Account enabled");
				#endif

				if (strcmp(userPassword, newUserPassword) != 0)
				{
					operationResult = adAccountManager -> SetUserPassword(wUserName, wNewUserPassword);

					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
						WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Try to set new password");

						if (operationResult)
							WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. New password saved");
						else
							WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Can't set new user password");
					#endif
				}
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Can't enable user account");
				#endif
			}
			
            // Change user name
			if (strcmp(userName, newUserName) != 0)
			{
				operationResult = adAccountManager -> ChangeUserName(wUserName, wNewUserName);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Try to set new user name");

					if (operationResult)
						WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. New user name saved");
					else
						WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Can't set new user name");
				#endif
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Done");
			#endif
						
			delete adAccountManager;
			return operationResult;
		}
        else
		{
			// Create new AD account
            operationResult = adAccountManager -> CreateNewUser(wUserName, wUserPassword);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. User does not exist");

				if (operationResult)
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Created new user account");
				else
					WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Can't create new user account");

				WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Done");
			#endif
			
			delete adAccountManager;
			return operationResult;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Do nothing");
			WriteToLog("UserAccountsSynchronizer : SyncADAccountOnUpdate. Done");
		#endif
					
		return false;
	}
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : ValidateADAccount

   Parameters :
			Input : 
				userName - user name
				userPassword - password
				settingsString - settings string

	Return : TRUE - if success

	Description :  Validation of AD user account

*****************************************************************/
bool UserAccountsSynchronizer :: ValidateADAccount(char * userName, char * userPassword, char * settingsString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : ValidateADAccount. Start");
	#endif

	// Get account manager
	ADAccountManager * adAccountManager = GetADAccountManager(settingsString);

	// Convert to wide string
	WCHAR wUserName[USER_NAME_LEN];
	WCHAR wUserPwd[PWD_LEN];
	mbstowcs(wUserName, userName, USER_NAME_LEN);
	mbstowcs(wUserPwd, userPassword, PWD_LEN);
    
	bool validationResult = adAccountManager -> ValidateCredentials(wUserName, wUserPwd);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		if(validationResult)
			WriteToLog("UserAccountsSynchronizer : ValidateADAccount. Account validated!");
		else
			WriteToLog("UserAccountsSynchronizer : ValidateADAccount. Account not validated!");
	#endif

	delete adAccountManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : ValidateADAccount. Done");
	#endif

	return validationResult;
}

#pragma endregion

#pragma region Groups

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : SyncADGroupOnDelete

   Parameters :
			Input : 
				groupName - group name
				action - action on delete
				settingsString - settings string

	Return : TRUE - if success

	Description :  Synchronize user group on delete user 
				   group record from database

*****************************************************************/
bool UserAccountsSynchronizer :: SyncADGroupOnDelete(char * groupName, int action, char * settingsString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SyncADGroupOnDelete. Start");
	#endif

	// Get account manager
	ADAccountManager * adAccountManager = GetADAccountManager(settingsString);

	// Convert to wide string
	WCHAR wGroupName[OU_NAME_LEN];
	mbstowcs(wGroupName, groupName, OU_NAME_LEN);

	// result flag
	bool operationResult = false;

    // Check input group
	if (adAccountManager -> IsGroupExisting(wGroupName))
    {
		// Check action
        switch (action)
        {
			case ACTION_DO_DELETE:
            {
				// Delete user from AD
				operationResult = adAccountManager -> DeleteGroup(wGroupName);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					if (operationResult)
						WriteToLog("UserAccountsSynchronizer : SyncADGroupOnDelete. Group deleted!");
					else
						WriteToLog("UserAccountsSynchronizer : SyncADGroupOnDelete. Can't delete group!");

					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnDelete. Done");
				#endif

				delete adAccountManager;
				return operationResult;
            }

			default: 
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnDelete. Do nothing");
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnDelete. Done");
				#endif

				delete adAccountManager;
				return true;
			}
		}
	}
    else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnDelete. Group does not exists!");
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnDelete. Done");
		#endif

		delete adAccountManager;
		return false;
	}
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : SyncADGroupOnInsert

   Parameters :
			Input : 
				groupName - group name
				groupSettings - group settings
				groupDescription - group description
				action - action on delete
				settingsString - settings string

	Return : TRUE - if success

	Description :  Synchronize user group on insert user 
	               group record to the database

*****************************************************************/
bool UserAccountsSynchronizer :: SyncADGroupOnInsert(char * groupName, char * groupSettings, char * groupDescription, int action, char * settingsString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Start");
	#endif

	// Check action
    if (action == ACTION_DO_NOTHING)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Do nothing");
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Done");
		#endif

		return true;
	}
	
	// result flag
	bool operationResult = false;
	            
	// Check action and input user
	if (action == ACTION_DO_INSERT)
    {
		ADAccountManager * adAccountManager = GetADAccountManager(settingsString);

		// Parse group settings
		ADSettingsParser * adSettingsParser = new ADSettingsParser(zSynchronizeDllDefinition.dllID, logWriter);

		char groupScopeName[OU_NAME_LEN];
		char groupTypeName[OU_NAME_LEN];

		// Get group scope
		adSettingsParser -> GetGroupScopeName(groupSettings, groupScopeName);

		// Get group type
		adSettingsParser -> GetGroupTypeName(groupSettings, groupTypeName);

		delete adSettingsParser;

		WCHAR wGroupName[OU_NAME_LEN];
		WCHAR wGroupScopeName[OU_NAME_LEN];
		WCHAR wGroupTypeName[OU_NAME_LEN];
		WCHAR wGroupDescription[GROUP_DESCRIPTION_LEN];
		
		mbstowcs(wGroupName, groupName, OU_NAME_LEN);
		mbstowcs(wGroupScopeName, groupScopeName, OU_NAME_LEN);
		mbstowcs(wGroupTypeName, groupTypeName, OU_NAME_LEN);
		mbstowcs(wGroupDescription, groupDescription, GROUP_DESCRIPTION_LEN);

        // Create new AD group
		if (!adAccountManager -> IsGroupExisting(wGroupName))
		{
			operationResult = adAccountManager -> CreateNewGroup(wGroupName, wGroupDescription, wGroupScopeName, wGroupTypeName);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Group does not exist");

				if (operationResult)
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Created new group account");
				else
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Can't create new group account");

				WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Done");
			#endif
			
			delete adAccountManager;
			return operationResult;
		}
		else
        {
			operationResult = adAccountManager -> ChangeGroupParameters(wGroupName, wGroupDescription, wGroupScopeName, wGroupTypeName);
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				if (operationResult)
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Group account changed!");
				else
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Can't change group account");

				WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Done");
			#endif
			
			delete adAccountManager;
			return operationResult;
		}
    }
    else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Do nothing");
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnInsert. Done");
		#endif
				
		return false;
	}
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : SyncADGroupOnUpdate

   Parameters :
			Input : 
				groupName - group name
				groupSettings - group settings
				groupDescription - group description
				newGroupName - group name
				newGroupSettings - group settings
				newGroupDescription - group description
				action - action on delete
				settingsString - settings string

	Return : TRUE - if success

	Description :  Synchronize user group on update user 
	               group record in the database

*****************************************************************/
bool UserAccountsSynchronizer::SyncADGroupOnUpdate(char * groupName, char * groupSettings, char * groupDescription, char * newGroupName, char * newGroupSettings, char * newGroupDescription, int action, char * settingsString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Start");
	#endif

	// Check action
    if (action == ACTION_DO_NOTHING)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Do nothing");
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Done");
		#endif

		return true;
	}
	
	// result flag
	bool operationResult = false;

	// Check action and input user
    if (action == ACTION_DO_UPDATE)
	{
		ADAccountManager * adAccountManager = GetADAccountManager(settingsString);

		// Parse group settings
		ADSettingsParser * adSettingsParser = new ADSettingsParser(zSynchronizeDllDefinition.dllID, logWriter);

		char newGroupScopeName[OU_NAME_LEN];
		char newGroupTypeName[OU_NAME_LEN];

		// Get group scope
		adSettingsParser -> GetGroupScopeName(groupSettings, newGroupScopeName);

		// Get group type
		adSettingsParser -> GetGroupTypeName(groupSettings, newGroupTypeName);

		delete adSettingsParser;

		WCHAR wGroupName[OU_NAME_LEN];
		WCHAR wNewGroupName[OU_NAME_LEN];
		WCHAR wNewGroupScopeName[OU_NAME_LEN];
		WCHAR wNewGroupTypeName[OU_NAME_LEN];
		WCHAR wGroupSettings[OU_NAME_LEN];
		WCHAR wNewGroupSettings[OU_NAME_LEN];
		WCHAR wGroupDescription[GROUP_DESCRIPTION_LEN];
		WCHAR wNewGroupDescription[GROUP_DESCRIPTION_LEN];
		

		mbstowcs(wGroupName, groupName, OU_NAME_LEN);
		mbstowcs(wNewGroupName, newGroupName, OU_NAME_LEN);

		mbstowcs(wGroupName, groupName, OU_NAME_LEN);
		mbstowcs(wNewGroupName, newGroupName, OU_NAME_LEN);

		mbstowcs(wGroupSettings, groupSettings, OU_NAME_LEN);
		mbstowcs(wNewGroupSettings, newGroupSettings, OU_NAME_LEN);

		mbstowcs(wGroupDescription, groupDescription, GROUP_DESCRIPTION_LEN);
		mbstowcs(wNewGroupDescription, newGroupDescription, GROUP_DESCRIPTION_LEN);

		mbstowcs(wNewGroupScopeName, newGroupScopeName, OU_NAME_LEN);
		mbstowcs(wNewGroupTypeName, newGroupTypeName, OU_NAME_LEN);
		

		if (adAccountManager -> IsGroupExisting(wGroupName))
        {
			operationResult = true;
			
			// Change group params
			if (strcmp(groupSettings, newGroupSettings) != 0)
			{
				operationResult = adAccountManager -> ChangeGroupParameters(wGroupName, wNewGroupDescription, wNewGroupScopeName, wNewGroupTypeName) && operationResult;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Try to set new group parameters");

					if (operationResult)
						WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. New group parameters saved");
					else
						WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Can't set new group group parameters");
				#endif

			}

			// Change group name
			if (strcmp(groupName, newGroupName) != 0)
			{
				operationResult = adAccountManager -> ChangeGroupName(wGroupName, wNewGroupName) && operationResult;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Try to set new group name");

					if (operationResult)
						WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. New name saved");
					else
						WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Can't set new group name");
				#endif
			}
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Done");
			#endif
						
			delete adAccountManager;
			return operationResult;
		}
        else
		{
			// Create new AD group account
			operationResult = adAccountManager -> CreateNewGroup(wNewGroupName, wNewGroupDescription, wNewGroupScopeName, wNewGroupTypeName);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Group does not exist");

				if (operationResult)
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Created new group account");
				else
					WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Can't create new group account");

				WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Done");
			#endif
			
			delete adAccountManager;
			return operationResult;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Do nothing");
			WriteToLog("UserAccountsSynchronizer : SyncADGroupOnUpdate. Done");
		#endif
					
		return false;
	}
}

/****************************************************************

	Class : UserAccountsSynchronizer

	Method : SyncUserGroupMember

	Parameters:
			Input:
				userID - userID
				groupID - groupID

	Return : TRUE - if success

	Description :  Synchronize user/group membership

*****************************************************************/
bool UserAccountsSynchronizer :: SyncUserGroupMember(int userID, int groupID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SyncUserGroupMember. Start");
	#endif
	
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT UserGroupAuthSystems.GroupName, UserAccounts.UserName, AuthSystems.AuthSystemTypeID, AuthSystems.SettingsString, AuthSystems.MoveGroupUsers \
					 FROM UserGroupAuthSystems, UserAccounts, AuthSystems \
					 WHERE (UserGroupAuthSystems.GroupID = %d) AND \
						   (UserAccounts.UserID = %d) AND \
						   (UserGroupAuthSystems.AuthSystemID = UserAccounts.AuthSystemID) AND \
						   (UserGroupAuthSystems.AuthSystemID = AuthSystems.ID) AND \
						   (UserAccounts.AuthSystemID = AuthSystems.ID)", groupID, userID);

		// Execute SQl query
		ResultSet * usersGroupsResult = dbManager -> ExecuteSelectQuery(sql);

		unsigned char groupNameBuf[ENCRYPTED_DATA_SIZE];
		int groupNameLenBuf = 0;
		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;
		int authSystemTypeBuf = 0;
		unsigned char settingsStringBuf[ENCRYPTED_DATA_SIZE];
		int settingsStringLenBuf = 0;
		int moveUsersBuf = 0;
		
		int userNameLen = 0;
		char userName[USER_NAME_LEN];

		int groupNameLen = 0;
		char groupName[USER_NAME_LEN];

		int settingsStringLen = 0;
		char settingsString[SETTINGS_STRING_LEN];

		bool syncResult = true;

		// Bind data
		usersGroupsResult -> Bind(1, groupNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersGroupsResult -> Bind(2, &groupNameLenBuf, sizeof(groupNameLenBuf), SQL_C_LONG);
		usersGroupsResult -> Bind(3, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersGroupsResult -> Bind(4, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);
		usersGroupsResult -> Bind(5, &authSystemTypeBuf, sizeof(authSystemTypeBuf), SQL_C_LONG);
		usersGroupsResult -> Bind(6, settingsStringBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersGroupsResult -> Bind(7, &settingsStringLenBuf, sizeof(settingsStringLenBuf), SQL_C_LONG);
		usersGroupsResult -> Bind(8, &moveUsersBuf, sizeof(moveUsersBuf), SQL_C_LONG);
		

		// Retrieve records
		while (usersGroupsResult -> MoveNext())
		{
			// Decrypt data
			if(encryptor -> UnPackAndDecryptSecurityData(userNameBuf, userNameLenBuf, (unsigned char *)userName, USER_NAME_LEN, &userNameLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncUserGroupMember. Can't decrypt user name!");
				#endif
			}
			else
			{
				userName[userNameLen] = 0;
			}

			if (encryptor -> UnPackAndDecryptSecurityData(groupNameBuf, groupNameLenBuf, (unsigned char *)groupName, PWD_LEN, &groupNameLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncUserGroupMember. Can't decrypt group name!");
				#endif
			}
			else
			{
				groupName[groupNameLen] = 0;
			}

			if (encryptor -> UnPackAndDecryptSecurityData(settingsStringBuf, settingsStringLenBuf, (unsigned char *)settingsString, USER_NAME_LEN, &settingsStringLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : SyncUserGroupMember. Can't decrypt settings string!");
				#endif
			}
			else
			{
				settingsString[settingsStringLen] = 0;
			}

			// Synchronize user account
			switch(authSystemTypeBuf)
			{
				case UAC_AD :
					{
						if (moveUsersBuf)
						{
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
								WriteToLog("UserAccountsSynchronizer : SyncUserGroupMember. Sync AD user\group");
							#endif

							ADAccountManager * adAccountManager = GetADAccountManager(settingsString);
							
							WCHAR wGroupName[OU_NAME_LEN];
							WCHAR wUserName[OU_NAME_LEN];
							
							mbstowcs(wGroupName, groupName, OU_NAME_LEN);
							mbstowcs(wUserName, userName, OU_NAME_LEN);

							if (!(adAccountManager -> IsUserGroupMember(wUserName, wGroupName)))
							{
								syncResult =  adAccountManager -> AddUserToGroup(wUserName, wGroupName) && syncResult;
							}

							delete adAccountManager;
						}
					}
			}

			// Clear buffers
			userName[0] = 0;
			groupName[0] = 0;
			settingsString[0] = 0;
			userNameBuf[0] = 0;
			userNameLenBuf = 0;
			groupNameBuf[0] = 0;
			groupNameLenBuf = 0;
			settingsStringBuf[0] = 0;
			settingsStringLenBuf = 0;
			authSystemTypeBuf = 0;
			moveUsersBuf = 0;
		}

		delete usersGroupsResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncUserGroupMember. Done");
		#endif

		return syncResult;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

/****************************************************************

	Class : UserAccountsSynchronizer

	Method : SyncUserGroupMembers
	
	Return : TRUE - if success

	Description :  Synchronize user/group membership

*****************************************************************/
bool UserAccountsSynchronizer :: SyncUserGroupMembers(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SyncUserGroupMembers. Start");
	#endif
	
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT UserGroupUsers.UserID, UserGroupUsers.GroupID FROM UserGroupUsers");

		// Execute SQl query
		ResultSet * usersGroupsResult = dbManager -> ExecuteSelectQuery(sql);

		int userIDBuf = 0;
		int groupIDBuf = 0;
				
		bool syncResult = true;

		// Bind data
		usersGroupsResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);
		usersGroupsResult -> Bind(2, &groupIDBuf, sizeof(groupIDBuf), SQL_C_LONG);

		// Retrieve records
		while (usersGroupsResult -> MoveNext())
		{
			syncResult = SyncUserGroupMember(userIDBuf, groupIDBuf) && syncResult;

			// Clear buffers
			userIDBuf = 0;
			groupIDBuf = 0;
		}

		delete usersGroupsResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : SyncUserGroupMember. Done");
		#endif

		return syncResult;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

#pragma endregion

#pragma endregion

#pragma region General synchronization

/****************************************************************

	Class : UserAccountsSynchronizer

	Method : ForcedSynchronization

	Return : TRUE - if success

	Description :  General forces synchronization

*****************************************************************/
bool UserAccountsSynchronizer :: ForcedSynchronization(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : ForcedSynchronization. Start");
	#endif

	bool usersSyncRes = ForcedUsersSynchronization();
	bool groupsSyncRes = ForcedGroupsSynchronization();
	bool grMemSyncRes = SyncUserGroupMembers();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : ForcedSynchronization. Save sync time");
	#endif

	// Get current time
	char date[STR_VALUE_LEN];
	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);
	strftime(date, STR_VALUE_LEN, "%m/%d/%Y %H:%M:%S", timeinfo); 

	// Save last sync time
	SettingsManager * settingsManager = new SettingsManager(zSynchronizeDllDefinition.dllID);
	settingsManager -> SetLastSyncTime(date);
	delete settingsManager;	

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : ForcedSynchronization. Done");
	#endif

	return usersSyncRes && groupsSyncRes && grMemSyncRes;;
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : ForcedUsersSynchronization

   Return : TRUE - if success

   Description :  Forces synchronization of all user accounts

*****************************************************************/
bool UserAccountsSynchronizer :: ForcedUsersSynchronization(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : ForcedUsersSynchronization. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT UserAccounts.UserName, DATALENGTH(UserAccounts.UserName),\
							UserAccounts.Password, DATALENGTH(UserAccounts.Password),\
							AuthSystems.SettingsString, DATALENGTH(AuthSystems.SettingsString),\
							AuthSystems.OnInsertAction, AuthSystems.AuthSystemTypeID\
					FROM UserAccounts, AuthSystems\
					WHERE (UserAccounts.AuthSystemID = AuthSystems.ID)");

		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;
		unsigned char userPwdBuf[ENCRYPTED_DATA_SIZE];
		int userPwdLenBuf = 0;
		unsigned char settingsStringBuf[ENCRYPTED_DATA_SIZE];
		int settingsStringLenBuf = 0;
		int actionBuf = 0;
		int authSystemTypeBuf = 0;

		int userNameLen = 0;
		char userName[USER_NAME_LEN];

		int userPasswordLen = 0;
		char userPassword[PWD_LEN];

		int settingsStringLen = 0;
		char settingsString[SETTINGS_STRING_LEN];

		bool syncResult = true;

		// Bind data
		usersResult -> Bind(1, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(2, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);
		usersResult -> Bind(3, userPwdBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(4, &userPwdLenBuf, sizeof(userPwdLenBuf), SQL_C_LONG);
		usersResult -> Bind(5, settingsStringBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(6, &settingsStringLenBuf, sizeof(settingsStringLenBuf), SQL_C_LONG);
		usersResult -> Bind(7, &actionBuf, sizeof(actionBuf), SQL_C_LONG);
		usersResult -> Bind(8, &authSystemTypeBuf, sizeof(authSystemTypeBuf), SQL_C_LONG);

		// Retrieve records
		while (usersResult -> MoveNext())
		{
			// Decrypt data
			if(encryptor -> UnPackAndDecryptSecurityData(userNameBuf, userNameLenBuf, (unsigned char *)userName, USER_NAME_LEN, &userNameLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ForcedUsersSynchronization. Can't decrypt user name!");
				#endif
			}
			else
			{
				userName[userNameLen] = 0;
			}

			if (encryptor -> UnPackAndDecryptSecurityData(userPwdBuf, userPwdLenBuf, (unsigned char *)userPassword, PWD_LEN, &userPasswordLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ForcedUsersSynchronization. Can't decrypt user password!");
				#endif
			}
			else
			{
				userPassword[userPasswordLen] = 0;
			}

			if (encryptor -> UnPackAndDecryptSecurityData(settingsStringBuf, settingsStringLenBuf, (unsigned char *)settingsString, USER_NAME_LEN, &settingsStringLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ForcedUsersSynchronization. Can't decrypt settings string!");
				#endif
			}
			else
			{
				settingsString[settingsStringLen] = 0;
			}

			// Synchronize user account
			switch(authSystemTypeBuf)
			{
				case UAC_AD :
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
							WriteToLog("UserAccountsSynchronizer : ForcedUsersSynchronization. Sync AD account");
						#endif

						syncResult = SyncADAccountOnInsert(userName, userPassword, actionBuf, settingsString) && syncResult;

						break;
					}
			}

			// Clear buffers
			userName[0] = 0;
			userPassword[0] = 0;
			settingsString[0] = 0;
			userNameBuf[0] = 0;
			userNameLenBuf = 0;
			userPwdBuf[0] = 0;
			userPwdLenBuf = 0;
			settingsStringBuf[0] = 0;
			settingsStringLenBuf = 0;
			authSystemTypeBuf = 0;
		}

		delete usersResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : ForcedUsersSynchronization. Done");
		#endif

		return syncResult;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : ForcedGroupsSynchronization

   Return : TRUE - if success

   Description :  Forces synchronization of all groups accounts

*****************************************************************/
bool UserAccountsSynchronizer :: ForcedGroupsSynchronization(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : ForcedGroupsSynchronization. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT UserGroupAuthSystems.GroupName, DATALENGTH(UserGroupAuthSystems.GroupName),\
							 UserGroupAuthSystems.GroupSettings, DATALENGTH(UserGroupAuthSystems.GroupSettings),\
							 UserGroups.Description, DATALENGTH(UserGroups.Description),\
							 AuthSystems.SettingsString, DATALENGTH(AuthSystems.SettingsString),\
							 AuthSystems.OnInsertAction, AuthSystems.AuthSystemTypeID\
					 FROM UserGroupAuthSystems, AuthSystems, UserGroups\
					 WHERE((UserGroupAuthSystems.AuthSystemID = AuthSystems.ID) AND(UserGroupAuthSystems.GroupID = UserGroups.ID))");

		// Execute SQl query
		ResultSet * groupsResult = dbManager -> ExecuteSelectQuery(sql);

		unsigned char groupNameBuf[ENCRYPTED_DATA_SIZE];
		int groupNameLenBuf = 0;
		unsigned char groupSettingsBuf[ENCRYPTED_DATA_SIZE];
		int groupSettingsLenBuf = 0;
		unsigned char groupDescriptionBuf[ENCRYPTED_DATA_SIZE];
		int groupDescriptionLenBuf = 0;
		unsigned char settingsStringBuf[ENCRYPTED_DATA_SIZE];
		int settingsStringLenBuf = 0;
		int actionBuf = 0;
		int authSystemTypeBuf = 0;

		int groupNameLen = 0;
		char groupName[USER_NAME_LEN] = "";

		int groupDescriptionLen = 0;
		char groupDescription[GROUP_DESCRIPTION_LEN] = "";

		int groupSettingsLen = 0;
		char groupSettings[PWD_LEN] = "";

		int settingsStringLen = 0;
		char settingsString[SETTINGS_STRING_LEN] = "";

		bool syncResult = true;

		// Bind data
		groupsResult -> Bind(1, groupNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		groupsResult -> Bind(2, &groupNameLenBuf, sizeof(groupNameLenBuf), SQL_C_LONG);
		groupsResult -> Bind(3, groupSettingsBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		groupsResult -> Bind(4, &groupSettingsLenBuf, sizeof(groupSettingsLenBuf), SQL_C_LONG);
		groupsResult -> Bind(5, groupDescriptionBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		groupsResult -> Bind(6, &groupDescriptionLenBuf, sizeof(groupDescriptionLenBuf), SQL_C_LONG);
		groupsResult -> Bind(7, settingsStringBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		groupsResult -> Bind(8, &settingsStringLenBuf, sizeof(settingsStringLenBuf), SQL_C_LONG);
		groupsResult -> Bind(9, &actionBuf, sizeof(actionBuf), SQL_C_LONG);
		groupsResult -> Bind(10, &authSystemTypeBuf, sizeof(authSystemTypeBuf), SQL_C_LONG);

		// Retrieve records
		while (groupsResult -> MoveNext())
		{
			// Decrypt data
			if (encryptor -> UnPackAndDecryptSecurityData(groupNameBuf, groupNameLenBuf, (unsigned char *)groupName, USER_NAME_LEN, &groupNameLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ForcedGroupsSynchronization. Can't decrypt group name!");
				#endif
			}
			else
			{
				groupName[groupNameLen] = 0;
			}

			if (encryptor -> UnPackAndDecryptSecurityData(groupSettingsBuf, groupSettingsLenBuf, (unsigned char *)groupSettings, PWD_LEN, &groupSettingsLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ForcedGroupsSynchronization. Can't decrypt group settings!");
				#endif
			}
			else
			{
				groupSettings[groupSettingsLen] = 0;
			}

			if (encryptor -> UnPackAndDecryptSecurityData(groupDescriptionBuf, groupDescriptionLenBuf, (unsigned char *)groupDescription, GROUP_DESCRIPTION_LEN, &groupDescriptionLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ForcedGroupsSynchronization. Can't decrypt group description!");
				#endif
			}
			else
			{
				groupDescription[groupDescriptionLen] = 0;
			}

			if (encryptor -> UnPackAndDecryptSecurityData(settingsStringBuf, settingsStringLenBuf, (unsigned char *)settingsString, USER_NAME_LEN, &settingsStringLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ForcedGroupsSynchronization. Can't decrypt settings string!");
				#endif
			}
			else
			{
				settingsString[settingsStringLen] = 0;
			}

			// Synchronize user account
			switch(authSystemTypeBuf)
			{
				case UAC_AD :
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
							WriteToLog("UserAccountsSynchronizer : ForcedGroupsSynchronization. Sync AD group account");
						#endif

						syncResult = SyncADGroupOnInsert(groupName, groupSettings, groupDescription, actionBuf, settingsString) && syncResult;
						break;
					}
			}

			// Clear buffers
			groupName[0] = 0;
			groupSettings[0] = 0;
			settingsString[0] = 0;
			groupNameBuf[0] = 0;
			groupNameLenBuf = 0;
			groupSettingsBuf[0] = 0;
			groupSettingsLenBuf = 0;
			groupDescriptionLen = 0;
			groupDescription[0] = 0;
			settingsStringBuf[0] = 0;
			settingsStringLenBuf = 0;
			authSystemTypeBuf = 0;
		}

		delete groupsResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : ForcedGroupsSynchronization. Done");
		#endif

		return syncResult;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : ReverseSyncAccount

   Parameters :
			Input : 
				userName - user ID
				userPassword - user password
				authSystemID - ID of authentication system

	Return : TRUE - if success

	Description : Reverse synchronization of user acocunt

*****************************************************************/
bool UserAccountsSynchronizer :: ReverseSyncAccount(char * userName, char * userPassword, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT AuthSystems.SettingsString, DATALENGTH(AuthSystems.SettingsString), \
					         AuthSystems.AuthSystemTypeID\
						FROM AuthSystems\
						WHERE AuthSystems.ID = %d", authSystemID);

		// Execute SQl query
		ResultSet * authSystemResult = dbManager -> ExecuteSelectQuery(sql);

		unsigned char settingsStringBuf[ENCRYPTED_DATA_SIZE];
		int settingsStringLenBuf = 0;
		int authSystemTypeBuf = 0;

		int settingsStringLen = 0;
		char settingsString[SETTINGS_STRING_LEN];

		// Bind data
		authSystemResult -> Bind(1, settingsStringBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		authSystemResult -> Bind(2, &settingsStringLenBuf, sizeof(settingsStringLenBuf), SQL_C_LONG);
		authSystemResult -> Bind(3, &authSystemTypeBuf, sizeof(authSystemTypeBuf), SQL_C_LONG);

		if (authSystemResult -> MoveFirst())
		{
			if (encryptor -> UnPackAndDecryptSecurityData(settingsStringBuf, settingsStringLenBuf, (unsigned char *)settingsString, SETTINGS_STRING_LEN, &settingsStringLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't decrypt settings string!");
				#endif
			}
			else
			{
				settingsString[settingsStringLen] = 0;
			}

			delete authSystemResult;
		}
		else
		{
			delete authSystemResult;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't find authentication system!");
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
			#endif

			return false;
		}

		// Prepare sql query
		sprintf(sql, "SELECT UserAccounts.UserID, UserAccounts.UserName, DATALENGTH(UserAccounts.UserName)\
						FROM UserAccounts WHERE (UserAccounts.AuthSystemID = %d)", authSystemID);
		
		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		int userID = -1;
		int userIDBuf = userID;
		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;

		// Bind data
		usersResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);
		usersResult -> Bind(2, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(3, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);

		// Retrieve records
		while (usersResult -> MoveNext())
		{
			unsigned char decryptedUserName[NAME_LEN];
			int decryptedUserNameLen;
			
			if (encryptor -> UnPackAndDecryptSecurityData(userNameBuf, userNameLenBuf, decryptedUserName, NAME_LEN, &decryptedUserNameLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Get user ID. Can't decrypt user name!");
				#endif
			}
			else
			{
				decryptedUserName[decryptedUserNameLen] = 0;
				if (strcmp(userName, (char *)decryptedUserName) == 0)
				{
					userID = userIDBuf;
					break;
				}
			}

			userIDBuf = -1;
			userNameBuf[0] = 0;
			userNameLenBuf = 0;
		}

		delete usersResult;

		if (userID != -1)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. This user already synchronized!");
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
			#endif

			return true;
		}

		// Synchronize user account
		switch(authSystemTypeBuf)
		{
			case UAC_AD :
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
						WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Sync AD account");
					#endif

					if (ValidateADAccount(userName, userPassword, settingsString))
					{
						unsigned char encUserName[ENCRYPTED_DATA_SIZE];
						int encUserNameLen = 0;
						int userNameLen = strlen(userName);

						unsigned char encUserPassword[ENCRYPTED_DATA_SIZE];
						int encUserPasswordLen = 0;
						int userPasswordLen = strlen(userPassword);

						if (encryptor -> EncryptAndPackSecurityData((unsigned char *)userName, userNameLen, encUserName, ENCRYPTED_DATA_SIZE, &encUserNameLen))
						{
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
								WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't encrypt user name!");
							#endif
						}

						if (encryptor -> EncryptAndPackSecurityData((unsigned char *)userPassword, userPasswordLen, encUserPassword, ENCRYPTED_DATA_SIZE, &encUserPasswordLen))
						{
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
								WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't encrypt user password!");
							#endif
						}

						char hexUserName[ENCRYPTED_DATA_SIZE];
						char hexUserPassword[ENCRYPTED_DATA_SIZE];
							
						if (!(encryptor -> BinToHexStr(encUserName, encUserNameLen, hexUserName, ENCRYPTED_DATA_SIZE)))
						{
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
								WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't get user name hex form!");
							#endif
						}

						if (!(encryptor -> BinToHexStr(encUserPassword, encUserPasswordLen, hexUserPassword, ENCRYPTED_DATA_SIZE)))
						{
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
								WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't get user password hex form!");
							#endif
						}


						// Prepare sql query
						sprintf(sql, "SELECT Users.ID, Users.UserName, DATALENGTH(Users.UserName) FROM Users");
		
						// Execute SQl query
						ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

						userID = -1;
						userIDBuf = userID;
						userNameLenBuf = 0;

						// Bind data
						usersResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);
						usersResult -> Bind(2, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
						usersResult -> Bind(3, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);

						// Retrieve records
						while (usersResult -> MoveNext())
						{
							unsigned char decryptedUserName[NAME_LEN];
							int decryptedUserNameLen;

							if (encryptor -> UnPackAndDecryptSecurityData(userNameBuf, userNameLenBuf, decryptedUserName, NAME_LEN, &decryptedUserNameLen))
							{
								#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
									WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Get user ID. Can't decrypt user name!");
								#endif
							}
							else
							{
								decryptedUserName[decryptedUserNameLen] = 0;
								if (strcmp(userName, (char *)decryptedUserName) == 0)
								{
									userID = userIDBuf;
									break;
								}
							}

							userIDBuf = -1;
							userNameBuf[0] = 0;
							userNameLenBuf = 0;
						}

						delete usersResult;

						// Prepare sql query
						char insSQL[SQL_SIZE * 2];

						if (userID == -1)
						{
							sprintf(insSQL, "INSERT INTO Users (Name, UserName, PwdAttemptsCount, MaxPwdAttemptsCount, UserToken, NeedStudy, RandomEduCateg, LastSignInDate, PresetID)\
										VALUES (%s, %s, 0, 20, ROUND(RAND()*100, 0, 0), 0, 0, GETDATE(), NULL)", hexUserName, hexUserName);
							
							dbManager ->  Execute(insSQL);

							sprintf(insSQL, "INSERT INTO UserAccounts (UserID, AuthSystemID, UserName, Password, LastSignInDate, PassThru)\
												VALUES ((SELECT IDENT_CURRENT('Users')), %d, %s, %s, GETDATE(), 1)", authSystemID, hexUserName, hexUserPassword);

							dbManager ->  Execute(insSQL);
						}
						else
						{
							sprintf(insSQL, "INSERT INTO UserAccounts (UserID, AuthSystemID, UserName, Password, LastSignInDate, PassThru)\
												VALUES (%d, %d, %s, %s, GETDATE(), 1)", userID, authSystemID, hexUserName, hexUserPassword);
							
							dbManager ->  Execute(insSQL);
						}

						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
							WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Success!");
							WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
						#endif

						return true;
					}
					else
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
							WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Wrong user credentials!");
							WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
						#endif

						return false;
					}
				}

			default:
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Auth sytem type not recognized!");
					WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
				#endif

				return false;
			}
		}
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : ReverseSyncAccount

   Parameters :
			Input : 
				userName - user ID
				userPassword - user password
				authSystemID - ID of authentication system

	Return : TRUE - if success

	Description : Reverse synchronization of user acocunt

*****************************************************************/
bool UserAccountsSynchronizer :: ReverseSyncAccount(unsigned char * encUserName, int encUserNameLen, unsigned char * encUserPassword, int encUserPasswordLen, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT AuthSystems.SettingsString, DATALENGTH(AuthSystems.SettingsString), \
					         AuthSystems.AuthSystemTypeID\
						FROM AuthSystems\
						WHERE AuthSystems.ID = %d", authSystemID);

		// Execute SQl query
		ResultSet * authSystemResult = dbManager -> ExecuteSelectQuery(sql);

		unsigned char settingsStringBuf[ENCRYPTED_DATA_SIZE];
		int settingsStringLenBuf = 0;
		int authSystemTypeBuf = 0;

		int settingsStringLen = 0;
		char settingsString[SETTINGS_STRING_LEN];

		// Bind data
		authSystemResult -> Bind(1, settingsStringBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		authSystemResult -> Bind(2, &settingsStringLenBuf, sizeof(settingsStringLenBuf), SQL_C_LONG);
		authSystemResult -> Bind(3, &authSystemTypeBuf, sizeof(authSystemTypeBuf), SQL_C_LONG);

		if (authSystemResult -> MoveFirst())
		{
			if (encryptor -> UnPackAndDecryptSecurityData(settingsStringBuf, settingsStringLenBuf, (unsigned char *)settingsString, SETTINGS_STRING_LEN, &settingsStringLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't decrypt settings string!");
				#endif
			}
			else
			{
				settingsString[settingsStringLen] = 0;
			}

			delete authSystemResult;
		}
		else
		{
			delete authSystemResult;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't find authentication system!");
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
			#endif

			return false;
		}

		int userNameLen = 0;
		char userName[USER_NAME_LEN];

		if (encryptor -> UnPackAndDecryptSecurityData(encUserName, encUserNameLen, (unsigned char *)userName, USER_NAME_LEN, &userNameLen))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't decrypt user name!");
			#endif
		}
		else
		{
			userName[userNameLen] = 0;
		}

		int userPasswordLen = 0;
		char userPassword[PWD_LEN];

		if (encryptor -> UnPackAndDecryptSecurityData(encUserPassword, encUserPasswordLen, (unsigned char *)userPassword, PWD_LEN, &userPasswordLen))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't decrypt user password!");
			#endif
		}
		else
		{
			userPassword[userPasswordLen] = 0;
		}


		// Prepare sql query
		sprintf(sql, "SELECT UserAccounts.UserID, UserAccounts.UserName, DATALENGTH(UserAccounts.UserName)\
						FROM UserAccounts WHERE (UserAccounts.AuthSystemID = %d)", authSystemID);
		
		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		int userID = -1;
		int userIDBuf = userID;
		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;

		// Bind data
		usersResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);
		usersResult -> Bind(2, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(3, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);

		// Retrieve records
		while (usersResult -> MoveNext())
		{
			unsigned char decryptedUserName[NAME_LEN];
			int decryptedUserNameLen;
			
			if (encryptor -> UnPackAndDecryptSecurityData(userNameBuf, userNameLenBuf, decryptedUserName, NAME_LEN, &decryptedUserNameLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Get user ID. Can't decrypt user name!");
				#endif
			}
			else
			{
				decryptedUserName[decryptedUserNameLen] = 0;
				if (strcmp(userName, (char *)decryptedUserName) == 0)
				{
					userID = userIDBuf;
					break;
				}
			}

			userIDBuf = -1;
			userNameBuf[0] = 0;
			userNameLenBuf = 0;
		}

		delete usersResult;

		if (userID != -1)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. This user already synchronized!");
				WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
			#endif

			return true;
		}
		
		// Synchronize user account
		switch(authSystemTypeBuf)
		{
			case UAC_AD :
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
						WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Sync AD account");
					#endif

					if (ValidateADAccount(userName, userPassword, settingsString))
					{
						char hexUserName[ENCRYPTED_DATA_SIZE];
						char hexUserPassword[ENCRYPTED_DATA_SIZE];
							
						if (!(encryptor -> BinToHexStr(encUserName, encUserNameLen, hexUserName, ENCRYPTED_DATA_SIZE)))
						{
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
								WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't get user name hex form!");
							#endif
						}

						if (!(encryptor -> BinToHexStr(encUserPassword, encUserPasswordLen, hexUserPassword, ENCRYPTED_DATA_SIZE)))
						{
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
								WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Can't get user password hex form!");
							#endif
						}

						// Prepare sql query
						sprintf(sql, "SELECT Users.ID, Users.UserName, DATALENGTH(Users.UserName) FROM Users");
		
						// Execute SQl query
						ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

						userID = -1;
						userIDBuf = userID;
						userNameLenBuf = 0;

						// Bind data
						usersResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);
						usersResult -> Bind(2, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
						usersResult -> Bind(3, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);

						// Retrieve records
						while (usersResult -> MoveNext())
						{
							unsigned char decryptedUserName[NAME_LEN];
							int decryptedUserNameLen;

							if (encryptor -> UnPackAndDecryptSecurityData(userNameBuf, userNameLenBuf, decryptedUserName, NAME_LEN, &decryptedUserNameLen))
							{
								#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
									WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Get user ID. Can't decrypt user name!");
								#endif
							}
							else
							{
								decryptedUserName[decryptedUserNameLen] = 0;
								if (strcmp(userName, (char *)decryptedUserName) == 0)
								{
									userID = userIDBuf;
									break;
								}
							}

							userIDBuf = -1;
							userNameBuf[0] = 0;
							userNameLenBuf = 0;
						}

						delete usersResult;

						// Prepare sql query
						char insSQL[SQL_SIZE * 2];
						
						if (userID == -1)
						{
							sprintf(insSQL, "INSERT INTO Users (Name, UserName, PwdAttemptsCount, MaxPwdAttemptsCount, UserToken, TmpUserToken, NeedStudy, RandomEduCateg, LastSignInDate, PresetID, Email, Phone, EmailPwdReset, SmsPwdReset, PwdResetted, PwdResetDate, PwdResetPeriod, PwdTypeID, Locked)\
										                VALUES (%s, %s, 0, 20, ROUND(RAND()*10000, 0, 0), ROUND(RAND()*10000, 0, 0), 0, 0, GETDATE(), NULL, NULL, NULL, 1, 0, 0, NULL, 24, 1, 0)", hexUserName, hexUserName);
							
							dbManager ->  Execute(insSQL);

							sprintf(insSQL, "INSERT INTO UserAccounts (UserID, AuthSystemID, UserName, Password, LastSignInDate, PassThru)\
												VALUES ((SELECT IDENT_CURRENT('Users')), %d, %s, %s, GETDATE(), 1)", authSystemID, hexUserName, hexUserPassword);

							dbManager ->  Execute(insSQL);
						}
						else
						{
							sprintf(insSQL, "INSERT INTO UserAccounts (UserID, AuthSystemID, UserName, Password, LastSignInDate, PassThru)\
												VALUES (%d, %d, %s, %s, GETDATE(), 1)", userID, authSystemID, hexUserName, hexUserPassword);
							
							dbManager ->  Execute(insSQL);
						}
												
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
							WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Success!");
							WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
						#endif

						return true;
					}
					else
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
							WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Wrong user credentials!");
							WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
						#endif

						return false;
					}
						
				}
				
		default:
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
					WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Auth sytem type not recognized!");
					WriteToLog("UserAccountsSynchronizer : ReverseSyncAccount. Done");
				#endif

				return false;
			}
		}
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

#pragma endregion

#pragma region LOG

/****************************************************************

   Class : UserAccountsSynchronizer

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  UserAccountsSynchronizer :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion

