/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : DllUserChecker.h

   Description :  this module defines interface of 
				  class DllUserChecker. This class 
				  is designed to test the legal use 
				  of each DLL.

*****************************************************************/

#include "DllID.h"

#ifndef DLLUSERCHECKER_H
#define DLLUSERCHECKER_H

/****************************************************************

   Class : DllUserChecker

   Description : test the legal use of each DLL

*****************************************************************/
class DllUserChecker
{
	private:
		
		// DLL user ID
		unsigned long int dllUser;

		// DLL definition structure
		PDLL_COMMON_DEFINITION dllDefinition;

		// Set DllUserChecker parameters
		void SetParams(DLL_ID dllUser, PDLL_COMMON_DEFINITION dllDefinition);

	public:
		// DllUserChecker constructor
		DllUserChecker(DLL_ID dllUser, PDLL_COMMON_DEFINITION dllDefinition);

		// Check some DLL user
		unsigned short CheckUser(void);
};

#endif