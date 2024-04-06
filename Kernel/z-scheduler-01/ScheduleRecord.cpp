/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : ScheduleRecord.cpp

   Description :  this module implements methods of
				  class ScheduleRecord

*****************************************************************/

#include "stdafx.h"
#include "ScheduleRecord.h"

// z-scheduler-01.dll definition structure
extern DLL_COMMON_DEFINITION zSchedulerDllDefinition;
 
/****************************************************************

   Class : ScheduleRecord

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
ScheduleRecord :: ScheduleRecord(unsigned long dllUserID, 
								   LogWriter * logWriter,
								   int ID,
								   int userID,
								   int computerID,
								   int action,
								   int function,
								   int programID,
								   char * conditionString,
								   bool incCountValue) : SystemBase(dllUserID, &zSchedulerDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("ScheduleRecord : constructor");
	#endif
	
	this -> scheduleRecordID = ID;
	this -> userID = userID;
	this -> computerID = computerID;
	this -> scheduleAction = action;
	this -> scheduleFunction = function;
	this -> programID = programID;
	strcpy(this -> conditionString, conditionString);
	this -> incCountValue = incCountValue;

	scheduleCondition = new SchedulerCondition(dllUserID, logWriter, conditionString);
}

/****************************************************************

   Class : ScheduleRecord

   Method : Destructor

*****************************************************************/
ScheduleRecord :: ~ScheduleRecord(void)
{
	delete scheduleCondition;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("ScheduleRecord : destructor");
	#endif
}

/****************************************************************

   Class : ScheduleRecord

   Method : Verify

   Returns : action type

   Description : Verify schedule record

*****************************************************************/
int ScheduleRecord :: Verify(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("ScheduleRecord : Verify. Start");
	#endif

	int verificationResult = ALLOW_ACTION;

	// Check condition and prepare verification result
	if (scheduleCondition -> Check())
	{
		verificationResult = scheduleAction;
	}
	else
	{
		if (scheduleAction == ALLOW_ACTION)
			verificationResult = DENY_ACTION;
	}

	// Check inc count value flag
	if (incCountValue)
	{
		// Increase count value
		scheduleCondition -> IncCountConditions();

		// Get updated condition string
		scheduleCondition -> GetConditionString(conditionString);

		// Rebuid condition
		scheduleCondition -> BuildCondition(conditionString);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		char buffer[STR_VALUE_LEN * 4] = "";
		sprintf(buffer, "ScheduleRecord : Verify. UserID = %d, ComputerID = %d, Action = %d, Function = %d, ProgramID = %d, Condition = %s, Verification result = %d", userID, computerID, scheduleAction, scheduleFunction, programID, conditionString, verificationResult);
		WriteToLog(buffer);

		WriteToLog("ScheduleRecord : Verify. Done");
	#endif

	return verificationResult;
}

/****************************************************************

   Class : ScheduleRecord

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int ScheduleRecord :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}