/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ValidateAnswersCommand.cpp

   Description :  this module implements methods of
				  class ValidateAnswersCommand

*****************************************************************/

#include "stdafx.h"
#include "ValidateAnswersCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : ValidateAnswersCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
ValidateAnswersCommand :: ValidateAnswersCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateAnswersCommand : constructor");
	#endif
}

/****************************************************************

   Class : ValidateAnswersCommand

   Method : Destructor

*****************************************************************/
ValidateAnswersCommand :: ~ValidateAnswersCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateAnswersCommand : destructor");
	#endif
}

/****************************************************************

   Class : ValidateAnswersCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST ValidateAnswersCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateAnswersCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 3) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[1] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[2] -> paramDataType == ANSWER_CONTAINER_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
					
		// Unpack user ID
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);

		// Unpack computer name
		char compName[NAME_LEN];
		serializationManager -> UnpackString(parameters -> paramList[1], compName);
		
		// Unpack education container
		PANSWER_CONTAINER eduContainer = serializationManager -> UnpackAnswerContainer(parameters -> paramList[2]);

		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			int validateResult = ValidateAnswers(userID, compName, eduContainer);
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackDWORD(validateResult, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("ValidateAnswersCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete education conatiner
		eduContainer = DeleteAnswerContainer(eduContainer);

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("ValidateAnswersCommand : Execute. Wrong input parameters!");

		WriteToLog("ValidateAnswersCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ValidateAnswersCommand

   Method :  ValidateAnswers

   Return : Error code

   Description : Validate user answers

*****************************************************************/
int ValidateAnswersCommand :: ValidateAnswers(int userID, char * compName, PANSWER_CONTAINER eduContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateAnswersCommand: ValidateAnswers. Start");
	#endif
	
	ResponseValidator * responseValidator = new ResponseValidator(zHostCmdDllDefinition.dllID, logWriter);
	int validateResult = responseValidator -> ValidateAnswers(userID, compName, eduContainer);
	delete responseValidator;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateAnswersCommand: ValidateAnswers. Done");
	#endif

	return validateResult - dllUserCheckResult;
}

/****************************************************************

   Class : ValidateAnswersCommand

   Method :  DeleteAnswerContainer

   Parameters:
			Input:
				eduContainer - Education container pointer

   Return : Education container pointer

   Description : Delete education container

*****************************************************************/
PANSWER_CONTAINER ValidateAnswersCommand :: DeleteAnswerContainer(PANSWER_CONTAINER eduContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ValidateAnswersCommand: DeleteAnswerContainer");
	#endif

	if (eduContainer) 
	{
		for (int i = 0; i < eduContainer -> answersCount; i++)
			free(eduContainer -> answers[i]);

		free(eduContainer);

		eduContainer = NULL;
	}

	return eduContainer;
}
