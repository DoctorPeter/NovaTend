/****************************************************************

   Solution : NovaTend

   Project : z-winservice-01.dll

   Module : WinService.h

   Description :  this module defines interface of 
				  class WinService

*****************************************************************/

#include <windows.h>

#ifdef ZWINSERVICE01_EXPORTS
#define WINSERVICE_API __declspec(dllexport)
#else
#define WINSERVICE_API __declspec(dllimport)
#endif

#ifndef WINSERVICE_H
#define WINSERVICE_H

#include <SafeLogWriter.h>
#include <WinExceptionHandler.h>

// Define restrictions

// Maximum service name length
#define SERVICE_NAME_LEN					256

// Maximum service dependicies length
#define SERVICE_DEPENDENCIES_LEN			256

// Maximum service account name length
#define SERVICE_ACCOUNT_LEN					256

// Maximum service account password length
#define SERVICE_PASSWORD_LEN				256

/****************************************************************

   Class : WinService

   Description : Provides a base class for a service that will 
                 exist as part of a service application.

				 This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class WINSERVICE_API WinService : public SystemBase
{
	private:
		
		// The service status handle
		SERVICE_STATUS_HANDLE hServiceStatusHandle; 

		// The service status
		SERVICE_STATUS serviceStatus;

		// The name of the service
		WCHAR serviceName[SERVICE_NAME_LEN];

		// The path ro the service executable
		WCHAR servicePath[MAX_PATH];

		// Entry point for the service. It registers the handler function for the 
		// service and starts the service.
		static VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);

	    // The function is called by the SCM whenever a control code is sent to 
	    // the service.
		static VOID WINAPI ServiceCtrlHandler(DWORD fdwControl);

		// Start the service.
		void Start(DWORD dwArgc, PWSTR *pszArgv);
    
		// Pause the service.
		void Pause(void);

		// Resume the service after being paused.
		void Continue(void);

		// Execute when the system is shutting down.
		void Shutdown(void);

		// The singleton service instance.
		static WinService * _this;

	public:
		
		// Constructor
		WinService(unsigned long dllUserID,
				   WCHAR * serviceName = L"Windows Service",
				   WCHAR * servicePath = L"",
				   BOOL fCanStop = TRUE,
				   BOOL fCanShutdown = TRUE,
				   BOOL fCanPauseContinue = FALSE,
				   unsigned short logWriterMode = LOG_MODE_WRITE_TO_FILE,
				   char * logFilesPath = "",
				   int logFileSize = 0);

		// Destructor
		virtual ~WinService(void);
	
		// Register the executable for a service with the Service Control Manager 
	    // (SCM). After you call Run, the SCM issues a Start command, 
	    // which results in a call to the OnStart method in the service. This 
	    // method blocks until the service has stopped.
		BOOL Run(void);

		// Stop the service.
		void Stop(void);

		// Install the current application as a service to the local 
		// service control manager database.
		static DWORD Install(PWSTR pszServiceName,
							 PWSTR pszDisplayName,
							 PWSTR pszDescription,
							 PWSTR pszExeName,
							 DWORD dwStartType,
							 PWSTR pszDependencies,
							 PWSTR pszAccount,
							 PWSTR pszPassword);

		// Stop and remove the service from the local service control 
		// manager database.
		static DWORD UnInstall(PWSTR pszServiceName);

		// Write message to Log-file
		int WriteToLog(char * message);

	protected:

		// The path to the LOG-files vault
		char logFilesPath[MAX_PATH];

		// Log writer mode
		unsigned short logWriterMode;

		// LOG-file fixed size
		int logFileFixedSize;

		// Log writer instance
		LogWriter * logWriter;

		// Exception handler
		WinExceptionHandler * exceptionHandler;
		
		// Creates log file name
		char * CreateLogFileName(char * fileName);

		// When implemented in a derived class, executes when a Start command is 
		// sent to the service by the SCM or when the operating system starts 
		// (for a service that starts automatically). Specifies actions to take 
		// when the service starts.
		virtual void OnStart(DWORD dwArgc, PWSTR *pszArgv);

		// When implemented in a derived class, executes when a Stop command is 
		// sent to the service by the SCM. Specifies actions to take when a 
		// service stops running.
		virtual void OnStop(void);

		// When implemented in a derived class, executes when a Pause command is 
		// sent to the service by the SCM. Specifies actions to take when a 
		// service pauses.
		virtual void OnPause(void);

		// When implemented in a derived class, OnContinue runs when a Continue 
		// command is sent to the service by the SCM. Specifies actions to take 
		// when a service resumes normal functioning after being paused.
		virtual void OnContinue(void);

		// When implemented in a derived class, executes when the system is 
		// shutting down. Specifies what should occur immediately prior to the 
		// system shutting down.
		virtual void OnShutdown(void);

		// Set the service status and report the status to the SCM.
		void SetServiceStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode = NO_ERROR, DWORD dwWaitHint = 0);
};

#endif