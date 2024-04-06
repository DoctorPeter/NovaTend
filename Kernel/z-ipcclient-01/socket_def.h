/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : Socket_def.h

   Description :  this module defines restrictions
				  for SocketClient and SocketServer

*****************************************************************/

#ifndef SOCKETDEF_H
#define SOCKETDEF_H

// Default port
#define DEFAULT_PORT						0x10

// Maximum address size
#define ADDRESS_SIZE						256

// Maximum socket buffer size
#define MAX_SOCKET_BUFFER_SIZE				1048576

// Maximum clients count
#define MAX_CLIENTS_COUNT					4096

// Default timeout value
#define DEFAULT_TIMEOUT						300


// Error codes

// Success code
#define SERR_SUCCESS						0

// Session is closed
#define SERR_CLOSE_SESSION					1

// Listen error
#define SERR_LISTER_ERROR					2

// Bad client socket
#define SERR_BAD_CLIENT						3

// Bad server socket
#define SERR_BAD_SERVER						4

// Stop server error
#define SERR_SERVER_STOPED					5

// Thread creation error
#define	SERR_THREAD_CREATE					6

// Connection error
#define	SERR_CONNECTION_ERROR				7

// Server already started
#define	SERR_ALREADY_STARTED				8

// Server already stopped
#define	SERR_ALREADY_STOPPED				9

// Servrer not started
#define	SERR_NOT_STARTED					10

// Already connected
#define	SERR_ALREADY_CONNECTED				11

// Not connected
#define	SERR_NOT_CONNECTED					12

// Not disconnected
#define	SERR_NOT_DISCONNECTED				13

// Bad buffer
#define	SERR_BAD_BUFFER						14

// Bind error
#define	SERR_BIND_ERROR						15

// Already binded
#define	SERR_ALREADY_BINDED					16

// Threads time out

// Client reconnection thread
#define CLIENT_RECONN_TIME_OUT				0xFFFFFFFF

// Client receiver thread
#define CLIENT_RECEVER_TIME_OUT				0xFFFFFFFF

// Client timer thread
#define CLIENT_TIMER_TIME_OUT				0xFFFFFFFF

// Server client processor 
#define SERVER_CLIENT_PROCESSOR_TIME_OUT	0xFFFFFFFF

// Server client checking
#define SERVER_CLIENT_CHECKING_TIME_OUT		0xFFFFFFFF

// Server client accept
#define SERVER_CLIENT_ACCEPT_TIME_OUT		0xFFFFFFFF



// Buffer types

// Buffer for received messages
#define RECEIVED_DATA_BUFFER_TYPE			0

// Buffer for sent messages
#define SENT_DATA_BUFFER_TYPE				1


// Server types

// Unkonwn client
#define SERVER_TYPE_UNKNOWN					0

// Hub
#define SERVER_TYPE_HUB						1

// Host
#define SERVER_TYPE_HOST					2

// Desktop
#define SERVER_TYPE_DESKTOP					3


// Client types

// Unkonwn client
#define CLIENT_TYPE_UNKNOWN					0

// Hub
#define CLIENT_TYPE_HUB						1

// Host
#define CLIENT_TYPE_HOST					2

// Desktop
#define CLIENT_TYPE_DESKTOP					3

// Credential provider
#define CLIENT_TYPE_WCP						4

// Management tool
#define CLIENT_TYPE_MAN_TOOL				5

// Post login
#define CLIENT_TYPE_POST_LOGIN				6

// Dashboard
#define CLIENT_TYPE_DASH_BOARD				7

// Updater
#define CLIENT_UPDATER						8


#endif