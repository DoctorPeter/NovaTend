/****************************************************************

   Solution : NovaTend

   Project : z-hostsrv-01.exe

   Module : HostServer.cpp

   Description :  z-hostsrv-01 is the windows service that
				  implements HOST-server subsystem of NovaTend 
				  authentication system

				  This code is designed only for the 
				  Windows operating systems.

*****************************************************************/
#include "stdafx.h"

#include "HostServerService.h"
#include <SettingsManager.h>

// z-hostsrv-01.exe definition structure
DLL_COMMON_DEFINITION zHostServerServiceDefinition =
{
	Z_HOST_SERVER_ID,
	0x00010000,
	"z-hostsrv-01.exe - application HOST-server. Windows service",
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
			if (WinService :: Install(L"NovaTend_HOST_Server", 
									  L"NovaTend HOST-Server", 
									  L"The NovaTend HOST-server subsystem. This service provides full\
									    authentication management functionality.", 
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
            if (WinService :: UnInstall(L"NovaTend_HOST_Server"))
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

		SettingsManager * settingsManager = new SettingsManager(zHostServerServiceDefinition.dllID);

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
		HostServerService * service = new HostServerService(L"NovaTend_HOST_Server", pExeFileName, TRUE, TRUE, TRUE, logWriterMode, logFilesPath, fixeSizeValue);
		
		// Run the service
		if (!(service -> Run()))
        {
            wprintf(L"Service failed to run w/err 0x%08lx\n", GetLastError());
        }

		delete service;
    }
	
	return 0;
}