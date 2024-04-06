/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetUserListCommand.cpp

   Description :  this module implements methods of
				  class GetUserListCommand

*****************************************************************/

#include "stdafx.h"
#include "GetUserListCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : GetUserListCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
GetUserListCommand :: GetUserListCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserListCommand : constructor");
	#endif
	
	contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
}

/****************************************************************

   Class : GetUserListCommand

   Method : Destructor

*****************************************************************/
GetUserListCommand :: ~GetUserListCommand(void)
{
	delete contentManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserListCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetUserListCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetUserListCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserListCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((!parameters) || 
		((parameters) &&
		(parameters -> paramCount == 0)))
	{

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			PUSER_LIST userList = GetUserListContainer();
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackUserList(userList, RETURN_CMD_DATA);
			userList = DeleteUserListContainer(userList);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetUserListCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("GetUserListCommand : Execute. Wrong input parameters!");

		WriteToLog("GetUserListCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetUserListCommand

   Method : GetUserListContainer

   Return : Pointer to list of users

   Description : Get list of users

*****************************************************************/
PUSER_LIST GetUserListCommand :: GetUserListContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserListCommand : GetUserListContainer. Start");
	#endif
	
	PUSER_LIST userListContainer = NULL;
	
	if (contentManager)
		userListContainer = contentManager -> GetUserList();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserListCommand : GetUserListContainer. Done");
	#endif

	return userListContainer - dllUserCheckResult;
}

/****************************************************************

   Class : GetUserListCommand

   Method : DeleteUserListContainer

   Parameters:
			Input:
				userList - pointer to user list

   Return : Pointer to list of users

   Description : Delete list of users

*****************************************************************/
PUSER_LIST GetUserListCommand :: DeleteUserListContainer(PUSER_LIST userList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetUserListCommand : DeleteUserListContainer");
	#endif

	if ((userList) && (contentManager))
		userList = contentManager -> ClearUserList(userList);

	return userList;
}
