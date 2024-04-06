/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : IPCClient.cpp

   Description :  this module implements methods of
				  class IPCClient

*****************************************************************/

#include "stdafx.h"

#include "IPCClient.h"

// z-ipcclient-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCClientDllDefinition;

/****************************************************************

   Class : IPCClientEx

   Method : IPCClient

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				aF - address family specification
				sType - windows socket type
				sProt - windows socket protocol
				serverID - remote server ID
				serverType - remote server type
				port - remote server port 
				address - remote server IP address
				timeoutValue - timeout value
				clientType - client type
				clientName - client name
				pSelfServerDescr - pointer to own server description structure

*****************************************************************/
IPCClient :: IPCClient(unsigned long dllUserID, 
							 LogWriter * logWriter, 
							 int aF, 
							 int sType, 
							 int sProt, 
							 unsigned int wsaVer, 
							 unsigned int serverID,
							 int serverType,
							 unsigned int port, 
							 char * address,
							 unsigned int timeoutValue,
							 int clientType,
							 char * clientName,
							 PSERVER_DESCRIPTION pSelfServerDescr) : SocketClient(dllUserID, 
																				  logWriter, 
																				  aF, 
																				  sType, 
																				  sProt, 
																				  wsaVer, 
																				  port, 
																				  address,
																				  timeoutValue)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : constructor");
	#endif

	// Set remote server data
	PrepareRemoteServerData(serverID, serverType);

	// Set client description to zero
	memset(&clientDescr, 0, sizeof(CLIENT_DESCRIPTION));

	// Set server description to zero
	memset(&serverDescr, 0, sizeof(SERVER_DESCRIPTION));

	// Fill client description fields
	clientDescr.clientType = clientType;

	if (clientName)
		strcpy(clientDescr.clientName, clientName);

	// Set self server description
	if (pSelfServerDescr)
	{
		this -> pSelfServerDescr = (PSERVER_DESCRIPTION)malloc(sizeof(SERVER_DESCRIPTION));

		if (this -> pSelfServerDescr)
		{
			memcpy(this -> pSelfServerDescr, pSelfServerDescr, sizeof(SERVER_DESCRIPTION));
			clientDescr.ownClientID = this -> pSelfServerDescr -> serverID;
		}
	}
	else
		this -> pSelfServerDescr = NULL;
}

/****************************************************************

   Class : IPCClient

   Method : Destructor

*****************************************************************/
IPCClient :: ~IPCClient(void)
{
	// Stop reconnection thread
	StopReconnection();

	// Disconnect from server
	if (Connected())
		Disconnect();

	if (this -> pSelfServerDescr)
		free(this -> pSelfServerDescr);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : destructor");
	#endif
}

/****************************************************************

   Class : IPCClient

   Method : PrepareRemoteServerData

   Parameters:
			Input:
				serverID - server ID
				serverType - server type

   Description : Set remote server connection data

*****************************************************************/
void IPCClient :: PrepareRemoteServerData(unsigned int serverID, int serverType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : PrepareRemoteServerData. Start");
	#endif

	if (!Connected())
	{
		this -> serverID = serverID;
		this -> serverType = serverType;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			char message[256] = "";
			sprintf(message, "IPCClient : PrepareRemoteServerData. Server ID : %d. Server type : %d", serverID, serverType);
			WriteToLog(message);
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		else
			WriteToLog("IPCClient : PrepareRemoteServerData. Can't change remote server connection settings. Socket is working now");

		WriteToLog("IPCClient : PrepareRemoteServerData. Done");
	#endif
}

/****************************************************************

   Class : IPCClient

   Method : GetRemoteServerData

   Parameters:
			Output:
				serverID - server ID
				serverType - server type

   Description : Get remote server connection data

*****************************************************************/
void IPCClient :: GetRemoteServerData(unsigned int * serverID, int * serverType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : GetRemoteServerData. Start");
	#endif

	if (serverID) *serverID = this -> serverID;

	if (serverType) *serverType = this -> serverType;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : GetRemoteServerData. Done");
	#endif
}

/****************************************************************

   Class : IPCClient

   Method : Connect

   Parameters :
			Input : 
				serverID - server ID
				serverType - server type
				port - server port
				address - server address
    
   Returns : error code

   Description : Connect to server

*****************************************************************/
int IPCClient :: Connect(unsigned int serverID, int serverType, unsigned int port, char * address)
{
	PrepareRemoteServerData(serverID, serverType);
	return SocketClient :: Connect(port, address);
}

/****************************************************************

   Class : IPCClient

   Method : Connect
    
   Returns : error code

   Description : Connect to server

*****************************************************************/
int IPCClient :: Connect(void)
{
	return SocketClient :: Connect();
}

/****************************************************************

   Class : IPCClient

   Method : ConfirmConnect
    
   Returns : Connection confirmation

   Description : Connection confirmation

*****************************************************************/
bool IPCClient :: ConfirmConnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : ConfirmConnect. Start");
	#endif

	// Close threads
	CloseThreads();

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCClientDllDefinition.dllID, logWriter);

	LOCK_SECTION(clientCSGuard);

	// Recieve data
	int recvBytes = RecieveData();
	bool confimResult = false;

	// Check command
	int checkCmdRes = SERIALIZE_DATA_ERROR;
	
	if (recvBytes > 0)
	{
		LOCK_SECTION(rBuffCSGuard);
		checkCmdRes = serializationManager -> CheckCommand(receivedDataBuffer, CMD_CONNECT, REQUEST_CMD);

		// Get client ID from server
		clientDescr.clientID = serializationManager -> ConnectInBufferUnpack(receivedDataBuffer, receivedDataBufferSize, &serverDescr);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			char message[256] = "";
			sprintf(message, "IPCClient : ConfirmConnect. Client ID : %d. Server ID : %d (%d). Server type : %d (%d)", clientDescr.clientID, serverDescr.serverID, serverID, serverDescr.serverType, serverType);
			WriteToLog(message);
		#endif
	}
	
	// Validate checking result
	if (checkCmdRes == SERIALIZE_DATA_SUCCESS)
	{
		if (clientDescr.clientID != SERIALIZE_DATA_ERROR)
		{
			if ((serverDescr.serverID == serverID) && (serverDescr.serverType == serverType))
			{
				// Fill client description
				clientDescr.osVersion = GetOSVersion();
				clientDescr.version = zIPCClientDllDefinition.dllVersion;
				strcpy(clientDescr.privateIP, bindAddrStr);
				clientDescr.privatePort = bindPort;
				strcpy(clientDescr.publicIP, bindAddrStr);
				clientDescr.publicPort = bindPort;
			
				// Serialize client description
				int packSize = 0;
				char * package = serializationManager -> ConnectBufferPack(serverDescr.serverID, &clientDescr, &packSize);

				if (package)
				{
					// Set sent data buffer
					SetDataBuffer(package, packSize, SENT_DATA_BUFFER_TYPE);

					// Delete package
					free(package);
					
					// Send buffer
					SendData();
						
					//confimResult = true;
					confimResult = CreateBackConnection();

					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
						if (confimResult)
							WriteToLog("IPCClient : ConfirmConnect. Connection confirmed!");
						else
							WriteToLog("IPCClient : ConfirmConnect. Back connection not established! Connection not confirmed!");
					#endif
				}
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					else
						WriteToLog("IPCClient : ConfirmConnect. Bad client description package!");
				#endif
			}
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				else
					WriteToLog("IPCClient : ConfirmConnect. Wrong server ID and type!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			else
				WriteToLog("IPCClient : ConfirmConnect. Bad client ID!");
		#endif
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		else
			WriteToLog("IPCClient : ConfirmConnect. Connection not confirmed!");
	#endif

	// Delete serialization manager
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : ConfirmConnect. Done");
	#endif

	return confimResult;
}

/****************************************************************

   Class : IPCClient

   Method : Disconnect
    
   Returns : Error code

   Description : Disconnect from server

*****************************************************************/
int IPCClient :: Disconnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : Disconnect. Start");
	#endif
	
	// Check connection flag
	if (!Connected())
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("IPCClient : Disconnect. Already disconnected!");
			WriteToLog("IPCClient : Disconnect. Done");
		#endif

		return SERR_NOT_CONNECTED;
	}

	WriteToLog("IPC client : Disconnecting...");

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCClientDllDefinition.dllID, logWriter);
	
	// Disconnection result
	int disconnectResult = SERR_NOT_DISCONNECTED;
		
	// Serialize disconnect command
	int packSize = 0;
	char * disconnectPackage = serializationManager -> DisconnectBufferPack(REQUEST_CMD, clientDescr.clientID, serverDescr.serverID, &packSize);
		
	if (disconnectPackage)
	{
		LOCK_SECTION(clientCSGuard);

		// Set buffer for sent data
		SetDataBuffer(disconnectPackage, packSize, SENT_DATA_BUFFER_TYPE);

		// Remove package
		free(disconnectPackage);

		// Send command
		SendData();

		dataRecieved = true;
				
		char message[128];
		sprintf(message, "IPC client : Disconnect --> Disconnected from [%s : %d]", srvAddrStr, srvPort);
		WriteToLog(message);

		// Base class disconnect method
		disconnectResult = SocketClient :: Disconnect();
	}
	else
	{
		char message[128];
		sprintf(message, "IPC client : Disconnect --> Can't disconnect from [%s : %d]", srvAddrStr, srvPort);
		WriteToLog(message);
	}
	
	// Delete serialization manager
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : Disconnect. Done");
	#endif

	return disconnectResult;
}

/****************************************************************

   Class : IPCClient

   Method : DispatchResponse
   
   Returns : whether to return the result of the query?

   Description :  Dispatch recieved response

*****************************************************************/
bool IPCClient :: DispatchResponse(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : DispatchResponse. Start");
	#endif

	LOCK_SECTION(rBuffCSGuard);
	
	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCClientDllDefinition.dllID, logWriter);

	// Get command code
	unsigned int command = serializationManager -> GetCommandCode(receivedDataBuffer);
		
	// Delete serialization manager
	delete serializationManager;
	
	// Check command code
	switch (command)
	{
		// Disconnect command
		case CMD_DISCONNECT :
		{
			Disconnect();
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClient : DispatchResponse. Disconnect command is received");
				WriteToLog("IPCClient : DispatchResponse. Done");
			#endif

			return false;
		}
		
		// Other commands
		default:
		{
			SetRecieveDataFlag(true);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClient : DispatchResponse. Server respond received");
				WriteToLog("IPCClient : DispatchResponse. Done");
			#endif

			return false;
		}
	}
}

/****************************************************************

   Class : IPCClient

   Method : CreateBackConnection
   
   Returns : TRUE - if back connection established

   Description :  Create back connection

*****************************************************************/
bool IPCClient :: CreateBackConnection(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : CreateBackConnection. Start");
	#endif

	// Check self server description
	if (!pSelfServerDescr)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("IPCClient : CreateBackConnection. No self server description!");
			WriteToLog("IPCClient : CreateBackConnection. Done");
		#endif

		return true;
	}

	bool result = false;

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCClientDllDefinition.dllID, logWriter);

	// Prepare request
	PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_CREATE_BACK_CONNECTION, REQUEST_CMD, clientDescr.clientID, serverDescr.serverID);
	
	// Create parameter with server description
	if ((pRequest) && (pRequest -> parameters))
	{
		pRequest -> parameters -> paramCount = 1;
		pRequest -> parameters -> paramList[0] = serializationManager -> PackServerDescription(pSelfServerDescr, INPUT_CMD_DATA);

		int packSize = 0;
		char * package = serializationManager -> PackCommandRequestResponse(pRequest, &packSize);
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);

		if (package)
		{
			// Set sent data buffer
			SetDataBuffer(package, packSize, SENT_DATA_BUFFER_TYPE);

			// Delete package
			free(package);
					
			// Send buffer
			SendData();

			// Recieve data
			int recvBytes = RecieveData();
			int checkCmdRes = SERIALIZE_DATA_ERROR;

			if (recvBytes > 0)
				checkCmdRes = serializationManager -> CheckCommand(receivedDataBuffer, CMD_CREATE_BACK_CONNECTION, RESPONSE_CMD);

			// Validate checking result
			if ((recvBytes > 0) && (checkCmdRes == SERIALIZE_DATA_SUCCESS))
			{
				// Get response
				PCOMMAND_REQUEST_RESPONSE pResponse = serializationManager -> UnpackCommandRequestResponse(receivedDataBuffer, receivedDataBufferSize);

				if ((pResponse) &&
					(pResponse -> parameters) &&
					(pResponse -> parameters -> paramCount == 1) &&
					(pResponse -> parameters -> paramList[0]) &&
					(pResponse -> parameters -> paramList[0] -> paramDataType == BYTE_DATA))
				{
					// Get back connection result
					result = (bool)(serializationManager -> UnpackByte(pResponse -> parameters -> paramList[0]));
					pResponse = serializationManager -> DeleteRequestResponse(pResponse);

					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
						if (result)
							WriteToLog("IPCClient : CreateBackConnection. Back connection established!");
					#endif
				}
			}
		}
	}
		
	// Delete serialization manager
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClient : CreateBackConnection. Done");
	#endif

	return result;
}
