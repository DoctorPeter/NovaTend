/****************************************************************

   Solution : NovaTend

   Project : z-dbconnect-01.dll

   Module : ODBCDatabaseManager.h

   Description :  this module defines interface of
				  class ODBCDatabaseManager and 
				  additioanl classes: ODBCException, 
				  ResultSetMetaData, ResultSet

*****************************************************************/

#include "DatabaseManager.h"

#include <sql.h>
#include <sqlext.h>

#ifndef ODBCDBMANAGER_H
#define ODBCDBMANAGER_H

/****************************************************************

   Class :  ODBCResultSetMetaData

   Description : contains metadata for some ResultSet

*****************************************************************/
class DBMANAGER_API ODBCResultSetMetaData : public ResultSetMetaData {
	
	public:
		
		// Constructor
		ODBCResultSetMetaData(void);

		// Destructor
		virtual ~ODBCResultSetMetaData(void);

		// Convert type code to string value
		virtual void TypeToString(int type, char * ret);
};


/****************************************************************

   Class :  ODBCResultSet

   Description : describes result of any query

*****************************************************************/
class DBMANAGER_API ODBCResultSet : public ResultSet {

	private:

		// SQL statement handle
		SQLHSTMT * hStmt;	

		// number of rows
		SQLUINTEGER lNumRows;

		// rows status array
		SQLUSMALLINT nRowStatusArray[ROW_STATUS_ARRAY_SIZE]; 

		// Error handling members

		// status record from which the application seeks information
		SQLSMALLINT iRec;

		// State buffer
		SQLCHAR cState[STATE_LEN];

		// Message buffer
		SQLCHAR cMsg[SQL_MAX_MESSAGE_LENGTH];

		// Error code
		SQLINTEGER nErr;

		// Message length
		SQLSMALLINT nMsg;
		
		// ODBC exceptions handler
		void HandleError(void);

	public:

		// Constructor
		ODBCResultSet(SQLHSTMT * stmt);

		// Destructor
		~ODBCResultSet(void);

		// Get metadata for this ResultSet
		virtual ResultSetMetaData * GetMetaData(void);

		// Move cursor to next row
		virtual bool MoveNext(void);

		// Move cursor to previous row
		virtual bool MovePrevious(void);

		// Move cursor to first row
		virtual bool MoveFirst(void);

		// Move cursor to last row
		virtual bool MoveLast(void);

		// Bind data to string buffer
		virtual bool Bind(int colNum, char * buff, int buffLen);

		// Bind data to buffer with targetType
		virtual bool Bind(int colNum, void * buff, int buffLen, int targetType);

		// Get count of rows
		virtual unsigned long GetNumRows(void);
};

/****************************************************************

   Class : ODBCDatabaseManager

   Description : provides access to database via ODBC

*****************************************************************/
class DBMANAGER_API	ODBCDatabaseManager : public DatabaseManager
{
	private:

		// environment handle
		SQLHENV hEnv; 

		// database handle
		SQLHDBC hDbc; 

		// statement handle
		SQLHSTMT hStmt; 

		// Error handling 

		// status record from which the application seeks information
		SQLSMALLINT iRec;

		// State buffer
		SQLCHAR cState[STATE_LEN];

		// Message buffer
		SQLCHAR cMsg[SQL_MAX_MESSAGE_LENGTH];

		// Error code
		SQLINTEGER nErr;

		// Message length
		SQLSMALLINT nMsg;
		
		// ODBC exceptions handler
		void HandleError(const char * type);


	public:

		// Constructor
		ODBCDatabaseManager(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~ODBCDatabaseManager(void);
		
		// Connect to database
		virtual int Connect(char * dataSource = "", char * userName = "", char * password = "", int timeout = 120);

		// Deisconnect from database
		virtual int Disconnect(void);

		// Execute SQl query
		virtual long Execute(const char * sql);

		// Execute SQL SELECT query
		virtual ResultSet * ExecuteSelectQuery(const char * sql);

		// Execute SQL SELECT query
		ResultSet * ExecuteSelectQuery(const char * sql, int cursorType, bool scrollable);
				
		// Commit work
		virtual int Commit(void);

		// Rollback work
		virtual int Rollback(void);
};

#endif