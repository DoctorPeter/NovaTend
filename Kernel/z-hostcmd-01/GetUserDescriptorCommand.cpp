/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetUserDescriptorCommand.cpp

   Description :  this module implements methods of
				  class GetUserDescriptorCommand

*****************************************************************/

#include "stdafx.h"
#include "GetUserDescriptorCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : GetUserDescriptorCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
GetUserDescriptorCommand :: GetUserDescriptorCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : constructor");
	#endif

	contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
}

/****************************************************************

   Class : GetUserDescriptorCommand

   Method : Destructor

*****************************************************************/
GetUserDescriptorCommand :: ~GetUserDescriptorCommand(void)
{
	delete contentManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetUserDescriptorCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetUserDescriptorCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 1) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);

		// Unpack user ID
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			PUSER_DESCRIPTOR pUser = GetUserDescriptor(userID);
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackUserDescriptor(pUser, RETURN_CMD_DATA);
			pUser = DeleteUserDescriptor(pUser);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetUserDescriptorCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	else
	if ((parameters) &&
		(parameters -> paramCount == 1) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramDataType == ENCRYPTED_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);

		// Unpack user name
		int nameSize = 0;
		unsigned char * encName = serializationManager -> UnpackEncrypted(parameters -> paramList[0], &nameSize);
		
		if (encName)
		{
			// Create result parameters list
			result = serializationManager -> CreateCommandParameterList();

			if (result)
			{
				PUSER_DESCRIPTOR pUser = GetUserDescriptor(encName, nameSize);
				result -> paramCount = 1;
				result -> paramList[0] = serializationManager -> PackUserDescriptor(pUser, RETURN_CMD_DATA);
				pUser = DeleteUserDescriptor(pUser);
			}
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				else
					WriteToLog("GetUserDescriptorCommand : Execute. Can't create result parameters list!");
			#endif

			// Free encrypted name
			free(encName);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetUserDescriptorCommand : Execute. Can't unpack user name!");
		#endif
		// Delete serialization manager instance
		delete serializationManager;
	}
	else
	if ((parameters) &&
		(parameters -> paramCount == 2) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[0] -> paramDataType == ENCRYPTED_DATA) &&
		(parameters -> paramList[1] -> paramDataType == DWORD_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);

		// Unpack user name
		int nameSize = 0;
		unsigned char * encName = serializationManager -> UnpackEncrypted(parameters -> paramList[0], &nameSize);
		
		// Unpack authentication system ID
		int authSystemID = serializationManager -> UnpackDWORD(parameters -> paramList[1]);

		if (encName)
		{
			// Create result parameters list
			result = serializationManager -> CreateCommandParameterList();

			if (result)
			{
				PUSER_DESCRIPTOR pUser = GetUserDescriptor(encName, nameSize, authSystemID);
				result -> paramCount = 1;
				result -> paramList[0] = serializationManager -> PackUserDescriptor(pUser, RETURN_CMD_DATA);
				pUser = DeleteUserDescriptor(pUser);
			}
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				else
					WriteToLog("GetUserDescriptorCommand : Execute. Can't create result parameters list!");
			#endif

			// Free encrypted name
			free(encName);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetUserDescriptorCommand : Execute. Can't unpack user name!");
		#endif
		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("GetUserDescriptorCommand : Execute. Wrong input parameters!");

		WriteToLog("GetUserDescriptorCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetUserDescriptorCommand

   Method : GetUserDescriptor

   Parameters:
			Input:
				userID - user ID
				
   Return : Pointer user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR GetUserDescriptorCommand :: GetUserDescriptor(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : GetUserDescriptor. Start");
	#endif

	PUSER_DESCRIPTOR pUser = NULL;

	if (contentManager)
		pUser = contentManager -> GetUserDescriptor(userID);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : GetUserDescriptor. Done");
	#endif

	return pUser - dllUserCheckResult;
}

/****************************************************************

   Class : GetUserDescriptorCommand

   Method : GetUserDescriptor

   Parameters:
			Input:
				userName - encrypted name of user
				userNameLen - length of encrypted name of user
				
   Return : Pointer user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR GetUserDescriptorCommand :: GetUserDescriptor(unsigned char * userName, int userNameLen)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : GetUserDescriptor. Start");
	#endif

	PUSER_DESCRIPTOR pUser = NULL;
	
	if (contentManager)
		pUser = contentManager -> GetUserDescriptor(userName, userNameLen);
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : GetUserDescriptor. Done");
	#endif

	return pUser - dllUserCheckResult;
}

/****************************************************************

   Class : ServerAuthManager

   Method : GetUserDescriptor

   Parameters:
			Input:
				userName - encrypted name of user
				userNameLen - length of encrypted name of user
				authSystemID - authentication system type

   Return : Pointer user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR GetUserDescriptorCommand :: GetUserDescriptor(unsigned char * userName, int userNameLen, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : GetUserDescriptor. Start");
	#endif

	PUSER_DESCRIPTOR pUser = NULL;
	
	if (contentManager)
		pUser = contentManager -> GetUserDescriptor(userName, userNameLen, authSystemID);
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : GetUserDescriptor. Done");
	#endif

	return pUser - dllUserCheckResult;
}

/****************************************************************

   Class : ServerAuthManager

   Method : DeleteUserDescriptor

   Parameters:
			Input:
				pUser - user descriptor
   
   Return : Pointer to user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR GetUserDescriptorCommand :: DeleteUserDescriptor(PUSER_DESCRIPTOR pUser)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserDescriptorCommand : DeleteUserDescriptor");
	#endif

	if ((pUser) && (contentManager))
		pUser = contentManager -> RemoveUserDescriptor(pUser);
	
	return pUser;
}
