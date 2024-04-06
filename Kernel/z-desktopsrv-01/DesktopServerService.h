/****************************************************************

   Solution : NovaTend

   Project : z-desktopsrv-01.exe

   Module : DesktopServerService.h

   Description :  this module defines interface of 
				  class DesktopServerService

*****************************************************************/
#include <IPCServer.h>
#include <IPCClientsManager.h>
#include <DesktopCommandManager.h>
#include <ProgramsController.h>
#include <WinExceptionHandler.h>

#include <SafeLogWriter.h>

#ifndef DESKTOP_SERVER_SERVICE_H
#define DESKTOP_SERVER_SERVICE_H

/****************************************************************

   Class : DesktopServerService

   Description : provides functionallity of DESKTOP
				 server service

				 This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class DesktopServerService
{
	private:
		
		// Service name
		char serviceName[256];

		// Exception handler
		WinExceptionHandler * exceptionHandler;

		// Command manager
		DesktopCommandManager * desktopCommandManager;

		// IPC server
		IPCServer * ipcServer;

		// Connections to the HUB servers
		IPCClientsManager * hubConnectionsMananger;

		//Programs controller
		ProgramsController * programsController;


		// The path to the LOG-files vault
		char logFilesPath[MAX_PATH];

		// Log writer instance
		LogWriter * logWriter;


		// Creates log file name
		char * CreateLogFileName(char * fileName);

		// Delete instances
		void Cleanup(void);

		// Check license
		bool CheckLicense(PSERVER_DESCRIPTION pServer);

		// Get maximum count of clients
		int GetMaxClientsCount(void);


	public:

		// Constructor
		DesktopServerService(char * serviceName = "DESKTOP server");

		// Destructor
		virtual ~DesktopServerService(void);

		// Start DESKTOP-server
		bool Start(void);

		// Stop DESKTOP-server
		bool Stop(void);

		// Write message to Log-file
		int WriteToLog(char * message);
};

#endif