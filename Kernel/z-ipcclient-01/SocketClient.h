/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : SocketClient.h

   Description :  this module defines interface of
				  class SocketClient

*****************************************************************/
#ifdef ZIPCCLIENT01_EXPORTS
#define SOCKETCLIENT_API __declspec(dllexport)
#else
#define SOCKETCLIENT_API __declspec(dllimport)
#endif

#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <winsock2.h>
#include <windows.h>

#include <BackgroundThread.h>
#include <LogWriter.h>
#include "socket_def.h"

/****************************************************************

   Class : SocketClient

   Description : provides data exchange mechanism
				 for interprocess communication

*****************************************************************/
class SOCKETCLIENT_API SocketClient : public SystemBase
{
	protected:
		
		// Windows socket api version
		unsigned int wsaVersion;

		// WSA descriptor
		WSADATA wsaData;
		
		
		// bind flag
		bool socketBinded;

		// client port
		unsigned int bindPort;

		// bind address
		char bindAddrStr[ADDRESS_SIZE];

		// bind address structure
		sockaddr_in bindAddress;


		// server port
		unsigned int srvPort;
		
		// server address
		char srvAddrStr[ADDRESS_SIZE];

		// server address structure
		sockaddr_in serverAddress;

		
		// address family specification
		int addressFamilySpec;

		// windows socket type
		int socketType;

		// windows socket protocol
		int socketProtocol;

		// Timeout value
		unsigned int timeoutValue;

		// Timeout counter value
		unsigned int timeoutCounterValue;

		
		// Receiver thread
		BackgroundThread * receiverThread;

		// Reconnector thread
		BackgroundThread * reconnectThread;

		// Timeout thread
		BackgroundThread * timeoutThread;


		// Client critical section
		CriticalSection * clientCSGuard;

		// Send data critical section
		CriticalSection * sendCSGuard;

		// Recieve data critical serction
		CriticalSection * recvCSGuard;

		// Data buffer for received messages critical section
		CriticalSection * rBuffCSGuard;

		// Data buffer for sent messages critical section
		CriticalSection * sBuffCSGuard;

		// Session critical serction
		CriticalSection * sessCSGuard;

		// Socket critical serction
		CriticalSection * sockCSGuard;

		// Reconnector critical serction
		CriticalSection * reconCSGuard;

		// Timeout critical serction
		CriticalSection * timeCSGuard;


		// Client socket
		SOCKET clientSocket;

		// Log writer instance
		LogWriter * logWriter;

		
		// Size of internal buffer for received messages
		long receivedDataBufferSize;

		// Data buffer for received messages
		char * receivedDataBuffer;

		// Size of internal buffer for sent messages
		long sentDataBufferSize;

		// Data buffer for sent messages
		char * sentDataBuffer;

		// Socket status
		bool socketOpened;

		// Session flag
		bool sessionOpened;

		// Data recieving flag
		bool dataRecieved;

		// Reconnector flag
		bool mustReconnect;

		// Create threads
		int CreateThreads(void);

		// Close threads
		void CloseThreads(void);

		// Recieve data
		int Recieve(char * recvBuff, long size);

		// Send data
		int Send(char * sendBuff, long size);

		// Prepare data buffer
		char * PrepareBuffer(long buffSize, int buffType);

		// Remove data buffer
		void RemoveBuffer(int buffType);

		// Data recieving thread function
		static unsigned long __stdcall DataRecieving(void * socketClient);

		// Reconnection thread function
		static unsigned long __stdcall Reconnection(void * socketClient);

		// Timeout thread function
		static unsigned long __stdcall TimeoutCounter(void * socketClient);

		// Bind client socket
		int BindClientSocket(void);

		// Bind client socket
		int BindClientSocket(char * ipAddress, unsigned int port);

		// Prepare address
		bool PrepareIPAddress(char * ipAddress, sockaddr_in * addressStruct);

		// Get current IP
		char * GetCurrentIP(char * ipAddress);

		// Connect socket
		int ConnectSocket(void);

	public:
				
		// Constructor
		SocketClient(unsigned long dllUserID,
					 LogWriter * logWriter,
					 int aF = AF_INET,
					 int sType = SOCK_STREAM, 
					 int sProt = 0,
					 unsigned int wsaVer = 0x0202, 
					 unsigned int port = DEFAULT_PORT,
					 char * address = NULL,
					 unsigned int timeoutValue = 0);

		// Destructor
		virtual ~SocketClient(void);

		// Set windows socket specification
		void PrepareSocketSpecification(unsigned int wsaVer, int aF, int sType, int sProt);

		// Set windows socket connection data
		void PrepareSocketConnection(unsigned int port, char * address);

		// Get windows socket specification
		void GetSocketSpecification(unsigned int * wsaVer, int * aF, int * sType, int * sProt);

		// Get windows socket connection data
		void GetSocketConnection(unsigned int * port, char * address);

		// Connect to server
		virtual int Connect(void);

		// Connect to server
		int Connect(unsigned int port, char * address);

		// Check connection
		bool Connected(void);

		// Disconnect from server
		virtual int Disconnect(void);
				
		// Dispatch input data
		virtual bool DispatchResponse(void);

		// Recieve message
		long RecieveData(void);
		
		// Send message
		long SendData(void);



		// Connection confirmation
		virtual bool ConfirmConnect(void);

		// Set data buffer
		int SetDataBuffer(char * buffer, long size, int buffType);

		// Get data buffer size
		long GetDataBufferSize(int buffType);

		// Get data buffer copy
		char * GetDataBuffer(int buffType);


		// Set recieve data flag
		void SetRecieveDataFlag(bool flag);

		// Get recieve data flag
		bool GetRecieveDataFlag(void);


		// Set session status
		bool SetSessionStatus(bool status);

		// Get session status
		bool GetSessionStatus(void);

		// Open session
		bool OpenSession(void);

		// Close session
		bool CloseSession(void);
		
		// Session opened
		bool SessionOpened(void);

		

		// Set socket status
		bool SetSocketStatus(bool status);

		// Get socket status
		bool GetSocketStatus(void);

		// Open session
		bool OpenSocket(void);

		// Close session
		bool CloseSocket(void);
		
		// Session opened
		bool SocketOpened(void);



		// Set timeout value
		void SetTimeoutCounterValue(unsigned int time);

		// Get timeout value
		unsigned int GetTimeoutCounterValue(void);

		// Set timeout value
		void SetTimeoutValue(unsigned int time);

		// Get timeout value
		unsigned int GetTimeoutValue(void);


		// Start reconnection thread
		bool StartReconnection(void);

		// Stop Reconnection thread
		bool StopReconnection(void);

		// Set reconnection flag
		void SetReconnectionFlag(bool flag);

		// Get reconnection flag
		bool GetReconnectionFlag(void);

		// Write message to LOG-file
		int WriteToLog(char * message);
};

#endif