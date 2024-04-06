/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ValidateAnswersCommand.h

   Description :  this module defines interface of
				  class ValidateAnswersCommand

*****************************************************************/

#include <Command.h>
#include <ResponseValidator.h>

#ifdef ZHOSTCMD01_EXPORTS
#define VALIDATE_ANSWERS_CMD_API __declspec(dllexport)
#else
#define VALIDATE_ANSWERS_CMD_API __declspec(dllimport)
#endif

#ifndef VALIDATE_ANSWERS_CMD_H
#define VALIDATE_ANSWERS_CMD_H

/****************************************************************

   Class : ValidateAnswersCommand

   Description : Validate user education answers.

*****************************************************************/
class VALIDATE_ANSWERS_CMD_API ValidateAnswersCommand : public Command
{
	private:
		
		//  Validate user answers
		int ValidateAnswers(int userID, char * compName, PANSWER_CONTAINER eduContainer);

		// Delete education container
		PANSWER_CONTAINER DeleteAnswerContainer(PANSWER_CONTAINER eduContainer);

	public:

		// Constructor
		ValidateAnswersCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~ValidateAnswersCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif