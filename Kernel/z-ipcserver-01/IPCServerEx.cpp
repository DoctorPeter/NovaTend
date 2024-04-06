/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : IPCServerEx.cpp

   Description :  this module implements methods of
				  class IPCServerEx

*****************************************************************/
#include "stdafx.h"

#include "IPCServerEx.h"

// z-ipcserver-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCServerDllDefinition;

/****************************************************************

   Class : IPCServerEx

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
IPCServerEx :: IPCServerEx(unsigned long dllUserID, 
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
						   CommandManager * commandManager) : IPCServer(dllUserID, 
																		logWriter,
																		serverID,
																		serverType,
																		serverPriority,
																		serverName,
																		maxClientsCount,
																		aF, 
																		sType, 
																		sProt, 
																		wsaVer, 
																		port, 
																		address,
																		commandManager)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServerEx : constructor");
	#endif
}

/****************************************************************

   Class : IPCServerEx

   Method : Destructor

*****************************************************************/
IPCServerEx :: ~IPCServerEx(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServerEx : destructor");
	#endif
}

/****************************************************************

   Class : IPCServerEx

   Method : TryConnectBeyondNAT
  
   Parameters:
			Input:
				bindIPAddress - IP address for binding
				bindPort - port for binding
				remoteIPAddress - IP address for connection
				remotePort - port for connection

   Returns : error code

   Description : Try to connect beyond NAT

*****************************************************************/
int IPCServerEx :: TryConnectBeyondNAT(char * bindIPAddress, unsigned int bindPort, char * remoteIPAddress, unsigned int remotePort)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("IPCServerEx : TryConnectBeyondNAT. Start");

		char message[256] = "";
		sprintf(message, "IPCServerEx : TryConnectBeyondNAT. Bind --> %s : %d. Remote --> %s : %d", bindIPAddress, bindPort, remoteIPAddress, remotePort);
		WriteToLog(message);
	#endif

	SOCKET clientSocket = INVALID_SOCKET;

	// Create client socket
	if ((clientSocket = socket(addressFamilySpec, socketType, socketProtocol)) < 0)
	{
		int wsaError = WSAGetLastError();

		WriteToLog("Extended IPC Server : Connect beyond NAT --> Can't create client socket!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCServerEx : TryConnectBeyondNAT. Done");
		#endif

		return wsaError;
	}
	else
	{
		const char yes = 1;

		// Set SO_REUSEADDRR option
		if (setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)))
		{
			closesocket(clientSocket);

			int wsaError = WSAGetLastError();

			WriteToLog("Extended IPC Server : Connect beyond NAT --> Can't set SO_REUSEADDR option for socket!");

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				WriteToLog("IPCServerEx : TryConnectBeyondNAT. Done");
			#endif

			return wsaError;
		}
	}
	
	// Prepare bind address struct
	sockaddr_in bindAddressStruct;
	memset(&bindAddressStruct, 0, sizeof(bindAddressStruct));
	bindAddressStruct.sin_family = addressFamilySpec;
	bindAddressStruct.sin_port = htons(bindPort);
	HOSTENT *hst;
	
	// Set address for binding
	if (inet_addr(bindIPAddress) != INADDR_NONE)
	{
		bindAddressStruct.sin_addr.s_addr = inet_addr(bindIPAddress);
	}
	else
	{
		if (hst = gethostbyname(bindIPAddress))
		{
			((unsigned long *)&bindAddressStruct.sin_addr)[0] = ((unsigned long **)hst -> h_addr_list)[0][0];
		}
		else
		{
			closesocket(clientSocket);

			int wsaError = WSAGetLastError();

			WriteToLog("Extended IPC Server : Connect beyond NAT --> Wrong bind IP address!");

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				WriteToLog("IPCServerEx : TryConnectBeyondNAT. Done");
			#endif

			return wsaError;
		}
	}
	
	// Bind socket
	if(bind(clientSocket, (sockaddr*)&bindAddressStruct, sizeof(bindAddressStruct)))
	{
		closesocket(clientSocket);

		int wsaError = WSAGetLastError();

		WriteToLog("Extended IPC Server : Connect beyond NAT --> Can not bind!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCServerEx : TryConnectBeyondNAT. Done");
		#endif

		return wsaError;
	}

	// Prepare remote address struct
	sockaddr_in remoteAddressStruct;
	memset(&remoteAddressStruct, 0, sizeof(remoteAddressStruct));
	remoteAddressStruct.sin_family = addressFamilySpec;
	remoteAddressStruct.sin_port = htons(remotePort);

	// Set address for connection
	if (inet_addr(remoteIPAddress) != INADDR_NONE)
	{
		remoteAddressStruct.sin_addr.s_addr = inet_addr(remoteIPAddress);
	}
	else
	{
		if (hst = gethostbyname(remoteIPAddress))
		{
			((unsigned long *)&remoteAddressStruct.sin_addr)[0] = ((unsigned long **)hst -> h_addr_list)[0][0];
		}
		else
		{
			closesocket(clientSocket);

			int wsaError = WSAGetLastError();

			WriteToLog("Extended IPC Server : Connect beyond NAT --> Wrong remote IP address!");

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				WriteToLog("IPCServerEx : TryConnectBeyondNAT. Done");
			#endif

			return wsaError;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		char mes[128];
		sprintf(mes, "IPCServerEx : TryConnectBeyondNAT. Trying connect to --> %s : %d ", remoteIPAddress, remotePort);
		WriteToLog(mes);
	#endif

	bool connectionFlag = false;
	int counter = 5;

	// Trying to connect
	while ((counter-- > 0) && (!connectionFlag))
	{
		if (connect(clientSocket, (sockaddr *)&remoteAddressStruct, sizeof(remoteAddressStruct)))
		{
			int wsaError = WSAGetLastError();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				char message[128];
				sprintf(message, "IPCServerEx : TryConnectBeyondNAT. --> Connection error [%d]", wsaError);
				WriteToLog(message);
			#endif

			Sleep(200);
		}
		else
			connectionFlag = true;
	}

	// If connected - Add new client
	if ((connectionFlag) && (AddClient(clientSocket, &remoteAddressStruct)))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCServerEx : TryConnectBeyondNAT. Success!!!");
			WriteToLog("IPCServerEx : TryConnectBeyondNAT. Done");
		#endif

		return SERR_SUCCESS;
	}	
	else
	{
		closesocket(clientSocket);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("IPCServerEx : TryConnectBeyondNAT. Fail!!!");
			WriteToLog("IPCServerEx : TryConnectBeyondNAT. Done");
		#endif
		
		return SERR_CONNECTION_ERROR;
	}
}

/****************************************************************

   Class : IPCServerEx

   Method : CreateClientProcessor

   Parameters :
			Input : 
				socket - windows socket descriptor
				address - client address

   Returns: Client processor instance

   Description :  Create client processor

*****************************************************************/
ClientProcessor * IPCServerEx :: CreateClientProcessor(SOCKET socket, sockaddr_in * address)
{
	return IPCServer :: CreateClientProcessor(socket, address);
}