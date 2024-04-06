/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : IPCClientEx.cpp

   Description :  this module implements methods of
				  class IPCClientEx

*****************************************************************/

#include "stdafx.h"

#include "IPCClientEx.h"

// z-ipcclient-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCClientDllDefinition;

/****************************************************************

   Class : IPCClientEx

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				aF - address family specification
				sType - windows socket type
				sProt - windows socket protocol
				wsaVer - windows socket api version
				localServerID - local server ID
				localServerType - local server type
				localPort - local server port
				localAddress - local server address
				globalServerID - global server ID
				globalPort - global server port
				globalAddress - global server address
				timeoutValue - timeout value
				clientType - client type
				clientName - client name
				pSelfServerDescr - pointer to own server description structure
				pIPCServerEx - pointer to extended IPC server instance

*****************************************************************/
IPCClientEx :: IPCClientEx(unsigned long dllUserID,
							LogWriter * logWriter,
							int aF,
							int sType, 
							int sProt,
							unsigned int wsaVer, 
							unsigned int localServerID,
							int localServerType,
							unsigned int localPort,
							char * localAddress,
							unsigned int globalServerID,
							unsigned int globalPort,
							char * globalAddress,
							unsigned int timeoutValue,
							int clientType,
							char * clientName,
							PSERVER_DESCRIPTION pSelfServerDescr,
							IPCServerEx * pIPCServerEx) : IPCClient(dllUserID, 
																	logWriter, 
																	aF,  
																	sType, 
																	sProt, 
																	wsaVer,
																	localServerID,
																	localServerType,
																	localPort, 
																	localAddress,
																	timeoutValue,
																	clientType,
																	clientName, 
																	pSelfServerDescr)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : constructor");
	#endif

	// Set global server ID
	this -> globalServerID = globalServerID;

	// Set pointer to extended IPC server instance
	this -> pIPCServerEx = pIPCServerEx;

	if ((!(this -> pSelfServerDescr)) && (this -> pIPCServerEx))
	{
		clientDescr.ownClientID = this -> pIPCServerEx -> serverID;
	}

	// Set initial values to remote address
	remoteSrvAddrStr[0] = 0;
	remoteSrvPort = 0;

	// Save connection data
	PrepareSocketConnection(localPort, localAddress, globalPort, globalAddress);
}

/****************************************************************

   Class : IPCClientEx

   Method : Destructor

*****************************************************************/
IPCClientEx :: ~IPCClientEx(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : destructor");
	#endif
}

/****************************************************************

   Class : SocketClient

   Method : PrepareSocketConnection
    
   Parameters :
			Input : 
				localPort - local server port
				localAddress - local server address
				globalPort - global server port
				globalAddress - global server address

   Description :  Set windows socket connection data

*****************************************************************/
void IPCClientEx :: PrepareSocketConnection(unsigned int localPort, char * localAddress, unsigned int globalPort, char * globalAddress)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : PrepareSocketConnection. Start");
	#endif

	if (!Connected())
	{
		srvPort = localPort;
	
		if (localAddress != NULL)
			strcpy(srvAddrStr, localAddress);
		else
			strcpy(srvAddrStr, "127.0.0.1");

		gSrvPort = globalPort;
	
		if (globalAddress != NULL)
			strcpy(gSrvAddrStr, globalAddress);
		else
			strcpy(gSrvAddrStr, "127.0.0.1");
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		else
			WriteToLog("IPCClientEx : PrepareSocketConnection. Can't change socket connection settings. Socket is working now");

		WriteToLog("IPCClientEx : PrepareSocketConnection. Done");
	#endif
}

/****************************************************************

   Class : IPCClientEx

   Method : GetSocketConnection
    
   Parameters :
			Output : 
				port - server port
				address - server address

   Description :  Get windows socket connection data

*****************************************************************/
void IPCClientEx :: GetSocketConnection(unsigned int  * localPort, char * localAddress, unsigned int  * globalPort, char * globalAddress)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : GetSocketConnection. Start");
	#endif

	if (localPort) *localPort = srvPort;

	if (localAddress) strcpy(localAddress, srvAddrStr);

	if (globalPort) *globalPort = gSrvPort;

	if (globalAddress) strcpy(globalAddress, gSrvAddrStr);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : GetSocketConnection. Done");
	#endif
}


/****************************************************************

   Class : IPCClientEx

   Method : Connect
    
   Returns : error code

   Description : Connect to server

*****************************************************************/
int IPCClientEx :: Connect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : Connect. Start");
	#endif

	// Try to connect via local address
	int connectResult = IPCClient :: Connect();

	// May be already connected
	if (connectResult == SERR_ALREADY_CONNECTED)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("IPCClientEx : Connect. Already connected!");
			WriteToLog("IPCClientEx : Connect. Done");
		#endif

		return connectResult;
	}

	if ((!pIPCServerEx) && (connectResult != SERR_SUCCESS))
	{
		// Save local server data
		unsigned int tmpLocalServerID = serverID;
		int tmpLocalServerType = serverType;
		unsigned int tmpLocalServerPort = srvPort;
		char tmpLocalServerAddress[ADDRESS_SIZE] = "";
		strcpy(tmpLocalServerAddress, srvAddrStr);
		
		// Erase register data
		PSERVER_DESCRIPTION tmpSelfServerDescr = pSelfServerDescr;
		pSelfServerDescr = NULL;
		unsigned int tmpOwnClientID = clientDescr.ownClientID;
		clientDescr.ownClientID = 0;

		// Try to connect via global address
		connectResult = IPCClient :: Connect(globalServerID, SERVER_TYPE_HOST, gSrvPort, gSrvAddrStr);

		// Recover local server address
		serverID = tmpLocalServerID;
		serverType = tmpLocalServerType;
		srvPort = tmpLocalServerPort;
		strcpy(srvAddrStr, tmpLocalServerAddress);

		// Recover register data
		pSelfServerDescr = tmpSelfServerDescr;
		clientDescr.ownClientID = tmpOwnClientID;

		// Try to connect via TCP HP
		if (connectResult == SERR_SUCCESS)
			connectResult = TCPHPConnect();

		// If not connected beyond NAT - disconnect from global server
		if ((connectResult != SERR_SUCCESS) && (SocketOpened()) && (SessionOpened()))
			Disconnect();
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : Connect. Done");
	#endif

	return connectResult;
}

/****************************************************************

   Class : IPCClientEx

   Method : ConfirmConnect
    
   Returns : Connection confirmation

   Description : Connection confirmation

*****************************************************************/
bool IPCClientEx :: ConfirmConnect(void)
{
	return IPCClient :: ConfirmConnect();
}

/****************************************************************

   Class : IPCClientEx

   Method : Disconnect
    
   Returns : Error code

   Description : Disconnect from server

*****************************************************************/
int IPCClientEx :: Disconnect(void)
{
	return IPCClient :: Disconnect();
}

/****************************************************************

   Class : IPCClientEx

   Method : Connect

   Parameters :
			Input : 
				serverID - server ID
				serverType - server type
				port - server port
				address - server address
				gServerPort - global server port
				gServerAddress - global server address
    
   Returns : error code

   Description : Connect to server

*****************************************************************/
int IPCClientEx :: Connect(unsigned int serverID, int serverType, unsigned int port, char * address, unsigned int gServerID, unsigned int gServerPort, char * gServerAddress)
{
	PrepareRemoteServerData(serverID, serverType);
	PrepareSocketConnection(port, address, gServerPort, gServerAddress);
	this -> globalServerID = gServerID;
	return Connect();
}

/****************************************************************

   Class : IPCClientEx

   Method : ProcessConnectToRequest
  
   Returns : TRUE - if success

   Description : Process connect to request

*****************************************************************/
bool IPCClientEx :: ProcessConnectToRequest(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : ProcessConnectToRequest. Start");
	#endif

	LOCK_SECTION(rBuffCSGuard);

	// Result value
	bool result = false;

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCClientDllDefinition.dllID, logWriter);

	char ipAddress[ADDRESS_SIZE] = "";
	unsigned int port = 0;

	remoteSrvAddrStr[0] = 0;
	remoteSrvPort = 0;

	// Unpack response
	if (serializationManager -> ConnectToReqBufferUnpack(receivedDataBuffer, receivedDataBufferSize, ipAddress, &port) == SERIALIZE_DATA_SUCCESS)
	{
		strcpy(remoteSrvAddrStr, ipAddress);
		remoteSrvPort = port;
		result = true;
	}

	// Delete serialization manager
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : ProcessConnectToRequest. Done");
	#endif

	return result;
}

/****************************************************************

   Class : IPCClientEx

   Method : ProcessConnectToResponse
  
   Returns : TRUE - if success

   Description : Process connect to response

*****************************************************************/
bool IPCClientEx :: ProcessConnectToResponse(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : ProcessConnectToResponse. Start");
	#endif

	LOCK_SECTION(rBuffCSGuard);

	// Result value
	bool result = false;

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCClientDllDefinition.dllID, logWriter);

	char ipAddress[ADDRESS_SIZE] = "";
	unsigned int port = 0;
	
	remoteSrvAddrStr[0] = 0;
	remoteSrvPort = 0;

	// Unpack response
	if (serializationManager -> ConnectToRetBufferUnpack(receivedDataBuffer, receivedDataBufferSize, ipAddress, &port) == SERIALIZE_DATA_SUCCESS)
	{
		strcpy(remoteSrvAddrStr, ipAddress);
		remoteSrvPort = port;
		result = true;
	}

	// Delete serialization manager
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : ProcessConnectToResponse. Done");
	#endif

	return result;
}

/****************************************************************

   Class : IPCClientEx

   Method : TCPHPConnect
  
   Returns : error code

   Description : Try to connect via TCP HP

*****************************************************************/
int IPCClientEx :: TCPHPConnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : TCPHPConnect. Start");
	#endif

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCClientDllDefinition.dllID, logWriter);
			
	// Create CONNECT TO command package
	int packageSize = 0;
	char * package = serializationManager -> ConnectToReqBufferPack(clientDescr.clientID, globalServerID, serverID, serverType, &packageSize);
	
	// Connection result
	int connectResult = SERR_CONNECTION_ERROR;

	if (package)
	{
		// Set sent data buffer
		SetDataBuffer(package, packageSize, SENT_DATA_BUFFER_TYPE);

		// Delete package
		free(package);
		
		SetRecieveDataFlag(false);

		// Send buffer
		SendData();

		// Wait for response
		int counter = 10;
		while ((counter-- > 0) && (!GetRecieveDataFlag())) 
			Sleep(500);

		// Check data receiving result
		if (GetRecieveDataFlag())
		{
			SetRecieveDataFlag(false);
						
			// Process CONNECT TO response
			if (ProcessConnectToResponse())
			{
				// Try connect beyond NAT
				connectResult = TryConnectBeyondNAT();
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			else
			WriteToLog("IPCClientEx : TCPHPConnect. No response from global server!");
		#endif
	}

	// Delete serialization manager
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : TCPHPConnect. Done");
	#endif

	return connectResult;
}

/****************************************************************

   Class : IPCClientEx

   Method : TryConnectBeyondNAT
  
   Returns : error code

   Description : Try to connect beyond NAT

*****************************************************************/
int IPCClientEx :: TryConnectBeyondNAT(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : TryConnectBeyondNAT. Start");
	#endif

	// Connection result
	int connectResult = SERR_CONNECTION_ERROR;

	// Disconnect from global server
	Disconnect();
	
	// Wait closing of socket
	while (SocketOpened());

	// Close threads
	CloseThreads();

	// Try to connect (5 attempts)
	int counter = 5;
	while (counter-- > 0)
	{
		// Create socket
		if ((!SocketOpened()) && (OpenSocket()))
		{
			// Bind to previous IP : port
			int bindResult = BindClientSocket(bindAddrStr, bindPort);
			if ((bindResult == SERR_SUCCESS) || (bindResult == SERR_ALREADY_BINDED))
			{
				// Save server IP : port
				unsigned int tmpLocalServerPort = srvPort;
				char tmpLocalServerAddress[ADDRESS_SIZE] = "";
				strcpy(tmpLocalServerAddress, srvAddrStr);

				// Set ip : port
				srvPort = remoteSrvPort;
				strcpy(srvAddrStr, remoteSrvAddrStr);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					char message[256] = "";
					sprintf(message, "IPCClientEx : TryConnectBeyondNAT. Bind --> %s : %d. Remote --> %s : %d", bindAddrStr, bindPort, remoteSrvAddrStr, remoteSrvPort);
					WriteToLog(message);
				#endif

				// Connecting ...
				int connectionResult = IPCClient :: Connect();

				// Recover server IP : port
				srvPort = tmpLocalServerPort;
				strcpy(srvAddrStr, tmpLocalServerAddress);

				// Check connection result
				if (connectionResult == SERR_SUCCESS)
				{
					connectResult = SERR_SUCCESS;
					break;
				}
				else
					Sleep(200);
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : TryConnectBeyondNAT. Done");
	#endif

	return connectResult;
}

/****************************************************************

   Class : IPCClientEx

   Method : DispatchResponse
   
   Returns : whether to return the result of the query?

   Description :  Dispatch recieved response

*****************************************************************/
bool IPCClientEx :: DispatchResponse(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : DispatchResponse. Start");
	#endif

	// Result flag
	bool sendData = false;

	LOCK_SECTION(rBuffCSGuard);

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCClientDllDefinition.dllID, logWriter);

	// Get command code
	unsigned int command = serializationManager -> GetCommandCode(receivedDataBuffer);
	
	// Check command code
	switch (command)
	{
		// Connect command
		case CMD_CONNECT :
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClientEx : DispatchResponse. Connect command is received");
			#endif

			if (serializationManager -> CheckCommand(receivedDataBuffer, CMD_CONNECT, REQUEST_CMD) == SERIALIZE_DATA_SUCCESS)
			{
				// Process CONNECT TO request
				if (ProcessConnectToRequest())
				{
					SetRecieveDataFlag(false);

					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
						WriteToLog("IPCClientEx : DispatchResponse. Processing of CONNECT TO command request");
					#endif
					
					// Add client processor on the server
					if (pIPCServerEx)
					{
						// Check reconection flag
						bool needReconect = GetReconnectionFlag();

						// Stop reconection
						if (needReconect) StopReconnection();

						// Disconnect from global server
						Disconnect();

						// Close socket
						CloseSocket();

						// Try connect beyond NAT
						pIPCServerEx -> TryConnectBeyondNAT(bindAddrStr, bindPort, remoteSrvAddrStr, remoteSrvPort);

						// Start reconection
						if (needReconect) StartReconnection();
					}
				}
			}
			else
			if (serializationManager -> CheckCommand(receivedDataBuffer, CMD_CONNECT, RESPONSE_CMD) == SERIALIZE_DATA_SUCCESS)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					WriteToLog("IPCClientEx : DispatchResponse. Processing of CONNECT TO command response");
				#endif

				SetRecieveDataFlag(true);
			}
			
			sendData = false;
			break;
		}

		// Disconnect command
		case CMD_DISCONNECT :
		{
			Disconnect();
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClientEx : DispatchResponse. Disconnect command is received");
			#endif

			sendData = false;
			break;
		}
		
		// Other commands
		default:
		{
			SetRecieveDataFlag(true);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("IPCClientEx : DispatchResponse. Server response received");
			#endif

			sendData = false;
			break;
		}
	}

	// Delete serialization manager
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientEx : DispatchResponse. Done");
	#endif

	return sendData;
}