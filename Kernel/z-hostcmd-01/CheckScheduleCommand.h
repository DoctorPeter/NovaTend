/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckScheduleCommand.h

   Description :  this module defines interface of
				  class CheckScheduleCommand

*****************************************************************/

#include <Command.h>

#ifdef ZHOSTCMD01_EXPORTS
#define CHECK_SCHEDULE_CMD_API __declspec(dllexport)
#else
#define CHECK_SCHEDULE_CMD_API __declspec(dllimport)
#endif

#ifndef CHECK_SCHEDULE_CMD_H
#define CHECK_SCHEDULE_CMD_H

/****************************************************************

   Class : CheckScheduleCommand

   Description : Check schedule records and get validation result

*****************************************************************/
class CHECK_SCHEDULE_CMD_API CheckScheduleCommand : public Command
{
	private:

		// Check schedule records
		int CheckSchedulerRecords(int userID, char * compName, int functionID);

	public:

		// Constructor
		CheckScheduleCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~CheckScheduleCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif