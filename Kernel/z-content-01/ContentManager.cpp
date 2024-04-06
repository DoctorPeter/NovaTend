/****************************************************************

   Solution : NovaTend

   Project : z-content-01.dll

   Module : ContentManager.cpp

   Description :  this module implements methods of
				  class ContentManager

*****************************************************************/

#include "stdafx.h"

#include "ContentManager.h"
#include <ODBCDatabaseManager.h>
#include <SettingsManager.h>
#include <Scheduler.h>

#include <stdio.h>
#include <stdlib.h>

// z-content-01.dll definition structure
extern DLL_COMMON_DEFINITION zContentDllDefinition;

#pragma region Constructor

/****************************************************************

   Class : ContentManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
ContentManager :: ContentManager(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zContentDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : constructor");
	#endif

	dbManager = new ODBCDatabaseManager(zContentDllDefinition.dllID, logWriter);
	encryptor = new Encryptor(zContentDllDefinition.dllID);

	DatabaseConnect();
}

/****************************************************************

   Class : ContentManager

   Method : Destructor

*****************************************************************/
ContentManager :: ~ContentManager(void)
{
	DatabaseDisconnect();

	delete dbManager;
	delete encryptor;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : destructor");
	#endif
}

#pragma endregion

#pragma region Database

/****************************************************************

   Class : ContentManager

   Method : DatabaseConnect

   Return : Connection state

   Description :  Connect to database

*****************************************************************/
bool ContentManager :: DatabaseConnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DatabaseConnect. Start");
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

			SettingsManager * settingsManager = new SettingsManager(zContentDllDefinition.dllID);

			if (settingsManager -> GetDatabaseSourceName(dsn) != ERROR_SUCCESS)
				WriteToLog("Content manager : Connect to DB --> Can't get DSN ");

			if (settingsManager -> GetDatabaseUserName(dbUser) != ERROR_SUCCESS)
				WriteToLog("Content manager :  Connect to DB --> Can't get db user name ");

			if (settingsManager -> GetDatabasePassword(dbPassword) != ERROR_SUCCESS)
				WriteToLog("Content manager :  Connect to DB --> Can't get db password ");

			delete settingsManager;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : DatabaseConnect. Connecting...");
			#endif

			// Connect
			dbManager -> Connect(dsn, dbUser, dbPassword);
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			else
				WriteToLog("ContentManager : DatabaseConnect. Already connected!");

			WriteToLog("ContentManager : DatabaseConnect. Done");
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

   Class : ContentManager

   Method : DatabaseDisconnect

   Return : Connection state

   Description :  Disconnect from database

*****************************************************************/
bool ContentManager :: DatabaseDisconnect(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DatabaseDisconnect. Start");
	#endif

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Check connection
		if (dbManager -> Opened())
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : DatabaseDisconnect. Disconnecting...");
			#endif

			// Disconnect
			dbManager -> Disconnect();
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			else
				WriteToLog("ContentManager : DatabaseDisconnect. Already disconnected!");

			WriteToLog("ContentManager : DatabaseDisconnect. Done");
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

   Class : ContentManager

   Method : GetUserPermissions

   Parameters :
			Input : 
				user ID - user ID
			
			Output:
				userPermissions - user permissions list
				userPermissionsCount - user permissions count

	Returns: success flag
	
   Description :  Get user permissions

*****************************************************************/
bool ContentManager :: GetUserPermissions(int userID, int * userPermissions, int * userPermissionsCount)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserPermissions. Start");
	#endif
		
	// Check input data
	if ((userPermissions == NULL) || (userPermissionsCount == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserPermissions. Wrong input data!");
			WriteToLog("ContentManager : GetUserPermissions. Done");
		#endif

		return false;
	}

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// SQL query buffer
		char sql[SQL_SIZE];

		// Get permissions of user
		sprintf(sql, "SELECT UserPermissions.PermissionID\
					  FROM UserPermissions\
					  WHERE (UserPermissions.UserID = %d)", userID);
		
		// Execute query
		ResultSet * permissionsResult = dbManager -> ExecuteSelectQuery(sql);
		
		int permissionIDBuf;

		// Bind data
		permissionsResult -> Bind(1, &permissionIDBuf, sizeof(permissionIDBuf), SQL_C_LONG);

		int count = 0;

		while(permissionsResult -> MoveNext())
		{
			userPermissions[count] = permissionIDBuf;
			count++;
		}
		
		delete permissionsResult;

		// Get permissions of user groups
		sprintf(sql, "SELECT UserGroupPermissions.PermissionID\
					  FROM UserGroupPermissions\
					  WHERE UserGroupPermissions.GroupID in (SELECT UserGroupUsers.GroupID\
															 FROM UserGroupUsers\
															 WHERE UserGroupUsers.UserID = %d)", userID);

		// Execute query
		permissionsResult = dbManager -> ExecuteSelectQuery(sql);

		// Bind data
		permissionsResult -> Bind(1, &permissionIDBuf, sizeof(permissionIDBuf), SQL_C_LONG);

		while (permissionsResult -> MoveNext())
		{
			userPermissions[count] = permissionIDBuf;
			count++;
		}

		*userPermissionsCount = count;
		delete permissionsResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserPermissions. Done");
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

   Class : ContentManager 

   Method : CheckDBAccess

   Return : Success flag

   Description : Check database connection

*****************************************************************/
bool ContentManager :: CheckDBAccess(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CheckDBAccess. Start");
	#endif
		
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		if (dbManager -> Opened())
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : CheckDBAccess. Successfull connection!");	
			#endif

			return true;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : CheckDBAccess. Connection failed!");	
			#endif

			return false;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckDBAccess. Done");
		#endif
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

#pragma region User security data

/****************************************************************

   Class : ContentManager

   Method : CreateUserSecurityData
   
   Return : pointer to user security data structure
	
   Description :  Create user security data structure

*****************************************************************/
PUSER_SECURITY_DATA ContentManager :: CreateUserSecurityData(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CreateUserSecurityData. Start");
	#endif
	
	PUSER_SECURITY_DATA securityData = (PUSER_SECURITY_DATA)malloc(sizeof(USER_SECURITY_DATA));

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		if (securityData)
			WriteToLog("ContentManager : CreateUserSecurityData. Success");
		else
			WriteToLog("ContentManager : CreateUserSecurityData. Error of memory allocation!");

		WriteToLog("ContentManager : CreateUserSecurityData. Done");
	#endif

	return securityData;
}

/****************************************************************

   Class : ContentManager

   Method : RemoveUserSecurityData
   
   Parameters :
			Input : 
				user - pointer to user security data structure

   Return : pointer to user security data structure
	
   Description :  Remove user security data structure

*****************************************************************/
PUSER_SECURITY_DATA ContentManager :: RemoveUserSecurityData(PUSER_SECURITY_DATA securityData)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : RemoveUserSecurityData");
	#endif

	if (securityData)
	{
		free(securityData);
		securityData = NULL;
	}

	return securityData;
}

/****************************************************************

   Class : ContentManager

   Method : GetUserSecurityData

   Parameters:
			Input:
				userID - user ID
				authSystemID - authentication system ID

   Return : pointer to user security data structure
	
   Description :  Get user security data structure

*****************************************************************/
PUSER_SECURITY_DATA ContentManager :: GetUserSecurityData(int userID, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserSecurityData. Start");
	#endif

	// Create security data
	PUSER_SECURITY_DATA securityData = CreateUserSecurityData();

	// Validate pointer
	if(!securityData)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserSecurityData. User security data structure was not created");
			WriteToLog("ContentManager : GetUserSecurityData. Done");
		#endif

		return securityData;
	}

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT UserAccounts.UserName,\
					        DATALENGTH(UserAccounts.UserName),\
							UserAccounts.Password,\
							DATALENGTH(UserAccounts.Password),\
							UserAccounts.LastSignInDate,\
							UserAccounts.PassThru\
					FROM UserAccounts\
					WHERE ((UserAccounts.UserID = %d) and (UserAccounts.AuthSystemID = %d))", userID, authSystemID);

		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		// Prepare buffers
		unsigned char sysUserNameBuf[ENCRYPTED_DATA_SIZE];
		int sysUserNameLenBuf = 0;
		unsigned char sysPwdBuf[ENCRYPTED_DATA_SIZE];
		int sysPwdLenBuf = 0;
		char dateBuf[STR_VALUE_LEN];
		int passThruFlag = 0;

		// Bind data
		usersResult -> Bind(1,  sysUserNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(2,  &sysUserNameLenBuf, sizeof(sysUserNameLenBuf), SQL_C_LONG);
		usersResult -> Bind(3,  sysPwdBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(4,  &sysPwdLenBuf, sizeof(sysPwdLenBuf), SQL_C_LONG);
		usersResult -> Bind(5,  dateBuf, STR_VALUE_LEN);
		usersResult -> Bind(6,  &passThruFlag, sizeof(passThruFlag), SQL_C_LONG);
		
		if (usersResult -> MoveFirst())
		{
			securityData -> userID = userID;
			securityData -> authSystemID = authSystemID;
			securityData -> passThru = (passThruFlag == 0) ? false : true;
			strcpy(securityData -> lastLogOnDate, dateBuf);

			securityData -> encSystemUserNameLen = sysUserNameLenBuf;
			if (sysUserNameLenBuf > ENCRYPTED_DATA_SIZE)
				memcpy(securityData -> encSystemUserName, sysUserNameBuf, ENCRYPTED_DATA_SIZE);
			else
				memcpy(securityData -> encSystemUserName, sysUserNameBuf, sysUserNameLenBuf);

			securityData -> encSystemPasswordLen = sysPwdLenBuf;
			if (sysPwdLenBuf > ENCRYPTED_DATA_SIZE)
				memcpy(securityData -> encSystemPassword, sysPwdBuf, ENCRYPTED_DATA_SIZE);
			else
				memcpy(securityData -> encSystemPassword, sysPwdBuf, sysPwdLenBuf);

			delete usersResult;
		}
		else
		{
			securityData = RemoveUserSecurityData(securityData);
			delete usersResult;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserSecurityData. Wrong input data!");
				WriteToLog("ContentManager : GetUserSecurityData. Done");
			#endif

			return securityData;
		}

		// Prepare sql query
		sprintf(sql, "SELECT Users.UserToken,\
							 Users.TmpUserToken,\
							 Users.PwdTypeID\
						  FROM Users\
							WHERE (Users.ID = %d)", userID);

		// Execute SQl query
		usersResult = dbManager -> ExecuteSelectQuery(sql);

		// Prepare buffers
		int userTokenBuf = 0;
		int tmpUserTokenBuf = 0;
		int pwdTypeBuf = 0;

		// Bind data
		usersResult -> Bind(1, &userTokenBuf, sizeof(userTokenBuf), SQL_C_LONG);
		usersResult -> Bind(2, &tmpUserTokenBuf, sizeof(tmpUserTokenBuf), SQL_C_LONG);
		usersResult -> Bind(3, &pwdTypeBuf, sizeof(pwdTypeBuf), SQL_C_LONG);
		
		// Retrieve record
		if (usersResult -> MoveFirst())
		{
			securityData -> userToken = userTokenBuf;
			securityData -> tmpUserToken = tmpUserTokenBuf;
			securityData -> pwdType = pwdTypeBuf;
			delete usersResult;
		}
		else
		{
			securityData = RemoveUserSecurityData(securityData);
			delete usersResult;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserSecurityData. Wrong user ID!");
				WriteToLog("ContentManager : GetUserSecurityData. Done");
			#endif

			return securityData;
		}
		
		if (!GetUserPasswordConstructionRules(securityData))
		{
			securityData = RemoveUserSecurityData(securityData);
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserSecurityData. Can't read password construction rules!");
				WriteToLog("ContentManager : GetUserSecurityData. Done");
			#endif

			return securityData;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserSecurityData. Done");
		#endif

		return securityData;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return RemoveUserSecurityData(securityData);
	}
}

/****************************************************************

   Class : ContentManager

   Method : GetUserSecurityData

   Parameters:
			Input:
				userID - user ID
				
   Return : pointer to user security data structure
	
   Description :  Get user security data structure

*****************************************************************/
PUSER_SECURITY_DATA ContentManager :: GetUserSecurityData(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserSecurityData. Start");
	#endif

	// Create security data
	PUSER_SECURITY_DATA securityData = CreateUserSecurityData();

	// Validate pointer
	if(!securityData)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserSecurityData. User security data structure was not created");
			WriteToLog("ContentManager : GetUserSecurityData. Done");
		#endif

		return securityData;
	}

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT Users.UserToken,\
							 Users.TmpUserToken,\
							 Users.PwdTypeID\
						  FROM Users\
							WHERE (Users.ID = %d)", userID);

		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		// Prepare buffers
		int userTokenBuf = 0;
		int tmpUserTokenBuf = 0;
		int pwdTypeBuf = 0;

		// Bind data
		usersResult -> Bind(1, &userTokenBuf, sizeof(userTokenBuf), SQL_C_LONG);
		usersResult -> Bind(2, &tmpUserTokenBuf, sizeof(tmpUserTokenBuf), SQL_C_LONG);
		usersResult -> Bind(3, &pwdTypeBuf, sizeof(pwdTypeBuf), SQL_C_LONG);
		
		// Retrieve record
		if (usersResult -> MoveFirst())
		{
			securityData -> userID = userID;
			securityData -> encSystemPasswordLen = 0;
			securityData -> encSystemUserNameLen = 0;
			securityData -> authSystemID = -1;
			securityData -> passThru = false;
			securityData ->  lastLogOnDate[0] = 0;
			securityData -> userToken = userTokenBuf;
			securityData -> tmpUserToken = tmpUserTokenBuf;
			securityData -> pwdType = pwdTypeBuf;
			delete usersResult;
		}
		else
		{
			securityData = RemoveUserSecurityData(securityData);
			delete usersResult;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserSecurityData. Wrong user ID!");
				WriteToLog("ContentManager : GetUserSecurityData. Done");
			#endif

			return securityData;
		}
		
		if (!GetUserPasswordConstructionRules(securityData))
		{
			securityData = RemoveUserSecurityData(securityData);
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserSecurityData. Can't read password construction rules!");
				WriteToLog("ContentManager : GetUserSecurityData. Done");
			#endif

			return securityData;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserSecurityData. Done");
		#endif

		return securityData;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return RemoveUserSecurityData(securityData);
	}
}

/****************************************************************

   Class : ContentManager

   Method : GetUserPasswordConstructionRules
   
   Parameters :
			Input : 
				securityData - pointer to user security data structure
				
   Return : TRUE - if success
	
   Description :  Get user password construction rules

*****************************************************************/
bool ContentManager :: GetUserPasswordConstructionRules(PUSER_SECURITY_DATA securityData)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserPasswordConstructionRules. Start");
	#endif
		
	// Validate pointer
	if(!securityData)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserPasswordConstructionRules. Wrong input data!");
			WriteToLog("ContentManager : GetUserPasswordConstructionRules. Done");
		#endif

		return false;
	}

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		// Retrieving password construction rules

		// Prepare SQL query
		sprintf(sql, "SELECT UserPasswordConstructionRules.RuleID\
						FROM UserPasswordConstructionRules, PasswordConstructionRules\
						WHERE ((UserPasswordConstructionRules.RuleID = PasswordConstructionRules.ID) AND\
								(UserPasswordConstructionRules.UserID = %d) AND\
  								(UserPasswordConstructionRules.TmpRule = 0) AND\
  								(PasswordConstructionRules.TypeID = %d))\
								ORDER BY UserPasswordConstructionRules.RulesOrder", securityData -> userID, securityData -> pwdType);

		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		int ruleIDBuf = 0;
				
		usersResult -> Bind(1, &ruleIDBuf, sizeof(ruleIDBuf), SQL_C_LONG);

		securityData -> pwdConstRulesCount = 0;
		while(usersResult -> MoveNext())
		{
			securityData -> pwdConstRules[securityData -> pwdConstRulesCount] = ruleIDBuf;
			securityData -> pwdConstRulesCount++;
		}
		
		delete usersResult;

		// Check symbol box password
		if (((securityData -> pwdType == TWO_SYMBOL_BOX_PWD) && (CheckTwoSymbolsBoxPasswordConstructionRules(securityData -> pwdConstRules, securityData -> pwdConstRulesCount) == false)) || 
			((securityData -> pwdType == ONE_SYMBOL_BOX_PWD) && (CheckOneSymbolBoxPasswordConstructionRules(securityData -> pwdConstRules, securityData -> pwdConstRulesCount) == false)))
			securityData -> pwdConstRulesCount = 0;

		// Retrieving temporary password construction rules

		// Prepare SQL query
		sprintf(sql, "SELECT UserPasswordConstructionRules.RuleID\
						FROM UserPasswordConstructionRules, PasswordConstructionRules\
						WHERE ((UserPasswordConstructionRules.RuleID = PasswordConstructionRules.ID) AND\
								(UserPasswordConstructionRules.UserID = %d) AND\
  								(UserPasswordConstructionRules.TmpRule = 1) AND\
  								(PasswordConstructionRules.TypeID = %d))\
								ORDER BY UserPasswordConstructionRules.RulesOrder", securityData -> userID, securityData -> pwdType);


		// Execute SQl query
		usersResult = dbManager -> ExecuteSelectQuery(sql);
		usersResult -> Bind(1, &ruleIDBuf, sizeof(ruleIDBuf), SQL_C_LONG);

		securityData -> tmpPwdConstRulesCount = 0;
		while(usersResult -> MoveNext())
		{
			securityData -> tmpPwdConstRules[securityData -> tmpPwdConstRulesCount] = ruleIDBuf;
			securityData -> tmpPwdConstRulesCount++;
		}

		delete usersResult;

		// Check symbol box password
		if (((securityData -> pwdType == TWO_SYMBOL_BOX_PWD) && (CheckTwoSymbolsBoxPasswordConstructionRules(securityData -> tmpPwdConstRules, securityData -> tmpPwdConstRulesCount) == false)) || 
			((securityData -> pwdType == ONE_SYMBOL_BOX_PWD) && (CheckOneSymbolBoxPasswordConstructionRules(securityData -> tmpPwdConstRules, securityData -> tmpPwdConstRulesCount) == false)))
			securityData -> tmpPwdConstRulesCount = 0;

	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserPasswordConstructionRules. Done");
	#endif

	return true;
}

/****************************************************************

   Class : ContentManager

   Method : CheckOneSymbolBoxPasswordConstructionRules
   
   Parameters :
			Input : 
				rules - password construction rules list
				rulesCout - password construction rules list size

   Return : TRUE - if success
	
   Description :  Check symbol box password (one symbol per cell)

*****************************************************************/
bool ContentManager :: CheckOneSymbolBoxPasswordConstructionRules(int * rules, int rulesCount)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Start");
	#endif

	// Check input data
	if ((!rules) || (rulesCount != 4))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Wrong input data");
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}
	
	bool found = false;

	// Check for joker 1
	for(int i = 0; i < rulesCount; i++)
	{
		if ((rules[i] >= ONE_SYM_PWD_JOKER_1_MIN) && (rules[i] <= ONE_SYM_PWD_JOKER_1_MAX))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Joker 1 not found!");
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}

	found = false;

	// Check for joker 2
	for(int i = 0; i < rulesCount; i++)
	{
		if ((rules[i] >= ONE_SYM_PWD_JOKER_2_MIN) && (rules[i] <= ONE_SYM_PWD_JOKER_2_MAX))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Joker 2 not found!");
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}

	found = false;

	// Check for formula
	for(int i = 0; i < rulesCount; i++)
	{
		if ((rules[i] >= ONE_SYM_PWD_FORMULA_MIN) && (rules[i] <= ONE_SYM_PWD_FORMULA_MAX))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Formula not found!");
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}
	
	found = false;

	// Check for symbol location
	for(int i = 0; i < rulesCount; i++)
	{
		if ((rules[i] >= ONE_SYM_PWD_SYMBOL_LOCATION_MIN) && (rules[i] <= ONE_SYM_PWD_SYMBOL_LOCATION_MAX))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Symbol location not found!");
			WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CheckOneSymbolBoxPasswordConstructionRules. Done");
	#endif

	return true;
}

/****************************************************************

   Class : ContentManager

   Method : CheckTwoSymbolsBoxPasswordConstructionRules
   
   Parameters :
			Input : 
				rules - password construction rules list
				rulesCout - password construction rules list size

   Return : TRUE - if success
	
   Description :  Check symbol box password (two symbols per cell)

*****************************************************************/
bool ContentManager :: CheckTwoSymbolsBoxPasswordConstructionRules(int * rules, int rulesCount)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Start");
	#endif

	// Check input data
	if ((!rules) || (rulesCount != 5))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Wrong input data");
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}
	
	bool found = false;

	// Check for joker 1
	for(int i = 0; i < rulesCount; i++)
	{
		if ((rules[i] >= TWO_SYM_PWD_JOKER_1_MIN) && (rules[i] <= TWO_SYM_PWD_JOKER_1_MAX))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Joker 1 not found!");
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}

	found = false;

	// Check for joker 2
	for(int i = 0; i < rulesCount; i++)
	{
		if ((rules[i] >= TWO_SYM_PWD_JOKER_2_MIN) && (rules[i] <= TWO_SYM_PWD_JOKER_2_MAX))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Joker 2 not found!");
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}

	found = false;

	// Check for formula
	for(int i = 0; i < rulesCount; i++)
	{
		if ((rules[i] >= TWO_SYM_PWD_FORMULA_MIN) && (rules[i] <= TWO_SYM_PWD_FORMULA_MAX))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Formula not found!");
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}

	found = false;

	// Check for pair location
	for(int i = 0; i < rulesCount; i++)
	{
		if ((rules[i] >= TWO_SYM_PWD_PAIR_LOCATION_MIN) && (rules[i] <= TWO_SYM_PWD_PAIR_LOCATION_MAX))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Pair location not found!");
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}

	found = false;

	// Check for symbol location
	for(int i = 0; i < rulesCount; i++)
	{
		if ((rules[i] >= TWO_SYM_PWD_SYMBOL_LOCATION_MIN) && (rules[i] <= TWO_SYM_PWD_SYMBOL_LOCATION_MAX))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Symbol location not found!");
			WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Done");
		#endif

		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CheckTwoSymbolsBoxPasswordConstructionRules. Done");
	#endif

	return true;
}

#pragma endregion

#pragma region User descriptor

/****************************************************************

   Class : ContentManager

   Method : CreateUserDescriptor
   
   Return : pointer to user descriptor
	
   Description :  Create user descriptor

*****************************************************************/
PUSER_DESCRIPTOR ContentManager :: CreateUserDescriptor(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CreateUserDescriptor. Start");
	#endif
	
	PUSER_DESCRIPTOR user = (PUSER_DESCRIPTOR)malloc(sizeof(USER_DESCRIPTOR));

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		if (user)
			WriteToLog("ContentManager : CreateUserDescriptor. Success");
		else
			WriteToLog("ContentManager : CreateUserDescriptor. Error of memory allocation!");

		WriteToLog("ContentManager : CreateUserDescriptor. Done");
	#endif

	return user;
}

/****************************************************************

   Class : ContentManager

   Method : RemoveUserDescriptor
   
   Parameters :
			Input : 
				user - pointer to user descriptor

   Return : pointer to user descriptor
	
   Description :  Remove user descriptor

*****************************************************************/
PUSER_DESCRIPTOR ContentManager ::  RemoveUserDescriptor(PUSER_DESCRIPTOR user)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : RemoveUserDescriptor");
	#endif

	if (user)
	{
		free(user);
		user = NULL;
	}

	return user;
}

/****************************************************************

   Class : ContentManager

   Method : GetUserID
   
   Parameters :
			Input : 
				userName - user name

   Return : user ID
	
   Description :  Get user ID

*****************************************************************/
int ContentManager :: GetUserID(char * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserID. Start");
	#endif

	// User ID
	int userID = -1;

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT Users.ID, Users.UserName, DATALENGTH(Users.UserName) FROM Users");
		
		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		int userIDBuf = userID;
		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;

		// Bind data
		usersResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);
		usersResult -> Bind(2, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(3, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);

		// Retrieve record
		while (usersResult -> MoveNext())
		{
			unsigned char decryptedUserName[NAME_LEN];
			int decryptedUserNameLen;

			if (encryptor -> UnPackAndDecryptSecurityData(userNameBuf, userNameLenBuf, decryptedUserName, NAME_LEN, &decryptedUserNameLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserID. Can't decrypt user name!");
				#endif
			}
			else
			{
				decryptedUserName[decryptedUserNameLen] = 0;
				if (strcmp(userName, (char *)decryptedUserName) == 0)
				{
					userID = userIDBuf;
					break;
				}
			}

			userIDBuf = -1;
			userNameBuf[0] = 0;
			userNameLenBuf = 0;
		}

		delete usersResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserID. Done");
		#endif

		return userID;
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

   Class : ContentManager

   Method : GetUserID
   
   Parameters :
			Input : 
				userName - encrypted user name
				userNameLen - length of encrypted user name

   Return : user ID
	
   Description :  Get user ID

*****************************************************************/
int ContentManager :: GetUserID(unsigned char * userName, int userNameLen)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserID. Start");
	#endif

	unsigned char decryptedUserName[NAME_LEN];
	int decryptedUserNameLen = 0;
	int userID = -1;

	if (encryptor -> UnPackAndDecryptSecurityData(userName, userNameLen, decryptedUserName, NAME_LEN, &decryptedUserNameLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserID. Can't decrypt user name!");
			WriteToLog("ContentManager : GetUserID. Done");
		#endif

		return userID;
	}
	else
		decryptedUserName[decryptedUserNameLen] = 0;
	
	userID = GetUserID((char *)decryptedUserName);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserID. Done");
	#endif

	return userID;
}

/****************************************************************

   Class : ContentManager

   Method : GetUserNames

   Parameters:
			Input:
				userID - user ID
				authSystemID - authentication system ID
			Output:
				userName - encrypted name of user
				userNameLen - length of encrypted name of user
				sysUserName - encrypted system name of user
				sysUserNameLen - length of encrypted system name of user
				fullUserName - encrypted full name of user
				fullUserNameLen - length of encrypted full name of user

   Return : TRUE - if success

   Description : Get user names

*****************************************************************/
bool ContentManager :: GetUserNames(int userID, int authSystemID, unsigned char * userName, int * userNameLen, unsigned char * sysUserName, int * sysUserNameLen, unsigned char * fullUserName, int * fullUserNameLen)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserNames. Start");
	#endif
				
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Prepare sql query
		char sql[SQL_SIZE];
			
		sprintf(sql, "SELECT Users.Name, DATALENGTH(Users.Name),\
							 Users.UserName, DATALENGTH(Users.UserName),\
							 UserAccounts.UserName, DATALENGTH(UserAccounts.UserName)\
					  FROM Users, UserAccounts\
					  WHERE ((Users.ID = %d) AND (UserAccounts.UserID = %d) AND (UserAccounts.AuthSystemID = %d))", userID, userID, authSystemID);

		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);


		unsigned char nameBuf[ENCRYPTED_DATA_SIZE];
		int nameLenBuf = 0;
		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;
		unsigned char sysUserNameBuf[ENCRYPTED_DATA_SIZE];
		int sysUserNameLenBuf = 0;

		// Bind data
		usersResult -> Bind(1, nameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(2, &nameLenBuf, sizeof(nameLenBuf), SQL_C_LONG);
		usersResult -> Bind(3, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(4, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);
		usersResult -> Bind(5, sysUserNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(6, &sysUserNameLenBuf, sizeof(sysUserNameLenBuf), SQL_C_LONG);
		
		// Retrieve record
		if (usersResult -> MoveFirst())
		{
			// Get user name
			if (userNameLen) *userNameLen = userNameLenBuf;
			if (userName) memcpy(userName, userNameBuf, userNameLenBuf);

			// Get full user name
			if (fullUserNameLen) *fullUserNameLen = nameLenBuf;
			if (fullUserName) memcpy(fullUserName, nameBuf, nameLenBuf);

			// Get system user name
			if (sysUserNameLen) *sysUserNameLen = sysUserNameLenBuf;
			if (sysUserName) memcpy(sysUserName, sysUserNameBuf, sysUserNameLenBuf);

			delete usersResult;
		}
		else
		{
			*userNameLen = 0;
			*fullUserNameLen = 0;
			*sysUserNameLen = 0;
			delete usersResult;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserNames. Can't get user names!");
				WriteToLog("ContentManager : GetUserNames. Done");
			#endif

			return false;
		}
				
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserNames. Done");
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

   Class : ContentManager

   Method : GetUserEducationValues
   
   Parameters :
			Input : 
				user - pointer to user descriptor
				
   Return : TRUE - if success
	
   Description :  Get user education values

*****************************************************************/
bool ContentManager :: GetUserEducationValues(PUSER_DESCRIPTOR user)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserEducationValues. Start");
	#endif
		
	// Validate pointer
	if(!user)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserEducationValues. Wrong input data!");
			WriteToLog("ContentManager : GetUserEducationValues. Done");
		#endif

		return false;
	}

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE * 2];

		// Retrieving education info
		if (user -> needStudy)
		{
			// Prepare SQL query
			if (user -> randomEduCateg)
				sprintf(sql, "SELECT TOP 1 EducationCategories.ID\
				              FROM EducationCategories\
							  WHERE(((EducationCategories.ID in (SELECT TOP 1000 UserEducation.EduCategID\
				                                                 FROM UserEducation\
				                                                 WHERE (UserEducation.UserID = %d)\
				                                                 ORDER BY NEWID()))\
				                   OR\
				                   (EducationCategories.ID in (SELECT TOP 1000 UserGroupEducation.EduCategID\
				                                               FROM UserGroupEducation\
				                                               WHERE UserGroupEducation.GroupID in (SELECT UserGroupUsers.GroupID\
																									FROM UserGroupUsers\
																									WHERE (UserGroupUsers.UserID = %d))\
															   ORDER BY NEWID())))\
								   AND\
								   (EducationCategories.ID in (SELECT EducationLessons.CategoryID\
				                                               FROM EducationLessons\
															   WHERE EducationLessons.ID in (SELECT EducationQuestions.LessonID\
																						     FROM EducationQuestions\
																							 WHERE EducationQuestions.ID not in (SELECT UserEducationAnswers.QuestionID\
																																 FROM UserEducationAnswers\
																																 WHERE (UserEducationAnswers.UserID = %d) AND\
																																	   (UserEducationAnswers.CorrectAnswerSign = 1))))))", user -> userID, user -> userID, user -> userID);
			else
				sprintf(sql, "SELECT TOP 1 EducationCategories.ID\
				              FROM EducationCategories\
							  WHERE(((EducationCategories.ID in (SELECT TOP 1000 UserEducation.EduCategID\
				                                                 FROM UserEducation\
				                                                 WHERE (UserEducation.UserID = %d)\
				                                                 ORDER BY UserEducation.EduCategOrder))\
				                   OR\
				                   (EducationCategories.ID in (SELECT TOP 1000 UserGroupEducation.EduCategID\
				                                               FROM UserGroupEducation\
				                                               WHERE UserGroupEducation.GroupID in (SELECT UserGroupUsers.GroupID\
																									FROM UserGroupUsers\
																									WHERE (UserGroupUsers.UserID = %d))\
															   ORDER BY UserGroupEducation.EduCategOrder)))\
								   AND\
								   (EducationCategories.ID in (SELECT EducationLessons.CategoryID\
				                                               FROM EducationLessons\
															   WHERE EducationLessons.ID in (SELECT EducationQuestions.LessonID\
																						     FROM EducationQuestions\
																							 WHERE EducationQuestions.ID not in (SELECT UserEducationAnswers.QuestionID\
																																 FROM UserEducationAnswers\
																																 WHERE (UserEducationAnswers.UserID = %d) AND\
																																	   (UserEducationAnswers.CorrectAnswerSign = 1))))))", user -> userID, user -> userID, user -> userID);
								
			// Execute SQl query
			ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

			int categIDBuf;

			// Bind data
			usersResult -> Bind(1, &categIDBuf, sizeof(categIDBuf), SQL_C_LONG);

			if (usersResult -> MoveFirst())
			{
				user -> eduCategotyID = categIDBuf;
				
				// Prepare SQL query
				sprintf(sql, "SELECT UserEducation.RandomQuestion\
							  FROM UserEducation\
							  WHERE ((UserEducation.UserID = %d) AND \
								     (UserEducation.EduCategID = %d))", user -> userID, user -> eduCategotyID);

				delete usersResult;

				// Execute SQl query
				usersResult = dbManager -> ExecuteSelectQuery(sql);

				int rndQuestionBuf;

				// Bind data
				usersResult -> Bind(1, &rndQuestionBuf, sizeof(rndQuestionBuf), SQL_C_LONG);

				if (usersResult -> MoveFirst())
				{
					user -> eduQuestionRandom = (rndQuestionBuf == 0) ? false : true;
					delete usersResult;
				}
				else
				{
					// Prepare SQL query
					sprintf(sql, "SELECT UserGroupEducation.RandomQuestion\
								  FROM UserGroupEducation\
						          WHERE ((UserGroupEducation.GroupID in (SELECT UserGroupUsers.GroupID\
						                                                 FROM UserGroupUsers\
						                                                 WHERE (UserGroupUsers.UserID = %d)))\
						                AND (UserGroupEducation.EduCategID = %d))", user -> userID, user -> eduCategotyID);

					delete usersResult;

					// Execute SQl query
					usersResult = dbManager -> ExecuteSelectQuery(sql);

					// Bind data
					usersResult -> Bind(1, &rndQuestionBuf, sizeof(rndQuestionBuf), SQL_C_LONG);

					if (usersResult -> MoveFirst())
						user -> eduQuestionRandom = (rndQuestionBuf == 0) ? false : true;
					else
						user -> needStudy = false;

					delete usersResult;
				}
			}
			else
			{
				user -> needStudy = false;
				delete usersResult;
			}
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

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserEducationValues. Done");
	#endif

	return true;
}

/****************************************************************

   Class : ContentManager

   Method : GetUserDescriptor
   
   Parameters :
			Input : 
				userID - user ID
				
   Return : pointer to user descriptor
	
   Description :  Get user descriptor

*****************************************************************/
PUSER_DESCRIPTOR ContentManager :: GetUserDescriptor(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserDescriptor. Start");
	#endif
				
	// Allocate memory for user descriptor
	PUSER_DESCRIPTOR user = CreateUserDescriptor();

	// Validate pointer
	if(!user)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserDescriptor. User descriptor was not created");
			WriteToLog("ContentManager : GetUserDescriptor. Done");
		#endif

		return user;
	}

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT Users.Name,\
							DATALENGTH(Users.Name),\
							Users.UserName,\
							DATALENGTH(Users.UserName),\
							Users.NeedStudy,\
							Users.RandomEduCateg,\
							Users.LastSignInDate,\
							Users.PwdAttemptsCount,\
							Users.MaxPwdAttemptsCount,\
							Users.Email,\
							DATALENGTH(Users.Email),\
							Users.Phone,\
							DATALENGTH(Users.Phone),\
							Users.EmailPwdReset,\
							Users.SmsPwdReset,\
							Users.PwdResetted,\
							Users.PwdResetDate,\
							Users.PwdResetPeriod,\
							Users.Locked,\
							Users.PwdTypeID\
						  FROM Users\
							WHERE (Users.ID = %d)", userID);

		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		unsigned char nameBuf[ENCRYPTED_DATA_SIZE];
		int nameLenBuf = 0;
		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;
		int studyFlagBuf = 0;
		int rndCategBuf = 0;
		char signInDateBuf[STR_VALUE_LEN] = "";
		int pwdAttemptsCountBuf = 0;
		int maxPwdAttemptsCountBuf = 0;
		unsigned char emailBuf[ENCRYPTED_DATA_SIZE];
		int emailLenBuf = 0;
		unsigned char phoneBuf[ENCRYPTED_DATA_SIZE];
		int phoneLenBuf = 0;
		int emailPwdResetBuf = 0;
		int smsPwdResetBuf = 0;
		int pwdResetedFlagBuf = 0;
		char pwdResetDateBuf[STR_VALUE_LEN] = "";
		int pwdResetPeriodBuf = 0;
		int lockedBuf = 0;
		int pwdTypeBuf = 0;

		// Bind data
		usersResult -> Bind(1, nameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(2, &nameLenBuf, sizeof(nameLenBuf), SQL_C_LONG);
		usersResult -> Bind(3, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(4, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);
		usersResult -> Bind(5, &studyFlagBuf, sizeof(studyFlagBuf), SQL_C_LONG);
		usersResult -> Bind(6, &rndCategBuf, sizeof(rndCategBuf), SQL_C_LONG);
		usersResult -> Bind(7, signInDateBuf, STR_VALUE_LEN);
		usersResult -> Bind(8, &pwdAttemptsCountBuf, sizeof(pwdAttemptsCountBuf), SQL_C_LONG);
		usersResult -> Bind(9, &maxPwdAttemptsCountBuf, sizeof(maxPwdAttemptsCountBuf), SQL_C_LONG);
		usersResult -> Bind(10, emailBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(11, &emailLenBuf, sizeof(emailLenBuf), SQL_C_LONG);
		usersResult -> Bind(12, phoneBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(13, &phoneLenBuf, sizeof(phoneLenBuf), SQL_C_LONG);
		usersResult -> Bind(14, &emailPwdResetBuf, sizeof(emailPwdResetBuf), SQL_C_LONG);
		usersResult -> Bind(15, &smsPwdResetBuf, sizeof(smsPwdResetBuf), SQL_C_LONG);
		usersResult -> Bind(16, &pwdResetedFlagBuf, sizeof(pwdResetedFlagBuf), SQL_C_LONG);
		usersResult -> Bind(17, pwdResetDateBuf, STR_VALUE_LEN);
		usersResult -> Bind(18, &pwdResetPeriodBuf, sizeof(pwdResetPeriodBuf), SQL_C_LONG);
		usersResult -> Bind(19, &lockedBuf, sizeof(lockedBuf), SQL_C_LONG);
		usersResult -> Bind(20, &pwdTypeBuf, sizeof(pwdTypeBuf), SQL_C_LONG);
		
		// Retrieve record
		if (usersResult -> MoveFirst())
		{
			user -> userID = userID;

			user -> encNameLen = nameLenBuf;
			if (nameLenBuf > ENCRYPTED_DATA_SIZE)
				memcpy(user -> encName, nameBuf, ENCRYPTED_DATA_SIZE);
			else
				memcpy(user -> encName, nameBuf, nameLenBuf);
			
			user -> encUserNameLen = userNameLenBuf;
			if (userNameLenBuf > ENCRYPTED_DATA_SIZE)
				memcpy(user -> encUserName, userNameBuf, ENCRYPTED_DATA_SIZE);
			else
				memcpy(user -> encUserName, userNameBuf, userNameLenBuf);

			user -> encEmailAddressLen = emailLenBuf;
			if (emailLenBuf > ENCRYPTED_DATA_SIZE)
				memcpy(user -> encEmailAddress, emailBuf, ENCRYPTED_DATA_SIZE);
			else
				memcpy(user -> encEmailAddress, emailBuf, emailLenBuf);

			user -> encPhoneNumberLen = phoneLenBuf;
			if (phoneLenBuf > ENCRYPTED_DATA_SIZE)
				memcpy(user -> encPhoneNumber, phoneBuf, ENCRYPTED_DATA_SIZE);
			else
				memcpy(user -> encPhoneNumber, phoneBuf, phoneLenBuf);
				
			user -> needStudy = (studyFlagBuf == 0) ? false : true;
			user -> randomEduCateg = (rndCategBuf == 0) ? false : true;
			user -> pwdAttemptsCount = pwdAttemptsCountBuf;
			user -> pwdType = pwdTypeBuf;

			strcpy(user -> lastLogOnDate, signInDateBuf);

			if (maxPwdAttemptsCountBuf > 0)
				user -> maxPwdAttemptsCount = maxPwdAttemptsCountBuf;
			else
				user -> maxPwdAttemptsCount = 20;

			user -> emailPwdReset = (emailPwdResetBuf == 0) ? false : true;
			user -> smsPwdReset = (smsPwdResetBuf == 0) ? false : true;
			user -> pwdReseted = (pwdResetedFlagBuf == 0) ? false : true;
			user -> pwdResetPeriod = pwdResetPeriodBuf;
			user -> locked = (lockedBuf == 0) ? false : true;
			
			if (user -> pwdReseted)
				strcpy(user -> pwdResetDate, pwdResetDateBuf);
			else
				strcpy(user -> pwdResetDate, "");

			user -> eduCategotyID = -1;
			user -> eduQuestionRandom = false;

			delete usersResult;
		}
		else
		{
			user = RemoveUserDescriptor(user);
			delete usersResult;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserDescriptor. Wrong user ID!");
				WriteToLog("ContentManager : GetUserDescriptor. Done");
			#endif

			return user;
		}
			
		// Get education info
		if(!GetUserEducationValues(user))
			user -> needStudy = false;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserDescriptor. Done");
		#endif

		return user;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return RemoveUserDescriptor(user);
	}
}

/****************************************************************

   Class : ContentManager

   Method : GetUserDescriptor
   
   Parameters :
			Input : 
				userName - user name

   Return : pointer to user descriptor
	
   Description :  Get user descriptor by user name

*****************************************************************/
PUSER_DESCRIPTOR ContentManager :: GetUserDescriptor(char * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserDescriptor. Start");
	#endif
	
	int userID = GetUserID(userName);
	PUSER_DESCRIPTOR user = NULL;

	if (userID != -1)
		user = GetUserDescriptor(userID);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserDescriptor. Done");
	#endif

	return user;
}

/****************************************************************

   Class : ContentManager

   Method : GetUserDescriptor
   
   Parameters :
			Input : 
				userName - encrypted user name
				userNameLen - length of encrypted user name

   Return : pointer to user descriptor
	
   Description :  Get user descriptor by encrypted user name

*****************************************************************/
PUSER_DESCRIPTOR ContentManager :: GetUserDescriptor(unsigned char * userName, int userNameLen)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserDescriptor. Start");
	#endif
	
	int userID = GetUserID(userName, userNameLen);
	PUSER_DESCRIPTOR user = NULL;

	if (userID != -1)
		user = GetUserDescriptor(userID);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserDescriptor. Done");
	#endif

	return user;
}

/****************************************************************

   Class : ContentManager

   Method : GetUserDescriptor
   
   Parameters :
			Input : 
				userName -  user name
				authSystemID - authentication system type 

   Return : pointer to user descriptor
	
   Description :  Get user descriptor by system user name

*****************************************************************/
PUSER_DESCRIPTOR ContentManager :: GetUserDescriptor(char * userName, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserDescriptor. Start");
	#endif

	// User ID
	int userID = -1;

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT UserAccounts.UserID, UserAccounts.UserName, DATALENGTH(UserAccounts.UserName) FROM UserAccounts WHERE (UserAccounts.AuthSystemID = %d)", authSystemID);
		
		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		int userIDBuf = userID;
		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;

		// Bind data
		usersResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);
		usersResult -> Bind(2, userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(3, &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);

		// Retrieve record
		while (usersResult -> MoveNext())
		{
			unsigned char decryptedUserName[NAME_LEN];
			int decryptedUserNameLen;

			if (encryptor -> UnPackAndDecryptSecurityData(userNameBuf, userNameLenBuf, decryptedUserName, NAME_LEN, &decryptedUserNameLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserDescriptor. Can't decrypt user name!");
				#endif
			}
			else
			{
				decryptedUserName[decryptedUserNameLen] = 0;
				if (strcmp(userName, (char *)decryptedUserName) == 0)
				{
					userID = userIDBuf;
					break;
				}
			}

			userIDBuf = -1;
			userNameBuf[0] = 0;
			userNameLenBuf = 0;
		}

		delete usersResult;

		PUSER_DESCRIPTOR user = GetUserDescriptor(userID);
				
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserID. Done");
		#endif

		return user;
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

   Class : ContentManager

   Method : GetUserDescriptor
   
   Parameters :
			Input : 
				encUserName -  encrypted user name
				encUserNameLen -  encrypted user name length
				authSystemID - authentication system type 

   Return : pointer to user descriptor
	
   Description :  Get user descriptor by system user name

*****************************************************************/
PUSER_DESCRIPTOR ContentManager :: GetUserDescriptor(unsigned char * encUserName, int encUserNameLen, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserDescriptor. Start");
	#endif

	unsigned char decryptedUserName[NAME_LEN];
	int decryptedUserNameLen;
	
	if (encryptor -> UnPackAndDecryptSecurityData(encUserName, encUserNameLen, decryptedUserName, NAME_LEN, &decryptedUserNameLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserDescriptor. Can't decrypt user name!");
			WriteToLog("ContentManager : GetUserDescriptor. Done");
		#endif

		return NULL;
	}
	else
		decryptedUserName[decryptedUserNameLen] = 0;

	PUSER_DESCRIPTOR user = GetUserDescriptor((char *)decryptedUserName, authSystemID);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserID. Done");
	#endif

	return user;
}

#pragma endregion

#pragma region User list

/****************************************************************

   Class : ContentManager

   Method : CreateSimpleUserDescriptor

   Return : pointer to simple user descriptor
	
   Description :  Create simple user descriptor

*****************************************************************/
PSIMPLE_USER_DESCRIPTOR ContentManager :: CreateSimpleUserDescriptor(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CreateSimpleUserDescriptor. Start");
	#endif
	
	PSIMPLE_USER_DESCRIPTOR user = (PSIMPLE_USER_DESCRIPTOR)malloc(sizeof(SIMPLE_USER_DESCRIPTOR));

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)

		if (user)
			WriteToLog("ContentManager : CreateSimpleUserDescriptor. Success");
		else
			WriteToLog("ContentManager : CreateSimpleUserDescriptor. Error of memory allocation!");

		WriteToLog("ContentManager : CreateSimpleUserDescriptor. Done");

	#endif

	return user;
}

/****************************************************************

   Class : ContentManager

   Method : RemoveSimpleUserDescriptor

   Parameters:
			Input:
				user - pointer to simple user descriptor

   Return : pointer to simple user descriptor
	
   Description :  Remove simple user descriptor

*****************************************************************/
PSIMPLE_USER_DESCRIPTOR ContentManager :: RemoveSimpleUserDescriptor(PSIMPLE_USER_DESCRIPTOR user)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : RemoveSimpleUserDescriptor");
	#endif

	if (user)
	{
		free(user);
		user = NULL;
	}

	return user;
}

/****************************************************************

   Class : ContentManager

   Method : ClearUserList

   Parameters :
			Input : 
					userList - pointer to user list structure

   Return : if list is cleared then returns NULL
	
	Description :  Clear of list of users

*****************************************************************/
PUSER_LIST ContentManager :: ClearUserList(PUSER_LIST userList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : ClearUserList");
	#endif

	// Validate user list pointer
	if (userList)
	{
		// Free user list items
		for(int i = 0 ; i < userList -> usersCount; i++)
		{
			if (userList -> users[i])
				userList -> users[i] = RemoveSimpleUserDescriptor(userList -> users[i]);
		}

		// Free user list
		free(userList);

		userList = NULL;
	}

	return userList;
}

/****************************************************************

   Class : ContentManager

   Method : CreateUserList

   Return : pointer to list of users
	
	Description :  Allocate memory for list of users

*****************************************************************/
PUSER_LIST ContentManager :: CreateUserList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CreateUserList. Start");
	#endif
			
	// Allocate memory to user container
	PUSER_LIST userList = (PUSER_LIST)malloc(sizeof(USER_LIST));

	if (userList)
	{
		// Set default values
		userList -> usersCount = 0;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CreateUserList. Success!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
	
		else
			WriteToLog("ContentManager : CreateUserList. Error!");

		WriteToLog("ContentManager : CreateUserList. Done");

	#endif

	return userList;
}



/****************************************************************

   Class : ContentManager

   Method : GetUserList
   
   Return : pointer to list of users
	
   Description :  Get list of users

*****************************************************************/
PUSER_LIST ContentManager :: GetUserList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserList. Start");
	#endif

	// Create user list
	PUSER_LIST userList = CreateUserList();

	// Validate pointer
	if(!userList)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserList. User list was not created");
			WriteToLog("ContentManager : GetUserList. Done");
		#endif

		return userList;
	}

	try
	{
		// Get users list
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT Users.ID,\
								Users.UserName,\
								DATALENGTH(Users.UserName)\
					  FROM Users");
		
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		int userIDBuf = 0;
		unsigned char userNameBuf[ENCRYPTED_DATA_SIZE];
		int userNameLenBuf = 0;
		
		// Bind data
		usersResult -> Bind(1,  &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);
		usersResult -> Bind(2,  userNameBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		usersResult -> Bind(3,  &userNameLenBuf, sizeof(userNameLenBuf), SQL_C_LONG);

		// Retrieve records
		while(usersResult -> MoveNext())
		{
			// Allocate memory
			userList -> users[userList -> usersCount] = CreateSimpleUserDescriptor();

			// Validate allocation result
			if(!userList -> users[userList -> usersCount])
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserList. Error list item memory allocation!");
					WriteToLog("ContentManager : GetUserList. Done.");
				#endif

				return ClearUserList(userList);
			}

			// Get values
			userList -> users[userList -> usersCount] -> userID = userIDBuf;
			userList -> users[userList -> usersCount] -> encUserNameLen = userNameLenBuf;
			memcpy(userList -> users[userList -> usersCount] -> encUserName, userNameBuf, userNameLenBuf);

			userList -> usersCount++;

			if (userList -> usersCount >= MAX_USERS_COUNT)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserList. User list overflow!");
				#endif

				break;
			}

			// Clear buffers
			userIDBuf = 0;
			userNameLenBuf = 0;
		    userNameBuf[0] = 0;
		}

		delete usersResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserList. Done");
		#endif

		return userList;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return ClearUserList(userList);
	}
}

#pragma endregion

#pragma region Content

/****************************************************************

   Class : ContentManager

   Method : CreateContent

   Return : pointer to user content container
	
	Description :  Allocate memory for user content container

*****************************************************************/
PPRESET_CONTAINER ContentManager :: CreateContent(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : CreateContent. Start");
	#endif
	
	// Allocate memory to user container
	PPRESET_CONTAINER content = (PPRESET_CONTAINER)malloc(sizeof(PRESET_CONTAINER));

	if (content)
	{
		// Set default values
		content -> presetID = -1;
		content -> userScreensCount = 0;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : CreateContent. Success!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		else
			WriteToLog("ContentManager : CreateContent. Error!");

		WriteToLog("ContentManager : CreateContent. Done");
	#endif

	return content;
}

/****************************************************************

   Class : ContentManager

   Method : ClearContent
   
   Parameters :
			Input : 
				content - pointer to content structure
   
   Return : if container is cleared then returns NULL
	
   Description :  Clear of container of content

*****************************************************************/
PPRESET_CONTAINER ContentManager :: ClearContent(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : ClearContent. Start");
	#endif

	// Validate container pointer
	if (content)
	{
		// Free user screens list
		for(int i = 0 ; i < content -> userScreensCount; i++)
			content -> userScreens[i] = ClearUserScreen(content ->userScreens[i]);

		// Free container
		free(content);

		content = NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : ClearContent. Done");
	#endif

	return content;
}

/****************************************************************

   Class : ContentManager

   Method : ClearUserScreen
   
   Parameters :
			Input : 
					userScreen - pointer to user screen structure

   Return : if screen is cleared then returns NULL
	
   Description :  Clear of user screen content

*****************************************************************/
PUSER_SCREEN ContentManager :: ClearUserScreen(PUSER_SCREEN userScreen)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : ClearUserScreen. Start");
	#endif

	// Validate pointer
	if (userScreen)
	{
		// Free screen objects
		for(int j = 0; j < userScreen -> scrObjCount; j++)
			userScreen -> screenObjects[j] = ClearUserScreenObject(userScreen -> screenObjects[j]);
			
		// Free user screen
		free(userScreen);
		
		userScreen = NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : ClearUserScreen. Done");
	#endif

	return userScreen;
}

/****************************************************************

   Class : ContentManager

   Method : FindUserScreen

   Parameters :
			Input : 
			    content - pointer to content structure
				screenType - type of user screen

   Return : user screen index
	
	Description :  Find user screen by type

*****************************************************************/
int ContentManager :: FindUserScreen(PPRESET_CONTAINER content, int screenType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : FindUserScreen");
	#endif

	int screenInd = -1;

	if (content)
	{
		for(int i = 0; i < content -> userScreensCount; i++)
			if (content -> userScreens[i] -> screenTypeID == screenType)
			{
				screenInd = i;
				break;
			}
	}

	return screenInd;
}

/****************************************************************

   Class : ContentManager

   Method : DeleteUserScreen

   Parameters :
			Input : 
			    content - pointer to content structure
				userScreen - user screen instance

	Description :  Delete user screen

*****************************************************************/
void ContentManager :: DeleteUserScreen(PPRESET_CONTAINER content, PUSER_SCREEN userScreen)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteUserScreen. Start");
	#endif

	if(content)
	{
		for(int i = 0; i < content -> userScreensCount; i++)
			if ((content -> userScreens[i]) && (content -> userScreens[i] == userScreen))
			{
				DeleteUserScreenByInd(content, i);
				break;
			}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteUserScreen. Done");
	#endif
}

/****************************************************************

   Class : ContentManager

   Method : DeleteUserScreenByType

   Parameters :
			Input : 
				content - pointer to content structure
				screenType - type of user screen
				
	Description :  Delete user screen by type

*****************************************************************/
void ContentManager :: DeleteUserScreenByType(PPRESET_CONTAINER content, int screenType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteUserScreenByType. Start");
	#endif
	
	if (content)
	{
		int screenInd = FindUserScreen(content, screenType);

		if (screenInd != -1)
			DeleteUserScreenByInd(content, screenInd);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteUserScreenByType. Done");
	#endif
}

/****************************************************************

   Class : ContentManager

   Method : DeleteUserScreenByInd

   Parameters :
			Input : 
				content - pointer to content structure
				screenInd - index of user screen

	Description :  Delete user screen by index

*****************************************************************/
void ContentManager :: DeleteUserScreenByInd(PPRESET_CONTAINER content, int screenInd)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteUserScreenByInd. Start");
	#endif

	if ((content) && (screenInd >= 0) && (screenInd < content -> userScreensCount))
	{
		content -> userScreens[screenInd] = ClearUserScreen(content -> userScreens[screenInd]);
		
		for(int i = screenInd; i < content -> userScreensCount - 1; i++)
		   content -> userScreens[i] = content -> userScreens[i + 1];
		
		content -> userScreens[content -> userScreensCount - 1] = NULL;
		content -> userScreensCount--;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteUserScreenByInd. Done");
	#endif
}

/****************************************************************

   Class : ContentManager

   Method : ClearUserScreenObject

   Parameters :
			Input : 
				scrObject - pointer to screen object structure

   Return : if screen object is cleared then returns NULL
	
   Description :  Clear of user screen object  content

*****************************************************************/
PSCREEN_OBJECT ContentManager :: ClearUserScreenObject(PSCREEN_OBJECT scrObject)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : ClearUserScreenObject");
	#endif

	if (scrObject)
	{
		// Free screen object list values
		if (scrObject -> listValuesSet) 
			free(scrObject -> listValuesSet);

		// Free screen object text value
		if (scrObject -> textValue) 
			free(scrObject -> textValue);

		// Free screen object image value
		if (scrObject -> imgValue) 
			free(scrObject -> imgValue);

		// Free screen object
		free(scrObject);

		scrObject = NULL;
	}

	return scrObject;
}

/****************************************************************

   Class : ContentManager

   Method : FindScreenObject

   Parameters :
			Input : 
				userScreen - pointer to user screen
				objectType - object type

   Return : user screen object index
	
	Description :  Find user screen object by type

*****************************************************************/
int ContentManager :: FindScreenObject(PUSER_SCREEN userScreen, int objectType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : FindScreenObject");
	#endif

	int objInd = -1;

	if (userScreen)
	{
		for(int i = 0; i < userScreen -> scrObjCount; i++)
			if (userScreen -> screenObjects[i] -> objTypeId == objectType)
			{
				objInd = i;
				break;
			}
	}

	return objInd;
}

/****************************************************************

   Class : ContentManager

   Method : DeleteScreenObject

   Parameters :
			Input : 
			    content - pointer to content structure
				screenObject - pointer to user screen object instance

   Description :  Delete user screen object

*****************************************************************/
void ContentManager :: DeleteScreenObject(PPRESET_CONTAINER content, PSCREEN_OBJECT screenObject)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteScreenObjectByType. Start");
	#endif

	if (content)
	{
		for(int i = 0; i < content -> userScreensCount; i++)
			if(content -> userScreens[i])
				for(int j = 0; j < content -> userScreens[i] -> scrObjCount; j++)
					if ((content -> userScreens[i] -> screenObjects[j]) &&
						(content -> userScreens[i] -> screenObjects[j] == screenObject))
					{
						DeleteScreenObjectByInd(content -> userScreens[i], j);
						break;
					}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteScreenObjectByType. Done");
	#endif
}

/****************************************************************

   Class : ContentManager

   Method : DeleteScreenObjectByType

   Parameters :
			Input : 
				userScreen - pointer to user screen
				objectType - object type

   Description :  Delete user screen object by type

*****************************************************************/
void ContentManager :: DeleteScreenObjectByType(PUSER_SCREEN userScreen, int objectType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteScreenObjectByType. Start");
	#endif

	if (userScreen)
	{
		int objectInd = FindScreenObject(userScreen, objectType);

		if (objectInd != -1)
			DeleteScreenObjectByInd(userScreen, objectInd);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteScreenObjectByType. Done");
	#endif
}

/****************************************************************

   Class : ContentManager

   Method : DeleteScreenObjectByInd

   Parameters :
			Input : 
				userScreen - pointer to user screen
				objectInd - object index

   Description :  Delete user screen object by index

*****************************************************************/
void ContentManager :: DeleteScreenObjectByInd(PUSER_SCREEN userScreen, int objectInd)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteScreenObjectByInd");
	#endif

	if ((userScreen) && (objectInd >= 0) && (objectInd < userScreen -> scrObjCount))
	{
		userScreen -> screenObjects[objectInd] = ClearUserScreenObject(userScreen -> screenObjects[objectInd]);
		
		for(int i = objectInd; i < userScreen -> scrObjCount - 1; i++)
		   userScreen -> screenObjects[i] = userScreen -> screenObjects[i + 1];
		
		userScreen -> screenObjects[userScreen -> scrObjCount - 1] = NULL;
		userScreen -> scrObjCount--;
	}
}

/****************************************************************

   Class : ContentManager

   Method : GetUserContent

   Parameters :
			Input : 
				compName - computer name
				userID - user ID
				osID - OS ID
				eduFunc - education functuonallity flag
				snFunc - notification functuonallity flag
				ldFunc - legal disclaimer functuonallity flag

   Return : pointer to user content container
	
   Description :  Get user content from database

*****************************************************************/
PPRESET_CONTAINER ContentManager :: GetUserContent(char * compName, int userID, int osID, bool eduFunc, bool snFunc, bool ldFunc)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserContent. Start");
	#endif

	// Allocate memory to user container
	PPRESET_CONTAINER content = CreateContent();

	if (!content)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserContent. User content was not created!");
			WriteToLog("ContentManager : GetUserContent. Done");
		#endif

		return content;
	}

	try
	{
		// Get user preset
		if (!GetPreset(content, compName, userID, osID)) 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
				WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get preset!");
				WriteToLog("ContentManager : GetUserContent. Done.");
			#endif

			return ClearContent(content);
		}

		// Get user screens list
		if (!GetUserScreens(content)) 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
				WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get user screens!");
				WriteToLog("ContentManager : GetUserContent. Done.");
			#endif

			return ClearContent(content);
		}
		
		for(int i = 0; (i < content -> userScreensCount) && (i < MAX_SCREEN_COUNT); i++)
		{
			// Get objects for each screen
			if (!GetUserScreenObjects(content, i))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
					WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get user screen objects!");
					WriteToLog("ContentManager : GetUserContent. Done.");
				#endif
		
				return ClearContent(content);
			}
		}

		// Get drop down list values
		if (!GetListValuesSet(content))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
				WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get user list values!");
				WriteToLog("ContentManager : GetUserContent. Done.");
			#endif

			return ClearContent(content);
		}

		// Create scheduler instance
		Scheduler * scheduler = new Scheduler(zContentDllDefinition.dllID, logWriter, dbManager);

		if ((eduFunc) && (!((scheduler -> VerifyScheduleRecords(userID, compName, EDUCATION_FUNCTION) & DENY_ACTION) == DENY_ACTION)))
		{
			// Get values for questions
			if(!GetEducationValues(content, userID))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
					WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get education values!");
					WriteToLog("ContentManager : GetUserContent. Done.");
				#endif

				return ClearContent(content);
			}
		}
		else
			DeleteEducationScreenObjects(content);

		if ((snFunc) && (!((scheduler -> VerifyScheduleRecords(userID, compName, NOTIFICATION_FUNCTION) & DENY_ACTION) == DENY_ACTION)))
		{
			// Get values for user notices
			if(!GetUserNotificationValues(content, userID))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
					WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get user notification values!");
					WriteToLog("ContentManager : GetUserContent. Done.");
				#endif
		
				return ClearContent(content);
			}
		}
		else
			DeleteSimpleNoticesScreenObjects(content);

		if ((ldFunc) && (!((scheduler -> VerifyScheduleRecords(userID, compName, LEGAL_DISCLAIMER_FUNCTION) & DENY_ACTION) == DENY_ACTION)))
		{
			// Get values for legal disclaimer
			if(!GetLegalDisclaimerValues(content, userID))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
					WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get legal disclaimer values!");
					WriteToLog("ContentManager : GetUserContent. Done.");
				#endif

				return ClearContent(content);
			}
		}
		else
			DeleteLegalDisclaimerScreenObjects(content);

		// Delete scheduler instance
		delete scheduler;


		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
			WriteToLog("ContentManager : GetUserContent. Done");
		#endif

		return content;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return ClearContent(content);
	}
}


/****************************************************************

   Class : ContentManager

   Method : GetDefaultContent

   Return : pointer to user content container
	
	Description :  Get default user content from database

*****************************************************************/
PPRESET_CONTAINER ContentManager :: GetDefaultContent(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserContent. Start");
	#endif

	// Allocate memory to user container
	PPRESET_CONTAINER content = CreateContent();

	if (!content)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserContent. User content was not created!");
			WriteToLog("ContentManager : GetUserContent. Done");
		#endif

		return content;
	}

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user preset
		if (!GetPreset(content, "", -1, -1)) 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
				WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get preset!");
				WriteToLog("ContentManager : GetUserContent. Done.");
			#endif
			
			return ClearContent(content);
		}

		// Get user screens list
		if (!GetUserScreens(content)) 
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
				WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get user screens!");
				WriteToLog("ContentManager : GetUserContent. Done.");
			#endif
			
			return ClearContent(content);
		}

		// Remove sub windows
		int mainScreenInd = -1;
		for(int i = content -> userScreensCount - 1; i >= 0; i--)
		{
			mainScreenInd = FindUserScreen(content, SOT_MAIN_SCREEN);
			if ((mainScreenInd != -1) && (i != mainScreenInd))
				DeleteUserScreenByInd(content, i);
		} 
				
		if (!GetUserScreenObjects(content, mainScreenInd))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
				WriteToLog("ContentManager : GetUserContent. Content was not created. Can't get user screen objects!");
				WriteToLog("ContentManager : GetUserContent. Done.");
			#endif

			return ClearContent(content);
		}

		PUSER_SCREEN mainScreen = content -> userScreens[mainScreenInd];

		// Remove excess objects
		for(int i = mainScreen -> scrObjCount - 1; i >= 0; i--)
		{
			if (!((mainScreen -> screenObjects[i] -> objTypeId == SOT_IMAGE) ||
				(mainScreen -> screenObjects[i] -> objTypeId == SOT_BUTTON) ||
				(mainScreen -> screenObjects[i] -> objTypeId == SOT_USER_NAME_BOX) ||
				(mainScreen -> screenObjects[i] -> objTypeId == SOT_DOMAIN_NAME_BOX) ||
				(mainScreen -> screenObjects[i] -> objTypeId == SOT_PASSWORD_BOX) ||
				(mainScreen -> screenObjects[i] -> objTypeId == SOT_PASSWORD_RESET_BUTTON) ||
				(mainScreen -> screenObjects[i] -> objTypeId == SOT_DATE_TIME_TEXT)))
					DeleteScreenObjectByInd(mainScreen, i);
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)	
			WriteToLog("ContentManager : GetUserContent. Done");
		#endif

		return content;
	}
	catch(DBException & ex)
	{
		// Error processing
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);
		return ClearContent(content);
	}
}

/****************************************************************

   Class : ContentManager

   Method : GetPreset

   Parameters :
			Input : 
			    content - pointer to user content structure
				compName - computer name
				userID - user ID
				osID - OS ID

   Return : TRUE if success, FALSE if fail
	
	Description :  Retrieve from database preset information
				   for this computer

*****************************************************************/
bool ContentManager :: GetPreset(PPRESET_CONTAINER content, char * compName, int userID, int osID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetPreset. Start");

		char message[128];
		sprintf(message, "ContentManager : GetPreset. Computer name = %s, User ID = %d, OS ID = %d", compName, userID, osID);
		WriteToLog(message);
	#endif
		
	// Check DLL legal user
	dbManager += dllUserCheckResult;

	// Validate database and container
	if ((content == NULL) || (!(dbManager -> Opened())))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetPreset. Error of GetPreset using!");
			WriteToLog("ContentManager : GetPreset. Done");
		#endif

		return false;
	}

	try
	{
		// SQL queries list
		char queries[16][SQL_SIZE] = 
		{
		 // Full hookup (1)
		 "SELECT PresetHookup.PresetID\
		  FROM PresetHookup\
		  WHERE((PresetHookup.ComputerID = (SELECT TOP 1 Computers.ID\
		                                    FROM Computers\
		                                    WHERE(Computers.Name = '%s'))) AND \
		        (PresetHookup.OSTypeID = %d) AND\
		        (PresetHookup.UserID = %d) AND\
		        (PresetHookup.GroupID in (SELECT UserGroupUsers.GroupID\
		                                  FROM UserGroupUsers\
		                                  WHERE (UserGroupUsers.UserID = %d))))", 

		 // Computer + OS + User (2)
		 "SELECT PresetHookup.PresetID\
		  FROM PresetHookup\
		  WHERE((PresetHookup.ComputerID = (SELECT TOP 1 Computers.ID\
		                                    FROM Computers\
		                                    WHERE(Computers.Name = '%s'))) AND \
		        (PresetHookup.OSTypeID = %d) AND\
		        (PresetHookup.UserID = %d) AND\
		        (PresetHookup.GroupID is NULL /*%d*/))", 

		  // User + OS + Group (3)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID is NULL) /*%s*/ AND \
				  (PresetHookup.OSTypeID = %d) AND\
				  (PresetHookup.UserID = %d) AND \
				  (PresetHookup.GroupID in (SELECT UserGroupUsers.GroupID\
				                            FROM UserGroupUsers\
				                            WHERE (UserGroupUsers.UserID = %d))))", 

		  // Computer + User + Group (4)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID = (SELECT TOP 1 Computers.ID\
											  FROM Computers\
											  WHERE (Computers.Name = '%s'))) AND \
				  (PresetHookup.OSTypeID is NULL) /*%d*/ AND\
				  (PresetHookup.UserID = %d) AND\
				  (PresetHookup.GroupID in (SELECT UserGroupUsers.GroupID\
				                            FROM UserGroupUsers\
				                            WHERE(UserGroupUsers.UserID = %d))))", 

		  // OS + Computer + Group (5)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID = (SELECT TOP 1 Computers.ID\
								  FROM Computers\
								  WHERE (Computers.Name = '%s'))) AND \
				                        (PresetHookup.OSTypeID = %d) AND \
				                        (PresetHookup.UserID is NULL) /*%d*/ AND \
										(PresetHookup.GroupID in (SELECT UserGroupUsers.GroupID\
										                          FROM UserGroupUsers\
										                          WHERE(UserGroupUsers.UserID = %d))))",

		  // User + Group (6)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID is NULL) /*%s*/ AND \
				  (PresetHookup.OSTypeID is NULL) /*%d*/ AND\
				  (PresetHookup.UserID = %d) AND \
				  (PresetHookup.GroupID in (SELECT UserGroupUsers.GroupID\
				                            FROM UserGroupUsers\
				                            WHERE(UserGroupUsers.UserID = %d))))",

		  // OS + Group (7)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID is NULL) /*%s*/AND \
				  (PresetHookup.OSTypeID = %d) AND\
				  (PresetHookup.UserID is NULL) /*%d*/ AND \
				  (PresetHookup.GroupID in (SELECT UserGroupUsers.GroupID\
										    FROM UserGroupUsers\
				                            WHERE(UserGroupUsers.UserID = %d))))",

		  // Computer + Group (8)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID = (SELECT TOP 1 Computers.ID\
								              FROM Computers\
								              WHERE (Computers.Name = '%s'))) AND \
				  (PresetHookup.OSTypeID is NULL) /*%d*/ AND\
				  (PresetHookup.UserID is NULL) /*%d*/  AND \
				  (PresetHookup.GroupID in (SELECT UserGroupUsers.GroupID\
					     				    FROM UserGroupUsers\
				                            WHERE(UserGroupUsers.UserID = %d))))",

		  // User + OS (9)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID is NULL) /*%s*/ AND \
				  (PresetHookup.OSTypeID = %d) AND\
				  (PresetHookup.UserID = %d) AND \
				  (PresetHookup.GroupID is NULL /*%d*/))", 

		  // Computer + User (10)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID = (SELECT TOP 1 Computers.ID\
											  FROM Computers\
											  WHERE (Computers.Name = '%s'))) AND \
				  (PresetHookup.OSTypeID is NULL) /*%d*/ AND\
				  (PresetHookup.UserID = %d) AND\
				  (PresetHookup.GroupID is NULL /*%d*/))", 

		  // OS + Computer (11)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID = (SELECT TOP 1 Computers.ID\
								              FROM Computers\
								              WHERE (Computers.Name = '%s'))) AND \
				  (PresetHookup.OSTypeID = %d) AND \
				  (PresetHookup.UserID is NULL) /*%d*/ AND \
				  (PresetHookup.GroupID is NULL /*%d*/))",

		  // User (12)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID is NULL) /*%s*/ AND \
				  (PresetHookup.OSTypeID is NULL) /*%d*/ AND\
				  (PresetHookup.UserID = %d) AND \
				  (PresetHookup.GroupID is NULL /*%d*/))",

		  

		  // OS (13)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID is NULL) /*%s*/AND \
				  (PresetHookup.OSTypeID = %d) AND\
				  (PresetHookup.UserID is NULL) /*%d*/ AND \
				  (PresetHookup.GroupID is NULL /*%d*/))",

		  // Computer (14)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID = (SELECT TOP 1 Computers.ID\
								              FROM Computers\
								              WHERE (Computers.Name = '%s'))) AND \
				  (PresetHookup.OSTypeID is NULL) /*%d*/ AND\
				  (PresetHookup.UserID is NULL) /*%d*/  AND \
				  (PresetHookup.GroupID is NULL /*%d*/))",

		   // Group (15)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID is NULL) /*%s*/AND \
				  (PresetHookup.OSTypeID is NULL) /*%d*/AND\
				  (PresetHookup.UserID is NULL) /*%d*/ AND\
				  (PresetHookup.GroupID in (SELECT UserGroupUsers.GroupID\
					     				    FROM UserGroupUsers\
				                            WHERE(UserGroupUsers.UserID = %d))))",

		  // (ALL NULL) Default preset (16)
		  "SELECT PresetHookup.PresetID\
		   FROM PresetHookup\
		   WHERE ((PresetHookup.ComputerID is NULL) /*%s*/AND \
				  (PresetHookup.OSTypeID is NULL) /*%d*/AND\
				  (PresetHookup.UserID is NULL) /*%d*/ AND\
				  (PresetHookup.GroupID is NULL) /*%d*/)" 
		};

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetPreset. Trying get personal preset for current user");
		#endif


		bool presetFound = false;
		int presetIndex = -1;
		for(int i = 0; i < 16; i++)
		{
			// Prepare SQL query
			char sql[SQL_SIZE];
			sprintf(sql, queries[i], compName, osID, userID, userID);

			// Execute SQl query
			ResultSet * presetResult = dbManager -> ExecuteSelectQuery(sql);

			// Bind data
			presetResult -> Bind(1, &(content -> presetID), sizeof(content -> presetID), SQL_C_LONG);

			// Get preset ID
			if (presetResult -> MoveFirst())
			{
				presetFound = true;
				presetIndex = i;
				break;
			}

			delete presetResult;
		}
		
		// If preset was found
		if (presetFound)
		{
			// Get personal preset
			char sql[SQL_SIZE];
			sprintf(sql, "SELECT Name FROM Preset WHERE ID = %d", content -> presetID);
			
			// Execute SQl query
			ResultSet  * presetResult = dbManager -> ExecuteSelectQuery(sql);

			// Bind data
			presetResult -> Bind(1, content -> presetName, NAME_LEN);

			// Get personal preset
			if (presetResult -> MoveFirst())
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					switch (presetIndex)
					{
						case 0 :
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : Full hookup (1)");
								break;
							}

						case 1 :
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : Computer + OS + User (2)");
								break;
							}

						case 2 :
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : User + OS + Group (3)");
								break;
							}

						case 3 :
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : Computer + User + Group (4)");
								break;
							}

						case 4 :
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : OS + Computer + Group (5)");
								break;
							}

						case 5 :
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : User + Group (6)");
								break;
							}

						case 6 :
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : OS + Group (7)");
								break;
							}

						case 7 :
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : Computer + Group (8)");
								break;
							}

						case 8:
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : User + OS (9)");
								break;
							}

						case 9:
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : Computer + User (10)");
								break;
							}

						case 10:
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : OS + Computer (11)");
								break;
							}

						case 11:
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : User (12)");
								break;
							}

						case 12:
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : OS (13)");
								break;
							}

						case 13:
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : Computer (14)");
								break;
							}

						case 14:
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : Group (15)");
								break;
							}

						case 15:
							{
								WriteToLog("ContentManager : GetPreset. Retrieved : (ALL NULL) Default preset (16)");
								break;
							}
					}

					WriteToLog("ContentManager : GetPreset. Success!");
					WriteToLog("ContentManager : GetPreset. Done");
				#endif

				delete presetResult;

				return true;
			}
			else
			{
				delete presetResult;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetPreset. Can't get preset name!");
					WriteToLog("ContentManager : GetPreset. Done");
				#endif

				return false;
			}
		}
		else
		{
			WriteToLog("ContentManager --> No preset! Can not get preset! Please establish default preset!");

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetPreset. Done");
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

   Class : ContentManager

   Method : GetUserScreens

   Parameters:
			Input:
				content - pointer to content structure

   Return : TRUE if success, FALSE if fail
	
   Description :  Retrieve from database information 
				  about user screens

*****************************************************************/
bool ContentManager :: GetUserScreens(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserScreens. Start");
	#endif
		
	// Check DLL legal user
	dbManager += dllUserCheckResult;

	// Validate critical params
	if ((content == NULL) || (content -> presetID == -1) || (!(dbManager -> Opened())))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : Error of GetUserScreens using");
			WriteToLog("ContentManager : GetUserScreens. Done");
		#endif

		return false;
	}

	try
	{
		// Get user screens
		char sql[SQL_SIZE];
		sprintf(sql, "SELECT ScreenObjects.ID, \
								ScreenObjects.Name, \
								ScreenObjects.Caption, \
								ScreenObjects.TypeID, \
								PresetDetails.ScreenObjectScopeID, \
								ScreenObjects.LocationX, \
								ScreenObjects.LocationY, \
								ScreenObjects.LocationXPers, \
								ScreenObjects.LocationYPers, \
								ScreenObjects.WidthPix, \
								ScreenObjects.WidthPers, \
								ScreenObjects.HeightPix, \
								ScreenObjects.HeightPers, \
								ScreenObjects.BackGrColor \
						FROM PresetDetails, \
							 ScreenObjects \
						WHERE ((ScreenObjects.ID = PresetDetails.ScreenObjectID) and \
							   (PresetDetails.PresetID = %d) and \
							   (ScreenObjects.TypeID >=0) and \
								(ScreenObjects.TypeID <= 255))", content -> presetID);
		
		// Execute SQL query
		ResultSet * screenResult = dbManager -> ExecuteSelectQuery(sql);
		
		// Define buffers
		int idBuf = 0;
		char nameBuf[NAME_LEN] = "";
		char captionBuf[NAME_LEN] = "";
		int typeBuf = 0;
		int scopeBuf = 0;
		int locationXBuf = 0;
		int locationYBuf = 0;
		int locationXPersBuf = 0;
		int locationYPersBuf = 0;
		int WidthPixBuf = 0;
		int WidthPersBuf = 0;
		int HeightPixBuf = 0;
		int HeightPersBuf = 0;
		int colorBuf = 0;

		// Bind data
		screenResult -> Bind(1, &idBuf, sizeof(idBuf), SQL_C_LONG);
		screenResult -> Bind(2, nameBuf, NAME_LEN);
		screenResult -> Bind(3, captionBuf, NAME_LEN);
		screenResult -> Bind(4, &typeBuf, sizeof(typeBuf), SQL_C_LONG);
		screenResult -> Bind(5, &scopeBuf, sizeof(scopeBuf), SQL_C_LONG);
		screenResult -> Bind(6, &locationXBuf, sizeof(locationXBuf), SQL_C_LONG);
		screenResult -> Bind(7, &locationYBuf, sizeof(locationYBuf), SQL_C_LONG);
		screenResult -> Bind(8, &locationXPersBuf, sizeof(locationXPersBuf), SQL_C_LONG);
		screenResult -> Bind(9, &locationYPersBuf, sizeof(locationYPersBuf), SQL_C_LONG);
		screenResult -> Bind(10, &WidthPixBuf, sizeof(WidthPixBuf), SQL_C_LONG);
		screenResult -> Bind(11, &WidthPersBuf, sizeof(WidthPersBuf), SQL_C_LONG);
		screenResult -> Bind(12, &HeightPixBuf, sizeof(HeightPixBuf), SQL_C_LONG);
		screenResult -> Bind(13, &HeightPersBuf, sizeof(HeightPersBuf), SQL_C_LONG);
		screenResult -> Bind(14, &colorBuf, sizeof(colorBuf), SQL_C_LONG);

		// Main screen flag
		bool mainScreenFound = false;

		// Get user screens data
		while(screenResult -> MoveNext())
		{
			// Allocate memory for user screen
			content -> userScreens[content -> userScreensCount] = (PUSER_SCREEN)malloc(sizeof(USER_SCREEN));

			if (!content -> userScreens[content -> userScreensCount])
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserScreens. Error of user screen creation");
					WriteToLog("ContentManager : GetUserScreens. Done");
				#endif

				return false;
			}

			// Main screen can be just one
			if ((mainScreenFound) && (typeBuf == SOT_MAIN_SCREEN))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserScreens. Main screen duplicate. Skipped.");
				#endif
			}
			else
			{
				// Validate screen type
				if (typeBuf == SOT_MAIN_SCREEN) mainScreenFound = true;

				// Get user screen data
				content -> userScreens[content -> userScreensCount] -> screenID = idBuf;
				content -> userScreens[content -> userScreensCount] -> screenTypeID = typeBuf;
				content -> userScreens[content -> userScreensCount] -> screenScope = scopeBuf;
				content -> userScreens[content -> userScreensCount] -> locationX = locationXBuf;
				content -> userScreens[content -> userScreensCount] -> locationY = locationYBuf;
				content -> userScreens[content -> userScreensCount] -> locationXPers = locationXPersBuf;
				content -> userScreens[content -> userScreensCount] -> locationYPers = locationYPersBuf;
				content -> userScreens[content -> userScreensCount] -> widthPix = WidthPixBuf;
				content -> userScreens[content -> userScreensCount] -> widthPers = WidthPersBuf;
				content -> userScreens[content -> userScreensCount] -> heightPix = HeightPixBuf;
				content -> userScreens[content -> userScreensCount] -> heightPers = HeightPersBuf;
				content -> userScreens[content -> userScreensCount] -> color = colorBuf;
				strcpy(content -> userScreens[content -> userScreensCount] -> Name, nameBuf);
				strcpy(content -> userScreens[content -> userScreensCount] -> screenCaption, captionBuf);
				
				content -> userScreens[content -> userScreensCount] -> scrObjCount = 0;

				content -> userScreensCount++;

				if (content -> userScreensCount >= MAX_SCREEN_COUNT)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
						WriteToLog("ContentManager : GetUserScreens. List of screens overflow!");
					#endif

					break;
				}

				// Clear buffers
				idBuf = 0;
				typeBuf = 0;
				scopeBuf = 0;
				locationXBuf = 0;
				locationYBuf = 0;
				locationXPersBuf = 0;
				locationYPersBuf = 0;
				WidthPixBuf = 0;
				WidthPersBuf = 0;
				HeightPixBuf = 0;
				HeightPersBuf = 0;
				colorBuf = 0;
				nameBuf[0] = 0;
				captionBuf[0] = 0;
			}
		}

		delete screenResult;

		// Validate main screen flag
		if (!mainScreenFound)
		{
			WriteToLog("ContentManager : Get user screens --> Main screen not found!");

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserScreens. Done");
			#endif

			return false;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			char msg[NAME_LEN];
			sprintf(msg, "ContentManager : GetUserScreens. Total screens count: %d", content -> userScreensCount);
			WriteToLog(msg);
			WriteToLog("ContentManager : GetUserScreens. Done.");
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

   Class : ContentManager

   Method : GetUserScreenObjects

   Parameters :
			Input : 
			    content - pointer to content structure
				screenInd - index of user screen

   Return : TRUE if success, FALSE if fail
	
	Description :  Retrieve from database preset information
				   for this computer

*****************************************************************/
bool ContentManager :: GetUserScreenObjects(PPRESET_CONTAINER content, int screenInd)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserScreenObjects. Start");
	#endif
		
	// Check DLL legal user
	dbManager += dllUserCheckResult;

	// Validate critical parameters
	if ((content == NULL) || (content -> presetID == -1) || (!(dbManager -> Opened())))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : Error of GetUserScreenObjects using");
			WriteToLog("ContentManager : GetUserScreenObjects. Done");
		#endif

		return false;
	}

	// Validate screen index
	if ((screenInd < 0) || (screenInd >= content -> userScreensCount))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserScreenObjects. Error! Incorrect screen index");
			WriteToLog("ContentManager : GetUserScreenObjects. Done");
		#endif

		return false;
	}

	try
	{
		// Prepare SQL query
		char sql[SQL_SIZE * 2];
		sprintf(sql, "SELECT ScreenObjects.ID, \
								ScreenObjects.Name, \
								ScreenObjects.Caption, \
								ScreenObjects.TypeID, \
								PresetDetails.ScreenObjectScopeID, \
								ScreenObjects.LocationX, \
								ScreenObjects.LocationY, \
								ScreenObjects.LocationXPers, \
								ScreenObjects.LocationYPers, \
								ScreenObjects.WidthPix, \
								ScreenObjects.WidthPers, \
								ScreenObjects.HeightPix, \
								ScreenObjects.HeightPers, \
								ScreenObjects.FontSize, \
								ScreenObjects.TextColor, \
								ScreenObjects.BackGrColor, \
								ScreenObjects.StrValue, \
								ScreenObjects.ImgValue, \
								DATALENGTH(ScreenObjects.ImgValue), \
								ScreenObjects.TextValue, \
								DATALENGTH(ScreenObjects.TextValue), \
								PresetDetails.ScreenObjectOrder \
					FROM ScreenObjects, PresetDetails \
					WHERE ((PresetDetails.PresetID = %d) and \
							(PresetDetails.ScreenObjectID = ScreenObjects.ID) and \
							(ScreenObjects.ParentID = %d) and \
							(ScreenObjects.TypeID >= 256) and \
							(ScreenObjects.TypeID <= 511)) \
					ORDER BY PresetDetails.ScreenObjectOrder" , content -> presetID, content -> userScreens[screenInd] -> screenID);
			
		// Execute SQL query
		ResultSet * screenResult = dbManager -> ExecuteSelectQuery(sql);

		// Prepare buffers
		int idBuf = 0;
		char nameBuf[NAME_LEN] = "";
		char captionBuf[NAME_LEN] = "";
		int typeBuf = 0;
		int scopeBuf = 0;
		int locationXBuf = 0;
		int locationYBuf = 0;
		int locationXPersBuf = 0;
		int locationYPersBuf = 0;
		int WidthPixBuf = 0;
		int WidthPersBuf = 0;
		int HeightPixBuf = 0;
		int HeightPersBuf = 0;
		int fontSizeBuf = 0;
		int textColorBuf = 0;
		int bckGrndColorBuf = 0;
		char strValueBuf[STR_VALUE_LEN] = "";
		void * imgValueBuf = malloc(BLOB_VALUE_LEN);
		char * textValueBuf = (char *)malloc(BLOB_VALUE_LEN);
		int imgValueSize = 0;
		int textValueSize = 0;
		int orderBuf = 0;

		// Check allocation memory errors
		if ((!imgValueBuf) || (!textValueBuf))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserScreenObjects. Error of buffer memory allocation!");
				WriteToLog("ContentManager : GetUserScreenObjects. Done");
			#endif

			return false;
		}

		// Bind data
		screenResult -> Bind(1, &idBuf, sizeof(idBuf), SQL_C_LONG);
		screenResult -> Bind(2, nameBuf, NAME_LEN);
		screenResult -> Bind(3, captionBuf, NAME_LEN);
		screenResult -> Bind(4, &typeBuf, sizeof(typeBuf), SQL_C_LONG);
		screenResult -> Bind(5, &scopeBuf, sizeof(scopeBuf), SQL_C_LONG);
		screenResult -> Bind(6, &locationXBuf, sizeof(locationXBuf), SQL_C_LONG);
		screenResult -> Bind(7, &locationYBuf, sizeof(locationYBuf), SQL_C_LONG);
		screenResult -> Bind(8, &locationXPersBuf, sizeof(locationXPersBuf), SQL_C_LONG);
		screenResult -> Bind(9, &locationYPersBuf, sizeof(locationYPersBuf), SQL_C_LONG);
		screenResult -> Bind(10, &WidthPixBuf, sizeof(WidthPixBuf), SQL_C_LONG);
		screenResult -> Bind(11, &WidthPersBuf, sizeof(WidthPersBuf), SQL_C_LONG);
		screenResult -> Bind(12, &HeightPixBuf, sizeof(HeightPixBuf), SQL_C_LONG);
		screenResult -> Bind(13, &HeightPersBuf, sizeof(HeightPersBuf), SQL_C_LONG);
		screenResult -> Bind(14, &fontSizeBuf, sizeof(fontSizeBuf), SQL_C_LONG);
		screenResult -> Bind(15, &textColorBuf, sizeof(textColorBuf), SQL_C_LONG);
		screenResult -> Bind(16, &bckGrndColorBuf, sizeof(bckGrndColorBuf), SQL_C_LONG);
		screenResult -> Bind(17, strValueBuf, NAME_LEN);
		screenResult -> Bind(18, imgValueBuf, BLOB_VALUE_LEN, SQL_C_BINARY);
		screenResult -> Bind(19, &imgValueSize, sizeof(imgValueSize), SQL_C_LONG);
		screenResult -> Bind(20, textValueBuf, BLOB_VALUE_LEN);
		screenResult -> Bind(21, &textValueSize, sizeof(textValueSize), SQL_C_LONG);
		screenResult -> Bind(22, &orderBuf, sizeof(orderBuf), SQL_C_LONG);

		// Tile image flag
		bool tileImageFound = false;

		// Submit button flag
		bool submitButtonFound = false;

		// User name text box flag
		bool userNameTextBoxFound = false;

		// Password text box flag
		bool passwordBoxFound = false;

		// Domain combo box flag
		bool domainBoxFound = false;

		// Get user screen objects
		while(screenResult -> MoveNext())
		{
			// Tile image can be placed only on main screen and just one time
			if ((tileImageFound) && (typeBuf == SOT_IMAGE) && (content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserScreenObjects. Tile image duplicate found. Skipped.");
				#endif

				continue;
			}

			// Submit button can be placed only just one time
			if ((submitButtonFound) && (typeBuf == SOT_BUTTON) && (content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserScreenObjects. Submit button duplicate found. Skipped.");
				#endif
				
				continue;
			}

			// User nsme text box can be placed only just one time
			if ((userNameTextBoxFound) && (typeBuf == SOT_USER_NAME_BOX) && (content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserScreenObjects. User name text box duplicate found. Skipped.");
				#endif

				continue;
			}

			// Password text box can be placed only just one time
			if ((passwordBoxFound) && (typeBuf == SOT_PASSWORD_BOX) && (content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserScreenObjects. Password text box duplicate found. Skipped.");
				#endif

				continue;
			}

			// Domain box can be placed only just one time
			if ((domainBoxFound) && (typeBuf == SOT_DOMAIN_NAME_BOX) && (content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserScreenObjects. Domain name combo box duplicate found. Skipped.");
				#endif

				continue;
			}
			
			// Check flags
			if ((typeBuf == SOT_IMAGE) && 
				(content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN)) 
					tileImageFound = true;

			if ((typeBuf == SOT_BUTTON) &&
				(content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN)) 
					submitButtonFound = true;

			if ((typeBuf == SOT_USER_NAME_BOX) &&
				(content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
					userNameTextBoxFound = true;

			if ((typeBuf == SOT_PASSWORD_BOX) &&
				(content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
					passwordBoxFound = true;

			if ((typeBuf == SOT_DOMAIN_NAME_BOX) &&
				(content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
					domainBoxFound = true;

			// Allocate memory for scrren object
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] = (PSCREEN_OBJECT)malloc(sizeof(SCREEN_OBJECT));
			if (!content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount])
			{
				free(imgValueBuf);
				free(textValueBuf);
				delete screenResult;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetUserScreenObjects. Error memory allocation");
					WriteToLog("ContentManager : GetUserScreenObjects. Done");
				#endif

				return false;
			}

			// Get screen object data
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> objID = idBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> objTypeId = typeBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> objScope = scopeBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> locationX = locationXBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> locationY = locationYBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> locationXPers = locationXPersBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> locationYPers = locationYPersBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> widthPix = WidthPixBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> widthPers = WidthPersBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> heightPix = HeightPixBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> heightPers = HeightPersBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> fontSize = fontSizeBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> textColor = textColorBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> backgroundColor = bckGrndColorBuf;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> order = orderBuf;
			strcpy(content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> objName, nameBuf);
			strcpy(content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> objCaption, captionBuf);
			strcpy(content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> strValue, strValueBuf);

			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> textValue = NULL;
			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> imgValue = NULL;

			if (textValueSize > BLOB_VALUE_LEN - 1)
				textValueSize = BLOB_VALUE_LEN - 1;

			if (imgValueSize > BLOB_VALUE_LEN)
				imgValueSize = BLOB_VALUE_LEN;

			if (textValueSize > 0)
				content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> textValueSize = textValueSize + 1;
			else
				content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> textValueSize = 0;

			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> imgValueSize = imgValueSize;
			
			// Allocate memory for big text block
			if (((typeBuf == SOT_BIG_TEXT_BLOCK) ||
				(typeBuf == SOT_EDU_LESSON_TEXT) ||
				(typeBuf == SOT_EDU_QUESTION_TEXT) ||
				(typeBuf == SOT_LEGAL_DISCLAIMER_TEXT)) && (textValueSize > 0))
			{
				content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> textValue = (char *)malloc(textValueSize + 1);
		
				if (!content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> textValue)
				{
					free(imgValueBuf);
					free(textValueBuf);
					delete screenResult;

					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
						WriteToLog("ContentManager : GetUserScreenObjects. Error content BLOB values memory allocation.");
						WriteToLog("ContentManager : GetUserScreenObjects. Done");
					#endif

					return false;
				}

				memcpy(content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> textValue, textValueBuf, textValueSize);
				content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> textValue[textValueSize] = '\0';
			}

			// Allocate memory for image
			if (((typeBuf == SOT_IMAGE) ||
				(typeBuf == SOT_EDU_LESSON_IMAGE) ||
				(typeBuf == SOT_LEGAL_DISCLAIMER_IMAGE)) && (imgValueSize > 0))
			{
			
				content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> imgValue = malloc(imgValueSize);
							
				if (!content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> imgValue)
				{
					free(imgValueBuf);
					free(textValueBuf);
					delete screenResult;

					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
						WriteToLog("ContentManager : GetUserScreenObjects. Error content BLOB values memory allocation.");
						WriteToLog("ContentManager : GetUserScreenObjects. Done");
					#endif

					return false;
				}
			
				memcpy(content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> imgValue, imgValueBuf, imgValueSize);
			}

			content -> userScreens[screenInd] -> screenObjects[content -> userScreens[screenInd] -> scrObjCount] -> listValuesSet = NULL;

			content -> userScreens[screenInd] -> scrObjCount++;

			if (content -> userScreens[screenInd] -> scrObjCount >= MAX_SCR_OBJ_COUNT)
			{
				char msg[STR_VALUE_LEN];
				sprintf(msg, "ContentManager : Get user screen objects --> Screen : %s. Screen objects list overlow!", content -> userScreens[screenInd] -> Name);
				WriteToLog(msg);
				break;
			}
			
			// Clear buffers
			idBuf = 0;
			typeBuf = 0;
			scopeBuf = 0;
			locationXBuf = 0;
			locationYBuf = 0;
			locationXPersBuf = 0;
			locationYPersBuf = 0;
			WidthPixBuf = 0;
			WidthPersBuf = 0;
			HeightPixBuf = 0;
			HeightPersBuf = 0;
			fontSizeBuf = 0;
			textColorBuf = 0;
			bckGrndColorBuf = 0;
			nameBuf[0] = 0;
		    captionBuf[0] = 0;
			strValueBuf[0] = 0;
			*((char *)(imgValueBuf)) = 0;
			textValueBuf[0] = 0;
			imgValueSize = 0;
			textValueSize = 0;
			orderBuf = 0;
		}

		free(imgValueBuf);
		free(textValueBuf);
		delete screenResult;

		// Validate submit button flag
		if ((!submitButtonFound) && (content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
		{
			char msg[STR_VALUE_LEN];
			sprintf(msg, "ContentManager : Get user screen objects --> Screen : %s.  Submit button not found!", content -> userScreens[screenInd] -> Name);
			(msg);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserScreenObjects. Done");
			#endif

			return false;
		}

		// Validate user text box flag
		if ((!userNameTextBoxFound) && (content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
		{
			char msg[STR_VALUE_LEN];
			sprintf(msg, "ContentManager : Get user screen objects --> Screen : %s.  User name text box not found!", content -> userScreens[screenInd] -> Name);
			WriteToLog(msg);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserScreenObjects. Done");
			#endif

			return false;
		}

		// Validate password box flag
		if ((!passwordBoxFound) && (content -> userScreens[screenInd] -> screenTypeID == SOT_MAIN_SCREEN))
		{
			char msg[STR_VALUE_LEN];
			sprintf(msg, "ContentManager : Get user screen objects --> Screen : %s.  Password box not found!", content -> userScreens[screenInd] -> Name);
			WriteToLog(msg);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserScreenObjects. Done");
			#endif

			return false;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserScreenObjects. Done");
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

   Class : ContentManager

   Method : GetListValuesSet

   Parameters :
			Input : 
			    content - pointer to content structure

   Return : TRUE if success, FALSE if fail
	
	Description :  Retrieve from database list items
				   for each SOT_COMBOBOX

*****************************************************************/
bool ContentManager :: GetListValuesSet(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetListValuesSet. Start");
	#endif
		
	// Check DLL legal user
	dbManager += dllUserCheckResult;

	// Validate critical parameters
	if ((content == NULL) || (content -> presetID == -1) || (!(dbManager -> Opened())))
	{
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : Error of GetListValuesSet using");
			WriteToLog("ContentManager : GetListValuesSet. Done");
		#endif

		return false;
	}

	try
	{
		for(int i = 0; (i < content -> userScreensCount) && (i < MAX_SCREEN_COUNT); i++)
		{
			if (content -> userScreens[i])
				for(int j = 0; (j < content -> userScreens[i] -> scrObjCount) && (j < MAX_SCR_OBJ_COUNT); j++)
				{
					if ((content -> userScreens[i] -> screenObjects[j]) &&
						(content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_COMBOBOX))
					{
						// Prepare SQL query
						char sql[SQL_SIZE];
						sprintf(sql, "SELECT Value \
			 							FROM ScreenObjectListValues\
										WHERE (ScreenObjectID = %d)", content -> userScreens[i] -> screenObjects[j] -> objID);

						// Allocate memory for list
						content -> userScreens[i] -> screenObjects[j] -> listValuesSet = (PLIST_VALUES_SET)malloc(sizeof(LIST_VALUES_SET));

						if (!content -> userScreens[i] -> screenObjects[j] -> listValuesSet)
						{
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
								WriteToLog("ContentManager :  GetListValuesSet. Error list memory allocation");
								WriteToLog("ContentManager : GetListValuesSet. Done");
							#endif

							return false;
						}

						// Execute SQL query
						ResultSet * listResult = dbManager -> ExecuteSelectQuery(sql);

						char valueBuf[STR_VALUE_LEN];

						// Bind data
						listResult -> Bind(1, valueBuf, STR_VALUE_LEN);

						content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount = 0;

						// Get list items
						while (listResult -> MoveNext())
						{
							strcpy(content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> listValues[content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount], valueBuf);
							
							content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount++;

							if (content -> userScreens[i] -> screenObjects[j] -> listValuesSet -> valuesCount >= LIST_VALUES_SET_MAX_SIZE)
							{
								char msg[STR_VALUE_LEN];
								sprintf(msg, "ContentManager : Get list values set --> Screen : %s.  Screen object: %s. List overflow!", content -> userScreens[i] -> Name, content -> userScreens[i] -> screenObjects[j] -> objName);
								WriteToLog(msg);
								break;
							}
							
							// clear buffer
							valueBuf[0] = 0;
						}

						delete listResult;
					}
				}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetListValuesSet. Done.");
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

#pragma region Education

/****************************************************************

   Class : ContentManager

   Method :  GetEducationValues

   Parameters :
			Input : 
			    content - pointer to content structure
				userID - user ID
				authSystemID - authentication system type

   Return : TRUE if success, FALSE if fail
	
	Description :  Retrieve from database text of questions and 
				   list items of answers

*****************************************************************/
bool ContentManager :: GetEducationValues(PPRESET_CONTAINER content, int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetEducationValues. Start");
	#endif
		
	// Check DLL legal user
	dbManager += dllUserCheckResult;

	// Validate critical parameters
	if ((content == NULL) || (content -> presetID == -1) || (!(dbManager -> Opened())))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : Error of GetEducationValues using");
			WriteToLog("ContentManager : GetEducationValues. Done");
		#endif

		return false;
	}

	bool needStudy = true;
	PUSER_DESCRIPTOR user = GetUserDescriptor(userID);

	if (!user)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetEducationValues. Can't get user descriptor!");
		#endif

		needStudy = false;
	}
	
	for(int i = 0; i < content -> userScreensCount; i++)
	{
		if (content -> userScreens[i] -> screenTypeID != SOT_STUDY_SCREEN)
		{
			int objInd = -1;

			while ((objInd = FindScreenObject(content -> userScreens[i], SOT_EDU_LESSON_TEXT)) != -1)
				DeleteScreenObjectByInd(content -> userScreens[i], objInd);

			while ((objInd = FindScreenObject(content -> userScreens[i], SOT_EDU_LESSON_IMAGE)) != -1)
				DeleteScreenObjectByInd(content -> userScreens[i], objInd);

			while ((objInd = FindScreenObject(content -> userScreens[i], SOT_EDU_QUESTION_TEXT)) != -1)
				DeleteScreenObjectByInd(content -> userScreens[i], objInd);
		}
	}

	// Temporary buffers
	int lgnLessonTextCount = 0;
	PSCREEN_OBJECT lgnLessonTexts[MAX_SCR_OBJ_COUNT];

	int pstLessonTextCount = 0;
	PSCREEN_OBJECT pstLessonTexts[MAX_SCR_OBJ_COUNT];
		
	int lgnLessonImageCount = 0;
	PSCREEN_OBJECT lgnLessonImages[MAX_SCR_OBJ_COUNT];
	
	int pstLessonImageCount = 0;
	PSCREEN_OBJECT pstLessonImages[MAX_SCR_OBJ_COUNT];
	
	int lgnQuestCount = 0;
	PSCREEN_OBJECT lgnQuests[MAX_SCR_OBJ_COUNT];

	int pstQuestCount = 0;
	PSCREEN_OBJECT pstQuests[MAX_SCR_OBJ_COUNT];
	
	int lgnAnswerCount = 0;
	PSCREEN_OBJECT lgnAnswers[MAX_SCR_OBJ_COUNT];

	int pstAnswerCount = 0;
	PSCREEN_OBJECT pstAnswers[MAX_SCR_OBJ_COUNT];

	for(int i = 0; (i < content -> userScreensCount) && (i < MAX_SCREEN_COUNT); i++)
	{
		if (content -> userScreens[i])
		{
			for(int j = 0; (j < content -> userScreens[i] -> scrObjCount) && (j < MAX_SCR_OBJ_COUNT); j++)
			{
				if (content -> userScreens[i] -> screenObjects[j])
				{
					if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_EDU_LESSON_TEXT)
					{
						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_LOGON_SCREEN) &&
						   	(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_LOGON_SCREEN))
						{
							lgnLessonTexts[lgnLessonTextCount] = content -> userScreens[i] -> screenObjects[j];
							lgnLessonTextCount++;
						}

						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_POST_LOGIN_SCREEN) &&
						   	(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_POST_LOGIN_SCREEN))
						{
							pstLessonTexts[pstLessonTextCount] = content -> userScreens[i] -> screenObjects[j];
							pstLessonTextCount++;
						}
					}

					if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_EDU_LESSON_IMAGE)
					{
						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_LOGON_SCREEN) &&
						   	(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_LOGON_SCREEN))
						{
							lgnLessonImages[lgnLessonImageCount] = content -> userScreens[i] -> screenObjects[j];
							lgnLessonImageCount++;
						}

						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_POST_LOGIN_SCREEN) &&
						   	(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_POST_LOGIN_SCREEN))
						{
							pstLessonImages[pstLessonImageCount] = content -> userScreens[i] -> screenObjects[j];
							pstLessonImageCount++;
						}
					}

					if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_EDU_QUESTION_TEXT)
					{
						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_LOGON_SCREEN) &&
						   	(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_LOGON_SCREEN))
						{
							lgnQuests[lgnQuestCount] = content -> userScreens[i] -> screenObjects[j];
							lgnQuestCount++;
						}

						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_POST_LOGIN_SCREEN) &&
						   	(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_POST_LOGIN_SCREEN))
						{
							pstQuests[pstQuestCount] = content -> userScreens[i] -> screenObjects[j];
							pstQuestCount++;
						}
					}

					if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_EDU_ANSWER_BOX)
					{
						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_LOGON_SCREEN) &&
						   	(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_LOGON_SCREEN))
						{
							lgnAnswers[lgnAnswerCount] = content -> userScreens[i] -> screenObjects[j];
							lgnAnswerCount++;
						}

						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_POST_LOGIN_SCREEN) &&
						   	(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_POST_LOGIN_SCREEN))
						{
							pstAnswers[pstAnswerCount] = content -> userScreens[i] -> screenObjects[j];
							pstAnswerCount++;
						}
					}
				}
			}
		}
	}
	
	if ((!((lgnLessonTextCount == lgnQuestCount) && (lgnLessonTextCount == lgnAnswerCount))))
	{
		DeleteEducationScreenObjects(content, SO_SCOPE_LOGON_SCREEN);
		lgnLessonTextCount = 0;
	}
	

	if (!((pstLessonTextCount == pstQuestCount) && (pstLessonTextCount == pstAnswerCount)))
	{
		DeleteEducationScreenObjects(content, SO_SCOPE_POST_LOGIN_SCREEN);
		pstLessonTextCount = 0;

	}

	if((lgnLessonTextCount == 0) &&(pstLessonTextCount == 0))
	{
		needStudy = false;
		WriteToLog("ContentManager : Get education values --> Wrong study elements design!");
	}

	needStudy =  needStudy && user -> needStudy;
	
	if (!needStudy)
	{
		DeleteEducationScreenObjects(content);

		RemoveUserDescriptor(user);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetEducationValues. This user no need study");
			WriteToLog("ContentManager : GetEducationValues. Done");
		#endif

		return true;
	}

	try
	{
		// Get lessons

		// Prepare SQl query
		char sql[SQL_SIZE * 2];

		sprintf(sql, "SELECT EducationLessons.ID,\
					         EducationLessons.LessonText,\
							 DATALENGTH(EducationLessons.LessonText),\
							 EducationLessons.LessonImage,\
							 DATALENGTH(EducationLessons.LessonImage)\
						FROM EducationLessons\
						WHERE (EducationLessons.CategoryID = %d) and\
					   		   EducationLessons.ID in (SELECT EducationQuestions.LessonID\
							                           FROM EducationQuestions\
							                           WHERE EducationQuestions.ID not in (SELECT UserEducationAnswers.QuestionID\
							                                                               FROM UserEducationAnswers\
							                                                               WHERE (UserEducationAnswers.UserID = %d) and\
							                                                                     (UserEducationAnswers.CorrectAnswerSign = 1)))\
					    ORDER BY EducationLessons.LessonOrder", user -> eduCategotyID, user -> userID);
		
				
		int lessonIDBuf = 0;
		char * lessonTextBuf = (char *)malloc(BLOB_VALUE_LEN);
		void * lessonImageBuf = malloc(BLOB_VALUE_LEN);
		int lessonTextSizeBuf = 0;
		int lessonImageSizeBuf = 0;

		if ((!lessonTextBuf) || (!lessonImageBuf))
		{
			RemoveUserDescriptor(user);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager :  GetEducationValues. Error BLOB buffer memory allocation");
				WriteToLog("ContentManager : GetEducationValues. Done");
			#endif

			return false;
		}

		// Execute SQL query
		ResultSet * lessonResult = dbManager -> ExecuteSelectQuery(sql);

		// Bind data
		lessonResult -> Bind(1, &lessonIDBuf, sizeof(lessonIDBuf), SQL_C_LONG);
		lessonResult -> Bind(2, lessonTextBuf, BLOB_VALUE_LEN);
		lessonResult -> Bind(3, &lessonTextSizeBuf, sizeof(lessonTextSizeBuf), SQL_C_LONG);
		lessonResult -> Bind(4, lessonImageBuf, BLOB_VALUE_LEN, SQL_C_BINARY);
		lessonResult -> Bind(5, &lessonImageSizeBuf, sizeof(lessonImageSizeBuf), SQL_C_LONG);

		// Get lessons
		int lgnLessonTextCounter = 0;
		int lgnLessonImageCounter = 0;
		int pstLessonTextCounter = 0;
		int pstLessonImageCounter = 0;

		PSCREEN_OBJECT lessonText = NULL;
		PSCREEN_OBJECT lessonImage = NULL;
		
		while(lessonResult -> MoveNext())
		{
			if (lgnLessonTextCounter < lgnLessonTextCount)
			{
				lessonText = lgnLessonTexts[lgnLessonTextCounter];
				lgnLessonTextCounter++;

				if (lgnLessonImageCounter < lgnLessonImageCount)
				{
					lessonImage = lgnLessonImages[lgnLessonImageCounter];
					lgnLessonImageCounter++;
				}
				else
					lessonImage = NULL;
			}
			else
				if (pstLessonTextCounter < pstLessonTextCount)
				{
					lessonText = pstLessonTexts[pstLessonTextCounter];
					pstLessonTextCounter++;

					if (pstLessonImageCounter < pstLessonImageCount)
					{
						lessonImage = pstLessonImages[pstLessonImageCounter];
						pstLessonImageCounter++;
					}
					else
						lessonImage = NULL;
				}
				else
				{
					lessonText = NULL;
					lessonImage = NULL;
				}

			if (lessonText)
			{
				lessonText -> lessonID = lessonIDBuf;
			
				if (lessonText -> textValue)
					free(lessonText -> textValue);

				if (lessonTextSizeBuf > BLOB_VALUE_LEN - 1)
					lessonTextSizeBuf = BLOB_VALUE_LEN - 1;

				if (lessonTextSizeBuf > 0)
				{
					lessonText -> textValueSize = lessonTextSizeBuf + 1;
					lessonText -> textValue = (char *)malloc(lessonTextSizeBuf + 1);
			
					if(!lessonText -> textValue)
					{
						RemoveUserDescriptor(user);
						delete lessonResult;

						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
							WriteToLog("ContentManager : GetEducationValues. Error BLOB text value memory allocation");
							WriteToLog("ContentManager : GetEducationValues. Done");
						#endif

						return false;
					}
			
					memcpy(lessonText -> textValue, lessonTextBuf, lessonTextSizeBuf);
					lessonText -> textValue[lessonTextSizeBuf] = '\0';
				}
				else
				{
					lessonText -> textValueSize = 0;
					lessonText -> textValue = NULL;
				}
			}

			if (lessonImage)
			{
				if (lessonImage -> imgValue)
					free(lessonImage -> imgValue);
				
				if (lessonImageSizeBuf > BLOB_VALUE_LEN)
					lessonImageSizeBuf = BLOB_VALUE_LEN;

				if (lessonImageSizeBuf > 0)
				{
					lessonImage -> imgValueSize = lessonImageSizeBuf;
					lessonImage -> imgValue = malloc(lessonImageSizeBuf);

					if(!lessonImage -> imgValue)
					{
						RemoveUserDescriptor(user);
						delete lessonResult;

						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
							WriteToLog("ContentManager : GetEducationValues. Error BLOB image value memory allocation");
							WriteToLog("ContentManager : GetEducationValues. Done");
						#endif

						return false;
					}

					memcpy(lessonImage -> imgValue, lessonImageBuf, lessonImageSizeBuf);
				}
				else
				{
					lessonImage -> imgValueSize = 0;
					lessonImage -> imgValue = NULL;
				}
			}

			lessonIDBuf = 0;
		    lessonTextBuf[0] = 0;
			*(char *)lessonImageBuf = 0;
			lessonTextSizeBuf = 0;
			lessonImageSizeBuf = 0;
		}

		free(lessonTextBuf);
		free(lessonImageBuf);
		delete lessonResult;

		// Logon screen objects corection
		if(lgnLessonImageCounter < lgnLessonImageCount)
		{
			for(int i = lgnLessonImageCounter; i < lgnLessonImageCount; i++)
			{
				DeleteScreenObject(content, lgnLessonImages[i]);
			}
		}

		if(lgnLessonTextCounter < lgnLessonTextCount)
		{
			for(int i = lgnLessonTextCounter; i < lgnLessonTextCount; i++)
			{
				DeleteScreenObject(content, lgnLessonTexts[i]);
			}
		}

		if(lgnLessonTextCounter < lgnLessonTextCount)
		{
			for(int i = lgnLessonTextCounter; i < lgnLessonTextCount; i++)
			{
				DeleteScreenObject(content, lgnQuests[i]);
				DeleteScreenObject(content, lgnAnswers[i]);
			}
		}

		// Post login screen objects correction
		if(pstLessonImageCounter < pstLessonImageCount)
		{
			for(int i = pstLessonImageCounter; i < pstLessonImageCount; i++)
			{
				DeleteScreenObject(content, pstLessonImages[i]);
			}
		}

		if(pstLessonTextCounter < pstLessonTextCount)
		{
			for(int i = pstLessonTextCounter; i < pstLessonTextCount; i++)
			{
				DeleteScreenObject(content, pstLessonTexts[i]);
			}
		}

		if(pstLessonTextCounter < pstLessonTextCount)
		{
			for(int i = pstLessonTextCounter; i < pstLessonTextCount; i++)
			{
				DeleteScreenObject(content, pstQuests[i]);
				DeleteScreenObject(content, pstAnswers[i]);
			}
		}

		lgnLessonTextCount = lgnLessonTextCounter;
		pstLessonTextCount = pstLessonTextCounter;

		if (lgnLessonTextCount == 0)
			DeleteEducationScreenObjects(content, SO_SCOPE_LOGON_SCREEN);

		if (pstLessonTextCount == 0)
			DeleteEducationScreenObjects(content, SO_SCOPE_POST_LOGIN_SCREEN);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			char msg[NAME_LEN];
			sprintf(msg, "ContentManager : GetEducationValues. Logon screen lessons count: %d", lgnLessonTextCounter);
			WriteToLog(msg);
			sprintf(msg, "ContentManager : GetEducationValues. Post login screen lessons count: %d", pstLessonTextCounter);
			WriteToLog(msg);

		#endif

		int lessonTextCount = 0;
		PSCREEN_OBJECT lessonTexts[MAX_SCR_OBJ_COUNT];
		PSCREEN_OBJECT quests[MAX_SCR_OBJ_COUNT];
		PSCREEN_OBJECT answers[MAX_SCR_OBJ_COUNT];

		for (int k = 0; k < 2; k++)
		{
			switch (k)
			{
				case 0 : 
					{
						lessonTextCount = lgnLessonTextCount;
						for(int i = 0; i < lessonTextCount; i++)
						{
							lessonTexts[i] = lgnLessonTexts[i];
							quests[i] = lgnQuests[i];
							answers[i] = lgnAnswers[i];
						}
						break;
					}

				case 1 : 
					{
						lessonTextCount = pstLessonTextCount;
						for(int i = 0; i < lessonTextCount; i++)
						{
							lessonTexts[i] = pstLessonTexts[i];
							quests[i] = pstQuests[i];
							answers[i] = pstAnswers[i];
						}
						break;
					}
			}

			if(lessonTextCount > 0)
			{
				// Get questions 
				for(int i = 0; i < lessonTextCount; i++)
				{
					if (user -> eduQuestionRandom)
						sprintf(sql, "SELECT TOP 1 EducationQuestions.ID,\
										           EducationQuestions.QuestionText,\
										           DATALENGTH(EducationQuestions.QuestionText),\
										           EducationQuestions.RightAnswerID\
									  FROM EducationQuestions\
									  WHERE (EducationQuestions.LessonID = %d) and\
											 EducationQuestions.ID not in (SELECT UserEducationAnswers.QuestionID\
										                                   FROM UserEducationAnswers\
										                                   WHERE (UserEducationAnswers.UserID = %d) and\
										                                         (UserEducationAnswers.CorrectAnswerSign = 1))\
									  ORDER BY NEWID()", lessonTexts[i] -> lessonID, user -> userID);
					else
						sprintf(sql, "SELECT TOP 1 EducationQuestions.ID,\
										           EducationQuestions.QuestionText,\
										           DATALENGTH(EducationQuestions.QuestionText),\
										           EducationQuestions.RightAnswerID\
									  FROM EducationQuestions\
									  WHERE (EducationQuestions.LessonID = %d) and\
										  	 EducationQuestions.ID not in (SELECT UserEducationAnswers.QuestionID\
										                                   FROM UserEducationAnswers\
										                                   WHERE (UserEducationAnswers.UserID = %d) and\
										                                         (UserEducationAnswers.CorrectAnswerSign = 1))\
									  ORDER BY EducationQuestions.QuestionOrder", lessonTexts[i] -> lessonID, user -> userID);

					// Execute SQL query
					ResultSet * questionResult = dbManager -> ExecuteSelectQuery(sql);
		
					int questionIDBuf = 0;
					int rightAnswerIDBuf = 0;
					char * questionTextBuf = (char *)malloc(BLOB_VALUE_LEN);
					int questionTextSizeBuf = 0;

					if (!questionTextBuf)
					{
						RemoveUserDescriptor(user);
					
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
							WriteToLog("ContentManager :  GetEducationValues. Error BLOB buffer memory allocation");
							WriteToLog("ContentManager : GetEducationValues. Done");
						#endif

						return false;
					}

					// Bind data
					questionResult -> Bind(1, &questionIDBuf, sizeof(questionIDBuf), SQL_C_LONG);
					questionResult -> Bind(2, questionTextBuf, BLOB_VALUE_LEN);
					questionResult -> Bind(3, &questionTextSizeBuf, sizeof(questionTextSizeBuf), SQL_C_LONG);
					questionResult -> Bind(4, &(rightAnswerIDBuf), sizeof(rightAnswerIDBuf), SQL_C_LONG);

					if (questionResult -> MoveFirst())
					{
						quests[i] -> questionID = questionIDBuf;
						quests[i] -> rightAnswerID = rightAnswerIDBuf;
						quests[i] -> lessonID = lessonTexts[i] -> lessonID;
			
						if (quests[i] -> textValue)
							free(quests[i] -> textValue);

						if (questionTextSizeBuf > BLOB_VALUE_LEN - 1)
							questionTextSizeBuf = BLOB_VALUE_LEN - 1;

						if (questionTextSizeBuf > 0)
						{
							quests[i] -> textValueSize = questionTextSizeBuf + 1;
							quests[i] -> textValue = (char *)malloc(questionTextSizeBuf + 1);
			
							if(!quests[i] -> textValue)
							{
								RemoveUserDescriptor(user);
								delete questionResult;

								#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
									WriteToLog("ContentManager :  GetEducationValues. Error BLOB text value memory allocation");
									WriteToLog("ContentManager : GetEducationValues. Done");
								#endif

								return false;
							}
			
							memcpy(quests[i] -> textValue, questionTextBuf, questionTextSizeBuf);
							quests[i] -> textValue[questionTextSizeBuf] = '\0';
						}
						else
						{
							quests[i] -> textValueSize = 0;
							quests[i] -> textValue = NULL;
						}
					}

					free(questionTextBuf);
					delete questionResult;
				}


				for(int i = 0; i < lessonTextCount; i++)
				{
					answers[i] -> questionID = quests[i] -> questionID;
					answers[i] -> lessonID = quests[i] -> lessonID;
					answers[i] -> rightAnswerID = quests[i] -> rightAnswerID;
					answers[i] -> listValuesSet = (PLIST_VALUES_SET)malloc(sizeof(LIST_VALUES_SET));

					// Validate allocation result
					if (!answers[i] -> listValuesSet)
					{
						RemoveUserDescriptor(user);

						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
							WriteToLog("ContentManager :  GetEducationValues. Error answers memory allocation. Done");
							WriteToLog("ContentManager : GetEducationValues. Done");
						#endif

						return false;
					}

					// Prepare SQL query
					char sql[SQL_SIZE];
					sprintf(sql, "SELECT EducationAnswers.AnswerText\
								  FROM EducationAnswers, EducationQuestionAnswers\
								  WHERE (EducationAnswers.ID = EducationQuestionAnswers.AnswerID) and\
										(EducationQuestionAnswers.QuestionID = %d)\
								  ORDER BY EducationQuestionAnswers.AnswerOrder", answers[i] -> questionID);
								
					// Execute SQL query
					ResultSet * answerResult = dbManager -> ExecuteSelectQuery(sql);

					char valueBuf[STR_VALUE_LEN];

					// Bind data
					answerResult -> Bind(1, valueBuf, STR_VALUE_LEN);

					answers[i] -> listValuesSet -> valuesCount = 0;

					// Get answer list items
					while (answerResult -> MoveNext())
					{
						strcpy(answers[i] -> listValuesSet -> listValues[answers[i] -> listValuesSet -> valuesCount], valueBuf);
									
						answers[i] -> listValuesSet -> valuesCount++;

						// clear buffer
						valueBuf[0] = 0;
					}

					delete answerResult;
				}
			}
		}	

		RemoveUserDescriptor(user);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetEducationValues. Done");
		#endif

		return true;
	}
	catch(DBException & ex)
	{
		// Error processing
		RemoveUserDescriptor(user);
				
		char errMsg[ERROR_MSG_MAXLEN];
		ex.GetMessage(errMsg);
		WriteToLog(errMsg);

		return false;
	}
}

/****************************************************************

   Class : ContentManager

   Method : DeleteEducationScreenObjects
   
   Parameters :
			Input : 
			    content - pointer to content structure

   Description :  Delete education objects

*****************************************************************/
void ContentManager :: DeleteEducationScreenObjects(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteEducationScreenObjects. Start");
	#endif

	int screenInd = -1;

	while ((screenInd = FindUserScreen(content, SOT_STUDY_SCREEN)) != -1)
		DeleteUserScreenByInd(content, screenInd);

	for(int i = 0; i < content -> userScreensCount; i++)
	{
		int objInd = -1;
				
		while ((objInd = FindScreenObject(content -> userScreens[i], SOT_EDU_LESSON_TEXT)) != -1)
			DeleteScreenObjectByInd(content -> userScreens[i], objInd);

		while ((objInd = FindScreenObject(content -> userScreens[i], SOT_EDU_LESSON_IMAGE)) != -1)
			DeleteScreenObjectByInd(content -> userScreens[i], objInd);

		while ((objInd = FindScreenObject(content -> userScreens[i], SOT_EDU_QUESTION_TEXT)) != -1)
			DeleteScreenObjectByInd(content -> userScreens[i], objInd);

		while ((objInd = FindScreenObject(content -> userScreens[i], SOT_EDU_ANSWER_BOX)) != -1)
			DeleteScreenObjectByInd(content -> userScreens[i], objInd);

		while ((objInd = FindScreenObject(content -> userScreens[i], SOT_EDUCATION_LABEL)) != -1)
			DeleteScreenObjectByInd(content -> userScreens[i], objInd);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteEducationScreenObjects. Done");
	#endif
}

/****************************************************************

   Class : ContentManager

   Method : DeleteEducationScreenObjects
   
   Parameters :
			Input : 
			    content - pointer to content structure
				scope - screen objects scope

   Description :  Delete education objects

*****************************************************************/
void ContentManager :: DeleteEducationScreenObjects(PPRESET_CONTAINER content, int scope)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteEducationScreenObjects. Start");
	#endif

	for (int i = content -> userScreensCount - 1; i >= 0; i--)
	{
		if ((content -> userScreens[i] -> screenTypeID == SOT_STUDY_SCREEN) &&
			(content -> userScreens[i] -> screenScope == scope))
				DeleteUserScreenByInd(content, i);
	}

	for(int i = 0; i < content -> userScreensCount; i++)
	{
		for (int j = content -> userScreens[i] -> scrObjCount - 1; j >= 0; j--)
		{
			if (((content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_EDU_LESSON_TEXT) ||
				(content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_EDU_LESSON_IMAGE) ||
				(content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_EDU_QUESTION_TEXT) ||
				(content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_EDU_ANSWER_BOX) ||
				(content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_EDUCATION_LABEL)) &&
				(content -> userScreens[i] -> screenObjects[j] -> objScope == scope))
			{
				DeleteScreenObjectByInd(content -> userScreens[i], j);
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteEducationScreenObjects. Done");
	#endif
}
#pragma endregion

#pragma region Legal disclaimer

/****************************************************************

   Class : ContentManager

   Method :  GetLegalDisclaimerValues

   Parameters :
			Input : 
			    content - pointer to content structure

   Return : TRUE if success, FALSE if fail
	
	Description :  Retrieve from database legal disclaimer

*****************************************************************/
bool ContentManager :: GetLegalDisclaimerValues(PPRESET_CONTAINER content, int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetLegalDisclaimerValues. Start");
	#endif
		
	// Check DLL legal user
	dbManager += dllUserCheckResult;

	// Validate critical parameters
	if ((content == NULL) || (content -> presetID == -1) || (!(dbManager -> Opened())))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : Error of GetLegalDisclaimerValues using");
			WriteToLog("ContentManager : GetLegalDisclaimerValues. Done");
		#endif

		return false;
	}

	bool showLegalDisclaimer = true;		
		
	for(int i = 0; i < content -> userScreensCount; i++)
	{
		if (content -> userScreens[i] -> screenTypeID != SOT_LEGAL_DISCLAIMER_SCREEN)
		{
			int objInd = -1;

			while ((objInd = FindScreenObject(content -> userScreens[i], SOT_LEGAL_DISCLAIMER_TEXT)) != -1)
				DeleteScreenObjectByInd(content -> userScreens[i], objInd);

			while ((objInd = FindScreenObject(content -> userScreens[i], SOT_LEGAL_DISCLAIMER_IMAGE)) != -1)
				DeleteScreenObjectByInd(content -> userScreens[i], objInd);
		}
	}

	// Temporary buffers
	int lgnLegalDisclaimerTextCount = 0;
	PSCREEN_OBJECT lgnLegalDisclaimerTexts[MAX_SCR_OBJ_COUNT];

	int pstLegalDisclaimerTextCount = 0;
	PSCREEN_OBJECT pstLegalDisclaimerTexts[MAX_SCR_OBJ_COUNT];

	int lgnLegalDisclaimerImageCount = 0;
	PSCREEN_OBJECT lgnLegalDisclaimerImages[MAX_SCR_OBJ_COUNT];
	
	int pstLegalDisclaimerImageCount = 0;
	PSCREEN_OBJECT pstLegalDisclaimerImages[MAX_SCR_OBJ_COUNT];

	int lgnLegalDisclaimerAnswerCount = 0;
	PSCREEN_OBJECT lgnLegalDisclaimerAnswers[MAX_SCR_OBJ_COUNT];
	
	int pstLegalDisclaimerAnswerCount = 0;
	PSCREEN_OBJECT pstLegalDisclaimerAnswers[MAX_SCR_OBJ_COUNT];
	

	for(int i = 0; (i < content -> userScreensCount) && (i < MAX_SCREEN_COUNT); i++)
	{
		if (content -> userScreens[i])
		{
			for(int j = 0; (j < content -> userScreens[i] -> scrObjCount) && (j < MAX_SCR_OBJ_COUNT); j++)
			{
				if (content -> userScreens[i] -> screenObjects[j])
				{
					if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_LEGAL_DISCLAIMER_TEXT)
					{
						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_LOGON_SCREEN) &&
							(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_LOGON_SCREEN))
						{
							lgnLegalDisclaimerTexts[lgnLegalDisclaimerTextCount] = content -> userScreens[i] -> screenObjects[j];
							lgnLegalDisclaimerTextCount++;
						}

						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_POST_LOGIN_SCREEN) &&
							(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_POST_LOGIN_SCREEN))
						{
							pstLegalDisclaimerTexts[pstLegalDisclaimerTextCount] = content -> userScreens[i] -> screenObjects[j];
							pstLegalDisclaimerTextCount++;
						}
					}

					if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_LEGAL_DISCLAIMER_IMAGE)
					{
						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_LOGON_SCREEN) &&
							(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_LOGON_SCREEN))
						{
							lgnLegalDisclaimerImages[lgnLegalDisclaimerImageCount] = content -> userScreens[i] -> screenObjects[j];
							lgnLegalDisclaimerImageCount++;
						}

						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_POST_LOGIN_SCREEN) &&
							(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_POST_LOGIN_SCREEN))
						{
							pstLegalDisclaimerImages[pstLegalDisclaimerImageCount] = content -> userScreens[i] -> screenObjects[j];
							pstLegalDisclaimerImageCount++;
						}
					}

					if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_LEGAL_DISCLAIMER_COMBOBOX)
					{
						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_LOGON_SCREEN) &&
							(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_LOGON_SCREEN))
						{
							lgnLegalDisclaimerAnswers[lgnLegalDisclaimerAnswerCount] = content -> userScreens[i] -> screenObjects[j];
							lgnLegalDisclaimerAnswerCount++;
						}

						if ((content -> userScreens[i] -> screenScope == SO_SCOPE_POST_LOGIN_SCREEN) &&
							(content -> userScreens[i] -> screenObjects[j] -> objScope == SO_SCOPE_POST_LOGIN_SCREEN))
						{
							pstLegalDisclaimerAnswers[pstLegalDisclaimerAnswerCount] = content -> userScreens[i] -> screenObjects[j];
							pstLegalDisclaimerAnswerCount++;
						}
					}
				}
			}
		}
	}
	
	if (lgnLegalDisclaimerTextCount != lgnLegalDisclaimerAnswerCount)
	{
		DeleteLegalDisclaimerScreenObjects(content, SO_SCOPE_LOGON_SCREEN);
		lgnLegalDisclaimerTextCount = 0;
	}

	if (pstLegalDisclaimerTextCount != pstLegalDisclaimerAnswerCount)
	{
		DeleteLegalDisclaimerScreenObjects(content, SO_SCOPE_POST_LOGIN_SCREEN);
		pstLegalDisclaimerTextCount = 0;
	}

	if ((lgnLegalDisclaimerTextCount == 0) && (pstLegalDisclaimerTextCount == 0))
	{
		showLegalDisclaimer = false;
		WriteToLog("ContentManager : Get legal disclaimer values --> Wrong legal disclaimer elements design!");
	}

	if (!showLegalDisclaimer)
	{
		DeleteLegalDisclaimerScreenObjects(content);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetLegalDisclaimerValues. Legal disclaimer will not be show!");
			WriteToLog("ContentManager : GetLegalDisclaimerValues. Done");
		#endif

		return true;
	}


	try
	{
		// Prepare SQl query
		char sql[SQL_SIZE * 2];

		int lgnLegalDisclaimerTextCounter = 0;
		int lgnLegalDisclaimerImageCounter = 0;
		int pstLegalDisclaimerTextCounter = 0;
		int pstLegalDisclaimerImageCounter = 0;

		PSCREEN_OBJECT legalDisclaimerText = NULL;
		PSCREEN_OBJECT legalDisclaimerImage = NULL;

		for(int scopeType = NS_PRIVATE; scopeType <= NS_PUBLIC; scopeType++)
		{
			for(int ldType = NDT_SHOW_ONLY_ONCE; ldType <= NDT_ALWAYS_SHOW; ldType++)
			{
				switch (ldType)
				{
					case NDT_SHOW_ONCE_PER_DAY : if (scopeType == NS_PRIVATE) 
														sprintf(sql, "SELECT Notifications.ID, \
																			 Notifications.NoticeText,\
																			 DATALENGTH(Notifications.NoticeText),\
																			 Notifications.NoticeImage,\
																			 DATALENGTH(Notifications.NoticeImage)\
																	  FROM Notifications\
														              WHERE (((Notifications.ID in (SELECT UserNotifications.NoticeID\
														                                            FROM UserNotifications\
														                                            WHERE ((UserNotifications.UserID = %d) AND\
																										   (UserNotifications.DispTypeID = %d))))\
																			OR\
																			(Notifications.ID in (SELECT UserGroupNotifications.NoticeID\
																								  FROM UserGroupNotifications\
																								  WHERE ((UserGroupNotifications.GroupID in (SELECT UserGroupUsers.GroupID\
																																			 FROM UserGroupUsers\
																																			 WHERE (UserGroupUsers.UserID = %d))) AND\
																										(UserGroupNotifications.DispTypeID = %d)))))\
																			AND\
																			(Notifications.NoticeTypeID = %d) AND\
																			(Notifications.ScopeID = %d) AND\
																			(Notifications.ID not in (SELECT UserNotificationsHistory.NoticeID\
																									  FROM UserNotificationsHistory\
																									  WHERE (UserNotificationsHistory.UserID = %d) AND\
																											(UserNotificationsHistory.NoticeDate = CONVERT(date, GETDATE())))))", userID, ldType, userID, ldType, NT_LEGAL_DISCLAIMER, scopeType, userID);
													if (scopeType == NS_PUBLIC) 
														sprintf(sql, "SELECT Notifications.ID, \
																			 Notifications.NoticeText,\
																			 DATALENGTH(Notifications.NoticeText),\
																			 Notifications.NoticeImage,\
																			 DATALENGTH(Notifications.NoticeImage)\
																	 FROM Notifications\
																	 WHERE (Notifications.DispTypeID = %d) AND\
																		   (Notifications.NoticeTypeID = %d) AND\
																		   (Notifications.ScopeID = %d) AND\
																		   (Notifications.ID not in (SELECT UserNotificationsHistory.NoticeID\
																									 FROM UserNotificationsHistory\
														                                             WHERE (UserNotificationsHistory.UserID = %d) AND\
																										   (UserNotificationsHistory.NoticeDate = CONVERT(date, GETDATE()))))", ldType, NT_LEGAL_DISCLAIMER, scopeType, userID);
													break;

						case NDT_SHOW_ONLY_ONCE		: if (scopeType == NS_PRIVATE) 
															sprintf(sql, "SELECT Notifications.ID, \
																			 Notifications.NoticeText,\
																			 DATALENGTH(Notifications.NoticeText),\
																			 Notifications.NoticeImage,\
																			 DATALENGTH(Notifications.NoticeImage)\
																	  FROM Notifications\
														              WHERE (((Notifications.ID in (SELECT UserNotifications.NoticeID\
														                                            FROM UserNotifications\
														                                            WHERE ((UserNotifications.UserID = %d) AND\
																										   (UserNotifications.DispTypeID = %d))))\
																			OR\
																			(Notifications.ID in (SELECT UserGroupNotifications.NoticeID\
																								  FROM UserGroupNotifications\
																								  WHERE ((UserGroupNotifications.GroupID in (SELECT UserGroupUsers.GroupID\
																																			 FROM UserGroupUsers\
																																			 WHERE (UserGroupUsers.UserID = %d))) AND\
																										(UserGroupNotifications.DispTypeID = %d)))))\
																			AND\
																			(Notifications.NoticeTypeID = %d) AND\
																			(Notifications.ScopeID = %d) AND\
																			(Notifications.ID not in (SELECT UserNotificationsHistory.NoticeID\
																									  FROM UserNotificationsHistory\
																									  WHERE (UserNotificationsHistory.UserID = %d))))", userID, ldType, userID, ldType, NT_LEGAL_DISCLAIMER, scopeType, userID);
													  if (scopeType == NS_PUBLIC) 
															sprintf(sql, "SELECT Notifications.ID, \
																		         Notifications.NoticeText,\
																				 DATALENGTH(Notifications.NoticeText),\
																		         Notifications.NoticeImage, \
																				 DATALENGTH(Notifications.NoticeImage)\
																		  FROM Notifications\
																		  WHERE (Notifications.DispTypeID = %d) AND\
																				(Notifications.NoticeTypeID = %d) AND\
																				(Notifications.ScopeID = %d) AND\
																				(Notifications.ID not in (SELECT UserNotificationsHistory.NoticeID\
																						                  FROM UserNotificationsHistory\
																						                  WHERE (UserNotificationsHistory.UserID = %d)))", ldType, NT_LEGAL_DISCLAIMER, scopeType, userID);

													break;

						case NDT_ALWAYS_SHOW		: if (scopeType == NS_PRIVATE) 
															sprintf(sql, "SELECT Notifications.ID, \
																				 Notifications.NoticeText,\
																				 DATALENGTH(Notifications.NoticeText),\
																				 Notifications.NoticeImage,\
																				 DATALENGTH(Notifications.NoticeImage)\
																		  FROM Notifications\
																		  WHERE (((Notifications.ID in (SELECT UserNotifications.NoticeID\
																										FROM UserNotifications\
																										WHERE ((UserNotifications.UserID = %d) AND\
																											   (UserNotifications.DispTypeID = %d))))\
																				OR\
																				(Notifications.ID in (SELECT UserGroupNotifications.NoticeID\
																									  FROM UserGroupNotifications\
																									  WHERE ((UserGroupNotifications.GroupID in (SELECT UserGroupUsers.GroupID\
																																				 FROM UserGroupUsers\
																																				 WHERE(UserGroupUsers.UserID = %d))) AND\
																											 (UserGroupNotifications.DispTypeID = %d)))))\
																				AND\
																				(Notifications.NoticeTypeID = %d) AND\
																				(Notifications.ScopeID = %d))", userID, ldType, userID, ldType, NT_LEGAL_DISCLAIMER, scopeType);
													if (scopeType == NS_PUBLIC) 
															sprintf(sql, "SELECT Notifications.ID, \
															                     Notifications.NoticeText,\
																				 DATALENGTH(Notifications.NoticeText), \
																		         Notifications.NoticeImage, \
																				 DATALENGTH(Notifications.NoticeImage)\
																	      FROM Notifications\
																	      WHERE (Notifications.DispTypeID = %d) AND\
																			    (Notifications.NoticeTypeID = %d) AND\
																			    (Notifications.ScopeID = %d)", ldType, NT_LEGAL_DISCLAIMER, scopeType);

													break;
				}

				int legalDisclaimerIDBuf = 0;
				char * legalDisclaimerTextBuf = (char *)malloc(BLOB_VALUE_LEN);
				void * legalDisclaimerImageBuf = malloc(BLOB_VALUE_LEN);
				int legalDisclaimerTextSizeBuf = 0;
				int legalDisclaimerImageSizeBuf = 0;

				if ((!legalDisclaimerTextBuf) || (!legalDisclaimerImageBuf))
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
						WriteToLog("ContentManager :  GetLegalDisclaimerValues. Error BLOB buffer memory allocation");
						WriteToLog("ContentManager : GetLegalDisclaimerValues. Done");
					#endif

					return false;
				}

				// Execute SQL query
				ResultSet * legalDisclaimerResult = dbManager -> ExecuteSelectQuery(sql);

				// Bind data
				legalDisclaimerResult -> Bind(1, &legalDisclaimerIDBuf, sizeof(legalDisclaimerIDBuf), SQL_C_LONG);
				legalDisclaimerResult -> Bind(2, legalDisclaimerTextBuf, BLOB_VALUE_LEN);
				legalDisclaimerResult -> Bind(3, &legalDisclaimerTextSizeBuf, sizeof(legalDisclaimerTextSizeBuf), SQL_C_LONG);
				legalDisclaimerResult -> Bind(4, legalDisclaimerImageBuf, BLOB_VALUE_LEN, SQL_C_BINARY);
				legalDisclaimerResult -> Bind(5, &legalDisclaimerImageSizeBuf, sizeof(legalDisclaimerImageSizeBuf), SQL_C_LONG);

				while(legalDisclaimerResult -> MoveNext())
				{
					for (int k = 0; k < 2; k++)
					{
						switch (k)
						{
							case 0 : 
							{
								if (lgnLegalDisclaimerTextCounter < lgnLegalDisclaimerTextCount)
								{
									legalDisclaimerText = lgnLegalDisclaimerTexts[lgnLegalDisclaimerTextCounter];
									lgnLegalDisclaimerTextCounter++;

									if (lgnLegalDisclaimerImageCounter < lgnLegalDisclaimerImageCount)
									{
										legalDisclaimerImage = lgnLegalDisclaimerImages[lgnLegalDisclaimerImageCounter];
										lgnLegalDisclaimerImageCounter++;
									}
									else
										legalDisclaimerImage = NULL;
								}
								else
								{
									legalDisclaimerText = NULL;
									legalDisclaimerImage = NULL;
								}

								break;
							}

							case 1 : 
							{
								if (pstLegalDisclaimerTextCounter < pstLegalDisclaimerTextCount)
								{
									legalDisclaimerText = pstLegalDisclaimerTexts[pstLegalDisclaimerTextCounter];
									pstLegalDisclaimerTextCounter++;

									if (pstLegalDisclaimerImageCounter < pstLegalDisclaimerImageCount)
									{
										legalDisclaimerImage = pstLegalDisclaimerImages[pstLegalDisclaimerImageCounter];
										pstLegalDisclaimerImageCounter++;
									}
									else
										legalDisclaimerImage = NULL;
								}
								else
								{
									legalDisclaimerText = NULL;
									legalDisclaimerImage = NULL;
								}

								break;
							}
						}
										
						if (legalDisclaimerText)
						{
							if (legalDisclaimerText -> textValue)
								free(legalDisclaimerText -> textValue);

							if (legalDisclaimerTextSizeBuf > BLOB_VALUE_LEN - 1)
								legalDisclaimerTextSizeBuf = BLOB_VALUE_LEN - 1;
						
							if (legalDisclaimerTextSizeBuf > 0)
							{
								legalDisclaimerText -> textValueSize = legalDisclaimerTextSizeBuf + 1;
								legalDisclaimerText -> textValue = (char *)malloc(legalDisclaimerTextSizeBuf + 1);
			
								if(!legalDisclaimerText -> textValue)
								{
									delete legalDisclaimerResult;

									#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
										WriteToLog("ContentManager : GetLegalDisclaimerValues. Error BLOB text value memory allocation");
										WriteToLog("ContentManager : GetLegalDisclaimerValues. Done");
									#endif

									return false;
								}
			
								memcpy(legalDisclaimerText -> textValue, legalDisclaimerTextBuf, legalDisclaimerTextSizeBuf);
								legalDisclaimerText -> textValue[legalDisclaimerTextSizeBuf] = '\0';
							}
							else
							{
								legalDisclaimerText -> textValueSize = 0;
								legalDisclaimerText -> textValue = NULL;
							}

							legalDisclaimerText -> questionID = legalDisclaimerIDBuf;
						}

						if (legalDisclaimerImage)
						{
							if (legalDisclaimerImage -> imgValue)
								free(legalDisclaimerImage -> imgValue);
						
							if (legalDisclaimerImageSizeBuf > BLOB_VALUE_LEN)
								legalDisclaimerImageSizeBuf = BLOB_VALUE_LEN;

							if (legalDisclaimerImageSizeBuf > 0)
							{
								legalDisclaimerImage -> imgValueSize = legalDisclaimerImageSizeBuf;
								legalDisclaimerImage -> imgValue = malloc(legalDisclaimerImageSizeBuf);
			
								if(!legalDisclaimerImage -> imgValue)
								{
									delete legalDisclaimerResult;

									#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
										WriteToLog("ContentManager : GetLegalDisclaimerValues. Error BLOB text value memory allocation");
										WriteToLog("ContentManager : GetLegalDisclaimerValues. Done");
									#endif

									return false;
								}
			
								memcpy(legalDisclaimerImage -> imgValue, legalDisclaimerImageBuf, legalDisclaimerImageSizeBuf);
							}
							else
							{
								legalDisclaimerImage -> imgValueSize = 0;
								legalDisclaimerImage -> imgValue = NULL;
							}

							legalDisclaimerImage -> questionID = legalDisclaimerIDBuf;
						}
					}

					legalDisclaimerIDBuf = 0;
					legalDisclaimerTextBuf[0] = 0;
					*(char *)legalDisclaimerImageBuf = 0;
				}

				free(legalDisclaimerTextBuf);
				free(legalDisclaimerImageBuf);
				delete legalDisclaimerResult;
			}
		}

		if (lgnLegalDisclaimerTextCounter < lgnLegalDisclaimerTextCount)
		{
			for(int i = lgnLegalDisclaimerTextCounter; i < lgnLegalDisclaimerTextCount; i++)
			{
				DeleteScreenObject(content, lgnLegalDisclaimerTexts[i]);
			}
		}

		if (lgnLegalDisclaimerImageCounter < lgnLegalDisclaimerImageCount)
		{
			for(int i = lgnLegalDisclaimerImageCounter; i < lgnLegalDisclaimerImageCount; i++)
			{
				DeleteScreenObject(content, lgnLegalDisclaimerImages[i]);
			}
		}

		if (pstLegalDisclaimerTextCounter < pstLegalDisclaimerTextCount)
		{
			for(int i = pstLegalDisclaimerTextCounter; i < pstLegalDisclaimerTextCount; i++)
			{
				DeleteScreenObject(content, pstLegalDisclaimerTexts[i]);
			}
		}

		if (pstLegalDisclaimerImageCounter < pstLegalDisclaimerImageCount)
		{
			for(int i = pstLegalDisclaimerImageCounter; i < pstLegalDisclaimerImageCount; i++)
			{
				DeleteScreenObject(content, pstLegalDisclaimerImages[i]);
			}
		}

		if (lgnLegalDisclaimerTextCounter == 0)
		{
			DeleteLegalDisclaimerScreenObjects(content, SO_SCOPE_LOGON_SCREEN);
			lgnLegalDisclaimerTextCount = 0;
		}

		if (pstLegalDisclaimerTextCounter == 0)
		{
			DeleteLegalDisclaimerScreenObjects(content, SO_SCOPE_POST_LOGIN_SCREEN);
			pstLegalDisclaimerTextCount = 0;
		}

		int legalDisclaimerAnswerCount = 0;
		PSCREEN_OBJECT legalDisclaimerAnswers[MAX_SCR_OBJ_COUNT];
		for (int k = 0; k < 2; k++)
		{
			switch (k)
			{
				case 0 : 
					{
						legalDisclaimerAnswerCount = lgnLegalDisclaimerTextCount;
						for(int i = 0; i < legalDisclaimerAnswerCount; i++)
						{
							legalDisclaimerAnswers[i] = lgnLegalDisclaimerAnswers[i];
						}
						break;
					}

				case 1 : 
					{
						legalDisclaimerAnswerCount = pstLegalDisclaimerTextCount;
						for(int i = 0; i < legalDisclaimerAnswerCount; i++)
						{
							legalDisclaimerAnswers[i] = pstLegalDisclaimerAnswers[i];
						}
						break;
					}
			}

			for(int i = 0; i < legalDisclaimerAnswerCount; i++)
			{
				if (legalDisclaimerAnswers[i] -> listValuesSet)
					free(legalDisclaimerAnswers[i] -> listValuesSet);

				legalDisclaimerAnswers[i] -> listValuesSet = (PLIST_VALUES_SET)malloc(sizeof(LIST_VALUES_SET));

				if (!legalDisclaimerAnswers[i] -> listValuesSet)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
						WriteToLog("ContentManager : GetLegalDisclaimerValues. List values set memory allocation error!");
						WriteToLog("ContentManager : GetLegalDisclaimerValues. Done");
					#endif

					return false;
				}

				legalDisclaimerAnswers[i] -> listValuesSet -> valuesCount = 3;
				strcpy(legalDisclaimerAnswers[i] -> listValuesSet -> listValues[0], " ");
				strcpy(legalDisclaimerAnswers[i] -> listValuesSet -> listValues[1], "I disagree");
				strcpy(legalDisclaimerAnswers[i] -> listValuesSet -> listValues[2], "I agree");
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetLegalDisclaimerValues. Done");
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

   Class : ContentManager

   Method : DeleteLegalDisclaimerScreenObjects

   Parameters :
			Input : 
			    content - pointer to content structure

   Description :  Delete legal disclaimer objects

*****************************************************************/
void ContentManager :: DeleteLegalDisclaimerScreenObjects(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteLegalDisclaimerScreenObjects. Start");
	#endif

	int screenInd = -1;

	while ((screenInd = FindUserScreen(content, SOT_LEGAL_DISCLAIMER_SCREEN)) != -1)
		DeleteUserScreenByInd(content, screenInd);

	for(int i = 0; i < content -> userScreensCount; i++)
	{
		int objInd = -1;
		
		while ((objInd = FindScreenObject(content -> userScreens[i], SOT_LEGAL_DISCLAIMER_TEXT)) != -1)
			DeleteScreenObjectByInd(content -> userScreens[i], objInd);

		while ((objInd = FindScreenObject(content -> userScreens[i], SOT_LEGAL_DISCLAIMER_IMAGE)) != -1)
			DeleteScreenObjectByInd(content -> userScreens[i], objInd);
		
		while ((objInd = FindScreenObject(content -> userScreens[i], SOT_LEGAL_DISCLAIMER_LABEL)) != -1)
			DeleteScreenObjectByInd(content -> userScreens[i], objInd);

		while ((objInd = FindScreenObject(content -> userScreens[i], SOT_LEGAL_DISCLAIMER_COMBOBOX)) != -1)
			DeleteScreenObjectByInd(content -> userScreens[i], objInd);
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteLegalDisclaimerScreenObjects. Done");
	#endif
}

/****************************************************************

   Class : ContentManager

   Method : DeleteLegalDisclaimerScreenObjects

   Parameters :
			Input : 
			    content - pointer to content structure
				scope - screen objects scope

   Description :  Delete legal disclaimer objects

*****************************************************************/
void ContentManager :: DeleteLegalDisclaimerScreenObjects(PPRESET_CONTAINER content, int scope)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteLegalDisclaimerScreenObjects. Start");
	#endif

	for (int i = content -> userScreensCount - 1; i >= 0; i--)
	{
		if ((content -> userScreens[i] -> screenTypeID == SOT_LEGAL_DISCLAIMER_SCREEN) &&
			(content -> userScreens[i] -> screenScope == scope))
				DeleteUserScreenByInd(content, i);
	}

	for(int i = 0; i < content -> userScreensCount; i++)
	{
		for (int j = content -> userScreens[i] -> scrObjCount - 1; j >= 0; j--)
		{
			if (((content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_LEGAL_DISCLAIMER_TEXT) ||
				(content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_LEGAL_DISCLAIMER_IMAGE) ||
				(content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_LEGAL_DISCLAIMER_LABEL) ||
				(content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_LEGAL_DISCLAIMER_COMBOBOX)) &&
				(content -> userScreens[i] -> screenObjects[j] -> objScope == scope))
			{
				DeleteScreenObjectByInd(content -> userScreens[i], j);
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteLegalDisclaimerScreenObjects. Done");
	#endif
}

#pragma endregion

#pragma region Notifications

/****************************************************************

   Class : ContentManager

   Method :  GetUserNotificationValues

   Parameters :
			Input : 
			    content - pointer to content structure

   Return : TRUE if success, FALSE if fail
	
	Description :  Retrieve user notifications from database

*****************************************************************/
bool ContentManager :: GetUserNotificationValues(PPRESET_CONTAINER content, int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetUserNotificationValues. Start");
	#endif
		
	// Check DLL legal user
	dbManager += dllUserCheckResult;

	// Validate critical parameters
	if ((content == NULL) || (content -> presetID == -1) || (!(dbManager -> Opened())))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : Error of GetUserNotificationValues using");
			WriteToLog("ContentManager : GetUserNotificationValues. Done");
		#endif

		return false;
	}
	
	bool showNotifications = true;	
		
	for(int i = 0; i < content -> userScreensCount; i++)
	{
		if (content -> userScreens[i] -> screenTypeID != SOT_NOTIFICATION_SCREEN)
		{
			int objInd = -1;

			while ((objInd = FindScreenObject(content -> userScreens[i], SOT_SIMPLE_NOTICE_TEXT)) != -1)
				DeleteScreenObjectByInd(content -> userScreens[i], objInd);

			while ((objInd = FindScreenObject(content -> userScreens[i], SOT_WARNING_NOTICE_TEXT)) != -1)
				DeleteScreenObjectByInd(content -> userScreens[i], objInd);
		}
	}


	if (!showNotifications)
	{
		DeleteSimpleNoticesScreenObjects(content);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserNotificationValues. Notices will not be show!");
			WriteToLog("ContentManager : GetUserNotificationValues. Done");
		#endif

		return true;
	}


	try
	{
		// Prepare SQl query
		char sql[SQL_SIZE * 2];

		int noticeCounter = 0;
		int noticeIDs[MAX_SCR_OBJ_COUNT];

		char * simpleNoticeMes = (char *)calloc(BLOB_VALUE_LEN, 1);
		char * warningNoticeMes = (char *)calloc(BLOB_VALUE_LEN, 1);
		int simpleNoticesSize = 0;
		int warningNotiesSize = 0;

		if ((!simpleNoticeMes) || (!warningNoticeMes))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager :  GetUserNotificationValues. Error of message buffer memory allocation");
				WriteToLog("ContentManager : GetUserNotificationValues. Done");
			#endif

			return false;
		}

		for(int noticeType = NT_SIMPLE_NOTICE; noticeType <= NT_WARNING_NOTICE; noticeType++)
		{
			for(int scopeType = NS_PRIVATE; scopeType <= NS_PUBLIC; scopeType++)
			{
				for(int dispType = NDT_SHOW_ONLY_ONCE; dispType <= NDT_ALWAYS_SHOW; dispType++)
				{
					switch (dispType)
					{
					case NDT_SHOW_ONCE_PER_DAY : if (scopeType == NS_PRIVATE) 
														sprintf(sql, "SELECT Notifications.ID, \
																			 Notifications.NoticeText,\
																			 DATALENGTH(Notifications.NoticeText),\
																			 Notifications.NoticeImage,\
																			 DATALENGTH(Notifications.NoticeImage)\
																	  FROM Notifications\
														              WHERE (((Notifications.ID in (SELECT UserNotifications.NoticeID\
														                                            FROM UserNotifications\
														                                            WHERE ((UserNotifications.UserID = %d) AND\
																										   (UserNotifications.DispTypeID = %d))))\
																			OR\
																			(Notifications.ID in (SELECT UserGroupNotifications.NoticeID\
																								  FROM UserGroupNotifications\
																								  WHERE ((UserGroupNotifications.GroupID in (SELECT UserGroupUsers.GroupID\
																																			 FROM UserGroupUsers\
																																			 WHERE (UserGroupUsers.UserID = %d))) AND\
																										(UserGroupNotifications.DispTypeID = %d)))))\
																			AND\
																			(Notifications.NoticeTypeID = %d) AND\
																			(Notifications.ScopeID = %d) AND\
																			(Notifications.ID not in (SELECT UserNotificationsHistory.NoticeID\
																									  FROM UserNotificationsHistory\
																									  WHERE (UserNotificationsHistory.UserID = %d) AND\
																											(UserNotificationsHistory.NoticeDate = CONVERT(date, GETDATE())))))", userID, dispType, userID, dispType, noticeType, scopeType, userID);

													if (scopeType == NS_PUBLIC) 
														sprintf(sql, "SELECT Notifications.ID, \
																			 Notifications.NoticeText,\
																			 DATALENGTH(Notifications.NoticeText),\
																			 Notifications.NoticeImage,\
																			 DATALENGTH(Notifications.NoticeImage)\
																	 FROM Notifications\
																	 WHERE (Notifications.DispTypeID = %d) AND\
																		   (Notifications.NoticeTypeID = %d) AND\
																		   (Notifications.ScopeID = %d) AND\
																		   (Notifications.ID not in (SELECT UserNotificationsHistory.NoticeID\
																									 FROM UserNotificationsHistory\
														                                             WHERE (UserNotificationsHistory.UserID = %d) AND\
																									 	   (UserNotificationsHistory.NoticeDate = CONVERT(date, GETDATE()))))", dispType, noticeType, scopeType, userID);
													break;

						case NDT_SHOW_ONLY_ONCE		: if (scopeType == NS_PRIVATE) 
															sprintf(sql, "SELECT Notifications.ID, \
																			 Notifications.NoticeText,\
																			 DATALENGTH(Notifications.NoticeText),\
																			 Notifications.NoticeImage,\
																			 DATALENGTH(Notifications.NoticeImage)\
																	  FROM Notifications\
														              WHERE (((Notifications.ID in (SELECT UserNotifications.NoticeID\
														                                            FROM UserNotifications\
														                                            WHERE ((UserNotifications.UserID = %d) AND\
																										   (UserNotifications.DispTypeID = %d))))\
																			OR\
																			(Notifications.ID in (SELECT UserGroupNotifications.NoticeID\
																								  FROM UserGroupNotifications\
																								  WHERE ((UserGroupNotifications.GroupID in (SELECT UserGroupUsers.GroupID\
																																			 FROM UserGroupUsers\
																																			 WHERE (UserGroupUsers.UserID = %d))) AND\
																										(UserGroupNotifications.DispTypeID = %d)))))\
																			AND\
																			(Notifications.NoticeTypeID = %d) AND\
																			(Notifications.ScopeID = %d) AND\
																			(Notifications.ID not in (SELECT UserNotificationsHistory.NoticeID\
																									  FROM UserNotificationsHistory\
																									  WHERE (UserNotificationsHistory.UserID = %d))))", userID, dispType, userID, dispType, noticeType, scopeType, userID);

													  if (scopeType == NS_PUBLIC) 
															sprintf(sql, "SELECT Notifications.ID, \
																		         Notifications.NoticeText,\
																				 DATALENGTH(Notifications.NoticeText),\
																		         Notifications.NoticeImage, \
																				 DATALENGTH(Notifications.NoticeImage)\
																		  FROM Notifications\
																		  WHERE (Notifications.DispTypeID = %d) AND\
																				(Notifications.NoticeTypeID = %d) AND\
																				(Notifications.ScopeID = %d) AND\
																				(Notifications.ID not in (SELECT UserNotificationsHistory.NoticeID\
																						                  FROM UserNotificationsHistory\
																						                  WHERE (UserNotificationsHistory.UserID = %d)))", dispType, noticeType, scopeType, userID);

													break;

						case NDT_ALWAYS_SHOW		: if (scopeType == NS_PRIVATE) 
															sprintf(sql, "SELECT Notifications.ID, \
																				 Notifications.NoticeText,\
																				 DATALENGTH(Notifications.NoticeText),\
																				 Notifications.NoticeImage,\
																				 DATALENGTH(Notifications.NoticeImage)\
																		  FROM Notifications\
																		  WHERE (((Notifications.ID in (SELECT UserNotifications.NoticeID\
																										FROM UserNotifications\
																										WHERE ((UserNotifications.UserID = %d) AND\
																											   (UserNotifications.DispTypeID = %d))))\
																				OR\
																				(Notifications.ID in (SELECT UserGroupNotifications.NoticeID\
																									  FROM UserGroupNotifications\
																									  WHERE ((UserGroupNotifications.GroupID in (SELECT UserGroupUsers.GroupID\
																																				 FROM UserGroupUsers\
																																				 WHERE(UserGroupUsers.UserID = %d))) AND\
																											 (UserGroupNotifications.DispTypeID = %d)))))\
																				AND\
																				(Notifications.NoticeTypeID = %d) AND\
																				(Notifications.ScopeID = %d))", userID, dispType, userID, dispType, noticeType, scopeType);

													if (scopeType == NS_PUBLIC) 
															sprintf(sql, "SELECT Notifications.ID, \
															                     Notifications.NoticeText,\
																				 DATALENGTH(Notifications.NoticeText), \
																		         Notifications.NoticeImage, \
																				 DATALENGTH(Notifications.NoticeImage)\
																	      FROM Notifications\
																	      WHERE (Notifications.DispTypeID = %d) AND\
																			    (Notifications.NoticeTypeID = %d) AND\
																				(Notifications.ScopeID = %d)", dispType, noticeType, scopeType);

													break;
				}


				int noticeIDBuf = 0;
				char * noticeTextBuf = (char *)malloc(BLOB_VALUE_LEN);
				int noticeTextSizeBuf = 0;

				if (!noticeTextBuf)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
						WriteToLog("ContentManager :  GetUserNotificationValues. Error BLOB buffer memory allocation");
						WriteToLog("ContentManager : GetUserNotificationValues. Done");
					#endif

					return false;
				}

				// Execute SQL query
				ResultSet * notificationResult = dbManager -> ExecuteSelectQuery(sql);

				// Bind data
				notificationResult -> Bind(1, &noticeIDBuf, sizeof(noticeIDBuf), SQL_C_LONG);
				notificationResult -> Bind(2, noticeTextBuf, BLOB_VALUE_LEN);
				notificationResult -> Bind(3, &noticeTextSizeBuf, sizeof(noticeTextSizeBuf), SQL_C_LONG);

				char newLine[7] = {10, 13, 10, 13, 10, 13, 0};

				while(notificationResult -> MoveNext())
				{
					if (noticeType == NT_SIMPLE_NOTICE)
					{
						if ((noticeTextSizeBuf > 0) && (simpleNoticesSize + noticeTextSizeBuf + sizeof(newLine) + sizeof("NOTICE: ") <= BLOB_VALUE_LEN - 1))
						{
							strcat(simpleNoticeMes, "NOTICE: ");
							strcat(simpleNoticeMes, noticeTextBuf);
							strcat(simpleNoticeMes, newLine);

							simpleNoticesSize += noticeTextSizeBuf + sizeof(newLine) + sizeof("NOTICE: ");
						}
					}

					if (noticeType == NT_WARNING_NOTICE)
					{
						if ((noticeTextSizeBuf > 0) && (warningNotiesSize + noticeTextSizeBuf + sizeof(newLine) + sizeof("WARNING: ") <= BLOB_VALUE_LEN - 1))
						{
							strcat(warningNoticeMes, "WARNING: ");
							strcat(warningNoticeMes, noticeTextBuf);
							strcat(warningNoticeMes, newLine);

							warningNotiesSize += noticeTextSizeBuf + sizeof(newLine) + sizeof("WARNING: ");
						}
					}

					noticeTextBuf[0] = 0;
					noticeTextSizeBuf = 0;

					noticeIDs[noticeCounter] = noticeIDBuf;
					noticeCounter++;
				}

				free(noticeTextBuf);
				delete notificationResult;

			}
		  }
		}

		if (noticeCounter == 0)
		{
			int screenInd = -1;
			while ((screenInd = FindUserScreen(content, SOT_NOTIFICATION_SCREEN)) != -1)
				DeleteUserScreenByInd(content, screenInd);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetUserNotificationValues. Notices will not be show!");
				WriteToLog("ContentManager : GetUserNotificationValues. Done");
			#endif

			return true;
		}
		else
			for(int i = 0; i < noticeCounter; i++)
				SaveUserNotificationHistory(userID, noticeIDs[i]);
		
		for(int i = 0; i < content -> userScreensCount; i++)
		{
			if (content -> userScreens[i] -> screenTypeID == SOT_NOTIFICATION_SCREEN)
			{
				for(int j = 0; j < content -> userScreens[i] -> scrObjCount; j++)
				{
					if ((content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_SIMPLE_NOTICE_TEXT)||
						(content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_WARNING_NOTICE_TEXT))
					{
						if (content -> userScreens[i] -> screenObjects[j] -> textValue)
							free(content -> userScreens[i] -> screenObjects[j] -> textValue);

						if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_SIMPLE_NOTICE_TEXT)
						{
							content -> userScreens[i] -> screenObjects[j] -> textValueSize = simpleNoticesSize;
							content -> userScreens[i] -> screenObjects[j] -> textValue = (char *)malloc(simpleNoticesSize);
						}

						if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_WARNING_NOTICE_TEXT)
						{
							content -> userScreens[i] -> screenObjects[j] -> textValueSize = warningNotiesSize;
							content -> userScreens[i] -> screenObjects[j] -> textValue = (char *)malloc(warningNotiesSize);
						}

						if (!content -> userScreens[i] -> screenObjects[j] -> textValue)
						{
							#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
								WriteToLog("ContentManager :  GetUserNotificationValues. Error BLOB buffer memory allocation");
								WriteToLog("ContentManager : GetUserNotificationValues. Done");
							#endif

							return false;
						}

						if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_SIMPLE_NOTICE_TEXT)
							memcpy(content -> userScreens[i] -> screenObjects[j] -> textValue, simpleNoticeMes, simpleNoticesSize);

						if (content -> userScreens[i] -> screenObjects[j] -> objTypeId == SOT_WARNING_NOTICE_TEXT)
							memcpy(content -> userScreens[i] -> screenObjects[j] -> textValue, warningNoticeMes, warningNotiesSize);
					}
				}
			}
		}

		free(simpleNoticeMes);
		free(warningNoticeMes);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetUserNotificationValues. Done");
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

	Class : ContentManager

	Method :  SaveUserNotificationHistory
    
	Parameters :
			Input : 
				userID - user ID
				 noticeID -  notice ID

	Return:  Error code

	Description :  Set to database user notification infomation

*****************************************************************/
bool ContentManager ::  SaveUserNotificationHistory(int userID, int noticeID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : SaveUserNotificationHistory. Start");
	#endif
	
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];

		sprintf(sql, "SELECT *\
						FROM UserNotificationsHistory\
						WHERE (UserNotificationsHistory.NoticeID = %d) and\
						(UserNotificationsHistory.UserID = %d)", noticeID, userID);
		
		ResultSet * historyResult = dbManager -> ExecuteSelectQuery(sql);

		if (historyResult -> MoveFirst())
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : SaveUserNotificationHistory. Update data");
			#endif

			sprintf(sql, "UPDATE UserNotificationsHistory\
							SET UserNotificationsHistory.NoticeDate = GETDATE()\
							WHERE (UserNotificationsHistory.NoticeID = %d) and\
								(UserNotificationsHistory.UserID = %d)", noticeID, userID);
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : SaveUserNotificationHistory. Insert data");
			#endif

			sprintf(sql, "INSERT INTO UserNotificationsHistory\
							(UserID, NoticeID) VALUES (%d, %d)", userID, noticeID);
		}

		delete historyResult;

		dbManager ->  Execute(sql);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : SaveUserNotificationHistory. Done");
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

   Class : ContentManager

   Method : DeleteSimpleNoticesScreenObjects
   
   Parameters :
			Input : 
			    content - pointer to content structure

   Description :  Delete simple notices objects

*****************************************************************/
void ContentManager :: DeleteSimpleNoticesScreenObjects(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteSimpleNoticesScreenObjects. Start");
	#endif

	int screenInd = -1;
	while ((screenInd = FindUserScreen(content, SOT_NOTIFICATION_SCREEN)) != -1)
		DeleteUserScreenByInd(content, screenInd);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : DeleteSimpleNoticesScreenObjects. Done");
	#endif
}

#pragma endregion

#pragma region Sign In

/****************************************************************

   Class : ContentManager

   Method : SetUserSignInDate

   Parameters :
			Input : 
				userID - user ID
				authSystemID - ID of authentication system

   Return : success flag

   Description : Save date of last sign in 

*****************************************************************/
bool ContentManager :: SetUserSignInDate(int userID, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : SetUserSignInDate. Start");
	#endif
	
	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		char sql[SQL_SIZE];
		sprintf(sql, "UPDATE UserAccounts\
						SET UserAccounts.LastSignInDate = GETDATE()\
						WHERE ((UserAccounts.UserID = %d) and (UserAccounts.AuthSystemID = %d))", userID, authSystemID);

		dbManager ->  Execute(sql);
		
		sprintf(sql, "UPDATE Users\
						SET Users.LastSignInDate = GETDATE()\
						WHERE (Users.ID = %d)", userID);

		dbManager ->  Execute(sql);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : SetUserSignInDate. Done");
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

   Class : ContentManager

   Method : GetAuthSystemID
   
   Parameters :
			Input : 
				systemSettings - settings string param
				authSystemType - authentication system type ID

   Return : authentication system ID
	
   Description :  Get authentication system ID

*****************************************************************/
int ContentManager :: GetAuthSystemID(char * systemSettings, int authSystemType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetAuthSystemID. Start");
	#endif

	// Auth system ID
	int authSystemID = -1;

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT AuthSystems.ID, AuthSystems.SettingsString, DATALENGTH(AuthSystems.SettingsString) FROM AuthSystems WHERE (AuthSystems.AuthSystemTypeID = %d)", authSystemType);
		
		// Execute SQl query
		ResultSet * authSystemsResult = dbManager -> ExecuteSelectQuery(sql);

		int authSystemIDBuf = authSystemID;
		unsigned char settingsStringBuf[ENCRYPTED_DATA_SIZE];
		int settingsStringLenBuf = 0;

		// Bind data
		authSystemsResult -> Bind(1, &authSystemIDBuf, sizeof(authSystemIDBuf), SQL_C_LONG);
		authSystemsResult -> Bind(2, settingsStringBuf, ENCRYPTED_DATA_SIZE, SQL_BINARY);
		authSystemsResult -> Bind(3, &settingsStringLenBuf, sizeof(settingsStringLenBuf), SQL_C_LONG);

		// Retrieve record
		while (authSystemsResult -> MoveNext())
		{
			unsigned char decryptedSettingsString[NAME_LEN];
			int decryptedSettingsStringLen;

			if (encryptor -> UnPackAndDecryptSecurityData(settingsStringBuf, settingsStringLenBuf, decryptedSettingsString, NAME_LEN, &decryptedSettingsStringLen))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
					WriteToLog("ContentManager : GetAuthSystemID. Can't decrypt settings string!");
				#endif
			}
			else
			{
				decryptedSettingsString[decryptedSettingsStringLen] = 0;
				
				if (strstr(_strlwr((char *)decryptedSettingsString), _strlwr(systemSettings)) != NULL)
				{
					authSystemID = authSystemIDBuf;
					break;
				}
			}

			authSystemIDBuf = -1;
			settingsStringBuf[0] = 0;
			settingsStringLenBuf = 0;
		}
			
		delete authSystemsResult;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetAuthSystemID. Done");
		#endif

		return authSystemID;
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

   Class : ContentManager

   Method : GetAuthSystemID
   
   Parameters :
			Input : 
				encSystemSettings - encrypted settings string param
				encSystemSettingsLen - encrypted settings string param length
				authSystemType - authentication system type ID

   Return : authentication system ID
	
   Description :  Get authentication system ID

*****************************************************************/
int ContentManager :: GetAuthSystemID(unsigned char * encSystemSettings, int encSystemSettingsLen, int authSystemType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetAuthSystemID. Start");
	#endif

	unsigned char systemSettings[STR_VALUE_LEN];
	int systemSettingsLen;
	
	if (encryptor -> UnPackAndDecryptSecurityData(encSystemSettings, encSystemSettingsLen, systemSettings, NAME_LEN, &systemSettingsLen))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetAuthSystemID. Can't decrypt system settings!");
			WriteToLog("ContentManager : GetAuthSystemID. Done");
		#endif

		return -1;
	}
	else
		systemSettings[systemSettingsLen] = 0;

	int authSystemID = GetAuthSystemID((char *)systemSettings, authSystemType);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetAuthSystemID. Done");
	#endif

	return authSystemID;
}

/****************************************************************

   Class : ContentManager

   Method : GetAuthSystemName
   
   Parameters :
			Input : 
				authSystemID - authentcation system ID
			
			Output:
				authSystemName - authentcation system name

   Return : authentication system name
	
   Description :  Get authentication system name

*****************************************************************/
char *  ContentManager :: GetAuthSystemName(int authSystemID, char * authSystemName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : GetAuthSystemName. Start");
	#endif

	if ((authSystemID < 0) || (authSystemName == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetAuthSystemName. Wrong input parameters!");
			WriteToLog("ContentManager : GetAuthSystemName. Done");
		#endif

		return NULL;
	}

	try
	{
		try
		{
			// Check DLL legal user
			dbManager += dllUserCheckResult;

			// Get user descriptor
			char sql[SQL_SIZE];

			// Prepare sql query
			sprintf(sql, "SELECT AuthSystems.Name FROM AuthSystems WHERE (AuthSystems.ID = %d)", authSystemID);
		
			// Execute SQl query
			ResultSet * authSystemsResult = dbManager -> ExecuteSelectQuery(sql);

			char authSystemNameBuf[NAME_LEN] = "";

			// Bind data
			authSystemsResult -> Bind(1, authSystemNameBuf, NAME_LEN);

			// Retrieve record
			if (authSystemsResult -> MoveFirst())
			{
				strcpy(authSystemName, authSystemNameBuf);
			}
			else
			{
				strcpy(authSystemName, "");
			}
			
			delete authSystemsResult;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetAuthSystemName. Done");
			#endif

			return authSystemName;
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
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : GetAuthSystemName. Error of working with memory!");
			WriteToLog("ContentManager : GetAuthSystemName. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : ContentManager

   Method : GetAuthSystemName
   
   Parameters :
			Input : 
				authSystemID - authentcation system ID
			
			Output:
				encAuthSystemName - authentcation system name 
				                    in encrypted form
				encAuthSystemNameLen - length of authentcation 
				                    system name 
				                    in encrypted form

   Return : authentication system name
	
   Description :  Get authentication system name

*****************************************************************/
char * ContentManager :: GetAuthSystemName(int authSystemID, unsigned char * encAuthSystemName, int * encAuthSystemNameLen)
{
	// Get authentication system name 
	char authSystemName[NAME_LEN] = "";

	if ((encAuthSystemName == NULL) || 
		(encAuthSystemNameLen == NULL) || 
		(GetAuthSystemName(authSystemID, authSystemName)))
	{
		// Get authentication system name length
		int authSystemNameLen = strlen(authSystemName);

		// Encrypted authentication system name
		unsigned char encAuthSystemNameBuffer[ENCRYPTED_DATA_SIZE] = "";
		int encAuthSystemNameLenBuffer = 0;

		// Encrypt authentication system name
		if (encryptor -> EncryptAndPackSecurityData((unsigned char *)authSystemName, authSystemNameLen, encAuthSystemNameBuffer, ENCRYPTED_DATA_SIZE, &encAuthSystemNameLenBuffer))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : GetAuthSystemName. Can't encrypt authentication system name!");
			#endif

			return NULL;
		}
		else
		{
			memcpy(encAuthSystemName, encAuthSystemNameBuffer, encAuthSystemNameLenBuffer);
			*encAuthSystemNameLen = encAuthSystemNameLenBuffer;

			return authSystemName;
		}
	}
	else
		return NULL;
}

/****************************************************************

   Class : ContentManager

   Method : FirstUserAuthSystemSignInToday
   
   Parameters :
			Input : 
				userID - user ID
				authSystemID - auth system ID

   Return : Checking result. TRUE - if first time today.
	
   Description :  Check sign in date for user in some auth system 

*****************************************************************/
bool ContentManager :: FirstUserAuthSystemSignInToday(int userID, int authSystemID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
		WriteToLog("ContentManager : FirstUserAuthSystemSignInToday. Start");
	#endif

	// Auth system ID
	bool result = false;

	try
	{
		// Check DLL legal user
		dbManager += dllUserCheckResult;

		// Get user descriptor
		char sql[SQL_SIZE];

		// Prepare sql query
		sprintf(sql, "SELECT UserAccounts.UserID \
					  FROM UserAccounts \
					  WHERE ((DATEADD(DAY, DATEDIFF(DAY, 0, UserAccounts.LastSignInDate),0) = DATEADD(DAY, DATEDIFF(DAY, 0, GETDATE()), 0)) AND \
					         (UserAccounts.AuthSystemID = %d) AND \
							 (UserAccounts.UserID = %d))", authSystemID, userID);
		
		// Execute SQl query
		ResultSet * usersResult = dbManager -> ExecuteSelectQuery(sql);

		int userIDBuf = -1;

		// Bind data
		usersResult -> Bind(1, &userIDBuf, sizeof(userIDBuf), SQL_C_LONG);

		// Retrieve record
		if (usersResult -> MoveFirst())
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : FirstUserAuthSystemSignInToday. It is not first sign in for today");
			#endif

			result = false;
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
				WriteToLog("ContentManager : FirstUserAuthSystemSignInToday. It is first sign in for today");
			#endif

			result = true;
		}

		delete usersResult;
				
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_CONTENT)
			WriteToLog("ContentManager : FirstUserAuthSystemSignInToday. Done");
		#endif

		return result;
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

#pragma region LOG

/****************************************************************

   Class : ContentManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  ContentManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion

