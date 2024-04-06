/****************************************************************

   Solution : NovaTend

   Project : z-serialize-01.dll

   Module : SerializationManager.cpp

   Description : this module implements methods of
				  class SerializationManager

*****************************************************************/

#include "stdafx.h"
#include "SerializationManager.h"

#include <stdlib.h>

// z-serialize-01.dll definition structure
extern DLL_COMMON_DEFINITION zSerializeDllDefinition;

#pragma region Constructor

/****************************************************************

   Class : SerializationManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - log writer instance

*****************************************************************/
SerializationManager :: SerializationManager(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zSerializeDllDefinition)
{
	this -> logWriter = logWriter;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : Constructor");
	#endif
}

/****************************************************************

   Class : SerializationManager

   Method : Destructor

*****************************************************************/
SerializationManager :: ~SerializationManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : Destructor");
	#endif
}

#pragma endregion

#pragma region Connect/Disconnect

/****************************************************************

   Class : SerializationManager

   Method : ConnectBufferPack

   Parameters:
			Input:
				clientID - client ID
				serverDescr - server description

			Output
				packageSize - size of package

   Return : Pointer to package buffer

   Description : Serialize connect request

*****************************************************************/
char * SerializationManager :: ConnectBufferPack(unsigned int clientID, PSERVER_DESCRIPTION serverDescr, int * packageSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectBufferPack. Start");
	#endif
		
	// Create connect command request structure
	PCOMMAND_REQUEST_RESPONSE connectRequest = NULL;

	if (serverDescr) 
		connectRequest = CreateRequestResponse(CMD_CONNECT, REQUEST_CMD, serverDescr -> serverID, clientID);

	// Package pointer
	char * package = NULL;

	try
	{
		if (connectRequest)
		{
			// Set parameters count
			connectRequest -> parameters -> paramCount = 1;

			// Pack server description
			connectRequest -> parameters -> paramList[0] = PackServerDescription(serverDescr, INPUT_CMD_DATA);

			// Serialize request
			package = PackCommandRequestResponse(connectRequest, packageSize);

			// Delete request structure
			connectRequest = DeleteRequestResponse(connectRequest);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectBufferPack. Request successfully serialized!");	
			#endif
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectBufferPack. Done");
		#endif

		return package;
	}
	catch(...)
	{
		if (package)
			free(package);

		if (connectRequest)
			connectRequest = DeleteRequestResponse(connectRequest);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectBufferPack. Error of connection request serialization!");
			WriteToLog("SerializationManager : ConnectBufferPack. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : ConnectBufferPack

   Parameters:
			Input:
				serverID - server ID
				clientDescription - client description

			Output
				packageSize - size of package

   Return : Pointer to package buffer

   Description : Serialize connect response

*****************************************************************/
char * SerializationManager :: ConnectBufferPack(unsigned int serverID, PCLIENT_DESCRIPTION clientDescription, int * packageSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectBufferPack. Start");
	#endif
		
	// Create connect command response structure
	PCOMMAND_REQUEST_RESPONSE connectResponse = NULL;
	
	if (clientDescription)
		connectResponse = CreateRequestResponse(CMD_CONNECT, RESPONSE_CMD, clientDescription -> clientID, serverID);

	// Package pointer
	char * package = NULL;

	try
	{
		if (connectResponse)
		{
			// Set parameters count
			connectResponse -> parameters -> paramCount = 1;

			// Pack client ID
			connectResponse -> parameters -> paramList[0] = PackClientDescription(clientDescription, RETURN_CMD_DATA);

			// Serialize request
			package = PackCommandRequestResponse(connectResponse, packageSize);

			// Delete response structure
			connectResponse = DeleteRequestResponse(connectResponse);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectBufferPack. Response successfully serialized!");	
			#endif
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectBufferPack. Done");
		#endif

		return package;
	}
	catch(...)
	{
		if (package)
			free(package);

		if (connectResponse)
			connectResponse = DeleteRequestResponse(connectResponse);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectBufferPack. Error of connection request serialization!");
			WriteToLog("SerializationManager : ConnectBufferPack. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : ConnectInBufferUnpack

   Parameters :
			Input : 
				package - source data buffer
				packageSize - package size
			
			Output:
				serverDecrs - server description

   Return : server ID

   Description : Deserialize connect response

*****************************************************************/
unsigned int SerializationManager :: ConnectInBufferUnpack(char * package, int packageSize, PSERVER_DESCRIPTION serverDecrs)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectInBufferUnpack. Start");
	#endif

	// Deserialize request
	PCOMMAND_REQUEST_RESPONSE connectRequest = UnpackCommandRequestResponse(package, packageSize);

	try
	{
		// Validate request
		if ((connectRequest) &&	(connectRequest -> header) && (connectRequest -> parameters) &&
			(connectRequest -> header -> commandCode == CMD_CONNECT) &&
			(connectRequest -> header -> commandType == REQUEST_CMD) &&
			(connectRequest -> parameters -> paramCount == 1) &&
			(connectRequest -> parameters -> paramList[0]))
		{
			// Get server description
			PSERVER_DESCRIPTION serverDescription = UnpackServerDescription(connectRequest -> parameters -> paramList[0]);
			if ((serverDescription) && (serverDecrs))
			{
				memcpy(serverDecrs, serverDescription, sizeof(SERVER_DESCRIPTION));
				free(serverDescription);
			}
			
			unsigned int clientID = connectRequest -> header -> recipientID;

			connectRequest = DeleteRequestResponse(connectRequest);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectInBufferUnPack. Done");
			#endif

			return clientID;
		}
		else 
		{
			if (connectRequest)
				connectRequest = DeleteRequestResponse(connectRequest);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectInBufferUnPack. Wrong source buffer structure!");
				WriteToLog("SerializationManager : ConnectInBufferUnPack. Done");
			#endif

			return SERIALIZE_DATA_ERROR;
		}
	}
	catch(...)
	{
		if (connectRequest)
			connectRequest = DeleteRequestResponse(connectRequest);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectInBufferUnPack. Error of data deserialization!");
			WriteToLog("SerializationManager : ConnectInBufferUnPack. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : ConnectRetBufferUnPack

   Parameters :
			Input : 
				package - source data buffer
				packageSize - package size

	Return : pointer to client description structure

   Description : Deserialize connect response buffer

*****************************************************************/
PCLIENT_DESCRIPTION SerializationManager :: ConnectRetBufferUnpack(char * package, int packageSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectRetBufferUnPack. Start");
	#endif

	// Deserialize request
	PCOMMAND_REQUEST_RESPONSE connectResponse = UnpackCommandRequestResponse(package, packageSize);

	try
	{
		// Validate request
		if ((connectResponse) && (connectResponse -> header) && (connectResponse -> parameters) &&
			(connectResponse -> header -> commandCode == CMD_CONNECT) &&
			(connectResponse -> header -> commandType == RESPONSE_CMD) &&
			(connectResponse -> parameters -> paramCount == 1) &&
			(connectResponse -> parameters -> paramList[0]))
		{
			// Deserialize client description
			PCLIENT_DESCRIPTION clientDescription = UnpackClientDescription(connectResponse -> parameters -> paramList[0]);
			clientDescription -= dllUserCheckResult;

			connectResponse = DeleteRequestResponse(connectResponse);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectRetBufferUnPack. Done");
			#endif

			return clientDescription;
		}
		else 
		{
			if (connectResponse)
				connectResponse = DeleteRequestResponse(connectResponse);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectRetBufferUnPack. Wrong source buffer structure!");
				WriteToLog("SerializationManager : ConnectRetBufferUnPack. Done");
			#endif

			return NULL;
		}
	}
	catch(...)
	{
		if (connectResponse)
			connectResponse = DeleteRequestResponse(connectResponse);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectRetBufferUnPack. Error of data deserialization!");
			WriteToLog("SerializationManager : ConnectRetBufferUnPack. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : ConnectToReqBufferPack

   Parameters:
			Input:
				clientID - client ID
				gServerID - global server ID
				serverID - server ID
				serverType - server type

			Output
				packageSize - size of package

   Return : Pointer to package buffer

   Description : Serialize connect request

*****************************************************************/
char * SerializationManager :: ConnectToReqBufferPack(unsigned int clientID, unsigned int gServerID, unsigned int serverID, int serverType, int *packageSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectToReqBufferPack. Start");
	#endif
		
	// Create connect command request structure
	PCOMMAND_REQUEST_RESPONSE connectRequest = CreateRequestResponse(CMD_CONNECT, REQUEST_CMD, clientID, gServerID);

	// Package pointer
	char * package = NULL;

	try
	{
		if (connectRequest)
		{
			// Set parameters count
			connectRequest -> parameters -> paramCount = 2;

			// Pack remote server ID
			connectRequest -> parameters -> paramList[0] = PackDWORD(serverID, INPUT_CMD_DATA);

			// Pack server type
			connectRequest -> parameters -> paramList[1] = PackDWORD(serverType, INPUT_CMD_DATA);

			// Serialize request
			package = PackCommandRequestResponse(connectRequest, packageSize);

			// Delete request structure
			connectRequest = DeleteRequestResponse(connectRequest);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectToReqBufferPack. Request successfully serialized!");	
			#endif
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectToReqBufferPack. Done");
		#endif

		return package;
	}
	catch(...)
	{
		if (package)
			free(package);

		if (connectRequest)
			connectRequest = DeleteRequestResponse(connectRequest);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectToReqBufferPack. Error of connection request serialization!");
			WriteToLog("SerializationManager : ConnectToReqBufferPack. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : ConnectToReqBufferPack

   Parameters:
			Input:
				serverID - server ID
				clientID - client ID
				ipAddress - IP
				port - port

			Output
				packageSize - size of package

   Return : Pointer to package buffer

   Description : Serialize connect request

*****************************************************************/
char * SerializationManager :: ConnectToReqBufferPack(unsigned int serverID, unsigned int clientID, char * ipAddress, unsigned int port, int *packageSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectToReqBufferPack. Start");
	#endif
		
	// Create connect command response structure
	PCOMMAND_REQUEST_RESPONSE connectResponse = CreateRequestResponse(CMD_CONNECT, REQUEST_CMD, serverID, clientID);

	// Package pointer
	char * package = NULL;

	try
	{
		if (connectResponse)
		{
			// Set parameters count
			connectResponse -> parameters -> paramCount = 2;

			// Pack remote server IP
			if (ipAddress)
				connectResponse -> parameters -> paramList[0] = PackString(ipAddress, RETURN_CMD_DATA);
			else
				connectResponse -> parameters -> paramList[0] = PackString("WRONG", RETURN_CMD_DATA);

			// Pack port
			connectResponse -> parameters -> paramList[1] = PackDWORD(port, RETURN_CMD_DATA);

			// Serialize response
			package = PackCommandRequestResponse(connectResponse, packageSize);

			// Delete response structure
			connectResponse = DeleteRequestResponse(connectResponse);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectToReqBufferPack. Request successfully serialized!");	
			#endif
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectToReqBufferPack. Done");
		#endif

		return package;
	}
	catch(...)
	{
		if (package)
			free(package);

		if (connectResponse)
			connectResponse = DeleteRequestResponse(connectResponse);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectToReqBufferPack. Error of connection request serialization!");
			WriteToLog("SerializationManager : ConnectToReqBufferPack. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : ConnectToRetBufferPack

   Parameters:
			Input:
				serverID - server ID
				clientID - client ID
				ipAddress - IP
				port - port

			Output
				packageSize - size of package

   Return : Pointer to package buffer

   Description : Serialize connect response

*****************************************************************/
char * SerializationManager :: ConnectToRetBufferPack(unsigned int serverID, unsigned int clientID, char * ipAddress, unsigned int port, int *packageSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectToRetBufferPack. Start");
	#endif
		
	// Create connect command response structure
	PCOMMAND_REQUEST_RESPONSE connectResponse = CreateRequestResponse(CMD_CONNECT, RESPONSE_CMD, serverID, clientID);

	// Package pointer
	char * package = NULL;

	try
	{
		if (connectResponse)
		{
			// Set parameters count
			connectResponse -> parameters -> paramCount = 2;

			// Pack remote server IP
			if (ipAddress)
				connectResponse -> parameters -> paramList[0] = PackString(ipAddress, RETURN_CMD_DATA);
			else
				connectResponse -> parameters -> paramList[0] = PackString("WRONG", RETURN_CMD_DATA);

			// Pack port
			connectResponse -> parameters -> paramList[1] = PackDWORD(port, RETURN_CMD_DATA);

			// Serialize response
			package = PackCommandRequestResponse(connectResponse, packageSize);

			// Delete response structure
			connectResponse = DeleteRequestResponse(connectResponse);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectToRetBufferPack. Response successfully serialized!");	
			#endif
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectToRetBufferPack. Done");
		#endif

		return package;
	}
	catch(...)
	{
		if (package)
			free(package);

		if (connectResponse)
			connectResponse = DeleteRequestResponse(connectResponse);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectToRetBufferPack. Error of connection response serialization!");
			WriteToLog("SerializationManager : ConnectToRetBufferPack. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : ConnectToReqBufferUnpack

   Parameters:
			Input:
				package - pointer to package buffer
				packageSize - size of package

			Output:
				serverID - server ID
				serverType - server type

   Return : Error code

   Description : Deserialize connect to request

*****************************************************************/
int SerializationManager :: ConnectToReqBufferUnpack(char * package, int packageSize, int * serverID, int * serverType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Start");
	#endif

	// Deserialize request
	PCOMMAND_REQUEST_RESPONSE connectRequest = UnpackCommandRequestResponse(package, packageSize);

	try
	{
		// Validate request
		if ((connectRequest) &&	(connectRequest -> header) && (connectRequest -> parameters) &&
			(connectRequest -> header -> commandCode == CMD_CONNECT) &&
			(connectRequest -> header -> commandType == REQUEST_CMD) &&
			(connectRequest -> parameters -> paramCount == 2) &&
			(connectRequest -> parameters -> paramList[0]) &&
			(connectRequest -> parameters -> paramList[1]))
		{
			// Get server ID
			*serverID = UnpackDWORD(connectRequest -> parameters -> paramList[0]);

			// Get server type
			*serverType = UnpackDWORD(connectRequest -> parameters -> paramList[1]);

			connectRequest = DeleteRequestResponse(connectRequest);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Done");
			#endif

			return SERIALIZE_DATA_SUCCESS;
		}
		else 
		{
			if (connectRequest)
				connectRequest = DeleteRequestResponse(connectRequest);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Wrong source buffer structure!");
				WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Done");
			#endif

			return SERIALIZE_DATA_ERROR;
		}
	}
	catch(...)
	{
		if (connectRequest)
			connectRequest = DeleteRequestResponse(connectRequest);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Error of data deserialization!");
			WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : ConnectToReqBufferUnpack

   Parameters:
			Input:
				package - pointer to package buffer
				packageSize - size of package

			Output:
				ipAddress - IP
				port - port

   Return : Error code

   Description : Deserialize connect to request

*****************************************************************/
int SerializationManager :: ConnectToReqBufferUnpack(char * package, int packageSize, char * ipAddress, unsigned int * port)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Start");
	#endif

	// Deserialize response
	PCOMMAND_REQUEST_RESPONSE connectResponse = UnpackCommandRequestResponse(package, packageSize);

	try
	{
		// Validate request
		if ((connectResponse) && (connectResponse -> header) && (connectResponse -> parameters) &&
			(connectResponse -> header -> commandCode == CMD_CONNECT) &&
			(connectResponse -> header -> commandType == REQUEST_CMD) &&
			(connectResponse -> parameters -> paramCount == 2) &&
			(connectResponse -> parameters -> paramList[0]) &&
			(connectResponse -> parameters -> paramList[1]))
		{
			// Get IP
			if (ipAddress)
			{
				char ipString[STR_VALUE_LEN] = "";
				UnpackString(connectResponse -> parameters -> paramList[0], ipString);
				strcpy(ipAddress, ipString);
			}

			// Get port
			*port = UnpackDWORD(connectResponse -> parameters -> paramList[1]);

			connectResponse = DeleteRequestResponse(connectResponse);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Done");
			#endif

			return SERIALIZE_DATA_SUCCESS;
		}
		else 
		{
			if (connectResponse)
				connectResponse = DeleteRequestResponse(connectResponse);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Wrong source buffer structure!");
				WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Done");
			#endif

			return SERIALIZE_DATA_ERROR;
		}
	}
	catch(...)
	{
		if (connectResponse)
			connectResponse = DeleteRequestResponse(connectResponse);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Error of data deserialization!");
			WriteToLog("SerializationManager : ConnectToReqBufferUnpack. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : ConnectToRetBufferUnpack

   Parameters:
			Input:
				package - pointer to package buffer
				packageSize - size of package

			Output:
				ipAddress - IP
				port - port

   Return : Error code

   Description : Deserialize connect to response

*****************************************************************/
int SerializationManager :: ConnectToRetBufferUnpack(char * package, int packageSize, char * ipAddress, unsigned int * port)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : ConnectToRetBufferUnpack. Start");
	#endif

	// Deserialize response
	PCOMMAND_REQUEST_RESPONSE connectResponse = UnpackCommandRequestResponse(package, packageSize);

	try
	{
		// Validate request
		if ((connectResponse) && (connectResponse -> header) && (connectResponse -> parameters) &&
			(connectResponse -> header -> commandCode == CMD_CONNECT) &&
			(connectResponse -> header -> commandType == RESPONSE_CMD) &&
			(connectResponse -> parameters -> paramCount == 2) &&
			(connectResponse -> parameters -> paramList[0]) &&
			(connectResponse -> parameters -> paramList[1]))
		{
			// Get IP
			if (ipAddress)
			{
				char ipString[STR_VALUE_LEN] = "";
				UnpackString(connectResponse -> parameters -> paramList[0], ipString);
				strcpy(ipAddress, ipString);
			}

			// Get port
			*port = UnpackDWORD(connectResponse -> parameters -> paramList[1]);

			connectResponse = DeleteRequestResponse(connectResponse);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectToRetBufferUnpack. Done");
			#endif

			return SERIALIZE_DATA_SUCCESS;
		}
		else 
		{
			if (connectResponse)
				connectResponse = DeleteRequestResponse(connectResponse);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : ConnectToRetBufferUnpack. Wrong source buffer structure!");
				WriteToLog("SerializationManager : ConnectToRetBufferUnpack. Done");
			#endif

			return SERIALIZE_DATA_ERROR;
		}
	}
	catch(...)
	{
		if (connectResponse)
			connectResponse = DeleteRequestResponse(connectResponse);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : ConnectToRetBufferUnpack. Error of data deserialization!");
			WriteToLog("SerializationManager : ConnectToRetBufferUnpack. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : DisconnectBufferPack

   Parameters:
			Input:
				commandType - command type
				clientID - client ID

			Output
				packageSize - size of package

   Return : Pointer to package buffer

   Description : Serialize disconnect request/response

*****************************************************************/
char * SerializationManager :: DisconnectBufferPack(int commandType, unsigned int senderID, unsigned int recipientID, int *packageSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DisconnectBufferPack. Start");
	#endif
		
	// Create connect command request structure
	PCOMMAND_REQUEST_RESPONSE disconnectRequest = CreateRequestResponse(CMD_DISCONNECT, commandType, senderID, recipientID);

	// Package pointer
	char * package = NULL;

	try
	{
		if (disconnectRequest)
		{
			// Serialize request
			package = PackCommandRequestResponse(disconnectRequest, packageSize);

			// Delete request structure
			disconnectRequest = DeleteRequestResponse(disconnectRequest);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : DisconnectBufferPack. Request successfully serialized!");	
			#endif
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : DisconnectBufferPack. Done");
		#endif

		return package;
	}
	catch(...)
	{
		if (package)
			free(package);

		if (disconnectRequest)
			disconnectRequest = DeleteRequestResponse(disconnectRequest);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : DisconnectBufferPack. Error of connection request serialization!");
			WriteToLog("SerializationManager : DisconnectBufferPack. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : DisconnectInBufferUnpack

   Parameters :
			Input : 
				commandType - command type
				package - source data buffer
				packageSize - package size

			Output:
				senderID - sender ID
				recipientID - recipient ID
			
   Return : Error code

   Description : Deserialize disconnect response buffer 

*****************************************************************/
int SerializationManager :: DisconnectInBufferUnpack(int commandType, char * package, int packageSize, int * senderID, int * recipientID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DisconnectInBufferUnpack. Start");
	#endif

	// Deserialize request
	PCOMMAND_REQUEST_RESPONSE disconnectRequest = UnpackCommandRequestResponse(package, packageSize);

	try
	{
		// Validate request
		if ((disconnectRequest) &&	(disconnectRequest -> header) && (disconnectRequest -> parameters) &&
			(disconnectRequest -> header -> commandCode == CMD_DISCONNECT) &&
			(disconnectRequest -> header -> commandType == commandType) &&
			(disconnectRequest -> parameters -> paramCount == 0))
		{
			if (senderID) *senderID = disconnectRequest -> header -> senderID;
			if (recipientID) *recipientID = disconnectRequest -> header -> recipientID;
			
			disconnectRequest = DeleteRequestResponse(disconnectRequest);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : DisconnectInBufferUnpack. Done");
			#endif

			return SERIALIZE_DATA_SUCCESS;
		}
		else 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : DisconnectInBufferUnpack. Wrong source buffer structure!");
				WriteToLog("SerializationManager : DisconnectInBufferUnpack. Done");
			#endif

			return SERIALIZE_DATA_ERROR;
		}
	}
	catch(...)
	{
		if (disconnectRequest)
			disconnectRequest = DeleteRequestResponse(disconnectRequest);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : DisconnectInBufferUnpack. Error of data deserialization!");
			WriteToLog("SerializationManager : DisconnectInBufferUnpack. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

#pragma endregion

#pragma region Command header

/****************************************************************

   Class : SerializationManager

   Method : CreateCommandHeader
      
   Return : Pointer to the command header structure

   Description : Creates empty command header

*****************************************************************/
PCOMMAND_HEADER SerializationManager :: CreateCommandHeader(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : CreateCommandHeader. Start");
	#endif
	
	PCOMMAND_HEADER cmdHeader = (PCOMMAND_HEADER)malloc(sizeof(COMMAND_HEADER));

	if (cmdHeader)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CreateCommandHeader. Command header successfully created!");
		#endif

		cmdHeader -> commandCode = 0;
		cmdHeader -> commandType = 0;
		cmdHeader -> senderID = 0;
		cmdHeader -> recipientID = 0;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		else
			WriteToLog("SerializationManager : CreateCommandHeader. Error of command header memory allocation!");
	
		WriteToLog("SerializationManager : CreateCommandHeader. Done");
	#endif

	return cmdHeader - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : CreateCommandHeader

   Parameters:
			Input:
				commandCode - type of command (command code)
				commandType - type of data (request/response)
				senderID - sender ID
				recipientID - recipient ID
      
   Return : Pointer to the command header structure

   Description : Creates empty command header

*****************************************************************/
PCOMMAND_HEADER SerializationManager :: CreateCommandHeader(int commandCode, int commandType, unsigned int senderID, unsigned int recipientID)
{
	PCOMMAND_HEADER cmdHeader = CreateCommandHeader();

	if (cmdHeader)
	{
		cmdHeader -> commandCode = commandCode;
		cmdHeader -> commandType = commandType;
		cmdHeader -> senderID = senderID;
		cmdHeader -> recipientID = recipientID;
	}

	return cmdHeader - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : DeleteCommandHeader
      
   Parameters:
			Input:
				header - pointer to the command header structure

   Return : Pointer to the command header structure

   Description : Deletes command header

*****************************************************************/
PCOMMAND_HEADER SerializationManager :: DeleteCommandHeader(PCOMMAND_HEADER header)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DeleteCommandHeader. Start");
	#endif
	
	if (header)
	{
		free(header);
		header = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : DeleteCommandHeader. Command header succesfully deleted!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DeleteCommandHeader. Done");
	#endif

	return header - dllUserCheckResult;
}

#pragma endregion

#pragma region Command parameter

/****************************************************************

   Class : SerializationManager

   Method : CreateCommandParameter
      
   Return : Pointer to the command parameter structure

   Description : Creates empty command parameter

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: CreateCommandParameter(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : CreateCommandParameter. Start");
	#endif
	
	PCOMMAND_PARAMETER cmdParameter = (PCOMMAND_PARAMETER)malloc(sizeof(COMMAND_PARAMETER));

	if (cmdParameter)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CreateCommandParameter. Command parameter successfully created!");
		#endif

		cmdParameter -> paramType = 0;
		cmdParameter -> paramDataType = 0;
		cmdParameter -> dataBufferSize = 0;
		cmdParameter -> dataBuffer = NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		else
			WriteToLog("SerializationManager : CreateCommandParameter. Error of command parameter memory allocation!");
	
		WriteToLog("SerializationManager : CreateCommandParameter. Done");
	#endif

	return cmdParameter - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : CreateCommandParameter

   Parameters:
			Input:
				paramType - type of parameter
				paramDataType - type of parameter data
				dataBufferSize - size of parameter data buffer
      
   Return : Pointer to the command parameter structure

   Description : Creates command parameter

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: CreateCommandParameter(int paramType, int paramDataType, int dataBufferSize)
{
	PCOMMAND_PARAMETER cmdParameter = CreateCommandParameter();

	if (cmdParameter)
	{
		cmdParameter -> paramType = paramType;
		cmdParameter -> paramDataType = paramDataType;
		
		if (dataBufferSize > 0)
		{
			cmdParameter -> dataBuffer = (char *)malloc(dataBufferSize);

			if (cmdParameter -> dataBuffer)
				cmdParameter -> dataBufferSize = dataBufferSize;
			else
				cmdParameter -> dataBufferSize = 0;
		}
		else
		{
			cmdParameter -> dataBufferSize = 0;
			cmdParameter -> dataBuffer = NULL;
		}
	}

	return cmdParameter - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : DeleteCommandParameter
      
   Parameters:
			Input:
				param - pointer to the command parameter structure

   Return : Pointer to the command parameter structure

   Description : Deletes command parameter

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: DeleteCommandParameter(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DeleteCommandParameter. Start");
	#endif
	
	if (param)
	{
		if (param -> dataBuffer)
		{
			free(param -> dataBuffer);
			param -> dataBuffer = NULL;
			param -> dataBufferSize = 0;
		}

		free(param);
		param = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : DeleteCommandParameter. Command parameter succesfully deleted!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DeleteCommandParameter. Done");
	#endif

	return param - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : GetCommandParameterSize
      
   Parameters:
			Input:
				param - pointer to the command parameter structure

   Return : Size of command parameter structure

   Description : Get size of command parameter

*****************************************************************/
int SerializationManager :: GetCommandParameterSize(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetCommandParameterSize. Start");
	#endif
	
	int size = 0;

	if (param)
	{
		size += sizeof(param -> paramType) + sizeof(param -> paramDataType) + sizeof(param -> dataBufferSize) + param -> dataBufferSize;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
	else
		WriteToLog("SerializationManager : GetCommandParameterSize. No command parameter!");

		WriteToLog("SerializationManager : GetCommandParameterSize. Done");
	#endif

	return size - dllUserCheckResult;
}

#pragma endregion

#pragma region Command parameter list

/****************************************************************

   Class : SerializationManager

   Method : CreateCommandParameterList
      
   Return : Pointer to the command parameter list structure

   Description : Creates empty command parameter list

*****************************************************************/
PCOMMAND_PARAMETER_LIST SerializationManager :: CreateCommandParameterList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : CreateCommandParameterList. Start");
	#endif
	
	PCOMMAND_PARAMETER_LIST cmdParameterList = (PCOMMAND_PARAMETER_LIST)malloc(sizeof(COMMAND_PARAMETER_LIST));

	if (cmdParameterList)
	{
		cmdParameterList -> paramCount = 0;

		for(int i = 0; i < MAX_PARAMETERS_COUNT; i++)
			cmdParameterList -> paramList[i] = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CreateCommandParameterList. Command parameter list successfully created!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		else
			WriteToLog("SerializationManager : CreateCommandParameterList. Error of command parameter list memory allocation!");
	
		WriteToLog("SerializationManager : CreateCommandParameterList. Done");
	#endif

	return cmdParameterList - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : CreateCommandParameterList

   Parameters:
			Input:
				size - size of list
      
   Return : Pointer to the command parameter list structure

   Description : Creates empty command parameter list

*****************************************************************/
PCOMMAND_PARAMETER_LIST SerializationManager :: CreateCommandParameterList(int size)
{
	PCOMMAND_PARAMETER_LIST cmdParameterList = CreateCommandParameterList();

	if (cmdParameterList)
	{
		cmdParameterList -> paramCount = size;

		for(int i = 0; i < cmdParameterList -> paramCount; i++)
			cmdParameterList -> paramList[i] = CreateCommandParameter();
	}

	return cmdParameterList - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : DeleteCommandParameterList
      
   Parameters:
			Input:
				param - pointer to the command parameter list structure

   Return : pointer to the command parameter list structure

   Description : Deletes command parameter list

*****************************************************************/
PCOMMAND_PARAMETER_LIST SerializationManager :: DeleteCommandParameterList(PCOMMAND_PARAMETER_LIST cmdParameterList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DeleteCommandParameterList. Start");
	#endif
	
	if (cmdParameterList)
	{
		for(int i = 0; i < cmdParameterList -> paramCount; i++)
			cmdParameterList -> paramList[i] = DeleteCommandParameter(cmdParameterList -> paramList[i]);

		free(cmdParameterList);
		cmdParameterList = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : DeleteCommandParameterList. Command parameter list succesfully deleted!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DeleteCommandParameterList. Done");
	#endif

	return cmdParameterList - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : GetCommandParameterSizeList
      
   Parameters:
			Input:
				param - pointer to the command parameter list structure

   Return : size of command parameter list

   Description : Get size of command parameter list

*****************************************************************/
int SerializationManager :: GetCommandParameterListSize(PCOMMAND_PARAMETER_LIST cmdParameterList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetCommandParameterListSize. Start");
	#endif
	
	int size = 0;

	if (cmdParameterList)
	{
		// Parameters count
		size += sizeof(cmdParameterList -> paramCount);

		// Get size of each parameter
		for (int i = 0; i < cmdParameterList -> paramCount; i++)
			size += GetCommandParameterSize(cmdParameterList -> paramList[i]);
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		else
			WriteToLog("SerializationManager : GetCommandParameterListSize. No command parameters list!");

		WriteToLog("SerializationManager : GetCommandParameterListSize. Done");
	#endif

	return size - dllUserCheckResult;
}

#pragma endregion

#pragma region Command request/response

/****************************************************************

   Class : SerializationManager

   Method : CreateRequestResponse
      
   Return : Pointer to the command request/response structure

   Description : Creates empty command request/response structure

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE SerializationManager :: CreateRequestResponse(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : CreateRequestResponse. Start");
	#endif
	
	PCOMMAND_REQUEST_RESPONSE cmdRequestResponse = (PCOMMAND_REQUEST_RESPONSE)malloc(sizeof(COMMAND_REQUEST_RESPONSE));

	if (cmdRequestResponse)
	{
		cmdRequestResponse -> header = CreateCommandHeader();

		cmdRequestResponse -> parameters = CreateCommandParameterList();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CreateRequestResponse. Command request/response successfully created!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		else
			WriteToLog("SerializationManager : CreateRequestResponse. Error of command request/response allocation!");
	
		WriteToLog("SerializationManager : CreateRequestResponse. Done");
	#endif

	return cmdRequestResponse - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : CreateRequestResponse

   Parameters:
			Input:
				commandType - type of command (command code)
				commandDataType - type of data (request/response)      
				serverID - server ID
				recipientID - recipient ID
   
   Return : Pointer to the command request/response structure

   Description : Creates empty command request/response structure

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE SerializationManager :: CreateRequestResponse(int commandType, int commandDataType, unsigned int senderID, unsigned int recipientID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : CreateRequestResponse. Start");
	#endif
	
	PCOMMAND_REQUEST_RESPONSE cmdRequestResponse = (PCOMMAND_REQUEST_RESPONSE)malloc(sizeof(COMMAND_REQUEST_RESPONSE));

	if (cmdRequestResponse)
	{
		cmdRequestResponse -> header = CreateCommandHeader(commandType, commandDataType, senderID, recipientID);

		cmdRequestResponse -> parameters = CreateCommandParameterList();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CreateRequestResponse. Command request/response successfully created!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		else
			WriteToLog("SerializationManager : CreateRequestResponse. Error of command request/response allocation!");
	
		WriteToLog("SerializationManager : CreateRequestResponse. Done");
	#endif

	return cmdRequestResponse - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : DeleteRequestResponse
      
   Parameters:
			Input:
				cmdReqResp - pointer to the command request/response

   Return : Pointer to the command request/response structure

   Description : Deletes command request/response

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE SerializationManager :: DeleteRequestResponse(PCOMMAND_REQUEST_RESPONSE cmdReqResp)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DeleteRequestResponse. Start");
	#endif
	
	if (cmdReqResp)
	{
		cmdReqResp -> header = DeleteCommandHeader(cmdReqResp -> header);

		cmdReqResp -> parameters = DeleteCommandParameterList(cmdReqResp -> parameters);

		free(cmdReqResp);
		cmdReqResp = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : DeleteRequestResponse. Command request/response succesfully deleted!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : DeleteRequestResponse. Done");
	#endif

	return cmdReqResp - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : GetCommandRequestResponseSize
      
   Parameters:
			Input:
				cmdReqResp - pointer to the command request/response
			
   Return : Command request/response size

   Description : Get command request/response size

*****************************************************************/
int SerializationManager :: GetCommandRequestResponseSize(PCOMMAND_REQUEST_RESPONSE cmdReqResp)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetCommandRequestResponseSize. Start");
	#endif

	int size = 0;

	if (cmdReqResp)
	{
		// Get size of header
		if (cmdReqResp -> header)
			size += sizeof(COMMAND_HEADER);
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : GetCommandRequestResponseSize. No command header");
		#endif

		// Get size of parameters list
		size += GetCommandParameterListSize(cmdReqResp -> parameters);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetCommandRequestResponseSize. Done");
	#endif

	return size - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : PackCommandRequestResponse
      
   Parameters:
			Input:
				cmdReqResp - pointer to the command request/response
			
			Output:
				packageSize - package size

   Return : Pointer to the command package buffer

   Description : Pack command request/response

*****************************************************************/
char * SerializationManager :: PackCommandRequestResponse(PCOMMAND_REQUEST_RESPONSE cmdReqResp, int * packageSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackCommandRequestResponse. Start");
	#endif

	// Check input parameters
	if ((cmdReqResp == NULL) || (packageSize == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackCommandRequestResponse. Wrong input parameters!");	
			WriteToLog("SerializationManager : PackCommandRequestResponse. Done");
		#endif

		return NULL;
	}

	// Get request/response size
	int size = GetCommandRequestResponseSize(cmdReqResp);
	
	// Result package buffer
	char * buffer = NULL;

	try
	{
		// Check size value
		if (size > 0)
		{
			// Create buffer
			buffer = (char *)malloc(size);

			// Check memory allocation result
			if (buffer == NULL)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackCommandRequestResponse. Error of memory allocation!");	
					WriteToLog("SerializationManager : PackCommandRequestResponse. Done");
				#endif

				return NULL;
			}

			// Set work pointer
			char * workData = buffer;

			// Pack command header
			if (cmdReqResp -> header)
			{
				memcpy(workData, cmdReqResp -> header, sizeof(COMMAND_HEADER));
				workData += sizeof(COMMAND_HEADER);
			}
			else
			{
				// Delete buffer
				free(buffer);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackCommandRequestResponse. No command header!");	
					WriteToLog("SerializationManager : PackCommandRequestResponse. Done");
				#endif

				return NULL;
			}

			// Pack parameters data
			if (cmdReqResp -> parameters)
			{
				// Pack parameters count
				memcpy(workData, &(cmdReqResp -> parameters -> paramCount), sizeof(cmdReqResp -> parameters -> paramCount));
				workData += sizeof(cmdReqResp -> parameters -> paramCount);

				// Pack each parameter
				for (int i = 0; i < cmdReqResp -> parameters -> paramCount; i++)
				{
					PCOMMAND_PARAMETER cmdParam = cmdReqResp -> parameters -> paramList[i];

					if (cmdParam)
					{
						// Pack parameter type
						memcpy(workData, &(cmdParam -> paramType), sizeof(cmdParam -> paramType));
						workData += sizeof(cmdParam -> paramType);

						// Pack parameter data type
						memcpy(workData, &(cmdParam -> paramDataType), sizeof(cmdParam -> paramDataType));
						workData += sizeof(cmdParam -> paramDataType);

						// Pack parameter data buffer size
						memcpy(workData, &(cmdParam -> dataBufferSize), sizeof(cmdParam -> dataBufferSize));
						workData += sizeof(cmdParam -> dataBufferSize);

						// Pack parameter data buffer
						if ((cmdParam -> dataBufferSize > 0) && (cmdParam -> dataBuffer))
						{
							memcpy(workData, cmdParam -> dataBuffer, cmdParam -> dataBufferSize);
							workData += cmdParam -> dataBufferSize;
						}
					}
				}
			}
		}
	}
	catch(...)
	{
		// Delete buffer
		if (buffer)	free(buffer);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackCommandRequestResponse. Data serialization error!");	
			WriteToLog("SerializationManager : PackCommandRequestResponse. Done");
		#endif

		return NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackCommandRequestResponse. Done");
	#endif

	*packageSize = size;
	return buffer - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackCommandRequestResponse
      
   Parameters:
			Input:
				package - pointer to the command package buffer
				packageSize - package size

   Return : Pointer to the command request/response

   Description : Unpack command request/response

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE SerializationManager :: UnpackCommandRequestResponse(char * package, int packageSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackCommandRequestResponse. Start");
	#endif

	// Check input data
	if ((package == NULL) || (packageSize < sizeof(COMMAND_HEADER)))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackCommandRequestResponse. Wrong input parameters!");	
			WriteToLog("SerializationManager : UnpackCommandRequestResponse. Done");
		#endif

		return NULL;
	}

	// Create empty request/response structure
	PCOMMAND_REQUEST_RESPONSE cmdReqResp = CreateRequestResponse();

	// Check memory allocation result
	if (cmdReqResp == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackCommandRequestResponse. Error of request/response memory allocation!");	
			WriteToLog("SerializationManager : UnpackCommandRequestResponse. Done");
		#endif

		return NULL;
	}

	try
	{
		// Set work pointer
		char * workData = package;

		// Unpack command header
		if (cmdReqResp -> header)
		{
			memcpy(cmdReqResp -> header, workData, sizeof(COMMAND_HEADER));
			workData += sizeof(COMMAND_HEADER);
		}

		// Unpack parameters data
		if ((cmdReqResp -> parameters) && (packageSize > sizeof(COMMAND_HEADER)))
		{
			// Unpack parameters count
			memcpy(&(cmdReqResp -> parameters -> paramCount), workData, sizeof(cmdReqResp -> parameters -> paramCount));
			workData += sizeof(cmdReqResp -> parameters -> paramCount);

			// Unpack each parameter
			for (int i = 0; i < cmdReqResp -> parameters -> paramCount; i++)
			{
				cmdReqResp -> parameters -> paramList[i] = CreateCommandParameter();
				PCOMMAND_PARAMETER cmdParam = cmdReqResp -> parameters -> paramList[i];

				if (cmdParam)
				{
					// Unpack parameter type
					memcpy(&(cmdParam -> paramType), workData, sizeof(cmdParam -> paramType));
					workData += sizeof(cmdParam -> paramType);

					// Unpack parameter data type
					memcpy(&(cmdParam -> paramDataType), workData, sizeof(cmdParam -> paramDataType));
					workData += sizeof(cmdParam -> paramDataType);

					// Unpack parameter data buffer size
					memcpy(&(cmdParam -> dataBufferSize), workData, sizeof(cmdParam -> dataBufferSize));
					workData += sizeof(cmdParam -> dataBufferSize);

					// Unpack parameter data buffer
					if (cmdParam -> dataBufferSize > 0)
					{
						// Create command data buffer
						cmdParam -> dataBuffer = (char *)malloc(cmdParam -> dataBufferSize);

						// Check allocation result
						if (cmdParam -> dataBuffer)
						{
							// Set parameter data
							memcpy(cmdParam -> dataBuffer, workData, cmdParam -> dataBufferSize);
							workData += cmdParam -> dataBufferSize;
						}
						else
						{
							workData += cmdParam -> dataBufferSize;
							cmdParam -> dataBufferSize = 0;
						}
					}
					else
						cmdParam -> dataBuffer = NULL;
				}
			}
		}
	}
	catch(...)
	{
		// Delete request response
		if (cmdReqResp)
			cmdReqResp = DeleteRequestResponse(cmdReqResp);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackCommandRequestResponse. Data deserialization error!");	
			WriteToLog("SerializationManager : UnpackCommandRequestResponse. Done");
		#endif

		return NULL;
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackCommandRequestResponse. Done");
	#endif

	return cmdReqResp - dllUserCheckResult;
}

/****************************************************************

   Class : SerializationManager

   Method : CheckCommand

   Parameters :
			Input : 
				package - source data buffer
				commandCode - command type

   Return : Error code

   Description : Check command buffer

*****************************************************************/
int SerializationManager :: CheckCommand(char * package, unsigned int commandCode)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : CheckCommand. Start");
	#endif

	// Validate source buffer
	if (!package) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Bad source buffer!");
		#endif

		return SERIALIZE_DATA_ERROR;
	}

	try
	{
		PCOMMAND_HEADER pHeader = (PCOMMAND_HEADER) package;

		// Validate command type
		if (pHeader -> commandCode != commandCode) 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : CheckCommand. Wrong command!");
			#endif

			return SERIALIZE_DATA_ERROR;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Done");
		#endif

		return SERIALIZE_DATA_SUCCESS;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Error of source buffer checking!");
			WriteToLog("SerializationManager : CheckCommand. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : CheckCommand

   Parameters :
			Input : 
				package - source data buffer
				commandCode - command code
				commandType - command type

   Return : Error code

   Description : Check command buffer

*****************************************************************/
int SerializationManager :: CheckCommand(char * package, unsigned int commandCode, unsigned int commandType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : CheckCommand. Start");
	#endif

	// Validate source buffer
	if (!package) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Bad source buffer!");
		#endif

		return SERIALIZE_DATA_ERROR;
	}

	try
	{
		PCOMMAND_HEADER pHeader = (PCOMMAND_HEADER) package;

		// Validate command type
		if ((pHeader -> commandCode != commandCode) ||
			(pHeader -> commandType != commandType))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : CheckCommand. Wrong command!");
			#endif

			return SERIALIZE_DATA_ERROR;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Done");
		#endif

		return SERIALIZE_DATA_SUCCESS;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Error of source buffer checking!");
			WriteToLog("SerializationManager : CheckCommand. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : CheckCommand

   Parameters :
			Input : 
				cmdReqResp - command request/response
				commandCode - command code

   Return : Error code

   Description : Check command buffer

*****************************************************************/
int SerializationManager :: CheckCommand(PCOMMAND_REQUEST_RESPONSE cmdReqResp, unsigned int commandCode)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : CheckCommand. Start");
	#endif

	// Validate source buffer
	if (!cmdReqResp) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Bad source buffer!");
		#endif

		return SERIALIZE_DATA_ERROR;
	}

	try
	{
		// Validate command type
		if (cmdReqResp -> header -> commandCode != commandCode)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : CheckCommand. Wrong command!");
			#endif

			return SERIALIZE_DATA_ERROR;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Done");
		#endif

		return SERIALIZE_DATA_SUCCESS;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Error of source buffer checking!");
			WriteToLog("SerializationManager : CheckCommand. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : CheckCommand

   Parameters :
			Input : 
				cmdReqResp - command request/response
				commandCode - command code
				commandType - command type

   Return : Error code

   Description : Check command buffer

*****************************************************************/
int SerializationManager :: CheckCommand(PCOMMAND_REQUEST_RESPONSE cmdReqResp, unsigned int commandCode, unsigned int commandType)
{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : CheckCommand. Start");
	#endif

	// Validate source buffer
	if (!cmdReqResp) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Bad source buffer!");
		#endif

		return SERIALIZE_DATA_ERROR;
	}

	try
	{
		// Validate command type
		if ((cmdReqResp -> header -> commandCode != commandCode) ||
			(cmdReqResp -> header -> commandType != commandType))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : CheckCommand. Wrong command!");
			#endif

			return SERIALIZE_DATA_ERROR;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Done");
		#endif

		return SERIALIZE_DATA_SUCCESS;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : CheckCommand. Error of source buffer checking!");
			WriteToLog("SerializationManager : CheckCommand. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : GetCommandCode

   Parameters :
			Input : 
				package - source data buffer

   Return : Command code

   Description : Get command code

*****************************************************************/
unsigned int SerializationManager :: GetCommandCode(char * package)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetCommandCode. Start");
	#endif

	// Validate source buffer
	if (!package) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetCommandCode. Bad source buffer!");
		#endif

		return SERIALIZE_DATA_ERROR;
	}

	try
	{
		PCOMMAND_HEADER pHeader = (PCOMMAND_HEADER) package;

		unsigned int commandCode = pHeader -> commandCode;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetCommandCode. Done");
		#endif

		return commandCode;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetCommandCode. Error of source buffer checking!");
			WriteToLog("SerializationManager : GetCommandCode. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : CheckCommand

   Parameters :
			Input : 
				package - source data buffer
				commandCode - command type

   Return : Error code

   Description : Check command buffer

*****************************************************************/
unsigned int SerializationManager :: GetCommandCode(PCOMMAND_REQUEST_RESPONSE cmdReqResp)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetCommandCode. Start");
	#endif

	// Validate source buffer
	if (!cmdReqResp) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetCommandCode. Bad source buffer!");
		#endif

		return SERIALIZE_DATA_ERROR;
	}

	try
	{
		unsigned int commandCode = cmdReqResp -> header -> commandCode;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetCommandCode. Done");
		#endif


		return commandCode;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetCommandCode. Error of source buffer checking!");
			WriteToLog("SerializationManager : GetCommandCode. Done");
		#endif

		return SERIALIZE_DATA_ERROR;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : EmptyCommandBufferPack

   Parameters :
			Output : 
				packageSize - package size
				commandCode - command type
				senderID - sender ID
				recipientID - recipient ID

   Return : command package buffer

   Description : Serialize empty command

*****************************************************************/
char * SerializationManager :: EmptyCommandBufferPack(int *packageSize, unsigned int senderID, unsigned int recipientID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : EmptyCommandBufferPack. Start");
	#endif
		
	// Create command request structure
	PCOMMAND_REQUEST_RESPONSE emptyRequest = CreateRequestResponse(CMD_EMPTY, RESPONSE_CMD, senderID, recipientID);

	// Package pointer
	char * package = NULL;

	try
	{
		if (emptyRequest)
		{
			// Serialize request
			package = PackCommandRequestResponse(emptyRequest, packageSize);

			// Delete request structure
			emptyRequest = DeleteRequestResponse(emptyRequest);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : EmptyCommandBufferPack. Request successfully serialized!");	
			#endif
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : EmptyCommandBufferPack. Done");
		#endif

		return package;
	}
	catch(...)
	{
		if (package)
			free(package);

		if (emptyRequest)
			emptyRequest = DeleteRequestResponse(emptyRequest);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : EmptyCommandBufferPack. Error of request serialization!");
			WriteToLog("SerializationManager : EmptyCommandBufferPack. Done");
		#endif

		return NULL;
	}
}

#pragma endregion

#pragma region Byte

/****************************************************************

   Class : SerializationManager

   Method : PackByte

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack one byte value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackByte(unsigned char value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackByte. Start");
	#endif

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, BYTE_DATA, sizeof(value));
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				memcpy(cmdParam -> dataBuffer, &value, cmdParam -> dataBufferSize);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackByte. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackByte. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackByte. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackByte. Serialization error!");
			WriteToLog("SerializationManager : PackByte. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackByte

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : one byte value

   Description : Unpack one byte value

*****************************************************************/
unsigned char SerializationManager :: UnpackByte(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackByte. Start");
	#endif
	
	// Result value
	unsigned char value;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == BYTE_DATA) && 
			(param -> dataBufferSize == sizeof(unsigned char)) &&
			(param -> dataBuffer))
		{
			// Get value
			memcpy(&value, param -> dataBuffer, param -> dataBufferSize);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackByte. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackByte. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackByte. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackByte. Serialization error!");
			WriteToLog("SerializationManager : UnpackByte. Done");
		#endif

		return value;
	}
}

#pragma endregion

#pragma region WORD

/****************************************************************

   Class : SerializationManager

   Method : PackWORD

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack WORD value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackWORD(short value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackWORD. Start");
	#endif

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, WORD_DATA, sizeof(value));
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				memcpy(cmdParam -> dataBuffer, &value, cmdParam -> dataBufferSize);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackWORD. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackWORD. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackWORD. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackWORD. Serialization error!");
			WriteToLog("SerializationManager : PackWORD. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackWORD

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : WORD value

   Description : Unpack one byte value

*****************************************************************/
short SerializationManager :: UnpackWORD(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackWORD. Start");
	#endif
	
	// Result value
	short value;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == WORD_DATA) && 
			(param -> dataBufferSize == sizeof(short)) &&
			(param -> dataBuffer))
		{
			// Get value
			memcpy(&value, param -> dataBuffer, param -> dataBufferSize);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackWORD. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackWORD. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackWORD. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackWORD. Serialization error!");
			WriteToLog("SerializationManager : UnpackWORD. Done");
		#endif

		return value;
	}
}

#pragma endregion

#pragma region DWORD

/****************************************************************

   Class : SerializationManager

   Method : PackDWORD

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack DWORD value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackDWORD(int value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackDWORD. Start");
	#endif

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, DWORD_DATA, sizeof(value));
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				memcpy(cmdParam -> dataBuffer, &value, cmdParam -> dataBufferSize);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackDWORD. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackDWORD. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackDWORD. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackDWORD. Serialization error!");
			WriteToLog("SerializationManager : PackDWORD. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackDWORD

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : DWORD value

   Description : Unpack one byte value

*****************************************************************/
int SerializationManager :: UnpackDWORD(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackDWORD. Start");
	#endif
	
	// Result value
	int value;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == DWORD_DATA) && 
			(param -> dataBufferSize == sizeof(int)) &&
			(param -> dataBuffer))
		{
			// Get value
			memcpy(&value, param -> dataBuffer, param -> dataBufferSize);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackDWORD. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackDWORD. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackDWORD. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackDWORD. Serialization error!");
			WriteToLog("SerializationManager : UnpackDWORD. Done");
		#endif

		return value;
	}
}

#pragma endregion

#pragma region Long

/****************************************************************

   Class : SerializationManager

   Method : PackLong

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack long value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackLong(long long value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackLong. Start");
	#endif

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, LONG_DATA, sizeof(value));
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				memcpy(cmdParam -> dataBuffer, &value, cmdParam -> dataBufferSize);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackLong. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackLong. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackLong. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackLong. Serialization error!");
			WriteToLog("SerializationManager : PackLong. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackLong

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Long value

   Description : Unpack long value

*****************************************************************/
long long SerializationManager :: UnpackLong(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackLong. Start");
	#endif
	
	// Result value
	long long value;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == LONG_DATA) && 
			(param -> dataBufferSize == sizeof(long long)) &&
			(param -> dataBuffer))
		{
			// Get value
			memcpy(&value, param -> dataBuffer, param -> dataBufferSize);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackLong. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackLong. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackLong. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackLong. Serialization error!");
			WriteToLog("SerializationManager : UnpackLong. Done");
		#endif

		return value;
	}
}

#pragma endregion

#pragma region Binary

/****************************************************************

   Class : SerializationManager

   Method : PackBinary

   Parameters:
			Input:
				value - value for packing
				size - value size
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack binary value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackBinary(unsigned char * value, int size, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackBinary. Start");
	#endif

	// Check input data
	if ((value == NULL) || (size <= 0))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackBinary. Wrong input data!");
			WriteToLog("SerializationManager : PackBinary. Done");
		#endif

		return CreateCommandParameter(paramType, BINARY_DATA, 0);
	}

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, BINARY_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				memcpy(cmdParam -> dataBuffer, value, size);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackBinary. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackBinary. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackBinary. Wrong command parameter!");

			WriteToLog("SerializationManager : PackBinary. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackBinary. Serialization error!");
			WriteToLog("SerializationManager : PackBinary. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackBinary

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Binary value

   Description : Unpack binary value

*****************************************************************/
unsigned char *  SerializationManager :: UnpackBinary(PCOMMAND_PARAMETER param, int * size)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackBinary. Start");
	#endif
	
	// Result value
	unsigned char * value = NULL;

	try
	{
		// Check command parameter
		if ((size) && (param) && 
			(param -> paramDataType == BINARY_DATA) && 
			(param -> dataBufferSize > 0) &&
			(param -> dataBuffer))
		{
			// Allocate memory for binary buffer
			value = (unsigned char *)malloc(param -> dataBufferSize);

			// Check memory allocation
			if (!value)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : UnpackBinary. Error of binary buffer memory allocation!");
					WriteToLog("SerializationManager : UnpackBinary. Done");
				#endif

				return NULL;
			}

			memcpy(value, param -> dataBuffer, param -> dataBufferSize);
			*size = param -> dataBufferSize;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackBinary. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackBinary. Wrong command parameter!");
			}
			
			WriteToLog("SerializationManager : UnpackBinary. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackBinary. Serialization error!");
			WriteToLog("SerializationManager : UnpackBinary. Done");
		#endif
		*size = 0;
		return NULL;
	}
}

#pragma endregion

#pragma region String

/****************************************************************

   Class : SerializationManager

   Method : PackString

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack string value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackString(char * value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackString. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackString. Wrong input data!");
			WriteToLog("SerializationManager : PackString. Done");
		#endif

		return CreateCommandParameter(paramType, STRING_DATA, 0);
	}
	
	// Length of string
	int size = strlen(value) + 1;

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, STRING_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				memcpy(cmdParam -> dataBuffer, value, size);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackString. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackString. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackString. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackString. Serialization error!");
			WriteToLog("SerializationManager : PackString. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackString

   Parameters:
			Input:
				param - pointer to the command parameter structure

			Output:
				value - string value
     
   Return : size of string value

   Description : Unpack string value

*****************************************************************/
int SerializationManager :: UnpackString(PCOMMAND_PARAMETER param, char * value)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackString. Start");
	#endif
	
	int size = 0;

	try
	{
		// Check command parameter
		if ((value) && (param) && 
			(param -> paramDataType == STRING_DATA) && 
			(param -> dataBuffer) &&
			(param -> dataBufferSize > 0))
		{
			memcpy(value, param -> dataBuffer, param -> dataBufferSize);
			size = param -> dataBufferSize - 1;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackString. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackString. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackString. Done");
		#endif

		return size;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackString. Serialization error!");
			WriteToLog("SerializationManager : UnpackString. Done");
		#endif

		return 0;
	}
}

#pragma endregion

#pragma region Encrypted data

/****************************************************************

   Class : SerializationManager

   Method : PackEncrypted

   Parameters:
			Input:
				value - value for packing
				size - value size
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack encrypted value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackEncrypted(unsigned char * value, int size, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackEncrypted. Start");
	#endif

	// Check input data
	if ((value == NULL) || (size <= 0))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackEncrypted. Wrong input data!");
			WriteToLog("SerializationManager : PackEncrypted. Done");
		#endif

		return CreateCommandParameter(paramType, ENCRYPTED_DATA, 0);
	}

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, ENCRYPTED_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				memcpy(cmdParam -> dataBuffer, value, size);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackEncrypted. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackEncrypted. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackEncrypted. Wrong command parameter!");

			WriteToLog("SerializationManager : PackEncrypted. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackEncrypted. Serialization error!");
			WriteToLog("SerializationManager : PackEncrypted. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackEncrypted

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Encrypted value

   Description : Unpack encrypted value

*****************************************************************/
unsigned char *  SerializationManager :: UnpackEncrypted(PCOMMAND_PARAMETER param, int * size)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackEncrypted. Start");
	#endif
	
	// Result value
	unsigned char * value = NULL;

	try
	{
		// Check command parameter
		if ((size) && (param) && 
			(param -> paramDataType == ENCRYPTED_DATA) && 
			(param -> dataBufferSize > 0) &&
			(param -> dataBuffer))
		{
			// Allocate memory for binary buffer
			value = (unsigned char *)malloc(param -> dataBufferSize);

			// Check memory allocation
			if (!value)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : UnpackEncrypted. Error of binary buffer memory allocation!");
					WriteToLog("SerializationManager : UnpackEncrypted. Done");
				#endif

				return NULL;
			}

			memcpy(value, param -> dataBuffer, param -> dataBufferSize);
			*size = param -> dataBufferSize;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackEncrypted. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackBinary. Wrong command parameter!");
			}
			
			WriteToLog("SerializationManager : UnpackEncrypted. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackEncrypted. Serialization error!");
			WriteToLog("SerializationManager : UnpackEncrypted. Done");
		#endif
		*size = 0;
		return NULL;
	}
}

#pragma endregion

#pragma region Client description

/****************************************************************

   Class : SerializationManager

   Method : PackClientDescription

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack client description value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackClientDescription(PCLIENT_DESCRIPTION value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackClientDescription. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackClientDescription. Wrong input data!");
			WriteToLog("SerializationManager : PackClientDescription. Done");
		#endif

		return CreateCommandParameter(paramType, CLIENT_DESCRIPTION_DATA, 0);
	}

	int size = sizeof(CLIENT_DESCRIPTION);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, CLIENT_DESCRIPTION_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				char * workData = cmdParam -> dataBuffer;

				memcpy(workData, value, cmdParam -> dataBufferSize);
				workData += cmdParam -> dataBufferSize;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackClientDescription. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackClientDescription. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackClientDescription. Wrong command parameter!");

			WriteToLog("SerializationManager : PackClientDescription. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackClientDescription. Serialization error!");
			WriteToLog("SerializationManager : PackClientDescription. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackClientDescription

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Client description value

   Description : Unpack client description value

*****************************************************************/
PCLIENT_DESCRIPTION SerializationManager :: UnpackClientDescription(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackClientDescription. Start");
	#endif
	
	// Result value
	PCLIENT_DESCRIPTION value = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == CLIENT_DESCRIPTION_DATA) && 
			(param -> dataBufferSize == sizeof(CLIENT_DESCRIPTION)) &&
			(param -> dataBuffer))
		{
			// Get value
			value = (PCLIENT_DESCRIPTION)malloc(sizeof(CLIENT_DESCRIPTION));

			memcpy(value, param -> dataBuffer, param -> dataBufferSize);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackClientDescription. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackClientDescription. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackClientDescription. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackClientDescription. Serialization error!");
			WriteToLog("SerializationManager : UnpackClientDescription. Done");
		#endif

		return NULL;
	}	
}

#pragma endregion

#pragma region Server description

/****************************************************************

   Class : SerializationManager

   Method : PackServerDescription

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack server description value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackServerDescription(PSERVER_DESCRIPTION value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackServerDescription. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackServerDescription. Wrong input data!");
			WriteToLog("SerializationManager : PackServerDescription. Done");
		#endif

		return CreateCommandParameter(paramType, SERVER_DESCRIPTION_DATA, 0);
	}

	int size = sizeof(SERVER_DESCRIPTION);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, SERVER_DESCRIPTION_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				char * workData = cmdParam -> dataBuffer;

				memcpy(workData, value, cmdParam -> dataBufferSize);
				workData += cmdParam -> dataBufferSize;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackServerDescription. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackServerDescription. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackServerDescription. Wrong command parameter!");

			WriteToLog("SerializationManager : PackServerDescription. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackServerDescription. Serialization error!");
			WriteToLog("SerializationManager : PackServerDescription. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackServerDescription

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Server description value

   Description : Unpack server description value

*****************************************************************/
PSERVER_DESCRIPTION SerializationManager :: UnpackServerDescription(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackServerDescription. Start");
	#endif
	
	// Result value
	PSERVER_DESCRIPTION value = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == SERVER_DESCRIPTION_DATA) && 
			(param -> dataBufferSize == sizeof(SERVER_DESCRIPTION)) &&
			(param -> dataBuffer))
		{
			// Get value
			value = (PSERVER_DESCRIPTION)malloc(sizeof(SERVER_DESCRIPTION));

			memcpy(value, param -> dataBuffer, param -> dataBufferSize);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackServerDescription. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackServerDescription. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackServerDescription. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackServerDescription. Serialization error!");
			WriteToLog("SerializationManager : UnpackServerDescription. Done");
		#endif

		return NULL;
	}	
}

#pragma endregion

#pragma region Client description list

/****************************************************************

   Class : SerializationManager

   Method : PackClientDescriptionList

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter list structure

   Description : Pack client description list value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackClientDescriptionList(PCLIENT_DESCRIPTION_LIST value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackClientDescriptionList. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackClientDescriptionList. Wrong input data!");
			WriteToLog("SerializationManager : PackClientDescriptionList. Done");
		#endif

		return CreateCommandParameter(paramType, CLIENT_DESCRIPTION_LIST_DATA, 0);
	}

	PCOMMAND_PARAMETER cmdParam = NULL;

	try
	{
		// Size of list computing
		int size = sizeof(value -> clientsCount);

		for(int i = 0; i < value -> clientsCount; i++)
			size += sizeof(CLIENT_DESCRIPTION);

		// Create command parameter
		cmdParam = CreateCommandParameter(paramType, CLIENT_DESCRIPTION_LIST_DATA, size);
		
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				char * workData = cmdParam -> dataBuffer;

				memcpy(workData, &(value -> clientsCount), sizeof(value -> clientsCount));
				workData += sizeof(value -> clientsCount);

				for(int i = 0; i < value -> clientsCount; i++)
				{
					memcpy(workData, value -> clientsList[i], sizeof(CLIENT_DESCRIPTION));
					workData += sizeof(CLIENT_DESCRIPTION);
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackClientDescriptionList. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackClientDescriptionList. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackClientDescriptionList. Wrong command parameter!");

			WriteToLog("SerializationManager : PackClientDescriptionList. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackClientDescriptionList. Serialization error!");
			WriteToLog("SerializationManager : PackClientDescriptionList. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackClientDescriptionList

   Parameters:
			Input:
				param - pointer to the command parameter list structure
     
   Return : Client description list value

   Description : Unpack client description list value

*****************************************************************/
PCLIENT_DESCRIPTION_LIST SerializationManager :: UnpackClientDescriptionList(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackClientDescriptionList. Start");
	#endif
	
	// Result value
	PCLIENT_DESCRIPTION_LIST value = NULL; 
	
	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == CLIENT_DESCRIPTION_LIST_DATA) && 
			(param -> dataBuffer))
		{
			value = (PCLIENT_DESCRIPTION_LIST)malloc(sizeof(CLIENT_DESCRIPTION_LIST));

			// Get data
			char * workData = param -> dataBuffer;

			memcpy(&(value -> clientsCount), workData, sizeof(value -> clientsCount));
			workData += sizeof(value -> clientsCount);

			for(int i = 0; i < value -> clientsCount; i++)
			{
				memcpy(value -> clientsList[i], workData, sizeof(CLIENT_DESCRIPTION));
				workData += sizeof(CLIENT_DESCRIPTION);
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackClientDescriptionList. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackClientDescriptionList. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackClientDescriptionList. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackClientDescriptionList. Serialization error!");
			WriteToLog("SerializationManager : UnpackClientDescriptionList. Done");
		#endif

		return NULL;
	}	
}

#pragma endregion

#pragma region Server description list

/****************************************************************

   Class : SerializationManager

   Method : PackServerDescriptionList

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter list structure

   Description : Pack server description list value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackServerDescriptionList(PSERVER_DESCRIPTION_LIST value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackServerDescriptionList. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackServerDescriptionList. Wrong input data!");
			WriteToLog("SerializationManager : PackServerDescriptionList. Done");
		#endif

		return CreateCommandParameter(paramType, SERVER_DESCRIPTION_LIST_DATA, 0);
	}

	PCOMMAND_PARAMETER cmdParam = NULL;

	try
	{
		// Size of list computing
		int size = sizeof(value -> serversCount);

		for(int i = 0; i < value -> serversCount; i++)
			size += sizeof(SERVER_DESCRIPTION);

		// Create command parameter
		cmdParam = CreateCommandParameter(paramType, SERVER_DESCRIPTION_LIST_DATA, size);
		
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				char * workData = cmdParam -> dataBuffer;

				memcpy(workData, &(value -> serversCount), sizeof(value -> serversCount));
				workData += sizeof(value -> serversCount);

				for(int i = 0; i < value -> serversCount; i++)
				{
					memcpy(workData, value -> serversList[i], sizeof(SERVER_DESCRIPTION));
					workData += sizeof(SERVER_DESCRIPTION);
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackServerDescriptionList. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackServerDescriptionList. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackServerDescriptionList. Wrong command parameter!");

			WriteToLog("SerializationManager : PackServerDescriptionList. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackServerDescriptionList. Serialization error!");
			WriteToLog("SerializationManager : PackServerDescriptionList. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackServerDescriptionList

   Parameters:
			Input:
				param - pointer to the command parameter list structure
     
   Return : Server description list value

   Description : Unpack server description list value

*****************************************************************/
PSERVER_DESCRIPTION_LIST SerializationManager :: UnpackServerDescriptionList(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackServerDescriptionList. Start");
	#endif
	
	// Result value
	PSERVER_DESCRIPTION_LIST value = NULL; 
	
	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == SERVER_DESCRIPTION_LIST_DATA) && 
			(param -> dataBuffer))
		{
			value = (PSERVER_DESCRIPTION_LIST)malloc(sizeof(SERVER_DESCRIPTION_LIST));

			// Get data
			char * workData = param -> dataBuffer;

			memcpy(&(value -> serversCount), workData, sizeof(value -> serversCount));
			workData += sizeof(value -> serversCount);

			for(int i = 0; i < value -> serversCount; i++)
			{
				memcpy(value -> serversList[i], workData, sizeof(SERVER_DESCRIPTION));
				workData += sizeof(SERVER_DESCRIPTION);
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackServerDescriptionList. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackServerDescriptionList. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackServerDescriptionList. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackServerDescriptionList. Serialization error!");
			WriteToLog("SerializationManager : UnpackServerDescriptionList. Done");
		#endif

		return NULL;
	}	
}

#pragma endregion

#pragma region Preset

/****************************************************************

   Class : SerializationManager

   Method : PackPresetContainer

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack preset container value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackPresetContainer(PPRESET_CONTAINER value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackPresetContainer. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackPresetContainer. Wrong input data!");
			WriteToLog("SerializationManager : PackPresetContainer. Done");
		#endif

		return CreateCommandParameter(paramType, PRESET_CONTAINER_DATA, 0);
	}

	int size = GetUserContentSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, PRESET_CONTAINER_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Serialize user content container
				char * cntParam = cmdParam -> dataBuffer;
				PPRESET_CONTAINER content = value;

				memcpy(cntParam, &(content -> presetID), sizeof(content -> presetID));
				cntParam += sizeof(content -> presetID);

				int sLen = strlen(content -> presetName);
				if (sLen > NAME_LEN) sLen = NAME_LEN;
				memcpy(cntParam, &(sLen), sizeof(sLen));
				cntParam += sizeof(sLen);

				memcpy(cntParam, content -> presetName, sLen);
				cntParam += sLen;

				memcpy(cntParam, &(content -> userScreensCount), sizeof(content -> userScreensCount));
				cntParam += sizeof(content -> userScreensCount);

				// Serialize user screens
				for(int i = 0; i < content -> userScreensCount; i++)
				{
					memcpy(cntParam, &(content -> userScreens[i] -> screenID), sizeof(content -> userScreens[i] -> screenID));
					cntParam += sizeof(content -> userScreens[i] -> screenID);

					memcpy(cntParam, &(content -> userScreens[i] -> screenTypeID), sizeof(content -> userScreens[i] -> screenTypeID));
					cntParam += sizeof(content -> userScreens[i] -> screenTypeID);
			
					memcpy(cntParam, &(content -> userScreens[i] -> screenScope), sizeof(content -> userScreens[i] -> screenScope));
					cntParam += sizeof(content -> userScreens[i] -> screenScope);

					sLen = strlen(content -> userScreens[i] -> Name);
					if (sLen > NAME_LEN) sLen = NAME_LEN;
					memcpy(cntParam, &(sLen), sizeof(sLen));
					cntParam += sizeof(sLen);

					memcpy(cntParam, content -> userScreens[i] -> Name, sLen);
					cntParam += sLen;

					sLen = strlen(content -> userScreens[i] -> screenCaption);
					if (sLen > NAME_LEN) sLen = NAME_LEN;
					memcpy(cntParam, &(sLen), sizeof(sLen));
					cntParam += sizeof(sLen);

					memcpy(cntParam, content -> userScreens[i] -> screenCaption, sLen);
					cntParam += sLen;

					memcpy(cntParam, &(content -> userScreens[i] -> color), sizeof(content -> userScreens[i] -> color));
					cntParam += sizeof(content -> userScreens[i] -> color);
					memcpy(cntParam, &(content -> userScreens[i] -> heightPers), sizeof(content -> userScreens[i] -> heightPers));
					cntParam += sizeof(content -> userScreens[i] -> heightPers);
					memcpy(cntParam, &(content -> userScreens[i] -> heightPix), sizeof(content -> userScreens[i] -> heightPix));
					cntParam += sizeof(content -> userScreens[i] -> heightPix);
					memcpy(cntParam, &(content -> userScreens[i] -> widthPers), sizeof(content -> userScreens[i] -> widthPers));
					cntParam += sizeof(content -> userScreens[i] -> widthPers);
					memcpy(cntParam, &(content -> userScreens[i] -> widthPix), sizeof(content -> userScreens[i] -> widthPix));
					cntParam += sizeof(content -> userScreens[i] -> widthPix);
					memcpy(cntParam, &(content -> userScreens[i] -> locationX), sizeof(content -> userScreens[i] -> locationX));
					cntParam += sizeof(content -> userScreens[i] -> locationX);
					memcpy(cntParam, &(content -> userScreens[i] -> locationY), sizeof(content -> userScreens[i] -> locationY));
					cntParam += sizeof(content -> userScreens[i] -> locationY);
					memcpy(cntParam, &(content -> userScreens[i] -> locationXPers), sizeof(content -> userScreens[i] -> locationXPers));
					cntParam += sizeof(content -> userScreens[i] -> locationXPers);
					memcpy(cntParam, &(content -> userScreens[i] -> locationYPers), sizeof(content -> userScreens[i] -> locationYPers));
					cntParam += sizeof(content -> userScreens[i] -> locationYPers);
					memcpy(cntParam, &(content -> userScreens[i] -> scrObjCount), sizeof(content -> userScreens[i] -> scrObjCount));
					cntParam += sizeof(content -> userScreens[i] -> scrObjCount);

					// Serialize user screens objects
					for(int j = 0; j < content -> userScreens[i] -> scrObjCount; j++)
					{
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> objID), sizeof(content -> userScreens[i] -> screenObjects[j] -> objID));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> objID);

						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> objTypeId), sizeof(content -> userScreens[i] -> screenObjects[j] -> objTypeId));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> objTypeId);

						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> objScope), sizeof(content -> userScreens[i] -> screenObjects[j] -> objScope));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> objScope);

						sLen = strlen(content -> userScreens[i] -> screenObjects[j] -> objName);
						if (sLen > NAME_LEN) sLen = NAME_LEN;
						memcpy(cntParam, &(sLen), sizeof(sLen));
						cntParam += sizeof(sLen);

						memcpy(cntParam, content -> userScreens[i] -> screenObjects[j] -> objName, sLen);
						cntParam += sLen;

						sLen = strlen(content -> userScreens[i] -> screenObjects[j] -> objCaption);
						if (sLen > NAME_LEN) sLen = NAME_LEN;
						memcpy(cntParam, &(sLen), sizeof(sLen));
						cntParam += sizeof(sLen);

						memcpy(cntParam, content -> userScreens[i] -> screenObjects[j] -> objCaption, sLen);
						cntParam += sLen;

						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> heightPers), sizeof(content -> userScreens[i] -> screenObjects[j] -> heightPers));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> heightPers);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> heightPix), sizeof(content -> userScreens[i] -> screenObjects[j] -> heightPix));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> heightPix);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> widthPers), sizeof(content -> userScreens[i] -> screenObjects[j] -> widthPers));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> widthPers);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> widthPix), sizeof(content -> userScreens[i] -> screenObjects[j] -> widthPix));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> widthPix);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> locationX), sizeof(content -> userScreens[i] -> screenObjects[j] -> locationX));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> locationX);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> locationXPers), sizeof(content -> userScreens[i] -> screenObjects[j] -> locationXPers));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> locationXPers);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> locationY), sizeof(content -> userScreens[i] -> screenObjects[j] -> locationY));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> locationY);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> locationYPers), sizeof(content -> userScreens[i] -> screenObjects[j] -> locationYPers));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> locationYPers);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> order), sizeof(content -> userScreens[i] -> screenObjects[j] -> order));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> order);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> backgroundColor), sizeof(content -> userScreens[i] -> screenObjects[j] -> backgroundColor));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> backgroundColor);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> textColor), sizeof(content -> userScreens[i] -> screenObjects[j] -> textColor));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> textColor);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> fontSize), sizeof(content -> userScreens[i] -> screenObjects[j] -> fontSize));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> fontSize);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> lessonID), sizeof(content -> userScreens[i] -> screenObjects[j] -> lessonID));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> lessonID);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> questionID), sizeof(content -> userScreens[i] -> screenObjects[j] -> questionID));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> questionID);
						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> rightAnswerID), sizeof(content -> userScreens[i] -> screenObjects[j] -> rightAnswerID));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> rightAnswerID);

						sLen = strlen(content -> userScreens[i] -> screenObjects[j] -> strValue);
						if (sLen > STR_VALUE_LEN) sLen = STR_VALUE_LEN;
						memcpy(cntParam, &(sLen), sizeof(sLen));
						cntParam += sizeof(sLen);

						memcpy(cntParam, content -> userScreens[i] -> screenObjects[j] -> strValue, sLen);
						cntParam += sLen;

						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> imgValueSize), sizeof(content -> userScreens[i] -> screenObjects[j] -> imgValueSize));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> imgValueSize);

						if ((content -> userScreens[i] -> screenObjects[j] -> imgValueSize > 0) && 
							(content -> userScreens[i] -> screenObjects[j] -> imgValue))
						{
							memcpy(cntParam, content -> userScreens[i] -> screenObjects[j] -> imgValue, content -> userScreens[i] -> screenObjects[j] -> imgValueSize);
							cntParam += content -> userScreens[i] -> screenObjects[j] -> imgValueSize;
						}

						memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> textValueSize), sizeof(content -> userScreens[i] -> screenObjects[j] -> textValueSize));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> textValueSize);
				
						if ((content -> userScreens[i] -> screenObjects[j] -> textValueSize > 0) && 
							(content -> userScreens[i] -> screenObjects[j] -> textValue))
						{
							memcpy(cntParam, content -> userScreens[i] -> screenObjects[j] -> textValue, content -> userScreens[i] -> screenObjects[j] -> textValueSize);
							cntParam += content -> userScreens[i] -> screenObjects[j] -> textValueSize;
						}
				
						if (content -> userScreens[i] -> screenObjects[j] -> listValuesSet)
						{
							bool _null = false;
							memcpy(cntParam, &(_null), sizeof(_null));
							cntParam += sizeof(_null);

							memcpy(cntParam, &(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount), sizeof(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount));
							cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount);

							for(int k = 0; (k < content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount) && (k < LIST_VALUES_SET_MAX_SIZE); k++)
							{
								sLen = strlen(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> listValues[k]);
								if (sLen > STR_VALUE_LEN) sLen = STR_VALUE_LEN;
								memcpy(cntParam, &(sLen), sizeof(sLen));
								cntParam += sizeof(sLen);

								memcpy(cntParam, content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> listValues[k], sLen);
								cntParam += sLen;
							}
						}
						else
						{
							bool _null = true;
							memcpy(cntParam, &(_null), sizeof(_null));
							cntParam += sizeof(_null);
						}
					}
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackPresetContainer. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackPresetContainer. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackPresetContainer. Wrong command parameter!");

			WriteToLog("SerializationManager : PackPresetContainer. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackPresetContainer. Serialization error!");
			WriteToLog("SerializationManager : PackPresetContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackPresetContainer

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Preset container value

   Description : Unpack preset container value

*****************************************************************/
PPRESET_CONTAINER SerializationManager :: UnpackPresetContainer(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackPresetContainer. Start");
	#endif
	
	// Result value
	PPRESET_CONTAINER content = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == PRESET_CONTAINER_DATA) && 
			(param -> dataBuffer))
		{
			// Deserialize content container

			// Create container
			content = (PPRESET_CONTAINER)malloc(sizeof(PRESET_CONTAINER));
						
			char * cntParam = param -> dataBuffer;

			memcpy(&(content -> presetID), cntParam, sizeof(content -> presetID));
			cntParam += sizeof(content -> presetID);

			int sLen = 0;
			memcpy(&sLen, cntParam, sizeof(sLen));
			if (sLen > NAME_LEN) sLen = NAME_LEN;
			cntParam += sizeof(sLen);

			memcpy(content -> presetName, cntParam, sLen);
			cntParam += sLen;

			if (sLen >= NAME_LEN) sLen = NAME_LEN - 1;
			content -> presetName[sLen] = '\0';
			
			memcpy(&(content -> userScreensCount), cntParam, sizeof(content -> userScreensCount));
			cntParam += sizeof(content -> userScreensCount);
			
			
			for(int i = 0; i < content -> userScreensCount; i++)
			{
				content -> userScreens[i] = (PUSER_SCREEN)malloc(sizeof(USER_SCREEN));

				memcpy(&(content -> userScreens[i] -> screenID), cntParam,  sizeof(content -> userScreens[i] -> screenID));
				cntParam += sizeof(content -> userScreens[i] -> screenID);

				memcpy(&(content -> userScreens[i] -> screenTypeID), cntParam, sizeof(content -> userScreens[i] -> screenTypeID));
				cntParam += sizeof(content -> userScreens[i] -> screenTypeID);

				memcpy(&(content -> userScreens[i] -> screenScope), cntParam, sizeof(content -> userScreens[i] -> screenScope));
				cntParam += sizeof(content -> userScreens[i] -> screenScope);

				sLen = 0;
				memcpy(&sLen, cntParam, sizeof(sLen));
				if (sLen > NAME_LEN) sLen = NAME_LEN;
				cntParam += sizeof(sLen);

				memcpy(content -> userScreens[i] -> Name, cntParam, sLen);
				cntParam += sLen;

				if (sLen >= NAME_LEN) sLen = NAME_LEN - 1;
				content -> userScreens[i] -> Name[sLen] = '\0';
				
				sLen = 0;
				memcpy(&sLen, cntParam, sizeof(sLen));
				if (sLen > NAME_LEN) sLen = NAME_LEN;
				cntParam += sizeof(sLen);

				memcpy(content -> userScreens[i] -> screenCaption, cntParam, sLen);
				cntParam += sLen;

				if (sLen >= NAME_LEN) sLen = NAME_LEN - 1;
				content -> userScreens[i] -> screenCaption[sLen] = '\0';
				
				
				memcpy(&(content -> userScreens[i] -> color), cntParam, sizeof(content -> userScreens[i] -> color));
				cntParam += sizeof(content -> userScreens[i] -> color);
				memcpy(&(content -> userScreens[i] -> heightPers), cntParam, sizeof(content -> userScreens[i] -> heightPers));
				cntParam += sizeof(content -> userScreens[i] -> heightPers);
				memcpy(&(content -> userScreens[i] -> heightPix), cntParam, sizeof(content -> userScreens[i] -> heightPix));
				cntParam += sizeof(content -> userScreens[i] -> heightPix);
				memcpy(&(content -> userScreens[i] -> widthPers), cntParam, sizeof(content -> userScreens[i] -> widthPers));
				cntParam += sizeof(content -> userScreens[i] -> widthPers);
				memcpy(&(content -> userScreens[i] -> widthPix), cntParam, sizeof(content -> userScreens[i] -> widthPix));
				cntParam += sizeof(content -> userScreens[i] -> widthPix);
				memcpy(&(content -> userScreens[i] -> locationX), cntParam, sizeof(content -> userScreens[i] -> locationX));
				cntParam += sizeof(content -> userScreens[i] -> locationX);
				memcpy(&(content -> userScreens[i] -> locationY), cntParam, sizeof(content -> userScreens[i] -> locationY));
				cntParam += sizeof(content -> userScreens[i] -> locationY);
				memcpy(&(content -> userScreens[i] -> locationXPers), cntParam, sizeof(content -> userScreens[i] -> locationXPers));
				cntParam += sizeof(content -> userScreens[i] -> locationXPers);
				memcpy(&(content -> userScreens[i] -> locationYPers), cntParam, sizeof(content -> userScreens[i] -> locationYPers));
				cntParam += sizeof(content -> userScreens[i] -> locationYPers);
				memcpy(&(content -> userScreens[i] -> scrObjCount), cntParam, sizeof(content -> userScreens[i] -> scrObjCount));
				cntParam += sizeof(content -> userScreens[i] -> scrObjCount);

				// Deserialize user screens objects
				for(int j = 0; j < content -> userScreens[i] -> scrObjCount; j++)
				{
					content -> userScreens[i] -> screenObjects[j] = (PSCREEN_OBJECT)malloc(sizeof(SCREEN_OBJECT));

					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> objID), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> objID));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> objID);
					
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> objTypeId), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> objTypeId));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> objTypeId);

					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> objScope), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> objScope));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> objScope);

					sLen = 0;
					memcpy(&sLen, cntParam, sizeof(sLen));
					if (sLen > NAME_LEN) sLen = NAME_LEN;
					cntParam += sizeof(sLen);

					memcpy(content -> userScreens[i] -> screenObjects[j] -> objName, cntParam, sLen);
					cntParam += sLen;

					if (sLen >= NAME_LEN) sLen = NAME_LEN - 1;
					content -> userScreens[i] -> screenObjects[j] -> objName[sLen] = '\0';
					
					sLen = 0;
					memcpy(&sLen, cntParam, sizeof(sLen));
					if (sLen > NAME_LEN) sLen = NAME_LEN;
					cntParam += sizeof(sLen);

					memcpy(content -> userScreens[i] -> screenObjects[j] -> objCaption, cntParam, sLen);
					cntParam += sLen;

					if (sLen >= NAME_LEN) sLen = NAME_LEN - 1;
					content -> userScreens[i] -> screenObjects[j] -> objCaption[sLen] = '\0';
					
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> heightPers), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> heightPers));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> heightPers);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> heightPix), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> heightPix));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> heightPix);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> widthPers), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> widthPers));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> widthPers);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> widthPix), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> widthPix));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> widthPix);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> locationX), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> locationX));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> locationX);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> locationXPers), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> locationXPers));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> locationXPers);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> locationY), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> locationY));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> locationY);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> locationYPers), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> locationYPers));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> locationYPers);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> order), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> order));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> order);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> backgroundColor), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> backgroundColor));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> backgroundColor);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> textColor), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> textColor));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> textColor);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> fontSize), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> fontSize));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> fontSize);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> lessonID), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> lessonID));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> lessonID);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> questionID), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> questionID));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> questionID);
					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> rightAnswerID), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> rightAnswerID));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> rightAnswerID);

					sLen = 0;
					memcpy(&sLen, cntParam, sizeof(sLen));
					if (sLen > STR_VALUE_LEN) sLen = STR_VALUE_LEN;
					cntParam += sizeof(sLen);

					memcpy(content -> userScreens[i] -> screenObjects[j] -> strValue, cntParam, sLen);
					cntParam += sLen;

					if (sLen >= STR_VALUE_LEN) sLen = STR_VALUE_LEN - 1;
					content -> userScreens[i] -> screenObjects[j] -> strValue[sLen] = '\0';

					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> imgValueSize), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> imgValueSize));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> imgValueSize);

					if (content -> userScreens[i] -> screenObjects[j] -> imgValueSize > 0)
					{
						content -> userScreens[i] -> screenObjects[j] -> imgValue = malloc(content -> userScreens[i] -> screenObjects[j] -> imgValueSize);
						memcpy(content -> userScreens[i] -> screenObjects[j] -> imgValue, cntParam, content -> userScreens[i] -> screenObjects[j] -> imgValueSize);
						cntParam += content -> userScreens[i] -> screenObjects[j] -> imgValueSize;
					}
					else
						content -> userScreens[i] -> screenObjects[j] -> imgValue = NULL;

					memcpy(&(content -> userScreens[i] -> screenObjects[j] -> textValueSize), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> textValueSize));
					cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> textValueSize);

					if (content -> userScreens[i] -> screenObjects[j] -> textValueSize > 0)
					{
						content -> userScreens[i] -> screenObjects[j] -> textValue = (char *)malloc(content -> userScreens[i] -> screenObjects[j] -> textValueSize);
						memcpy(content -> userScreens[i] -> screenObjects[j] -> textValue, cntParam, content -> userScreens[i] -> screenObjects[j] -> textValueSize);
						cntParam += content -> userScreens[i] -> screenObjects[j] -> textValueSize;
					}
					else
						content -> userScreens[i] -> screenObjects[j] -> textValue = NULL;
					
					bool _null = true;
					memcpy(&(_null), cntParam, sizeof(_null));
					cntParam += sizeof(_null);

					if (!_null)
					{
						content -> userScreens[i] -> screenObjects[j] -> listValuesSet = (PLIST_VALUES_SET)malloc(sizeof(LIST_VALUES_SET));

						memcpy(&(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount), cntParam, sizeof(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount));
						cntParam += sizeof(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount);

						for(int k = 0; (k < content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount) && (k < LIST_VALUES_SET_MAX_SIZE); k++)
						{
							sLen = 0;
							memcpy(&sLen, cntParam, sizeof(sLen));
							if (sLen > STR_VALUE_LEN) sLen = STR_VALUE_LEN;
							cntParam += sizeof(sLen);

							memcpy(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> listValues[k], cntParam, sLen);
							cntParam += sLen;

							if (sLen >= STR_VALUE_LEN) sLen = STR_VALUE_LEN - 1;
							content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> listValues[k][sLen] = '\0';
						}
					}
					else
						content -> userScreens[i] -> screenObjects[j] -> listValuesSet = NULL;
				}
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackPresetContainer. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackPresetContainer. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackPresetContainer. Done");
		#endif

		return content;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackPresetContainer. Serialization error!");
			WriteToLog("SerializationManager : UnpackPresetContainer. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetUserContentSize

   Parameters :
			Input : 
				content - pointer to user content container

   Return : size of user content container

   Description : get size of user content container

*****************************************************************/
int SerializationManager :: GetUserContentSize(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetUserContentSize. Start");
	#endif

	// Validate container
	if (!content) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetUserContentSize. User content is empty");
		#endif

		return 0;
	}
	
	// Calculate size of container

	// Get length of preset name
	int sLen = strlen(content -> presetName);
	if (sLen > NAME_LEN) sLen = NAME_LEN;

	// Get size of preset info
	int size = sizeof(content -> presetID) + sizeof(content -> userScreensCount) + sizeof(sLen) + sLen;
		
	// Check screens
	for(int i = 0; i < content -> userScreensCount; i++)
	{
		// Calculate size of screen 
		size += sizeof(USER_SCREEN) - sizeof(PSCREEN_OBJECT)*MAX_SCR_OBJ_COUNT - 2*NAME_LEN;
		
		// Get size of screen name
		sLen = strlen(content -> userScreens[i] -> Name);
		if (sLen > NAME_LEN) sLen = NAME_LEN;
		size += sizeof(sLen) + sLen;

		// Get size of screen caption
		sLen = strlen(content -> userScreens[i] -> screenCaption);
		if (sLen > NAME_LEN) sLen = NAME_LEN;
		size += sizeof(sLen) + sLen;

		for(int j = 0; j < content -> userScreens[i] -> scrObjCount; j++)
		{
			// Get size of screen object
			size += sizeof(SCREEN_OBJECT) - sizeof(content -> userScreens[i] -> screenObjects[j] -> imgValue)
				                          - sizeof(content -> userScreens[i] -> screenObjects[j] -> textValue) 
										  - sizeof(content -> userScreens[i] -> screenObjects[j] -> listValuesSet)
										  - 2*NAME_LEN
										  - STR_VALUE_LEN;

			// Get size of object name
			sLen = strlen(content -> userScreens[i] -> screenObjects[j] -> objName);
			if (sLen > NAME_LEN) sLen = NAME_LEN;
			size += sizeof(sLen) + sLen;

			// Get size of object caption
			sLen = strlen(content -> userScreens[i] -> screenObjects[j] -> objCaption);
			if (sLen > NAME_LEN) sLen = NAME_LEN;
			size += sizeof(sLen) + sLen;

			// Get size of object string value
			sLen = strlen(content -> userScreens[i] -> screenObjects[j] -> strValue);
			if (sLen > STR_VALUE_LEN) sLen = STR_VALUE_LEN;
			size += sizeof(sLen) + sLen;

			// Check blob values
			if (content -> userScreens[i] -> screenObjects[j] -> imgValueSize > 0)
				size += content -> userScreens[i] -> screenObjects[j] -> imgValueSize;

			if (content -> userScreens[i] -> screenObjects[j] -> textValueSize > 0)
				size += content -> userScreens[i] -> screenObjects[j] -> textValueSize;

			// Check list values
			if (content -> userScreens[i] -> screenObjects[j] -> listValuesSet)
			{
				size += sizeof(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount);

				for(int k = 0; (k < content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount) && (k < LIST_VALUES_SET_MAX_SIZE); k++)
				{
					sLen = strlen(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> listValues[k]);
					if (sLen > STR_VALUE_LEN) sLen = STR_VALUE_LEN;
					size += sizeof(sLen) + sLen;
				}
			}

			size += sizeof(bool);
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetUserContentSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region User list

/****************************************************************

   Class : SerializationManager

   Method : PackUserList

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack user list value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackUserList(PUSER_LIST value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackUserList. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackUserList. Wrong input data!");
			WriteToLog("SerializationManager : PackUserList. Done");
		#endif

		return CreateCommandParameter(paramType, USER_LIST_DATA, 0);
	}

	int size = GetUserListContainerSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, USER_LIST_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Serialize user list container
				char * lstParam = cmdParam -> dataBuffer;

				memcpy(lstParam, &(value -> usersCount), sizeof(value -> usersCount));
				lstParam += sizeof(value -> usersCount);

				// Serialize users 
				for(int i = 0; (i < value -> usersCount) && (i < MAX_USERS_COUNT); i++)
					lstParam = PackSimpleUserDescriptor(lstParam, value -> users[i]);


				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackUserList. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackUserList. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackUserList. Wrong command parameter!");

			WriteToLog("SerializationManager : PackUserList. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackUserList. Serialization error!");
			WriteToLog("SerializationManager : PackUserList. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackUserList

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : User list container value

   Description : Unpack user list value

*****************************************************************/
PUSER_LIST SerializationManager :: UnpackUserList(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackUserList. Start");
	#endif
	
	// Result value
	PUSER_LIST userList = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == USER_LIST_DATA) && 
			(param -> dataBuffer))
		{
			// Deserialize user list container

			// Create container
			userList = (PUSER_LIST)malloc(sizeof(USER_LIST));
						
			// Serialize user list container
			char * lstParam = param -> dataBuffer;
			memcpy(&(userList -> usersCount), lstParam, sizeof(userList -> usersCount));
			lstParam += sizeof(userList -> usersCount);

			// Serialize users 
			for(int i = 0; (i < userList -> usersCount) && (i < MAX_USERS_COUNT); i++)
			{
				userList -> users[i] = UnPackSimpleUserDescriptor(lstParam);
				lstParam += GetSimpleUserDescriptorSize(userList -> users[i]);	
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackUserList. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackUserList. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackUserList. Done");
		#endif

		return userList;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackUserList. Serialization error!");
			WriteToLog("SerializationManager : UnpackUserList. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : PackSimpleUserDescriptor

   Parameters :
			Input : 
				lstParam - source data buffer pointer
				pUser - user descriptor

   Return : pointer to data buffer

   Description : Serialize user descriptor

*****************************************************************/
char * SerializationManager :: PackSimpleUserDescriptor(char * lstParam, PSIMPLE_USER_DESCRIPTOR pUser)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackSimpleUserDescriptor. Start");
	#endif

	try
	{
		memcpy(lstParam, &(pUser -> userID), sizeof(pUser -> userID));
		lstParam += sizeof(pUser -> userID);

		memcpy(lstParam, &(pUser -> encUserNameLen), sizeof(pUser -> encUserNameLen));
		lstParam += sizeof(pUser -> encUserNameLen);

		int sLen = pUser -> encUserNameLen;
		if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
		memcpy(lstParam, pUser -> encUserName, sLen);
		lstParam += sLen;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackSimpleUserDescriptor. Error of data serialization!");
			WriteToLog("SerializationManager : PackSimpleUserDescriptor. Done");
		#endif

		return lstParam;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackSimpleUserDescriptor. Done");
	#endif

	return lstParam;
}

/****************************************************************

   Class : SerializationManager

   Method : UnPackSimpleUserDescriptor

   Parameters :
			Input : 
				lstParam - source data buffer pointer
			
   Return : pointer to user descriptor

   Description : Deserialize user descriptor

*****************************************************************/
PSIMPLE_USER_DESCRIPTOR SerializationManager :: UnPackSimpleUserDescriptor(char * lstParam)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnPackSimpleUserDescriptor. Start");
	#endif

	PSIMPLE_USER_DESCRIPTOR pUser = NULL;

	try
	{
		pUser = (PSIMPLE_USER_DESCRIPTOR)malloc(sizeof(SIMPLE_USER_DESCRIPTOR));

		memcpy(&(pUser -> userID), lstParam, sizeof(pUser -> userID));
		lstParam += sizeof(pUser -> userID);
		
		memcpy(&(pUser -> encUserNameLen), lstParam, sizeof(pUser -> encUserNameLen));
		lstParam += sizeof(pUser -> encUserNameLen);

		int sLen = pUser -> encUserNameLen;
		if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
		memcpy(pUser -> encUserName, lstParam, sLen);
		lstParam += sLen;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnPackSimpleUserDescriptor. Error of data deserialization!");
			WriteToLog("SerializationManager : UnPackSimpleUserDescriptor. Done");
		#endif

		return NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnPackSimpleUserDescriptor. Done");
	#endif

	return pUser;
}

/****************************************************************

   Class : SerializationManager

   Method : GetSimpleUserDescriptorSize

   Parameters :
			Input : 
				pUser - pointer to user descriptor

   Return : user descriptor size

   Description : Calculate size of user descriptor

*****************************************************************/
int SerializationManager :: GetSimpleUserDescriptorSize(PSIMPLE_USER_DESCRIPTOR pUser)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetSimpleUserDescriptorSize. Start");
	#endif

	if (!pUser)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetSimpleUserDescriptorSize. Empty descriptor!");
		#endif

		return 0;
	}

	int size = sizeof(pUser -> userID) + sizeof(pUser -> encUserNameLen) + pUser -> encUserNameLen;
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetSimpleUserDescriptorSize. Done");
	#endif

	return size;
}

/****************************************************************

   Class : SerializationManager

   Method : GetUserListContainerSize

   Parameters :
			Input : 
				userList - pointer to user list container

   Return : user list container size

   Description : Calculate size of user list container

*****************************************************************/
int SerializationManager :: GetUserListContainerSize(PUSER_LIST userList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetUserListContainerSize. Start");
	#endif

	// Validate container
	if (!userList) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetUserListContainerSize. User list is empty");
		#endif

		return 0;
	}

	// Calculate size of container
	int size = sizeof(userList -> usersCount);

	for(int i = 0; (i < userList -> usersCount) && (i < MAX_USERS_COUNT); i++)
		size += GetSimpleUserDescriptorSize(userList -> users[i]);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetUserListContainerSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region User descriptor

/****************************************************************

   Class : SerializationManager

   Method : PackUserDescriptor

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack user descriptor value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackUserDescriptor(PUSER_DESCRIPTOR value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackUserList. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackUserList. Wrong input data!");
			WriteToLog("SerializationManager : PackUserList. Done");
		#endif

		return CreateCommandParameter(paramType, USER_DESCRIPTOR_DATA, 0);
	}

	int size = GetUserDescriptorSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, USER_DESCRIPTOR_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Serialize user container
				char * userParam = cmdParam -> dataBuffer;
				PUSER_DESCRIPTOR pUser = value;

				memcpy(userParam, &(pUser -> userID), sizeof(pUser -> userID));
				userParam += sizeof(pUser -> userID);

				memcpy(userParam, &(pUser -> encNameLen), sizeof(pUser -> encNameLen));
				userParam += sizeof(pUser -> encNameLen);

				int sLen = pUser -> encNameLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(userParam, pUser -> encName, sLen);
				userParam += sLen;

				memcpy(userParam, &(pUser -> encUserNameLen), sizeof(pUser -> encUserNameLen));
				userParam += sizeof(pUser -> encUserNameLen);

				sLen = pUser -> encUserNameLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(userParam, pUser -> encUserName, sLen);
				userParam += sLen;
						
				memcpy(userParam, &(pUser -> encEmailAddressLen), sizeof(pUser -> encEmailAddressLen));
				userParam += sizeof(pUser -> encEmailAddressLen);

				sLen = pUser -> encEmailAddressLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(userParam, pUser -> encEmailAddress, sLen);
				userParam += sLen;

				memcpy(userParam, &(pUser -> encPhoneNumberLen), sizeof(pUser -> encPhoneNumberLen));
				userParam += sizeof(pUser -> encPhoneNumberLen);

				sLen = pUser -> encPhoneNumberLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(userParam, pUser -> encPhoneNumber, sLen);
				userParam += sLen;

				memcpy(userParam, pUser -> lastLogOnDate, DATE_STR_LEN);
				userParam += DATE_STR_LEN;
						
				memcpy(userParam, &(pUser -> needStudy), sizeof(pUser -> needStudy));
				userParam += sizeof(pUser -> needStudy);

				memcpy(userParam, &(pUser -> eduCategotyID), sizeof(pUser -> eduCategotyID));
				userParam += sizeof(pUser -> eduCategotyID);

				memcpy(userParam, &(pUser -> eduQuestionRandom), sizeof(pUser -> eduQuestionRandom));
				userParam += sizeof(pUser -> eduQuestionRandom);

				memcpy(userParam, &(pUser -> randomEduCateg), sizeof(pUser -> randomEduCateg));
				userParam += sizeof(pUser -> randomEduCateg);
		
				memcpy(userParam, &(pUser -> pwdType), sizeof(pUser -> pwdType));
				userParam += sizeof(pUser -> pwdType);

				memcpy(userParam, &(pUser -> pwdAttemptsCount), sizeof(pUser -> pwdAttemptsCount));
				userParam += sizeof(pUser -> pwdAttemptsCount);
		
				memcpy(userParam, &(pUser -> maxPwdAttemptsCount), sizeof(pUser -> maxPwdAttemptsCount));
				userParam += sizeof(pUser -> maxPwdAttemptsCount);

				memcpy(userParam, &(pUser -> locked), sizeof(pUser -> locked));
				userParam += sizeof(pUser -> locked);

				memcpy(userParam, &(pUser -> pwdReseted), sizeof(pUser -> pwdReseted));
				userParam += sizeof(pUser -> pwdReseted);

				memcpy(userParam, &(pUser -> emailPwdReset), sizeof(pUser -> emailPwdReset));
				userParam += sizeof(pUser -> emailPwdReset);

				memcpy(userParam, &(pUser -> smsPwdReset), sizeof(pUser -> smsPwdReset));
				userParam += sizeof(pUser -> smsPwdReset);

				memcpy(userParam, &(pUser -> pwdResetPeriod), sizeof(pUser -> pwdResetPeriod));
				userParam += sizeof(pUser -> pwdResetPeriod);

				memcpy(userParam, pUser -> pwdResetDate, DATE_STR_LEN);
				userParam += DATE_STR_LEN;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackUserList. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackUserList. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackUserList. Wrong command parameter!");

			WriteToLog("SerializationManager : PackUserList. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackUserList. Serialization error!");
			WriteToLog("SerializationManager : PackUserList. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackUserDescriptor

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : User descriptor container value

   Description : Unpack user descriptor value

*****************************************************************/
PUSER_DESCRIPTOR SerializationManager :: UnpackUserDescriptor(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackUserDescriptor. Start");
	#endif
	
	// Result value
	PUSER_DESCRIPTOR pUser = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == USER_DESCRIPTOR_DATA) && 
			(param -> dataBuffer))
		{
			// Create container
			pUser = (PUSER_DESCRIPTOR)malloc(sizeof(USER_DESCRIPTOR));
						
			// Deserialize user container
			char * userParam = param -> dataBuffer;

			memcpy(&(pUser -> userID), userParam, sizeof(pUser -> userID));
			userParam += sizeof(pUser -> userID);

			memcpy(&(pUser -> encNameLen), userParam, sizeof(pUser -> encNameLen));
			userParam += sizeof(pUser -> encNameLen);

			int sLen = pUser -> encNameLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(pUser -> encName, userParam, sLen);
			userParam += sLen;

			memcpy(&(pUser -> encUserNameLen), userParam, sizeof(pUser -> encUserNameLen));
			userParam += sizeof(pUser -> encUserNameLen);

			sLen = pUser -> encUserNameLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(pUser -> encUserName, userParam, sLen);
			userParam += sLen;
						
			memcpy(&(pUser -> encEmailAddressLen), userParam, sizeof(pUser -> encEmailAddressLen));
			userParam += sizeof(pUser -> encEmailAddressLen);

			sLen = pUser -> encEmailAddressLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(pUser -> encEmailAddress, userParam, sLen);
			userParam += sLen;

			memcpy(&(pUser -> encPhoneNumberLen), userParam, sizeof(pUser -> encPhoneNumberLen));
			userParam += sizeof(pUser -> encPhoneNumberLen);

			sLen = pUser -> encPhoneNumberLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(pUser -> encPhoneNumber, userParam, sLen);
			userParam += sLen;

			memcpy(pUser -> lastLogOnDate, userParam, DATE_STR_LEN);
			userParam += DATE_STR_LEN;
						
			memcpy(&(pUser -> needStudy), userParam, sizeof(pUser -> needStudy));
			userParam += sizeof(pUser -> needStudy);

			memcpy(&(pUser -> eduCategotyID), userParam, sizeof(pUser -> eduCategotyID));
			userParam += sizeof(pUser -> eduCategotyID);

			memcpy(&(pUser -> eduQuestionRandom), userParam, sizeof(pUser -> eduQuestionRandom));
			userParam += sizeof(pUser -> eduQuestionRandom);

			memcpy(&(pUser -> randomEduCateg), userParam, sizeof(pUser -> randomEduCateg));
			userParam += sizeof(pUser -> randomEduCateg);
		
			memcpy(&(pUser -> pwdType), userParam, sizeof(pUser -> pwdType));
			userParam += sizeof(pUser -> pwdType);

			memcpy(&(pUser -> pwdAttemptsCount), userParam, sizeof(pUser -> pwdAttemptsCount));
			userParam += sizeof(pUser -> pwdAttemptsCount);
		
			memcpy(&(pUser -> maxPwdAttemptsCount), userParam, sizeof(pUser -> maxPwdAttemptsCount));
			userParam += sizeof(pUser -> maxPwdAttemptsCount);

			memcpy(&(pUser -> locked), userParam, sizeof(pUser -> locked));
			userParam += sizeof(pUser -> locked);

			memcpy(&(pUser -> pwdReseted), userParam, sizeof(pUser -> pwdReseted));
			userParam += sizeof(pUser -> pwdReseted);

			memcpy(&(pUser -> emailPwdReset), userParam, sizeof(pUser -> emailPwdReset));
			userParam += sizeof(pUser -> emailPwdReset);

			memcpy(&(pUser -> smsPwdReset), userParam, sizeof(pUser -> smsPwdReset));
			userParam += sizeof(pUser -> smsPwdReset);

			memcpy(&(pUser -> pwdResetPeriod), userParam, sizeof(pUser -> pwdResetPeriod));
			userParam += sizeof(pUser -> pwdResetPeriod);

			memcpy(pUser -> pwdResetDate, userParam, DATE_STR_LEN);
			userParam += DATE_STR_LEN;


			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackUserDescriptor. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackUserDescriptor. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackUserDescriptor. Done");
		#endif

		return pUser;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackUserDescriptor. Serialization error!");
			WriteToLog("SerializationManager : UnpackUserDescriptor. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetUserDescriptorSize

   Parameters :
			Input : 
				pUser - pointer to user descriptor

   Return : user descriptor size

   Description : Calculate size of user descriptor

*****************************************************************/
int SerializationManager :: GetUserDescriptorSize(PUSER_DESCRIPTOR pUser)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetUserDescriptorSize. Start");
	#endif

	if (!pUser)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetUserDescriptorSize. Empty descriptor!");
		#endif

		return 0;
	}

	int size = sizeof(USER_DESCRIPTOR) - 4*ENCRYPTED_DATA_SIZE;

	size += pUser -> encNameLen + pUser -> encUserNameLen + pUser -> encEmailAddressLen + pUser -> encPhoneNumberLen;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetUserDescriptorSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region Authentication container

/****************************************************************

   Class : SerializationManager

   Method : PackAuthContainer

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack authenticate container value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackAuthContainer(PAUTH_CONTAINER value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackAuthContainer. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackAuthContainer. Wrong input data!");
			WriteToLog("SerializationManager : PackAuthContainer. Done");
		#endif

		return CreateCommandParameter(paramType, AUTH_CONTAINER_DATA, 0);
	}

	int size = GetAuthContainerSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, AUTH_CONTAINER_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				char * authParam = cmdParam -> dataBuffer;
				PAUTH_CONTAINER authContainer = value;

				// Serialize container
				memcpy(authParam, &(authContainer -> authElementCount), sizeof(authContainer -> authElementCount));
				authParam += sizeof(authContainer -> authElementCount);

				// Serialize items 
				int sLen = 0;

				for(int i = 0; (i < authContainer -> authElementCount) && (i < MAX_SCR_OBJ_COUNT); i++)
				{
					memcpy(authParam, &(authContainer -> authElements[i] -> objectID), sizeof(authContainer -> authElements[i] -> objectID));
					authParam += sizeof(authContainer -> authElements[i] -> objectID);
			
					sLen = authContainer -> authElements[i] -> objectNameLen;
					if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
					memcpy(authParam, &(sLen), sizeof(sLen));
					authParam += sizeof(sLen);

					memcpy(authParam, authContainer -> authElements[i] -> objectName, sLen);
					authParam += sLen;

					memcpy(authParam, &(authContainer -> authElements[i] -> objectTypeID), sizeof(authContainer -> authElements[i] -> objectTypeID));
					authParam += sizeof(authContainer -> authElements[i] -> objectTypeID);

					sLen = authContainer -> authElements[i] -> objectValueLen;
					if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
					memcpy(authParam, &(sLen), sizeof(sLen));
					authParam += sizeof(sLen);

					memcpy(authParam, authContainer -> authElements[i] -> objectValue, sLen);
					authParam += sLen;
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackAuthContainer. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackAuthContainer. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackAuthContainer. Wrong command parameter!");

			WriteToLog("SerializationManager : PackAuthContainer. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackAuthContainer. Serialization error!");
			WriteToLog("SerializationManager : PackAuthContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackAuthContainer

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Authenticate container value

   Description : Unpack authenticate container value

*****************************************************************/
PAUTH_CONTAINER SerializationManager :: UnpackAuthContainer(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackAuthContainer. Start");
	#endif
	
	// Result value
	PAUTH_CONTAINER authContainer = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == AUTH_CONTAINER_DATA) && 
			(param -> dataBuffer))
		{
			char * authParam = param -> dataBuffer;

			// Create container
			authContainer = (PAUTH_CONTAINER)malloc(sizeof(AUTH_CONTAINER));
						
			// Deserialize container
			memcpy(&(authContainer -> authElementCount), authParam, sizeof(authContainer -> authElementCount));
			authParam += sizeof(authContainer -> authElementCount);

			// Deserialize items 
			int sLen = 0;

			for(int i = 0; (i < authContainer -> authElementCount) && (i < MAX_SCR_OBJ_COUNT); i++)
			{
				authContainer -> authElements[i] = (PAUTH_ELEMENT)malloc(sizeof(AUTH_ELEMENT));
				
				memcpy(&(authContainer -> authElements[i] -> objectID), authParam, sizeof(authContainer -> authElements[i] -> objectID));
				authParam += sizeof(authContainer -> authElements[i] -> objectID);
			
				sLen = 0;
				memcpy(&sLen, authParam, sizeof(sLen));
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				authParam += sizeof(sLen);
				
				authContainer -> authElements[i] -> objectNameLen = sLen;
				memcpy(authContainer -> authElements[i] -> objectName, authParam, sLen);
				authParam += sLen;

				memcpy(&(authContainer -> authElements[i] -> objectTypeID), authParam, sizeof(authContainer -> authElements[i] -> objectTypeID));
				authParam += sizeof(authContainer -> authElements[i] -> objectTypeID);

				sLen = 0;
				memcpy(&sLen, authParam, sizeof(sLen));
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				authParam += sizeof(sLen);
				
				authContainer -> authElements[i] -> objectValueLen = sLen;
				memcpy(authContainer -> authElements[i] -> objectValue, authParam, sLen);
				authParam += sLen;
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackAuthContainer. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackAuthContainer. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackAuthContainer. Done");
		#endif

		return authContainer;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackAuthContainer. Serialization error!");
			WriteToLog("SerializationManager : UnpackAuthContainer. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetAuthContainerSize

   Parameters :
			Input : 
				authContainer - pointer to authentication container

   Return : authentication container size

   Description : Get authentication container size

*****************************************************************/
int SerializationManager :: GetAuthContainerSize(PAUTH_CONTAINER authContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetAuthContainerSize. Start");
	#endif

	// Validate container
	if (!authContainer) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetAuthContainerSize. Authentication container is empty");
		#endif

		return 0;
	}

	// Calculate size of container
	int size = sizeof(authContainer -> authElementCount);
	
	for(int i = 0; (i < authContainer -> authElementCount) && (i < MAX_SCR_OBJ_COUNT); i++)
	{
		size += sizeof(authContainer -> authElements[i] -> objectID) + 
			    sizeof(authContainer -> authElements[i] -> objectTypeID) +
				sizeof(authContainer -> authElements[i] -> objectNameLen) + 
				sizeof(authContainer -> authElements[i] -> objectValueLen) +
				authContainer -> authElements[i] -> objectNameLen + 
				authContainer -> authElements[i] -> objectValueLen;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetAuthContainerSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region Answer container

/****************************************************************

   Class : SerializationManager

   Method : PackAnswerContainer

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack answer container value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackAnswerContainer(PANSWER_CONTAINER value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackAnswerContainer. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackAnswerContainer. Wrong input data!");
			WriteToLog("SerializationManager : PackAnswerContainer. Done");
		#endif

		return CreateCommandParameter(paramType, ANSWER_CONTAINER_DATA, 0);
	}

	int size = GetAnswerContainerSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, ANSWER_CONTAINER_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				char * eduParam = cmdParam -> dataBuffer;
				PANSWER_CONTAINER eduContainer = value;

				// Serialize container
				memcpy(eduParam, &(eduContainer -> answersCount), sizeof(eduContainer -> answersCount));
				eduParam += sizeof(eduContainer -> answersCount);

				for(int i = 0; (i < eduContainer -> answersCount) && (i < MAX_SCR_OBJ_COUNT); i++)
				{
					memcpy(eduParam, &(eduContainer -> answers[i] -> questionID), sizeof(eduContainer -> answers[i] -> questionID));
					eduParam += sizeof(eduContainer -> answers[i] -> questionID);

					memcpy(eduParam, &(eduContainer -> answers[i] -> rightAnswerID), sizeof(eduContainer -> answers[i] -> rightAnswerID));
					eduParam += sizeof(eduContainer -> answers[i] -> rightAnswerID);

					int sLen = strlen(eduContainer -> answers[i] -> answerValue);
					if (sLen > STR_VALUE_LEN) sLen = STR_VALUE_LEN;
					memcpy(eduParam, &(sLen), sizeof(sLen));
					eduParam += sizeof(sLen);

					memcpy(eduParam, eduContainer -> answers[i] -> answerValue, sLen);
					eduParam += sLen;
				}
				
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackAnswerContainer. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackAnswerContainer. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackAnswerContainer. Wrong command parameter!");

			WriteToLog("SerializationManager : PackAuthContainer. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackAnswerContainer. Serialization error!");
			WriteToLog("SerializationManager : PackAnswerContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackAnswerContainer

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Answer container value

   Description : Unpack answer container value

*****************************************************************/
PANSWER_CONTAINER SerializationManager :: UnpackAnswerContainer(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackAnswerContainer. Start");
	#endif
	
	// Result value
	PANSWER_CONTAINER eduContainer = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == ANSWER_CONTAINER_DATA) && 
			(param -> dataBuffer))
		{
			char * eduParam = param -> dataBuffer;

			// Create container
			eduContainer = (PANSWER_CONTAINER)malloc(sizeof(ANSWER_CONTAINER));
								
			// Deserialize education container
			memcpy(&(eduContainer -> answersCount), eduParam, sizeof(eduContainer -> answersCount));
			eduParam += sizeof(eduContainer -> answersCount);

			for(int i = 0; (i < eduContainer -> answersCount) && (i < MAX_SCR_OBJ_COUNT); i++)
			{
				eduContainer -> answers[i] = (PANSWER_DESCRIPTOR)malloc(sizeof(ANSWER_DESCRIPTOR));

				memcpy(&(eduContainer -> answers[i] -> questionID), eduParam, sizeof(eduContainer -> answers[i] -> questionID));
				eduParam += sizeof(eduContainer -> answers[i] -> questionID);

				memcpy(&(eduContainer -> answers[i] -> rightAnswerID), eduParam, sizeof(eduContainer -> answers[i] -> rightAnswerID));
				eduParam += sizeof(eduContainer -> answers[i] -> rightAnswerID);

				int sLen = 0;
				memcpy(&sLen, eduParam, sizeof(sLen));
				if (sLen > STR_VALUE_LEN) sLen = STR_VALUE_LEN;
				eduParam += sizeof(sLen);

				memcpy(eduContainer -> answers[i] -> answerValue, eduParam, sLen);
				if (sLen >= STR_VALUE_LEN) sLen = STR_VALUE_LEN - 1;
				eduContainer -> answers[i] -> answerValue[sLen]  = '\0';
				eduParam += sLen;
			}
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackAnswerContainer. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackAnswerContainer. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackAnswerContainer. Done");
		#endif

		return eduContainer;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackAnswerContainer. Serialization error!");
			WriteToLog("SerializationManager : UnpackAnswerContainer. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetAnswerContainerSize

   Parameters :
			Input : 
				eduContainer - pointer to education container

   Return : education container size

   Description : Get education container size

*****************************************************************/
int SerializationManager :: GetAnswerContainerSize(PANSWER_CONTAINER eduContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetAnswerContainerSize. Start");
	#endif

	// Validate container
	if (!eduContainer) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetAnswerContainerSize. Education container is empty");
		#endif

		return 0;
	}

	// Calculate size of container
	int size = sizeof(eduContainer -> answersCount);

	for(int i = 0; (i < eduContainer -> answersCount) && (i < MAX_SCR_OBJ_COUNT); i++)
	{
		size += sizeof(eduContainer -> answers[i] -> questionID) + sizeof(eduContainer -> answers[i] -> rightAnswerID);

		int sLen = strlen(eduContainer -> answers[i] -> answerValue);
		if (sLen > STR_VALUE_LEN) sLen = STR_VALUE_LEN;
		size += sLen + sizeof(sLen);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetAnswerContainerSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region Timeinfo

/****************************************************************

   Class : SerializationManager

   Method : PackTimeinfo

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack timeinfo value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackTimeinfo(tm * value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackTimeinfo. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackTimeinfo. Wrong input data!");
			WriteToLog("SerializationManager : PackTimeinfo. Done");
		#endif

		return CreateCommandParameter(paramType, TIMEINFO_DATA, 0);
	}

	int size = sizeof(tm);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, TIMEINFO_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if ((value) && (cmdParam -> dataBuffer))
			{
				// Get data
				char * workData = cmdParam -> dataBuffer;

				memcpy(workData, value, cmdParam -> dataBufferSize);
				workData += cmdParam -> dataBufferSize;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackTimeinfo. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackTimeinfo. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackTimeinfo. Wrong command parameter!");

			WriteToLog("SerializationManager : PackTimeinfo. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackTimeinfo. Serialization error!");
			WriteToLog("SerializationManager : PackTimeinfo. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackTimeinfo

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Timeinfo value

   Description : Unpack timeinfo value

*****************************************************************/
tm * SerializationManager :: UnpackTimeinfo(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackTimeinfo. Start");
	#endif
	
	// Result value
	tm * value = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == TIMEINFO_DATA) && 
			(param -> dataBufferSize == sizeof(tm)) &&
			(param -> dataBuffer))
		{
			// Get value
			value = (tm *)malloc(sizeof(tm));

			memcpy(value, param -> dataBuffer, param -> dataBufferSize);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackTimeinfo. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackTimeinfo. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackTimeinfo. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackTimeinfo. Serialization error!");
			WriteToLog("SerializationManager : UnpackTimeinfo. Done");
		#endif

		return NULL;
	}	
}

#pragma endregion

#pragma region Symbol boxes

/****************************************************************

   Class : SerializationManager

   Method : PackSymbolBoxesList

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack symbol boxes value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackSymbolBoxesList(PUTF8_STRINGS_MATRIX_LIST value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackSymbolBoxesList. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackSymbolBoxesList. Wrong input data!");
			WriteToLog("SerializationManager : PackSymbolBoxesList. Done");
		#endif

		return CreateCommandParameter(paramType, SYMBOL_BOXES_DATA, 0);
	}

	int size = GetSymbolMatrixesListSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, SYMBOL_BOXES_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Pack symbol matrixes list
				char * pTmp = cmdParam -> dataBuffer;
				PUTF8_STRINGS_MATRIX_LIST symbolBoxesList = value;

				// Pack symbol matrixes list size
				memcpy(pTmp, &(symbolBoxesList -> size), sizeof(symbolBoxesList -> size));
				pTmp += sizeof(symbolBoxesList -> size);
			
				for(int k = 0; k < symbolBoxesList -> size; k++)
				{
					// Pack size of each symbol matrix
					memcpy(pTmp, &(symbolBoxesList -> matrixes[k] -> size), sizeof(symbolBoxesList -> matrixes[k] -> size));
					pTmp += sizeof(symbolBoxesList -> matrixes[k] -> size);

					for(int i = 0; i < symbolBoxesList -> matrixes[k] -> size; i++)
					{
						// Pack size of each symbol matrix
						memcpy(pTmp, &(symbolBoxesList -> matrixes[k] -> size), sizeof(symbolBoxesList -> matrixes[k] -> size));
						pTmp += sizeof(symbolBoxesList -> matrixes[k] -> size);

						for(int j = 0; j < symbolBoxesList -> matrixes[k] -> size; j++)
						{
							// Pack size of each symbol matrix string
							memcpy(pTmp, &(symbolBoxesList -> matrixes[k] -> strings[i][j] -> length), sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> length));
							pTmp += sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> length);

							for(int q = 0 ; q < symbolBoxesList -> matrixes[k] -> strings[i][j] -> length; q++)
							{
								// Pack size of each symbol
								memcpy(pTmp, &(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount), sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount));
								pTmp += sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount);

								// Pack each symbol bytes
								memcpy(pTmp, symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytes, symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount);
								pTmp += symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount;
							}
						}
					}
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackSymbolBoxesList. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackSymbolBoxesList. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackSymbolBoxesList. Wrong command parameter!");

			WriteToLog("SerializationManager : PackSymbolBoxesList. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackSymbolBoxesList. Serialization error!");
			WriteToLog("SerializationManager : PackSymbolBoxesList. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackSymbolBoxesList

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Symbol boxes value

   Description :  Unpack symbol boxes value

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST SerializationManager :: UnpackSymbolBoxesList(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackSymbolBoxesList. Start");
	#endif
	
	// Result value
	PUTF8_STRINGS_MATRIX_LIST symbolBoxesList = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == SYMBOL_BOXES_DATA) && 
			(param -> dataBuffer))
		{
			char * pTmp = param -> dataBuffer;

			// Unpack symbol matrixes list
			symbolBoxesList = (PUTF8_STRINGS_MATRIX_LIST)malloc(sizeof(UTF8_STRINGS_MATRIX_LIST));

			// Unpack symbol matrixes list size
			memcpy(&(symbolBoxesList -> size), pTmp, sizeof(symbolBoxesList -> size));
			pTmp += sizeof(symbolBoxesList -> size);
			
			for(int k = 0; k < symbolBoxesList -> size; k++)
			{
				symbolBoxesList -> matrixes[k] = (PUTF8_STRINGS_MATRIX)malloc(sizeof(UTF8_STRINGS_MATRIX));

				// Unpack size of each symbol matrix
				memcpy(&(symbolBoxesList -> matrixes[k] -> size), pTmp, sizeof(symbolBoxesList -> matrixes[k] -> size));
				pTmp += sizeof(symbolBoxesList -> matrixes[k] -> size);
				
				for(int i = 0; i < symbolBoxesList -> matrixes[k] -> size; i++)
				{
					// Unpack size of each symbol matrix
					memcpy(&(symbolBoxesList -> matrixes[k] -> size), pTmp, sizeof(symbolBoxesList -> matrixes[k] -> size));
					pTmp += sizeof(symbolBoxesList -> matrixes[k] -> size);

					for(int j = 0; j < symbolBoxesList -> matrixes[k] -> size; j++)
					{
						symbolBoxesList -> matrixes[k] -> strings[i][j] = (PUTF8_STRING)malloc(sizeof(UTF8_STRING));

						// Unpack size of each symbol matrix string
						memcpy(&(symbolBoxesList -> matrixes[k] -> strings[i][j] -> length), pTmp, sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> length));
						pTmp += sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> length);

						for(int q = 0 ; q < symbolBoxesList -> matrixes[k] -> strings[i][j] -> length; q++)
						{
							symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] = (PUTF8_CHAR)malloc(sizeof(UTF8_CHAR));

							// Unpack size of each symbol
							memcpy(&(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount), pTmp, sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount));
							pTmp += sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount);

							// Pack each symbol bytes
							memcpy(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytes, pTmp, symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount);
							pTmp += symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount;
						}
					}
				}
			}
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackSymbolBoxesList. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackSymbolBoxesList. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackSymbolBoxesList. Done");
		#endif

		return symbolBoxesList;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackSymbolBoxesList. Serialization error!");
			WriteToLog("SerializationManager : UnpackSymbolBoxesList. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetSymbolMatrixesListSize

   Parameters :
			Input : 
				symbolBoxesList - list of symbol matrixes

   Return : Size of symbol matrixes list size in bytes

   Description : Get symbol matrixes list size

*****************************************************************/
int SerializationManager :: GetSymbolMatrixesListSize(PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetSymbolMatrixesListSize. Start");
	#endif

	if (symbolBoxesList)
	{
		// Length of matrixes list
		int size = sizeof(symbolBoxesList -> size);

		for(int k = 0; k < symbolBoxesList -> size; k++)
		{
			// Size of each matrix
			size += sizeof(symbolBoxesList -> matrixes[k] -> size);

			for(int i = 0; i < symbolBoxesList -> matrixes[k] -> size; i++)
			{
				// Size of each matrix
				size += sizeof(symbolBoxesList -> matrixes[k] -> size);

				for(int j = 0; j < symbolBoxesList -> matrixes[k] -> size; j++)
				{
					// Size of each string
					size += sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> length);

					for(int q = 0 ; q < symbolBoxesList -> matrixes[k] -> strings[i][j] -> length; q++)
					{
						// Size of each char
						size += sizeof(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount) +
								symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q] -> bytesCount;
					}
				}
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetSymbolMatrixesListSize. Done");
		#endif

		return size;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetSymbolMatrixesListSize. Symbol matrixes list is empty!");
			WriteToLog("SerializationManager : GetSymbolMatrixesListSize. Done");
		#endif

		return 0;
	}
}

#pragma endregion

#pragma region User security data

/****************************************************************

   Class : SerializationManager

   Method : PackUserSecurity

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack user security value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackUserSecurity(PUSER_SECURITY_DATA value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackUserSecurity. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackUserSecurity. Wrong input data!");
			WriteToLog("SerializationManager : PackUserSecurity. Done");
		#endif

		return CreateCommandParameter(paramType, USER_PRIVATE_DATA, 0);
	}

	int size = GetSecurityDataContainerSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, USER_PRIVATE_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Pack symbol matrixes list
				char * pTmp = cmdParam -> dataBuffer;
				PUSER_SECURITY_DATA pSecurityData = value;

				memcpy(pTmp, &(pSecurityData -> userID), sizeof(pSecurityData -> userID));
				pTmp += sizeof(pSecurityData -> userID);

				memcpy(pTmp, &(pSecurityData -> authSystemID), sizeof(pSecurityData -> authSystemID));
				pTmp += sizeof(pSecurityData -> authSystemID);

				memcpy(pTmp, &(pSecurityData -> encSystemUserNameLen), sizeof(pSecurityData -> encSystemUserNameLen));
				pTmp += sizeof(pSecurityData -> encSystemUserNameLen);

				int sLen = pSecurityData -> encSystemUserNameLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(pTmp, pSecurityData -> encSystemUserName, sLen);
				pTmp += sLen;

				memcpy(pTmp, &(pSecurityData -> encSystemPasswordLen), sizeof(pSecurityData -> encSystemPasswordLen));
				pTmp += sizeof(pSecurityData -> encSystemPasswordLen);

				sLen = pSecurityData -> encSystemPasswordLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(pTmp, pSecurityData -> encSystemPassword, sLen);
				pTmp += sLen;

				memcpy(pTmp, &(pSecurityData -> passThru), sizeof(pSecurityData -> passThru));
				pTmp += sizeof(pSecurityData -> passThru);

				memcpy(pTmp, pSecurityData -> lastLogOnDate, DATE_STR_LEN);
				pTmp += DATE_STR_LEN;

				memcpy(pTmp, &(pSecurityData -> userToken), sizeof(pSecurityData -> userToken));
				pTmp += sizeof(pSecurityData -> userToken);

				memcpy(pTmp, &(pSecurityData -> tmpUserToken), sizeof(pSecurityData -> tmpUserToken));
				pTmp += sizeof(pSecurityData -> tmpUserToken);

				memcpy(pTmp, &(pSecurityData -> pwdType), sizeof(pSecurityData -> pwdType));
				pTmp += sizeof(pSecurityData -> pwdType);

				memcpy(pTmp, &(pSecurityData -> pwdConstRulesCount), sizeof(pSecurityData -> pwdConstRulesCount));
				pTmp += sizeof(pSecurityData -> pwdConstRulesCount);

				for (int j = 0; (j < pSecurityData -> pwdConstRulesCount) && (j < MAX_PWD_CONSTR_RULES_COUNT); j++)
				{
					memcpy(pTmp, &(pSecurityData -> pwdConstRules[j]), sizeof(pSecurityData -> pwdConstRules[j]));
					pTmp += sizeof(pSecurityData -> pwdConstRules[j]);
				}

				memcpy(pTmp, &(pSecurityData -> tmpPwdConstRulesCount), sizeof(pSecurityData -> tmpPwdConstRulesCount));
				pTmp += sizeof(pSecurityData -> tmpPwdConstRulesCount);

				for (int j = 0; (j < pSecurityData -> tmpPwdConstRulesCount) && (j < MAX_PWD_CONSTR_RULES_COUNT); j++)
				{
					memcpy(pTmp, &(pSecurityData -> tmpPwdConstRules[j]), sizeof(pSecurityData -> tmpPwdConstRules[j]));
					pTmp += sizeof(pSecurityData -> tmpPwdConstRules[j]);
				}
				
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackUserSecurity. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackUserSecurity. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackUserSecurity. Wrong command parameter!");

			WriteToLog("SerializationManager : PackUserSecurity. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackUserSecurity. Serialization error!");
			WriteToLog("SerializationManager : PackUserSecurity. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackUserSecurity

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : User security value

   Description :  Unpack user security value

*****************************************************************/
PUSER_SECURITY_DATA SerializationManager :: UnpackUserSecurity(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackUserSecurity. Start");
	#endif
	
	// Result value
	PUSER_SECURITY_DATA secData = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == USER_PRIVATE_DATA) && 
			(param -> dataBuffer))
		{
			char * pTmp = param -> dataBuffer;

			secData = (PUSER_SECURITY_DATA)malloc(sizeof(USER_SECURITY_DATA));

			memcpy(&(secData -> userID), pTmp, sizeof(secData -> userID));
			pTmp += sizeof(secData -> userID);

			memcpy(&(secData -> authSystemID), pTmp, sizeof(secData -> authSystemID));
			pTmp += sizeof(secData -> authSystemID);

			memcpy(&(secData -> encSystemUserNameLen), pTmp, sizeof(secData -> encSystemUserNameLen));
			pTmp += sizeof(secData -> encSystemUserNameLen);

			int sLen = secData -> encSystemUserNameLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(secData -> encSystemUserName, pTmp, sLen);
			pTmp += sLen;

			memcpy(&(secData -> encSystemPasswordLen), pTmp, sizeof(secData -> encSystemPasswordLen));
			pTmp += sizeof(secData -> encSystemPasswordLen);

			sLen = secData -> encSystemPasswordLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(secData -> encSystemPassword, pTmp, sLen);
			pTmp += sLen;

			memcpy(&(secData -> passThru), pTmp, sizeof(secData -> passThru));
			pTmp += sizeof(secData -> passThru);

			memcpy(secData -> lastLogOnDate, pTmp, DATE_STR_LEN);
			pTmp += DATE_STR_LEN;

			memcpy(&(secData -> userToken), pTmp, sizeof(secData -> userToken));
			pTmp += sizeof(secData -> userToken);

			memcpy(&(secData -> tmpUserToken), pTmp, sizeof(secData -> tmpUserToken));
			pTmp += sizeof(secData -> tmpUserToken);

			memcpy(&(secData -> pwdType), pTmp, sizeof(secData -> pwdType));
			pTmp += sizeof(secData -> pwdType);

			memcpy(&(secData -> pwdConstRulesCount), pTmp, sizeof(secData -> pwdConstRulesCount));
			pTmp += sizeof(secData -> pwdConstRulesCount);

			for (int j = 0; (j < secData -> pwdConstRulesCount) && (j < MAX_PWD_CONSTR_RULES_COUNT); j++)
			{
				memcpy(&(secData -> pwdConstRules[j]), pTmp, sizeof(secData -> pwdConstRules[j]));
				pTmp += sizeof(secData -> pwdConstRules[j]);
			}

			memcpy(&(secData -> tmpPwdConstRulesCount), pTmp, sizeof(secData -> tmpPwdConstRulesCount));
			pTmp += sizeof(secData -> tmpPwdConstRulesCount);

			for (int j = 0; (j < secData -> tmpPwdConstRulesCount) && (j < MAX_PWD_CONSTR_RULES_COUNT); j++)
			{
				memcpy(&(secData -> tmpPwdConstRules[j]), pTmp, sizeof(secData -> tmpPwdConstRules[j]));
				pTmp += sizeof(secData -> tmpPwdConstRules[j]);
			}
						
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackUserSecurity. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackUserSecurity. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackUserSecurity. Done");
		#endif

		return secData;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackUserSecurity. Serialization error!");
			WriteToLog("SerializationManager : UnpackUserSecurity. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetSecurityDataContainerSize

   Parameters :
			Input : 
				pSecurityData - pointer to security data structure
				
   Return : security data structure size

   Description : Get size of security data structure

*****************************************************************/
int SerializationManager :: GetSecurityDataContainerSize(PUSER_SECURITY_DATA pSecurityData)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetSecurityDataContainerSize. Start");
	#endif

	if (pSecurityData)
	{
		// Length of matrixes list
		int size = sizeof(USER_SECURITY_DATA) - 2*ENCRYPTED_DATA_SIZE - 2*(MAX_PWD_CONSTR_RULES_COUNT*sizeof(int));

		size += pSecurityData -> encSystemPasswordLen + pSecurityData -> encSystemUserNameLen + 
				pSecurityData -> pwdConstRulesCount * sizeof(int) + pSecurityData -> tmpPwdConstRulesCount * sizeof(int);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetSecurityDataContainerSize. Done");
		#endif

		return size;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetSecurityDataContainerSize. Security data container is empty!");
			WriteToLog("SerializationManager : GetSecurityDataContainerSize. Done");
		#endif

		return 0;
	}
}

#pragma endregion

#pragma region User DB access information

/****************************************************************

   Class : SerializationManager

   Method : PackUserDBAccessInfo

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack user DB access info value

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackUserDBAccessInfo(PUSER_DB_ACCESS_INFO value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackUserDBAccessInfo. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackUserDBAccessInfo. Wrong input data!");
			WriteToLog("SerializationManager : PackUserDBAccessInfo. Done");
		#endif

		return CreateCommandParameter(paramType, USER_DB_ACCESS_DATA, 0);
	}

	int size = GetDBAccessInfoSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, USER_DB_ACCESS_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Serialize container
				char * pTmp = cmdParam -> dataBuffer;
				PUSER_DB_ACCESS_INFO dbAccessInfo = value;

				int sLen = 0;
		
				sLen = dbAccessInfo -> dbServerNameLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(pTmp, &(sLen), sizeof(sLen));
				pTmp += sizeof(sLen);

				memcpy(pTmp, dbAccessInfo -> dbServerName, sLen);
				pTmp += sLen;

				sLen = dbAccessInfo -> dbNameLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(pTmp, &(sLen), sizeof(sLen));
				pTmp += sizeof(sLen);

				memcpy(pTmp, dbAccessInfo -> dbName, sLen);
				pTmp += sLen;

				sLen = dbAccessInfo -> dbUserNameLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(pTmp, &(sLen), sizeof(sLen));
				pTmp += sizeof(sLen);

				memcpy(pTmp, dbAccessInfo -> dbUserName, sLen);
				pTmp += sLen;

				sLen = dbAccessInfo -> dbPasswordLen;
				if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
				memcpy(pTmp, &(sLen), sizeof(sLen));
				pTmp += sizeof(sLen);

				memcpy(pTmp, dbAccessInfo -> dbPassword, sLen);
				pTmp += sLen;

				sLen = dbAccessInfo -> userPermissionsCount;
				if (sLen > MAX_PERMISSIONS_COUNT) sLen = MAX_PERMISSIONS_COUNT;
				sLen *= sizeof(int) ;
				memcpy(pTmp, &(sLen), sizeof(sLen));
				pTmp += sizeof(sLen);

				memcpy(pTmp, dbAccessInfo -> userPermissions, sLen);
				pTmp += sLen;
								
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackUserDBAccessInfo. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackUserDBAccessInfo. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackUserDBAccessInfo. Wrong command parameter!");

			WriteToLog("SerializationManager : PackUserDBAccessInfo. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackUserDBAccessInfo. Serialization error!");
			WriteToLog("SerializationManager : PackUserDBAccessInfo. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackUserDBAccessInfo

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : User DB access info value

   Description :  Unpack user DB access info value

*****************************************************************/
PUSER_DB_ACCESS_INFO SerializationManager :: UnpackUserDBAccessInfo(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackUserDBAccessInfo. Start");
	#endif
	
	// Result value
	PUSER_DB_ACCESS_INFO dbAccessInfo = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == USER_DB_ACCESS_DATA) && 
			(param -> dataBuffer))
		{
			char * pTmp = param -> dataBuffer;
			
			dbAccessInfo = (PUSER_DB_ACCESS_INFO)malloc(sizeof(USER_DB_ACCESS_INFO));

			int sLen = 0;
		
			memcpy(&(dbAccessInfo -> dbServerNameLen), pTmp, sizeof(dbAccessInfo -> dbServerNameLen));
			pTmp += sizeof(dbAccessInfo -> dbServerNameLen);

			sLen = dbAccessInfo -> dbServerNameLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(dbAccessInfo -> dbServerName, pTmp, sLen);
			pTmp += sLen;

			memcpy(&(dbAccessInfo -> dbNameLen), pTmp, sizeof(dbAccessInfo -> dbNameLen));
			pTmp += sizeof(dbAccessInfo -> dbNameLen);

			sLen = dbAccessInfo -> dbNameLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(dbAccessInfo -> dbName, pTmp, sLen);
			pTmp += sLen;

			memcpy(&(dbAccessInfo -> dbUserNameLen), pTmp, sizeof(dbAccessInfo -> dbUserNameLen));
			pTmp += sizeof(dbAccessInfo -> dbUserNameLen);

			sLen = dbAccessInfo -> dbUserNameLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(dbAccessInfo -> dbUserName, pTmp, sLen);
			pTmp += sLen;

			memcpy(&(dbAccessInfo -> dbPasswordLen), pTmp, sizeof(dbAccessInfo -> dbPasswordLen));
			pTmp += sizeof(dbAccessInfo -> dbPasswordLen);

			sLen = dbAccessInfo -> dbPasswordLen;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			memcpy(dbAccessInfo -> dbPassword, pTmp, sLen);
			pTmp += sLen;

			memcpy(&(dbAccessInfo -> userPermissionsCount), pTmp, sizeof(dbAccessInfo -> userPermissionsCount));
			pTmp += sizeof(dbAccessInfo -> userPermissionsCount);

			sLen = dbAccessInfo -> userPermissionsCount;
			if (sLen > ENCRYPTED_DATA_SIZE) sLen = ENCRYPTED_DATA_SIZE;
			sLen *= sizeof(int) ;
			memcpy(dbAccessInfo -> userPermissions, pTmp, sLen);
			pTmp += sLen;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackUserDBAccessInfo. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackUserDBAccessInfo. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackUserDBAccessInfo. Done");
		#endif

		return dbAccessInfo;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackUserDBAccessInfo. Serialization error!");
			WriteToLog("SerializationManager : UnpackUserDBAccessInfo. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetDBAccessInfoSize

   Parameters :
			Input : 
				dbAccessInfo - pointer to DB access info container

   Return : DB access info size

   Description : Get DB access info container size

*****************************************************************/
int SerializationManager :: GetDBAccessInfoSize(PUSER_DB_ACCESS_INFO dbAccessInfo)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetDBAccessInfoSize. Start");
	#endif

	// Validate container
	if (!dbAccessInfo) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetDBAccessInfoSize. DB access info container is empty");
		#endif

		return 0;
	}

	// Calculate size of container
	int size = sizeof(dbAccessInfo -> dbServerNameLen) + sizeof(dbAccessInfo -> dbNameLen) +  sizeof(dbAccessInfo -> dbUserNameLen) + sizeof(dbAccessInfo -> dbPasswordLen) + sizeof(dbAccessInfo -> userPermissionsCount);

	if (dbAccessInfo -> dbServerNameLen > ENCRYPTED_DATA_SIZE) size += ENCRYPTED_DATA_SIZE;
	else size += dbAccessInfo -> dbServerNameLen;

	if (dbAccessInfo -> dbNameLen > ENCRYPTED_DATA_SIZE) size += ENCRYPTED_DATA_SIZE;
	else size += dbAccessInfo -> dbNameLen;

	if (dbAccessInfo -> dbUserNameLen > ENCRYPTED_DATA_SIZE) size += ENCRYPTED_DATA_SIZE;
	else size += dbAccessInfo -> dbUserNameLen;

	if (dbAccessInfo -> dbPasswordLen > ENCRYPTED_DATA_SIZE) size += ENCRYPTED_DATA_SIZE;
	else size += dbAccessInfo -> dbPasswordLen;

	if (dbAccessInfo -> userPermissionsCount > MAX_PERMISSIONS_COUNT) size += MAX_PERMISSIONS_COUNT * sizeof(int);
	else size += dbAccessInfo -> userPermissionsCount * sizeof(int);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetDBAccessInfoSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region User enviroment info

/****************************************************************

   Class : SerializationManager

   Method : PackEnviromentInfoContainer

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack enviroment info container structure

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackEnviromentInfoContainer(PENVIROMENT_INFO_CONTAINER value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackEnviromentInfoContainer. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackEnviromentInfoContainer. Wrong input data!");
			WriteToLog("SerializationManager : PackEnviromentInfoContainer. Done");
		#endif

		return CreateCommandParameter(paramType, ENVIROMENT_INFO_CONTAINER_DATA, 0);
	}

	int size = GetEnviromentInfoContainerSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, ENVIROMENT_INFO_CONTAINER_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				char * envParam = cmdParam -> dataBuffer;
				PENVIROMENT_INFO_CONTAINER envContainer = value;

				// Serialize container
				int len = strlen(envContainer -> activeProgramName);
				memcpy(envParam, &len, sizeof(len));
				envParam += sizeof(len);
				memcpy(envParam, envContainer -> activeProgramName, len);
				envParam += len;

				memcpy(envParam, &(envContainer -> userDowntime), sizeof(envContainer -> userDowntime));
				envParam += sizeof(envContainer -> userDowntime);
				
				if(envContainer -> programNamesListCount == 0)
				{
					bool _null = true;
					memcpy(envParam, &(_null), sizeof(_null));
					envParam += sizeof(_null);
				}
				else
				{
					bool _null = false;
					memcpy(envParam, &(_null), sizeof(_null));
					envParam += sizeof(_null);

					memcpy(envParam, &(envContainer -> programNamesListCount), sizeof(envContainer -> programNamesListCount));
					envParam += sizeof(envContainer -> programNamesListCount);
								
					for(int i = 0; (i < envContainer -> programNamesListCount) && (i < MAX_PROGRAMS_COUNT); i++)
					{
						len = strlen(envContainer -> programNamesList[i]);
						memcpy(envParam, &len, sizeof(len));
						envParam += sizeof(len);

						memcpy(envParam, envContainer -> programNamesList[i], len);
						envParam += len;
					}
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackEnviromentInfoContainer. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackEnviromentInfoContainer. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackEnviromentInfoContainer. Wrong command parameter!");

			WriteToLog("SerializationManager : PackEnviromentInfoContainer. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackEnviromentInfoContainer. Serialization error!");
			WriteToLog("SerializationManager : PackEnviromentInfoContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackEnviromentInfoContainer

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : Enviroment info container value

   Description : Unpack enviroment info container structure

*****************************************************************/
PENVIROMENT_INFO_CONTAINER SerializationManager :: UnpackEnviromentInfoContainer(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackEnviromentInfoContainer. Start");
	#endif
	
	// Result value
	PENVIROMENT_INFO_CONTAINER envContainer = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == ENVIROMENT_INFO_CONTAINER_DATA) && 
			(param -> dataBuffer))
		{
			char * envParam = param -> dataBuffer;

			// Create container
			envContainer = (PENVIROMENT_INFO_CONTAINER)malloc(sizeof(ENVIROMENT_INFO_CONTAINER));
								
			// Deserialize container
			int len = 0;

			memcpy(&len, envParam, sizeof(len));
			envParam += sizeof(len);

			memcpy(envContainer -> activeProgramName, envParam, len);
			envContainer -> activeProgramName[len] = 0;
			envParam += len;

			memcpy(&(envContainer -> userDowntime), envParam, sizeof(envContainer -> userDowntime));
			envParam += sizeof(envContainer -> userDowntime);
						
			bool _null = true;
			memcpy(&(_null), envParam, sizeof(_null));
			envParam += sizeof(_null);

			if (!_null)
			{
				memcpy(&(envContainer -> programNamesListCount), envParam, sizeof(envContainer -> programNamesListCount));
				envParam += sizeof(envContainer -> programNamesListCount);

				for(int i = 0; (i < envContainer -> programNamesListCount) && (i < MAX_PROGRAMS_COUNT); i++)
				{
					memcpy(&len, envParam, sizeof(len));
					envParam += sizeof(len);

					memcpy(envContainer -> programNamesList[i], envParam, len);
					envContainer -> programNamesList[i][len] = 0;
					envParam += len;
				}
			}
			else
				envContainer -> programNamesListCount = 0;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackEnviromentInfoContainer. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackEnviromentInfoContainer. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackEnviromentInfoContainer. Done");
		#endif

		return envContainer;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackEnviromentInfoContainer. Serialization error!");
			WriteToLog("SerializationManager : UnpackEnviromentInfoContainer. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetEnviromentInfoContainerSize

   Parameters :
			Input : 
				envContainer - pointer to enviroment info container

   Return : enviroment info container size

   Description : Get size of enviroment info container structure

*****************************************************************/
int SerializationManager :: GetEnviromentInfoContainerSize(PENVIROMENT_INFO_CONTAINER envContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetEnviromentInfoContainerSize. Start");
	#endif

	// Validate container
	if (!envContainer) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetEnviromentInfoContainerSize. Education container is empty");
		#endif

		return 0;
	}

	// Calculate size of container
	int len = strlen(envContainer -> activeProgramName);
	int size = sizeof(envContainer -> userDowntime) + sizeof(envContainer -> programNamesListCount) + sizeof(len) + len + sizeof(bool);

	for(int i = 0; (i < envContainer -> programNamesListCount) && (i < MAX_PROGRAMS_COUNT); i++)
	{
		len = strlen(envContainer -> programNamesList[i]);
		size += sizeof(len) + len;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetEnviromentInfoContainerSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region Controlled program list container

/****************************************************************

   Class : SerializationManager

   Method : PackControlledProgramListContainer

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack controlled program list container structure

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackControlledProgramListContainer(PCONTROL_PROGRAM_INFO_CONTAINER_LIST value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackControlledProgramListContainer. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackControlledProgramListContainer. Wrong input data!");
			WriteToLog("SerializationManager : PackControlledProgramListContainer. Done");
		#endif

		return CreateCommandParameter(paramType, CTRL_PRG_INFO_LIST_DATA, 0);
	}

	int size = GetControlledProgramListContainerSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, CTRL_PRG_INFO_LIST_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				char * prgLstParam = cmdParam -> dataBuffer;
				PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgLstContainer = value;

				// Serialize container
				memcpy(prgLstParam, &(prgLstContainer -> programListSize), sizeof(prgLstContainer -> programListSize));
				prgLstParam += sizeof(prgLstContainer -> programListSize);

				for(int i = 0; (i < prgLstContainer -> programListSize) && (i < MAX_PROGRAMS_LIST); i++)
				{
					if (prgLstContainer -> programList[i])
					{
						memcpy(prgLstParam, &(prgLstContainer -> programList[i] -> pid), sizeof(prgLstContainer -> programList[i] -> pid));
						prgLstParam += sizeof(prgLstContainer -> programList[i] -> pid);

						memcpy(prgLstParam, &(prgLstContainer -> programList[i] -> allowed), sizeof(prgLstContainer -> programList[i] -> allowed));
						prgLstParam += sizeof(prgLstContainer -> programList[i] -> allowed);

						int len = strlen(prgLstContainer -> programList[i] -> moduleName);
						memcpy(prgLstParam, &len, sizeof(len));
						prgLstParam += sizeof(len);

						memcpy(prgLstParam, prgLstContainer -> programList[i] -> moduleName, len);
						prgLstParam += len;

						len = strlen(prgLstContainer -> programList[i] -> programName);
						memcpy(prgLstParam, &len, sizeof(len));
						prgLstParam += sizeof(len);

						memcpy(prgLstParam, prgLstContainer -> programList[i] -> programName, len);
						prgLstParam += len;
					}
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackControlledProgramListContainer. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackControlledProgramListContainer. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackControlledProgramListContainer. Wrong command parameter!");

			WriteToLog("SerializationManager : PackControlledProgramListContainer. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackControlledProgramListContainer. Serialization error!");
			WriteToLog("SerializationManager : PackControlledProgramListContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackControlledProgramListContainer

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : controlled program list container structure

   Description : Unpack controlled program list container structure

*****************************************************************/
PCONTROL_PROGRAM_INFO_CONTAINER_LIST SerializationManager :: UnpackControlledProgramListContainer(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackControlledProgramListContainer. Start");
	#endif
	
	// Result value
	PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgLstContainer = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == CTRL_PRG_INFO_LIST_DATA) && 
			(param -> dataBuffer))
		{
			char * prgLstParam = param -> dataBuffer;

			// Create container
			prgLstContainer = (PCONTROL_PROGRAM_INFO_CONTAINER_LIST)malloc(sizeof(CONTROL_PROGRAM_INFO_CONTAINER_LIST));
								
			// Deserialize container
			memcpy(&(prgLstContainer -> programListSize), prgLstParam, sizeof(prgLstContainer -> programListSize));
			prgLstParam += sizeof(prgLstContainer -> programListSize);

			for(int i = 0; (i < prgLstContainer -> programListSize) && (i < MAX_PROGRAMS_LIST); i++)
			{
				prgLstContainer -> programList[i] = (PCONTROL_PROGRAM_INFO_CONTAINER)malloc(sizeof(CONTROL_PROGRAM_INFO_CONTAINER));

				if (prgLstContainer -> programList[i])
				{
					memcpy(&(prgLstContainer -> programList[i] -> pid), prgLstParam, sizeof(prgLstContainer -> programList[i] -> pid));
					prgLstParam += sizeof(prgLstContainer -> programList[i] -> pid);

					memcpy(&(prgLstContainer -> programList[i] -> allowed), prgLstParam, sizeof(prgLstContainer -> programList[i] -> allowed));
					prgLstParam += sizeof(prgLstContainer -> programList[i] -> allowed);

					int len = 0;
					memcpy(&len, prgLstParam, sizeof(len));
					prgLstParam += sizeof(len);

					memcpy(prgLstContainer -> programList[i] -> moduleName, prgLstParam, len);
					prgLstContainer -> programList[i] -> moduleName[len] = 0;
					prgLstParam += len;

					memcpy(&len, prgLstParam, sizeof(len));
					prgLstParam += sizeof(len);

					memcpy(prgLstContainer -> programList[i] -> programName, prgLstParam, len);
					prgLstContainer -> programList[i] -> programName[len] = 0;
					prgLstParam += len;
				}
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackControlledProgramListContainer. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackControlledProgramListContainer. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackControlledProgramListContainer. Done");
		#endif

		return prgLstContainer;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackControlledProgramListContainer. Serialization error!");
			WriteToLog("SerializationManager : UnpackControlledProgramListContainer. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetControlledProgramListContainerSize

   Parameters :
			Input : 
				prgLstContainer - pointer to controlled programs container

   Return : controlled programs container size

   Description : Get size of controlled programs container structure

*****************************************************************/
int SerializationManager :: GetControlledProgramListContainerSize(PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgLstContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetControlledProgramListContainerSize. Start");
	#endif

	// Validate container
	if (!prgLstContainer) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetControlledProgramListContainerSize. Container is empty");
		#endif

		return 0;
	}

	// Calculate size of container
	int size = sizeof(prgLstContainer -> programListSize);

	for(int i = 0; (i < prgLstContainer -> programListSize) && (i < MAX_PROGRAMS_LIST); i++)
	{
		if (prgLstContainer -> programList[i])
		{
			int len = strlen(prgLstContainer -> programList[i] -> moduleName) + strlen(prgLstContainer -> programList[i] -> programName);
			size += sizeof(prgLstContainer -> programList[i] -> pid) + sizeof(prgLstContainer -> programList[i] -> allowed) + len + 2*sizeof(len);
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetControlledProgramListContainerSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region Geo location data

/****************************************************************

   Class : SerializationManager

   Method : PackGeoLocationDataContainer

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack geo location data

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackGeoLocationDataContainer(PGEO_LOCATION_COORDS value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackGeoLocationDataContainer. Start");
	#endif

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, GEO_LOCATION_DATA, sizeof(GEO_LOCATION_COORDS));
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				// Get data
				memcpy(cmdParam -> dataBuffer, value, cmdParam -> dataBufferSize);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackGeoLocationDataContainer. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackGeoLocationDataContainer. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackGeoLocationDataContainer. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackGeoLocationDataContainer. Serialization error!");
			WriteToLog("SerializationManager : PackGeoLocationDataContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackGeoLocationDataContainer

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : pointer to geo location data structure

   Description : Unpack geo location data

*****************************************************************/
PGEO_LOCATION_COORDS SerializationManager :: UnpackGeoLocationDataContainer(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackGeoLocationDataContainer. Start");
	#endif
	
	// Result value
	PGEO_LOCATION_COORDS value = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == GEO_LOCATION_DATA) && 
			(param -> dataBufferSize == sizeof(GEO_LOCATION_COORDS)) &&
			(param -> dataBuffer))
		{
			// Get value
			value = (PGEO_LOCATION_COORDS)malloc(sizeof(GEO_LOCATION_COORDS));
			if (value) memcpy(value, param -> dataBuffer, param -> dataBufferSize);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackGeoLocationDataContainer. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackGeoLocationDataContainer. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackGeoLocationDataContainer. Done");
		#endif

		return value;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackGeoLocationDataContainer. Serialization error!");
			WriteToLog("SerializationManager : UnpackGeoLocationDataContainer. Done");
		#endif

		return value;
	}
}

#pragma endregion

#pragma region Command history container

/****************************************************************

   Class : SerializationManager

   Method : PackCommandHistoryContainer

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack command history container structure

*****************************************************************/
PCOMMAND_PARAMETER  SerializationManager :: PackCommandHistoryContainer(PCMD_HISTORY value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackCommandHistoryContainer. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackCommandHistoryContainer. Wrong input data!");
			WriteToLog("SerializationManager : PackCommandHistoryContainer. Done");
		#endif

		return CreateCommandParameter(paramType, CMD_HIST_CONTAINER_DATA, 0);
	}

	int size = GetCommandHistoryContainerSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, CMD_HIST_CONTAINER_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				char * pHistoryParam = cmdParam -> dataBuffer;
				PCMD_HISTORY pHistoryContainer = value;

				// Serialize container
				memcpy(pHistoryParam, &(pHistoryContainer -> size), sizeof(pHistoryContainer -> size));
				pHistoryParam += sizeof(pHistoryContainer -> size);

				for(int i = 0; (i < pHistoryContainer -> size) && (i < MAX_CMD_HIST_SIZE); i++)
				{
					if (pHistoryContainer -> historyItems[i])
					{
						memcpy(pHistoryParam, pHistoryContainer -> historyItems[i], sizeof(CMD_HISTORY_ITEM));
						pHistoryParam += sizeof(CMD_HISTORY_ITEM);
					}
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackCommandHistoryContainer. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackCommandHistoryContainer. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackCommandHistoryContainer. Wrong command parameter!");

			WriteToLog("SerializationManager : PackCommandHistoryContainer. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackCommandHistoryContainer. Serialization error!");
			WriteToLog("SerializationManager : PackCommandHistoryContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackCommandHistoryContainer

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : command history container structure

   Description : Unpack command history container structure

*****************************************************************/
PCMD_HISTORY  SerializationManager :: UnpackCommandHistoryContainer(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackCommandHistoryContainer. Start");
	#endif
	
	// Result value
	PCMD_HISTORY pHistoryContainer = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == CMD_HIST_CONTAINER_DATA) && 
			(param -> dataBuffer))
		{
			char * pHistoryParam = param -> dataBuffer;

			// Create container
			pHistoryContainer = (PCMD_HISTORY)malloc(sizeof(CMD_HISTORY));
								
			// Deserialize container
			memcpy(&(pHistoryContainer -> size), pHistoryParam, sizeof(pHistoryContainer -> size));
			pHistoryParam += sizeof(pHistoryContainer -> size);

			for(int i = 0; (i < pHistoryContainer -> size) && (i < MAX_CMD_HIST_SIZE); i++)
			{
				pHistoryContainer -> historyItems[i] = (PCMD_HISTORY_ITEM)malloc(sizeof(CMD_HISTORY_ITEM));

				if (pHistoryContainer -> historyItems[i])
				{
					memcpy(pHistoryContainer -> historyItems[i], pHistoryParam, sizeof(CMD_HISTORY_ITEM));
					pHistoryParam += sizeof(CMD_HISTORY_ITEM);
				}
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackCommandHistoryContainer. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackCommandHistoryContainer. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackCommandHistoryContainer. Done");
		#endif

		return pHistoryContainer;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackCommandHistoryContainer. Serialization error!");
			WriteToLog("SerializationManager : UnpackCommandHistoryContainer. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetCommandHistoryContainerSize

   Parameters :
			Input : 
				pHistoryCnt - pointer to command history container

   Return : size of command history

   Description : Get size of command history container structure

*****************************************************************/
int  SerializationManager :: GetCommandHistoryContainerSize(PCMD_HISTORY pHistoryCnt)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetCommandHistoryContainerSize. Start");
	#endif

	// Validate container
	if (!pHistoryCnt) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetCommandHistoryContainerSize. Container is empty");
		#endif

		return 0;
	}

	// Calculate size of container
	int size = sizeof(pHistoryCnt -> size);

	for(int i = 0; (i < pHistoryCnt -> size) && (i < MAX_CMD_HIST_SIZE); i++)
	{
		if (pHistoryCnt -> historyItems[i]) 
			size += sizeof(CMD_HISTORY_ITEM);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetCommandHistoryContainerSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region File Info container

/****************************************************************

   Class : SerializationManager

   Method : PackFileInfoContainer

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack file info container structure

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackFileInfoContainer(PFILE_INFO_CONTAINER value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackFileInfoContainer. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackFileInfoContainer. Wrong input data!");
			WriteToLog("SerializationManager : PackFileInfoContainer. Done");
		#endif

		return CreateCommandParameter(paramType, FILE_INFO_CONTAINER_DATA, 0);
	}

	int size = GetFileInfoContainerSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, FILE_INFO_CONTAINER_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				char * pFileInfoParam = cmdParam -> dataBuffer;
				PFILE_INFO_CONTAINER pFileInfoContainer = value;

				// Serialize container
				int len = strlen(pFileInfoContainer -> fileName);
				memcpy(pFileInfoParam, &len, sizeof(len));
				pFileInfoParam += sizeof(len);

				memcpy(pFileInfoParam, pFileInfoContainer -> fileName, len);
				pFileInfoParam += len;

				memcpy(pFileInfoParam, &(pFileInfoContainer -> fileSize), sizeof(pFileInfoContainer -> fileSize));
				pFileInfoParam += sizeof(pFileInfoContainer -> fileSize);

				memcpy(pFileInfoParam, &(pFileInfoContainer -> updateTime), sizeof(pFileInfoContainer -> updateTime));
				pFileInfoParam += sizeof(pFileInfoContainer -> updateTime);

				memcpy(pFileInfoParam, &(pFileInfoContainer -> isDir), sizeof(pFileInfoContainer -> isDir));
				pFileInfoParam += sizeof(pFileInfoContainer -> isDir);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackFileInfoContainer. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackFileInfoContainer. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackFileInfoContainer. Wrong command parameter!");

			WriteToLog("SerializationManager : PackFileInfoContainer. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackFileInfoContainer. Serialization error!");
			WriteToLog("SerializationManager : PackFileInfoContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackFileInfoContainer

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : file info container structure

   Description : Unpack file info container structure

*****************************************************************/
PFILE_INFO_CONTAINER SerializationManager :: UnpackFileInfoContainer(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackFileInfoContainer. Start");
	#endif
	
	// Result value
	PFILE_INFO_CONTAINER pFileInfoContainer = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == FILE_INFO_CONTAINER_DATA) && 
			(param -> dataBuffer))
		{
			char * pFileInfoParam = param -> dataBuffer;

			// Create container
			pFileInfoContainer = (PFILE_INFO_CONTAINER)malloc(sizeof(FILE_INFO_CONTAINER));
								
			// Deserialize container
			int len = 0;
			memcpy(&len, pFileInfoParam, sizeof(len));
			pFileInfoParam += sizeof(len);

			memcpy(pFileInfoContainer -> fileName, pFileInfoParam, len);
			pFileInfoContainer -> fileName[len] = 0;
			pFileInfoParam += len;

			memcpy(&(pFileInfoContainer -> fileSize), pFileInfoParam, sizeof(pFileInfoContainer -> fileSize));
			pFileInfoParam += sizeof(pFileInfoContainer -> fileSize);

			memcpy(&(pFileInfoContainer -> updateTime), pFileInfoParam, sizeof(pFileInfoContainer -> updateTime));
			pFileInfoParam += sizeof(pFileInfoContainer -> updateTime);

			memcpy(&(pFileInfoContainer -> isDir), pFileInfoParam, sizeof(pFileInfoContainer -> isDir));
			pFileInfoParam += sizeof(pFileInfoContainer -> isDir);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackFileInfoContainer. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackFileInfoContainer. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackFileInfoContainer. Done");
		#endif

		return pFileInfoContainer;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackFileInfoContainer. Serialization error!");
			WriteToLog("SerializationManager : UnpackFileInfoContainer. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetFileInfoContainerSize

   Parameters :
			Input : 
				pFileInfoContainer - pointer to file info container

   Return : size of file info container

   Description : Get size of file info container structure

*****************************************************************/
int SerializationManager :: GetFileInfoContainerSize(PFILE_INFO_CONTAINER pFileInfoContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetFileInfoContainerSize. Start");
	#endif

	// Validate container
	if (!pFileInfoContainer) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetFileInfoContainerSize. Container is empty");
		#endif

		return 0;
	}

	// Calculate size of container
	int size = strlen(pFileInfoContainer -> fileName) + sizeof(int) + sizeof(pFileInfoContainer -> fileSize) + sizeof(pFileInfoContainer -> updateTime) + sizeof(pFileInfoContainer -> isDir);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetFileInfoContainerSize. Done");
	#endif

	return size;
}

#pragma endregion

#pragma region Folder Info container

/****************************************************************

   Class : SerializationManager

   Method : PackFolderInfoContainer

   Parameters:
			Input:
				value - value for packing
				paramType - type of parameter
      
   Return : Pointer to the command parameter structure

   Description : Pack folder info container structure

*****************************************************************/
PCOMMAND_PARAMETER SerializationManager :: PackFolderInfoContainer(PFOLDER_INFO_CONTAINER value, int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : PackFolderInfoContainer. Start");
	#endif

	// Check input data
	if (value == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackFolderInfoContainer. Wrong input data!");
			WriteToLog("SerializationManager : PackFolderInfoContainer. Done");
		#endif

		return CreateCommandParameter(paramType, FOLDER_INFO_CONTAINER_DATA, 0);
	}

	int size = GetFolderInfoContainerSize(value);

	// Create command parameter
	PCOMMAND_PARAMETER cmdParam = CreateCommandParameter(paramType, FOLDER_INFO_CONTAINER_DATA, size);
	
	try
	{
		// Check command parameter pointer
		if (cmdParam)
		{
			// Check command parameter data buffer
			if (cmdParam -> dataBuffer)
			{
				char * pFolderInfoParam = cmdParam -> dataBuffer;
				PFOLDER_INFO_CONTAINER pFolderInfoContainer = value;

				// Serialize container
				int len = strlen(pFolderInfoContainer -> dirName);
				memcpy(pFolderInfoParam, &len, sizeof(len));
				pFolderInfoParam += sizeof(len);

				memcpy(pFolderInfoParam, pFolderInfoContainer -> dirName, len);
				pFolderInfoParam += len;

				memcpy(pFolderInfoParam, &(pFolderInfoContainer -> filesCount), sizeof(pFolderInfoContainer -> filesCount));
				pFolderInfoParam += sizeof(pFolderInfoContainer -> filesCount);
				
				for(int i = 0; i < pFolderInfoContainer -> filesCount; i++)
				{
					PFILE_INFO_CONTAINER pFileInfoContainer = pFolderInfoContainer -> filesList[i];
					
					len = strlen(pFileInfoContainer -> fileName);
					memcpy(pFolderInfoParam, &len, sizeof(len));
					pFolderInfoParam += sizeof(len);

					memcpy(pFolderInfoParam, pFileInfoContainer -> fileName, len);
					pFolderInfoParam += len;

					memcpy(pFolderInfoParam, &(pFileInfoContainer -> fileSize), sizeof(pFileInfoContainer -> fileSize));
					pFolderInfoParam += sizeof(pFileInfoContainer -> fileSize);

					memcpy(pFolderInfoParam, &(pFileInfoContainer -> updateTime), sizeof(pFileInfoContainer -> updateTime));
					pFolderInfoParam += sizeof(pFileInfoContainer -> updateTime);

					memcpy(pFolderInfoParam, &(pFileInfoContainer -> isDir), sizeof(pFileInfoContainer -> isDir));
					pFolderInfoParam += sizeof(pFileInfoContainer -> isDir);
				}

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackFolderInfoContainer. Value succesfully packed!");
				#endif
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
					WriteToLog("SerializationManager : PackFolderInfoContainer. Wrong data buffer!");
				#endif

				// Delete command parameter
				cmdParam = DeleteCommandParameter(cmdParam);
			}
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
				WriteToLog("SerializationManager : PackFolderInfoContainer. Wrong command parameter!");

			WriteToLog("SerializationManager : PackFolderInfoContainer. Done");
		#endif

		return cmdParam;
	}
	catch(...)
	{
		// Delete command parameter
		cmdParam = DeleteCommandParameter(cmdParam);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : PackFolderInfoContainer. Serialization error!");
			WriteToLog("SerializationManager : PackFolderInfoContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SerializationManager

   Method : UnpackFolderInfoContainer

   Parameters:
			Input:
				param - pointer to the command parameter structure
     
   Return : folder info container structure

   Description : Unpack folder info container structure

*****************************************************************/
PFOLDER_INFO_CONTAINER SerializationManager :: UnpackFolderInfoContainer(PCOMMAND_PARAMETER param)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : UnpackFolderInfoContainer. Start");
	#endif
	
	// Result value
	PFOLDER_INFO_CONTAINER pFolderInfoContainer = NULL;

	try
	{
		// Check command parameter
		if ((param) && 
			(param -> paramDataType == FOLDER_INFO_CONTAINER_DATA) && 
			(param -> dataBuffer))
		{
			char * pFolderInfoParam = param -> dataBuffer;

			// Create container
			pFolderInfoContainer = (PFOLDER_INFO_CONTAINER)malloc(sizeof(FOLDER_INFO_CONTAINER));
								
			// Deserialize container
			int len = 0;
			memcpy(&len, pFolderInfoParam, sizeof(len));
			pFolderInfoParam += sizeof(len);

			memcpy(pFolderInfoContainer -> dirName, pFolderInfoParam, len);
			pFolderInfoContainer -> dirName[len] = 0;
			pFolderInfoParam += len;

			memcpy(&(pFolderInfoContainer -> filesCount), pFolderInfoParam, sizeof(pFolderInfoContainer -> filesCount));
			pFolderInfoParam += sizeof(pFolderInfoContainer -> filesCount);

			for(int i = 0; i < pFolderInfoContainer -> filesCount; i++)
			{
				PFILE_INFO_CONTAINER pFileInfoContainer = (PFILE_INFO_CONTAINER)malloc(sizeof(FILE_INFO_CONTAINER));
				
				memcpy(&len, pFolderInfoParam, sizeof(len));
				pFolderInfoParam += sizeof(len);

				memcpy(pFileInfoContainer -> fileName, pFolderInfoParam, len);
				pFileInfoContainer -> fileName[len] = 0;
				pFolderInfoParam += len;

				memcpy(&(pFileInfoContainer -> fileSize), pFolderInfoParam, sizeof(pFileInfoContainer -> fileSize));
				pFolderInfoParam += sizeof(pFileInfoContainer -> fileSize);

				memcpy(&(pFileInfoContainer -> updateTime), pFolderInfoParam, sizeof(pFileInfoContainer -> updateTime));
				pFolderInfoParam += sizeof(pFileInfoContainer -> updateTime);

				memcpy(&(pFileInfoContainer -> isDir), pFolderInfoParam, sizeof(pFileInfoContainer -> isDir));
				pFolderInfoParam += sizeof(pFileInfoContainer -> isDir);
			
				pFolderInfoContainer -> filesList[i] = pFileInfoContainer;
			}

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
				WriteToLog("SerializationManager : UnpackFolderInfoContainer. Value unpacked succesfully!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			else
			{
				WriteToLog("SerializationManager : UnpackFolderInfoContainer. Wrong command parameter!");
			}

			WriteToLog("SerializationManager : UnpackFolderInfoContainer. Done");
		#endif

		return pFolderInfoContainer;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : UnpackFolderInfoContainer. Serialization error!");
			WriteToLog("SerializationManager : UnpackFolderInfoContainer. Done");
		#endif

		return NULL;
	}	
}

/****************************************************************

   Class : SerializationManager

   Method : GetFolderInfoContainerSize

   Parameters :
			Input : 
				pFileInfoContainer - pointer to folder info container

   Return : size of folder info container

   Description : Get size of folder info container structure

*****************************************************************/
int SerializationManager :: GetFolderInfoContainerSize(PFOLDER_INFO_CONTAINER pFolderInfoContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetFolderInfoContainerSize. Start");
	#endif

	// Validate container
	if (!pFolderInfoContainer) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
			WriteToLog("SerializationManager : GetFolderInfoContainerSize. Container is empty");
		#endif

		return 0;
	}

	// Calculate size of container
	int size = strlen(pFolderInfoContainer -> dirName) + sizeof(int) + sizeof(pFolderInfoContainer -> filesCount);
	
	for (int i = 0; i < pFolderInfoContainer -> filesCount; i++)
		size += GetFileInfoContainerSize(pFolderInfoContainer -> filesList[i]);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SERIALIZE)
		WriteToLog("SerializationManager : GetFolderInfoContainerSize. Done");
	#endif

	return size;
}

#pragma endregion 

#pragma region LOG

/****************************************************************

   Class : SerializationManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  SerializationManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion
