/****************************************************************

   Solution : NovaTend

   Project : z-sms-01.dll

   Module : SMSManager.h

   Description :  this module defines interface of
				  class SMSManager

*****************************************************************/

#include "stdafx.h"

#include <SystemBase.h>
#include <LogWriter.h>

#include "SMSDataDef.h"


#ifdef ZSMS01_EXPORTS
#define SMS_API __declspec(dllexport)
#else
#define SMS_API __declspec(dllimport)
#endif

#ifndef SMS_MANAGER_H
#define SMS_MANAGER_H

/****************************************************************

   Class : SMSManager

   Description : Abstract class. Designed as general structure of 
				 class that responsible for SMS sending

*****************************************************************/
class SMS_API SMSManager : public SystemBase
{
	protected:

		// Log writer instance
		LogWriter * logWriter;

	public:
		// Constructor
		SMSManager(unsigned long dllUserID, LogWriter * logWriter);
		
		// Destructor
		virtual ~SMSManager(void);

		// Login		
		virtual int Login(char * login, char * password) = 0;

		// Logout
		virtual void Logout(void) = 0;
		
		//Send SMS
		virtual int SendSMS(char * number, char * msg) = 0;

		// Get SMS threads
		virtual PSMS_THREADS GetSMSThreads(void) = 0;

		// Get SMS inbox
		virtual PSMS_MESSAGES_LIST GetSMSInbox(char * number) = 0;

		// Get SMS outbox
		virtual PSMS_MESSAGES_LIST GetSMSOutbox(char * number) = 0;

		// Delete SMS threads
		virtual PSMS_THREADS DeleteSMSThreads(PSMS_THREADS smsThreads) = 0;

		// Delete SMS list
		virtual PSMS_MESSAGES_LIST DeleteSMSList(PSMS_MESSAGES_LIST smsList) = 0;
						
		// Write message to log-file
		int WriteToLog(char * message);
};

#endif