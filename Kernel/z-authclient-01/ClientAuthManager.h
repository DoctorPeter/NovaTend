/****************************************************************

   Solution : NovaTend

   Project : z-authclient-01.dll

   Module : ClientAuthManager.h

   Description : this module defines interface of
				  class ClientAuthManager

*****************************************************************/
#include <CommandManager.h>
#include <AuthenticateManager.h>

#ifdef ZAUTHCLIENT01_EXPORTS
#define CLIENTAUTHMANAGER_API __declspec(dllexport)
#else
#define CLIENTAUTHMANAGER_API __declspec(dllimport)
#endif

#ifndef CLIENTAUTHMANAGER_H
#define CLIENTAUTHMANAGER_H

/****************************************************************

   Class : ClientAuthManager 

   Description : responsible for management
				 of all process of authentification
				 for Windows OS on client side

*****************************************************************/
class CLIENTAUTHMANAGER_API ClientAuthManager : public AuthenticateManager
{
	protected:

		// command manager instance
		CommandManager * commandManager;

	public:

		// Constructor
		ClientAuthManager(unsigned long dllUserID, 
						  LogWriter * logWriter,
						  CommandManager * commandManager);

		// Copy constructor
		ClientAuthManager(const ClientAuthManager & src);

		// Destructor
		virtual ~ClientAuthManager(void);

		// Clone object
		virtual AuthenticateManager * Clone(void);
				
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

		// Valdate user custom password
		virtual int ValidateUserCustomPassword(int userID, int authSystemID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList, PUSER_SECURITY_DATA securityData);

		// Reset user custom password
		virtual int ResetUserCustomPassword(int userID);

		// Validate user account
		virtual int ValidateUserAccount(unsigned char * userName, int userNameLen, unsigned char * userPassword, int userPasswordLen, int authSystemID);

		// Save to database user notification history
		virtual bool SaveUserNotificationHistory(int userID, int noticeID);

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
};

#endif