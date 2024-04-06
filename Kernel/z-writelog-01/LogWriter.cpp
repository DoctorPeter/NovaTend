/****************************************************************

   Solution : NovaTend

   Project : z-writelog-01.dll

   Module : LogWriter.cpp

   Description :  this module implements methods of
				  class LogWriter

*****************************************************************/

#include "stdafx.h"
#include "LogWriter.h"

#include <Encryptor.h>

#include <stdio.h>
#include <time.h>

extern DLL_COMMON_DEFINITION zWriteLogDllDefinition;

/****************************************************************

   Class : LogWriter

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				fileName - name of Log-file
				fixedSize - LOG-file fixed size value

*****************************************************************/
LogWriter :: LogWriter(unsigned long dllUserID, char * fileName, unsigned int fixedSize) : SystemBase(dllUserID, &zWriteLogDllDefinition)
{
	smtpClient = NULL;
	SetMode(LOG_MODE_WRITE_TO_FILE);
	SetFileName(fileName);
	this -> fixedSize = fixedSize;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WRITELOG)
		WriteToLog("LogWriter : constructor");
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
				fixedSize - LOG-file fixed size value

*****************************************************************/
LogWriter :: LogWriter(unsigned long dllUserID, unsigned short mode, char * fileName, unsigned int fixedSize) : SystemBase(dllUserID, &zWriteLogDllDefinition)
{
	smtpClient = NULL;
	SetMode(mode);
	if (mode & LOG_MODE_SEND_MAIL) smtpClient = new SmtpClient(zWriteLogDllDefinition.dllID);
	SetFileName(fileName);
	this -> fixedSize = fixedSize;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WRITELOG)
		WriteToLog("LogWriter : constructor");
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
LogWriter :: LogWriter(unsigned long dllUserID,
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
					   unsigned int fixedSize) : SystemBase(dllUserID, &zWriteLogDllDefinition)
{
	SetFileName(fileName);

	smtpClient = NULL;
	SetMode(mode);

	if (!(mode & LOG_MODE_SEND_MAIL)) AddMode(LOG_MODE_SEND_MAIL);

	smtpClient = new SmtpClient(zWriteLogDllDefinition.dllID, host, port, security, authenticate, login, password);
	SetSMTPSettings(host, port, security, authenticate, login, password, sender, recipient, subject);

	this -> fixedSize = fixedSize;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WRITELOG)
		WriteToLog("LogWriter : constructor");
	#endif
}

/****************************************************************

   Class : LogWriter

   Method : Destructor

*****************************************************************/
LogWriter :: ~LogWriter(void)
{
	if (smtpClient)	
		delete smtpClient;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WRITELOG)
		WriteToLog("LogWriter : destructor");
	#endif
}

/****************************************************************

   Class : LogWriter

   Method : SetFileName

   Parameters :
			Input : 
				fileName - name of Log-file
	
	Description :  Set name of Log-file

*****************************************************************/
void LogWriter :: SetFileName(char * fileName)
{
	strcpy(this -> fileName, fileName);
}

/****************************************************************

   Class : LogWriter

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
void LogWriter :: SetSMTPSettings(char * host, 
								  unsigned short port,
								  SMTP_SECURITY_TYPE security,
								  bool authenticate, 
								  char * login,
								  char * password,
								  char * sender, 
								  char * recipient, 
								  char * subject)
{
	if ((mode & LOG_MODE_SEND_MAIL) && (smtpClient))
	{
		smtpClient -> SetSmtpSettings(subject, sender, recipient, login, password, authenticate, host, port, security);
	}
}

/****************************************************************

	Class : LogWriter

	Method : WriteToLog

	Returns : TRUE - if current log-file is no bigger 
	                 then fixedSize value

	Description : Check LOG-file size

*****************************************************************/
bool LogWriter :: CheckFileSize(void)
{
	FILE * pFile = NULL;
	pFile = fopen(fileName, "rb");
	int size = 0;

	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		size = ftell(pFile);
		fclose(pFile);
	}

	return (size < fixedSize) ? true : false;
}

/****************************************************************

	Class : LogWriter

	Method : WriteToLog

	Returns : New file name

	Description : Change file name

*****************************************************************/
char * LogWriter :: ChangeFileName(void)
{
	// Copy current name to tmp buffer
	char tmpFileName[MAX_PATH] = "";
	strcpy(tmpFileName, fileName);

	// Delete file extention
	for (int i = strlen(tmpFileName) - 1; i >= 0; i--)
	{
		if (tmpFileName[i] == '.')
		{
			tmpFileName[i] = '\0';
			break;
		}
	}

	// Find number of file with fixed size
	bool noNumber = true;
	if (tmpFileName[strlen(tmpFileName) - 1] == ')')
	{
		int pos = -1;
		for (int i = strlen(tmpFileName) - 1; i >= 0; i--)
		{
			if (tmpFileName[i] == '(')
			{
				pos = i;
				break;
			}
		}

		if (pos != -1)
		{
			// Get number
			char sNumber[16] = "";
			strncpy(sNumber, tmpFileName + pos + 1, strlen(tmpFileName) - pos - 2);

			tmpFileName[pos] = '\0';

			// Convert string number to int
			char* ends;
			int num = strtol(sNumber, &ends, 10);

			// If convetion result is OK
			if (*ends == 0)
			{
				// Increment of number
				num += 1;

				itoa(num, sNumber, 10);
				strcat(tmpFileName, "(");
				strcat(tmpFileName, sNumber);
				strcat(tmpFileName, ").log");

				noNumber = false;
			}
			else
			{
				strcat(tmpFileName, "(");
				strcat(tmpFileName, sNumber);
				strcat(tmpFileName, ")");
			}

		}
	}

	// Add first number
	if (noNumber)
	{
		strcat(tmpFileName, "(1).log");
	}

	// Back to the fileName
	strcpy(fileName, tmpFileName);

	// Return fileName
	return fileName;
}

/****************************************************************

   Class : LogWriter

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Description : Write message to log-file

*****************************************************************/
int LogWriter :: WriteToLog(char * message)
{
	int iResult = LOG_FILE_WRITE_OK;

	// Message buffer
	char recordText[MAX_DATA_BUFFER_LEN];

	//Prepare log message
	
	// Get current time
	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);
    char timeBuf[32];                                
    
	// Prepare message
	strftime(timeBuf, 32, "%m.%d.%Y %I:%M %p", timeinfo); 
	sprintf(recordText, "[%s]  >> %s \n", timeBuf, message);
		

	//Out to console
	if(mode & LOG_MODE_WRITE_TO_CONSOLE)
	{
		fprintf(stdout, recordText);
	}

	//Write to file
	if(mode & LOG_MODE_WRITE_TO_FILE)
	{
		if(mode & LOG_MODE_ENCRYPT_MESSAGES)
			//With encryption
			iResult |= WriteToFileWithEncryption(recordText);
		else
			//Without ecnryption
			iResult |= WriteToFile(recordText);
	}

	//Send e-mail
	if(mode & LOG_MODE_SEND_MAIL)
	{
		iResult |= SendMail(recordText);
	}

	return iResult;
}

/****************************************************************

   Class : LogWriter

   Method : WriteToFile

   Parameters :
			Input : 
				message - message for writting into log-file

   Returns : error code

   Description : Write message to log-file

*****************************************************************/
int LogWriter :: WriteToFile(char * message)
{
	// If using fixed size if LOG-file
	if (fixedSize > 0)
	{
		// Check file size
		while (!CheckFileSize())
		{
			//Change file name
			ChangeFileName();
		}
	}
	
	// Open file
	FILE * hFile = fopen(fileName, "a");

	// Check legal user
	hFile += dllUserCheckResult;

	if (hFile)
	{
		// Write message to file
		size_t recordSize = strlen(message);
		if (fwrite(message, 1, recordSize, hFile) != recordSize)
		{
			fclose(hFile);
			return LOG_FILE_WRITE_ERROR;
		}

		// Close file
		fclose(hFile);
		
	} else 
		return LOG_FILE_OPEN_ERROR;

	return LOG_FILE_WRITE_OK;
}

/****************************************************************

   Class : LogWriter

   Method : SendMail

   Parameters :
			Input : 
				message - message for sending by e-mail

   Returns : error code

   Description : Send message by e-mail

*****************************************************************/
int LogWriter :: SendMail(char * message)
{
	int iResult = LOG_FILE_WRITE_OK;
	
	if ((mode & LOG_MODE_SEND_MAIL) && (smtpClient))
	{
		//disable LOG_MODE_SEND_MAIL
		RemoveMode(LOG_MODE_SEND_MAIL);

		try
		{
			smtpClient -> Send(message);
		}
		catch(...)
		{
			WriteToLog("Log writer ->> SMTP error! Can't send message!");
			iResult |= LOG_SEND_MAIL_ERROR;
		}

		//enable LOG_MODE_SEND_MAIL
		AddMode(LOG_MODE_SEND_MAIL);
	}
	
	return iResult;
}

/****************************************************************

   Class : LogWriter

   Method : WriteToFileWithEncryption

   Parameters :
			Input : 
				message - message for encrypting and saving

   Returns : error code

   Description : Write encryptd message to log-file

*****************************************************************/
int LogWriter :: WriteToFileWithEncryption(char * message)
{
	if (fixedSize > 0)
	{
		// Check file size
		while (!CheckFileSize())
		{
			//Change file name
			ChangeFileName();
		}
	}

	int iResult = LOG_FILE_WRITE_OK;

	unsigned char packedData[MAX_DATA_BUFFER_LEN];
	memset(packedData, 0, sizeof(packedData));
	int packedDataLength = 0;

	Encryptor * encryptor = new Encryptor(zWriteLogDllDefinition.dllID);
	if(!(encryptor -> EncryptAndPackSecurityData((unsigned char *)message, strlen(message), packedData, sizeof(packedData), &packedDataLength)))
	{
		// Open file
		FILE * hFile = fopen(fileName, "ab");

		// Check legal user
		hFile += dllUserCheckResult;

		if (hFile)
		{
			char sep = LOG_ENCRYPTION_SEPARATOR;
			unsigned char msgBlock[MAX_DATA_BUFFER_LEN + 1];
					
			//Prepare data
			memset(msgBlock, 0, sizeof(msgBlock));

			memcpy(msgBlock, &sep, sizeof(sep));
			memcpy(msgBlock + sizeof(sep), &packedDataLength, sizeof(packedDataLength));
			memcpy(msgBlock + sizeof(sep) + sizeof(packedDataLength), packedData, packedDataLength);
			
			unsigned long msgBlockLength = sizeof(sep) + sizeof(packedDataLength) + packedDataLength;

			//Save data
			if (fwrite(msgBlock, 1, msgBlockLength, hFile) != msgBlockLength)
			{
				iResult = LOG_FILE_WRITE_ERROR;
			}

			fclose(hFile);
		}
		
	}
	else
		iResult = LOG_ENCRYPTION_ERROR;

	delete	encryptor;
	
	return	iResult;
}

/****************************************************************

   Class : LogWriter

   Method : GetMode

   Returns: work mode

   Description :  Get Log-writer work mode

*****************************************************************/
unsigned short LogWriter :: GetMode()
{
	return mode;
}

/****************************************************************

   Class : LogWriter

   Method : SetMode

   Parameters:
			Input:
				mode - work mode

  Returns: old work mode

  Description :  Set Log-writer work mode

*****************************************************************/
unsigned short LogWriter :: SetMode(unsigned short mode)
{
	unsigned short oldMode = this -> mode;
	this -> mode = mode;
	return oldMode;
}

/****************************************************************

   Class : LogWriter

   Method : AddMode

   Parameters:
			Input:
				mode - work mode

  Description :  Add mode to current Log-writer state

*****************************************************************/
void LogWriter :: AddMode(unsigned short mode)
{
	this -> mode |= mode;
}

/****************************************************************

   Class : LogWriter

   Method : RemoveMode

   Parameters:
			Input:
				mode - work mode

  Description :  Remove mode from current Log-writer state

*****************************************************************/
void LogWriter :: RemoveMode(unsigned short mode)
{
	this -> mode ^= mode;
}