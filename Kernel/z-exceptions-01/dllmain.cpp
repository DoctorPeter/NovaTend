/****************************************************************

   Solution : NovaTend

   Project : z-exceptions-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-exceptions-01.dll definition structure
DLL_COMMON_DEFINITION zExceptionsDllDefinition =
{
	Z_EXCEPTIONS_DLL_ID,
	0x00010000,
	"z-exceptions-01.dll - library responsible for handling errors",
	3,
	{Z_WIN_CRED_PROV_DLL_ID, Z_WIN_SERVICE_DLL_ID, Z_DESKTOP_SERVER_ID}
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

