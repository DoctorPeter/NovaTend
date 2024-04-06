/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : IPCClient.h

   Description :  this module defines interface of
				  class IPCClient

*****************************************************************/
#ifdef ZIPCCLIENT01_EXPORTS
#define IPC_CLIENT_API __declspec(dllexport)
#else
#define IPC_CLIENT_API __declspec(dllimport)
#endif

#ifndef IPC_CLIENT_H
#define IPC_CLIENT_H

#include "SocketClient.h"
#include <SerializationManager.h>

/****************************************************************

   Class : IPCClient

   Description : provides data exchange mechanism
				 for interprocess communication

*****************************************************************/
class IPC_CLIENT_API IPCClient : public SocketClient
{
	protected:

		// Remote server ID
		unsigned int serverID;

		// Remote server type
		int serverType;

	public:
		
		// Client description
		CLIENT_DESCRIPTION clientDescr;

		// Server description
		SERVER_DESCRIPTION serverDescr;

		// Self server description
		PSERVER_DESCRIPTION pSelfServerDescr;
				
		// Constructor
		IPCClient(unsigned long dllUserID,
					 LogWriter * logWriter,
					 int aF = AF_INET,
					 int sType = SOCK_STREAM, 
					 int sProt = 0,
					 unsigned int wsaVer = 0x0202, 
					 unsigned int serverID = 0,
					 int serverType = SERVER_TYPE_UNKNOWN,
					 unsigned int port = DEFAULT_PORT,
					 char * address = NULL,
					 unsigned int timeoutValue = 0,
					 int clientType = 0,
					 char * clientName = NULL,
					 PSERVER_DESCRIPTION pSelfServerDescr = NULL);

		// Destructor
		virtual ~IPCClient(void);

		// Set remote server connection data
		void PrepareRemoteServerData(unsigned int serverID, int serverType);

		// Get remote server connection data
		void GetRemoteServerData(unsigned int * serverID, int * serverType);

		// Connect to server
		virtual int Connect(void);
				
		// Connect to server
		int Connect(unsigned int serverID, int serverType, unsigned int port, char * address);
		
		// Dispatch input data
		virtual bool DispatchResponse(void);

		// Connection confirmation
		virtual bool ConfirmConnect(void);

		// Disconnect from server
		virtual int Disconnect(void);

		// Create back connection
		bool CreateBackConnection(void);
};

#endif