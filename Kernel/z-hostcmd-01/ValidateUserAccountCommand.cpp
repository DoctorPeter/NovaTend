/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ValidateUserAccountCommand.cpp

   Description :  this module implements methods of
				  class ValidateUserAccountCommand

*****************************************************************/

#include "stdafx.h"
#include "ValidateUserAccountCommand.h"
#include <ResponseValidator.h>
#include <SettingsManager.h>
#include <UserAccountsSynchronizer.h>

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : ValidateUserAccountCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
ValidateUserAccountCommand :: ValidateUserAccountCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserAccountCommand : constructor");
	#endif
}

/****************************************************************

   Class : ValidateUserAccountCommand

   Method : Destructor

*****************************************************************/
ValidateUserAccountCommand :: ~ValidateUserAccountCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserAccountCommand : destructor");
	#endif
}

/****************************************************************

   Class : ValidateUserAccountCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST ValidateUserAccountCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserAccountCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 3) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[0] -> paramDataType == ENCRYPTED_DATA) &&
		(parameters -> paramList[1] -> paramDataType == ENCRYPTED_DATA) &&
		(parameters -> paramList[2] -> paramDataType == DWORD_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
					
		// Unpack data
		int userNameLen = 0;
		unsigned char * userName = serializationManager -> UnpackEncrypted(parameters -> paramList[0], &userNameLen);
		
		int userPwdLen = 0;
		unsigned char * userPwd = serializationManager -> UnpackEncrypted(parameters -> paramList[1], &userPwdLen);
		
		int authSystemID = serializationManager -> UnpackDWORD(parameters -> paramList[2]);
						
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			bool valResult = ValidateUserAccount(userName, userNameLen, userPwd, userPwdLen, authSystemID);

			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackByte((unsigned char)valResult, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("ValidateUserAccountCommand : Execute. Can't create result parameters list!");
		#endif
		
		// Delete user name
		if (userName) free(userName);

		// Delete user password
		if (userPwd) free(userPwd);

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("ValidateUserAccountCommand : Execute. Wrong input parameters!");

		WriteToLog("ValidateUserAccountCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ValidateUserAccountCommand

   Method : ValidateUserAccount

   	Parameters :
			Input : 
				userName - encrypted user name
				userNameLen - length of encrypted user name
				userPassword - encrypted user password
				userPasswordLen - length of encrypted user password
				authSystemID - authentication system ID

   Return : Error code

   Description : Valdate user account

*****************************************************************/
int ValidateUserAccountCommand :: ValidateUserAccount(unsigned char * userName, int userNameLen, unsigned char * userPassword, int userPasswordLen, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserAccountCommand: ValidateUserAccount. Start");
	#endif
	
	int validateResult = RESPONSE_BAD;

	ResponseValidator * responseValidator = new ResponseValidator(zHostCmdDllDefinition.dllID, logWriter);
	validateResult = responseValidator -> ValidateCredentials(userName, userNameLen, userPassword, userPasswordLen, authSystemID);
	delete responseValidator;

	if (validateResult == RESPONSE_BAD)
	{
		bool logonSync = false;

		SettingsManager * settingsManager = new SettingsManager(zHostCmdDllDefinition.dllID);

		if (settingsManager -> GetLogonSyncOnOffFlag(&logonSync) != ERROR_SUCCESS)
			WriteToLog("Server authentication manager : ValidateUserAccount --> Can't get logon sync flag! ");

		delete settingsManager;

		bool syncResult = false;

		if (logonSync)
		{
			UserAccountsSynchronizer * userAccountsSynchronizer = new UserAccountsSynchronizer(zHostCmdDllDefinition.dllID, logWriter);
			syncResult = userAccountsSynchronizer -> ReverseSyncAccount(userName, userNameLen, userPassword, userPasswordLen, authSystemID);
			delete userAccountsSynchronizer;
		}

		if(syncResult)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				WriteToLog("ValidateUserAccountCommand: ValidateUserAccount. Account synchronized!");
			#endif

			validateResult = RESPONSE_OK;

		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				WriteToLog("ValidateUserAccountCommand: ValidateUserAccount.  Account not synchronized!");
			#endif

			validateResult = RESPONSE_BAD;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("ValidateUserAccountCommand: ValidateUserAccount. Account validated! No reverse synchronization!");
		#endif
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserAccountCommand: ValidateUserAccount. Done");
	#endif

	return validateResult - dllUserCheckResult;
}