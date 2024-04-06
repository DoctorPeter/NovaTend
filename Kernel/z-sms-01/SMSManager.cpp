/****************************************************************

   Solution : NovaTend

   Project : z-sms-01.dll

   Module : SMSManager.cpp

   Description :  this module implements methods of
				  class SMSManager

*****************************************************************/

#include "stdafx.h"
#include "SMSManager.h"

// z-sms-01.dll definition structure
extern DLL_COMMON_DEFINITION zSMSDllDefinition;

/****************************************************************

   Class : SMSManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
SMSManager :: SMSManager(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zSMSDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("SMSManager : constructor");
	#endif
}

/****************************************************************

   Class : SMSManager

   Method : Destructor

*****************************************************************/
SMSManager :: ~SMSManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SMS)
		WriteToLog("SMSManager : destructor");
	#endif
}

/****************************************************************

   Class : SMSManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int SMSManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}