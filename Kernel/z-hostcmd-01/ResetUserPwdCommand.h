/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ResetUserPwdCommand.h

   Description :  this module defines interface of
				  class ResetUserPwdCommand

*****************************************************************/

#include <Command.h>
#include <LicenseManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define RESET_PWD_CMD_API __declspec(dllexport)
#else
#define RESET_PWD_CMD_API __declspec(dllimport)
#endif

#ifndef RESET_PWD_CMD_H
#define RESET_PWD_CMD_H

/****************************************************************

   Class : ResetUserPwdCommand

   Description : Reset user custom password

*****************************************************************/
class RESET_PWD_CMD_API ResetUserPwdCommand : public Command
{
	private:
				
		// License manager instance
		LicenseManager * licenseManager;

		// Reset user custom password
		int ResetUserCustomPassword(int userID);

	public:

		// Constructor
		ResetUserPwdCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~ResetUserPwdCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif