/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : IPCClientsManager.h

   Description :  this module defines interface of
				  class IPCClientsManager

*****************************************************************/
#ifdef ZIPCCLIENT01_EXPORTS
#define IPC_CLIENTS_MANAGER_API __declspec(dllexport)
#else
#define IPC_CLIENTS_MANAGER_API __declspec(dllimport)
#endif

#ifndef IPC_CLIENTS_MANAGER_H
#define IPC_CLIENTS_MANAGER_H

#include "IPCClient.h"

/****************************************************************

   Class : IPCClientsManager

   Description : provides data exchange mechanism
				 for interprocess communication

*****************************************************************/
class IPC_CLIENTS_MANAGER_API IPCClientsManager : public SystemBase
{
	protected:
		
		// Connections critical section
		CriticalSection * connectCSGuard;

		// Log writer instance
		LogWriter * logWriter;

		
	public:

		// Count of clients connections
		int connectCount;

		// List of clients connections
		IPCClient * connectList[MAX_CLIENTS_COUNT];

				
		// Constructor
		IPCClientsManager(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~IPCClientsManager(void);

		// Add new connection
		virtual IPCClient * AddConnection(unsigned int serverID, int serverType, char * serverIPAddress, unsigned int port, int clientType, char * clientName, PSERVER_DESCRIPTION pSelfServerDescr, unsigned int timeoutValue);

		// Remove connection from list
		IPCClient * RemoveConnection(int index);

		// Clear connection list
		void ClearConnectionList(void);

		// Find connection
		IPCClient * FindConnection(unsigned int serverID);

		// Find connection
		int FindConnectionIndex(unsigned int serverID);

		// Get server ID
		unsigned int GetServerID(int index);

		// Find most priority server
		unsigned int FindMostPriorityServer(void);

		// Get server description list
		PSERVER_DESCRIPTION_LIST GetServerDescriptionList(void);

		// Send data
		char * SendData(unsigned int serverID, char * requestPack, int requestSize, int * responsePackSize);

		// Send data
		PCOMMAND_REQUEST_RESPONSE SendData(unsigned int serverID, PCOMMAND_REQUEST_RESPONSE pRequest);

		// Write message to LOG-file
		int WriteToLog(char * message);
};

#endif