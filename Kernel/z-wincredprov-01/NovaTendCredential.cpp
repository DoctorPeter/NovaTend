/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : NovaTendCredential.cpp

   Description :  Implements methods of class
                  NovaTendCredential

*****************************************************************/


#ifndef WIN32_NO_STATUS
#include <ntstatus.h>
#define WIN32_NO_STATUS
#endif

#include "NovaTendCredential.h"

#include <unknwn.h>
#include "guid.h"
#include <wincred.h>

#include <SettingsManager.h>

// z-wincredprov-01.dll definition structure
extern DLL_COMMON_DEFINITION zWinCredProvDllDefinition;

// Screen rebuild flag
BOOL _gScreenRebuilded = TRUE;

// Set selected credential flag
BOOL _gSetSelected = FALSE;


/****************************************************************

   Function : EnumLogoScreenUIElementsUserNameBoxFunc

   Parameters:
			Input:
				hWnd - handle to a child window of the parent 
					   window specified in EnumChildWindows

				lParam - application-defined value given 
						 in EnumChildWindows. In this case
						 it is a pointer to the last user name
   
   Returns : to continue enumeration, the callback function must 
			 return TRUE; to stop enumeration, it must return FALSE.
			
   Description:  callback function used with the EnumChildWindows function
  
*****************************************************************/
BOOL CALLBACK EnumLogoScreenUIElementsUserNameBoxFunc(HWND hWnd, LPARAM lParam)
{    
	WCHAR * lastUserName = (WCHAR *)lParam;
	WCHAR wndClassName[STR_VALUE_LEN];
	WCHAR buffer[STR_VALUE_LEN];

    GetClassName(hWnd, wndClassName, STR_VALUE_LEN);
	//MessageBox(NULL, wndClassName, L"MessageBox", MB_OK|MB_ICONWARNING);
	if (wcscmp(wndClassName, L"Edit") == 0)
	{
		SendMessage(hWnd, WM_GETTEXT, (WPARAM)STR_VALUE_LEN, (LPARAM)buffer);
		
		if (wcscmp(buffer, lastUserName) == 0)
		{
			size_t textSize = wcslen(buffer);
			SendMessage(hWnd, EM_SETSEL, textSize, textSize);
			_gScreenRebuilded = FALSE;
			return FALSE;
		}
	}

    return TRUE;
}

/****************************************************************

   Function : EnumLogoScreenUIElementsPasswordBoxFunc

   Parameters:
			Input:
				hWnd - handle to a child window of the parent 
					   window specified in EnumChildWindows

				lParam - application-defined value given 
						 in EnumChildWindows. In this case
						 it is a pointer to the last user name
   
   Returns : to continue enumeration, the callback function must 
			 return TRUE; to stop enumeration, it must return FALSE.
			
   Description:  callback function used with the EnumChildWindows function
  
*****************************************************************/
BOOL CALLBACK EnumLogoScreenUIElementsPasswordBoxFunc(HWND hWnd, LPARAM lParam)
{    
	NovaTendCredential * _this = (NovaTendCredential *)lParam;

	if (_this == NULL) return FALSE;
	
	WCHAR wndClassName[STR_VALUE_LEN];
	//WCHAR buffer[STR_VALUE_LEN];

    GetClassName(hWnd, wndClassName, STR_VALUE_LEN);
	//MessageBox(NULL, wndClassName, L"MessageBox", MB_OK|MB_ICONWARNING);
	if (wcscmp(wndClassName, L"Edit") == 0)
	{
		if (_this -> CheckPasswordBoxControl(hWnd))
		{
			return FALSE;
		}
	}

    return TRUE;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : CheckPasswordBoxControl

   Parameters:
			Input:
				hWnd - handle of edit control
   
   Returns : TRUE - if password box was found
			
   Description:  Check main screen control for pasword box
  
*****************************************************************/
BOOL NovaTendCredential :: CheckPasswordBoxControl(HWND hWnd)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: CheckPasswordBoxControl. Start");
	#endif

	if (!_authManager)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential: CheckPasswordBoxControl. Wrong authentication manager instance!");
			WriteToLog("NovaTendCredential: CheckPasswordBoxControl. Done");
		#endif
		
		return FALSE;
	}

	int pwdScrInd = _authManager -> GetSymbolBoxPasswordWindowIndex();
	int pwdInd = _authManager -> GetPasswortTextFieldIndex();

	if ((pwdScrInd != -1) && (pwdInd != -1) && (_pInfoWnd[pwdScrInd]))
	{
		WCHAR lblBuffer[STR_VALUE_LEN];
		SendMessage(hWnd, EM_GETCUEBANNER, (WPARAM)lblBuffer, (LPARAM)STR_VALUE_LEN);

		if ((_usrScrCnt) && (wcscmp(lblBuffer, _usrScrCnt -> screenObjects[pwdInd] -> fieldDescriptor.pszLabel) == 0))
		{
			_pInfoWnd[pwdScrInd] -> hPasswordBox = hWnd;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: CheckPasswordBoxControl. Password box successfully found!");
				WriteToLog("NovaTendCredential: CheckPasswordBoxControl. Done");
			#endif

			return TRUE;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: CheckPasswordBoxControl. Wrong edit control label");
				WriteToLog("NovaTendCredential: CheckPasswordBoxControl. Done");
			#endif

			return FALSE;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential: CheckPasswordBoxControl. No password box or symbol box window");
			WriteToLog("NovaTendCredential: CheckPasswordBoxControl. Done");
		#endif

		return FALSE;
	}
}

/****************************************************************

   Class :  NovaTendCredential

   Method : Constructor
  
*****************************************************************/
NovaTendCredential :: NovaTendCredential() : _cRef(1)
{
    DllAddRef();
	
	_usrScrCnt = NULL;
	_usrLstCnt = NULL;
	_lastUserDescr = NULL;
	_lastUserName = NULL;
	_lastDomainName = NULL;
	_lastDomainNameChanged = FALSE;
	_pCredProvCredentialEvents = NULL;
	_authManager = NULL;
	_logWriter = NULL;
    _pCredentialProviderEvents = NULL;
	_upCredentialProviderAdviseContext = NULL; 
	
	for(int i = 0; i < MAX_SCREEN_COUNT; i++)
		_pInfoWnd[i] = NULL;
}


/****************************************************************

   Class :  NovaTendCredential

   Method : Destructor
  
*****************************************************************/
NovaTendCredential :: ~NovaTendCredential()
{
	
	int pwdInd = -1;

	if (_authManager)
		pwdInd = _authManager -> GetPasswortTextFieldIndex();

	if ((pwdInd != -1) && (_usrScrCnt))
	{
		size_t lenPassword = lstrlen(_usrScrCnt -> screenObjects[pwdInd] -> strValue);
		SecureZeroMemory(_usrScrCnt -> screenObjects[pwdInd] -> strValue, lenPassword * sizeof(*_usrScrCnt -> screenObjects[pwdInd] -> strValue));
	}	

	DeleteSubWindows();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: destructor");
	#endif

    DllRelease();
}

/****************************************************************

   Class :  NovaTendCredential

   Method : CreateSubWindows
     		
   Return : error code

   Description : Create and show all sub windows
  
*****************************************************************/
HRESULT NovaTendCredential :: CreateSubWindows()
{
	HRESULT hr = S_OK;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: CreateSubWindows");
	#endif

	if (_usrScrCnt)
	{
		for(int i = 0; i < _usrScrCnt -> subWindowCount; i++)
		{
			if (_pInfoWnd[i])
			{
				hr = _pInfoWnd[i] -> Show();

				if (FAILED(hr))
				{
					return hr;
				}
			}
			else
			{
				_pInfoWnd[i] = new InfoWindow();

				if (_pInfoWnd[i])
				{
					hr = _pInfoWnd[i] -> Initialize(_usrScrCnt -> subWindows[i], i + 1, _pInfoWnd);

					if (FAILED(hr))
					{
						delete _pInfoWnd[i];
						_pInfoWnd[i] = NULL;
						return hr;
					}

					_pInfoWnd[i] -> osVersion = OS_UNKNOWN;
					if (_authManager)
						_pInfoWnd[i] -> osVersion = _authManager -> GetOSVersion();
				}
			}
		}
	}

	return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : DeleteSubWindows
     		
   Return : error code

   Description : Delete all sub windows
  
*****************************************************************/
void NovaTendCredential :: DeleteSubWindows()
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: DeleteSubWindows");
	#endif

	if (_usrScrCnt)
	{
		for(int i = 0; i < _usrScrCnt -> subWindowCount; i++)
		{
			if (_pInfoWnd[i] != NULL) 
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: DeleteSubWindows. Hide");
				#endif

				_pInfoWnd[i] -> Hide();
			
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: DeleteSubWindows. Delete");
				#endif

				delete _pInfoWnd[i];
				_pInfoWnd[i] = NULL;
			}
		}
	}
}

/****************************************************************

   Class :  NovaTendCredential

   Method : FindSumbitButtonPosition
     		
   Return : index of filed when will be placed submit button

   Description : Find position for submit button
  
*****************************************************************/
DWORD NovaTendCredential :: FindSumbitButtonPosition()
{
	DWORD posIndex = 0;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: FindSumbitButtonPosition");
	#endif

	if (_usrScrCnt)
	{
		for(int i = 0; i < _usrScrCnt -> screenObjectsCount; i++)
		{
			if ((_usrScrCnt -> screenObjects[i] -> objectTypeID == SOT_TEXT_BOX) ||
				(_usrScrCnt -> screenObjects[i] -> objectTypeID == SOT_COMBOBOX) ||
				(_usrScrCnt -> screenObjects[i] -> objectTypeID == SOT_CHECKBOX) ||
				(_usrScrCnt -> screenObjects[i] -> objectTypeID == SOT_PASSWORD_BOX) ||
				(_usrScrCnt -> screenObjects[i] -> objectTypeID == SOT_USER_NAME_BOX) ||
				(_usrScrCnt -> screenObjects[i] -> objectTypeID == SOT_EDU_ANSWER_BOX) ||
				(_usrScrCnt -> screenObjects[i] -> objectTypeID == SOT_LEGAL_DISCLAIMER_COMBOBOX))
					posIndex = i;
		}
	}
	
	return posIndex;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : GetAuthSystemID
     		
   Return : authentication system ID

   Description : Get authentication system ID
  
*****************************************************************/
int NovaTendCredential :: GetAuthSystemID(void)
{
	// Check depended data
	if ((!_authManager) || (!_lastDomainName))
	{
		_authSystemID = -1;
		return _authSystemID;
	}

	if (_lastDomainNameChanged)
	{
		unsigned char encDomianName[ENCRYPTED_DATA_SIZE];
		int encDomianNameLen;

		if (!(_authManager -> EncryptWCHARString(_lastDomainName, encDomianName, &encDomianNameLen)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetAuthSystemID. Can't encrypt domain name! Done");
			#endif

			return _authSystemID;
		}

		_authSystemID = _authManager -> GetAuthSystemID(encDomianName, encDomianNameLen, AUTH_SYSTEM_TYPE);
		_lastDomainNameChanged = FALSE;
	}

	return _authSystemID;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : Initialize

   Parameters :
			Input : 
				cpus - usage scenario
				crdMng - pointer to credential manager
				userScrCnt - pointer to user screen container
				userListCnt - pointer to list of users
				lastUserName - name of last logged on user
				credentialProviderEvents - pointer to credential
				                           provider events 
										   interface
				credentialProviderAdviseContext - pointer to credential
												  provider advise
												  context
			
	Return : Error code

	Description : Initializes one credential with the field 
	              information passed in.
  
*****************************************************************/
HRESULT NovaTendCredential :: Initialize(__in CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
							__in DWORD dwFlags,
							__in WinAuthenticateManager * authMng,
							__in SafeLogWriter * logWriter, 
							__in BOOL connectionFlag,
						   __in const PUSER_SCREEN_CONTAINER userScrCnt,
						   __in const PUSER_LIST userListCnt,
						   __in WCHAR * lastUserName,
						   __in WCHAR * lastDomainName,
						   __in PUSER_DESCRIPTOR lastUserDescr,
						   __in int authSystemID,
						   __in ICredentialProviderEvents * credentialProviderEvents,
						   __in UINT_PTR credentialProviderAdviseContext)
{
    HRESULT hr = S_OK;

    _cpus = cpus;

	_dwFlags = dwFlags;

	_connectionFlag = connectionFlag;

	_authManager = authMng;

	_logWriter = logWriter;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential : Initialize. Start");
	#endif

	_usrScrCnt = userScrCnt;

	_usrLstCnt = userListCnt;

	_lastUserName = lastUserName;

	_lastDomainName = lastDomainName;
	
	_lastUserDescr = lastUserDescr;

	_authSystemID = authSystemID;

	SetCredentialProviderEvents(credentialProviderEvents, credentialProviderAdviseContext);

	_gScreenRebuilded = TRUE;

	_gSetSelected = FALSE;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential : Initialize. Done");
	#endif
		
    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : SetCredentialProviderEvents

   Parameters :
			Input : 
				credentialProviderEvents - pointer to credential
				                           provider events 
										   interface
				credentialProviderAdviseContext - pointer to credential
												  provider advise
												  context
			
	Return : Error code

	Description : Set values of credential provider events.
  
*****************************************************************/
void NovaTendCredential :: SetCredentialProviderEvents(__in ICredentialProviderEvents * credentialProviderEvents, __in UINT_PTR credentialProviderAdviseContext)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential : SetCredentialProviderEvents");
	#endif

	_pCredentialProviderEvents = credentialProviderEvents;
	_upCredentialProviderAdviseContext = credentialProviderAdviseContext;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : RebuildUserScreen

	Description : Send event "CredentialsChanged" to credential
	              provider. It causes rebuild of user screen.
  
*****************************************************************/
void NovaTendCredential :: RebuildUserScreen()
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential : RebuildUserScreen");
	#endif

	if (_pCredentialProviderEvents != NULL)
    {
		_gScreenRebuilded = TRUE;
		_gSetSelected = FALSE;
		_pCredentialProviderEvents -> CredentialsChanged(_upCredentialProviderAdviseContext);
    }
}

/****************************************************************

   Class :  NovaTendCredential

   Method :  SetSymbolBoxWindowSettings

   Description : Set settings of symbol box password sub window
  
*****************************************************************/
void NovaTendCredential :: SetSymbolBoxWindowSettings()
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: SetSymbolBoxWindowSettings. Start");
	#endif

	int pwdScrInd = -1;
	int pwdInd = -1;
	
	if (_authManager)
	{
		pwdScrInd = _authManager -> GetSymbolBoxPasswordWindowIndex();
		pwdInd = _authManager -> GetPasswortTextFieldIndex();
	}

	if ((pwdScrInd != -1) && (_pInfoWnd[pwdScrInd]) && (pwdInd != -1))
	{
		_pInfoWnd[pwdScrInd] -> pwdIndex = pwdInd;
		_pInfoWnd[pwdScrInd] -> SetCredentialProviderCredential(_pCredProvCredentialEvents, this);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential: SetSymbolBoxWindowSettings. Success");
		#endif
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		else
			WriteToLog("NovaTendCredential: SetSymbolBoxWindowSettings. Fail");
		
		WriteToLog("NovaTendCredential: SetSymbolBoxWindowSettings. Done");
	#endif
}

/****************************************************************

   Class :  NovaTendCredential

   Method :  Advise

   Parameters :
			Input : 
				pcpce - pointer to credential events instance
	
	Return : Error code

	Description : LogonUI calls this in order to give us a 
	              callback in case we need to notify it of anything.
  
*****************************************************************/
HRESULT NovaTendCredential :: Advise(__in ICredentialProviderCredentialEvents * pcpce)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: Advise. Start");
	#endif

	if (_pCredProvCredentialEvents)
    {
		_pCredProvCredentialEvents -> Release();
    }

    _pCredProvCredentialEvents = pcpce;

	_pCredProvCredentialEvents -> AddRef();

	if ((_gScreenRebuilded) && (_lastUserName))
		EnumChildWindows(GetParentWindow(), EnumLogoScreenUIElementsUserNameBoxFunc, (LPARAM)_lastUserName);

	if ((_gSetSelected) && (_lastUserDescr) && ((_lastUserDescr -> pwdType == ONE_SYMBOL_BOX_PWD) || (_lastUserDescr -> pwdType == TWO_SYMBOL_BOX_PWD)))
	{
		EnumChildWindows(GetParentWindow(), EnumLogoScreenUIElementsPasswordBoxFunc, (LPARAM)this);
		SetSymbolBoxWindowSettings();
		_gSetSelected = FALSE;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: Advise. Done");
	#endif

    return S_OK;
}

/****************************************************************

   Class :  NovaTendCredential

   Method :  UnAdvise

	Return : Error code

	Description : LogonUI calls this to tell us to release the callback.
  
*****************************************************************/
HRESULT NovaTendCredential :: UnAdvise()
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: UnAdvise. Start");
	#endif

	if (_pCredProvCredentialEvents)
    {
		_pCredProvCredentialEvents -> Release();
    }
    
	_pCredProvCredentialEvents = NULL;
	
	if ((_lastUserDescr) && ((_lastUserDescr -> pwdType == ONE_SYMBOL_BOX_PWD) || (_lastUserDescr -> pwdType == TWO_SYMBOL_BOX_PWD)))
	{
		SetSymbolBoxWindowSettings();
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: UnAdvise. Done");
	#endif

	return S_OK;
}

/****************************************************************

   Class :  NovaTendCredential

   Method :  GetParentWindow

  	Return : Parent window handle

	Description : provides to get creating window handle
  
*****************************************************************/
HWND NovaTendCredential :: GetParentWindow()
{
	HWND hWnd = NULL;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetParentWindow. Start");
	#endif

	if (_pCredProvCredentialEvents)
	{
		HRESULT hr = _pCredProvCredentialEvents -> OnCreatingWindow(&hWnd);

		if (FAILED(hr)) hWnd = NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		if (hWnd)
			WriteToLog("NovaTendCredential: GetParentWindow. Success");
		else
			WriteToLog("NovaTendCredential: GetParentWindow. Fail");
	
		WriteToLog("NovaTendCredential: GetParentWindow. Done");
	#endif

	return hWnd;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : SetSelected

   Parameters :
			Output : 
				pbAutoLogon - auto logon flag
	
	Return : Error code

	Description : LogonUI calls this function when our tile 
				  is selected (zoomed). If you simply want fields
				  to show/hide based on the selected state, there's
				  no need to do anything here - you can set that up 
				  in the field definitions. But if you want to do
				  something more complicated, like change the contents
				  of a field when the tile is selected, you would do
				  it here.
  
*****************************************************************/
HRESULT NovaTendCredential :: SetSelected(__out BOOL * pbAutoLogon)  
{
    HRESULT hr = S_OK;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: SetSelected. Start");
	#endif
	
	hr = CreateSubWindows();

	if ((SUCCEEDED(hr)) && (_lastUserDescr) && ((_lastUserDescr -> pwdType == ONE_SYMBOL_BOX_PWD) || (_lastUserDescr -> pwdType == TWO_SYMBOL_BOX_PWD)))
	{
		EnumChildWindows(GetParentWindow(), EnumLogoScreenUIElementsPasswordBoxFunc, (LPARAM)this);
		SetSymbolBoxWindowSettings();
	}

	_gSetSelected = TRUE;

	*pbAutoLogon = FALSE;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: SetSelected. Done");
	#endif

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : SetDeselected

	Return : Error code

	Description : Similarly to SetSelected, LogonUI calls this 
				  when your tile was selected and now no longer is.
				  The most common thing to do here (which we do below)
				  is to clear out the password field.
  
*****************************************************************/
HRESULT NovaTendCredential :: SetDeselected()
{
    HRESULT hr = S_OK;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: SetDeselected. Start");
	#endif

	DeleteSubWindows();

	_gSetSelected = FALSE;

	int pwdInd = -1;
	
	if (_authManager)
		pwdInd = _authManager -> GetPasswortTextFieldIndex();

	if ((pwdInd != -1) && (_usrScrCnt))
	{
		size_t lenPassword = lstrlen(_usrScrCnt -> screenObjects[pwdInd] -> strValue);
		SecureZeroMemory(_usrScrCnt -> screenObjects[pwdInd] -> strValue, lenPassword * sizeof(*_usrScrCnt -> screenObjects[pwdInd] -> strValue));
		wcscpy_s(_usrScrCnt -> screenObjects[pwdInd] -> strValue, L"");
		        
		if (_pCredProvCredentialEvents)
		{
			_pCredProvCredentialEvents -> SetFieldString(this, pwdInd, _usrScrCnt -> screenObjects[pwdInd] -> strValue);
		}
	}	

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: SetDeselected. Done");
	#endif

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : GetFieldState

   Parameters :
			Input:
				dwFieldID - field index
			Output : 
				pcpfs - pointer to state structure
				pcpfis - pointer to interactive state structure

	Return : Error code

	Description : Get info for a particular field of a tile. 
				  Called by logonUI to get information to display 
				  the tile.
  
*****************************************************************/
HRESULT NovaTendCredential :: GetFieldState(
    __in DWORD dwFieldID,
    __out CREDENTIAL_PROVIDER_FIELD_STATE* pcpfs,
    __out CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE* pcpfis
    )
{
    HRESULT hr;
    
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetFieldState");
	#endif

    // Validate our parameters.
	if ((_usrScrCnt) && (dwFieldID < (DWORD)_usrScrCnt -> screenObjectsCount) && pcpfs && pcpfis)
    {
		*pcpfs = _usrScrCnt -> screenObjects[dwFieldID] -> fieldState;
		*pcpfis = _usrScrCnt -> screenObjects[dwFieldID] -> fieldInteractiveState;

		hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
    }
    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : GetStringValue

   Parameters :
			Input:
				dwFieldID - field index
			Output : 
				ppwsz - pointer to string

	Return : Error code

	Description : Sets ppwsz to the string value of the field 
				  at the index dwFieldID
  
*****************************************************************/
HRESULT NovaTendCredential :: GetStringValue(
    __in DWORD dwFieldID, 
    __deref_out PWSTR* ppwsz
    )
{
    HRESULT hr;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetStringValue");
	#endif

    // Check to make sure dwFieldID is a legitimate index
	if ((_usrScrCnt) && (dwFieldID < (DWORD)_usrScrCnt -> screenObjectsCount) && ppwsz) 
    {
        // Make a copy of the string and return that. The caller
        // is responsible for freeing it.
		hr = SHStrDupW(_usrScrCnt -> screenObjects[dwFieldID] -> strValue, ppwsz);
	}
	else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : GetBitmapValue

   Parameters :
			Input:
				dwFieldID - field index
			Output : 
				phbmp - pointer to HBITMAP

	Return : Error code

	Description : Get the image to show in the user tile
  
*****************************************************************/
HRESULT NovaTendCredential :: GetBitmapValue(
    __in DWORD dwFieldID, 
    __out HBITMAP* phbmp
    )
{
    HRESULT hr;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetBitmapValue");
	#endif

	if ((_usrScrCnt) && (_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_TILE_IMAGE) && phbmp)
    {
        hr = S_OK;
		*phbmp = LoadBmpImage((char *)_usrScrCnt -> screenObjects[dwFieldID] -> imgValue);
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : GetSubmitButtonValue

   Parameters :
			Input:
				dwFieldID - field index
			Output : 
				pdwAdjacentTo - adjacent to index

	Return : Error code

	Description : Sets pdwAdjacentTo to the index of the field the
				  submit button should be adjacent to. We recommend
				  that the submit button is placed next to the last
				  field which the user is required to enter information 
				  in. Optional fields should be below the submit button.
  
*****************************************************************/
HRESULT NovaTendCredential :: GetSubmitButtonValue(
    __in DWORD dwFieldID,
    __out DWORD* pdwAdjacentTo
    )
{
    HRESULT hr;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetSubmitButtonValue");
	#endif

	if ((_usrScrCnt) && (_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_SUBMIT_BUTTON) && pdwAdjacentTo)
    {
        // pdwAdjacentTo is a pointer to the fieldID you want the submit button to 
        // appear next to.
		*pdwAdjacentTo = FindSumbitButtonPosition();
        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
    }
    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : SetStringValue

   Parameters :
			Input:
				dwFieldID - field index
				pwz  - pointer to string

	Return : Error code

	Description : Sets the value of a field which can accept a string 
				  as a value. This is called on each keystroke when a 
				  user types into an edit field
  
*****************************************************************/
HRESULT NovaTendCredential :: SetStringValue(
    __in DWORD dwFieldID, 
    __in PCWSTR pwz      
    )
{
    HRESULT hr;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: SetStringValue. Start");
	#endif

    // Validate parameters.
	if ((_authManager) && (_usrScrCnt) && (_lastUserName) && (_lastDomainName) && 
		(dwFieldID < (DWORD)_usrScrCnt -> screenObjectsCount) &&
		((_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_EDIT_TEXT) || 
		 (_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_PASSWORD_TEXT)))
    {
		wcscpy_s(_usrScrCnt -> screenObjects[dwFieldID] -> strValue, pwz);

		// If current field is password box
		if ((_usrScrCnt -> screenObjects[dwFieldID] -> objectTypeID == SOT_PASSWORD_BOX) && 
			(_lastUserDescr) && ((_lastUserDescr -> pwdType == ONE_SYMBOL_BOX_PWD) || (_lastUserDescr -> pwdType == TWO_SYMBOL_BOX_PWD)))
		{
			int pwdScrInd = _authManager -> GetSymbolBoxPasswordWindowIndex();
			if ((pwdScrInd != -1) && (_pInfoWnd[pwdScrInd]))
			{
				wcscpy(_pInfoWnd[pwdScrInd] -> currPwdSymbols, _usrScrCnt -> screenObjects[dwFieldID] -> strValue);
			}
		}

		// If current field is user name box
		if (_usrScrCnt -> screenObjects[dwFieldID] -> objectTypeID == SOT_USER_NAME_BOX)
		{
			WCHAR  pwszUsername[NAME_LEN] = L"";
			WCHAR  pwszDomain[NAME_LEN] = L"";
			DomainUsernameStringSplit(_usrScrCnt -> screenObjects[dwFieldID] -> strValue, pwszDomain, pwszUsername);
			
			// Check domain name
			if ((wcscmp(pwszDomain, _lastDomainName)) && (wcscmp(pwszDomain, L"")))
			{
				wcscpy_s(_lastDomainName, NAME_LEN, pwszDomain);
				_lastDomainNameChanged = TRUE;
			}
						
			// Is it a new user?
			if (!(_authManager -> StringsAreEqual(_lastUserName, pwszUsername)))
			{
				// Copy user name
				wcscpy_s(_lastUserName, NAME_LEN, pwszUsername);

				// Find current new user
				char lstUsrName[NAME_LEN];
				wcstombs(lstUsrName, _lastUserName, NAME_LEN);
				int userID = _authManager -> FindUser(lstUsrName);

				// Rebuild screen flag
				BOOL rebuildScreen = TRUE;

				// Is it unknown user?
				if (userID == -1)
				{
					if (_lastUserDescr)
					{
						// Delete sub windows
						DeleteSubWindows();

						// Remove current user descriptor
						_lastUserDescr = _authManager -> DeleteUserDescriptor();

						// Get user screen container
						if (_connectionFlag)
							_usrScrCnt = _authManager -> GetUserScreenContainer(_cpus, GetAuthSystemID());
						else
							_usrScrCnt = _authManager -> GetUserLocalScreenContainer();
					}
					else
						rebuildScreen = FALSE;
				}
				else
				{
					// Delete sub windows
					DeleteSubWindows();

					// Get user screen container new user
					if (_connectionFlag)
					{
						_lastUserDescr = _authManager -> GetUserDescriptor(userID);
						_usrScrCnt = _authManager -> GetUserScreenContainer(_cpus, GetAuthSystemID());
					}
					else
					{
						_lastUserDescr = _authManager -> GetLocalUserDescriptor(userID);
						_usrScrCnt = _authManager -> GetUserLocalScreenContainer();
					}
				}

				// Validate creation result
				if ((_usrScrCnt) && (rebuildScreen))
				{
					// Create domain names list
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
						WriteToLog("NovaTendCredential: SetStringValue. Create domain names list!");
					#endif

					_authManager -> EnumDomainNames(_lastDomainName);

					// Put user name to user name box
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
						WriteToLog("NovaTendCredential: SetStringValue. Put last user name to field");
					#endif

					if (!wcscmp(pwszDomain, L""))
					{
						_authManager -> SetUserNameFieldValue(_lastUserName);
					}
					else
					{
						WCHAR pwszDomainUsername[NAME_LEN];
						DomainUsernameStringConcat(_lastDomainName, _lastUserName, pwszDomainUsername);
						_authManager -> SetUserNameFieldValue(pwszDomainUsername);
					}
					
					// Rebuild screen
					RebuildUserScreen();
				}
				else 
					return E_OUTOFMEMORY;
			}
		}

		hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
    }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: SetStringValue. Done");
	#endif

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : GetCheckboxValue

   Parameters :
			Input:
				dwFieldID - field index
				pbChecked  - checking flag
			Output:
				ppwszLabel - checkbox label

	Return : Error code

	Description : Returns whether a checkbox is checked or
	              not as well as its label.
  
*****************************************************************/
HRESULT NovaTendCredential :: GetCheckboxValue(
    __in DWORD dwFieldID, 
    __in BOOL* pbChecked,
    __deref_out PWSTR* ppwszLabel
    )
{
    HRESULT hr;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetCheckboxValue");
	#endif

    // Validate parameters.
	if ((_usrScrCnt) && (dwFieldID < (DWORD)_usrScrCnt -> screenObjectsCount) && 
		(_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_CHECKBOX))
	 {
		 *pbChecked = _usrScrCnt -> screenObjects[dwFieldID] -> chbChecked;
		 hr = SHStrDupW(_usrScrCnt -> screenObjects[dwFieldID] -> strValue, ppwszLabel);
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : SetCheckboxValue

   Parameters :
			Input:
				dwFieldID - field index
				pbChecked  - checking flag
			
	Return : Error code

	Description : Sets whether the specified checkbox is checked or not.
  
*****************************************************************/
HRESULT NovaTendCredential :: SetCheckboxValue(
    __in DWORD dwFieldID, 
    __in BOOL bChecked
    )
{
    HRESULT hr;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: SetCheckboxValue");
	#endif

    // Validate parameters.
	if ((_usrScrCnt) && (dwFieldID < (DWORD)_usrScrCnt -> screenObjectsCount) && 
		(_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_CHECKBOX))
    {
        _usrScrCnt -> screenObjects[dwFieldID] -> chbChecked = bChecked;

		if (bChecked)
			wcscpy_s(_usrScrCnt -> screenObjects[dwFieldID] -> strValue, L"TRUE");
		else
			wcscpy_s(_usrScrCnt -> screenObjects[dwFieldID] -> strValue, L"FALSE");

        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : GetComboBoxValueCount

   Parameters :
			Input:
				dwFieldID - field index
			Output:
				pcItems - items count
				pdwSelectedItem - selected item index
			
	Return : Error code

	Description : Returns the number of items to be included 
				  in the combobox (pcItems), as well as the
				  currently selected item (pdwSelectedItem).
  
*****************************************************************/
HRESULT NovaTendCredential :: GetComboBoxValueCount(
    __in DWORD dwFieldID, 
    __out DWORD* pcItems, 
    __out_range(<,*pcItems) DWORD* pdwSelectedItem
    )
{
    HRESULT hr;
	 
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetComboBoxValueCount");
	#endif

    // Validate parameters.
	if ((_usrScrCnt) && (dwFieldID < (DWORD)_usrScrCnt -> screenObjectsCount) && 
		(_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_COMBOBOX))
    {
		*pcItems = _usrScrCnt -> screenObjects[dwFieldID] -> comboBoxValuesCount;
        *pdwSelectedItem = 0;
        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return S_OK;
}
 
/****************************************************************

   Class :  NovaTendCredential

   Method : GetComboBoxValueAt

   Parameters :
			Input:
				dwFieldID - field index
				dwItem - comobox item index
			Output:
				ppwszItem - comobox item value
			
	Return : Error code

	Description : Called iteratively to fill the combobox with the 
				 string (ppwszItem) at index dwItem.
  
*****************************************************************/
HRESULT NovaTendCredential :: GetComboBoxValueAt(
    __in DWORD dwFieldID, 
    __in DWORD dwItem,
    __deref_out PWSTR* ppwszItem
    )
{
    HRESULT hr;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetComboBoxValueAt");
	#endif

    // Validate parameters.
	if ((_usrScrCnt) && (dwFieldID < (DWORD)_usrScrCnt -> screenObjectsCount) && 
		(_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_COMBOBOX))
    {
		hr = SHStrDupW(_usrScrCnt -> screenObjects[dwFieldID] -> comboBoxValues[dwItem], ppwszItem);
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : SetComboBoxSelectedValue

   Parameters :
			Input:
				dwFieldID - field index
				dwSelectedItem - comobox item index
			
	Return : Error code

	Description : Called when the user changes the selected 
				  item in the combobox.
  
*****************************************************************/
HRESULT NovaTendCredential :: SetComboBoxSelectedValue(
    __in DWORD dwFieldID,
    __in DWORD dwSelectedItem
    )
{
    HRESULT hr;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: SetComboBoxSelectedValue");
	#endif

    // Validate parameters.
	if ((_usrScrCnt) && (dwFieldID < (DWORD)_usrScrCnt -> screenObjectsCount) && 
		(_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_COMBOBOX))
    {
		if(dwSelectedItem < (DWORD)_usrScrCnt -> screenObjects[dwFieldID] -> comboBoxValuesCount)
		{
			_usrScrCnt -> screenObjects[dwFieldID] -> comboBoxIndex = dwSelectedItem;
			wcscpy_s(_usrScrCnt -> screenObjects[dwFieldID] -> strValue, _usrScrCnt -> screenObjects[dwFieldID] -> comboBoxValues[_usrScrCnt -> screenObjects[dwFieldID] -> comboBoxIndex]);

			if (_usrScrCnt -> screenObjects[dwFieldID] -> objectTypeID == SOT_DOMAIN_NAME_BOX)
			{
				if (wcscmp(_usrScrCnt -> screenObjects[dwFieldID] -> strValue, _lastDomainName))
				{
					wcscpy(_lastDomainName, _usrScrCnt -> screenObjects[dwFieldID] -> strValue);
					_lastDomainNameChanged = TRUE;
				}
			}
		}

        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : CommandLinkClicked

   Parameters :
			Input:
				dwFieldID - field index
	
	Return : Error code

	Description : Called when the user clicks a command link.
  
*****************************************************************/
HRESULT NovaTendCredential :: CommandLinkClicked(__in DWORD dwFieldID)
{
    HRESULT hr;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: CommandLinkClicked");
	#endif

    // Validate parameter.
	if ((_authManager) && (_usrScrCnt) && (dwFieldID < (DWORD)_usrScrCnt -> screenObjectsCount) && 
		(_usrScrCnt -> screenObjects[dwFieldID] -> fieldDescriptor.cpft == CPFT_COMMAND_LINK))
    {
		// Password reset
		if (_usrScrCnt -> screenObjects[dwFieldID] -> objectTypeID == SOT_PASSWORD_RESET_BUTTON)
		{
			int resetResult = RESPONSE_BAD;
			HWND hWndOwner = GetParentWindow();

			if(_lastUserDescr)
			{
				 if (_connectionFlag)
				 {
					 resetResult = _authManager -> ResetUserCustomPassword(_lastUserDescr -> userID);

					 switch(resetResult)
					 {
						case RESPONSE_OK :
							{
								_lastUserDescr = _authManager -> GetUserDescriptor(_lastUserDescr -> userID);

								MessageBox(hWndOwner, L"Password successfully reseted! Please follow the instructions that were sent to you by email (SMS).", L"Information", MB_ICONINFORMATION | MB_SYSTEMMODAL | MB_OK);
								break;
							}

						case RESPONSE_BAD :
							{
								MessageBox(hWndOwner, L"Password reset general error! Please try again later.", L"Error", MB_ICONERROR | MB_SYSTEMMODAL | MB_OK);
								break;
							}

						case RESET_PWD_USER_NOT_FOUND :
							{
								MessageBox(hWndOwner, L"Wrong user ID! The system cannot find user with that user ID.", L"Error", MB_ICONERROR | MB_SYSTEMMODAL | MB_OK);
								break;
							}

						case RESET_PWD_WRONG_EMAIL_ADDRESS :
							{
								MessageBox(hWndOwner, L"Email sending error! The system can't send password reset instructions to your email box. Your email address is wrong.", L"Error", MB_ICONERROR | MB_SYSTEMMODAL | MB_OK);
								break;
							}

						case RESET_PWD_WRONG_PHONE_NUMBER :
							{
								MessageBox(hWndOwner, L"SMS sending error! The system can't send password reset instructions to your phone. Your phone number is wrong.", L"Error", MB_ICONERROR | MB_SYSTEMMODAL | MB_OK);
								break;
							}
						case RESET_PWD_EMAIL_SEND_ERROR :
							{
								MessageBox(hWndOwner, L"Email sending error! The system can't send password reset instructions to your email box.", L"Error", MB_ICONERROR | MB_SYSTEMMODAL | MB_OK);
								break;
							}

						case RESET_PWD_SMS_SEND_ERROR :
							{
								MessageBox(hWndOwner, L"SMS sending error! The system can't send password reset instructions to your phone.", L"Error", MB_ICONERROR | MB_SYSTEMMODAL | MB_OK);
								break;
							}
						
						default:
							{
								MessageBox(hWndOwner, L"Unknown password reset result! Please try again later.", L"Error", MB_ICONERROR | MB_SYSTEMMODAL | MB_OK);
								break;
							}
					 }
				 }
				 else
					 MessageBox(hWndOwner, L"Server is not available now! Please try again later.", L"Error", MB_ICONERROR | MB_SYSTEMMODAL | MB_OK);
			 }
			 else
				 MessageBox(hWndOwner, L"Unkown user name!", L"Error", MB_ICONERROR | MB_SYSTEMMODAL | MB_OK);

		}

        hr = S_OK;
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

/****************************************************************

   Class :  NovaTendCredential

   Method : GetSerialization

   Parameters :
			Input:
				pcpsiOptionalStatusIcon - status icon
			Output:
				pcpgsr - response serialization buffer
				pcpcs - serialization buffer
				ppwszOptionalStatusText - status text
	
	Return : Error code

	Description : Collect the username and password into a 
				  serialized credential for the correct usage scenario
				  (logon/unlock is what's demonstrated in this sample).
				  LogonUI then passes these credentials 
				  back to the system to log on.
  
*****************************************************************/
HRESULT NovaTendCredential :: GetSerialization(
    __out CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE* pcpgsr,
    __out CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcs, 
    __deref_out_opt PWSTR* ppwszOptionalStatusText, 
    __in CREDENTIAL_PROVIDER_STATUS_ICON* pcpsiOptionalStatusIcon
    )
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetSerialization. Start");
	#endif

    HRESULT hr;

	DeleteSubWindows();

	// Check current authentication system
	_authSystemID = GetAuthSystemID();
			
	// Get indexes of user name / password / domain name boxes
	int pwdInd = -1;
	int usrNameInd = -1;
	int dmnInd = -1;

	if ((_authManager) && (_usrScrCnt))
	{
		pwdInd = _authManager -> GetPasswortTextFieldIndex();
		usrNameInd = _authManager -> GetLoginTextFieldIndex();
		dmnInd = _authManager -> GetDomainTextFieldIndex();
	}

	// Check user name and password boxes
	if ((pwdInd == -1) || (usrNameInd == -1))
	{
		*pcpgsr = CPGSR_NO_CREDENTIAL_FINISHED;
		pcpcs -> clsidCredentialProvider = CLSID_NovaTend;
		pcpcs -> ulAuthenticationPackage = NULL;

		hr = SHStrDupW(L"Credential provider crashed!", ppwszOptionalStatusText);

		if (FAILED(hr))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. Credential provider crashed. Can't prepare error massage!");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return hr;
		}

		*pcpsiOptionalStatusIcon = CPSI_ERROR;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential: GetSerialization. Credential provider crashed");
			WriteToLog("NovaTendCredential: GetSerialization. Done");
		#endif

		return ERROR_NOT_AUTHENTICATED;
	}

	// Get domain name
	WCHAR wszDomain[STR_VALUE_LEN];
	DWORD cch = ARRAYSIZE(wszDomain);

	if (dmnInd == -1)
	{
		// If domain box not found, then set computer name as domain name
		if (!GetComputerNameW(wszDomain, &cch))
		{
			DWORD dwErr = GetLastError();
			hr = HRESULT_FROM_WIN32(dwErr);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. Bad domain name");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return hr;
		}
	}
	else 
	{
		// Get domain name
		wcscpy_s(wszDomain, _usrScrCnt -> screenObjects[dmnInd] -> strValue);
	}

	// Check legal disclaimer confirmation
	if ((_connectionFlag) && (_lastUserDescr))
	{
		if (_authManager -> ConfirmLegalDisclaimer(_lastUserDescr -> userID) != RESPONSE_OK)
		{
			*pcpgsr = CPGSR_NO_CREDENTIAL_FINISHED;
			pcpcs -> clsidCredentialProvider = CLSID_NovaTend;
			pcpcs -> ulAuthenticationPackage = NULL;

			hr = SHStrDupW(L"You can use the system only if you agree with the legal disclaimer!", ppwszOptionalStatusText);

			if (FAILED(hr))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. User disagree with legal discalimer! Can't prepare error massage!");
					WriteToLog("NovaTendCredential: GetSerialization. Done");
				#endif

				return hr;
			}

			*pcpsiOptionalStatusIcon = CPSI_ERROR;
		
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. User disagree with legal discalimer!");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return ERROR_NOT_AUTHENTICATED;

		}
	}

	// Check user locked flag
	if ((_lastUserDescr) && (_lastUserDescr -> locked))
	{
		*pcpgsr = CPGSR_NO_CREDENTIAL_FINISHED;
		pcpcs -> clsidCredentialProvider = CLSID_NovaTend;
		pcpcs -> ulAuthenticationPackage = NULL;

		hr = SHStrDupW(L"User account is locked!", ppwszOptionalStatusText);
		
		if (FAILED(hr))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. User account is locked!");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return hr;
		}

		*pcpsiOptionalStatusIcon = CPSI_ERROR;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential: GetSerialization. User account is locked!");
			WriteToLog("NovaTendCredential: GetSerialization. Done");
		#endif

		return ERROR_NOT_AUTHENTICATED;
	}

	// Check count of password attempts for current user
	if ((_lastUserDescr) && (_lastUserDescr -> pwdAttemptsCount >= _lastUserDescr -> maxPwdAttemptsCount))
	{
		*pcpgsr = CPGSR_NO_CREDENTIAL_FINISHED;
		pcpcs -> clsidCredentialProvider = CLSID_NovaTend;
		pcpcs -> ulAuthenticationPackage = NULL;

		hr = SHStrDupW(L"Exceeded count of password attempts for this user!", ppwszOptionalStatusText);
		
		if (FAILED(hr))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. Exceeded count of password attempts for this user! Can't prepare error massage!");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return hr;
		}

		*pcpsiOptionalStatusIcon = CPSI_ERROR;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential: GetSerialization. Exceeded count of password attempts for this user!");
			WriteToLog("NovaTendCredential: GetSerialization. Done");
		#endif

		return ERROR_NOT_AUTHENTICATED;
	}
	
	
	PWSTR pwzPassword;
	BOOL passThruPwd = FALSE;
	PWSTR pwzUserName;
	BOOL passThruUserName = FALSE;

	// Prepare user security data structure
	USER_SECURITY_DATA securityData;
	securityData.authSystemID = -1;
	securityData.encSystemPasswordLen = 0;
	securityData.encSystemPassword[0] = 0;
	securityData.encSystemUserNameLen = 0;
	securityData.encSystemUserName[0] = 0;
	securityData.lastLogOnDate[0] = 0;
	securityData.passThru = true;
	securityData.pwdConstRulesCount = 0;
	securityData.tmpPwdConstRulesCount = 0;
	securityData.pwdType = 0;
	securityData.userToken = 0;
	securityData.tmpUserToken = 0;
	securityData.userID = -1;

	// Check of user custom constructed password
	if (_lastUserDescr)
	{
		tm * timeinfo = NULL;

		if (_usrScrCnt)
		{
			// Get screen time
			for(int i = 0; i < _usrScrCnt -> screenObjectsCount; i++)
				if (_usrScrCnt -> screenObjects[i] -> objectTypeID == SOT_DATE_TIME_TEXT)
				{
					timeinfo = _usrScrCnt -> screenObjects[i] -> timeinfo;
					break;
				}
		}

		unsigned char encPwd[ENCRYPTED_DATA_SIZE];
		int encPwdLen;

		int validationResult = RESPONSE_BAD;

		// Encrypt entered password
		if (_authManager -> EncryptWCHARString(_usrScrCnt -> screenObjects[pwdInd] -> strValue, encPwd, &encPwdLen))
		{		
			if (_connectionFlag)
			{
				// Validate password on server
				validationResult = _authManager -> ValidateUserCustomPassword(_lastUserDescr -> userID, _authSystemID, encPwd, encPwdLen, timeinfo, _authManager -> GetSymbolBoxesListPointer(), &securityData);
			}
			else
			{
				// Validate local user password
				char tmpPwd[STR_VALUE_LEN];
				wcstombs(tmpPwd, _usrScrCnt -> screenObjects[pwdInd] -> strValue, STR_VALUE_LEN);
				validationResult = _authManager -> ValidateLocalUserCustomPassword(_lastUserDescr, tmpPwd, timeinfo, &securityData);
			}
		}

		// Check validation result
		if (validationResult != RESPONSE_OK)
		{
			*pcpgsr = CPGSR_NO_CREDENTIAL_FINISHED;
			pcpcs -> clsidCredentialProvider = CLSID_NovaTend;
			pcpcs -> ulAuthenticationPackage = NULL;

			if (validationResult == RESPONSE_PWD_EXPIRED)
				hr = SHStrDupW(L"Your password expired and must be changed!", ppwszOptionalStatusText);
			else
			if (validationResult == RESPONSE_ACCOUNT_LOCKED)
				hr = SHStrDupW(L"Your account locked!", ppwszOptionalStatusText);
			else
				hr = SHStrDupW(L"Wrong user name or password!", ppwszOptionalStatusText);

			if (FAILED(hr))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. Wrong user name or password! Credential provider crashed. Can't prepare error massage!");
					WriteToLog("NovaTendCredential: GetSerialization. Done");
				#endif

				return hr;
			}

			*pcpsiOptionalStatusIcon = CPSI_ERROR;
		
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. Wrong user name or password!");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return ERROR_NOT_AUTHENTICATED;
		}
		else
		{
			if (securityData.passThru)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. Password passed through!");
				#endif

				// Get password string from password box
				hr = SHStrDupW(_usrScrCnt -> screenObjects[pwdInd] -> strValue, &pwzPassword);	
				passThruPwd = TRUE;
			}
			else
			{
				// Get system password
				WCHAR pwdBuffer[STR_VALUE_LEN];
				_authManager -> DecryptWCHARString(pwdBuffer, securityData.encSystemPassword, securityData.encSystemPasswordLen);
				hr = SHStrDupW(pwdBuffer, &pwzPassword);	
				SecureZeroMemory(pwdBuffer, STR_VALUE_LEN * sizeof(WCHAR));
			}

			if (FAILED(hr))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. Can't allocate memmory for password string");
					WriteToLog("NovaTendCredential: GetSerialization. Done");
				#endif

				return hr;
			}

			if(securityData.encSystemUserNameLen > 0)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. Uses system user name from security data structure!");
				#endif

				WCHAR usrBuffer[STR_VALUE_LEN];
				_authManager -> DecryptWCHARString(usrBuffer, securityData.encSystemUserName, securityData.encSystemUserNameLen);
				hr = SHStrDupW(usrBuffer, &pwzUserName);
				SecureZeroMemory(usrBuffer, STR_VALUE_LEN * sizeof(WCHAR));
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. Pass thru user name!");
				#endif

				// Get user name form user name box
				hr = SHStrDupW(_usrScrCnt -> screenObjects[usrNameInd] -> strValue, &pwzUserName);	

				passThruUserName = TRUE;
			}

			if (FAILED(hr))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. Can't allocate memmory for user name string");
					WriteToLog("NovaTendCredential: GetSerialization. Done");
				#endif

				return hr;
			}

			if(_connectionFlag)
			{
				// Save local copy of security data
				_authManager -> SaveLocalUserSecurityData(&securityData);
			}
		}

		SecureZeroMemory(&securityData, sizeof(USER_SECURITY_DATA));
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential: GetSerialization. Unknown user!");
			WriteToLog("NovaTendCredential: GetSerialization. Password and user name will pass thru!");
		#endif

		// Get password string from password box
		hr = SHStrDupW(_usrScrCnt -> screenObjects[pwdInd] -> strValue, &pwzPassword);	
		passThruPwd = TRUE;

		if (FAILED(hr))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. Can't allocate memmory for password string");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return hr;
		}

		// Get user name form user name box
		hr = SHStrDupW(_usrScrCnt -> screenObjects[usrNameInd] -> strValue, &pwzUserName);	
		passThruUserName = TRUE;

		if (FAILED(hr))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. Can't allocate memmory for user name string");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return hr;
		}
	}

	// Validate other entered parameters
	if ((_connectionFlag) && (_lastUserDescr))
	{
		if (_authManager -> ValidateParams() != RESPONSE_OK)
		{
			*pcpgsr = CPGSR_NO_CREDENTIAL_FINISHED;
			pcpcs -> clsidCredentialProvider = CLSID_NovaTend;
			pcpcs -> ulAuthenticationPackage = NULL;

			hr = SHStrDupW(L"Invalid credential parameters!", ppwszOptionalStatusText);

			if (FAILED(hr))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. Invalid credentials! Credential provider crashed. Can't prepare error massage!");
					WriteToLog("NovaTendCredential: GetSerialization. Done");
				#endif

				return hr;
			}

			*pcpsiOptionalStatusIcon = CPSI_ERROR;
		
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. Invalid credentials!");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return ERROR_NOT_AUTHENTICATED;
		}
	}

	// Validate user answers
	if ((_connectionFlag) && (_lastUserDescr) && (_lastUserDescr -> needStudy))
	{
		if (_authManager -> ValidateAnswers() != RESPONSE_OK)
		{
			*pcpgsr = CPGSR_NO_CREDENTIAL_FINISHED;
			pcpcs -> clsidCredentialProvider = CLSID_NovaTend;
			pcpcs -> ulAuthenticationPackage = NULL;

			hr = SHStrDupW(L"Wrong answer!", ppwszOptionalStatusText);

			if (FAILED(hr))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. Wrong answer! Credential provider crashed. Can't prepare error massage!");
					WriteToLog("NovaTendCredential: GetSerialization. Done");
				#endif

				return hr;
			}

			*pcpsiOptionalStatusIcon = CPSI_ERROR;
		
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. Wrong answer!");
				WriteToLog("NovaTendCredential: GetSerialization. Done");
			#endif

			return ERROR_NOT_AUTHENTICATED;
		}
	}

	if (SUCCEEDED(hr))
	{
		if ((_connectionFlag) && (passThruPwd) && (passThruUserName))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendCredential: GetSerialization. User name and password passed thru!");
			#endif

			unsigned char encUserName[ENCRYPTED_DATA_SIZE];
			int encUserNameLen;

			unsigned char encPassword[ENCRYPTED_DATA_SIZE];
			int encPasswordLen;

			// Encrypt entered user name and password
			if (_authManager -> EncryptWCHARString(pwzUserName, encUserName, &encUserNameLen) &&
				_authManager -> EncryptWCHARString(pwzPassword, encPassword, &encPasswordLen))
			{
				if (_authManager -> ValidateUserAccount(encUserName, encUserNameLen, encPassword, encPasswordLen, _authSystemID) == RESPONSE_OK)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
						WriteToLog("NovaTendCredential: GetSerialization. User account validated and synchronized!");
					#endif
							  				
					if (_lastUserDescr)
					{
						USER_SECURITY_DATA securityData;
						securityData.userID = _lastUserDescr -> userID;
						securityData.authSystemID = _authSystemID;
						securityData.encSystemUserNameLen = encUserNameLen;
						memcpy(securityData.encSystemUserName, encUserName, encUserNameLen);
						securityData.encSystemPasswordLen = encPasswordLen;
						memcpy(securityData.encSystemPassword, encPassword, encPasswordLen);
						securityData.lastLogOnDate[0] = 0;
						securityData.passThru = true;
						securityData.pwdConstRulesCount = 0;
						securityData.tmpPwdConstRulesCount = 0;
						securityData.pwdType = 1;
						securityData.userToken = 0;
						securityData.tmpUserToken = 0;

						_authManager -> SaveLocalUserSecurityData(&securityData);

						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
							WriteToLog("NovaTendCredential: GetSerialization. User name and password copied to the user descriptor!");
						#endif
					}
				}
				else
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
						WriteToLog("NovaTendCredential: GetSerialization. User account not validated and synchronized!");
					#endif
				}
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendCredential: GetSerialization. Error of encryption of user name and password!");
				#endif
			}
		}

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		//wszDomain[0] = 0;
		//SHStrDupW(L"admin", &pwzUserName);
		//SHStrDupW(L"admin", &pwzPassword);
				
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		

		PWSTR pwzProtectedPassword;

		// Create protected password
		hr = ProtectIfNecessaryAndCopyPassword(pwzPassword, _cpus, &pwzProtectedPassword);
		
		DWORD cb = 0;
		BYTE * rgb = NULL;

		// Only CredUI scenarios should use CredPackAuthenticationBuffer.  Custom packing logic is necessary for
		// logon and unlock scenarios in order to specify the correct MessageType.
		if (CPUS_CREDUI == _cpus)
		{
			if (SUCCEEDED(hr))
			{
				PWSTR pwzDomainUsername = NULL;
				hr = DomainUsernameStringAlloc(wszDomain, pwzUserName, &pwzDomainUsername);

				if (SUCCEEDED(hr))
				{
					if (!CredPackAuthenticationBufferW((CREDUIWIN_PACK_32_WOW & _dwFlags) ? CRED_PACK_WOW_BUFFER : 0, pwzDomainUsername, pwzProtectedPassword, rgb, &cb))
					{
						if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
						{
							rgb = (BYTE *)HeapAlloc(GetProcessHeap(), 0, cb);
							if (rgb)
							{
								// If the CREDUIWIN_PACK_32_WOW flag is set we need to return 32 bit buffers to our caller we do this by 
								// passing CRED_PACK_WOW_BUFFER to CredPacAuthenticationBufferW.
								if (!CredPackAuthenticationBufferW((CREDUIWIN_PACK_32_WOW & _dwFlags) ? CRED_PACK_WOW_BUFFER : 0, pwzDomainUsername, pwzProtectedPassword, rgb, &cb))
								{
									HeapFree(GetProcessHeap(), 0, rgb);
									hr = HRESULT_FROM_WIN32(GetLastError());
								}
								else
								{
									hr = S_OK;
								}
							}
							else
							{
								hr = E_OUTOFMEMORY;
							}
						}
						else
						{
							hr = E_FAIL;
						}

						HeapFree(GetProcessHeap(), 0, pwzDomainUsername);
					}
					else
					{
						hr = E_FAIL;
					}
				}
			}
		}
		else
		{

			KERB_INTERACTIVE_UNLOCK_LOGON kiul;

			// Initialize kiul with weak references to our credential.
			hr = KerbInteractiveUnlockLogonInit(wszDomain, pwzUserName, pwzProtectedPassword, _cpus, &kiul);

			if (SUCCEEDED(hr))
			{
				// We use KERB_INTERACTIVE_UNLOCK_LOGON in both unlock and logon scenarios.  It contains a
				// KERB_INTERACTIVE_LOGON to hold the creds plus a LUID that is filled in for us by Winlogon
				// as necessary.
				hr = KerbInteractiveUnlockLogonPack(kiul, &pcpcs -> rgbSerialization, &pcpcs -> cbSerialization);
			}
		}

		if (SUCCEEDED(hr))
		{
			ULONG ulAuthPackage;
			hr = RetrieveNegotiateAuthPackage(&ulAuthPackage);

			if (SUCCEEDED(hr))
			{
				pcpcs -> ulAuthenticationPackage = ulAuthPackage;
				pcpcs -> clsidCredentialProvider = CLSID_NovaTend;

				// In CredUI scenarios, we must pass back the buffer constructed with CredPackAuthenticationBuffer.
				if (_cpus == CPUS_CREDUI)
				{
					pcpcs -> rgbSerialization = rgb;
					pcpcs -> cbSerialization = cb;
				}

				// At this point the credential has created the serialized credential used for logon
				// By setting this to CPGSR_RETURN_CREDENTIAL_FINISHED we are letting logonUI know
				// that we have all the information we need and it should attempt to submit the 
				// serialized credential.
				*pcpgsr = CPGSR_RETURN_CREDENTIAL_FINISHED;
			}
			else
			{
				HeapFree(GetProcessHeap(), 0, rgb);
			}
		}
		
		//if (SUCCEEDED(hr))
		//{
		//	KERB_INTERACTIVE_UNLOCK_LOGON kiul;

		//	hr = KerbInteractiveUnlockLogonInit(wszDomain, pwzUserName, pwzProtectedPassword, _cpus, &kiul);

		//	if (SUCCEEDED(hr))
		//	{
		//		// We use KERB_INTERACTIVE_UNLOCK_LOGON in both unlock and logon scenarios.  It contains a
		//		// KERB_INTERACTIVE_LOGON to hold the creds plus a LUID that is filled in for us by Winlogon
		//		// as necessary.
		//		hr = KerbInteractiveUnlockLogonPack(kiul, &pcpcs -> rgbSerialization, &pcpcs -> cbSerialization);

		//		if (SUCCEEDED(hr))
		//		{
		//			ULONG ulAuthPackage;
		//			hr = RetrieveNegotiateAuthPackage(&ulAuthPackage);

		//			if (SUCCEEDED(hr))
		//			{
		//				pcpcs->ulAuthenticationPackage = ulAuthPackage;
		//				pcpcs->clsidCredentialProvider = CLSID_NovaTend;

		//				// At this point the credential has created the serialized credential used for logon
		//				// By setting this to CPGSR_RETURN_CREDENTIAL_FINISHED we are letting logonUI know
		//				// that we have all the information we need and it should attempt to submit the 
		//				// serialized credential.
		//				*pcpgsr = CPGSR_RETURN_CREDENTIAL_FINISHED;
		//			}
		//		}
		//	}
		//}


		CoTaskMemFree(pwzProtectedPassword);
		CoTaskMemFree(pwzPassword);
		CoTaskMemFree(pwzUserName);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential: GetSerialization. Done");
	#endif

    return hr;
}


// Report status information structure.
// It using by ReportResult
struct REPORT_RESULT_STATUS_INFO
{
    NTSTATUS ntsStatus;
    NTSTATUS ntsSubstatus;
    PWSTR     pwzMessage;
    CREDENTIAL_PROVIDER_STATUS_ICON cpsi;
};

// Report status information structure array.
// It using by ReportResult
static const REPORT_RESULT_STATUS_INFO s_rgLogonStatusInfo[] =
{
    { STATUS_LOGON_FAILURE, STATUS_SUCCESS, L"Incorrect user name or password!", CPSI_ERROR, },
    { STATUS_ACCOUNT_RESTRICTION, STATUS_ACCOUNT_DISABLED, L"The account is disabled.", CPSI_WARNING },
};


/****************************************************************

   Class :  NovaTendCredential

   Method : ReportResult

   Parameters :
			Input:
				ntsStatus - NT status
				ntsSubstatus - NT sub status

			Output:
				ppwszOptionalStatusText - status text
				pcpsiOptionalStatusIcon - status icon
	
	Return : Error code

	Description : ReportResult is completely optional. Its purpose
				  is to allow a credential to customize the string
				  and the icon displayed in the case of a logon failure.
				  For example, we have chosen to customize the error shown
				  in the case of bad username/password and in the case of 
				  the account being disabled.
  
*****************************************************************/
HRESULT NovaTendCredential :: ReportResult(
    __in NTSTATUS ntsStatus, 
    __in NTSTATUS ntsSubstatus,
    __deref_out_opt PWSTR* ppwszOptionalStatusText, 
    __out CREDENTIAL_PROVIDER_STATUS_ICON* pcpsiOptionalStatusIcon
    )
{
    *ppwszOptionalStatusText = NULL;
    *pcpsiOptionalStatusIcon = CPSI_NONE;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential:  ReportResult. Start");
	#endif

    DWORD dwStatusInfo = (DWORD)-1;

    // Look for a match on status and substatus.
    for (DWORD i = 0; i < ARRAYSIZE(s_rgLogonStatusInfo); i++)
    {
        if (s_rgLogonStatusInfo[i].ntsStatus == ntsStatus && s_rgLogonStatusInfo[i].ntsSubstatus == ntsSubstatus)
        {
            dwStatusInfo = i;
            break;
        }
    }

    if ((DWORD)-1 != dwStatusInfo)
    {
        if (SUCCEEDED(SHStrDupW(s_rgLogonStatusInfo[dwStatusInfo].pwzMessage, ppwszOptionalStatusText)))
        {
            *pcpsiOptionalStatusIcon = s_rgLogonStatusInfo[dwStatusInfo].cpsi;
        }
    }

	if ((SUCCEEDED(HRESULT_FROM_NT(ntsStatus))) && (_cpus == CPUS_LOGON) && (_authManager) && (_connectionFlag))
	{
		if (_lastUserDescr)
			_authManager -> SaveLoggedUserData(_lastUserDescr -> userID, _authSystemID);

		_authManager -> SetAutoStartPostLogin();
	}

	if ((SUCCEEDED(HRESULT_FROM_NT(ntsStatus))) && (_cpus == CPUS_LOGON) && (_lastUserDescr) && (_authManager) && (_connectionFlag == FALSE))
	{
		_authManager -> SaveLocalUser(_lastUserDescr, false);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential:  ReportResult. Success!");    
		#endif
	}


	if ((SUCCEEDED(HRESULT_FROM_NT(ntsStatus))) && (_cpus == CPUS_LOGON) && (_lastUserDescr) && (_authManager) && (_connectionFlag == TRUE))
	{
		_authManager -> SaveLocalUser(_lastUserDescr, true);
		_authManager -> SetUserSignInDate(_lastUserDescr -> userID, _authSystemID);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential:  ReportResult. Success!");    
		#endif
	}


    // If we failed the logon, try to erase the password field.
    if (!SUCCEEDED(HRESULT_FROM_NT(ntsStatus)))
    {
		if ((_pCredProvCredentialEvents) && (_authManager))
        {
			_pCredProvCredentialEvents -> SetFieldString(this, _authManager -> GetPasswortTextFieldIndex(), L"");
        }

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendCredential:  ReportResult. Fail!");    
		#endif
    }

    // Since NULL is a valid value for *ppwszOptionalStatusText and *pcpsiOptionalStatusIcon
    // this function can't fail.

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendCredential:  ReportResult. Done");
	#endif

    return S_OK;
}

/****************************************************************

   Class : NovaTendCredential

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int NovaTendCredential :: WriteToLog(char * message)
{
	if (_logWriter)
		return _logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}