/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : dll.cpp

   Description :  Defines the entry point for the DLL application.
				  Standard dll required functions and class 
				  factory implementation.

*****************************************************************/

#include <windows.h>
#include <unknwn.h>
#include "Dll.h"
#include "helpers.h"

#include <DllID.h>

// z-wincredprov-01.dll definition structure
DLL_COMMON_DEFINITION zWinCredProvDllDefinition =
{
	Z_WIN_CRED_PROV_DLL_ID,
	0x00010000,
	"z-wincredprov-01.dll - windows credential provider",
	0,
	{}
};


// Global dll reference count
static LONG g_cRef = 0;   

// Global dll hinstance
HINSTANCE g_hinst = NULL; 

// Extern definition of function to create windows credential provider instance
extern HRESULT NovaTend_WCP_CreateInstance(__in REFIID riid, __deref_out void** ppv);

// Extern definition of function to create windows credential provider filter instance
extern HRESULT NovaTendFilter_CreateInstance(__in REFIID riid, __deref_out void** ppv);

// Windows credential provider GUID
EXTERN_C GUID CLSID_NovaTend;

/****************************************************************

   Class : CClassFactory

   Description : factory of windows credential provider objects

*****************************************************************/
class CClassFactory : public IClassFactory
{
	public:
		
		// Constructor
		CClassFactory() : _cRef(1) 
		{
		}

    
		// IUnknown QueryInterface implamentation
		IFACEMETHODIMP QueryInterface(__in REFIID riid, __deref_out void **ppv)
		{
			static const QITAB qit[] = {QITABENT(CClassFactory, IClassFactory),	{0}, };
			return QISearch(this, qit, riid, ppv);
		}

		// Add reference
		IFACEMETHODIMP_(ULONG) AddRef()
		{
			return InterlockedIncrement(&_cRef);
		}

		// Subtract reference
		IFACEMETHODIMP_(ULONG) Release()
		{
			LONG cRef = InterlockedDecrement(&_cRef);
			if (!cRef)
				delete this;
			return cRef;
		}

		// IClassFactory CreateInstance method implementation
		IFACEMETHODIMP CreateInstance(__in IUnknown* pUnkOuter, __in REFIID riid, __deref_out void **ppv)
		{
			HRESULT hr; 
			hr = NULL;
			if (!pUnkOuter) 
			{ 
				// Create windows credential provider
				if (IID_ICredentialProvider == riid)
					hr = NovaTend_WCP_CreateInstance(riid, ppv);
				else
					// Create windows credential provider filter
					 if (IID_ICredentialProviderFilter == riid)
						 hr = NovaTendFilter_CreateInstance(riid, ppv); 
			}
			else 
			{ 
				hr = CLASS_E_NOAGGREGATION; 
			} 
       
			return hr; 
		}

		// Lock class factory
		IFACEMETHODIMP LockServer(__in BOOL bLock)
		{
			if (bLock)
			{
				DllAddRef();
			}
			else
			{
				DllRelease();
			}
			
			return S_OK;
		}

	private:
		
		// Destructor
		~CClassFactory()
		{
		}
		
		// Class factory reference counter
		long _cRef;
};

/****************************************************************

   Function : CClassFactory_CreateInstance

   Parameters :
			Input : 
				rclsid - GUID of client
				riid - interface ID
			Output:
				ppv - interface pointer requested in riid

	Return : error code

	Description : create instance of class factory

*****************************************************************/
HRESULT CClassFactory_CreateInstance(__in REFCLSID rclsid, __in REFIID riid, __deref_out void **ppv)
{
    *ppv = NULL;

    HRESULT hr;

    if (CLSID_NovaTend == rclsid)
    {
        CClassFactory* pcf = new CClassFactory();

        if (pcf)
        {
            hr = pcf -> QueryInterface(riid, ppv);
            pcf -> Release();
        }
        else
        {
            hr = E_OUTOFMEMORY;
        }
    }
    else
    {
        hr = CLASS_E_CLASSNOTAVAILABLE;
    }
    
	return hr;
}

/****************************************************************

   Function : DllAddRef

   Description : add global dll reference

*****************************************************************/
void DllAddRef()
{
    InterlockedIncrement(&g_cRef);
}

/****************************************************************

   Function : DllRelease

   Description : subtract global dll reference

*****************************************************************/
void DllRelease()
{
    InterlockedDecrement(&g_cRef);
}

/****************************************************************

   Function : DllRelease

   Return : if the function succeeds, the return value is S_OK.
            Otherwise, it is S_FALSE.

   Description : Determines whether the DLL that implements this function
                 is in use. If not, the caller can unload the DLL 
				 from memory.

*****************************************************************/
STDAPI DllCanUnloadNow()
{
    return (g_cRef > 0) ? S_FALSE : S_OK;
}

/****************************************************************

   Function : DllGetClassObject

   Parameters :
			Input : 
				rclsid - GUID of client
				riid - interface ID
			Output:
				ppv - interface pointer requested in riid

	Return : error code

	Description : Retrieves the class object from a DLL object 
				  handler or object application.

*****************************************************************/
STDAPI DllGetClassObject(__in REFCLSID rclsid, __in REFIID riid, __deref_out void** ppv)
{
    return CClassFactory_CreateInstance(rclsid, riid, ppv);
}

// Entry point for the DLL application.
STDAPI_(BOOL) DllMain(__in HINSTANCE hinstDll, __in DWORD dwReason, __in void *)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDll);
        break;

    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    
    g_hinst = hinstDll;

    return TRUE;
}

