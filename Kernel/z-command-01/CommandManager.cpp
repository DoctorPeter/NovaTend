/****************************************************************

   Solution : NovaTend

   Project : z-commands-01.dll

   Module : CommandManager.cpp

   Description :  this module implements methods of
				  class CommandManager

*****************************************************************/

#include "stdafx.h"
#include "CommandManager.h"

// z-command-01.dll definition structure
extern DLL_COMMON_DEFINITION zCommandDllDefinition;
 
/****************************************************************

   Class : CommandManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
CommandManager :: CommandManager(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zCommandDllDefinition)
{
	this -> logWriter = logWriter;
	
	// Set client description to zero
	memset(&clientDescr, 0, sizeof(CLIENT_DESCRIPTION));

	// Set server description to zero
	memset(&serverDescr, 0, sizeof(SERVER_DESCRIPTION));


	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : constructor");
	#endif
}

/****************************************************************

   Class : CommandManager

   Method : Copy constructor

   Parameters :
			Input : 
				src - soucre instance

*****************************************************************/
CommandManager :: CommandManager(const CommandManager & src) : SystemBase(src.dllUserID, &zCommandDllDefinition)
{
	logWriter = src.logWriter;

	// Set client description to zero
	memset(&clientDescr, 0, sizeof(CLIENT_DESCRIPTION));

	// Set server description to zero
	memset(&serverDescr, 0, sizeof(SERVER_DESCRIPTION));

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : Copy constructor");
	#endif
}

/****************************************************************

   Class : CommandManager

   Method : Destructor

*****************************************************************/
CommandManager :: ~CommandManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : destructor");
	#endif
}

/****************************************************************

   Class : CommandManager

   Method : Clone

   Return : Pointer to command mamanger clone object

   Description : Clone command manager

*****************************************************************/
CommandManager * CommandManager :: Clone(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : Clone");
	#endif
	
	CommandManager * cloneObject = new CommandManager(*this);
	
	return cloneObject;
}

/****************************************************************

   Class : CommandManager

   Method : GenerateCommand

   Parameters :
			Input : 
				commandType - type of command

	Return : Command instance

	Description : Generate command instance by command type

*****************************************************************/
Command * CommandManager :: GenerateCommand(int commandType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : GenerateCommand. Start");
	#endif

	Command * command = NULL;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : GenerateCommand. Done");
	#endif

	return command - dllUserCheckResult;
}

/****************************************************************

   Class : CommandManager

   Method : GetCommandRequest

   Parameters :
			Input : 
				dataBuffer - package buffer
				size - package size

	Return : Command request/response structure

	Description : Get command request

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE CommandManager :: GetCommandRequest(char * dataBuffer, int size)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : GetCommandRequest. Start");
	#endif

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zCommandDllDefinition.dllID, logWriter);

	// Deserialize command message
	PCOMMAND_REQUEST_RESPONSE cmdRequest = serializationManager -> UnpackCommandRequestResponse(dataBuffer, size);

	// Delete serialization manager instance
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : GetCommandRequest. Done");
	#endif

	return cmdRequest - dllUserCheckResult;
}

/****************************************************************

   Class : CommandManager

   Method : GetCommandCode

   Parameters :
			Input : 
				dataBuffer - package buffer

	Return : Command code

	Description : Get command code

*****************************************************************/
unsigned int CommandManager :: GetCommandCode(char * dataBuffer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : GetCommandCode. Start");
	#endif

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zCommandDllDefinition.dllID, logWriter);

	// Deserialize command message
	unsigned int commandCode = serializationManager -> GetCommandCode(dataBuffer);

	// Delete serialization manager instance
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : GetCommandCode. Done");
	#endif

	return commandCode - dllUserCheckResult;
}

/****************************************************************

   Class : CommandManager

   Method : GetCommandCode

   Parameters :
			Input : 
				cmdRequest - command request/response structure

	Return : Command code

	Description : Get command code

*****************************************************************/
unsigned int CommandManager :: GetCommandCode(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : GetCommandCode. Start");
	#endif

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zCommandDllDefinition.dllID, logWriter);

	// Deserialize command message
	unsigned int commandCode = serializationManager -> GetCommandCode(cmdRequest);

	// Delete serialization manager instance
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : GetCommandCode. Done");
	#endif

	return commandCode - dllUserCheckResult;
}

/****************************************************************

   Class : CommandManager

   Method : ExecuteCommand

   Parameters :
			Input : 
				requestPackage - request package buffer
				requestSize - request package buffer size

			Output:
				responseSize - response package size

	Return : Response package

	Description : Execute command

*****************************************************************/
char * CommandManager :: ExecuteCommand(char * requestPackage, int requestSize, int * responseSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : ExecuteCommand. Start");
	#endif

	// Get request
	PCOMMAND_REQUEST_RESPONSE cmdRequest = GetCommandRequest(requestPackage, requestSize);

	// Get response
	PCOMMAND_REQUEST_RESPONSE cmdResponse = ExecuteCommand(cmdRequest);

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zCommandDllDefinition.dllID, logWriter);

	// Serialize response
	char * respPackage = serializationManager -> PackCommandRequestResponse(cmdResponse, responseSize);

	// Delete request
	cmdRequest = serializationManager -> DeleteRequestResponse(cmdRequest);

	// Delete response
	cmdResponse = serializationManager -> DeleteRequestResponse(cmdResponse);

	// Delete serialization manager instance
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : ExecuteCommand. Done");
	#endif

	return respPackage;
}

/****************************************************************

   Class : CommandManager

   Method : ExecuteCommand

   Parameters :
			Input : 
				cmdRequest - request structure

	Return : Response structure

	Description : Execute command

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE CommandManager :: ExecuteCommand(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : ExecuteCommand. Start");
	#endif
	
	// Command response
	PCOMMAND_REQUEST_RESPONSE cmdResponse = NULL;

	if (cmdRequest)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
			char message[STR_VALUE_LEN * 2] = "";
			sprintf(message, "CommandManager : ExecuteCommand. HEADER [Sender ID : %d, Recipient ID : %d, Command code : %d, Command type : %d]", cmdRequest -> header -> senderID, cmdRequest -> header -> recipientID, cmdRequest -> header -> commandCode, cmdRequest -> header -> commandType);
			WriteToLog(message);
		#endif

		// Check request recipient
		if (cmdRequest -> header -> recipientID != serverDescr.serverID)
		{
			// Redirect request
			cmdResponse = RedirectRequest(cmdRequest);
		}
		else
		{
			if (cmdRequest -> header -> commandCode == CMD_CREATE_BACK_CONNECTION)
			{
				cmdResponse = CreateBackConnection(cmdRequest);
			}
			else
			{
				// Get command code
				unsigned int commandCode = GetCommandCode(cmdRequest);

				// Generate command by code
				Command * command = GenerateCommand(commandCode);
		
				// Check generation result
				if (command)
				{
					// Execute command
					PCOMMAND_PARAMETER_LIST responseParams = command -> Execute(cmdRequest -> parameters);
		
					// Delete command
					delete command;

					// Create serialization manager instance
					SerializationManager * serializationManager = new SerializationManager(zCommandDllDefinition.dllID, logWriter);

					// Create request response
					cmdResponse = serializationManager -> CreateRequestResponse(commandCode, RESPONSE_CMD, serverDescr.serverID, cmdRequest -> header -> senderID);

					// Delete emtpy list
					cmdResponse -> parameters = serializationManager -> DeleteCommandParameterList(cmdResponse -> parameters);

					// Set generated list
					cmdResponse -> parameters = responseParams;

					// Delete serialization manager instance
					delete serializationManager;
				}
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : ExecuteCommand. Done");
	#endif
	
	return cmdResponse;
}

/****************************************************************

   Class : CommandManager

   Method : CreateBackConnection

   Parameters :
			Input : 
				cmdRequest - request structure

	Return : Response structure

	Description : Create back connection

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE CommandManager :: CreateBackConnection(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : CreateBackConnection");
	#endif

	return NULL;
}

/****************************************************************

   Class : CommandManager

   Method : RedirectRequest

   Parameters :
			Input : 
				cmdRequest - request structure

	Return : Response structure

	Description : Redirect request

*****************************************************************/
PCOMMAND_REQUEST_RESPONSE CommandManager :: RedirectRequest(PCOMMAND_REQUEST_RESPONSE cmdRequest)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : RedirectRequest");
	#endif

	return NULL;
}

/****************************************************************

   Class : CommandManager

   Method : CheckLicense

   Parameters :
			Input : 
				id - license point ID
				strValue - value
				index - index of value
				relType - type of relation

   Return : TRUE - if success

   Description : Check license of current client

*****************************************************************/
bool CommandManager :: CheckLicense(char * id, char * strValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : CheckLicense");
	#endif

	return false;
}

/****************************************************************

   Class : CommandManager

   Method : CheckLicense

   Parameters :
			Input : 
				id - license point ID
				intValue - value
				index - index of value
				relType - type of relation

   Return : TRUE - if success

   Description : Check license of current client

*****************************************************************/
bool CommandManager :: CheckLicense(char * id, int * intValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : CheckLicense");
	#endif

	return false;
}

/****************************************************************

   Class : CommandManager

   Method : CheckLicense

   Parameters :
			Input : 
				id - license point ID
				tmValue - value
				index - index of value
				relType - type of relation

   Return : TRUE - if success

   Description : Check license of current client

*****************************************************************/
bool CommandManager :: CheckLicense(char * id, tm * tmValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("CommandManager : CheckLicense");
	#endif

	return false;
}

/****************************************************************

   Class : CommandManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int CommandManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}