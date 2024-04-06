/****************************************************************

   Solution : NovaTend

   Project : z-sms-01.dll

   Module : GoogleVoiceSMSManager.h

   Description : this module defines interface of
				  class GoogleVoiceSMSManager

*****************************************************************/

#ifndef GOOGLE_VOICE_H
#define GOOGLE_VOICE_H

#include <curl\curl.h>
#include "SMSManager.h"

#include "SmsDataDef.h"

#include "json\json.h"

// Restriction definitions

// E-mail string length
#define EMAIL_LENGTH			64

// Password length
#define PWD_LENGTH				32

// Length of phone number
#define PHONE_NUM_LENGTH		16

// Session tocken length
#define SESSION_TOCKEN_LENGTH	256

// Version length
#define VERSION_LENGTH			16


// Error codes

// Success
#define GVOICE_OK					0

// CURL error
#define GVOICE_CURL_ERROR			-1

// Wrong input data
#define GVOICE_INPUT_DATA_ERROR		-2

// Login error
#define GVOICE_LOGIN_ERROR			-3

// SMS sending error
#define GVOICE_SMS_SEND_ERROR		-4

// SMS retrieving error
#define GVOICE_GET_SMS_ERROR		-5



/****************************************************************

   Class : GoogleVoice 

   Description : responsible for SMS sending

*****************************************************************/
class SMS_API GoogleVoiceSMSManager : public SMSManager
{
	private:
	
		// Create name of cookie file
		char * GetCookieFileName(char * fileName);

		// Create name of cookie time file
		char * GetCookieTimeFileName(char * fileName);

	protected:

		// CURL data
		CURL * hCURL;
		CURLcode curlCode;
	
		// Goggle Voice account data
		char email[EMAIL_LENGTH];
		char password[PWD_LENGTH];
				
		// Session token that Google needs. 
		char rnrSE[SESSION_TOCKEN_LENGTH];	

		// Log writer instance
		LogWriter * logWriter;
			
		// Version string
		char version[VERSION_LENGTH];

		// Logged in flag
		bool loggedIn;

		// Error buffer
		char errorBuffer[CURL_ERROR_SIZE];

		// Curl buffer
		char * curlBuffer;

		// Initialization
		int Init(void);

		// Login
		int Login(void);
		
		// Get cookie time
		bool ReadCookieTime(void);

		// Set cookie time
		bool WriteCookieTime(void);

		// Get page count
		int GetPageCount(void);

		// Get page count
		int GetPageCount(json_object * jobj);

		// Get SMS threads
		int GetSMSThreads(json_object * jobj, PSMS_THREADS smsThreads);
		
	public:
		
		// Constructor		
		GoogleVoiceSMSManager(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~GoogleVoiceSMSManager(void);

		// Login		
		virtual int Login(char * login, char * password);

		// Logout
		virtual void Logout(void);
		
		//Send SMS
		virtual int SendSMS(char * number, char * msg);

		// Get SMS threads
		virtual PSMS_THREADS GetSMSThreads(void);

		// Get SMS inbox
		virtual PSMS_MESSAGES_LIST GetSMSInbox(char * number);

		// Get SMS outbox
		virtual PSMS_MESSAGES_LIST GetSMSOutbox(char * number);

		// Delete SMS threads
		virtual PSMS_THREADS DeleteSMSThreads(PSMS_THREADS smsThreads);

		// Delete SMS list
		virtual PSMS_MESSAGES_LIST DeleteSMSList(PSMS_MESSAGES_LIST smsList);

		// Clear CURL buffer
		int ClearCurlBuffer(void);

		// Write data CURL callback function
		static int CurlWriter(char *data, size_t size, size_t nMemb, char ** buffer);
};

#endif