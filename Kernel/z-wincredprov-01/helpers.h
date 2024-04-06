/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : helpers.h

   Description : Helper functions for copying parameters and 
				 packaging the buffer for GetSerialization

*****************************************************************/

#pragma once
#include <credentialprovider.h>
#include <ntsecapi.h>
#define SECURITY_WIN32
#include <security.h>
#include <intsafe.h>

#include <windows.h>
#include <Shlobj.h>
#include <strsafe.h>

#pragma warning(push)
#pragma warning(disable : 4995)
#include <shlwapi.h>
#pragma warning(pop)

// Makes a copy of a field descriptor using CoTaskMemAlloc
HRESULT FieldDescriptorCoAllocCopy(
    __in const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR& rcpfd,
    __deref_out CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR** ppcpfd
    );

// Makes a copy of a field descriptor on the normal heap
HRESULT FieldDescriptorCopy(
    __in const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR& rcpfd,
    __deref_out CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR* pcpfd
    );

// Creates a UNICODE_STRING from a NULL-terminated string
HRESULT UnicodeStringInitWithString(
    __in PWSTR pwz, 
    __out UNICODE_STRING* pus
    );

// Initializes a KERB_INTERACTIVE_UNLOCK_LOGON with weak references to the provided credentials
HRESULT KerbInteractiveUnlockLogonInit(
    __in PWSTR pwzDomain,
    __in PWSTR pwzUsername,
    __in PWSTR pwzPassword,
    __in CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    __out KERB_INTERACTIVE_UNLOCK_LOGON* pkiul
    );

// Packages the credentials into the buffer that the system expects
HRESULT KerbInteractiveUnlockLogonPack(
    __in const KERB_INTERACTIVE_UNLOCK_LOGON& rkiulIn,
    __deref_out_bcount(*pcb) BYTE** prgb,
    __out DWORD* pcb
    );

// Get the authentication package that will be used for our logon attempt
HRESULT RetrieveNegotiateAuthPackage(
    __out ULONG * pulAuthPackage
    );

// Encrypt a password (if necessary) and copy it; if not, just copy it
HRESULT ProtectIfNecessaryAndCopyPassword(
    __in PCWSTR pwzPassword,
    __in CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    __deref_out PWSTR* ppwzProtectedPassword
    );

// Convert a 32 bit WOW cred blob into a 64 bit native blob by unpacking 
// it and immediately repacking it.
HRESULT KerbInteractiveUnlockLogonRepackNative(
    __in_bcount(cbWow) BYTE* rgbWow,
    __in DWORD cbWow,
    __deref_out_bcount(*pcbNative) BYTE** prgbNative,
    __out DWORD* pcbNative
    );

// Unpack a KERB_INTERACTIVE_UNLOCK_LOGON *in place*.  That is, reset the Buffers from being offsets to
// being real pointers.  This means, of course, that passing the resultant struct across any sort of 
// memory space boundary is not going to work -- repack it if necessary!
void KerbInteractiveUnlockLogonUnpackInPlace(
    __inout_bcount(cb) KERB_INTERACTIVE_UNLOCK_LOGON* pkiul,
    __in DWORD cb
    );

// Concatonates pwszDomain and pwszUsername and places the result in *ppwszDomainUsername
HRESULT DomainUsernameStringAlloc(
    __in PCWSTR pwszDomain,
    __in PCWSTR pwszUsername,
    __deref_out PWSTR* ppwszDomainUsername
    );

// Concatonates pwszDomain and pwszUsername and places the result in *ppwszDomainUsername
HRESULT DomainUsernameStringConcat(
	__in PCWSTR pwszDomain,
	__in PCWSTR pwszUsername,
	__deref_out PWSTR pwszDomainUsername
	);

// Split pwszDomainUsername to pwszDomain and pwszUsername
HRESULT DomainUsernameStringSplit(
	__in PCWSTR pwszDomainUsername,
	__deref_out PWSTR pwszDomain,
	__deref_out PWSTR pwszUsername
	);

// Load BMP image from memory stream
HBITMAP LoadBmpImage(char * bmpBuffer);

// Change windows logon background image
int ChangeLogonBackground(WCHAR * picFileName);

//  Get from registry last logged on user name
HRESULT  GetLastLogOnUserName(LPWSTR domainName, LPWSTR userName);


