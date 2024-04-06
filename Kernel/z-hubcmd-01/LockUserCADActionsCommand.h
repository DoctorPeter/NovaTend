/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : LockUserCADActionsCommand.h

   Description :  this module defines interface of
				  class LockUserCADActionsCommand

*****************************************************************/

#include <Command.h>


#ifdef ZHUBCMD01_EXPORTS
#define LOCK_CAD_CMD_API __declspec(dllexport)
#else
#define LOCK_CAD_CMD_API __declspec(dllimport)
#endif

#ifndef LOCK_CAD_CMD_H
#define LOCK_CAD_CMD_H

/****************************************************************

   Class : LockUserCADActionsCommand

   Description : Lock/unlock user actions by
				 pressing Ctrl + Alt + Del.

*****************************************************************/
class LOCK_CAD_CMD_API LockUserCADActionsCommand : public Command
{
	private:
		
		// Lock/Unlock CTRL + ALT + DEL
		bool LockCtrlAltDelActions(bool lock, char * userName);

	public:

		// Constructor
		LockUserCADActionsCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~LockUserCADActionsCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif