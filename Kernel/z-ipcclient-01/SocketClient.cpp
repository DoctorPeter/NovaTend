/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : SocketClient.cpp

   Description :  this module implements methods of
				  class SocketClient

*****************************************************************/

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#include "SocketClient.h"

// z-ipcclient-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCClientDllDefinition;

#pragma region Constructing

/****************************************************************

   Class : SocketServer

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				aF - address family specification
				sType - windows socket type
				sProt - windows socket protocol
				wsaVer - windows socket api version
				port - server port
				address - server address
				timeoutValue - timeout value

*****************************************************************/
SocketClient :: SocketClient(unsigned long dllUserID, 
							 LogWriter * logWriter, 
							 int aF, 
							 int sType, 
							 int sProt, 
							 unsigned int wsaVer, 
							 unsigned int port, 
							 char * address,
							 unsigned int timeoutValue) : SystemBase(dllUserID, &zIPCClientDllDefinition)
{
	clientCSGuard	= new CriticalSection();
	sendCSGuard		= new CriticalSection();
	recvCSGuard		= new CriticalSection();
	rBuffCSGuard	= new CriticalSection();
	sBuffCSGuard	= new CriticalSection();
	sessCSGuard		= new CriticalSection();
	sockCSGuard		= new CriticalSection();
	reconCSGuard	= new CriticalSection();
	timeCSGuard		= new CriticalSection();

	this -> logWriter = logWriter;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : constructor");
	#endif
	
	sessionOpened = false;
	dataRecieved = false;
	mustReconnect = false;
	socketOpened = false;
	socketBinded = false;

	PrepareSocketSpecification(wsaVer, aF, sType, sProt);
	PrepareSocketConnection(port, address);
	
	receivedDataBufferSize = 0;
	receivedDataBuffer = NULL;

	sentDataBufferSize = 0;
	sentDataBuffer = NULL;

	receiverThread = NULL;
	reconnectThread = NULL;
	timeoutThread = NULL;

	SetTimeoutValue(timeoutValue);
	SetTimeoutCounterValue(0);

	clientSocket = INVALID_SOCKET;

	// WSA startup
	WSAStartup(wsaVersion, &wsaData);
}

/****************************************************************

   Class : SocketClient

   Method : Destructor

*****************************************************************/
SocketClient :: ~SocketClient(void)
{
	// Stop reconnection thread
	StopReconnection();

	// Disconnect from server
	if (Connected())
		Disconnect();

	// Wait for thread finishing
	if ((receiverThread) && (receiverThread -> Stop(3000) == false))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : destructor. Correct threads finish");
		#endif

		// Close threads
		CloseThreads();

		// Close socket
		CloseSocket();
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : destructor. Emergency threads finish");
		#endif
			
		// Close socket
		CloseSocket();

		// Close threads
		CloseThreads();	
	}
		
	// Remove buffer
	RemoveBuffer(RECEIVED_DATA_BUFFER_TYPE);

	// Remove buffer
	RemoveBuffer(SENT_DATA_BUFFER_TYPE);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : destructor");
	#endif

	delete rBuffCSGuard;
	delete sBuffCSGuard;
	delete recvCSGuard;
	delete sendCSGuard;
	delete sessCSGuard;
	delete sockCSGuard;
	delete reconCSGuard;
	delete timeCSGuard;
	delete clientCSGuard;

	WSACleanup();
}

#pragma endregion

#pragma region Session control

/****************************************************************

   Class : SocketClient

   Method : SetSessionStatus
    
   Parameters :
			Input : 
				status - session status

   Description :  Set session status

*****************************************************************/
bool SocketClient :: SetSessionStatus(bool status)
{
	LOCK_SECTION(sessCSGuard);
	sessionOpened = status;
	return status;
}

/****************************************************************

   Class : SocketClient

   Method : GetSessionStatus
    
   Returs: session status

   Description :  Get session status

*****************************************************************/
bool SocketClient :: GetSessionStatus(void)
{
	LOCK_SECTION(sessCSGuard);
	return sessionOpened;
}

/****************************************************************

   Class : SocketClient

   Method : OpenSession
    
   Returs: session status

   Description :  Open session

*****************************************************************/
bool SocketClient :: OpenSession(void)
{
	return SetSessionStatus(true);
}

/****************************************************************

   Class : SocketClient

   Method : CloseSession
    
   Returs: session status

   Description :  Close session

*****************************************************************/
bool SocketClient :: CloseSession(void)
{
	return SetSessionStatus(false);
}
		
/****************************************************************

   Class : SocketClient

   Method : SessionOpened
    
   Returs: session status

   Description :  Check session status

*****************************************************************/
bool SocketClient :: SessionOpened(void)
{
	return Connected();
}

#pragma endregion

#pragma region Socket control

/****************************************************************

   Class : SocketClient

   Method : SetSocketStatus
    
   Parameters :
			Input : 
				status - socket status

   Description :  Set socket status

*****************************************************************/
bool SocketClient :: SetSocketStatus(bool status)
{
	LOCK_SECTION(sockCSGuard);
	socketOpened = status;
	return status;
}

/****************************************************************

   Class : SocketClient

   Method : GetSocketStatus
    
   Returs: socket status

   Description :  Get socket status

*****************************************************************/
bool SocketClient :: GetSocketStatus(void)
{
	LOCK_SECTION(sockCSGuard);
	return socketOpened;
}

/****************************************************************

   Class : SocketClient

   Method : OpenSocket
    
   Returs: socket status

   Description :  Open socket

*****************************************************************/
bool SocketClient :: OpenSocket(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : OpenSocket. Start");
	#endif

	LOCK_SECTION(clientCSGuard);

	// Create client socket
	if ((clientSocket = socket(addressFamilySpec, socketType, socketProtocol)) < 0)
	{
		WriteToLog("Socket client : Open socket --> Can't create client socket!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : Connect. Done");
		#endif

		return false;
	}
	else
	{
		const char yes = 1;

		// Set SO_REUSEADDRR option
		if (setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)))
		{
			closesocket(clientSocket);

			WriteToLog("Socket client : Open socket --> Can't set SO_REUSEADDR option for socket!");

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("SocketClient : OpenSocket. Done");
			#endif

			return false;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("SocketClient : OpenSocket. Socket successfully created!");
				WriteToLog("SocketClient : OpenSocket. Done");
			#endif

			// Set socket status
			return SetSocketStatus(true);
		}
	}
}

/****************************************************************

   Class : SocketClient

   Method : CloseSocket
   
   Description :  Close client socket

*****************************************************************/
bool SocketClient :: CloseSocket(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : CloseSocket. Start");
	#endif
	
	LOCK_SECTION(clientCSGuard);
	
	if (SocketOpened())
	{
		closesocket(clientSocket);
		socketBinded = false;
		clientSocket = INVALID_SOCKET;
		SetSocketStatus(false);
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : CloseSocket. Done");
	#endif

	return SocketOpened();
}
		
/****************************************************************

   Class : SocketClient

   Method : SocketOpened
    
   Returs: socket status

   Description :  Check socket status

*****************************************************************/
bool SocketClient :: SocketOpened(void)
{
	return GetSocketStatus();
}

/****************************************************************

   Class : SocketClient

   Method : PrepareSocketSpecification
    
   Parameters :
			Input : 
				wsaVer - windows socket api version				
				aF - address family specification
				sType - windows socket type
				sProt - windows socket protocol

   Description :  Set windows socket specification

*****************************************************************/
void SocketClient :: PrepareSocketSpecification(unsigned int wsaVer, int aF, int sType, int sProt)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : PrepareSocketSpecification. Start");
	#endif

	if (!Connected())
	{
		wsaVersion = wsaVer;
		addressFamilySpec = aF;
		socketType = sType;
		socketProtocol = sProt;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		else
			WriteToLog("SocketClient : PrepareSocketSpecification. Can't change specification. Socket is working now");

		WriteToLog("SocketClient : PrepareSocketSpecification. Done");
	#endif
}

/****************************************************************

   Class : SocketClient

   Method : PrepareSocketConnection
    
   Parameters :
			Input : 
				port - server port
				address - server address

   Description :  Set windows socket connection data

*****************************************************************/
void SocketClient :: PrepareSocketConnection(unsigned int port, char * address)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : PrepareSocketConnection. Start");
	#endif

	if (!Connected())
	{
		srvPort = port;
	
		if (address != NULL)
			strcpy(srvAddrStr, address);
		else
			strcpy(srvAddrStr, "127.0.0.1");
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		else
			WriteToLog("SocketClient : PrepareSocketConnection. Can't change socket connection settings. Socket is working now");

		WriteToLog("SocketClient : PrepareSocketConnection. Done");
	#endif
}

/****************************************************************

   Class : SocketClient

   Method : GetSocketSpecification
    
   Parameters :
			Output : 
				wsaVer - windows socket api version				
				aF - address family specification
				sType - windows socket type
				sProt - windows socket protocol

   Description :  Get windows socket specification

*****************************************************************/
void SocketClient :: GetSocketSpecification(unsigned int * wsaVer, int * aF, int * sType, int * sProt)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : GetSocketSpecification. Start");
	#endif

	if (wsaVer) *wsaVer = wsaVersion;
	if (aF)     *aF = addressFamilySpec;
	if (sType)  *sType = socketType;
	if (sProt)  *sProt = socketProtocol;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : GetSocketSpecification. Done");
	#endif
}

/****************************************************************

   Class : SocketClient

   Method : GetSocketConnection
    
   Parameters :
			Output : 
				port - server port
				address - server address

   Description :  Get windows socket connection data

*****************************************************************/
void SocketClient :: GetSocketConnection(unsigned int * port, char * address)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : GetSocketConnection. Start");
	#endif

	if (port) *port = srvPort;

	if (address) strcpy(address, srvAddrStr);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : GetSocketConnection. Done");
	#endif
}

#pragma endregion

#pragma region Timer control

/****************************************************************

   Class : SocketClient

   Method : SetTimeoutCounterValue
    
   Parameters :
			Input : 
				time - counter value

   Description :  Set timeout cuonter value

*****************************************************************/
void SocketClient :: SetTimeoutCounterValue(unsigned int time)
{
	LOCK_SECTION(timeCSGuard);
	timeoutCounterValue = time;
}

/****************************************************************

   Class : SocketClient

   Method : GetTimeoutCounterValue
    
   Description :  Get timeout counter value

*****************************************************************/
unsigned int SocketClient :: GetTimeoutCounterValue(void)
{
	LOCK_SECTION(timeCSGuard);
	return timeoutCounterValue;
}

/****************************************************************

   Class : SocketClient

   Method : SetTimeoutValue
    
   Parameters :
			Input : 
				time - counter value

   Description :  Set timeout value

*****************************************************************/
void SocketClient :: SetTimeoutValue(unsigned int time)
{
	LOCK_SECTION(timeCSGuard);
	timeoutValue = time;
}

/****************************************************************

   Class : SocketClient

   Method : GetTimeoutValue
    
   Description :  Get timeout value

*****************************************************************/
unsigned int SocketClient :: GetTimeoutValue(void)
{
	LOCK_SECTION(timeCSGuard);
	return timeoutValue;
}

#pragma endregion

#pragma region Connection

/****************************************************************

   Class : SocketClient

   Method : Connect
    
   Returns : error code

   Description : Connect to server

*****************************************************************/
int SocketClient :: Connect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : Connect. Start");
		WriteToLog("Socket client : Connecting...");
	#endif
		
	// Check session status
	if (SessionOpened())
	{
		WriteToLog("Socket client : Connect --> Already connected!");
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : Connect. Done");
		#endif

		return SERR_ALREADY_CONNECTED;
	}

	// Create socket
	if ((!SocketOpened()) && (!OpenSocket()))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : Connect. Can not create socket!");
			WriteToLog("SocketClient : Connect. Done");
		#endif

		return SERR_CONNECTION_ERROR;
	}

	// Bind client socket
	int bindResult = BindClientSocket();
	if ((bindResult != SERR_SUCCESS) && (bindResult != SERR_ALREADY_BINDED))
	{
		CloseSocket();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : Connect. Can not bind socket!");
			WriteToLog("SocketClient : Connect. Done");
		#endif

		return SERR_BIND_ERROR;
	}

	// Try connect socket
	if (ConnectSocket() != SERR_SUCCESS)
	{
		CloseSocket();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : Connect. Can not connect to server!");
			WriteToLog("SocketClient : Connect. Done");
		#endif

		return SERR_CONNECTION_ERROR;
	}
		
	// Set session status
	OpenSession();

	// Confirm connection
	if (ConfirmConnect())
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			// peer address structure
			sockaddr_in peerAddress;
			int peerAddressLen = sizeof(peerAddress);

			// Get peer information
			if (!getpeername(clientSocket, (struct sockaddr *)&peerAddress, &peerAddressLen))
			{
				char message[128];
				sprintf(message, "Socket client : Connect --> Connected to [%s : %d]",  inet_ntoa(peerAddress.sin_addr), (unsigned)ntohs(peerAddress.sin_port));
				WriteToLog(message);
			}
			else
			{
				char message[128];
				sprintf(message, "Socket client : Connect --> Can't get peer connection information. Error [%d]", WSAGetLastError());
				WriteToLog(message);
			}
		#endif

		// Create client threads
		if (CreateThreads() != SERR_SUCCESS)
		{
			WriteToLog("SocketClient : Connect --> Threads error! Breake connection!");

			CloseSession();
			CloseSocket();

			return SERR_THREAD_CREATE;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : Connect. Done");
		#endif

		return SERR_SUCCESS;
	}
	else
	{
		CloseSession();
		CloseSocket();
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("Socket client : Connect --> Connection not confirmed!");
			WriteToLog("SocketClient : Connect. Done");
		#endif

		return SERR_CONNECTION_ERROR;
	}
}

/****************************************************************

   Class : SocketClient

   Method : Connect

   Parameters :
			Input : 
				port - server port
				address - server address
    
   Returns : error code

   Description : Connect to server

*****************************************************************/
int SocketClient :: Connect(unsigned int port, char * address)
{
	PrepareSocketConnection(port, address);
	return SocketClient :: Connect();
}

/****************************************************************

   Class : SocketClient

   Method : Connected

   Returns : connction status

   Description : Check connection

*****************************************************************/
bool SocketClient :: Connected(void)
{
	return GetSessionStatus();
}

/****************************************************************

   Class : SocketClient

   Method : ConfirmConnect
    
   Returns : Connection confirmation

   Description : Connection confirmation

*****************************************************************/
bool SocketClient :: ConfirmConnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : ConfirmConnect. Start");
	#endif

	CloseThreads();

	LOCK_SECTION(clientCSGuard);
	
	bool confirm = true;


	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : ConfirmConnect. Done");
	#endif

	return confirm;
}

/****************************************************************

   Class : SocketClient

   Method : Disconnect
    
   Returns : Error code

   Description : Disconnect from server

*****************************************************************/
int SocketClient :: Disconnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : Disconnect. Start");
	#endif

	LOCK_SECTION(clientCSGuard);
	
	CloseSession();
		
	int disconnectResult = SERR_SUCCESS;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : Disconnect. Done");
	#endif

	return disconnectResult;
}

/****************************************************************

   Class : SocketClient

   Method : BindClientSocket
    
   Returns: error code

   Description : Bind client socket

*****************************************************************/
int SocketClient :: BindClientSocket(void)
{
	// Generate random port number and get current host IP
	char currentIP[ADDRESS_SIZE] = "";
	return BindClientSocket(GetCurrentIP(currentIP), (Rand() + 1024) % 64000);
}

/****************************************************************

   Class : SocketClient

   Method : BindClientSocket
    
   Parameters:
			Input:
				ipAddress - IP
				port - port number

   Returns: error code

   Description : Bind client socket

*****************************************************************/
int SocketClient :: BindClientSocket(char * ipAddress, unsigned int port)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : BindClientSocket. Start");

		if (socketBinded)
			WriteToLog("SocketClient : BindClientSocket. Socket already binded!");
		else
			WriteToLog("SocketClient : BindClientSocket. Socket not binded yet!");
	#endif

	int bindResult = SERR_SUCCESS;

	// Check bindidng flag
	if (!socketBinded)
	{
		bindAddress.sin_family = AF_INET; 

		bindPort = port;
		bindAddress.sin_port = htons(bindPort);

		if (!PrepareIPAddress(ipAddress, &bindAddress))
		{
			int wsaError = WSAGetLastError();
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("Socket client : BindClientSocket. Wrong server address!");
				WriteToLog("SocketClient : BindClientSocket. Done");
			#endif

			return wsaError;
		}
		
		// Bind socket
		if(bind(clientSocket, (sockaddr*)&bindAddress, sizeof(bindAddress)))
		{
			bindResult = WSAGetLastError();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("SocketClient : BindClientSocket. Error of socket binding!!!");
			#endif
		}
		else
		{
			strcpy(bindAddrStr, inet_ntoa(bindAddress.sin_addr));
			socketBinded = true;
		}
	}
	else
		bindResult = SERR_ALREADY_BINDED;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		if ((bindResult == SERR_SUCCESS) || (bindResult == SERR_ALREADY_BINDED))
		{
			char message[128];
			sprintf(message, "Socket client : BindClientSocket. Binded to [%s : %d]",  bindAddrStr, bindPort);
			WriteToLog(message);
		
		}
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : BindClientSocket. Done");
	#endif

	return bindResult;
}

/****************************************************************

   Class : SocketClient

   Method : ConnectSocket
    
   Returns: error code

   Description : Connect socket

*****************************************************************/
int SocketClient :: ConnectSocket(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : ConnectSocket. Start");
	#endif

	serverAddress.sin_family = addressFamilySpec;
	serverAddress.sin_port = htons(srvPort);

	if (!PrepareIPAddress(srvAddrStr, &serverAddress))
	{
		int wsaError = WSAGetLastError();
		CloseSocket();

		WriteToLog("Socket client : ConnectSocket --> Wrong server address!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : ConnectSocket. Done");
		#endif

		return wsaError;
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		char mes[128];
		sprintf(mes, "SocketClient : ConnectSocket. Trying connect to server --> %s : %d ", srvAddrStr, srvPort);
		WriteToLog(mes);
	#endif


	// Connect to server
	if (connect(clientSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)))
	{
		int wsaError = WSAGetLastError();
		CloseSocket();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			char message[128];
			sprintf(message, "Socket client : ConnectSocket --> Connection error [%d]", wsaError);
			WriteToLog(message);

			WriteToLog("SocketClient : ConnectSocket. Done");
		#endif

		return wsaError;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : ConnectSocket. Done");
	#endif

	return SERR_SUCCESS;
}

/****************************************************************

   Class : SocketClient

   Method : PrepareIPAddress

   Parameters:
			Input:
				ipAddress - IP
			Output:
				addressStruct - struct sockaddr_in
    
   Returns: TRUE - if success

   Description : Prepare address

*****************************************************************/
bool SocketClient :: PrepareIPAddress(char * ipAddress, sockaddr_in * addressStruct)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : PrepareIPAddress. Start");
	#endif

	// Check sockaddr_in structure
	if (!addressStruct)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : PrepareIPAddress. Wrong input parameters.");
			WriteToLog("SocketClient : PrepareIPAddress. Done");
		#endif

		return false;
	}

	// Check IP string
	if (!ipAddress)
	{
		addressStruct -> sin_addr.s_addr = INADDR_ANY;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : PrepareIPAddress. Any address established.");
			WriteToLog("SocketClient : PrepareIPAddress. Done");
		#endif

		return true;
	}

	HOSTENT *hst;

	// Set server address
	if (inet_addr(ipAddress) != INADDR_NONE)
	{
		addressStruct -> sin_addr.s_addr = inet_addr(ipAddress);
	}
	else
	{
		// Get host by name (if address string is not IP)
		if (hst = gethostbyname(ipAddress))
		{
			((unsigned long *)&addressStruct -> sin_addr)[0] = ((unsigned long **)hst -> h_addr_list)[0][0];
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("Socket client : PrepareIPAddress. Wrong address string!");
				WriteToLog("SocketClient : PrepareIPAddress. Done");
			#endif

			return false;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : PrepareIPAddress. Done");
	#endif

	return true;
}

/****************************************************************

   Class : SocketClient

   Method : GetCurrentIP

   Parameters:
			Output:
				ipAddress - current IP
   
   Returns: current IP

   Description : Get current IP

*****************************************************************/
char * SocketClient :: GetCurrentIP(char * ipAddress)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("Socket client : GetCurrentIP. Start");
	#endif

	try
	{
		HOSTENT *hst;

		// Get current host name
		char hostName[ADDRESS_SIZE] = "";
		if (gethostname(hostName, sizeof(hostName)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("Socket client : GetCurrentIP. Can't get host name!");
				WriteToLog("SocketClient : GetCurrentIP. Done");
			#endif

			return NULL;
		}
		else
		{
			// Get host address by name
			if (hst = gethostbyname(hostName))
			{
				for (int i = 0; hst->h_addr_list[i] != NULL; i++)
				{
					struct sockaddr_in adrrStruct;
					memcpy(&adrrStruct.sin_addr, hst -> h_addr_list[i], hst -> h_length);
					strcpy(ipAddress, inet_ntoa(adrrStruct.sin_addr));
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					char message[128];
					sprintf(message, "Socket client : GetCurrentIP. Current IP --> %s", ipAddress);
					WriteToLog(message);

					WriteToLog("Socket client : GetCurrentIP. Done");
				#endif

				return ipAddress;
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					WriteToLog("Socket client : GetCurrentIP. Can't get IP address string!");
					WriteToLog("SocketClient : GetCurrentIP. Done");
				#endif

				return NULL;
			}
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("Socket client : GetCurrentIP. IP address string retrieving error!");
			WriteToLog("SocketClient : GetCurrentIP. Done");
		#endif

		return NULL;
	}
}

#pragma endregion

#pragma region Reconnection

/****************************************************************

   Class : SocketClient

   Method : StartReconnection

   Returns: boolean result flag

   Description : Start reconnection thread

*****************************************************************/
bool SocketClient :: StartReconnection(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : StartReconnection. Start");
	#endif

	if (GetReconnectionFlag())
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : StartReconnection. Reconnection thread already started!");
			WriteToLog("SocketClient : StartReconnection. Done");
		#endif

		return false;
	}

	SetReconnectionFlag(true);

	// Create thread
	reconnectThread = new BackgroundThread(Reconnection, this, CLIENT_RECONN_TIME_OUT);
	
	// Run thread	
	if (!(reconnectThread -> Run()))
	{
		delete reconnectThread;
		reconnectThread = NULL;

		SetReconnectionFlag(false);	

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : StartReconnection. Can't create reconnector thread!");
			WriteToLog("SocketClient : StartReconnection. Done");
		#endif

		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : StartReconnection. Done");
	#endif

	return true;
}

/****************************************************************

   Class : SocketClient

   Method : StopReconnection

   Returns: boolean result flag

   Description : Stop reconnection thread

*****************************************************************/
bool SocketClient :: StopReconnection(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : StopReconnection. Start");
	#endif

	if (GetReconnectionFlag())
	{
		SetReconnectionFlag(false);	

		delete reconnectThread;
		reconnectThread = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : StopReconnection. Reconnection thread is deleted!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : StopReconnection. Done");
	#endif

	return true;
}

/****************************************************************

   Class : SocketClient

   Method : SetReconnectionFlag

   Parameters :
			Input : 
				flag - reconnector flag value

	Description : Set reconnection flag

*****************************************************************/
void SocketClient :: SetReconnectionFlag(bool flag)
{
	LOCK_SECTION(reconCSGuard);
	mustReconnect = flag;
}

/****************************************************************

   Class : SocketClient

   Method : GetReconnectionFlag

   Returns: reconnector flag value

   Description : Get reconnection flag

*****************************************************************/
bool SocketClient :: GetReconnectionFlag(void)
{
	LOCK_SECTION(reconCSGuard);
	return mustReconnect;
}

#pragma endregion

#pragma region Data processing

/****************************************************************

   Class : SocketClient

   Method : Recieve
   
    Parameters :
			Input : 
				recvBuff - data buffer
				size - buffer size
  

   Returns : data size

   Description :  Recieve data

*****************************************************************/
int SocketClient :: Recieve(char * recvBuff, long size)
{
	char * pBuff = recvBuff;
	int count = size;
	int recvBytes = 0;
		
	while (count > 0)
	{
		recvBytes = recv(clientSocket, pBuff, count, 0);

		if (recvBytes == 0)
			return 0;

		if (recvBytes == SOCKET_ERROR)
			return SOCKET_ERROR;

		pBuff += recvBytes;
		count -= recvBytes;
	}

	SetTimeoutCounterValue(0);
	
	return size;
}

/****************************************************************

   Class : SocketClient

   Method : Send
   
    Parameters :
			Input : 
				sendBuff - data buffer
				size - buffer size
  

   Returns : data size

   Description :  Send data

*****************************************************************/
int SocketClient :: Send(char * sendBuff, long size)
{
	char * pBuff = sendBuff;
	int count = size;
	int sentBytes = 0;

	while (count > 0)
	{
		sentBytes = send(clientSocket, pBuff, count, 0);
		
		if (sentBytes == SOCKET_ERROR)
			return SOCKET_ERROR;

		pBuff += sentBytes;
		count -= sentBytes;
	}

	SetTimeoutCounterValue(0);

	return size;
}


/****************************************************************

   Class : SocketClient

   Method : RecieveMessage
   
   Returns : message size

   Description :  Recieve message

*****************************************************************/
long  SocketClient :: RecieveData(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : RecieveData. Start");
	#endif

	// Check server connection
	if (!Connected())
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : RecieveData. No server connection!");
			WriteToLog("SocketClient : RecieveData. Done");
		#endif

		return -1;
	}
	
	LOCK_SECTION(recvCSGuard);

	// Recieve message size
	long messageSize = 0;
	int recvBytes = Recieve((char *)&messageSize, sizeof(messageSize));
		
	// Validate message size
	if ((recvBytes == 0) || (recvBytes == SOCKET_ERROR))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : RecieveData. Failed to recieve message size!");
			WriteToLog("SocketClient : RecieveData. Done");
		#endif

		return 0;
	}
	
	// Validate message size
	if (messageSize == 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : RecieveData. Zero message size!");
			WriteToLog("SocketClient : RecieveData. Done");
		#endif

		return 0;
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		char message[128];
		sprintf(message, "SocketClient : RecieveData. Message size : %d", messageSize);
		WriteToLog(message);
	#endif

	// Prepare buffer
	if (PrepareBuffer(messageSize, RECEIVED_DATA_BUFFER_TYPE) == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : RecieveData. Memory allocation error!");
			WriteToLog("SocketClient : RecieveData. Done");
		#endif

		return SOCKET_ERROR;
	}

	recvBytes = Recieve(receivedDataBuffer, messageSize);
	
	// Validate recv result
	if ((recvBytes == 0) || (recvBytes == SOCKET_ERROR))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			char message[128];
			sprintf(message, "ClientProcessor : RecieveData. Recv return: %d Error [%d]", recvBytes, WSAGetLastError());
			WriteToLog(message);
		
			WriteToLog("SocketClient : RecieveData. Failed to recieve message!");
			WriteToLog("SocketClient : RecieveData. Done");
		#endif

		return 0;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		sprintf(message, "SocketClient : RecieveData. Total recieved : %d", messageSize + sizeof(messageSize));
		WriteToLog(message);

		WriteToLog("SocketClient : RecieveData. Message recieved successfully!");
		WriteToLog("SocketClient : RecieveData. Done");
	#endif

	return messageSize + sizeof(messageSize);
}


/****************************************************************

   Class : SocketClient

   Method : SendMessage
   
   Returns : message size

   Description :  Send message

*****************************************************************/
long  SocketClient :: SendData(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : SendData. Start");
	#endif

	// Check buffer
	if (!sentDataBuffer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : SendData. Bad data buffer!");
			WriteToLog("SocketClient : SendData. Done");
		#endif

		return 0;
	}
	
	LOCK_SECTION(sendCSGuard);

	int bufferSize = GetDataBufferSize(SENT_DATA_BUFFER_TYPE);

	// Send buffer size
	int sentBytes = Send((char *)&bufferSize, sizeof(bufferSize));
	
	if (sentBytes == SOCKET_ERROR)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : SendData. Can't sent message size!");
			WriteToLog("SocketClient : SendData. Done");
		#endif

		return SOCKET_ERROR;
	}

	// Send buffer
	sentBytes = Send(sentDataBuffer, bufferSize);

	if (sentBytes == SOCKET_ERROR)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : SendData. Can't sent message buffer!");
			WriteToLog("SocketClient : SendData. Done");
		#endif

		return SOCKET_ERROR;
	}

	int totalSent = sentBytes + sizeof(bufferSize);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		char message[128];
		sprintf(message, "SocketClient : SendData. BuffSize : %d. Total sent : %d", bufferSize, totalSent);
		WriteToLog(message);

		WriteToLog("SocketClient : SendData. Message sent successfully!");
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : SendData. Done");
	#endif

	return totalSent;
}

/****************************************************************

   Class : SocketClient

   Method : DispatchResponse
   
   Returns : whether to return the result of the query?

   Description :  Dispatch recieved response

*****************************************************************/
bool SocketClient :: DispatchResponse(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : DispatchResponse. Start");
	#endif

	bool sendResult = false;
	SetRecieveDataFlag(true);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : DispatchResponse. Done");
	#endif
		
	return sendResult;
}

/****************************************************************

   Class : SocketClient

   Method : SetRecieveDataFlag

   Parameters :
			Input : 
				flag - recieve data flag value

	Description : Set recieve data flag

*****************************************************************/
void SocketClient :: SetRecieveDataFlag(bool flag)
{
	LOCK_SECTION(clientCSGuard);
	dataRecieved = flag;
}

/****************************************************************

   Class : SocketClient

   Method : GetRecieveDataFlag

   Returns: recieve data flag value

   Description : Get recieve data flag

*****************************************************************/
bool SocketClient :: GetRecieveDataFlag(void)
{
	LOCK_SECTION(clientCSGuard);
	return dataRecieved;
}

#pragma endregion

#pragma region Data buffer

/****************************************************************

   Class : SocketClient

   Method : PrepareBuffer
    
   Parameters :
			Input : 
				buffSize - buffer size
				buffType - type of buffer

   Return : pointer to data buffer
	
   Description :  Allocate memory for internal buffer

*****************************************************************/
char *  SocketClient :: PrepareBuffer(long buffSize, int buffType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : PrepareBuffer. Start");
	#endif

	// Remove previous buffer
	RemoveBuffer(buffType);
	
	// Check buffer type
	switch (buffType)
	{
		// Receive buffer
		case RECEIVED_DATA_BUFFER_TYPE:
		{
			LOCK_SECTION(rBuffCSGuard);

			if (buffSize <= 0)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					WriteToLog("SocketClient : PrepareBuffer. Wrong received messages buffer size value!");
				#endif
			}
			else
			{
				receivedDataBufferSize = buffSize;
				receivedDataBuffer = (char *)malloc(receivedDataBufferSize);
			}
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("SocketClient : PrepareBuffer. Done");
			#endif

			return receivedDataBuffer;
		}

		// Send buffer
		case SENT_DATA_BUFFER_TYPE:
		{
			LOCK_SECTION(sBuffCSGuard);

			if (buffSize <= 0)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					WriteToLog("SocketClient : PrepareBuffer. Wrong sent messages buffer size value!");
				#endif
			}
			else
			{
				sentDataBufferSize = buffSize;
				sentDataBuffer = (char *)malloc(sentDataBufferSize);
			}
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("SocketClient : PrepareBuffer. Done");
			#endif

			return sentDataBuffer;
		}

		default: 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				WriteToLog("SocketClient : PrepareBuffer. Wrong buffer type!");
				WriteToLog("SocketClient : PrepareBuffer. Done");
			#endif

			return NULL;
		}
	}
}

/****************************************************************

   Class : SocketClient

   Method : RemoveBuffer

   Parameters :
			Input : 
				buffSize - buffer size
				buffType - type of buffer
    
   Description :  Clear internal buffer

*****************************************************************/
void  SocketClient :: RemoveBuffer(int buffType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : RemoveBuffer");
	#endif

	// Check buffer type
	switch (buffType)
	{
		case RECEIVED_DATA_BUFFER_TYPE :
		{
			// Receive buffer
			LOCK_SECTION(rBuffCSGuard);
			
			if (receivedDataBuffer)
			{
				free(receivedDataBuffer);
				receivedDataBuffer = NULL;
			}

			receivedDataBufferSize = 0;
			break;
		}

		case SENT_DATA_BUFFER_TYPE :
		{
			// Sent buffer
			LOCK_SECTION(sBuffCSGuard);

			if (sentDataBuffer)
			{
				free(sentDataBuffer);
				sentDataBuffer = NULL;
			}

			sentDataBufferSize = 0;
			break;
		}
	}
}

/****************************************************************

   Class : SocketClient

   Method : SetDataBuffer

   Parameters :
			Input : 
				buffer - pointer to buffer
				size - buffer size
				buffType - type of buffer

   Returns : error code

   Description : Set data buffer

*****************************************************************/
int SocketClient :: SetDataBuffer(char * buffer, long size, int buffType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : SetDataBuffer. Start");
	#endif

	if (PrepareBuffer(size, buffType) != NULL)
	{
		// Check buffer type
		switch (buffType)
		{
			case RECEIVED_DATA_BUFFER_TYPE:
			{
				// Receive buffer
				LOCK_SECTION(rBuffCSGuard);
				if (buffer) memcpy(receivedDataBuffer, buffer, size);			

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					WriteToLog("SocketClient : SetDataBuffer. Done");
				#endif

				return SERR_SUCCESS;
			}

			case SENT_DATA_BUFFER_TYPE:
			{
				// Sent buffer
				LOCK_SECTION(sBuffCSGuard);
				if (buffer) memcpy(sentDataBuffer, buffer, size);			

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					WriteToLog("SocketClient : SetDataBuffer. Done");
				#endif

				return SERR_SUCCESS;
			}

			default:
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					WriteToLog("SocketClient : SetDataBuffer. Wrong buffer type");
					WriteToLog("SocketClient : SetDataBuffer. Done");
				#endif

				return SERR_BAD_BUFFER;
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : SetDataBuffer. Can't prepare buffer!");
		WriteToLog("SocketClient : SetDataBuffer. Done");
	#endif

	return SERR_BAD_BUFFER;
}

/****************************************************************

   Class : SocketClient

   Method : GetDataBufferSize

   Parameters:
			Input:
				buffType - type of buffer

   Returns : data buffer size

   Description : Get data buffer size

*****************************************************************/
long SocketClient :: GetDataBufferSize(int buffType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : GetDataBufferSize");
	#endif

	int result = -1;

	// Check buffer type
	switch (buffType)
	{
		case RECEIVED_DATA_BUFFER_TYPE:
		{
			// Receive buffer
			LOCK_SECTION(rBuffCSGuard);
			result = receivedDataBufferSize;			
			break;
		}

		case SENT_DATA_BUFFER_TYPE:
		{
			// Sent buffer
			LOCK_SECTION(sBuffCSGuard);
			result = sentDataBufferSize;			
			break;
		}
	}
	
	return result;
}
/****************************************************************

   Class : SocketClient

   Method : GetDataBuffer

   Parameters:
			Input:
				buffType - type of buffer

   Returns : pointer to data buffer copy

   Description : Get data buffer copy

*****************************************************************/
char * SocketClient :: GetDataBuffer(int buffType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : GetDataBuffer. Start");
	#endif

	char * result = NULL;

	// Check buffer type
	switch (buffType)
	{
		case RECEIVED_DATA_BUFFER_TYPE:
		{
			// Receive buffer
			LOCK_SECTION(rBuffCSGuard);

			if ((receivedDataBufferSize <= 0) || (!receivedDataBuffer))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					WriteToLog("SocketClient : GetDataBuffer. Bad buffer for received messages!");
				#endif
				result = NULL;			
			}
			else
			{
				result = (char *)malloc(receivedDataBufferSize);
				result += dllUserCheckResult;

				if (result)
					memcpy(result, receivedDataBuffer, receivedDataBufferSize);
			}

			break;
		}

		case SENT_DATA_BUFFER_TYPE:
		{
			// Sent buffer
			LOCK_SECTION(sBuffCSGuard);

			if ((sentDataBufferSize <= 0) || (!sentDataBuffer))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
					WriteToLog("SocketClient : GetDataBuffer. Bad buffer for sent messages!");
				#endif
				result = NULL;			
			}
			else
			{
				result = (char *)malloc(sentDataBufferSize);
				result += dllUserCheckResult;

				if (result)
					memcpy(result, sentDataBuffer, sentDataBufferSize);
			}

			break;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : GetDataBuffer. Done");
	#endif

	return result;
}

#pragma endregion

#pragma region Threads

/****************************************************************

   Class : SocketClient

   Method : Reconnection

   Parameters :
			Input : 
				socketClient - socket client pointer

   Returns : error code

   Description : Thread of reconnection manager

*****************************************************************/
unsigned long __stdcall SocketClient :: Reconnection(LPVOID socketClient)
{
	SocketClient * client = (SocketClient *) socketClient;

	if (client)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			client -> WriteToLog("SocketClient : Reconnection. Start");
		#endif
		
		do
		{
			if ((!(client -> Connected())) && (!(client -> SocketOpened())))
			{
				client -> CloseThreads();
				client -> Connect();
			}
			
			Sleep(1000);

		} while (client -> GetReconnectionFlag());
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			client -> WriteToLog("SocketClient : Reconnection. Done");
		#endif

		return SERR_SUCCESS;
	}
	
	return SERR_BAD_CLIENT;
}

/****************************************************************

   Class : SocketClient

   Method : TimeoutCounter

   Parameters :
			Input : 
				socketClient - socket client pointer

   Returns : error code

   Description : Thread of timeout checking

*****************************************************************/
unsigned long __stdcall SocketClient :: TimeoutCounter(LPVOID socketClient)
{
	SocketClient * client = (SocketClient *) socketClient;

	if (client)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			client -> WriteToLog("SocketClient : TimeoutCounter. Start");
		#endif
		
		if (client -> GetTimeoutValue() == 0)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
				client -> WriteToLog("SocketClient : TimeoutCounter. Timeout counter is disabled!");
				client -> WriteToLog("SocketClient : TimeoutCounter. Done");
			#endif

			return SERR_SUCCESS;
		}

		do
		{
			unsigned int time = client -> GetTimeoutCounterValue() + 1;

			if (time > client -> GetTimeoutValue())
			{
				if (client -> Connected())
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
						client -> WriteToLog("SocketClient : TimeoutCounter. Timeout period expired!");
					#endif

					client -> Disconnect();

					int waitCorrectDisconnect = 0;
					while ((waitCorrectDisconnect < 30) && (client -> Connected()))
					{
						waitCorrectDisconnect++;
						Sleep(100);
					}

					client -> CloseSocket();
					Sleep(1000);
				}

				client -> SetTimeoutCounterValue(0);
			}
			else
			{
				client -> SetTimeoutCounterValue(time);
				Sleep(1000);
			}

		} while (client -> Connected());
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			client -> WriteToLog("SocketClient : TimeoutCounter. Done");
		#endif

		return SERR_SUCCESS;
	}
	
	return SERR_BAD_CLIENT;
}

/****************************************************************

   Class : SocketClient

   Method : DataRecieving

   Parameters :
			Input : 
				socketClient - socket client pointer

   Returns : error code

   Description : Get buffer from serialization manager

*****************************************************************/
unsigned long __stdcall SocketClient :: DataRecieving(LPVOID socketClient)
{
	SocketClient * client = (SocketClient *) socketClient;

	if (client)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			client -> WriteToLog("SocketClient : DataRecieving. Start");
		#endif
		
		do
		{
			int bytesRecv = client -> RecieveData();
			
			if ((bytesRecv == 0) || (bytesRecv == SOCKET_ERROR))
			{
				client -> CloseSession();
			}
			else
			{
				if (client -> DispatchResponse())
					client -> SendData();
			}

		} while (client -> Connected());
		
		client -> CloseSocket();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			client -> WriteToLog("SocketClient : DataRecieving. Done");
		#endif

		return SERR_SUCCESS;
	}
	
	return SERR_BAD_CLIENT;
}

/****************************************************************

   Class : SocketClient

   Method : CreateThreads
   
   Description :  Create all client threads

*****************************************************************/
int SocketClient :: CreateThreads(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : CreateThreads. Start");
	#endif

	// Create recieving thread
	receiverThread = new BackgroundThread(DataRecieving, this, CLIENT_RECEVER_TIME_OUT, false);
		
	// validate thread
	if (!(receiverThread -> Run()))
	{
		delete receiverThread;
		receiverThread = NULL;

		WriteToLog("Socket client : CreateThreads --> Can't create reciever thread!");
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : CreateThreads. Done");
		#endif

		return SERR_THREAD_CREATE;
	}
				
	// Create timeout thread
	timeoutThread = new BackgroundThread(TimeoutCounter, this, CLIENT_TIMER_TIME_OUT, false);
		
	// validate thread
	if (!(timeoutThread -> Run()))
	{
		delete timeoutThread;
		timeoutThread = NULL;

		WriteToLog("Socket client : CreateThreads --> Can't create timeout thread!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : CreateThreads. Done");
		#endif

		return SERR_THREAD_CREATE;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : CreateThreads. Done");
	#endif

	return SERR_SUCCESS;
}

/****************************************************************

   Class : SocketClient

   Method : CloseThreads
   
   Description :  Close all client threads

*****************************************************************/
void SocketClient :: CloseThreads(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : CloseThreads. Start");
	#endif

	// Wait for timeout thread
	if (timeoutThread)
	{
		delete timeoutThread;
		timeoutThread = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : StopReconnection. Timeout thread is deleted!");
		#endif
	}	

	// Wait for reciever thread
	if (receiverThread)
	{
		delete receiverThread;
		receiverThread = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
			WriteToLog("SocketClient : StopReconnection. Receiver thread is deleted!");
		#endif
	}	

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("SocketClient : CloseThreads. Done");
	#endif
}

#pragma endregion

#pragma region LOG

/****************************************************************

   Class : SocketClient

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int SocketClient :: WriteToLog(char * message)
{
    if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}

#pragma endregion
