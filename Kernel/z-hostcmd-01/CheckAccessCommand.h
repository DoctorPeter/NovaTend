/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckAccessCommand.h

   Description :  this module defines interface of
				  class CheckAccessCommand

*****************************************************************/

#include <Command.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define CHECK_ACCESS_CMD_API __declspec(dllexport)
#else
#define CHECK_ACCESS_CMD_API __declspec(dllimport)
#endif

#ifndef CHECK_ACCESS_CMD_H
#define CHECK_ACCESS_CMD_H

/****************************************************************

   Class : CheckAccessCommand

   Description : Check access to the host server DB

*****************************************************************/
class CHECK_ACCESS_CMD_API CheckAccessCommand : public Command
{
	private:
		
		// Content manager instance
		ContentManager * contentManager;

		// Check access to the server
		bool CheckServerAccess(void);

	public:

		// Constructor
		CheckAccessCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~CheckAccessCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif