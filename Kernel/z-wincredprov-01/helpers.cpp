/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : helpers.cpp

   Description : Helper functions for copying parameters and 
				 packaging the buffer for GetSerialization

*****************************************************************/


#include "helpers.h"
#include <intsafe.h>
#include <wincred.h>

/****************************************************************

   Function : FieldDescriptorCoAllocCopy

   Parameters :
			Input : 
				rcpfd - field descriptor
			Output:
				ppcpfd - field descriptor buffer

	Return : Returns that buffer in ppcpfd

	Description : Copies the field descriptor pointed to by rcpfd 
				  into a buffer allocated using CoTaskMemAlloc. 

*****************************************************************/
HRESULT FieldDescriptorCoAllocCopy(
    __in const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR& rcpfd,
    __deref_out CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR** ppcpfd
    )
{
    HRESULT hr;
    DWORD cbStruct = sizeof(**ppcpfd);

    CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR* pcpfd = (CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR*)CoTaskMemAlloc(cbStruct);

    if (pcpfd)
    {
        pcpfd->dwFieldID = rcpfd.dwFieldID;
        pcpfd->cpft = rcpfd.cpft;

        if (rcpfd.pszLabel)
        {
            hr = SHStrDupW(rcpfd.pszLabel, &pcpfd->pszLabel);
        }
        else
        {
            pcpfd->pszLabel = NULL;
            hr = S_OK;
        }
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }

    if (SUCCEEDED(hr))
    {
        *ppcpfd = pcpfd;
    }
    else
    {
        CoTaskMemFree(pcpfd);  
        *ppcpfd = NULL;
    }

    return hr;
}

/****************************************************************

   Function : FieldDescriptorCopy

   Parameters :
			Input : 
				rcpfd - field descriptor
			Output:
				pcpfd - field descriptor buffer

	Return : Returns that buffer in pcpfd

	Description : Coppies rcpfd into the buffer pointed to by pcpfd. 
				  The caller is responsible for allocating pcpfd. 
				  This function uses CoTaskMemAlloc to allocate memory for 
				  pcpfd->pszLabel. 

*****************************************************************/
HRESULT FieldDescriptorCopy(
    __in const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR& rcpfd,
    __deref_out CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR* pcpfd
    )
{
    HRESULT hr;
    CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR cpfd;

    cpfd.dwFieldID = rcpfd.dwFieldID;
    cpfd.cpft = rcpfd.cpft;

    if (rcpfd.pszLabel)
    {
        hr = SHStrDupW(rcpfd.pszLabel, &cpfd.pszLabel);
    }
    else
    {
        cpfd.pszLabel = NULL;
        hr = S_OK;
    }

    if (SUCCEEDED(hr))
    {
        *pcpfd = cpfd;
    }

    return hr;
}

/****************************************************************

   Function : UnicodeStringInitWithString

   Parameters :
			Input : 
				pwz - pointer to wide char string
			Output:
				pus - pointer to unicode string structure

	Return : Error code

	Description : This function copies the length of pwz and the 
	              pointer pwz into the UNICODE_STRING structure.
				  This function is intended for serializing a credential
				  in GetSerialization only.
				  Note that this function just makes a copy of the 
				  string pointer. It DOES NOT ALLOCATE storage!
				  Be very, very sure that this is what you want,
				  because it probably isn't outside of the exact 
				  GetSerialization call where the sample uses it.

*****************************************************************/
HRESULT UnicodeStringInitWithString(
    __in PWSTR pwz,
    __deref_out UNICODE_STRING* pus
    )
{
    HRESULT hr;
    if (pwz)
    {
        size_t lenString = lstrlen(pwz);
        USHORT usCharCount;
        hr = SizeTToUShort(lenString, &usCharCount);
        if (SUCCEEDED(hr))
        {
            USHORT usSize;
            hr = SizeTToUShort(sizeof(WCHAR), &usSize);
            if (SUCCEEDED(hr))
            {
				// Explicitly NOT including NULL terminator
                hr = UShortMult(usCharCount, usSize, &(pus->Length)); 

                if (SUCCEEDED(hr))
                {
                    pus->MaximumLength = pus->Length;
                    pus->Buffer = pwz;
                    hr = S_OK;
                }
                else
                {
                    hr = HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
                }
            }
        }
    }
    else
    {
        hr = E_INVALIDARG;
    }
    return hr;
}

/****************************************************************

   Function : _UnicodeStringPackedUnicodeStringCopy

   Parameters :
			Input : 
				rus - pointer to unicode string structure
				pwzBuffer - pointer to wide char string
			Output:
				pus - pointer to unicode string structure

	Description : The following function is intended to be used 
				  ONLY with the Kerb*Pack functions.  It does
				  no bounds-checking because its callers have 
				  precise requirements and are written to respect
				  its limitations.

*****************************************************************/
static void _UnicodeStringPackedUnicodeStringCopy(
    __in const UNICODE_STRING& rus,
    __in PWSTR pwzBuffer,
    __out UNICODE_STRING* pus
    )
{
    pus->Length = rus.Length;
    pus->MaximumLength = rus.Length;
    pus->Buffer = pwzBuffer;

    CopyMemory(pus->Buffer, rus.Buffer, pus->Length);
}

/****************************************************************

   Function : KerbInteractiveUnlockLogonInit

   Parameters :
			Input : 
				pwzDomain - domain name string
				pwzUsername - user name string
				pwzPassword - password string
				cpus- usage scenario

			Output:
				pkiul - pointer to kerberous interactive
						logon structure

	Return : Error code

	Description : Initialize the members of a KERB_INTERACTIVE_UNLOCK_LOGON
	              with weak references to the passed-in strings.  
				  This is useful if you will later use 
				  KerbInteractiveUnlockLogonPackto serialize the structure.  
				  The password is stored in encrypted form for CPUS_LOGON 
				  and CPUS_UNLOCK_WORKSTATION because the system can accept 
				  encrypted credentials.  It is not encrypted in CPUS_CREDUI
				  because we cannot know whether our caller 
				  can accept encrypted credentials.

*****************************************************************/
HRESULT KerbInteractiveUnlockLogonInit(
    __in PWSTR pwzDomain,
    __in PWSTR pwzUsername,
    __in PWSTR pwzPassword,
    __in CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    __out KERB_INTERACTIVE_UNLOCK_LOGON* pkiul
    )
{
    KERB_INTERACTIVE_UNLOCK_LOGON kiul;
    ZeroMemory(&kiul, sizeof(kiul));

    KERB_INTERACTIVE_LOGON* pkil = &kiul.Logon;

    // Note: this method uses custom logic to pack a KERB_INTERACTIVE_UNLOCK_LOGON with a
    // serialized credential.  We could replace the calls to UnicodeStringInitWithString
    // and KerbInteractiveUnlockLogonPack with a single cal to CredPackAuthenticationBuffer,
    // but that API has a drawback: it returns a KERB_INTERACTIVE_UNLOCK_LOGON whose
    // MessageType is always KerbInteractiveLogon.  
    //
    // If we only handled CPUS_LOGON, this drawback would not be a problem.  For 
    // CPUS_UNLOCK_WORKSTATION, we could cast the output buffer of CredPackAuthenticationBuffer
    // to KERB_INTERACTIVE_UNLOCK_LOGON and modify the MessageType to KerbWorkstationUnlockLogon,
    // but such a cast would be unsupported -- the output format of CredPackAuthenticationBuffer
    // is not officially documented.

    // Initialize the UNICODE_STRINGS to share our username and password strings.
    HRESULT hr = UnicodeStringInitWithString(pwzDomain, &pkil -> LogonDomainName);
    if (SUCCEEDED(hr))
    {
        hr = UnicodeStringInitWithString(pwzUsername, &pkil -> UserName);
        if (SUCCEEDED(hr))
        {
            hr = UnicodeStringInitWithString(pwzPassword, &pkil -> Password);
            if (SUCCEEDED(hr))
            {
                // Set a MessageType based on the usage scenario.
                switch (cpus)
                {
                case CPUS_UNLOCK_WORKSTATION:
                    pkil -> MessageType = KerbWorkstationUnlockLogon;
                    hr = S_OK;
                    break;

                case CPUS_LOGON:
                    pkil -> MessageType = KerbInteractiveLogon;
                    hr = S_OK;
                    break;

                case CPUS_CREDUI:
					// MessageType does not apply to CredUI
                    pkil -> MessageType = (KERB_LOGON_SUBMIT_TYPE)0; 
                    hr = S_OK;
                    break;

                default:
                    hr = E_FAIL;
                    break;
                }

                if (SUCCEEDED(hr))
                {
                    // KERB_INTERACTIVE_UNLOCK_LOGON is just a series of structures.  A
                    // flat copy will properly initialize the output parameter.
                    CopyMemory(pkiul, &kiul, sizeof(*pkiul));
                }
            }
        }
    }

    return hr;
}

/****************************************************************

   Function : KerbInteractiveUnlockLogonPack

   Parameters :
			Input : 
				rkiulIn - pointer to kerberous interactive
						  logon structure
			Output:
				prgb - pointer to serialization buffer
				pcb - buffer size


	Return : Error code

	Description : WinLogon and LSA consume "packed" KERB_INTERACTIVE_UNLOCK_LOGONs.
				In these, the PWSTR members of each	UNICODE_STRING are not actually
				pointers but byte offsets into the overall buffer represented
				by the packed KERB_INTERACTIVE_UNLOCK_LOGON. 

*****************************************************************/
HRESULT KerbInteractiveUnlockLogonPack(
    __in const KERB_INTERACTIVE_UNLOCK_LOGON& rkiulIn,
    __deref_out_bcount(*pcb) BYTE** prgb,
    __out DWORD* pcb
    )
{

// Example:
// 
// rkiulIn.Logon.LogonDomainName.Length = 14                                    -> Length is in bytes, not characters
// rkiulIn.Logon.LogonDomainName.Buffer = sizeof(KERB_INTERACTIVE_UNLOCK_LOGON) -> LogonDomainName begins immediately
//                                                                              after the KERB_... struct in the buffer
// rkiulIn.Logon.UserName.Length = 10
// rkiulIn.Logon.UserName.Buffer = sizeof(KERB_INTERACTIVE_UNLOCK_LOGON) + 14   -> UNICODE_STRINGS are NOT null-terminated
//
// rkiulIn.Logon.Password.Length = 16
// rkiulIn.Logon.Password.Buffer = sizeof(KERB_INTERACTIVE_UNLOCK_LOGON) + 14 + 10
// 
    HRESULT hr;

    const KERB_INTERACTIVE_LOGON* pkilIn = &rkiulIn.Logon;

    // alloc space for struct plus extra for the three strings
    DWORD cb = sizeof(rkiulIn) +
        pkilIn->LogonDomainName.Length +
        pkilIn->UserName.Length +
        pkilIn->Password.Length;

    KERB_INTERACTIVE_UNLOCK_LOGON* pkiulOut = (KERB_INTERACTIVE_UNLOCK_LOGON*)CoTaskMemAlloc(cb);
    if (pkiulOut)
    {
        ZeroMemory(&pkiulOut->LogonId, sizeof(pkiulOut->LogonId));

        //
        // point pbBuffer at the beginning of the extra space
        //
        BYTE* pbBuffer = (BYTE*)pkiulOut + sizeof(*pkiulOut);

        //
        // set up the Logon structure within the KERB_INTERACTIVE_UNLOCK_LOGON
        //
        KERB_INTERACTIVE_LOGON* pkilOut = &pkiulOut->Logon;

        pkilOut->MessageType = pkilIn->MessageType;

        //
        // copy each string,
        // fix up appropriate buffer pointer to be offset,
        // advance buffer pointer over copied characters in extra space
        //
        _UnicodeStringPackedUnicodeStringCopy(pkilIn->LogonDomainName, (PWSTR)pbBuffer, &pkilOut->LogonDomainName);
        pkilOut->LogonDomainName.Buffer = (PWSTR)(pbBuffer - (BYTE*)pkiulOut);
        pbBuffer += pkilOut->LogonDomainName.Length;

        _UnicodeStringPackedUnicodeStringCopy(pkilIn->UserName, (PWSTR)pbBuffer, &pkilOut->UserName);
        pkilOut->UserName.Buffer = (PWSTR)(pbBuffer - (BYTE*)pkiulOut);
        pbBuffer += pkilOut->UserName.Length;

        _UnicodeStringPackedUnicodeStringCopy(pkilIn->Password, (PWSTR)pbBuffer, &pkilOut->Password);
        pkilOut->Password.Buffer = (PWSTR)(pbBuffer - (BYTE*)pkiulOut);

        *prgb = (BYTE*)pkiulOut;
        *pcb = cb;

        hr = S_OK;
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }

    return hr;
}

/****************************************************************

   Function : _LsaInitString

   Parameters :
			Input : 
				pszSourceString - pointer to source string
			Output:
				pszDestinationString - pointer to destination string

	Return : Error code

	Description : This function packs the string pszSourceString in
				  pszDestinationString for use with LSA functions
				  including LsaLookupAuthenticationPackage.

*****************************************************************/
static HRESULT _LsaInitString(
    __out PSTRING pszDestinationString, 
    __in PCSTR pszSourceString
    )
{
    size_t cchLength = lstrlenA(pszSourceString);
    USHORT usLength;
    HRESULT hr = SizeTToUShort(cchLength, &usLength);
    if (SUCCEEDED(hr))
    {
        pszDestinationString->Buffer = (PCHAR)pszSourceString;
        pszDestinationString->Length = usLength;
        pszDestinationString->MaximumLength = pszDestinationString->Length+1;
        hr = S_OK;
    }
    return hr;
}

/****************************************************************

   Function : RetrieveNegotiateAuthPackage

   Parameters :
			Output:
				pulAuthPackage - pointer to authetication package

	Return : Error code

	Description : Retrieves the 'negotiate' AuthPackage from the LSA.
				  In this case, Kerberos

*****************************************************************/
HRESULT RetrieveNegotiateAuthPackage(__out ULONG *pulAuthPackage)
{
    HRESULT hr;
    HANDLE hLsa;

    NTSTATUS status = LsaConnectUntrusted(&hLsa);
    if (SUCCEEDED(HRESULT_FROM_NT(status)))
    {
        ULONG ulAuthPackage;
        LSA_STRING lsaszKerberosName;
        _LsaInitString(&lsaszKerberosName, NEGOSSP_NAME_A);

        status = LsaLookupAuthenticationPackage(hLsa, &lsaszKerberosName, &ulAuthPackage);
        if (SUCCEEDED(HRESULT_FROM_NT(status)))
        {
            *pulAuthPackage = ulAuthPackage;
            hr = S_OK;
        }
        else
        {
            hr = HRESULT_FROM_NT(status);
        }
        LsaDeregisterLogonProcess(hLsa);
    }
    else
    {
        hr = HRESULT_FROM_NT(status);
    }

    return hr;
}

/****************************************************************

   Function : _ProtectAndCopyString

   Parameters :
			Input : 
				pwzToProtect - pointer to string to protect
			Output:
				ppwzProtected - pointer to destination protected string

	Return : Error code

	Description : Return a copy of pwzToProtect encrypted with the CredProtect API.
				  pwzToProtect must not be NULL or the empty string.
				 
*****************************************************************/
static HRESULT _ProtectAndCopyString(
    __in PCWSTR pwzToProtect, 
    __deref_out PWSTR* ppwzProtected
    )
{
    *ppwzProtected = NULL;

    // pwzToProtect is const, but CredProtect takes a non-const string.
    // So, ake a copy that we know isn't const.
    PWSTR pwzToProtectCopy;
    HRESULT hr = SHStrDupW(pwzToProtect, &pwzToProtectCopy);
    if (SUCCEEDED(hr))
    {
        // The first call to CredProtect determines the length of the encrypted string.
        // Because we pass a NULL output buffer, we expect the call to fail.
        //
        // Note that the third parameter to CredProtect, the number of characters of pwzToProtectCopy
        // to encrypt, must include the NULL terminator!
        DWORD cchProtected = 0;
        if (!CredProtectW(FALSE, pwzToProtectCopy, (DWORD)wcslen(pwzToProtectCopy)+1, NULL, &cchProtected, NULL))
        {
            DWORD dwErr = GetLastError();

            if ((ERROR_INSUFFICIENT_BUFFER == dwErr) && (0 < cchProtected))
            {
                // Allocate a buffer long enough for the encrypted string.
                PWSTR pwzProtected = (PWSTR)CoTaskMemAlloc(cchProtected * sizeof(WCHAR));
                if (pwzProtected)
                {
                    // The second call to CredProtect actually encrypts the string.
                    if (CredProtectW(FALSE, pwzToProtectCopy, (DWORD)wcslen(pwzToProtectCopy)+1, pwzProtected, &cchProtected, NULL))
                    {
                        *ppwzProtected = pwzProtected;
                        hr = S_OK;
                    }
                    else
                    {
                        CoTaskMemFree(pwzProtected);

                        dwErr = GetLastError();
                        hr = HRESULT_FROM_WIN32(dwErr);
                    }
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                }
            }
            else
            {
                hr = HRESULT_FROM_WIN32(dwErr);
            }
        }

        CoTaskMemFree(pwzToProtectCopy);
    }

    return hr;
}

/****************************************************************

   Function : ProtectIfNecessaryAndCopyPassword

   Parameters :
			Input : 
				pwzPassword - pointer to password string
				cpus - usage scenario
			Output:
				ppwzProtectedPassword - pointer to protected password string

	Return : Error code

	Description : if pwzPassword should be encrypted, return a copy encrypted with CredProtect.
				  If not, just return a copy.
				 
*****************************************************************/
HRESULT ProtectIfNecessaryAndCopyPassword(
    __in PCWSTR pwzPassword,
    __in CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    __deref_out PWSTR* ppwzProtectedPassword
    )
{
    *ppwzProtectedPassword = NULL;

    HRESULT hr;

    // ProtectAndCopyString is intended for non-empty strings only.  Empty passwords
    // do not need to be encrypted.
    if (pwzPassword && *pwzPassword)
    {
        // pwzPassword is const, but CredIsProtected takes a non-const string.
        // So, ake a copy that we know isn't const.
        PWSTR pwzPasswordCopy;
        hr = SHStrDupW(pwzPassword, &pwzPasswordCopy);
        if (SUCCEEDED(hr))
        {
            bool bCredAlreadyEncrypted = false;
            CRED_PROTECTION_TYPE protectionType;

            // If the password is already encrypted, we should not encrypt it again.
            // An encrypted password may be received through SetSerialization in the 
            // CPUS_LOGON scenario during a Terminal Services connection, for instance.
            if (CredIsProtectedW(pwzPasswordCopy, &protectionType))
            {
                if(CredUnprotected != protectionType)
                {
                    bCredAlreadyEncrypted = true;
                }
            }

            // Passwords should not be encrypted in the CPUS_CREDUI scenario.  We
            // cannot know if our caller expects or can handle an encryped password.
            if (CPUS_CREDUI == cpus || bCredAlreadyEncrypted)
            {
                hr = SHStrDupW(pwzPasswordCopy, ppwzProtectedPassword);
            }
            else
            {
                hr = _ProtectAndCopyString(pwzPasswordCopy, ppwzProtectedPassword);
            }
            
            CoTaskMemFree(pwzPasswordCopy);
        }
    }
    else
    {
        hr = SHStrDupW(L"", ppwzProtectedPassword);
    }

    return hr;
}

/****************************************************************

   Function : KerbInteractiveUnlockLogonUnpackInPlace

   Parameters :
			Input : 
				cb - buffer size
			Input/Output:
				 pkiuld - pointer to kerberous interactive
						  logon structure

	Description : Unpack a KERB_INTERACTIVE_UNLOCK_LOGON *in place*. 
				  That is, reset the Buffers from being offsets to
				  being real pointers.  This means, of course, that 
				  passing the resultant struct across any sort of
				  memory space boundary is not going to work -- 
				  repack it if necessary!
				 
*****************************************************************/
void KerbInteractiveUnlockLogonUnpackInPlace(
    __inout_bcount(cb) KERB_INTERACTIVE_UNLOCK_LOGON* pkiul,
    __in DWORD cb
    )
{
    if (sizeof(*pkiul) <= cb)
    {
        KERB_INTERACTIVE_LOGON* pkil = &pkiul->Logon;

        // Sanity check: if the range described by each (Buffer + MaximumSize) falls within the total bytecount,
        // we can be pretty confident that the Buffers are actually offsets and that this is a packed credential.
        if (((ULONG_PTR)pkil->LogonDomainName.Buffer + pkil->LogonDomainName.MaximumLength <= cb) &&
            ((ULONG_PTR)pkil->UserName.Buffer + pkil->UserName.MaximumLength <= cb) &&
            ((ULONG_PTR)pkil->Password.Buffer + pkil->Password.MaximumLength <= cb))
        {
            pkil->LogonDomainName.Buffer = pkil->LogonDomainName.Buffer
                ? (PWSTR)((BYTE*)pkiul + (ULONG_PTR)pkil->LogonDomainName.Buffer)
                : NULL;

            pkil->UserName.Buffer = pkil->UserName.Buffer
                ? (PWSTR)((BYTE*)pkiul + (ULONG_PTR)pkil->UserName.Buffer)
                : NULL;

            pkil->Password.Buffer = pkil->Password.Buffer 
                ? (PWSTR)((BYTE*)pkiul + (ULONG_PTR)pkil->Password.Buffer)
                : NULL;
        }
    }
}

/****************************************************************

   Function : KerbInteractiveUnlockLogonRepackNative

   Parameters :
			Input : 
				rgbWow - pointer to WOW 32-bit serialization buffer
				cbWow - size of WOW 32-bit serialization buffer
			Output:
				prgbNative - pointer to native 64-bit serialization buffer
				pcbNative - size of native 64-bit serialization buffer

	Return : Error code

	Description : Use the CredPackAuthenticationBuffer and 
				  CredUnpackAuthenticationBuffer to convert a 32 bit WOW
				  cred blob into a 64 bit native blob by unpacking it
				  and immediately repacking it.
				 
*****************************************************************/
HRESULT KerbInteractiveUnlockLogonRepackNative(
    __in_bcount(cbWow) BYTE* rgbWow,
    __in DWORD cbWow,
    __deref_out_bcount(*pcbNative) BYTE** prgbNative,
    __out DWORD* pcbNative)
{
    HRESULT hr = E_OUTOFMEMORY;
    PWSTR pszDomainUsername = NULL;
    DWORD cchDomainUsername = 0;
    PWSTR pszPassword = NULL;
    DWORD cchPassword = 0;

    *prgbNative = NULL;
    *pcbNative = 0;

    // Unpack the 32 bit KERB structure
    CredUnPackAuthenticationBufferW(CRED_PACK_WOW_BUFFER, rgbWow, cbWow, pszDomainUsername, &cchDomainUsername, NULL, NULL, pszPassword, &cchPassword);
    if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
    {
        pszDomainUsername = (PWSTR) LocalAlloc(0, cchDomainUsername * sizeof(WCHAR));
        if (pszDomainUsername)
        {
            pszPassword = (PWSTR) LocalAlloc(0, cchPassword * sizeof(WCHAR));
            if (pszPassword)
            {
                if (CredUnPackAuthenticationBufferW(CRED_PACK_WOW_BUFFER, rgbWow, cbWow, pszDomainUsername, &cchDomainUsername, NULL, NULL, pszPassword, &cchPassword))
                {
                    hr = S_OK;
                }
                else
                {
                    hr = GetLastError();
                }
            }
        }
    }

    // Repack native
    if (SUCCEEDED(hr))
    {
        hr = E_OUTOFMEMORY;
        CredPackAuthenticationBufferW(0, pszDomainUsername, pszPassword, *prgbNative, pcbNative);
        if (ERROR_INSUFFICIENT_BUFFER == GetLastError())
        {
            *prgbNative = (BYTE*) LocalAlloc(LMEM_ZEROINIT, *pcbNative);
            if (*prgbNative)
            {
                if (CredPackAuthenticationBufferW(0, pszDomainUsername, pszPassword, *prgbNative, pcbNative))
                {
                    hr = S_OK;
                }
                else
                {
                    LocalFree(*prgbNative);
                }
            }
        }
    }

    LocalFree(pszDomainUsername);
    if (pszPassword)
    {
        SecureZeroMemory(pszPassword, cchPassword * sizeof(WCHAR));
        LocalFree(pszPassword);
    }
    return hr;
}

/****************************************************************

   Function : DomainUsernameStringAlloc

   Parameters :
			Input : 
				pwszDomain - domain name string
				pwszUsername - user name string
			Output:
				ppwszDomainUsername - concatonated string

	Return : Error code

	Description : Concatonates pwszDomain and pwszUsername and 
	               places the result in *ppwszDomainUsername.
				 
*****************************************************************/
HRESULT DomainUsernameStringAlloc(
    __in PCWSTR pwszDomain,
    __in PCWSTR pwszUsername,
    __deref_out PWSTR* ppwszDomainUsername
    )
{
    HRESULT hr;
    size_t cchDomain = lstrlen(pwszDomain);
    size_t cchUsername = lstrlen(pwszUsername);
    // Length of domain, 1 character for '\', length of Username, plus null terminator. 
    size_t cbLen = sizeof(WCHAR) * (cchDomain + 1 + cchUsername + 1);
    PWSTR pwszDest = (PWSTR)HeapAlloc(GetProcessHeap(), 0, cbLen);
    if (pwszDest)
    {
        hr = StringCbPrintfW(pwszDest, cbLen, L"%s\\%s", pwszDomain, pwszUsername);
        if (SUCCEEDED(hr))
        {
            *ppwszDomainUsername = pwszDest;
        }
        else
        {
            HeapFree(GetProcessHeap(), 0, pwszDest);
        }
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }

    return hr;
}


/****************************************************************

   Function : DomainUsernameStringAlloc

   Parameters :
			Input : 
				pwszDomain - domain name string
				pwszUsername - user name string
			Output:
				pwszDomainUsername - concatonated string

	Return : Error code

	Description : Concatonates pwszDomain and pwszUsername and 
	               places the result in *ppwszDomainUsername.
				 
*****************************************************************/
HRESULT DomainUsernameStringConcat(
    __in PCWSTR pwszDomain,
    __in PCWSTR pwszUsername,
    __deref_out PWSTR pwszDomainUsername
    )
{
    HRESULT hr;

	if ((!pwszDomainUsername) || (!pwszDomain) || (!pwszUsername))
	{
		hr = E_INVALIDARG;
	}
	else
	{
		wcscpy(pwszDomainUsername, pwszDomain);
		wcscat(pwszDomainUsername, L"\\");
		wcscat(pwszDomainUsername, pwszUsername);

		hr = S_OK;
	}

    return hr;
}

/****************************************************************

   Function : DomainUsernameStringSplit

   Parameters :
			Input : 
				ppwszDomainUsername - concatonated string
				
			Output:
				pwszDomain - domain name string
				pwszUsername - user name string

	Return : Error code

	Description : Split pwszDomainUsername to 
				  pwszDomain and pwszUsername
				 
*****************************************************************/
HRESULT DomainUsernameStringSplit(
	__in PCWSTR pwszDomainUsername,
	__deref_out PWSTR pwszDomain,
	__deref_out PWSTR pwszUsername
	)
{
	HRESULT hr;

	if ((!pwszDomainUsername) || (!pwszDomain) || (!pwszUsername))
	{
		hr = E_INVALIDARG;
	}
	else
	{
		PCWSTR splitter = wcschr(pwszDomainUsername, L'\\');
		if (splitter == NULL)
		{
			wcscpy(pwszUsername, pwszDomainUsername);
			wcscpy(pwszDomain, L"");
		}
		else
		{
			DWORD splitterPosition = (DWORD)(splitter - pwszDomainUsername);
			wcsncpy(pwszDomain, pwszDomainUsername, splitterPosition);
			pwszDomain[splitterPosition] = L'\0';
			wcscpy(pwszUsername, splitter + 1);
		}

		hr = S_OK;
	}

	return hr;
}

/****************************************************************

   Function : LoadBmpImage

   Parameters :
			Input : 
				bmpBuffer - pointer to BMP buffer

	Return : Pointer to HBITMAP structure

	Description : create HBITMAP structure from BMP-file that
				  placed into memory buffer
				 
*****************************************************************/
HBITMAP LoadBmpImage(char * bmpBuffer)
{
	if (!bmpBuffer) return NULL;

	char * pBmp = bmpBuffer;

	BITMAPFILEHEADER bmfHeader;
		
	if(memcpy_s(&bmfHeader, sizeof(BITMAPFILEHEADER), pBmp, sizeof(BITMAPFILEHEADER))) return NULL;
	
	// File type should be 'BM'
	if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))  return NULL;

	pBmp = pBmp + sizeof(BITMAPFILEHEADER);

	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)pBmp;
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)pBmp;

	// If bmiHeader.biClrUsed is zero we have to infer the number
	// of colors from the number of bits used to specify it.
	int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 1 << bmiHeader.biBitCount;

	LPVOID lpDIBBits;
	if(bmInfo.bmiHeader.biBitCount > 8)
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
		            ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

	HDC hdc = GetDC(NULL);
	HBITMAP hBmp = CreateDIBitmap(hdc, &bmiHeader, CBM_INIT, lpDIBBits, &bmInfo, DIB_RGB_COLORS);
	ReleaseDC(NULL, hdc);
	return hBmp;
  }

/****************************************************************

   Function : CreateBackgroundImageDirectory

   Parameters :
			Output : 
				SystemDirectory - system directory path

	Return : Error code

	Description : Creates path to logon backgound image file
				 
*****************************************************************/
int CreateBackgroundImageDirectory(WCHAR * SystemDirectory)
{
	if (GetSystemDirectory(SystemDirectory, MAX_PATH) == 0)
		return ERROR_CANCELLED;
	wcscat_s(SystemDirectory, MAX_PATH, L"\\oobe\\info\\backgrounds");
	return SHCreateDirectory(NULL, SystemDirectory);
}

/****************************************************************

   Function : CreateLogonBackgroundRegistryRecord

	Return : Error code

	Description : Write to system registry change of 
				  logon backgound image
				 
*****************************************************************/
int CreateLogonBackgroundRegistryRecord(void)
{
	HKEY hKey; 
	DWORD disp;
	WCHAR * regPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\LogonUI\\Background";
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regPath, 0, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, &disp);
	if (errorRes != ERROR_SUCCESS)
      return errorRes;
    
	DWORD value = 1;
	errorRes = RegSetValueEx(hKey, L"OEMBackground", 0, REG_DWORD, (BYTE *)&value, sizeof(value));
	if(errorRes != ERROR_SUCCESS)
      return errorRes;

	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
      return errorRes;

	return ERROR_SUCCESS;
}

/****************************************************************

   Function : ChangeLogonBackground

   Parameters :
			Input : 
				picFileName - path to new background image file
	
	Return : Error code

	Description : Change logon backgound image
				 
*****************************************************************/
int ChangeLogonBackground(WCHAR * picFileName)
{
	WCHAR SystemDirectory[MAX_PATH];
	int dirCreateResult = CreateBackgroundImageDirectory(SystemDirectory);

	if ((dirCreateResult == ERROR_SUCCESS) ||
		(dirCreateResult == ERROR_FILE_EXISTS) ||
		(dirCreateResult == ERROR_ALREADY_EXISTS))
	{
		int regKeyCreateRes = CreateLogonBackgroundRegistryRecord();

		if (regKeyCreateRes == ERROR_SUCCESS)
		{
			wcscat_s(SystemDirectory, MAX_PATH, L"\\BackgroundDefault.jpg");		
			if (CopyFile(picFileName, SystemDirectory, FALSE))
				return ERROR_SUCCESS;
			else
				return GetLastError();
		}
		else
			return regKeyCreateRes;
	}
	else
		return dirCreateResult;
}

/****************************************************************

   Function : GetLastLogOnUserName

   Parameters :
			Output : 
				domainName	- domain name
				userName	- user name string

	Return : Error code

	Description : Get from registry last logged on user name
				 
*****************************************************************/
HRESULT  GetLastLogOnUserName(LPWSTR domainName, LPWSTR userName)
{
	if ((domainName == NULL) || (userName == NULL))
		return E_POINTER;

	HRESULT hr = S_OK;

	HKEY hKey; 
	DWORD disp;
	
	WCHAR * regPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Authentication\\LogonUI";
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regPath, 0, NULL, REG_OPTION_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	if (errorRes != ERROR_SUCCESS)
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	DWORD valueType = 0;
	DWORD userNameLen = 128;
	WCHAR userNameBuf[128];
	errorRes = RegGetValue(hKey, NULL, L"LastLoggedOnSAMUser", RRF_RT_REG_SZ, &valueType, userNameBuf, &userNameLen);
	if(errorRes != ERROR_SUCCESS)
    {
		hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    {
		hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	int pos = -1;
	for(DWORD i = userNameLen - 1; i >= 0; i--)
		if (userNameBuf[i] == L'\\')
		{
			pos = i + 1;
			break;
		}


	if (pos != -1)
	{
		DWORD k = 0;
		
		while(userNameBuf[pos] != L'\0')
		{
			userName[k] = userNameBuf[pos];
			k++;
			pos++;
		}

		userName[k] = L'\0';


		k = 0;
		while(userNameBuf[k] != L'\\')
		{
			domainName[k] = userNameBuf[k];
			k++;
		}

		domainName[k] = L'\0';
	}
	else
		hr = E_ABORT;

	return hr;
}

/****************************************************************

   Function : SaveLoggedUserData

   Parameters :
			Input :
				userID - user ID
				authSystemID - authentication system IDng

	Return : Error code

	Description : Save data of last logged user
				 
*****************************************************************/
HRESULT SaveLoggedUserData(int userID, int authSystemID)
{
	HKEY hKey; 
	DWORD disp;
	HRESULT hr = S_OK;

	// Open key for write
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\NovaTend\\Users", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}
	
	// Set user ID value
	errorRes = RegSetValueEx(hKey, L"LSTLGDUID", NULL, REG_DWORD, (BYTE *)&userID, sizeof(userID));
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}
	
	// Set authentication system ID value
	errorRes = RegSetValueEx(hKey, L"LSTAUTHSYSID", NULL, REG_DWORD, (BYTE *)&authSystemID, sizeof(authSystemID));
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	// Close key
	errorRes = RegCloseKey(hKey);

	return hr;
}