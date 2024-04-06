/****************************************************************

   Solution : NovaTend

   Project : z-ipcclient-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-ipcclient-01.dll definition structure
DLL_COMMON_DEFINITION zIPCClientDllDefinition =
{
	Z_IPC_CLIENT_DLL_ID,
	0x00010000,
	"z-ipcclient-01.dll - responsible for interproccess communication. Client part",
	8,
	{Z_HUBCMD_DLL_ID, Z_HUB_SERVER_ID, Z_HOSTCMD_DLL_ID, Z_HOST_SERVER_ID, Z_DESKTOPCMD_DLL_ID, Z_DESKTOP_SERVER_ID, Z_WIN_CRED_PROV_DLL_ID, Z_UPDATE_SRV_ID}
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

