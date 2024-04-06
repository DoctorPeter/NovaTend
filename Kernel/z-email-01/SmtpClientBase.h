/****************************************************************

   Solution : NovaTend

   Project : z-email-01.dll

   Module : SmtpClientBase.h

   Description :  this module defines interface of
				  class SmtpClientBase

*****************************************************************/
#include <SystemBase.h>

#ifdef ZEMAIL01_EXPORTS
#define EMAIL_API __declspec(dllexport)
#else
#define EMAIL_API __declspec(dllimport)
#endif

#ifndef SMTP_CLIENT_BASE_H
#define SMTP_CLIENT_BASE_H

#include "SMTP\Smtp.h"

// Restriction definitions

// Short strings
#define SHORT_SMTP_STR_LEN		256

// Long strings
#define LONG_SMTP_STR_LEN		1024


/****************************************************************

   Class : SmtpClientBase

   Description : abstract class for general SMTP client

*****************************************************************/
class EMAIL_API SmtpClientBase : public SystemBase
{
	protected:
		
		// Inner SMTP-client instance
		CSmtp * smtp;

		// Mail subject
		char subject[SHORT_SMTP_STR_LEN];

		// Sender e-mail address
		char sender[SHORT_SMTP_STR_LEN];
		
		// Recipient e-mail address
		char recipient[SHORT_SMTP_STR_LEN];

		// Login
		char login[SHORT_SMTP_STR_LEN];
		
		// Password
		char password[SHORT_SMTP_STR_LEN];

		// SMTP authentication flag
		bool authenticate;

		// SMTP server address
		char host[SHORT_SMTP_STR_LEN];
		 
		// SMTP port
		unsigned short port;
		
		// Seciruty type
		SMTP_SECURITY_TYPE security;

		// Connection flag
		bool connected;

	public:
		
		// Constructor
		SmtpClientBase(unsigned long dllUserID);

		// Destructor
		virtual ~SmtpClientBase(void);

		// Connnect to remote SMTP server
		virtual bool ConnectToSMTPServer(void) = NULL;

		virtual bool ConnectToSMTPServer(char * host, 
										 unsigned short port = 0,
										 SMTP_SECURITY_TYPE security = DO_NOT_SET,
										 bool authenticate = true, 
										 char * login = NULL,
										 char * password = NULL) = NULL;
	
		// Disconnect from remote server
		virtual void DisconnectFromSMTPServer(void) = NULL;

		// Send mail
		virtual bool Send(char * body) = NULL;
		virtual bool Send(char * sender, char * recipient, char * subject, char * body) = NULL;
		virtual bool Send(char * subject, char * body) = NULL;
	
		//Set smtp settings
		void SetSmtpSettings(char * subject = NULL, char * sender = NULL, char * recipient = NULL, char * login = NULL, char * password = NULL, bool authenticate = true, char * host = NULL, unsigned short port = 0, SMTP_SECURITY_TYPE security = DO_NOT_SET);

		//Get SMTP settings
		void GetSmtpSettings(char * subject, char * sender, char * recipient, char * login, char * password, bool * authenticate, char * host, unsigned short * port, SMTP_SECURITY_TYPE * security);
};

#endif