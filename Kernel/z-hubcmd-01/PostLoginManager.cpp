/****************************************************************

   Solution : NovaTend

   Project : z-hubsrv-01.exe

   Module : PostLoginManager.cpp

   Description :  this module implements methods of
				  class PostLoginManager

*****************************************************************/

#include "stdafx.h"

#include "PostLoginManager.h"
#include <SettingsManager.h>
#include <Wtsapi32.h>

// z-hubcmd-01.exe definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;

/****************************************************************

   Class : PostLoginManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - dll user ID
				logWriter - pointer to LOG-writer instance
								
*****************************************************************/
PostLoginManager :: PostLoginManager(unsigned long dllUserID, LogWriter * logWriter) : ThreadController(dllUserID, &zHubCmdDllDefinition, INFINITE)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("PostLoginManager : constructor");
	#endif
}

/****************************************************************

   Class : PostLoginManager

   Method : Destructor
   
*****************************************************************/
PostLoginManager :: ~PostLoginManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("PostLoginManager : destructor");
	#endif
}

/****************************************************************

   Class : PostLoginManager

   Method : RunPostLoginProcess

   Returns : TRUE - if success

   Description : Run post login process
                 
*****************************************************************/
bool PostLoginManager :: RunPostLoginProcess(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("PostLoginManager : RunPostLoginProcess. Start");
	#endif

	SettingsManager * settingsManager = new SettingsManager(zHubCmdDllDefinition.dllID);

	if (settingsManager -> GetPostLoginPath(postLoginPath) == ERROR_SUCCESS)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		
		ZeroMemory(&pi, sizeof(pi));
		HANDLE hUserToken;
		
		WCHAR wPostLoginPath[MAX_PATH];
		mbstowcs(wPostLoginPath, postLoginPath, MAX_PATH);

		// Start post login process
		if ((WTSQueryUserToken(WTSGetActiveConsoleSessionId(), &hUserToken)) &&
			(!CreateProcessAsUser(hUserToken, wPostLoginPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)))
		{
			delete settingsManager;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("PostLoginManager : RunPostLoginProcess. Can't start post login process");
				WriteToLog("PostLoginManager : RunPostLoginProcess. Done");
			#endif

			return false;
		}

		delete settingsManager;

		// Wait until child process exits.
		WaitForSingleObject(pi.hProcess, INFINITE);

		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("PostLoginManager : RunPostLoginProcess. Done");
		#endif

		return true;
	}
	else
	{
		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("PostLoginManager : RunPostLoginProcess. Can't get post login process path");
			WriteToLog("PostLoginManager : RunPostLoginProcess. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : PostLoginManager

   Method : CheckPeriodicFlag

   Returns : TRUE - if success

   Description : Check periodic flag
                 
*****************************************************************/
bool PostLoginManager :: CheckPeriodicFlag(void)
{
	SettingsManager * settingsManager = new SettingsManager(zHubCmdDllDefinition.dllID);

	if (settingsManager -> GetPostLoginPeriodicFlag(&periodicallyFlag) != ERROR_SUCCESS)
		periodicallyFlag = false;

	delete settingsManager;

	return periodicallyFlag;
}

/****************************************************************

   Class : PostLoginManager

   Method : CheckPeriod

   Returns : TRUE - if success

   Description : Check post login period
                 
*****************************************************************/
bool PostLoginManager :: CheckPeriod(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("PostLoginManager : CheckPeriod. Start");
	#endif

	SettingsManager * settingsManager = new SettingsManager(zHubCmdDllDefinition.dllID);

	if (settingsManager -> GetPostLoginPeriod(&periodValue) == ERROR_SUCCESS)
	{
		// Get current time
		time_t nowSeconds;
		time(&nowSeconds);

		// Subtract dates
		double resSeconds = difftime(nowSeconds, prevTimeSeconds);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			char message[STR_VALUE_LEN];
			sprintf(message, "PostLoginManager : CheckPeriod. Period: %d. Seconds: %d", periodValue, (int)resSeconds);
			WriteToLog(message);
		#endif
					
		// Prepare result
		bool result = false;

		if (resSeconds > periodValue * 60)
		{
			// Save current time
			prevTimeSeconds = nowSeconds;

			result = true;
		}

		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("PostLoginManager : CheckPeriod. Done");
		#endif

		return result;
	}
	else
	{
		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("PostLoginManager : CheckPeriod. Can't get period!");
			WriteToLog("PostLoginManager : CheckPeriod. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : PostLoginManager

   Method : ControllerEntry

   Description :  Run post login process

*****************************************************************/
void PostLoginManager :: ControllerEntry(void)
{
	RunPostLoginProcess();
}

/****************************************************************

   Class : PostLoginManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int PostLoginManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}