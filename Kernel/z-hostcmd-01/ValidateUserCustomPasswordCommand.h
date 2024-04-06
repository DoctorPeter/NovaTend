/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ValidateUserCustomPasswordCommand.h

   Description :  this module defines interface of
				  class ValidateUserCustomPasswordCommand

*****************************************************************/

#include <Command.h>
#include <ResponseValidator.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define VALIDATE_CUSTOM_PWD_CMD_API __declspec(dllexport)
#else
#define VALIDATE_CUSTOM_PWD_CMD_API __declspec(dllimport)
#endif

#ifndef VALIDATE_CUSTOM_PWD_CMD_H
#define VALIDATE_CUSTOM_PWD_CMD_H

/****************************************************************

   Class : ValidateUserCustomPasswordCommand

   Description : Validate user parameters for checking.

*****************************************************************/
class VALIDATE_CUSTOM_PWD_CMD_API ValidateUserCustomPasswordCommand : public Command
{
	private:
		
		// Content manager instance
		ContentManager * contentManager;

		// Response validator instance
		ResponseValidator * responseValidator;

		// Create user security data
		PUSER_SECURITY_DATA CreateUserSecurityData(void);

		// Delete user security data
		PUSER_SECURITY_DATA DeleteUserSecurityData(PUSER_SECURITY_DATA securityData);

		// Validate user custom password
		int ValidateUserCustomPassword(int userID, int authSystemID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList, PUSER_SECURITY_DATA securityData);

		// Delete symbol boxes list
		PUTF8_STRINGS_MATRIX_LIST DeleteSymbolBoxesList(PUTF8_STRINGS_MATRIX_LIST symbolBoxesList);

	public:

		// Constructor
		ValidateUserCustomPasswordCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~ValidateUserCustomPasswordCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif