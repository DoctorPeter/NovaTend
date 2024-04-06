/****************************************************************

   Solution : NovaTend

   Project : z-exceptions-01.dll

   Module : ExceptionHandler.cpp

   Description :  this module implements methods of 
				  class ExceptionHandler

*****************************************************************/

#include "stdafx.h"
#include "ExceptionHandler.h"

// z-exceptions-01.dll definition structure
extern DLL_COMMON_DEFINITION zExceptionsDllDefinition;

/****************************************************************

   Class : ExceptionHandler

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
ExceptionHandler :: ExceptionHandler(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zExceptionsDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_EXCEPTION)
		WriteToLog("ExceptionHandler : constructor");
	#endif
}

/****************************************************************

   Class : ExceptionHandler

   Method : Destructor

****************************************************************/
ExceptionHandler :: ~ExceptionHandler(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_EXCEPTION)
		WriteToLog("ExceptionHandler : destructor");
	#endif
}

/****************************************************************

   Class : ExceptionHandler

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Description : Write message to log-file

*****************************************************************/
int ExceptionHandler :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

