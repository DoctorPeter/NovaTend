/****************************************************************

   Solution : NovaTend

   Project : z-exceptions-01.dll

   Module : ExceptionHandler.h

   Description :  this module defines interface of abstract 
				  class ExceptionHandler

*****************************************************************/

#include <LogWriter.h>

#ifdef ZEXCEPTIONS01_EXPORTS
#define EXCEPTIONHANDLER_API __declspec(dllexport)
#else
#define EXCEPTIONHANDLER_API __declspec(dllimport)
#endif

#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

/****************************************************************

   Class : ExceptionHandler

   Description : abstract class. Defines general structure 
				 of exception handler

*****************************************************************/
class EXCEPTIONHANDLER_API ExceptionHandler : public SystemBase
{
	protected:
		
		// Set global exception filter
		virtual void * SetExceptionFilter(void * exceptionFilter) = 0;
		
		// Log writer instance
		LogWriter * logWriter;

	public:
		
		// constructor
		ExceptionHandler(unsigned long dllUserID, LogWriter * logWriter);

		// destructor
		virtual ~ExceptionHandler(void);

		// Write message to log-file
		int WriteToLog(char * message);
};

#endif