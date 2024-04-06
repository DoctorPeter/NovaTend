/****************************************************************

   Solution : NovaTend

   Project : z-authclient-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-authclient-01.dll definition structure
DLL_COMMON_DEFINITION zAuthClientDllDefinition =
{
	Z_AUTH_CLIENT_DLL_ID,
	0x00010000,
	"z-authclient-01.dll - provides functions of authenticate process management for application client",
	3,
	{Z_WIN_CRED_PROV_DLL_ID, Z_AUTH_WCP_DLL_ID, Z_UPDATE_SRV_ID}
};


// Entry point to z-authclient-01.dll
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

