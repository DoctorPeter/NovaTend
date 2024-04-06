/****************************************************************

   Solution : NovaTend

   Project : z-winservice-01.dll

   Module : WinService.cpp

   Description :  this module implements methods of
				  class WinService

*****************************************************************/

#include "stdafx.h"

#include "WinService.h"
#include <time.h>
#include <stdlib.h>

// z-winservice-01.dll definition structure
extern DLL_COMMON_DEFINITION zWinServiceDllDefinition;

// Initialize the singleton service instance.
WinService * WinService :: _this = NULL;

/****************************************************************

   Class : WinService

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				serviceName - name of service
				servicePath - path to service executable
				fCanStop - flag can be stopped
				fCanShutdown - flag can be shutdown
				fCanPauseContinue - flag can be paused

*****************************************************************/
WinService :: WinService(unsigned long dllUserID,
				   WCHAR * srvName,
				   WCHAR * srvPath,
				   BOOL fCanStop,
				   BOOL fCanShutdown,
				   BOOL fCanPauseContinue,
				   unsigned short logWriterMode,
				   char * logFilesPath,
				   int logFileSize) : SystemBase(dllUserID, &zWinServiceDllDefinition)
{
	exceptionHandler = NULL;
	logWriter = NULL;
	
	this -> logWriterMode = logWriterMode;
	this -> logFileFixedSize = logFileSize;
	if (logFilesPath)
		strcpy(this -> logFilesPath, logFilesPath);
	else
		strcpy(this -> logFilesPath, "");

	// Set service string params
	if (srvName != NULL)
		wcscpy(serviceName, srvName);
	else
		wcscpy(serviceName, L"Windows Service");

	if (srvPath != NULL)
		wcscpy(servicePath, srvPath);
	else
		wcscpy(servicePath, L"");

	// Service status handle to NULL
	hServiceStatusHandle = NULL;
	
	// Set service status
    serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;

    // The service is starting.
    serviceStatus.dwCurrentState = SERVICE_START_PENDING;

    // The accepted commands of the service.
    DWORD dwControlsAccepted = 0;

	// Check flags
    if (fCanStop) 
        dwControlsAccepted |= SERVICE_ACCEPT_STOP;

    if (fCanShutdown) 
        dwControlsAccepted |= SERVICE_ACCEPT_SHUTDOWN;

    if (fCanPauseContinue) 
        dwControlsAccepted |= SERVICE_ACCEPT_PAUSE_CONTINUE;

    serviceStatus.dwControlsAccepted = dwControlsAccepted;

    serviceStatus.dwWin32ExitCode = NO_ERROR;
    serviceStatus.dwServiceSpecificExitCode = 0;
    serviceStatus.dwCheckPoint = 0;
    serviceStatus.dwWaitHint = 0;
}

/****************************************************************

   Class : WinService

   Method : Destructor
   
*****************************************************************/
WinService :: ~WinService(void)
{
	if (exceptionHandler)
		delete exceptionHandler;

	if (logWriter)
	{
		delete logWriter;
	}
}


/****************************************************************

   Class : WinService

   Method : Run

   Returns: service running status

   Description : Connects the main thread of a service process to 
				 the service control manager, which causes the thread
				 to be the service control dispatcher thread for the 
				 calling process. This call returns when the service has
				 stopped. The process should simply terminate when 
				 the call returns.

*****************************************************************/
BOOL WinService :: Run(void)
{
   // Save pointer to service
	_this = this + dllUserCheckResult;
	
	// Prepare service table
    SERVICE_TABLE_ENTRY serviceTable[] = 
    {
		{serviceName, ServiceMain},
        {NULL, NULL}
    };

	// Start service control dispatcher
	BOOL result = StartServiceCtrlDispatcher(serviceTable);

    return result;
}

/****************************************************************

   Class : WinService

   Method : ServiceMain

   Parameters :
			Input : 
				dwArgc   - number of command line arguments
				lpszArgv - array of command line arguments

   Description : Entry point for the service. It registers the 
				 handler function for the service and starts
				 the service.

*****************************************************************/
void WINAPI WinService :: ServiceMain(DWORD dwArgc, PWSTR *pszArgv)
{
    if (_this != NULL)
	{
		// Create log writer
		char filePath[MAX_PATH];
		_this -> logWriter = new SafeLogWriter(zWinServiceDllDefinition.dllID, _this -> logWriterMode, _this -> CreateLogFileName(filePath), _this -> logFileFixedSize);
		_this -> exceptionHandler = new WinExceptionHandler(zWinServiceDllDefinition.dllID, _this -> logWriter);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			_this -> WriteToLog("WinService : ServiceMain. Start");
		#endif

		// Register the handler function for the service
		_this -> hServiceStatusHandle = RegisterServiceCtrlHandler(_this -> serviceName, ServiceCtrlHandler);

		if (_this -> hServiceStatusHandle == NULL)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
				_this -> WriteToLog("WinService : ServiceMain. Error of register service conroller handler!");
			#endif
		}
		else
		{
			// Start the service.
			_this -> Start(dwArgc, pszArgv);
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			_this -> WriteToLog("WinService : ServiceMain. Done");
		#endif
	}
}

/****************************************************************

   Class : WinService

   Method : ServiceCtrlHandler

   Parameters :
			Input : 
				dwCtrlCode - the control code. 

   Description : The function is called by the SCM whenever
				 a control code is sent to the service.

*****************************************************************/
void WINAPI WinService :: ServiceCtrlHandler(DWORD dwCtrl)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		_this -> WriteToLog("WinService : ServiceCtrlHandler. Start");
	#endif

    switch (dwCtrl)
    {
		case SERVICE_CONTROL_STOP :			
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
					_this -> WriteToLog("WinService : ServiceCtrlHandler. SERVICE_CONTROL_STOP");
				#endif

				_this -> Stop(); 
				break;
			}

		case SERVICE_CONTROL_PAUSE :
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
					_this -> WriteToLog("WinService : ServiceCtrlHandler. SERVICE_CONTROL_PAUSE");
				#endif

				_this -> Pause();
				break;
			}

		case SERVICE_CONTROL_CONTINUE :
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
					_this -> WriteToLog("WinService : ServiceCtrlHandler. SERVICE_CONTROL_CONTINUE");
				#endif

				_this -> Continue();
				break;
			}

		case SERVICE_CONTROL_SHUTDOWN :
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
					_this -> WriteToLog("WinService : ServiceCtrlHandler. SERVICE_CONTROL_SHUTDOWN");
				#endif

				_this -> Shutdown();
				break;
			}

		case SERVICE_CONTROL_INTERROGATE :	break;

		default :							break;
    }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		_this -> WriteToLog("WinService : ServiceCtrlHandler. Done");
	#endif
}

/****************************************************************

   Class : WinService

   Method : Start

   Parameters :
			Input : 
				dwArgc   - number of command line arguments
				lpszArgv - array of command line arguments

   Description : The function starts the service. It calls the 
				 OnStart virtual function in which you can specify
				 the actions to take when the service starts.
				 If an error occurs during the startup, the error 
				 will be logged and the service will be stopped.

*****************************************************************/
void WinService :: Start(DWORD dwArgc, PWSTR *pszArgv)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : Start. Start");
	#endif

    try
    {
        // Tell SCM that the service is starting.
		SetServiceStatus(SERVICE_START_PENDING + dllUserCheckResult);

        // Perform service-specific initialization.
        OnStart(dwArgc, pszArgv);

        // Tell SCM that the service is started.
		SetServiceStatus(SERVICE_RUNNING + dllUserCheckResult);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinService : Start. Service successfully started");
		#endif
    }
    catch (...)
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			// Log the error.
			WriteToLog("WinService : Start. Service failed to start");
		#endif
        
        // Set the service status to be stopped.
		SetServiceStatus(SERVICE_STOPPED + dllUserCheckResult);
    }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : Start. Done");
	#endif
}

/****************************************************************

   Class : WinService

   Method : OnStart

   Parameters :
			Input : 
				dwArgc   - number of command line arguments
				lpszArgv - array of command line arguments

   Description : When implemented in a derived class, executes when 
				 a Start command is sent to the service by the SCM or 
				 when the operating system starts (for a service that
				 starts automatically). Specifies actions to take when
				 the service starts. Be sure to periodically call 
				 SetServiceStatus() with SERVICE_START_PENDING
				 if the procedure is going to take long time. You may also 
				 consider spawning a new thread in OnStart to perform 
				 time-consuming initialization tasks.

*****************************************************************/
void WinService :: OnStart(DWORD dwArgc, PWSTR *pszArgv)
{
}

/****************************************************************

   Class : WinService

   Method : Stop

   Description : The function stops the service. It calls the 
                 OnStop virtual function in which you can specify
				 the actions to take when the service stops. If an
				 error occurs, the error will be logged and the 
				 service will be restored to the original state.

*****************************************************************/
void WinService :: Stop(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : Stop. Start");
	#endif

	DWORD dwOriginalState = serviceStatus.dwCurrentState;

    try
    {
        // Tell SCM that the service is stopping.
        SetServiceStatus(SERVICE_STOP_PENDING);

        // Perform service-specific stop operations.
        OnStop();

        // Tell SCM that the service is stopped.
        SetServiceStatus(SERVICE_STOPPED);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinService : Stop. Service stopped");
		#endif
    }
    catch (...)
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			// Log the error.
			WriteToLog("WinService : Stop. Service failed to stop");
		#endif

        // Set the orginal service status.
        SetServiceStatus(dwOriginalState);
    }


	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : Stop. Done");
	#endif
}

/****************************************************************

   Class : WinService

   Method : OnStop

   Description : When implemented in a derived class, executes when
                 a Stop command is sent to the service by the SCM. 
				 Specifies actions to take when a service stops running.
				 Be sure to periodically call SetServiceStatus() with 
				 SERVICE_STOP_PENDING if the procedure is going to take
				 long time. 

*****************************************************************/
void WinService :: OnStop(void)
{
}

/****************************************************************

   Class : WinService

   Method : Pause

   Description : The function pauses the service if the service 
                 supports pause and continue. It calls the OnPause
				 virtual function in which you can specify the actions
				 to take when the service pauses. If an error occurs,
				 the error will be logged and the service will become
				 running.

*****************************************************************/
void WinService :: Pause(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : Pause. Start");
	#endif

	try
    {
        // Tell SCM that the service is pausing.
        SetServiceStatus(SERVICE_PAUSE_PENDING);

        // Perform service-specific pause operations.
        OnPause();

        // Tell SCM that the service is paused.
        SetServiceStatus(SERVICE_PAUSED);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			 WriteToLog("WinService : Pause. Service paused");
		#endif
    }
    catch (...)
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			// Log the error.
			WriteToLog("WinService : Pause. Service failed to pause");
		#endif

        // Tell SCM that the service is still running.
        SetServiceStatus(SERVICE_RUNNING);
    }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		 WriteToLog("WinService : Pause. Done");
	#endif
}

/****************************************************************

   Class : WinService

   Method : OnPause

   Description : When implemented in a derived class, executes when
                 a Pause command is sent to the service by the SCM. 
				 Specifies actions to take when a service pauses.

*****************************************************************/
void WinService :: OnPause(void)
{
}

/****************************************************************

   Class : WinService

   Method : Continue

   Description : The function resumes normal functioning after being
                 paused if the service supports pause and continue. 
				 It calls the OnContinue virtual function in which
				 you can specify the actions to take when the service 
				 continues. If an error occurs, the error will be 
				 logged and the service will still be paused.

*****************************************************************/
void WinService :: Continue(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : Continue. Start");
	#endif

    try
    {
        // Tell SCM that the service is resuming.
        SetServiceStatus(SERVICE_CONTINUE_PENDING);

        // Perform service-specific continue operations.
        OnContinue();

        // Tell SCM that the service is running.
        SetServiceStatus(SERVICE_RUNNING);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinService : Continue. Service resumed");
		#endif
    }
    catch (...)
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			// Log the error.
       		WriteToLog("WinService : Continue. Service failed to resume");
		#endif

        // Tell SCM that the service is still paused.
        SetServiceStatus(SERVICE_PAUSED);
    }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : Continue. Done");
	#endif
}

/****************************************************************

   Class : WinService

   Method : OnContinue

   Description :  When implemented in a derived class, OnContinue 
                  runs when a Continue command is sent to the service
				  by the SCM. Specifies actions to take when a 
				  service resumes normal functioning after 
				  being paused.

*****************************************************************/
void WinService :: OnContinue(void)
{
}

/****************************************************************

   Class : WinService

   Method : Shutdown

   Description :  The function executes when the system is 
                  shutting down. It calls the OnShutdown virtual 
				  function in which you can specify what should
				  occur immediately prior to the system shutting down.
				  If an error occurs, the error will be logged.

*****************************************************************/
void WinService :: Shutdown(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : Shutdown. Start");
	#endif

    try
    {
        // Perform service-specific shutdown operations.
        OnShutdown();

        // Tell SCM that the service is stopped.
        SetServiceStatus(SERVICE_STOPPED);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			WriteToLog("WinService : Shutdown. Sevice shut down");
		#endif
    }
    catch (...)
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
			// Log the error.
    		WriteToLog("WinService : Shutdown. Service failed to shut down");
		#endif
    }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : Shutdown. Done");
	#endif
}

/****************************************************************

   Class : WinService

   Method : Shutdown

   Description :  When implemented in a derived class, executes
                  when the system is shutting down. Specifies what
				  should occur immediately prior to the system
				  shutting down.

*****************************************************************/
void WinService :: OnShutdown(void)
{
}


/****************************************************************

   Class : WinService

   Method : SetServiceStatus

   Parameters :
			Input : 
			     dwCurrentState - the state of the service
				 dwWin32ExitCode - error code to report
				 dwWaitHint - estimated time for pending operation, 
				              in milliseconds

   Description :  The function sets the service status and reports 
                  the status to the SCM.

*****************************************************************/
void WinService :: SetServiceStatus(DWORD dwCurrentState, 
                                    DWORD dwWin32ExitCode, 
                                    DWORD dwWaitHint)
{
    
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_WINSRV)
		WriteToLog("WinService : SetServiceStatus");
	#endif

	static DWORD dwCheckPoint = 1;

    // Fill in the SERVICE_STATUS structure of the service.

	serviceStatus.dwCurrentState = dwCurrentState;
    serviceStatus.dwWin32ExitCode = dwWin32ExitCode;
    serviceStatus.dwWaitHint = dwWaitHint;

    serviceStatus.dwCheckPoint = 
        ((dwCurrentState == SERVICE_RUNNING) ||
        (dwCurrentState == SERVICE_STOPPED)) ? 
        0 : dwCheckPoint++;

    // Report the status of the service to the SCM.
	::SetServiceStatus(hServiceStatusHandle, &serviceStatus);
}

/****************************************************************

   Class : WinService

   Method : Install

   Parameters :
			Input : 
				pszServiceName - the name of the service 
				                 to be installed
				pszDisplayName - the display name of 
				                 the service
				dwStartType - the service start option. This 
				              parameter can be one of the following 
							  values: SERVICE_AUTO_START, SERVICE_BOOT_START, 
						      SERVICE_DEMAND_START, SERVICE_DISABLED, 
							  SERVICE_SYSTEM_START.
				pszDependencies - a pointer to a double null-terminated 
								  array of null-separated names of services
								  or load ordering groups that the system 
								  must start before this service.
				pszAccount - the name of the account under which 
				             the service runs.
				pszPassword - the password to the account name.

   Returns: error code

   Description :  Install the current application as a service 
				  to the local service control manager database.

*****************************************************************/
DWORD  WinService :: Install(PWSTR pszServiceName,
							 PWSTR pszDisplayName,
							 PWSTR pszDescription,
							 PWSTR pszExeName,
							 DWORD dwStartType,
							 PWSTR pszDependencies,
							 PWSTR pszAccount,
							 PWSTR pszPassword)
{
	SC_HANDLE schSCManager = NULL;
    SC_HANDLE schService = NULL;

     // Open the local default service control manager database
    schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE);
    if (schSCManager == NULL)
    {
		DWORD error = GetLastError();
        return error;
    }

    // Install the service into SCM by calling CreateService
    schService = CreateService(schSCManager,				// SCManager database
							   pszServiceName,				// Name of service
							   pszDisplayName,			    // Name to display
							   SERVICE_ALL_ACCESS,			// Desired access
							   SERVICE_WIN32_OWN_PROCESS | 
							   SERVICE_INTERACTIVE_PROCESS, // Service type
							   dwStartType,					// Service start type
							   SERVICE_ERROR_NORMAL,        // Error control type
							   pszExeName,                  // Service's binary
							   NULL,                        // No load ordering group
							   NULL,                        // No tag identifier
							   pszDependencies,				// Dependencies
							   pszAccount,					// Service running account
							   pszPassword);				// Password of the account
        
    if (schService == NULL)
    {
        DWORD error = GetLastError();
	    CloseServiceHandle(schSCManager);
        schSCManager = NULL;
        return error;
    }

	SERVICE_DESCRIPTION sd;
	sd.lpDescription = pszDescription;

	if (sd.lpDescription)
	{
		if (ChangeServiceConfig2(schService, SERVICE_CONFIG_DESCRIPTION, &sd) == FALSE)
		{
			DWORD error = GetLastError();
			CloseServiceHandle(schSCManager);
			CloseServiceHandle(schService);
			schSCManager = NULL;
			schService = NULL;
			return error;
		}
	}

    CloseServiceHandle(schSCManager);
	CloseServiceHandle(schService);
	return 0;
}

/****************************************************************

   Class : WinService

   Method : UnInstall

   Parameters :
			Input : 
				pszServiceName - the name of the service 

   Returns: error code

   Description :  Stop and remove the service from the local 
                  service control manager database.

*****************************************************************/
DWORD WinService :: UnInstall(PWSTR pszServiceName)
{
	SC_HANDLE schSCManager = NULL;
    SC_HANDLE schService = NULL;
    SERVICE_STATUS ssSvcStatus = {};

    // Open the local default service control manager database
    schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (schSCManager == NULL)
    {
        DWORD error = GetLastError();
        return error;
    }

    // Open the service with delete, stop, and query status permissions
    schService = OpenService(schSCManager, pszServiceName, SERVICE_STOP | SERVICE_QUERY_STATUS | DELETE);
    if (schService == NULL)
    {
        DWORD error = GetLastError();
	    CloseServiceHandle(schSCManager);
        schSCManager = NULL;

        return error;
    }

    // Try to stop the service
    if (ControlService(schService, SERVICE_CONTROL_STOP, &ssSvcStatus))
    {
        Sleep(1000);

        while (QueryServiceStatus(schService, &ssSvcStatus))
        {
            if (ssSvcStatus.dwCurrentState == SERVICE_STOP_PENDING)
            {
                Sleep(1000);
            }
            else break;
        }
    }

    // Now remove the service by calling DeleteService.
    if (!DeleteService(schService))
    {
		DWORD error = GetLastError();
        CloseServiceHandle(schSCManager);
        schSCManager = NULL;
        CloseServiceHandle(schService);
        schService = NULL;
		return error;
    }

	CloseServiceHandle(schSCManager);
    CloseServiceHandle(schService);
	return 0;
}


/****************************************************************

   Class : WinService

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int WinService :: WriteToLog(char * message)
{
    if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}

/****************************************************************

   Class : WinService

   Method : CreateLogFileName

   Parameters :
			Input/Output : 
				fileName - path to Log-file

	Return : log file name

	Description : Create name of log-file

*****************************************************************/
char * WinService :: CreateLogFileName(char * fileName)
{
	strcpy(fileName, logFilesPath);
	if (strcmp(fileName, "") != 0)
		strcat(fileName, "\\");
	
	// Convert service name
	char serviceNameBuf[64];
	wcstombs(serviceNameBuf, serviceName, 64);

	// Get current time
	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);
	char timeBuf[32];                                
    strftime(timeBuf, 32, "_%m.%d.%Y", timeinfo); 

	// Prepare file name
	strcat(fileName, serviceNameBuf);
	strcat(fileName, timeBuf);
	strcat(fileName, ".log");

	// Return file name
	return fileName;
}