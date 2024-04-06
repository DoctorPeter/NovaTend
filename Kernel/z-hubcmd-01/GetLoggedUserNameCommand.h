/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetLoggedUserNameCommand.h

   Description :  this module defines interface of
				  class GetLoggedUserNameCommand

*****************************************************************/

#include <Command.h>


#ifdef ZHUBCMD01_EXPORTS
#define USER_NAME_CMD_API __declspec(dllexport)
#else
#define USER_NAME_CMD_API __declspec(dllimport)
#endif

#ifndef USER_NAME_CMD_H
#define USER_NAME_CMD_H

/****************************************************************

   Class : GetLoggedUserNameCommand

   Description : Get name of currently logged on user.

*****************************************************************/
class USER_NAME_CMD_API GetLoggedUserNameCommand : public Command
{
	public:

		// Constructor
		GetLoggedUserNameCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetLoggedUserNameCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif