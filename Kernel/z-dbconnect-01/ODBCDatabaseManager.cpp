/****************************************************************

   Solution : NovaTend

   Project : z-dbconnect-01.dll

   Module : ODBCDatabaseManager.cpp

   Description :  this module implements methods of
				  class ODBCDatabaseManager and 
				  additioanl classes: ODBCException, 
				  ResultSetMetaData, ResultSet

*****************************************************************/

#include "stdafx.h"

#include "ODBCDatabaseManager.h"
#include <stdio.h>


// z-dbconnect-01.dll definition structure
extern DLL_COMMON_DEFINITION zDBConnectDefinition;

#pragma region ODBCResultSetMetaData methods

/****************************************************************

		Implementation methods of class ODBCResultSetMetaData
   
*****************************************************************/

/****************************************************************

   Class :  ODBCResultSetMetaData

   Method : Constructor

   
*****************************************************************/
ODBCResultSetMetaData :: ODBCResultSetMetaData(void)
{
	// For future use
}

/****************************************************************

   Class :  ODBCResultSetMetaData

   Method : Destructor

   
*****************************************************************/
ODBCResultSetMetaData :: ~ODBCResultSetMetaData(void)
{
	// For future use
}

/****************************************************************

   Class : ODBCResultSetMetaData

   Method : TypeToString

   Parameters :
			Input : 
				type - column type code

			Output:
				ret - string of column type name

	Description : Convert type code to string value

*****************************************************************/
void ODBCResultSetMetaData :: TypeToString(int type, char * ret)
{
	if (ret)
	{
		switch(type)
		{
			// Character type
			case SQL_CHAR:
				strcpy(ret,"CHAR");
				break;

			// Character sequence type
			case SQL_VARCHAR:
				strcpy(ret,"VARCHAR");
				break;
				
			// Long character sequence type
			case SQL_LONGVARCHAR:
				strcpy(ret,"LONG VARCHAR");
				break;

			// Unicode character type
			case SQL_WCHAR:
				strcpy(ret,"UNICODE CHAR");
				break;

			// Unicode character sequence type
			case SQL_WVARCHAR:
				strcpy(ret,"UNICODE VARCHAR");
				break;

			// Unicode long character sequence type
			case SQL_WLONGVARCHAR:
				strcpy(ret,"UNICODE LONG VARCHAR");
				break;

			/// Decimal type
			case SQL_DECIMAL:
				strcpy(ret,"DECIMAL");
				break;

			// Numeric type
			case SQL_NUMERIC:
				strcpy(ret,"NUMERIC");
				break;

			// Small integer type
			case SQL_SMALLINT:
				strcpy(ret,"SMALLINT");
				break;

			// Integer type
			case SQL_INTEGER:
				strcpy(ret,"INTEGER");
				break;

			// Float type
			case SQL_REAL:
				strcpy(ret,"REAL");
				break;

			// Float type
			case SQL_FLOAT:
				strcpy(ret,"FLOAT");
				break;

			// Double float type
			case SQL_DOUBLE:
				strcpy(ret,"DOUBLE");
				break;

			// One bit type
			case SQL_BIT:
				strcpy(ret,"BIT");
				break;
				
			// Tiny integer type
			case SQL_TINYINT:
				strcpy(ret,"TINYINT");
				break;

			// Long integer type
			case SQL_BIGINT:
				strcpy(ret,"BIGINT");
				break;

			// Binary (BLOB) type
			case SQL_BINARY:
				strcpy(ret,"BINARY");
				break;

			// Binary (BLOB) type
			case SQL_VARBINARY:
				strcpy(ret,"VARBINARY");
				break;
				
			// Binary (BLOB) type
			case SQL_LONGVARBINARY:
				strcpy(ret,"LONG VARBINARY");
				break;
				
			// Date type
			case SQL_TYPE_DATE:
			case SQL_DATE:
				strcpy(ret,"DATE");
				break;

			// Time type
			case SQL_TYPE_TIME:
			case SQL_TIME:
				strcpy(ret,"TIME");
				break;
				
			// Time stamp type
			case SQL_TYPE_TIMESTAMP:
			case SQL_TIMESTAMP:
				strcpy(ret,"TIMESTAMP");
				break;
				
			// Month interval type
			case SQL_INTERVAL_MONTH:
				strcpy(ret,"INTERVAL MONTH");
				break;

			// Year interval type
			case SQL_INTERVAL_YEAR:
				strcpy(ret,"INTERVAL YEAR");
				break;

			// Year to month interval type
			case SQL_INTERVAL_YEAR_TO_MONTH:
				strcpy(ret,"INTERVAL YEAR TO MONTH");
				break;

			// Day interval type
			case SQL_INTERVAL_DAY:
				strcpy(ret,"INTERVAL DAY");
				break;

			// Hour interval type
			case SQL_INTERVAL_HOUR:
				strcpy(ret,"INTERVAL HOUR");
				break;

			// Minute interval type 
			case SQL_INTERVAL_MINUTE:
				strcpy(ret,"INTERVAL MINUTE");
				break;

			// Second interval type
			case SQL_INTERVAL_SECOND:
				strcpy(ret,"INTERVAL SECOND");
				break;

			// Day to hour interval type
			case SQL_INTERVAL_DAY_TO_HOUR:
				strcpy(ret,"INTERVAL DAY TO HOUR");
				break;

			// Day to minute interval type
			case SQL_INTERVAL_DAY_TO_MINUTE:
				strcpy(ret,"INTERVAL DAY TO MINUTE");
				break;

			// Day to second interval type
			case SQL_INTERVAL_DAY_TO_SECOND:
				strcpy(ret,"INTERVAL DAY TO SECOND");
				break;

			// Hour to minute interval type
			case SQL_INTERVAL_HOUR_TO_MINUTE:
				strcpy(ret,"INTERVAL HOUR TO MINUTE");
				break;

			// Hour to second interval type
			case SQL_INTERVAL_HOUR_TO_SECOND:
				strcpy(ret,"INTERVAL HOUR TO SECOND");
				break;

			// Minute to second interval type
			case SQL_INTERVAL_MINUTE_TO_SECOND:
				strcpy(ret,"INTERVAL MINUTE TO SECOND");
				break;

			// GUID type
			case SQL_GUID:
				strcpy(ret,"GUID");
				break;

			// Unknown type
			default:
				strcpy(ret,"UNKNOWN");
		}
	}
}

#pragma endregion

#pragma region ODBCResultSet methods

/****************************************************************

		Implementation methods of class ODBCResultSet
   
*****************************************************************/

/****************************************************************

   Class :  ODBCResultSet

   Method : Constructor

   Parameters :
			Input : 
				stmt - SQL statement handle
   
*****************************************************************/
ODBCResultSet :: ODBCResultSet(SQLHSTMT * stmt)
{
	hStmt = stmt;		
	lNumRows = 0;
	SQLRETURN rc = SQLSetStmtAttr(*hStmt, SQL_ATTR_ROW_STATUS_PTR, nRowStatusArray, 0);
	rc = SQLSetStmtAttr(*hStmt, SQL_ATTR_ROWS_FETCHED_PTR, &lNumRows, 0);
	iRec = 1;
}

/****************************************************************

   Class :  ODBCResultSet

   Method : Destructor
   
*****************************************************************/
ODBCResultSet :: ~ODBCResultSet(void)
{
	// For future use
}

/****************************************************************

   Class : ODBCResultSet

   Method : GetMetaData

   Return : metadata for this ResultSet

   Description :  Get metadata for this ResultSet

*****************************************************************/
ResultSetMetaData * ODBCResultSet :: GetMetaData(void)
{
	
	// create metadata instance
	ResultSetMetaData * metaData = new ODBCResultSetMetaData();
	
	try
	{
		SQLSMALLINT columnCount = 0;

		// Get columns count
		SQLRETURN ret = SQLNumResultCols(*hStmt, &columnCount);

		// Validate result
		if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE) HandleError();
		
		// Set column count
		metaData -> SetNumCols(columnCount);
		

		for(int i = 1; i <= columnCount; i++)
		{
			// Allocate memory fo column meta data structure
			PCOLUMN col = (PCOLUMN)malloc(sizeof(COLUMN));

			// Check result
			if (col)
			{
				int nameLen = 0;
				strcpy(col -> title,"");
				col -> decimSize = 0;
				col -> nullable = 0;
				col -> size = 0;
				col -> type = 0;

				// Retrieve column metedata
				ret =  SQLDescribeColA(*hStmt, (SQLUSMALLINT)i, 
							(SQLCHAR*)col -> title,
							(SQLSMALLINT)sizeof(col -> title),
							(SQLSMALLINT*)&nameLen,
							(SQLSMALLINT*)&(col -> type),
							(SQLULEN*)&(col -> size),
							(SQLSMALLINT*)&(col -> decimSize),
							(SQLSMALLINT*)&(col -> nullable));			

				// validate error
				if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE) HandleError();

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

   Class : ODBCResultSet

   Method : MoveNext

   Return : false - if no more data, else - true

   Description :  Move cursor to next row

*****************************************************************/
bool ODBCResultSet :: MoveNext(void)
{
	try
	{
		// Fetch next row
		SQLRETURN rc = SQLFetchScroll(*hStmt, SQL_FETCH_NEXT, 0);

		// validate result
		if (rc == SQL_NO_DATA) return false;
		if (rc == SQL_ERROR) HandleError(); 
	}
	catch(...) 
	{
		// error handling
		HandleError();
	}

	return true;
}

/****************************************************************

   Class : ODBCResultSet

   Method : MovePrevious

   Return : false - if no more data, else - true

   Description :  Move cursor to previous row

*****************************************************************/
bool ODBCResultSet :: MovePrevious(void)
{
	try
	{
		// Fetch previous row
		SQLRETURN rc = SQLFetchScroll(*hStmt, SQL_FETCH_PRIOR, 0);

		// Validate result
		if (rc == SQL_NO_DATA || rc < 0) return false;
		if (rc == SQL_ERROR) HandleError();
	}
	catch(...)
	{ 
		// Error handling
		HandleError();
	}
	
	return true;
}

/****************************************************************

   Class : ODBCResultSet

   Method : MoveFirst

   Return : false - if no more data, else - true

   Description :  Move cursor to first row

*****************************************************************/
bool ODBCResultSet :: MoveFirst(void)
{
	try
	{		
		// Fetch first row
		SQLRETURN rc = SQLFetchScroll(*hStmt, SQL_FETCH_FIRST, 0);

		// Validate result
		if (rc == SQL_NO_DATA || rc < 0) return false;
		if (rc == SQL_ERROR) HandleError();
	}
	catch(...)
	{ 
		// Error handling
		HandleError(); 
	}
	
	return true;
}

/****************************************************************

   Class : ODBCResultSet

   Method : MoveLast

   Return : false - if no more data, else - true

   Description :  Move cursor to last row

*****************************************************************/
bool ODBCResultSet :: MoveLast(void)
{
	try
	{		
		// Fetch first row
		SQLRETURN rc = SQLFetchScroll(*hStmt, SQL_FETCH_LAST, 0);

		// Validate result
		if (rc == SQL_NO_DATA || rc < 0) return false;
		if (rc == SQL_ERROR) HandleError();
	}
	catch(...)
	{ 
		
		// Error handling
		HandleError(); 
	}
	
	return true;
}

/****************************************************************

   Class : ODBCResultSet

   Method : Bind
   
   Parameters :
			Input : 
				colNum - number of column
				buff - buffer for binring
				buffLen - size of buffer
   
   Return : binding succesfull result

   Description : Bind data to string buffer

*****************************************************************/
bool ODBCResultSet :: Bind(int colNum, char * buff, int buffLen)
{
	try
	{
		SQLINTEGER sz = 0;			
		// Bind column
		// NOTE : resulting value in buffer will covert to string value
		SQLRETURN rc = SQLBindCol(*hStmt, colNum, SQL_C_CHAR, buff, buffLen, (SQLLEN *)&sz);

		// vaidate result
		if (rc == SQL_ERROR) HandleError();
	}
	catch(...)
	{ 
		// Error handling
		HandleError(); 
	}
	
	return true;
}

/****************************************************************

   Class : ODBCResultSet

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
bool ODBCResultSet :: Bind(int colNum, void * buff, int buffLen, int targetType)
{
	try
	{
		SQLINTEGER sz = 0;			
		
		// Bind data
		// NOTE : type of buffer data will accord to targetType
		SQLRETURN rc = SQLBindCol(*hStmt, colNum, targetType, buff, buffLen, (SQLLEN *)&sz);

		// vaidate result
		if (rc == SQL_ERROR) HandleError();
	}
	catch(...)
	{ 
		// Error handling
		HandleError(); 
	}
	
	return true;
}


/****************************************************************

   Class : ODBCResultSet

   Method : GetNumRows
   
   Return : count of rows

   Description : Get count of rows

*****************************************************************/
unsigned long ODBCResultSet :: GetNumRows(void)
{
	 return lNumRows;
}
/****************************************************************

   Class : ODBCResultSet

   Method : HandleError
   
   Description : ODBC exceptions handler

*****************************************************************/
void ODBCResultSet :: HandleError(void)
{
	SQLGetDiagRecA(SQL_HANDLE_STMT, *hStmt, iRec, cState, &nErr, cMsg, sizeof(cMsg), &nMsg);

	throw DBException((char*)cMsg, nErr);
}

#pragma endregion

#pragma region ODBCDatabaseManager methods

/****************************************************************

		Implementation methods of class ODBCDatabaseManager
   
*****************************************************************/

/****************************************************************

   Class : ODBCDatabaseManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
ODBCDatabaseManager :: ODBCDatabaseManager(unsigned long dllUserID, LogWriter * logWriter) : DatabaseManager(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
		WriteToLog("ODBC manager: constructor");
	#endif

	hEnv = NULL;
	hDbc = NULL;
	hStmt = NULL;
	SetTimeout(90);
	bOpened = false;
	cState[0] = 0;
	cMsg[0] = 0;
	iRec = 1;
}

/****************************************************************

   Class : ODBCDatabaseManager

   Method : Destructor

*****************************************************************/
ODBCDatabaseManager :: ~ODBCDatabaseManager(void)
{
	Disconnect();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
		WriteToLog("ODBC manager: destructor");
	#endif
}


/****************************************************************

   Class : ODBCDatabaseManager

   Method : Connect
   
   Parameters :
			Input : 
				dataSource - ODBC data source
				userName - user name
				password - password
  
   Return : error code

   Description : Connect to database

*****************************************************************/
int ODBCDatabaseManager :: Connect(char * dataSource, char * userName, char * password, int timeout)
{
	if(Opened())
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
			WriteToLog("ODBC manager: can't connect. DB already opened!");
		#endif

		return CONNECT_FIALED;
	}
	
	SQLRETURN ret = 0;
	
	try
	{
		// Allocate SQL environment
		ret = SQLAllocEnv(&hEnv);

		if (ret == SQL_ERROR) 
			HandleError("ENV");
		else 
			if (ret == SQL_INVALID_HANDLE || ret < 0) HandleError("ENV");
	}
	catch(...)
	{
		HandleError("ENV");
	}

	try
	{
		// Connect to SQL environment
		ret = SQLAllocConnect(hEnv, &hDbc);

		if (ret == SQL_ERROR)
			HandleError("ENV");
		else
			if (ret == SQL_INVALID_HANDLE || ret < 0)
			HandleError("ENV");
	}
	catch(...)
	{
		HandleError("ENV");
	}

	// set connection timeout
	SetTimeout(timeout);
	SQLSetConnectAttr(hDbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)nConnTimeOut, 0); 

	try
	{
		int nUserLen = (userName != NULL) ? strlen(userName) : 0;
		int nPwLen = (password != NULL) ? strlen(password) : 0;

		// Connect to database via ODBC driver
		ret = SQLConnectA(hDbc, (SQLCHAR*)dataSource, strlen(dataSource),
						(SQLCHAR*)userName, nUserLen, 
						(SQLCHAR*)password, nPwLen); 

		// Validate result
		if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE || ret < 0) HandleError("DBC");

		// Allocate SQL statement
		ret = SQLAllocStmt(hDbc, &hStmt);

		// Validate result
		if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE || ret < 0) HandleError("DBC");

		// Set opening flag and check DLL legal user
		bOpened = true && !((bool)dllUserCheckResult);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
			char message[256];
			sprintf(message, "ODBC manager: connected to %s as %s with password %s", dataSource, userName, password);
			WriteToLog(message);
		#endif

		return CONNECT_OK;
	}
	catch(...)
	{
		HandleError("DBC");
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
		char message[256];
		sprintf(message, "ODBC manager: can't connect to %s as %s with password %s", dataSource, userName, password);
		WriteToLog(message);
	#endif

	return CONNECT_FIALED;
}

/****************************************************************

   Class : ODBCDatabaseManager

   Method : Disconnect
  
   Return : error code

   Description : Disconnect from database

*****************************************************************/
int ODBCDatabaseManager :: Disconnect(void)
{
	if(Opened())
	{
		SQLFreeStmt(hStmt, SQL_CLOSE);
		SQLDisconnect(hDbc);
		SQLFreeConnect(hDbc);
		SQLFreeEnv(hEnv);
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

   Class : ODBCDatabaseManager

   Method : Execute
   
   Parameters :
			Input :
				sql - SQL query text

   Return : count of selected / inserted/ updated/ deleted records

   Description : Execute SQL query

*****************************************************************/
long ODBCDatabaseManager :: Execute(const char * sql)
{
	try
	{
		// Only for opened datasource
		if (!bOpened)
			throw DBException("Connection not opened", -1);
		
		// Close SQL statement
		SQLFreeStmt(hStmt, SQL_CLOSE);

		// Allocate SQl statement
		SQLRETURN ret = SQLAllocStmt(hDbc, &hStmt);

		// Validate result
		if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE || ret < 0) HandleError("DBC");

		// Prepare sql query
		ret = SQLPrepareA(hStmt, (unsigned char*)sql, SQL_NTS);
		if(ret == SQL_ERROR) HandleError("STMT");

		// Execute sql query
		ret = SQLExecute(hStmt);

		// Validate result
		if(ret == SQL_ERROR || ret < 0)	HandleError("STMT");
		
		SQLLEN count = -1;

		// Get count of records
		ret = SQLRowCount(hStmt, &count);

		return count;
	}
	catch(...)
	{
		// Error handling
		HandleError("STMT");
	}
	
	return -2;
}

/****************************************************************

   Class : ODBCDatabaseManager

   Method : ExecuteSelectQuery
   
   Parameters :
			Input :
				sql - SQL query text

   Return : count of selected records

   Description : Execute SELECT SQL query

*****************************************************************/
ResultSet * ODBCDatabaseManager :: ExecuteSelectQuery(const char * sql)
{
	try
	{
		// Only for opened datasource
		if(!bOpened)
			throw DBException("Connection not opened", -1);
		
		// Close SQL statement
		SQLFreeStmt(hStmt, SQL_CLOSE);

		// Allocate SQl statement
		SQLRETURN ret = SQLAllocStmt(hDbc, &hStmt);

		// Validate result
		if(ret == SQL_ERROR || ret == SQL_INVALID_HANDLE || ret < 0) HandleError("DBC");

		// Set cursor
		ret = SQLSetStmtAttr(hStmt, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_DYNAMIC, SQL_IS_INTEGER);
		if (ret < 0) HandleError("STMT");
		
		// Execute SQL query
		ret = SQLExecDirectA(hStmt, (SQLCHAR*)sql, strlen(sql));

		// validate result
		if(ret == SQL_ERROR) HandleError("STMT");
	}
	catch(...)
	{
		// Error handling
		HandleError("STMT");
	}

	return new ODBCResultSet(&hStmt);
}

/****************************************************************

   Class : ODBCDatabaseManager

   Method : ExecuteSelectQuery
   
   Parameters :
			Input :
				sql - SQL query text
				cursorType - cursor type
				scrollable - scrollable flag

   Return : count of selected records

   Description : Execute SELECT SQL query

*****************************************************************/
ResultSet * ODBCDatabaseManager :: ExecuteSelectQuery(const char * sql, int cursorType, bool scrollable)
{
	try
	{
		// Only for opened datasource
		if (!bOpened)
			throw DBException("Connection not opened", -1);
							
		// Validate cursor type
		if ((cursorType != SQL_CURSOR_DYNAMIC) &&
		   (cursorType != SQL_CURSOR_FORWARD_ONLY) &&
		   (cursorType != SQL_CURSOR_KEYSET_DRIVEN) &&
		   (cursorType != SQL_CURSOR_STATIC))
				throw DBException("Invalid cursor type", -1);
		
		// Close SQL statement
		SQLFreeStmt(hStmt, SQL_CLOSE);

		// Allocate SQL statement
		SQLRETURN ret = SQLAllocStmt(hDbc, &hStmt);

		// Validate result
		if (ret == SQL_ERROR || ret == SQL_INVALID_HANDLE || ret < 0) HandleError("DBC");

		// Set cursor
		ret = SQLSetStmtAttr(hStmt, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)cursorType, SQL_IS_INTEGER);

		// Validate result
		if (ret < 0) HandleError("STMT");

		if (scrollable)
		{
			// Set scrolable result attribute
			ret = SQLSetStmtAttr(hStmt, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER)SQL_SCROLLABLE, SQL_IS_INTEGER);
			if(ret < 0)	HandleError("STMT");
		}

		// Execute SQL query
		ret = SQLExecDirectA(hStmt, (SQLCHAR*)sql, strlen(sql));

		// validate result
		if(ret == SQL_ERROR) HandleError("STMT");

	}
	catch(...)
	{ 
		// Error handling
		HandleError("STMT"); 
	}

	return new ODBCResultSet(&hStmt);
}

/****************************************************************

   Class : ODBCDatabaseManager

   Method : Commit
   
   Return : commit succesfull

   Description : Commit work

*****************************************************************/
int ODBCDatabaseManager :: Commit(void)
{
	SQLRETURN ret = SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_COMMIT);
	if (ret == SQL_ERROR || ret == SQL_INVALID_HANDLE)
		throw DBException("Commit failed", ret);
	
	return true;
}

/****************************************************************

   Class : ODBCDatabaseManager

   Method : Rollback
   
   Return : Rollback succesfull

   Description : Rollback work

*****************************************************************/
int ODBCDatabaseManager :: Rollback(void)
{
	SQLRETURN ret = SQLEndTran(SQL_HANDLE_DBC, hDbc,SQL_ROLLBACK);
	if (ret == SQL_ERROR || ret == SQL_INVALID_HANDLE)
		throw DBException("Rollback failed", ret);
	
	return true;
}

/****************************************************************

   Class : ODBCDatabaseManager

   Method : HandleError
   
   Parameters :
			Input :
				type - type description string

   Description :  ODBC exceptions handler

*****************************************************************/
void ODBCDatabaseManager :: HandleError(const char * type)
{
	try
	{
		// Validate type
		if(strcmp(type,"STMT") == 0)
			SQLGetDiagRecA(SQL_HANDLE_STMT, hStmt, iRec, cState, &nErr, cMsg, sizeof(cMsg), &nMsg);		
		else if(strcmp(type,"ENV") == 0)
			SQLGetDiagRecA(SQL_HANDLE_ENV, hEnv, iRec,cState, &nErr, cMsg, sizeof(cMsg), &nMsg);		
		else if(strcmp(type,"DBC") == 0)
			SQLGetDiagRecA(SQL_HANDLE_DBC, hDbc, iRec, cState, &nErr, cMsg, sizeof(cMsg), &nMsg);		
	}
	catch(...)
	{
		// throw ODBCException
		throw DBException("Database error", 0);
	}

	// throw ODBCException
	throw DBException((char*)cMsg, nErr);
}

#pragma endregion