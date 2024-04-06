/****************************************************************

   Solution : NovaTend

   Project : z-hostsrv-01.exe

   Module : HostServerService.h

   Description :  this module defines interface of 
				  class HostServerService

				  This class is designed only for the 
				  Windows operating systems.

*****************************************************************/

#include <IPCServerEx.h>
#include <IPCClientsManagerEx.h>
#include <ServerService.h>
#include <HostCommandManager.h>
#include <LogWriter.h>
#include <AutoUserAccountsSynchronizer.h>
#include <PostLoginManager.h>
#include <CommandHistorian.h>

#ifndef HOST_SERVER_SERVICE_H
#define HOST_SERVER_SERVICE_H

/****************************************************************

   Class : HostServerService

   Description : provides functionallity of application
				 server windows service. Derived from WinService.

*****************************************************************/
class HostServerService : public ServerService
{
	private:

		// Post login manager
		PostLoginManager * postLoginManager;

		// Commnd historian
		CommandHistorian * commandHistorian;

		// User accounts synchronizer
		AutoUserAccountsSynchronizer * userAccountsSynchronizer;

		// Connections to the HOST servers
		IPCClientsManagerEx * hostConnectionsMananger;

		// Connections to the DESKTOP servers
		IPCClientsManager * desktopConnectionsMananger;

		// Connections to the HUB servers
		IPCClientsManagerEx * hubConnectionsMananger;

		// Delete instances
		virtual void Cleanup(void);

	public:

		// Constructor
		HostServerService(WCHAR * serviceName = L"HOST-Server Service",
						   WCHAR * servicePath = L"",
						   BOOL fCanStop = TRUE,
						   BOOL fCanShutdown = TRUE,
						   BOOL fCanPauseContinue = FALSE,
						   unsigned short logWriterMode = LOG_MODE_WRITE_TO_FILE,
						   char * logFilesPath = "",
						   int logFileSize = 0);

		// Destructor
		virtual ~HostServerService(void);

		// Check DB access
		bool CheckServerAccess(void);

	protected:

		// Executes when a Start command is sent to the service by the SCM
		// or when the operating system starts
		virtual void OnStart(DWORD dwArgc, PWSTR *pszArgv);
};

#endif