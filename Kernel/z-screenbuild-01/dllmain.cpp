/****************************************************************

   Solution : NovaTend

   Project : z-screenbuild-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/
#include "stdafx.h"

#include <DllID.h>

// z-screenbuild-01.dll structure definition
DLL_COMMON_DEFINITION zScreenBuildDllDefinition =
{
	Z_SCREEN_BUILD_DLL_ID,
	0x00010000,
	"z-screenbuild-01.dll - custom “User Sign In” screen builder",
	1,
	{Z_AUTH_WCP_DLL_ID}
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

