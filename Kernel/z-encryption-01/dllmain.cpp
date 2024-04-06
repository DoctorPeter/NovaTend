/****************************************************************

   Solution : NovaTend

   Project : z-encryption-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"
#include <DllID.h>

// z-encryption-01.dll definition structure
DLL_COMMON_DEFINITION zEncryptionDllDefinition =
{
	Z_ENCRYPTION_DLL_ID,
	0x00010000,
	"z-encryption-01.dll - library responsible for encryption data",
	12,
	{Z_HOST_SERVER_ID, Z_HUB_SERVER_ID, Z_DESKTOP_SERVER_ID,
	 Z_CONTENT_DLL_ID, Z_WRITE_LOG_DLL_ID, Z_LICENSE_MAN_DLL_ID, 
	 Z_SYNC_DLL_ID, Z_SET_MAN_DLL_ID, Z_VALIDATE_RESPONSE_DLL_ID, 
	 Z_AUTH_WCP_DLL_ID, Z_CMDHIST_DLL_ID, Z_UPDATE_SRV_ID}
};

// Entry point to z-encryption-01.dll
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

