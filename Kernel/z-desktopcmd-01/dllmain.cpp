/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/
#include "stdafx.h"


#include <DllID.h>

// z-desktopcmd-01.dll definition structure
DLL_COMMON_DEFINITION zDesktopCmdDllDefinition =
{
	Z_DESKTOPCMD_DLL_ID,
	0x00010000,
	"z-desktopcmd-01.dll - provides general interface for executing commands by DESKTOP server",
	1,
	{Z_DESKTOP_SERVER_ID}
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

