/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : IPCProcessor.h

   Description :  this module defines interface of
				  class IPCProcessor

*****************************************************************/

#ifdef ZIPCSERVER01_EXPORTS
#define IPC_PROCESSOR_API __declspec(dllexport)
#else
#define IPC_PROCESSOR_API __declspec(dllimport)
#endif

#ifndef IPC_PROCESSOR_H
#define IPC_PROCESSOR_H

#include "ClientProcessor.h"
#include <CommandManager.h>

/****************************************************************

   Class : IPCProcessor

   Description : provides processing of clients IPC commands

*****************************************************************/
class IPC_PROCESSOR_API IPCProcessor : public ClientProcessor
{
	protected:

		// Pointer to command manager instance
		CommandManager * commandManager;
		
		// Process "connect to" request
		bool ProcessConnectToRequest(unsigned int * clientID);

		// Prepare empty command
		bool PrepareEmptyCommand(void);

	public:

		// Client description
		CLIENT_DESCRIPTION clientDescr;

		// Constructor
		IPCProcessor(unsigned long dllUserID, 
					 CommandManager * commandManager, 
					 SocketServer * socketServer, 
					 SOCKET clientSocket, 
					 sockaddr_in * clientAddress, 
					 PTHREAD_BODY_FUNCTION pProcessorBodyFunction, 
					 LogWriter * logWriter, 
					 unsigned int timeoutValue);

		// Destructor
		virtual ~IPCProcessor(void);
		

		// Connection procedure
		virtual bool Connect(void);

		// Disconnection procedure
		virtual bool Disconnect(void);


		// Dispatch recieved request
		virtual bool DispatchRequest(void);

		// Send CONNECT TO request to client
		long ConnectToRequest(char * ipAddress, int port);

		// Check license
		bool CheckLicense(void);
};

#endif