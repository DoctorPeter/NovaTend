/****************************************************************

   Solution : NovaTend

   Project : z-dbconnect-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"
#include <DllID.h>

// z-dbconnect-01.dll definition structure
DLL_COMMON_DEFINITION zDBConnectDefinition =
{
	Z_DB_CONNECT_DLL_ID,
	0x00010000,
	"z-dbconnect-01.dll - library responsible for databes asscess",
	6,
	{Z_CONTENT_DLL_ID, Z_VALIDATE_RESPONSE_DLL_ID, Z_LICENSE_MAN_DLL_ID, Z_SYNC_DLL_ID, Z_SCHEDULER_DLL_ID, Z_CMDHIST_DLL_ID}
};

// Entry point to z-dbconnect-01.dll
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

