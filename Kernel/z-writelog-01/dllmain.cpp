/****************************************************************

   Solution : NovaTend

   Project : z-writelog-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-writelog-01.dll definition structure
DLL_COMMON_DEFINITION zWriteLogDllDefinition =
{
	Z_WRITE_LOG_DLL_ID,
	0x00010000,
	"z-writelog-01.dll - responsible for writing log file of all events and supporting \
	                 information which would help to trace back on what occurred",
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

