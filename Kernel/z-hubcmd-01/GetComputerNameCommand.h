/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetComputerNameCommand.h

   Description :  this module defines interface of
				  class GetComputerNameCommand

*****************************************************************/

#include <Command.h>


#ifdef ZHUBCMD01_EXPORTS
#define COMPUTER_NAME_CMD_API __declspec(dllexport)
#else
#define COMPUTER_NAME_CMD_API __declspec(dllimport)
#endif

#ifndef COMPUTER_NAME_CMD_H
#define COMPUTER_NAME_CMD_H

/****************************************************************

   Class : GetComputerNameCommand

   Description : Get name of computer.

*****************************************************************/
class COMPUTER_NAME_CMD_API GetComputerNameCommand : public Command
{
	public:

		// Constructor
		GetComputerNameCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetComputerNameCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif