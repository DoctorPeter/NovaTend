/****************************************************************

   Solution : NovaTend

   Project : z-commands-01.dll

   Module : Command.cpp

   Description :  this module implements methods of
				  class Command

*****************************************************************/

#include "stdafx.h"
#include "Command.h"

// z-command-01.dll definition structure
extern DLL_COMMON_DEFINITION zCommandDllDefinition;
 
/****************************************************************

   Class : Command

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
Command :: Command(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zCommandDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("Command : constructor");
	#endif
}

/****************************************************************

   Class : Command

   Method : Destructor

*****************************************************************/
Command :: ~Command(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("Command : destructor");
	#endif
}

/****************************************************************

   Class : Command

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST Command :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("Command : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD)
		WriteToLog("Command : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : Command

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int Command :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}