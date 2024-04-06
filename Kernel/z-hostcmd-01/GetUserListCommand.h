/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetUserListCommand.h

   Description :  this module defines interface of
				  class GetUserListCommand

*****************************************************************/

#include <Command.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define GET_USER_LIST_CMD_API __declspec(dllexport)
#else
#define GET_USER_LIST_CMD_API __declspec(dllimport)
#endif

#ifndef GET_USER_LIST_CMD_H
#define GET_USER_LIST_CMD_H

/****************************************************************

   Class : GetUserListCommand

   Description : Get list of simple user descriptors

*****************************************************************/
class GET_USER_LIST_CMD_H GetUserListCommand : public Command
{
	private:

		// Content manager instance
		ContentManager * contentManager;

		// Get list of users
		PUSER_LIST GetUserListContainer(void);

		// Delete list of users
		PUSER_LIST DeleteUserListContainer(PUSER_LIST userList);

	public:

		// Constructor
		GetUserListCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetUserListCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif