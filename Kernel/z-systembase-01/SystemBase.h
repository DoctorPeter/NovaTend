/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : SystemBase.h

   Description :  this module defines interface of 
				  class SystemBase. This class is 
				  designed to define general structure
				  of all solution classes.

*****************************************************************/

#include "DllUserChecker.h"
#include "RandomGenerator.h"
#include "CriticalSection.h"

#ifdef ZSYSTEMBASE01_EXPORTS
#define SYSTEMBASE_API __declspec(dllexport)
#else
#define SYSTEMBASE_API __declspec(dllimport)
#endif

#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H

// OS versions list

#define OS_UNKNOWN				0

// Windows 7 (32 bits)
#define OS_WIN_7_X32			1

// Windows 7 (64 bits)
#define OS_WIN_7_X64			2

// Windows 8 (32 bits)
#define OS_WIN_8_X32			3

// Windows 8 (64 bits)
#define OS_WIN_8_X64			4

// Windows 10 (32 bits)
#define OS_WIN_10_X32			5

// Windows 10 (64 bits)
#define OS_WIN_10_X64			6


/****************************************************************

   Class : SystemBase

   Description : parent for all solution classes.
                
*****************************************************************/
class SYSTEMBASE_API SystemBase	
{
	protected:
		// DLL user ID
		unsigned long dllUserID;

		// result of DLL user checking
		unsigned short dllUserCheckResult;

	private:
		
		// Random generator instance
		RandomGenerator * randomGenerator;

		// Check the DLL user
		unsigned short CheckDllUser(unsigned long dllUserID, PDLL_COMMON_DEFINITION dllDefinition);

	public:
		// SystemBase constructor
		SystemBase(unsigned long dllUserID, PDLL_COMMON_DEFINITION dllDefinition);
		
		// SystemBase destructor
		virtual ~SystemBase(void);

		// Get OS Version
		int GetOSVersion(void);

		// Get OS Version
		char * GetOSVersion(char * osVersionStr);

		// Get OS Version
		static char * GetOSVersion(int osVersion, char * osVersionStr);

		// Generate random number
		unsigned int Rand(void);
};

#endif