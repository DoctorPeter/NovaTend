/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetCmdHistoryCommand.h

   Description :  this module defines interface of
				  class GetCmdHistoryCommand

*****************************************************************/

#include <Command.h>
#include <CommandHistoryManager.h>

#ifdef ZHUBCMD01_EXPORTS
#define CMD_HISTORY_CMD_API __declspec(dllexport)
#else
#define CMD_HISTORY_CMD_API __declspec(dllimport)
#endif

#ifndef CMD_HISTORY_CMD_H
#define CMD_HISTORY_CMD_H

/****************************************************************

   Class : GetCmdHistoryCommand

   Description : Get command history.

*****************************************************************/
class CMD_HISTORY_CMD_API GetCmdHistoryCommand : public Command
{
	public:

		// Constructor
		GetCmdHistoryCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetCmdHistoryCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif