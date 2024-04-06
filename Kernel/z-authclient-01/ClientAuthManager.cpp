/****************************************************************

   Solution : NovaTend

   Project : z-authclient-01.dll

   Module : ClientAuthManager.cpp

   Description : this module implements methods of
				  class ClientAuthManager

*****************************************************************/

#include "stdafx.h"
#include "ClientAuthManager.h"
#include <Sddl.h>

// z-authclient-01.dll definition structure
extern DLL_COMMON_DEFINITION zAuthClientDllDefinition;

/****************************************************************

   Class : ClientAuthManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - log writer instance
				hubCommandManager - command manager instance


*****************************************************************/
ClientAuthManager :: ClientAuthManager(unsigned long dllUserID, 
									   LogWriter * logWriter,
									   CommandManager * commandManager) : AuthenticateManager(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : constructor");
	#endif

	this -> commandManager = commandManager - dllUserCheckResult;
}

/****************************************************************

   Class : ClientAuthManager

   Method : Copy constructor

   Parameters :
			Input : 
				src - soucre instance

*****************************************************************/		
ClientAuthManager :: ClientAuthManager(const ClientAuthManager & src)  : AuthenticateManager(src.dllUserID, src.logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : copy constructor");
	#endif

	this -> commandManager = src.commandManager;
}

/****************************************************************

   Class : ClientAuthManager

   Method : Destructor

*****************************************************************/
ClientAuthManager :: ~ClientAuthManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : Destructor");
	#endif
}

/****************************************************************

   Class : ClientAuthManager

   Method : Clone

   Return : Pointer to authenticate mananger clone object

   Description : Clone authenticate manager

*****************************************************************/
AuthenticateManager *  ClientAuthManager :: Clone(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : Clone");
	#endif

	return new ClientAuthManager(*this);
}

/****************************************************************

   Class : ClientAuthManager

   Method : CheckServerAccess

   Return : Success flag

   Description : Check server connection

*****************************************************************/
bool ClientAuthManager :: CheckServerAccess(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : CheckServerAccess. Start");
	#endif

	bool result = false;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_CHECK_ACCESS, REQUEST_CMD, senderID, recipientID);

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) &&
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == BYTE_DATA))
		{
			result = (bool)(serializationManager -> UnpackByte(pResponse -> parameters -> paramList[0]));
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : CheckServerAccess. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : GetUserContent

   Return : Pointer to user conetnt container

	Description : Get user content container

*****************************************************************/
PPRESET_CONTAINER ClientAuthManager :: GetUserContent(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserContent. Start");	
	#endif
	
	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_GET_CONTENT, REQUEST_CMD, senderID, recipientID);

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == PRESET_CONTAINER_DATA))
		{
			DeleteContent();
			content = serializationManager -> UnpackPresetContainer(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserContent. Done");	
	#endif

	return content;
}

/****************************************************************

   Class : ClientAuthManager

   Method : GetUserContent

   Parameters :
			Input : 
				compName - computer name
				userID - user ID
				osID - OS ID

   Return : pointer to user content container
	
	Description :  Get user content from database

*****************************************************************/
PPRESET_CONTAINER ClientAuthManager :: GetUserContent(char * compName, int userID, int osID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserContent. Start");	
	#endif
	
	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_GET_CONTENT, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 3;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackString(compName, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[2] = serializationManager -> PackDWORD(osID, INPUT_CMD_DATA);
		}
		
		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == PRESET_CONTAINER_DATA))
		{
			DeleteContent();
			content = serializationManager -> UnpackPresetContainer(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserContent. Done");	
	#endif

	return content;
}

/****************************************************************

   Class : ClientAuthManager

   Method : SetUserSignInDate

   Parameters :
			Input : 
				userID - user ID

   Return : success flag

   Description : Save date of last sign in 

*****************************************************************/
bool ClientAuthManager :: SetUserSignInDate(int userID, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : SetUserSignInDate. Start");
	#endif

	bool result = false;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_SET_USER_SIGNIN_DATE, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 2;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackDWORD(authSystemID, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == BYTE_DATA))
		{
			result = (bool)(serializationManager -> UnpackByte(pResponse -> parameters -> paramList[0]));
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : SetUserSignInDate. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : GetUserListContainer

   Return : Pointer to list of users

	Description : Get list of users

*****************************************************************/
PUSER_LIST ClientAuthManager :: GetUserListContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserListContainer. Start");	
	#endif
	
	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_GET_USER_LIST, REQUEST_CMD, senderID, recipientID);

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == USER_LIST_DATA))
		{
			DeleteUserListContainer();
			userListContainer = serializationManager -> UnpackUserList(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserListContainer. Done");	
	#endif

	return userListContainer;
}

/****************************************************************

   Class : ClientAuthManager

   Method : GetUserDescriptor

   Parameters:
			Input:
				userID - user ID

   Return : Pointer user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR ClientAuthManager :: GetUserDescriptor(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserDescriptor. Start");
	#endif

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_GET_USER_DESCRIPTOR, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 1;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) &&
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == USER_DESCRIPTOR_DATA))
		{
			currentUser = serializationManager -> UnpackUserDescriptor(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserDescriptor. Done");
	#endif

	return currentUser;
}

/****************************************************************

   Class : ClientAuthManager

   Method : GetUserDescriptor

   Parameters:
			Input:
				userName - encrypted name of user
				userNameLen - length of encrypted name of user
				
   Return : Pointer user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR ClientAuthManager :: GetUserDescriptor(unsigned char * userName, int userNameLen)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserDescriptor. Start");
	#endif

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_GET_USER_DESCRIPTOR, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 1;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackEncrypted(userName, userNameLen, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == USER_DESCRIPTOR_DATA))
		{
			currentUser = serializationManager -> UnpackUserDescriptor(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserDescriptor. Done");
	#endif

	return currentUser;
}

/****************************************************************

   Class : ClientAuthManager

   Method : GetUserDescriptor

   Parameters:
			Input:
				userName - encrypted name of user
				userNameLen - length of encrypted name of user
				authSystemID - authentication system type

   Return : Pointer user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR ClientAuthManager :: GetUserDescriptor(unsigned char * userName, int userNameLen, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserDescriptor. Start");
	#endif

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_GET_USER_DESCRIPTOR, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 2;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackEncrypted(userName, userNameLen, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackDWORD(authSystemID, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == USER_DESCRIPTOR_DATA))
		{
			currentUser = serializationManager -> UnpackUserDescriptor(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetUserDescriptor. Done");
	#endif

	return currentUser;
}

/****************************************************************

   Class : ClientAuthManager

   Method : ValidateParams

   Parameters :
			Input : 
				userID - user ID
				compName - computer name
				authContainer - authentication container

   Return : Error code

   Description : Validate user parameters

*****************************************************************/
int ClientAuthManager :: ValidateParams(int userID, char * compName, PAUTH_CONTAINER authContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ValidateParams. Start");
	#endif

	int result = RESPONSE_BAD;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_VALIDATE_PARAMS, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 3;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackString(compName, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[2] = serializationManager -> PackAuthContainer(authContainer, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			result = serializationManager -> UnpackDWORD(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ValidateParams. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method :  ValidateAnswers

   Parameters :
			Input : 
				userID - user ID
				compName - computer name
				eduContainer - education container

   Return : Error code

   Description : Validate user answers

*****************************************************************/
int ClientAuthManager :: ValidateAnswers(int userID, char * compName, PANSWER_CONTAINER eduContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ValidateAnswers. Start");
	#endif

	int result = RESPONSE_BAD;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_VALIDATE_ANSWERS, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 3;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackString(compName, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[2] = serializationManager -> PackAnswerContainer(eduContainer, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			result = serializationManager -> UnpackDWORD(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ValidateAnswers. Done");
	#endif

	return result;
}


/****************************************************************

   Class : ClientAuthManager

   Method :  CheckScheduleRecords

   Parameters :
			Input : 
				userID - user id
				compName - computer name
				funcID - function ID

   Return : Action code

   Description : Check schedule records

*****************************************************************/
int ClientAuthManager ::  CheckScheduleRecords(int userID, char * compName, int funcID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : CheckScheduleRecords. Start");
	#endif

	int result = RESPONSE_BAD;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_CHECK_SCHEDULE, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 3;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackString(compName, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[2] = serializationManager -> PackDWORD(funcID, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			result = serializationManager -> UnpackDWORD(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : CheckScheduleRecords. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : ValidateUserCustomPassword

   	Parameters :
			Input : 
				userID - pointer to user descriptor
				authSystemID - authentication system ID
				userPassword - encrypted user custom password
				userPasswordLen - encrypted user custom password size
				timeinfo - time info structure
				symbolBoxesList - symbol matrixes list

			Output:
				securityData - user security data

   Return : Error code

   Description : Validate user custom password

*****************************************************************/
int ClientAuthManager :: ValidateUserCustomPassword(int userID, int authSystemID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList, PUSER_SECURITY_DATA securityData)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ValidateUserCustomPassword. Start");
	#endif

	int result = RESPONSE_BAD;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_VALIDATE_USER_CUSTOM_PASSWORDS, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 5;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackDWORD(authSystemID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[2] = serializationManager -> PackEncrypted(userPassword, userPasswordLen, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[3] = serializationManager -> PackTimeinfo(timeinfo, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[4] = serializationManager -> PackSymbolBoxesList(symbolBoxesList, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 2) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
			(pResponse -> parameters -> paramList[1]) &&
			(pResponse -> parameters -> paramList[1] -> paramDataType == USER_PRIVATE_DATA))
		{
			result = serializationManager -> UnpackDWORD(pResponse -> parameters -> paramList[0]);
			PUSER_SECURITY_DATA pSecure = serializationManager -> UnpackUserSecurity(pResponse -> parameters -> paramList[1]);
			if ((securityData) && (pSecure))
				memcpy(securityData, pSecure, sizeof(USER_SECURITY_DATA));
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ValidateUserCustomPassword. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : ResetUserCustomPassword

   	Parameters :
			Input : 
				userID - user ID

   Return : Error code

   Description : Reset user password

*****************************************************************/
int ClientAuthManager :: ResetUserCustomPassword(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ResetUserCustomPassword. Start");
	#endif

	int result = RESPONSE_BAD;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_RESET_USER_PASSWORD, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 1;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			result = serializationManager -> UnpackDWORD(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ResetUserCustomPassword. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : ValidateUserAccount

   	Parameters :
			Input : 
				userName - encrypted user name
				userNameLen - length of encrypted user name
				userPassword - encrypted user password
				userPasswordLen - length of encrypted user password
				authSystemID - authentication system ID

   Return : Error code

   Description : Valdate user account

*****************************************************************/
int ClientAuthManager :: ValidateUserAccount(unsigned char * userName, int userNameLen, unsigned char * userPassword, int userPasswordLen, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ValidateUserAccount. Start");
	#endif

	int result = RESPONSE_BAD;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_VALIDATE_USER_ACCOUNT, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 3;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackEncrypted(userName, userNameLen, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackEncrypted(userPassword, userPasswordLen, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[2] = serializationManager -> PackDWORD(authSystemID, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			result = serializationManager -> UnpackDWORD(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : ValidateUserAccount. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : SaveUserNotificationHistory

   	Parameters :
			Input : 
				userID - user ID
				noticeID - notice ID

   Return : Saving result

   Description : Save user notification result

*****************************************************************/
bool ClientAuthManager :: SaveUserNotificationHistory(int userID, int noticeID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : SaveUserNotificationHistory. Start");
	#endif

	bool result = false;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_SAVE_NOTIFICATION_HISTORY, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 2;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackDWORD(noticeID, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == BYTE_DATA))
		{
			result = (bool)(serializationManager -> UnpackByte(pResponse -> parameters -> paramList[0]));
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : SaveUserNotificationHistory. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : GetDBAccess

   	Parameters :
			Input : 
				userID - user ID
				userPassword - encrypted user password
				userPasswordLen - user password length
				timeinfo - current time structure
				symbolBoxesList - symbol boxes list

   Return : DB access info structure

   Description : Get DB connection

*****************************************************************/
PUSER_DB_ACCESS_INFO ClientAuthManager :: GetDBAccess(int userID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetDBAccess. Start");
	#endif

	PUSER_DB_ACCESS_INFO result = NULL;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_GET_DB_ACCESS, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 4;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackEncrypted(userPassword, userPasswordLen, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[2] = serializationManager -> PackTimeinfo(timeinfo, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[3] = serializationManager -> PackSymbolBoxesList(symbolBoxesList, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == USER_DB_ACCESS_DATA))
		{
			result = serializationManager -> UnpackUserDBAccessInfo(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetDBAccess. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : GetAuthSystemID

   	Parameters :
			Input : 
				encSystemSettings - encrypted system settings
				encSystemSettingsLen - encrypted system settings length
				authSystemType - system type
				
   Return : auth system ID

   Description : Get auth system ID

*****************************************************************/
int ClientAuthManager :: GetAuthSystemID(unsigned char * encSystemSettings, int encSystemSettingsLen, int authSystemType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetAuthSystemID. Start");
	#endif

	int result = -1;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_GET_AUTH_SYSTEM, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 2;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackEncrypted(encSystemSettings, encSystemSettingsLen, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackDWORD(authSystemType, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			result = serializationManager -> UnpackDWORD(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetAuthSystemID. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : FirstUserSignInToday

   Parameters :
			Input : 
				userID - user ID
				authSystemID - auth system ID

   Return : TRUE - if it is first time

   Description : Is it first sign in for today for this user?

*****************************************************************/
bool ClientAuthManager :: FirstUserSignInToday(int userID, int authSystemID)
{
	///////////////////////////////////
	//
	return true;
	//
	///////////////////////////////////

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : FirstUserSignInToday. Start");
	#endif

	bool result = false;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_CHECK_SIGN_IN_DATE, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 2;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackDWORD(authSystemID, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == BYTE_DATA))
		{
			result = (bool)(serializationManager -> UnpackByte(pResponse -> parameters -> paramList[0]));
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : FirstUserSignInToday. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : LockCtrlAltDelActions

   	Parameters :
			Input : 
				lock - lock/unclok flag
				userName - user name

   Return : TRUE - if success

   Description : Lock/Unlock CTRL + ALT + DEL

*****************************************************************/
bool ClientAuthManager :: LockCtrlAltDelActions(bool lock, char * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : LockCtrlAltDelActions. Start");
	#endif

	bool result = false;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_LOCK_USER_CAD_ACTIONS, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 2;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackByte((unsigned char)lock, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackString(userName, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == BYTE_DATA))
		{
			result = (bool)(serializationManager -> UnpackByte(pResponse -> parameters -> paramList[0]));
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : LockCtrlAltDelActions. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : GetFileList

   	Parameters :
			Input : 
				dirPath - path to the folder
				maxFileCount - maximum count of files in list

   Return : pointer to structure with folder description

   Description : Get list of files in some remote directory

*****************************************************************/
PFOLDER_INFO_CONTAINER ClientAuthManager :: GetFileList(char * dirPath, int maxFileCount)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetFileList. Start");
	#endif

	PFOLDER_INFO_CONTAINER result = NULL;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_FILE_TRANSFER, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 2;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(maxFileCount, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackString(dirPath, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == FOLDER_INFO_CONTAINER_DATA))
		{
			result = serializationManager -> UnpackFolderInfoContainer(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : GetFileList. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : DownloadFile

   	Parameters :
			Input : 
				filePath - path to the file
				
   Return : size of file

   Description : Download file

*****************************************************************/
long long ClientAuthManager :: DownloadFile(char * filePath)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : DownloadFile. Start");
	#endif

	long long result = 0;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_FILE_TRANSFER, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 1;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackString(filePath, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == LONG_DATA))
		{
			result = serializationManager -> UnpackLong(pResponse -> parameters -> paramList[0]);
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : DownloadFile. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : UploadFile

   	Parameters :
			Input : 
				filePath - path to the file
				fileSize - size of file

   Return : path to the file

   Description : Upload file

*****************************************************************/
bool ClientAuthManager :: UploadFile(char * filePath, long long fileSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : UploadFile. Start");
	#endif

	bool result = false;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_FILE_TRANSFER, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 2;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackString(filePath, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackLong(fileSize, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == STRING_DATA))
		{
			serializationManager -> UnpackString(pResponse -> parameters -> paramList[0], filePath);
			result = true;
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : UploadFile. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : DownloadBlockFile

   	Parameters :
			Input : 
				filePath - path to the file
				blockNUmber - number of block
				blockSize - size of block
				
   Return : block data

   Description : Download block of file

*****************************************************************/
char * ClientAuthManager :: DownloadBlockFile(char * filePath, int blockNUmber, int * blockSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : DownloadBlockFile. Start");
	#endif

	char * result = NULL;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_FILE_TRANSFER, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 3;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackString(filePath, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackDWORD(blockNUmber, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[2] = serializationManager -> PackDWORD(*blockSize, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == BINARY_DATA))
		{
			result = (char *)(serializationManager -> UnpackBinary(pResponse -> parameters -> paramList[0], blockSize));
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : DownloadBlockFile. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ClientAuthManager

   Method : UploadBlockFile

   	Parameters :
			Input : 
				filePath - path to the file
				blockNUmber - number of block
				blockSize - size of block
				blockData - block data

   Return : path to the file

   Description : Upload block of file

*****************************************************************/
bool ClientAuthManager :: UploadBlockFile(char * filePath, int blockNUmber, int blockSize, char * blockData)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : UploadBlockFile. Start");
	#endif

	bool result = false;

	if (commandManager)
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zAuthClientDllDefinition.dllID, logWriter);
		
		// Get ID
		unsigned int senderID = commandManager -> serverDescr.serverID;
		unsigned int recipientID = commandManager -> serverDescr.serverID;

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_FILE_TRANSFER, REQUEST_CMD, senderID, recipientID);

		// Set parameters
		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 4;
			pRequest -> parameters -> paramList[0] = serializationManager -> PackString(filePath, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[1] = serializationManager -> PackDWORD(blockNUmber, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[2] = serializationManager -> PackDWORD(blockSize, INPUT_CMD_DATA);
			pRequest -> parameters -> paramList[3] = serializationManager -> PackBinary((unsigned char *)blockData, blockSize, INPUT_CMD_DATA);
		}

		// Execute command
		PCOMMAND_REQUEST_RESPONSE pResponse = commandManager -> ExecuteCommand(pRequest);

		// Retrieve result
		if ((pResponse) && 
			(pResponse -> parameters) &&
			(pResponse -> parameters -> paramCount == 1) && 
			(pResponse -> parameters -> paramList[0]) &&
			(pResponse -> parameters -> paramList[0] -> paramDataType == STRING_DATA))
		{
			serializationManager -> UnpackString(pResponse -> parameters -> paramList[0], filePath);
			result = true;
		}

		// Delete data structuters
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
		pResponse = serializationManager -> DeleteRequestResponse(pResponse);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("ClientAuthManager : UploadBlockFile. Done");
	#endif

	return result;
}