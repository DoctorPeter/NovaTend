/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckSignInDateCommand.cpp

   Description :  this module implements methods of
				  class CheckSignInDateCommand

*****************************************************************/

#include "stdafx.h"
#include "CheckSignInDateCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : CheckSignInDateCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
CheckSignInDateCommand :: CheckSignInDateCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckSignInDateCommand : constructor");
	#endif
}

/****************************************************************

   Class : CheckSignInDateCommand

   Method : Destructor

*****************************************************************/
CheckSignInDateCommand :: ~CheckSignInDateCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckSignInDateCommand : destructor");
	#endif
}

/****************************************************************

   Class : CheckSignInDateCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST CheckSignInDateCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckSignInDateCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 2) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[1] -> paramDataType == DWORD_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
					
		// Unpack data
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
		int authSystemID = serializationManager -> UnpackDWORD(parameters -> paramList[1]);
						
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			bool dateResult = FirstUserSignInToday(userID, authSystemID);

			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackByte((unsigned char)dateResult, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("CheckSignInDateCommand : Execute. Can't create result parameters list!");
		#endif
		
		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("CheckSignInDateCommand : Execute. Wrong input parameters!");

		WriteToLog("CheckSignInDateCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : CheckSignInDateCommand

   Method : FirstUserSignInToday

   Parameters :
			Input : 
				userID - user ID
				authSystemID - auth system ID

   Return : TRUE - if it is first time

   Description : Is it first sign in for today for this user?

*****************************************************************/
bool CheckSignInDateCommand :: FirstUserSignInToday(int userID, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckSignInDateCommand : FirstUserSignInToday. Start");
	#endif

	bool result = true;

	ContentManager * contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
	result = contentManager -> FirstUserAuthSystemSignInToday(userID, authSystemID);
	delete contentManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckSignInDateCommand : FirstUserSignInToday. Done");
	#endif

	return result;
}