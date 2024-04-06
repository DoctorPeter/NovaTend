/****************************************************************

   Solution : NovaTend

   Project : z-dbconnect-01.dll

   Module : SQLiteDatabaseManager.h

   Description :  this module defines interface of
				  class SQLiteDatabaseManager and 
				  additioanl classes: SQLiteResultSetMetaData, 
				  SQLiteResultSet

*****************************************************************/

#include "DatabaseManager.h"

#ifndef SQLITEDBMANAGER_H
#define SQLITEDBMANAGER_H

#include "SQLite\sqlite3.h"

/****************************************************************

   Class :  SQLiteResultSetMetaData

   Description : contains metadata for some ResultSet

*****************************************************************/
class DBMANAGER_API SQLiteResultSetMetaData : public ResultSetMetaData {
	
	public:
		
		// Constructor
		SQLiteResultSetMetaData(void);

		// Destructor
		virtual ~SQLiteResultSetMetaData(void);

		// Convert type code to string value
		virtual void TypeToString(int type, char * ret);
};


/****************************************************************

   Class :  SQLiteResultSet

   Description : describes result of any query

*****************************************************************/
class DBMANAGER_API SQLiteResultSet : public ResultSet {

	private:

		// Database handle
		sqlite3 * hDatabase; 

		//SQL statement
		struct sqlite3_stmt * hStatement;

		// Number of rows
		unsigned long lNumRows;

		// Numbers of columns
		unsigned long lNumCols;

		// Number of current row
		unsigned long currRowInd;

		// List of pointers to buffers for binding
		void * pBindBuffers[MAX_COLUMN_COUNT];

		// Fetch row
		bool FetchRow(void);

		// Reset statement
		void Reset(void);

		// Load data
		void LoadData(void);

		// SQLite exceptions handler
		void HandleError(void);

		// SQLite exceptions handler
		void HandleError(const char * errMsg, int errorCode);

	public:

		// Constructor
		SQLiteResultSet(sqlite3 * hDatabase, struct sqlite3_stmt * hStatement);

		// Destructor
		~SQLiteResultSet(void);

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

   Class : SQLiteDatabaseManager

   Description : provides access to database for SQLite

*****************************************************************/
class DBMANAGER_API	SQLiteDatabaseManager : public DatabaseManager
{
	private:

		// Database handle
		sqlite3 * hDatabase; 

		//SQL statement
		struct sqlite3_stmt * hStatement;
		
		// Error handling 
		
		// SQLite exceptions handler
		void HandleError(void);

		// SQLite exceptions handler
		void HandleError(const char * errMsg, int errorCode);


	public:

		// Constructor
		SQLiteDatabaseManager(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~SQLiteDatabaseManager(void);
		
		// Connect to database
		virtual int Connect(char * dataSource = "", char * userName = "", char * password = "", int timeout = 120);

		// Deisconnect from database
		virtual int Disconnect(void);

		// Execute SQl query
		virtual long Execute(const char * sql);

		// Execute SQL SELECT query
		virtual ResultSet * ExecuteSelectQuery(const char * sql);
		
		// Commit work
		virtual int Commit(void);

		// Rollback work
		virtual int Rollback(void);
};

#endif