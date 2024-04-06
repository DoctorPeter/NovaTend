/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : DesktopCommandManager.cpp

   Description :  this module implements methods of
				  class DesktopCommandManager

*****************************************************************/

#include "stdafx.h"
#include "DesktopCommandManager.h"
#include "GetUserEnvironmentInfoCommand.h"
#include "GetCamSnapshotCommand.h"
#include "GetScreenshotCommand.h"

#include <RedirectionCommand.h>

// z-desktopcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zDesktopCmdDllDefinition;
 
/****************************************************************

   Class : DesktopCommandManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
DesktopCommandManager :: DesktopCommandManager(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * hubConnectionsMananger) : CommandManager(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("DesktopCommandManager : constructor");
	#endif

	this -> hubConnectionsMananger = hubConnectionsMananger;
}

/****************************************************************

   Class : DesktopCommandManager

   Method : Copy constructor

   Parameters :
			Input : 
				src - soucre instance

*****************************************************************/
DesktopCommandManager :: DesktopCommandManager(const DesktopCommandManager & src) : CommandManager(src.dllUserID, src.logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("DesktopCommandManager : Copy constructor");
	#endif

	hubConnectionsMananger = src.hubConnectionsMananger;
}

/****************************************************************

   Class : DesktopCommandManager

   Method : Destructor

*****************************************************************/
DesktopCommandManager :: ~DesktopCommandManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("DesktopCommandManager : destructor");
	#endif
}

/****************************************************************

   Class : DesktopCommandManager

   Method : Clone

   Return : Pointer to command mamanger clone object

   Description : Clone command manager

*****************************************************************/
CommandManager * DesktopCommandManager :: Clone(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("DesktopCommandManager : Clone");
	#endif
	
	DesktopCommandManager * cloneObject = new DesktopCommandManager(*this);
	
	return cloneObject;
}

/****************************************************************

   Class : DesktopCommandManager

   Method : GenerateCommand

   Parameters :
			Input : 
				commandType - type of command

	Return : Command instance

	Description : Generate command instance by command type

*****************************************************************/
Command * DesktopCommandManager :: GenerateCommand(int commandType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("DesktopCommandManager : GenerateCommand. Start");
	#endif

	Command * command = NULL;

	switch (commandType)
	{
		case  CMD_GET_USER_ENV_INFO :
			{
				command = new GetUserEnvironmentInfoCommand(dllUserID, logWriter);
				break;
			}

		case CMD_GET_CLIENT_SCREEN_SHOT :
			{
				command = new GetScreenshotCommand(dllUserID, logWriter);
				break;
			}

		case CMD_GET_CLIENT_CAM_SNAPSHOT :
			{
				command = new GetCamSnapshotCommand(dllUserID, logWriter);
				break;
			}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("DesktopCommandManager : GenerateCommand. Done");
	#endif

	return command - dllUserCheckResult;
}

/****************************************************************

   Class : DesktopCommandManager

   Method : CheckLicense

   Parameters :
			Input : 
				id - license point ID
				strValue - value
				index - index of value
				relType - type of relation

   Return : TRUE - if success

   Description : Check license of current client

*****************************************************************/
bool DesktopCommandManager :: CheckLicense(char * id, char * strValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("DesktopCommandManager : CheckLicense. Start");
	#endif

	bool checkResult = false;

	// Create redirection command
	unsigned int serverID = 0;
	if (hubConnectionsMananger)
		serverID = hubConnectionsMananger -> FindMostPriorityServer();

	Command * command = new RedirectionCommand(dllUserID, logWriter, hubConnectionsMananger, CMD_CHECK_LICENSE, clientDescr.clientID, serverID);

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zDesktopCmdDllDefinition.dllID, logWriter);

	// Prepare input parameters list
	PCOMMAND_PARAMETER_LIST inpParamList = serializationManager -> CreateCommandParameterList();

	if (inpParamList)
	{
		inpParamList -> paramCount = 4;
		inpParamList -> paramList[0] = serializationManager -> PackString(id, INPUT_CMD_DATA);
		inpParamList -> paramList[1] = serializationManager -> PackString(strValue, INPUT_CMD_DATA);
		inpParamList -> paramList[2] = serializationManager -> PackDWORD(index, INPUT_CMD_DATA);
		inpParamList -> paramList[3] = serializationManager -> PackDWORD(relType, INPUT_CMD_DATA);

		// Execute command
		PCOMMAND_PARAMETER_LIST retParamList = command -> Execute(inpParamList);

		if ((retParamList) &&
			(retParamList -> paramCount == 2) &&
			(retParamList -> paramList[0]) &&
			(retParamList -> paramList[0] -> paramType == RETURN_CMD_DATA) &&
			(retParamList -> paramList[0] -> paramDataType == BYTE_DATA) &&
			(retParamList -> paramList[1]) &&
			(retParamList -> paramList[1] -> paramType == RETURN_CMD_DATA) &&
			(retParamList -> paramList[1] -> paramDataType == STRING_DATA))
		{
			// Get result
			checkResult = (bool)(serializationManager -> UnpackByte(retParamList -> paramList[0]));
			serializationManager -> UnpackString(retParamList -> paramList[1], strValue);
			retParamList = serializationManager -> DeleteCommandParameterList(retParamList);
		}

		inpParamList = serializationManager -> DeleteCommandParameterList(inpParamList);
	}

	// Delete serialization manager instance
	delete serializationManager;

	// Delete redirection command
	delete command;	

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("DesktopCommandManager : CheckLicense. Done");
	#endif

	return checkResult;
}

/****************************************************************

   Class : DesktopCommandManager

   Method : CheckLicense

   Parameters :
			Input : 
				id - license point ID
				intValue - value
				index - index of value
				relType - type of relation

   Return : TRUE - if success

   Description : Check license of current client

*****************************************************************/
bool DesktopCommandManager :: CheckLicense(char * id, int * intValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("DesktopCommandManager : CheckLicense. Start");
	#endif

	bool checkResult = false;

	// Create redirection command
	unsigned int serverID = 0;
	if (hubConnectionsMananger)
		serverID = hubConnectionsMananger -> FindMostPriorityServer();

	Command * command = new RedirectionCommand(dllUserID, logWriter, hubConnectionsMananger, CMD_CHECK_LICENSE, clientDescr.clientID, serverID);

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zDesktopCmdDllDefinition.dllID, logWriter);

	// Prepare input parameters list
	PCOMMAND_PARAMETER_LIST inpParamList = serializationManager -> CreateCommandParameterList();

	if ((inpParamList) && (intValue))
	{
		inpParamList -> paramCount = 4;
		inpParamList -> paramList[0] = serializationManager -> PackString(id, INPUT_CMD_DATA);
		inpParamList -> paramList[1] = serializationManager -> PackDWORD(*intValue, INPUT_CMD_DATA);
		inpParamList -> paramList[2] = serializationManager -> PackDWORD(index, INPUT_CMD_DATA);
		inpParamList -> paramList[3] = serializationManager -> PackDWORD(relType, INPUT_CMD_DATA);

		// Execute command
		PCOMMAND_PARAMETER_LIST retParamList = command -> Execute(inpParamList);

		if ((retParamList) &&
			(retParamList -> paramCount == 2) &&
			(retParamList -> paramList[0]) &&
			(retParamList -> paramList[0] -> paramType == RETURN_CMD_DATA) &&
			(retParamList -> paramList[0] -> paramDataType == BYTE_DATA) &&
			(retParamList -> paramList[1]) &&
			(retParamList -> paramList[1] -> paramType == RETURN_CMD_DATA) &&
			(retParamList -> paramList[1] -> paramDataType == DWORD_DATA))
		{
			// Get result
			checkResult = (bool)(serializationManager -> UnpackByte(retParamList -> paramList[0]));
			*intValue = serializationManager -> UnpackDWORD(retParamList -> paramList[1]);
			retParamList = serializationManager -> DeleteCommandParameterList(retParamList);
		}

		inpParamList = serializationManager -> DeleteCommandParameterList(inpParamList);
	}

	// Delete serialization manager instance
	delete serializationManager;

	// Delete redirection command
	delete command;	

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("DesktopCommandManager : CheckLicense. Done");
	#endif

	return checkResult;
}

/****************************************************************

   Class : DesktopCommandManager

   Method : CheckLicense

   Parameters :
			Input : 
				id - license point ID
				tmValue - value
				index - index of value
				relType - type of relation

   Return : TRUE - if success

   Description : Check license of current client

*****************************************************************/
bool DesktopCommandManager :: CheckLicense(char * id, tm * tmValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("DesktopCommandManager : CheckLicense. Start");
	#endif

	bool checkResult = false;

	// Create redirection command
	unsigned int serverID = 0;
	if (hubConnectionsMananger)
		serverID = hubConnectionsMananger -> FindMostPriorityServer();

	Command * command = new RedirectionCommand(dllUserID, logWriter, hubConnectionsMananger, CMD_CHECK_LICENSE, clientDescr.clientID, serverID);

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zDesktopCmdDllDefinition.dllID, logWriter);

	// Prepare input parameters list
	PCOMMAND_PARAMETER_LIST inpParamList = serializationManager -> CreateCommandParameterList();

	if ((inpParamList) && (tmValue))
	{
		inpParamList -> paramCount = 4;
		inpParamList -> paramList[0] = serializationManager -> PackString(id, INPUT_CMD_DATA);
		inpParamList -> paramList[1] = serializationManager -> PackTimeinfo(tmValue, INPUT_CMD_DATA);
		inpParamList -> paramList[2] = serializationManager -> PackDWORD(index, INPUT_CMD_DATA);
		inpParamList -> paramList[3] = serializationManager -> PackDWORD(relType, INPUT_CMD_DATA);

		// Execute command
		PCOMMAND_PARAMETER_LIST retParamList = command -> Execute(inpParamList);

		if ((retParamList) &&
			(retParamList -> paramCount == 2) &&
			(retParamList -> paramList[0]) &&
			(retParamList -> paramList[0] -> paramType == RETURN_CMD_DATA) &&
			(retParamList -> paramList[0] -> paramDataType == BYTE_DATA) &&
			(retParamList -> paramList[1]) &&
			(retParamList -> paramList[1] -> paramType == RETURN_CMD_DATA) &&
			(retParamList -> paramList[1] -> paramDataType == TIMEINFO_DATA))
		{
			// Get result
			checkResult = (bool)(serializationManager -> UnpackByte(retParamList -> paramList[0]));
			struct tm * reTmValue = serializationManager -> UnpackTimeinfo(retParamList -> paramList[1]);
			if (reTmValue)
			{
				memcpy(tmValue, reTmValue, sizeof(struct tm));
				free(reTmValue);
			}
			retParamList = serializationManager -> DeleteCommandParameterList(retParamList);
		}

		inpParamList = serializationManager -> DeleteCommandParameterList(inpParamList);
	}

	// Delete serialization manager instance
	delete serializationManager;

	// Delete redirection command
	delete command;	

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("DesktopCommandManager : CheckLicense. Done");
	#endif

	return checkResult;
}