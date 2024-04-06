/****************************************************************

   Solution : NovaTend

   Project : z-winservice-01.dll

   Module : WinServiceManager.cpp

   Description :  this module implements methods of
				  class WinServiceManager

*****************************************************************/

#include "stdafx.h"

#include "WinServiceManager.h"

// z-winservice-01.dll definition structure
extern DLL_COMMON_DEFINITION zWinServiceDllDefinition;

/****************************************************************

   Class : WinServiceManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				serviceName - service name
				logWriter - pointer to log writer instance

*****************************************************************/
WinServiceManager :: WinServiceManager(unsigned long dllUserID, WCHAR * serviceName, LogWriter * logWriter) : SystemBase(dllUserID, &zWinServiceDllDefinition)
{
	// Initialize fields
	hSCM = NULL;
	init = false;
	wcscpy(this -> serviceName, L"");
	this -> logWriter = logWriter;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. Constructor");
	#endif

	// Set service name and initialize service manager
	SetServiceName(serviceName);
}

/****************************************************************

   Class : WinServiceManager

   Method : Destructor
   
*****************************************************************/
WinServiceManager :: ~WinServiceManager(void)
{
	if (init)
	{
		CloseServiceHandle(hSCM);
		init = false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. Destructor");
	#endif
}

/****************************************************************

   Class : WinServiceManager

   Method : GetServiceStatus

   Parameters :
			Output : 
				status - pointer to service status information
						 structure
   
   Returns: zero, if successful, nonzero - otherwise.

   Description : Get service status information

*****************************************************************/
int WinServiceManager :: GetServiceStatus(LPSERVICE_STATUS status)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. GetServiceStatus. Start");
	#endif

	// Check initialization flag
	if (!init)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. GetServiceStatus. Service manager not initialized!");
			WriteToLog("WinServiceManager. GetServiceStatus. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	SC_HANDLE hService;
	
	// Open service
	hService = OpenService(hSCM, serviceName, SERVICE_QUERY_STATUS);
    if (hService == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. GetServiceStatus. Can't open service!");
			WriteToLog("WinServiceManager. GetServiceStatus. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	// Get service status information
	BOOL queryResult = QueryServiceStatus(hService, status);
	CloseServiceHandle(hService);

	if (queryResult)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. GetServiceStatus. Service status information was retrieved successfully");
			WriteToLog("WinServiceManager. GetServiceStatus. Done.");
		#endif

		return ERROR_SUCCESS;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. GetServiceStatus. Can't get service status information!");
			WriteToLog("WinServiceManager. GetServiceStatus. Done.");
		#endif

		return ERROR_INVALID_DATA;
	}
}

/****************************************************************

   Class : WinServiceManager

   Method : StartService

   Returns: zero, if successful, nonzero - otherwise.

   Description : Start service

*****************************************************************/
int WinServiceManager :: StartService(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. StartService. Start");
	#endif

	// Check initialization flag
	if (!init)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. StartService. Service manager not initialized!");
			WriteToLog("WinServiceManager. StartService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	SC_HANDLE hService;
	SERVICE_STATUS Status;

	// Open service handle with SERVICE_START and SERVICE_QUERY_STATUS access
	hService = OpenService(hSCM, serviceName, SERVICE_START|SERVICE_QUERY_STATUS);

	if (hService == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. StartService. Can't open service!");
			WriteToLog("WinServiceManager. StartService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	// Start the service
	if (!::StartService(hService, 0, NULL))
	{
		CloseServiceHandle(hService);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. StartService. Service start failed!");
			WriteToLog("WinServiceManager. StartService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	// Poll service status
	while(TRUE)
	{
		
		// Get service status information
		if (!QueryServiceStatus(hService, &Status))
		{
			CloseServiceHandle(hService);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
				WriteToLog("WinServiceManager. StartService. Can't get service status information!");
				WriteToLog("WinServiceManager. StartService. Done.");
			#endif

			return ERROR_INVALID_DATA;
		}

		// Check current state
		if (Status.dwCurrentState != SERVICE_START_PENDING)	break;

		DWORD dwWait = Status.dwWaitHint;

		if (dwWait == 0) dwWait = 1000;

		Sleep(dwWait);
	}

	// Close service
	CloseServiceHandle(hService);

	// Check service state
	if (Status.dwCurrentState != SERVICE_RUNNING)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. StartService. Service start failed!");
			WriteToLog("WinServiceManager. StartService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;	
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. StartService. Service started successfully!");
		WriteToLog("WinServiceManager. StartService. Done.");
	#endif

	return ERROR_SUCCESS;	
}

/****************************************************************

   Class : WinServiceManager

   Method : StopService

   Returns: zero, if successful, nonzero - otherwise.

   Description : Stop service

*****************************************************************/
int WinServiceManager :: StopService(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. StopService. Start");
	#endif

	// Check initialization flag
	if (!init)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. StopService. Service manager not initialized!");
			WriteToLog("WinServiceManager. StopService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	SC_HANDLE hService;

	// Open service handle with SERVICE_STOP and SERVICE_QUERY_STATUS access
	hService = OpenService(hSCM, serviceName, SERVICE_STOP|SERVICE_QUERY_STATUS);
	
	if (hService == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. StopService. Can't open service!");
			WriteToLog("WinServiceManager. StopService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	// Send SERVICE_CONTROL_STOP command to the service and wait until it
	// reaches SERVICE_STOPPED state
	BOOL srvCntRes = ControlServiceAndWait(hService, SERVICE_CONTROL_STOP, SERVICE_STOPPED, 120000);
	CloseServiceHandle(hService);

	if (srvCntRes)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. StopService. Service stopped successfully");
			WriteToLog("WinServiceManager. StopService. Done.");
		#endif

		return ERROR_SUCCESS;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. StopService. Can't stop service!");
			WriteToLog("WinServiceManager. StopService. Done.");
		#endif

		return ERROR_INVALID_DATA;
	}
}

/****************************************************************

   Class : WinServiceManager

   Method : PauseService

   Returns: zero, if successful, nonzero - otherwise.

   Description : Pause service

*****************************************************************/
int WinServiceManager :: PauseService(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. PauseService. Start");
	#endif

	// Check initialization flag
	if (!init)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. PauseService. Service manager not initialized!");
			WriteToLog("WinServiceManager. PauseService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	SC_HANDLE hService;

	// Open service handle with SERVICE_PAUSE_CONTINUE and SERVICE_QUERY_STATUS access
	hService = OpenService(hSCM, serviceName, SERVICE_PAUSE_CONTINUE|SERVICE_QUERY_STATUS);
	
	if (hService == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. PauseService. Can't open service!");
			WriteToLog("WinServiceManager. PauseService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	// Send SERVICE_CONTROL_PAUSE command to the service and wait until it
	// reaches SERVICE_PAUSED state
	BOOL srvCntRes = ControlServiceAndWait(hService, SERVICE_CONTROL_PAUSE, SERVICE_PAUSED, 120000);
	CloseServiceHandle(hService);

	if (srvCntRes)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. PauseService. Service paused successfully");
			WriteToLog("WinServiceManager. PauseService. Done.");
		#endif

		return ERROR_SUCCESS;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. PauseService. Can't pause service!");
			WriteToLog("WinServiceManager. PauseService. Done.");
		#endif

		return ERROR_INVALID_DATA;
	}
}

/****************************************************************

   Class : WinServiceManager

   Method : ContinueService

   Returns: zero, if successful, nonzero - otherwise.

   Description : Continue service

*****************************************************************/
int WinServiceManager :: ContinueService(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. ContinueService. Start");
	#endif

	// Check initialization flag
	if (!init)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. ContinueService. Service manager not initialized!");
			WriteToLog("WinServiceManager. ContinueService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	SC_HANDLE hService;

	// Open service handle with SERVICE_PAUSE_CONTINUE and SERVICE_QUERY_STATUS access
	hService = OpenService(hSCM, serviceName, SERVICE_PAUSE_CONTINUE|SERVICE_QUERY_STATUS);
	
	if (hService == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. ContinueService. Can't open service!");
			WriteToLog("WinServiceManager. ContinueService. Done.");
		#endif

		return ERROR_INVALID_HANDLE;
	}

	// Send SERVICE_PAUSE_CONTINUE command to the service and wait until it
	// reaches SERVICE_RUNNING state
	BOOL srvCntRes = ControlServiceAndWait(hService, SERVICE_PAUSE_CONTINUE, SERVICE_RUNNING, 120000);
	CloseServiceHandle(hService);

	if (srvCntRes)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. ContinueService. Service continued successfully");
			WriteToLog("WinServiceManager. ContinueService. Done.");
		#endif

		return ERROR_SUCCESS;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. ContinueService. Can't continue service!");
			WriteToLog("WinServiceManager. ContinueService. Done.");
		#endif

		return ERROR_INVALID_DATA;
	}

}

/****************************************************************

   Class : WinServiceManager

   Method : RestartService

   Returns: zero, if successful, nonzero - otherwise.

   Description : Restart service

*****************************************************************/
int WinServiceManager :: RestartService(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. RestartService. Start");
	#endif

	int res = StopService();

	if (res != ERROR_SUCCESS) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. RestartService. Done");
		#endif

		return res;
	}

	res = StartService();
	if (res != ERROR_SUCCESS) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. RestartService. Done");
		#endif

		return res;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. RestartService. Done");
	#endif

	return ERROR_SUCCESS;
}

/****************************************************************

   Class : WinServiceManager

   Method : ControlServiceAndWait

   Parameters:
			Input:
				hService  - service handle
				dwControl - control code
				dwState	- service state to wait for
				dwTimeout - timeout in milliseconds

   Returns: TRUE, if successful, FALSE - otherwise.

   Description : Restart service

*****************************************************************/
BOOL WinServiceManager :: ControlServiceAndWait(SC_HANDLE hService, DWORD dwControl, DWORD dwState, DWORD dwTimeout)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. ControlServiceAndWait. Start");
	#endif

	// Check initialization flag
	if (hService == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. ControlServiceAndWait. Bad service handler!");
			WriteToLog("WinServiceManager. ControlServiceAndWait. Done.");
		#endif

		return FALSE;
	}

	SERVICE_STATUS Status;
	DWORD dwStart;
	DWORD dwCheckPoint = (DWORD) - 1;
	DWORD dwWait;

	// Send control code
	if (!ControlService(hService, dwControl, &Status))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. ControlServiceAndWait. Control code sending failed!");
			WriteToLog("WinServiceManager. ControlServiceAndWait. Done.");
		#endif

		return FALSE;
	}

	// Remember when the operation was started
	dwStart = GetTickCount();

	// Wait until the service reaches the specified state
	while (Status.dwCurrentState != dwState &&
		   Status.dwCurrentState != SERVICE_STOPPED)
	{
		// Check if timeout has expired
		if (dwTimeout != INFINITE)
		{
			if (GetTickCount() - dwStart >= dwTimeout)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
					WriteToLog("WinServiceManager. ControlServiceAndWait. Time out error!");
					WriteToLog("WinServiceManager. ControlServiceAndWait. Done.");
				#endif

				return SetLastError(ERROR_TIMEOUT), FALSE;
			}
		}

		// Determine how long to wait
		if (dwCheckPoint != Status.dwCheckPoint)
		{
			dwCheckPoint = Status.dwCheckPoint;
			dwWait = Status.dwWaitHint;
		}
		else
		{
			dwWait = 1000;
		}

		// Do wait
		Sleep(dwWait);

		// Query service status
		if (!QueryServiceStatus(hService, &Status))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
				WriteToLog("WinServiceManager. ControlServiceAndWait. Can't get service status information!");
				WriteToLog("WinServiceManager. ControlServiceAndWait. Done.");
			#endif

			return FALSE;
		}
	}

	if (Status.dwCurrentState == SERVICE_STOPPED &&
		Status.dwWin32ExitCode != ERROR_SUCCESS)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. ControlServiceAndWait. Control code setting error!");
			WriteToLog("WinServiceManager. ControlServiceAndWait. Done.");
		#endif

		SetLastError(Status.dwWin32ExitCode);
		return FALSE;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. ControlServiceAndWait. Done.");
	#endif

	return TRUE;
}

/****************************************************************

   Class : WinServiceManager

   Method : SetServiceName

   Parameters:
			Input:
				serviceName  - service name

   Description : Set service name

*****************************************************************/
void WinServiceManager :: SetServiceName(WCHAR * serviceName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. SetServiceName. Start");
	#endif

	// Check input parameter
	if (serviceName == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinServiceManager. SetServiceName. Bad service name!");
			WriteToLog("WinServiceManager. SetServiceName. Done");
		#endif

		return;
	}

	// Check initialization flag
	wcscpy(this -> serviceName, serviceName);

	if (!init)
	{
		init = true;
			
		// Open handle to the service manager
		hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
		if (hSCM == NULL)
		{
			init = false;
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
				WriteToLog("WinServiceManager. SetServiceName. Can't open SCM!");
			#endif
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			else
				WriteToLog("WinServiceManager. SetServiceName. SCM opened");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinServiceManager. SetServiceName. Done");
	#endif
}

/****************************************************************

   Class : WinServiceManager

   Method : GetServiceName
      
   Returns: Pointer to service name

   Description : Get service name

*****************************************************************/
WCHAR * WinServiceManager :: GetServiceName(void)
{
	return serviceName;
}

/****************************************************************

   Class : WinServiceManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int WinServiceManager :: WriteToLog(char * message)
{
    if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}