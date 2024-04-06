/****************************************************************

   Solution : NovaTend

   Project : z-srvsrv-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-srvsrv-01.dll definition structure
DLL_COMMON_DEFINITION zServerServiceDllDefinition =
{
	Z_SERVER_SERVICE_DLL_ID,
	0x00010000,
	"z-srvsrv-01.dll - defines general structure of server service",
	3,
	{Z_HOST_SERVER_ID, Z_HUB_SERVER_ID}
};

HMODULE hDLL;

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
	case DLL_PROCESS_DETACH: hDLL = hModule;
							 break;
	}
	return TRUE;
}

