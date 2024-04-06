/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : SocketServer.h

   Description :  this module defines interface of
				  class SocketServer

*****************************************************************/

#ifdef ZIPCSERVER01_EXPORTS
#define SOCKETSERVER_API __declspec(dllexport)
#else
#define SOCKETSERVER_API __declspec(dllimport)
#endif

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <winsock2.h>
#include <windows.h>

#ifdef IPC_CLIENT_EX_H
#include "socket_def.h"
#else
#include <socket_def.h>
#endif

#include "ClientProcessor.h"
#include <LogWriter.h>
#include <BackgroundThread.h>

/****************************************************************

   Class : SocketServer

   Description : provides data exchange mechanism
				 for interprocess communication

*****************************************************************/
class SOCKETSERVER_API SocketServer : public SystemBase
{
	protected:
		
		// Windows socket api version
		unsigned int wsaVersion;

		// WSA descriptor
		WSADATA wsaData;

		// server port
		unsigned int port;

		// server address
		char address[ADDRESS_SIZE];
			
		// address family specification
		int addressFamilySpec;

		// windows socket type
		int socketType;

		// windows socket protocol
		int socketProtocol;
		
		// clients count
		int clientsCount;

		// Maximum count of clients
		int maxClientsCount;

		// clients list
		ClientProcessor * clientProcessors[MAX_CLIENTS_COUNT];
		
		// server listen socket
		SOCKET serverSocket;

		// server address structure
		sockaddr_in serverAddress;

		// flag for server start
		bool serverStarted;

		// flag for clients accepting
		bool stopAccepting;
		
		// server critical section
		CriticalSection * serverCSGuard;
		
		// Accept thread
		BackgroundThread * acceptThread;

		// Checking thread
		BackgroundThread * checkThread;

		// Log writer instance
		LogWriter * logWriter;
				
		// Add client to list
		ClientProcessor * AddClient(SOCKET socket, sockaddr_in * address);

		// Remove client from list
		void RemoveClient(int clientIndex);

		// Clear clients list
		void ClearClients(void);

		// Create client processor
		virtual ClientProcessor * CreateClientProcessor(SOCKET socket, sockaddr_in * address);

	public:

		// Client processing thread
		static unsigned long __stdcall ClientProcessing(void * clientProcessor);

		// Client accepting thread
		static unsigned long __stdcall ClientAppcepting(void * socketServer);

		//Client checking thread
		static unsigned long __stdcall ClientChecking(void * socketServer);

		// Constructor
		SocketServer(unsigned long dllUserID,
					 LogWriter * logWriter,
					 int maxClientsCount,
					 int aF = AF_INET,
					 int sType = SOCK_STREAM, 
					 int sProt = 0,
					 unsigned int wsaVer = 0x0202, 
					 unsigned int port = DEFAULT_PORT,
					 char * address = NULL);
		
		// Destructor
		virtual ~SocketServer(void);

		// Start server
		int Start(void);

		// Shutdown server
		int Shutdown(void);

		// Start request processing
		int StartRequestProcessing(void);
		
		// Stop request processing
		int StopRequestProcessing(void);

		// Set windows socket specification
		void PrepareSocketSpecification(unsigned int wsaVer, int aF, int sType, int sProt);

		// Set windows socket connection data
		void PrepareSocketConnection(unsigned int port, char * address);
				
		// Write message to LOG-file
		int WriteToLog(char * message);
};

#endif