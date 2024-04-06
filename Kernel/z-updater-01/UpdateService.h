/****************************************************************

   Solution : NovaTend

   Project : z-updater-01.exe

   Module : UpdateService.h

   Description :  this module defines interface of 
				  class UpdateService

				  This class is designed only for the 
				  Windows operating systems.

*****************************************************************/
#include <IPCClientsManagerEx.h>
#include <WinService.h>
#include <HubCommandManager.h>
#include <ClientAuthManager.h>
#include <FileProcessor.h>
#include "UpdateManager.h"

#ifndef UPDATE_SERVICE_H
#define UPDATE_SERVICE_H

/****************************************************************

   Class : UpdateService

   Description : provides functionallity of system 
                 components updating. Derived from WinService.

*****************************************************************/
class UpdateService : public WinService
{
	private:
		
		// Update manager instance
		UpdateManager * updateManager;

		// File processor instance
		FileProcessor * fileProcessor;

		// Client authenticate manager instance
		ClientAuthManager * clientAuthManager;

		// Command manager
		HubCommandManager * hubCommandManager;

		// Connections to the HOST servers
		IPCClientsManagerEx * hostConnectionsMananger;

		// Connections to the DESKTOP servers
		IPCClientsManager * desktopConnectionsMananger;

		// Delete instances
		void Cleanup(void);

		// Prepare hub command manager client and server descriptions
		void PrepareHubCommandManager(void);

	public:

		// Constructor
		UpdateService(WCHAR * serviceName = L"Update Service",
					  WCHAR * servicePath = L"",
					  BOOL fCanStop = TRUE,
					  BOOL fCanShutdown = TRUE,
					  BOOL fCanPauseContinue = FALSE,
					  unsigned short logWriterMode = LOG_MODE_WRITE_TO_FILE,
					  char * logFilesPath = "",
					  int logFileSize = 0);

		// Destructor
		virtual ~UpdateService(void);

	protected:

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