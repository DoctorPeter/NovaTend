/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ValidateParamsCommand.h

   Description :  this module defines interface of
				  class ValidateParamsCommand

*****************************************************************/

#include <Command.h>
#include <ResponseValidator.h>

#ifdef ZHOSTCMD01_EXPORTS
#define VALIDATE_PARAMS_CMD_API __declspec(dllexport)
#else
#define VALIDATE_PARAMS_CMD_API __declspec(dllimport)
#endif

#ifndef VALIDATE_PARAMS_CMD_H
#define VALIDATE_PARAMS_CMD_H

/****************************************************************

   Class : ValidateParamsCommand

   Description : Validate user parameters for checking.

*****************************************************************/
class VALIDATE_PARAMS_CMD_API ValidateParamsCommand : public Command
{
	private:
		
		//  Validate user parameters
		int ValidateParams(int userID, char * compName, PAUTH_CONTAINER authContainer);

		// Delete authentication container
		PAUTH_CONTAINER DeleteAuthContainer(PAUTH_CONTAINER authContainer);

	public:

		// Constructor
		ValidateParamsCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~ValidateParamsCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif