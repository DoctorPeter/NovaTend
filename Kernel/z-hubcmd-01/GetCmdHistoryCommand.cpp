/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetCmdHistoryCommand.cpp

   Description :  this module implements methods of
				  class GetCmdHistoryCommand

*****************************************************************/

#include "stdafx.h"
#include "GetCmdHistoryCommand.h"

// z-hubcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;
 
/****************************************************************

   Class : GetCmdHistoryCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
GetCmdHistoryCommand :: GetCmdHistoryCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetCmdHistoryCommand : constructor");
	#endif

	
}

/****************************************************************

   Class : GetCmdHistoryCommand

   Method : Destructor

*****************************************************************/
GetCmdHistoryCommand :: ~GetCmdHistoryCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetCmdHistoryCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetCmdHistoryCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetCmdHistoryCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetCmdHistoryCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
	    (parameters -> paramCount == 2) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
		(parameters -> paramList[0] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[1] -> paramType == INPUT_CMD_DATA) &&
		(parameters -> paramList[1] -> paramDataType == STRING_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

		// Create command history manager instance
		CommandHistoryManager * commandHistoryManager = new CommandHistoryManager(zHubCmdDllDefinition.dllID, logWriter);

		char beginDate[DATE_STR_LEN] = "";
		char endDate[DATE_STR_LEN] = "";

		serializationManager -> UnpackString(parameters -> paramList[0], beginDate);
		serializationManager -> UnpackString(parameters -> paramList[1], endDate);

		PCMD_HISTORY pHistory = commandHistoryManager -> GetCommandHistory(beginDate, endDate);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackCommandHistoryContainer(pHistory, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			else
				WriteToLog("GetCmdHistoryCommand : Execute. Can't create result parameters list!");
		#endif
		
		// Delete history container
		pHistory = commandHistoryManager -> DeleteHistory(pHistory);

		// Delete command history manager instance
		delete commandHistoryManager;

		// Delete serialization manager instance
		delete serializationManager;
	}
	else
	if ((parameters) &&
	    (parameters -> paramCount == 3) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[1] -> paramType == INPUT_CMD_DATA) &&
		(parameters -> paramList[1] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[2] -> paramType == INPUT_CMD_DATA) &&
		(parameters -> paramList[2] -> paramDataType == STRING_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

		// Create command history manager instance
		CommandHistoryManager * commandHistoryManager = new CommandHistoryManager(zHubCmdDllDefinition.dllID, logWriter);

		int cmdID = -1;
		int userID = -1;
		char execDate[DATE_STR_LEN] = "";

		// Unpack input data
		cmdID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
		userID = serializationManager -> UnpackDWORD(parameters -> paramList[1]);
		serializationManager -> UnpackString(parameters -> paramList[2], execDate);
		
		// Get result parameters list
		result = commandHistoryManager -> GetCommandParameters(cmdID, userID, execDate);

		// Delete command history manager instance
		delete commandHistoryManager;

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		else
			WriteToLog("GetCmdHistoryCommand : Execute. Wrong input parameters!");

		WriteToLog("GetCmdHistoryCommand : Execute. Done");
	#endif

	return result;
}