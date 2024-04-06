/****************************************************************

   Solution : NovaTend

   Project : z-validateresponse-01.dll

   Module : ResponseValidator.cpp

   Description :  this module implements methods of class
				  ResponseValidator

*****************************************************************/

#include "stdafx.h"

#include "ResponseValidator.h"
#include <ODBCDatabaseManager.h>
#include <SettingsManager.h>
#include <Scheduler.h>

#include "PasswordConstructor.h"

#include <stdio.h>
#include <stdlib.h>

// z-validateresponse-01.dll definition structure
extern DLL_COMMON_DEFINITION zValidateResponseDllDefinition;

#pragma region Constructor

/****************************************************************

   Class : ResponseValidator

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
ResponseValidator :: ResponseValidator(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zValidateResponseDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : constructor");
	#endif

	dbManager = new ODBCDatabaseManager(zValidateResponseDllDefinition.dllID, logWriter);
	encryptor = new Encryptor(zValidateResponseDllDefinition.dllID);

	DatabaseConnect();
}

/****************************************************************

   Class : ResponseValidator

   Method : Destructor

*****************************************************************/
ResponseValidator :: ~ResponseValidator(void)
{
	DatabaseDisconnect();

	delete dbManager;
	delete encryptor;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : destructor");
	#endif
}

#pragma endregion

#pragma region Database

/****************************************************************

   Class : ResponseValidator

   Method : DatabaseConnect

   Return : Connection state

   Description :  Connect to database

*****************************************************************/
bool ResponseValidator :: DatabaseConnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : DatabaseConnect. Start");
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

			SettingsManager * settingsManager = new SettingsManager(zValidateResponseDllDefinition.dllID);

			if (settingsManager -> GetDatabaseSourceName(dsn) != ERROR_SUCCESS)
				WriteToLog("Response validator : Connect to DB --> Can't get DSN ");

			if (settingsManager -> GetDatabaseUserName(dbUser) != ERROR_SUCCESS)
				WriteToLog("Response validator :  Connect to DB --> Can't get db user name ");

			if (settingsManager -> GetDatabasePassword(dbPassword) != ERROR_SUCCESS)
				WriteToLog("Response validator :  Connect to DB --> Can't get db password ");

			delete settingsManager;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : DatabaseConnect. Connecting...");
			#endif

			// Connect
			dbManager -> Connect(dsn, dbUser, dbPassword);
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			else
				WriteToLog("ResponseValidator : DatabaseConnect. Already connected!");

			WriteToLog("ResponseValidator : DatabaseConnect. Done");
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

   Class : ResponseValidator

   Method : DatabaseDisconnect

   Return : Connection state

   Description :  Disconnect from database

*****************************************************************/
bool ResponseValidator :: DatabaseDisconnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : DatabaseDisconnect. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Check connection
		if (dbManager -> Opened())
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : DatabaseDisconnect. Disconnecting...");
			#endif

			// Disconnect
			dbManager -> Disconnect();
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			else
				WriteToLog("ResponseValidator : DatabaseDisconnect. Already disconnected!");

			WriteToLog("ResponseValidator : DatabaseDisconnect. Done");
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

#pragma region Validate params

/****************************************************************

   Class : ResponseValidator

   Method : DecryptAuthElement
   
   Parameters :
			Input : 
				pAuthElem - authenticate element
			Output:
				objectName - object name
				objectValue - object value
	
	Return: error code

	Description :  Decrypt authenticate element

*****************************************************************/
bool ResponseValidator :: DecryptAuthElement(PAUTH_ELEMENT pAuthElem, char * objectName, char * objectValue)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : DecryptAuthElement. Start");
	#endif

	unsigned char decryptedObjectName[STR_VALUE_LEN];
	int decryptedObjectNameLen;

	unsigned char decryptedObjectValue[STR_VALUE_LEN];
	int decryptedObjectValueLen;

	if (encryptor -> UnPackAndDecryptSecurityData(pAuthElem -> objectName, pAuthElem -> objectNameLen, decryptedObjectName, STR_VALUE_LEN, &decryptedObjectNameLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : DecryptAuthElement. Can't decrypt object name");
			WriteToLog("ResponseValidator : DecryptAuthElement. Done");
		#endif

		return false;
	}
	else
	{
		memcpy(objectName, decryptedObjectName, decryptedObjectNameLen);
		objectName[decryptedObjectNameLen] = 0;
	}

	if (encryptor -> UnPackAndDecryptSecurityData(pAuthElem -> objectValue, pAuthElem -> objectValueLen, decryptedObjectValue, STR_VALUE_LEN, &decryptedObjectValueLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : DecryptAuthElement. Can't decrypt object value");
			WriteToLog("ResponseValidator : DecryptAuthElement. Done");
		#endif

		return false;
	}
	else
	{
		memcpy(objectValue, decryptedObjectValue, decryptedObjectValueLen);
		objectValue[decryptedObjectValueLen] = 0;
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : DecryptAuthElement. All decrypted!");
		WriteToLog("ResponseValidator : DecryptAuthElement. Done");
	#endif

	return true;
}

/****************************************************************

   Class : ResponseValidator

   Method : ValidateParams
    
	Parameters :
			Input : 
				userID - user unique number
				compName - computer name
				pAuthContainer - pointr to authecticate container

	Return: error code

	Description :  Database credential records validation

*****************************************************************/
int ResponseValidator :: ValidateParams(int userID, char * compName, PAUTH_CONTAINER pAuthContainer)
{
	try
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateParams. Start");
		#endif
					
		// Create scheduler instance
		Scheduler * scheduler = new Scheduler(zValidateResponseDllDefinition.dllID, logWriter, dbManager);
		int actionCode = scheduler -> VerifyScheduleRecords(userID, compName, LOG_IN_FUNCTION);
		delete scheduler;

		// Verify schedule records
		if ((actionCode & DENY_ACTION) == DENY_ACTION)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateParams. LOG IN banned in schedule!");
				WriteToLog("ResponseValidator : ValidateParams. Done");
			#endif

			return RESPONSE_BAD;
		}

		// Verify schedule records
		if ((actionCode & IGNORE_ACTION) == IGNORE_ACTION)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateParams. LOG IN ignored in schedule!");
				WriteToLog("ResponseValidator : ValidateParams. Done");
			#endif

			return RESPONSE_OK;
		}

		// Check auth container
		if (!pAuthContainer)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateParams. Empty athenticate container!");
				WriteToLog("ResponseValidator : ValidateParams. Done");
			#endif

			return RESPONSE_BAD;
		}

		for(int i = 0; i < pAuthContainer -> authElementCount; i++)
		{
			
			// Validate all params except user name, 
			// domain name and password
			if ((i != GetLoginParamID(pAuthContainer)) &&
				(i != GetPasswordParamID(pAuthContainer)) &&
				(i != GetDomainParamID(pAuthContainer)))
			{
				char objName[NAME_LEN];
				char objValue[STR_VALUE_LEN];

				if (!DecryptAuthElement(pAuthContainer -> authElements[i], objName, objValue))
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
						WriteToLog("ResponseValidator : ValidateParams. Can't decrypt auth element!");
						WriteToLog("ResponseValidator : ValidateParams. Done");
					#endif
											
					return RESPONSE_BAD;
				}
				
				// Prepare SQL query
				char sql[SQL_SIZE];
				sprintf(sql, "SELECT UserCheckValues.Value, DATALENGTH(UserCheckValues.Value)\
						      FROM UserCheckValues\
						       WHERE ((UserCheckValues.ScreenObjectID = %d) and \
		   							  (UserCheckValues.UserID = %d))", pAuthContainer -> authElements[i] -> objectID, userID);
				
				// Execute SQL query
				ResultSet * validateResult = dbManager -> ExecuteSelectQuery(sql);

				unsigned char valueBuf[MAX_DATA_BUFFER_LEN];
				int valueBufLen;

				// Bind data
				validateResult -> Bind(1, valueBuf, MAX_DATA_BUFFER_LEN, SQL_C_BINARY);
				validateResult -> Bind(2, &valueBufLen, sizeof(valueBufLen), SQL_C_LONG);
		        
				bool found = false;
				
				// Retrive data from database
				while((validateResult -> MoveNext()) && (!found))
				{
					unsigned char decryptedValue[STR_VALUE_LEN];
					int decryptedValueLen;
					char resultValue[STR_VALUE_LEN];

					if (!encryptor -> UnPackAndDecryptSecurityData(valueBuf, valueBufLen, decryptedValue, STR_VALUE_LEN, &decryptedValueLen))
					{
						memcpy(resultValue, decryptedValue, decryptedValueLen);
						resultValue[decryptedValueLen] = 0;

						if (strcmp(resultValue, objValue))
							found = true;
					}
				}

				delete validateResult;

				if (!found)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
						WriteToLog("ResponseValidator : ValidateParams. Parameter validation failed!");
					#endif

					return RESPONSE_BAD;
				}
			}
		}
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateParams. Done");
		#endif

		return RESPONSE_OK;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return RESPONSE_BAD;
	}
}

/****************************************************************

   Class : ResponseValidator

   Method :  GetLoginParamID
    
	Return:  user name index

	Description :  Get user name index

*****************************************************************/
int ResponseValidator :: GetLoginParamID(PAUTH_CONTAINER pAuthContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : GetLoginParamID");
	#endif

	if (!pAuthContainer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : GetLoginParamID. Empty athenticate container!");
		#endif

		return -1;
	}

	for(int i = 0; i < pAuthContainer -> authElementCount; i++)
		if (pAuthContainer -> authElements[i] -> objectTypeID == SOT_USER_NAME_BOX)
			return i;

    return -1;	
}

/****************************************************************

   Class : ResponseValidator

   Method :  GetPasswordParamID
    
	Return:  password index

	Description :  Get password index

*****************************************************************/
int ResponseValidator :: GetPasswordParamID(PAUTH_CONTAINER pAuthContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : GetPasswordParamID");
	#endif
	
	if (!pAuthContainer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : GetPasswordParamID. Empty athenticate container!");
		#endif

		return -1;
	}

	for(int i = 0; i < pAuthContainer -> authElementCount; i++)
		if (pAuthContainer -> authElements[i] -> objectTypeID == SOT_PASSWORD_BOX)
			return i;

    return -1;	
}

/****************************************************************

   Class : ResponseValidator

   Method :  GetDomainParamID
    
	Return:  domain name index

	Description :  Get domain name index

*****************************************************************/
int ResponseValidator :: GetDomainParamID(PAUTH_CONTAINER pAuthContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : GetDomainParamID");
	#endif

	if (!pAuthContainer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : GetDomainParamID. Empty athenticate container!");
		#endif

		return -1;
	}

	for(int i = 0; i < pAuthContainer -> authElementCount; i++)
		if (pAuthContainer -> authElements[i] -> objectTypeID == SOT_DOMAIN_NAME_BOX)
			return i;

    return -1;	
}

/****************************************************************

	Class : ResponseValidator

	Method :  ValidateDomain
    
	Parameters :
			Input : 
				pAnsCnt - pointer to answer container

	Return:  Error code

	Description :  Validate domain name

*****************************************************************/
int ResponseValidator :: ValidateDomain(PAUTH_CONTAINER pAuthContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : ValidateDomain. Start");
	#endif

	if (!pAuthContainer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateDomain. Empty athenticate container!");
			WriteToLog("ResponseValidator : ValidateDomain. Done");
		#endif

		return RESPONSE_BAD;
	}

	int domainID = GetDomainParamID(pAuthContainer);
	
	char objName[STR_VALUE_LEN] = "";
	char objValue[STR_VALUE_LEN] = "";

	if (domainID == -1)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateDomain. No domain check value!");
			WriteToLog("ResponseValidator : ValidateDomain. Done");
		#endif

		return RESPONSE_BAD;
	}
	else
		if (!DecryptAuthElement(pAuthContainer -> authElements[domainID], objName, objValue))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateDomain. Can't decrypt domain check value!");
				WriteToLog("ResponseValidator : ValidateDomain. Done");
			#endif

			return RESPONSE_BAD;
		}


	// Check licensed domain name
	LicenseManager * licenseManager = new LicenseManager(zValidateResponseDllDefinition.dllID, logWriter);
	bool found = licenseManager -> CheckLicensePointValue("DOMAIN", objValue);
	delete licenseManager;

	if (found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateDomain. Legal domain!");
			WriteToLog("ResponseValidator : ValidateDomain. Done");
		#endif

		return RESPONSE_OK;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateDomain. Non legal domain!");
			WriteToLog("ResponseValidator : ValidateDomain. Done");
		#endif

		return RESPONSE_BAD;
	}
}

#pragma endregion

#pragma region Validate answers

/****************************************************************

	Class : ResponseValidator

	Method :  ValidateAnswers
    
	Parameters :
			Input : 
				userID - user ID
				compName - computer name
				pAnsCnt - pointer to answer container

	Return:  Error code

	Description :  Validate user answers

*****************************************************************/
int ResponseValidator :: ValidateAnswers(int userID, char * compName, PANSWER_CONTAINER pAnsCnt)
{
	try
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateAnswers. Start");
		#endif
		
		// Create scheduler instance
		Scheduler * scheduler = new Scheduler(zValidateResponseDllDefinition.dllID, logWriter, dbManager);
		int actionCode = scheduler -> VerifyScheduleRecords(userID, compName, EDUCATION_FUNCTION);
		delete scheduler;

		// Verify schedule records
		if ((actionCode & DENY_ACTION) == DENY_ACTION)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateParams. LOG IN banned in schedule!");
				WriteToLog("ResponseValidator : ValidateParams. Done");
			#endif
						
			return RESPONSE_BAD;
		}

		// Verify schedule records
		if ((actionCode & IGNORE_ACTION) == IGNORE_ACTION)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateParams. LOG IN ignored in schedule!");
				WriteToLog("ResponseValidator : ValidateParams. Done");
			#endif

			return RESPONSE_OK;
		}
		
		// Check answer container
		if (!pAnsCnt)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateAnswers. Empty answer container!");
			#endif

			return RESPONSE_BAD;
		}
		
		// Check DLL legal user
		dbManager += dllUserCheckResult;

	   bool wrongAnswer = false;
	   	   
	   for(int i = 0; i < pAnsCnt -> answersCount; i++)
	   {
		   if (!pAnsCnt -> answers[i])
		   {
			   #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
	   				WriteToLog("ResponseValidator : ValidateAnswers. Bad answer pointer!");
			   #endif
							   
			   return RESPONSE_BAD;
		   }

		   #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				char message[STR_VALUE_LEN];
				sprintf(message, "ResponseValidator : ValidateAnswers. Answer: %s, Question: %d", pAnsCnt -> answers[i] -> answerValue, pAnsCnt -> answers[i] -> questionID);
	   			WriteToLog(message);
		   #endif

		    int answerIDBuf = 0;

			char sql[SQL_SIZE];
			sprintf(sql, "SELECT EducationAnswers.ID\
							FROM EducationAnswers, EducationQuestionAnswers\
							WHERE ((EducationAnswers.ID = EducationQuestionAnswers.AnswerID) and\
									(EducationAnswers.AnswerText = '%s') and\
									(EducationQuestionAnswers.QuestionID = %d))", pAnsCnt -> answers[i] -> answerValue, 
																				pAnsCnt -> answers[i] -> questionID);

			ResultSet * answerResult = dbManager -> ExecuteSelectQuery(sql);

			answerResult -> Bind(1, &answerIDBuf, sizeof(answerIDBuf), SQL_C_LONG);

			if (!answerResult -> MoveFirst())
			{
				delete answerResult;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
					WriteToLog("ResponseValidator : ValidateAnswers. No answer ID!");
				#endif	
				
				return RESPONSE_BAD;
			}
			
			delete answerResult;

			if (answerIDBuf != pAnsCnt -> answers[i] -> rightAnswerID)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
					WriteToLog("ResponseValidator : ValidateAnswers. Wrong answer!");
				#endif

				wrongAnswer = true;

				char sql[SQL_SIZE];
				sprintf(sql, "INSERT INTO UserEducationAnswers\
									(UserID\
									,QuestionID\
									,AnswerID\
									,CorrectAnswerSign)\
						VALUES (%d, %d, %d, 0)", userID, pAnsCnt -> answers[i] -> questionID, answerIDBuf);

				dbManager ->  Execute(sql);
			}
			else
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
					WriteToLog("ResponseValidator : ValidateAnswers. Right answer!");
				#endif

				char sql[SQL_SIZE];
				sprintf(sql, "INSERT INTO UserEducationAnswers\
									(UserID\
									,QuestionID\
									,AnswerID\
									,CorrectAnswerSign)\
						VALUES (%d, %d, %d, 1)", userID, pAnsCnt -> answers[i] -> questionID, answerIDBuf);

				dbManager ->  Execute(sql);
			}
	   }

	   #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateAnswers. Done");
	   #endif

	   if (wrongAnswer) 
		   return RESPONSE_BAD;
	   else
		   return RESPONSE_OK;

	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		
		return RESPONSE_BAD;
	}
}

#pragma endregion

#pragma region Validate password

/****************************************************************

	Class : ResponseValidator

	Method :  DecryptString
    
	Parameters :
			Input : 
				encStr - encrypted string
				encStrLen - encrypted string length
			Output:
				decStr - decrypted string

	Return:  Error code

	Description :  Decrypt string

*****************************************************************/
bool ResponseValidator :: DecryptString(unsigned char * encStr, int encStrLen, char * decStr)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : DecryptString. Start");
	#endif

	unsigned char decryptedString[STR_VALUE_LEN];
	int decryptedStringLen;

	if (encryptor -> UnPackAndDecryptSecurityData(encStr, encStrLen, decryptedString, STR_VALUE_LEN, &decryptedStringLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : DecryptString. Can't decrypt!");
			WriteToLog("ResponseValidator : DecryptString. Done");
		#endif

		return false;
	}
	else
	{
		memcpy(decStr, decryptedString, decryptedStringLen);
		decStr[decryptedStringLen] = 0;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : DecryptString. String decrypted!");
		WriteToLog("ResponseValidator : DecryptString. Done");
	#endif

	return true;
}

/****************************************************************

	Class : ResponseValidator

	Method :  CheckAllSystemPasswords
    
	Parameters :
			Input : 
				userID - user ID
				sysPwd - user entered system password

	Return:  Error code

	Description :  Check all system apsswords

*****************************************************************/
int ResponseValidator :: CheckAllSystemPasswords(int userID, char * sysPwd)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : CheckAllSystemPasswords. Start");
	#endif

	// Check input data
	if (!sysPwd)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : CheckAllSystemPasswords. Bad input system password!");
			WriteToLog("ResponseValidator : CheckAllSystemPasswords. Done");
		#endif

		return RESPONSE_BAD;
	}

	try
	{
		// Prepare SQL query
		char sql[SQL_SIZE];
		sprintf(sql, "SELECT UserAccounts.UserID,\
							 UserAccounts.AuthSystemID,\
							 UserAccounts.Password,\
							 DATALENGTH(UserAccounts.Password)\
						FROM UserAccounts\
						WHERE (UserAccounts.UserID = %d)", userID);

		// Execute SQL query
		ResultSet * validateResult = dbManager -> ExecuteSelectQuery(sql);

		int userIDBuf;
		int authSysIDBuf;
		unsigned char pwdBuf[MAX_DATA_BUFFER_LEN];
		int pwdBufLen;

		// Bind data
		validateResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);
		validateResult -> Bind(2, &authSysIDBuf, sizeof(authSysIDBuf), SQL_C_LONG);
		validateResult -> Bind(3, pwdBuf, MAX_DATA_BUFFER_LEN, SQL_C_BINARY);
		validateResult -> Bind(4, &pwdBufLen, sizeof(pwdBufLen), SQL_C_LONG);
		        
		bool found = false;
				
		// Retrive data from database
		while((validateResult -> MoveNext()) && (!found))
		{
			unsigned char decryptedValue[STR_VALUE_LEN];
			int decryptedValueLen;
			char resultValue[STR_VALUE_LEN];

			if (!encryptor -> UnPackAndDecryptSecurityData(pwdBuf, pwdBufLen, decryptedValue, STR_VALUE_LEN, &decryptedValueLen))
			{
				memcpy(resultValue, decryptedValue, decryptedValueLen);
				resultValue[decryptedValueLen] = 0;

				if (strcmp(resultValue, sysPwd) == 0)
				{
					found = true;
					break;
				}
			}
		}

		delete validateResult;

		if (!found)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : CheckAllSystemPasswords. Password not found!");
				WriteToLog("ResponseValidator : CheckAllSystemPasswords. Done");
			#endif

			return RESPONSE_BAD;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : CheckAllSystemPasswords. Done");
			#endif

			return authSysIDBuf;
		}
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		
		return RESPONSE_BAD;
	}
}

/****************************************************************

   Class : ResponseValidator

   Method : CheckTimePeriod

   Parameters :
			Input : 
				period - period code
				data - data string

   Returns : TRUE - if period expired

   Description : Check time period

*****************************************************************/
bool ResponseValidator :: CheckTimePeriod(int period, char * data)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : CheckTimePeriod. Start");
	#endif

	try
	{
		int day, mon, year, hour, min, sec;

		// Retrieve date values
		sscanf_s(data, "%d-%d-%d %d:%d:%d", &year, &mon, &day, &hour, &min, &sec);
	
		time_t nowSeconds;
		struct tm inpTime;

		// Get current time
		time (&nowSeconds);
		inpTime = * localtime(&nowSeconds);

		// Set new values
		inpTime.tm_year = year - 1900;
		inpTime.tm_mon = mon - 1;
		inpTime.tm_mday = day;
		inpTime.tm_hour = hour;
		inpTime.tm_min = min;
		inpTime.tm_sec = sec;
		inpTime.tm_isdst = -1;
	    
		// Subtract dates
		double resSeconds = difftime(nowSeconds, mktime(&inpTime));

		// Count period
		double hours = resSeconds / 3600;
		
		if(hours > period)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : CheckTimePeriod. Time period expired");
				WriteToLog("ResponseValidator : CheckTimePeriod. Done");
			#endif
	
			return true;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : CheckTimePeriod. Time period not expired");
				WriteToLog("ResponseValidator : CheckTimePeriod. Done");
			#endif
	
			return false;
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : CheckTimePeriod. Can't check period!");
			WriteToLog("ResponseValidator : CheckTimePeriod. Done");
		#endif

		return true;
	}
}

/****************************************************************

	Class : ResponseValidator

	Method :  ValidateMainPassword
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor
				pSecurityData - pointer to security data structure
				userPassword - user custom password
				timeinfo - time info structure
				symbolBoxesList - symbol matrixes list

	Return:  Error code

	Description :  Validate user custom password

*****************************************************************/
int ResponseValidator :: ValidateMainPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, char * userPassword, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : ValidateMainPassword. Start");
	#endif

	// Check user instance
	if ((!pUser) || (!pSecurityData) || (pUser -> userID != pSecurityData -> userID))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateMainPassword. Wrong input data!");
			WriteToLog("ResponseValidator : ValidateMainPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	// Check rules
	char genPassword[STR_VALUE_LEN] = "";
	if ((pSecurityData -> pwdConstRulesCount > 0) && (pSecurityData -> passThru == false))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateMainPassword. Password generates by rules!");
		#endif

		// Construct password
		PasswordConstructor * passwordConstructor = new PasswordConstructor(pUser, pSecurityData, timeinfo, symbolBoxesList, encryptor);
		passwordConstructor -> CreateMainPassword();
		passwordConstructor -> GetPassword(genPassword);
		delete passwordConstructor;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateMainPassword. Uses system password!");
		#endif

		if (CheckAllSystemPasswords(pUser -> userID, userPassword) != RESPONSE_BAD)
			strcpy(genPassword, userPassword);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		char msg[STR_VALUE_LEN];
		sprintf(msg, "ResponseValidator : ValidateMainPassword. User constructed password: '%s'. System constructed password: '%s'", userPassword, genPassword);
		WriteToLog(msg);
	#endif

	if (strcmp(genPassword, userPassword) == 0) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateMainPassword. Main password succeeded!");
			WriteToLog("ResponseValidator : ValidateMainPassword. Done");
		#endif

		return RESPONSE_OK;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateMainPassword. Main password failed!");
			WriteToLog("ResponseValidator : ValidateMainPassword. Done");
		#endif

		return RESPONSE_BAD;
	}
}

/****************************************************************

	Class : ResponseValidator

	Method :  ValidateTempPassword
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor
				pSecurityData - pointer to security data structure
				userPassword - user custom password
				timeinfo - time info structure
				symbolBoxesList - symbol matrixes list

	Return:  Error code

	Description :  Validate user custom password

*****************************************************************/
int ResponseValidator :: ValidateTempPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, char * userPassword, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : ValidateTempPassword. Start");
	#endif

	// Check user instance
	if ((!pUser) || (!pSecurityData) || (pUser -> userID != pSecurityData -> userID))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateTempPassword. Wrong input data!");
			WriteToLog("ResponseValidator : ValidateTempPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	// Check temp password
	if ((pUser -> pwdReseted) && (pSecurityData -> tmpPwdConstRulesCount > 0))
	{
		// Check password period
		if (CheckTimePeriod(pUser -> pwdResetPeriod, pUser -> pwdResetDate))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateTempPassword. Temporary password expired!");
				WriteToLog("ResponseValidator : ValidateTempPassword. Done");
			#endif

			return RESPONSE_PWD_EXPIRED;
		}

		char genPassword[STR_VALUE_LEN] = "";
		
		// Construct password
		PasswordConstructor * passwordConstructor = new PasswordConstructor(pUser, pSecurityData, timeinfo, symbolBoxesList, encryptor);
		passwordConstructor -> CreateTempPassword();
		passwordConstructor -> GetPassword(genPassword);
		delete passwordConstructor;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			char msg[STR_VALUE_LEN];
			sprintf(msg, "ResponseValidator : ValidateTempPassword. User constructed password: '%s'. System constructed password: '%s'", userPassword, genPassword);
			WriteToLog(msg);
		#endif

		if (strcmp(genPassword, userPassword) == 0) 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateTempPassword. Temp password succeeded!");
				WriteToLog("ResponseValidator : ValidateTempPassword. Done");
			#endif

			return RESPONSE_OK;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateTempPassword. Temp password failed!");
				WriteToLog("ResponseValidator : ValidateTempPassword. Done");
			#endif

			return RESPONSE_BAD;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateTempPassword. No temporary password!");
			WriteToLog("ResponseValidator : ValidateTempPassword. Done");
		#endif

		return RESPONSE_BAD;
	}
}

/****************************************************************

	Class : ResponseValidator

	Method :  SavePasswordAttemptInformation
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor
				validationResult - password validation result

	Description :  Save password attempt information

*****************************************************************/
void ResponseValidator :: SavePasswordAttemptInformation(PUSER_DESCRIPTOR pUser, int validationResult)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : SavePasswordAttemptInformation. Start");
	#endif

	try
	{
		// Save attempts
		if (validationResult == RESPONSE_OK)
		{
			char sql[SQL_SIZE];
			sprintf(sql, "UPDATE Users\
						  SET Users.PwdAttemptsCount = 0\
						  WHERE Users.ID = %d", pUser -> userID);

			dbManager -> Execute(sql);
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : SavePasswordAttemptInformation. Correct password!");
				WriteToLog("ResponseValidator : SavePasswordAttemptInformation. Done");
			#endif
		}
		else
		{
			char sql[SQL_SIZE];
			sprintf(sql, "UPDATE Users\
						  SET Users.PwdAttemptsCount = Users.PwdAttemptsCount + 1\
						  WHERE Users.ID = %d", pUser -> userID);

			dbManager -> Execute(sql);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : SavePasswordAttemptInformation. Wrong password!");
				WriteToLog("ResponseValidator : SavePasswordAttemptInformation. Done");
			#endif
		}
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

	Class : ResponseValidator

	Method :  ValidateCustomPassword
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor
				pSecurityData - pointer to security data structure
				userPassword - encrypted user custom password
				userPasswordLen - encrypted user custom password size
				timeinfo - time info structure
				symbolBoxesList - symbol matrixes list

	Return:  Error code

	Description :  Validate user custom password

*****************************************************************/
int ResponseValidator :: ValidateCustomPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : ValidateCustomPassword. Start");
	#endif

	// Check user instance
	if ((!pUser) || (!pSecurityData) || (pUser -> userID != pSecurityData -> userID))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateCustomPassword. Wrong input data!");
			WriteToLog("ResponseValidator : ValidateCustomPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	// Check locked flag
	if (pUser -> locked)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateCustomPassword. User account locked!");
			WriteToLog("ResponseValidator : ValidateCustomPassword. Done");
		#endif

		return RESPONSE_ACCOUNT_LOCKED;
	}

	// Decrypt user password
	char decPWD[STR_VALUE_LEN];
	if (!DecryptString(userPassword, userPasswordLen, decPWD))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ValidateCustomPassword. Password decryption failed!");
			WriteToLog("ResponseValidator : ValidateCustomPassword. Done");
		#endif

		return RESPONSE_BAD;
	}
		
	// Validate main password
	int validationResult = ValidateMainPassword(pUser, pSecurityData, decPWD, timeinfo, symbolBoxesList);

	if (validationResult == RESPONSE_OK)
	{
		DeleteTempPassword(pUser -> userID);
		pUser -> pwdReseted = false;
	}
	else
	{
		// Validate temp password
		validationResult = ValidateTempPassword(pUser, pSecurityData, decPWD, timeinfo, symbolBoxesList);

		if (validationResult == RESPONSE_PWD_EXPIRED)
		{
			DeleteTempPassword(pUser -> userID);
			pUser -> pwdReseted = false;
		}
	}
	
	// Save password attemtps count infomation
	SavePasswordAttemptInformation(pUser, validationResult);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : ValidateCustomPassword. Done");
	#endif

	return validationResult;
}

/****************************************************************

	Class : ResponseValidator

	Method :  ValidateCredentials
    
	Parameters :
			Input : 
				encUserName - encrypted user name
				encUserNameLen - length of encrypted user name
				encUserPassword - encrypted user password
				encUserPasswordLen - length of encrypted user password
				authSystemID - authentication system ID

	Return:  Error code

	Description :  Validate user credentials

*****************************************************************/
int ResponseValidator :: ValidateCredentials(unsigned char * encUserName, int encUserNameLen, unsigned char * encUserPassword, int encUserPasswordLen, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : ValidateCredentials. Start");
	#endif

	try
	{
		char userName[NAME_LEN];
		char userPassword[STR_VALUE_LEN];

		// Decrypt user name and password
		if (!(DecryptString(encUserName, encUserNameLen, userName) && DecryptString(encUserPassword, encUserPasswordLen, userPassword)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateCredentials. Can't decrypt input data!");
				WriteToLog("ResponseValidator : ValidateCredentials. Done");
			#endif

			return RESPONSE_BAD;
		}

		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT UserAccounts.UserName, DATALENGTH(UserAccounts.UserName), \
								UserAccounts.Password, DATALENGTH(UserAccounts.Password)\
						FROM UserAccounts\
						WHERE (UserAccounts.AuthSystemID = %d)", authSystemID);

		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;
		unsigned char userPwdBuf[ENCRYPTED_DATA_SIZE];
		int userPwdLenBuf = 0;

		// Bind data
		usersResult -> Bind(1, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(2, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);
		usersResult -> Bind(3, userPwdBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(4, &userPwdLenBuf, sizeof(userPwdLenBuf), SQL_C_LONG);
		
		bool found = false;

		while(usersResult -> MoveNext())
		{
			char dbUserName[NAME_LEN];
			char dbUserPassword[STR_VALUE_LEN];

			// Decrypt user name and password
			if (DecryptString(userNameBuf, userNameLenBuf, dbUserName) && DecryptString(userPwdBuf, userPwdLenBuf, dbUserPassword))
			{
				if ((strcmp(userName, dbUserName) == 0)	&& (strcmp(userPassword, dbUserPassword) == 0))
				{
					found = true;
					break;
				}
			}
		}

		delete usersResult;

		if (!found)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateCredentials. Validation failed!");
				WriteToLog("ResponseValidator : ValidateCredentials. Done");
			#endif

			return RESPONSE_BAD;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : ValidateCredentials. Validation succeded!");
				WriteToLog("ResponseValidator : ValidateCredentials. Done");
			#endif

			return RESPONSE_OK;
		}
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return RESPONSE_BAD;
	}
}

#pragma endregion

#pragma region Reset user password

/****************************************************************

	Class : ResponseValidator

	Method :  DeleteTempPassword
    
	Parameters :
			Input : 
				userID - user ID

	Description :  Delete temp password

*****************************************************************/
void ResponseValidator :: DeleteTempPassword(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : DeleteTempPassword. Start");
	#endif

	try
	{
		char sql[SQL_SIZE];

		// Set reset flag
		sprintf(sql, "UPDATE Users\
						SET Users.PwdResetted = 0\
					WHERE (Users.ID = %d)", userID);

		dbManager -> Execute(sql);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : DeleteTempPassword. Done");
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

/****************************************************************

	Class : ResponseValidator

	Method :  DeleteTempPasswordRules
    
	Parameters :
			Input : 
				userID - user ID

	Description :  Delete temp password rules

*****************************************************************/
void ResponseValidator :: DeleteTempPasswordRules(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : DeleteTempPasswordRules. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Delete previous temporary rules
		sprintf(sql, "DELETE FROM UserPasswordConstructionRules \
					  WHERE ((UserPasswordConstructionRules.UserID = %d) and \
					  (UserPasswordConstructionRules.TmpRule = 1))", userID);

		dbManager -> Execute(sql);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : DeleteTempPasswordRules. Done");
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

/****************************************************************

	Class : ResponseValidator

	Method :  SetTempPasswordRules
    
	Parameters :
			Input : 
				userID - user ID
				userTmpPwdConstRules - user temp password construction rules list
				userTmpPwdConstRulesCount - user temp password construction rules list size

	Returns : TRUE - if success
				
	Description :  Set temporary password rules
	
*****************************************************************/
bool ResponseValidator :: SetTempPasswordRules(int userID, int * userTmpPwdConstRules, int userTmpPwdConstRulesCount)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : SetTempPasswordRules. Start");
	#endif

	if (userTmpPwdConstRules == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SetTempPasswordRules. Wrong input data!");
			WriteToLog("ResponseValidator : SetTempPasswordRules. Done");
		#endif

		return false;
	}

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		for(int i = 0; i < userTmpPwdConstRulesCount; i++)
		{
			// Insert temporary rules to DB
			sprintf(sql, "INSERT INTO UserPasswordConstructionRules (UserID, RuleID, RulesOrder, TmpRule)\
							VALUES (%d, %d, %d, 1)", userID, userTmpPwdConstRules[i], i + 1);

			dbManager -> Execute(sql);
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SetTempPasswordRules. Done");
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

	Class : ResponseValidator

	Method :  SetTempCascadeStringPassword
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor

			Output:
				messageBuffer - result message

	Return:  Error code

	Description :  Set temporary cascade string password

*****************************************************************/
int ResponseValidator :: SetTempCascadeStringPassword(PUSER_DESCRIPTOR pUser, char * messageBuffer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : SetTempCascadeStringPassword. Start");
	#endif

	if ((pUser == NULL) || 
		(messageBuffer == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SetTempCascadeStringPassword. Wrong input data!");
			WriteToLog("ResponseValidator : SetTempCascadeStringPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	DeleteTempPasswordRules(pUser -> userID);
		
	// Generate temporary rules
	int userTmpPwdConstRulesCount = encryptor -> RangedRand(1, 5);
	int userTmpPwdConstRules[MAX_PWD_CONSTR_RULES_COUNT];

	for(int i = 0; i < userTmpPwdConstRulesCount; i++)
		userTmpPwdConstRules[i] = encryptor -> RangedRand(CASCADE_STRING_PWD_MIN, CASCADE_STRING_PWD_MAX - 1);
		
	if(!SetTempPasswordRules(pUser -> userID, userTmpPwdConstRules, userTmpPwdConstRulesCount))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SetTempCascadeStringPassword. Can't save password construction rules!");
			WriteToLog("ResponseValidator : SetTempCascadeStringPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	int tmpUserToken = encryptor -> RangedRand(1000, 9999);
		
	PreparePasswordResetMessage(pUser, tmpUserToken, userTmpPwdConstRules, userTmpPwdConstRulesCount, messageBuffer);
				
	SaveUserResetFlag(pUser, tmpUserToken);
			
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : SetTempCascadeStringPassword. Password successfully resseted!");
		WriteToLog("ResponseValidator : SetTempCascadeStringPassword. Done");
	#endif

	return RESPONSE_OK;
}

/****************************************************************

	Class : ResponseValidator

	Method :  SetTempOneSymbolBoxesPassword
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor

			Output:
				messageBuffer - result message

	Return:  Error code

	Description :  Set temporary symbol boxes password

*****************************************************************/
int ResponseValidator :: SetTempOneSymbolBoxesPassword(PUSER_DESCRIPTOR pUser, char * messageBuffer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : SetTempOneSymbolBoxesPassword. Start");
	#endif

	if ((pUser == NULL) || (messageBuffer == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SetTempOneSymbolBoxesPassword. Wrong input data!");
			WriteToLog("ResponseValidator : SetTempOneSymbolBoxesPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	DeleteTempPasswordRules(pUser -> userID);
				
	// Generate temporary rules
	int userTmpPwdConstRulesCount = 4;
	int userTmpPwdConstRules[MAX_PWD_CONSTR_RULES_COUNT];

	userTmpPwdConstRules[0] = encryptor -> RangedRand(ONE_SYM_PWD_JOKER_1_MIN, ONE_SYM_PWD_JOKER_1_MAX);
	userTmpPwdConstRules[1] = encryptor -> RangedRand(ONE_SYM_PWD_JOKER_2_MIN, ONE_SYM_PWD_JOKER_2_MAX);
	userTmpPwdConstRules[2] = encryptor -> RangedRand(ONE_SYM_PWD_FORMULA_MIN, ONE_SYM_PWD_FORMULA_MAX);
	userTmpPwdConstRules[3] = encryptor -> RangedRand(ONE_SYM_PWD_SYMBOL_LOCATION_MIN, ONE_SYM_PWD_SYMBOL_LOCATION_MAX);

	if(!SetTempPasswordRules(pUser -> userID, userTmpPwdConstRules, userTmpPwdConstRulesCount))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SetTempOneSymbolBoxesPassword. Can't save password construction rules!");
			WriteToLog("ResponseValidator : SetTempOneSymbolBoxesPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	int tmpUserToken = encryptor -> RangedRand(1000, 9999);

	PreparePasswordResetMessage(pUser, tmpUserToken, userTmpPwdConstRules, userTmpPwdConstRulesCount, messageBuffer);
				
	SaveUserResetFlag(pUser, tmpUserToken);
			
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : SetTempOneSymbolBoxesPassword. Password successfully resseted!");
		WriteToLog("ResponseValidator : SetTempOneSymbolBoxesPassword. Done");
	#endif

	return RESPONSE_OK;
	
}

/****************************************************************

	Class : ResponseValidator

	Method :  SetTempTwoSymbolsBoxesPassword
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor

			Output:
				messageBuffer - result message

	Return:  Error code

	Description :  Set temporary symbol boxes password

*****************************************************************/
int ResponseValidator :: SetTempTwoSymbolsBoxesPassword(PUSER_DESCRIPTOR pUser, char * messageBuffer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : SetTempTwoSymbolsBoxesPassword. Start");
	#endif

	if ((pUser == NULL) || (messageBuffer == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SetTempTwoSymbolsBoxesPassword. Wrong input data!");
			WriteToLog("ResponseValidator : SetTempTwoSymbolsBoxesPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	DeleteTempPasswordRules(pUser -> userID);
	// Generate temporary rules
	int userTmpPwdConstRulesCount = 5;
	int userTmpPwdConstRules[MAX_PWD_CONSTR_RULES_COUNT];

	userTmpPwdConstRules[0] = encryptor -> RangedRand(TWO_SYM_PWD_JOKER_1_MIN, TWO_SYM_PWD_JOKER_1_MAX);
	userTmpPwdConstRules[1] = encryptor -> RangedRand(TWO_SYM_PWD_JOKER_2_MIN, TWO_SYM_PWD_JOKER_2_MAX);
	userTmpPwdConstRules[2] = encryptor -> RangedRand(TWO_SYM_PWD_FORMULA_MIN, TWO_SYM_PWD_FORMULA_MAX);
	userTmpPwdConstRules[3] = encryptor -> RangedRand(TWO_SYM_PWD_PAIR_LOCATION_MIN, TWO_SYM_PWD_PAIR_LOCATION_MAX);
	userTmpPwdConstRules[4] = encryptor -> RangedRand(TWO_SYM_PWD_SYMBOL_LOCATION_MIN, TWO_SYM_PWD_SYMBOL_LOCATION_MAX);

	if(!SetTempPasswordRules(pUser -> userID, userTmpPwdConstRules, userTmpPwdConstRulesCount))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SetTempTwoSymbolsBoxesPassword. Can't save password construction rules!");
			WriteToLog("ResponseValidator : SetTempTwoSymbolsBoxesPassword. Done");
		#endif

		return RESPONSE_BAD;
	}
	
	// Generate temp user token
	int tmpUserToken = encryptor -> RangedRand(1000, 9999);

	PreparePasswordResetMessage(pUser, tmpUserToken, userTmpPwdConstRules, userTmpPwdConstRulesCount, messageBuffer);
				
	SaveUserResetFlag(pUser, tmpUserToken);
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : SetTempTwoSymbolsBoxesPassword. Password successfully resseted!");
		WriteToLog("ResponseValidator : SetTempTwoSymbolsBoxesPassword. Done");
	#endif

	return RESPONSE_OK;
	
}

/****************************************************************

	Class : ResponseValidator

	Method :  GetPasswordTypeName
    
	Parameters :
			Input : 
				passwordTypeID - password type ID

			Output:
				passwordTypeName - password type name

	Return:  password type name

	Description :  Get password type name

*****************************************************************/
char * ResponseValidator :: GetPasswordTypeName(int passwordTypeID, char * passwordTypeName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : GetPasswordTypeName. Start");
	#endif
	
	if (passwordTypeName == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : GetPasswordTypeName. Wrong input data!");
			WriteToLog("ResponseValidator : GetPasswordTypeName. Done");
		#endif

		return passwordTypeName;
	}
	
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Get password type name query
		sprintf(sql, "SELECT PasswordConstructionRulesTypes.Name, DATALENGTH(PasswordConstructionRulesTypes.Name)\
					  FROM PasswordConstructionRulesTypes\
					  WHERE (PasswordConstructionRulesTypes.ID = %d)", passwordTypeID);

		// Execute SQl query
		ResultSet * pwdTypeResult = dbManager -> ExecuteSelectQuery(sql);

		unsigned char pwdTypeNameBuf[ENCRYPTED_DATA_SIZE];
		int pwdTypeNameLenBuf = 0;

		pwdTypeResult -> Bind(1, pwdTypeNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		pwdTypeResult -> Bind(2, &pwdTypeNameLenBuf, sizeof(pwdTypeNameLenBuf), SQL_C_LONG);
				
		if (!((pwdTypeResult -> MoveFirst()) && (DecryptString(pwdTypeNameBuf, pwdTypeNameLenBuf, passwordTypeName))))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
				WriteToLog("ResponseValidator : GetPasswordTypeName. Can't get password type name!");
			#endif

			strcpy(passwordTypeName, "UNKNOWN");
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		else
		{
			WriteToLog("ResponseValidator : GetPasswordTypeName. Password type name succesully decrypted!");
		}
			WriteToLog("ResponseValidator : GetPasswordTypeName. Done");
		#endif

		delete pwdTypeResult;

		return passwordTypeName;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return NULL;
	}
}

/****************************************************************

	Class : ResponseValidator

	Method :  PreparePasswordResetMessage
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor
				userTmpPwdConstRules - user tmp rules list
				userTmpPwdConstRulesCount - user tmp rules list size

			Output:
				messageBuffer - message buffer

	Return:  password reset message

	Description :  Prepare password reset message

*****************************************************************/
char * ResponseValidator :: PreparePasswordResetMessage(PUSER_DESCRIPTOR pUser, int tmpUserToken, int * userTmpPwdConstRules, int userTmpPwdConstRulesCount, char * messageBuffer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : PreparePasswordResetMessage. Start");
	#endif
	
	if ((pUser == NULL) || (messageBuffer == NULL) || (userTmpPwdConstRules == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : PreparePasswordResetMessage. Wrong input data!");
			WriteToLog("ResponseValidator : PreparePasswordResetMessage. Done");
		#endif

		return messageBuffer;
	}
	
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Temp user token
		char token[8];
		char number[3];
		
		// Prepare message
		char userName[NAME_LEN];
		if (!DecryptString(pUser -> encName, pUser -> encNameLen, userName))
			strcpy(userName, "UNKNOWN");
		
		char passwordTypeName[NAME_LEN];
		GetPasswordTypeName(pUser -> pwdType, passwordTypeName);

		strcpy(messageBuffer, "Dear user ");
		strcat(messageBuffer, userName);
		strcat(messageBuffer, ".\nPlease note that your NovaTend password was reset.\n");
		strcat(messageBuffer, "\nYou are using password type: ");
		strcat(messageBuffer, passwordTypeName);
		strcat(messageBuffer, "\n\nYour new temporary token is: ");
		strcat(messageBuffer, itoa(tmpUserToken, token, 10));
		strcat(messageBuffer, "\n\nIf you do not set permanent password within the next ");
		strcat(messageBuffer, itoa(pUser -> pwdResetPeriod, number, 10));
		strcat(messageBuffer, " hours, your temporary password will expire.\nIf you forgot your current password, you will have to reset your password again.\n\n");
		strcat(messageBuffer, "Below are your login parameters:\n");
		
		unsigned char ruleNameBuf[ENCRYPTED_DATA_SIZE];
		int ruleNameLenBuf = 0;
		
		char ruleName[NAME_LEN];

		for(int i = 0; i < userTmpPwdConstRulesCount; i++)
		{
			char sql[SQL_SIZE];
			sprintf(sql, "SELECT PasswordConstructionRules.Name, DATALENGTH(PasswordConstructionRules.Name)\
							FROM PasswordConstructionRules\
							WHERE (PasswordConstructionRules.ID = %d)", userTmpPwdConstRules[i]);
		
			// Execute SQl query
			ResultSet * rulesResult = dbManager -> ExecuteSelectQuery(sql);

			rulesResult -> Bind(1, ruleNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
			rulesResult -> Bind(2, &ruleNameLenBuf, sizeof(ruleNameLenBuf), SQL_C_LONG);

			strcat(messageBuffer, itoa(i + 1, number, 10));
			strcat(messageBuffer, ". ");

			if ((rulesResult -> MoveFirst()) && (DecryptString(ruleNameBuf, ruleNameLenBuf, ruleName)))
			{
				strcat(messageBuffer, ruleName);
				strcat(messageBuffer, ";\n");
			}
			else
			{
				strcat(messageBuffer, "UNKNOWN RULE;\n");
			}

			delete rulesResult;
		}

		strcat(messageBuffer, "\nIf you do not attempt to reset password, please ignore this message!");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : PreparePasswordResetMessage. Password reset message created successfully!");
			WriteToLog("ResponseValidator : PreparePasswordResetMessage. Done");
		#endif

		return messageBuffer;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return NULL;
	}
}

/****************************************************************

	Class : ResponseValidator

	Method :  SaveUserResetFlag
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor
				tmpUserToken - new user temp token


	Description :  Save user reset params

*****************************************************************/
void ResponseValidator :: SaveUserResetFlag(PUSER_DESCRIPTOR pUser, int tmpUserToken)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : SaveUserResetFlag. Start");
	#endif
	
	if (pUser == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SaveUserResetFlag. Wrong input data!");
			WriteToLog("ResponseValidator : SaveUserResetFlag. Done");
		#endif

		return;
	}
	
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Set reset flag
		sprintf(sql, "UPDATE Users\
							SET Users.PwdResetted = 1,\
							Users.PwdResetDate = GETDATE(),\
							Users.TmpUserToken = %d\
						WHERE (Users.ID = %d)", tmpUserToken, pUser -> userID);

		dbManager -> Execute(sql);

		pUser -> pwdReseted = true;

		// Get reset date from DB
		sprintf(sql, "SELECT Users.PwdResetDate\
					  FROM Users\
					   WHERE (Users.ID = %d)", pUser -> userID);
		
		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		char pwdResetDateBuf[STR_VALUE_LEN];

		usersResult -> Bind(1, pwdResetDateBuf, STR_VALUE_LEN);

		if (usersResult -> MoveFirst())
			strcpy(pUser -> pwdResetDate, pwdResetDateBuf);

		delete usersResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : SaveUserResetFlag. Done");
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

/****************************************************************

	Class : ResponseValidator

	Method :  ResetUserCustomPassword
    
	Parameters :
			Input : 
				pUser - pointer to user descriptor

			Output:
				email - decrypted user email address
				phone - decrypted user phone number
				messageBuffer - result message

	Return:  Error code

	Description :  Reset user custom password

*****************************************************************/
int ResponseValidator :: ResetUserCustomPassword(PUSER_DESCRIPTOR pUser, char * email, char * phone, char * messageBuffer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
		WriteToLog("ResponseValidator : ResetUserCustomPassword. Start");
	#endif

	if ((pUser == NULL) || (email == NULL) || (phone == NULL) || (messageBuffer == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
			WriteToLog("ResponseValidator : ResetUserCustomPassword. Wrong input data!");
			WriteToLog("ResponseValidator : ResetUserCustomPassword. Done");
		#endif

		return RESPONSE_BAD;
	}

	if (pUser -> emailPwdReset)
	{
		if (!DecryptString(pUser -> encEmailAddress, pUser -> encEmailAddressLen, email))
			return RESET_PWD_WRONG_EMAIL_ADDRESS;
	}

	if (pUser -> smsPwdReset)
	{
		if (!DecryptString(pUser -> encPhoneNumber, pUser -> encPhoneNumberLen, phone))
			return RESET_PWD_WRONG_PHONE_NUMBER;
	}

	switch (pUser -> pwdType)
	{
		case CASCADE_STRING_PWD :
			{
				int resetResult = SetTempCascadeStringPassword(pUser, messageBuffer);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
					WriteToLog("ResponseValidator : ResetUserCustomPassword. Cascade string password reseted!");
					WriteToLog("ResponseValidator : ResetUserCustomPassword. Done");
				#endif

				return resetResult;
			}

		case ONE_SYMBOL_BOX_PWD :
			{
				int resetResult = SetTempOneSymbolBoxesPassword(pUser, messageBuffer);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
					WriteToLog("ResponseValidator : ResetUserCustomPassword. Symbol boxes password (one symbol) reseted!");
					WriteToLog("ResponseValidator : ResetUserCustomPassword. Done");
				#endif

				return resetResult;
			}

		case TWO_SYMBOL_BOX_PWD :
			{
				int resetResult = SetTempTwoSymbolsBoxesPassword(pUser, messageBuffer);

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
					WriteToLog("ResponseValidator : ResetUserCustomPassword. Symbol boxes password (two symbols) reseted!");
					WriteToLog("ResponseValidator : ResetUserCustomPassword. Done");
				#endif

				return resetResult;
			}

		default:
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_VAL_RESP)
					WriteToLog("ResponseValidator : ResetUserCustomPassword. Wrong password type!");
					WriteToLog("ResponseValidator : ResetUserCustomPassword. Done");
				#endif

				return RESPONSE_BAD;
			}
	}
}

#pragma endregion

#pragma region LOG
/****************************************************************

   Class : ResponseValidator

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int ResponseValidator ::  WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion