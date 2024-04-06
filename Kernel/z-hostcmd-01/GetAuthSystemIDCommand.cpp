/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetAuthSystemIDCommand.cpp

   Description :  this module implements methods of
				  class GetAuthSystemIDCommand

*****************************************************************/

#include "stdafx.h"
#include "GetAuthSystemIDCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : GetAuthSystemIDCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
GetAuthSystemIDCommand :: GetAuthSystemIDCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetAuthSystemIDCommand : constructor");
	#endif
}

/****************************************************************

   Class : GetAuthSystemIDCommand

   Method : Destructor

*****************************************************************/
GetAuthSystemIDCommand :: ~GetAuthSystemIDCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetAuthSystemIDCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetAuthSystemIDCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetAuthSystemIDCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetAuthSystemIDCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 2) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[0] -> paramDataType == ENCRYPTED_DATA) &&
		(parameters -> paramList[1] -> paramDataType == DWORD_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
		
		// Unpack data
		int authSystemSettingsSize = 0;
		unsigned char * authSystemSettings = serializationManager -> UnpackEncrypted(parameters -> paramList[0], &authSystemSettingsSize);
		int authSystemType = serializationManager -> UnpackDWORD(parameters -> paramList[1]);
						
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			int authSystemID = GetAuthSystemID(authSystemSettings, authSystemSettingsSize, authSystemType);

			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackDWORD(authSystemID, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetAuthSystemIDCommand : Execute. Can't create result parameters list!");
		#endif
		
		// Delete authentication system settings string
		if (authSystemSettings) free(authSystemSettings);

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("GetAuthSystemIDCommand : Execute. Wrong input parameters!");

		WriteToLog("GetAuthSystemIDCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetAuthSystemIDCommand

   Method : GetAuthSystemID

   	Parameters :
			Input : 
				encSystemSettings - encrypted system settings
				encSystemSettingsLen - encrypted system settings length
				authSystemType - system type
				
   Return : auth system ID

   Description : Get auth system ID

*****************************************************************/
int GetAuthSystemIDCommand :: GetAuthSystemID(unsigned char * encSystemSettings, int encSystemSettingsLen, int authSystemType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetAuthSystemIDCommand : GetAuthSystemID. Start");
	#endif

	int authSystemID = -1;

	ContentManager * contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
	authSystemID = contentManager -> GetAuthSystemID(encSystemSettings, encSystemSettingsLen, authSystemType);
	delete contentManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetAuthSystemIDCommand : GetAuthSystemID. Done");
	#endif

	return authSystemID - dllUserCheckResult;
}