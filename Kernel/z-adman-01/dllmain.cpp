/****************************************************************

   Solution : NovaTend

   Project : z-adman-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"
#include <DllID.h>

// z-adman-01.dll definition structure
DLL_COMMON_DEFINITION zADManDllDefinition =
{
	Z_AD_MAN_DLL_ID,
	0x00010000,
	"z-adman-01.dll - responsible for AD user accounts management",
	1,
	{Z_SYNC_DLL_ID}
};

// Entry point to z-adman-01.dll
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

