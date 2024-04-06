/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : RedirectionCommand.cpp

   Description :  this module implements methods of
				  class RedirectionCommand

*****************************************************************/

#include "stdafx.h"
#include "RedirectionCommand.h"

// z-hubcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;
 
/****************************************************************

   Class : RedirectionCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				ipcClient - pointer to IPCClient instance
				commandCode - code of command

*****************************************************************/
RedirectionCommand :: RedirectionCommand(unsigned long dllUserID, 
										 LogWriter * logWriter, 
										 IPCClientsManager * ipcClientsManager, 
										 unsigned int commandCode, 
										 unsigned int senderID, 
										 unsigned int recipientID) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("RedirectionCommand : constructor");
	#endif

	this -> ipcClientsManager = ipcClientsManager;
	this -> commandCode = commandCode;
	this -> senderID = senderID;
	this -> recipientID = recipientID;
}

/****************************************************************

   Class : RedirectionCommand

   Method : Destructor

*****************************************************************/
RedirectionCommand :: ~RedirectionCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("RedirectionCommand : destructor");
	#endif
}

/****************************************************************

   Class : RedirectionCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST RedirectionCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("RedirectionCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Create serialization manager instance
	SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

	// Create request
	PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(commandCode, REQUEST_CMD, senderID, recipientID);
		
	// Request package size
	int requestPackageSize = 0;
		
	// Request package
	char * requestPackage = NULL;

	if (pRequest)
	{
		// Delete prameters list
		pRequest -> parameters = serializationManager -> DeleteCommandParameterList(pRequest -> parameters);

		// Set parameters pointer
		pRequest -> parameters = parameters;

		// Pack request
		requestPackage = serializationManager -> PackCommandRequestResponse(pRequest, &requestPackageSize);

		// Set parameters pointer
		pRequest -> parameters = NULL;

		// Delete request
		pRequest = serializationManager -> DeleteRequestResponse(pRequest);
	}

	// Response package size
	int responsePackageSize = 0;
		
	// Response package
	char * responsePackage = NULL;

	// Check request package
	if ((requestPackage) && (requestPackageSize > 0))
	{
		if (ipcClientsManager)
			responsePackage = ipcClientsManager ->  SendData(recipientID, requestPackage, requestPackageSize, &responsePackageSize);

		free(requestPackage);
	}

	// Check response package
	if ((responsePackage) && (responsePackageSize > 0))
	{
		PCOMMAND_REQUEST_RESPONSE pResponse = serializationManager -> UnpackCommandRequestResponse(responsePackage, responsePackageSize);
		free(responsePackage);

		if (pResponse)
		{
			// Get result parameter list
			result = pResponse -> parameters;

			// Delete response
			pResponse -> parameters = NULL;
			pResponse = serializationManager -> DeleteRequestResponse(pResponse);
		}
	}

	// Delete serialization manager instance
	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("RedirectionCommand : Execute. Done");
	#endif

	return result;
}