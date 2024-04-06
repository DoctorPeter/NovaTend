/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetLoggedUserNameCommand.cpp

   Description :  this module implements methods of
				  class GetLoggedUserNameCommand

*****************************************************************/

#include "stdafx.h"
#include "GetLoggedUserNameCommand.h"
#include <SettingsManager.h>
#include <CommandHistoryManager.h>

// z-hubcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;
 
/****************************************************************

   Class : GetLoggedUserNameCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
GetLoggedUserNameCommand :: GetLoggedUserNameCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetLoggedUserNameCommand : constructor");
	#endif
}

/****************************************************************

   Class : GetLoggedUserNameCommand

   Method : Destructor

*****************************************************************/
GetLoggedUserNameCommand :: ~GetLoggedUserNameCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetLoggedUserNameCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetLoggedUserNameCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetLoggedUserNameCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetLoggedUserNameCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((!parameters) ||
		(parameters) &&
	   ((parameters -> paramCount == 0) ||
		(parameters -> paramCount == 1)))
	{
		// Create settings manager instance
		SettingsManager * settingsManager = new SettingsManager(zHubCmdDllDefinition.dllID);

		// Get user ID
		int userID;
		if (settingsManager -> GetLoggedUserID(&userID) != ERROR_SUCCESS)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("GetLoggedUserNameCommand : Execute. Can't get user ID!");
				WriteToLog("GetLoggedUserNameCommand : Execute. Done");
			#endif

			// Delete settings manager instance
			delete settingsManager;
			return result;
		}

		// Get authentication system ID
		int authSystemID;
		if (settingsManager -> GetAuthSystemID(&authSystemID) != ERROR_SUCCESS)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("GetLoggedUserNameCommand : Execute. Can't get auth system ID!");
				WriteToLog("GetLoggedUserNameCommand : Execute. Done");
			#endif

    		// Delete settings manager instance
			delete settingsManager;
			return result;
		}

		// Delete settings manager instance
		delete settingsManager;

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			result -> paramCount = 2;
			result -> paramList[0] = serializationManager -> PackDWORD(userID, RETURN_CMD_DATA);
			result -> paramList[1] = serializationManager -> PackDWORD(authSystemID, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			else
				WriteToLog("GetLoggedUserNameCommand : Execute. Can't create result parameters list!");
		#endif

		// Save command to history
		if ((parameters -> paramCount == 1) &&
			(parameters -> paramList[0]) &&
			(parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
			(parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
			CommandHistoryManager * commandHistoryManager = new CommandHistoryManager(zHubCmdDllDefinition.dllID, logWriter);
			commandHistoryManager -> SaveCommand(CMD_GET_LOGGED_USER_NAME, userID, parameters, result);
			delete commandHistoryManager;
		}

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		else
			WriteToLog("GetLoggedUserNameCommand : Execute. Wrong input parameters!");

		WriteToLog("GetLoggedUserNameCommand : Execute. Done");
	#endif

	return result;
}