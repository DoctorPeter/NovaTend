/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : NovaTendFilter.cpp

   Description :  Implements methods of class
                  NovaTendFilter

*****************************************************************/

#include "NovaTendFilter.h"
#include "dll.h"

/****************************************************************

   Class :  NovaTendFilter

   Method : Constructor
  
*****************************************************************/
NovaTendFilter :: NovaTendFilter() : _cRef(1)
{
    DllAddRef();
}

/****************************************************************

   Class :  NovaTendFilter

   Method : Destructor
  
*****************************************************************/
NovaTendFilter :: ~NovaTendFilter()
{
	DllRelease();
}

/****************************************************************

   Class : NovaTendFilter

   Method : Filter

   Parameters :
			Input : 
				cpus - usage scenario
				dwFlags - flags
				rgclsidProviders - provider GUID list
			    cProviders - provider GUID list size
			Oputput:
				rgbAllow - pointer to the boolean counter 

	Return : Error code

	Description : This method does the work of filtering. 
				  Logon UI and Credential UI call Filter before 
				  calls to GetCredentialCount.
  
*****************************************************************/
HRESULT NovaTendFilter :: Filter(
	CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus, 
	DWORD dwFlags, 
	GUID* rgclsidProviders, 
	BOOL* rgbAllow, 
	DWORD cProviders)
{
	switch (cpus) 
    { 
        case CPUS_LOGON: 
		case CPUS_UNLOCK_WORKSTATION: 
			for (DWORD i = 0; i < cProviders; i++) 
				if (IsEqualGUID(rgclsidProviders[i], CLSID_PasswordCredentialProvider)) 
					rgbAllow[i] = FALSE; 
            return S_OK; 
        case CPUS_CREDUI: 
        case CPUS_CHANGE_PASSWORD: 
            return E_NOTIMPL; 
        default: 
            return E_INVALIDARG; 
    } 
}

/****************************************************************

   Class : NovaTendFilter

   Method : UpdateRemoteCredential

   Parameters :
			Input : 
				pcpsIn - allows the caller to specify a 
						 credential to be updated
			Oputput:
				pcpcsOut - allows the filter to send a credential 
						   serialization back to the caller

	Return : Error code

	Description : This interface is only useful to individuals 
				  working in certain uncommon remoting scenarios. 
				  Most filter implementers should return E_NOTIMPL 
				  from this method.
  
*****************************************************************/
HRESULT NovaTendFilter :: UpdateRemoteCredential(
	const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpsIn, 
	CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION *pcpcsOut)
{
	return E_NOTIMPL;
}

/****************************************************************

   Function :  NovaTendFilter_CreateInstance

   Parameters :
			Input:
				riid - GUID

			Output : 
				ppv - interface pointer requested in riid
					   
	Return : Error code

	Description : Boilerplate code to create our filter.

*****************************************************************/
HRESULT NovaTendFilter_CreateInstance(__in REFIID riid, __deref_out void** ppv)
{
    HRESULT hr;
    NovaTendFilter* pFilter = new NovaTendFilter();

	if (pFilter)
    {
        hr = pFilter -> QueryInterface(riid, ppv);
        pFilter -> Release();
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }
    
    return hr;
}