/****************************************************************

   Solution : NovaTend

   Project : z-setman-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-setman-01.dll definition structure
DLL_COMMON_DEFINITION zSetmanDllDefinition =
{
	Z_SET_MAN_DLL_ID,
	0x00010000,
	"z-setman-01.dll - responsible for settings management",
	16,
	{Z_CONTENT_DLL_ID, Z_HOSTCMD_DLL_ID, Z_HOST_SERVER_ID, 
	 Z_HUBCMD_DLL_ID, Z_HUB_SERVER_ID, Z_LICENSE_MAN_DLL_ID, 
	 Z_SYNC_DLL_ID, Z_VALIDATE_RESPONSE_DLL_ID, Z_DESKTOP_SERVER_ID, 
	 Z_DESKTOPCMD_DLL_ID, Z_AUTH_WCP_DLL_ID, Z_WIN_CRED_PROV_DLL_ID, 
	 Z_CMDHIST_DLL_ID, Z_UPDATE_SRV_ID, Z_SCHEDULER_DLL_ID,
	 Z_SET_MAN_DLL_ID}
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

