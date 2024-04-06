/****************************************************************

   Solution : NovaTend

   Project : z-authenticate-01.dll

   Module : AuthenticateManager.cpp

   Description : this module implements methods of
				  class AuthenticateManager

*****************************************************************/

#include "stdafx.h"
#include <stdio.h>
#include "AuthenticateManager.h"


// z-authenticate-01.dll definition structure
extern DLL_COMMON_DEFINITION zAuthenticateDllDefinition;


/****************************************************************

   Class : AuthenticateManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - log writer instance

*****************************************************************/
AuthenticateManager :: AuthenticateManager(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zAuthenticateDllDefinition)
{
	this -> logWriter = logWriter;

	content = NULL;
	userListContainer = NULL;
	currentUser = NULL;
	authContainer = NULL;
	eduContainer = NULL;
}


/****************************************************************

   Class : AuthenticateManager

   Method : Copy constructor

   Parameters :
			Input : 
				src - soucre instance

*****************************************************************/
AuthenticateManager :: AuthenticateManager(const AuthenticateManager & src) : SystemBase(src.dllUserID, &zAuthenticateDllDefinition)
{
	logWriter = src.logWriter;
	
	content = NULL;
	userListContainer = NULL;
	currentUser = NULL;
	authContainer = NULL;
	eduContainer = NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : Destructor

*****************************************************************/
AuthenticateManager :: ~AuthenticateManager(void)
{
	DeleteAuthContainer();
	DeleteEducationContainer();
	DeleteContent();
	DeleteUserListContainer();
	DeleteUserDescriptor();
}

/****************************************************************

   Class : AuthenticateManager

   Method : Clone

   Return : Pointer to authenticate mamanger clone object

   Description : Clone authenticate manager

*****************************************************************/
AuthenticateManager * AuthenticateManager :: Clone(void)
{
	return new AuthenticateManager(*this);
}


/****************************************************************

   Class : AuthenticateManager

   Method : CreateAuthContainer

   Return : Authenctication container pointer

   Description : Create authenticate container

*****************************************************************/
PAUTH_CONTAINER AuthenticateManager :: CreateAuthContainer(void)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteAuthContainer

   Description : Delete authenticate container

*****************************************************************/
PAUTH_CONTAINER AuthenticateManager :: DeleteAuthContainer(void)
{
	authContainer = DeleteAuthContainer(authContainer);
	return authContainer;
}

/****************************************************************

   Class : AuthenticateManager

   Method : CreateEducationContainer

   Return : Education container pointer

   Description : Create answer container

*****************************************************************/
PANSWER_CONTAINER AuthenticateManager :: CreateEducationContainer(void)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteEducationContainer

   Description : Delete education container

*****************************************************************/
PANSWER_CONTAINER AuthenticateManager :: DeleteEducationContainer(void)
{
	eduContainer = DeleteEducationContainer(eduContainer);
	return eduContainer;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteContent

   Description : Delete user content

*****************************************************************/
PPRESET_CONTAINER AuthenticateManager :: DeleteContent(void)
{
	content = DeleteContent(content);
	return content;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteUserListContainer

   Description : Delete user list container

*****************************************************************/
PUSER_LIST AuthenticateManager :: DeleteUserListContainer(void)
{
	userListContainer = DeleteUserListContainer(userListContainer);
	return userListContainer;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteUserDescriptor

   Description : Delete user list container

*****************************************************************/
PUSER_DESCRIPTOR  AuthenticateManager :: DeleteUserDescriptor(void)
{
	currentUser = DeleteUserDescriptor(currentUser);
	return currentUser;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteAuthContainer

   Parameters :
			Input : 
				authContainer - authentication container

   Description : Delete authenticate container

*****************************************************************/
PAUTH_CONTAINER AuthenticateManager :: DeleteAuthContainer(PAUTH_CONTAINER authContainer)
{
	if (authContainer) 
	{
		for (int i = 0; i < authContainer -> authElementCount; i++)
			free(authContainer -> authElements[i]);

		free(authContainer);

		authContainer = NULL;
	}

	return authContainer;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteEducationContainer

   Parameters :
			Input : 
				eduContainer - education container

   Description : Delete education container

*****************************************************************/
PANSWER_CONTAINER AuthenticateManager :: DeleteEducationContainer(PANSWER_CONTAINER eduContainer)
{
	if (eduContainer) 
	{
		for (int i = 0; i < eduContainer -> answersCount; i++)
			free(eduContainer -> answers[i]);

		free(eduContainer);

		eduContainer = NULL;
	}

	return eduContainer;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteContent

   Parameters :
			Input : 
				content - user content

   Description : Delete user content

*****************************************************************/
PPRESET_CONTAINER AuthenticateManager :: DeleteContent(PPRESET_CONTAINER content)
{
	// Validate container pointer
	if (content)
	{
		// Free user screens list
		for(int i = 0 ; i < content -> userScreensCount; i++)
		{
			if (content -> userScreens[i])
			{
				for(int j = 0; j < content -> userScreens[i] -> scrObjCount; j++)
				{
					if (content -> userScreens[i] -> screenObjects[j])
					{
						// Free screen object list values
						if (content -> userScreens[i] -> screenObjects[j] -> listValuesSet) 
							free(content -> userScreens[i] -> screenObjects[j] -> listValuesSet);

						// Free screen object text value
						if (content -> userScreens[i] -> screenObjects[j] -> textValue) 
							free(content -> userScreens[i] -> screenObjects[j] -> textValue);

						// Free screen object image value
						if (content -> userScreens[i] -> screenObjects[j] -> imgValue) 
							free(content -> userScreens[i] -> screenObjects[j] -> imgValue);

						// Free screen object
						free(content -> userScreens[i] -> screenObjects[j]);
					}
				}

				// Free user screen
				free(content -> userScreens[i]);
			}
		}
		
		// Free container
		free(content);

		content = NULL;
	}

	return content;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteUserListContainer

   Parameters :
			Input : 
				userListContainer - user list container

   Description : Delete user list container

*****************************************************************/
PUSER_LIST AuthenticateManager :: DeleteUserListContainer(PUSER_LIST userListContainer)
{
	// Validate user list pointer
	if (userListContainer)
	{
		// Free user list items
		for(int i = 0 ; i < userListContainer -> usersCount; i++)
		{
			if (userListContainer -> users[i])
				free(userListContainer -> users[i]);
		}

		// Free user list
		free(userListContainer);

		userListContainer = NULL;
	}

	return userListContainer;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteUserDescriptor

   Parameters :
			Input : 
				pUser - user descriptor

   Description : Delete user descriptor

*****************************************************************/
PUSER_DESCRIPTOR AuthenticateManager :: DeleteUserDescriptor(PUSER_DESCRIPTOR pUser)
{
	// Validate user 
	if (pUser)
	{
		// Free user 
		free(pUser);
		pUser = NULL;
	}

	return pUser;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DeleteUTF8MatrixList
   
   Parameters:
			Input:
				symbolBoxesList - pointer to symbol matrix list

   Return : pointer to symbol matrix list

   Description : Delete list of symbol boxes

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST AuthenticateManager :: DeleteUTF8MatrixList(PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH)
		WriteToLog("AuthenticateManager : DeleteUTF8MatrixList. Start");
	#endif

	try
	{
		// Remove symbol boxes list
		if (symbolBoxesList)
		{
			for(int k = 0; k < symbolBoxesList -> size; k++)
			{
				for(int i = 0; i < symbolBoxesList -> matrixes[k] -> size; i++)
					for(int j = 0; j < symbolBoxesList -> matrixes[k] -> size; j++)
					{
						for(int q = 0 ; q < symbolBoxesList -> matrixes[k] -> strings[i][j] -> length; q++)
							free(symbolBoxesList -> matrixes[k] -> strings[i][j] -> chars[q]);

						free(symbolBoxesList -> matrixes[k] -> strings[i][j]);
					}

				free(symbolBoxesList -> matrixes[k]);
			}

			free(symbolBoxesList);
			symbolBoxesList = NULL;
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH)
			WriteToLog("AuthenticateManager : DeleteUTF8MatrixList. Can't remove symbol boxes list!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH)
		WriteToLog("AuthenticateManager : DeleteUTF8MatrixList. Done");
	#endif

	return symbolBoxesList;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetPasswortTextFieldIndex

   Return : index of password field

   Description : Get index of password field

*****************************************************************/
int AuthenticateManager :: GetPasswortTextFieldIndex(void)
{
	return -1;
}

/****************************************************************

   Class : AuthenticateManager

   Method :  GetLoginTextFieldIndex

   Return : index of user name field

   Description : Get index of user name field

*****************************************************************/
int AuthenticateManager :: GetLoginTextFieldIndex(void)
{
	return -1;
}

/****************************************************************

   Class : AuthenticateManager

   Method :  GetDomainTextFieldIndex

   Return : index of domain name field

   Description : Get index of domain name field

*****************************************************************/
int AuthenticateManager :: GetDomainTextFieldIndex(void)
{
	return -1;
}


/****************************************************************

   Class : AuthenticateManager

   Method : FirstUserSignInToday

   Parameters :
			Input : 
				userID - user ID
				authSystemID - auth system ID

   Return : TRUE - if it is first time

   Description : Is it first sign in for today for this user?

*****************************************************************/
bool AuthenticateManager :: FirstUserSignInToday(int userID, int authSystemID)
{
	return false;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetUserListContainerPointer

   Return : Pointer to user list container

   Description : Get user list container pointer

*****************************************************************/
PUSER_LIST AuthenticateManager :: GetUserListContainerPointer(void)
{
	return userListContainer;
}


/****************************************************************

   Class : AuthenticateManager

   Method : GetContentPointer

   Return : Pointer to user content container

   Description : Get user content container pointer

*****************************************************************/
PPRESET_CONTAINER AuthenticateManager :: GetContentPointer(void)
{
	return content;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetUserDescriptorPointer

   Return : Pointer to user content container

   Description : Get user descriptor pointer

*****************************************************************/
PUSER_DESCRIPTOR AuthenticateManager :: GetUserDescriptorPointer(void)
{
	return currentUser;
}

/****************************************************************

   Class : AuthenticateManager

   Method : CheckServerAccess

   Return : Success flag

   Description : Check server connection

*****************************************************************/
bool AuthenticateManager :: CheckServerAccess(void)
{
	return false;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetUserContent

   Return : Pointer to user conetnt container

	Description : Get user content container

*****************************************************************/
PPRESET_CONTAINER AuthenticateManager :: GetUserContent(void)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetUserContent

   Parameters :
			Input : 
				compName - computer name
				userID - user ID
				osID - OS ID

   Return : pointer to user content container
	
	Description :  Get user content from database

*****************************************************************/
PPRESET_CONTAINER AuthenticateManager :: GetUserContent(char * compName, int userID, int osID)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : SetUserSignInDate

   Parameters :
			Input : 
				userID - user id

   Return : success flag

   Description : Save date of last sign in 

*****************************************************************/
bool AuthenticateManager :: SetUserSignInDate(int userID, int authSystemID)
{
	return false;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetUserListContainer

   Return : Pointer to list of users

	Description : Get list of users

*****************************************************************/
PUSER_LIST AuthenticateManager :: GetUserListContainer(void)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetUserDescriptor

   Parameters:
			Input:
				userID - user ID
				
   Return : Pointer user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR AuthenticateManager :: GetUserDescriptor(int userID)
{
	return NULL;
}
		
/****************************************************************

   Class : AuthenticateManager

   Method : GetUserDescriptor

   Parameters:
			Input:
				userName - encrypted name of user
				userNameLen - length of encrypted name of user

   Return : Pointer user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR AuthenticateManager :: GetUserDescriptor(unsigned char * userName, int userNameLen)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetUserDescriptor

   Parameters:
			Input:
				userName - encrypted name of user
				userNameLen - length of encrypted name of user
				authSystemID - authentication system type

   Return : Pointer user descriptor

   Description : Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR AuthenticateManager :: GetUserDescriptor(unsigned char * userName, int userNameLen, int authSystemID)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : ValidateParams

   Parameters :
			Input : 
				userID - user id
				compName - computer name
				authContainer - authentication container

   Return : Error code

   Description : Validate user parameters

*****************************************************************/
int AuthenticateManager :: ValidateParams(int userID, char * compName, PAUTH_CONTAINER authContainer)
{
	return RESPONSE_BAD;
}

/****************************************************************

   Class : AuthenticateManager

   Method :  ValidateAnswers

   Parameters :
			Input : 
				userID - user id
				compName - computer name
				eduContainer - education container

   Return : Error code

   Description : Validate user answers

*****************************************************************/
int AuthenticateManager ::  ValidateAnswers(int userID, char * compName, PANSWER_CONTAINER eduContainer)
{
	return RESPONSE_BAD;
}

/****************************************************************

   Class : AuthenticateManager

   Method :  CheckScheduleRecords

   Parameters :
			Input : 
				userID - user id
				compName - computer name
				funcID - function ID

   Return : Action code

   Description : Check schedule records

*****************************************************************/
int AuthenticateManager ::  CheckScheduleRecords(int userID, char * compName, int funcID)
{
	return ALLOW_ACTION;
}

/****************************************************************

   Class : AuthenticateManager

   Method : ValidateUserCustomPassword

   	Parameters :
			Input : 
				userID - pointer to user descriptor
				authSystemID - authentication system ID
				userPassword - encrypted user custom password
				userPasswordLen - encrypted user custom password size
				timeinfo - time info structure
				symbolBoxesList - symbol matrixes list
			
			Output:
				securityData - user security data

   Return : Error code

   Description : Valdate user custom password

*****************************************************************/
int AuthenticateManager :: ValidateUserCustomPassword(int userID, int authSystemID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList, PUSER_SECURITY_DATA securityData)
{
	return RESPONSE_BAD;
}

/****************************************************************

   Class : AuthenticateManager

   Method : ResetUserCustomPassword

   	Parameters :
			Input : 
				userID - user ID

   Return : Error code

   Description : Reset user password

*****************************************************************/
int AuthenticateManager :: ResetUserCustomPassword(int userID)
{
	return RESPONSE_BAD;
}

/****************************************************************

   Class : AuthenticateManager

   Method : ValidateUserAccount

   	Parameters :
			Input : 
				userName - encrypted user name
				userNameLen - length of encrypted user name
				userPassword - encrypted user password
				userPasswordLen - length of encrypted user password
				authSystemID - authentication system ID

   Return : Error code

   Description : Valdate user account

*****************************************************************/
int AuthenticateManager :: ValidateUserAccount(unsigned char * userName, int userNameLen, unsigned char * userPassword, int userPasswordLen, int authSystemID)
{
	return RESPONSE_BAD;
}

/****************************************************************

   Class : AuthenticateManager

   Method : SaveUserNotificationHistory

   	Parameters :
			Input : 
				userID - user ID
				noticeID - notice ID

   Return : Saving result

   Description : Save user notification result

*****************************************************************/
bool AuthenticateManager :: SaveUserNotificationHistory(int userID, int noticeID)
{
	return false;
}


/****************************************************************

   Class : AuthenticateManager

   Method : CheckLicense

   	Parameters :
			Input : 
				pClient - pointer to client description structure
				
   Return : Legal license flag

   Description : Check license info

*****************************************************************/
bool AuthenticateManager :: CheckLicense(PCLIENT_DESCRIPTION pClient)
{
	return true;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetDBAccess

   	Parameters :
			Input : 
				userID - user ID
				userPassword - encrypted user password
				userPasswordLen - user password length
				timeinfo - current time structure
				symbolBoxesList - symbol boxes list
				
   Return : DB access info structure

   Description : Get DB connection

*****************************************************************/
PUSER_DB_ACCESS_INFO AuthenticateManager :: GetDBAccess(int userID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetAuthSystemID

   	Parameters :
			Input : 
				encSystemSettings - encrypted system settings
				encSystemSettingsLen - encrypted system settings length
				authSystemType - system type
				
   Return : auth system ID

   Description : Get auth system ID

*****************************************************************/
int AuthenticateManager :: GetAuthSystemID(unsigned char * encSystemSettings, int encSystemSettingsLen, int authSystemType)
{
	return -1;
}

/****************************************************************

   Class : AuthenticateManager

   Method : LockCtrlAltDelActions

   	Parameters :
			Input : 
				lock - lock/unclok flag
				userName - user name
				
   Return : TRUE - if success

   Description : Lock/Unlock CTRL+ALT+DEL

*****************************************************************/
bool AuthenticateManager :: LockCtrlAltDelActions(bool lock, char * userName)
{
	return false;
}

/****************************************************************

   Class : AuthenticateManager

   Method : GetFileList

   	Parameters :
			Input : 
				dirPath - path to the folder
				maxFileCount - maximum count of files in list

   Return : pointer to structure with folder description

   Description : Get list of files in some remote directory

*****************************************************************/
PFOLDER_INFO_CONTAINER AuthenticateManager :: GetFileList(char * dirPath, int maxFileCount)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DownloadFile

   	Parameters :
			Input : 
				filePath - path to the file
				
   Return : size of file

   Description : Download file

*****************************************************************/
long long AuthenticateManager :: DownloadFile(char * filePath)
{
	return 0;
}

/****************************************************************

   Class : AuthenticateManager

   Method : UploadFile

   	Parameters :
			Input : 
				filePath - path to the file
				fileSize - size of file

   Return : path to the file

   Description : Upload file

*****************************************************************/
bool AuthenticateManager :: UploadFile(char * filePath, long long fileSize)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : DownloadBlockFile

   	Parameters :
			Input : 
				filePath - path to the file
				blockNUmber - number of block
				blockSize - size of block
				
   Return : block data

   Description : Download block of file

*****************************************************************/
char * AuthenticateManager :: DownloadBlockFile(char * filePath, int blockNUmber, int * blockSize)
{
	return NULL;
}

/****************************************************************

   Class : AuthenticateManager

   Method : UploadBlockFile

   	Parameters :
			Input : 
				filePath - path to the file
				blockNUmber - number of block
				blockSize - size of block
				blockData - block data

   Return : path to the file

   Description : Upload block of file

*****************************************************************/
bool AuthenticateManager :: UploadBlockFile(char * filePath, int blockNUmber, int blockSize, char * blockData)
{
	return NULL;
}


/****************************************************************

   Class : AuthenticateManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  AuthenticateManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}
