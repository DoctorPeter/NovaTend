/****************************************************************

   Solution : NovaTend

   Project : z-cmdhist-01.dll

   Module : CommandHistoryManager.cpp

   Description :  this module implements methods of
				  class CommandHistoryManager

*****************************************************************/

#include "stdafx.h"
#include "CommandHistoryManager.h"

#include <SQLiteDatabaseManager.h>
#include <SerializationManager.h>
#include <SettingsManager.h>

#include <stdio.h>
#include <stdlib.h>

// z-cmdhist-01.dll definition structure
extern DLL_COMMON_DEFINITION zCmdHistDllDefinition;

#pragma region Constructing
 
/****************************************************************

   Class : CommandHistoryManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
CommandHistoryManager :: CommandHistoryManager(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zCmdHistDllDefinition)
{
	this -> logWriter = logWriter;
			
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : constructor");
	#endif

	dbManager = new SQLiteDatabaseManager(zCmdHistDllDefinition.dllID, logWriter);
	encryptor = new Encryptor(zCmdHistDllDefinition.dllID);

	DatabaseConnect();
}

/****************************************************************

   Class : CommandHistoryManager

   Method : Destructor

*****************************************************************/
CommandHistoryManager :: ~CommandHistoryManager(void)
{
	DatabaseDisconnect();

	delete dbManager;
	delete encryptor;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : destructor");
	#endif
}

#pragma endregion

#pragma region Database

/****************************************************************

   Class : CommandHistoryManager

   Method : DatabaseConnect

   Return : Connection state

   Description :  Connect to database

*****************************************************************/
bool CommandHistoryManager :: DatabaseConnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : DatabaseConnect. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Check connection
		if (!(dbManager -> Opened()))
		{
		
			// Data source name
			char dbName[NAME_LEN] = "";

			SettingsManager * settingsManager = new SettingsManager(zCmdHistDllDefinition.dllID);

			if (settingsManager -> GetCmdHistDatabase(dbName) != ERROR_SUCCESS)
				WriteToLog("Command history manager : Connect to DB --> Can't get DSN ");

			delete settingsManager;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
				WriteToLog("CommandHistoryManager : DatabaseConnect. Connecting...");
			#endif

			// Connect
			dbManager -> Connect(dbName);

			// Turn ON foreign keys support
			dbManager -> Execute("PRAGMA foreign_keys = ON;");
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
			else
				WriteToLog("CommandHistoryManager : DatabaseConnect. Already connected!");

			WriteToLog("CommandHistoryManager : DatabaseConnect. Done");
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

   Class : CommandHistoryManager

   Method : DatabaseDisconnect

   Return : Connection state

   Description :  Disconnect from database

*****************************************************************/
bool CommandHistoryManager :: DatabaseDisconnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : DatabaseDisconnect. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Check connection
		if (dbManager -> Opened())
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
				WriteToLog("CommandHistoryManager : DatabaseDisconnect. Disconnecting...");
			#endif

			// Disconnect
			dbManager -> Disconnect();
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
			else
				WriteToLog("CommandHistoryManager : DatabaseDisconnect. Already disconnected!");

			WriteToLog("CommandHistoryManager : DatabaseDisconnect. Done");
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

#pragma endregion

#pragma region History

/****************************************************************

   Class : CommandHistoryManager

   Method : CreateHistory

   Return : History container

   Description :  Create history list

*****************************************************************/
PCMD_HISTORY CommandHistoryManager :: CreateHistory(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : CreateHistory. Start");
	#endif

	PCMD_HISTORY pHistory = (PCMD_HISTORY)malloc(sizeof(CMD_HISTORY));

	if (pHistory)
	{
		pHistory -> size = 0;

		for(int i = 0; i < MAX_CMD_HIST_SIZE; i++)
			pHistory -> historyItems[i] = NULL;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		else
			WriteToLog("CommandHistoryManager : CreateHistory. Error of memory allocation!");

		WriteToLog("CommandHistoryManager : CreateHistory. Done");
	#endif

	return pHistory;
}

/****************************************************************

   Class : CommandHistoryManager

   Method : DeleteHistory

   Parameters:
			Input:
				pHistory - pointer to history container
   
   Return : Pointer to history container

   Description :  Delete history list

*****************************************************************/
PCMD_HISTORY CommandHistoryManager :: DeleteHistory(PCMD_HISTORY pHistory)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : DeleteHistory");
	#endif

	if (pHistory)
	{
		for (int i = 0; i < pHistory -> size; i++)
			free(pHistory -> historyItems[i]);

		free(pHistory);

		pHistory = NULL;
	}

	return pHistory;
}

/****************************************************************

   Class : CommandHistoryManager

   Method : GetCommandHistory

   Parameters:
			Input:
				beginTime - begin time in format YYYY-MM-DD HH:MM:SS
				endTime - end time in format YYYY-MM-DD HH:MM:SS
   
   Return : Pointer to history container

   Description :  Get command history

*****************************************************************/
PCMD_HISTORY CommandHistoryManager :: GetCommandHistory(char * beginTime, char * endTime)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : GetCommandHistory. Start");
	#endif

	PCMD_HISTORY pHistory = NULL;

	try
	{
		// Create history
		pHistory = CreateHistory();

		if ((dbManager -> Opened()) && (pHistory) && (beginTime) && (endTime))
		{
			try
			{
				// Check DLL legal user
				dbManager += dllUserCheckResult;

				// Get commnds history
				char sql[SQL_SIZE];

				// Prepare sql query
				sprintf(sql, "SELECT CmdID, UserID, ExecTime FROM CommandsHistory WHERE ExecTime BETWEEN '%s' AND '%s';", beginTime, endTime);
		
				// Execute SQl query
				ResultSet * historyResult = dbManager -> ExecuteSelectQuery(sql);

				int cmdIDBuf = 0;
				int userIDBuf = 0;
				char execTimeBuf[DATE_STR_LEN] = "";

				// Bind data
				historyResult -> Bind(0, &cmdIDBuf, sizeof(cmdIDBuf), SQLITE_INTEGER);
				historyResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQLITE_INTEGER);
				historyResult -> Bind(2, execTimeBuf, DATE_STR_LEN, SQLITE_TEXT);

				// Retrieve record
				while ((historyResult -> MoveNext()) && (pHistory -> size < MAX_CMD_HIST_SIZE))
				{
					// Create history item
					pHistory -> historyItems[pHistory -> size] = (PCMD_HISTORY_ITEM)malloc(sizeof(CMD_HISTORY_ITEM));

					// Fill history item values
					if (pHistory -> historyItems[pHistory -> size])
					{
						pHistory -> historyItems[pHistory -> size] -> cmdID = cmdIDBuf;
						pHistory -> historyItems[pHistory -> size] -> userID = userIDBuf;
						strcpy(pHistory -> historyItems[pHistory -> size] -> execTime, execTimeBuf);
						pHistory -> size++;
					}
					else
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
							WriteToLog("CommandHistoryManager : GetCommandHistory. Error of memory allocation for command history item!");
						#endif
						break;
					}

					cmdIDBuf = 0;
					userIDBuf = 0;
					execTimeBuf[0] = 0;
				}

				delete historyResult;
			}
			catch(DBException & ex)
			{
				// Error processing
				char errMsg[ERROR_MSG_MAXLEN];
				ex.GetMessage(errMsg);
				WriteToLog(errMsg);
				return DeleteHistory(pHistory);
			}
		}
	}
	catch(...)
	{
		// Delete history
		if (pHistory)
			pHistory = DeleteHistory(pHistory);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("CommandHistoryManager : GetCommandHistory. Error of command history retrieving!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("CommandHistoryManager : GetCommandHistory. Done");
	#endif

	return pHistory;
}

/****************************************************************

   Class : CommandHistoryManager

   Method : GetCommandParameters

   Parameters:
			Input:
				cmdID - command ID
				userID - user ID
				execTime - time in format YYYY-MM-DD HH:MM:SS
  
   Return : Pointer to list of command parameters

   Description :  Get command parameters

*****************************************************************/
PCOMMAND_PARAMETER_LIST CommandHistoryManager :: GetCommandParameters(int cmdID, int userID, char * execTime)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : GetCommandParameters. Start");
	#endif

	SerializationManager * serializationManager = new SerializationManager(zCmdHistDllDefinition.dllID, logWriter);
	
	PCOMMAND_PARAMETER_LIST pCmdParamList = serializationManager -> CreateCommandParameterList();

	try
	{
		if ((dbManager -> Opened()) && (pCmdParamList) && (execTime))
		{
			try
			{
				// Check DLL legal user
				dbManager += dllUserCheckResult;

				// Get parameter values
				char sql[SQL_SIZE * 2] = "";

				// Prepare sql query
				sprintf(sql, "SELECT CommandParameters.ParamType, CommandParameters.ParamDataType, CommandParameters.BufferSize, CommandParameters.Buffer \
								FROM CommandParameters, CommandParameterList \
								WHERE  ((CommandParameterList.PID = CommandParameters.ID) AND \
										(CommandParameterList.HID = (SELECT CommandsHistory.ID \
																		FROM CommandsHistory \
																		WHERE ((CommandsHistory.CmdID = %d) AND \
																			(CommandsHistory.UserID = %d) AND \
																			(CommandsHistory.ExecTime = '%s')) LIMIT 1)));", cmdID, userID, execTime);
		
				// Execute SQl query
				ResultSet * paramResult = dbManager -> ExecuteSelectQuery(sql);

				int paramTypeBuf = 0;
				int paramDataTypeBuf = 0;
				int sizeBuf = 0;
				char * valueBuf = (char *)malloc(MAX_PARAMETER_SIZE);

				// Bind data
				paramResult -> Bind(0, &paramTypeBuf, sizeof(paramTypeBuf), SQLITE_INTEGER);
				paramResult -> Bind(1, &paramDataTypeBuf, sizeof(paramDataTypeBuf), SQLITE_INTEGER);
				paramResult -> Bind(2, &sizeBuf, sizeof(sizeBuf), SQLITE_INTEGER);
				paramResult -> Bind(3, valueBuf, MAX_PARAMETER_SIZE, SQLITE_BLOB);

				// Retrieve record
				while (paramResult -> MoveNext())
				{
					pCmdParamList -> paramList[pCmdParamList -> paramCount] = serializationManager -> CreateCommandParameter(paramTypeBuf, paramDataTypeBuf, sizeBuf);

					if (pCmdParamList -> paramList[pCmdParamList -> paramCount])
					{
						if (valueBuf) memcpy(pCmdParamList -> paramList[pCmdParamList -> paramCount] -> dataBuffer, valueBuf, sizeBuf);
						pCmdParamList -> paramCount++;
					}
					else
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
							WriteToLog("CommandHistoryManager : GetCommandParameters. Error of memory allocation for command parameter!");
						#endif
						break;
					}
				}

				if (valueBuf) free(valueBuf);
				delete paramResult;
			}
			catch(DBException & ex)
			{
				// Error processing
				pCmdParamList = serializationManager -> DeleteCommandParameterList(pCmdParamList);
				delete serializationManager;

				char errMsg[ERROR_MSG_MAXLEN];
				ex.GetMessage(errMsg);
				WriteToLog(errMsg);
				return pCmdParamList;
			}
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
			WriteToLog("CommandHistoryManager : GetCommandParameters. Error of working with memory!");
		#endif
		pCmdParamList = serializationManager -> DeleteCommandParameterList(pCmdParamList);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("CommandHistoryManager : GetCommandParameters. Done");
	#endif

	delete serializationManager;

	return pCmdParamList;
}

/****************************************************************

   Class : CommandHistoryManager

   Method : SaveCommandInfo

   Parameters:
			Input:
				cmdID - command ID
				userID - user ID
 
   Return : history rocord ID

   Description :  Save command info

*****************************************************************/
int CommandHistoryManager :: SaveCommandInfo(int cmdID, int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : SaveCommandInfo. Start");
	#endif

	// History ID
	int historyRowID = -1;

	if (dbManager -> Opened())
	{
		// Insert command to history
		try
		{
			// Check DLL legal user
			dbManager += dllUserCheckResult;

			// Get parameter values
			char sql[SQL_SIZE * 2] = "";

			// Prepare sql query
			sprintf(sql, "INSERT INTO CommandsHistory (CmdID, UserID) VALUES (%d, %d);", cmdID, userID);
		
			// Insert new command to history
			dbManager -> Execute(sql);
				
			// Get record ID
			ResultSet * historyResult = dbManager -> ExecuteSelectQuery("SELECT last_insert_rowid();");

			int rowIDBuf = 0;

			// Bind data
			historyResult -> Bind(0, &rowIDBuf, sizeof(rowIDBuf), SQLITE_INTEGER);

			// Retrieve data
			if (historyResult -> MoveFirst())
				historyRowID = rowIDBuf;

			// Delete history result set
			delete historyResult;
		}
		catch(DBException & ex)
		{
			char errMsg[ERROR_MSG_MAXLEN];
			ex.GetMessage(errMsg);
			WriteToLog(errMsg);
			return -1;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : SaveCommandInfo. Done");
	#endif

	return historyRowID;
}

/****************************************************************

   Class : CommandHistoryManager

   Method : SaveCommandParameterInfo

   Parameters:
			Input:
				historyID - history record ID
				paramList - parameter list
  
   Return : TRUE - if success

   Description :  Save command parameter info

*****************************************************************/
bool CommandHistoryManager :: SaveCommandParameterInfo(int historyID, PCOMMAND_PARAMETER_LIST paramList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : SaveCommandParameterInfo. Start");
	#endif

	// Result flag
	bool result = false;

	try
	{
		if ((dbManager -> Opened()) && (paramList) && (historyID > 0))
		{
			char * hexStr = NULL;
			char * insSQL = NULL;
			int parameterRowID = 0;

			try
			{
				// Insert command parameters
				for (int i = 0; i < paramList -> paramCount; i++)
				{
					// Check parameter buffer
					if ((paramList -> paramList[i] -> dataBuffer) && 
						(paramList -> paramList[i] -> dataBufferSize > 0))
					{
						// Alloc memory
						hexStr = (char *)malloc((paramList -> paramList[i] -> dataBufferSize) * 2 + 4);
						insSQL = (char *)malloc((paramList -> paramList[i] -> dataBufferSize) * 2 + 256);
						
						// Get hex string of buffer
						if ((hexStr) && (insSQL) && (encryptor -> BinToHexStr((unsigned char *)(paramList -> paramList[i] -> dataBuffer), paramList -> paramList[i] -> dataBufferSize, hexStr, (paramList -> paramList[i] -> dataBufferSize) * 2 + 4)))
						{
							sprintf(insSQL, "INSERT INTO CommandParameters (ParamType, ParamDataType, BufferSize, Buffer) VALUES (%d, %d, %d, X'%s');", paramList -> paramList[i] -> paramType, paramList -> paramList[i] -> paramDataType, paramList -> paramList[i] -> dataBufferSize, hexStr + 2);
							
							// Insert new parameter value
							dbManager -> Execute(insSQL);
														
							// Get record ID
							ResultSet * paramResult = dbManager -> ExecuteSelectQuery("SELECT last_insert_rowid();");

							int rowIDBuf = 0;
							
							// Bind data
							paramResult -> Bind(0, &rowIDBuf, sizeof(rowIDBuf), SQLITE_INTEGER);

							// Retrieve data
							if (paramResult -> MoveFirst())
								parameterRowID = rowIDBuf;

							// Delete history result set
							delete paramResult;

							sprintf(insSQL, "INSERT INTO CommandParameterList (HID, PID) VALUES (%d, %d);", historyID, parameterRowID);

							// Insert new parameter value
							dbManager -> Execute(insSQL);
						}

						// Delete temp buffers
						if (hexStr) free(hexStr);
						if (insSQL) free(insSQL);
					}
				}

				result = true;
			}
			catch(DBException & ex)
			{
				if (hexStr) free(hexStr);
				if (insSQL) free(insSQL);

				char errMsg[ERROR_MSG_MAXLEN];
				ex.GetMessage(errMsg);
				WriteToLog(errMsg);
				return false;
			}
		}
	}
	catch(...)
	{
		result = false;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
			WriteToLog("CommandHistoryManager : SaveCommandParameterInfo. Error of working with memory!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : SaveCommandParameterInfo. Done");
	#endif

	return result;
}

/****************************************************************

   Class : CommandHistoryManager

   Method : SaveCommand

   Parameters:
			Input:
				cmdID - command ID
				userID - user ID
				inParams - input parameter list
				outParams - output parameter list
  
   Return : TRUE - if success

   Description :  Save command to history

*****************************************************************/
bool CommandHistoryManager :: SaveCommand(int cmdID, int userID, PCOMMAND_PARAMETER_LIST inParams, PCOMMAND_PARAMETER_LIST outParams)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : SaveCommand. Start");
	#endif

	// Save command info to history
	int historyID = SaveCommandInfo(cmdID, userID);

	// Save input parameters
	bool inParamResult = SaveCommandParameterInfo(historyID, inParams);

	// Save output parameters
	bool outParamResult = SaveCommandParameterInfo(historyID, outParams);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : SaveCommand. Done");
	#endif

	return inParamResult || outParamResult;
}

/****************************************************************

   Class : CommandHistoryManager

   Method : CleanHistory

   Description :  Clean history

*****************************************************************/
void CommandHistoryManager :: CleanHistory(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : CleanHistory. Start");
	#endif

	try
	{
		// Delete commands from history
		try
		{
			// Check DLL legal user
			dbManager += dllUserCheckResult;

			// Get current time
			time_t nowSeconds;
			struct tm inpTime;
			time (&nowSeconds);
			inpTime = * localtime(&nowSeconds);

			char beginTimeString[DATE_STR_LEN] = "";
			char endTimeString[DATE_STR_LEN] = "";
			strftime(endTimeString, DATE_STR_LEN, "%Y-%m-%d %H:%M:%S", &inpTime);

			// Calculate first date
			int day, mon, year, hour, min, sec;
			sscanf_s(endTimeString, "%d-%d-%d %d:%d:%d", &year, &mon, &day, &hour, &min, &sec);
			sprintf(beginTimeString, "%04d-%02d-%02d %02d:%02d:%02d", year, mon - 2, day, hour, min, sec);
			sprintf(endTimeString, "%04d-%02d-%02d %02d:%02d:%02d", year, mon - 1, day, hour, min, sec);

			// Get parameter values
			char sql[SQL_SIZE * 2] = "";

			// Prepare sql query
			sprintf(sql, "DELETE FROM CommandParameters \
						  WHERE ID in (SELECT PID \
									   FROM CommandParameterList \
									   WHERE HID in (SELECT ID \
													 FROM CommandsHistory \
													 WHERE ExecTime BETWEEN '%s' AND '%s'));\
						  DELETE FROM CommandsHistory WHERE ExecTime BETWEEN '%s' AND '%s'; ", beginTimeString, endTimeString, beginTimeString, endTimeString);
		
			// Insert new command to history
			dbManager -> Execute(sql);
		
		}
		catch(DBException & ex)
		{
			char errMsg[ERROR_MSG_MAXLEN];
			ex.GetMessage(errMsg);
			WriteToLog(errMsg);
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
			WriteToLog("CommandHistoryManager : CleanHistory. Error of working with memory!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CMD_HIST)
		WriteToLog("CommandHistoryManager : CleanHistory. Done");
	#endif
}

#pragma endregion

#pragma region LOG

/****************************************************************

   Class : CommandHistoryManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  CommandHistoryManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion