/****************************************************************

   Solution : NovaTend

   Project : z-email-01.dll

   Module : SmtpClientBase.cpp

   Description :  this module implements methods of
				  class SmtpClientBase

*****************************************************************/

#include "stdafx.h"
#include "SmtpClientBase.h"

extern DLL_COMMON_DEFINITION zEmailDllDefinition;

/****************************************************************

   Class : SmtpClientBase

   Method : Constructor

*****************************************************************/
SmtpClientBase :: SmtpClientBase(unsigned long dllUserID) : SystemBase(dllUserID, &zEmailDllDefinition)
{
	smtp = new CSmtp();

	subject[0] = '\0';
	sender[0] = '\0';
	recipient[0] = '\0';
	login[0] = '\0';
	password[0] = '\0';
	authenticate = true;
	host[0] = '\0';
	port = 0;
	security = DO_NOT_SET;
	connected = false;
}

/****************************************************************

   Class : SmtpClientBase

   Method : Destructor

*****************************************************************/
SmtpClientBase :: ~SmtpClientBase(void)
{
	delete smtp;
}

/****************************************************************

   Class : SmtpClientBase

   Method : SetSmtpSettings

   Parameters :
			Input : 
				subject - mail subject 
	            sender - sender address
				recipient - recipient address 
				login - login for SMTP server connection
				password - password for SMTP server connection
				authenticate - SMTP connection flag 
				host - SMTP server address 
				port - SMTP server port 
				security - security settings
	
	Description :  Set SMTP configuration

*****************************************************************/
void SmtpClientBase :: SetSmtpSettings(char * subject, 
	                                   char * sender,
									   char * recipient, 
									   char * login, 
									   char * password, 
									   bool authenticate, 
									   char * host, 
									   unsigned short port, 
									   SMTP_SECURITY_TYPE security)
{
	if (subject)
		strcpy(this -> subject, subject);

	if (sender)
		strcpy(this -> sender, sender);

	if (recipient)
		strcpy(this -> recipient, recipient);

	if (login)
		strcpy(this -> login, login);

	if (password)
		strcpy(this -> password, password);

	if (host)
		strcpy(this -> host, host);

	this -> authenticate = authenticate + (bool)dllUserCheckResult;
	this -> port = port + dllUserCheckResult;
	this -> security = security;
}

/****************************************************************

   Class : SmtpClientBase

   Method : GetSmtpSettings

   Parameters :
			Output : 
				subject - mail subject 
	            sender - sender address
				recipient - recipient address 
				login - login for SMTP server connection
				password - password for SMTP server connection
				authenticate - SMTP connection flag 
				host - SMTP server address 
				port - SMTP server port 
				security - security settings
	
	Description :  Get SMTP configuration

*****************************************************************/
void SmtpClientBase :: GetSmtpSettings(char * subject, char * sender, char * recipient, char * login, char * password, bool * authenticate, char * host, unsigned short * port, SMTP_SECURITY_TYPE * security)
{
	if (subject)
		strcpy(subject, this -> subject);

	if (sender)
		strcpy(sender, this -> sender);

	if (recipient)
		strcpy(recipient, this -> recipient);

	if (login)
		strcpy(login, this -> login);

	if (password)
		strcpy(password, this -> password);

	if (host)
		strcpy(host, this -> host);

	*authenticate = this -> authenticate;
	*port = this -> port;
	*security = this -> security;
}