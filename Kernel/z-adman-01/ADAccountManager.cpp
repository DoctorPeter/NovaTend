/****************************************************************

   Solution : NovaTend

   Project : z-adman-01.dll

   Module : ADAccountManager.cpp

   Description : this module implements methods of
				  class ADAccountManager

*****************************************************************/

#include "stdafx.h"
#include "ADAccountManager.h"

// z-adman-01.dll definition structure
extern DLL_COMMON_DEFINITION zADManDllDefinition;

#pragma region Construction

/****************************************************************

   Class : ADAccountManager

   Method : Constructor

   Parameters :
			Input : 
				domain - domain name
				defaultOU - default OU
				defaultRootOU - default root OU
				serviceUser - admin user name
				servicePassword - admin password

*****************************************************************/
ADAccountManager :: ADAccountManager(unsigned long dllUserID, LogWriter * logWriter, WCHAR * domain, WCHAR * defaultOU, WCHAR * defaultRootOU, WCHAR * serviceUser, WCHAR * servicePassword) : SystemBase(dllUserID, &zADManDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : constructor");
	#endif
	
	// Copy all input values
	wcscpy_s(_sDomain, DOMAIN_NAME_LEN, domain);
	wcscpy_s(_sDefaultOU, OU_NAME_LEN, defaultOU);
	wcscpy_s(_sDefaultRootOU, OU_NAME_LEN, defaultRootOU);
	wcscpy_s(_sServiceUser, USER_NAME_LEN, serviceUser);
	wcscpy_s(_sServicePassword, USER_NAME_LEN, servicePassword);

	// Init COM
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		comInit = true;
	}
	else
	{
		WriteToLog("ADAccountManager : constructor --> COM library initialization failed!");
		comInit = false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : Destructor

*****************************************************************/
ADAccountManager :: ~ADAccountManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : destructor");
	#endif

	CoUninitialize();
}

#pragma endregion

#pragma region Validation

/****************************************************************

   Class : ADAccountManager

   Method : ValidateCredentials

   Parameters :
			Input : 
				userName - user name
				password - password

   Return : validation result
	
   Description :  Validate user credentials

*****************************************************************/
bool ADAccountManager :: ValidateCredentials(WCHAR * userName, WCHAR * password)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : ValidateCredentials. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ValidateCredentials. COM library not initialized!");
			WriteToLog("ADAccountManager : ValidateCredentials. Done");
		#endif

		return false;
	}

	// Prepare path
    WCHAR adspath[DOMAIN_NAME_LEN];
	wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
	wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultRootOU, DOMAIN_NAME_LEN);
		
	// Open AD Object with secure authentication
	IADs * pAuth = NULL;
    HRESULT hr = ADsOpenObject(adspath, userName, password, ADS_SECURE_AUTHENTICATION, IID_IADs, (void **)&pAuth);

	if (pAuth) pAuth -> Release();
	
	
	if (FAILED(hr))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ValidateCredentials. Validation failed!");
			WriteToLog("ADAccountManager : ValidateCredentials. Done");
		#endif

	   return false;
    }
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ValidateCredentials. Validation succeeded!");
			WriteToLog("ADAccountManager : ValidateCredentials. Done");
		#endif

	   return true;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : IsUserExpired

   Parameters :
			Input : 
				userName - user name

   Return : checking result
	
   Description :  Checks if user account expired

*****************************************************************/
bool ADAccountManager :: IsUserExpired(WCHAR * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : IsUserExpired. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsUserExpired. COM library not initialized!");
			WriteToLog("ADAccountManager : IsUserExpired. Done");
		#endif

		return true;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		DATE date;
		hr = pUser -> get_AccountExpirationDate(&date);
		pUser -> Release();

		if (SUCCEEDED(hr))
		{
			if (date <= 0) 
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
					WriteToLog("ADAccountManager : IsUserExpired. User account expired!");
					WriteToLog("ADAccountManager : IsUserExpired. Done");
				#endif

				return true;
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
					WriteToLog("ADAccountManager : IsUserExpired. User account not expired!");
					WriteToLog("ADAccountManager : IsUserExpired. Done");
				#endif

				return false;
			}
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : IsUserExpired. Can't get user account expiration date!");
				WriteToLog("ADAccountManager : IsUserExpired. Done");
			#endif

			return true;
		}

	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsUserExpired. Can't get user!");
			WriteToLog("ADAccountManager : IsUserExpired. Done");
		#endif

		return true;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : IsUserExisting

   Parameters :
			Input : 
				userName - user name

   Return : checking result
	
   Description :  Checks if user account exists

*****************************************************************/
bool ADAccountManager :: IsUserExisting(WCHAR * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : IsUserExisting. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsUserExisting. COM library not initialized!");
			WriteToLog("ADAccountManager : IsUserExisting. Done");
		#endif

		return false;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		pUser -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsUserExisting. User exists!");
			WriteToLog("ADAccountManager : IsUserExisting. Done");
		#endif

		return true;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsUserExisting. User does not exist!");
			WriteToLog("ADAccountManager : IsUserExisting. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : IsGroupExisting

   Parameters :
			Input : 
				groupName - group name

   Return : checking result
	
   Description :  Checks if user group exists

*****************************************************************/
bool ADAccountManager :: IsGroupExisting(WCHAR * groupName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : IsGroupExisting. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsGroupExisting. COM library not initialized!");
			WriteToLog("ADAccountManager : IsGroupExisting. Done");
		#endif

		return false;
	}

	IADsGroup * pGroup = NULL;
	HRESULT hr = GetGroup(groupName, &pGroup);

	if ((SUCCEEDED(hr)) && (pGroup))
	{
		pGroup -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsGroupExisting. Group exists!");
			WriteToLog("ADAccountManager : IsGroupExisting. Done");
		#endif

		return true;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsGroupExisting. Group does not exists!");
			WriteToLog("ADAccountManager : IsGroupExisting. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : IsAccountLocked

   Parameters :
			Input : 
				userName - user name

   Return : checking result
	
   Description :  Checks if user account locked

*****************************************************************/
bool ADAccountManager :: IsAccountLocked(WCHAR * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : IsAccountLocked. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsAccountLocked. COM library not initialized!");
			WriteToLog("ADAccountManager : IsAccountLocked. Done");
		#endif

		return false;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		VARIANT_BOOL flag;
		hr = pUser -> get_IsAccountLocked(&flag);
		pUser -> Release();

		if (SUCCEEDED(hr))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : IsAccountLocked. Done");
			#endif

			return (flag == VARIANT_TRUE);
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : IsAccountLocked. Can't get lock account flag!");
				WriteToLog("ADAccountManager : IsAccountLocked. Done");
			#endif

			return true;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsAccountLocked. Can't get user!");
			WriteToLog("ADAccountManager : IsAccountLocked. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : IsAccountEnabled

   Parameters :
			Input : 
				userName - user name

   Return : checking result
	
   Description :  Checks if user account enabled

*****************************************************************/
bool ADAccountManager :: IsAccountEnabled(WCHAR * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : IsAccountEnabled. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsAccountEnabled. COM library not initialized!");
			WriteToLog("ADAccountManager : IsAccountEnabled. Done");
		#endif

		return false;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		VARIANT_BOOL flag;
		hr = pUser -> get_AccountDisabled(&flag);
		pUser -> Release();

		if (SUCCEEDED(hr))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : IsAccountEnabled. Done");
			#endif

			return !(flag == VARIANT_TRUE);
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : IsAccountEnabled. Can't get enable account flag!");
				WriteToLog("ADAccountManager : IsAccountEnabled. Done");
			#endif

			return false;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsAccountEnabled. Can't get user!");
			WriteToLog("ADAccountManager : IsAccountEnabled. Done");
		#endif

		return false;
	}
}

#pragma endregion

#pragma region Users and groups

/****************************************************************

   Class : ADAccountManager

   Method : SetUserPassword

   Parameters :
			Input : 
				userName - user name
				password - password

   Return : TRUE - if operation succeeded
	
   Description :  Set user account password

*****************************************************************/
bool ADAccountManager :: SetUserPassword(WCHAR * userName, WCHAR * password)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : SetUserPassword. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : SetUserPassword. COM library not initialized!");
			WriteToLog("ADAccountManager : SetUserPassword. Done");
		#endif

		return false;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		hr = pUser -> SetPassword(password);
		pUser -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : SetUserPassword. Done");
		#endif

		return SUCCEEDED(hr);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : SetUserPassword. Can't get user!");
			WriteToLog("ADAccountManager : SetUserPassword. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : ChangeUserName

   Parameters :
			Input : 
				userName - user name
				newUserName - new user name

   Return : TRUE - if operation succeeded
	
   Description :  Set user account name

*****************************************************************/
bool ADAccountManager :: ChangeUserName(WCHAR * userName, WCHAR * newUserName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : ChangeUserName. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ChangeUserName. COM library not initialized!");
			WriteToLog("ADAccountManager : ChangeUserName. Done");
		#endif

		return false;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		VARIANT var;
		VariantInit(&var);
		V_BSTR(&var) = SysAllocString(newUserName);
		V_VT(&var) = VT_BSTR;
		hr = pUser -> Put(L"sAMAccountName", var);
		VariantClear(&var);
	
		if (FAILED(hr)) 
		{
			pUser -> Release();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeUserName. Can't set samAccountName!");
				WriteToLog("ADAccountManager : ChangeUserName. Done");
			#endif

			return false;
		}

		WCHAR userPN[USER_NAME_LEN];
		wcsncpy_s(userPN, sizeof(userPN)/sizeof(userPN[0]), newUserName, USER_NAME_LEN);
		wcsncat_s(userPN,  sizeof(userPN)/sizeof(userPN[0]), L"@", USER_NAME_LEN);
		wcsncat_s(userPN,  sizeof(userPN)/sizeof(userPN[0]), _sDomain, USER_NAME_LEN);

		V_BSTR(&var) = SysAllocString(userPN);
		V_VT(&var) = VT_BSTR;
		hr = pUser -> Put(L"userPrincipalName", var);
		VariantClear(&var);

		if (FAILED(hr)) 
		{
			pUser -> Release();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeUserName. Can't set userPrincipalName!");
				WriteToLog("ADAccountManager : ChangeUserName. Done");
			#endif

			return false;
		}

		V_BSTR(&var) = SysAllocString(newUserName);
		V_VT(&var) = VT_BSTR;
		hr = pUser -> Put(L"displayName", var);
		VariantClear(&var);
		
		if (SUCCEEDED(hr))
		{
			hr = pUser -> SetInfo();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeUserName. Account names saved successfully!");
				WriteToLog("ADAccountManager : ChangeUserName. Done");
			#endif
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeUserName. Can't set displayName!");
				WriteToLog("ADAccountManager : ChangeUserName. Done");
			#endif
		}

		pUser -> Release();

		WCHAR adspath[DOMAIN_NAME_LEN];
		wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
		wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultOU, DOMAIN_NAME_LEN);
		
		IADsContainer *pCont = NULL;
		hr = ADsGetObject(adspath, IID_IADsContainer, (void**)&pCont);

		if (FAILED(hr))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeUserName. Can't get AD container!");
				WriteToLog("ADAccountManager : ChangeUserName. Done");
			#endif

			return false;
		}

		WCHAR firstPath[DOMAIN_NAME_LEN];
		wcsncpy_s(firstPath, sizeof(firstPath)/sizeof(firstPath[0]), L"LDAP://CN=", DOMAIN_NAME_LEN);
		wcsncat_s(firstPath, sizeof(firstPath)/sizeof(firstPath[0]), userName, DOMAIN_NAME_LEN);
		wcsncat_s(firstPath, sizeof(firstPath)/sizeof(firstPath[0]), L",", DOMAIN_NAME_LEN);
		wcsncat_s(firstPath, sizeof(firstPath)/sizeof(firstPath[0]), _sDefaultOU, DOMAIN_NAME_LEN);

		WCHAR secondPath[DOMAIN_NAME_LEN];
		wcsncpy_s(secondPath, sizeof(secondPath)/sizeof(secondPath[0]), L"CN=", DOMAIN_NAME_LEN);
		wcsncat_s(secondPath, sizeof(secondPath)/sizeof(secondPath[0]), newUserName, DOMAIN_NAME_LEN);
		
		IDispatch *pDisp = NULL;
		hr = pCont -> MoveHere(firstPath, secondPath, &pDisp);
		
		pCont -> Release();
		if (pDisp) pDisp -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ChangeUserName. Done");
		#endif

		return SUCCEEDED(hr);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ChangeUserName. Can't get user!");
			WriteToLog("ADAccountManager : ChangeUserName. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : ChangeGroupName

   Parameters :
			Input : 
				groupName - group name
				newGroupName - new group name

   Return : TRUE - if operation succeeded
	
   Description :  Set user group name

*****************************************************************/
bool ADAccountManager :: ChangeGroupName(WCHAR * groupName, WCHAR * newGroupName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : ChangeGroupName. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ChangeGroupName. COM library not initialized!");
			WriteToLog("ADAccountManager : ChangeGroupName. Done");
		#endif

		return false;
	}

	IADsGroup * pGroup = NULL;
	HRESULT hr = GetGroup(groupName, &pGroup);

	if ((SUCCEEDED(hr)) && (pGroup))
	{
		VARIANT var;
		VariantInit(&var);
		V_BSTR(&var) = SysAllocString(newGroupName);
		V_VT(&var) = VT_BSTR;
		hr = pGroup -> Put(L"sAMAccountName", var);
		VariantClear(&var);
	
		if (SUCCEEDED(hr))
		{
			hr = pGroup -> SetInfo();
			pGroup -> Release();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeGroupName. Account names saved successfully!");
				WriteToLog("ADAccountManager : ChangeGroupName. Done");
			#endif
		}
		else
		{
			pGroup -> Release();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeGroupName. Can't set displayName!");
				WriteToLog("ADAccountManager : ChangeGroupName. Done");
			#endif

			return false;
		}

		WCHAR adspath[DOMAIN_NAME_LEN];
		wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
		wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultOU, DOMAIN_NAME_LEN);
		
		IADsContainer *pCont = NULL;
		hr = ADsGetObject(adspath, IID_IADsContainer, (void**)&pCont);

		if (FAILED(hr))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeGroupName. Can't get AD container!");
				WriteToLog("ADAccountManager : ChangeGroupName. Done");
			#endif

			return false;
		}

		WCHAR firstPath[DOMAIN_NAME_LEN];
		wcsncpy_s(firstPath, sizeof(firstPath)/sizeof(firstPath[0]), L"LDAP://CN=", DOMAIN_NAME_LEN);
		wcsncat_s(firstPath, sizeof(firstPath)/sizeof(firstPath[0]), groupName, DOMAIN_NAME_LEN);
		wcsncat_s(firstPath, sizeof(firstPath)/sizeof(firstPath[0]), L",", DOMAIN_NAME_LEN);
		wcsncat_s(firstPath, sizeof(firstPath)/sizeof(firstPath[0]), _sDefaultOU, DOMAIN_NAME_LEN);

		WCHAR secondPath[DOMAIN_NAME_LEN];
		wcsncpy_s(secondPath, sizeof(secondPath)/sizeof(secondPath[0]), L"CN=", DOMAIN_NAME_LEN);
		wcsncat_s(secondPath, sizeof(secondPath)/sizeof(secondPath[0]), newGroupName, DOMAIN_NAME_LEN);
		
		IDispatch *pDisp = NULL;
		hr = pCont -> MoveHere(firstPath, secondPath, &pDisp);
		
		pCont -> Release();
		if (pDisp) pDisp -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ChangeGroupName. Done");
		#endif

		return SUCCEEDED(hr);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ChangeGroupName. Can't get group!");
			WriteToLog("ADAccountManager : ChangeGroupName. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : ChangeGroupParameters

   Parameters :
			Input : 
				wGroupName - group name
				wGroupDescription - new group description
				wGroupScopeName - new group scope name
				wGroupTypeName - new group type name

   Return : TRUE - if operation succeeded
	
   Description :  Set user group parameters

*****************************************************************/
bool ADAccountManager :: ChangeGroupParameters(WCHAR * wGroupName, WCHAR * wGroupDescription, WCHAR * wGroupScopeName, WCHAR * wGroupTypeName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : ChangeGroupParameters. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ChangeGroupParameters. COM library not initialized!");
			WriteToLog("ADAccountManager : ChangeGroupParameters. Done");
		#endif

		return false;
	}

	IADsGroup * pGroup = NULL;
	HRESULT hr = GetGroup(wGroupName, &pGroup);

	if ((SUCCEEDED(hr)) && (pGroup))
	{
		VARIANT var;
		VariantInit(&var);
		V_BSTR(&var) = SysAllocString(wGroupDescription);
		V_VT(&var) = VT_BSTR;
		hr = pGroup -> Put(L"description", var);
		VariantClear(&var);
	
		if (FAILED(hr))
		{
			pGroup -> Release();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeGroupParameters. Can't save group description!");
				WriteToLog("ADAccountManager : ChangeGroupParameters. Done");
			#endif

			return false;
		}

		int iGroupType = ADS_GROUP_TYPE_GLOBAL_GROUP;
		if (_wcsicmp(L"Local", wGroupScopeName) == 0)
			iGroupType = ADS_GROUP_TYPE_DOMAIN_LOCAL_GROUP;
		else
			if (_wcsicmp(L"Universal", wGroupScopeName) == 0)
				iGroupType = ADS_GROUP_TYPE_UNIVERSAL_GROUP;

		if (_wcsicmp(L"Security", wGroupTypeName) == 0)
			iGroupType |= ADS_GROUP_TYPE_SECURITY_ENABLED;

		VariantInit(&var);
		var.intVal = iGroupType;
		V_VT(&var) = VT_I4;
		hr = pGroup -> Put(L"groupType", var);
		VariantClear(&var);

		if (FAILED(hr))
		{
			pGroup -> Release();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : ChangeGroupParameters. Can't save group type!");
				WriteToLog("ADAccountManager : ChangeGroupParameters. Done");
			#endif

			return false;
		}

		hr = pGroup -> SetInfo();
		pGroup -> Release();
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ChangeGroupName. Done");
		#endif

		return SUCCEEDED(hr);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : ChangeGroupName. Can't get group!");
			WriteToLog("ADAccountManager : ChangeGroupName. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : EnableAccount

   Parameters :
			Input : 
				userName - user name
				
   Return : TRUE - if operation succeeded
	
   Description :  Enable user account

*****************************************************************/
bool ADAccountManager :: EnableAccount(WCHAR * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : EnableAccount. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : EnableAccount. COM library not initialized!");
			WriteToLog("ADAccountManager : EnableAccount. Done");
		#endif

		return false;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		hr = pUser -> put_AccountDisabled(VARIANT_FALSE);

		if (SUCCEEDED(hr))
		{
			pUser -> SetInfo();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : EnableAccount. Account enabled!");
			#endif
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : EnableAccount. Can't enable account!");
			#endif
		}

		pUser -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : EnableAccount. Done");
		#endif

		return SUCCEEDED(hr);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : EnableAccount. Can't get user!");
			WriteToLog("ADAccountManager : EnableAccount. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : DisableAccount

   Parameters :
			Input : 
				userName - user name
				
   Return : TRUE - if operation succeeded
	
   Description :  Disable user account

*****************************************************************/
bool ADAccountManager :: DisableAccount(WCHAR * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : DisableAccount. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DisableAccount. COM library not initialized!");
			WriteToLog("ADAccountManager : DisableAccount. Done");
		#endif

		return false;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		hr = pUser -> put_AccountDisabled(VARIANT_TRUE);

		if (SUCCEEDED(hr))
		{
			pUser -> SetInfo();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : DisableAccount. Account disabled!");
			#endif
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : DisableAccount. Can't disable account!");
			#endif
		}

		pUser -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DisableAccount. Done");
		#endif

		return SUCCEEDED(hr);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DisableAccount. Can't get user!");
			WriteToLog("ADAccountManager : DisableAccount. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : LockAccount

   Parameters :
			Input : 
				userName - user name
				
   Return : TRUE - if operation succeeded
	
   Description :  Lock user account

*****************************************************************/
bool ADAccountManager :: LockAccount(WCHAR * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : LockAccount. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : LockAccount. COM library not initialized!");
			WriteToLog("ADAccountManager : LockAccount. Done");
		#endif

		return false;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		hr = pUser -> put_IsAccountLocked(VARIANT_TRUE);

		if (SUCCEEDED(hr))
		{
			pUser -> SetInfo();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : LockAccount. Account locked!");
			#endif
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : LockAccount. Can't lock account!");
			#endif
		}

		pUser -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : LockAccount. Done");
		#endif

		return SUCCEEDED(hr);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : LockAccount. Can't get user!");
			WriteToLog("ADAccountManager : LockAccount. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : UnLockAccount

   Parameters :
			Input : 
				userName - user name
				
   Return : TRUE - if operation succeeded
	
   Description :  Unlock user account

*****************************************************************/
bool ADAccountManager :: UnLockAccount(WCHAR * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : UnLockAccount. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : UnLockAccount. COM library not initialized!");
			WriteToLog("ADAccountManager : UnLockAccount. Done");
		#endif

		return false;
	}

	IADsUser * pUser = NULL;
	HRESULT hr = GetUser(userName, &pUser);

	if ((SUCCEEDED(hr)) && (pUser))
	{
		hr = pUser -> put_IsAccountLocked(VARIANT_FALSE);

		if (SUCCEEDED(hr))
		{
			pUser -> SetInfo();

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : UnLockAccount. Account unlocked!");
			#endif
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
				WriteToLog("ADAccountManager : UnLockAccount. Can't unlock account!");
			#endif
		}

		pUser -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : UnLockAccount. Done");
		#endif

		return SUCCEEDED(hr);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : UnLockAccount. Can't get user!");
			WriteToLog("ADAccountManager : UnLockAccount. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : CreateNewUser

   Parameters :
			Input : 
				userName - user name
				password - password
				
   Return : TRUE - if operation succeeded
	
   Description :  Create new user aacount

*****************************************************************/
bool ADAccountManager :: CreateNewUser(WCHAR * userName, WCHAR * password)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : CreateNewUser. Start");
	#endif

	if ((!comInit) || (wcslen(userName) > 20)) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : CreateNewUser. Wrong input data!");
			WriteToLog("ADAccountManager : CreateNewUser. Done");
		#endif

		return false;
	}

	WCHAR adspath[DOMAIN_NAME_LEN];
	wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
	wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultOU, DOMAIN_NAME_LEN);

	IDirectoryObject * pDirObject = NULL;
    HRESULT hr = ADsOpenObject(adspath, _sServiceUser, _sServicePassword, ADS_SECURE_AUTHENTICATION, IID_IDirectoryObject, (void **)&pDirObject);

	if (FAILED(hr))	
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : CreateNewUser. Can't open AD container!");
			WriteToLog("ADAccountManager : CreateNewUser. Done");
		#endif

		return false;
	}

	ADSVALUE sAMValue;
	ADSVALUE uPNValue;
    ADSVALUE classValue;
    
    WCHAR pwCommonNameFull[1024];
    
    ADS_ATTR_INFO  attrInfo[] = {{L"objectClass", ADS_ATTR_UPDATE, ADSTYPE_CASE_IGNORE_STRING, &classValue, 1},
							     {L"sAMAccountName", ADS_ATTR_UPDATE, ADSTYPE_CASE_IGNORE_STRING, &sAMValue, 1},
								 {L"userPrincipalName", ADS_ATTR_UPDATE, ADSTYPE_CASE_IGNORE_STRING, &uPNValue, 1},};

    DWORD dwAttrs = sizeof(attrInfo)/sizeof(ADS_ATTR_INFO); 
    classValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
    classValue.CaseIgnoreString = L"User";
   
    sAMValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
    sAMValue.CaseIgnoreString = userName;
 
	WCHAR userPN[USER_NAME_LEN];
	wcsncpy_s(userPN, sizeof(userPN)/sizeof(userPN[0]), userName, USER_NAME_LEN);
	wcsncat_s(userPN,  sizeof(userPN)/sizeof(userPN[0]), L"@", USER_NAME_LEN);
	wcsncat_s(userPN,  sizeof(userPN)/sizeof(userPN[0]), _sDomain, USER_NAME_LEN);

	uPNValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	uPNValue.CaseIgnoreString = userPN;

    wsprintfW(pwCommonNameFull, L"CN=%s", userName);
    
	LPDISPATCH pDisp;
    hr = pDirObject -> CreateDSObject(pwCommonNameFull, attrInfo, dwAttrs, &pDisp);
	pDirObject -> Release();

    if (SUCCEEDED(hr))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : CreateNewUser. Success!");
			WriteToLog("ADAccountManager : CreateNewUser. Done");
		#endif

		return EnableAccount(userName) && SetUserPassword(userName, password);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : CreateNewUser. Fail!");
			WriteToLog("ADAccountManager : CreateNewUser. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : CreateNewGroup

   Parameters :
			Input : 
				groupName - group name
				groupDescription - group description
				groupScopeName - group scope
				groupTypeName - group type
				
   Return : TRUE - if operation succeeded
	
   Description :  Create new group

*****************************************************************/
bool ADAccountManager :: CreateNewGroup(WCHAR * groupName, WCHAR * groupDescription, WCHAR * groupScopeName, WCHAR * groupTypeName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : CreateNewGroup. Start");
	#endif

	if ((!comInit) || (groupName == NULL) || (groupDescription == NULL) || (groupScopeName == NULL) || (groupTypeName == NULL) || (wcslen(groupName) > 20))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : CreateNewGroup. Wrong input data!");
			WriteToLog("ADAccountManager : CreateNewGroup. Done");
		#endif

		return false;
	}

	WCHAR adspath[DOMAIN_NAME_LEN];
	wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
	wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultOU, DOMAIN_NAME_LEN);

	IDirectoryObject * pDirObject = NULL;
    HRESULT hr = ADsOpenObject(adspath, _sServiceUser, _sServicePassword, ADS_SECURE_AUTHENTICATION, IID_IDirectoryObject, (void **)&pDirObject);

	if (FAILED(hr))	
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : CreateNewGroup. Can't open AD container!");
			WriteToLog("ADAccountManager : CreateNewGroup. Done");
		#endif

		return false;
	}

	ADSVALUE descriptionValue;
	ADSVALUE sAMValue;
	ADSVALUE groupType;
    ADSVALUE classValue;
    
    WCHAR pwCommonNameFull[1024];
    
    ADS_ATTR_INFO  attrInfo[] = {{L"objectClass", ADS_ATTR_UPDATE, ADSTYPE_CASE_IGNORE_STRING, &classValue, 1},
							     {L"sAMAccountName", ADS_ATTR_UPDATE, ADSTYPE_CASE_IGNORE_STRING, &sAMValue, 1},
								 {L"groupType", ADS_ATTR_UPDATE, ADSTYPE_INTEGER, &groupType, 1},
								 {L"description", ADS_ATTR_UPDATE, ADSTYPE_CASE_IGNORE_STRING, &descriptionValue, 1}};

    DWORD dwAttrs = sizeof(attrInfo)/sizeof(ADS_ATTR_INFO); 
    classValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
    classValue.CaseIgnoreString = L"group";
   
    sAMValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
    sAMValue.CaseIgnoreString = groupName;

	descriptionValue.dwType = ADSTYPE_CASE_IGNORE_STRING;
	descriptionValue.CaseIgnoreString = groupDescription;
 
	int iGroupType = ADS_GROUP_TYPE_GLOBAL_GROUP;
	if (_wcsicmp(L"Local", groupScopeName) == 0)
		iGroupType = ADS_GROUP_TYPE_DOMAIN_LOCAL_GROUP;
	else 
		if (_wcsicmp(L"Universal", groupScopeName) == 0)
			iGroupType = ADS_GROUP_TYPE_UNIVERSAL_GROUP;

	if (_wcsicmp(L"Security", groupTypeName) == 0)
		iGroupType |= ADS_GROUP_TYPE_SECURITY_ENABLED;
	
	groupType.dwType = ADSTYPE_INTEGER;
	groupType.Integer = iGroupType;

    wsprintfW(pwCommonNameFull, L"CN=%s", groupName);
    
	LPDISPATCH pDisp;
    hr = pDirObject -> CreateDSObject(pwCommonNameFull, attrInfo, dwAttrs, &pDisp);
	pDirObject -> Release();

    if (SUCCEEDED(hr))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : CreateNewGroup. Success!");
			WriteToLog("ADAccountManager : CreateNewGroup. Done");
		#endif

		return true;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : CreateNewGroup. Fail!");
			WriteToLog("ADAccountManager : CreateNewGroup. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : DeleteUser

   Parameters :
			Input : 
				userName - user name
				
   Return : TRUE - if operation succeeded
	
   Description :  Delete user account

*****************************************************************/
bool ADAccountManager :: DeleteUser(WCHAR * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : DeleteUser. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DeleteUser. COM library not initialized!");
			WriteToLog("ADAccountManager : DeleteUser. Done");
		#endif

		return false;
	}

	WCHAR adspath[DOMAIN_NAME_LEN];
	wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
	wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultOU, DOMAIN_NAME_LEN);

	IDirectoryObject * pDirObject = NULL;
    HRESULT hr = ADsOpenObject(adspath, _sServiceUser, _sServicePassword, ADS_SECURE_AUTHENTICATION, IID_IDirectoryObject, (void **)&pDirObject);

	if (FAILED(hr))	
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DeleteUser. Can't open AD container!");
			WriteToLog("ADAccountManager : DeleteUser. Done");
		#endif

		return false;
	}
		    
    WCHAR pwCommonNameFull[1024];
    wsprintfW(pwCommonNameFull, L"CN=%s", userName);

    hr = pDirObject -> DeleteDSObject(pwCommonNameFull);
	pDirObject -> Release();

    if (SUCCEEDED(hr))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DeleteUser. Success!");
			WriteToLog("ADAccountManager : DeleteUser. Done");
		#endif

		return true;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DeleteUser. Fail!");
			WriteToLog("ADAccountManager : DeleteUser. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : DeleteGroup

   Parameters :
			Input : 
				groupName - user name
				
   Return : TRUE - if operation succeeded
	
   Description :  Delete group

*****************************************************************/
bool ADAccountManager :: DeleteGroup(WCHAR * groupName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : DeleteGroup. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DeleteGroup. COM library not initialized!");
			WriteToLog("ADAccountManager : DeleteGroup. Done");
		#endif

		return false;
	}

	WCHAR adspath[DOMAIN_NAME_LEN];
	wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
	wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultOU, DOMAIN_NAME_LEN);

	IDirectoryObject * pDirObject = NULL;
    HRESULT hr = ADsOpenObject(adspath, _sServiceUser, _sServicePassword, ADS_SECURE_AUTHENTICATION, IID_IDirectoryObject, (void **)&pDirObject);

	if (FAILED(hr))	
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DeleteGroup. Can't open AD container!");
			WriteToLog("ADAccountManager : DeleteGroup. Done");
		#endif

		return false;
	}
		    
    WCHAR pwCommonNameFull[1024];
	wsprintfW(pwCommonNameFull, L"CN=%s", groupName);

    hr = pDirObject -> DeleteDSObject(pwCommonNameFull);
	pDirObject -> Release();

    if (SUCCEEDED(hr))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DeleteGroup. Success!");
			WriteToLog("ADAccountManager : DeleteGroup. Done");
		#endif

		return true;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : DeleteGroup. Fail!");
			WriteToLog("ADAccountManager : DeleteGroup. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : IsUserGroupMember

   Parameters :
			Input : 
				userName - user name
				groupName - group name
				
   Return : TRUE - if operation succeeded
	
   Description :  Check if the user belongs to some group

*****************************************************************/
bool ADAccountManager :: IsUserGroupMember(WCHAR * userName, WCHAR * groupName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : IsUserGroupMember. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsUserGroupMember. COM library not initialized!");
			WriteToLog("ADAccountManager : IsUserGroupMember. Done");
		#endif

		return false;
	}

	IADsGroup * pGroup = NULL;
	HRESULT hr = GetGroup(groupName, &pGroup);

	if ((SUCCEEDED(hr)) && (pGroup))
	{
		WCHAR userPath[DOMAIN_NAME_LEN];
		wcsncpy_s(userPath, sizeof(userPath) / sizeof(userPath[0]), L"LDAP://CN=", DOMAIN_NAME_LEN);
		wcsncat_s(userPath, sizeof(userPath) / sizeof(userPath[0]), userName, DOMAIN_NAME_LEN);
		wcsncat_s(userPath, sizeof(userPath) / sizeof(userPath[0]), L",", DOMAIN_NAME_LEN);
		wcsncat_s(userPath, sizeof(userPath) / sizeof(userPath[0]), _sDefaultOU, DOMAIN_NAME_LEN);

		VARIANT_BOOL inG = false;
		hr = pGroup -> IsMember(userPath, &inG);
		
		pGroup -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsUserGroupMember. Done");
		#endif

		return ((SUCCEEDED(hr)) && (inG == true));
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : IsUserGroupMember. Can't get group!");
			WriteToLog("ADAccountManager : IsUserGroupMember. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : AddUserToGroup

   Parameters :
			Input : 
				userName - user name
				groupName - group name
				
   Return : TRUE - if operation succeeded
	
   Description :  Add user to group

*****************************************************************/
bool ADAccountManager :: AddUserToGroup(WCHAR * userName, WCHAR * groupName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : AddUserToGroup. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : AddUserToGroup. COM library not initialized!");
			WriteToLog("ADAccountManager : AddUserToGroup. Done");
		#endif

		return false;
	}

	IADsGroup * pGroup = NULL;
	HRESULT hr = GetGroup(groupName, &pGroup);

	if ((SUCCEEDED(hr)) && (pGroup))
	{
		WCHAR userPath[DOMAIN_NAME_LEN];
		wcsncpy_s(userPath, sizeof(userPath) / sizeof(userPath[0]), L"LDAP://CN=", DOMAIN_NAME_LEN);
		wcsncat_s(userPath, sizeof(userPath) / sizeof(userPath[0]), userName, DOMAIN_NAME_LEN);
		wcsncat_s(userPath, sizeof(userPath) / sizeof(userPath[0]), L",", DOMAIN_NAME_LEN);
		wcsncat_s(userPath, sizeof(userPath) / sizeof(userPath[0]), _sDefaultOU, DOMAIN_NAME_LEN);

		hr = pGroup -> Add(userPath);
		
		pGroup -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : AddUserToGroup. Done");
		#endif

		return (SUCCEEDED(hr));
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : AddUserToGroup. Can't get group!");
			WriteToLog("ADAccountManager : AddUserToGroup. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : RemoveUserFromGroup

   Parameters :
			Input : 
				userName - user name
				groupName - group name
				
   Return : TRUE - if operation succeeded
	
   Description :  Remove user from group

*****************************************************************/
bool ADAccountManager :: RemoveUserFromGroup(WCHAR * userName, WCHAR * groupName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : RemoveUserFromGroup. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : RemoveUserFromGroup. COM library not initialized!");
			WriteToLog("ADAccountManager : RemoveUserFromGroup. Done");
		#endif

		return false;
	}

	IADsGroup * pGroup = NULL;
	HRESULT hr = GetGroup(groupName, &pGroup);

	if ((SUCCEEDED(hr)) && (pGroup))
	{
		WCHAR userPath[DOMAIN_NAME_LEN];
		wcsncpy_s(userPath, sizeof(userPath) / sizeof(userPath[0]), L"LDAP://CN=", DOMAIN_NAME_LEN);
		wcsncat_s(userPath, sizeof(userPath) / sizeof(userPath[0]), userName, DOMAIN_NAME_LEN);
		wcsncat_s(userPath, sizeof(userPath) / sizeof(userPath[0]), L",", DOMAIN_NAME_LEN);
		wcsncat_s(userPath, sizeof(userPath) / sizeof(userPath[0]), _sDefaultOU, DOMAIN_NAME_LEN);

		hr = pGroup -> Remove(userPath);
		
		pGroup -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : RemoveUserFromGroup. Done");
		#endif

		return (SUCCEEDED(hr));
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : RemoveUserFromGroup. Can't get group!");
			WriteToLog("ADAccountManager : RemoveUserFromGroup. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : ADAccountManager

   Method : EnumUserAccounts

   Parameters :
			Output : 
				userList - list of user names
				
   Return : TRUE - if operation succeeded
	
   Description :  Enumerate users

*****************************************************************/
bool ADAccountManager :: EnumUserAccounts(PNAMES_LIST userList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : EnumUserAccounts. Start");
	#endif

	if ((!comInit) || (!userList)) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : EnumUserAccounts. Wrong input data!");
			WriteToLog("ADAccountManager : EnumUserAccounts. Done");
		#endif

		return false;
	}

	userList -> itemsCount = 0;

	WCHAR adspath[DOMAIN_NAME_LEN];
	wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
	wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultRootOU, DOMAIN_NAME_LEN);

	IDirectorySearch *pContainerToSearch = NULL;
    HRESULT hr = ADsOpenObject(adspath, _sServiceUser, _sServicePassword, ADS_SECURE_AUTHENTICATION, IID_IDirectorySearch, (void **)&pContainerToSearch);

	if (FAILED(hr))	
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : EnumUserAccounts. Can't open AD searcher!");
			WriteToLog("ADAccountManager : EnumUserAccounts. Done");
		#endif

		return false;
	}

	WCHAR pszSearchFilter[] = L"(&(objectClass=user)(objectCategory=person))";

	//Specify subtree search
	ADS_SEARCHPREF_INFO SearchPrefs;
	SearchPrefs.dwSearchPref = ADS_SEARCHPREF_SEARCH_SCOPE;
	SearchPrefs.vValue.dwType = ADSTYPE_INTEGER;
	SearchPrefs.vValue.Integer = ADS_SCOPE_SUBTREE;
    DWORD dwNumPrefs = 1;

	// COL for iterations
	LPOLESTR pszColumn = NULL;    
	ADS_SEARCH_COLUMN col;
    
    // Handle used for searching
    ADS_SEARCH_HANDLE hSearch = NULL;
	
	// Set the search preference
    hr = pContainerToSearch -> SetSearchPreference(&SearchPrefs, dwNumPrefs);
    if (FAILED(hr))
	{
		pContainerToSearch -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : EnumUserAccounts. Wrong search preferences!");
			WriteToLog("ADAccountManager : EnumUserAccounts. Done");
		#endif

        return false;
	}

	LPOLESTR propList[] = {L"name"};
	unsigned long popsCount = 1;

	hr = pContainerToSearch -> ExecuteSearch(pszSearchFilter, propList, popsCount, &hSearch);

    if (FAILED(hr))
	{
		pContainerToSearch -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : EnumUserAccounts. Wrong search parameters!");
			WriteToLog("ADAccountManager : EnumUserAccounts. Done");
		#endif

        return false;
	}

	hr = pContainerToSearch -> GetFirstRow(hSearch);
	
	if (FAILED(hr))
	{
		pContainerToSearch -> CloseSearchHandle(hSearch);
		pContainerToSearch -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : EnumUserAccounts. Can't retrieve searched data!");
			WriteToLog("ADAccountManager : EnumUserAccounts. Done");
		#endif

        return false;
	}

	int iCount = 0;

    while(hr != S_ADS_NOMORE_ROWS)
	{
		//Keep track of count.
		iCount++;

		// loop through the array of passed column names,
        // print the data for each column
		while (pContainerToSearch -> GetNextColumnName(hSearch, &pszColumn) != S_ADS_NOMORE_COLUMNS)
        {
			hr = pContainerToSearch -> GetColumn(hSearch, pszColumn, &col);

			if (SUCCEEDED(hr))
			{
				if (wcscmp(L"name", pszColumn) == 0)
				{
					userList -> items[userList -> itemsCount][0] = L'\0';
					wcscpy_s(userList -> items[userList -> itemsCount], MAX_PATH, col.pADsValues -> CaseIgnoreString);
					userList -> itemsCount++;
				}

				pContainerToSearch -> FreeColumn(&col);
			}

			FreeADsMem(pszColumn);
		}

		hr = pContainerToSearch -> GetNextRow(hSearch);
	}
	

	// Close the search handle to clean up
    pContainerToSearch -> CloseSearchHandle(hSearch);
	pContainerToSearch -> Release();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : EnumUserAccounts. Done");
	#endif

    return true;
}

#pragma endregion

#pragma region Searching

/****************************************************************

   Class : ADAccountManager

   Method : GetUser

   Parameters :
			Input : 
				pSearchBase - directory searcher
				userName - user name
			Output:
				ppUser -IADs object

   Return : Error code
	
   Description :  Get user IADs object

*****************************************************************/
HRESULT ADAccountManager :: GetUser(IDirectorySearch * pSearchBase, WCHAR * userName, IADs ** ppUser)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : GetUser. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetUser. COM library not initialized!");
			WriteToLog("ADAccountManager : GetUser. Done");
		#endif

		return E_FAIL;
	}

    WCHAR pszSearchFilter[MAX_PATH];
    WCHAR pszADsPath[MAX_PATH];
    ADS_SEARCHPREF_INFO searchPrefs;
    ADS_SEARCH_COLUMN col;
    ADS_SEARCH_HANDLE hSearch;
    LPWSTR pszAttribute[1] = {L"ADsPath"};   
	
	*ppUser = NULL;

    if ((pSearchBase == NULL) || (userName == NULL) || (ppUser == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetUser. Wrong input data");
			WriteToLog("ADAccountManager : GetUser. Done");
		#endif

		return E_INVALIDARG;
	}
    
    // Build search filter.
    if (_snwprintf_s(pszSearchFilter, sizeof(pszSearchFilter)/sizeof(pszSearchFilter[0]), MAX_PATH, L"(&(objectCategory=person)(objectClass=user)(cn=%ws))", userName) < 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetUser. Can't prepare search string");
			WriteToLog("ADAccountManager : GetUser. Done");
		#endif

        return E_INVALIDARG;
	}
 
    ZeroMemory(&searchPrefs, sizeof(searchPrefs)) ;
    searchPrefs.dwSearchPref = ADS_SEARCHPREF_SEARCH_SCOPE;
    searchPrefs.vValue.dwType = ADSTYPE_INTEGER;
    searchPrefs.vValue.Integer = ADS_SCOPE_SUBTREE;
    
	HRESULT hr = pSearchBase -> SetSearchPreference(&searchPrefs, 1) ;

    if (FAILED(hr))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetUser. Wrong search preferences");
			WriteToLog("ADAccountManager : GetUser. Done");
		#endif

        return hr;
	}
    
    hr = pSearchBase -> ExecuteSearch(pszSearchFilter, pszAttribute, 1, &hSearch) ;

    if (SUCCEEDED(hr))
	{
        if (pSearchBase -> GetNextRow(hSearch) != S_ADS_NOMORE_ROWS)
		{       
            hr = pSearchBase -> GetColumn(hSearch, pszAttribute[0], &col) ;

            if (SUCCEEDED(hr)) 
			{
                wcsncpy_s(pszADsPath, sizeof(pszADsPath)/sizeof(pszADsPath[0]), col.pADsValues -> CaseIgnoreString, MAX_PATH) ;
                pszADsPath[MAX_PATH - 1] = 0 ;

                hr = ADsOpenObject(pszADsPath, NULL, NULL, ADS_SECURE_AUTHENTICATION, IID_IADs, (void**)ppUser);

                pSearchBase -> FreeColumn(&col) ;
            }            
        }

        pSearchBase -> CloseSearchHandle(hSearch) ;
    }

	if ((FAILED(hr)) || (*ppUser == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetUser. Can't get user!");
		#endif

		hr = E_FAIL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : GetUser. Done");
	#endif

    return hr;
}

/****************************************************************

   Class : ADAccountManager

   Method : GetUser

   Parameters :
			Input : 
				userName - user name
			Output:
				pUser -IADsUser object

   Return : Error code
	
   Description :  Get user IADsUser object

*****************************************************************/
HRESULT ADAccountManager :: GetUser(WCHAR * userName, IADsUser **pUser)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : GetUser. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetUser. COM library not initialized!");
			WriteToLog("ADAccountManager : GetUser. Done");
		#endif

		return E_FAIL;
	}

	WCHAR adspath[DOMAIN_NAME_LEN];
	wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
	wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultRootOU, DOMAIN_NAME_LEN);

	IADs * pObject = NULL;
    HRESULT hr = ADsOpenObject(adspath, _sServiceUser, _sServicePassword, ADS_SECURE_AUTHENTICATION, IID_IADs, (void **)&pObject);

	if (SUCCEEDED(hr))
	{
		IDirectorySearch *pDS = NULL;
		HRESULT hr = pObject -> QueryInterface(IID_IDirectorySearch, (void **)&pDS);

		if (SUCCEEDED(hr))
		{
			hr = GetUser(pDS, userName, &pObject);

			if (SUCCEEDED(hr))
			{
				*pUser = NULL;
				hr = pObject -> QueryInterface(IID_IADsUser, (void**)pUser);
			}

			if (pDS) pDS -> Release();
		}

		if (pObject) pObject -> Release();
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		if (FAILED(hr))	WriteToLog("ADAccountManager : GetUser. Can't get user!");
		WriteToLog("ADAccountManager : GetUser. Done");
	#endif

	return hr;
}

/****************************************************************

   Class : ADAccountManager

   Method : GetGroup

   Parameters :
			Input : 
				pSearchBase - directory searcher
				groupName - group name

			Output:
				ppGroup - IADs object

   Return : Error code
	
   Description :  Get group IADs object

*****************************************************************/
HRESULT ADAccountManager :: GetGroup(IDirectorySearch * pSearchBase, WCHAR * groupName, IADs ** ppGroup)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : GetGroup. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetGroup. COM library not initialized!");
			WriteToLog("ADAccountManager : GetGroup. Done");
		#endif

		return E_FAIL;
	}

    WCHAR pszSearchFilter[MAX_PATH];
    WCHAR pszADsPath[MAX_PATH];
    ADS_SEARCHPREF_INFO searchPrefs;
    ADS_SEARCH_COLUMN col;
    ADS_SEARCH_HANDLE hSearch;
    LPWSTR pszAttribute[1] = {L"ADsPath"};   
	
	*ppGroup = NULL;

    if ((pSearchBase == NULL) || (groupName == NULL) || (ppGroup == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetGroup. Wrong input data");
			WriteToLog("ADAccountManager : GetGroup. Done");
		#endif

		return E_INVALIDARG;
	}
    
    // Build search filter.
	if (_snwprintf_s(pszSearchFilter, sizeof(pszSearchFilter)/sizeof(pszSearchFilter[0]), MAX_PATH, L"(&(objectCategory=group)(objectClass=group)(cn=%ws))", groupName) < 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetGroup. Can't prepare search string");
			WriteToLog("ADAccountManager : GetGroup. Done");
		#endif

        return E_INVALIDARG;
	}
 
    ZeroMemory(&searchPrefs, sizeof(searchPrefs)) ;
    searchPrefs.dwSearchPref = ADS_SEARCHPREF_SEARCH_SCOPE;
    searchPrefs.vValue.dwType = ADSTYPE_INTEGER;
    searchPrefs.vValue.Integer = ADS_SCOPE_SUBTREE;
    
	HRESULT hr = pSearchBase -> SetSearchPreference(&searchPrefs, 1) ;

    if (FAILED(hr))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetGroup. Wrong search preferences");
			WriteToLog("ADAccountManager : GetGroup. Done");
		#endif

        return hr;
	}
    
    hr = pSearchBase -> ExecuteSearch(pszSearchFilter, pszAttribute, 1, &hSearch) ;

    if (SUCCEEDED(hr))
	{
        if (pSearchBase -> GetNextRow(hSearch) != S_ADS_NOMORE_ROWS)
		{       
            hr = pSearchBase -> GetColumn(hSearch, pszAttribute[0], &col) ;

            if (SUCCEEDED(hr)) 
			{
                wcsncpy_s(pszADsPath, sizeof(pszADsPath)/sizeof(pszADsPath[0]), col.pADsValues -> CaseIgnoreString, MAX_PATH) ;
                pszADsPath[MAX_PATH - 1] = 0 ;

                hr = ADsOpenObject(pszADsPath, NULL, NULL, ADS_SECURE_AUTHENTICATION, IID_IADs, (void**)ppGroup);

                pSearchBase -> FreeColumn(&col) ;
            }            
        }

        pSearchBase -> CloseSearchHandle(hSearch) ;
    }

	if ((FAILED(hr)) || (*ppGroup == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetGroup. Can't get group!");
		#endif

		hr = E_FAIL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : GetGroup. Done");
	#endif

    return hr;
}

/****************************************************************

   Class : ADAccountManager

   Method : GetGroup

   Parameters :
			Input : 
				groupName - group name
			Output:
				pGroup - IADsGroup object

   Return : Error code
	
   Description :  Get IADsGroup object

*****************************************************************/
HRESULT ADAccountManager :: GetGroup(WCHAR * groupName, IADsGroup **pGroup)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADAccountManager : GetGroup. Start");
	#endif

	if (!comInit) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
			WriteToLog("ADAccountManager : GetGroup. COM library not initialized!");
			WriteToLog("ADAccountManager : GetGroup. Done");
		#endif

		return E_FAIL;
	}

	WCHAR adspath[DOMAIN_NAME_LEN];
	wcsncpy_s(adspath, sizeof(adspath)/sizeof(adspath[0]), L"LDAP://", DOMAIN_NAME_LEN);
	wcsncat_s(adspath,  sizeof(adspath)/sizeof(adspath[0]), _sDefaultRootOU, DOMAIN_NAME_LEN);

	IADs * pObject = NULL;
    HRESULT hr = ADsOpenObject(adspath, _sServiceUser, _sServicePassword, ADS_SECURE_AUTHENTICATION, IID_IADs, (void **)&pObject);

	if (SUCCEEDED(hr))
	{
		IDirectorySearch *pDS = NULL;
		HRESULT hr = pObject -> QueryInterface(IID_IDirectorySearch, (void **)&pDS);

		if (SUCCEEDED(hr))
		{
			hr = GetGroup(pDS, groupName, &pObject);

			if (SUCCEEDED(hr))
			{
				*pGroup = NULL;
				hr = pObject -> QueryInterface(IID_IADsGroup, (void**)pGroup);
			}

			if (pDS) pDS -> Release();
		}

		if (pObject) pObject -> Release();
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		if (FAILED(hr))	WriteToLog("ADAccountManager : GetGroup. Can't get group!");
		WriteToLog("ADAccountManager : GetGroup. Done");
	#endif

	return hr;
}

#pragma endregion

#pragma region LOG

/****************************************************************

   Class : ADAccountManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  ADAccountManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion
