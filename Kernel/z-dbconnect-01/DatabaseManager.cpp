/****************************************************************

   Solution : NovaTend

   Project : z-dbconnect-01.dll

   Module : DatabaseManager.cpp

   Description :  this module implements methods of
				  class DatabaseManager

*****************************************************************/

#include "stdafx.h"
#include "DatabaseManager.h"

// z-dbconnect-01.dll definition structure
extern DLL_COMMON_DEFINITION zDBConnectDefinition;

#pragma region ResultSetMetaData methods

/****************************************************************

		Implementation of methods of class ResultSetMetaData
   
*****************************************************************/


/****************************************************************

   Class :  ResultSetMetaData

   Method : Constructor

   
*****************************************************************/
ResultSetMetaData :: ResultSetMetaData(void)
{
	SetNumCols(0);

	for (int i = 0; i < MAX_COLUMN_COUNT; i++)
		colsList[i] = NULL;
}

/****************************************************************

   Class :  ResultSetMetaData

   Method : Destructor

   
*****************************************************************/
ResultSetMetaData :: ~ResultSetMetaData(void)
{
	for (int i = 0; i < nNumCols; i++)
		if (colsList[i])
			free(colsList[i]);

	SetNumCols(0);
}

/****************************************************************

   Class : ResultSetMetaData

   Method : SetNumCols

   Parameters :
			Input : 
				n - count of columns

	Description : Set count of columns

*****************************************************************/
void ResultSetMetaData :: SetNumCols(int n)
{
	nNumCols = n;
}

/****************************************************************

   Class : ResultSetMetaData

   Method : GetColumnCount

   Return: count of columns

   Description : Get count of columns

*****************************************************************/
int ResultSetMetaData :: GetColumnCount(void)
{
	return nNumCols;
}

/****************************************************************

   Class : ResultSetMetaData

   Method : AddColumn

   Parameters :
			Input : 
				col - column structure

	Description : Add column to list

*****************************************************************/
void ResultSetMetaData :: AddColumn(PCOLUMN col)
{
	if (col) colsList[nNumCols++] = col;
}

/****************************************************************

   Class : ResultSetMetaData

   Method : GetColumn

   Parameters :
			Input : 
				n - column index

	Return: pointer to column

	Description : Get column from list by index

*****************************************************************/
PCOLUMN ResultSetMetaData :: GetColumn(int n)
{
	if ((n < 0) || (n > nNumCols)) 
		return NULL;
	else
		return colsList[n];
}

/****************************************************************

   Class : ResultSetMetaData

   Method : GetColumn

   Parameters :
			Input : 
				title - column name

	Return: pointer to column

	Description : Get column from list by title

*****************************************************************/
PCOLUMN ResultSetMetaData :: GetColumn(const char * title)
{
	for(int i = 0; i < nNumCols; i++)
	{
	  if(strcmp(colsList[i] -> title, title) == 0)
	  {
		return colsList[i];
	  }
	}

	return NULL;
}

/****************************************************************

   Class : ResultSetMetaData

   Method : TypeToString

   Parameters :
			Input : 
				type - column type code

			Output:
				ret - string of column type name

	Description : Convert type code to string value

*****************************************************************/
void ResultSetMetaData :: TypeToString(int type, char * ret)
{
	if (ret)
		strcpy(ret, "UNKNOWN TYPE");
}

/****************************************************************

   Class : ResultSetMetaData

   Method : NullableToString

   Parameters :
			Input : 
				nullable - nullable code

			Output:
				ret - nullable string

	Description :  Convert nullable value to string

*****************************************************************/
void ResultSetMetaData :: NullableToString(int nullable, char * ret)
{
	if (ret)
	{
		switch(nullable)
		{
				
			// Column value is NULL
			case COLUMN_NULL:
				strcpy(ret,"NULL");
				break;

			// Column value is NOt NULL
			case COLUMN_NOT_NULL:
				strcpy(ret,"NOT NULL");
				break;

			// Unknow column value
			default:
				strcpy(ret,"UNKNOWN");
		}
	}
}

#pragma endregion

#pragma region DBException methods

/****************************************************************

		Implementation methods of class DBException
   
*****************************************************************/


/****************************************************************

   Class :  DBException

   Method : Constructor

   Parameters :
			Input : 
				msg - error message string
				code - error code

*****************************************************************/
DBException :: DBException(const char * msg, int code)
{
	strcpy(strErrMsg, msg);
	nErrCode = code;
}

/****************************************************************

   Class :  DBException

   Method : Destructor

*****************************************************************/
DBException :: ~DBException(void)
{
	// For future use
}

/****************************************************************

   Class :  DBException

   Method : GetMessage

   Parameters :
			Input : 
				buff - error message string
	
	Description: Get message string


*****************************************************************/
void DBException :: GetMessage(char * buff)
{
	strcpy(buff, strErrMsg);
}

/****************************************************************

   Class :  DBException

   Method :  GetCode

   Return : error code
	
	Description: Get error code


*****************************************************************/
int DBException :: GetCode(void)
{
	return nErrCode;
}

#pragma endregion

#pragma region ResultSet methods

/****************************************************************

		Implementation methods of class ResultSet
   
*****************************************************************/


/****************************************************************

   Class :  ResultSet

   Method : Constructor
   
*****************************************************************/
ResultSet :: ResultSet(void)
{
	// For future use
}


/****************************************************************

   Class :  ResultSet

   Method : Destructor
   
*****************************************************************/
ResultSet :: ~ResultSet(void)
{
	// For future use
}

#pragma endregion

#pragma region DatabaseManager methods

/****************************************************************

   Class : DatabaseManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
DatabaseManager :: DatabaseManager(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zDBConnectDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
		WriteToLog("DatabaseManager : constructor");
	#endif
}

/****************************************************************

   Class : DatabaseManager

   Method : Destructor

*****************************************************************/
DatabaseManager :: ~DatabaseManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DBCONNECT)
		WriteToLog("DatabaseManager : destructor");
	#endif
}

/****************************************************************

   Class : DatabaseManager

   Method : SetTimeout
   
   Parameters :
			Input :
				n - timeout value in seconds

   Description : Set connection timeout value

*****************************************************************/
void DatabaseManager :: SetTimeout(int n)
{
	nConnTimeOut = n;
}

/****************************************************************

   Class : DatabaseManager

   Method : GetTimeout
   
   Return : timeout value in seconds

   Description : Get connection timeout value

*****************************************************************/
int DatabaseManager :: GetTimeout(void)
{
	 return nConnTimeOut;
}

/****************************************************************

   Class : DatabaseManager

   Method : Opened
   
   Return : true if opened, else - false

   Description : Check coonnection

*****************************************************************/
bool DatabaseManager :: Opened(void)
{
	return bOpened; 
}

/****************************************************************

   Class : ContentManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int DatabaseManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion
