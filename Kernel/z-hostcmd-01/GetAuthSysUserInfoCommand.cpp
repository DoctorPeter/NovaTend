/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetAuthSysUserInfoCommand.cpp

   Description :  this module implements methods of
				  class GetAuthSysUserInfoCommand

*****************************************************************/

#include "stdafx.h"
#include "GetAuthSysUserInfoCommand.h"
#include <Encryptor.h>


// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : GetAuthSysUserInfoCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
GetAuthSysUserInfoCommand :: GetAuthSysUserInfoCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetAuthSysUserInfoCommand : constructor");
	#endif
}

/****************************************************************

   Class : GetAuthSysUserInfoCommand

   Method : Destructor

*****************************************************************/
GetAuthSysUserInfoCommand :: ~GetAuthSysUserInfoCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetAuthSysUserInfoCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetAuthSysUserInfoCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetAuthSysUserInfoCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetAuthSysUserInfoCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 2) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[1] -> paramDataType == DWORD_DATA))
	{

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);

		// Unpack user ID
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);

		// Unpack authentication system ID
		int authSystemID = serializationManager -> UnpackDWORD(parameters -> paramList[1]);

		// Create content manager
		ContentManager * contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);

		// Get authentication system name 
		unsigned char encAuthSystemName[ENCRYPTED_DATA_SIZE] = "";
		int encAuthSystemNameLen = 0;
		contentManager -> GetAuthSystemName(authSystemID, encAuthSystemName, &encAuthSystemNameLen);

		// User names
		unsigned char userName[ENCRYPTED_DATA_SIZE] = "";
		int userNameLen = 0;
		unsigned char sysUserName[ENCRYPTED_DATA_SIZE] = "";
		int sysUserNameLen = 0;
		unsigned char fullUserName[ENCRYPTED_DATA_SIZE] = "";
		int fullUserNameLen = 0;

		// Get user names
		contentManager -> GetUserNames(userID, authSystemID, userName, &userNameLen, sysUserName, &sysUserNameLen, fullUserName, &fullUserNameLen);

		delete contentManager;

		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			result -> paramCount = 4;
			result -> paramList[0] = serializationManager -> PackEncrypted(encAuthSystemName, encAuthSystemNameLen, RETURN_CMD_DATA);
			result -> paramList[1] = serializationManager -> PackEncrypted(userName, userNameLen, RETURN_CMD_DATA);
			result -> paramList[2] = serializationManager -> PackEncrypted(sysUserName, sysUserNameLen, RETURN_CMD_DATA);
			result -> paramList[3] = serializationManager -> PackEncrypted(fullUserName, fullUserNameLen, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetAuthSysUserInfoCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("GetAuthSysUserInfoCommand : Execute. Wrong input parameters!");

		WriteToLog("GetAuthSysUserInfoCommand : Execute. Done");
	#endif

	return result;
}