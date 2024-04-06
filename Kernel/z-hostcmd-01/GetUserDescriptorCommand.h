/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetUserDescriptorCommand.h

   Description :  this module defines interface of
				  class GetUserDescriptorCommand

*****************************************************************/

#include <Command.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define GET_USER_DESCRIPTOR_CMD_API __declspec(dllexport)
#else
#define GET_USER_DESCRIPTOR_CMD_API __declspec(dllimport)
#endif

#ifndef GET_USER_DESCRIPTOR_CMD_H
#define GET_USER_DESCRIPTOR_CMD_H

/****************************************************************

   Class : GetUserDescriptorCommand

   Description : Get user descriptor

*****************************************************************/
class GET_USER_DESCRIPTOR_CMD_API GetUserDescriptorCommand : public Command
{
	private:
		
		// Content manager instance
		ContentManager * contentManager;

		// Get user descriptor by user ID
		PUSER_DESCRIPTOR GetUserDescriptor(int userID);

		// Get user descriptor by encrypted user name
		PUSER_DESCRIPTOR GetUserDescriptor(unsigned char * userName, int userNameLen);

		// Get user descriptor by encrypted user name and authentication system ID
		PUSER_DESCRIPTOR GetUserDescriptor(unsigned char * userName, int userNameLen, int authSystemID);

		// Delete user descriptor
		PUSER_DESCRIPTOR DeleteUserDescriptor(PUSER_DESCRIPTOR pUser);

	public:

		// Constructor
		GetUserDescriptorCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetUserDescriptorCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif