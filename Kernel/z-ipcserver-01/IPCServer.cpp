/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : IPCServer.cpp

   Description :  this module implements methods of
				  class IPCServer

*****************************************************************/
#include "stdafx.h"

#include "IPCServer.h"
#include "IPCProcessor.h"

// z-ipcserver-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCServerDllDefinition;

/****************************************************************

   Class : IPCServer

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				serverID - server ID
				serverType - server type
				serverPriority - server priority
				serverName - server name
				maxClientsCount - maximum count of clients
				aF - address family specification
				sType - windows socket type
				sProt - windows socket protocol
				wsaVer - windows socket api version
				port - server port
				address - server address
				commandManager - pointer to command manager instance

*****************************************************************/
IPCServer :: IPCServer(unsigned long dllUserID, 
					   LogWriter * logWriter,
					   unsigned int serverID,
					   int serverType,
					   int serverPriority,
					   char * serverName,
					   int maxClientsCount,
					   int aF, 
					   int sType, 
					   int sProt, 
					   unsigned int wsaVer, 
					   unsigned int port, 
				       char * address,
					   CommandManager * commandManager) : SocketServer(dllUserID, 
																	   logWriter, 
																	   maxClientsCount, 
																	   aF, 
																	   sType, 
																	   sProt, 
																	   wsaVer, 
																	   port, 
																	   address)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServer : constructor");
	#endif

	this -> serverID = serverID;
	this -> serverType = serverType;
	this -> serverPriority = serverPriority;

	if (serverName)
		strcpy(this -> serverName, serverName);
	else
		strcpy(this -> serverName, "Unknown server");

	this -> commandManager = commandManager;
}

/****************************************************************

   Class : IPCServer

   Method : Destructor

*****************************************************************/
IPCServer :: ~IPCServer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServer : destructor");
	#endif
}

/****************************************************************

   Class : IPCServer

   Method : CreateClientProcessor

   Parameters :
			Input : 
				socket - windows socket descriptor
				address - client address

   Returns: Client processor instance

   Description :  Create client processor

*****************************************************************/
ClientProcessor * IPCServer :: CreateClientProcessor(SOCKET socket, sockaddr_in * address)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServer : CreateClientProcessor. Start");
	#endif

	// Create command manager instance
	CommandManager * commandManagerClone = NULL;

	if (commandManager)
		commandManagerClone = commandManager -> Clone();

	// Create client processor instance
	ClientProcessor * clientProcessor = new IPCProcessor(this -> dllUserID, commandManagerClone, this, socket, address, ClientProcessing, logWriter, DEFAULT_TIMEOUT);
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServer : CreateClientProcessor. Done");
	#endif

	return clientProcessor;
}

/****************************************************************

   Class : IPCServer

   Method : GenerateClientID

   Returns : client ID
    
   Description :  Generate new unique ID for client

*****************************************************************/
unsigned int IPCServer :: GenerateClientID(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServer : GenerateClientID. Start");
	#endif

	// Generate random value
	unsigned int ID = Rand();

	// Flag of generation finish
	bool newIDGenerated;

	do
	{
		LOCK_SECTION(serverCSGuard);

		newIDGenerated = true;

		// Enum all processors
		for (int i = 0; i < clientsCount; i++)
		{
			IPCProcessor * processor = (IPCProcessor *)clientProcessors[i];

			// Check client ID
			if ((processor) && (processor -> clientDescr.clientID == ID))
			{
				newIDGenerated = false;
				break;
			}
		}

		// Check flag of generation finish
		if (!newIDGenerated) ID = Rand();

	}while (!newIDGenerated);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		char message[128];
		sprintf(message, "IPCServer : GenerateClientID. Generated value: %d ", ID);
		WriteToLog(message);
		WriteToLog("IPCServer : GenerateClientID. Done");
	#endif

	return ID;
}

/****************************************************************

   Class : IPCServer

   Method : GetServerDescription

   Returns : server description
    
   Description :  Get server description

*****************************************************************/
PSERVER_DESCRIPTION IPCServer :: GetServerDescription(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServer : GetServerDescription");
	#endif

	PSERVER_DESCRIPTION serverDescription = (PSERVER_DESCRIPTION)malloc(sizeof(SERVER_DESCRIPTION));

	if (serverDescription)
	{
		serverDescription -> port = port;
		strcpy(serverDescription -> ipAddress, address);
		serverDescription -> serverID = serverID;
		serverDescription -> serverType = serverType;
		serverDescription -> serverPriority = serverPriority;
		strcpy(serverDescription -> serverName, serverName);
	}

	return serverDescription;
}

/****************************************************************

   Class : IPCServer

   Method : FindClient

   Parameters:
			Input:
				ownClientID - client ID (own, not generated by server)
				clientType - client type

   Returns : client description
    
   Description :  Find client in server connections list

*****************************************************************/
PCLIENT_DESCRIPTION IPCServer :: FindClient(unsigned int ownClientID, int clientType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServer : FindClient. Start");
	#endif

	PCLIENT_DESCRIPTION pClientDescription = (PCLIENT_DESCRIPTION)malloc(sizeof(CLIENT_DESCRIPTION));

	if (!pClientDescription)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCServer : FindClient. Memory allocation error!!!");
			WriteToLog("IPCServer : FindClient. Done");
		#endif

		return NULL;
	}

	LOCK_SECTION(serverCSGuard);

	bool found = false;

	for (int i = clientsCount - 1; i >= 0; i--)
	{
		IPCProcessor * processor = (IPCProcessor *)clientProcessors[i];

		if ((processor) && (processor -> clientDescr.ownClientID == ownClientID) && (processor -> clientDescr.clientType == clientType))
		{
			memcpy(pClientDescription, &(processor -> clientDescr), sizeof(CLIENT_DESCRIPTION));
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCServer : FindClient. Client not found!");
		#endif

		free(pClientDescription);
		pClientDescription = NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServer : FindClient. Done");
	#endif

	return pClientDescription;
}

/****************************************************************

   Class : IPCServer

   Method : FindClient

   Parameters:
			Input:
				clientID - client ID

   Returns : pointer to client processor
    
   Description :  Find client in server connections list

*****************************************************************/
ClientProcessor * IPCServer :: FindClient(unsigned int clientID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServer : FindClient. Start");
	#endif
	
	ClientProcessor * resultCP = NULL;

	LOCK_SECTION(serverCSGuard);

	bool found = false;

	for (int i = clientsCount - 1; i >= 0; i--)
	{
		IPCProcessor * processor = (IPCProcessor *)clientProcessors[i];

		if ((processor) && (processor -> clientDescr.clientID == clientID))
		{
			resultCP = processor;
			found = true;
			break;
		}
	}
			
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		if (!found)
			WriteToLog("IPCServer : FindClient. Client not found!");

		WriteToLog("IPCServer : FindClient. Done");
	#endif

	return resultCP;
}