/****************************************************************

   Solution : NovaTend

   Project : z-dbconnect-01.dll

   Module : DatabaseManager.h

   Description :  this module defines interface of
				  class DatabaseManager

*****************************************************************/

#include "stdafx.h"

#include <LogWriter.h>
#include <Encryptor.h>

#ifdef ZDBCONNECT01_EXPORTS
#define DBMANAGER_API __declspec(dllexport)
#else
#define DBMANAGER_API __declspec(dllimport)
#endif


#ifndef DBMANAGER_H
#define DBMANAGER_H

// Restricions definition

// Maximum count of table colums
#define MAX_COLUMN_COUNT	256

// Maximum size of column name
#define COLUMN_TITLE_SIZE	128



// Column restrictions

// Column value is NOT NULL
#define COLUMN_NOT_NULL		0

// Column value is NOT NULL
#define COLUMN_NULL			1

// Column value is undefined
#define COLUMN_NOT_KNOWN	2



// ODBC exceptions restrictions

// Error message maximum length
#define ERROR_MSG_MAXLEN	256

// State maximum length
#define STATE_LEN				6

// Row status array maximum length
#define ROW_STATUS_ARRAY_SIZE	10


// Error codes

// Succesfull disconnect
#define DISCONNECT_OK 0

// Disconnect failed
#define DISCONNECT_FIALED 1

// Succesfull connect
#define CONNECT_OK 0

// Connect failed
#define CONNECT_FIALED 1


// Structure of column metadata
typedef struct Column {
	    
	// Column name
	char title[COLUMN_TITLE_SIZE];

	// Column type
	int type;

	// Column value size
	unsigned int size;

	// Count of decimal digits
	int decimSize;

	// Nullable status
	// 0: NOT-NULL, 1: NULL, 2: NOT-KNOWN
	int nullable; 

} COLUMN, *PCOLUMN;


/****************************************************************

   Class :  ResultSetMetaData

   Description : contains metadata for some ResultSet

*****************************************************************/
class DBMANAGER_API ResultSetMetaData {
	
	private:
		
		// number of columns in the ResultSet
		int nNumCols; 

		// List of columns
		PCOLUMN colsList[MAX_COLUMN_COUNT];

	public:
		
		// Constructor
		ResultSetMetaData(void);

		// Destructor
		virtual ~ResultSetMetaData(void);

		// Set count of columns
		void SetNumCols(int n);

		// Get columns count
		int GetColumnCount(void);

		// Add column to list
		void AddColumn(PCOLUMN col);

		// Get column from list by index
		PCOLUMN GetColumn(int n);

		// Get column from list by title
		PCOLUMN GetColumn(const char * title);

		// Convert type code to string value
		virtual void TypeToString(int type, char * ret);

		// Convert nullable value to string
		void NullableToString(int nullable, char * ret);
};


/****************************************************************

   Class :  DBException

   Description : Database exception handling

*****************************************************************/
class DBMANAGER_API DBException {
	private:
		
		// Error message string
		char strErrMsg[ERROR_MSG_MAXLEN];

		// Error code
		int nErrCode;

	public:

		// Constructor
		DBException(const char * msg, int code);

		// Destructor
		virtual ~DBException(void);

		// Get message string
		void GetMessage(char * buff);

		// Get error code
		int GetCode(void);
};


/****************************************************************

   Class :  ResultSet

   Description : describes result of any query

*****************************************************************/
class DBMANAGER_API ResultSet {

	public:

		// Constructor
		ResultSet(void);

		// Destructor
		virtual ~ResultSet(void);

		// Get metadata for this ResultSet
		virtual ResultSetMetaData * GetMetaData(void) = NULL;

		// Move cursor to next row
		virtual bool MoveNext(void) = NULL;

		// Move cursor to previous row
		virtual bool MovePrevious(void) = NULL;

		// Move cursor to first row
		virtual bool MoveFirst(void) = NULL;

		// Move cursor to last row
		virtual bool MoveLast(void) = NULL;

		// Bind data to string buffer
		virtual bool Bind(int colNum, char * buff, int buffLen) = NULL;

		// Bind data to buffer with targetType
		virtual bool Bind(int colNum, void * buff, int buffLen, int targetType) = NULL;

		// Get count of rows
		virtual unsigned long GetNumRows(void) = NULL;
};


/****************************************************************

   Class : DatabaseManager

   Description : Abstract class. Provides general
				 structure of class of access to database.

*****************************************************************/
class DBMANAGER_API	DatabaseManager : public SystemBase
{
	protected:

		// Log writer instance
		LogWriter * logWriter;

		// Encryptor instance
		Encryptor * encryptor;

		// connection timeout
		int nConnTimeOut; 

		// opening flag
		bool bOpened;

	public:

		// Constructor
		DatabaseManager(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~DatabaseManager(void);

		// Connect to database
		virtual int Connect(char * dataSource = "", char * userName = "", char * password = "", int timeout = 120) = NULL;

		// Deisconnect from database
		virtual int Disconnect(void) = NULL;

		// Execute SQl query
		virtual long Execute(const char * sql) = NULL;

		// Execute SQL SELECT query
		virtual ResultSet * ExecuteSelectQuery(const char * sql) = NULL;
				
		// Commit work
		virtual int Commit(void) = NULL;

		// Rollback work
		virtual int Rollback(void) = NULL;

		// Set timeout value
		void SetTimeout(int n);

		// Get timeout value
		int GetTimeout(void);

		// Check coonnection
		bool Opened(void);
		
		// Write message to log-file
		int WriteToLog(char * message);
};

#endif