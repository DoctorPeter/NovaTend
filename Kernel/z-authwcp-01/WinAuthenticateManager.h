/****************************************************************

   Solution : NovaTend

   Project : z-authwcp-01.dll

   Module : WinAuthenticateManager.h

   Description : this module defines interface of
				  class WinAuthenticateManager

*****************************************************************/
#include <CommandManager.h>
#include <ClientAuthManager.h>
#include <WinCPScreenBuilder.h>
#include <SerializationManager.h>
#include <Encryptor.h>
#include <LM.h>

#ifdef ZAUTHWCP01_EXPORTS
#define WINAUTHENTICATEMANAGER_API __declspec(dllexport)
#else
#define WINAUTHENTICATEMANAGER_API __declspec(dllimport)
#endif


#ifndef WINAUTHENTICATEMANAGER_H
#define WINAUTHENTICATEMANAGER_H

/****************************************************************

   Class : WinAuthenticateManager 

   Description : responsible for general management
				 of all process of authentification
				 for Windows OS

				 This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class WINAUTHENTICATEMANAGER_API WinAuthenticateManager : public ClientAuthManager
{
	private:
		
		// Post Login flag
		bool postLogin;

		// Encryptor instance
		Encryptor * encryptor;

		// Pointer to user screen container
		PUSER_SCREEN_CONTAINER userScreenContainer;

		// Symbol boxes list pointer
		PUTF8_STRINGS_MATRIX_LIST symbolMatrixesList;

		// Screen builder instance
		WinCPScreenBuilder * screenBuilder;

		// Recreate local user account
		NET_API_STATUS CreateWinLocalUser(WCHAR * userName, WCHAR * userPassword);

		// Encrypt authenticate element
		bool EncryptAuthElement(WCHAR * objectName, WCHAR * objectValue, PAUTH_ELEMENT pAuthElem);
		
		// Decrypt user list
		bool DecryptUserList(void);

		// Validate main password
		int ValidateLocalMainPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, char * userPassword, tm * timeinfo);

		// Validate temporary pasword
		int ValidateLocalTempPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, char * userPassword, tm * timeinfo);

		// Check time period
		bool CheckTimePeriod(int period, char * data);

		// Check post login flag
		bool CheckPostLogin(PPRESET_CONTAINER content);

	public:

		// Constructor
		WinAuthenticateManager(unsigned long dllUserID, 
							   LogWriter * logWriter,
	  						   CommandManager * commandManager);

		// Copy constructor
		WinAuthenticateManager(const WinAuthenticateManager & src);

		// Destructor
		virtual ~WinAuthenticateManager(void);

		// Clone object
		virtual AuthenticateManager * Clone(void);



		// Create authentication container
		virtual PAUTH_CONTAINER CreateAuthContainer(void);

		// Create answer container
		virtual PANSWER_CONTAINER CreateEducationContainer(void);

	

		// Get index of password field
		virtual int GetPasswortTextFieldIndex(void);

		// Get index of user name field
		virtual int GetLoginTextFieldIndex(void);

		// Get index of domain name field
		virtual int GetDomainTextFieldIndex(void);

		// Get index of password window (symbol boxes)
		int GetSymbolBoxPasswordWindowIndex(void);

		// Get user list container
		virtual PUSER_LIST GetUserListContainer(void);

		// Find user in user list
		int FindUser(char * userName);

		// Get list of doamin names
		void EnumDomainNames(WCHAR * lookedDomainName);
		
		// Set name to user name box
		void SetUserNameFieldValue(PWSTR userName);

		// Encrypt user string
		bool EncryptWCHARString(WCHAR * srcStr, unsigned char * encStr, int * encStrLen);

		// Decrypt user string
		bool DecryptWCHARString(WCHAR * destStr, unsigned char * encStr, int encStrLen);

		// Compare two WCHAR strings
		bool StringsAreEqual(WCHAR * str1, WCHAR * str2);

		// Compare two char strings
		bool StringsAreEqual(char * str1, char * str2);

		// Get user local screen container
		PUSER_SCREEN_CONTAINER GetUserLocalScreenContainer(void);

		// Get user screen container
		PUSER_SCREEN_CONTAINER GetUserScreenContainer(void);

		// Get user screen container
		PUSER_SCREEN_CONTAINER GetUserScreenContainer(PPRESET_CONTAINER content);

		// Get user screen container
		PUSER_SCREEN_CONTAINER GetUserScreenContainer(int userID);

		// Get user screen container
		PUSER_SCREEN_CONTAINER GetUserScreenContainer(CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus, int authSystemID);
		
		// Get user screen container pointer
		PUSER_SCREEN_CONTAINER GetUserScreenContainerPointer(void);

		// Get symbol boxes list pointer
		PUTF8_STRINGS_MATRIX_LIST GetSymbolBoxesListPointer(void);

		
		// User data validation

		// Validate user parameters
		int ValidateParams(void);

		// Validate user answers
		int ValidateAnswers(void);

		// Legal disclaimer confirmation
		int ConfirmLegalDisclaimer(int userID);


		// Local users management

		// Get list of local users
		PUSER_LIST GetLocalUserList(void);

		// Get local user descriptor
		PUSER_DESCRIPTOR GetLocalUserDescriptor(int userID);

		// Get local user descriptor
		PUSER_DESCRIPTOR GetLocalUserDescriptor(WCHAR * sysUserName);

		// Save local user account
		bool SaveLocalUser(PUSER_DESCRIPTOR pUser, bool createAccount);

		// Save local user security data
		bool SaveLocalUserSecurityData(PUSER_SECURITY_DATA pSecurityData);

		// Validate constructed password for local user
		int ValidateLocalUserCustomPassword(PUSER_DESCRIPTOR pUser, char * userPassword, tm * timeinfo, PUSER_SECURITY_DATA securityData);

		// Save data of last logged user
		bool SaveLoggedUserData(int userID, int authSystemID);

		//Set post login program to windows auto start
		bool SetAutoStartPostLogin(void);
};

#endif