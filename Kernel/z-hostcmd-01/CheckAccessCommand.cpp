/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckAccessCommand.cpp

   Description :  this module implements methods of
				  class CheckAccessCommand

*****************************************************************/

#include "stdafx.h"
#include "CheckAccessCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : CheckAccessCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
CheckAccessCommand :: CheckAccessCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckAccessCommand : constructor");
	#endif

	contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
}

/****************************************************************

   Class : CheckAccessCommand

   Method : Destructor

*****************************************************************/
CheckAccessCommand :: ~CheckAccessCommand(void)
{
	delete contentManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckAccessCommand : destructor");
	#endif
}

/****************************************************************

   Class : CheckAccessCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST CheckAccessCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckAccessCommand : Execute. Start");
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
			bool checkResult = CheckServerAccess();
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackByte((unsigned char)checkResult, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("CheckAccessCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("CheckAccessCommand : Execute. Wrong input parameters!");

		WriteToLog("CheckAccessCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : CheckAccessCommand

   Method : CheckServerAccess

   Return : Success flag

   Description : Check server connection

*****************************************************************/
bool CheckAccessCommand :: CheckServerAccess(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckAccessCommand : CheckServerAccess. Start");
	#endif

	bool connFlag = false;

	if (contentManager)
		connFlag = contentManager -> CheckDBAccess();
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckAccessCommand : CheckServerAccess. Done");
	#endif

	return connFlag;
}