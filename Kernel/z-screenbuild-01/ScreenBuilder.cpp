/****************************************************************

   Solution : NovaTend

   Project : z-screenbuild-01.dll

   Module : ScreenBuilder.cpp

   Description :  this module implements methods of
				  class ScreenBuilder

*****************************************************************/

#include "stdafx.h"
#include "ScreenBuilder.h"

// z-screenbuild-01.dll structure definition
extern DLL_COMMON_DEFINITION zScreenBuildDllDefinition;

/****************************************************************

   Class : ScreenBuilder

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
ScreenBuilder :: ScreenBuilder(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zScreenBuildDllDefinition)
{
	this -> logWriter = logWriter;
		
	screenHeight = 0;
	screenWidth = 0;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("ScreenBuilder : constructor");
	#endif
}

/****************************************************************

   Class : ScreenBuilder

   Method : Destructor

*****************************************************************/
ScreenBuilder :: ~ScreenBuilder(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("ScreenBuilder : destructor");
	#endif
}

/****************************************************************

   Class : ScreenBuilder

   Method : LoadScreenSize

   Description : Load size of screen

*****************************************************************/
void ScreenBuilder :: LoadScreenSize(void)
{
	try
	{
		DEVMODE devMode;
		devMode.dmSize = sizeof(devMode);
	
		// Get display settings
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);

		screenHeight = devMode.dmPelsHeight;
		screenWidth = devMode.dmPelsWidth;
	}
	catch(...)
	{
		screenHeight = 0;
		screenWidth = 0;
	}
}

/****************************************************************

   Class : ScreenBuilder

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int ScreenBuilder :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}