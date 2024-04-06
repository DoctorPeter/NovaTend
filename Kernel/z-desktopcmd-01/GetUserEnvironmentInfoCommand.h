/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : GetUserEnvironmentInfoCommand.h

   Description :  this module defines interface of
				  class GetUserEnvironmentInfoCommand

*****************************************************************/

#include <Command.h>


#ifdef ZDESKTOPCMD01_EXPORTS
#define USER_ENV_INFO_CMD_API __declspec(dllexport)
#else
#define USER_ENV_INFO_CMD_API __declspec(dllimport)
#endif

#ifndef USER_ENV_INFO_CMD_H
#define USER_ENV_INFO_CMD_H

/****************************************************************

   Class : GetUserEnvironmentInfoCommand

   Description : Get name of foreground window.

				This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class USER_ENV_INFO_CMD_API GetUserEnvironmentInfoCommand : public Command
{
	private:
		
		// Get downtime
		int GetUserDowntime(void);

		// Get active application name
		int GetActiveAppName(char * activeAppName);

		// Get user applications list
		int GetAppList(PENVIROMENT_INFO_CONTAINER envContainer);
				
	public:

		// Constructor
		GetUserEnvironmentInfoCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetUserEnvironmentInfoCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif