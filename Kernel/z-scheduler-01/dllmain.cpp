/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/
#include "stdafx.h"

#include <SystemBase.h>

// z-scheduler-01.dll definition structure
DLL_COMMON_DEFINITION zSchedulerDllDefinition =
{
	Z_SCHEDULER_DLL_ID,
	0x00010000,
	"z-scheduler-01.dll - system action scheduler",
	3,
	{Z_CONTENT_DLL_ID, Z_VALIDATE_RESPONSE_DLL_ID, Z_HOSTCMD_DLL_ID}
};


// Contiions records parser critical section
CriticalSection * parserGuard = NULL;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			parserGuard = new CriticalSection();
			break;
		}

	case DLL_PROCESS_DETACH:
		{
			delete parserGuard;
			break;
		}

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

