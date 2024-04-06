/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : LockUserCADActionsCommand.cpp

   Description :  this module implements methods of
				  class LockUserCADActionsCommand

*****************************************************************/

#include "stdafx.h"
#include "LockUserCADActionsCommand.h"
#include <Sddl.h>

// z-hubcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;
 
/****************************************************************

   Class : LockUserCADActionsCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
LockUserCADActionsCommand :: LockUserCADActionsCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("LockUserCADActionsCommand : constructor");
	#endif
}

/****************************************************************

   Class : LockUserCADActionsCommand

   Method : Destructor

*****************************************************************/
LockUserCADActionsCommand :: ~LockUserCADActionsCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("LockUserCADActionsCommand : destructor");
	#endif
}

/****************************************************************

   Class : LockUserCADActionsCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST LockUserCADActionsCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("LockUserCADActionsCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) && 
		(parameters -> paramCount == 2) &&
		(parameters -> paramList[0]) && 
		(parameters -> paramList[1]) &&
		(parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
		(parameters -> paramList[0] -> paramDataType == BYTE_DATA) &&
		(parameters -> paramList[1] -> paramType == INPUT_CMD_DATA) &&
		(parameters -> paramList[1] -> paramDataType == STRING_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);
		
		// Lock flag
		bool lockFlag = (bool)(serializationManager -> UnpackByte(parameters -> paramList[0]));

		// User name
		char userName[NAME_LEN] = "";
		serializationManager -> UnpackString(parameters -> paramList[1], userName);

		// Lock/unlock CTRL + ALT + DEL
		bool lockingResult = LockCtrlAltDelActions(lockFlag, userName);

		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackByte((unsigned char)lockingResult, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			else
				WriteToLog("LockUserCADActionsCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		else
			WriteToLog("LockUserCADActionsCommand : Execute. Wrong input parameters!");

		WriteToLog("LockUserCADActionsCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LockUserCADActionsCommand

   Method : LockCtrlAltDelActions

   	Parameters :
			Input : 
				lock - lock/unclok flag
				userName - user name

   Return : TRUE - if success

   Description : Lock/Unlock CTRL + ALT + DEL

*****************************************************************/
bool LockUserCADActionsCommand :: LockCtrlAltDelActions(bool lock, char * userName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Start");
	#endif

	// Get user SID by user name
	BYTE sid[NAME_LEN];
	DWORD sidSize = sizeof(sid);
	WCHAR * sidString;
	WCHAR wUserName[STR_VALUE_LEN];
	WCHAR domainName[STR_VALUE_LEN];
	DWORD domainNameLen = STR_VALUE_LEN;
	SID_NAME_USE peUse;

	mbstowcs(wUserName, userName, STR_VALUE_LEN);
	if(!LookupAccountName(NULL, wUserName, (PSID)sid, &sidSize, domainName, &domainNameLen, &peUse))
	{
		int error = GetLastError();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Can't get user SID!");	
			WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Done");
		#endif

		return false;
	}

	// Convert SID to string
	if (!ConvertSidToStringSid((PSID)sid, &sidString))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Can't convert SID to string!");	
			WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Done");
		#endif

		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		else
		{
			char mbSidStr[STR_VALUE_LEN];
			wcstombs(mbSidStr, sidString, STR_VALUE_LEN);

			char message[STR_VALUE_LEN];
			sprintf(message, "LockUserCADActionsCommand : LockCtrlAltDelActions. User: %s has SID: %s", userName, mbSidStr);
			WriteToLog(message);
		}
	#endif

	// Prepare registry key path
	WCHAR regKey[MAX_PATH];
	wcscpy_s(regKey, sidString);
	wcscat_s(regKey, L"\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
	LocalFree((HLOCAL)sidString);
			
	HKEY hKey; 
	DWORD disp;

	// Open key for write
	int errorRes = RegCreateKeyEx(HKEY_USERS, regKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &disp);
	
	if (errorRes != ERROR_SUCCESS)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			char message[STR_VALUE_LEN];
			char mbRegKey[MAX_PATH];
			wcstombs(mbRegKey, regKey, MAX_PATH);
			sprintf(message, "LockUserCADActionsCommand : LockCtrlAltDelActions. Can't open registry key: %s. Error code: %d", mbRegKey, errorRes);
			WriteToLog(message);	
			WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Done");
		#endif

		return false;
	}

	if (lock)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Trying to lock CTRL+ALT+DEL");
		#endif

		// Set value
		int value = 1;

		errorRes = RegSetValueEx(hKey, L"DisableTaskMgr", NULL, REG_DWORD, (BYTE *)&value, sizeof(value));

		if(errorRes != ERROR_SUCCESS)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Can't disable task manager!");	
				WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Done");
			#endif

			RegCloseKey(hKey);
    		return false;
		}
	    
		errorRes = RegSetValueEx(hKey, L"DisableChangePassword", NULL, REG_DWORD, (BYTE *)&value, sizeof(value));

		if(errorRes != ERROR_SUCCESS)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Can't disable change password action!");	
				WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Done");
			#endif

			RegCloseKey(hKey);
    		return false;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Trying to unlock CTRL+ALT+DEL");
		#endif

		errorRes = RegDeleteValue(hKey, L"DisableTaskMgr");

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			if(errorRes != ERROR_SUCCESS)
			{
				WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Can't enable task manager!");	
			}
		#endif

		errorRes = RegDeleteValue(hKey, L"DisableChangePassword");
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			if(errorRes != ERROR_SUCCESS)
			{
				WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Can't enable change password action!");	
			}
		#endif
	}

	// Close key
	RegCloseKey(hKey);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Locking/Unlocking success!");	
		WriteToLog("LockUserCADActionsCommand : LockCtrlAltDelActions. Done");
	#endif

	return true;
}