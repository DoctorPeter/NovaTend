/****************************************************************

   Solution : NovaTend

   Project : z-hubsrv-01.exe

   Module : HubServerService.h

   Description :  this module defines interface of 
				  class HubServerService

				  This class is designed only for the 
				  Windows operating systems.

*****************************************************************/
#include <IPCServerEx.h>
#include <IPCClientsManagerEx.h>
#include <ServerService.h>
#include <HubCommandManager.h>
#include <PostLoginManager.h>
#include <CommandHistorian.h>
#include <LogWriter.h>

#ifndef HUB_SERVER_SERVICE_H
#define HUB_SERVER_SERVICE_H

/****************************************************************

   Class : HubServerService

   Description : provides functionallity of application
				 server windows service. Derived from WinService.

*****************************************************************/
class HubServerService : public ServerService
{
	protected :

		// Post login manager
		PostLoginManager * postLoginManager;

		// Commnd historian
		CommandHistorian * commandHistorian;

		// Connections to the HOST servers
		IPCClientsManagerEx * hostConnectionsMananger;

		// Connections to the DESKTOP servers
		IPCClientsManager * desktopConnectionsMananger;

		// Delete instances
		virtual void Cleanup(void);

	public :

		// Constructor
		HubServerService(WCHAR * serviceName = L"HUB-Server Service",
						   WCHAR * servicePath = L"",
						   BOOL fCanStop = TRUE,
						   BOOL fCanShutdown = TRUE,
						   BOOL fCanPauseContinue = FALSE,
						   unsigned short logWriterMode = LOG_MODE_WRITE_TO_FILE,
						   char * logFilesPath = "",
						   int logFileSize = 0);

		// Destructor
		virtual ~HubServerService(void);

	protected:

		// Executes when a Start command is sent to the service by the SCM
		// or when the operating system starts
		virtual void OnStart(DWORD dwArgc, PWSTR *pszArgv);
};

#endif