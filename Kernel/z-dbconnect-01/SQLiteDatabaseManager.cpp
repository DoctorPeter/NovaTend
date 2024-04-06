/****************************************************************

   Solution : NovaTend

   Project : z-dbconnect-01.dll

   Module : SQLiteDatabaseManager.cpp

   Description :  this module implements methods of
				  class ODBCDatabaseManager and 
				  additioanl classes:
				  SQLiteResultSetMetaData, SQLiteResultSet

*****************************************************************/

#include "stdafx.h"

#include "SQLiteDatabaseManager.h"
#include <stdio.h>


// z-dbconnect-01.dll definition structure
extern DLL_COMMON_DEFINITION zDBConnectDefinition;

#pragma region SQLiteResultSetMetaData methods

/****************************************************************

		Implementation methods of class SQLiteResultSetMetaData
   
*****************************************************************/

/****************************************************************

   Class :  SQLiteResultSetMetaData

   Method : Constructor

   
*****************************************************************/
SQLiteResultSetMetaData :: SQLiteResultSetMetaData(void)
{
	// For future use
}

/****************************************************************

   Class :  ODBCResultSetMetaData

   Method : Destructor

   
*****************************************************************/
SQLiteResultSetMetaData :: ~SQLiteResultSetMetaData(void)
{
	// For future use
}

/****************************************************************

   Class : SQLiteResultSetMetaData

   Method : TypeToString

   Parameters :
			Input : 
				type - column type code

			Output:
				ret - string of column type name

	Description : Convert type code to string value

*****************************************************************/
void SQLiteResultSetMetaData :: TypeToString(int type, char * ret)
{
	if (ret)
	{
		switch(type)
		{
			// Integer type
			case SQLITE_INTEGER:
				strcpy(ret,"INTEGER");
				break;

			// Float type
			case SQLITE_FLOAT:
				strcpy(ret,"FLOAT");
				break;
				
			// BLOB type
			case SQLITE_BLOB:
				strcpy(ret,"BLOB");
				break;

			// NULL type
			case SQLITE_NULL:
				strcpy(ret,"NULL");
				break;

			// Text type
			case SQLITE_TEXT:
				strcpy(ret,"TEXT");
				break;

			// Unknown type
			default:
				strcpy(ret,"UNKNOWN");
		}
	}
}

#pragma endregion

#pragma region SQLiteResultSet methods

/****************************************************************

		Implementation methods of class SQLiteResultSet
   
*****************************************************************/

/****************************************************************

   Class :  SQLiteResultSet

   Method : Constructor

   Parameters :
			Input : 
				stmt - SQL statement handle
   
*****************************************************************/
SQLiteResultSet :: SQLiteResultSet(sqlite3 * hDatabase, struct sqlite3_stmt * hStatement)
{
	this -> hDatabase = hDatabase;		
	this -> hStatement = hStatement;

	for (int i = 0; i < MAX_COLUMN_COUNT; i++)
		pBindBuffers[i] = NULL;
	
	lNumCols = sqlite3_column_count(hStatement);
	lNumRows = 0;

	while(FetchRow()) lNumRows++;
	Reset();
}

/****************************************************************

   Class :  SQLiteResultSet

   Method : Destructor
   
*****************************************************************/
SQLiteResultSet :: ~SQLiteResultSet(void)
{
	sqlite3_finalize(hStatement);
}

/****************************************************************

   Class : SQLiteResultSet

   Method : FetchRow

   Return : TRUE - if row was fetched

   Description :  Fetch row

*****************************************************************/
bool SQLiteResultSet :: FetchRow(void) 
{
	int rc = sqlite3_step(hStatement);

	switch(rc)
	{
		case SQLITE_BUSY:
			HandleError("FetchRow() SQLITE_BUSY", SQLITE_BUSY);
			return false;

		case SQLITE_DONE:
			return false;

		case SQLITE_ROW:
			return true;

		case SQLITE_ERROR:
			HandleError(sqlite3_errmsg(hDatabase), SQLITE_ERROR);
			return false;

		case SQLITE_MISUSE:
			HandleError("FetchRow() SQLITE_MISUSE", SQLITE_MISUSE);
			return false;
	}

	return false;
}

/****************************************************************

   Class : SQLiteResultSet

   Method : Reset

   Description :  Reset statement

*****************************************************************/
void SQLiteResultSet :: Reset(void)
{
	currRowInd = 0;
	if (sqlite3_reset(hStatement) != SQLITE_OK)
		HandleError();
}

/****************************************************************

   Class : SQLiteResultSet

   Method : LoadData

   Description :  Load current data

*****************************************************************/
void SQLiteResultSet :: LoadData(void)
{
	for (int i = 0; i < lNumCols; i++)
	{
		if (pBindBuffers[i])
		{
			switch (sqlite3_column_type(hStatement, i))
			{
				// Integer type
				case SQLITE_INTEGER:
				{
					int iValue = sqlite3_column_int(hStatement, i);
					memcpy(pBindBuffers[i], &iValue, sizeof(int));
					break;
				}

				// Float type
				case SQLITE_FLOAT:
				{
					double dValue = sqlite3_column_double(hStatement, i);
					memcpy(pBindBuffers[i], &dValue, sizeof(double));
					break;
				}
				
				// BLOB type
				case SQLITE_BLOB:
				{
					void * vValue = (void *)sqlite3_column_blob(hStatement, i);
					int bytesCount = sqlite3_column_bytes(hStatement, i);
					memcpy(pBindBuffers[i], vValue, bytesCount);
					break;
				}

				// NULL type
				case SQLITE_NULL:
				{
					unsigned char bValue = 0;
					memcpy(pBindBuffers[i], &bValue, sizeof(unsigned char));
					break;
				}
				// Text type
				case SQLITE_TEXT:
				{
					strcpy((char *)pBindBuffers[i], (char *)sqlite3_column_text(hStatement, i));
					break;
				}
				// Unknown type
				default:
				{
					HandleError();
				}
			}
		}
	}
}

/****************************************************************

   Class : SQLiteResultSet

   Method : GetMetaData

   Return : metadata for this ResultSet

   Description :  Get metadata for this ResultSet

*****************************************************************/
ResultSetMetaData * SQLiteResultSet :: GetMetaData(void)
{
	
	// create metadata instance
	ResultSetMetaData * metaData = new SQLiteResultSetMetaData();
	
	try
	{
		int columnCount = sqlite3_column_count(hStatement);
		
		// Validate result
		if(columnCount <= 0) HandleError();
		
		// Set column count
		metaData -> SetNumCols(columnCount);
		

		for(int i = 0; i < columnCount; i++)
		{
			// Allocate memory fo column meta data structure
			PCOLUMN col = (PCOLUMN)malloc(sizeof(COLUMN));

			// Check result
			if (col)
			{
				strcpy(col -> title, sqlite3_column_name(hStatement, i));
				
				col -> size = sqlite3_column_bytes(hStatement, i);
				col -> type = sqlite3_column_type(hStatement, i);

				// ????
				col -> nullable = 0;
				col -> decimSize = 0;
				
				// Add column to list
				metaData -> AddColumn(col);
			}
		}		

	}
	catch(...)
	{ 
		// Error handling
		HandleError();
		return NULL;
	}

	return metaData;
}

/****************************************************************

   Class : SQLiteResultSet

   Method : MoveNext

   Return : false - if no more data, else - true

   Description :  Move cursor to next row

*****************************************************************/
bool SQLiteResultSet :: MoveNext(void)
{
	switch(sqlite3_step(hStatement))
	{
		// sqlite3_step() has finished executing
		case SQLITE_DONE:
			currRowInd++;
			LoadData();
			return false;

		// sqlite3_step() has another row ready
		case SQLITE_ROW:
			currRowInd++;
			LoadData();
			return true;

		default:
			HandleError();
			return false;
	}
}

/****************************************************************

   Class : SQLiteResultSet

   Method : MovePrevious

   Return : false - if no more data, else - true

   Description :  Move cursor to previous row

*****************************************************************/
bool SQLiteResultSet :: MovePrevious(void)
{
	// Check current index
	if (currRowInd > 1)
	{
		// Save current index
		unsigned long tmpRowInd = currRowInd;
		
		// Reset statement
		Reset();

		// Get new row until current index - 1
		do
		{
			MoveNext();
		} 
		while(currRowInd < tmpRowInd - 1);

		return true;

	}
	else
		return false;
}

/****************************************************************

   Class : SQLiteResultSet

   Method : MoveFirst

   Return : false - if no more data, else - true

   Description :  Move cursor to first row

*****************************************************************/
bool SQLiteResultSet :: MoveFirst(void)
{
	Reset();
	return MoveNext();
}

/****************************************************************

   Class : SQLiteResultSet

   Method : MoveLast

   Return : false - if no more data, else - true

   Description :  Move cursor to last row

*****************************************************************/
bool SQLiteResultSet :: MoveLast(void)
{
	// Check current index
	if (currRowInd < lNumRows)
	{
		// Reset statement
		Reset();

		// Get new row until current last index
		do
		{
			MoveNext();
		} 
		while(currRowInd < lNumRows);

		return true;

	}
	else
		return false;
}

/****************************************************************

   Class : SQLiteResultSet

   Method : Bind
   
   Parameters :
			Input : 
				colNum - number of column
				buff - buffer for binring
				buffLen - size of buffer
   
   Return : binding succesfull result

   Description : Bind data to string buffer

*****************************************************************/
bool SQLiteResultSet :: Bind(int colNum, char * buff, int buffLen)
{
	return Bind(colNum, buff, buffLen, sqlite3_column_type(hStatement, colNum));
}

/****************************************************************

   Class : SQLiteResultSet

   Method : Bind
   
   Parameters :
			Input : 
				colNum - number of column
				buff - buffer for binring
				buffLen - size of buffer
				targetType - column type code
   
   Return : binding succesfull result

   Description : Bind data to untyped buffer

*****************************************************************/
bool SQLiteResultSet :: Bind(int colNum, void * buff, int buffLen, int targetType)
{
	if (!buff) 
		return false;

	switch(targetType)
	{
		// Integer type
		case SQLITE_INTEGER:
			if (buffLen != sizeof(int))
				return false;
			pBindBuffers[colNum] = buff;	
			break;

		// Float type
		case SQLITE_FLOAT:
			if (buffLen != sizeof(double))
				return false;
			pBindBuffers[colNum] = buff;	
			break;
				
		// BLOB type
		case SQLITE_BLOB:
		// NULL type
		case SQLITE_NULL:
		// Text type
		case SQLITE_TEXT:
			pBindBuffers[colNum] = buff;	
			break;

		// Unknown type
		default:
			HandleError();
	}
	
	return true;
}


/****************************************************************

   Class : SQLiteResultSet

   Method : GetNumRows
   
   Return : count of rows

   Description : Get count of rows

*****************************************************************/
unsigned long SQLiteResultSet :: GetNumRows(void)
{
	 return lNumRows;
}

/****************************************************************

   Class : SQLiteResultSet

   Method : HandleError
   
   Description : ODBC exceptions handler

*****************************************************************/
void SQLiteResultSet :: HandleError(void)
{
	HandleError(sqlite3_errmsg(hDatabase), sqlite3_errcode(hDatabase));
}

/****************************************************************

   Class : SQLiteResultSet

   Method : HandleError
   
   Description : ODBC exceptions handler

*****************************************************************/
void SQLiteResultSet :: HandleError(const char * errMsg, int errorCode)
{
	throw DBException(errMsg, errorCode);
}

#pragma endregion

#pragma region SQLiteDatabaseManager methods

/****************************************************************

		Implementation methods of class SQLiteDatabaseManager
   
*****************************************************************/

/****************************************************************

   Class : SQLiteDatabaseManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
SQLiteDatabaseManager :: SQLiteDatabaseManager(unsigned long dllUserID, LogWriter * logWriter) : DatabaseManager(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
		WriteToLog("SQLite manager: constructor");
	#endif

	this -> hDatabase = NULL;		
	this -> hStatement = NULL;
	SetTimeout(90);
	bOpened = false;
}

/****************************************************************

   Class : SQLiteDatabaseManager

   Method : Destructor

*****************************************************************/
SQLiteDatabaseManager :: ~SQLiteDatabaseManager(void)
{
	Disconnect();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
		WriteToLog("SQLite manager: destructor");
	#endif
}

/****************************************************************

   Class : SQLiteDatabaseManager

   Method : Connect
   
   Parameters :
			Input : 
				dataSource - ODBC data source
				userName - user name
				password - password
  
   Return : error code

   Description : Connect to database

*****************************************************************/
int SQLiteDatabaseManager :: Connect(char * dataSource, char * userName, char * password, int timeout)
{
	// Check connection status
	if(Opened())
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
			WriteToLog("SQLite manager: can't connect. DB already opened!");
		#endif

		return CONNECT_FIALED;
	}
	
	// Open database
	if(sqlite3_open_v2(dataSource, &hDatabase, SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX, NULL) != SQLITE_OK)
		HandleError();

	// Set timeout
	SetTimeout(timeout * 1000);
	sqlite3_busy_timeout(hDatabase, nConnTimeOut);

	// Set opening flag and check DLL legal user
	bOpened = true && !((bool)dllUserCheckResult);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
	    char message[256];
		sprintf(message, "SQLite manager: connected to %s", dataSource);
		WriteToLog(message);
	#endif

	return CONNECT_OK;
}

/****************************************************************

   Class : SQLiteDatabaseManager

   Method : Disconnect
  
   Return : error code

   Description : Disconnect from database

*****************************************************************/
int SQLiteDatabaseManager :: Disconnect(void)
{
	if(Opened())
	{
		if (sqlite3_close(hDatabase) != SQLITE_OK)
			HandleError();

		bOpened = false;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
			WriteToLog("ODBC manager: disconnected from database");
		#endif

		return DISCONNECT_OK;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
			WriteToLog("ODBC manager: can't disconnect. DB is not opened!");
		#endif

		return DISCONNECT_FIALED;
	}
}

/****************************************************************

   Class : SQLiteDatabaseManager

   Method : Execute
   
   Parameters :
			Input :
				sql - SQL query text

   Return : count of selected / inserted/ updated/ deleted records

   Description : Execute SQL query

*****************************************************************/
long SQLiteDatabaseManager :: Execute(const char * sql)
{
	// Only for opened datasource
	if (!bOpened)
		throw DBException("Connection not opened", -1);

	// Prepare sql statement
	if(sqlite3_prepare_v2(hDatabase, sql, -1, &hStatement, 0) != SQLITE_OK)
		HandleError();
	
	// Column count
	int colCount = sqlite3_column_count(hStatement);

	// Exec sql statement
	switch(sqlite3_step(hStatement))
	{
		// sqlite3_step() has finished executing
		case SQLITE_DONE:
		// sqlite3_step() has another row ready
		case SQLITE_ROW:
			// Destroy statement
			sqlite3_finalize(hStatement);
			hStatement = 0;
			break;

		default:
			HandleError();
	}

	// Columns count
	return colCount;
}

/****************************************************************

   Class : SQLiteDatabaseManager

   Method : ExecuteSelectQuery
   
   Parameters :
			Input :
				sql - SQL query text

   Return : count of selected records

   Description : Execute SELECT SQL query

*****************************************************************/
ResultSet * SQLiteDatabaseManager :: ExecuteSelectQuery(const char * sql)
{
	// Only for opened datasource
	if (!bOpened)
		throw DBException("Connection not opened", -1);

	// Prepare sql statement
	if(sqlite3_prepare_v2(hDatabase, sql, -1, &hStatement, 0) != SQLITE_OK)
		HandleError();
	
	// Result set
	return new SQLiteResultSet(hDatabase, hStatement);
}

/****************************************************************

   Class : SQLiteDatabaseManager

   Method : Commit
   
   Return : commit succesfull

   Description : Commit work

*****************************************************************/
int SQLiteDatabaseManager :: Commit(void)
{
	return Execute("COMMIT;");
}

/****************************************************************

   Class : SQLiteDatabaseManager

   Method : Rollback
   
   Return : Rollback succesfull

   Description : Rollback work

*****************************************************************/
int SQLiteDatabaseManager :: Rollback(void)
{
	return Execute("ROLLBACK;");
}

/****************************************************************

   Class : SQLiteDatabaseManager

   Method : HandleError
   
   Description : ODBC exceptions handler

*****************************************************************/
void SQLiteDatabaseManager :: HandleError(void)
{
	HandleError(sqlite3_errmsg(hDatabase), sqlite3_errcode(hDatabase));
}

/****************************************************************

   Class : SQLiteResultSet

   Method : HandleError
   
   Description : ODBC exceptions handler

*****************************************************************/
void SQLiteDatabaseManager :: HandleError(const char * errMsg, int errorCode)
{
	throw DBException(errMsg, errorCode);
}

#pragma endregion