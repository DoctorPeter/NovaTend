/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetAuthSystemIDCommand.h

   Description :  this module defines interface of
				  class GetAuthSystemIDCommand

*****************************************************************/

#include <Command.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define GET_AUTH_SYS_ID_CMD_API __declspec(dllexport)
#else
#define GET_AUTH_SYS_ID_CMD_API __declspec(dllimport)
#endif

#ifndef GET_AUTH_SYS_ID_CMD_H
#define GET_AUTH_SYS_ID_CMD_H

/****************************************************************

   Class : GetAuthSystemIDCommand

   Description : Get authentication system ID

*****************************************************************/
class GET_AUTH_SYS_ID_CMD_API GetAuthSystemIDCommand : public Command
{
	private:
				
		// Get authentication system ID
		int GetAuthSystemID(unsigned char * encSystemSettings, int encSystemSettingsLen, int authSystemType);

	public:

		// Constructor
		GetAuthSystemIDCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetAuthSystemIDCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif