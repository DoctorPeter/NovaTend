/****************************************************************

   Solution : NovaTend

   Project : z-authwcp-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-authwcp-01.dll definition structure
DLL_COMMON_DEFINITION zAuthWCPDllDefinition =
{
	Z_AUTH_WCP_DLL_ID,
	0x00010000,
	"z-authwcp-01.dll - responsible for management of WCP authentication",
	1,
	{Z_WIN_CRED_PROV_DLL_ID}
};

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

