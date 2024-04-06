/****************************************************************

   Solution : NovaTend

   Project : z-setman-01.dll

   Module : SettingsManager.h

   Description : this module defines interface of
				  class SettingsManager

*****************************************************************/
#include <Windows.h>
#include <SystemBase.h>
#include <ContentDataDef.h>
#include <Encryptor.h>
#include <SerializationDef.h>

#ifdef ZSETMAN01_EXPORTS
#define SETTINGS_MANAGER_API __declspec(dllexport)
#else
#define SETTINGS_MANAGER_API __declspec(dllimport)
#endif

#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

/****************************************************************

   Class : SettingsManager 

   Description : responsible for management of the
				 system settings

*****************************************************************/
class SETTINGS_MANAGER_API SettingsManager : SystemBase
{
	private:

		// Encryptor instance
		Encryptor * encryptor;

		// Get binary value
		int GetBinaryValue(WCHAR * regKey, WCHAR * regValue, unsigned char * buffer, int * buffSize);

		// Set binary value
		int SetBinaryValue(WCHAR * regKey, WCHAR * regValue, unsigned char * buffer, int buffSize);

		// Get string value
		int GetStringValue(WCHAR * regKey, WCHAR * regValue, char * buffer);

		// Set string value
		int SetStringValue(WCHAR * regKey, WCHAR * regValue, char * buffer);

		// Get string value
		int GetEncStringValue(WCHAR * regKey, WCHAR * regValue, char * buffer);

		// Set string value
		int SetEncStringValue(WCHAR * regKey, WCHAR * regValue, char * buffer);

		// Get string value
		int GetEncStringValue(WCHAR * regKey, WCHAR * regValue, unsigned char * buffer, int * buffSize);

		// Set string value
		int SetEncStringValue(WCHAR * regKey, WCHAR * regValue, unsigned char * buffer, int buffSize);

		//Get integer value
		int GetIntValue(WCHAR * regKey, WCHAR * regValue, int * buffer);

		// Set integer value
		int SetIntValue(WCHAR * regKey, WCHAR * regValue, int buffer);

		// Get boolean value
		int GetBoolValue(WCHAR * regKey, WCHAR * regValue, bool * buffer);

		// Set boolean value
		int SetBoolValue(WCHAR * regKey, WCHAR * regValue, bool buffer);


	public:
	
		// Constructor
		SettingsManager(unsigned long dllUserID);

		// Destructor
		virtual ~SettingsManager(void);


		// Database settings

		// Get DSN
		int GetDatabaseServerName(char * srv);

		// Set DSN
		int SetDatabaseServerName(char * srv);

		// Get DSN
		int GetDatabaseSourceName(char * dsn);

		// Set DSN
		int SetDatabaseSourceName(char * dsn);

		// Get DB user name
		int GetDatabaseUserName(char * userName);

		// Set DB user name
		int SetDatabaseUserName(char * userName);

		// Get DB password
		int GetDatabasePassword(char * pwd);

		// Set DB password
		int SetDatabasePassword(char * pwd);

		// Get DB acceess data
		int GetDatabaseConnectionData(unsigned char * dbServerName, int * dbServerNameLen,  unsigned char * dbName,	int * dbNameLen, unsigned char * dbUserName, int * dbUserNameLen, unsigned char * dbPassword, int * dbPasswordLen);


		// IPC settings

		// Get server description list
		PSERVER_DESCRIPTION_LIST GetServerDescriptionList(void);

		// Get server description
		PSERVER_DESCRIPTION GetServerDescription(WCHAR * regPath, WCHAR * serverIDname);

		// Set server description
		int SetServerDescription(WCHAR * regPath, WCHAR * serverIDname, PSERVER_DESCRIPTION pServer);
				
		// Get HOST-server
		PSERVER_DESCRIPTION GetHostServer(void);

		// Get GLOBAL-server
		PSERVER_DESCRIPTION GetGlobalServer(void);

		// Get HUB-server
		PSERVER_DESCRIPTION GetHubServer(void);

		// Get DESKTOP-server
		PSERVER_DESCRIPTION GetDesktopServer(void);

		// Get HOST-server starting flag
		bool GetHostServerStartingFlag(void);

		// Set HOST-server starting flag
		int SetHostServerStartingFlag(bool value);

		// Get HUB-server starting flag
		bool GetHubServerStartingFlag(void);

		// Set HUB-server starting flag
		int SetHubServerStartingFlag(bool value);

		// Get DESKTOP-server starting flag
		bool GetDesktopServerStartingFlag(void);

		// Set DESKTOP-server starting flag
		int SetDesktopServerStartingFlag(bool value);


		// E-mail settings

		// Get e-mail host
		int GetEmailHost(char * host);

		// Set e-mail host
		int SetEmailHost(char * host);

		// Get e-mail port
		int GetEmailPort(unsigned int * port);

		// Set e-mail port
		int SetEmailPort(unsigned int port);

		// Get e-mail security type
		int GetEmailSecurityType(unsigned int * secType);

		// Set e-mail security type
		int SetEmailSecurityType(unsigned int secType);

		// Get e-mail authentication flag
		int GetEmailAuthFlag(bool * auth);

		// Set e-mail authentication flag
		int SetEmailAuthFlag(bool  auth);

		// Get e-mail login
		int GetEmailLogin(char * login);

		// Set e-mail login
		int SetEmailLogin(char * login);

		// Get e-mail password
		int GetEmailPassword(char * password);

		// Set e-mail password
		int SetEmailPassword(char * password);

		// Get e-mail sender address
		int GetEmailSenderAddress(char * sender);

		// Set e-mail sender address
		int SetEmailSenderAddress(char * sender);

		// Get e-mail recipient address
		int GetEmailRecipientAddress(char * recipient);

		// Set e-mail recipient address
		int SetEmailRecipientAddress(char * recipient);


		// Google Voice settings
		
		// Get googl voice login
		int GetGoogleVoiceLogin(char * gvoiceEmail);

		// Set googl voice login
		int SetGoogleVoiceLogin(char * gvoiceEmail);

		// Get googl voice password
		int GetGoogleVoicePassword(char * password);

		// Set googl voice password
		int SetGoogleVoicePassword(char * password);


		// LOG files settings

		// Get LOG-files encryption flag
		int GetLogEncryptFlag(bool * logEnc);

		// Set LOG-files encryption flag
		int SetLogEncryptFlag(bool  logEnc);

		// Get LOG-files messages e-mail sending flag
		int GetLogEmailSendFlag(bool * eMail);

		// Set LOG-files messages e-mail sending flag
		int SetLogEmailSendFlag(bool  eMail);

		// Get LOG-files fixed size flag
		int GetLogFixedSizeFlag(bool * logFix);

		// Set LOG-files fixed size flag
		int SetLogFixedSizeFlag(bool  logFix);

		// Get LOG-files fixed size value
		int GetLogFixedSizeValue(int * logFixVal);

		// Set LOG-files fixed size value
		int SetLogFixedSizeValue(int  logFixVal);

		// Get LOG-files storing path
		int GetLogPath(char * logPath);

		// Set LOG-files storing path
		int SetLogPath(char * logPath);


		// Synchronization settings

		// Get periodic user accounts synchronization on/off flag
		int GetPeriodicSyncOnOffFlag(bool *syncFlag);

		// Set periodic user accounts synchronization on/off flag
		int SetPeriodicSyncOnOffFlag(bool syncFlag);

		// Get logon user accounts synchronization on/off flag
		int GetLogonSyncOnOffFlag(bool *syncFlag);

		// Set logon user accounts synchronization on/off flag
		int SetLogonSyncOnOffFlag(bool syncFlag);

		// Get synchronization period
		int GetSyncPeriod(int *period);

		// Set synchronization period
		int SetSyncPeriod(int period);

		// Get last sync time
		int GetLastSyncTime(char * lastSyncTime);

		// Set last sync time
		int SetLastSyncTime(char * lastSyncTime);
		

		// Local users settings

		// Set local user data
		int SetLocalUser(PUSER_DESCRIPTOR pUser);
		
		// Set user security data
		int SetUserSecurityData(PUSER_SECURITY_DATA pSecurityData);

		// Get local user data
		PUSER_DESCRIPTOR GetLocalUser(int userID);

		// Get user security data
		PUSER_SECURITY_DATA GetUserSecurityData(int userID);
		
		// Get local user data
		PSIMPLE_USER_DESCRIPTOR GetLocalUser(char * userIDName);

		// Get local user data
		PUSER_DESCRIPTOR GetLocalUser(WCHAR * userName);

		// Create local users list
		PUSER_LIST GetLocalUsersList(void);


		// Post login settings

		//Set post login program to windows auto start
		int SetAutoStartPostLogin(void);

		// Get post login process path from windows registry
		int GetPostLoginPath(char * postLoginPath);

		// Set post login process path to windows registry
		int SetPostLoginPath(char * postLoginPath);

		// Get post login process user ID from windows registry
		int GetPostLoginUserID(int * userID);

		// Set post login process user ID to windows registry
		int SetPostLoginUserID(int userID);

		// Get post login process periodic flag from windows registry
		int GetPostLoginPeriodicFlag(bool * postFlag);

		// Set post login process periodic flag to windows registry
		int SetPostLoginPeriodicFlag(bool postFlag);

		// Get post login process period from windows registry
		int GetPostLoginPeriod(int * period);

		// Set post login process period to windows registry
		int SetPostLoginPeriod(int period);

		
		// Logged user data
		
		// Get logged user ID from windows registry
		int GetLoggedUserID(int * userID);

		// Set logged user ID to windows registry
		int SetLoggedUserID(int userID);

		// Get authentication system ID from windows registry
		int GetAuthSystemID(int * authSystemID);

		// Set authentication system ID to windows registry
		int SetAuthSystemID(int authSystemID);


		// Program controll

		// Get program controll On/Off flag
		int GetProgramControllFlag(bool * prgCtrlFlag);

		// Set program controll On/Off flag
		int SetProgramControllFlag(bool prgCtrlFlag);
		

		// File transfering settings

		// Get upload directory
		int GetUploadDirectory(char * uploadDir);

		// Set upload directory
		int SetUploadDirectory(char * uploadDir);

		// Get download directory
		int GetDownloadDirectory(char * downloadDir);

		// Set download directory
		int SetDownloadDirectory(char * downloadDir);

		// Get temporary directory
		int GetTemporaryDirectory(char * tempDir);

		// Set temporary directory
		int SetTemporaryDirectory(char * tempDir);


		// Command history settings

		// Get command history database
		int GetCmdHistDatabase(char * dbName);

		// Set command history database
		int SetCmdHistDatabase(char * dbName);

		// Get historian periodic flag from windows registry
		int GetHistorianPeriodicFlag(bool * histFlag);

		// Set historian periodic flag to windows registry
		int SetHistorianPeriodicFlag(bool histFlag);

		// Get historian period from windows registry
		int GetHistorianPeriod(int * period);

		// Set historian period to windows registry
		int SetHistorianPeriod(int period);

		// Get user enviroment command flag from windows registry
		int GetUserEnvironmentCommandFlag(bool * flag);

		// Set user enviroment command flag to windows registry
		int SetUserEnvironmentCommandFlag(bool flag);

		// Get user name command flag from windows registry
		int GetLoggedUserNameCommandFlag(bool * flag);

		// Set user name command flag to windows registry
		int SetLoggedUserNameCommandFlag(bool flag);

		// Get screenshot command flag from windows registry
		int GetScreenshotCommandFlag(bool * flag);

		// Set screenshot command flag to windows registry
		int SetScreenshotCommandFlag(bool flag);

		// Get snapshot command flag from windows registry
		int GetCamSnapshotCommandFlag(bool * flag);

		// Set snapshot command flag to windows registry
		int SetCamSnapshotCommandFlag(bool flag);


		// Update settings

		// Get update directory
		int GetUpdateDirectory(char * updateDir);

		// Set update directory
		int SetUpdateDirectory(char * updateDir);

		// Get update periodic flag from windows registry
		int GetUpdatePeriodicFlag(bool * upFlag);

		// Set update periodic flag to windows registry
		int SetUpdatePeriodicFlag(bool upFlag);

		// Get update period from windows registry
		int GetUpdatePeriod(int * period);

		// Set update period to windows registry
		int SetUpdatePeriod(int period);

		// Get list of files for update
		PFOLDER_INFO_CONTAINER GetUpdateFileList(void);

		// Set list of files for update
		int SetUpdateFileList(PFOLDER_INFO_CONTAINER pFolder);

		// Get update file info
		PFILE_INFO_CONTAINER GetUpdateFileInfo(WCHAR * regPath, WCHAR * fileIDname);

		// Set update file info
		int SetUpdateFileInfo(WCHAR * regPath, WCHAR * fileIDname, PFILE_INFO_CONTAINER pFile);

		// Get update installed flag from windows registry
		int GetUpdateInstalledFlag(bool * upFlag);

		// Set update installed flag from windows registry
		int SetUpdateInstalledFlag(bool upFlag);

		// Get updater path from windows registry
		int GetUserUpdaterPath(char * upPath);

		// Set updater path from windows registry
		int SetUserUpdaterPath(char * upPath);
};

#endif