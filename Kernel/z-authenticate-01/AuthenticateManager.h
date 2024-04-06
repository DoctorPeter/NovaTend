/****************************************************************

   Solution : NovaTend

   Project : z-authenticate-01.dll

   Module : AuthenticateManager.h

   Description : this module defines interface of
				  class AuthenticateManager

*****************************************************************/
#include <LogWriter.h>
#include <ContentDataDef.h>
#include <ValidationDataDef.h>
#include <SerializationDef.h>
#include <SchedulerDef.h>

#include <time.h>
#include <stdlib.h>

#ifdef ZAUTHENTICATE01_EXPORTS
#define AUTHENTICATEMANAGER_API __declspec(dllexport)
#else
#define AUTHENTICATEMANAGER_API __declspec(dllimport)
#endif

#ifndef AUTHENTICATEMANAGER_H
#define AUTHENTICATEMANAGER_H

/****************************************************************

   Class : AuthenticateManager 

   Description : responsible for general management
				 of all process of authentification

*****************************************************************/
class AUTHENTICATEMANAGER_API AuthenticateManager : public SystemBase
{
	protected:		
		
		// Pointer to log writer instance
		LogWriter * logWriter;

		// Pointer to user content container
		PPRESET_CONTAINER content;
		
		//Pointer to user list container
		PUSER_LIST userListContainer;

		// Pointer to user descriptor
		PUSER_DESCRIPTOR currentUser;

		// Pointer to authentication container
		PAUTH_CONTAINER authContainer;

		// Pointer to answer container
		PANSWER_CONTAINER eduContainer;


	public:
		
		// Constructor
		AuthenticateManager(unsigned long dllUserID, LogWriter * logWriter);

		// Copy constructor
		AuthenticateManager(const AuthenticateManager & src);

		// Destructor
		virtual ~AuthenticateManager(void);

		// Clone object
		virtual AuthenticateManager * Clone(void);



		// Create authentication container
		virtual PAUTH_CONTAINER CreateAuthContainer(void);

		// Delete authentication container
		virtual PAUTH_CONTAINER DeleteAuthContainer(void);

		// Create answer container
		virtual PANSWER_CONTAINER CreateEducationContainer(void);

		// Delete education container
		virtual PANSWER_CONTAINER DeleteEducationContainer(void);


		
		// Delete user content container
		virtual PPRESET_CONTAINER DeleteContent(void);

		// Delete user list container
		virtual PUSER_LIST DeleteUserListContainer(void);

		// Delete user descriptor
		virtual PUSER_DESCRIPTOR DeleteUserDescriptor(void);



		// Delete user content container
		virtual PPRESET_CONTAINER DeleteContent(PPRESET_CONTAINER content);

		// Delete user list container
		virtual PUSER_LIST DeleteUserListContainer(PUSER_LIST userListContainer);

		// Delete user descriptor
		virtual PUSER_DESCRIPTOR DeleteUserDescriptor(PUSER_DESCRIPTOR pUser);
		
		// Delete authentication container
		virtual PAUTH_CONTAINER DeleteAuthContainer(PAUTH_CONTAINER authContainer);

		// Delete education container
		virtual PANSWER_CONTAINER DeleteEducationContainer(PANSWER_CONTAINER eduContainer);

		// Delete list of symbol boxes
		virtual PUTF8_STRINGS_MATRIX_LIST DeleteUTF8MatrixList(PUTF8_STRINGS_MATRIX_LIST symbolBoxesList);


		
		// Get index of password field
		virtual int GetPasswortTextFieldIndex(void);

		// Get index of user name field
		virtual int GetLoginTextFieldIndex(void);

		// Get index of domain name field
		virtual int GetDomainTextFieldIndex(void);

		

		// Get user list container pointer 
		PUSER_LIST GetUserListContainerPointer(void);

		// Get user content pointer 
		PPRESET_CONTAINER GetContentPointer(void);

		// Get user descriptor pointer
		PUSER_DESCRIPTOR GetUserDescriptorPointer(void);


		
		// Check access to server
		virtual bool CheckServerAccess(void);

		// Get user content
		virtual PPRESET_CONTAINER GetUserContent(void);
		
		// Get user content
		virtual PPRESET_CONTAINER GetUserContent(char * compName, int userID, int osID);

		// Save date of last sign in 
		virtual bool SetUserSignInDate(int userID, int authSystemID);

		// Get user list container
		virtual PUSER_LIST GetUserListContainer(void);

		// Get user descriptor
		virtual PUSER_DESCRIPTOR GetUserDescriptor(int userID);

		// Get user descriptor
		virtual PUSER_DESCRIPTOR GetUserDescriptor(unsigned char * userName, int userNameLen);

		// Get user descriptor
		virtual PUSER_DESCRIPTOR GetUserDescriptor(unsigned char * userName, int userNameLen, int authSystemID);

		// Validate user parameters
		virtual int ValidateParams(int userID, char * compName, PAUTH_CONTAINER authContainer);

		// Validate user answers
		virtual int ValidateAnswers(int userID, char * compName, PANSWER_CONTAINER eduContainer);

		// Check schedule records
		virtual int CheckScheduleRecords(int userID, char * compName, int funcID);

		// Validate user custom password
		virtual int ValidateUserCustomPassword(int userID, int authSystemID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList, PUSER_SECURITY_DATA securityData);

		// Reset user custom password
		virtual int ResetUserCustomPassword(int userID);

		// Validate user account
		virtual int ValidateUserAccount(unsigned char * userName, int userNameLen, unsigned char * userPassword, int userPasswordLen, int authSystemID);

		// Save to database user notification history
		virtual bool SaveUserNotificationHistory(int userID, int noticeID);

		// Check license info
		virtual bool CheckLicense(PCLIENT_DESCRIPTION pClient);

		// Get DB connection
		virtual PUSER_DB_ACCESS_INFO GetDBAccess(int userID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList);

		// Is it first sign in for today
		virtual bool FirstUserSignInToday(int userID, int authSystemID);

		// Get authentication system ID
		virtual int GetAuthSystemID(unsigned char * encSystemSettings, int encSystemSettingsLen, int authSystemType);

		// Lock CTRL+ALT+DEL
		virtual bool LockCtrlAltDelActions(bool lock, char * userName);

		// Get list of files in some remote directory
		virtual PFOLDER_INFO_CONTAINER GetFileList(char * dirPath, int maxFileCount = MAX_DIR_FILES_COUNT);

		// Download file
		virtual long long DownloadFile(char * filePath);

		// Upload file
		virtual bool UploadFile(char * filePath, long long fileSize);

		// Download block of file
		virtual char * DownloadBlockFile(char * filePath, int blockNUmber, int * blockSize);

		// Upload block of file
		virtual bool UploadBlockFile(char * filePath, int blockNUmber, int blockSize, char * blockData);
		

		// Write message to log-file
		int WriteToLog(char * message);
};

#endif