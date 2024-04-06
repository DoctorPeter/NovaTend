/****************************************************************

   Solution : NovaTend

   Project : z-writelog-01.dll

   Module : SafeLogWriter.cpp

   Description :  this module implements methods of
				  class SafeLogWriter

*****************************************************************/

#include "stdafx.h"
#include "SafeLogWriter.h"

extern DLL_COMMON_DEFINITION zWriteLogDllDefinition;


// Macros for critical sections creation
#define CREATE_CRITICAL_SECTIONS	fileGuard = new CriticalSection();\
									modeGuard = new CriticalSection();\
									mailGuard = new CriticalSection();


// Macros for critical sections removing
#define REMOVE_CRITICAL_SECTIONS		delete fileGuard;\
										delete modeGuard;\
										delete mailGuard;

/****************************************************************

   Class : SafeLogWriter

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				fileName - name of Log-file
				fixedSize - LOG-file fixed size value

*****************************************************************/
SafeLogWriter :: SafeLogWriter(unsigned long int dllUserID, char * fileName, unsigned int fixedSize) : LogWriter(dllUserID, fileName, fixedSize)
{
	CREATE_CRITICAL_SECTIONS;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WRITELOG)
		WriteToLog("SafeLogWriter : constructor");
	#endif
}


/****************************************************************

   Class : SafeLogWriter

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				mode - mode of LogWriter functionality
				fileName - name of Log-file
				fixedSize - LOG-file fixed size value

*****************************************************************/
SafeLogWriter :: SafeLogWriter(unsigned long dllUserID, unsigned short mode, char * fileName, unsigned int fixedSize) : LogWriter(dllUserID, mode, fileName, fixedSize)
{
	CREATE_CRITICAL_SECTIONS;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WRITELOG)
		WriteToLog("SafeLogWriter : constructor");
	#endif
}

/****************************************************************

   Class : LogWriter

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				mode - mode of LogWriter functionality
				fileName - name of Log-file
				host - SMTP server address
				port - SMTP server port
				security - security settings
				authenticate - authenticate flag
				login - login
				password - password
				sender - sender address
				recipient - recipient address
				subject -  mail subject
				fixedSize - LOG-file fixed size value

*****************************************************************/
SafeLogWriter :: SafeLogWriter(unsigned long dllUserID,
							   unsigned short mode,
							   char * fileName, 
							   char * host, 
							   unsigned short port,
							   SMTP_SECURITY_TYPE security,
							   bool authenticate, 
							   char * login,
							   char * password,
							   char * sender, 
							   char * recipient, 
							   char * subject, 
							   unsigned int fixedSize) : LogWriter(dllUserID, mode, fileName, host, port, security, authenticate, login, password, sender, recipient, subject, fixedSize)
{
	CREATE_CRITICAL_SECTIONS;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WRITELOG)
		WriteToLog("SafeLogWriter : constructor");
	#endif
}

/****************************************************************

   Class : SafeLogWriter

   Method : Destructor

*****************************************************************/
SafeLogWriter :: ~SafeLogWriter(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WRITELOG)
		WriteToLog("SafeLogWriter : destructor");
	#endif

	REMOVE_CRITICAL_SECTIONS;
}

/****************************************************************

   Class : SafeLogWriter

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Description : Write message to log-file

*****************************************************************/
int SafeLogWriter :: WriteToLog(char * message)
{
	LOCK_SECTION(fileGuard);
	return LogWriter :: WriteToLog(message);
}

/****************************************************************

   Class : SafeLogWriter

   Method : GetMode

   Returns: work mode

   Description :  Get Log-writer work mode

*****************************************************************/
unsigned short SafeLogWriter :: GetMode()
{
	LOCK_SECTION(modeGuard);
	return LogWriter :: GetMode();
}

/****************************************************************

   Class : SafeLogWriter

   Method : SetMode

   Parameters:
			Input:
				mode - work mode

  Returns: old work mode

  Description :  Set Log-writer work mode

*****************************************************************/
unsigned short SafeLogWriter :: SetMode(unsigned short mode)
{
	LOCK_SECTION(modeGuard);
	return LogWriter :: SetMode(mode);
}

/****************************************************************

   Class : SafeLogWriter

   Method : AddMode

   Parameters:
			Input:
				mode - work mode

  Description :  Add mode to current Log-writer state

*****************************************************************/
void SafeLogWriter :: AddMode(unsigned short mode)
{
	LOCK_SECTION(modeGuard);
	LogWriter :: AddMode(mode);
}

/****************************************************************

   Class : SafeLogWriter

   Method : RemoveMode

   Parameters:
			Input:
				mode - work mode

  Description :  Remove mode from current Log-writer state

*****************************************************************/
void SafeLogWriter :: RemoveMode(unsigned short mode)
{
	LOCK_SECTION(modeGuard);
	LogWriter :: RemoveMode(mode);
}

/****************************************************************

   Class : SafeLogWriter

   Method : SetFileName

   Parameters :
			Input : 
				fileName - name of Log-file
	
	Description :  Set name of Log-file

*****************************************************************/
void SafeLogWriter :: SetFileName(char * fileName)
{
	LOCK_SECTION(fileGuard);
	LogWriter :: SetFileName(fileName);
}

/****************************************************************

   Class : SafeLogWriter

   Method : SetSMTPSettings

   Parameters :
			Input : 
				host - SMTP server address
				port - SMTP server port
				security - security settings
				authenticate - authenticate flag
				login - login
				password - password
				sender - sender address
				recipient - recipient address
				subject -  mail subject
	
	Description :  Set SMTP settings

*****************************************************************/
void SafeLogWriter :: SetSMTPSettings(char * host, 
								  unsigned short port,
								  SMTP_SECURITY_TYPE security,
								  bool authenticate, 
								  char * login,
								  char * password,
								  char * sender, 
								  char * recipient, 
								  char * subject)
{
	LOCK_SECTION(mailGuard);
	LogWriter :: SetSMTPSettings(host, port, security, authenticate, login, password, sender, recipient, subject);
}

/****************************************************************

   Class : SafeLogWriter

   Method : SendMail

   Parameters :
			Input : 
				message - message for sending by e-mail

   Returns : error code

   Description : Send message by e-mail

*****************************************************************/
int SafeLogWriter :: SendMail(char * message)
{
	LOCK_SECTION(mailGuard);
	return LogWriter :: SendMail(message);
}