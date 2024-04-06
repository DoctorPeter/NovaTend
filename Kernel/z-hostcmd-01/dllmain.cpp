/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/
#include "stdafx.h"


#include <DllID.h>

// z-hostcmd-01.dll definition structure
DLL_COMMON_DEFINITION zHostCmdDllDefinition =
{
	Z_HOSTCMD_DLL_ID,
	0x00010000,
	"z-hostcmd-01.dll - provides general interface for executing commands by HOST server",
	1,
	{Z_HOST_SERVER_ID}
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

