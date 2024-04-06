/****************************************************************

   Solution : NovaTend

   Project : z-sms-01.dll

   Module : dllmain.cpp

   Description :  Defines the entry point for the DLL application.

*****************************************************************/

#include "stdafx.h"

#include <DllID.h>

// z-sms-01.dll definition structure
DLL_COMMON_DEFINITION zSMSDllDefinition =
{
	Z_SMS_DLL_ID,
	0x00010000,
	"z-sms-01.dll - responsible for SMS sending",
	1,
	{Z_HOSTCMD_DLL_ID}
};

// Global DLL handler instance
HMODULE g_hinst;

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
	case DLL_PROCESS_DETACH: g_hinst = hModule;
		break;
	}
	return TRUE;
}

