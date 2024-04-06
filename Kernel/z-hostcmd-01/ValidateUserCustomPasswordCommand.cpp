/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ValidateUserCustomPasswordCommand.cpp

   Description :  this module implements methods of
				  class ValidateUserCustomPasswordCommand

*****************************************************************/

#include "stdafx.h"
#include "ValidateUserCustomPasswordCommand.h"
#include <SymbolBox.h>


// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : ValidateUserCustomPasswordCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
ValidateUserCustomPasswordCommand :: ValidateUserCustomPasswordCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserCustomPasswordCommand : constructor");
	#endif

	responseValidator = new ResponseValidator(zHostCmdDllDefinition.dllID, logWriter);
	contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
}

/****************************************************************

   Class : ValidateUserCustomPasswordCommand

   Method : Destructor

*****************************************************************/
ValidateUserCustomPasswordCommand :: ~ValidateUserCustomPasswordCommand(void)
{
	delete contentManager;
	delete responseValidator;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserCustomPasswordCommand : destructor");
	#endif
}

/****************************************************************

   Class : ValidateUserCustomPasswordCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST ValidateUserCustomPasswordCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserCustomPasswordCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 5) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[3]) &&
		(parameters -> paramList[4]) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[1] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[2] -> paramDataType == ENCRYPTED_DATA) &&
		(parameters -> paramList[3] -> paramDataType == TIMEINFO_DATA) &&
		(parameters -> paramList[4] -> paramDataType == SYMBOL_BOXES_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
					
		// Unpack data
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
		int authSystemID = serializationManager -> UnpackDWORD(parameters -> paramList[1]);

		int userPwdSize = 0;
		unsigned char * userPwd = serializationManager -> UnpackEncrypted(parameters -> paramList[2], &userPwdSize);

		tm * timeinfo = serializationManager -> UnpackTimeinfo(parameters -> paramList[3]);

		PUTF8_STRINGS_MATRIX_LIST symbolBoxesList = serializationManager -> UnpackSymbolBoxesList(parameters -> paramList[4]);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			PUSER_SECURITY_DATA securityData = CreateUserSecurityData();
			int validateResult = ValidateUserCustomPassword(userID, authSystemID, userPwd, userPwdSize, timeinfo, symbolBoxesList, securityData);

			result -> paramCount = 2;
			result -> paramList[0] = serializationManager -> PackDWORD(validateResult, RETURN_CMD_DATA);
			result -> paramList[1] = serializationManager -> PackUserSecurity(securityData, RETURN_CMD_DATA);

			securityData = DeleteUserSecurityData(securityData);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("ValidateUserCustomPasswordCommand : Execute. Can't create result parameters list!");
		#endif
		
		// Delete encrypted user password
		if (userPwd) free(userPwd);

		// Delete time info
		if (timeinfo) free(timeinfo);

		// Delete symbol boxes list
		DeleteSymbolBoxesList(symbolBoxesList);

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("ValidateUserCustomPasswordCommand : Execute. Wrong input parameters!");

		WriteToLog("ValidateUserCustomPasswordCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ValidateUserCustomPasswordCommand

   Method : ValidateUserCustomPassword

   	Parameters :
			Input : 
				userID - user ID
				authSystemID - authentication system ID
				userPassword - encrypted user custom password
				userPasswordLen - encrypted user custom password size
				timeinfo - time info structure
				symbolBoxesList - symbol matrixes list

			Output:
				securityData - user security data

   Return : Error code

   Description : Valdate user custom password

*****************************************************************/
int ValidateUserCustomPasswordCommand :: ValidateUserCustomPassword(int userID, int authSystemID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList, PUSER_SECURITY_DATA securityData)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserCustomPasswordCommand: ValidateUserCustomPassword. Start");
	#endif
	
	int validateResult = RESPONSE_BAD;
	
	if (!securityData)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("ValidateUserCustomPasswordCommand: ValidateUserCustomPassword. Wrong security data container!");
			WriteToLog("ValidateUserCustomPasswordCommand: ValidateUserCustomPassword. Done");
		#endif

		return validateResult;
	}

	PUSER_DESCRIPTOR pUser = NULL;
	PUSER_SECURITY_DATA pSecurityData = NULL;
	
	if (contentManager)
	{
		pUser = contentManager -> GetUserDescriptor(userID);
		pSecurityData = contentManager -> GetUserSecurityData(userID, authSystemID);
	}
	
	if ((pUser) && (pSecurityData) && (responseValidator))
	{
		validateResult = responseValidator -> ValidateCustomPassword(pUser, pSecurityData, userPassword, userPasswordLen, timeinfo, symbolBoxesList);

		if (validateResult == RESPONSE_OK)
			memcpy(securityData, pSecurityData, sizeof(USER_SECURITY_DATA));
	}

	if (contentManager)
	{
		pUser = contentManager -> RemoveUserDescriptor(pUser);
		pSecurityData = contentManager -> RemoveUserSecurityData(pSecurityData);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserCustomPasswordCommand: ValidateUserCustomPassword. Done");
	#endif

	return validateResult - dllUserCheckResult;
}

/****************************************************************

   Class : ValidateUserCustomPasswordCommand

   Method : CreateUserSecurityData

   Return : Pointer to user secutiry data

   Description : Create user security data

*****************************************************************/
PUSER_SECURITY_DATA ValidateUserCustomPasswordCommand :: CreateUserSecurityData(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserCustomPasswordCommand: CreateUserSecurityData");
	#endif

	PUSER_SECURITY_DATA securityData = NULL;

	if (contentManager)
		securityData = contentManager -> CreateUserSecurityData();

	return securityData;
}


/****************************************************************

   Class : ValidateUserCustomPasswordCommand

   Method : DeleteUserSecurityData

   	Parameters :
			Input : 
				securityData - pointer to user secutiry data

   Return : Pointer to user secutiry data

   Description : Delete user security data

*****************************************************************/
PUSER_SECURITY_DATA ValidateUserCustomPasswordCommand :: DeleteUserSecurityData(PUSER_SECURITY_DATA securityData)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserCustomPasswordCommand: CreateUserSecurityData");
	#endif

	if ((securityData) && (contentManager))
		securityData = contentManager -> RemoveUserSecurityData(securityData);
	
	return securityData;
}


/****************************************************************

   Class : ValidateUserCustomPasswordCommand

   Method : DeleteSymbolBoxesList

   	Parameters :
			Input : 
				symbolBoxesList - symbol boxes list

   Return : Pointer to symbol boxes list

   Description : Delete symbol boxes list

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST ValidateUserCustomPasswordCommand :: DeleteSymbolBoxesList(PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserCustomPasswordCommand : DeleteSymbolBoxesList. Start");
	#endif

	try
	{
		// Remove symbol boxes list
		if (symbolBoxesList)
		{
			for(int k = 0; k < symbolBoxesList -> size; k++)
			{
				for(int i = 0; i < symbolBoxesList -> matrixes[k] -> size; i++)
					for(int j = 0; j < symbolBoxesList -> matrixes[k] -> size; j++)
					{
						for(int q = 0 ; q < symbolBoxesList -> matrixes[k] -> strings[i][j] -> length; q++)
							free(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q]);

						free(symbolBoxesList -> matrixes[k] -> strings[i][j]);
					}

				free(symbolBoxesList -> matrixes[k]);
			}

			free(symbolBoxesList);
			symbolBoxesList = NULL;
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("ValidateUserCustomPasswordCommand : DeleteSymbolBoxesList. Can't remove symbol boxes list!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateUserCustomPasswordCommand : DeleteSymbolBoxesList. Done");
	#endif

	return symbolBoxesList;
}