/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : ClientProcessor.cpp

   Description :  this module implements methods of
				  class ClientProcessor

*****************************************************************/

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#include "ClientProcessor.h"
#include "SocketServer.h"

// z-ipcserver-01.dll definition structure
extern DLL_COMMON_DEFINITION zIPCServerDllDefinition;

/****************************************************************

   Class : ClientProcessor

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				socketServer - pointer to socket server
				clientSocket - client windows socket
				clientAddress - client address structure
				logWriter - pointer to LogWriter instance
				timeoutValue - timeout value

*****************************************************************/
ClientProcessor :: ClientProcessor(unsigned long dllUserID, 
									SocketServer * socketServer, 
									SOCKET clientSocket, 
									sockaddr_in * clientAddress, 
									PTHREAD_BODY_FUNCTION pProcessorBodyFunction, 
									LogWriter * logWriter, 
									unsigned int timeoutValue) : SystemBase(dllUserID, &zIPCServerDllDefinition)
{
	clientCSGuard	= new CriticalSection();
	sendCSGuard		= new CriticalSection();
	recvCSGuard		= new CriticalSection();
	rBuffCSGuard	= new CriticalSection();
	sBuffCSGuard	= new CriticalSection();
	timeCSGuard		= new CriticalSection();
	sessionCSGuard	= new CriticalSection();
	
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : constructor");
	#endif

	this -> socketServer = socketServer;

	this -> clientSocket = clientSocket;
	memcpy(&(this -> clientAddress), clientAddress, sizeof(this -> clientAddress));

	receivedDataBufferSize = 0;
	receivedDataBuffer = NULL;

	sentDataBufferSize = 0;
	sentDataBuffer = NULL;

	processorThread = new BackgroundThread(pProcessorBodyFunction, this, SERVER_CLIENT_PROCESSOR_TIME_OUT);

	openSession = false;
	OpenSession();
	if (!(processorThread -> Run()))
		CloseSession();

	SetTimeoutValue(timeoutValue);
	SetTimeoutCounterValue(0);
}

/****************************************************************

   Class : ClientProcessor

   Method : Destructor

*****************************************************************/
ClientProcessor :: ~ClientProcessor(void)
{
	// Close session
	CloseSession();

	// Wait thread
	processorThread -> Stop(3000);
	
	// Close client socket
	closesocket(clientSocket);

	// Remove thread
	delete processorThread;

	// Remove buffer
	RemoveBuffer(RECEIVED_DATA_BUFFER_TYPE);

	// Remove buffer
	RemoveBuffer(SENT_DATA_BUFFER_TYPE);

	delete rBuffCSGuard;
	delete sBuffCSGuard;
	delete recvCSGuard;
	delete sendCSGuard;
	delete clientCSGuard;
	delete timeCSGuard;
	delete sessionCSGuard;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : destructor");
	#endif

}

/****************************************************************

   Class : ClientProcessor

   Method : SetTimeoutCounterValue
    
   Parameters :
			Input : 
				time - counter value

   Description :  Set timeout cuonter value

*****************************************************************/
void ClientProcessor :: SetTimeoutCounterValue(unsigned int time)
{
	LOCK_SECTION(timeCSGuard);
	timeoutCounterValue = time;
}

/****************************************************************

   Class : ClientProcessor

   Method : GetTimeoutCounterValue
    
   Description :  Get timeout counter value

*****************************************************************/
unsigned int ClientProcessor :: GetTimeoutCounterValue(void)
{
	LOCK_SECTION(timeCSGuard);
	return timeoutCounterValue;
}

/****************************************************************

   Class : ClientProcessor

   Method : SetTimeoutValue
    
   Parameters :
			Input : 
				time - counter value

   Description :  Set timeout value

*****************************************************************/
void ClientProcessor :: SetTimeoutValue(unsigned int time)
{
	LOCK_SECTION(timeCSGuard);
	timeoutValue = time;
}

/****************************************************************

   Class : ClientProcessor

   Method : GetTimeoutValue
    
   Description :  Get timeout value

*****************************************************************/
unsigned int ClientProcessor :: GetTimeoutValue(void)
{
	LOCK_SECTION(timeCSGuard);
	return timeoutValue;
}

/****************************************************************

   Class : ClientProcessor

   Method : PrepareBuffer
    
   Parameters :
			Input : 
				buffSize - buffer size
				buffType - type of buffer

   Return : pointer to data buffer
	
   Description :  Allocate memory for internal buffer

*****************************************************************/
char * ClientProcessor :: PrepareBuffer(long buffSize, int buffType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : PrepareBuffer. Start");
	#endif

	// Remove previous buffer
	RemoveBuffer(buffType);
	
	// Check buffer type
	switch (buffType)
	{
		// Receive buffer
		case RECEIVED_DATA_BUFFER_TYPE:
		{
			LOCK_SECTION(rBuffCSGuard);

			if (buffSize <= 0)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
					WriteToLog("ClientProcessor : PrepareBuffer. Wrong received messages buffer size value!");
				#endif
			}
			else
			{
				receivedDataBufferSize = buffSize;
				receivedDataBuffer = (char *)malloc(receivedDataBufferSize);
			}
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				WriteToLog("ClientProcessor : PrepareBuffer. Done");
			#endif

			return receivedDataBuffer;
		}

		// Send buffer
		case SENT_DATA_BUFFER_TYPE:
		{
			LOCK_SECTION(sBuffCSGuard);

			if (buffSize <= 0)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
					WriteToLog("ClientProcessor : PrepareBuffer. Wrong sent messages buffer size value!");
				#endif
			}
			else
			{
				sentDataBufferSize = buffSize;
				sentDataBuffer = (char *)malloc(sentDataBufferSize);
			}
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				WriteToLog("ClientProcessor : PrepareBuffer. Done");
			#endif

			return sentDataBuffer;
		}

		default: 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
				WriteToLog("ClientProcessor : PrepareBuffer. Wrong buffer type!");
				WriteToLog("ClientProcessor : PrepareBuffer. Done");
			#endif

			return NULL;
		}
	}
}

/****************************************************************

   Class : ClientProcessor

   Method : RemoveBuffer

   Parameters :
			Input : 
				buffType - type of buffer
    
   Description :  Clear internal buffer

*****************************************************************/
void ClientProcessor :: RemoveBuffer(int buffType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : RemoveBuffer");
	#endif

	// Check buffer type
	switch (buffType)
	{
		case RECEIVED_DATA_BUFFER_TYPE:
		{
			// Receive buffer
			LOCK_SECTION(rBuffCSGuard);
			
			if (receivedDataBuffer)
			{
				free(receivedDataBuffer);
				receivedDataBuffer = NULL;
			}

			receivedDataBufferSize = 0;
			break;
		}

		case SENT_DATA_BUFFER_TYPE:
		{
			// Sent buffer
			LOCK_SECTION(sBuffCSGuard);

			if (sentDataBuffer)
			{
				free(sentDataBuffer);
				sentDataBuffer = NULL;
			}

			sentDataBufferSize = 0;
			break;
		}
	}
}

/****************************************************************

   Class : ClientProcessor

   Method : GetDataBufferSize

   Parameters :
			Input : 
				buffType - type of buffer
    
   Description :  Get data buffer size

*****************************************************************/
int ClientProcessor :: GetDataBufferSize(int buffType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : GetDataBufferSize");
	#endif

	int result = -1;

	// Check buffer type
	switch (buffType)
	{
		case RECEIVED_DATA_BUFFER_TYPE :
		{
			// Receive buffer
			LOCK_SECTION(rBuffCSGuard);
			result = receivedDataBufferSize;			
			break;
		}

		case SENT_DATA_BUFFER_TYPE :
		{
			// Sent buffer
			LOCK_SECTION(sBuffCSGuard);
			result = sentDataBufferSize;			
			break;
		}
	}
	
	return result;
}

/****************************************************************

   Class : ClientProcessor

   Method : SetDataBuffer
    
   Parameters :
			Input : 
				buffer - source buffer
				buffSize - buffer size
				buffType - type of buffer

   Return : pointer to data buffer
	
   Description :  Allocate memory for internal buffer

*****************************************************************/
char * ClientProcessor :: SetDataBuffer(char * buffer, long buffSize, int buffType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : SetDataBuffer. Start");
	#endif

	if (PrepareBuffer(buffSize, buffType) != NULL)
	{
		// Check buffer type
		switch (buffType)
		{
			case RECEIVED_DATA_BUFFER_TYPE :
			{
				// Receive buffer
				LOCK_SECTION(rBuffCSGuard);
				if (buffer) memcpy(receivedDataBuffer, buffer, buffSize);			

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
					WriteToLog("ClientProcessor : SetDataBuffer. Done");
				#endif
				return receivedDataBuffer;
			}

			case SENT_DATA_BUFFER_TYPE :
			{
				// Sent buffer
				LOCK_SECTION(sBuffCSGuard);
				if (buffer) memcpy(sentDataBuffer, buffer, buffSize);			

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
					WriteToLog("ClientProcessor : SetDataBuffer. Done");
				#endif
				return sentDataBuffer;
			}

			default:
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
					WriteToLog("ClientProcessor : SetDataBuffer. Wrong buffer type");
					WriteToLog("ClientProcessor : SetDataBuffer. Done");
				#endif

				return NULL;
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : SetDataBuffer. Can't prepare buffer!");
		WriteToLog("ClientProcessor : SetDataBuffer. Done");
	#endif

	return NULL;
}


/****************************************************************

   Class : ClientProcessor

   Method : OpenSession
   
   Returns : session state

   Description :  Open connection session

*****************************************************************/
bool ClientProcessor :: OpenSession(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : OpenSession. Start");

		if (openSession)
			WriteToLog("ClientProcessor : OpenSession. Can't open session! Session already opened!");
	#endif

	LOCK_SECTION(sessionCSGuard);
	openSession = true;
	
	char message[256];
	sprintf(message, "Client processing : The session has opened for the client [%s : %d]", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
	WriteToLog(message);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : OpenSession. Session successfully opened!");
		WriteToLog("ClientProcessor : OpenSession. Done");
	#endif

	return openSession;
}

/****************************************************************

   Class : ClientProcessor

   Method : CloseSession
   
   Returns : session state

   Description :  Close connection session

*****************************************************************/
bool ClientProcessor :: CloseSession(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : CloseSession. Start");

		if (!openSession)
			WriteToLog("ClientProcessor : CloseSession. Can't close session! Session already closed!");
	#endif

	LOCK_SECTION(sessionCSGuard);

	char message[256];
	sprintf(message, "Client processing : The session has closed for the client [%s : %d]", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
	WriteToLog(message);

	openSession = false;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : CloseSession. Session successfully closed!");
		WriteToLog("ClientProcessor : CloseSession. Done");
	#endif

	return openSession;
}

/****************************************************************

   Class : ClientProcessor

   Method : SessionOppened
   
   Returns : session state

   Description :  Check connection session status

*****************************************************************/
bool ClientProcessor :: SessionOppened(void)
{
	LOCK_SECTION(sessionCSGuard);
	return openSession;
}

/****************************************************************

   Class : ClientProcessor

   Method : DispatchRequest
   
   Returns : whether to return the result of the query?

   Description :  Dispatch recieved request

*****************************************************************/
bool ClientProcessor :: DispatchRequest(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : DispatchRequest. Start");
	#endif
	
	LOCK_SECTION(clientCSGuard);
	bool sendResult = false;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : DispatchRequest. Done");
	#endif

	return sendResult;
}

/****************************************************************

   Class : ClientProcessor

   Method : Recieve
   
    Parameters :
			Input : 
				recvBuff - data buffer
				size - buffer size
  
   Returns : data size

   Description :  Recieve data

*****************************************************************/
int ClientProcessor :: Recieve(char * recvBuff, long size)
{
	char * pBuff = recvBuff;
	int count = size;
	int recvBytes = 0;

	while (count > 0)
	{
		recvBytes = recv(clientSocket, pBuff, count, 0);

		if (recvBytes == 0)
			return 0;

		if (recvBytes == SOCKET_ERROR)
			return SOCKET_ERROR;

		pBuff += recvBytes;
		count -= recvBytes;
	}

	SetTimeoutCounterValue(0);
	return size;
}

/****************************************************************

   Class : ClientProcessor

   Method : Send
   
    Parameters :
			Input : 
				sendBuff - data buffer
				size - buffer size
  

   Returns : data size

   Description :  Send data

*****************************************************************/
int ClientProcessor :: Send(char * sendBuff, long size)
{
	char * pBuff = sendBuff;
	int count = size;
	int sentBytes = 0;

	while (count > 0)
	{
		sentBytes = send(clientSocket, pBuff, count, 0);
		
		if (sentBytes == SOCKET_ERROR)
			return SOCKET_ERROR;

		pBuff += sentBytes;
		count -= sentBytes;
	}

	SetTimeoutCounterValue(0);
	return size;
}

/****************************************************************

   Class : ClientProcessor

   Method : RecieveMessage
   
   Returns : message size

   Description :  Recieve message

*****************************************************************/
long  ClientProcessor :: RecieveData(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : RecieveData. Start");
	#endif

	LOCK_SECTION(recvCSGuard);

	// Recieve message size
	long messageSize = 0;
	int recvBytes = Recieve((char *)&messageSize, sizeof(messageSize));

	// Validate message size
	if ((recvBytes == 0) || (recvBytes == SOCKET_ERROR))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("ClientProcessor : RecieveData. Failed to recieve message size!");
			WriteToLog("ClientProcessor : RecieveData. Done");
		#endif

		return 0;
	}

	// Validate message size
	if (messageSize == 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("ClientProcessor : RecieveData. Zero message size!");
			WriteToLog("ClientProcessor : RecieveData. Done");
		#endif

		return 0;
	}
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		char message[128];
		sprintf(message, "ClientProcessor : RecieveData. Message size : %d", messageSize);
		WriteToLog(message);
	#endif

	// Prepare buffer
	if (PrepareBuffer(messageSize, RECEIVED_DATA_BUFFER_TYPE) == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("ClientProcessor : RecieveData. Memory allocation error!");
			WriteToLog("ClientProcessor : RecieveData. Done");
		#endif

		return SOCKET_ERROR;
	}

	recvBytes = Recieve(receivedDataBuffer, messageSize);

	if ((recvBytes == 0) || (recvBytes == SOCKET_ERROR))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			sprintf(message, "ClientProcessor : RecieveData. Recv return: %d Error [%d]", recvBytes, WSAGetLastError());
			WriteToLog(message);
			WriteToLog("ClientProcessor : RecieveData. Failed to recieve message!");
			WriteToLog("ClientProcessor : RecieveData. Done");
		#endif

		return 0;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		sprintf(message, "ClientProcessor : RecieveData. Total recieved : %d", messageSize + sizeof(messageSize));
		WriteToLog(message);
	
		WriteToLog("ClientProcessor : RecieveData. Message recieved successfully!");
		WriteToLog("ClientProcessor : RecieveData. Done");
	#endif

	return messageSize + sizeof(messageSize);
}

/****************************************************************

   Class : ClientProcessor

   Method : SendData
   
   Returns : message size

   Description :  Send message

*****************************************************************/
long  ClientProcessor :: SendData(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : SendData. Start");
	#endif

	// Check buffer
	if (!sentDataBuffer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("ClientProcessor : SendData. Bad data buffer!");
			WriteToLog("ClientProcessor : SendData. Done");
		#endif

		return 0;
	}
		
	LOCK_SECTION(sendCSGuard);

	int bufferSize = GetDataBufferSize(SENT_DATA_BUFFER_TYPE);

	// Send buffer size
	int sentBytes = Send((char *)&bufferSize, sizeof(bufferSize));
	
	if (sentBytes == SOCKET_ERROR)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("ClientProcessor : SendData. Can't sent message size!");
			WriteToLog("ClientProcessor : SendData. Done");
		#endif

		return SOCKET_ERROR;
	}

	// Send buffer
	sentBytes = Send(sentDataBuffer, bufferSize);

	if (sentBytes == SOCKET_ERROR)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
			WriteToLog("ClientProcessor : SendData. Can't sent message buffer!");
			WriteToLog("ClientProcessor : SendData. Done");
		#endif

		return SOCKET_ERROR;
	}

	int totalSent = sentBytes + sizeof(bufferSize);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		char message[128];
		sprintf(message, "ClientProcessor : SendData. BuffSize : %d. Total sent : %d", bufferSize, totalSent);
		WriteToLog(message);

		WriteToLog("ClientProcessor : SendData. Message sent successfully!");
	#endif

	RemoveBuffer(SENT_DATA_BUFFER_TYPE);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : SendData. Done");
	#endif

	return totalSent;
}

/****************************************************************

   Class : ClientProcessor

   Method : Connect

	Return : success flag

	Description : Connection confirmation

*****************************************************************/
bool ClientProcessor :: Connect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : Connect. Start");
	#endif

	LOCK_SECTION(clientCSGuard);
	bool connectionResult = OpenSession();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : Connect. Done");
	#endif

	return connectionResult;
}

/****************************************************************

   Class : ClientProcessor

   Method : Disconnect

	Return : success flag

	Description : Disconnect from server

*****************************************************************/
bool ClientProcessor :: Disconnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : Disconnect. Start");
	#endif

	LOCK_SECTION(clientCSGuard);
	bool disconnectionResult = CloseSession();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_IPC_SERVER)
		WriteToLog("ClientProcessor : Disconnect. Done");
	#endif

	return disconnectionResult;
}

/****************************************************************

   Class : ClientProcessor

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int ClientProcessor :: WriteToLog(char * message)
{
    if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}