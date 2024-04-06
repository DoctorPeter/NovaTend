/****************************************************************

   Solution : NovaTend

   Project : z-exceptions-01.dll

   Module : WinExceptionHandler.h

   Description :  this module defines interface of abstract 
				  class WinExceptionHandler. This class 
				  designed for Windows OS.

*****************************************************************/

#include "ExceptionHandler.h"

#ifndef WINEXCEPTIONHANDLER_H
#define WINEXCEPTIONHANDLER_H

/****************************************************************

   Class : WinExceptionHandler

   Description : Defines general structure of 
				 Windows global exception handler

				 This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class EXCEPTIONHANDLER_API WinExceptionHandler : public ExceptionHandler
{
	private:
		
		// Pointer to old global exception filter
		LPTOP_LEVEL_EXCEPTION_FILTER oldExceptionFilter;
	
		// New global exception filter callback function
		friend LONG WINAPI MainExceptionFilter(EXCEPTION_POINTERS *exceptionInfo);

	protected:

		// Set global exception filter
		void * SetExceptionFilter(void * exceptionFilter);

	public:

		// constructor
		WinExceptionHandler(unsigned long dllUserID, LogWriter * logWriter);

		//destructor
		virtual ~WinExceptionHandler(void);

		// Get exception description by exception code
		LPCSTR GetExceptionName(DWORD code);

		// Get address and name of module which throw exception
		HMODULE GetExceptionModule(LPVOID address, char * moduleName);
};


#endif