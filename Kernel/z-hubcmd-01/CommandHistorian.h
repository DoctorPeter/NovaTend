/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : CommandHistorian.h

   Description :  this module defines interface of
				  class CommandHistorian

*****************************************************************/

#include "stdafx.h"

#include "CommandManager.h"
#include <ThreadController.h>
#include <LogWriter.h>

#ifdef ZHUBCMD01_EXPORTS
#define COMMAND_HISTORIAN_API __declspec(dllexport)
#else
#define COMMAND_HISTORIAN_API __declspec(dllimport)
#endif

#ifndef COMMAND_HISTORIAN_H
#define COMMAND_HISTORIAN_H

/****************************************************************

   Class : CommandHistorian

   Description : Responsible for management of
				 periodicaly writing of command history to
				 archive.

*****************************************************************/
class COMMAND_HISTORIAN_API CommandHistorian : public ThreadController
{
	protected:

		// Log writer instance
		LogWriter * logWriter;
		
		// Command manager instance
		CommandManager * commandManager;

		// Write to history
		void WriteToHistory(void);

		// Main rountine
		virtual void ControllerEntry(void);

		// Check periodic flag
		virtual bool CheckPeriodicFlag(void);

		// Check period
		virtual bool CheckPeriod(void);

	public:

		// Constructor
		CommandHistorian(unsigned long dllUserID, CommandManager * commandManager, LogWriter * logWriter);

		// Desctructor
		virtual ~CommandHistorian(void);

		// Write message to LOG-file
		int WriteToLog(char * message);
};

#endif