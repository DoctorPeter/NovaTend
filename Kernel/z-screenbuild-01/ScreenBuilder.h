/****************************************************************

   Solution : NovaTend

   Project : z-screenbuild-01.dll

   Module : ScreenBuilder.h

   Description :  this module defines interface of
				  class ScreenBuilder

*****************************************************************/

#include "stdafx.h"

#include <LogWriter.h>
#include <ContentDataDef.h>


#ifdef ZSCREENBUILD01_EXPORTS
#define SCREENBUILDER_API __declspec(dllexport)
#else
#define SCREENBUILDER_API __declspec(dllimport)
#endif

#ifndef SCREENBUILDER_H
#define SCREENBUILDER_H

/****************************************************************

   Class : ScreenBuilder

   Description : Abstract class. Designed as general structure of 
				 class that responsible for creation structure of 
				 user sing in screen 

*****************************************************************/
class SCREENBUILDER_API ScreenBuilder : public SystemBase
{
	protected:
				
		// Log writer instance
		LogWriter * logWriter;
				
	public:

		// Screen width
		int screenWidth;

		// Screen height
		int screenHeight;
		
		
		// Constructor
		ScreenBuilder(unsigned long dllUserID, LogWriter * logWriter);
		
		// Destructor
		virtual ~ScreenBuilder(void);

		// User screen builder
		virtual void * CreateUserScreen(PPRESET_CONTAINER content) = NULL;
		
		// Load screen size
		void LoadScreenSize(void);

		// Write message to log-file
		int WriteToLog(char * message);
};

#endif