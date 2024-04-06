/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : SetUserSignInDateCommand.h

   Description :  this module defines interface of
				  class SetUserSignInDateCommand

*****************************************************************/

#include <Command.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define SET_SIGNIN_DATE_CMD_API __declspec(dllexport)
#else
#define SET_SIGNIN_DATE_CMD_API __declspec(dllimport)
#endif

#ifndef SET_SIGNIN_DATE_CMD_H
#define SET_SIGNIN_DATE_CMD_H

/****************************************************************

   Class : SetUserSignInDateCommand

   Description : Set user sign in date

*****************************************************************/
class SET_SIGNIN_DATE_CMD_API SetUserSignInDateCommand : public Command
{
	private:
				
		// Save date of last sign in 
		bool SetUserSignInDate(int userID, int authSystemID);

	public:

		// Constructor
		SetUserSignInDateCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~SetUserSignInDateCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif