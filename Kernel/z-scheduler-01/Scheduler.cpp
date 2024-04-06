/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : Scheduler.cpp

   Description :  this module implements methods of
				  class Scheduler

*****************************************************************/

#include "stdafx.h"
#include "Scheduler.h"
#include "FuzzyStringCompare.h"

#include <ODBCDatabaseManager.h>
#include <SettingsManager.h>

#include <stdio.h>
#include <stdlib.h>

// z-scheduler-01.dll definition structure
extern DLL_COMMON_DEFINITION zSchedulerDllDefinition;
 
#pragma region Constructing

/****************************************************************

   Class : Scheduler

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
Scheduler :: Scheduler(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zSchedulerDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : constructor");
	#endif

	for(int i = 0; i < MAX_SHEDULE_RECORDS_COUNT - 1; i++)
		schedule[i] = NULL;

	scheduleRecordsCount = 0;

	ownDBManager = true;
	dbManager = new ODBCDatabaseManager(zSchedulerDllDefinition.dllID, logWriter);
	DatabaseConnect();
}

/****************************************************************

   Class : Scheduler

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				dbManager - DB manager

*****************************************************************/
Scheduler :: Scheduler(unsigned long dllUserID, LogWriter * logWriter, DatabaseManager * dbManager) : SystemBase(dllUserID, &zSchedulerDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : constructor");
	#endif

	for(int i = 0; i < MAX_SHEDULE_RECORDS_COUNT - 1; i++)
		schedule[i] = NULL;

	scheduleRecordsCount = 0;

	ownDBManager = false;
	this -> dbManager = dbManager;
}

/****************************************************************

   Class : Scheduler

   Method : Destructor

*****************************************************************/
Scheduler :: ~Scheduler(void)
{
	RemoveSchedule();
	
	if (ownDBManager)
	{
		DatabaseDisconnect();
		delete dbManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : destructor");
	#endif
}


#pragma endregion

#pragma region Database

/****************************************************************

   Class : Scheduler

   Method : DatabaseConnect

   Return : Connection state

   Description :  Connect to database

*****************************************************************/
bool Scheduler :: DatabaseConnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : DatabaseConnect. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Check connection
		if (!(dbManager -> Opened()))
		{
		
			// Data source name
			char dsn[NAME_LEN];

			// Name of database user
			char dbUser[NAME_LEN];

			// Password for database access
			char dbPassword[STR_VALUE_LEN];

			SettingsManager * settingsManager = new SettingsManager(zSchedulerDllDefinition.dllID);

			if (settingsManager -> GetDatabaseSourceName(dsn) != ERROR_SUCCESS)
				WriteToLog("Scheduler : Connect to DB --> Can't get DSN ");

			if (settingsManager -> GetDatabaseUserName(dbUser) != ERROR_SUCCESS)
				WriteToLog("Scheduler :  Connect to DB --> Can't get db user name ");

			if (settingsManager -> GetDatabasePassword(dbPassword) != ERROR_SUCCESS)
				WriteToLog("Scheduler :  Connect to DB --> Can't get db password ");

			delete settingsManager;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
				WriteToLog("Scheduler : DatabaseConnect. Connecting...");
			#endif

			// Connect
			dbManager -> Connect(dsn, dbUser, dbPassword);
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			else
				WriteToLog("Scheduler : DatabaseConnect. Already connected!");

			WriteToLog("Scheduler : DatabaseConnect. Done");
		#endif

		// Return connection state
		return dbManager -> Opened();
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

/****************************************************************

   Class : Scheduler

   Method : DatabaseDisconnect

   Return : Connection state

   Description :  Disconnect from database

*****************************************************************/
bool Scheduler :: DatabaseDisconnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : DatabaseDisconnect. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Check connection
		if (dbManager -> Opened())
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
				WriteToLog("Scheduler : DatabaseDisconnect. Disconnecting...");
			#endif

			// Disconnect
			dbManager -> Disconnect();
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			else
				WriteToLog("Scheduler : DatabaseDisconnect. Already disconnected!");

			WriteToLog("Scheduler : DatabaseDisconnect. Done");
		#endif

		// Return connection state
		return dbManager -> Opened();
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return true;
	}
}

/****************************************************************

   Class : Scheduler

   Method : LoadSchedule

   Parameters:
			Input:
				userID - user ID
				computerID - computer ID
				functionID - function type

   Return : TRUE - if success

   Description :  Load schedule records

*****************************************************************/
bool Scheduler :: LoadSchedule(int userID, int computerID, int functionID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : LoadSchedule. Start");
	#endif
	
	// Remove previous schedule
	RemoveSchedule();

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;
				
		// SQL query buffer
		char sql[SQL_SIZE];

		// Get permissions of user
		sprintf(sql, "SELECT Schedule.ID,\
							 Schedule.ActionID,\
							 Schedule.ProgramID,\
							 Schedule.incCountValues,\
							 Schedule.ConditionString\
						FROM Schedule\
						WHERE (((Schedule.UserID = %d) OR (Schedule.UserID is NULL)) AND\
							   ((Schedule.CompID = %d) OR (Schedule.CompID is NULL)) AND\
							   ((Schedule.GroupID in (SELECT UserGroupUsers.GroupID\
													  FROM UserGroupUsers\
													  WHERE UserGroupUsers.UserID = %d)) OR (Schedule.GroupID is NULL)) AND\
							   ((Schedule.FuncID = %d) OR (Schedule.FuncID is NULL)))", userID, computerID, userID, functionID);
		
		// Execute query
		ResultSet * scheduleResult = dbManager -> ExecuteSelectQuery(sql);
		
		// Buffers definition
		int recordIDBuf = 0;
		int scheduleActionBuf = 0;
		int programIDBuf = 0;
		int incCountValueBuf = 0;
		char conditionStringBuf[PARAM_STR_LEN] = "";
		
		// Bind data
		scheduleResult -> Bind(1, &recordIDBuf, sizeof(recordIDBuf), SQL_C_LONG);
		scheduleResult -> Bind(2, &scheduleActionBuf, sizeof(scheduleActionBuf), SQL_C_LONG);
		scheduleResult -> Bind(3, &programIDBuf, sizeof(programIDBuf), SQL_C_LONG);
		scheduleResult -> Bind(4, &incCountValueBuf, sizeof(incCountValueBuf), SQL_C_LONG);
		scheduleResult -> Bind(5, conditionStringBuf, PARAM_STR_LEN);
		
		// Get schedule records
		while(scheduleResult -> MoveNext())
		{
			schedule[scheduleRecordsCount] = new ScheduleRecord(dllUserID, logWriter, recordIDBuf, userID, computerID, scheduleActionBuf, functionID, programIDBuf, conditionStringBuf, (incCountValueBuf == 0 ? false : true));
			scheduleRecordsCount++;

			recordIDBuf = 0;;
		    scheduleActionBuf = 0;;
		    programIDBuf = 0;;
		    incCountValueBuf = 0;;
		    conditionStringBuf[0] = 0;
		}
		
		delete scheduleResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			WriteToLog("Scheduler : LoadSchedule. Done");
		#endif

		return true;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

/****************************************************************

   Class : Scheduler

   Method : SaveSheduleRecord

   Parameters:
			Input:
				scheduleRecordIndex - index of record in list

   Return : TRUE - if success

   Description :  Save schedule record to database

*****************************************************************/
bool Scheduler :: SaveSheduleRecord(int scheduleRecordIndex)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : SaveSheduleRecord. Start");
	#endif

	// Check input data
	if ((scheduleRecordIndex < 0) || (scheduleRecordIndex > scheduleRecordsCount - 1) || (!schedule[scheduleRecordIndex]))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			WriteToLog("Scheduler : SaveSheduleRecord. Wrong input!");
			WriteToLog("Scheduler : SaveSheduleRecord. Done");
		#endif

		return false;
	}

	ScheduleRecord * record = schedule[scheduleRecordIndex];

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Buffers definition
		char userIDBuf[BUF_SIZE] = "NULL";
		char compIDBuf[BUF_SIZE] = "NULL";
		char progIDBuf[BUF_SIZE] = "NULL";

		//Fill buffers
		if ((record -> userID != 0) && (record -> userID != -1))
			itoa(record -> userID, userIDBuf, 10);

		if ((record -> computerID != 0) && (record -> computerID != -1))
			itoa(record -> computerID, compIDBuf, 10);

		if ((record -> programID != 0) && (record -> programID != -1))
			itoa(record -> programID, progIDBuf, 10);

		// Prepare update query
		sprintf(sql, "UPDATE Schedule\
					   SET UserID = %s,\
						   CompID = %s,\
						   ActionID = %d,\
						   FuncID = %d,\
						   ProgramID = %s,\
						   incCountValues = %d,\
						   ConditionString = \'%s\'\
					 WHERE (ID = %d)", userIDBuf, 
					                   compIDBuf,
									   record -> scheduleAction, 
									   record -> scheduleFunction, 
									   progIDBuf, 
									   (int)(record -> incCountValue), 
									   record -> conditionString,
									   record -> scheduleRecordID);
		
		// Execute query
		dbManager ->  Execute(sql);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			WriteToLog("Scheduler : SaveSheduleRecord. Done");
		#endif

		return true;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

#pragma endregion

#pragma region Schedule

/****************************************************************

  Class : Scheduler

  Method : DatabaseConnect

  Description :  Free schedule records

*****************************************************************/
void Scheduler :: RemoveSchedule(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : RemoveSchedule");
	#endif

	for (int i = 0; i < scheduleRecordsCount; i++)
	{
		if (schedule[i])
		{
			delete schedule[i];
			schedule[i] = NULL;
		}
	}

	scheduleRecordsCount = 0;
}

/****************************************************************

  Class : Scheduler

  Method : VerifyScheduleRecords

  Parameters:
			Input:
				userID - user ID
				computerID - computer ID
				functionID	- shedule function

  Returns: verification result (action)

  Description :  Verify schedule records

*****************************************************************/
int Scheduler :: VerifyScheduleRecords(int userID, int computerID, int functionID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : VerifyScheduleRecords. Start");
	#endif

	int verificationResult = ALLOW_ACTION;

	if (LoadSchedule(userID, computerID, functionID))
	{
		for (int i = 0; i < scheduleRecordsCount; i++)
		{
			verificationResult = verificationResult | schedule[i] -> Verify();

			if (schedule[i] -> incCountValue)
				SaveSheduleRecord(i);
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : VerifyScheduleRecords. Done");
	#endif

	return verificationResult;
}

/****************************************************************

   Class : Scheduler

   Method : GetComputerID
   
   Parameters :
			Input : 
				compName - computer name

   Return : computer ID
	
   Description :  Get computer ID

*****************************************************************/
int Scheduler :: GetComputerID(char * compName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : GetComputerID. Start");
	#endif

	// Check input data
	if (!compName)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			WriteToLog("Scheduler : GetComputerID. Wrong input data!");
			WriteToLog("Scheduler : GetComputerID. Done");
		#endif

		return -1;
	}

	// Computer ID
	int compID = -1;

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT TOP 1 Computers.ID FROM Computers WHERE (Computers.Name = '%s')", compName);
		
		// Execute SQl query
		ResultSet * compResult = dbManager -> ExecuteSelectQuery(sql);

		int compIDBuf = -1;

		// Bind data
		compResult -> Bind(1, &compIDBuf, sizeof(compIDBuf), SQL_C_LONG);

		// Retrieve record
		if (compResult -> MoveFirst())
		{
			compID = compIDBuf;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
				WriteToLog("Scheduler : GetComputerID. Computer ID was retrieved!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			else
				WriteToLog("Scheduler : GetComputerID. Computer not found!");

			WriteToLog("Scheduler : GetComputerID. Done");
		#endif

		delete compResult;

		return compID;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return -1;
	}
}

/****************************************************************

  Class : Scheduler

  Method : VerifyScheduleRecords

  Parameters:
			Input:
				userID - user ID
				compName - computer name
				functionID	- shedule function

  Returns: verification result (action)

  Description :  Verify schedule records

*****************************************************************/
int Scheduler :: VerifyScheduleRecords(int userID, char * compName, int functionID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : VerifyScheduleRecords. Start");
	#endif
				
	// Get computer ID
	int computerID = GetComputerID(compName);

	// Verify
	int verificationResult = VerifyScheduleRecords(userID, computerID, functionID);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : VerifyScheduleRecords. Done");
	#endif

	return verificationResult;
}

/****************************************************************

   Class : Scheduler

   Method : GetProgramName
   
   Parameters :
			Input : 
				programID - program ID
			Output:
				programNme - program name

   Return : TRUE - if program is allowed
	
   Description :  Get program name

*****************************************************************/
bool Scheduler :: GetProgramName(int programID, char * programName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : GetProgramName. Start");
	#endif

	if ((programID <= 0) || (!programName))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			WriteToLog("Scheduler : GetProgramName. Wrong input data!");
			WriteToLog("Scheduler : GetProgramName. Done");
		#endif

		return false;
	}

	// Allow flag
	bool allowed = false;

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT ControlledPrograms.Name, ControlledPrograms.Allowed FROM ControlledPrograms WHERE (ControlledPrograms.ID = %d)", programID);
		
		// Execute SQl query
		ResultSet * prgResult = dbManager -> ExecuteSelectQuery(sql);

		char prgNameBuf[NAME_LEN] = "";
		int allowBuf = 0;

		// Bind data
		prgResult -> Bind(1, prgNameBuf, NAME_LEN);
		prgResult -> Bind(2, &allowBuf, sizeof(allowBuf), SQL_C_LONG);

		// Retrieve record
		if (prgResult -> MoveFirst())
		{
			strcpy(programName, prgNameBuf);
			allowed = (allowBuf == 0) ? false : true;;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
				WriteToLog("Scheduler : GetProgramName. Program name was retrieved!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			else
				WriteToLog("Scheduler : GetProgramName. Program not found!");

			WriteToLog("Scheduler : GetProgramName. Done");
		#endif

		delete prgResult;

		return allowed;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}
}

/****************************************************************

   Class : Scheduler

   Method : DenyProgramInList
   
   Parameters :
			Input : 
				programList - programs list
				programName - program name

   Description :  Deny some program

*****************************************************************/
void Scheduler :: DenyProgramInList(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList, char * programName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : DenyProgramInList. Start");
	#endif

	// Check input values
	if ((programList) && (programName))
	{
		for (int i = 0; i < (programList -> programListSize); i++)
		{
			// Prepare program name string
			char genName[NAME_LEN] = "";
			strcpy(genName, programList -> programList[i] -> programName);
			strcat(genName, " : ");
			strcat(genName, programList -> programList[i] -> moduleName);

			// Check program name
			if (FuzzyStrCmp(genName, programName))
				 programList -> programList[i] -> allowed = false;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : DenyProgramInList. Done");
	#endif
}

/****************************************************************

   Class : Scheduler

   Method : VerifySchedulePrograms
   
   Parameters :
			Input : 
				userID - user ID
				computerID - computer ID
				programList - programs list

   Description : Verify some program

*****************************************************************/
void Scheduler :: VerifySchedulePrograms(int userID, int computerID, PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : VerifyScheduleProgram. Start");
	#endif

	if (programList)
	{
		for (int i = 0; i < (programList -> programListSize); i++)
			programList -> programList[i] -> allowed = true;

		// Load schedule
		if (LoadSchedule(userID, computerID, PROGRAM_CONTROL_FUNCTION))
		{
			for (int i = 0; i < scheduleRecordsCount; i++)
			{
				// Get program name
				char prgName[NAME_LEN] = "";
				bool prgAllowed = GetProgramName(schedule[i] -> programID, prgName);

				if (prgAllowed)
				{
					// Verify schedule record
					int verificationResult = schedule[i] -> Verify();
				
					// Inc count if it needed
					if (schedule[i] -> incCountValue)
						SaveSheduleRecord(i);

					// Deny program if it needed
					if ((verificationResult & DENY_ACTION) == DENY_ACTION)
						DenyProgramInList(programList, prgName);
				}
				else
					DenyProgramInList(programList, prgName);
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : VerifyScheduleProgram. Done");
	#endif
}

/****************************************************************

   Class : Scheduler

   Method : VerifySchedulePrograms
   
   Parameters :
			Input : 
				userID - user ID
				compName - computer name
				programList - programs list

   Description : Verify some program

*****************************************************************/
void Scheduler :: VerifySchedulePrograms(int userID, char * compName, PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : VerifySchedulePrograms. Start");
	#endif
				
	// Get computer ID
	int computerID = GetComputerID(compName);

	// Verify
	VerifySchedulePrograms(userID, computerID, programList);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : VerifySchedulePrograms. Done");
	#endif
}


/****************************************************************

   Class : Scheduler

   Method : VerifyProgramList
   
   Parameters :
			Input : 
				programList - programs list

   Description : Verify some program

*****************************************************************/
void Scheduler :: VerifyProgramList(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("Scheduler : VerifyProgramList. Start");
	#endif

	if (!programList)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			WriteToLog("Scheduler : VerifyProgramList. Wrong input data!");
			WriteToLog("Scheduler : VerifyProgramList. Done");
		#endif

		return;
	}

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT ControlledPrograms.Name, ControlledPrograms.Allowed FROM ControlledPrograms");
		
		// Execute SQl query
		ResultSet * prgResult = dbManager -> ExecuteSelectQuery(sql);

		char prgNameBuf[NAME_LEN] = "";
		int allowBuf = 0;

		// Bind data
		prgResult -> Bind(1, prgNameBuf, NAME_LEN);
		prgResult -> Bind(2, &allowBuf, sizeof(allowBuf), SQL_C_LONG);

		// Retrieve records
		while (prgResult -> MoveNext())
		{
			for(int i = 0; i < programList -> programListSize; i++)
			{
				// Prepare program name string
				char genName[NAME_LEN] = "";
				strcpy(genName, programList -> programList[i] -> programName);
				strcat(genName, " : ");
				strcat(genName, programList -> programList[i] -> moduleName);

				// Check program name
				if ((programList -> programList[i] -> allowed) && (allowBuf == 0) && (FuzzyStrCmp(genName, prgNameBuf)))
				{
					programList -> programList[i] -> allowed = false;

					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
						WriteToLog("Scheduler : VerifyProgramList. Program denied!");
					#endif
				}
			}
		}

		delete prgResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			WriteToLog("Scheduler : VerifyProgramList. Done");
		#endif
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
	}
}

#pragma endregion

#pragma region LOG

/****************************************************************

   Class : Scheduler

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int Scheduler :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion