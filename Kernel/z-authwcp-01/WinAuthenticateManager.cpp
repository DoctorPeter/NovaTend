/****************************************************************

   Solution : NovaTend

   Project : z-authwcp-01.dll

   Module : WinAuthenticateManager.cpp

   Description : this module implements methods of
				  class WinAuthenticateManager

*****************************************************************/

#include "stdafx.h"

#include <SerializationManager.h>
#include <SettingsManager.h>
#include <PasswordConstructor.h>
#include <SchedulerDef.h>

#include "WinAuthenticateManager.h"

#include <stdio.h>

// z-authwcp-01.dll definition structure
extern DLL_COMMON_DEFINITION zAuthWCPDllDefinition;

/****************************************************************

   Class : WinAuthenticateManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - log writer instance
				commandManager - command manager instance

*****************************************************************/
WinAuthenticateManager :: WinAuthenticateManager(unsigned long dllUserID, 
	                                             LogWriter * logWriter,
												 CommandManager * commandManager) : ClientAuthManager(dllUserID, logWriter, commandManager)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : constructor");
	#endif

	postLogin = false;
	userScreenContainer = NULL;
	symbolMatrixesList = NULL;
	screenBuilder = new WinCPScreenBuilder(zAuthWCPDllDefinition.dllID, logWriter);
	encryptor = new Encryptor(zAuthWCPDllDefinition.dllID);
	encryptor -> Init();
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : Copy constructor

   Parameters :
			Input : 
				src - soucre instance

*****************************************************************/		
WinAuthenticateManager :: WinAuthenticateManager(const WinAuthenticateManager & src)  : ClientAuthManager(src.dllUserID, src.logWriter, src.commandManager)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : copy constructor");
	#endif

	postLogin = false;
	userScreenContainer = NULL;
	symbolMatrixesList = NULL;
	screenBuilder = new WinCPScreenBuilder(zAuthWCPDllDefinition.dllID, logWriter);
	encryptor = new Encryptor(zAuthWCPDllDefinition.dllID);
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : Destructor

*****************************************************************/
WinAuthenticateManager :: ~WinAuthenticateManager(void)
{
	userScreenContainer = screenBuilder -> ClearScreenContainer(userScreenContainer);
	symbolMatrixesList = screenBuilder -> RemoveSymbolBoxes(symbolMatrixesList);
	delete screenBuilder;
	
	encryptor -> Cleanup();
	delete encryptor;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : Destructor");
	#endif
}


/****************************************************************

   Class : WinAuthenticateManager

   Method : Clone

   Return : Pointer to authenticate mananger clone object

   Description : Clone authenticate manager

*****************************************************************/
AuthenticateManager * WinAuthenticateManager :: Clone(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : Clone");
	#endif

	return new WinAuthenticateManager(*this);
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : EncryptAuthElement

   Parameters:
			Input:
				objectName - object name
				objectValue - object value
			Output:
				pAuthElem - authenticate element

   Return : Error code

   Description : Encrypt authenticate element

*****************************************************************/
bool WinAuthenticateManager :: EncryptAuthElement(WCHAR * objectName, WCHAR * objectValue, PAUTH_ELEMENT pAuthElem)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : EncryptAuthElement. Start");
	#endif
	
	char objName[NAME_LEN];
	char objValue[STR_VALUE_LEN];
	wcstombs(objName, objectName, NAME_LEN); 
	wcstombs(objValue, objectValue, STR_VALUE_LEN); 
	
	int objNameLen = strlen(objName);
	int objValueLen = strlen(objValue);

	unsigned char packedData[ENCRYPTED_DATA_SIZE];
	int packedDataLen;

	if (encryptor -> EncryptAndPackSecurityData((unsigned char *)objName, objNameLen, packedData, ENCRYPTED_DATA_SIZE, &packedDataLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : EncryptAuthElement. Can't encrypt object name!");
			WriteToLog("WinAuthenticateManager : EncryptAuthElement. Done");
		#endif

		return false;
	}
	else
	{
		memcpy(pAuthElem -> objectName, packedData, packedDataLen);
		pAuthElem -> objectNameLen = packedDataLen;
	}

	if (encryptor -> EncryptAndPackSecurityData((unsigned char *)objValue, objValueLen, packedData, ENCRYPTED_DATA_SIZE, &packedDataLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : EncryptAuthElement. Can't encrypt object value!");
			WriteToLog("WinAuthenticateManager : EncryptAuthElement. Done");
		#endif

		return false;
	}
	else
	{
		memcpy(pAuthElem -> objectValue, packedData, packedDataLen);
		pAuthElem -> objectValueLen = packedDataLen;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : EncryptAuthElement. All encrypted!");
		WriteToLog("WinAuthenticateManager : EncryptAuthElement. Done");
	#endif

	return true;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : DecryptUserList

   Return : Error code

   Description : Decrypt user list

*****************************************************************/
bool WinAuthenticateManager :: DecryptUserList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : DecryptUserList. Start");
	#endif

	if (userListContainer)
	{
		for (int i = 0; i < userListContainer -> usersCount; i++)
		{
			unsigned char decryptedData[STR_VALUE_LEN];
			int decryptedDataLen;

			if (encryptor -> UnPackAndDecryptSecurityData(userListContainer -> users[i] -> encUserName, userListContainer -> users[i] -> encUserNameLen, decryptedData, STR_VALUE_LEN, &decryptedDataLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
					WriteToLog("WinAuthenticateManager : DecryptUserList. Can't decrypt user name!");
					WriteToLog("WinAuthenticateManager : DecryptUserList. Done");
				#endif

				return false;
			}
			else
			{
				decryptedData[decryptedDataLen] = 0;
				strcpy((char *)userListContainer -> users[i] -> encUserName, (char *)decryptedData);
				userListContainer -> users[i] -> encUserNameLen = strlen((char *)userListContainer -> users[i] -> encUserName);
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : DecryptUserList. Done");
	#endif

	return true;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : CreateAuthContainer

   Return : Error code

   Description : Create authenticate container

*****************************************************************/
PAUTH_CONTAINER WinAuthenticateManager :: CreateAuthContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : CreateAuthContainer. Start");
	#endif
	
	// Validate user screen container
	if (userScreenContainer == NULL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CreateAuthContainer. UserScreenContainer not found");
			WriteToLog("WinAuthenticateManager : CreateAuthContainer. Done");
		#endif

		return NULL;
	}
	
	// Delete authentication container
	DeleteAuthContainer();
	
	// Allocate memory for authentication container
	authContainer = (PAUTH_CONTAINER)malloc(sizeof(AUTH_CONTAINER));
	
	// Validate allocation result
	if (authContainer == NULL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CreateAuthContainer. Can't allocate authenticate container");
			WriteToLog("WinAuthenticateManager : CreateAuthContainer. Done");
		#endif

		return NULL;
	}

	// Fill authentication container
	authContainer -> authElementCount = 0;

	for(int i = 0; i < userScreenContainer -> screenObjectsCount; i++)
	{
		// Valiadte field type
		if ((userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_COMBOBOX) ||
			(userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_TEXT_BOX) ||
			(userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_USER_NAME_BOX) ||
			(userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_DOMAIN_NAME_BOX) ||
			(userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_PASSWORD_BOX))
		{
			// Allocate memory for authenticate container element
			authContainer -> authElements[authContainer -> authElementCount] = (PAUTH_ELEMENT)malloc(sizeof(AUTH_ELEMENT));

			// Validate allocation result
			if (authContainer -> authElements[authContainer -> authElementCount] == NULL)
			{
				free(authContainer);
				authContainer = NULL;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
					WriteToLog("WinAuthenticateManager : CreateAuthContainer. Can't allocate authenticate container element");
					WriteToLog("WinAuthenticateManager : CreateAuthContainer. Done");
				#endif

				return NULL;
			}
			
			// Copy values
			authContainer -> authElements[authContainer -> authElementCount] -> objectID = userScreenContainer -> screenObjects[i] -> objectID;
			authContainer -> authElements[authContainer -> authElementCount] -> objectTypeID = userScreenContainer -> screenObjects[i] -> objectTypeID;
			if (EncryptAuthElement(userScreenContainer -> screenObjects[i] -> objectName, userScreenContainer -> screenObjects[i] -> strValue, authContainer -> authElements[authContainer -> authElementCount]))
			{
				char objName[NAME_LEN];
				char objValue[STR_VALUE_LEN];
				wcstombs(objName, userScreenContainer -> screenObjects[i] -> objectName, NAME_LEN); 
				wcstombs(objValue, userScreenContainer -> screenObjects[i] -> strValue, STR_VALUE_LEN); 

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
					char msg[256];
					sprintf(msg, "WinAuthenticateManager : CreateAuthContainer. Add parameter %s - %s to AuthContainer", objName, objValue);
					WriteToLog(msg);
				#endif

			}
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			else
				WriteToLog("WinAuthenticateManager : CreateAuthContainer. Encryption failed!");
			#endif

			authContainer -> authElementCount++;
		}
	}
   
	// Check DLL legal user
	authContainer -> authElementCount -= dllUserCheckResult;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : CreateAuthContainer. Done");
	#endif

	return authContainer;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : CreateEducationContainer

   Return : Error code

   Description : Create answer container

*****************************************************************/
PANSWER_CONTAINER WinAuthenticateManager :: CreateEducationContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : CreateEducationContainer. Start");
	#endif
	
	// Validate user screen container
	if (userScreenContainer == NULL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CreateEducationContainer. UserScreenContainer not found");
			WriteToLog("WinAuthenticateManager : CreateEducationContainer. Done");
		#endif

		return NULL;
	}
	
	// Delete answer container
	DeleteEducationContainer();
	
	// Allocate memory for answer container
	eduContainer = (PANSWER_CONTAINER)malloc(sizeof(ANSWER_CONTAINER));
	
	// Validate allocation result
	if (eduContainer == NULL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CreateEducationContainer. Can't allocate answer container");
			WriteToLog("WinAuthenticateManager : CreateEducationContainer. Done");
		#endif

		return NULL;
	}

	// Fill answer container
	eduContainer -> answersCount = 0;

	for(int i = 0; i < userScreenContainer -> screenObjectsCount; i++)
	{
		if(userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_EDU_ANSWER_BOX)
		{
			// Allocate memory for answer container element
			eduContainer -> answers[eduContainer -> answersCount] = (PANSWER_DESCRIPTOR)malloc(sizeof(ANSWER_DESCRIPTOR));

			// Validate allocation result
			if (eduContainer -> answers[eduContainer -> answersCount] == NULL)
			{
				free(eduContainer);
				authContainer = NULL;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
					WriteToLog("WinAuthenticateManager : CreateEducationContainer. Can't allocate answer container element");
					WriteToLog("WinAuthenticateManager : CreateEducationContainer. Done");
				#endif

				return ANS_CNT_CREATION_BAD;
			}

			// Copy values
			eduContainer -> answers[eduContainer -> answersCount] -> questionID = userScreenContainer -> screenObjects[i] -> questionID;
			eduContainer -> answers[eduContainer -> answersCount] -> rightAnswerID = userScreenContainer -> screenObjects[i] -> rightAnswerID;
			wcstombs(eduContainer -> answers[eduContainer -> answersCount] -> answerValue, userScreenContainer -> screenObjects[i] -> strValue, STR_VALUE_LEN);
			eduContainer -> answersCount++;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : CreateEducationContainer. Done");
	#endif

	return eduContainer;
}

/****************************************************************

   Class : WinCredentialManager

   Method : GetPasswortTextFieldIndex

   Return : index of password field

   Description : Get index of password field

*****************************************************************/
int WinAuthenticateManager :: GetPasswortTextFieldIndex(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: GetPasswortTextFieldIndex");
	#endif

	if (userScreenContainer == NULL) 
		return -1;

	for(int i = 0; i < userScreenContainer -> screenObjectsCount; i++)
		if (userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_PASSWORD_BOX)
			return i;

	return -1;
}

/****************************************************************

   Class : WinCredentialManager

   Method :  GetLoginTextFieldIndex

   Return : index of user name field

   Description : Get index of user name field

*****************************************************************/
int WinAuthenticateManager :: GetLoginTextFieldIndex(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: GetLoginTextFieldIndex");
	#endif

	if (userScreenContainer == NULL) 
		return -1;

	for(int i = 0; i < userScreenContainer -> screenObjectsCount; i++)
		if (userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_USER_NAME_BOX)
			return i;

	return -1;
}

/****************************************************************

   Class : WinCredentialManager

   Method :  GetDomainTextFieldIndex

   Return : index of domain name field

   Description : Get index of domain name field

*****************************************************************/
int WinAuthenticateManager :: GetDomainTextFieldIndex(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: GetDomainTextFieldIndex");
	#endif

	if (userScreenContainer == NULL) 
		return -1;

	for(int i = 0; i < userScreenContainer -> screenObjectsCount; i++)
		if (userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_DOMAIN_NAME_BOX)
			return i;

	return -1;
}

/****************************************************************

   Class : WinCredentialManager

   Method :  GetSymbolBoxPasswordWindowIndex

   Return : index of password window

   Description : Get index of password window (symbol boxes)

*****************************************************************/
int WinAuthenticateManager :: GetSymbolBoxPasswordWindowIndex(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: GetSymbolBoxPasswordWindowIndex");
	#endif

	if (userScreenContainer == NULL)
		return -1;

	for(int i = 0; i < userScreenContainer -> subWindowCount; i++)
		if (userScreenContainer -> subWindows[i] -> windowTypeId == SOT_SYMBOL_BOXES_PWD_SCREEN)
			return i;

	return -1;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : GetUserListContainer

   Return : Pointer to list of users

	Description : Get list of users

*****************************************************************/
PUSER_LIST WinAuthenticateManager :: GetUserListContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: GetUserListContainer. Start");
	#endif
	
	userListContainer = ClientAuthManager :: GetUserListContainer();

	DecryptUserList();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: GetUserListContainer. Done");
	#endif

	return userListContainer;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : EnumDomainNames
	
   Description : Enumerates all domains names and local computer name
				 
*****************************************************************/
void WinAuthenticateManager :: EnumDomainNames(WCHAR * lookedDomainName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : EnumDomainNames. Start");
	#endif

	// Validate user screen container
	if (!userScreenContainer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : EnumDomainNames. User screen container is empty!");
			WriteToLog("WinAuthenticateManager : EnumDomainNames. Done");
		#endif

		return;
	}

	// Get domain box index
	int dmnInd = GetDomainTextFieldIndex();

	// Validate domain box index
	if (dmnInd == -1) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : EnumDomainNames. Can't find domain name box!");
			WriteToLog("WinAuthenticateManager : EnumDomainNames. Done");
		#endif

		return;
	}
   
   // Get domain box descriptor
   PMAIN_SCREEN_OBJECT_DESCRIPTOR pDmnFldDsc = userScreenContainer -> screenObjects[dmnInd];

   // Prepare network data structures
   LPSERVER_INFO_100 pBuf = NULL;
   LPSERVER_INFO_100 pTmpBuf;
   DWORD dwEntriesRead = 0;
   DWORD dwTotalEntries = 0;
   DWORD dwTotalCount = pDmnFldDsc -> comboBoxValuesCount;
   DWORD dwResumeHandle = 0;
   DWORD lookedIndex = -1;

   // Enumerate domains
   NET_API_STATUS nStatus = NetServerEnum(NULL, 100, (LPBYTE *) &pBuf, MAX_PREFERRED_LENGTH, &dwEntriesRead, &dwTotalEntries, SV_TYPE_DOMAIN_ENUM, NULL, &dwResumeHandle);

   // Validate enumeration result
   if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
   {
	   #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : EnumDomainNames. Successful domain enumeration!");
		#endif

	   // Save domain names
	   if ((pTmpBuf = pBuf) != NULL)
	   {
		     for (DWORD i = 0; i < dwEntriesRead; i++)
			 {
				 if (pTmpBuf == NULL) break;
				 wcscpy_s(pDmnFldDsc -> comboBoxValues[dwTotalCount], pTmpBuf -> sv100_name);
				 
				 if ((lookedDomainName != NULL) && (wcscmp(pDmnFldDsc -> comboBoxValues[dwTotalCount], lookedDomainName) == 0))
					 lookedIndex = dwTotalCount;

				 pTmpBuf++;
				 dwTotalCount++;
			 }
	   }
   }
   #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
   else
	   WriteToLog("WinAuthenticateManager : EnumDomainNames. Domain enumeration failed!");
	#endif

   // Get size of comobox values array
   DWORD cmpNmLn = ARRAYSIZE(pDmnFldDsc -> comboBoxValues[dwTotalCount]);

   // Get computer name
    if (GetComputerNameW(pDmnFldDsc -> comboBoxValues[dwTotalCount], &cmpNmLn))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : EnumDomainNames. Computer name retrieving. Success!");
		#endif

		dwTotalCount++;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
	else
		 WriteToLog("WinAuthenticateManager : EnumDomainNames. Computer name retrieving. Fail!");
	#endif

   pDmnFldDsc -> comboBoxValuesCount = dwTotalCount;

   // Save computer name
   if (dwTotalCount > 0)
   {
	   if (lookedIndex == -1)
	   {
			wcscpy_s(pDmnFldDsc -> strValue, pDmnFldDsc -> comboBoxValues[0]);
			pDmnFldDsc -> comboBoxIndex = 0;
	   }
	   else
	   {
		   wcscpy_s(pDmnFldDsc -> strValue, pDmnFldDsc -> comboBoxValues[lookedIndex]);
		   pDmnFldDsc -> comboBoxIndex = lookedIndex;
	   }

   }

   #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : EnumDomainNames. Done");
   #endif
}
		
/****************************************************************

   Class : WinCredentialManager

   Method : SetUserNameFieldValue

   Parameters :
			Input : 
				userName - name of user

   Return : Error code

   Description : Set name to user name box

*****************************************************************/
void WinAuthenticateManager :: SetUserNameFieldValue(PWSTR userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: SetUserNameFieldValue. Start");
	#endif
	
	// validate user screen container
	if (!userScreenContainer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SetUserNameFieldValue. User screen container is empty!");
			WriteToLog("WinAuthenticateManager : SetUserNameFieldValue. Done");
		#endif

		return;
	}

	// Get user name edit box index
	int usrNameInd = GetLoginTextFieldIndex();
	
	// Validate user name edit box index
	if (usrNameInd != -1)
		wcscpy_s(userScreenContainer -> screenObjects[usrNameInd] -> strValue, userName);
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		else
			WriteToLog("WinAuthenticateManager: SetUserNameFieldValue. Can't find user name box!");

		WriteToLog("WinAuthenticateManager: SetUserNameFieldValue. Done");
	#endif
}


/****************************************************************

   Class : WinAuthenticateManager

   Method : GetUserLocalScreenContainer

   Return : Pointer to user screen container

  Description : Get user local screen container

*****************************************************************/
PUSER_SCREEN_CONTAINER WinAuthenticateManager :: GetUserLocalScreenContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetUserLocalScreenContainer. Start");
	#endif

	if (screenBuilder)
	{
		// Delete previous container
		userScreenContainer = screenBuilder -> ClearScreenContainer(userScreenContainer);

		// Create new container
		userScreenContainer = screenBuilder -> CreateLocalScreenContainer();

		// Check user password type
		if ((currentUser) && ((currentUser -> pwdType == ONE_SYMBOL_BOX_PWD) || (currentUser -> pwdType == TWO_SYMBOL_BOX_PWD)))
		{
			// Remove previous symbol boxes list
			symbolMatrixesList = screenBuilder -> RemoveSymbolBoxes(symbolMatrixesList);

			// Generate new symbol boxes list
			symbolMatrixesList = screenBuilder -> GenerateSymbolBoxes(currentUser -> pwdType);
			
			// Add symbol boxes password window
			screenBuilder -> AddSymbolBoxesPasswordWindow(symbolMatrixesList, currentUser -> pwdType, userScreenContainer);
		}
		else
		{
			// Remove previous symbol boxes list
			symbolMatrixesList = screenBuilder -> RemoveSymbolBoxes(symbolMatrixesList);
		}
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		else
			WriteToLog("WinAuthenticateManager : GetUserLocalScreenContainer. No ScreenBuilder instance!");

		WriteToLog("WinAuthenticateManager : GetUserLocalScreenContainer. Done");
	#endif

	return userScreenContainer;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : GetLocalUserList

   Return : Pointer to user list container

  Description : Get user local list container

*****************************************************************/
PUSER_LIST WinAuthenticateManager :: GetLocalUserList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetLocalUserList. Start");
	#endif

	DeleteUserListContainer();

	SettingsManager * settingsManager = new SettingsManager(zAuthWCPDllDefinition.dllID);

	userListContainer = settingsManager -> GetLocalUsersList();
	DecryptUserList();

	delete settingsManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetLocalUserList. Done");
	#endif

	return userListContainer;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : GetLocalUserDescriptor

   Parameters:
			Input:
				userID - user ID

   Return : Pointer to user descriptor

  Description : Get local user descriptor

*****************************************************************/
PUSER_DESCRIPTOR WinAuthenticateManager :: GetLocalUserDescriptor(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetLocalUserDescriptor. Start");
	#endif

	DeleteUserDescriptor();

	SettingsManager * settingsManager = new SettingsManager(zAuthWCPDllDefinition.dllID);

	currentUser = settingsManager -> GetLocalUser(userID);

	delete settingsManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetLocalUserDescriptor. Done");
	#endif

	return currentUser;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : GetLocalUserDescriptor

   Parameters:
			Input:
				sysUserName - system user name

   Return : Pointer to user descriptor

  Description : Get local user descriptor

*****************************************************************/
PUSER_DESCRIPTOR WinAuthenticateManager :: GetLocalUserDescriptor(WCHAR * sysUserName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetLocalUserDescriptor. Start");
	#endif

	DeleteUserDescriptor();

	SettingsManager * settingsManager = new SettingsManager(zAuthWCPDllDefinition.dllID);

	currentUser = settingsManager -> GetLocalUser(sysUserName);

	delete settingsManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetLocalUserDescriptor. Done");
	#endif

	return currentUser;
}

/****************************************************************

	Class : WinAuthenticateManager

	Method :  ValidateLocalMainPassword
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor
				pSecurityData - pointer to security data structure
				userPassword - user custom password
				timeinfo - time info structure

	Return:  Error code

	Description :  Validate local main custom password

*****************************************************************/
int WinAuthenticateManager :: ValidateLocalMainPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, char * userPassword, tm * timeinfo)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : ValidateLocalMainPassword. Start");
	#endif

	// Check user instance
	if ((!pUser) || (!pSecurityData) || (pUser -> userID != pSecurityData -> userID))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : ValidateLocalMainPassword. Wrong input data!");
			WriteToLog("WinAuthenticateManager : ValidateLocalMainPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	// Check rules
	char genPassword[STR_VALUE_LEN] = "";
	if ((pSecurityData -> pwdConstRulesCount > 0) && (pSecurityData -> passThru == false))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : ValidateLocalMainPassword. Password generates by rules!");
		#endif

		// Construct password
		PasswordConstructor * passwordConstructor = new PasswordConstructor(pUser, pSecurityData, timeinfo, symbolMatrixesList, encryptor);
		passwordConstructor -> CreateMainPassword();
		passwordConstructor -> GetPassword(genPassword);
		delete passwordConstructor;
	}
	else
	{
		unsigned char decryptedPassword[STR_VALUE_LEN];
		int decryptedPasswordLen;

		if (encryptor -> UnPackAndDecryptSecurityData(pSecurityData -> encSystemPassword, pSecurityData -> encSystemPasswordLen, decryptedPassword, STR_VALUE_LEN, &decryptedPasswordLen))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : ValidateLocalMainPassword. Can't decrypt password!");
				WriteToLog("WinAuthenticateManager : ValidateLocalMainPassword. Done");
			#endif

			return RESPONSE_BAD;
		}
		else
		{
			decryptedPassword[decryptedPasswordLen] = 0;
		}

		strcpy(genPassword, (char *)decryptedPassword);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		char msg[STR_VALUE_LEN];
		sprintf(msg, "WinAuthenticateManager : ValidateLocalMainPassword. User constructed password: '%s'. System constructed password: '%s'", userPassword, genPassword);
		WriteToLog(msg);
	#endif

	int validationResult = RESPONSE_OK;

	if (pUser -> pwdType == CASCADE_STRING_PWD)
	{
		for(size_t i = 0; (i < strlen(userPassword)) && (i < strlen(genPassword)); i++)
		  if (userPassword[i] != genPassword[i])
		  {
			validationResult = RESPONSE_BAD;
			break;
		  }
	}
	else
		if ((pUser -> pwdType == ONE_SYMBOL_BOX_PWD) || (pUser -> pwdType == TWO_SYMBOL_BOX_PWD))
		{
			if(strstr(userPassword, genPassword) == NULL)
				validationResult = RESPONSE_BAD;
		}
		else
			validationResult = RESPONSE_BAD;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : ValidateLocalMainPassword. Done");
	#endif
	
	return validationResult;
}

/****************************************************************

	Class : WinAuthenticateManager

	Method :  ValidateLocalTempPassword
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor
				pSecurityData - pointer to security data structure
				userPassword - user custom password
				timeinfo - time info structure

	Return:  Error code

	Description :  Validate local temporary pasword

*****************************************************************/
int WinAuthenticateManager :: ValidateLocalTempPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, char * userPassword, tm * timeinfo)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : ValidateLocalTempPassword. Start");
	#endif

	// Check user instance
	if ((!pUser) || (!pSecurityData) || (pUser -> userID != pSecurityData -> userID))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : ValidateLocalTempPassword.  Wrong input data!");
			WriteToLog("WinAuthenticateManager : ValidateLocalTempPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	// Check temp password
	if ((pUser -> pwdReseted) && (pSecurityData -> tmpPwdConstRulesCount > 0))
	{
		// Check password period
		if (CheckTimePeriod(pUser -> pwdResetPeriod, pUser -> pwdResetDate))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : ValidateLocalTempPassword. Temporary password expired!");
				WriteToLog("WinAuthenticateManager : ValidateLocalTempPassword. Done");
			#endif

			return RESPONSE_PWD_EXPIRED;
		}

		char genPassword[STR_VALUE_LEN] = "";
		
		// Construct password
		PasswordConstructor * passwordConstructor = new PasswordConstructor(pUser, pSecurityData, timeinfo, symbolMatrixesList, encryptor);
		passwordConstructor -> CreateTempPassword();
		passwordConstructor -> GetPassword(genPassword);
		delete passwordConstructor;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			char msg[STR_VALUE_LEN];
			sprintf(msg, "WinAuthenticateManager : ValidateLocalTempPassword. User constructed password: '%s'. System constructed password: '%s'", userPassword, genPassword);
			WriteToLog(msg);
		#endif

		int validationResult = RESPONSE_OK;

		if (pUser -> pwdType == CASCADE_STRING_PWD)
		{
			for(size_t i = 0; (i < strlen(userPassword)) && (i < strlen(genPassword)); i++)
				if (userPassword[i] != genPassword[i])
				{
					validationResult = RESPONSE_BAD;
					break;
				}
		}
		else
			if ((pUser -> pwdType == ONE_SYMBOL_BOX_PWD) || (pUser -> pwdType == TWO_SYMBOL_BOX_PWD))
			{
				if(strstr(userPassword, genPassword) == NULL)
					validationResult = RESPONSE_BAD;
			}
			else
				validationResult = RESPONSE_BAD;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : ValidateLocalTempPassword. Done");
		#endif
	
		return validationResult;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : ValidateLocalTempPassword. No temporary password!");
			WriteToLog("WinAuthenticateManager : ValidateLocalTempPassword. Done");
		#endif

		return RESPONSE_BAD;
	}
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : CheckTimePeriod

   Parameters :
			Input : 
				period - period code
				data - data string

   Returns : TRUE - if period expired

   Description : Check time period

*****************************************************************/
bool WinAuthenticateManager :: CheckTimePeriod(int period, char * data)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : CheckTimePeriod. Start");
	#endif

	try
	{
		int day, mon, year, hour, min, sec;

		// Retrieve date values
		sscanf_s(data, "%d-%d-%d %d:%d:%d", &year, &mon, &day, &hour, &min, &sec);
	
		time_t nowSeconds;
		struct tm inpTime;

		// Get current time
		time (&nowSeconds);
		inpTime = * localtime(&nowSeconds);

		// Set new values
		inpTime.tm_year = year - 1900;
		inpTime.tm_mon = mon - 1;
		inpTime.tm_mday = day;
		inpTime.tm_hour = hour;
		inpTime.tm_min = min;
		inpTime.tm_sec = sec;
		inpTime.tm_isdst = -1;
	    
		// Subtract dates
		double resSeconds = difftime(nowSeconds, mktime(&inpTime));

		// Count period
		double hours = resSeconds / 3600;
		
		if(hours > period)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : CheckTimePeriod. Time period expired");
				WriteToLog("WinAuthenticateManager : CheckTimePeriod. Done");
			#endif
	
			return true;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : CheckTimePeriod. Time period not expired");
				WriteToLog("WinAuthenticateManager : CheckTimePeriod. Done");
			#endif
	
			return false;
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CheckTimePeriod. Can't check period!");
			WriteToLog("WinAuthenticateManager : CheckTimePeriod. Done");
		#endif

		return true;
	}
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : CheckPostLogin

   Parameters :
			Input : 
				content - user content

   Returns : TRUE - if post login screen needed

   Description : Check post login flag

*****************************************************************/
bool WinAuthenticateManager :: CheckPostLogin(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : CheckPostLogin. Start");
	#endif

	postLogin = false;

	// Check license
	if (commandManager)
	{
		char funcName[STR_VALUE_LEN] = "POST_LOGIN";
		postLogin = commandManager -> CheckLicense("CLIENTFUNC", funcName);
	
		if (!postLogin)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : CheckPostLogin. Post login process license failed!");
				WriteToLog("WinAuthenticateManager : CheckPostLogin. Done");
			#endif

			return postLogin;
		}
	}

	if (currentUser)
	{
		// Get computer name
		char compName[NAME_LEN] = "";
		unsigned long compNameLen = NAME_LEN;
		GetComputerNameA(compName, &compNameLen);

		// Get action code
		int actionCode = CheckScheduleRecords(currentUser -> userID, compName, POST_LOG_IN_FUNCTION);

		// Verify schedule records
		if (((actionCode & DENY_ACTION) == DENY_ACTION) || ((actionCode & IGNORE_ACTION) == IGNORE_ACTION))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("ResponseValidator : CheckPostLogin. Post Login Process banned or skipped in schedule!");
				WriteToLog("ResponseValidator : CheckPostLogin. Done");
			#endif
						
			return postLogin;
		}
	}

	if (content)
	{
		for(int i = 0; i < content -> userScreensCount; i++)
		{
			if ((content -> userScreens[i] -> screenScope == SO_SCOPE_POST_LOGIN_SCREEN) ||
				(content -> userScreens[i] -> screenScope == SO_SCOPE_BOTH))
			{
				postLogin = true;
				break;
			}
		}
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		else
			WriteToLog("WinAuthenticateManager : CheckPostLogin. Bad user content!");
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
	    if (postLogin)
			WriteToLog("WinAuthenticateManager : CheckPostLogin. User content setting has post login screens");
		else
			WriteToLog("WinAuthenticateManager : CheckPostLogin. User content setting dont have post login screens");

		WriteToLog("WinAuthenticateManager : CheckPostLogin. Done");
	#endif

	return postLogin;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : ValidateLocalUserCustomPassword

   Parameters :
			Input : 
				pUser - pointer to user descriptor
				pSecurityData - pointer to security data structure
				userPassword - user custom password
				timeinfo - time info structure
			Output:
				securityData - security data

   Return : Error code

  Description : Validate constructed password for local user

*****************************************************************/
int WinAuthenticateManager :: ValidateLocalUserCustomPassword(PUSER_DESCRIPTOR pUser, char * userPassword, tm * timeinfo, PUSER_SECURITY_DATA securityData)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : ValidateLocalUserCustomPassword. Start");
	#endif

	if ((!pUser) || (!securityData))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : ValidateLocalUserCustomPassword. Wrong input data!");
			WriteToLog("WinAuthenticateManager : ValidateLocalUserCustomPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	SettingsManager * settingsManager = new SettingsManager(zAuthWCPDllDefinition.dllID);
	
	PUSER_SECURITY_DATA pSecurityData = settingsManager -> GetUserSecurityData(pUser -> userID);

		// Validate main password
	int validationResult = ValidateLocalMainPassword(pUser, pSecurityData, userPassword, timeinfo);

	if (validationResult == RESPONSE_OK)
	{
		pSecurityData -> tmpPwdConstRulesCount = 0;
		pUser -> pwdReseted = false;
	}
	else
	{
		// Validate temp password
		validationResult = ValidateLocalTempPassword(pUser, pSecurityData, userPassword, timeinfo);

		if (validationResult == RESPONSE_PWD_EXPIRED)
		{
			pSecurityData -> tmpPwdConstRulesCount = 0;
			pUser -> pwdReseted = false;
		}
	}

	
	if (pSecurityData)
	{
		memcpy(securityData, pSecurityData, sizeof(USER_SECURITY_DATA));
		free(pSecurityData);
		
	}

	if (validationResult == RESPONSE_OK) 
	{
		pUser -> pwdAttemptsCount = 0;
	}
	else
	{
		pUser -> pwdAttemptsCount++;
	}
	
	if (settingsManager -> SetLocalUser(pUser) != ERROR_SUCCESS)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : ValidateLocalUserCustomPassword. Can't save user!");
		#endif
	}

	if (settingsManager -> SetUserSecurityData(securityData) != ERROR_SUCCESS)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : ValidateLocalUserCustomPassword. Can't save user security data!");
		#endif
	}

	delete settingsManager;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : ValidateLocalUserCustomPassword. Done");
	#endif

	return validationResult;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : SaveLocalUser

   Parameters :
			Input : 
				pUser - pointer to user descriptor

   Return : Error code

  Description : Save local user account

*****************************************************************/
bool WinAuthenticateManager :: SaveLocalUser(PUSER_DESCRIPTOR pUser, bool createAccount)
{	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : SaveLocalUser. Start");
	#endif

	if (!pUser)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Bad user container");
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Done");
		#endif

		return false;
	}

	SettingsManager * settingsManager = new SettingsManager(zAuthWCPDllDefinition.dllID);
	
	if (settingsManager -> SetLocalUser(pUser) != ERROR_SUCCESS)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Can't save user to registry!");
		#endif
	}

	PUSER_SECURITY_DATA securityData = settingsManager -> GetUserSecurityData(pUser -> userID);

	delete settingsManager;

	if (!securityData)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Can't get user security data!");
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Done");
		#endif

		return false;
	}

	if (!createAccount)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Windows account was not created!");
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Done");
		#endif

		return true;
	}
			
	if ((securityData -> encSystemUserNameLen <= 0) || (securityData -> encSystemPasswordLen <= 0))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Bad system user name or  password!");
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Done");
		#endif

		return false;
	}

	WCHAR userName[STR_VALUE_LEN];
	WCHAR userPassword[STR_VALUE_LEN];
	
	if (!DecryptWCHARString(userName, securityData -> encSystemUserName, securityData -> encSystemUserNameLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Can't decrypt user name!");
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Done");
		#endif

		return false;
	}

	if(!DecryptWCHARString(userPassword, securityData -> encSystemPassword, securityData -> encSystemPasswordLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Can't decrypt user password!");
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Done");
		#endif

		return false;
	}

	NET_API_STATUS addResult = CreateWinLocalUser(userName, userPassword);

	if (addResult != NERR_Success)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Error of windows account creation!");
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Done");
		#endif

		return false;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Windows account created successfully!");
			WriteToLog("WinAuthenticateManager : SaveLocalUser. Done");
		#endif

		return true;
	}
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : SaveLocalUserSecurityData

   Parameters :
			Input : 
				pSecurityData - pointer to user security data

   Return : Error code

  Description : Save local user security data

*****************************************************************/
bool WinAuthenticateManager :: SaveLocalUserSecurityData(PUSER_SECURITY_DATA pSecurityData)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : SaveLocalUserSecurityData. Start");
	#endif

	if (!pSecurityData)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUserSecurityData. Bad user security data container");
			WriteToLog("WinAuthenticateManager : SaveLocalUserSecurityData. Done");
		#endif

		return false;
	}

	
	SettingsManager * settingsManager = new SettingsManager(zAuthWCPDllDefinition.dllID);
	
	if (settingsManager -> SetUserSecurityData(pSecurityData) != ERROR_SUCCESS)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLocalUserSecurityData. Can't save user security data to registry!");
		#endif

		delete settingsManager;
		return false;
	}
	
	delete settingsManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : SaveLocalUserSecurityData. Done");
	#endif

	return true;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : SaveLoggedUserData

   Parameters :
			Input :
				userID - user ID
				authSystemID - authentication system ID

   Return : TRUE - if success

   Description : Save data of last logged user

*****************************************************************/
bool  WinAuthenticateManager :: SaveLoggedUserData(int userID, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : SaveLoggedUserData. Start");
	#endif

	SettingsManager * settingsManager = new SettingsManager(zAuthWCPDllDefinition.dllID);

	if (settingsManager -> SetLoggedUserID(userID) != ERROR_SUCCESS)
	{
		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLoggedUserData. Can't save user ID");
			WriteToLog("WinAuthenticateManager : SaveLoggedUserData. Done");
		#endif

		return false;
	}

	if (settingsManager -> SetAuthSystemID(authSystemID) != ERROR_SUCCESS)
	{
		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : SaveLoggedUserData. Can't save authentication system ID");
			WriteToLog("WinAuthenticateManager : SaveLoggedUserData. Done");
		#endif

		return false;
	}

	delete settingsManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : SaveLoggedUserData. Done");
	#endif

	return true;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : CreateWinLocalUser

   Parameters :
			Input : 
				userName - user name
				userPassword - password

   Return : Error code

  Description : Recreate local user account

*****************************************************************/
NET_API_STATUS WinAuthenticateManager :: CreateWinLocalUser(WCHAR * userName, WCHAR * userPassword)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Start");
	#endif

	NET_API_STATUS delStatus = NetUserDel(NULL, userName);

	if ((delStatus != NERR_Success) && (delStatus != NERR_UserNotFound))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Can't del previous user local account!");
			WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Done");
		#endif

		return NERR_AlertExists;
	}
	
	USER_INFO_1 ui;
	DWORD dwLevel = 1;
	DWORD dwError = 0;
	NET_API_STATUS nStatus;

	ui.usri1_name = userName;
	ui.usri1_password = userPassword;
	ui.usri1_priv = USER_PRIV_USER;
	ui.usri1_home_dir = NULL;
	ui.usri1_comment = NULL;
	ui.usri1_flags = UF_SCRIPT;
	ui.usri1_script_path = NULL;
   

	nStatus = NetUserAdd(NULL, dwLevel, (LPBYTE)&ui, &dwError);

	if (nStatus != NERR_Success)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Can't add user local account!");
			WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Done");
		#endif

		return nStatus;
	}

	DWORD sidSize;
	PSID groupSID;

	sidSize = SECURITY_MAX_SID_SIZE;
	
	if(!(groupSID = LocalAlloc(LMEM_FIXED, sidSize)))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Memory allocation error!");
			WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Done");
		#endif

		return NERR_AlertExists;
	}


	if(!CreateWellKnownSid(WinBuiltinUsersSid, NULL, groupSID, &sidSize))
	{
		LocalFree(groupSID);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CreateWinLocalUser. SID creation error!");
			WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Done");
		#endif

		return NERR_BadComponent;
	}
	else
	{
		DWORD dwSize = 256;
		WCHAR lpName[256];
		WCHAR lpDomain[256];
		SID_NAME_USE sidType;

        if(!LookupAccountSid(NULL, groupSID, lpName, &dwSize, lpDomain, &dwSize, &sidType)) 
        {
			LocalFree(groupSID);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Can't get group name!");
				WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Done");
			#endif

			return NERR_ACFNotFound;
        }
        
		LOCALGROUP_MEMBERS_INFO_3 lgmi3;
		lgmi3.lgrmi3_domainandname = userName;
		nStatus = NetLocalGroupAddMembers(NULL, lpName, 3, (LPBYTE)&lgmi3, 1);

		LocalFree(groupSID);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : CreateWinLocalUser. Done");
		#endif

		return nStatus;
	}
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : GetUserScreenContainer

   Return : Pointer to user screen container

  Description : Get user screen container

*****************************************************************/
PUSER_SCREEN_CONTAINER WinAuthenticateManager :: GetUserScreenContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Start");
	#endif

	// Get content
	content = GetUserContent();

	// Check legal DLL user
	content -= dllUserCheckResult;

	userScreenContainer = GetUserScreenContainer(content);

	DeleteContent();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Done");
	#endif

	return userScreenContainer;

}

/****************************************************************

   Class : WinAuthenticateManager

   Method : GetUserScreenContainer

   Parameters :
			Input : 
				content - user content

   Return : Pointer to user screen container

	Description : Get user screen container

*****************************************************************/
PUSER_SCREEN_CONTAINER WinAuthenticateManager :: GetUserScreenContainer(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Start");
	#endif

	// Check legal DLL user
	content -= dllUserCheckResult;
	
	// Check post login flag
	CheckPostLogin(content);

	// Check screen builder instance
	if (screenBuilder)
	{
		userScreenContainer = screenBuilder -> ClearScreenContainer(userScreenContainer);
		userScreenContainer = (PUSER_SCREEN_CONTAINER) screenBuilder -> CreateUserScreen(content);

		if ((userScreenContainer) && (currentUser) && ((currentUser -> pwdType == ONE_SYMBOL_BOX_PWD) || (currentUser -> pwdType == TWO_SYMBOL_BOX_PWD)))
		{
			for(int i = 0; i < userScreenContainer -> screenObjectsCount; i++)
			{
				if ((userScreenContainer -> screenObjects[i]) && (userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_PASSWORD_BOX))
				{
					userScreenContainer -> screenObjects[i] -> fieldDescriptor.cpft = CPFT_EDIT_TEXT;
				}
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		else
			WriteToLog("WinAuthenticateManager : GetUserScreenContainer. No ScreenBuilder instance!");

		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Done");
	#endif

	return userScreenContainer;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : GetUserScreenContainer

   Parameters :
			Input : 
				userID - ID of user

   Return : Pointer to user screen container

   Description : Get user screen container

*****************************************************************/
PUSER_SCREEN_CONTAINER WinAuthenticateManager :: GetUserScreenContainer(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Start");
		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Personal screen creation");
	#endif

	char compName[NAME_LEN];
	DWORD nameLen = NAME_LEN;

	// Get computer name
	GetComputerNameA(compName, &nameLen);

	// Get user content
	int osID = GetOSVersion();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		char message[256];
		sprintf(message, "WinAuthenticateManager : GetUserScreenContainer. OS Version : %d  ", osID);
		WriteToLog(message);
	#endif

	content = GetUserContent(compName, userID, osID);
	
	// Check legal DLL user
	content -= dllUserCheckResult;

	// Get User screen container
	userScreenContainer = GetUserScreenContainer(content);

	DeleteContent();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Done");
	#endif
	
	return userScreenContainer;

}

/****************************************************************

   Class : WinAuthenticateManager

   Method : GetUserScreenContainer

   Parameters :
			Input : 
				cpus - usage scenario
				authSystemID - authentication system ID
				
   Return : Pointer to user screen container

   Description : Get user screen container

*****************************************************************/
PUSER_SCREEN_CONTAINER WinAuthenticateManager :: GetUserScreenContainer(CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Start");
		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Create conatiner for some usage scenario.");
	#endif

	switch (cpus)
    {
		case CPUS_CREDUI:
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Cred UI scenario");
			#endif
			
			userScreenContainer = GetUserScreenContainer();
			
			if (!userScreenContainer) 
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
					WriteToLog("WinAuthenticateManager : GetUserScreenContainer. User screen container was not created!");
				#endif
									
				return NULL;
			}

			break;

		case CPUS_UNLOCK_WORKSTATION:       
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Unlock workstation scenario");
			#endif

			if ((!currentUser) || (!FirstUserSignInToday(currentUser -> userID, authSystemID)))
				userScreenContainer = GetUserScreenContainer();
			else
				userScreenContainer = GetUserScreenContainer(currentUser -> userID);

			if (!userScreenContainer) 
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
					WriteToLog("WinAuthenticateManager : GetUserScreenContainer. User screen container was not created!");
				#endif
									
				return NULL;
			}
		
			break;

		case CPUS_LOGON:

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Logon scenario");
			#endif

			if (!currentUser)
				userScreenContainer = GetUserScreenContainer();
			else
			{
				currentUser -> needStudy = currentUser -> needStudy && FirstUserSignInToday(currentUser -> userID, authSystemID);
				userScreenContainer = GetUserScreenContainer(currentUser -> userID);
			}

			if (!userScreenContainer) 
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
					WriteToLog("WinAuthenticateManager : GetUserScreenContainer. User screen container was not created!");
				#endif
					
				return NULL;
			}

			break;
    }
	
	// Check password type
	if ((currentUser) && ((currentUser -> pwdType == ONE_SYMBOL_BOX_PWD) || (currentUser -> pwdType == TWO_SYMBOL_BOX_PWD)))
	{
		symbolMatrixesList = screenBuilder -> RemoveSymbolBoxes(symbolMatrixesList);
		symbolMatrixesList = screenBuilder -> GenerateSymbolBoxes(currentUser -> pwdType);
		screenBuilder -> AddSymbolBoxesPasswordWindow(symbolMatrixesList, currentUser -> pwdType, userScreenContainer);
	}
	else
	{
		symbolMatrixesList = screenBuilder -> RemoveSymbolBoxes(symbolMatrixesList);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetUserScreenContainer. Done");
	#endif

	return userScreenContainer;
}


/****************************************************************

   Class : WinAuthenticateManager

   Method : GetUserScreenContainerPointer

   Return : Pointer to user screen container

   Description : Get user screen container pointer

*****************************************************************/
PUSER_SCREEN_CONTAINER WinAuthenticateManager :: GetUserScreenContainerPointer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetUserScreenContainerPointer");
	#endif

	return userScreenContainer;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : GetSymbolBoxesListPointer

   Return : Pointer to symbol boxes list

   Description : Get symbol boxes list pointer

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST WinAuthenticateManager :: GetSymbolBoxesListPointer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : GetSymbolBoxesListPointer");
	#endif

	return symbolMatrixesList;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : ValidateParams

   Return : Error code

   Description : Validate user parameters

*****************************************************************/
int WinAuthenticateManager :: ValidateParams(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : ValidateParams. Start");
	#endif
	
	int validateResult = RESPONSE_BAD;

	// Create athentication container
	if (CreateAuthContainer())
	{
		if (currentUser)
		{
			// Get computer name
			char compName[NAME_LEN] = "";
			unsigned long compNameLen = NAME_LEN;
			GetComputerNameA(compName, &compNameLen);

			// Validate params
			validateResult = ClientAuthManager :: ValidateParams(currentUser -> userID, compName, authContainer);
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : ValidateParams. Done");
	#endif

	return validateResult;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method :  ValidateAnswers

   Return : Error code

   Description : Validate user answers

*****************************************************************/
int WinAuthenticateManager :: ValidateAnswers(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: ValidateAnswers. Start");
	#endif

	int validateResult = RESPONSE_BAD;

	if (CreateEducationContainer())
	{
		if (currentUser)
		{
			// Get computer name
			char compName[NAME_LEN] = "";
			unsigned long compNameLen = NAME_LEN;
			GetComputerNameA(compName, &compNameLen);

			// Validate answers
			validateResult = ClientAuthManager ::  ValidateAnswers(currentUser -> userID, compName, eduContainer);
		}
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: ValidateAnswers. Done");
	#endif

	return validateResult;
}


/****************************************************************

   Class : WinAuthenticateManager

   Method : ConfirmLegalDisclaimer
   	
   Return : Error code

   Description : Valdate legal disclaimer

*****************************************************************/
int WinAuthenticateManager :: ConfirmLegalDisclaimer(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: ConfirmLegalDisclaimer. Start");
	#endif
	
	for (int i = 0; i < userScreenContainer -> subWindowCount; i++)
	{
		if (userScreenContainer -> subWindows[i] -> windowTypeId == SOT_LEGAL_DISCLAIMER_SCREEN)
		{
			// Get computer name
			char compName[NAME_LEN] = "";
			unsigned long compNameLen = NAME_LEN;
			GetComputerNameA(compName, &compNameLen);

			// Get action code
			int actionCode = CheckScheduleRecords(userID, compName, LEGAL_DISCLAIMER_FUNCTION);

			// Verify schedule records
			if ((actionCode & DENY_ACTION) == DENY_ACTION)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
					WriteToLog("ResponseValidator : ConfirmLegalDisclaimer. Legal Discalimer banned in schedule!");
					WriteToLog("ResponseValidator : ConfirmLegalDisclaimer. Done");
				#endif
						
				return RESPONSE_BAD;
			}

			// Verify schedule records
			if ((actionCode & IGNORE_ACTION) == IGNORE_ACTION)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
					WriteToLog("ResponseValidator : ConfirmLegalDisclaimer. Legal Disclaimer ignored in schedule!");
					WriteToLog("ResponseValidator : ConfirmLegalDisclaimer. Done");
				#endif

				return RESPONSE_OK;
			}
		}
	}

	for (int i = 0; i < userScreenContainer -> screenObjectsCount; i++)
		if ((userScreenContainer -> screenObjects[i] -> objectTypeID == SOT_LEGAL_DISCLAIMER_COMBOBOX) &&
			(userScreenContainer -> screenObjects[i] -> comboBoxIndex != 2))
			  return RESPONSE_BAD;

	for (int i = 0; i < userScreenContainer -> subWindowCount; i++)
	{
		if (userScreenContainer -> subWindows[i] -> windowTypeId == SOT_LEGAL_DISCLAIMER_SCREEN)
		{
			for (int j = 0; j < userScreenContainer -> subWindows[i] -> windowObjectsCount; j++)
			{
				if (userScreenContainer -> subWindows[i] -> windowObjects[j] -> objectTypeId == SOT_LEGAL_DISCLAIMER_TEXT)
					if(!SaveUserNotificationHistory(userID, userScreenContainer -> subWindows[i] -> windowObjects[j] -> questionID))
							return RESPONSE_BAD;
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager: ConfirmLegalDisclaimer. Done");
	#endif

	return RESPONSE_OK;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : EncryptWCHARString
   
   Parameters:
			Input:
				srcStr - user string
			Output:
				encStr - encrypted string
				encStrLen - encrypted string length

   Return : Error code

   Description : Encrypt user string

*****************************************************************/
bool WinAuthenticateManager :: EncryptWCHARString(WCHAR * srcStr, unsigned char * encStr, int * encStrLen)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : EncryptWCHARString. Start");
	#endif

	char tmpPwd[STR_VALUE_LEN];
	int pwdLen = wcstombs(tmpPwd, srcStr, STR_VALUE_LEN);

	if (encryptor -> EncryptAndPackSecurityData((unsigned char *)tmpPwd, pwdLen, encStr, ENCRYPTED_DATA_SIZE, encStrLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : EncryptWCHARString. Can't encrypt string!");
			WriteToLog("WinAuthenticateManager : EncryptWCHARString. Done");
		#endif

		return false;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : EncryptWCHARString. String encrypted!");
			WriteToLog("WinAuthenticateManager : EncryptWCHARString. Done");
		#endif

		return true;
	}
}


/****************************************************************

   Class : WinAuthenticateManager

   Method : DecryptWCHARString
   
   Parameters:
			Input:
				encStr - encrypted string
				encStrLen - encrypted string length
			Output:
				destStr - decrypted string

   Return : Error code

   Description : Decrypt user string

*****************************************************************/
bool WinAuthenticateManager :: DecryptWCHARString(WCHAR * destStr, unsigned char * encStr, int encStrLen)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : DecryptWCHARString. Start");
	#endif
	
	unsigned char decryptedStr[STR_VALUE_LEN];
	int decryptedStrLen;
	
	if (encryptor -> UnPackAndDecryptSecurityData(encStr, encStrLen, decryptedStr, STR_VALUE_LEN, &decryptedStrLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : DecryptWCHARString. Can't decrypt string");
			WriteToLog("WinAuthenticateManager : DecryptWCHARString. Done");
		#endif

		return false;
	}
	else
	{
		char userString[STR_VALUE_LEN];
		memcpy(userString, decryptedStr, decryptedStrLen);
		userString[decryptedStrLen] = 0;

		mbstowcs(destStr, userString, STR_VALUE_LEN);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : DecryptWCHARString. String successfully decrypted!");
			WriteToLog("WinAuthenticateManager : DecryptWCHARString. Done");
		#endif

		return true;
	}

}

/****************************************************************

   Class : WinAuthenticateManager

   Method : StringsAreEqual

   Parameters :
			Input : 
				str1 - first string
				str2 - second string

   Return : TRUE if equal

   Description : Compare two strings (case unsensetive)

*****************************************************************/
bool WinAuthenticateManager :: StringsAreEqual(WCHAR * str1, WCHAR * str2)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : StringsAreEqual. Start");
	#endif

	if ((str1 == NULL) || (str2 == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Wrong input data!");
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Done");
		#endif
		
		return false;
	}

	WCHAR copy1[STR_VALUE_LEN * 2];
	WCHAR copy2[STR_VALUE_LEN * 2];

	wcscpy(copy1, str1);
	wcscpy(copy2, str2);

	int err_no1 = _wcslwr_s(copy1, wcslen(str1) + 1); 
	int err_no2 = _wcslwr_s(copy2, wcslen(str2) + 1);

	if ((err_no1) || (err_no2))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Can't convert string value to lower case!");
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Done");
		#endif

		return false;
	}

	bool result = false;

	if (wcscmp(copy1, copy2) == 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Strings are equal");
		#endif

		result = true;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
	else
	{
		WriteToLog("WinAuthenticateManager : StringsAreEqual. Strings are not equal");
	}
	#endif


	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : StringsAreEqual. Done");
	#endif

	/*
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		char mbStr1[STR_VALUE_LEN];
		char mbStr2[STR_VALUE_LEN];
		wcstombs(mbStr1, str1, STR_VALUE_LEN);
		wcstombs(mbStr2, str2, STR_VALUE_LEN);
		
		char message[STR_VALUE_LEN * 2];
		sprintf(message, "WinAuthenticateManager : StringsAreEqual. Str1 = %s, Srt2 = %s", mbStr1, mbStr2);
		WriteToLog(message);
	#endif

	WCHAR * copy1 = wcsdup(str1);
	WCHAR * copy2 = wcsdup(str2);

	if ((copy1 == NULL) || (copy2 == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Can't create duplicates!");
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Done");
		#endif

		if (copy1) free(copy1);
		if (copy2) free(copy2);
		
		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		char mbCopyStr1[STR_VALUE_LEN];
		char mbCopyStr2[STR_VALUE_LEN];
		wcstombs(mbCopyStr1, copy1, STR_VALUE_LEN);
		wcstombs(mbCopyStr2, copy2, STR_VALUE_LEN);
		
		sprintf(message, "WinAuthenticateManager : StringsAreEqual. Copy1 = %s, Copy2 = %s", mbCopyStr1, mbCopyStr2);
		WriteToLog(message);
	#endif

	int err_no1 = _wcslwr_s(copy1, wcslen(str1) + 1); 
	int err_no2 = _wcslwr_s(copy2, wcslen(str2) + 1); 

	if ((err_no1) || (err_no2))
	{
		if (copy1) free(copy1);
		if (copy2) free(copy2);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Can't convert string value to lower case!");
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Done");
		#endif

		return false;
	}

	bool result = false;

	if (wcscmp(copy1, copy2) == 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Strings are equal");
		#endif

		result = true;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
	else
	{
		WriteToLog("WinAuthenticateManager : StringsAreEqual. Strings are not equal");
	}
	#endif

	if (copy1) free(copy1);
	if (copy2) free(copy2);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : StringsAreEqual. Done");
	#endif*/

	return result;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : StringsAreEqual

   Parameters :
			Input : 
				str1 - first string
				str2 - second string

   Return : TRUE if equal

   Description : Compare two strings (case unsensetive)

*****************************************************************/
bool WinAuthenticateManager :: StringsAreEqual(char * str1, char * str2)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : StringsAreEqual. Start");
	#endif

	char * copy1 = NULL;
	char * copy2 = NULL;

	int err_no1 = _strlwr_s(copy1 = strdup(str1), strlen(str1) + 1); 
	int err_no2 = _strlwr_s(copy2 = strdup(str2), strlen(str2) + 1); 

	if ((err_no1) || (err_no2))
	{
		if (copy1) free(copy1);
		if (copy2) free(copy2);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Can't convert string value to lower case!");
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Done");
		#endif

		return false;
	}

	bool result = false;

	if (strcmp(copy1, copy2) == 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			WriteToLog("WinAuthenticateManager : StringsAreEqual. Strings are equal");
		#endif

		result = true;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
	else
	{
		WriteToLog("WinAuthenticateManager : StringsAreEqual. Strings are not equal");
	}
	#endif

	if (copy1) free(copy1);
	if (copy2) free(copy2);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : StringsAreEqual. Done");
	#endif

	return result;
}

/****************************************************************

   Class : WinAuthenticateManager

   Method : FindUser

   Parameters :
			Input : 
				userName - name of user

   Return : user ID

   Description : Find user in list by his name

*****************************************************************/
int WinAuthenticateManager :: FindUser(char * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : FindUser. Start");
	#endif
	
	int userID = -1;

	if (userListContainer)
	{		
		for(int  i = 0; i < userListContainer -> usersCount; i++)
			if (StringsAreEqual((char *)userListContainer -> users[i] -> encUserName, userName))
			{
				userID = userListContainer -> users[i] -> userID;
				break;
			}
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
	else
		WriteToLog("WinAuthenticateManager : FindUser. UserListContainer is NULL!");


	WriteToLog("WinAuthenticateManager : FindUser. Done");
	#endif

	return userID;
}


/****************************************************************

   Class : WinAuthenticateManager

   Method : SetAutoStartPostLogin

	Return : TRUE - if success

	Description : Set post login program to windows auto start

*****************************************************************/
bool WinAuthenticateManager :: SetAutoStartPostLogin(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : SetAutoStartPostLogin. Start");
	#endif	
			
	if (postLogin)
	{
		SettingsManager * settingsManager = new SettingsManager(zAuthWCPDllDefinition.dllID);
	
		int userID = -1;
		if (currentUser)
		{
			userID = currentUser -> userID;
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : SetAutoStartPostLogin. Loaded current user ID.");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			else
			{
				WriteToLog("WinAuthenticateManager : SetAutoStartPostLogin. Current user descriptor is empty!");
			}
		#endif
				
		bool result = true;

		if (settingsManager -> SetPostLoginUserID(userID) != ERROR_SUCCESS)
		{
			result = result && false;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : SetAutoStartPostLogin. Can't set post login user ID!");
			#endif
		}
		else
		if	(settingsManager -> SetAutoStartPostLogin() != ERROR_SUCCESS)
		{
			result = result && false;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
				WriteToLog("WinAuthenticateManager : SetAutoStartPostLogin. Can't set auto start post login!");
			#endif
		}
	
		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
			if (result)
			{
				WriteToLog("WinAuthenticateManager : SetAutoStartPostLogin. Post login process established as autorun!");
				WriteToLog("WinAuthenticateManager : SetAutoStartPostLogin. Done");
			}
		#endif	

		return result;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_WCP)
		WriteToLog("WinAuthenticateManager : SetAutoStartPostLogin. No post login screens! Post login process dont established!");
		WriteToLog("WinAuthenticateManager : SetAutoStartPostLogin. Done");
	#endif	

	return false;
}