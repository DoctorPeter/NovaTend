/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetHubServerListCommand.cpp

   Description :  this module implements methods of
				  class GetHubServerListCommand

*****************************************************************/

#include "stdafx.h"
#include "GetHubServerListCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : GetHubServerListCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
GetHubServerListCommand :: GetHubServerListCommand(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * hubConnectionsMananger) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetHubServerListCommand : constructor");
	#endif
	
	this -> hubConnectionsMananger = hubConnectionsMananger;
}

/****************************************************************

   Class : GetHubServerListCommand

   Method : Destructor

*****************************************************************/
GetHubServerListCommand :: ~GetHubServerListCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetHubServerListCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetHubServerListCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetHubServerListCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetHubServerListCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((!parameters) || 
		((parameters) &&
		(parameters -> paramCount == 0)))
	{

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			PSERVER_DESCRIPTION_LIST hubServerList = GetHubServersList();
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackServerDescriptionList(hubServerList, RETURN_CMD_DATA);
			hubServerList = DeleteServerListContainer(hubServerList);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetHubServerListCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("GetHubServerListCommand : Execute. Wrong input parameters!");

		WriteToLog("GetHubServerListCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetUserListCommand

   Method : GetUserListContainer

   Return : Pointer to list of users

   Description : Get list of users

*****************************************************************/
PSERVER_DESCRIPTION_LIST GetHubServerListCommand :: GetHubServersList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetHubServerListCommand : GetHubServersList. Start");
	#endif
	
	PSERVER_DESCRIPTION_LIST serverListContainer = NULL;
	
	if (hubConnectionsMananger)
		serverListContainer = hubConnectionsMananger -> GetServerDescriptionList();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetHubServerListCommand : GetHubServersList. Done");
	#endif

	return serverListContainer - dllUserCheckResult;
}

/****************************************************************

   Class : GetHubServerListCommand

   Method : DeleteUserListContainer

   Parameters:
			Input:
				userList - pointer to user list

   Return : Pointer to list of users

   Description : Delete list of users

*****************************************************************/
PSERVER_DESCRIPTION_LIST GetHubServerListCommand :: DeleteServerListContainer(PSERVER_DESCRIPTION_LIST serverList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetHubServerListCommand : DeleteServerListContainer");
	#endif

	if (serverList)
	{
		for (int i = 0; i < serverList -> serversCount; i++)
			free(serverList -> serversList[i]);

		free(serverList);
	}

	return serverList;
}