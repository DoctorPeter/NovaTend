/****************************************************************

   Solution : NovaTend

   Project : z-setman-01.dll

   Module : SettingsManager.cpp

   Description : this module implements methods of
				  class SettingsManager

*****************************************************************/

#include "stdafx.h"
#include "SettingsManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <socket_def.h>

// z-setman-01.dll definition structure
extern DLL_COMMON_DEFINITION zSetmanDllDefinition;

#pragma region Constructor

/****************************************************************

   Class : SettingsManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
		
*****************************************************************/
SettingsManager :: SettingsManager(unsigned long dllUserID) : SystemBase(dllUserID, &zSetmanDllDefinition)
{
	encryptor = new Encryptor(zSetmanDllDefinition.dllID);
}

/****************************************************************

   Class : SettingsManager

   Method : Destructor

*****************************************************************/
SettingsManager :: ~SettingsManager(void)
{
	delete encryptor;
}

#pragma endregion

#pragma region Helper

/****************************************************************

   Class : SettingsManager

   Method : GetBinaryValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
			Output : 
				buffer - value buffer
				buffSize - buffer size

   Returns: error code

   Description : Get binary value

*****************************************************************/
int SettingsManager :: GetBinaryValue(WCHAR * regKey, WCHAR * regValue, unsigned char * buffer, int * buffSize)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL) || (buffer == NULL) || (buffSize == NULL))
		return ERROR_ACCESS_DENIED;
		
	HKEY hKey; 
	DWORD disp;

	// Open key for read
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	// Get value from registry
	DWORD valueType = 0;
	DWORD binBufLen = MAX_DATA_BUFFER_LEN;
	unsigned char binBuf[MAX_DATA_BUFFER_LEN];

	errorRes = RegGetValue(hKey, NULL, regValue, RRF_RT_REG_BINARY, &valueType, binBuf, &binBufLen);
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	// Close registry key
	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    	return errorRes;

	try
	{
		// Copy data
		memcpy(buffer, binBuf, binBufLen);
		*buffSize = binBufLen;
		
		return ERROR_SUCCESS;
	}
	catch(...)
	{
		return ERROR_OUTOFMEMORY;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : SetBinaryValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
				buffer - value buffer
				buffSize - buffer size

   Returns: error code

   Description : Set binary value

*****************************************************************/
int SettingsManager :: SetBinaryValue(WCHAR * regKey, WCHAR * regValue, unsigned char * buffer, int buffSize)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL) || (buffer == NULL))
		return ERROR_ACCESS_DENIED;
	
	HKEY hKey; 
	DWORD disp;

	// Open key for write
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	// Save value
	errorRes = RegSetValueEx(hKey, regValue, NULL, REG_BINARY, buffer, buffSize);
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	// Close key
	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    	return errorRes;

	return ERROR_SUCCESS;
}

/****************************************************************

   Class : SettingsManager

   Method : GetStringValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
			Output : 
				buffer - value buffer

   Returns: error code

   Description : Get string value

*****************************************************************/
int SettingsManager :: GetStringValue(WCHAR * regKey, WCHAR * regValue, char * buffer)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL) || (buffer == NULL))
		return ERROR_ACCESS_DENIED;
		
	HKEY hKey; 
	DWORD disp;

	// Open key for read
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	// Get value
	DWORD valueType = 0;
	DWORD tmpBufLen = STR_VALUE_LEN;
	WCHAR tmpBuf[STR_VALUE_LEN];
	errorRes = RegGetValue(hKey, NULL, regValue, RRF_RT_REG_SZ, &valueType, tmpBuf, &tmpBufLen);
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	// Close key
	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    	return errorRes;

	// Get buffer
	wcstombs(buffer, tmpBuf, tmpBufLen);

	return ERROR_SUCCESS;
}

/****************************************************************

   Class : SettingsManager

   Method : SetStringValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
				buffer - value buffer

   Returns: error code

   Description : Set string value

*****************************************************************/
int SettingsManager :: SetStringValue(WCHAR * regKey, WCHAR * regValue, char * buffer)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL) || (buffer == NULL))
		return ERROR_ACCESS_DENIED;
	
	HKEY hKey; 
	DWORD disp;

	// Open key for write
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	DWORD tmpBufLen = STR_VALUE_LEN;
	WCHAR tmpBuf[STR_VALUE_LEN];
	
	// Get buffer
	tmpBufLen = mbstowcs(tmpBuf, buffer, tmpBufLen);

	// Set value
	errorRes = RegSetValueEx(hKey, regValue, NULL, REG_SZ, (BYTE *)tmpBuf, tmpBufLen * sizeof(tmpBuf[0]));
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	// Close key
	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    	return errorRes;

	return ERROR_SUCCESS;
}

/****************************************************************

   Class : SettingsManager

   Method : GetEncStringValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
			Output : 
				buffer - value buffer

   Returns: error code

   Description : Get string value

*****************************************************************/
int SettingsManager :: GetEncStringValue(WCHAR * regKey, WCHAR * regValue, char * buffer)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL) || (buffer == NULL))
		return ERROR_ACCESS_DENIED;
		
	// Get encrypted data
	int encBufLen = MAX_DATA_BUFFER_LEN;
	unsigned char encBuf[MAX_DATA_BUFFER_LEN];
	int errorRes = GetEncStringValue(regKey, regValue, encBuf, &encBufLen);

	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	// Decrypt value
	unsigned char decBuf[STR_VALUE_LEN];
	int decBufLen;
	if (encryptor -> UnPackAndDecryptSecurityData(encBuf, encBufLen, decBuf, STR_VALUE_LEN, &decBufLen))
		return ERROR_ACCESS_DENIED;

	// Set value
	memcpy(buffer, decBuf, decBufLen);
	buffer[decBufLen] = 0;

	return ERROR_SUCCESS;
}

/****************************************************************

   Class : SettingsManager

   Method : SetEncStringValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
				buffer - value buffer

   Returns: error code

   Description : Set string value

*****************************************************************/
int SettingsManager :: SetEncStringValue(WCHAR * regKey, WCHAR * regValue, char * buffer)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL) || (buffer == NULL))
		return ERROR_ACCESS_DENIED;
	
	int bufLen = strlen(buffer);
	unsigned char packedData[MAX_DATA_BUFFER_LEN];
	int packedDataLen;

	unsigned char decBuf[STR_VALUE_LEN];
	memcpy(decBuf, buffer, bufLen);

	if (encryptor -> EncryptAndPackSecurityData((unsigned char*)decBuf, bufLen, packedData, MAX_DATA_BUFFER_LEN, &packedDataLen))
		return ERROR_ACCESS_DENIED;

	return SetEncStringValue(regKey, regValue, packedData, packedDataLen);
}

/****************************************************************

   Class : SettingsManager

   Method : GetEncStringValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
			Output : 
				buffer - value buffer
				buffSize - buffer size

   Returns: error code

   Description : Get string value

*****************************************************************/
int SettingsManager :: GetEncStringValue(WCHAR * regKey, WCHAR * regValue, unsigned char * buffer, int * buffSize)
{
	return GetBinaryValue(regKey, regValue, buffer, buffSize);
}

/****************************************************************

   Class : SettingsManager

   Method : SetEncStringValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
				buffer - value buffer
				buffSize - buffer size

   Returns: error code

   Description : Set string value

*****************************************************************/
int SettingsManager :: SetEncStringValue(WCHAR * regKey, WCHAR * regValue, unsigned char * buffer, int buffSize)
{
	return SetBinaryValue(regKey, regValue, buffer, buffSize);
}

/****************************************************************

   Class : SettingsManager

   Method : GetIntValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
			Output : 
				buffer - value buffer

   Returns: error code

   Description : Get integer value

*****************************************************************/
int SettingsManager :: GetIntValue(WCHAR * regKey, WCHAR * regValue, int * buffer)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL) || (buffer == NULL))
		return ERROR_ACCESS_DENIED;
		
	HKEY hKey; 
	DWORD disp;

	// Open key for read
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	// Get value
	DWORD valueType = 0;
	int tmpBuf = 0;
	DWORD tmpBufLen = sizeof(tmpBuf);
	errorRes = RegGetValue(hKey, NULL, regValue, RRF_RT_REG_DWORD, &valueType, &tmpBuf, &tmpBufLen);
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	// Set value
	*buffer = tmpBuf  + dllUserCheckResult;

	// Close key
	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    	return errorRes;

	return ERROR_SUCCESS;
}

/****************************************************************

   Class : SettingsManager

   Method : SetIntValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
				buffer - value buffer

   Returns: error code

   Description : Set integer value

*****************************************************************/
int SettingsManager :: SetIntValue(WCHAR * regKey, WCHAR * regValue, int buffer)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL))
		return ERROR_ACCESS_DENIED;
		
	HKEY hKey; 
	DWORD disp;

	// Open key for write
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	// Set value
	errorRes = RegSetValueEx(hKey, regValue, NULL, REG_DWORD, (BYTE *)&buffer, sizeof(buffer));
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	// Close key
	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    	return errorRes;

	return ERROR_SUCCESS;
}

/****************************************************************

   Class : SettingsManager

   Method : GetBoolValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
			Output : 
				buffer - value buffer

   Returns: error code

   Description : Get boolean value

*****************************************************************/
int SettingsManager :: GetBoolValue(WCHAR * regKey, WCHAR * regValue, bool * buffer)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL) || (buffer == NULL))
		return ERROR_ACCESS_DENIED;
		
	HKEY hKey; 
	DWORD disp;

	// Open key for read
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	// Get value
	DWORD valueType = 0;
	DWORD tmpBuf = 0;
	DWORD tmpBufLen = sizeof(tmpBuf);
	errorRes = RegGetValue(hKey, NULL, regValue, RRF_RT_REG_DWORD, &valueType, &tmpBuf, &tmpBufLen);
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	// Set value
	*buffer = (tmpBuf == 0) ? false : true;

	// Close key
	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    	return errorRes;

	return ERROR_SUCCESS;
}

/****************************************************************

   Class : SettingsManager

   Method : SetBoolValue

   Parameters :
			Input:
				regKey - registry key
				regValue - registry value
				buffer - value buffer

   Returns: error code

   Description : Set boolean value

*****************************************************************/
int SettingsManager :: SetBoolValue(WCHAR * regKey, WCHAR * regValue, bool buffer)
{
	// Check input data
	if ((regKey == NULL) || (regValue == NULL))
		return ERROR_ACCESS_DENIED;

	HKEY hKey; 
	DWORD disp;

	// Open key for write
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	// Set value
	DWORD tmpBuffer = (DWORD)buffer;
	errorRes = RegSetValueEx(hKey, regValue, NULL, REG_DWORD, (BYTE *)&tmpBuffer, sizeof(tmpBuffer));
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	// Close key
	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    	return errorRes;

	return ERROR_SUCCESS;
}

#pragma endregion

#pragma region Database settings

/****************************************************************

   Class : SettingsManager

   Method : GetDatabaseServerName

   Parameters :
			Output : 
				srv - database server name

   Returns: error code

   Description : Get database server name from windows registry

*****************************************************************/
int SettingsManager :: GetDatabaseServerName(char * srv)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\Database", L"SRV", srv);
}

/****************************************************************

   Class : SettingsManager

   Method : SetDatabaseServerName

   Parameters :
			Input : 
				srv - database server name

   Returns: error code

   Description : Set database server name to windows registry

*****************************************************************/
int SettingsManager :: SetDatabaseServerName(char * srv)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\Database", L"SRV", srv);
}

/****************************************************************

   Class : SettingsManager

   Method : GetDatabaseSourceName

   Parameters :
			Output : 
				dsn - data source name

   Returns: error code

   Description : Get database source name from windows registry

*****************************************************************/
int SettingsManager :: GetDatabaseSourceName(char * dsn)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\Database", L"DSN", dsn);
}

/****************************************************************

   Class : SettingsManager

   Method : SetDatabaseSourceName

   Parameters :
			Input : 
				dsn - data source name

   Returns: error code

   Description : Set database source name to windows registry

*****************************************************************/
int SettingsManager :: SetDatabaseSourceName(char * dsn)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\Database", L"DSN", dsn);
}

/****************************************************************

   Class : SettingsManager

   Method : GetDatabaseUserName

   Parameters :
			Output : 
				userName - db user name

   Returns: error code

   Description : Get database user name from windows registry

*****************************************************************/
int SettingsManager :: GetDatabaseUserName(char * userName)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\Database", L"USR", userName);
}

/****************************************************************

   Class : SettingsManager

   Method : SetDatabaseUserName

   Parameters :
			Input : 
				userName - db user name

   Returns: error code

   Description : Set database user name to windows registry

*****************************************************************/
int SettingsManager :: SetDatabaseUserName(char * userName)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\Database", L"USR", userName);
}

/****************************************************************

   Class : SettingsManager

   Method : GetDatabasePassword

   Parameters :
			Output : 
				pwd - database password

   Returns: error code

   Description : Get database password from windows registry

*****************************************************************/
int SettingsManager :: GetDatabasePassword(char * pwd)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\Database", L"PWD", pwd);
}

/****************************************************************

   Class : SettingsManager

   Method : SetDatabasePassword

   Parameters :
			Input : 
				pwd - database password

   Returns: error code

   Description : Set database password to windows registry

*****************************************************************/
int SettingsManager :: SetDatabasePassword(char * pwd)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\Database", L"PWD", pwd);
}

/****************************************************************

   Class : SettingsManager

   Method : GetDatabaseConnectionData

   Parameters :
			Output : 
				dbServerName - db server instance name
				dbServerNameLen - db server instance name length
				dbName - db name
				dbNameLen - db name length
				dbUserName - db user name
				dbUserNameLen - db user name length
				dbPassword - db password
				dbPasswordLen - db password length

   Returns: error code

   Description : Get DB acceess data

*****************************************************************/
int SettingsManager :: GetDatabaseConnectionData(unsigned char * dbServerName, int * dbServerNameLen,  unsigned char * dbName,	int * dbNameLen, unsigned char * dbUserName, int * dbUserNameLen, unsigned char * dbPassword, int * dbPasswordLen)
{
	// Check input data
	if ((dbServerName == NULL) ||
	   (dbServerNameLen == NULL) ||
	   (dbName == NULL) ||
	   (dbNameLen == NULL) ||
	   (dbUserName == NULL) ||
	   (dbUserNameLen == NULL) ||
	   (dbPassword == NULL) ||
	   (dbPasswordLen == NULL))
	   		return ERROR_ACCESS_DENIED;
	
	// Prepare registry key path
	WCHAR regPath[STR_VALUE_LEN] = L"SOFTWARE\\NovaTend\\Database";
	
	HKEY hKey; 
	DWORD disp;

	// Open key for read
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
		return errorRes;
	
	// Get value from registry
	DWORD valueType = 0;
	DWORD bufLen = MAX_DATA_BUFFER_LEN;
	unsigned char buf[MAX_DATA_BUFFER_LEN];

	errorRes = RegGetValue(hKey, NULL, L"SRV", RRF_RT_REG_BINARY, &valueType, buf, &bufLen);
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	memcpy(dbServerName, buf, bufLen);
	*dbServerNameLen = bufLen;

	bufLen = MAX_DATA_BUFFER_LEN;
	errorRes = RegGetValue(hKey, NULL, L"DSN", RRF_RT_REG_BINARY, &valueType, buf, &bufLen);
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	memcpy(dbName, buf, bufLen);
	*dbNameLen = bufLen;

	bufLen = MAX_DATA_BUFFER_LEN;
	errorRes = RegGetValue(hKey, NULL, L"USR", RRF_RT_REG_BINARY, &valueType, buf, &bufLen);
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	memcpy(dbUserName, buf, bufLen);
	*dbUserNameLen = bufLen;

	bufLen = MAX_DATA_BUFFER_LEN;
	errorRes = RegGetValue(hKey, NULL, L"PWD", RRF_RT_REG_BINARY, &valueType, buf, &bufLen);
	if(errorRes != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
    	return errorRes;
	}
	
	memcpy(dbPassword, buf, bufLen);
	*dbPasswordLen = bufLen;

	// Close registry key
	errorRes = RegCloseKey(hKey);
	if(errorRes != ERROR_SUCCESS)
    	return errorRes;
	
	return ERROR_SUCCESS;
}

#pragma endregion

#pragma region IPC settings

/****************************************************************

   Class : SettingsManager

   Method : GetServerDescriptionList

   Returns: pointer to server descriptor list

   Description : Get server description list from windows registry

*****************************************************************/
PSERVER_DESCRIPTION_LIST SettingsManager :: GetServerDescriptionList(void)
{
	// Prepare registry key path
	WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\IPC\\Alternative";
	
	HKEY hKey; 
	DWORD disp;

	// Open key for read
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	if(errorRes != ERROR_SUCCESS)
		return NULL;

	try
	{
		// Create list
		PSERVER_DESCRIPTION_LIST pServerList = (PSERVER_DESCRIPTION_LIST)malloc(sizeof(SERVER_DESCRIPTION_LIST));
	
		// Check result
		if(!pServerList)
		{
			RegCloseKey(hKey);
			return NULL;
		}

		pServerList -> serversCount = 0;
		DWORD count = 0;
		DWORD wcsServerNameLen;
		WCHAR wcsServerName[256];

		// Enumerate all subkeys
		do
		{
			wcsServerNameLen = 1024;
			errorRes = RegEnumKeyEx(hKey, count, wcsServerName, &wcsServerNameLen, 0, NULL, NULL, NULL);
			
			if (errorRes == ERROR_SUCCESS)
			{
				// Get server info
				PSERVER_DESCRIPTION pSrvDes = GetServerDescription(regPath, wcsServerName);

				if (pSrvDes)
				{
					if (pSrvDes -> serverType == SERVER_TYPE_HOST)
					{
						pServerList -> serversList[pServerList -> serversCount] = pSrvDes;
						pServerList -> serversCount++;
					}
					else
						free(pSrvDes);
				}
			}

			count++;
		} 
		while(errorRes != ERROR_NO_MORE_ITEMS);

		// Close key
		RegCloseKey(hKey);
		return pServerList + dllUserCheckResult;
	}
	catch(...)
	{
		return NULL;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : GetServerDescription

   Parameters :
			Input : 
				regPath - registry path
				serverIDname - server name

   Returns: pointer to server descriptor

   Description : Get server description from windows registry

*****************************************************************/
PSERVER_DESCRIPTION SettingsManager :: GetServerDescription(WCHAR * regPath, WCHAR * serverIDname)
{
	if ((regPath == NULL) || (serverIDname == NULL))
		return NULL;

	// Prepare registry key path
	WCHAR _regPath[256] = L"";

	try
	{
		// Prepare registry key path
		wcscpy(_regPath, regPath);
		wcscat(_regPath, L"\\");
		wcscat(_regPath, serverIDname);

		// Create server descriptor
		PSERVER_DESCRIPTION pServer = (PSERVER_DESCRIPTION)malloc(sizeof(SERVER_DESCRIPTION));

		// Check result
		if (!pServer) return NULL;
		
		// Get server ID
		int errorRes = GetIntValue(_regPath, L"SRVID", (int *)&(pServer -> serverID));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pServer);
			return NULL;
		}

		// Get server type
		errorRes = GetIntValue(_regPath, L"SRVTYPE", &(pServer -> serverType));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pServer);
			return NULL;
		}

		// Get server priority
		errorRes = GetIntValue(_regPath, L"SRVPRIOR", &(pServer -> serverPriority));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pServer);
			return NULL;
		}

		// Get server port
		errorRes = GetIntValue(_regPath, L"SRVPORT", (int *)&(pServer -> port));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pServer);
			return NULL;
		}

		// Get server IP address
		errorRes = GetStringValue(_regPath, L"SRVADR", pServer -> ipAddress);
		if(errorRes != ERROR_SUCCESS)
		{
			free(pServer);
			return NULL;
		}

		// Get server name
		errorRes = GetStringValue(_regPath, L"SRVNAME", pServer -> serverName);
		if(errorRes != ERROR_SUCCESS)
		{
			free(pServer);
			return NULL;
		}

		// Return pointer to server descriptor
		return pServer + dllUserCheckResult;
	}
	catch(...)
	{
		return NULL;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : SetServerDescription

   Parameters :
			Input : 
				regPath - registry path
				serverIDname - server key
				pServer - server description

   Returns: error code

   Description : Set server description to windows registry

*****************************************************************/
int SettingsManager :: SetServerDescription(WCHAR * regPath, WCHAR * serverIDname, PSERVER_DESCRIPTION pServer)
{
	// Check pointer to server descriptor
	if ((pServer == NULL) || (regPath == NULL) || (serverIDname == NULL))
		return ERROR_ACCESS_DENIED;
	
	// Prepare registry key path
	WCHAR _regPath[256] = L"";

	try
	{
		// Prepare registry key path
		wcscpy(_regPath, regPath);
		wcscat(_regPath, L"\\");
		wcscat(_regPath, serverIDname);

		// Set server ID	
		int errorRes = SetIntValue(_regPath, L"SRVID", pServer -> serverID);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;
		
		// Set server type
		errorRes = SetIntValue(_regPath, L"SRVTYPE", pServer -> serverType);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set server priority
		errorRes = SetIntValue(_regPath, L"SRVPRIOR", pServer -> serverPriority);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;
		
		// Set server port
		errorRes = SetIntValue(_regPath, L"SRVPORT", pServer -> port);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set server address
		errorRes = SetStringValue(_regPath, L"SRVADR", pServer -> ipAddress);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set server name
		errorRes = SetStringValue(_regPath, L"SRVNAME", pServer -> serverName);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		return ERROR_SUCCESS;
	}
	catch(...)
	{
		return ERROR_ACCESS_DENIED;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : GetHostServer

   Returns: pointer to server descriptor

   Description : Get HOST-server description from windows registry

*****************************************************************/
PSERVER_DESCRIPTION SettingsManager :: GetHostServer(void)
{
	return GetServerDescription(L"SOFTWARE\\NovaTend\\IPC", L"HOST");
}

/****************************************************************

   Class : SettingsManager

   Method : GetGlobalServer

   Returns: pointer to server descriptor

   Description : Get GLOBAL-server description from windows registry

*****************************************************************/
PSERVER_DESCRIPTION SettingsManager :: GetGlobalServer(void)
{
	return GetServerDescription(L"SOFTWARE\\NovaTend\\IPC", L"GLOBAL");
}

/****************************************************************

   Class : SettingsManager

   Method : GetHubServer

   Returns: pointer to server descriptor

   Description : Get HUB-server description from windows registry

*****************************************************************/
PSERVER_DESCRIPTION SettingsManager :: GetHubServer(void)
{
	return GetServerDescription(L"SOFTWARE\\NovaTend\\IPC", L"HUB");
}

/****************************************************************

   Class : SettingsManager

   Method : GetDesktopServer

   Returns: pointer to server descriptor

   Description : Get DESKTOP-server description from windows registry

*****************************************************************/
PSERVER_DESCRIPTION SettingsManager :: GetDesktopServer(void)
{
	return GetServerDescription(L"SOFTWARE\\NovaTend\\IPC", L"DESKTOP");
}

/****************************************************************

   Class : SettingsManager

   Method : GetHostServerStartingFlag

   Returns: starting flag

   Description :  Get HOST-server starting flag

*****************************************************************/
bool SettingsManager :: GetHostServerStartingFlag(void)
{
	bool flag = false;
	if (GetBoolValue(L"SOFTWARE\\NovaTend\\IPC\\HOST", L"START", &flag) == ERROR_SUCCESS)
		return flag;
	else
		return false;
}

/****************************************************************

   Class : SettingsManager

   Method : SetHostServerStartingFlag

   Parameters:
			Input:
				value - staeting flag value

   Returns: error code

   Description :  Set HOST-server starting flag

*****************************************************************/
int SettingsManager :: SetHostServerStartingFlag(bool value)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\IPC\\HOST", L"START", value);
}

/****************************************************************

   Class : SettingsManager

   Method : GetHubServerStartingFlag

   Returns: starting flag

   Description :  Get HUB-server starting flag

*****************************************************************/
bool SettingsManager :: GetHubServerStartingFlag(void)
{
	bool flag = false;
	if (GetBoolValue(L"SOFTWARE\\NovaTend\\IPC\\HUB", L"START", &flag) == ERROR_SUCCESS)
		return flag;
	else
		return false;
}

/****************************************************************

   Class : SettingsManager

   Method : SetHubServerStartingFlag

   Parameters:
			Input:
				value - staeting flag value

   Returns: error code

   Description :  Set HUB-server starting flag

*****************************************************************/
int SettingsManager :: SetHubServerStartingFlag(bool value)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\IPC\\HUB", L"START", value);
}

/****************************************************************

   Class : SettingsManager

   Method : GetDesktopServerStartingFlag

   Returns: starting flag

   Description :  Get DESKTOP-server starting flag

*****************************************************************/
bool SettingsManager :: GetDesktopServerStartingFlag(void)
{
	bool flag = false;
	if (GetBoolValue(L"SOFTWARE\\NovaTend\\IPC\\DESKTOP", L"START", &flag) == ERROR_SUCCESS)
		return flag;
	else
		return false;
}

/****************************************************************

   Class : SettingsManager

   Method : SetDesktopServerStartingFlag

   Parameters:
			Input:
				value - staeting flag value

   Returns: error code

   Description :  Set DESKTOP-server starting flag

*****************************************************************/
int SettingsManager :: SetDesktopServerStartingFlag(bool value)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\IPC\\DESKTOP", L"START", value);
}

#pragma endregion

#pragma region E-Mail settings

/****************************************************************

   Class : SettingsManager

   Method : GetEmailHost

   Parameters :
			Output : 
				host - host address string

   Returns: error code

   Description : Get e-mail host address from windows registry

*****************************************************************/
int SettingsManager :: GetEmailHost(char * host)
{
	return GetStringValue(L"SOFTWARE\\NovaTend\\EMail", L"HOST", host);
}

/****************************************************************

   Class : SettingsManager

   Method : SetEmailHost

   Parameters :
			Input : 
				address - host address string

   Returns: error code

   Description : Set e-mail host address to windows registry

*****************************************************************/
int SettingsManager :: SetEmailHost(char * host)
{
	return SetStringValue(L"SOFTWARE\\NovaTend\\EMail", L"HOST", host);
}

/****************************************************************

   Class : SettingsManager

   Method : GetEmailPort

   Parameters :
			Output : 
				port - port number

   Returns: error code

   Description : Get e-mail server port from windows registry

*****************************************************************/
int SettingsManager :: GetEmailPort(unsigned int * port)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\EMail", L"PORT", (int *)port);
}

/****************************************************************

   Class : SettingsManager

   Method : SetEmailPort

   Parameters :
			Input : 
				port - port number

   Returns: error code

   Description : Set e-mail server port to windows registry

*****************************************************************/
int SettingsManager :: SetEmailPort(unsigned int port)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\EMail", L"PORT", port);
}

/****************************************************************

   Class : SettingsManager

   Method : GetEmailSecurityType

   Parameters :
			Output : 
				secType - security type

   Returns: error code

   Description : Get e-mail security type from windows registry

*****************************************************************/
int SettingsManager :: GetEmailSecurityType(unsigned int * secType)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\EMail", L"SECTYPE", (int *)secType);
}

/****************************************************************

   Class : SettingsManager

   Method : SetEmailSecurityType

   Parameters :
			Input : 
				secType - security type

   Returns: error code

   Description : Set e-mail security type to windows registry

*****************************************************************/
int SettingsManager :: SetEmailSecurityType(unsigned int secType)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\EMail", L"SECTYPE", secType);
}

/****************************************************************

   Class : SettingsManager

   Method : GetEmailAuthFlag

   Parameters :
			Output : 
				auth - authentication flag

   Returns: error code

   Description : Get e-mail authentication flag from windows registry

*****************************************************************/
int SettingsManager :: GetEmailAuthFlag(bool * auth)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\EMail", L"AUTH", auth);
}

/****************************************************************

   Class : SettingsManager

   Method : SetEmailAuthFlag

   Parameters :
			Input : 
				auth - authentication flag

   Returns: error code

   Description : Set e-mail authentication flag to windows registry

*****************************************************************/
int SettingsManager :: SetEmailAuthFlag(bool  auth)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\EMail", L"AUTH", auth);
}

/****************************************************************

   Class : SettingsManager

   Method : GetEmailLogin

   Parameters :
			Output : 
				login - e-mail login

   Returns: error code

   Description : Get e-mail login from windows registry

*****************************************************************/
int SettingsManager :: GetEmailLogin(char * login)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\EMail", L"LOGIN", login);
}

/****************************************************************

   Class : SettingsManager

   Method : SetEmailLogin

   Parameters :
			Input : 
				login - e-mail login

   Returns: error code

   Description : Set e-mail login to windows registry

*****************************************************************/
int SettingsManager :: SetEmailLogin(char * login)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\EMail", L"LOGIN", login);
}

/****************************************************************

   Class : SettingsManager

   Method : GetEmailPassword

   Parameters :
			Output : 
				password - e-mail password

   Returns: error code

   Description : Get e-mail password from windows registry

*****************************************************************/
int SettingsManager :: GetEmailPassword(char * password)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\EMail", L"PASSWORD", password);
}

/****************************************************************

   Class : SettingsManager

   Method : SetEmailPassword

   Parameters :
			Input : 
				password - e-mail password

   Returns: error code

   Description : Set e-mail password to windows registry

*****************************************************************/
int SettingsManager :: SetEmailPassword(char * password)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\EMail", L"PASSWORD", password);
}

/****************************************************************

   Class : SettingsManager

   Method : GetEmailSenderAddress

   Parameters :
			Output : 
				sender - sender address

   Returns: error code

   Description : Get e-mail sender address from windows registry

*****************************************************************/
int SettingsManager :: GetEmailSenderAddress(char * sender)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\EMail", L"SENDER", sender);
}

/****************************************************************

   Class : SettingsManager

   Method : SetEmailSenderAddress

   Parameters :
			Input : 
				sender - sender address

   Returns: error code

   Description : Set e-mail sender address to windows registry

*****************************************************************/
int SettingsManager :: SetEmailSenderAddress(char * sender)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\EMail", L"SENDER", sender);
}

/****************************************************************

   Class : SettingsManager

   Method : GetEmailRecipientAddress

   Parameters :
			Output : 
				recipient - recipient address

   Returns: error code

   Description : Get e-mail recipient address from windows registry

*****************************************************************/
int SettingsManager :: GetEmailRecipientAddress(char * recipient)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\EMail", L"RECIPIENT", recipient);
}

/****************************************************************

   Class : SettingsManager

   Method : SetEmailRecipientAddress

   Parameters :
			Input : 
				recipient - recipient address

   Returns: error code

   Description : Set e-mail recipient address to windows registry

*****************************************************************/
int SettingsManager :: SetEmailRecipientAddress(char * recipient)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\EMail", L"RECIPIENT", recipient);
}

#pragma endregion

#pragma region Google Voice

/****************************************************************

   Class : SettingsManager

   Method : GetGoogleVoiceLogin

   Parameters :
			Output : 
				gvoiceEmail - google voice user email

   Returns: error code

   Description : Get google voice login

*****************************************************************/
int SettingsManager :: GetGoogleVoiceLogin(char * gvoiceEmail)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\SMS", L"LOGIN", gvoiceEmail);
}

/****************************************************************

   Class : SettingsManager

   Method : SetGoogleVoiceLogin

   Parameters :
			Input : 
				gvoiceEmail - google voice user email

   Returns: error code

   Description : Set google voice login

*****************************************************************/
int SettingsManager :: SetGoogleVoiceLogin(char * gvoiceEmail)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\SMS", L"LOGIN", gvoiceEmail);
}

/****************************************************************

   Class : SettingsManager

   Method : GetGoogleVoicePassword

   Parameters :
			Output : 
				password - google voice user password

   Returns: error code

   Description : Get google voice password

*****************************************************************/
int SettingsManager :: GetGoogleVoicePassword(char * password)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\SMS", L"PWD", password);
}

/****************************************************************

   Class : SettingsManager

   Method : SetGoogleVoicePassword

   Parameters :
			Input : 
				password - google voice user password

   Returns: error code

   Description : Set google voice password

*****************************************************************/
int SettingsManager :: SetGoogleVoicePassword(char * password)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\SMS", L"PWD", password);
}

#pragma endregion

#pragma region LOG-file settings

/****************************************************************

   Class : SettingsManager

   Method : GetLogEncryptFlag

   Parameters :
			Output : 
				logEnc - LOG-files encryption flag

   Returns: error code

   Description : Get LOG-files encryption flag from windows registry

*****************************************************************/
int SettingsManager :: GetLogEncryptFlag(bool * logEnc)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\LOG", L"ENC", logEnc);
}

/****************************************************************

   Class : SettingsManager

   Method : SetLogEncryptFlag

   Parameters :
			Input : 
				logEnc - LOG-files encryption flag

   Returns: error code

   Description : Set LOG-files encryption flag to windows registry

*****************************************************************/
int SettingsManager :: SetLogEncryptFlag(bool  logEnc)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\LOG", L"ENC", logEnc);
}

/****************************************************************

   Class : SettingsManager

   Method : GetLogEmailSendFlag

   Parameters :
			Output : 
				eMail - e-mail sending flag

   Returns: error code

   Description : Get LOG-files messages e-mail sending flag from windows registry

*****************************************************************/
int SettingsManager :: GetLogEmailSendFlag(bool * eMail)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\LOG", L"EMAIL", eMail);
}

/****************************************************************

   Class : SettingsManager

   Method : SetLogEmailSendFlag

   Parameters :
			Input : 
				eMail - e-mail sending flag

   Returns: error code

   Description : Set LOG-files messages e-mail sending flag to windows registry

*****************************************************************/
int SettingsManager :: SetLogEmailSendFlag(bool  eMail)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\LOG", L"EMAIL", eMail);
}

/****************************************************************

   Class : SettingsManager

   Method : GetLogFixedSizeFlag

   Parameters :
			Output : 
				logFix - log-file fixed size flag

   Returns: error code

   Description : Get LOG-files fixed size flag from Windows registry

*****************************************************************/
int SettingsManager :: GetLogFixedSizeFlag(bool * logFix)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\LOG", L"FIXED", logFix);
}

/****************************************************************

   Class : SettingsManager

   Method : SetLogFixedSizeFlag

   Parameters :
			Input : 
				logFix - log-file fixed size flag

   Returns: error code

   Description : Set LOG-files fixed size flag to Windows registry

*****************************************************************/
int SettingsManager :: SetLogFixedSizeFlag(bool  logFix)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\LOG", L"FIXED", logFix);
}

/****************************************************************

   Class : SettingsManager

   Method : GetLogFixedSizeValue

   Parameters :
			Output : 
				logFixVal - log-file fixed size value

   Returns: error code

   Description : Get LOG-files fixed size value from Windows registry

*****************************************************************/
int SettingsManager :: GetLogFixedSizeValue(int * logFixVal)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\LOG", L"FIXED_SIZE", logFixVal);
}

/****************************************************************

   Class : SettingsManager

   Method : SetLogFixedSizeValue

   Parameters :
			Input : 
				logFixVal - log-file fixed size value

   Returns: error code

   Description : Set LOG-files fixed size value to Windows registry

*****************************************************************/
int SettingsManager :: SetLogFixedSizeValue(int  logFixVal)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\LOG", L"FIXED_SIZE", logFixVal);
}

/****************************************************************

   Class : SettingsManager

   Method : GetLogPath

   Parameters :
			Output : 
				logPath - LOG-files storing path

   Returns: error code

   Description : Get LOG-files storing path

*****************************************************************/
int SettingsManager :: GetLogPath(char * logPath)
{
	return GetStringValue(L"SOFTWARE\\NovaTend\\LOG", L"LOG_PATH", logPath);
}

/****************************************************************

   Class : SettingsManager

   Method : SetLogPath

   Parameters :
			Input : 
				logPath - LOG-files storing path

   Returns: error code

   Description : Set LOG-files storing path

*****************************************************************/
int SettingsManager :: SetLogPath(char * logPath)
{
	return SetStringValue(L"SOFTWARE\\NovaTend\\LOG", L"LOG_PATH", logPath);
}

#pragma endregion

#pragma region Synchronization

/****************************************************************

   Class : SettingsManager

   Method : GetPeriodicSyncOnOffFlag

   Parameters :
			Output : 
				syncFlag - periodic synchronization flag

   Returns: error code

   Description : Get periodic user accounts synchronization on/off flag

*****************************************************************/
int SettingsManager :: GetPeriodicSyncOnOffFlag(bool *syncFlag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\Sync", L"PERIODON", syncFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetPeriodicSyncOnOffFlag

   Parameters :
			Input : 
				syncFlag - periodic synchronization flag

   Returns: error code

   Description : Set periodic user accounts synchronization on/off flag

*****************************************************************/
int SettingsManager :: SetPeriodicSyncOnOffFlag(bool syncFlag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\Sync", L"PERIODON", syncFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : GetLogonSyncOnOffFlag

   Parameters :
			Output : 
				syncFlag - periodic synchronization flag

   Returns: error code

   Description : Get logon user accounts synchronization on/off flag

*****************************************************************/
int SettingsManager :: GetLogonSyncOnOffFlag(bool * syncFlag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\Sync", L"LOGON", syncFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetLogonSyncOnOffFlag

   Parameters :
			Input : 
				syncFlag - periodic synchronization flag

   Returns: error code

   Description : Set logon user accounts synchronization on/off flag

*****************************************************************/
int SettingsManager :: SetLogonSyncOnOffFlag(bool syncFlag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\Sync", L"LOGON", syncFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : GetSyncPeriod

   Parameters :
			Output : 
				period - synchronization period

   Returns: error code

   Description : Get synchronization period

*****************************************************************/
int SettingsManager :: GetSyncPeriod(int * period)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\Sync", L"PERIOD", period);
}

/****************************************************************

   Class : SettingsManager

   Method : SetSyncPeriod

   Parameters :
			Input : 
				period - synchronization period

   Returns: error code

   Description : Set synchronization period

*****************************************************************/
int SettingsManager :: SetSyncPeriod(int period)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\Sync", L"PERIOD", period);
}

/****************************************************************

   Class : SettingsManager

   Method : GetLastSyncTime

   Parameters :
			Output : 
				lastSyncTime - last synchronization time buffer

   Returns: error code

   Description : Get last sync time

*****************************************************************/
int SettingsManager :: GetLastSyncTime(char * lastSyncTime)
{
	return GetStringValue(L"SOFTWARE\\NovaTend\\Sync", L"LASTSYNC", lastSyncTime);
}

/****************************************************************

   Class : SettingsManager

   Method : SetLastSyncTime

   Parameters :
			Input : 
				lastSyncTime - last synchronization time buffer

   Returns: error code

   Description : Set last sync time

*****************************************************************/
int SettingsManager :: SetLastSyncTime(char * lastSyncTime)
{
	return SetStringValue(L"SOFTWARE\\NovaTend\\Sync", L"LASTSYNC", lastSyncTime);
}

#pragma endregion

#pragma region Local users settings

/****************************************************************

   Class : SettingsManager

   Method : SetLocalUser

   Parameters :
			Input : 
				pUser - pointer to user descriptor

   Returns: error code

   Description : Set info about local user to windows registry

*****************************************************************/
int SettingsManager :: SetLocalUser(PUSER_DESCRIPTOR pUser)
{
	// Check pointer to user descriptor
	if (pUser == NULL)
		return ERROR_ACCESS_DENIED;

	try
	{
		// Prepare registry key path
		WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\Users\\";
		WCHAR userIDBuffer[16];

		_itow(pUser -> userID, userIDBuffer, 10);
		wcscat(regPath, L"U");
		wcscat(regPath, userIDBuffer);
		
		// Set user ID	
		int errorRes = SetIntValue(regPath, L"ID", pUser -> userID);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;
		
		// Set user password type
		errorRes = SetIntValue(regPath, L"PTYPE", pUser -> pwdType);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set user password attempts count
		errorRes = SetIntValue(regPath, L"PACNT", pUser -> pwdAttemptsCount);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set user name
		errorRes = SetEncStringValue(regPath, L"UNM", pUser -> encUserName, pUser -> encUserNameLen);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;
		
		// Set password reseted flag
		errorRes = SetBoolValue(regPath, L"PRES", pUser -> pwdReseted);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set password reset period
		errorRes = SetIntValue(regPath, L"RESPER", pUser -> pwdResetPeriod);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;
	
		// Set reset date
		errorRes = SetStringValue(regPath, L"RESD", pUser -> pwdResetDate);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		return ERROR_SUCCESS;
	}
	catch(...)
	{
		return ERROR_ACCESS_DENIED;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : SetUserSecurityData

   Parameters :
			Input : 
				pSecurityData - pointer to user security 
								data structure

   Returns: error code

   Description : Set user security data to windows registry

*****************************************************************/
int SettingsManager :: SetUserSecurityData(PUSER_SECURITY_DATA pSecurityData)
{
	// Check pointer to user security data structure
	if (pSecurityData == NULL)
		return ERROR_ACCESS_DENIED;

	try
	{
		// Prepare registry key path
		WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\Users\\";
		WCHAR userIDBuffer[16];

		_itow(pSecurityData -> userID, userIDBuffer, 10);
		wcscat(regPath, L"U");
		wcscat(regPath, userIDBuffer);
		
		// Set user tocken
		int errorRes = SetIntValue(regPath, L"TCKN", pSecurityData -> userToken);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set temp user tocken
		errorRes = SetIntValue(regPath, L"TTCKN", pSecurityData -> tmpUserToken);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set system user name
		errorRes = SetEncStringValue(regPath, L"UNMSYS", pSecurityData -> encSystemUserName, pSecurityData -> encSystemUserNameLen);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set user system password
		errorRes = SetEncStringValue(regPath, L"WSUP", pSecurityData -> encSystemPassword, pSecurityData -> encSystemPasswordLen);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;
		

		switch (pSecurityData -> pwdType)
		{
			case CASCADE_STRING_PWD :
				{
					// Set user password construction rules count
					errorRes = SetIntValue(regPath, L"UBRCNT", pSecurityData -> pwdConstRulesCount);
					if (errorRes != ERROR_SUCCESS)
						return errorRes;
		
					if (pSecurityData -> pwdConstRulesCount == 1)
					{
						// Set user password construction rules
						errorRes = SetIntValue(regPath, L"UBR1", pSecurityData -> pwdConstRules[0]);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}

					if (pSecurityData -> pwdConstRulesCount > 1)
					{
						// Set user password construction rules
						errorRes = SetIntValue(regPath, L"UBR1", pSecurityData -> pwdConstRules[0]);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;

						errorRes = SetIntValue(regPath, L"UBR2", pSecurityData -> pwdConstRules[1]);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}

					// Set temp user password construction rules count
					errorRes = SetIntValue(regPath, L"TUBRCNT", pSecurityData -> tmpPwdConstRulesCount);
					if (errorRes != ERROR_SUCCESS)
						return errorRes;
		
					if (pSecurityData -> tmpPwdConstRulesCount == 1)
					{
						// Set temp user password construction rules
						errorRes = SetIntValue(regPath, L"TUBR1", pSecurityData -> tmpPwdConstRules[0]);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}

					if (pSecurityData -> tmpPwdConstRulesCount > 1)
					{
						// Set temp user password construction rules
						errorRes = SetIntValue(regPath, L"TUBR1", pSecurityData -> tmpPwdConstRules[0]);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;

						errorRes = SetIntValue(regPath, L"TUBR2", pSecurityData -> tmpPwdConstRules[1]);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}

					break;
				}

			case ONE_SYMBOL_BOX_PWD :
				{
					// Set user password construction rules count
					errorRes = SetIntValue(regPath, L"UBRCNT", pSecurityData -> pwdConstRulesCount);
					if (errorRes != ERROR_SUCCESS)
						return errorRes;
		
					// Find and save symbol location
					int ruleID = -1;
					bool found = false;
					for(int i = 0; i < pSecurityData -> pwdConstRulesCount; i++)
						if ((pSecurityData -> pwdConstRules[i] >= ONE_SYM_PWD_SYMBOL_LOCATION_MIN) && (pSecurityData -> pwdConstRules[i] <= ONE_SYM_PWD_SYMBOL_LOCATION_MAX))
						{
							found = true;
							ruleID = pSecurityData -> pwdConstRules[i];
							break;
						}

					if (found)
					{
						errorRes = SetIntValue(regPath, L"UBR1", ruleID);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;

						errorRes = SetIntValue(regPath, L"UBR2", ruleID);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}
			

					// Set temp user password construction rules count
					errorRes = SetIntValue(regPath, L"TUBRCNT", pSecurityData -> tmpPwdConstRulesCount);
					if (errorRes != ERROR_SUCCESS)
						return errorRes;
						
					// Find and save symbol location
					ruleID = -1;
					found = false;
					for(int i = 0; i < pSecurityData -> tmpPwdConstRulesCount; i++)
						if ((pSecurityData -> tmpPwdConstRules[i] >= ONE_SYM_PWD_SYMBOL_LOCATION_MIN) && (pSecurityData -> tmpPwdConstRules[i] <= ONE_SYM_PWD_SYMBOL_LOCATION_MAX))
						{
							found = true;
							ruleID = pSecurityData -> tmpPwdConstRules[i];
							break;
						}

					if(found)
					{
						errorRes = SetIntValue(regPath, L"TUBR1", ruleID);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;

						errorRes = SetIntValue(regPath, L"TUBR2", ruleID);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}
					break;
				}

			case TWO_SYMBOL_BOX_PWD :
				{
					// Set user password construction rules count
					errorRes = SetIntValue(regPath, L"UBRCNT", pSecurityData -> pwdConstRulesCount);
					if (errorRes != ERROR_SUCCESS)
						return errorRes;
		
					// Find and save pair location
					int ruleID = -1;
					bool found = false;
					for(int i = 0; i < pSecurityData -> pwdConstRulesCount; i++)
						if ((pSecurityData -> pwdConstRules[i] >= TWO_SYM_PWD_PAIR_LOCATION_MIN) && (pSecurityData -> pwdConstRules[i] <= TWO_SYM_PWD_PAIR_LOCATION_MAX))
						{
							found = true;
							ruleID = pSecurityData -> pwdConstRules[i];
							break;
						}

					if(found)
					{
						errorRes = SetIntValue(regPath, L"UBR1", ruleID);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}

					// Find and save symbol location
					ruleID = -1;
					found = false;
					for(int i = 0; i < pSecurityData -> pwdConstRulesCount; i++)
						if ((pSecurityData -> pwdConstRules[i] >= TWO_SYM_PWD_SYMBOL_LOCATION_MIN) && (pSecurityData -> pwdConstRules[i] <= TWO_SYM_PWD_SYMBOL_LOCATION_MAX))
						{
							found = true;
							ruleID = pSecurityData -> pwdConstRules[i];
							break;
						}

					if (found)
					{
						errorRes = SetIntValue(regPath, L"UBR2", ruleID);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}
			

					// Set temp user password construction rules count
					errorRes = SetIntValue(regPath, L"TUBRCNT", pSecurityData -> tmpPwdConstRulesCount);
					if (errorRes != ERROR_SUCCESS)
						return errorRes;

					// Find and save pair location
					ruleID = -1;
					found = false;
					for(int i = 0; i < pSecurityData -> tmpPwdConstRulesCount; i++)
						if ((pSecurityData -> tmpPwdConstRules[i] >= TWO_SYM_PWD_PAIR_LOCATION_MIN) && (pSecurityData -> tmpPwdConstRules[i] <= TWO_SYM_PWD_PAIR_LOCATION_MAX))
						{
							found = true;
							ruleID = pSecurityData -> tmpPwdConstRules[i];
							break;
						}

					if(found)
					{
						errorRes = SetIntValue(regPath, L"TUBR1", ruleID);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}

					// Find and save symbol location
					ruleID = -1;
					found = false;
					for(int i = 0; i < pSecurityData -> tmpPwdConstRulesCount; i++)
						if ((pSecurityData -> tmpPwdConstRules[i] >= TWO_SYM_PWD_SYMBOL_LOCATION_MIN) && (pSecurityData -> tmpPwdConstRules[i] <= TWO_SYM_PWD_SYMBOL_LOCATION_MAX))
						{
							found = true;
							ruleID = pSecurityData -> tmpPwdConstRules[i];
							break;
						}

					if(found)
					{
						errorRes = SetIntValue(regPath, L"TUBR2", ruleID);
						if (errorRes != ERROR_SUCCESS)
							return errorRes;
					}
					break;
				}

		}
		
				
		// Set user pass thru flag
		errorRes = SetBoolValue(regPath, L"PSTR", pSecurityData -> passThru);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		return ERROR_SUCCESS;
	}
	catch(...)
	{
		return ERROR_ACCESS_DENIED;
	}

}

/****************************************************************

   Class : SettingsManager

   Method : GetLocalUser

   Parameters :
			Input : 
				userName - user name

   Returns: pointer to user descriptor

   Description : Get info about local user from windows registry

*****************************************************************/
PUSER_DESCRIPTOR SettingsManager :: GetLocalUser(int userID)
{
	try
	{
		// Prepare registry key path
		WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\Users\\";
		WCHAR userIDBuffer[16];

		_itow(userID, userIDBuffer, 10);
		wcscat(regPath, L"U");
		wcscat(regPath, userIDBuffer);
						
		// Create user descriptor
		PUSER_DESCRIPTOR pUser = (PUSER_DESCRIPTOR)malloc(sizeof(USER_DESCRIPTOR));

		// Check result
		if (!pUser)	return NULL;
		
		// Get user ID
		int errorRes = GetIntValue(regPath, L"ID", &(pUser -> userID));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pUser);
			return NULL;
		}

		// Get user password type
		errorRes = GetIntValue(regPath, L"PTYPE", &(pUser -> pwdType));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pUser);
			return NULL;
		}

		// Get user password attempts count
		errorRes = GetIntValue(regPath, L"PACNT", &(pUser -> pwdAttemptsCount));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pUser);
			return NULL;
		}
				
		// Get user name
		errorRes = GetEncStringValue(regPath, L"UNM", pUser -> encUserName, &(pUser -> encUserNameLen));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pUser);
			return NULL;
		}
				
		// Get password reseted flag
		errorRes = GetBoolValue(regPath, L"PRES", &(pUser -> pwdReseted));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pUser);
			return NULL;
		}

		// Get password reset period
		errorRes = GetIntValue(regPath, L"RESPER", &(pUser -> pwdResetPeriod));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pUser);
			return NULL;
		}

		// Get reset date
		errorRes = GetStringValue(regPath, L"RESD", pUser -> pwdResetDate);
		if(errorRes != ERROR_SUCCESS)
		{
			free(pUser);
			return NULL;
		}
				
		// Fill rest fields
		pUser -> maxPwdAttemptsCount = 20;
		pUser -> eduCategotyID = -1;
		pUser -> eduQuestionRandom = false;
		pUser -> lastLogOnDate[0] = '\0';
		pUser -> needStudy = false;
		pUser -> randomEduCateg = false;
		pUser -> locked = false;
		pUser -> emailPwdReset = false;
		pUser -> smsPwdReset = false;
		pUser -> encEmailAddressLen = 0;
		pUser -> encEmailAddress[0] = '\0';
		pUser -> encPhoneNumberLen = 0;
		pUser -> encPhoneNumber[0] = '\0';
		pUser -> encNameLen = 0;
		pUser -> encName[0] = '\0';

		// Return pointer to user descriptor
		return pUser + dllUserCheckResult;
	}
	catch(...)
	{
		return NULL;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : GetUserSecurityData

   Parameters :
			Input : 
				userID - user ID

   Returns: pointer to user security data structure

   Description : Get user security data from windows registry

*****************************************************************/
PUSER_SECURITY_DATA SettingsManager :: GetUserSecurityData(int userID)
{
	try
	{
		// Prepare registry key path
		WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\Users\\";
		WCHAR userIDBuffer[16];

		_itow(userID, userIDBuffer, 10);
		wcscat(regPath, L"U");
		wcscat(regPath, userIDBuffer);
						
		// Create user descriptor
		PUSER_SECURITY_DATA pSecurityData = (PUSER_SECURITY_DATA)malloc(sizeof(USER_SECURITY_DATA));

		// Check result
		if (!pSecurityData)	return NULL;
		
		// Get user ID
		int errorRes = GetIntValue(regPath, L"ID", &(pSecurityData -> userID));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pSecurityData);
			return NULL;
		}

		// Get user password type
		errorRes = GetIntValue(regPath, L"PTYPE", &(pSecurityData -> pwdType));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pSecurityData);
			return NULL;
		}

		// Get user tocken
		errorRes = GetIntValue(regPath, L"TCKN", &(pSecurityData -> userToken));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pSecurityData);
			return NULL;
		}

		// Get user temp tocken
		errorRes = GetIntValue(regPath, L"TTCKN", &(pSecurityData -> tmpUserToken));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pSecurityData);
			return NULL;
		}
		
		
		// Get system user name
		errorRes = GetEncStringValue(regPath, L"UNMSYS", pSecurityData -> encSystemUserName, &(pSecurityData -> encSystemUserNameLen));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pSecurityData);
			return NULL;
		}

		// Get user system password
		errorRes = GetEncStringValue(regPath, L"WSUP", pSecurityData -> encSystemPassword, &(pSecurityData -> encSystemPasswordLen));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pSecurityData);
			return NULL;
		}
		
		// Get user construction rules count
		errorRes = GetIntValue(regPath, L"UBRCNT", &(pSecurityData -> pwdConstRulesCount));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pSecurityData);
			return NULL;
		}
				
		// Get user password construction rules 
		if (pSecurityData -> pwdConstRulesCount == 1)
		{
			errorRes = GetIntValue(regPath, L"UBR1", &(pSecurityData -> pwdConstRules[0]));
			if(errorRes != ERROR_SUCCESS)
			{
				free(pSecurityData);
				return NULL;
			}
			
			pSecurityData -> pwdConstRulesCount = 1;
		}

		if (pSecurityData -> pwdConstRulesCount > 1)
		{
			errorRes = GetIntValue(regPath, L"UBR1", &(pSecurityData -> pwdConstRules[0]));
			if(errorRes != ERROR_SUCCESS)
			{
				free(pSecurityData);
				return NULL;
			}
	
			errorRes = GetIntValue(regPath, L"UBR2", &(pSecurityData -> pwdConstRules[1]));
			if(errorRes != ERROR_SUCCESS)
			{
				free(pSecurityData);
				return NULL;
			}

			pSecurityData -> pwdConstRulesCount = 2;
		}

		// Get temp user construction rules count
		errorRes = GetIntValue(regPath, L"TUBRCNT", &(pSecurityData -> tmpPwdConstRulesCount));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pSecurityData);
			return NULL;
		}
				
		// Get temp user password construction rules 
		if (pSecurityData -> tmpPwdConstRulesCount == 1)
		{
			errorRes = GetIntValue(regPath, L"TUBR1", &(pSecurityData -> tmpPwdConstRules[0]));
			if(errorRes != ERROR_SUCCESS)
			{
				free(pSecurityData);
				return NULL;
			}
			
			pSecurityData -> tmpPwdConstRulesCount = 1;
		}

		if (pSecurityData -> tmpPwdConstRulesCount > 1)
		{
			errorRes = GetIntValue(regPath, L"TUBR1", &(pSecurityData -> tmpPwdConstRules[0]));
			if(errorRes != ERROR_SUCCESS)
			{
				free(pSecurityData);
				return NULL;
			}

			errorRes = GetIntValue(regPath, L"TUBR2", &(pSecurityData -> tmpPwdConstRules[1]));
			if(errorRes != ERROR_SUCCESS)
			{
				free(pSecurityData);
				return NULL;
			}
			
			pSecurityData -> tmpPwdConstRulesCount = 2;
		}
		
		// Get user pass thru flag
		errorRes = GetBoolValue(regPath, L"PSTR", &(pSecurityData -> passThru));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pSecurityData);
			return NULL;
		}
		
		// Fill rest fields
		pSecurityData -> authSystemID = -1;
		pSecurityData -> lastLogOnDate[0] = '\0';

		// Return pointer to user security data
		return pSecurityData + dllUserCheckResult;
	}
	catch(...)
	{
		return NULL;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : GetLocalUser

   Parameters :
			Input : 
				userIDName - user name

   Returns: pointer to user descriptor

   Description : Get info about local user from windows registry

*****************************************************************/
PSIMPLE_USER_DESCRIPTOR SettingsManager :: GetLocalUser(char * userIDName)
{
	try
	{
		// Prepare registry key path
		WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\Users\\";
		WCHAR wUserName[NAME_LEN];
		DWORD wUserNameLen = 0;
		wUserNameLen = mbstowcs(wUserName, userIDName, NAME_LEN);
		wcscat(regPath, wUserName);

		// Create user descriptor
		PSIMPLE_USER_DESCRIPTOR pUser = (PSIMPLE_USER_DESCRIPTOR)malloc(sizeof(SIMPLE_USER_DESCRIPTOR));

		// Check result
		if (!pUser)	return NULL;
		
		// Get user ID
		int errorRes = GetIntValue(regPath, L"ID", &(pUser -> userID));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pUser);
			return NULL;
		}

		// Get user name
		errorRes = GetEncStringValue(regPath, L"UNM", pUser -> encUserName, &(pUser -> encUserNameLen));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pUser);
			return NULL;
		}

		// Return pointer to user descriptor
		return pUser + dllUserCheckResult;
	}
	catch(...)
	{
		return NULL;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : GetLocalUsersList

   Returns: pointer to user list

   Description : Get info about all local users from windows registry

*****************************************************************/
PUSER_LIST SettingsManager :: GetLocalUsersList(void)
{
	// Prepare registry key path
	WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\Users";
	
	HKEY hKey; 
	DWORD disp;

	// Open key for read
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	if(errorRes != ERROR_SUCCESS)
		return NULL;

	try
	{
		// Create list
		PUSER_LIST pUserList = (PUSER_LIST)malloc(sizeof(USER_LIST));
	
		// Check result
		if(!pUserList)
		{
			RegCloseKey(hKey);
			return NULL;
		}

		pUserList -> usersCount = 0;
		DWORD count = 0;
		DWORD wcsUserNameLen;
		WCHAR wcsUserName[256];

		// Enumerate all subkeys
		do
		{
			wcsUserNameLen = 256;
			errorRes = RegEnumKeyEx(hKey, count, wcsUserName, &wcsUserNameLen, 0, NULL, NULL, NULL);
			
			if (errorRes == ERROR_SUCCESS)
			{
				char userName[128];
				wcstombs(userName, wcsUserName, 128);
				
				// Get user info
				pUserList -> users[pUserList -> usersCount] = GetLocalUser(userName);
				if (pUserList -> users[pUserList -> usersCount])
					pUserList -> usersCount++;
			}

			count++;
		} 
		while(errorRes != ERROR_NO_MORE_ITEMS);

		// Close key
		RegCloseKey(hKey);
		return pUserList + dllUserCheckResult;
	}
	catch(...)
	{
		return NULL;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : GetLocalUser

   Parameters :
			Input : 
				userName - system user name

   Returns: pointer to user descriptor

   Description : Get info about local user from windows registry

*****************************************************************/
PUSER_DESCRIPTOR SettingsManager :: GetLocalUser(WCHAR * userName)
{
	// Prepare registry key path
	WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\Users";
	
	HKEY hKey; 
	DWORD disp;

	// Open key for read
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	if(errorRes != ERROR_SUCCESS)
		return NULL;

	try
	{
		int count = 0;
		DWORD wcsUserNameLen;
		WCHAR wcsUserName[256];

		// Enumerate all subkeys
		do
		{
			wcsUserNameLen = 256;
			errorRes = RegEnumKeyEx(hKey, count, wcsUserName, &wcsUserNameLen, 0, NULL, NULL, NULL);
			
			if (errorRes == ERROR_SUCCESS)
			{
				wcscpy(regPath, L"SOFTWARE\\NovaTend\\Users\\");
				wcscat(regPath, wcsUserName);
				HKEY hSubKey; 
			
				// Open key for read
				errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hSubKey, &disp);
		
				if(errorRes != ERROR_SUCCESS)
				{
					RegCloseKey(hKey);
					return NULL;
				}

				// Get user name
				DWORD valueType = 0;
				DWORD bufLen = ENCRYPTED_DATA_SIZE;
				unsigned char sysNameBuffer[ENCRYPTED_DATA_SIZE];

				errorRes = RegGetValue(hSubKey, NULL, L"UNMSYS", RRF_RT_REG_BINARY, &valueType, sysNameBuffer, &bufLen);
				if(errorRes != ERROR_SUCCESS)
				{
					RegCloseKey(hSubKey);
					RegCloseKey(hKey);
					return NULL;
				}
				
				unsigned char decryptedName[STR_VALUE_LEN];
				int decryptedNameLen;

				if (encryptor -> UnPackAndDecryptSecurityData(sysNameBuffer, bufLen, decryptedName, STR_VALUE_LEN, &decryptedNameLen))
				{
					RegCloseKey(hSubKey);
					RegCloseKey(hKey);
					return NULL;
				}
				else
					decryptedName[decryptedNameLen] = 0;

				WCHAR tmpUserName[STR_VALUE_LEN];
				mbstowcs(tmpUserName, (char *)decryptedName, STR_VALUE_LEN);

				if (wcscmp(tmpUserName, userName) == 0)
				{
					// Get user ID
					valueType = 0;
					int userID;
					bufLen = sizeof(userID);
					errorRes = RegGetValue(hSubKey, NULL, L"ID", RRF_RT_REG_DWORD, &valueType, &userID, &bufLen);
				
					RegCloseKey(hSubKey);
					RegCloseKey(hKey);

					if(errorRes != ERROR_SUCCESS)
						return NULL;
					else
						return GetLocalUser(userID);
				}
				
				RegCloseKey(hSubKey);
			}

			count++;
		} 
		while(errorRes != ERROR_NO_MORE_ITEMS);

		// Close key
		RegCloseKey(hKey);
		return NULL;
	}
	catch(...)
	{
		return NULL;
	}
}

#pragma endregion

#pragma region Post Login

/****************************************************************

   Class : SettingsManager

   Method : GetPostLoginPath

   Parameters :
			Output : 
				postLoginPath - post login process path

   Returns: error code

   Description : Get post login process path from windows registry

*****************************************************************/
int SettingsManager :: GetPostLoginPath(char * postLoginPath)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\PostLogin", L"PSTLGN", postLoginPath);
}

/****************************************************************

   Class : SettingsManager

   Method : SetPostLoginPath

   Parameters :
			Input : 
				postLoginPath - database server name

   Returns: error code

   Description : Set post login process path to windows registry

*****************************************************************/
int SettingsManager :: SetPostLoginPath(char * postLoginPath)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\PostLogin", L"PSTLGN", postLoginPath);
}

/****************************************************************

   Class : SettingsManager

   Method : GetPostLoginUserID

   Parameters :
			Output : 
				userID - user ID

   Returns: error code

   Description : Get post login process user ID from windows registry

*****************************************************************/
int SettingsManager :: GetPostLoginUserID(int * userID)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\PostLogin", L"LGDUID", userID);
}

/****************************************************************

   Class : SettingsManager

   Method : SetPostLoginUserID

   Parameters :
			Input : 
				userID - user ID

   Returns: error code

   Description : Set post login process user ID to windows registry

*****************************************************************/
int SettingsManager :: SetPostLoginUserID(int userID)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\PostLogin", L"LGDUID", userID);
}

/****************************************************************

   Class : SettingsManager

   Method : GetPostLoginPeriodicFlag

   Parameters :
			Output : 
				postFlag - post login process periodic flag

   Returns: error code

   Description : Get post login process periodic flag from windows registry

*****************************************************************/
int SettingsManager :: GetPostLoginPeriodicFlag(bool * postFlag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\PostLogin", L"PERIODIC", postFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetPostLoginPeriodicFlag

   Parameters :
			Input : 
				postFlag - post login process periodic flag

   Returns: error code

   Description : Set post login process periodic flag to windows registry

*****************************************************************/
int SettingsManager :: SetPostLoginPeriodicFlag(bool postFlag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\PostLogin", L"PERIODIC", postFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : GetPostLoginPeriod

   Parameters :
			Output : 
				period - post login process period

   Returns: error code

   Description : Get post login process period from windows registry

*****************************************************************/
int SettingsManager :: GetPostLoginPeriod(int * period)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\PostLogin", L"PERIOD", period);
}

/****************************************************************

   Class : SettingsManager

   Method : SetPostLoginPeriod

   Parameters :
			Input : 
				period - post login process period

   Returns: error code

   Description : Set post login process period to windows registry

*****************************************************************/
int SettingsManager :: SetPostLoginPeriod(int period)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\PostLogin", L"PERIOD", period);
}

/****************************************************************

   Class : SettingsManager

   Method : SetAutoStartPostLogin

   Return : Error code

   Description : Set post login program to windows auto start

*****************************************************************/
int SettingsManager :: SetAutoStartPostLogin(void)
{
	char postLoginPath[MAX_PATH * 2];
	if (GetPostLoginPath(postLoginPath) == ERROR_SUCCESS)
		return SetStringValue(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", L"NovaTendPostLogin", postLoginPath);
	else
		return ERROR_ACCESS_DENIED;
}

#pragma endregion

#pragma region Logged user data

/****************************************************************

   Class : SettingsManager

   Method : GetLoggedUserID

   Parameters :
			Output : 
				userID - user ID

   Returns: error code

   Description : Get logged user ID from windows registry

*****************************************************************/
int SettingsManager :: GetLoggedUserID(int * userID)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\Users", L"LSTLGDUID", userID);
}

/****************************************************************

   Class : SettingsManager

   Method : SetLoggedUserID

   Parameters :
			Input : 
				userID - user ID

   Returns: error code

   Description : Set logged user ID to windows registry

*****************************************************************/
int SettingsManager :: SetLoggedUserID(int userID)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\Users", L"LSTLGDUID", userID);
}

/****************************************************************

   Class : SettingsManager

   Method : GetAuthSystemID

   Parameters :
			Output : 
				authSystemID - authentication system ID

   Returns: error code

   Description : Get authentication system ID from windows registry

*****************************************************************/
int SettingsManager :: GetAuthSystemID(int * authSystemID)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\Users", L"LSTAUTHSYSID", authSystemID);
}

/****************************************************************

   Class : SettingsManager

   Method : SetAuthSystemID

   Parameters :
			Input : 
				authSystemID - authentication system ID

   Returns: error code

   Description : Set authentication system ID to windows registry

*****************************************************************/
int SettingsManager :: SetAuthSystemID(int authSystemID)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\Users", L"LSTAUTHSYSID", authSystemID);
}

#pragma endregion

#pragma region Program control

/****************************************************************

   Class : SettingsManager

   Method : GetProgramControllFlag

   Parameters :
			Output : 
				prgCtrlFlag - program control flag

   Returns: error code

   Description : Get program controll On/Off flag

*****************************************************************/
int SettingsManager :: GetProgramControllFlag(bool * prgCtrlFlag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\ProgramControl", L"PRGCTRLON", prgCtrlFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetProgramControllFlag

   Parameters :
			Input : 
				prgCtrlFlag - program control flag

   Returns: error code

   Description : Set program controll On/Off flag

*****************************************************************/
int SettingsManager :: SetProgramControllFlag(bool prgCtrlFlag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\ProgramControl", L"PRGCTRLON", prgCtrlFlag);
}


#pragma endregion

#pragma region Files transfer

/****************************************************************

   Class : SettingsManager

   Method : GetUploadDirectory

   Parameters :
			Output : 
				uploadDir - upload directory

   Returns: error code

   Description : Get upload directory

*****************************************************************/
int SettingsManager :: GetUploadDirectory(char * uploadDir)
{
	return GetStringValue(L"SOFTWARE\\NovaTend\\Files", L"UPLOADDIR", uploadDir);
}

/****************************************************************

   Class : SettingsManager

   Method : SetUploadDirectory

   Parameters :
			Input : 
				uploadDir - upload directory

   Returns: error code

   Description : Set upload directory

*****************************************************************/
int SettingsManager :: SetUploadDirectory(char * uploadDir)
{
	return SetStringValue(L"SOFTWARE\\NovaTend\\Files", L"UPLOADDIR", uploadDir);
}

/****************************************************************

   Class : SettingsManager

   Method : GetDownloadDirectory

   Parameters :
			Output : 
				downloadDir - download directory

   Returns: error code

   Description : Get download directory

*****************************************************************/
int SettingsManager :: GetDownloadDirectory(char * downloadDir)
{
	return GetStringValue(L"SOFTWARE\\NovaTend\\Files", L"DOWNLOADDIR", downloadDir);
}

/****************************************************************

   Class : SettingsManager

   Method : SetDownloadDirectory

   Parameters :
			Input : 
				downloadDir - download directory

   Returns: error code

   Description : Set download directory

*****************************************************************/
int SettingsManager :: SetDownloadDirectory(char * downloadDir)
{
	return SetStringValue(L"SOFTWARE\\NovaTend\\Files", L"DOWNLOADDIR", downloadDir);
}

/****************************************************************

   Class : SettingsManager

   Method : GetTemporaryDirectory

   Parameters :
			Output : 
				tempDir - temporary directory

   Returns: error code

   Description : Get temporary directory

*****************************************************************/
int SettingsManager :: GetTemporaryDirectory(char * tempDir)
{
	return GetStringValue(L"SOFTWARE\\NovaTend\\Files", L"TEMPDIR", tempDir);
}

/****************************************************************

   Class : SettingsManager

   Method : SetTemporaryDirectory

   Parameters :
			Input : 
				tempDir - temporary directory

   Returns: error code

   Description : Set temporary directory

*****************************************************************/
int SettingsManager :: SetTemporaryDirectory(char * tempDir)
{
	return SetStringValue(L"SOFTWARE\\NovaTend\\Files", L"TEMPDIR", tempDir);
}

#pragma endregion

#pragma region Command history

/****************************************************************

   Class : SettingsManager

   Method : GetCmdHistDatabase

   Parameters :
			Output : 
				dbName - database name

   Returns: error code

   Description : Get command history database

*****************************************************************/
int  SettingsManager :: GetCmdHistDatabase(char * dbName)
{
	return GetEncStringValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"HUBHIST", dbName);
}

/****************************************************************

   Class : SettingsManager

   Method : SetCmdHistDatabase

   Parameters :
			Input : 
				dbName - database name

   Returns: error code

   Description : Set command history database

*****************************************************************/
int  SettingsManager :: SetCmdHistDatabase(char * dbName)
{
	return SetEncStringValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"HUBHIST", dbName);
}

/****************************************************************

   Class : SettingsManager

   Method : GetHistorianPeriodicFlag

   Parameters :
			Output : 
				histFlag - periodic flag

   Returns: error code

   Description : Get historian periodic flag from windows registry

*****************************************************************/
int SettingsManager :: GetHistorianPeriodicFlag(bool * histFlag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"PERIODIC", histFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetHistorianPeriodicFlag

   Parameters :
			Input : 
				histFlag - periodic flag

   Returns: error code

   Description : Set historian periodic flag to windows registry

*****************************************************************/
int SettingsManager :: SetHistorianPeriodicFlag(bool histFlag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"PERIODIC", histFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : GetHistorianPeriod

   Parameters :
			Output : 
				period - historian process period

   Returns: error code

   Description : Get historian period from windows registry

*****************************************************************/
int SettingsManager :: GetHistorianPeriod(int * period)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"PERIOD", period);
}

/****************************************************************

   Class : SettingsManager

   Method : SetHistorianPeriod

   Parameters :
			Input : 
				period - historian process period

   Returns: error code

   Description : Set historian period to windows registry

*****************************************************************/
int SettingsManager :: SetHistorianPeriod(int period)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"PERIOD", period);
}

/****************************************************************

   Class : SettingsManager

   Method : GetUserEnvironmentCommandFlag

   Parameters :
			Output : 
				flag - run command flag

   Returns: error code

   Description : Get user enviroment command flag from windows registry

*****************************************************************/
int SettingsManager :: GetUserEnvironmentCommandFlag(bool * flag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"USERENV", flag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetUserEnvironmentCommandFlag

   Parameters :
			Input : 
				flag - run command flag

   Returns: error code

   Description : Set user enviroment command flag to windows registry

*****************************************************************/
int SettingsManager :: SetUserEnvironmentCommandFlag(bool flag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"USERENV", flag);
}

/****************************************************************

   Class : SettingsManager

   Method : GetLoggedUserNameCommandFlag

   Parameters :
			Output : 
				flag - run command flag

   Returns: error code

   Description : Get user name command flag from windows registry

*****************************************************************/
int SettingsManager :: GetLoggedUserNameCommandFlag(bool * flag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"USRNAME", flag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetLoggedUserNameCommandFlag

   Parameters :
			Input : 
				flag - run command flag

   Returns: error code

   Description : Set user name command flag to windows registry

*****************************************************************/
int SettingsManager :: SetLoggedUserNameCommandFlag(bool flag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"USRNAME", flag);
}

/****************************************************************

   Class : SettingsManager

   Method : GetScreenshotCommandFlag

   Parameters :
			Output : 
				flag - run command flag

   Returns: error code

   Description : Get screenshot command flag from windows registry

*****************************************************************/
int SettingsManager :: GetScreenshotCommandFlag(bool * flag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"SCRSHT", flag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetScreenshotCommandFlag

   Parameters :
			Input : 
				flag - run command flag

   Returns: error code

   Description : Set screenshot command flag to windows registry

*****************************************************************/
int SettingsManager :: SetScreenshotCommandFlag(bool flag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"SCRSHT", flag);
}

/****************************************************************

   Class : SettingsManager

   Method : GetCamSnapshotCommandFlag

   Parameters :
			Output : 
				flag - run command flag

   Returns: error code

   Description : Get snapshot command flag from windows registry

*****************************************************************/
int SettingsManager :: GetCamSnapshotCommandFlag(bool * flag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"SNPSHT", flag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetCamSnapshotCommandFlag

   Parameters :
			Input : 
				flag - run command flag

   Returns: error code

   Description : Set snapshot command flag to windows registry

*****************************************************************/
int SettingsManager :: SetCamSnapshotCommandFlag(bool flag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\CommandHistory", L"SNPSHT", flag);
}

#pragma endregion

#pragma region Update settings

/****************************************************************

   Class : SettingsManager

   Method : GetUpdateDirectory

   Parameters :
			Output : 
				updateDir - update directory

   Returns: error code

   Description : Get update directory

*****************************************************************/
int SettingsManager :: GetUpdateDirectory(char * updateDir)
{
	return GetStringValue(L"SOFTWARE\\NovaTend\\Update", L"UPDATEDIR", updateDir);
}

/****************************************************************

   Class : SettingsManager

   Method : SetUpdateDirectory

   Parameters :
			Input : 
				updateDir - update directory

   Returns: error code

   Description : Set update directory

*****************************************************************/
int SettingsManager :: SetUpdateDirectory(char * updateDir)
{
	return SetStringValue(L"SOFTWARE\\NovaTend\\Update", L"UPDATEDIR", updateDir);
}

/****************************************************************

   Class : SettingsManager

   Method : GetUpdatePeriodicFlag

   Parameters :
			Output : 
				upFlag - periodic flag

   Returns: error code

   Description : Get update periodic flag from windows registry

*****************************************************************/
int SettingsManager :: GetUpdatePeriodicFlag(bool * upFlag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\Update", L"PERIODIC", upFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetUpdatePeriodicFlag

   Parameters :
			Input : 
				upFlag - periodic flag

   Returns: error code

   Description : Set update periodic flag to windows registry

*****************************************************************/
int SettingsManager :: SetUpdatePeriodicFlag(bool upFlag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\Update", L"PERIODIC", upFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : GetUpdatePeriod

   Parameters :
			Output : 
				period - historian process period

   Returns: error code

   Description : Get update period from windows registry

*****************************************************************/
int SettingsManager :: GetUpdatePeriod(int * period)
{
	return GetIntValue(L"SOFTWARE\\NovaTend\\Update", L"PERIOD", period);
}

/****************************************************************

   Class : SettingsManager

   Method : SetUpdatePeriod

   Parameters :
			Input : 
				period - historian process period

   Returns: error code

   Description : Set update period to windows registry

*****************************************************************/
int SettingsManager :: SetUpdatePeriod(int period)
{
	return SetIntValue(L"SOFTWARE\\NovaTend\\Update", L"PERIOD", period);
}

/****************************************************************

   Class : SettingsManager

   Method : GetUpdateFileList

   Returns: pointer to folder description container

   Description : Get list of files for update from windows registry

*****************************************************************/
PFOLDER_INFO_CONTAINER SettingsManager :: GetUpdateFileList(void)
{
	// Prepare registry key path
	WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\Update";
	
	HKEY hKey; 
	DWORD disp;

	// Open key for read
	int errorRes = RegCreateKeyEx(HKEY_LOCAL_MACHINE, regPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &disp);
	if(errorRes != ERROR_SUCCESS)
		return NULL;

	try
	{
		// Create container
		PFOLDER_INFO_CONTAINER pFolder = (PFOLDER_INFO_CONTAINER)malloc(sizeof(FOLDER_INFO_CONTAINER));
	
		// Check result
		if(!pFolder)
		{
			RegCloseKey(hKey);
			return NULL;
		}

		pFolder -> filesCount = 0;
		strcpy(pFolder -> dirName, "Updating...");

		DWORD count = 0;
		DWORD wcsFileNameLen;
		WCHAR wcsFileName[256];

		// Enumerate all subkeys
		do
		{
			wcsFileNameLen = 1024;
			errorRes = RegEnumKeyEx(hKey, count, wcsFileName, &wcsFileNameLen, 0, NULL, NULL, NULL);
			
			if (errorRes == ERROR_SUCCESS)
			{
				// Get file info
				PFILE_INFO_CONTAINER pFile = GetUpdateFileInfo(regPath, wcsFileName);

				if (pFile)
				{
					pFolder -> filesList[pFolder -> filesCount] = pFile;
					pFolder -> filesCount++;
				}
			}

			count++;
		} 
		while(errorRes != ERROR_NO_MORE_ITEMS);

		// Close key
		RegCloseKey(hKey);
		return pFolder + dllUserCheckResult;
	}
	catch(...)
	{
		return NULL;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : SetUpdateFileList

   Parameters:
			Input:
				pFolder - pointer to file list container

   Returns: error code

   Description : Set list of files for update to windows registry

*****************************************************************/
int SettingsManager :: SetUpdateFileList(PFOLDER_INFO_CONTAINER pFolder)
{
	if (pFolder)
	{
		// Prepare registry key path
		WCHAR regPath[256] = L"SOFTWARE\\NovaTend\\Update";

		// Check all files
		for(int i = 0; i < pFolder -> filesCount; i++)
		{
			if (pFolder -> filesList[i])
			{
				// Get file name
				int pos = -1;
				for (int k = strlen(pFolder -> filesList[i] -> fileName) - 1; k >= 0; k--)
				{
					if ((pFolder -> filesList[i] -> fileName[k]) == '\\')
					{
						pos = k;
						break;
					}
				}

				char fileIDName[NAME_LEN] = "";

				if (pos >= 0)
					strcpy(fileIDName, pFolder -> filesList[i] -> fileName + pos + 1);
				else
					strcpy(fileIDName, pFolder -> filesList[i] -> fileName);

				WCHAR wFileIDName[NAME_LEN] = L"";
				mbstowcs(wFileIDName, fileIDName, NAME_LEN);

				// Save file info
				if (SetUpdateFileInfo(regPath, wFileIDName, pFolder -> filesList[i]) != ERROR_SUCCESS)
					return ERROR_ACCESS_DENIED;
			}
		}

		return ERROR_SUCCESS;
	}
	else
		return ERROR_BAD_ARGUMENTS;
}

/****************************************************************

   Class : SettingsManager

   Method : GetUpdateFileInfo

   Parameters :
			Input : 
				regPath - registry path
				fileIDname - file name

   Returns: pointer to file info container

   Description : Get update file info from windows registry

*****************************************************************/
PFILE_INFO_CONTAINER SettingsManager :: GetUpdateFileInfo(WCHAR * regPath, WCHAR * fileIDname)
{
	if ((regPath == NULL) || (fileIDname == NULL))
		return NULL;

	// Prepare registry key path
	WCHAR _regPath[256] = L"";

	try
	{
		// Prepare registry key path
		wcscpy(_regPath, regPath);
		wcscat(_regPath, L"\\");
		wcscat(_regPath, fileIDname);

		// Create file descriptor
		PFILE_INFO_CONTAINER pFile = (PFILE_INFO_CONTAINER)malloc(sizeof(FILE_INFO_CONTAINER));

		// Check result
		if (!pFile) return NULL;
		
		// Get file name
		int errorRes = GetStringValue(_regPath, L"FNAME", pFile -> fileName);
		if(errorRes != ERROR_SUCCESS)
		{
			free(pFile);
			return NULL;
		}

		// Get update time
		char timeBuf[DATE_STR_LEN] = "";
		errorRes = GetStringValue(_regPath, L"FTIME", timeBuf);
		if(errorRes != ERROR_SUCCESS)
		{
			free(pFile);
			return NULL;
		}
		else
		{
			// Calculate first date
			int day, mon, year, hour, min, sec;
			sscanf_s(timeBuf, "%d-%d-%d %d:%d:%d", &year, &mon, &day, &hour, &min, &sec);

			// Set time values
			pFile -> updateTime.tm_year = year - 1900;
			pFile -> updateTime.tm_mon = mon - 1;
			pFile -> updateTime.tm_mday = day;
			pFile -> updateTime.tm_hour = hour;
			pFile -> updateTime.tm_min = min;
			pFile -> updateTime.tm_sec = sec;
			pFile -> updateTime.tm_isdst = -1;
		}

		// Get file size
		errorRes = GetIntValue(_regPath, L"FSIZE", (int *)(&(pFile -> fileSize)));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pFile);
			return NULL;
		}

		// Get dir flag
		errorRes = GetBoolValue(_regPath, L"FDIRF", &(pFile -> isDir));
		if(errorRes != ERROR_SUCCESS)
		{
			free(pFile);
			return NULL;
		}

		// Return pointer to server descriptor
		return pFile + dllUserCheckResult;
	}
	catch(...)
	{
		return NULL;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : SetUpdateFileInfo

   Parameters :
			Input : 
				regPath - registry path
				fileIDname - file key
				pFile - file description

   Returns: error code

   Description : Set update file info to windows registry

*****************************************************************/
int SettingsManager :: SetUpdateFileInfo(WCHAR * regPath, WCHAR * fileIDname, PFILE_INFO_CONTAINER pFile)
{
	// Check pointer to server descriptor
	if ((pFile == NULL) || (regPath == NULL) || (fileIDname == NULL))
		return ERROR_ACCESS_DENIED;
	
	// Prepare registry key path
	WCHAR _regPath[256] = L"";

	try
	{
		// Prepare registry key path
		wcscpy(_regPath, regPath);
		wcscat(_regPath, L"\\");
		wcscat(_regPath, fileIDname);

		// Set file name	
		int errorRes = SetStringValue(_regPath, L"FNAME", pFile -> fileName);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;
		
		// Set file time
		char timeBuf[DATE_STR_LEN] = "";
		strftime(timeBuf, DATE_STR_LEN, "%Y-%m-%d %H:%M:%S", &(pFile -> updateTime));
		errorRes = SetStringValue(_regPath, L"FTIME", timeBuf);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		// Set file size priority
		errorRes = SetIntValue(_regPath, L"FSIZE", pFile -> fileSize);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;
		
		// Set dir flag
		errorRes = SetBoolValue(_regPath, L"FDIRF", pFile -> isDir);
		if (errorRes != ERROR_SUCCESS)
			return errorRes;

		return ERROR_SUCCESS;
	}
	catch(...)
	{
		return ERROR_ACCESS_DENIED;
	}
}

/****************************************************************

   Class : SettingsManager

   Method : GetUpdateInstalledFlag

   Parameters :
			Output : 
				upFlag - periodic flag

   Returns: error code

   Description : Get update installed flag from windows registry

*****************************************************************/
int SettingsManager :: GetUpdateInstalledFlag(bool * upFlag)
{
	return GetBoolValue(L"SOFTWARE\\NovaTend\\Update", L"INSTALLED", upFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : SetUpdateInstalledFlag

   Parameters :
			Input : 
				upFlag - periodic flag

   Returns: error code

   Description : Set update installed flag from windows registry

*****************************************************************/
int SettingsManager :: SetUpdateInstalledFlag(bool upFlag)
{
	return SetBoolValue(L"SOFTWARE\\NovaTend\\Update", L"INSTALLED", upFlag);
}

/****************************************************************

   Class : SettingsManager

   Method : GetUserUpdaterPath

   Parameters :
			Output : 
				upPath - Path to user uploader

   Returns: error code

   Description : Get updater path from windows registry

*****************************************************************/
int SettingsManager :: GetUserUpdaterPath(char * upPath)
{
	return GetStringValue(L"SOFTWARE\\NovaTend\\Update", L"UPPATH", upPath);
}

/****************************************************************

   Class : SettingsManager

   Method : SetUserUpdaterPath

   Parameters :
			Input : 
				upPath - Path to user uploader

   Returns: error code

   Description : Set updater path from windows registry

*****************************************************************/
int SettingsManager :: SetUserUpdaterPath(char * upPath)
{
	return SetStringValue(L"SOFTWARE\\NovaTend\\Update", L"UPPATH", upPath);
}

#pragma endregion
