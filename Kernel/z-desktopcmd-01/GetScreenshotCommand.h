/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : GetScreenshotCommand.h

   Description :  this module defines interface of
				  class GetScreenshotCommand

*****************************************************************/

#include <Command.h>

#ifdef ZDESKTOPCMD01_EXPORTS
#define SCREENSHOT_CMD_API __declspec(dllexport)
#else
#define SCREENSHOT_CMD_API __declspec(dllimport)
#endif

#ifndef SCREENSHOT_CMD_H
#define SCREENSHOT_CMD_H

/****************************************************************

   Class : GetScreenshotCommand

   Description : Get screenshot picture.

				This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class SCREENSHOT_CMD_API GetScreenshotCommand : public Command
{
	private:
		
		// Get screenshot (BMP)
		char * ScreenToBmp24Stretch(BYTE bZoomOut, int * resBufSize);

	public:

		// Constructor
		GetScreenshotCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetScreenshotCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif