/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : IPCServerEx.h

   Description :  this module defines interface of
				  class IPCServerEx

*****************************************************************/

#ifdef ZIPCSERVER01_EXPORTS
#define IPCSERVER_EX_API __declspec(dllexport)
#else
#define IPCSERVER_EX_API __declspec(dllimport)
#endif

#ifndef IPCSERVER_EX_H
#define IPCSERVER_EX_H

#include "IPCServer.h"

/****************************************************************

   Class : IPCServerEx

   Description : provides data exchange mechanism
				 for interprocess communication

*****************************************************************/
class IPCSERVER_EX_API IPCServerEx : public IPCServer
{
	protected:

		// Create client processor
		virtual ClientProcessor * CreateClientProcessor(SOCKET socket, sockaddr_in * address);

	public:

		// Constructor
		IPCServerEx(unsigned long dllUserID,
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
		virtual ~IPCServerEx(void);

		// Try to connect beyond NAT
		int TryConnectBeyondNAT(char * bindIPAddress, unsigned int bindPort, char * remoteIPAddress, unsigned int remotePort);
};

#endif