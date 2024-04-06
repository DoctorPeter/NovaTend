/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : NovaTendProvider.cpp

   Description :  Implements methods of class
                  NovaTendProvider

*****************************************************************/

#include "NovaTendProvider.h"
#include "NovaTendCredential.h"
#include "guid.h"
#include <wincred.h>

#include <SettingsManager.h>

// z-wincredprov-01.dll definition structure
extern DLL_COMMON_DEFINITION zWinCredProvDllDefinition;

// DLL module handle
extern HINSTANCE g_hinst;

/****************************************************************

   Class :  NovaTendProvider

   Method : Constructor
  
*****************************************************************/
NovaTendProvider :: NovaTendProvider() : _cRef(1)
{
    // Add dll refference
	DllAddRef();

	// Set NULL
	_pCredentialProviderEvents = NULL;
	_pCredential = NULL;
	_authManager = NULL;
	_hostConnectionsManager = NULL;
	_hubCommandManager = NULL;
	_usrScrCnt = NULL;
	_usrLstCnt = NULL;
			
	SettingsManager * settingsManager = new SettingsManager(zWinCredProvDllDefinition.dllID);

	// Get LOG-files vault path
	char filePath[MAX_PATH];
	settingsManager -> GetLogPath(filePath);

	// Get LOG-file fixed size settings values
	bool fixedFlag = false;
	int fixedSizeValue = 0;
	settingsManager -> GetLogFixedSizeFlag(&fixedFlag);
	if (fixedFlag) settingsManager -> GetLogFixedSizeValue(&fixedSizeValue);

	// Create LOG-writer
	_logWriter = new SafeLogWriter(zWinCredProvDllDefinition.dllID, CreateLogFileName(filePath), fixedSizeValue);

	// Get LOG modes
	bool encLogFile;
	settingsManager -> GetLogEncryptFlag(&encLogFile);

	bool emailLogFile;
	settingsManager -> GetLogEmailSendFlag(&emailLogFile);

	// Save logged user ID
	settingsManager -> SetLoggedUserID(-1);

	// Save authentication system ID
	settingsManager -> SetAuthSystemID(-1);

	delete settingsManager;

	// Set LOG modes
	if (encLogFile)
		_logWriter -> AddMode(LOG_MODE_ENCRYPT_MESSAGES);

	if (emailLogFile)
		_logWriter -> AddMode(LOG_MODE_SEND_MAIL);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: constructor");
	#endif

	_exceptionHandler = new WinExceptionHandler(zWinCredProvDllDefinition.dllID, _logWriter);
}

/****************************************************************

   Class :  NovaTendProvider

   Method : Destructor
  
*****************************************************************/
NovaTendProvider :: ~NovaTendProvider()
{
	if (_pCredential != NULL)
    {
		_pCredential -> Initialize(CPUS_INVALID, 0, NULL, NULL, FALSE, NULL, NULL, NULL, NULL, NULL, -1, NULL, NULL);
        _pCredential -> Release();
        _pCredential = NULL;
    }

	DeleteAuthenticatioManager();

	if (_exceptionHandler != NULL) 
	{
		delete _exceptionHandler;
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: destructor");
	#endif

	if (_logWriter != NULL) 
	{
		delete _logWriter;
	}

    DllRelease();
}

/****************************************************************

   Class :  NovaTendProvider

   Method : PrepareAuthenticationManager
   
   Description : Pepares all data and creates authentication manager.
  
*****************************************************************/
void NovaTendProvider :: PrepareAuthenticationManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: PrepareAuthenticationManager. Start");
	#endif

	DeleteAuthenticatioManager();

	// Get IPC connections information
	SettingsManager * settingsManager = new SettingsManager(zWinCredProvDllDefinition.dllID);
	
	// Get info of host server
	PSERVER_DESCRIPTION pHostServer = settingsManager -> GetHostServer();

	// Get info of GLOBAL server
	PSERVER_DESCRIPTION pGlobalServer = settingsManager -> GetGlobalServer();
	
	unsigned int gServerID = 0;
	char gServerIPAddress[ADDRESS_SIZE] = "";
	unsigned int gServerPort = 0;

	// Get global server info
	if (pGlobalServer)
	{
		gServerID = pGlobalServer -> serverID;
		gServerPort = pGlobalServer -> port;
		strcpy(gServerIPAddress, pGlobalServer -> ipAddress);
		free(pGlobalServer);
	}

	delete settingsManager;
	
	// Create HOST-connections manager
	_hostConnectionsManager = new IPCClientsManagerEx(zWinCredProvDllDefinition.dllID, _logWriter, gServerID, gServerIPAddress, gServerPort);

	// HOST-server
	if (pHostServer)
	{
		_hostConnectionsManager -> AddConnection(pHostServer -> serverID,
												 pHostServer -> serverType,
												 pHostServer -> ipAddress,
												 pHostServer -> port,
												 CLIENT_TYPE_WCP,
												 "Windows credential provider",
												 NULL,
												 DEFAULT_TIMEOUT);
		free(pHostServer);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendProvider: PrepareAuthenticationManager. Added connection to HOST-server");
		#endif
	}

	_hubCommandManager = new HubCommandManager(zWinCredProvDllDefinition.dllID, _logWriter, _hostConnectionsManager, NULL);

	_authManager = new WinAuthenticateManager(zWinCredProvDllDefinition.dllID, _logWriter, _hubCommandManager);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: PrepareAuthenticationManager. Done");
	#endif
}

/****************************************************************

   Class :  NovaTendProvider

   Method : DeleteAuthenticatioManager
   
   Description : Delete authentication manager and 
                 all depended inctnces.
  
*****************************************************************/
void NovaTendProvider :: DeleteAuthenticatioManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: DeleteAuthenticatioManager. Start");
	#endif

	// Remove previous credential manager instance
	if (_authManager != NULL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendProvider: DeleteAuthenticatioManager. Delete previous authenticate manager");
		#endif

		delete _authManager;
		_authManager = NULL;
	}

	// Remove previous command manager instance
	if (_hubCommandManager != NULL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendProvider: DeleteAuthenticatioManager. Delete command manager");
		#endif

		delete _hubCommandManager;
		_hubCommandManager = NULL;
	}
	
	// Remove previous command manager instance
	if (_hostConnectionsManager != NULL) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendProvider: DeleteAuthenticatioManager. Delete HOST connections manager");
		#endif

		delete _hostConnectionsManager;
		_hostConnectionsManager = NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: DeleteAuthenticatioManager. Done");
	#endif
}

/****************************************************************

   Class :  NovaTendProvider

   Method : SetUsageScenario

   Parameters :
			Input : 
				cpus - usage scenario
				dwFlags - flags
			
	Return : Error code

	Description : SetUsageScenario is the provider's cue that 
				  it's going to be asked for tiles in a 
				  subsequent call.
  
*****************************************************************/
HRESULT NovaTendProvider :: SetUsageScenario(
    __in CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    __in DWORD dwFlags
    )
{
    HRESULT hr;

	_dwCredUIFlags = dwFlags;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: SetUsageScenario. Start");
	#endif

	// Remove previous credential instance
	if (_pCredential != NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendProvider: SetUsageScenario. Delete previous credential");
		#endif

		_pCredential -> Release();
		_pCredential = NULL;
	}

	PrepareAuthenticationManager();

	// Validate creation result
	if (_authManager == NULL) 
	{
		return E_OUTOFMEMORY;
	}
			
	int counter = 0;
	_connectionFlag = FALSE;
	
	WriteToLog("NovaTend credential provider: Set usage scenario --> Try connect to server ...");
	
	// Try connect to system database
	do
	{
		_connectionFlag = _authManager -> CheckServerAccess();
		counter++;
		if (_connectionFlag == FALSE) Sleep(100);
	} while ((_connectionFlag == FALSE) && (counter < 10));
	
	// Validate connection result
	if (_connectionFlag == FALSE) 
	{
		WriteToLog("NovaTend credential provider: Set usage scenario --> No server connection!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendProvider: SetUsageScenario. Prepare local users list!");
		#endif

		_usrLstCnt = _authManager -> GetLocalUserList();
	}
	else
	{
		WriteToLog("NovaTend credential provider: Set usage scenario --> Connected to server!");
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendProvider: SetUsageScenario. Prepare global users list!");
		#endif

		_usrLstCnt = _authManager -> GetUserListContainer();
	}

	// Validate result
	if (_usrLstCnt == NULL) 
	{
		WriteToLog("NovaTend credential provider: Set usage scenario --> Can't get list of users!");
		return E_OUTOFMEMORY;
	}

	// Retrieve name of last logged on user
	GetLastLogOnUserName(_lastDomainName, _lastUserName);

	PUSER_DESCRIPTOR lastUserDescr = NULL;
	int authSystemID = -1;

	if (_connectionFlag == FALSE) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendProvider: SetUsageScenario. Get local user descriptor!");
		#endif

		lastUserDescr = _authManager -> GetLocalUserDescriptor(_lastUserName);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
			WriteToLog("NovaTendProvider: SetUsageScenario. Get user descriptor from server!");
		#endif
	
		// Encrypt last user name and domain
		unsigned char encUserName[ENCRYPTED_DATA_SIZE];
		int encUserNameLen;

		unsigned char encDomianName[ENCRYPTED_DATA_SIZE];
		int encDomianNameLen;


		if (!(_authManager -> EncryptWCHARString(_lastUserName, encUserName, &encUserNameLen)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendProvider: SetUsageScenario. Can't encrypt last user name! Done");
			#endif

			return E_OUTOFMEMORY;
		}

		if (!(_authManager -> EncryptWCHARString(_lastDomainName, encDomianName, &encDomianNameLen)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendProvider: SetUsageScenario. Can't encrypt domain name! Done");
			#endif

			return E_OUTOFMEMORY;
		}

		authSystemID = _authManager -> GetAuthSystemID(encDomianName, encDomianNameLen, AUTH_SYSTEM_TYPE);
		lastUserDescr = _authManager -> GetUserDescriptor(encUserName, encUserNameLen, authSystemID);
	}

	if (lastUserDescr)
	{
		if (!(_authManager -> DecryptWCHARString(_lastUserName, lastUserDescr -> encUserName, lastUserDescr -> encUserNameLen)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendProvider: SetUsageScenario. Can't descrypt user name and set it as last user name! Done");
			#endif

			return E_OUTOFMEMORY;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		char mes[256];
		sprintf(mes, "NovaTendProvider: SetUsageScenario. CPUS : %d", (int)cpus);
		WriteToLog(mes);
	#endif

	// Decide which scenarios to support here. Returning E_NOTIMPL simply tells the caller
    // that we're not designed for that scenario.
    switch (cpus)
    {
		// Implemented usage scenarios
		case CPUS_LOGON:
		case CPUS_UNLOCK_WORKSTATION:       
		case CPUS_CREDUI:

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendProvider: SetUsageScenario. One of supported scenarios!");
			#endif

			// Remember usage scenario
			_cpus = cpus;
		
			// Create user screen container
			if (_connectionFlag)
				_usrScrCnt = _authManager -> GetUserScreenContainer(_cpus, authSystemID);
			else
				_usrScrCnt = _authManager -> GetUserLocalScreenContainer();

			// Validate creation result
			if (_usrScrCnt)
			{
				// Create list of domain names
				if (_connectionFlag)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
						WriteToLog("NovaTendProvider: SetUsageScenario. Create domain names list!");
					#endif

					_authManager -> EnumDomainNames(_lastDomainName);
				}

				// Put last user name to username field
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
					WriteToLog("NovaTendProvider: SetUsageScenario. Put last user name to field");
				#endif

				_authManager -> SetUserNameFieldValue(_lastUserName);

				// Create credential instance
				_pCredential = new NovaTendCredential();

				// Validate creation result
				if(_pCredential)
				{
					// Initialize credential
					hr = _pCredential -> Initialize(_cpus, 
													_dwCredUIFlags,
													_authManager,
													_logWriter,
													_connectionFlag,
													_usrScrCnt, 
													_usrLstCnt, 
													_lastUserName,
													_lastDomainName,
													lastUserDescr,
													authSystemID,
													_pCredentialProviderEvents,
													_upAdviseContext);
				
					// Validate result
					if (FAILED(hr))
					{
						_pCredential -> Release();
						_pCredential = NULL;
						hr = E_OUTOFMEMORY;
					}
				}
				else
					hr = E_OUTOFMEMORY;
			}
			else
				hr = E_OUTOFMEMORY;

			break;

			// Not implemented usage scenarios
		case CPUS_CHANGE_PASSWORD:
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendProvider: SetUsageScenario. One of not supported scenarios!");
			#endif

			hr = E_NOTIMPL;
			break;

		default:
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
				WriteToLog("NovaTendProvider: SetUsageScenario. One of not supported scenarios!");
			#endif

			hr = E_INVALIDARG;
			break;
    }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: SetUsageScenario. Done");
	#endif

    return hr;
}

/****************************************************************

   Class :  NovaTendProvider

   Method : SetSerialization

   Parameters :
			Input : 
				pcpcs - pointer to serialization buffer
						
	Return : Error code

	Description : SetSerialization takes the kind of buffer that you 
				 would normally return to LogonUI for an authentication 
				 attempt. It's the opposite of ICredentialProviderCredential::GetSerialization.
				 GetSerialization is implement by a credential and 
				 serializes that credential. Instead, SetSerialization takes 
				 the serialization and uses it to create a tile.
				
				 SetSerialization is called for two main scenarios.
				 The first scenario is in the credui case where it is prepopulating
				 a tile with credentials that the user chose to store in the OS.
				 The second situation is in a remote logon case where the 
				 remote client may wish to prepopulate a tile with a username, 
				 or in some cases, completely populate the tile and
				 use it to logon without showing any UI.

*****************************************************************/
HRESULT NovaTendProvider :: SetSerialization(
    __in const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION * pcpcs
    )
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: SetSerialization");
	#endif

	if ((pcpcs -> clsidCredentialProvider == CLSID_NovaTend) || (_cpus == CPUS_CREDUI))
	{
		HRESULT hr = E_INVALIDARG;

		// Get the current AuthenticationPackageID that we are supporting
		ULONG ulNegotiateAuthPackage;
		hr = RetrieveNegotiateAuthPackage(&ulNegotiateAuthPackage);

		if (SUCCEEDED(hr))
		{
			if (_cpus == CPUS_CREDUI)
			{
				if (CREDUIWIN_IN_CRED_ONLY & _dwCredUIFlags)
				{
					// If we are being told to enumerate only the incoming credential, we must not return
					// success unless we can enumerate it.  We'll set hr to failure here and let it be
					// overridden if the enumeration logic below succeeds.
					hr = E_INVALIDARG;
				}
				else 
					if (_dwCredUIFlags & CREDUIWIN_AUTHPACKAGE_ONLY)
					{
						if (ulNegotiateAuthPackage == pcpcs -> ulAuthenticationPackage)
						{
							// In the credui case, SetSerialization should only ever return S_OK if it is able to serialize the input cred.
							// Unfortunately, SetSerialization had to be overloaded to indicate whether or not it will be able to GetSerialization 
							// for the specific Auth Package that is being requested for CREDUIWIN_AUTHPACKAGE_ONLY to work, so when that flag is 
							// set, it should return S_FALSE unless it is ALSO able to serialize the input cred, then it can return S_OK.
							// So in this case, we can set it to be S_FALSE because we support the authpackage, and then if we
							// can serialize the input cred, it will get overwritten with S_OK.
							hr = S_FALSE;
						}
						else
						{
							//we don't support this auth package, so we want to let logonUI know that by failing
							hr = E_INVALIDARG;
						}
					}
			}

			if ((ulNegotiateAuthPackage == pcpcs -> ulAuthenticationPackage) &&
				((pcpcs -> cbSerialization > 0)  && (pcpcs -> rgbSerialization)))
			{
				KERB_INTERACTIVE_UNLOCK_LOGON * pkil = (KERB_INTERACTIVE_UNLOCK_LOGON *)pcpcs -> rgbSerialization;
				if (pkil -> Logon.MessageType == KerbInteractiveLogon)
				{
					//hr = S_OK;

					// If there isn't a username, we can't serialize or create a tile for this credential.
					if ((pkil -> Logon.UserName.Length > 0)  && (pkil -> Logon.UserName.Buffer))
					{
						hr = S_OK;
					}
					else
					{
						hr = E_INVALIDARG;
					}
				}
			}
		}

		return hr;
	}
	else
	{
		UNREFERENCED_PARAMETER(pcpcs);
		return E_NOTIMPL;
	}
}

/****************************************************************

   Class :  NovaTendProvider

   Method :  Advise

   Parameters :
			Input : 
				pcpe - pointer to credentila provider
					   events instance
				upAdviseContext - pointer to context

	Return : Error code

	Description : called by LogonUI to give you a callback.  
				  Providers often use the callback if they
				  some event would cause them to need to change
				  the set of tiles that they enumerated.

*****************************************************************/
HRESULT NovaTendProvider :: Advise(
    __in ICredentialProviderEvents * pcpe,
    __in UINT_PTR upAdviseContext
    )
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: Advise. Start");
	#endif
	
	if (_pCredentialProviderEvents != NULL)
    {
        _pCredentialProviderEvents -> Release();
    }
    
	_pCredentialProviderEvents = pcpe;
    
	_pCredentialProviderEvents -> AddRef();

    _upAdviseContext = upAdviseContext;

	if (_pCredential)
		_pCredential -> SetCredentialProviderEvents(_pCredentialProviderEvents, _upAdviseContext);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: Advise. Done");
	#endif

    return S_OK;

}

/****************************************************************

   Class :  NovaTendProvider

   Method :  UnAdvise

	Return : Error code

	Description : Called by LogonUI when the ICredentialProviderEvents 
	              callback is no longer valid.

*****************************************************************/
HRESULT NovaTendProvider :: UnAdvise()
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: UnAdvise. Start");
	#endif

	if (_pCredential)
		_pCredential -> DeleteSubWindows();

	if (_pCredentialProviderEvents != NULL)
    {
        _pCredentialProviderEvents -> Release();
        _pCredentialProviderEvents = NULL;
    }

	if (_pCredential)
		_pCredential -> SetCredentialProviderEvents(NULL, NULL);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: UnAdvise. Done");
	#endif

	return S_OK;
}

/****************************************************************

   Class :  NovaTendProvider

   Method :  GetFieldDescriptorCount

   Parameters :
			Output : 
				pdwCount - descriptors count
					   
	Return : Error code

	Description : Called by LogonUI to determine the number of 
				  fields in your tiles. This does mean that all 
				  your tiles must have the same number of fields.
				  This number must include both visible and invisible 
				  fields. If you want a tile to have different fields
				  from the other tiles you enumerate for a given usage
				  scenario you must include them all in this count and 
				  then hide/show them as desired using the field descriptors.

*****************************************************************/
HRESULT NovaTendProvider :: GetFieldDescriptorCount(
    __out DWORD * pdwCount
    )
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: GetFieldDescriptorCount. Start");
	#endif
	
	_usrScrCnt = _authManager -> GetUserScreenContainerPointer();

	if (_usrScrCnt)
	{
		*pdwCount = _usrScrCnt -> screenObjectsCount;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: GetFieldDescriptorCount. Done");
	#endif

    return S_OK;
}

/****************************************************************

   Class :  NovaTendProvider

   Method :  GetFieldDescriptorAt

   Parameters :
			Input: 
				dwIndex - field index
			Output : 
				ppcpfd - pointer to descriptor structure
					   
	Return : Error code

	Description : Gets the field descriptor for a particular field.

*****************************************************************/
HRESULT NovaTendProvider :: GetFieldDescriptorAt(
    __in DWORD dwIndex, 
    __deref_out CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR ** ppcpfd
    )
{    
    HRESULT hr;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: GetFieldDescriptorAt. Start");
	#endif

	_usrScrCnt = _authManager -> GetUserScreenContainerPointer();

    // Verify dwIndex is a valid field.
	if ((_usrScrCnt != NULL) && (dwIndex < (DWORD)_usrScrCnt -> screenObjectsCount) && ppcpfd)
    {
		hr = FieldDescriptorCoAllocCopy(_usrScrCnt -> screenObjects[dwIndex] -> fieldDescriptor, ppcpfd);
    }
    else
    { 
        hr = E_INVALIDARG;
    }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: GetFieldDescriptorAt. Done");
	#endif

    return hr;
}

/****************************************************************

   Class :  NovaTendProvider

   Method :  GetCredentialCount

   Parameters :
			Output : 
				pdwCount - credential count
				pdwDefault - default credential index
				pbAutoLogonWithDefault - defautl logon index
					   
	Return : Error code

	Description : Sets pdwCount to the number of tiles that we 
				  wish to show at this time. Sets pdwDefault to 
				  the index of the tile which should be used as 
				  the default. The default tile is the tile which
				  will be shown in the zoomed view by default. If 
				  more than one provider specifies a default the 
				  last used cred prov gets to pick the default. 
				  If *pbAutoLogonWithDefault is TRUE, LogonUI will
				  immediately call GetSerialization on the credential
				  you've specified as the default and will submit
				  that credential for authentication without showing 
				  any further UI.

*****************************************************************/
HRESULT NovaTendProvider :: GetCredentialCount(
    __out DWORD* pdwCount,
    __out_range(<,*pdwCount) DWORD* pdwDefault,
    __out BOOL* pbAutoLogonWithDefault
    )
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: GetCredentialCount");
	#endif

	*pdwCount = 1;
    *pdwDefault = 0;
    *pbAutoLogonWithDefault = FALSE;
    return S_OK;
}

/****************************************************************

   Class :  NovaTendProvider

   Method :  GetCredentialAt

   Parameters :
			Input:
				dwIndex - credential index
			Output : 
				ppcpc - pointer to credential instance
					   
	Return : Error code

	Description : Returns the credential at the index specified 
				  by dwIndex. This function is called by logonUI
				  to enumerate the tiles.

*****************************************************************/
HRESULT NovaTendProvider :: GetCredentialAt(
    __in DWORD dwIndex, 
    __deref_out ICredentialProviderCredential ** ppcpc
    )
{
    HRESULT hr;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WCP)
		WriteToLog("NovaTendProvider: GetCredentialAt");
	#endif

    if((dwIndex == 0) && ppcpc)
    {
        hr = _pCredential -> QueryInterface(IID_ICredentialProviderCredential, reinterpret_cast<void**>(ppcpc));
    }
    else
    {
        hr = E_INVALIDARG;
    }

    return hr;
}

/****************************************************************

   Class : NovaTendProvider

   Method : CreateLogFileName

   Parameters :
			Input : 
				fileName - file name

	Return : file path

	Description : Create name for log file

*****************************************************************/
char * NovaTendProvider :: CreateLogFileName(char * fileName)
{
	/*
	// Get file name of DLL module
	GetModuleFileNameA(g_hinst, fileName, MAX_PATH);

	// Get file path
	for(size_t i = strlen(fileName) - 1; i >= 0; i--)
	  if (fileName[i] == '\\')
	  {
		  fileName[i + 1] = '\0';
		  break;
	  }
	  */

	if (strcmp(fileName, "") != 0)
		strcat_s(fileName, 256,  "\\");

	// Get current time
	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);
	char timeBuf[32];                                
    
	// Prepare file name
	strftime(timeBuf, 32, "_%m.%d.%Y", timeinfo); 
	strcat_s(fileName, MAX_PATH, "NovaTend_WCP");
	strcat_s(fileName, MAX_PATH, timeBuf);
	strcat_s(fileName, MAX_PATH, ".log");

	// Return file name
	return fileName;
}

/****************************************************************

   Class : NovaTendProvider

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int NovaTendProvider ::  WriteToLog(char * message)
{
	if (_logWriter)
		return _logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}


/****************************************************************

   Function :  NovaTend_WCP_CreateInstance

   Parameters :
			Input:
				riid - GUID

			Output : 
				ppv - interface pointer requested in riid
					   
	Return : Error code

	Description : Boilerplate code to create our provider.

*****************************************************************/
HRESULT NovaTend_WCP_CreateInstance(__in REFIID riid, __deref_out void** ppv)
{
    HRESULT hr;

    NovaTendProvider * pProvider = new NovaTendProvider();

    if (pProvider)
    {
        hr = pProvider -> QueryInterface(riid, ppv);
        pProvider -> Release();
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }
    
    return hr;
}
