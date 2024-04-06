/****************************************************************

   Solution : NovaTend

   Project : z-email-01.dll

   Module : SmtpClient.h

   Description :  this module defines interface of
				  class SmtpClient

*****************************************************************/

#ifndef SMTP_CLIENT_H
#define SMTP_CLIENT_H

#include "SmtpClientBase.h"


/****************************************************************

   Class : SmtpClient

   Description : SMTP client class

*****************************************************************/
class EMAIL_API SmtpClient : public SmtpClientBase
{
	public:
		
		// Constructor
		SmtpClient(unsigned long dllUserID);

		// Constructor
		SmtpClient(unsigned long dllUserID,
				   char * host, 
				   unsigned short port = 0,
				   SMTP_SECURITY_TYPE security = DO_NOT_SET,
				   bool authenticate = true, 
				   char * login = NULL,
				   char * password = NULL);

		// Destructor
		virtual ~SmtpClient(void);

		// Connnect to remote SMTP server
		virtual bool ConnectToSMTPServer(void);

		virtual bool ConnectToSMTPServer(char * host, 
										 unsigned short port = 0,
										 SMTP_SECURITY_TYPE security = DO_NOT_SET,
										 bool authenticate = true, 
										 char * login = NULL,
										 char * password = NULL);
	
		// Disconnect from remote server
		virtual void DisconnectFromSMTPServer(void);

		// Send mail
		virtual bool Send(char * body);
		virtual bool Send(char * sender, char * recipient, char * subject, char * body);
		virtual bool Send(char * subject, char * body);
};

#endif