/****************************************************************

   Solution : NovaTend

   Project : z-licenseman-01.dll

   Module : LicenseManager.cpp

   Description :  Implements the methods of class LicenseManager

*****************************************************************/

#include "stdafx.h"

#include "LicenseManager.h"
#include <SettingsManager.h>
#include <ODBCDatabaseManager.h>

// z-licenseman-01.dll definition structure
extern DLL_COMMON_DEFINITION zLicenseManDllDefinition;

/****************************************************************

   Class : LicenseManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
LicenseManager :: LicenseManager(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zLicenseManDllDefinition)
{
	this -> logWriter = logWriter;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : Constructor");
	#endif

	// License point list
	licensePointsList = NULL;

	// Data source name
	char dsn[NAME_LEN];

	// Name of database user
	char dbUser[NAME_LEN];

	// Password for database access
	char dbPassword[STR_VALUE_LEN];

	SettingsManager * settingsManager = new SettingsManager(zLicenseManDllDefinition.dllID);

	if (settingsManager -> GetDatabaseSourceName(dsn) != ERROR_SUCCESS)
		WriteToLog("License manager : Constructor --> Can't get DSN ");

	if (settingsManager -> GetDatabaseUserName(dbUser) != ERROR_SUCCESS)
		WriteToLog("License manager : Constructor --> Can't get db user name ");

	if (settingsManager -> GetDatabasePassword(dbPassword) != ERROR_SUCCESS)
		WriteToLog("License manager : Constructor --> Can't get db password ");

	delete settingsManager;

	try
	{
		dbManager = new ODBCDatabaseManager(zLicenseManDllDefinition.dllID, logWriter);
		
		// Connect to database
		if (dbManager -> Connect(dsn, dbUser, dbPassword) != CONNECT_OK)
			WriteToLog("License manager : Constructor --> Can't connect to db!");
		else
			ReadLicenseInfo();
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
	}
}


/****************************************************************

   Class : LicenseManager

   Method : Destructor

*****************************************************************/
LicenseManager :: ~LicenseManager(void)
{
	dbManager -> Disconnect();

	if (licensePointsList)
		delete licensePointsList;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : Destructor");
	#endif

	delete dbManager;	
}

/****************************************************************

   Class : LicenseManager

   Method : ReadLicenseInfo

   Return : TRUE - if success
	
   Description :  Get license information from database

*****************************************************************/
bool LicenseManager :: ReadLicenseInfo(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : ReadLicenseInfo. Start");
	#endif
		
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get license string from database
		char sql[SQL_SIZE];
		sprintf(sql, "SELECT License.LicenseString, DATALENGTH(License.LicenseString) FROM License WHERE (License.ID = 1)");
		
		// Execute SQl query
		ResultSet * licResult = dbManager -> ExecuteSelectQuery(sql);

		// license string buffer
		unsigned char encLicStr[ENCRYPTED_DATA_SIZE];
		int encLicStrLen = 0;

		// Bind data
		licResult -> Bind(1, encLicStr, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		licResult -> Bind(2, &encLicStrLen, sizeof(encLicStrLen), SQL_C_LONG);

		if (licResult -> MoveFirst())
		{
			// Decrypt value
			Encryptor * encryptor = new Encryptor(zLicenseManDllDefinition.dllID);

			unsigned char decLicStr[ENCRYPTED_DATA_SIZE];
			int decLicStrLen;

			if (encryptor -> UnPackAndDecryptSecurityData(encLicStr, encLicStrLen, decLicStr, ENCRYPTED_DATA_SIZE, &decLicStrLen))
			{
				delete encryptor;
				delete licResult;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
					WriteToLog("LicenseManager : ReadLicenseInfo. Can't decrypt license info!");
					WriteToLog("LicenseManager : ReadLicenseInfo. Done");
				#endif

				return false;
			}
			
			delete encryptor;
			delete licResult;

			char licInfoStr[ENCRYPTED_DATA_SIZE];
			memcpy(licInfoStr, decLicStr, decLicStrLen);
			licInfoStr[decLicStrLen] = 0;

			// Check license info list
			if (licensePointsList == NULL)
				licensePointsList = new LicensePointsList(dllUserID, licInfoStr, logWriter);			
			else
				licensePointsList -> ParseLicenseString(licInfoStr);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
				WriteToLog("LicenseManager : ReadLicenseInfo. License info loaded!");
				WriteToLog("LicenseManager : ReadLicenseInfo. Done");
			#endif

			return true;
		}
		else
		{
			delete licResult;
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
				WriteToLog("LicenseManager : ReadLicenseInfo. License info not found!");
				WriteToLog("LicenseManager : ReadLicenseInfo. Done");
			#endif

			return false;
		}
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

   Class : LicenseManager

   Method : WriteLicenseInfo

   Return : TRUE - if success
	
   Description :  Save license information to database

*****************************************************************/
bool LicenseManager :: WriteLicenseInfo(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : WriteLicenseInfo. Start");
	#endif

	// Check license info
	if (licensePointsList == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
			WriteToLog("LicenseManager : WriteLicenseInfo. Empty license points list!");
			WriteToLog("LicenseManager : WriteLicenseInfo. Done");
		#endif

		return false;
	}

	try
	{
		// Create license string
		char licStr[ENCRYPTED_DATA_SIZE];
		licensePointsList -> MakeLicenseString(licStr);

		// Encrypt string
		int licStrLen = strlen(licStr);
		unsigned char packedData[MAX_DATA_BUFFER_LEN];
		int packedDataLen;

		Encryptor * encryptor = new Encryptor(zLicenseManDllDefinition.dllID);

		if (encryptor -> EncryptAndPackSecurityData((unsigned char *)licStr, licStrLen, packedData, MAX_DATA_BUFFER_LEN, &packedDataLen))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
				WriteToLog("LicenseManager : WriteLicenseInfo. Can't encrypt license string!");
				WriteToLog("LicenseManager : WriteLicenseInfo. Done");
			#endif

			return false;
		}

		char hexStr[MAX_DATA_BUFFER_LEN];
		encryptor -> BinToHexStr(packedData, packedDataLen, hexStr, MAX_DATA_BUFFER_LEN);

		delete encryptor;

		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get license string from database
		char sql[SQL_SIZE];
		sprintf(sql, "UPDATE License SET License.LicenseString = %s WHERE (License.ID = 1)", hexStr);
		
		// Execute SQl query
		dbManager ->  Execute(sql);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
			WriteToLog("LicenseManager : WriteLicenseInfo. License info saved!");
			WriteToLog("LicenseManager : WriteLicenseInfo. Done");
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
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : WriteLicenseInfo. Done");
	#endif

	return true;
}

/****************************************************************

   Class : LicensePointsList

   Method : AddLicensePoint

   Parameters :
			Input : 
				licensePoint - pointer to license point instance

   Returns : TRUE - if success

   Description :  Add license point to list

*****************************************************************/
bool LicenseManager :: AddLicensePoint(LicensePoint * licensePoint)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : AddLicensePoint. Start");
	#endif

	// Check license info list
	if (licensePointsList == NULL)
		licensePointsList = new LicensePointsList(dllUserID, logWriter);

	// Add license point to list
	bool result = (licensePointsList -> Add(licensePoint) != NULL);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : AddLicensePoint. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePointsList

   Method : AddLicensePoint

   Parameters :
			Input : 
				id - license point ID
				name - license point name
				description - license point description
				type - license point type
				valuesCount - license point values count
				... - license point values list (list of PLICENSE_POINT_VALUE)

   Returns : TRUE - if success

   Description :  Add license point to list

*****************************************************************/
bool LicenseManager :: AddLicensePoint(char * id, char * name, char * description, int type, int valuesCount, ...)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : AddLicensePoint. Start");
	#endif

	// Check license info list
	if (licensePointsList == NULL)
		licensePointsList = new LicensePointsList(dllUserID, logWriter);

	int * pInt = &valuesCount;
	pInt++;

	// Add license point to list
	bool result = (licensePointsList -> Add(id, name, description, type, valuesCount, (PLICENSE_POINT_VALUE)(pInt)) != NULL);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : AddLicensePoint. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePointsList

   Method : DelLicensePoint

   Parameters :
			Input : 
				index - index of license point

   Returns : TRUE - if success

   Description : Del license point by index

*****************************************************************/
bool LicenseManager :: DelLicensePoint(int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : DelLicensePoint. Start");
	#endif

	bool result = false;

	// Check license info list
	if (licensePointsList)
	{
		// Deelete license point from list
		result = licensePointsList -> Del(index);
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : DelLicensePoint. No list!");

		WriteToLog("LicenseManager : DelLicensePoint. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePointsList

   Method : DelLicensePoint

   Parameters :
			Input : 
				id - license point ID

   Returns : TRUE - if success

   Description : Del license point by index

*****************************************************************/
bool LicenseManager :: DelLicensePoint(char * id)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : DelLicensePoint. Start");
	#endif

	bool result = false;

	// Check license info list
	if (licensePointsList)
	{
		// Find license point by ID
		int index = licensePointsList -> Find(id);

		// Deelete license point from list
		result = licensePointsList -> Del(index);
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : DelLicensePoint. No list!");

		WriteToLog("LicenseManager : DelLicensePoint. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePoint

   Method : CheckLicensePointValue

   Parameters :
			Input : 
				id - license point ID
				strValue - value
				index - index of value
				relType - type of relation

	Return : TRUE - if this value is accessible

	Description : Check licene point value

*****************************************************************/
bool LicenseManager :: CheckLicensePointValue(char * id, char * strValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : CheckLicensePointValue. Start");
	#endif

	bool result = false;

	// Check license info list
	if (licensePointsList)
	{
		// Find license point by ID
		int ind = licensePointsList -> Find(id);

		// Check value
		if (ind != -1)
			result = (*licensePointsList)[ind] -> CheckValue(strValue, index, relType);

	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : CheckLicensePointValue. No list!");

		WriteToLog("LicenseManager : CheckLicensePointValue. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePoint

   Method : CheckLicensePointValue

   Parameters :
			Input : 
				id - license point ID
				intValue - value
				index - index of value
				relType - type of relation

	Return : TRUE - if this value is accessible

	Description : Check licene point value

*****************************************************************/
bool LicenseManager :: CheckLicensePointValue(char * id, int intValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : CheckLicensePointValue. Start");
	#endif

	bool result = false;

	// Check license info list
	if (licensePointsList)
	{
		// Find license point by ID
		int ind = licensePointsList -> Find(id);

		// Check value
		if (ind != -1)
			result = (*licensePointsList)[ind] -> CheckValue(intValue, index, relType);

	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : CheckLicensePointValue. No list!");

		WriteToLog("LicenseManager : CheckLicensePointValue. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePoint

   Method : CheckLicensePointValue

   Parameters :
			Input : 
				id - license point ID
				tmValue - value
				index - index of value
				relType - type of relation

	Return : TRUE - if this value is accessible

	Description : Check licene point value

*****************************************************************/
bool LicenseManager :: CheckLicensePointValue(char * id, tm * tmValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : CheckLicensePointValue. Start");
	#endif

	bool result = false;

	// Check license info list
	if (licensePointsList)
	{
		// Find license point by ID
		int ind = licensePointsList -> Find(id);

		// Check value
		if (ind != -1)
			result = (*licensePointsList)[ind] -> CheckValue(tmValue, index, relType);

	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : CheckLicensePointValue. No list!");

		WriteToLog("LicenseManager : CheckLicensePointValue. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePoint

   Method : GetLicensePointValue

   Parameters :
			Output:
				outValue - string value

			Input : 
				id - license point ID
				index - index of value 

	Return : string value

	Description : Get license point value

*****************************************************************/
char * LicenseManager :: GetLicensePointValue(char * id, char * outValue, int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : GetLicensePointValue. Start");
	#endif

	// Check license info list
	if (licensePointsList)
	{
		// Find license point by ID
		int ind = licensePointsList -> Find(id);

		// Check value
		if (ind != -1)
			(*licensePointsList)[ind] -> GetValue(outValue, index);

	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : GetLicensePointValue. No list!");

		WriteToLog("LicenseManager : GetLicensePointValue. Done");
	#endif

	return outValue;
}

/****************************************************************

   Class : LicensePoint

   Method : GetLicensePointValue

   Parameters :
			Input : 
				id - license point ID
				index - index of value 

	Return : integer value

	Description : Get license point value

*****************************************************************/
int LicenseManager :: GetLicensePointValue(char * id, int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : GetLicensePointValue. Start");
	#endif

	int intValue = 0;

	// Check license info list
	if (licensePointsList)
	{
		// Find license point by ID
		int ind = licensePointsList -> Find(id);

		// Check value
		if (ind != -1)
			intValue = (*licensePointsList)[ind] -> ConvertValueToInt(index);
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : GetLicensePointValue. No list!");

		WriteToLog("LicenseManager : GetLicensePointValue. Done");
	#endif

	return intValue;
}

/****************************************************************

   Class : LicensePoint

   Method : GetLicensePointValue

   Parameters :
			Output:
				outValue - datetime value

			Input : 
				id - license point ID
				index - index of value 

	Return : datetime value

	Description : Get license point value

*****************************************************************/
tm * LicenseManager :: GetLicensePointValue(char * id, tm * outValue, int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : GetLicensePointValue. Start");
	#endif

	// Check license info list
	if (licensePointsList)
	{
		// Find license point by ID
		int ind = licensePointsList -> Find(id);

		// Check value
		if (ind != -1)
			(*licensePointsList)[ind] -> ConvertValueToDateTime(outValue, index);

	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : GetLicensePointValue. No list!");

		WriteToLog("LicenseManager : GetLicensePointValue. Done");
	#endif

	return outValue;
}

/****************************************************************

   Class : LicenseManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  LicenseManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

