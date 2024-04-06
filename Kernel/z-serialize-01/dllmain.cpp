/****************************************************************

   Solution : NovaTend

   Project : z-serialize-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/
#include "stdafx.h"


#include <DllID.h>

// z-serialize-01.dll definition structure
DLL_COMMON_DEFINITION zSerializeDllDefinition =
{
	Z_SERIALIZE_DLL_ID,
	0x00010000,
	"z-serialize-01.dll - provides functions of data serialization",
	10,
	{Z_COMMAND_DLL_ID, Z_DESKTOPCMD_DLL_ID, Z_HOSTCMD_DLL_ID, 
	 Z_HUBCMD_DLL_ID, Z_HOST_SERVER_ID, Z_HUB_SERVER_ID, 
	 Z_IPC_CLIENT_DLL_ID, Z_IPC_SERVER_DLL_ID, Z_AUTH_CLIENT_DLL_ID, Z_CMDHIST_DLL_ID}
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

