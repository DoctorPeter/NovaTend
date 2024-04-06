/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : ScheduleRecord.h

   Description :  this module defines interface of
				  class ScheduleRecord

*****************************************************************/

#include "stdafx.h"
#include "SchedulerCondition.h"

#ifdef ZSCHEDULER01_EXPORTS
#define SCHEDULE_RECORD_API __declspec(dllexport)
#else
#define SCHEDULE_RECORD_API __declspec(dllimport)
#endif

#ifndef SCHEDULER_RECORD_H
#define SCHEDULER_RECORD_H

/****************************************************************

   Class : ScheduleRecord

   Description : Provides general structure of class 
				of schedule record.

*****************************************************************/
class SCHEDULE_RECORD_API ScheduleRecord : public SystemBase
{
	private:

		// Condition instance
		SchedulerCondition * scheduleCondition;

		// Log writer instance
		LogWriter * logWriter;

		// Write message to log-file
		int WriteToLog(char * message);
		
	public:
		
		// ID
		int scheduleRecordID;

		// User ID
		int userID;

		// Computer ID
		int computerID;

		// Action value
		int scheduleAction;

		//  Schedule function
		int scheduleFunction;

		// Program ID
		int programID;

		// Condition string
		char conditionString[PARAM_STR_LEN];

		// Inc count value flag
		bool incCountValue;

		// Constructor
		ScheduleRecord(unsigned long dllUserID, 
			           LogWriter * logWriter,
					   int ID,
					   int userID,
					   int computerID,
					   int action,
					   int function,
					   int programID,
					   char * conditionString, 
					   bool incCountValue);

		// Desctructor
		virtual ~ScheduleRecord(void);

		// Verify
		int Verify(void);
};

#endif