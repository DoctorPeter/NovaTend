/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckProgramsCommand.h

   Description :  this module defines interface of
				  class CheckProgramsCommand

*****************************************************************/

#include <Command.h>
#include <SerializationDef.h>

#ifdef ZHOSTCMD01_EXPORTS
#define CHECK_PROGRAMS_CMD_API __declspec(dllexport)
#else
#define CHECK_PROGRAMS_CMD_API __declspec(dllimport)
#endif

#ifndef CHECK_PROGRAMS_CMD_H
#define CHECK_PROGRAMS_CMD_H

/****************************************************************

   Class : CheckProgramsCommand

   Description : Check program list and deny some programs

*****************************************************************/
class CHECK_PROGRAMS_CMD_API CheckProgramsCommand : public Command
{
	private:

		// Check programs
		void CheckProgramsInList(int userID, char * compName, PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList);

		// Delete program list
		PCONTROL_PROGRAM_INFO_CONTAINER_LIST DeleteProgramInfoContainerList(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList);
	public:

		// Constructor
		CheckProgramsCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~CheckProgramsCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif