/****************************************************************

   Solution : NovaTend

   Project : z-srvsrv-01.dll

   Module : ServerService.h

   Description :  this module defines interface of 
				  class ServerService

				  This class is designed only for the 
				  Windows operating systems.

*****************************************************************/
#include <IPCServerEx.h>
#include <WinService.h>
#include <CommandManager.h>
#include <LogWriter.h>

#ifdef ZSRVSRV01_EXPORTS
#define SERVER_SERVICE_API __declspec(dllexport)
#else
#define SERVER_SERVICE_API __declspec(dllimport)
#endif

#ifndef SERVER_SERVICE_H
#define SERVER_SERVICE_H

/****************************************************************

   Class : ServerService

   Description : provides functionallity of application
				 server windows service. Derived from WinService.

*****************************************************************/
class SERVER_SERVICE_API ServerService : public WinService
{
	protected :

		// IPC server
		IPCServerEx * ipcServer;
		
		// Command manager
		CommandManager * commandManager;

		// Delete instances
		virtual void Cleanup(void);

		// Check license
		virtual bool CheckLicense(PSERVER_DESCRIPTION pServer);

		// Get maximum count of clients
		virtual int GetMaxClientsCount(void);
		
	public :

		// Constructor
		ServerService(unsigned long dllUserID,
						   WCHAR * serviceName = L"Server Service",
						   WCHAR * servicePath = L"",
						   BOOL fCanStop = TRUE,
						   BOOL fCanShutdown = TRUE,
						   BOOL fCanPauseContinue = FALSE,
						   unsigned short logWriterMode = LOG_MODE_WRITE_TO_FILE,
						   char * logFilesPath = "",
						   int logFileSize = 0);

		// Destructor
		virtual ~ServerService(void);

	protected :

		// Executes when a Start command is sent to the service by the SCM
		// or when the operating system starts
		virtual void OnStart(DWORD dwArgc, PWSTR *pszArgv);

		// Executes when a Stop command is sent to the service by the SCM
		virtual void OnStop(void);

		// Executes when a Pause command is sent to the service by the SCM
		virtual void OnPause(void);

		// Executes when a Continue command is sent to the service by the SCM
		virtual void OnContinue(void);

		// Executes when a Shutdown command is sent to the service by the SCM
		virtual void OnShutdown(void);
};

#endif