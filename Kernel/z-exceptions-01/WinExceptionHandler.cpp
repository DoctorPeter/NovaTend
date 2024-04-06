/****************************************************************

   Solution : NovaTend

   Project : z-exceptions-01.dll

   Module : WinExceptionHandler.cpp

   Description :  this module implements methods of 
				  class WinExceptionHandler

*****************************************************************/

#include "stdafx.h"
#include "WinExceptionHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>
#include <Shlwapi.h>

// Maximum size of module handlers list
#define MODULE_LIST_SIZE 1024

// self pointer
WinExceptionHandler * _this = NULL;

/****************************************************************

   Class : WinExceptionHandler

   Method :  GetExceptionName

   Parameters :
			Input : 
				code - exception code

	Return: exception description string
			
	Description : Get exception description by exception code

*****************************************************************/
LPCSTR WinExceptionHandler :: GetExceptionName(DWORD code)  
{  
	switch(code)  
	{  
		
		// Access violation exception
		case EXCEPTION_ACCESS_VIOLATION				: return "Access violation";

		// Datatype misaligment exception
		case EXCEPTION_DATATYPE_MISALIGNMENT		: return "Datatype misaligment";
		
		// Breakpoint exception
		case EXCEPTION_BREAKPOINT					: return "Breakpoint";

		// Single step exception
		case EXCEPTION_SINGLE_STEP					: return "Single step";
		
		// Array bounds exceeded exception
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED		: return "Array bounds exceeded";

		// Abnormal float operand exception
		case EXCEPTION_FLT_DENORMAL_OPERAND			: return "Abnormal float operand";

		// Float argument division by zero exception
		case EXCEPTION_FLT_DIVIDE_BY_ZERO			: return "Float argument division by zero";

		// Inexact float result exception
		case EXCEPTION_FLT_INEXACT_RESULT			: return "Inexact float result";

		// Invalid float operation exception
		case EXCEPTION_FLT_INVALID_OPERATION		: return "Invalid float operation";	  

		// Float overflow exception
		case EXCEPTION_FLT_OVERFLOW					: return "Float overflow";	  	  

		// Float stack check exception
 		case EXCEPTION_FLT_STACK_CHECK				: return "Float stack check";	  	  

		// Float underflow exception
 		case EXCEPTION_FLT_UNDERFLOW				: return "Float underflow";	  	  

		// Integer argument division by zero exception
		case EXCEPTION_INT_DIVIDE_BY_ZERO			: return "Integer argument division by zero";

		// Integer overflow exception
 		case EXCEPTION_INT_OVERFLOW					: return "Integer overflow";	  	  

		// Privileged instruction exception
 		case EXCEPTION_PRIV_INSTRUCTION				: return "Privileged instruction";	  	  

		// Error in page exception
		case EXCEPTION_IN_PAGE_ERROR				: return "Error in page";	  	  	   

		// Datatype misaligment exception
		case EXCEPTION_ILLEGAL_INSTRUCTION			: return "Illegal instruction";	  	  	   

		// Illegal instruction exception
		case EXCEPTION_NONCONTINUABLE_EXCEPTION		: return "Noncontinuable error";	  	  	   

		// Stack overflow exception
		case EXCEPTION_STACK_OVERFLOW				: return "Stack overflow";	  	  	   

		// Invalid disposition exception
		case EXCEPTION_INVALID_DISPOSITION			: return "Invalid disposition";	  	  	   

		// Page guard error exception
		case EXCEPTION_GUARD_PAGE					: return "Page guard error";	  	  	   

		// Invalid handle exception
		case EXCEPTION_INVALID_HANDLE				: return "Invalid handle";	  	  	   

		// C++ Exception
		case 0xE06D7363								: return "C++ Exception";  

		// Other exception
		default										: return "Unknown exception";  
	}  
}


/****************************************************************

   Class : WinExceptionHandler

   Method :  GetExceptionModule

   Parameters :
			Input : 
				address - address of exception
			Output :
				moduleName - name of module which throw exception

	Return: handle of module which throw exception
			
	Description : Get address and name of module which throw exception

*****************************************************************/
HMODULE WinExceptionHandler :: GetExceptionModule(LPVOID address, char * moduleName)  
{  
	// list of modules
	HMODULE moduleList[MODULE_LIST_SIZE];  
	
	// The number of bytes required to store all module handles in the moduleList
	DWORD sizeNeeded = 0;  

	if((EnumProcessModules(GetCurrentProcess(), moduleList, MODULE_LIST_SIZE, &sizeNeeded) == FALSE) || (sizeNeeded < sizeof(HMODULE))) return NULL;  
  
	// Current module index
	int curModule = -1;  

	for(int i = 0; i < (int)(sizeNeeded / sizeof(HMODULE)); i++)  
	{  
		// Validate address
		if((DWORD)moduleList[i] < (DWORD)address)  
		{  
			if(curModule == -1)  
				curModule = i;  
			else  
			{  
				if((DWORD)moduleList[curModule] < (DWORD)moduleList[i])  
					curModule = i;  
			}  
		}  
	}  
  
	if(curModule == -1) return NULL;  
  
	// Get module name
	if(!GetModuleFileNameA(moduleList[curModule], moduleName, MAX_PATH)) return NULL;
	  
	return moduleList[curModule];  
}

/****************************************************************

   Class : WinExceptionHandler

   Method : MainExceptionFilter

   Parameters :
			Input : 
				exceptionInfo - exception description
			
	Return: next action scenario
			
	Description :  New global exception filter callback function

*****************************************************************/
LONG WINAPI MainExceptionFilter(EXCEPTION_POINTERS *exceptionInfo)
{
	// Error message text
	char message[MAX_PATH + 255];  

	// Module name
	char module[MAX_PATH];  
	char * moduleName = NULL;  
	
	// Get module which throw exception
	if(_this -> GetExceptionModule(exceptionInfo -> ExceptionRecord -> ExceptionAddress, module))  
		moduleName = PathFindFileNameA(module);  
	else  
		moduleName = "Unknown module!";  
  
	// Prepare error message
	sprintf(message, "Windows exception handler : In module %s has occurred exception! \n Exception code : %X \n Excecption address : %X \n Exception description : %s",
	   				 moduleName, 
					 exceptionInfo -> ExceptionRecord -> ExceptionCode,
					 exceptionInfo -> ExceptionRecord -> ExceptionAddress,
					 _this -> GetExceptionName(exceptionInfo -> ExceptionRecord -> ExceptionCode));

	// Write error message to log-file
	if (strcmp(_strlwr(moduleName), "z-writelog-01.dll"))
		_this -> WriteToLog(message);

	// Show message to user
	//MessageBoxA(NULL, message, "ERROR", MB_OK);
		
	// Return from UnhandledExceptionFilter and execute 
	// the associated exception handler. This usually 
	// results in process termination.
	return EXCEPTION_EXECUTE_HANDLER;  
}

/****************************************************************

   Class : WinExceptionHandler

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
WinExceptionHandler :: WinExceptionHandler(unsigned long dllUserID, LogWriter * logWriter) : ExceptionHandler(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_EXCEPTION)
		WriteToLog("WinExceptionHandler : constructor");
	#endif

	oldExceptionFilter = (LPTOP_LEVEL_EXCEPTION_FILTER)SetExceptionFilter(MainExceptionFilter);
	_this = this;
	_this += dllUserCheckResult;
}

/****************************************************************

   Class : WinExceptionHandler

   Method : Destructor

****************************************************************/
WinExceptionHandler ::	~WinExceptionHandler(void)
{
	SetExceptionFilter(oldExceptionFilter);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_EXCEPTION)
		WriteToLog("WinExceptionHandler : destructor");
	#endif
}

/****************************************************************

   Class : WinExceptionHandler

   Method : SetExceptionFilter

   Parameters :
			Input : 
				exceptionFilter - pointer to new exception filter
	
	Return: pointer to old exception filter
	
	Description :  Set global exception filter

*****************************************************************/
void * WinExceptionHandler :: SetExceptionFilter(void * exceptionFilter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_EXCEPTION)
		WriteToLog("WinExceptionHandler : installed as global exception handler");
	#endif
	
	return SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)exceptionFilter);
}