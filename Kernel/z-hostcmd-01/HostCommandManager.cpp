/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : HostCommandManager.cpp

   Description :  this module implements methods of
				  class HostCommandManager

*****************************************************************/

#include "stdafx.h"
#include "HostCommandManager.h"
#include "CheckLicenseCommand.h"
#include "GetContentCommand.h"
#include "GetUserListCommand.h"
#include "GetUserDescriptorCommand.h"
#include "CheckAccessCommand.h"
#include "ValidateParamsCommand.h"
#include "ValidateAnswersCommand.h"
#include "ValidateUserCustomPasswordCommand.h"
#include "SetUserSignInDateCommand.h"
#include "SaveNotificationHistoryCommand.h"
#include "GetDBAccessCommand.h"
#include "GetAuthSystemIDCommand.h"
#include "CheckSignInDateCommand.h"
#include "ValidateUserAccountCommand.h"
#include "ResetUserPwdCommand.h"
#include "GetHubServerListCommand.h"
#include "GetAuthSysUserInfoCommand.h"
#include "CheckScheduleCommand.h"
#include "CheckProgramsCommand.h"

#include <RedirectionCommand.h>
#include <Scheduler.h>


// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : HostCommandManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				hostConnectionsMananger - manager of connections 
				                          to host servers
				desktopConnectionsMananger - manager of connections 
				                             to desktop servers
				hubConnectionsMananger - manager of connections 
				                         to hub servers

*****************************************************************/
HostCommandManager :: HostCommandManager(unsigned long dllUserID, 
										 LogWriter * logWriter,
										 IPCClientsManager * hostConnectionsMananger,
									     IPCClientsManager * desktopConnectionsMananger,
									     IPCClientsManager * hubConnectionsMananger) : HubCommandManager(dllUserID, 
																										 logWriter,
																										 hostConnectionsMananger,
																										 desktopConnectionsMananger)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : constructor");
	#endif

	this -> hubConnectionsMananger = hubConnectionsMananger;
}

/****************************************************************

   Class : HostCommandManager

   Method : Copy constructor

   Parameters :
			Input : 
				src - soucre instance

*****************************************************************/
HostCommandManager :: HostCommandManager(const HostCommandManager & src) : HubCommandManager(src.dllUserID, src.logWriter, src.hostConnectionsMananger, src.desktopConnectionsMananger)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : Copy constructor");
	#endif

	hubConnectionsMananger = src.hubConnectionsMananger;
}

/****************************************************************

   Class : HostCommandManager

   Method : Destructor

*****************************************************************/
HostCommandManager :: ~HostCommandManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : destructor");
	#endif
}

/****************************************************************

   Class : HostCommandManager

   Method : Clone

   Return : Pointer to command mamanger clone object

   Description : Clone command manager

*****************************************************************/
CommandManager * HostCommandManager :: Clone(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : Clone");
	#endif
	
	HostCommandManager * cloneObject = new HostCommandManager(*this);
	
	return cloneObject;
}

/****************************************************************

   Class : HostCommandManager

   Method : GenerateCommand

   Parameters :
			Input : 
				commandType - type of command

	Return : Command instance

	Description : Generate command instance by command type

*****************************************************************/
Command * HostCommandManager :: GenerateCommand(int commandType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : GenerateCommand. Start");
	#endif

	Command * command = NULL;

	switch (commandType)
	{
		case CMD_CHECK_LICENSE :
			{
				// Check license of the client
				command = new CheckLicenseCommand(dllUserID, logWriter);
				break;
			}

		case CMD_GET_CONTENT :
			{
				// Get user content
				command = new GetContentCommand(dllUserID, logWriter);
				break;
			}

		case CMD_GET_USER_LIST :
			{
				// Get list of simple user descriptors
				command = new GetUserListCommand(dllUserID, logWriter);
				break;
			}

		case CMD_GET_USER_DESCRIPTOR :
			{
				// Get user descriptor
				command = new GetUserDescriptorCommand(dllUserID, logWriter);
				break;
			}
			
		case CMD_CHECK_ACCESS :
			{
				// Check access to the database server
				command = new CheckAccessCommand(dllUserID, logWriter);
				break;
			}

		case CMD_VALIDATE_PARAMS :
			{
				// Validate user parameters for checking
				command = new ValidateParamsCommand(dllUserID, logWriter);
				break;
			}

		case CMD_VALIDATE_ANSWERS :
			{
				// Validate user answers
				command = new ValidateAnswersCommand(dllUserID, logWriter);
				break;
			}

		case CMD_VALIDATE_USER_CUSTOM_PASSWORDS :
			{
				// Validate user custom passwords
				command = new ValidateUserCustomPasswordCommand(dllUserID, logWriter);
				break;
			}

		case CMD_SET_USER_SIGNIN_DATE :
			{
				// Set user sign in date
				command = new SetUserSignInDateCommand(dllUserID, logWriter);
				break;
			}

		case CMD_SAVE_NOTIFICATION_HISTORY :
			{
				// Save user notification history
				command = new SaveNotificationHistoryCommand(dllUserID, logWriter);
				break;
			}

		case CMD_GET_DB_ACCESS :
			{
				// Get database access parameters
				command = new GetDBAccessCommand(dllUserID, logWriter);
				break;
			}

		case CMD_GET_AUTH_SYSTEM :
			{
				// Get authentication system ID
				command = new GetAuthSystemIDCommand(dllUserID, logWriter);
				break;
			}

		case CMD_CHECK_SIGN_IN_DATE :
			{
				// Check user sign in date
				command = new CheckSignInDateCommand(dllUserID, logWriter);
				break;
			}

		case CMD_VALIDATE_USER_ACCOUNT :
			{
				// Validate user account
				command = new ValidateUserAccountCommand(dllUserID, logWriter);
				break;
			}

		case CMD_RESET_USER_PASSWORD :
			{
				// Reset user password
				command = new ResetUserPwdCommand(dllUserID, logWriter);
				break;
			}

		case CMD_GET_HUB_SERVERS_LIST :
			{
				// Get hub servers list
				command = new GetHubServerListCommand(dllUserID, logWriter, hubConnectionsMananger);
				break;
			}

		case CMD_GET_AUTH_SYS_USER_INFO :
			{
				// Get user and auth system info
				command = new GetAuthSysUserInfoCommand(dllUserID, logWriter);
				break;
			}

		case CMD_CHECK_SCHEDULE :
			{
				// Check schedule records
				command = new CheckScheduleCommand(dllUserID, logWriter);
				break;
			}

		case CMD_CHECK_PROGRAMS :
			{
				// Check program list
				command = new CheckProgramsCommand(dllUserID, logWriter);
				break;
			}

		case CMD_LOCK_USER_CAD_ACTIONS :
		case CMD_GET_CLIENT_SCREEN_SHOT :
		case CMD_GET_CLIENT_CAM_SNAPSHOT :
		case CMD_GET_USER_ENV_INFO :
		case CMD_GET_HARDWARE_INFO :
		case CMD_GET_LOGGED_USER_NAME :
		case CMD_GET_COMPUTER_NAME :
		case CMD_GET_FULL_CLIENT_INFO :
		case CMD_GET_GEO_LOCATION :
		case CMD_FILE_TRANSFER :
		case CMD_GET_CMD_HISTORY :
			{
				// Commands for HUB functionality
				command = HubCommandManager :: GenerateCommand(commandType);
				break;
			}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : GenerateCommand. Done");
	#endif

	return command - dllUserCheckResult;
}

/****************************************************************

   Class : HostCommandManager

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
bool HostCommandManager :: CheckLicense(char * id, char * strValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("HostCommandManager : CheckLicense. Start");
	#endif

	LicenseManager * licenseManager = new LicenseManager(zHostCmdDllDefinition.dllID, logWriter);
	bool result = licenseManager -> CheckLicensePointValue(id, strValue, index, relType);
	licenseManager -> GetLicensePointValue(id, strValue, index);
	delete licenseManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("HostCommandManager : CheckLicense. Done");
	#endif

	return result;
}

/****************************************************************

   Class : HostCommandManager

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
bool HostCommandManager :: CheckLicense(char * id, int * intValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("HostCommandManager : CheckLicense. Start");
	#endif

	bool result = false;

	if (intValue)
	{
		LicenseManager * licenseManager = new LicenseManager(zHostCmdDllDefinition.dllID, logWriter);
		result = licenseManager -> CheckLicensePointValue(id, *intValue, index, relType);
		*intValue = licenseManager -> GetLicensePointValue(id, index);
		delete licenseManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("HostCommandManager : CheckLicense. Done");
	#endif

	return result;
}

/****************************************************************

   Class : HostCommandManager

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
bool HostCommandManager :: CheckLicense(char * id, tm * tmValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("HostCommandManager : CheckLicense. Start");
	#endif

	LicenseManager * licenseManager = new LicenseManager(zHostCmdDllDefinition.dllID, logWriter);
	bool result = licenseManager -> CheckLicensePointValue(id, tmValue, index, relType);
	licenseManager -> GetLicensePointValue(id, tmValue, index);
	delete licenseManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("HostCommandManager : CheckLicense. Done");
	#endif

	return result;
}
	
/****************************************************************

   Class : HostCommandManager

   Method : CheckMonitoringAccess

   Parameters:
			Input:
				cmdRequest - request structure

   Return : TRUE - if access allowed

   Description : Check access monitoring

*****************************************************************/
bool HostCommandManager :: CheckMonitoringAccess(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : CheckMonitoringAccess. Start");
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
		case CMD_GET_FULL_CLIENT_INFO :
		{
			if ((cmdRequest) &&	
				(cmdRequest -> parameters) && 
				((cmdRequest -> parameters -> paramCount) > 0) &&	
				(cmdRequest -> parameters -> paramList[0]))
			{
				if (cmdRequest -> header -> recipientID != serverDescr.serverID)
				{
					checkResult = true;
				}
				else
				{
					// Create serialization manager instance
					SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);

					// Get user ID
					int userID = serializationManager -> UnpackDWORD(cmdRequest -> parameters -> paramList[0]);

					// Get computer name
					char compName[NAME_LEN] = "";
					unsigned long compNameLen = NAME_LEN;
					GetComputerNameA(compName, &compNameLen);

					// Get scheduler
					Scheduler * scheduler = new Scheduler(zHostCmdDllDefinition.dllID, logWriter);
					int actionCode = scheduler -> VerifyScheduleRecords(userID, compName, MONITORING_FUNCTION);
					delete scheduler;
				
					// Get result	
					checkResult = true;

					if ((actionCode & DENY_ACTION) == DENY_ACTION)
						checkResult = false;

					if ((actionCode & IGNORE_ACTION) == IGNORE_ACTION)
						checkResult = false;
								
					// Delete serialization manager instance
					delete serializationManager;
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

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : CheckMonitoringAccess. Done");
	#endif

	return checkResult;
}

/****************************************************************

   Class : HostCommandManager

   Method : CreateBackConnection

   Parameters :
			Input : 
				cmdRequest - back connection creation request

	Return : Back connection result

	Description : Create back connection

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE HostCommandManager :: CreateBackConnection(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : CreateBackConnection. Start");
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
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);

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
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				WriteToLog("HostCommandManager : CreateBackConnection. Add back connection to HOST-server");
			#endif

			// Add connection
			if ((hostConnectionsMananger) && 
				(hostConnectionsMananger -> AddConnection(pServerDecr -> serverID, pServerDecr -> serverType, pServerDecr -> ipAddress, pServerDecr -> port, CLIENT_TYPE_HOST, clientName, NULL, DEFAULT_TIMEOUT)))
					connCreated = true;
		}
		else
		if ((pServerDecr) &&
			(pServerDecr -> serverType == SERVER_TYPE_DESKTOP) &&
			(clientDescr.clientType == CLIENT_TYPE_DESKTOP))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				WriteToLog("HostCommandManager : CreateBackConnection. Add back connection to DESKTOP-server");
			#endif

			// Add connection
			if ((desktopConnectionsMananger) && 
				(desktopConnectionsMananger -> AddConnection(pServerDecr -> serverID, pServerDecr -> serverType, pServerDecr -> ipAddress, pServerDecr -> port, CLIENT_TYPE_HOST, clientName, NULL, DEFAULT_TIMEOUT)))
					connCreated = true;
		}
		else
		if ((pServerDecr) &&
			(pServerDecr -> serverType == SERVER_TYPE_HUB) &&
			(clientDescr.clientType == CLIENT_TYPE_HUB))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				WriteToLog("HostCommandManager : CreateBackConnection. Add back connection to HUB-server");
			#endif

			// Add connection
			if ((hubConnectionsMananger) && 
				(hubConnectionsMananger -> AddConnection(pServerDecr -> serverID, pServerDecr -> serverType, pServerDecr -> ipAddress, pServerDecr -> port, CLIENT_TYPE_HOST, clientName, NULL, DEFAULT_TIMEOUT)))
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

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : CreateBackConnection. Done");
	#endif

	return cmdResponse;
}
				
/****************************************************************

   Class : HostCommandManager

   Method : RedirectRequest

   Parameters :
			Input : 
				cmdRequest - request structure

	Return : Response structure

	Description : Redirect request

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE HostCommandManager :: RedirectRequest(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : RedirectRequest. Start");
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
		if ((hubConnectionsMananger) && (hubConnectionsMananger -> FindConnection(cmdRequest -> header -> recipientID)))
		{
			cmdResponse = hubConnectionsMananger -> SendData(cmdRequest -> header -> recipientID, cmdRequest);
		}
		else
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

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("HostCommandManager : RedirectRequest. Done");
	#endif

	return cmdResponse;
}