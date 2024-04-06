/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : IPCClientsManager.cpp

   Description :  this module implements methods of
				  class IPCClientsManager

*****************************************************************/

#include "stdafx.h"

#include "IPCClientsManager.h"

// z-ipcclient-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCClientDllDefinition;

/****************************************************************

   Class : IPCClientsManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
IPCClientsManager :: IPCClientsManager(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zIPCClientDllDefinition)
{
	connectCSGuard = new CriticalSection();

	this -> logWriter = logWriter;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : constructor");
	#endif

	// Initialize list
	connectCount = 0;
	for(int i = 0; i < MAX_CLIENTS_COUNT; i++)
		connectList[i] = NULL;
}

/****************************************************************

   Class : IPCClientsManager

   Method : Destructor

*****************************************************************/
IPCClientsManager :: ~IPCClientsManager(void)
{
	ClearConnectionList();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : destructor");
	#endif

	delete connectCSGuard;
}

/****************************************************************

   Class : IPCClientsManager

   Method : AddConnection

   Parameters:
			Input:
				serverID - server ID
				serverType - server type
				serverIPAddress - IP address of server
				port - server port
				clientType - type of client
				clientName - client name
				pSelfServerDescr - self server description
				timeoutValue - timeout value

   Returns: pointer to IPC client instance

   Description : Add new connection

*****************************************************************/
IPCClient * IPCClientsManager :: AddConnection(unsigned int serverID, int serverType, char * serverIPAddress, unsigned int port, int clientType, char * clientName, PSERVER_DESCRIPTION pSelfServerDescr, unsigned int timeoutValue)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : AddConnection. Start");
	#endif

	// Try to find server
	IPCClient * ipcClient = FindConnection(serverID);

	// if no such connection
	if ((!ipcClient) && (connectCount < MAX_CLIENTS_COUNT - 1))
	{
		LOCK_SECTION(connectCSGuard);

		ipcClient = new IPCClient(dllUserID, logWriter, AF_INET, SOCK_STREAM, 0, 0x0202, serverID, serverType, port, serverIPAddress, timeoutValue, clientType, clientName, pSelfServerDescr);
		ipcClient -> Connect();
		ipcClient -> StartReconnection();
		
		// Add connection to list
		connectList[connectCount] = ipcClient;
		connectCount++;

		char message[128];
		sprintf(message, "IPC client manager --> Added new connection to list [%s : %d]", serverIPAddress, port);
		WriteToLog(message);
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		else
			WriteToLog("IPCClientsManager : AddConnection. New connection can not be added!");

		WriteToLog("IPCClientsManager : AddConnection. Done");
	#endif

	return ipcClient;
}

/****************************************************************

   Class : IPCClientsManager

   Method : RemoveConnection

   Parameters:
			Input:
				index - index of connection in list

   Returns: pointer to IPC client

   Description : Remove connection from list

*****************************************************************/
IPCClient * IPCClientsManager :: RemoveConnection(int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : RemoveConnection");
	#endif

	IPCClient * ipcClient = NULL;

	LOCK_SECTION(connectCSGuard);
	
	if ((index >= 0) && (index <= connectCount - 1) && (connectList[index]))
	{
		char message[128];
		sprintf(message, "IPC client manager --> Remove connection from list [%s : %d]", connectList[index] -> serverDescr.ipAddress, connectList[index] -> serverDescr.port);
		WriteToLog(message);

		delete connectList[index];
		
		connectList[index] = NULL;
		ipcClient = connectList[index];

		for(int i = index; i < connectCount - 1; i++)
		   connectList[i] = connectList[i + 1];
		
		connectList[connectCount - 1] = NULL;
		connectCount--;
	}

	return ipcClient;
}

/****************************************************************

   Class : IPCClientsManager

   Method : ClearConnectionList

   Description : Clear connection list

*****************************************************************/
void IPCClientsManager :: ClearConnectionList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : ClearConnectionList. Start");
	#endif

	for (int i = connectCount - 1; i >= 0; i--)
		RemoveConnection(i);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : ClearConnectionList. Done");
	#endif
}

/****************************************************************

   Class : IPCClientsManager

   Method : FindConnection

   Parameters:
			Input:
				serverID - server ID

   Returns: pointer to IPC client

   Description : Find connection

*****************************************************************/
IPCClient *  IPCClientsManager :: FindConnection(unsigned int serverID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : FindConnection. Start");
	#endif

	LOCK_SECTION(connectCSGuard);

	for (int i = 0; i < connectCount; i++)
	{
		if (connectList[i] -> serverDescr.serverID == serverID)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClientsManager : FindConnection. Connection found!");
				WriteToLog("IPCClientsManager : FindConnection. Done");
			#endif

			return connectList[i];
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : FindConnection. Connection not found!");
		WriteToLog("IPCClientsManager : FindConnection. Done");
	#endif

	return NULL;
}

/****************************************************************

   Class : IPCClientsManager

   Method : FindConnection

   Parameters:
			Input:
				serverID - server ID

   Returns: connection index

   Description : Find connection

*****************************************************************/
int IPCClientsManager :: FindConnectionIndex(unsigned int serverID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : FindConnectionIndex. Start");
	#endif

	LOCK_SECTION(connectCSGuard);

	for (int i = 0; i < connectCount; i++)
	{
		if (connectList[i] -> serverDescr.serverID == serverID)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClientsManager : FindConnectionIndex. Connection found!");
				WriteToLog("IPCClientsManager : FindConnectionIndex. Done");
			#endif
			
			return i;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : FindConnectionIndex. Connection not found!");
		WriteToLog("IPCClientsManager : FindConnectionIndex. Done");
	#endif

	return -1;
}

/****************************************************************

   Class : IPCClientsManager

   Method : GetServerID

   Parameters:
			Input:
				index - connection index

   Returns: server ID

   Description : Get server ID

*****************************************************************/
unsigned int IPCClientsManager :: GetServerID(int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : GetServerID");
	#endif

	unsigned int serverID = 0;

	LOCK_SECTION(connectCSGuard);
	
	if ((index >= 0) && (index <= connectCount - 1) && (connectList[index]))
	{
		serverID = connectList[index] -> serverDescr.serverID;
	}

	return serverID;
}

/****************************************************************

   Class : IPCClientsManager

   Method : FindMostPriorityServer

   Returns: server ID

   Description : Find most priority server

*****************************************************************/
unsigned int IPCClientsManager :: FindMostPriorityServer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : FindMostPriorityServer");
	#endif

	LOCK_SECTION(connectCSGuard);

	int mainPriority = 0;
	unsigned int mainServerID = 0;

	if (connectCount > 0)
	{
		mainPriority = connectList[0] -> serverDescr.serverPriority;
		mainServerID = connectList[0] -> serverDescr.serverID;

		for (int i = 1; i < connectCount; i++)
		{
			if (connectList[i] -> serverDescr.serverPriority > mainPriority)
			{
				mainPriority = connectList[i] -> serverDescr.serverPriority;
				mainServerID = connectList[i] -> serverDescr.serverID;
			}
		}
	}

	return mainServerID;
}

/****************************************************************

   Class : IPCClientsManager

   Method : FindMostPriorityServer

   Returns: Server description list

   Description : Get server description list

*****************************************************************/
PSERVER_DESCRIPTION_LIST IPCClientsManager :: GetServerDescriptionList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : GetServerDescriptionList");
	#endif

	LOCK_SECTION(connectCSGuard);

	PSERVER_DESCRIPTION_LIST serverList = (PSERVER_DESCRIPTION_LIST)malloc(sizeof(SERVER_DESCRIPTION_LIST));

	if (serverList)
	{
		serverList -> serversCount = connectCount;

		for (int i = 0; i < connectCount; i++)
		{
			serverList -> serversList[i] = (PSERVER_DESCRIPTION)malloc(sizeof(SERVER_DESCRIPTION));

			if (serverList -> serversList[i])
				memcpy(serverList -> serversList[i], &(connectList[i] -> serverDescr), sizeof(SERVER_DESCRIPTION));
		}
	}

	return serverList;
}

/****************************************************************

   Class : IPCClientsManager

   Method : SendData

   Parameters :
			Input : 
				serverID - server ID
				requestPack - request package
				requestSize - request package size

			Oputput :
				responsePackSize - response package size

	Return : Response package

	Description : Send data via IPC client

*****************************************************************/
char * IPCClientsManager :: SendData(unsigned int serverID, char * requestPack, int requestSize, int * responsePackSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : SendData. Start");
	#endif

	// Get IPC client
	IPCClient * ipcClient = FindConnection(serverID);

	// Check legal DLL user
	ipcClient -= dllUserCheckResult;
	
	if ((ipcClient) && (ipcClient -> Connected()) &&
		(requestPack) && (requestSize > 0))
	{
		LOCK_SECTION(connectCSGuard);

		// Set send data package
		ipcClient -> SetDataBuffer(requestPack, requestSize, SENT_DATA_BUFFER_TYPE);

		// Send command
		ipcClient -> SetRecieveDataFlag(false);
		
		if (ipcClient -> SendData() <= 0)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClientsManager : SendData. Can't send data!");
				WriteToLog("IPCClientsManager : SendData. Done");
			#endif
			
			*responsePackSize = 0;

			return NULL;
		}

		// Get command result
		unsigned int counter = 4096;
		while ((ipcClient -> Connected()) &&
			   (!(ipcClient -> GetRecieveDataFlag())) && 
			   (counter > 0))
		{
			Sleep(100);
			counter--;
		}

		// Check connection
		if (!(ipcClient -> Connected()))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClientsManager : SendData. Lost connection! Response not received!");
				WriteToLog("IPCClientsManager : SendData. Done");
			#endif

			*responsePackSize = 0;
			return NULL;
		}

		// Check timeout
		if (counter == 0)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClientsManager : SendData. Timeout! Response not received!");
				WriteToLog("IPCClientsManager : SendData. Done");
			#endif
			
			*responsePackSize = 0;
			return NULL;
		}

		*responsePackSize = ipcClient -> GetDataBufferSize(RECEIVED_DATA_BUFFER_TYPE);
		char * receivedResult = ipcClient -> GetDataBuffer(RECEIVED_DATA_BUFFER_TYPE);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("IPCClientsManager : SendData. Respose recieved.");
			WriteToLog("IPCClientsManager : SendData. Done");
		#endif

		return receivedResult;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("IPCClientsManager : SendData. Bad socket client instance!");
			WriteToLog("IPCClientsManager : SendData. Done");
		#endif

		*responsePackSize = 0;
		return NULL;
	}
}

/****************************************************************

   Class : RedirectionCommand

   Method : SendData

   Parameters :
			Input : 
				serverID - server ID
				pRequest - request structure

	Return : Response structure

	Description : Send data via IPC client

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE IPCClientsManager :: SendData(unsigned int serverID, PCOMMAND_REQUEST_RESPONSE pRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManager : SendData. Start");
	#endif

	if (pRequest)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zIPCClientDllDefinition.dllID, logWriter);
		
		int requestPackageSize = 0;
		char * requestPackage = serializationManager -> PackCommandRequestResponse(pRequest, &requestPackageSize);

		int responsePackageSize = 0;
		char * responsePackage = SendData(serverID, requestPackage, requestPackageSize, &responsePackageSize);

		PCOMMAND_REQUEST_RESPONSE pResponse = NULL;
		if ((responsePackage != NULL) && (responsePackageSize > 0))
		{
			pResponse = serializationManager -> UnpackCommandRequestResponse(responsePackage, responsePackageSize);
			free(responsePackage);
		}

		// Delete serialization manager instance
		delete serializationManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("IPCClientsManager : SendData. Done");
		#endif

		return pResponse;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		else
			WriteToLog("IPCClientsManager : SendData. Bad request structure!");

		WriteToLog("IPCClientsManager : SendData. Done");
	#endif

	return NULL;
}

/****************************************************************

   Class : IPCClientsManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int IPCClientsManager :: WriteToLog(char * message)
{
    if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}
