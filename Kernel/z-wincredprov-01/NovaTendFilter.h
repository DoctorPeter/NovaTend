/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : NovaTendFilter.h

   Description :  Defines the interface of class of 
				  windows credential provider filter

				  This class is designed only for the 
				  Windows operating systems.

*****************************************************************/

#pragma once 

#include <credentialprovider.h>
#include <windows.h>
#include <strsafe.h>

#include "helpers.h"

/****************************************************************

   Class : NovaTendFilter

   Description : windows credential provider filter

*****************************************************************/
class NovaTendFilter : public ICredentialProviderFilter 
{ 
	public: 
		
		// Add reference
		STDMETHOD_(ULONG, AddRef)() 
		{ 
			return _cRef++; 
		} 

		// Remove reference
		STDMETHOD_(ULONG, Release)() 
		{ 
			LONG cRef = _cRef--; 

			if (!cRef) 
			{ 
				delete this; 
			} 
	
			return cRef; 
		} 
		
		// IUnknown QueryInterface implamentation
		STDMETHOD (QueryInterface)(REFIID riid, void** ppv) 
		{ 
			HRESULT hr; 
		
			if (IID_IUnknown == riid || IID_ICredentialProviderFilter == riid) 
			{ 
				*ppv = this; 
				
				reinterpret_cast<IUnknown*>(*ppv)->AddRef();
				hr = S_OK; 
			} 
			else 
			{ 
				*ppv = NULL; 
				hr = E_NOINTERFACE; 
			} 
		
			return hr; 
		} 


	#pragma warning(disable:4100)

	public: 

		// Create credentila provider filter instance 
		friend HRESULT NovaTendFilter_CreateInstance(__in REFIID riid, __deref_out void** ppv); 

		//This method does the work of filtering. Logon UI and Credential UI 
		// call Filter before calls to GetCredentialCount. 
		IFACEMETHODIMP Filter(CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus, DWORD dwFlags, GUID* rgclsidProviders, BOOL* rgbAllow, DWORD cProviders); 

		// This interface is only useful to individuals working in certain 
		// uncommon remoting scenarios. Most filter implementers should 
		// return E_NOTIMPL from this method.
		IFACEMETHODIMP UpdateRemoteCredential( const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcsIn, CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcsOut);

	protected: 
		
		// Constructor
		NovaTendFilter(); 

		// Destructor
		__override ~NovaTendFilter(); 

	private: 

		// Reference counter
		LONG _cRef; 
}; 
