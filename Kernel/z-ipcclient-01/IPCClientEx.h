/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : IPCClientEx.h

   Description :  this module defines interface of
				  class IPCClientEx

*****************************************************************/
#ifdef ZIPCCLIENT01_EXPORTS
#define IPC_CLIENT_EX_API __declspec(dllexport)
#else
#define IPC_CLIENT_EX_API __declspec(dllimport)
#endif

#ifndef IPC_CLIENT_EX_H
#define IPC_CLIENT_EX_H

#include "IPCClient.h"
#include <IPCServerEx.h>

/****************************************************************

   Class : IPCClientEx

   Description : provides data exchange mechanism
				 for interprocess communication

*****************************************************************/
class IPC_CLIENT_EX_API IPCClientEx : public IPCClient
{
	protected:

		// global server ID
		unsigned int globalServerID;


		// global server port
		unsigned int gSrvPort;
		
		// global server address
		char gSrvAddrStr[ADDRESS_SIZE];

		
		// pointer to extended IPC server instance
		IPCServerEx * pIPCServerEx;


		// remote server port
		unsigned int remoteSrvPort;
		
		// remote server address
		char remoteSrvAddrStr[ADDRESS_SIZE];


		
		// Try to connect via TCP HP
		int TCPHPConnect(void);

		// Try to connect beyond NAT
		int TryConnectBeyondNAT(void);


		// Process connect to request
		bool ProcessConnectToRequest(void);
		
		// Process connect to response
		bool ProcessConnectToResponse(void);


	public:
				
		// Constructor
		IPCClientEx(unsigned long dllUserID,
					 LogWriter * logWriter,
					 int aF = AF_INET,
					 int sType = SOCK_STREAM, 
					 int sProt = 0,
					 unsigned int wsaVer = 0x0202, 
					 unsigned int localServerID = 0,
					 int localServerType = SERVER_TYPE_UNKNOWN,
					 unsigned int localPort = DEFAULT_PORT,
					 char * localAddress = NULL,
					 unsigned int globalServerID = 0,
					 unsigned int globalPort = DEFAULT_PORT,
					 char * globalAddress = NULL,
					 unsigned int timeoutValue = 0,
					 int clientType = 0,
					 char * clientName = NULL,
					 PSERVER_DESCRIPTION pSelfServerDescr = NULL,
					 IPCServerEx * pIPCServerEx = NULL);

		// Destructor
		virtual ~IPCClientEx(void);

		// Set windows socket connection data
		void PrepareSocketConnection(unsigned int localPort, char * localAddress, unsigned int globalPort, char * globalAddress);

		// Get windows socket connection data
		void GetSocketConnection(unsigned int  * localPort, char * localAddress, unsigned int  * globalPort, char * globalAddress);

		// Connect to server
		virtual int Connect(void);

		// Connect to server
		int Connect(unsigned int serverID, int serverType, unsigned int port, char * address, unsigned int gServerID, unsigned int gServerPort, char * gServerAddress);

		// Connection confirmation
		virtual bool ConfirmConnect(void);

		// Disconnect from server
		virtual int Disconnect(void);

		// Dispatch input data
		virtual bool DispatchResponse(void);
};

#endif