/****************************************************************

   Solution : NovaTend

   Project : z-writelog-01.dll

   Module : SafeLogWriter.h

   Description :  this module defines interface of
				  class SafeLogWriter

*****************************************************************/

#include "stdafx.h"
#include "LogWriter.h"

#ifndef SAFELOGWRITER_H
#define SAFELOGWRITER_H

/****************************************************************

   Class : SafeLogWriter

   Description : write messages to Log-file.
                 Protects the recording process to 
				 the file through the use of WINDOWS 
				 CRITICAL SECTIONS.

*****************************************************************/
class LOGWRITER_API SafeLogWriter : public LogWriter
{
	protected:
		
		// Send message by e-mail
		virtual int SendMail(char * message);

	private:
		
		// Critical section for file protection
		CriticalSection * fileGuard;

		// Critical section for mode protection
		CriticalSection *  modeGuard;

		// Critical section for mode protection
		CriticalSection *  mailGuard;
	
	public:

		// Constructor
		SafeLogWriter(unsigned long dllUserID, char * fileName, unsigned int fixedSize = 0);
		SafeLogWriter(unsigned long dllUserID, unsigned short mode, char * fileName, unsigned int fixedSize = 0);
		SafeLogWriter(unsigned long dllUserID,
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
					  unsigned int fixedSize = 0);

		// destructor
		virtual ~SafeLogWriter(void);

		// Set name of Log-file
		virtual void SetFileName(char * fileName);

		// Set SMTP settings
		virtual void SetSMTPSettings(char * host, 
							 unsigned short port,
							 SMTP_SECURITY_TYPE security,
							 bool authenticate, 
							 char * login,
							 char * password,
							 char * sender, 
							 char * recipient, 
							 char * subject);

		// Get mode
		virtual unsigned short GetMode();

		// Set mode
		virtual unsigned short SetMode(unsigned short mode);
		
		//Add mode
		virtual void AddMode(unsigned short mode);

		//Remove mode
		virtual void RemoveMode(unsigned short mode);

		// Write message to Log-file
		virtual int WriteToLog(char * message);
};

#endif