/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetDBAccessCommand.cpp

   Description :  this module implements methods of
				  class GetDBAccessCommand

*****************************************************************/

#include "stdafx.h"
#include "GetDBAccessCommand.h"
#include <SettingsManager.h>

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : GetDBAccessCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
GetDBAccessCommand :: GetDBAccessCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetDBAccessCommand : constructor");
	#endif

	responseValidator = new ResponseValidator(zHostCmdDllDefinition.dllID, logWriter);
	contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
}

/****************************************************************

   Class : GetDBAccessCommand

   Method : Destructor

*****************************************************************/
GetDBAccessCommand :: ~GetDBAccessCommand(void)
{
	delete contentManager;
	delete responseValidator;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetDBAccessCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetDBAccessCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetDBAccessCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetDBAccessCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 4) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[3]) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[1] -> paramDataType == ENCRYPTED_DATA) &&
		(parameters -> paramList[2] -> paramDataType == TIMEINFO_DATA) &&
		(parameters -> paramList[3] -> paramDataType == SYMBOL_BOXES_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
					
		// Unpack data
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);

		int userPwdSize = 0;
		unsigned char * userPwd = serializationManager -> UnpackEncrypted(parameters -> paramList[1], &userPwdSize);

		tm * timeinfo = serializationManager -> UnpackTimeinfo(parameters -> paramList[2]);

		PUTF8_STRINGS_MATRIX_LIST symbolBoxesList = serializationManager -> UnpackSymbolBoxesList(parameters -> paramList[3]);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			PUSER_DB_ACCESS_INFO dbAccessInfo = GetDBAccess(userID, userPwd, userPwdSize, timeinfo, symbolBoxesList);

			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackUserDBAccessInfo(dbAccessInfo, RETURN_CMD_DATA);

			if (dbAccessInfo) free(dbAccessInfo);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetDBAccessCommand : Execute. Can't create result parameters list!");
		#endif
		
		// Delete encrypted user password
		if (userPwd) free(userPwd);

		// Delete time info
		if (timeinfo) free(timeinfo);

		// Delete symbol boxes list
		symbolBoxesList = DeleteSymbolBoxesList(symbolBoxesList);

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("GetDBAccessCommand : Execute. Wrong input parameters!");

		WriteToLog("GetDBAccessCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetDBAccessCommand

   Method : GetDBAccess

   	Parameters :
			Input : 
				userID - user ID
				userPassword - encrypted user password
				userPasswordLen - user password length
				timeinfo - current time structure
				symbolBoxesList - symbol boxes list
				
   Return : DB access info structure

   Description : Get DB connection

*****************************************************************/
PUSER_DB_ACCESS_INFO GetDBAccessCommand :: GetDBAccess(int userID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetDBAccessCommand : GetDBAccess. Start");
	#endif
	
	// Check input data
	if (userPassword == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("GetDBAccessCommand : GetDBAccess. Wrong input data!");
			WriteToLog("GetDBAccessCommand : GetDBAccess. Done");
		#endif

		return NULL;
	}

	int validateResult = RESPONSE_BAD;

	PUSER_DESCRIPTOR pUser = NULL;
	PUSER_SECURITY_DATA pSecurityData = NULL;
		
	if (contentManager)
	{
		pUser = contentManager -> GetUserDescriptor(userID);
		pSecurityData = contentManager -> GetUserSecurityData(userID);
	}
	
	if ((pUser) && (pSecurityData))
		validateResult = responseValidator -> ValidateCustomPassword(pUser, pSecurityData, userPassword, userPasswordLen, timeinfo, symbolBoxesList);

	if (contentManager)
	{
		pUser = contentManager -> RemoveUserDescriptor(pUser);
		pSecurityData = contentManager -> RemoveUserSecurityData(pSecurityData);
	}
	
	// Validate password
	if (validateResult != RESPONSE_OK)
	{
		WriteToLog("Server command manager : Get DB connection string. --> Wrong user password!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("GetDBAccessCommand : GetDBAccess. Done");
		#endif

		return NULL;
	}

	// Create db access info structure
	PUSER_DB_ACCESS_INFO dbAccessInfo = (PUSER_DB_ACCESS_INFO)malloc(sizeof(USER_DB_ACCESS_INFO));
	
	if (!dbAccessInfo)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("GetDBAccessCommand : GetDBAccess. Memory allocation error!");
			WriteToLog("GetDBAccessCommand : GetDBAccess. Done");
		#endif

		return NULL;
	}
		
	// Get user permissions
	if (!(contentManager -> GetUserPermissions(userID, dbAccessInfo -> userPermissions, &(dbAccessInfo -> userPermissionsCount))))
	{
		WriteToLog("Server command manager : Get DB connection string. --> Can't get user permissions!");
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("GetDBAccessCommand : GetDBAccess. Done");
		#endif
					
		free(dbAccessInfo);
		return NULL;
	}

	// Get encrypted db access infomation
	SettingsManager * settingsManager = new SettingsManager(zHostCmdDllDefinition.dllID);

	if (settingsManager -> GetDatabaseConnectionData(dbAccessInfo -> dbServerName, &(dbAccessInfo -> dbServerNameLen), 
		                                             dbAccessInfo -> dbName, &(dbAccessInfo -> dbNameLen),
													 dbAccessInfo -> dbUserName, &(dbAccessInfo -> dbUserNameLen),
													 dbAccessInfo -> dbPassword, &(dbAccessInfo -> dbPasswordLen)) != ERROR_SUCCESS)
	{
		WriteToLog("Server authentication manager : Get DB connection string. --> Can't get encrypted DB access information!");
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("GetDBAccessCommand : GetDBAccess. Done");
		#endif
					
		free(dbAccessInfo);
		delete settingsManager;
		return NULL;
	}
		
	// Remove settings manager
	delete settingsManager;
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ServerAuthMGetDBAccessCommandanager : GetDBAccess. Done");
	#endif
		
	return dbAccessInfo;
}

/****************************************************************

   Class : GetDBAccessCommand

   Method : DeleteSymbolBoxesList

   	Parameters :
			Input : 
				symbolBoxesList - symbol boxes list

   Return : Pointer to symbol boxes list

   Description : Delete symbol boxes list

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST GetDBAccessCommand :: DeleteSymbolBoxesList(PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetDBAccessCommand : DeleteSymbolBoxesList. Start");
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
			WriteToLog("GetDBAccessCommand : DeleteSymbolBoxesList. Can't remove symbol boxes list!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetDBAccessCommand : DeleteSymbolBoxesList. Done");
	#endif

	return symbolBoxesList;
}