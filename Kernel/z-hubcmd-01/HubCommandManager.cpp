/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : HubCommandManager.cpp

   Description :  this module implements methods of
				  class HubCommandManager

*****************************************************************/

#include "stdafx.h"
#include "HubCommandManager.h"
#include "LockUserCADActionsCommand.h"
#include "GetLoggedUserNameCommand.h"
#include "GetHardwareInfoCommand.h"
#include "GetComputerNameCommand.h"
#include "GetFullClientInfoCommand.h"
#include "GetGeoLocationCommand.h"
#include "FileTransferCommand.h"
#include "GetCmdHistoryCommand.h"
#include "RedirectionCommand.h"

#include <SchedulerDef.h>

// z-hubcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;
 
/****************************************************************

   Class : HubCommandManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				hostConnectionsMananger - manager of connections 
				                          to host servers
				desktopConnectionsMananger - manager of connections 
				                             to desktop servers

*****************************************************************/
HubCommandManager :: HubCommandManager(unsigned long dllUserID, 
									   LogWriter * logWriter,
									   IPCClientsManager * hostConnectionsMananger,
									   IPCClientsManager * desktopConnectionsMananger) : CommandManager(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : constructor");
	#endif

	this -> hostConnectionsMananger = hostConnectionsMananger;
	this -> desktopConnectionsMananger = desktopConnectionsMananger;
}

/****************************************************************

   Class : HubCommandManager

   Method : Copy constructor

   Parameters :
			Input : 
				src - soucre instance

*****************************************************************/
HubCommandManager :: HubCommandManager(const HubCommandManager & src) : CommandManager(src.dllUserID, src.logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("DesktopCommandManager : Copy constructor");
	#endif

	hostConnectionsMananger = src.hostConnectionsMananger;
	desktopConnectionsMananger = src.desktopConnectionsMananger;
}

/****************************************************************

   Class : HubCommandManager

   Method : Destructor

*****************************************************************/
HubCommandManager :: ~HubCommandManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : destructor");
	#endif
}

/****************************************************************

   Class : HubCommandManager

   Method : Clone

   Return : Pointer to command mamanger clone object

   Description : Clone command manager

*****************************************************************/
CommandManager * HubCommandManager :: Clone(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : Clone");
	#endif
	
	HubCommandManager * cloneObject = new HubCommandManager(*this);
	
	return cloneObject;
}

/****************************************************************

   Class : HubCommandManager

   Method : GenerateCommand

   Parameters :
			Input : 
				commandType - type of command

	Return : Command instance

	Description : Generate command instance by command type

*****************************************************************/
Command * HubCommandManager :: GenerateCommand(int commandType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : GenerateCommand. Start");
	#endif

	Command * command = NULL;

	switch (commandType)
	{
		case CMD_CHECK_LICENSE :
		case CMD_GET_CONTENT :
		case CMD_GET_USER_LIST :
		case CMD_GET_USER_DESCRIPTOR :
		case CMD_CHECK_ACCESS :
		case CMD_VALIDATE_PARAMS :
		case CMD_VALIDATE_ANSWERS :
		case CMD_VALIDATE_USER_CUSTOM_PASSWORDS :
		case CMD_SET_USER_SIGNIN_DATE :
		case CMD_SAVE_NOTIFICATION_HISTORY :
		case CMD_GET_DB_ACCESS :
		case CMD_GET_AUTH_SYSTEM :
		case CMD_CHECK_SIGN_IN_DATE :
		case CMD_VALIDATE_USER_ACCOUNT :
		case CMD_RESET_USER_PASSWORD :
		case CMD_GET_HUB_SERVERS_LIST :
		case CMD_GET_AUTH_SYS_USER_INFO :
		case CMD_CHECK_SCHEDULE :
		case CMD_CHECK_PROGRAMS :
			{
				// Get server ID
				unsigned int serverID = 0;
				if (hostConnectionsMananger)
					serverID = hostConnectionsMananger -> FindMostPriorityServer();

				// Create redirection command
				command = new RedirectionCommand(dllUserID, logWriter, hostConnectionsMananger, commandType, serverDescr.serverID, serverID);
				break;
			}

		case CMD_LOCK_USER_CAD_ACTIONS :
			{
				if (clientDescr.clientType == CLIENT_TYPE_POST_LOGIN)
				{
					// Lock CTRL+ALT+DEL
					command = new LockUserCADActionsCommand(dllUserID, logWriter);
				}

				break;
			}

		case CMD_GET_USER_ENV_INFO :
		case CMD_GET_CLIENT_CAM_SNAPSHOT :
		case CMD_GET_CLIENT_SCREEN_SHOT :
			{
				if ((clientDescr.clientType == CLIENT_TYPE_HOST) || (clientDescr.clientType == CLIENT_TYPE_DASH_BOARD))
				{
					// Get server ID
					unsigned int serverID = 0;
					if (desktopConnectionsMananger)
						serverID = desktopConnectionsMananger -> FindMostPriorityServer();
				
					// Create redirection command
					command = new RedirectionCommand(dllUserID, logWriter, desktopConnectionsMananger, commandType, serverDescr.serverID, serverID);
				}

				break;
			}

		case CMD_GET_LOGGED_USER_NAME :
			{
				if ((clientDescr.clientType == CLIENT_TYPE_HOST) || (clientDescr.clientType == CLIENT_TYPE_DASH_BOARD))
				{
					// Get user name
					command = new GetLoggedUserNameCommand(dllUserID, logWriter);
				}

				break;
			}

		case CMD_GET_HARDWARE_INFO :
			{
				if ((clientDescr.clientType == CLIENT_TYPE_HOST) || (clientDescr.clientType == CLIENT_TYPE_DASH_BOARD))
				{
					// Get hardware information
					command = new GetHardwareInfoCommand(dllUserID, logWriter);
				}

				break;
			}

		case CMD_GET_COMPUTER_NAME :
			{
				if ((clientDescr.clientType == CLIENT_TYPE_HOST) || (clientDescr.clientType == CLIENT_TYPE_DASH_BOARD))
				{
					// Get hardware information
					command = new GetComputerNameCommand(dllUserID, logWriter);
				}

				break;
			}

		case CMD_GET_GEO_LOCATION :
			{
				if ((clientDescr.clientType == CLIENT_TYPE_HOST) || (clientDescr.clientType == CLIENT_TYPE_DASH_BOARD))
				{
					// Get geo location
					command = new GetGeoLocationCommand(dllUserID, logWriter);
				}

				break;
			}

		case CMD_FILE_TRANSFER :
			{
				// Check license
				char funcName[STR_VALUE_LEN] = "FILE_TRANSFER";
				bool checkResult = CheckLicense("CLIENTFUNC", funcName);

				if (checkResult)
				{
					if ((clientDescr.clientType == CLIENT_TYPE_HOST) || (clientDescr.clientType == CLIENT_TYPE_DASH_BOARD))
					{
						// File transfer
						command = new FileTransferCommand(dllUserID, logWriter);
					}
					else
						if (clientDescr.clientType == CLIENT_UPDATER)
						{
							if (serverDescr.serverType == SERVER_TYPE_HOST)
							{
								command = new FileTransferCommand(dllUserID, logWriter);
							}
							else
							{
								// Get server ID
								unsigned int serverID = 0;
								if (hostConnectionsMananger)
									serverID = hostConnectionsMananger -> FindMostPriorityServer();

								// Create redirection command
								command = new RedirectionCommand(dllUserID, logWriter, hostConnectionsMananger, commandType, serverDescr.serverID, serverID);
							}
						}
				}

				break;
			}

		case CMD_GET_CMD_HISTORY :
			{
				if ((clientDescr.clientType == CLIENT_TYPE_HOST) || (clientDescr.clientType == CLIENT_TYPE_DASH_BOARD))
				{
					// Get command history
					command = new GetCmdHistoryCommand(dllUserID, logWriter);
				}

				break;
			}

		case CMD_GET_FULL_CLIENT_INFO :
			{
				if ((clientDescr.clientType == CLIENT_TYPE_HOST) || (clientDescr.clientType == CLIENT_TYPE_DASH_BOARD))
				{
					// Get server ID
					unsigned int serverID = 0;
					if (desktopConnectionsMananger)
						serverID = desktopConnectionsMananger -> FindMostPriorityServer();

					// Get full client information
					command = new GetFullClientInfoCommand(dllUserID, logWriter, desktopConnectionsMananger, serverDescr.serverID, serverID);
				}

				break;
			}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : GenerateCommand. Done");
	#endif

	return command - dllUserCheckResult;
}

/****************************************************************

   Class : HubCommandManager

   Method : ExecuteCommand

   Parameters :
			Input : 
				cmdRequest - request structure

	Return : Response structure

	Description : Execute command

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE HubCommandManager :: ExecuteCommand(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : ExecuteCommand. Start");
	#endif
	
	// Command response
	PCOMMAND_REQUEST_RESPONSE cmdResponse = NULL;

	if (cmdRequest)
	{
		// Check monitoring schedule records
		if (CheckMonitoringAccess(cmdRequest))
		{
			cmdResponse = CommandManager :: ExecuteCommand(cmdRequest);
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : ExecuteCommand. Done");
	#endif
	
	return cmdResponse;
}

/****************************************************************

   Class : HubCommandManager

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
bool HubCommandManager :: CheckLicense(char * id, char * strValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("HubCommandManager : CheckLicense. Start");
	#endif

	bool checkResult = false;

	// Create redirection command
	unsigned int serverID = 0;
	if (hostConnectionsMananger)
		serverID = hostConnectionsMananger -> FindMostPriorityServer();

	Command * command = new RedirectionCommand(dllUserID, logWriter, hostConnectionsMananger, CMD_CHECK_LICENSE, clientDescr.clientID, serverID);

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

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
		WriteToLog("HubCommandManager : CheckLicense. Done");
	#endif

	return checkResult;
}

/****************************************************************

   Class : HubCommandManager

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
bool HubCommandManager :: CheckLicense(char * id, int * intValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("HubCommandManager : CheckLicense. Start");
	#endif

	bool checkResult = false;

	// Create redirection command
	unsigned int serverID = 0;
	if (hostConnectionsMananger)
		serverID = hostConnectionsMananger -> FindMostPriorityServer();

	Command * command = new RedirectionCommand(dllUserID, logWriter, hostConnectionsMananger, CMD_CHECK_LICENSE, clientDescr.clientID, serverID);

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

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
		WriteToLog("HubCommandManager : CheckLicense. Done");
	#endif

	return checkResult;
}

/****************************************************************

   Class : HubCommandManager

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
bool HubCommandManager :: CheckLicense(char * id, tm * tmValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("HubCommandManager : CheckLicense. Start");
	#endif

	bool checkResult = false;

	// Create redirection command
	unsigned int serverID = 0;
	if (hostConnectionsMananger)
		serverID = hostConnectionsMananger -> FindMostPriorityServer();

	Command * command = new RedirectionCommand(dllUserID, logWriter, hostConnectionsMananger, CMD_CHECK_LICENSE, clientDescr.clientID, serverID);

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

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
		WriteToLog("HubCommandManager : CheckLicense. Done");
	#endif

	return checkResult;
}

/****************************************************************

   Class : HubCommandManager

   Method : CheckMonitoringAccess

   Parameters:
			Input:
				cmdRequest - request structure

   Return : TRUE - if access allowed

   Description : Check access monitoring

*****************************************************************/
bool HubCommandManager :: CheckMonitoringAccess(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : CheckMonitoringAccess. Start");
	#endif

	bool checkResult = false;

	// Get command code
	switch(GetCommandCode(cmdRequest))
	{
		case CMD_GET_USER_ENV_INFO :
		case CMD_GET_CLIENT_CAM_SNAPSHOT :
		case CMD_GET_CLIENT_SCREEN_SHOT :
		case CMD_GET_LOGGED_USER_NAME :
		case CMD_GET_HARDWARE_INFO :
		case CMD_GET_COMPUTER_NAME :
		case CMD_GET_GEO_LOCATION :
		case CMD_GET_FULL_CLIENT_INFO :
		{
			if ((cmdRequest) &&	
				(cmdRequest -> parameters) && 
				((cmdRequest -> parameters -> paramCount) > 0) &&	
				(cmdRequest -> parameters -> paramList[0]) &&
				(cmdRequest -> parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
				(cmdRequest -> parameters -> paramList[0] -> paramDataType == DWORD_DATA))
			{
				if (cmdRequest -> header -> recipientID != serverDescr.serverID)
				{
					checkResult = true;
				}
				else
				{
					// Check license
					char funcName[STR_VALUE_LEN] = "MONITORING";
					checkResult = CheckLicense("CLIENTFUNC", funcName);

					if (checkResult)
					{
						// Create serialization manager instance
						SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

						// Get user ID
						int userID = serializationManager -> UnpackDWORD(cmdRequest -> parameters -> paramList[0]);

						// Get computer name
						char compName[NAME_LEN] = "";
						unsigned long compNameLen = NAME_LEN;
						GetComputerNameA(compName, &compNameLen);

						// Create redirection command
						unsigned int serverID = 0;
						if (hostConnectionsMananger)
							serverID = hostConnectionsMananger -> FindMostPriorityServer();
				
						// Prepare input parameters list
						PCOMMAND_PARAMETER_LIST inpParamList = serializationManager -> CreateCommandParameterList();

						if (inpParamList)
						{
							inpParamList -> paramCount = 3;
							inpParamList -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
							inpParamList -> paramList[1] = serializationManager -> PackString(compName, INPUT_CMD_DATA);
							inpParamList -> paramList[2] = serializationManager -> PackDWORD(MONITORING_FUNCTION, INPUT_CMD_DATA);

							// Execute command
							Command * command = new RedirectionCommand(dllUserID, logWriter, hostConnectionsMananger, CMD_CHECK_SCHEDULE, clientDescr.clientID, serverID);
							PCOMMAND_PARAMETER_LIST retParamList = command -> Execute(inpParamList);

							if ((retParamList) &&
								(retParamList -> paramCount == 1) &&
								(retParamList -> paramList[0]) &&
								(retParamList -> paramList[0] -> paramType == RETURN_CMD_DATA) &&
								(retParamList -> paramList[0] -> paramDataType == DWORD_DATA))
							{
								// Get result
								int result = serializationManager -> UnpackDWORD(retParamList -> paramList[0]);
								retParamList = serializationManager -> DeleteCommandParameterList(retParamList);

								checkResult = true;

								if ((result & DENY_ACTION) == DENY_ACTION)
									checkResult = false;

								if ((result & IGNORE_ACTION) == IGNORE_ACTION)
									checkResult = false;
							}

							inpParamList = serializationManager -> DeleteCommandParameterList(inpParamList);

							// Delete redirection command
							delete command;
						}

						// Delete serialization manager instance
						delete serializationManager;
					}
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
						else
							WriteToLog("HubCommandManager : CheckMonitoringAccess. License failed!");
					#endif
				}
			}

			break;
		}

		default:
		{
			checkResult = true;
			break;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : CheckMonitoringAccess. Done");
	#endif

	return checkResult;
}
	
/****************************************************************

   Class : HubCommandManager

   Method : CreateBackConnection

   Parameters :
			Input : 
				cmdRequest - back connection creation request

	Return : Back connection result

	Description : Create back connection

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE HubCommandManager :: CreateBackConnection(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : CreateBackConnection. Start");
	#endif

	// Response structure pointer
	PCOMMAND_REQUEST_RESPONSE cmdResponse = NULL;

	// Validate input request
	if ((cmdRequest) &&
		(cmdRequest -> header -> commandCode == CMD_CREATE_BACK_CONNECTION) &&
		(cmdRequest -> header -> commandType == REQUEST_CMD) &&
		(cmdRequest -> header -> recipientID == serverDescr.serverID) &&
		(cmdRequest -> parameters) &&
		(cmdRequest -> parameters -> paramCount == 1) &&
		(cmdRequest -> parameters -> paramList[0]) &&
		(cmdRequest -> parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
		(cmdRequest -> parameters -> paramList[0] -> paramDataType == SERVER_DESCRIPTION_DATA))
	{
		// Connection creation flag
		bool connCreated = false;

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

		// Get server description for back connection
		PSERVER_DESCRIPTION pServerDecr = serializationManager -> UnpackServerDescription(cmdRequest -> parameters -> paramList[0]);

		// Get client name
		int clientNameLen = NAME_LEN;
		char clientName[NAME_LEN] = "";
		GetComputerNameA(clientName, (LPDWORD)(&clientNameLen));

		//Validate server and client type
		if ((pServerDecr) &&
			(pServerDecr -> serverType == SERVER_TYPE_HOST) &&
			(clientDescr.clientType == CLIENT_TYPE_HOST))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("HubCommandManager : CreateBackConnection. Add back connection to HOST-server");
			#endif

			// Add connection
			if ((hostConnectionsMananger) && 
				(hostConnectionsMananger -> AddConnection(pServerDecr -> serverID, pServerDecr -> serverType, pServerDecr -> ipAddress, pServerDecr -> port, CLIENT_TYPE_HUB, clientName, NULL, DEFAULT_TIMEOUT)))
					connCreated = true;
		}
		else
		if ((pServerDecr) &&
			(pServerDecr -> serverType == SERVER_TYPE_DESKTOP) &&
			(clientDescr.clientType == CLIENT_TYPE_DESKTOP))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("HubCommandManager : CreateBackConnection. Add back connection to DESKTOP-server");
			#endif

			// Add connection
			if ((desktopConnectionsMananger) && 
				(desktopConnectionsMananger -> AddConnection(pServerDecr -> serverID, pServerDecr -> serverType, pServerDecr -> ipAddress, pServerDecr -> port, CLIENT_TYPE_HUB, clientName, NULL, DEFAULT_TIMEOUT)))
					connCreated = true;
		}

		// Delete server description
		free(pServerDecr);

		// Create response structure
		cmdResponse = serializationManager -> CreateRequestResponse(CMD_CREATE_BACK_CONNECTION, RESPONSE_CMD, cmdRequest -> header -> recipientID, cmdRequest -> header -> senderID);

		if (cmdResponse)
		{
			cmdResponse -> parameters -> paramCount = 1;
			cmdResponse -> parameters -> paramList[0] = serializationManager -> PackByte((unsigned char)connCreated, RETURN_CMD_DATA);
		}

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : CreateBackConnection. Done");
	#endif

	return cmdResponse;
}
				
/****************************************************************

   Class : HubCommandManager

   Method : RedirectRequest

   Parameters :
			Input : 
				cmdRequest - request structure

	Return : Response structure

	Description : Redirect request

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE HubCommandManager :: RedirectRequest(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : RedirectRequest. Start");
	#endif

	// Response structure pointer
	PCOMMAND_REQUEST_RESPONSE cmdResponse = NULL;

	// if recipient found
	if ((cmdRequest) &&
		(cmdRequest -> header -> recipientID == serverDescr.serverID))
	{
		cmdResponse = ExecuteCommand(cmdRequest);
	}
	else
	// recipient not found
	if ((cmdRequest) && 
		(cmdRequest -> header -> recipientID != serverDescr.serverID))
	{
		if ((hostConnectionsMananger) && (hostConnectionsMananger -> FindConnection(cmdRequest -> header -> recipientID)))
		{
			cmdResponse = hostConnectionsMananger -> SendData(cmdRequest -> header -> recipientID, cmdRequest);
		}
		else
		if (hostConnectionsMananger)
		{
			unsigned int serverID = hostConnectionsMananger -> FindMostPriorityServer();
			cmdResponse = hostConnectionsMananger -> SendData(serverID, cmdRequest);
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("HubCommandManager : RedirectRequest. Done");
	#endif

	return cmdResponse;
}
