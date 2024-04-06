/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : GetUserEnvironmentInfoCommand.cpp

   Description :  this module implements methods of
				  class GetUserEnvironmentInfoCommand

*****************************************************************/

#include "stdafx.h"
#include "GetUserEnvironmentInfoCommand.h"
#include <CommandHistoryManager.h>

// z-desktopcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zDesktopCmdDllDefinition;
 
/****************************************************************

   Class : GetUserEnvironmentInfoCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
GetUserEnvironmentInfoCommand :: GetUserEnvironmentInfoCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetUserEnvironmentInfoCommand : constructor");
	#endif
}

/****************************************************************

   Class : GetUserEnvironmentInfoCommand

   Method : Destructor

*****************************************************************/
GetUserEnvironmentInfoCommand :: ~GetUserEnvironmentInfoCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetUserEnvironmentInfoCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetUserEnvironmentInfoCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetUserEnvironmentInfoCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetUserEnvironmentInfoCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((!parameters) ||
		(parameters) &&
	   ((parameters -> paramCount == 0) ||
		(parameters -> paramCount == 1)))
	{
		ENVIROMENT_INFO_CONTAINER envContainer = {0};

		// Get active program name
		GetActiveAppName(envContainer.activeProgramName);

		// Get user downtime
		envContainer.userDowntime = GetUserDowntime();

		// Get applications list
		GetAppList(&envContainer);

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zDesktopCmdDllDefinition.dllID, logWriter);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackEnviromentInfoContainer(&envContainer, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			else
				WriteToLog("GetUserEnvironmentInfoCommand : Execute. Can't create result parameters list!");
		#endif

		// Save command to history
		if ((parameters -> paramCount == 1) &&
			(parameters -> paramList[0]) &&
			(parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
			(parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
			CommandHistoryManager * commandHistoryManager = new CommandHistoryManager(zDesktopCmdDllDefinition.dllID, logWriter);
			commandHistoryManager -> SaveCommand(CMD_GET_USER_ENV_INFO, userID, parameters, result);
			delete commandHistoryManager;
		}

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		else
			WriteToLog("GetUserEnvironmentInfoCommand : Execute. Wrong input parameters!");

		WriteToLog("GetUserEnvironmentInfoCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetUserEnvironmentInfoCommand

   Method : GetUserDowntime

   Return : downtime in seconds

   Description : Get downtime

*****************************************************************/
int GetUserEnvironmentInfoCommand :: GetUserDowntime(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetUserEnvironmentInfoCommand : GetUserDowntime. Start");
	#endif

	LASTINPUTINFO lastInputInfo = {};
	lastInputInfo.cbSize = sizeof(LASTINPUTINFO);
	
	int downTime = 0;
	if (GetLastInputInfo(&lastInputInfo))
		downTime = 	(GetTickCount() - lastInputInfo.dwTime)/1000;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		char mes[STR_VALUE_LEN];
		sprintf(mes, "GetUserEnvironmentInfoCommand : GetUserDowntime. Downtime value = %d (s)", downTime);
		WriteToLog(mes);
		WriteToLog("GetUserEnvironmentInfoCommand : GetUserDowntime. Done");
	#endif

	return downTime;
}

/****************************************************************

   Function : IsAppWindow

   Parameters :
			Output : 
				hWnd - window handler

	Return : TRUE - if this window is desktop application

	Description : Check for application window

*****************************************************************/
bool IsAppWindow(HWND hWnd)
{
	if (!IsWindow(hWnd))
		return false;
	
	DWORD dwStyleEx = GetWindowLong(hWnd, GWL_EXSTYLE);

	return (IsWindow(hWnd) && IsWindowVisible(hWnd) && (!GetWindow(hWnd, GW_OWNER)) && (!(dwStyleEx & WS_EX_NOACTIVATE)) && (!(dwStyleEx & WS_EX_TOOLWINDOW)));
}

/****************************************************************

   Function : EnumWindowsProc

   Parameters :
			Output : 
				hWnd - window handler
				lParam - param pointer

	Return : TRUE - if success

	Description : Windows enumeration callback function

*****************************************************************/
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	// Check HWND
	if (IsAppWindow(hWnd))
	{
		PENVIROMENT_INFO_CONTAINER envContainer = (PENVIROMENT_INFO_CONTAINER)lParam;

		// Get window name
		char wndName[NAME_LEN];
		int len = GetWindowTextA(hWnd, wndName, NAME_LEN);

		// Add window name to list
		if (len)
		{
			int index = envContainer -> programNamesListCount;
			strcpy(envContainer -> programNamesList[index], wndName);
			envContainer -> programNamesListCount += 1;
		}
	}

	return TRUE;
}

/****************************************************************

   Class : GetUserEnvironmentInfoCommand

   Method : GetActiveAppName

   Parameters :
			Output : 
				activeAppName - name of foreground window

	Return : length of name of foreground window

	Description : Get active application name

*****************************************************************/
int GetUserEnvironmentInfoCommand :: GetActiveAppName(char * activeAppName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetUserEnvironmentInfoCommand : GetActiveAppName. Start");
	#endif

	// Check output buffer
	if (activeAppName)
	{
		activeAppName[0] = 0;
				
		// Get foreground window name
		HWND hWnd = GetForegroundWindow();

		// Check HWND
		if (!IsAppWindow(hWnd))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
				WriteToLog("GetUserEnvironmentInfoCommand : GetActiveAppName. This application is not desktop window");
				WriteToLog("GetUserEnvironmentInfoCommand : GetActiveAppName. Done");
			#endif

			return 0;
		}

		// Get window name
		int len = GetWindowTextA(hWnd, activeAppName, NAME_LEN);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetUserEnvironmentInfoCommand : GetActiveAppName. Done");
		#endif

		return (len ? (len + 1) : 0);
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetUserEnvironmentInfoCommand : GetActiveAppName. Wrong output buffer!");
			WriteToLog("GetUserEnvironmentInfoCommand : GetActiveAppName. Done");
		#endif

		return 0;
	}
}

/****************************************************************

   Class : GetUserEnvironmentInfoCommand

   Method : GetAppList

   Parameters :
			Output : 
				envContainer - enviroment info container structure

	Return : length of user applications list

	Description : Get user applications list

*****************************************************************/
int GetUserEnvironmentInfoCommand :: GetAppList(PENVIROMENT_INFO_CONTAINER envContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetUserEnvironmentInfoCommand : GetAppList. Start");
	#endif

	// Check output buffer
	if (envContainer)
	{
		// Enum windows
		if (!EnumDesktopWindows(NULL, EnumWindowsProc, LPARAM(envContainer)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
				WriteToLog("GetUserEnvironmentInfoCommand : GetAppList. Error of windows enumeration!");
				WriteToLog("GetUserEnvironmentInfoCommand : GetAppList. Done");
			#endif

			return 0;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetUserEnvironmentInfoCommand : GetAppList. Done");
		#endif

		return envContainer -> programNamesListCount;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetUserEnvironmentInfoCommand : GetAppList. Wrong output buffer!");
			WriteToLog("GetUserEnvironmentInfoCommand : GetAppList. Done");
		#endif

		return 0;
	}
}



