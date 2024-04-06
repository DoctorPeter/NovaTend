/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : Scheduler.h

   Description :  this module defines interface of
				  class Scheduler

*****************************************************************/

#include "stdafx.h"
#include "ScheduleRecord.h"
#include <DatabaseManager.h>
#include <SerializationDef.h>

#ifdef ZSCHEDULER01_EXPORTS
#define SCHEDULER_API __declspec(dllexport)
#else
#define SCHEDULER_API __declspec(dllimport)
#endif

#ifndef SCHEDULER_H
#define SCHEDULER_H

// Maximu count of schedule records
#define MAX_SHEDULE_RECORDS_COUNT		128

/****************************************************************

   Class : Scheduler

   Description : Provides general structure of class 
				of scheduler.

*****************************************************************/
class SCHEDULER_API Scheduler : public SystemBase
{
	private:
		
		// Schedule records count
		int scheduleRecordsCount;

		// Schedule
		ScheduleRecord * schedule[MAX_SHEDULE_RECORDS_COUNT];

		// Log writer instance
		LogWriter * logWriter;

		// Database manager instance
		DatabaseManager * dbManager;

		// DB manager flag
		bool ownDBManager;

		// Write message to log-file
		int WriteToLog(char * message);
		
		// Connect to database
		bool DatabaseConnect(void);

		// Disconnect from database
		bool DatabaseDisconnect(void);

		// Load schedule records
		bool LoadSchedule(int userID, int computerID, int functionID);

		// Save schedule record to database
		bool SaveSheduleRecord(int scheduleRecordIndex);

		// Free schedule records
		void RemoveSchedule(void);

		// Get computer ID
		int GetComputerID(char * compName);

		// Get program name
		bool GetProgramName(int programID, char * programName);

		// Deny some program
		void DenyProgramInList(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList, char * programName);

	public:
				
		// Constructor
		Scheduler(unsigned long dllUserID, LogWriter * logWriter);
		
		// Constructor
		Scheduler(unsigned long dllUserID, LogWriter * logWriter, DatabaseManager * dbManager);

		// Desctructor
		virtual ~Scheduler(void);

		// Verify schedule records
		int VerifyScheduleRecords(int userID, int computerID, int functionID);

		// Verify schedule records
		int VerifyScheduleRecords(int userID, char * compName, int functionID);

		// Verify programs
		void VerifySchedulePrograms(int userID, int computerID, PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList);

		// Verify programs
		void VerifySchedulePrograms(int userID, char * compName, PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList);

		// Verify programs
		void VerifyProgramList(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList);
};

#endif