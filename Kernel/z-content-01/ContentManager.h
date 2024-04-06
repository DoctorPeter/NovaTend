/****************************************************************

   Solution : NovaTend

   Project : z-content-01.dll

   Module : ContentManager.h

   Description :  this module defines interface of
				  class ContentManager

*****************************************************************/
#include <LogWriter.h>
#include <DatabaseManager.h>
#include <Encryptor.h>

#include "ContentDataDef.h"

#ifdef ZCONTENT01_EXPORTS
#define CONTENTMANAGER_API __declspec(dllexport)
#else
#define CONTENTMANAGER_API __declspec(dllimport)
#endif

#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

/****************************************************************

   Class : ContentManager

   Description : retrieve user content from database

*****************************************************************/
class CONTENTMANAGER_API ContentManager : public SystemBase
{
	private:
		
		// Log writer instance
		LogWriter * logWriter;

		// Database manager instance
		DatabaseManager * dbManager;

		// Encryptor instance
		Encryptor * encryptor;


		// Connect to database
		bool DatabaseConnect(void);

		// Disconnect from database
		bool DatabaseDisconnect(void);


		// Create of container of content
		PPRESET_CONTAINER CreateContent(void);

		// Create list of users
		PUSER_LIST CreateUserList(void);
				
		// Create simple user descriptor
		PSIMPLE_USER_DESCRIPTOR CreateSimpleUserDescriptor(void);

		// Remove simple user descriptor
		PSIMPLE_USER_DESCRIPTOR RemoveSimpleUserDescriptor(PSIMPLE_USER_DESCRIPTOR user);
		
		// Get preset for this computer
		bool GetPreset(PPRESET_CONTAINER content, char * compName, int userID, int osID);

		// Get list of user screens
		bool GetUserScreens(PPRESET_CONTAINER content);

		// Get list of screen objects
		bool GetUserScreenObjects(PPRESET_CONTAINER content, int screenID);

		// Get all lists of values (comboboxes)
		bool GetListValuesSet(PPRESET_CONTAINER content);

		// Get values for objects SOT_QUESTION_TEXT and SOT_ANSWER_BOX
		bool GetEducationValues(PPRESET_CONTAINER content, int userID);

		// Get values for legal declaimer objects 
		bool GetLegalDisclaimerValues(PPRESET_CONTAINER content, int userID);

		// Get values for notification objects 
		bool GetUserNotificationValues(PPRESET_CONTAINER content, int userID);

		// Delete education objects
		void DeleteEducationScreenObjects(PPRESET_CONTAINER content);

		// Delete education objects
		void DeleteEducationScreenObjects(PPRESET_CONTAINER content, int scope);

		// Delete simple notices objects
		void DeleteSimpleNoticesScreenObjects(PPRESET_CONTAINER content);

		// Delete legal disclaimer objects
		void DeleteLegalDisclaimerScreenObjects(PPRESET_CONTAINER content);

		// Delete legal disclaimer objects
		void DeleteLegalDisclaimerScreenObjects(PPRESET_CONTAINER content, int scope);

		// Get user password construction rules
		bool GetUserPasswordConstructionRules(PUSER_SECURITY_DATA securityData);

		// Check symbol box password (one symbol per cell)
		bool CheckOneSymbolBoxPasswordConstructionRules(int * rules, int rulesCount);

		// Check symbol box password (two symbols per cell)
		bool CheckTwoSymbolsBoxPasswordConstructionRules(int * rules, int rulesCount);

		// Get user education values
		bool GetUserEducationValues(PUSER_DESCRIPTOR user);

	public:

		// Constructor
		ContentManager(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~ContentManager(void);

		
		// Create user descriptor
		PUSER_DESCRIPTOR CreateUserDescriptor(void);

		// Remove user descriptor
		PUSER_DESCRIPTOR RemoveUserDescriptor(PUSER_DESCRIPTOR user);

		// Create user security data
		PUSER_SECURITY_DATA CreateUserSecurityData(void);

		// Remove user security data
		PUSER_SECURITY_DATA RemoveUserSecurityData(PUSER_SECURITY_DATA securityData);


		// Get user ID
		int GetUserID(char * userName);

		// Get user ID
		int GetUserID(unsigned char * userName, int userNameLen);

		// Get authentication system ID
		int GetAuthSystemID(char * systemSettings, int authSystemType);

		// Get authentication system ID
		int GetAuthSystemID(unsigned char * encSystemSettings, int encSystemSettingsLen, int authSystemType);

		// Get authentication system name
		char * GetAuthSystemName(int authSystemID, char * authSystemName);

		// Get authentication system name
		char * GetAuthSystemName(int authSystemID, unsigned char * encAuthSystemName, int * encAuthSystemNameLen);


		// Get user descriptor by user ID
		PUSER_DESCRIPTOR GetUserDescriptor(int userID);

		// Get user descriptor by user name
		PUSER_DESCRIPTOR GetUserDescriptor(char * userName);

		// Get user by encrypted user name
		PUSER_DESCRIPTOR GetUserDescriptor(unsigned char * userName, int userNameLen);

		// Get user descriptor by system user name
		PUSER_DESCRIPTOR GetUserDescriptor(char * userName, int authSystemID);

		// Get user descriptor by system user name
		PUSER_DESCRIPTOR GetUserDescriptor(unsigned char * encUserName, int encUserNameLen, int authSystemID);

		// Get user security data
		PUSER_SECURITY_DATA GetUserSecurityData(int userID, int authSystemID);

		// Get user security data
		PUSER_SECURITY_DATA GetUserSecurityData(int userID);
		
		// Get user names
		bool GetUserNames(int userID, int authSystemID, unsigned char * userName, int * userNameLen, unsigned char * sysUserName, int * sysUserNameLen, unsigned char * fullUserName, int * fullUserNameLen);

		// Get list of users
		PUSER_LIST GetUserList(void);

		// Clear of list of users
		PUSER_LIST ClearUserList(PUSER_LIST userList);



		// Get default user content from database
		PPRESET_CONTAINER GetDefaultContent(void);

		// Get user content from database
		PPRESET_CONTAINER GetUserContent(char * compName, int userID, int osID, bool eduFunc, bool snFunc, bool ldFunc);
		
		// Clear of container of content
		PPRESET_CONTAINER ClearContent(PPRESET_CONTAINER content);

		// Clear user screen
		PUSER_SCREEN ClearUserScreen(PUSER_SCREEN userScreen);

		// Clear user screen object
		PSCREEN_OBJECT ClearUserScreenObject(PSCREEN_OBJECT scrObject);



		// Find user screen by type
		int FindUserScreen(PPRESET_CONTAINER content, int screenType);

		// Delete user screen by instance
		void DeleteUserScreen(PPRESET_CONTAINER content, PUSER_SCREEN userScreen);

		// Delete user screen by type
		void DeleteUserScreenByType(PPRESET_CONTAINER content, int screenType);

		// Delete user screen by index
		void DeleteUserScreenByInd(PPRESET_CONTAINER content, int screenInd);


		// Find user screen object by type
		int FindScreenObject(PUSER_SCREEN userScreen, int objectType);

		// Delete user screen object by instance
		void DeleteScreenObject(PPRESET_CONTAINER content, PSCREEN_OBJECT screenObject);

		// Delete user screen object by type
		void DeleteScreenObjectByType(PUSER_SCREEN userScreen, int objectType);

		// Delete user screen object by index
		void DeleteScreenObjectByInd(PUSER_SCREEN userScreen, int objectInd);



		// Get user permissions
		bool GetUserPermissions(int userID, int * userPermissions, int * userPermissionsCount);

		// Check database connection
		bool CheckDBAccess(void);
		
		// Save to database user notification history
		bool SaveUserNotificationHistory(int userID, int noticeID);

		// Save last sing in date
		bool SetUserSignInDate(int userID, int authSystemID);

		// Check sign in date for user in some auth system 
		bool FirstUserAuthSystemSignInToday(int userID, int authSystemID);

		// Write message to Log-file
		int WriteToLog(char * message);
};

#endif