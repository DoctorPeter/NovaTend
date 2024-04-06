/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : IPCProcessor.cpp

   Description :  this module implements methods of
				  class IPCProcessor

*****************************************************************/

#include "stdafx.h"

#include "IPCProcessor.h"
#include "IPCServer.h"
#include <SerializationManager.h>

// z-ipcserver-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCServerDllDefinition;


/****************************************************************

   Class : IPCProcessor

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				commandManager - command manager
				socketServer - pointer to socket server
				clientSocket - client windows socket
				clientAddress - client address structure
				logWriter - pointer to LogWriter instance
				timeoutValue - timeout value

*****************************************************************/
IPCProcessor :: IPCProcessor(unsigned long dllUserID,
							 CommandManager * commandManager,
							 SocketServer * socketServer,
							 SOCKET clientSocket, 
							 sockaddr_in * clientAddress,
							 PTHREAD_BODY_FUNCTION pProcessorBodyFunction, 
							 LogWriter * logWriter,
							 unsigned int timeoutValue) : ClientProcessor(dllUserID, 
																		  socketServer, 
																	      clientSocket, 
																	      clientAddress,
																		  pProcessorBodyFunction,
																	      logWriter, 
																		  timeoutValue)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : constructor");
	#endif

	this -> commandManager = commandManager;
}

/****************************************************************

   Class : IPCProcessor

   Method : Destructor

*****************************************************************/
IPCProcessor :: ~IPCProcessor(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : destructor");
	#endif

	if (commandManager)
		delete commandManager;
}

/****************************************************************

   Class : IPCProcessor

   Method : Connect

	Return : success flag

	Description : Connection confirmation

*****************************************************************/
bool IPCProcessor :: Connect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : Connect. Start");
	#endif

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCServerDllDefinition.dllID, logWriter);

	LOCK_SECTION(clientCSGuard);
		
	// Set client description to zero
	memset(&clientDescr, 0, sizeof(CLIENT_DESCRIPTION));
	
	// Server description
	PSERVER_DESCRIPTION serverDescription = NULL;

	// Generate client ID
	if (socketServer)
	{
		IPCServer * ipcServer = (IPCServer *)socketServer;
		clientDescr.clientID = ipcServer -> GenerateClientID();
		serverDescription = ipcServer -> GetServerDescription();
	}

	// Serialize connect command
	int packSize = 0;
	char * connectPackage = serializationManager -> ConnectBufferPack(clientDescr.clientID, serverDescription, &packSize);

	if ((commandManager) && (serverDescription))
		memcpy(&(commandManager -> serverDescr), serverDescription, sizeof(SERVER_DESCRIPTION));

	if (serverDescription)
		free(serverDescription);
	
	// Response client description pointer
	PCLIENT_DESCRIPTION pClient = NULL;

	if (connectPackage)
	{
		// Set buffer for sent data
		SetDataBuffer(connectPackage, packSize, SENT_DATA_BUFFER_TYPE);

		// Remove package
		free(connectPackage);

		// Send command
		SendData();

		// Wait for receive response
		if (RecieveData() <= 0)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				WriteToLog("IPCProcessor : Connect. Can't recieve response!");
				WriteToLog("IPCProcessor : Connect. Done");
			#endif

			return false;
		}

		// Get client description
		pClient = serializationManager -> ConnectRetBufferUnpack(receivedDataBuffer, receivedDataBufferSize);
	}

	// Delete serialization manager
	delete serializationManager;

	// Remove buffers
	RemoveBuffer(SENT_DATA_BUFFER_TYPE);
	RemoveBuffer(RECEIVED_DATA_BUFFER_TYPE);

	// Validate client description
	if (pClient)
	{
		// Copy client description
		memcpy(&clientDescr, pClient, sizeof(CLIENT_DESCRIPTION));
		
		free(pClient);

		// Retrieve public IP:PORT
		strcpy(clientDescr.publicIP, inet_ntoa(clientAddress.sin_addr));
		clientDescr.publicPort = (unsigned)ntohs(clientAddress.sin_port);
				
		if (commandManager)
			memcpy(&(commandManager -> clientDescr), &clientDescr, sizeof(CLIENT_DESCRIPTION));
		
		/*WriteToLog("IPCProcessor : Connect. Connection confirmed!");
		WriteToLog("IPCProcessor : Connect. Done");
		return true;*/

		if (CheckLicense())
		{
			char message[STR_VALUE_LEN * 2] = "";
			char osVersionStr[STR_VALUE_LEN] = "";
			sprintf(message, "Client connected --> [ID: %d (%d), Name: %s, Type: %d, Version: %X, OS version: %s, Private address: %s:%d, Public address: %s:%d]", clientDescr.clientID, 
																																								   clientDescr.ownClientID,
																																								   clientDescr.clientName,
																																								   clientDescr.clientType,
																																								   clientDescr.version,
																																								   GetOSVersion(clientDescr.osVersion, osVersionStr),
																																								   clientDescr.privateIP, clientDescr.privatePort,
																																								   clientDescr.publicIP, clientDescr.publicPort);
			WriteToLog(message);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				WriteToLog("IPCProcessor : Connect. Connection confirmed!");
				WriteToLog("IPCProcessor : Connect. Done");
			#endif

			return true;
		}
		else
		{
			WriteToLog("Client connection --> No connection confirmation! License violation!");
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				WriteToLog("IPCProcessor : Connect. Done");
			#endif

			return false;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : Connect. No connection confirmation!");
			WriteToLog("IPCProcessor : Connect. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : IPCProcessor

   Method : Disconnect

	Return : success flag

	Description : Disconnect from server

*****************************************************************/
bool IPCProcessor :: Disconnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : Disconnect. Start");
	#endif
	
	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCServerDllDefinition.dllID, logWriter);
		
	LOCK_SECTION(clientCSGuard);

	// Get server ID
	unsigned int serverID = 0;

	if (socketServer)
	{
		IPCServer * ipcServer = (IPCServer *)socketServer;
		serverID = ipcServer -> serverID;
	}
		
	// Serialize disconnect command
	int packSize = 0;
	char * disconnectPackage = serializationManager -> DisconnectBufferPack(REQUEST_CMD, serverID, clientDescr.clientID, &packSize);

	bool disconnectResult = false;

	if (disconnectPackage)
	{
		// Set buffer for sent data
		SetDataBuffer(disconnectPackage, packSize, SENT_DATA_BUFFER_TYPE);

		// Remove package
		free(disconnectPackage);

		// Send command
		SendData();

		disconnectResult = true;
	}

	// Delete serialization manager
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : Disconnect. Done");
	#endif

	return disconnectResult;
}

/****************************************************************

   Class : IPCProcessor

   Method : DispatchRequest
   
   Returns : whether to return the result of the query?

   Description :  Dispatch recieved request

*****************************************************************/
bool IPCProcessor :: DispatchRequest(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : DispatchRequest. Start");
	#endif

	// Send data flag
	bool sendResult = true;

	LOCK_SECTION(clientCSGuard);

	// Check command manager
	if (commandManager)
	{
		LOCK_SECTION(rBuffCSGuard);
		
		// Get code of command
		unsigned int commandCode = commandManager -> GetCommandCode(receivedDataBuffer);
		
		switch (commandCode)
		{
			// Connect to another server
			case CMD_CONNECT :
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
					WriteToLog("IPCProcessor : DispatchRequest. Command CONNECT TO received!");
				#endif

				// CONNECT TO request processing
				unsigned int clientID = 0;
				sendResult = ProcessConnectToRequest(&clientID);

				// Check result
				if (sendResult)
				{
					if (socketServer)
					{
						// Get server pointer
						IPCServer * ipcServer = (IPCServer *)socketServer;

						// Find client processor pointer by ID
						ClientProcessor * processor = ipcServer -> FindClient(clientID);

						if (processor)
						{
							IPCProcessor * ipcProcessor = (IPCProcessor *)processor;

							// Send CONNECT TO request to another client
							ipcProcessor -> ConnectToRequest(clientDescr.publicIP, clientDescr.publicPort);
						}
					}
				}
				else
					sendResult = PrepareEmptyCommand();

				break;
			}

			// Disconnect code
			case CMD_DISCONNECT :
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
					WriteToLog("IPCProcessor : DispatchRequest. Disconnect command received!");
				#endif

				CloseSession();
				sendResult = false;
				break;
			}
			
			// Other commands
			default :
			{
				int packSize = 0;
		
				// Execute command
				char * package = commandManager -> ExecuteCommand(receivedDataBuffer, receivedDataBufferSize, &packSize);

				if (package)
				{
					// Set result buffer
					SetDataBuffer(package, packSize, SENT_DATA_BUFFER_TYPE);

					// Delete package
					free(package);

					sendResult = true;

					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
						WriteToLog("IPCProcessor : DispatchRequest. Command response prepared successfully!");
					#endif
				}
				else
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
						WriteToLog("IPCProcessor : DispatchRequest. Wrong command execution result!");
					#endif

					// Prepare empty command
					sendResult = PrepareEmptyCommand();
				}
			}
		}
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : DispatchRequest. Done");
	#endif

	return sendResult;
}

/****************************************************************

   Class : IPCProcessor

   Method : ProcessConnectToRequest
   
   Parameters:
			Output:
				clientID - client ID

   Returns : whether to return the result of the query?

   Description :  Process "connect to" request

*****************************************************************/
bool IPCProcessor :: ProcessConnectToRequest(unsigned int * clientID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : ProcessConnectToRequest. Start");
	#endif

	// Result flag
	bool sendData = false;

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCServerDllDefinition.dllID, logWriter);

	int serverID = 0;
	int serverType = SERVER_TYPE_UNKNOWN;

	int serialResult = serializationManager -> ConnectToReqBufferUnpack(receivedDataBuffer, receivedDataBufferSize, &serverID, &serverType);
		
	// Check result of deserializarion
	if (serialResult == SERIALIZE_DATA_SUCCESS)
	{
		if (socketServer)
		{
			// Get server pointer
			IPCServer * ipcServer = (IPCServer *)socketServer;

			// Find client description
			PCLIENT_DESCRIPTION pClient = ipcServer -> FindClient(serverID, serverType);

			if (pClient)
			{
				*clientID = pClient -> clientID;

				int packageSize = 0;
				char * package = serializationManager -> ConnectToRetBufferPack(ipcServer -> serverID, clientDescr.clientID, pClient -> publicIP, pClient -> publicPort, &packageSize);

				// Delete serialization manager
				delete serializationManager;

				// Delete client description
				free(pClient);

				if (package)
				{
					// Set result buffer
					SetDataBuffer(package, packageSize, SENT_DATA_BUFFER_TYPE);

					// Delete package
					free(package);

					sendData = true;

					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
						WriteToLog("IPCProcessor : ProcessConnectToRequest. CONNECT TO response prepared successfully!");
					#endif
				}
			}
		}
	}
			
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		if (!sendData)
			WriteToLog("IPCProcessor : ProcessConnectToRequest. CONNECT TO response creation failed!");

		WriteToLog("IPCProcessor : ProcessConnectToRequest. Done");
	#endif

	return sendData;
}

/****************************************************************

   Class : IPCProcessor

   Method : PrepareEmptyCommand
   
   Returns : whether to return the result of the query?

   Description :  Prepare empty command

*****************************************************************/
bool IPCProcessor :: PrepareEmptyCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : PrepareEmptyCommand. Start");
	#endif
		
	bool sendResult = false;

	// Get server ID
	unsigned int serverID = 0;

	if (socketServer)
	{
		IPCServer * ipcServer = (IPCServer *)socketServer;
		serverID = ipcServer -> serverID;
	}	

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zIPCServerDllDefinition.dllID, logWriter);
		
	// Serialize empty command
	int packSize = 0;
	char * package = serializationManager -> EmptyCommandBufferPack(&packSize, serverID, clientDescr.clientID);
	
	// Delete serialization manager
	delete serializationManager;

	if (package)
	{
		// Set result buffer
		SetDataBuffer(package, packSize, SENT_DATA_BUFFER_TYPE);

		// Delete package
		free(package);

		sendResult = true;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : PrepareEmptyCommand. Empty command response prepared successfully!");
		#endif
	}
	else
	{
		sendResult = false;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : PrepareEmptyCommand. No response prepared!");
		#endif
	}
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : PrepareEmptyCommand. Done");
	#endif

	return sendResult;
}

/****************************************************************

   Class : IPCProcessor

   Method : ConnectToRequest
   
   Parameters:
			Input:
				ipAddress - IP
				port - port

   Returns : bytes count

   Description :  Send CONNECT TO request to client

*****************************************************************/
long IPCProcessor :: ConnectToRequest(char * ipAddress, int port)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : ConnectToRequest. Start");
	#endif

	try
	{
		long bytesCount = 0;

		if (socketServer)
		{
			// Get server pointer
			IPCServer * ipcServer = (IPCServer *)socketServer;
	
			// Create serialization manager instance
			SerializationManager * serializationManager = new SerializationManager(zIPCServerDllDefinition.dllID, logWriter);
		
			int packageSize = 0;
			char * package = serializationManager -> ConnectToReqBufferPack(ipcServer -> serverID, clientDescr.clientID, ipAddress, port, &packageSize);

			// Delete serialization manager
			delete serializationManager;

			if (package)
			{
				LOCK_SECTION(clientCSGuard);

				// Set result buffer
				SetDataBuffer(package, packageSize, SENT_DATA_BUFFER_TYPE);

				// Delete buffer
				free(package);

				// Send data
				bytesCount = SendData();
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : ConnectToRequest. Done");
		#endif

		return bytesCount;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : ConnectToRequest. Can not send CONNECT TO data!");
			WriteToLog("IPCProcessor : ConnectToRequest. Done");
		#endif

		return 0;
	}
}

/****************************************************************

   Class : IPCProcessor

   Method : CheckLicense
   
   Returns : result of license checking

   Description :  Check license

*****************************************************************/
bool IPCProcessor :: CheckLicense(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : CheckLicense. Start");
	#endif

	// Check command manager
	if (!commandManager)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : CheckLicense. No command manager!");
			WriteToLog("IPCProcessor : CheckLicense. Done");
		#endif

		return false;
	}

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Check license owner
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	char ownerName[STR_VALUE_LEN] = "USER";
	//strcpy(ownerName, clientDescr.clientName);
	if (!(commandManager -> CheckLicense("LICOWNER", ownerName)))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : CheckLicense. Prohibited user!");
			WriteToLog("IPCProcessor : CheckLicense. Done");
		#endif

		return false;
	}

	// Get current time
	time_t nowSeconds;
	struct tm inpTime;
	time (&nowSeconds);
	inpTime = * localtime(&nowSeconds);

	// Check expiration date
	if(!(commandManager -> CheckLicense("EXPDATE", &inpTime, 0, REL_TYPE_LESS)))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : CheckLicense. License period expired!");
			WriteToLog("IPCProcessor : CheckLicense. Done");
		#endif

		return false;
	}

	// Check NovaTend system version
	int dllVersion = clientDescr.version;
	if(!(commandManager -> CheckLicense("SYSVERSION", &dllVersion)))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : CheckLicense. Prohibited software version!");
			WriteToLog("IPCProcessor : CheckLicense. Done");
		#endif

		return false;
	}

	// Check OS version
	char osVerStr[STR_VALUE_LEN] = "";
	GetOSVersion(clientDescr.osVersion, osVerStr);
	if(!(commandManager -> CheckLicense("OSVERSION", GetOSVersion(osVerStr))))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : CheckLicense. Prohibited OS version!");
			WriteToLog("IPCProcessor : CheckLicense. Done");
		#endif

		return false;
	}
	
	// Check client type
	char clientTypeStr[STR_VALUE_LEN] = "";
	switch (clientDescr.clientType)
	{
		case CLIENT_TYPE_HOST :
		{
			strcpy(clientTypeStr, "HOST");
			break;
		}
		case CLIENT_TYPE_HUB :
		{
			strcpy(clientTypeStr, "HUB");
			break;
		}
		case CLIENT_TYPE_DESKTOP :
		{
			strcpy(clientTypeStr, "DESKTOP");
			break;
		}
		case CLIENT_TYPE_WCP :
		{
			strcpy(clientTypeStr, "WCP");
			break;
		}
		case CLIENT_TYPE_MAN_TOOL :
		{
			strcpy(clientTypeStr, "MANTOOL");
			break;
		}
		case CLIENT_TYPE_POST_LOGIN :
		{
			strcpy(clientTypeStr, "POST_LOGIN");
			break;
		}
		case CLIENT_TYPE_DASH_BOARD :
		{
			strcpy(clientTypeStr, "DASHBOARD");
			break;
		}
		case CLIENT_UPDATER :
		{
			strcpy(clientTypeStr, "UPDATER");
			break;
		}
	}

	if(!(commandManager -> CheckLicense("CLIENTTYPE", clientTypeStr)))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : CheckLicense. Prohibited client type!");
			WriteToLog("IPCProcessor : CheckLicense. Done");
		#endif

		return false;
	}

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Check IP address !!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	char ipAddressStr[IP_ADDRESS_LEN] = "127.0.0.1";
	//strcpy(ipAddressStr, clientDescr.publicIP);
	
	if(!(commandManager -> CheckLicense("IPADDRESS", ipAddressStr)))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCProcessor : CheckLicense. Prohibited IP address!");
			WriteToLog("IPCProcessor : CheckLicense. Done");
		#endif

		return false;
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCProcessor : CheckLicense. Done");
	#endif

	return true;
}
