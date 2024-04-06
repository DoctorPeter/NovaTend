/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : SystemBase.cpp

   Description :  this module implements methods of 
				  class SystemBase

*****************************************************************/

#include "stdafx.h"
#include <windows.h>

#include "SystemBase.h"

/****************************************************************

   Class : SystemBase

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				dllDefinition - pointer to DLL 
								definition structure


*****************************************************************/
SystemBase :: SystemBase(unsigned long dllUserID, PDLL_COMMON_DEFINITION dllDefinition)
{
	this -> dllUserID = dllUserID;

	CheckDllUser(dllUserID, dllDefinition);

	randomGenerator = new RandomGenerator();
}

/****************************************************************

   Class : SystemBase

   Method : Destructor

*****************************************************************/
SystemBase :: ~SystemBase(void)
{
	delete randomGenerator;
}

/****************************************************************

   Class : SystemBase

   Method :  CheckDllUser

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				dllDefinition - pointer to DLL 
								definition structure
	
	Return: result of DLL user checking
			
	Description : Check the DLL user

*****************************************************************/
unsigned short SystemBase :: CheckDllUser(unsigned long dllUserID, PDLL_COMMON_DEFINITION dllDefinition)
{
	DllUserChecker * dllUserChecker = new DllUserChecker(dllUserID, dllDefinition);
	dllUserCheckResult = dllUserChecker -> CheckUser();
	delete dllUserChecker;
	return dllUserCheckResult;
}

/****************************************************************

   Class : SystemBase

   Method :  GetOSVersion

   Returns : OS version code

   Description : Get OS Version

*****************************************************************/
int SystemBase :: GetOSVersion(void)
{
	OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);

	unsigned char major, minor, bits;

	major = osvi.dwMajorVersion;
	minor = osvi.dwMinorVersion;

	/*typedef BOOL (WINAPI *IW64PFP)(HANDLE, BOOL *);
	IW64PFP IW64P = (IW64PFP)GetProcAddress(GetModuleHandleA("kernel32"), "IsWow64Process");
    if (IW64P != NULL)
    {
        BOOL bStatus = FALSE;
        IW64P(GetCurrentProcess(), &bStatus);
        *bits = (bStatus) ? 64 : 32;
    }*/

	if ((sizeof(void *)) == 4)
		bits = 32;
	else
		if ((sizeof(void *)) == 8)
			bits = 64;
		else
			bits = 0;

	int osVer = OS_UNKNOWN;
	
	if ((major == 6) && (minor == 1) && (bits == 32))
		osVer = OS_WIN_7_X32;

	if ((major == 6) && (minor == 1) && (bits == 64))
		osVer = OS_WIN_7_X64;

	if ((major == 6) && ((minor == 2) || (minor == 3)) && (bits == 32))
		osVer = OS_WIN_8_X32;

	if ((major == 6) && ((minor == 2) || (minor == 3)) && (bits == 64))
		osVer = OS_WIN_8_X64;

	if ((major == 10) && ((minor == 0) || (minor == 1)) && (bits == 32))
		osVer = OS_WIN_10_X32;

	if ((major == 10) && ((minor == 0) || (minor == 1)) && (bits == 64))
		osVer = OS_WIN_10_X64;

	return osVer;
}

/****************************************************************

   Class : SystemBase

   Method :  GetOSVersion

   Parameters :
			Output :
				osVersionStr - buffer for text representation
							   of OS version code

   Returns : OS version in text

   Description : Convert OS Version code to string

*****************************************************************/
char * SystemBase :: GetOSVersion(char * osVersionStr)
{
	return GetOSVersion(GetOSVersion(), osVersionStr);
}

/****************************************************************

   Class : SystemBase

   Method :  GetOSVersion

   Parameters :
			Input :
				osVersion - os version code

			Output :
				osVersionStr - buffer for text representation
							   of OS version code

   Returns : OS version in text

   Description : Convert OS Version code to string

*****************************************************************/
char * SystemBase :: GetOSVersion(int osVersion, char * osVersionStr)
{
	if (osVersionStr)
	{
		switch (osVersion)
		{
			case OS_UNKNOWN :
			{
				strcpy(osVersionStr, "OS_UNKNOWN");
				break;
			}

			case OS_WIN_7_X32 :
			{
				strcpy(osVersionStr, "OS_WIN_7_X32");
				break;
			}

			case OS_WIN_7_X64 :
			{
				strcpy(osVersionStr, "OS_WIN_7_X64");
				break;
			}

			case OS_WIN_8_X32 :
			{
				strcpy(osVersionStr, "OS_WIN_8_X32");
				break;
			}

			case OS_WIN_8_X64 :
			{
				strcpy(osVersionStr, "OS_WIN_8_X64");
				break;
			}

			case OS_WIN_10_X32 :
			{
				strcpy(osVersionStr, "OS_WIN_10_X32");
				break;
			}

			case OS_WIN_10_X64 :
			{
				strcpy(osVersionStr, "OS_WIN_10_X64");
				break;
			}
		}
	}

	return osVersionStr;
}


/****************************************************************

   Class : SystemBase

   Method : Rand

   Returns : random number

   Description: Get random number in range [0 - MAX_RAND_VALUE]

*****************************************************************/
unsigned int SystemBase :: Rand(void)
{
	return randomGenerator -> GenerateRandomValue();
}
