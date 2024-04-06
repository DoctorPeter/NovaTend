/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckSignInDateCommand.h

   Description :  this module defines interface of
				  class CheckSignInDateCommand

*****************************************************************/

#include <Command.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define CHECK_SIGNIN_DATE_CMD_API __declspec(dllexport)
#else
#define CHECK_SIGNIN_DATE_CMD_API __declspec(dllimport)
#endif

#ifndef CHECK_SIGNIN_DATE_CMD_H
#define CHECK_SIGNIN_DATE_CMD_H

/****************************************************************

   Class : CheckSignInDateCommand

   Description : Check user sign in date

*****************************************************************/
class CHECK_SIGNIN_DATE_CMD_API CheckSignInDateCommand : public Command
{
	private:
				
		// Is it first sign in for today for this user?
		bool FirstUserSignInToday(int userID, int authSystemID);

	public:

		// Constructor
		CheckSignInDateCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~CheckSignInDateCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif