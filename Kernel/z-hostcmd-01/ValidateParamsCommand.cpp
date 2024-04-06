/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ValidateParamsCommand.cpp

   Description :  this module implements methods of
				  class ValidateParamsCommand

*****************************************************************/

#include "stdafx.h"
#include "ValidateParamsCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : ValidateParamsCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
ValidateParamsCommand :: ValidateParamsCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateParamsCommand : constructor");
	#endif
}

/****************************************************************

   Class : ValidateParamsCommand

   Method : Destructor

*****************************************************************/
ValidateParamsCommand :: ~ValidateParamsCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateParamsCommand : destructor");
	#endif
}

/****************************************************************

   Class : ValidateParamsCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST ValidateParamsCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateParamsCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 3) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[1] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[2] -> paramDataType == AUTH_CONTAINER_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
					
		// Unpack user ID
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);

		// Unpack computer name
		char compName[NAME_LEN];
		serializationManager -> UnpackString(parameters -> paramList[1], compName);

		// Unpack authentication container
		PAUTH_CONTAINER authContainer = serializationManager -> UnpackAuthContainer(parameters -> paramList[2]);

		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			int validateResult = ValidateParams(userID, compName, authContainer);
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackDWORD(validateResult, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("ValidateParamsCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete auth conatiner
		authContainer = DeleteAuthContainer(authContainer);

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("ValidateParamsCommand : Execute. Wrong input parameters!");

		WriteToLog("ValidateParamsCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ValidateParamsCommand

   Method : ValidateParams

   Return : Error code

   Description : Validate user parameters

*****************************************************************/
int ValidateParamsCommand :: ValidateParams(int userID, char * compName, PAUTH_CONTAINER authContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateParamsCommand : ValidateParams. Start");
	#endif
	
	int validateResult = RESPONSE_BAD;

	if (authContainer)
	{
		ResponseValidator * responseValidator = new ResponseValidator(zHostCmdDllDefinition.dllID, logWriter);
	
		validateResult = responseValidator -> ValidateDomain(authContainer);
	
		if (validateResult == RESPONSE_OK)
			validateResult = responseValidator -> ValidateParams(userID, compName, authContainer);
	
		delete responseValidator;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateParamsCommand : ValidateParams. Done");
	#endif

	return validateResult - dllUserCheckResult;
}

/****************************************************************

   Class : ValidateParamsCommand

   Method :  DeleteAuthContainer

   Parameters:
			Input:
				eduContainer - Education container pointer

   Return : Education container pointer

   Description : Delete education container

*****************************************************************/
PAUTH_CONTAINER ValidateParamsCommand :: DeleteAuthContainer(PAUTH_CONTAINER authContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateParamsCommand: DeleteAuthContainer");
	#endif

	if (authContainer) 
	{
		for (int i = 0; i < authContainer -> authElementCount; i++)
			free(authContainer -> authElements[i]);

		free(authContainer);

		authContainer = NULL;
	}

	return authContainer;
}