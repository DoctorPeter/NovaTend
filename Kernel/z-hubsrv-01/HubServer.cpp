/****************************************************************

   Solution : NovaTend

   Project : z-hubsrv-01.exe

   Module : HubServer.cpp

   Description :  z-hubsrv-01 is the windows service that
				  implements HUB-server subsystem of NovaTend 
				  authentication system

				  This code is designed only for the 
				  Windows operating systems.

*****************************************************************/
#include "stdafx.h"

#include "HubServerService.h"
#include <SettingsManager.h>

// z-hubsrv-01.exe definition structure
DLL_COMMON_DEFINITION zHubServerServiceDefinition =
{
	Z_HUB_SERVER_ID,
	0x00010000,
	"z-hubsrv-01.exe - application HUB-server. Windows service",
	0,
	{}
};

int _tmain(int argc, _TCHAR* argv[])
{
	// Get service executalble path
	WCHAR pExeFileName[MAX_PATH + 1];
	DWORD dwSize = GetModuleFileName(NULL, pExeFileName, MAX_PATH);
	
	// Validate command line params
	if ((argc > 1) && ((*argv[1] == L'-' || (*argv[1] == L'/'))))
    {
        if (_wcsicmp(L"install", argv[1] + 1) == 0)
        {
            // Install the service when the command is 
            // "-install" or "/install".
			if (WinService :: Install(L"NovaTend_HUB_Server", 
									  L"NovaTend HUB-Server", 
									  L"The NovaTend HUB-server subsystem. This service provides functions of data retransator and client machine manager.", 
									  pExeFileName, 
									  SERVICE_AUTO_START, 
									  NULL, NULL, NULL))

				wprintf(L"Service installation failed!");
			else
				wprintf(L"Service successfully installed!");
        }
        else if (_wcsicmp(L"uninstall", argv[1] + 1) == 0)
        {
            // Uninstall the service when the command is 
            // "-uninstall" or "/uninstall".
            if (WinService :: UnInstall(L"NovaTend_HUB_Server"))
				wprintf(L"Service removing failed!");
			else
				wprintf(L"Service successfully uninstalled!");
        }
    }
    else
    {
        wprintf(L"Parameters:\n");
        wprintf(L" -install to install the service.\n");
        wprintf(L" -uninstall to remove the service.\n");
		
		bool encLog = false;
		bool emailLog = false;
		bool fixedSizeFlag = false;
		int fixeSizeValue = 0;
		char logFilesPath[ADDRESS_SIZE] = "";

		SettingsManager * settingsManager = new SettingsManager(zHubServerServiceDefinition.dllID);

		if (settingsManager -> GetLogEncryptFlag(&encLog) != ERROR_SUCCESS)
		{
			wprintf(L"Can't get log file encryption settings \n");
			delete settingsManager;
			return -1;
		}

		if (settingsManager -> GetLogEmailSendFlag(&emailLog) != ERROR_SUCCESS)
		{
			wprintf(L"Can't get log file EMAIL-sending settings \n");
			delete settingsManager;
			return -1;
		}

		if (settingsManager -> GetLogPath(logFilesPath) != ERROR_SUCCESS)
		{
			wprintf(L"Can't get log files vault path \n");
			delete settingsManager;
			return -1;
		}

		if (settingsManager -> GetLogFixedSizeFlag(&fixedSizeFlag) != ERROR_SUCCESS)
		{
			wprintf(L"Can't get log file fixed size flag settings \n");
			delete settingsManager;
			return -1;
		}

		if ((fixedSizeFlag) && (settingsManager -> GetLogFixedSizeValue(&fixeSizeValue) != ERROR_SUCCESS))
		{
			wprintf(L"Can't get log file fixed size value settings \n");
			delete settingsManager;
			return -1;
		}

		delete settingsManager;

		// Set log writer mode
		unsigned short logWriterMode = LOG_MODE_WRITE_TO_FILE;

		if (encLog)
			logWriterMode |= LOG_MODE_ENCRYPT_MESSAGES;

		if (emailLog)
			logWriterMode |= LOG_MODE_SEND_MAIL;

		// Create windows service instance
		HubServerService * service = new HubServerService(L"NovaTend_HUB_Server", pExeFileName,TRUE, TRUE, TRUE, logWriterMode, logFilesPath, fixeSizeValue);
		
		// Run the service
		if (!(service -> Run()))
        {
            wprintf(L"Service failed to run w/err 0x%08lx\n", GetLastError());
        }

		delete service;
    }
	
	return 0;
}