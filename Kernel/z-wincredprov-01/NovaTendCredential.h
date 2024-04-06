/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : NovaTendCredential.h

   Description :  Defines the interface of class of 
				  windows credential provider credential

				  This class is designed only for the 
				  Windows operating systems.

*****************************************************************/

#pragma once

#include <WinAuthenticateManager.h>
#include <windows.h>
#include <shlguid.h>
#include <strsafe.h>
#include <SafeLogWriter.h>

#include "dll.h"
#include "resource.h"
#include "helpers.h"
#include "InfoWindow.h"


/****************************************************************

   Class : NovaTendCredential

   Description : windows user credential

*****************************************************************/
class NovaTendCredential : public ICredentialProviderCredential
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
			static const QITAB qit[] =	{QITABENT(NovaTendCredential, ICredentialProviderCredential),	{0}, };
			return QISearch(this, qit, riid, ppv);
		}

	public:
		// Logon UI and Credential UI use this method to pass the Credential a pointer to an instance 
		// of ICredentialProviderCredentialEvents enabling synchronous callback communication
		IFACEMETHODIMP Advise(__in ICredentialProviderCredentialEvents* pcpce);

		// UnAdvise and Advise are called in pairs. Credential UI and Logon UI call 
		// UnAdvise when the pointer *pcpce supplied in Advise is no longer valid.
		IFACEMETHODIMP UnAdvise();
		
		// This method is called when a credential is selected. 
		IFACEMETHODIMP SetSelected(__out BOOL* pbAutoLogon);

		// This method is called when a credential loses selection. 
		IFACEMETHODIMP SetDeselected();
		
		// Allows Logon UI and Credential UI to retrieve information about a 
		// particular field of a credential in order to display this information in the user tile. 
		IFACEMETHODIMP GetFieldState(__in DWORD dwFieldID,  __out CREDENTIAL_PROVIDER_FIELD_STATE* pcpfs, __out CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE* pcpfis);

		// Credential UI and Logon UI use this method to obtain the pszLabel for a field
		IFACEMETHODIMP GetStringValue(__in DWORD dwFieldID, __deref_out PWSTR* ppwsz);

		// Credential UI and Logon UI obtain a bitmap to display in the user tile by calling this method. 
		IFACEMETHODIMP GetBitmapValue(__in DWORD dwFieldID, __out HBITMAP* phbmp);

		// Credential UI and Logon UI use this method to obtain checkbox value
		IFACEMETHODIMP GetCheckboxValue(__in DWORD dwFieldID, __out BOOL* pbChecked, __deref_out PWSTR* ppwszLabel);

		// Credential UI and Logon UI use this method to obtain the number of items 
		// in a combo box and which item should have initial selection.
		IFACEMETHODIMP GetComboBoxValueCount(__in DWORD dwFieldID, __out DWORD* pcItems, __out_range(<,*pcItems) DWORD* pdwSelectedItem);

		// Credential UI and Logon UI use this method to obtain the value of a string in 
		// the combo box at the index specified by the caller.
		IFACEMETHODIMP GetComboBoxValueAt(__in DWORD dwFieldID, __in DWORD dwItem, __deref_out PWSTR* ppwszItem);

		// Logon UI uses this method to obtain information about which field the submit button 
		// should be placed after. Credential UI never calls this method.
		IFACEMETHODIMP GetSubmitButtonValue(__in DWORD dwFieldID, __out DWORD* pdwAdjacentTo);
		
		//Credential UI and Logon UI use this method to set the value of 
		// strings on CPFT_EDIT_TEXT fields as the user types in them.
		IFACEMETHODIMP SetStringValue(__in DWORD dwFieldID, __in PCWSTR pwz);
		
		// Credential UI and Logon UI use this method to indicate to the credential 
		// that a checkbox value has been changed (set to true or false).
		IFACEMETHODIMP SetCheckboxValue(__in DWORD dwFieldID, __in BOOL bChecked);

		// Credential UI and Logon UI use this method to indicate to the 
		// credential that a Combo Box item has been selected.
		IFACEMETHODIMP SetComboBoxSelectedValue(__in DWORD dwFieldID, __in DWORD dwSelectedItem);

		// Credential UI and Logon UI use this method to indicate 
		// to the credential that a Command Link was clicked.
		IFACEMETHODIMP CommandLinkClicked(__in DWORD dwFieldID);

		// This method is required. The is expected to take appropriate action based 
		// on the usage scenario. In CPUS_LOGON and CPUS_UNLOCK_WORKSTATION, 
		// the information credential information should be packed up into a 
		// binary stream for transmission to Winlogon and eventual submission to LSA. 
		// In CPUS_CREDUI, the information should be serialized for 
		// delivery to the calling application. 
		IFACEMETHODIMP GetSerialization(__out CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE* pcpgsr, __out CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcs, __deref_out_opt PWSTR* ppwszOptionalStatusText, __out CREDENTIAL_PROVIDER_STATUS_ICON* pcpsiOptionalStatusIcon);

		// This method is called by Logon UI to allow the Credential to 
		// format the ntstatus code returned after the last logon attempt. 
		IFACEMETHODIMP ReportResult(__in NTSTATUS ntsStatus, __in NTSTATUS ntsSubstatus, __deref_out_opt PWSTR* ppwszOptionalStatusText, __out CREDENTIAL_PROVIDER_STATUS_ICON* pcpsiOptionalStatusIcon);

		// Initialize credentials data
		HRESULT Initialize(__in CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
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
						   __in UINT_PTR credentialProviderAdviseContext);
	
		// Get creating window handle
		HWND GetParentWindow();	
		
		// Constructor
		NovaTendCredential();
	
		// Destructor
		virtual ~NovaTendCredential();

		// Create and show sub windows
		HRESULT CreateSubWindows();

		// Remove all sub windows
		void DeleteSubWindows();

		// Set values of credential provider events
		void SetCredentialProviderEvents(__in ICredentialProviderEvents * credentialProviderEvents,
										 __in UINT_PTR credentialProviderAdviseContext);

		// Check main screen control for pasword box
		BOOL CheckPasswordBoxControl(HWND hWnd);

	private:
					
		// Rebuild user screen
		void RebuildUserScreen();

		// Set settings of symbol box password sub window
		void SetSymbolBoxWindowSettings();

		// Write messages to log-file
		int WriteToLog(char * message);

		//Get authentication system ID
		int GetAuthSystemID(void);

		// Find position for submit button
		DWORD FindSumbitButtonPosition();

		// Reference counter
		LONG _cRef;

		// Connection flag
		BOOL _connectionFlag;
		
		// Cred UI flags double word
		DWORD _dwFlags;

		// The usage scenario for which we were enumerated
		CREDENTIAL_PROVIDER_USAGE_SCENARIO _cpus; 

		// Pointer to user screen container
		PUSER_SCREEN_CONTAINER _usrScrCnt;

		// Pointer to list of users
		PUSER_LIST _usrLstCnt;

		// Name of last logged on user
		WCHAR * _lastUserName;

		// Name of last logged domain
		WCHAR * _lastDomainName;

		// Last domain name changing flag
		BOOL _lastDomainNameChanged;

		// Pointer to descriptor of last logged on user
		PUSER_DESCRIPTOR _lastUserDescr;

		// Current authentication system ID
		int	_authSystemID;
	
		// Pointer to authentication manager
		WinAuthenticateManager * _authManager;

		// Pointer to log writer
		SafeLogWriter * _logWriter;
		
		// Pointer to addiional information window
		InfoWindow * _pInfoWnd[MAX_SCR_OBJ_COUNT];

		// Pointer to ICredentialProviderCredentialEvents instance
		ICredentialProviderCredentialEvents * _pCredProvCredentialEvents;                     

		// Used to tell our owner to re-enumerate credentials.
		ICredentialProviderEvents	* _pCredentialProviderEvents;                    

		// Used to tell our owner who we are when asking to 
		UINT_PTR _upCredentialProviderAdviseContext;       
};
