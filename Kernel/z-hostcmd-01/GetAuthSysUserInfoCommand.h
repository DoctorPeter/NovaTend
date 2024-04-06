/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetAuthSysUserInfoCommand.h

   Description :  this module defines interface of
				  class GetAuthSysUserInfoCommand

*****************************************************************/

#include <Command.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define GET_AUTH_SYS_USER_INFO_CMD_API __declspec(dllexport)
#else
#define GET_AUTH_SYS_USER_INFO_CMD_API __declspec(dllimport)
#endif

#ifndef GET_AUTH_SYS_USER_INFO_CMD_H
#define GET_AUTH_SYS_USER_INFO_CMD_H

/****************************************************************

   Class : GetAuthSysUserInfoCommand

   Description : Get user info of some authentication system

*****************************************************************/
class GET_AUTH_SYS_USER_INFO_CMD_API GetAuthSysUserInfoCommand : public Command
{
	public:

		// Constructor
		GetAuthSysUserInfoCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetAuthSysUserInfoCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif