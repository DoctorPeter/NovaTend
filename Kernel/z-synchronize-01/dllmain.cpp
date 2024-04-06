/****************************************************************

   Solution : NovaTend

   Project : z-synchronize-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"
#include <DllID.h>

// z-synchronize-01.dll definition structure
DLL_COMMON_DEFINITION zSynchronizeDllDefinition =
{
	Z_SYNC_DLL_ID,
	0x00010000,
	"z-synchronize-01.dll - responsible for user accounts synchronization",
	2,
	{Z_HOST_SERVER_ID, Z_HOSTCMD_DLL_ID}
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

