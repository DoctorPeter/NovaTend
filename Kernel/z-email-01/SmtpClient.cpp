/****************************************************************

   Solution : NovaTend

   Project : z-email-01.dll

   Module : SmtpClient.cpp

   Description :  this module implements methods of
				  class SmtpClient

*****************************************************************/
#include "stdafx.h"
#include "SmtpClient.h"

/****************************************************************

   Class : SmtpClient

   Method : Constructor

*****************************************************************/
SmtpClient :: SmtpClient(unsigned long dllUserID) : SmtpClientBase(dllUserID)
{
}

/****************************************************************

   Class : SmtpClient

   Method : Constructor

   Parameters:
			Input:
				host - SMTP server address
				port - SMTP server port
				security - security settings
				authenticate - authenticate flag
				login - login
				password - password

*****************************************************************/
SmtpClient :: SmtpClient(unsigned long dllUserID,
						 char * host, 
						 unsigned short port,
						 SMTP_SECURITY_TYPE security,
						 bool authenticate, 
						 char * login,
						 char * password) : SmtpClientBase(dllUserID) 
{
	ConnectToSMTPServer(host, port, security, authenticate, login, password);
}

/****************************************************************

   Class : SmtpClient

   Method : Destructor

*****************************************************************/
SmtpClient :: ~SmtpClient(void)
{
	DisconnectFromSMTPServer();
}

/****************************************************************

   Class : SmtpClient

   Method : ConnectToSMTPServer

   Description: Connect to SMTP server with predefined settings

*****************************************************************/
bool SmtpClient :: ConnectToSMTPServer(void)
{
	if (connected)
		DisconnectFromSMTPServer();
	
	connected = smtp -> ConnectRemoteServer(host, port, security, authenticate, login, password);

	return connected;
}

/****************************************************************

   Class : SmtpClient

   Method : ConnectToSMTPServer

   Parameters:
			Input:
				host - SMTP server address
				port - SMTP server port
				security - security settings
				authenticate - authenticate flag
				login - login
				password - password

   Description: Connect to SMTP server

*****************************************************************/
bool SmtpClient :: ConnectToSMTPServer(char * host, 
									   unsigned short port,
									   SMTP_SECURITY_TYPE security,
									   bool authenticate, 
									   char * login,
									   char * password)
{
	SetSmtpSettings(NULL, NULL, NULL, login, password, authenticate, host, port, security);
	return ConnectToSMTPServer();
}

/****************************************************************

   Class : SmtpClient

   Method : DisconnectFromSMTPServer

   Description: Disconnect from remote server

*****************************************************************/
void SmtpClient :: DisconnectFromSMTPServer()
{
	if (connected)
	{
		smtp -> DisconnectRemoteServer();
		connected = false;
	}
}

/****************************************************************

   Class : SmtpClient

   Method : Send

   Parameters:
			Input:
				body - mail body

   Description: Send mail according to SMTP settings

*****************************************************************/
bool SmtpClient :: Send(char * body)
{
	try
	{
		if (connected)
		{
			smtp -> DelRecipients();
			smtp -> DelMsgLines();
	
			smtp -> SetSenderMail(sender);
			smtp -> AddRecipient(recipient);
			smtp -> SetSubject(subject);

			if (body)
				smtp -> AddMsgLine(body);

			smtp -> Send();

			return true;
		}
		else
			return false;
	}
	catch (...)
	{
		return false;
	}
}

/****************************************************************

   Class : SmtpClient

   Method : Send

   Parameters:
			Input:
				sender - sender address
				recipient - recipient address
				subject -  mail subject
				body - mail body

   Description: Send mail

*****************************************************************/
bool SmtpClient :: Send(char * sender, char * recipient, char * subject, char * body)
{
	if (connected)
	{
		SetSmtpSettings(subject, sender, recipient, NULL, NULL, this -> authenticate, NULL, this -> port, this -> security);
		return Send(body);
	}
	else
		return false;
}

/****************************************************************

   Class : SmtpClient

   Method : Send

   Parameters:
			Input:
				subject -  mail subject
				body - mail body

   Description: Send mail

*****************************************************************/
bool SmtpClient :: Send(char * subject, char * body)
{
	if (connected)
	{
		return Send(this -> sender, this -> recipient, subject, body);
	}
	else
		return false;
}