/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : SetUserSignInDateCommand.cpp

   Description :  this module implements methods of
				  class SetUserSignInDateCommand

*****************************************************************/

#include "stdafx.h"
#include "SetUserSignInDateCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : SetUserSignInDateCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
SetUserSignInDateCommand :: SetUserSignInDateCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SetUserSignInDateCommand : constructor");
	#endif
}

/****************************************************************

   Class : SetUserSignInDateCommand

   Method : Destructor

*****************************************************************/
SetUserSignInDateCommand :: ~SetUserSignInDateCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SetUserSignInDateCommand : destructor");
	#endif
}

/****************************************************************

   Class : SetUserSignInDateCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST SetUserSignInDateCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SetUserSignInDateCommand : Execute. Start");
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
			bool setResult = SetUserSignInDate(userID, authSystemID);

			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackByte((unsigned char)setResult, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("SetUserSignInDateCommand : Execute. Can't create result parameters list!");
		#endif
		
		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("SetUserSignInDateCommand : Execute. Wrong input parameters!");

		WriteToLog("SetUserSignInDateCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SetUserSignInDateCommand

   Method : SetUserSignInDate

   Parameters :
			Input : 
				user - user descriptor

   Return : success flag

   Description : Save date of last sign in 

*****************************************************************/
bool SetUserSignInDateCommand :: SetUserSignInDate(int userID, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SetUserSignInDateCommand : SetUserSignInDate. Start");
	#endif

	bool resFlag = false;
	
	ContentManager * contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
	resFlag = contentManager -> SetUserSignInDate(userID, authSystemID);
	delete contentManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SetUserSignInDateCommand : SetUserSignInDate. Done");
	#endif

	return resFlag;
}