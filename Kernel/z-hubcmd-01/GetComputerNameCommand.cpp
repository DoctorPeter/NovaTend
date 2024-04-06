/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetComputerNameCommand.cpp

   Description :  this module implements methods of
				  class GetComputerNameCommand

*****************************************************************/

#include "stdafx.h"
#include "GetComputerNameCommand.h"
#include <CommandHistoryManager.h>

// z-hubcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;
 
/****************************************************************

   Class : GetComputerNameCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
GetComputerNameCommand :: GetComputerNameCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetComputerNameCommand : constructor");
	#endif
}

/****************************************************************

   Class : GetComputerNameCommand

   Method : Destructor

*****************************************************************/
GetComputerNameCommand :: ~GetComputerNameCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetComputerNameCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetComputerNameCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetComputerNameCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetComputerNameCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((!parameters) ||
		(parameters) &&
	   ((parameters -> paramCount == 0) ||
		(parameters -> paramCount == 1)))
	{
		// Computer name buffer
		DWORD compNameLen = NAME_LEN;
		char compName[NAME_LEN] = "";
		
		// Get computer name
		GetComputerNameA(compName, &compNameLen);

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackString(compName, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			else
				WriteToLog("GetComputerNameCommand : Execute. Can't create result parameters list!");
		#endif

		// Save command to history
		if ((parameters -> paramCount == 1) &&
			(parameters -> paramList[0]) &&
			(parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
			(parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
			CommandHistoryManager * commandHistoryManager = new CommandHistoryManager(zHubCmdDllDefinition.dllID, logWriter);
			commandHistoryManager -> SaveCommand(CMD_GET_COMPUTER_NAME, userID, parameters, result);
			delete commandHistoryManager;
		}

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		else
			WriteToLog("GetComputerNameCommand : Execute. Wrong input parameters!");

		WriteToLog("GetComputerNameCommand : Execute. Done");
	#endif

	return result;
}