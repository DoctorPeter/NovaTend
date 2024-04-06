/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : IPCClientsManagerEx.cpp

   Description :  this module implements methods of
				  class IPCClientsManagerEx

*****************************************************************/

#include "stdafx.h"

#include "IPCClientsManagerEx.h"

// z-ipcclient-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCClientDllDefinition;

/****************************************************************

   Class : IPCClientsManagerEx

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
IPCClientsManagerEx :: IPCClientsManagerEx(unsigned long dllUserID, LogWriter * logWriter, unsigned int gServerID, char * gServerIPAddress, unsigned int gServerPort, IPCServerEx * pIPCServerEx) : IPCClientsManager(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManagerEx : constructor");
	#endif

	this -> gServerID = gServerID;
	this -> gServerPort = gServerPort;

	if (gServerIPAddress)
		strcpy(this -> gServerIPAddress, gServerIPAddress);
	else
		strcpy(this -> gServerIPAddress, "0.0.0.0");

	SetIPCServerInstance(pIPCServerEx);
}

/****************************************************************

   Class : IPCClientsManagerEx

   Method : Destructor

*****************************************************************/
IPCClientsManagerEx :: ~IPCClientsManagerEx(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManagerEx : destructor");
	#endif
}

/****************************************************************

   Class : IPCClientsManagerEx

   Method : AddConnection

   Parameters:
			Input:
				serverID - server ID
				serverType - server type
				serverIPAddress - IP address of server
				serverPort - server port
				clientType - type of client
				accountType - account type 
				clientName - client name
				pSelfServerDescr - self server description
				timeoutValue - timeout value

   Returns: pointer to IPC client instance

   Description : Add new connection

*****************************************************************/
IPCClient * IPCClientsManagerEx :: AddConnection(unsigned int serverID, int serverType, char * serverIPAddress, unsigned int port, int clientType, char * clientName, PSERVER_DESCRIPTION pSelfServerDescr, unsigned int timeoutValue)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_CLIENT)
		WriteToLog("IPCClientsManagerEx : AddConnection. Start");
	#endif

	// Try to find server
	IPCClient * ipcClient = FindConnection(serverID);

	// if no such connection
	if ((!ipcClient) && (connectCount < MAX_CLIENTS_COUNT - 1))
	{
		LOCK_SECTION(connectCSGuard);

		ipcClient = new IPCClientEx(dllUserID, logWriter, AF_INET, SOCK_STREAM, 0, 0x0202, 
			                        serverID, serverType, port, serverIPAddress, 
									gServerID, gServerPort, gServerIPAddress,
									timeoutValue, clientType, clientName, pSelfServerDescr, pIPCServerEx);
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
			WriteToLog("IPCClientsManagerEx : AddConnection. New connection can not be added!");

		WriteToLog("IPCClientsManagerEx : AddConnection. Done");
	#endif

	return ipcClient;
}

/****************************************************************

   Class : IPCClientsManagerEx

   Method : SetIPCServerInstance

   Parameters:
			Input:
				pIPCServerEx - pointer to extended IPCServer instance

   Description : Set pointer to extended IPCServer instance

*****************************************************************/
void IPCClientsManagerEx :: SetIPCServerInstance(IPCServerEx * pIPCServerEx)
{
	this -> pIPCServerEx = pIPCServerEx;
}