/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ValidateUserAccountCommand.h

   Description :  this module defines interface of
				  class ValidateUserAccountCommand

*****************************************************************/

#include <Command.h>

#ifdef ZHOSTCMD01_EXPORTS
#define VALIDATE_ACCOUNT_CMD_API __declspec(dllexport)
#else
#define VALIDATE_ACCOUNT_CMD_API __declspec(dllimport)
#endif

#ifndef VALIDATE_ACCOUNT_CMD_H
#define VALIDATE_ACCOUNT_CMD_H

/****************************************************************

   Class : ValidateUserAccountCommand

   Description : Validate user account

*****************************************************************/
class VALIDATE_ACCOUNT_CMD_API ValidateUserAccountCommand : public Command
{
	private:
				
		// Validate user account
		int ValidateUserAccount(unsigned char * userName, int userNameLen, unsigned char * userPassword, int userPasswordLen, int authSystemID);

	public:

		// Constructor
		ValidateUserAccountCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~ValidateUserAccountCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif