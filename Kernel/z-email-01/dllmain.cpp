/****************************************************************

   Solution : NovaTend

   Project : z-email-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"
#include <DllID.h>

// z-email-01.dll definition structure
DLL_COMMON_DEFINITION zEmailDllDefinition =
{
	Z_EMAIL_DLL_ID,
	0x00010000,
	"z-email-01.dll - responsible for EMAIL sending",
	2,
	{Z_WRITE_LOG_DLL_ID, Z_HOSTCMD_DLL_ID}
};

// Entry point to z-content-01.dll
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

