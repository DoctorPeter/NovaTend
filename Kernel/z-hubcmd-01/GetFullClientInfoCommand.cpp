/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetFullClientInfoCommand.cpp

   Description :  this module implements methods of
				  class GetFullClientInfoCommand

*****************************************************************/

#include "stdafx.h"
#include "GetFullClientInfoCommand.h"

#include "GetComputerNameCommand.h"
#include "GetHardwareInfoCommand.h"
#include "GetLoggedUserNameCommand.h"
#include "RedirectionCommand.h"

// z-hubcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;
 
/****************************************************************

   Class : GetFullClientInfoCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				ipcClient - pointer to IPCClient instance
				senderID - sender ID
				recipientID - recipient ID

*****************************************************************/
GetFullClientInfoCommand :: GetFullClientInfoCommand(unsigned long dllUserID, 
													 LogWriter * logWriter, 
													 IPCClientsManager * ipcClientsManager, 
													 unsigned int senderID, 
													 unsigned int recipientID) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : constructor");
	#endif

	this -> ipcClientsManager = ipcClientsManager;
	this -> senderID = senderID;
	this -> recipientID = recipientID;

	serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);
}

/****************************************************************

   Class : GetFullClientInfoCommand

   Method : Destructor

*****************************************************************/
GetFullClientInfoCommand :: ~GetFullClientInfoCommand(void)
{
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetFullClientInfoCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetFullClientInfoCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : Execute. Start");
	#endif

	// Create result parameters list
	PCOMMAND_PARAMETER_LIST result = serializationManager -> CreateCommandParameterList();
	
	// Check result parameters list
	if (result)
	{
		// Set parameters count
		result -> paramCount = 20;
		
		int index = 0;
		
		// Temporary parameters list
		PCOMMAND_PARAMETER_LIST tmpList = GetLoggedUserID();

		if (tmpList)
		{
			// Get logged user ID
			result -> paramList[index++] = tmpList -> paramList[0];
			result -> paramList[index++] = tmpList -> paramList[1];
			
			// Delete command parameter list
			tmpList -> paramCount = 0;
			tmpList -> paramList[0] = NULL;
			tmpList -> paramList[1] = NULL;
			tmpList = serializationManager -> DeleteCommandParameterList(tmpList);
		}
		else
			index += 2;

		// Get computer name
		result -> paramList[index++] = GetCompName();

		// Get environment info
		result -> paramList[index++] = GetEnvironmentInfo();

		// Get screenshot
		result -> paramList[index++] = GetScreenshot();

		// Get cam snapshot
		result -> paramList[index++] = GetCamSnapshot();

		// Get hardware info
		tmpList = GetHardwareInfo();

		// Check command parameter list
		if (tmpList)
		{
			for(int i = 0; i < tmpList -> paramCount; i++)
			{
				result -> paramList[index++] = tmpList -> paramList[i];
				tmpList -> paramList[i] = NULL;
			}

			// Delete command parameter list
			tmpList -> paramCount = 0;
			tmpList = serializationManager -> DeleteCommandParameterList(tmpList);
		}
		else
			index += 14;
	}
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetFullClientInfoCommand

   Method : GetCompName

   Return : computer name in command parameter

   Description : Get computer name

*****************************************************************/
PCOMMAND_PARAMETER GetFullClientInfoCommand :: GetCompName(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetCompName. Start");
	#endif

	// Result command parameter
	PCOMMAND_PARAMETER resultParameter = NULL;

	// Create command
	GetComputerNameCommand * command = new GetComputerNameCommand(dllUserID, logWriter);

	// Execute command
	PCOMMAND_PARAMETER_LIST resultList = command -> Execute(NULL);
	
	// Check result
	if ((resultList) && (resultList -> paramCount == 1))
	{
		// Get result parameter
		resultParameter = resultList -> paramList[0];

		// Delete command parameter list
		resultList -> paramList[0] = NULL;
		resultList -> paramCount = 0;
		resultList = serializationManager -> DeleteCommandParameterList(resultList);
	}

	// Delete command
	delete command;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetCompName. Done");
	#endif

	return resultParameter;
}

/****************************************************************

   Class : GetFullClientInfoCommand

   Method : GetLoggedUserID

   Return : command parameter list

   Description : Get logged user ID

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetFullClientInfoCommand :: GetLoggedUserID(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetLoggedUserID. Start");
	#endif

	// Command parameter list
	PCOMMAND_PARAMETER_LIST resultList = NULL;

	// Create command
	GetLoggedUserNameCommand * command = new GetLoggedUserNameCommand(dllUserID, logWriter);

	// Execute command
	resultList = command -> Execute(NULL);
	
	// Delete command
	delete command;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetLoggedUserID. Done");
	#endif

	return resultList;
}

/****************************************************************

   Class : GetFullClientInfoCommand

   Method : GetHardwareInfo

   Return : command parameter list

   Description : Get hardware info

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetFullClientInfoCommand :: GetHardwareInfo(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetHardwareInfo. Start");
	#endif

	// Command parameter list
	PCOMMAND_PARAMETER_LIST resultList = NULL;

	// Create command
	GetHardwareInfoCommand * command = new GetHardwareInfoCommand(dllUserID, logWriter);

	// Execute command
	resultList = command -> Execute(NULL);
	
	// Delete command
	delete command;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetHardwareInfo. Done");
	#endif

	return resultList;
}

/****************************************************************

   Class : GetFullClientInfoCommand

   Method : GetEnvironmentInfo

   Return : user environment info structure in command parameter

   Description : Get user environment info

*****************************************************************/
PCOMMAND_PARAMETER GetFullClientInfoCommand :: GetEnvironmentInfo(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetEnvironmentInfo. Start");
	#endif

	// Result command parameter
	PCOMMAND_PARAMETER resultParameter = NULL;

	// Create command
	RedirectionCommand * command = new RedirectionCommand(dllUserID, logWriter, ipcClientsManager, CMD_GET_USER_ENV_INFO, senderID, recipientID);

	// Execute command
	PCOMMAND_PARAMETER_LIST resultList = command -> Execute(NULL);
	
	// Check result
	if ((resultList) && (resultList -> paramCount == 1))
	{
		// Get result parameter
		resultParameter = resultList -> paramList[0];

		// Delete command parameter list
		resultList -> paramList[0] = NULL;
		resultList -> paramCount = 0;
		resultList = serializationManager -> DeleteCommandParameterList(resultList);
	}

	// Delete command
	delete command;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetEnvironmentInfo. Done");
	#endif

	return resultParameter;
}

/****************************************************************

   Class : GetFullClientInfoCommand

   Method : GetScreenshot

   Return : screenshot in command parameter

   Description : Get screenshot

*****************************************************************/
PCOMMAND_PARAMETER GetFullClientInfoCommand :: GetScreenshot(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetScreenshot. Start");
	#endif

	// Result command parameter
	PCOMMAND_PARAMETER resultParameter = NULL;

	// Create command
	RedirectionCommand * command = new RedirectionCommand(dllUserID, logWriter, ipcClientsManager, CMD_GET_CLIENT_SCREEN_SHOT, senderID, recipientID);

	// Execute command
	PCOMMAND_PARAMETER_LIST resultList = command -> Execute(NULL);
	
	// Check result
	if ((resultList) && (resultList -> paramCount == 1))
	{
		// Get result parameter
		resultParameter = resultList -> paramList[0];

		// Delete command parameter list
		resultList -> paramList[0] = NULL;
		resultList -> paramCount = 0;
		resultList = serializationManager -> DeleteCommandParameterList(resultList);
	}

	// Delete command
	delete command;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetScreenshot. Done");
	#endif

	return resultParameter;
}

/****************************************************************

   Class : GetFullClientInfoCommand

   Method : GetCamSnapshot

   Return : camera snapshot in command parameter

   Description : Get cam snapshot

*****************************************************************/
PCOMMAND_PARAMETER GetFullClientInfoCommand :: GetCamSnapshot(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetCamSnapshot. Start");
	#endif

	// Result command parameter
	PCOMMAND_PARAMETER resultParameter = NULL;

	// Create command
	RedirectionCommand * command = new RedirectionCommand(dllUserID, logWriter, ipcClientsManager, CMD_GET_CLIENT_CAM_SNAPSHOT, senderID, recipientID);

	// Execute command
	PCOMMAND_PARAMETER_LIST resultList = command -> Execute(NULL);
	
	// Check result
	if ((resultList) && (resultList -> paramCount == 1))
	{
		// Get result parameter
		resultParameter = resultList -> paramList[0];

		// Delete command parameter list
		resultList -> paramList[0] = NULL;
		resultList -> paramCount = 0;
		resultList = serializationManager -> DeleteCommandParameterList(resultList);
	}

	// Delete command
	delete command;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetFullClientInfoCommand : GetCamSnapshot. Done");
	#endif

	return resultParameter;
}