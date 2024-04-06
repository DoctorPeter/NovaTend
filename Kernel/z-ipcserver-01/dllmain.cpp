/****************************************************************

   Solution : NovaTend

   Project : z-ipcserver-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-ipcserver-01.dll definition structure
DLL_COMMON_DEFINITION zIPCServerDllDefinition =
{
	Z_IPC_SERVER_DLL_ID,
	0x00010000,
	"z-ipcserver-01.dll - responsible for interproccess communication. Server part",
	4,
	{Z_HOST_SERVER_ID, Z_HUB_SERVER_ID, Z_DESKTOP_SERVER_ID, Z_SERVER_SERVICE_DLL_ID}
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

