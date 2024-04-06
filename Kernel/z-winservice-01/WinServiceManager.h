/****************************************************************

   Solution : NovaTend

   Project : z-winservice-01.dll

   Module : WinServiceManager.h

   Description :  this module defines interface of 
				  class WinServiceManager

*****************************************************************/

#ifdef ZWINSERVICE01_EXPORTS
#define WINSERVICE_API __declspec(dllexport)
#else
#define WINSERVICE_API __declspec(dllimport)
#endif

#ifndef WINSERVICEMANAGER_H
#define WINSERVICEMANAGER_H

#include "WinService.h"

/****************************************************************

   Class : WinServiceManager

   Description : Provides a base class for a service manager 
				 that will exist as part of a service 
				 manager application.

				 This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class WINSERVICE_API WinServiceManager : public SystemBase
{
	private:
		
		// SCM handle
		SC_HANDLE hSCM;

		// The name of the service
		WCHAR serviceName[SERVICE_NAME_LEN];

		// Initialalization flag
		bool init;

		// Log writer instance
		LogWriter * logWriter;

		//  Sends a control request to a service and waits until the 
		//  service reaches	the specified state.
		BOOL ControlServiceAndWait(SC_HANDLE hService, DWORD dwControl, DWORD dwState, DWORD dwTimeout);

	public:

		// Constructor
		WinServiceManager(unsigned long dllUserID, WCHAR * serviceName = L"", LogWriter * logWriter = NULL);

		// Destructor
		~WinServiceManager(void);

		// Set service name
		void SetServiceName(WCHAR * serviceName);

		// Get service name
		WCHAR * GetServiceName(void);

		// Get service status information
		int GetServiceStatus(LPSERVICE_STATUS status);

		// Start service
		int StartService(void);

		// Stop service
		int StopService(void);

		// Pause service
		int PauseService(void);

		// Continue service
		int ContinueService(void);

		// Restart service
		int RestartService(void);

		// Write message to Log-file
		int WriteToLog(char * message);
};

#endif