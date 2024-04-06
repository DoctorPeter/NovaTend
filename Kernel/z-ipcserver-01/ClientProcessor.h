/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : ClientProcessor.h

   Description :  this module defines interface of
				  class ClientProcessor

*****************************************************************/

#ifdef ZIPCSERVER01_EXPORTS
#define CLIENT_PROCESSOR_API __declspec(dllexport)
#else
#define CLIENT_PROCESSOR_API __declspec(dllimport)
#endif

#ifndef CLIENT_PROCESSOR_H
#define CLIENT_PROCESSOR_H

#include <winsock2.h>
#include <windows.h>

#include "socket_def.h"
#include <LogWriter.h>
#include <BackgroundThread.h>

// Socket server forward declaration
class SocketServer;

/****************************************************************

   Class : ClientProcessor

   Description : provides processing of clients data

*****************************************************************/
class CLIENT_PROCESSOR_API ClientProcessor : public SystemBase
{
	protected:
	
		// Size of internal buffer for received messages
		long receivedDataBufferSize;

		// Data buffer for received messages
		char * receivedDataBuffer;

		// Size of internal buffer for sent messages
		long sentDataBufferSize;

		// Data buffer for sent messages
		char * sentDataBuffer;


		// Pointer to socket server instance
		SocketServer * socketServer;


		// Client socket
		SOCKET clientSocket;

	
		// Connection session flag
		bool openSession;


		// Client processor critical section
		CriticalSection * clientCSGuard;

		// Recieve data critical section
		CriticalSection * recvCSGuard;

		// Send data critical section
		CriticalSection * sendCSGuard;

		// Data buffer for received messages critical section
		CriticalSection * rBuffCSGuard;

		// Data buffer for sent messages critical section
		CriticalSection * sBuffCSGuard;

		// Session critical section
		CriticalSection * sessionCSGuard;

		// Timeout critical serction
		CriticalSection * timeCSGuard;


		// Timeout value
		unsigned int timeoutValue;

		// Timeout counter value
		unsigned int timeoutCounterValue;


		// Log writer instance
		LogWriter * logWriter;

		// Recieve data
		int Recieve(char * recvBuff, long size);

		// Send data
		int Send(char * sendBuff, long size);

		// Processor thread
		BackgroundThread * processorThread;

		// Client address
		sockaddr_in clientAddress;

	public:

		// Constructor
		ClientProcessor(unsigned long dllUserID, 
						SocketServer * socketServer, 
						SOCKET clientSocket, 
						sockaddr_in * clientAddress, 
						PTHREAD_BODY_FUNCTION pProcessorBodyFunction, 
						LogWriter * logWriter, 
						unsigned int timeoutValue);

		// Destructor
		virtual ~ClientProcessor(void);


		// Open connection session
		bool OpenSession(void);

		// Close connection session
		bool CloseSession(void);

		// Check session status
		bool SessionOppened(void);
				

		// Set timeout value
		void SetTimeoutCounterValue(unsigned int time);

		// Get timeout value
		unsigned int GetTimeoutCounterValue(void);

		// Set timeout value
		void SetTimeoutValue(unsigned int time);

		// Get timeout value
		unsigned int GetTimeoutValue(void);


		// Allocate memory for internal buffer
		char * PrepareBuffer(long buffSize, int buffType);

		// Clear internal buffer
		void RemoveBuffer(int buffType);

		// Get data buffer size
		int GetDataBufferSize(int buffType);

		// Set memory for internal buffer
		char * SetDataBuffer(char * buffer, long buffSize, int buffType);
		

		// Recieve message
		long RecieveData(void);
		
		// Send message
		long SendData(void);


		// Connection procedure
		virtual bool Connect(void);

		// Disconnection procedure
		virtual bool Disconnect(void);


		// Dispatch recieved request
		virtual bool DispatchRequest(void);

		
		// Write message to log-file
		int WriteToLog(char * message);
};

#endif