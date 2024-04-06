/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : NovaTendProvider.h

   Description :  Defines the interface of class of 
				  windows credential provider

				  This class is designed only for the 
				  Windows operating systems.

*****************************************************************/
#include <WinAuthenticateManager.h>
#include <IPCClientsManagerEx.h>
#include <HubCommandManager.h>
#include <credentialprovider.h>
#include <windows.h>
#include <strsafe.h>
#include <WinExceptionHandler.h>
#include <SafeLogWriter.h>
#include "NovaTendCredential.h"
#include "helpers.h"

/****************************************************************

   Class : NovaTendProvider

   Description : windows credential provider

*****************************************************************/
class NovaTendProvider : public ICredentialProvider
{
	public:
		
		// Add reference
		IFACEMETHODIMP_(ULONG) AddRef()
		{
			LONG cRef = ++_cRef;
			return cRef;
		}
    
		// Remove reference
		IFACEMETHODIMP_(ULONG) Release()
		{
			LONG cRef = --_cRef;

			if (!cRef)
			{
				delete this;
			}

			return cRef;
		}

		// IUnknown QueryInterface implamentation
		IFACEMETHODIMP QueryInterface(__in REFIID riid, __deref_out void** ppv)
		{
			static const QITAB qit[] = {QITABENT(NovaTendProvider, ICredentialProvider), {0}, };
			return QISearch(this, qit, riid, ppv);
		}

	public:

		// Allows the Credential Provider to be told how it will be used 
		// (for logon, unlock workstation, expired password change, etc).
		IFACEMETHODIMP SetUsageScenario(__in CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus, __in DWORD dwFlags);

		// Accepts an input credential
		IFACEMETHODIMP SetSerialization(__in const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcs);
		
		// This is an optional method used to enable a Credential Providers to receive an 
		// ICredentialProviderEvents interface pointer from Logon UI and Credential UI during usage. 
		IFACEMETHODIMP Advise(__in ICredentialProviderEvents* pcpe, __in UINT_PTR upAdviseContext);
		
		//Logon UI and Credential UI call UnAdvise to communicate the interface pointer is 
		// no longer valid. After receiving this call, the pointer to the ICredentialProviderEvents
		// interface pointer is not longer valid.
		IFACEMETHODIMP UnAdvise();
		
		// Returns the field count of the UI fields required to display this Credential Provider’s credentials.
		IFACEMETHODIMP GetFieldDescriptorCount(__out DWORD* pdwCount);

		// Returns metadata describing one of the individual UI fields for displaying 
		// this Credential Provider’s credentials. 
		IFACEMETHODIMP GetFieldDescriptorAt(__in DWORD dwIndex,  __deref_out CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR** ppcpfd);

		// This is a required method used to communicate the number of credentials 
		// that can be enumerated through GetCredentialAt.
		IFACEMETHODIMP GetCredentialCount(__out DWORD* pdwCount,  __out_range(<,*pdwCount) DWORD* pdwDefault,  __out BOOL* pbAutoLogonWithDefault);

		// Returns a specific credential from the Credential Provider. 
		IFACEMETHODIMP GetCredentialAt(__in DWORD dwIndex, __deref_out ICredentialProviderCredential** ppcpc);

		// Create credential provider instance 
		friend HRESULT NovaTend_WCP_CreateInstance(__in REFIID riid, __deref_out void** ppv);

	protected:

		// Constructor
		NovaTendProvider();

		// Destructor
		__override ~NovaTendProvider();
    
	private:
		
		// Writes messages to log file
		int WriteToLog(char * message);

		// Create name for log file
		char * CreateLogFileName(char * fileName);

		// Prepare authentication manager
		void PrepareAuthenticationManager(void);

		// Delete authentication manager
		void DeleteAuthenticatioManager(void);

		// Cred UI flags double word
		DWORD									_dwCredUIFlags;

		// Connection flag
		BOOL									_connectionFlag;

		// Reference counter
		LONG                                    _cRef;            

		// Pointer to credentials
		NovaTendCredential                    * _pCredential;    

		// Usage scenario
		CREDENTIAL_PROVIDER_USAGE_SCENARIO      _cpus;
			
		// Pointer to command manager
		HubCommandManager						* _hubCommandManager;

		// Pointer to connections manager
		IPCClientsManagerEx						* _hostConnectionsManager;

		// Pointer to authentication manager
		WinAuthenticateManager					* _authManager;

		// LogWriter instance
		SafeLogWriter							* _logWriter;

		// Eception handler instance
		WinExceptionHandler						*_exceptionHandler;

		// Pointer to user screen container
		PUSER_SCREEN_CONTAINER					_usrScrCnt;

		// Pointer to user list container
		PUSER_LIST								_usrLstCnt;

		// Name of last logged on user
		WCHAR									_lastUserName[NAME_LEN];

		// Name of last logged on domain
		WCHAR									_lastDomainName[NAME_LEN];

		// Used to tell our owner to re-enumerate credentials.
		ICredentialProviderEvents				* _pCredentialProviderEvents;                    

		// Used to tell our owner who we are when asking to 
		UINT_PTR								_upAdviseContext;       
};
