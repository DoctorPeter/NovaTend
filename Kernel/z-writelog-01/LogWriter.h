/****************************************************************

   Solution : NovaTend

   Project : z-writelog-01.dll

   Module : LogWriter.h

   Description :  this module defines interface of
				  class LogWriter

*****************************************************************/
#include "stdafx.h"
#include <SystemBase.h>
#include <SmtpClient.h>

#ifdef ZWRITELOG01_EXPORTS
#define LOGWRITER_API __declspec(dllexport)
#else
#define LOGWRITER_API __declspec(dllimport)
#endif

#ifndef LOGWRITER_H
#define LOGWRITER_H

// Definition of errors

// Succesfull write log result
#define LOG_FILE_WRITE_OK		0

// Error of Log-file opening
#define LOG_FILE_OPEN_ERROR		0x001

// Error of Log-file writing
#define LOG_FILE_WRITE_ERROR	0x002

// Error of encryptor
#define LOG_ENCRYPTION_ERROR	0x004

// Error of sending mail
#define LOG_SEND_MAIL_ERROR		0x008



// LogWriter modes definition

// Write messages to log file
#define LOG_MODE_WRITE_TO_FILE		0x001

// Write messages to console (for DEBUG)
#define LOG_MODE_WRITE_TO_CONSOLE	0x002

// Send messaes by e-mail
#define LOG_MODE_SEND_MAIL			0x004

// Encrypt messages before writting
#define LOG_MODE_ENCRYPT_MESSAGES	0x008



// Separator of encrypted message
#define LOG_ENCRYPTION_SEPARATOR	char(0xFF)



/****************************************************************

   Class : LogWriter

   Description : write messages to Log-file

*****************************************************************/
class LOGWRITER_API LogWriter : public SystemBase
{
	protected:

		// Log-file name
		char fileName[MAX_PATH];

		// SMTP client instance
		SmtpClient * smtpClient;

		// Work mode
		unsigned short mode;

		// Send message by e-mail
		virtual int SendMail(char * message);

		// Fixed size
		unsigned int fixedSize;

		// Check file size
		bool CheckFileSize(void);

		// Change file name
		char * ChangeFileName(void);
	
	private:

		// Write message to file
		int WriteToFile(char * message);

		// Write encrypted message to file
		int WriteToFileWithEncryption(char * message);

	public:
		
		// Constructor
		LogWriter(unsigned long dllUserID, char * fileName, unsigned int fixedSize = 0);
		LogWriter(unsigned long dllUserID, unsigned short mode, char * fileName, unsigned int fixedSize = 0);
		LogWriter(unsigned long dllUserID,
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

		// Destructor
		virtual ~LogWriter(void);

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