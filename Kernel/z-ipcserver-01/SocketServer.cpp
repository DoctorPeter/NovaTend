/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : SocketServer.cpp

   Description :  this module implements methods of
				  class SocketServer

*****************************************************************/

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "SocketServer.h"

#include <DllID.h>

// z-ipcserver-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCServerDllDefinition;

/****************************************************************

   Class : SocketServer

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				maxClientsCount - maximum count of clients
				aF - address family specification
				sType - windows socket type
				sProt - windows socket protocol
				wsaVer - windows socket api version
				port - server port
				address - server address

*****************************************************************/
SocketServer :: SocketServer(unsigned long dllUserID, 
							 LogWriter * logWriter,
							 int maxClientsCount,
							 int aF, 
							 int sType, 
							 int sProt, 
							 unsigned int wsaVer, 
							 unsigned int port, 
							 char * address) : SystemBase(dllUserID, &zIPCServerDllDefinition)
{
	// Initialize server critical section
	serverCSGuard = new CriticalSection();

	// Set LOG-writer pointer
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : constructor");
	#endif

	// Initialize falgs
	serverStarted = false;
	stopAccepting = true;

	// Set server options
	PrepareSocketSpecification(wsaVer, aF, sType, sProt);
	PrepareSocketConnection(port, address);
	
	// Initialize server socket
	serverSocket = INVALID_SOCKET;

	// Initialize threads
	acceptThread = NULL;
	checkThread = NULL;
	
	// Set maximum clients count
	if (maxClientsCount > MAX_CLIENTS_COUNT)
		this -> maxClientsCount = MAX_CLIENTS_COUNT - 1;
	else
		this -> maxClientsCount = maxClientsCount;

	// Initialize processors
	clientsCount = 0;
	for(int i = 0; i < this -> maxClientsCount; i++)
		clientProcessors[i] = NULL;
}

/****************************************************************

   Class : SocketServer

   Method : Destructor

*****************************************************************/
SocketServer :: ~SocketServer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : destructor");
	#endif

	Shutdown();
	delete serverCSGuard;
}

/****************************************************************

   Class : SocketServer

   Method : Start
    
   Return : error code
	
	Description :  Starts server

*****************************************************************/
int SocketServer :: Start(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : Start. Start");
	#endif
	
	WriteToLog("Socket server : Starting...");

	if (serverStarted)
	{
		WriteToLog("Socket server : Start --> Server already started!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : Start. Done");
		#endif

		return SERR_ALREADY_STARTED;
	}
	
	// Check WSA version
	if (WSAStartup(wsaVersion, &wsaData))
	{
		WriteToLog("Socket server : Start --> Windows socket API error!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : Start. Done");
		#endif

		return WSAGetLastError();
	}

	// Create socket
	if ((serverSocket = socket(addressFamilySpec, socketType, socketProtocol)) < 0)
	{
		int wsaError = WSAGetLastError();

		WriteToLog("Socket server : Start --> Can't create server socket!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : Start. Done");
		#endif
					
		WSACleanup();
		return wsaError;
	}
	
	// Check legal DLL user
	serverSocket -= dllUserCheckResult;

	// Prepare address
	serverAddress.sin_family = addressFamilySpec;
	serverAddress.sin_port = htons(port);

	if ((address == NULL) || (address[0] == 0))
		serverAddress.sin_addr.s_addr = 0;
	else
		serverAddress.sin_addr.s_addr = inet_addr(address);
	
	serverAddress.sin_addr.s_addr += dllUserCheckResult;

	// Bind address to socket
	if (bind(serverSocket, (sockaddr *) &serverAddress, sizeof(serverAddress)))
	{
		int wsaError = WSAGetLastError();

		char message[256];
		sprintf(message, "Socket server : Start --> Error number: [%d]", wsaError);
		WriteToLog(message);

		WriteToLog("Socket server : Start --> Can't bind server address!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : Start. Done");
		#endif
		
		WSACleanup();
		return wsaError;
	}

	serverStarted = true;
	
	WriteToLog("Socket server : Start --> Server successfully started!");

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : Start. Done");
	#endif

	return SERR_SUCCESS;
}

/****************************************************************

   Class : SocketServer

   Method : Shutdown
    
   Return : error code
	
	Description :  Stops server

*****************************************************************/
int SocketServer :: Shutdown(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : Shutdown. Start");
	#endif

	WriteToLog("Socket server : Shutting down...");

	if (serverStarted)
	{
		// Stop request processing
		StopRequestProcessing();

		serverStarted = false;

		// Close server socket
		closesocket(serverSocket);
		WSACleanup();

		WriteToLog("Socket server : Shutdown --> Server successfully stopped!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : Shutdown. Done");	
		#endif

		return SERR_SUCCESS;
	}
	else
	{
		WriteToLog("Socket server : Shutdown --> Server already stopped!");
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : Shutdown. Done");	
		#endif

		return SERR_ALREADY_STOPPED;
	}
}

/****************************************************************

   Class : SocketServer

   Method : PrepareSocketSpecification
    
   Parameters :
			Input : 
				wsaVer - windows socket api version				
				aF - address family specification
				sType - windows socket type
				sProt - windows socket protocol

   Description :  Set windows socket specification

*****************************************************************/
void SocketServer :: PrepareSocketSpecification(unsigned int wsaVer, int aF, int sType, int sProt)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : PrepareSocketSpecification. Start");
	#endif

	if (!serverStarted)
	{
		wsaVersion = wsaVer;
		addressFamilySpec = aF;
		socketType = sType;
		socketProtocol = sProt;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		else
			WriteToLog("SocketServer : PrepareSocketSpecification. Can't change specification. Socket is working now");

		WriteToLog("SocketServer : PrepareSocketSpecification. Done");
	#endif
}

/****************************************************************

   Class : SocketServer

   Method : PrepareSocketConnection
    
   Parameters :
			Input : 
				port - server port
				address - server address

   Description :  Set windows socket connection data

*****************************************************************/
void SocketServer :: PrepareSocketConnection(unsigned int port, char * address)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : PrepareSocketConnection. Start");
	#endif

	if (!serverStarted)
	{
		this -> port = port;
	
		if (address != NULL)
			strcpy(this -> address, address);
		else
			this -> address[0] = 0;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		else
			WriteToLog("SocketServer : PrepareSocketConnection. Can't change socket connection settings. Socket is working now");

		WriteToLog("SocketServer : PrepareSocketConnection. Done");
	#endif
}

/****************************************************************

   Class : SocketServer

   Method : CreateClientProcessor

   Parameters :
			Input : 
				socket - windows socket descriptor
				address - client address

   Returns: Client processor instance

   Description :  Create client processor

*****************************************************************/
ClientProcessor * SocketServer :: CreateClientProcessor(SOCKET socket, sockaddr_in * address)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : CreateClientProcessor. Start");
	#endif

	// Create client processor instance
	ClientProcessor * clientProcessor = new ClientProcessor(this -> dllUserID, this, socket, address, ClientProcessing, logWriter, DEFAULT_TIMEOUT);
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : CreateClientProcessor. Done");
	#endif

	return clientProcessor;
}

/****************************************************************

   Class : SocketServer

   Method : AddClient
    
   Parameters :
			Input : 
				socket - windows socket descriptor
				address - client address
   
   Returns: Client processor instance

   Description :  Add client to list

*****************************************************************/
ClientProcessor * SocketServer :: AddClient(SOCKET socket, sockaddr_in * address)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : AddClient. Start");
	#endif
	
	// Check server status
	if (!serverStarted) 
	{
		WriteToLog("Socket server : Add client --> Server is stopped. Can't add new client!");    

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : AddClient. Done");
		#endif

		return NULL;
	}

	if (clientsCount >= maxClientsCount)
	{
		WriteToLog("SocketServer : Add client --> Can't add new client! List of clients is overflowed!");    

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : AddClient. Done");
		#endif

		return NULL;
	}

	try
	{
		LOCK_SECTION(serverCSGuard);

		// Create client processor
		int clientIndex = clientsCount;
		clientProcessors[clientIndex] = CreateClientProcessor(socket, address);
		clientsCount++;

		WriteToLog("Socket server : Add client --> New client added!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : AddClient. Done");
		#endif

		return clientProcessors[clientIndex];
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : AddClient. General error! Can't add new client!");    
			WriteToLog("SocketServer : AddClient. Done");
		#endif
		return NULL;
	}
}

/****************************************************************

   Class : SocketServer

   Method : RemoveClient
    
   Parameters :
			Input : 
				clientIndex - client list index
   
   Description :  Remove client from list

*****************************************************************/
void SocketServer :: RemoveClient(int clientIndex)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : RemoveClient. Start");
	#endif

	// Check client index
	if ((serverStarted) && (clientIndex >= 0) && (clientIndex < clientsCount) && (clientProcessors[clientIndex]))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : RemoveClient. Send to client disconnect command");
		#endif

		// Send disconnect command
		bool disconnected = clientProcessors[clientIndex] -> Disconnect();
				
		if (!disconnected)
		{
			WriteToLog("Socket server : Remove client --> Can't disconnect client!");	
			return;
		}

		LOCK_SECTION(serverCSGuard);

		// Remove client processor
		delete clientProcessors[clientIndex];
				
		for (int i = clientIndex; i < clientsCount - 1; i++)
			clientProcessors[i] = clientProcessors[i + 1];

		clientsCount--;

		clientProcessors[clientsCount] = NULL;

		WriteToLog("Socket server : Remove client --> Client removed!");
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		else
			WriteToLog("SocketServer : RemoveClient. Wrong client index!");

		WriteToLog("SocketServer : RemoveClient. Done");
	#endif
}

/****************************************************************

   Class : SocketServer

   Method : ClearClients
    
   Description :  Clear clients list

*****************************************************************/
void SocketServer :: ClearClients(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : ClearClients. Start");
	#endif

	if (serverStarted)
	{
		for (int i = clientsCount - 1; i >= 0; i--)
			RemoveClient(i);
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		else
			WriteToLog("SocketServer : ClearClients. Server stopped. Can't clear clients list");

		WriteToLog("SocketServer : ClearClients. Done");
	#endif
}

/****************************************************************

   Class : SocketServer

   Method : StartRequestProcessing

   Returns : error code
    
   Description :  Start request processing

*****************************************************************/
int SocketServer :: StartRequestProcessing(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : StartRequestProcessing. Start");
	#endif
	
	// Check server status
	if (!serverStarted) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : StartRequestProcessing. Server stopped!");    
			WriteToLog("SocketServer : StartRequestProcessing. Done");    
		#endif

		return SERR_SERVER_STOPED;
	}

	// Check processing status
	if (!stopAccepting)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : StartRequestProcessing. Request processing already started!");    
			WriteToLog("SocketServer : StartRequestProcessing. Done");    
		#endif

		return SERR_ALREADY_STARTED;
	}

	// Start listen
	if (listen(serverSocket, SOMAXCONN))
	{
		Shutdown();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : StartRequestProcessing. Listen error!");    
			WriteToLog("SocketServer : StartRequestProcessing. Done");    
		#endif

		return SERR_LISTER_ERROR;
	}

	stopAccepting = false;

	// Create accepting thread
	acceptThread = new BackgroundThread(ClientAppcepting, this, SERVER_CLIENT_ACCEPT_TIME_OUT, true);

	//Create checking thread
	checkThread = new BackgroundThread(ClientChecking, this, SERVER_CLIENT_CHECKING_TIME_OUT, true);

	if (!(acceptThread -> Runing()) || !(checkThread -> Runing()))
	{
		stopAccepting = true;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : StartRequestProcessing. Accept or check thread creation error!");    
		#endif

		return SERR_THREAD_CREATE;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : StartRequestProcessing. Request processing started"); 
		WriteToLog("SocketServer : StartRequestProcessing. Done"); 
	#endif

	return SERR_SUCCESS;
}

/****************************************************************

   Class : SocketServer

   Method : StopRequestProcessing

   Returns : error code
    
   Description :  Stop request processing

*****************************************************************/
int SocketServer :: StopRequestProcessing(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : StopRequestProcessing. Start"); 
	#endif

	// Check server status
	if (!serverStarted) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : StopRequestProcessing. Server stopped!"); 
			WriteToLog("SocketServer : StopRequestProcessing. Done"); 
		#endif

		return SERR_SERVER_STOPED;
	}

	// Check processing status 
	if (stopAccepting)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : StopRequestProcessing. Request processing already stopped!");    
			WriteToLog("SocketServer : StopRequestProcessing. Done"); 
		#endif

		return SERR_ALREADY_STOPPED;
	}

	stopAccepting = true;
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : StopRequestProcessing. Create fake client!");    
	#endif

	// Create fake client for stop accept thread
	SOCKET fakeClientSocket;	

	if ((fakeClientSocket = socket(addressFamilySpec, socketType, socketProtocol)) < 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : StopRequestProcessing. Fake client creation error!");
			WriteToLog("SocketServer : StopRequestProcessing. Done");
		#endif

		int wsaError = WSAGetLastError();
		return wsaError;
	}

	// Local connection address
	sockaddr_in srvAddress;
	srvAddress.sin_family = addressFamilySpec;
	srvAddress.sin_port = htons(port);
	srvAddress.sin_addr.s_addr = inet_addr(address);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : StopRequestProcessing. Connect fake client!");    
	#endif

	// Fake client connection
	if (connect(fakeClientSocket, (sockaddr *)&srvAddress, sizeof(srvAddress)))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("SocketServer : StopRequestProcessing. Fake client connection error!");
			WriteToLog("SocketServer : StopRequestProcessing. Done");
		#endif

		int wsaError = WSAGetLastError();
		closesocket(fakeClientSocket);
		return wsaError;
	}

	// Close accepting thread
	delete acceptThread;
	acceptThread = NULL;

	// Close checking thread
	delete checkThread;
	checkThread = NULL;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : StopRequestProcessing. Delete fake client!");    
	#endif

	// Close fake client
	closesocket(fakeClientSocket);

	// Clear clients list
	ClearClients();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("SocketServer : StopRequestProcessing. Request processing stopped"); 
		WriteToLog("SocketServer : StopRequestProcessing. Done"); 
	#endif

	return SERR_SUCCESS;
}

/****************************************************************

   Class : SocketServer

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int SocketServer :: WriteToLog(char * message)
{
    if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}

/****************************************************************

   Class : SocketServer

   Method : ClientProcessing

   Parameters :
			Input : 
				clientProcessor - pointer toclient processor instance

   Returns : error code
    
   Description :  Client processing thread

*****************************************************************/
unsigned long __stdcall SocketServer :: ClientProcessing(void * clientProcessor)
{
	ClientProcessor * currentClientProcessor = (ClientProcessor *) clientProcessor;
	
	// Check client processor instance
	if (currentClientProcessor)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			currentClientProcessor -> WriteToLog("SocketServer : ClientProcessing. Start");
		#endif

		if (!currentClientProcessor -> Connect())
		{
			currentClientProcessor -> WriteToLog("Socket server : Client processing --> Connection not confirmed!");

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				currentClientProcessor -> WriteToLog("SocketServer : ClientProcessing. Done");
			#endif

			currentClientProcessor -> CloseSession();

			return SERR_CONNECTION_ERROR;
		}

		do
		{
			// Recieve data from client
			int bytesRecv = currentClientProcessor -> RecieveData();
			
			// Check for end of connection session
			if ((bytesRecv == 0) || (bytesRecv == SOCKET_ERROR))
			{
				currentClientProcessor -> CloseSession();
			}
			else
			{
				// Process recieved data
				if (currentClientProcessor -> DispatchRequest())
					currentClientProcessor -> SendData();
			}

			// Check connection session
		} while(currentClientProcessor -> SessionOppened());

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			currentClientProcessor -> WriteToLog("SocketServer : ClientProcessing. Done");
		#endif

		return SERR_SUCCESS;
	}

	return SERR_BAD_CLIENT;
}

/****************************************************************

   Class : SocketServer

   Method : ClientAppcepting

   Parameters :
			Input : 
				socketServer - pointer to server instance

   Returns : error code
    
   Description :  Client accepting thread

*****************************************************************/
unsigned long __stdcall  SocketServer ::  ClientAppcepting(void * socketServer)
{
	SocketServer * server = (SocketServer *) socketServer;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		server -> WriteToLog("SocketServer : ClientAppcepting. Start"); 
	#endif

	// Check server instance
	if (server)
	{
		do
		{
			// Check size of clients list
			if (server -> clientsCount < server -> maxClientsCount)
			{
				sockaddr_in clientAddress;
				int clientAddrSize = sizeof(clientAddress);
				SOCKET clientSocket;
				
				// Accept new client
				clientSocket = accept(server -> serverSocket, (sockaddr *)&clientAddress, &clientAddrSize);

				// Check accepting result
				if ((!server -> stopAccepting) && (clientSocket != INVALID_SOCKET))
				{
					// Add new client
					if (server -> AddClient(clientSocket, &clientAddress))
					{
						char message[128];
						sprintf(message, "Socket server : Client acceptance --> Clients count: %d ", server -> clientsCount);
						server -> WriteToLog(message);
					}
					else
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
							server -> WriteToLog("SocketServer : ClientAppcepting. Error memorry allocation for new client!");
						#endif
					}
				}
				else
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
						server -> WriteToLog("SocketServer : ClientAppcepting. New client not accepted!");
					#endif
				}
			}
			else
			{
				server -> WriteToLog("Socket server : Client acceptance --> Queue of clients is overflowed!");
			}

		// Check accepting flag
		} while(!server -> stopAccepting);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			server -> WriteToLog("SocketServer : ClientAppcepting. Done"); 
		#endif

		return SERR_SUCCESS;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		else
			server -> WriteToLog("SocketServer : ClientAppcepting. Bad server instance!"); 

		server -> WriteToLog("SocketServer : ClientAppcepting. Done");
	#endif

	return SERR_BAD_SERVER;
}

/****************************************************************

   Class : SocketServer

   Method : ClientChecking

   Parameters :
			Input : 
				socketServer - pointer to server instance

   Returns : error code
    
   Description :  Client checking thread

*****************************************************************/
unsigned long __stdcall  SocketServer :: ClientChecking(void * socketServer)
{
	SocketServer * server = (SocketServer *) socketServer;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		server -> WriteToLog("SocketServer : ClientChecking. Start"); 
	#endif

	// Check server instance
	if (server)
	{
		do
		{
			// check all clients in list
			for (int i = server -> clientsCount - 1; i >= 0; i--)
			{
				if (!(server -> clientProcessors[i] -> SessionOppened()))
				{
					server -> RemoveClient(i);
								
					char message[128];
					sprintf(message, "Socket server : Client checking --> Clients count: %d ", server -> clientsCount);
					server -> WriteToLog(message);
				}
				else
				{
					if (server -> clientProcessors[i] -> GetTimeoutValue() > 0)
					{
						unsigned int time = server -> clientProcessors[i] -> GetTimeoutCounterValue() + 1;

						if (time > server -> clientProcessors[i] -> GetTimeoutValue())
						{
							server -> clientProcessors[i] -> SetTimeoutCounterValue(0);

							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
								char message[128];
								sprintf(message, "Socket server : Client checking --> Timeout period expired for client Num. %d!", i);
								server -> WriteToLog(message);
							#endif
		
							server -> RemoveClient(i);
										
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
								sprintf(message, "Socket server : Client checking --> Clients count: %d ", server -> clientsCount);
								server -> WriteToLog(message);
							#endif

						}
						else
						{
							server -> clientProcessors[i] -> SetTimeoutCounterValue(time);
						}	
					}
				}
			}

			Sleep(1000);

			// Check accepting flag
		} while(!server -> stopAccepting);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			server -> WriteToLog("SocketServer : ClientChecking. Done"); 
		#endif

		return SERR_SUCCESS;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		else
			server -> WriteToLog("SocketServer : ClientChecking. Bad server instance!"); 

		server -> WriteToLog("SocketServer : ClientChecking. Done"); 
	#endif

	return SERR_BAD_SERVER;
}