/****************************************************************

   Solution : NovaTend

   Project : z-licenseman-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-licenseman-01.dll definition structure
DLL_COMMON_DEFINITION zLicenseManDllDefinition =
{
	Z_LICENSE_MAN_DLL_ID,
	0x00010000,
	"z-licenseman-01.dll - responsible for licensing management",
	2,
	{Z_HOSTCMD_DLL_ID, Z_VALIDATE_RESPONSE_DLL_ID}
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

