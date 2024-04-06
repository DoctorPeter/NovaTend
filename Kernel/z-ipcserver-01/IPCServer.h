/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : IPCServer.h

   Description :  this module defines interface of
				  class IPCServer

*****************************************************************/

#ifdef ZIPCSERVER01_EXPORTS
#define IPCSERVER_API __declspec(dllexport)
#else
#define IPCSERVER_API __declspec(dllimport)
#endif

#ifndef IPCSERVER_H
#define IPCSERVER_H

#include "SocketServer.h"
#include <SerializationDef.h>
#include <CommandManager.h>

/****************************************************************

   Class : IPCServer

   Description : provides data exchange mechanism
				 for interprocess communication

*****************************************************************/
class IPCSERVER_API IPCServer : public SocketServer
{
	protected:
		
		// Command manager instance
		CommandManager * commandManager;

		// Create client processor
		virtual ClientProcessor * CreateClientProcessor(SOCKET socket, sockaddr_in * address);

	public:

		// Server ID
		unsigned int serverID;

		// Server type
		int serverType;

		// Server priority
		int serverPriority;

		// Server name
		char serverName[MAX_SERVER_NAME_LEN];


		// Constructor
		IPCServer(unsigned long dllUserID,
					 LogWriter * logWriter,
					 unsigned int serverID,
					 int serverType,
					 int serverPriority,
					 char * serverName,
					 int maxClientsCount,
					 int aF = AF_INET,
					 int sType = SOCK_STREAM, 
					 int sProt = 0,
					 unsigned int wsaVer = 0x0202, 
					 unsigned int port = DEFAULT_PORT,
					 char * address = NULL,
					 CommandManager * commandManager = NULL);
		
		// Destructor
		virtual ~IPCServer(void);

		// Generate new unique ID for client
		unsigned int GenerateClientID(void);

		// Get server description
		PSERVER_DESCRIPTION GetServerDescription(void);

		// Find client
		PCLIENT_DESCRIPTION FindClient(unsigned int ownClientID, int clientType);

		// Find client
		ClientProcessor * FindClient(unsigned int clientID);
};

#endif