/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : IPCClientsManagerEx.h

   Description :  this module defines interface of
				  class IPCClientsManagerEx

*****************************************************************/
#ifdef ZIPCCLIENT01_EXPORTS
#define IPC_CLIENTS_MANAGER_EX_API __declspec(dllexport)
#else
#define IPC_CLIENTS_MANAGER_EX_API __declspec(dllimport)
#endif

#ifndef IPC_CLIENTS_MANAGER_EX_H
#define IPC_CLIENTS_MANAGER_EX_H

#include "IPCClientsManager.h"
#include "IPCClientEx.h"

/****************************************************************

   Class : IPCClientsManagerEx

   Description : provides data exchange mechanism
				 for interprocess communication

*****************************************************************/
class IPC_CLIENTS_MANAGER_EX_API IPCClientsManagerEx : public IPCClientsManager
{
	protected:

		// Global server ID
		unsigned int gServerID;

		// Global server IP
		char gServerIPAddress[ADDRESS_SIZE];

		// Global server port
		unsigned int gServerPort;

		// Pointer to extended IPCServer instance
		IPCServerEx * pIPCServerEx;

	public:
				
		// Constructor
		IPCClientsManagerEx(unsigned long dllUserID, LogWriter * logWriter, unsigned int gServerID, char * gServerIPAddress, unsigned int gServerPort, IPCServerEx * pIPCServerEx = NULL);

		// Destructor
		virtual ~IPCClientsManagerEx(void);

		// Add new connection
		virtual IPCClient * AddConnection(unsigned int serverID, int serverType, char * serverIPAddress, unsigned int port, int clientType, char * clientName, PSERVER_DESCRIPTION pSelfServerDescr, unsigned int timeoutValue);

		// Set pointer to extended IPCServer instance
		void SetIPCServerInstance(IPCServerEx * pIPCServerEx);
};

#endif