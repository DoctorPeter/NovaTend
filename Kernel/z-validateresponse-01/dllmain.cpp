/****************************************************************

   Solution : NovaTend

   Project : z-validateresponse-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"
#include <DllID.h>

// z-validateresponse-01.dll definition structure
DLL_COMMON_DEFINITION zValidateResponseDllDefinition =
{
	Z_VALIDATE_RESPONSE_DLL_ID,
	0x00010000,
	"z-validateresponse-01.dll - components that is called to process and validate user provided info",
	1,
	{Z_HOSTCMD_DLL_ID}
};

// Entry point to z-validateresponse-01.dll 
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

