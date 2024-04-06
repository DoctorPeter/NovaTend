/****************************************************************

   Solution : NovaTend

   Project : z-desktopsrv-01.dll

   Module : DesktopServerService.cpp

   Description :  Implements methods of class
                  DesktopServerService

*****************************************************************/
#include "stdafx.h"
#include "DesktopServerService.h"
#include <LicenseDataDef.h>
#include <SettingsManager.h>
#include <Encryptor.h>

// z-desktopsrv-01.exe definition structure
extern DLL_COMMON_DEFINITION zDesktopServerServiceDefinition;

/****************************************************************

   Class :  DesktopServerService

   Method : Constructor
  
*****************************************************************/
DesktopServerService :: DesktopServerService(char * serviceName)
{
	if (serviceName)
		strcpy_s(this -> serviceName, serviceName);
		
	bool encLog = false;

	SettingsManager * settingsManager = new SettingsManager(zDesktopServerServiceDefinition.dllID);
	settingsManager -> GetLogEncryptFlag(&encLog);
	settingsManager -> GetLogPath(logFilesPath);
	delete settingsManager;

	// Set log writer mode
	unsigned short logWriterMode = LOG_MODE_WRITE_TO_FILE;

	if (encLog)
		logWriterMode |= LOG_MODE_ENCRYPT_MESSAGES;

	char filePath[MAX_PATH] = "";
	logWriter  = new SafeLogWriter(Z_WIN_SERVICE_DLL_ID, logWriterMode, CreateLogFileName(filePath));

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_SRV)
		WriteToLog("DesktopServerService : Constructor");
	#endif

	exceptionHandler = new WinExceptionHandler(zDesktopServerServiceDefinition.dllID, logWriter);
	desktopCommandManager = NULL;
	hubConnectionsMananger = NULL;
	programsController = NULL;
	ipcServer = NULL;
}

/****************************************************************

   Class :  DesktopServerService

   Method : Destructor
  
*****************************************************************/
DesktopServerService :: ~DesktopServerService()
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_SRV)
		WriteToLog("DesktopServerService : Destructor");
	#endif

	Cleanup();

	if (exceptionHandler)
	{
		delete exceptionHandler;
		exceptionHandler = NULL;
	}

	if (logWriter)
	{
		delete logWriter;
		logWriter = NULL;
	}
}

/****************************************************************

   Class : DesktopServerService

   Method : Start

   Return : TRUE - if success

   Description : Start DESKTOP-server

*****************************************************************/
bool DesktopServerService :: Start(void)
{
	WriteToLog("DESKTOP-server service. --> Starting...");


	// Initialize encryptor
	Encryptor * encryptor = new Encryptor(zDesktopServerServiceDefinition.dllID);
	encryptor -> Init();
	delete encryptor;

	
	
	// Read IPC connections information


	// Get IPC connections information
	SettingsManager * settingsManager = new SettingsManager(zDesktopServerServiceDefinition.dllID);
	
	// Get starting flag
	bool startFlag = settingsManager -> GetDesktopServerStartingFlag();
	
	// Check starting flag
	if (!startFlag)
	{
		delete settingsManager;
		WriteToLog("DESKTOP-server service. --> Starting of server is DISABLED!");
		return false;
	}

	// Get info of DESKTOP-server
	PSERVER_DESCRIPTION pDesktopServer = NULL;
	if (startFlag)
		pDesktopServer = settingsManager -> GetDesktopServer();

	// Check information of listen
	if(!pDesktopServer)
	{
		delete settingsManager;
		WriteToLog("DESKTOP-server service. --> Can't get information for IPC server starting!");
		return false;
	}

	// Get info of HUB-server
	PSERVER_DESCRIPTION pHubServer = settingsManager -> GetHubServer();

	// Delete settings manager instance
	delete settingsManager;


	// Create connections
	
	// Create HOST-connections manager
	hubConnectionsMananger = new IPCClientsManager(zDesktopServerServiceDefinition.dllID, logWriter);

	if (pHubServer)
	{
		// Add connection to HUB-server
		hubConnectionsMananger -> AddConnection(pHubServer -> serverID,
												pHubServer -> serverType,
												pHubServer -> ipAddress,
												pHubServer -> port,
												CLIENT_TYPE_DESKTOP,
												pHubServer -> serverName,
												NULL,
												DEFAULT_TIMEOUT);
		free(pHubServer);
	}
		
	// Create command manager
	desktopCommandManager = new DesktopCommandManager(zDesktopServerServiceDefinition.dllID, logWriter, hubConnectionsMananger);


	// Check license
	if (!CheckLicense(pDesktopServer))
	{
		if (pDesktopServer) free(pDesktopServer);
		WriteToLog("DESKTOP-server service. License checking. --> Fail!");
		return false;
	}
	
	WriteToLog("DESKTOP-server service. License checking. --> Success!");

	// Create server instance
	ipcServer = new IPCServer(zDesktopServerServiceDefinition.dllID, 
								logWriter, 
								pDesktopServer -> serverID, 
								SERVER_TYPE_DESKTOP, 
								pDesktopServer -> serverPriority, 
								pDesktopServer -> serverName, 
								MAX_CLIENTS_COUNT, 
								AF_INET, 
								SOCK_STREAM, 
								IPPROTO_TCP, 
								0x0202, 
								pDesktopServer -> port, 
								pDesktopServer -> ipAddress, 
								desktopCommandManager);
			
	
	// Create programs controller instance
	int hubServerID  = hubConnectionsMananger -> FindMostPriorityServer();
	programsController = new ProgramsController(zDesktopServerServiceDefinition.dllID, logWriter, hubConnectionsMananger, pDesktopServer -> serverID, hubServerID);

	if (pDesktopServer) free(pDesktopServer);

	// Start server
	int result = ipcServer -> Start();

	if (result != SERR_SUCCESS)
	{
		WriteToLog("DESKTOP-server service. --> Can't start IPC server!");
		return false;
	}

	// Start requests processing
	result = ipcServer -> StartRequestProcessing();

	if (result != SERR_SUCCESS)
	{
		WriteToLog("DESKTOP-server service. --> Can't start request processing!");
		return false;
	}
	
	WriteToLog("DESKTOP-server service. --> NovaTend DESKTOP-server successfully started!");

	// Start programs controller
	char funcName[STR_VALUE_LEN] = "PROGRAMS_CONTROL";
	if (desktopCommandManager -> CheckLicense("CLIENTFUNC", funcName))
	{
		if (!programsController -> StartThreadController())
			WriteToLog("DESKTOP-server service. --> Can't start programs controller!");
		else
			WriteToLog("DESKTOP-server service. -->  Programs controller successfully started!");
	}
	else
		WriteToLog("DESKTOP-server service. -->  Programs controller license failed!");

	return true;
}

/****************************************************************

   Class : DesktopServerService

   Method : Stop

   Return : TRUE - if success

   Description : Stop DESKTOP-server

*****************************************************************/
bool DesktopServerService :: Stop(void)
{
	Cleanup();

	WriteToLog("DESKTOP-server service. --> NovaTend DESKTOP-server successfully stoped!");

	return true;
}

/****************************************************************

   Class : DesktopServerService

   Method : Cleanup

   Description : Delete instances

*****************************************************************/
void  DesktopServerService :: Cleanup(void)
{
	if (hubConnectionsMananger)
	{
		hubConnectionsMananger -> ClearConnectionList();
	}

	if (ipcServer)
	{
		ipcServer -> Shutdown();
	}

	if (programsController)
	{
		delete programsController;
		programsController = NULL;
	}

	if (ipcServer)
	{
		delete ipcServer;
		ipcServer = NULL;
	}

	if (desktopCommandManager)
	{
		delete desktopCommandManager;
		desktopCommandManager = NULL;
	}

	if (hubConnectionsMananger)
	{
		delete hubConnectionsMananger;
		hubConnectionsMananger = NULL;
	}

	Encryptor * encryptor = new Encryptor(zDesktopServerServiceDefinition.dllID);
	encryptor -> Cleanup();
	delete encryptor;
}

/****************************************************************

   Class : DesktopServerService

   Method : CheckLicense

   Parameters :
			Input:
				pServer - description of HOST-server

   Returns : result of license checking

   Description : Check license

*****************************************************************/
bool DesktopServerService :: CheckLicense(PSERVER_DESCRIPTION pServer)
{
	WriteToLog("DESKTOP-server service. --> License checking...");

	// Check server descriptor
	if (!pServer)
	{
		WriteToLog("DESKTOP-server service. --> License checking. Wrong server descriptor!");
		return false;
	}

	// Check command manager instance
	if (!desktopCommandManager)
	{
		WriteToLog("DESKTOP-server service. --> License checking. Wrong command manager instance!");
		return false;
	}
	
	// Check license owner
	char ownerName[STR_VALUE_LEN] = "USER";
	if (!(desktopCommandManager -> CheckLicense("LICOWNER", ownerName)))
	{
		WriteToLog("DESKTOP-server service. License checking. --> Prohibited user!");
		return false;
	}

	// Get current time
	time_t nowSeconds;
	struct tm inpTime;
	time (&nowSeconds);
	inpTime = * localtime(&nowSeconds);

	// Check expiration date
	if(!(desktopCommandManager -> CheckLicense("EXPDATE", &inpTime, 0, REL_TYPE_LESS)))
	{
		WriteToLog("DESKTOP-server service. License checking. --> License period expired!");
		return false;
	}

	// Check NovaTend system version
	int dllVersion = zDesktopServerServiceDefinition.dllVersion;
	if(!(desktopCommandManager -> CheckLicense("SYSVERSION", &dllVersion)))
	{
		WriteToLog("DESKTOP-server service. License checking. --> Prohibited software version!");
		return false;
	}

	// Check server type
	char serverTypeStr[STR_VALUE_LEN] = "";
	switch (pServer -> serverType)
	{
		case SERVER_TYPE_HOST :
		{
			strcpy(serverTypeStr, "HOST");
			break;
		}
		case SERVER_TYPE_HUB :
		{
			strcpy(serverTypeStr, "HUB");
			break;
		}
		case SERVER_TYPE_DESKTOP :
		{
			strcpy(serverTypeStr, "DESKTOP");
			break;
		}
	}

	if(!(desktopCommandManager -> CheckLicense("SERVERTYPE", serverTypeStr)))
	{
		WriteToLog("DESKTOP-server service. License checking. --> Prohibited server type!");
		return false;
	}

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Check IP address !!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	char ipAddressStr[IP_ADDRESS_LEN] = "";
	if (strcmp(pServer -> ipAddress, "127.0.0.1") != 0)
		strcpy(ipAddressStr, "127.0.0.1");
	else
		strcpy(ipAddressStr, pServer -> ipAddress);
	
	if(!(desktopCommandManager -> CheckLicense("IPADDRESS", ipAddressStr)))
	{
		WriteToLog("DESKTOP-server service. License checking. --> Prohibited IP address!");
		return false;
	}

	return true;
}

/****************************************************************

   Class : DesktopServerService

   Method : GetMaxClientsCount

   Returns : maximum count of clients

   Description : Get maximum count of clients

*****************************************************************/
int DesktopServerService :: GetMaxClientsCount(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_SRV)
		WriteToLog("DesktopServerService : GetMaxClientsCount. Start");
	#endif

	int maxClientsCount = 0;

	if (desktopCommandManager)
	{
		desktopCommandManager -> CheckLicense("MAXCLIENTSCOUNT", &maxClientsCount, 0, REL_TYPE_EQUAL);
	}
	else
		WriteToLog("DESKTOP-server service. --> License checking. Wrong command manager instance!");

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_SRV)
		WriteToLog("DesktopServerService : GetMaxClientsCount. Done");
	#endif

	return maxClientsCount;
}

/****************************************************************

   Class : DesktopServerService

   Method : CreateLogFileName

   Parameters :
			Input/Output : 
				fileName - path to Log-file

	Return : log file name

	Description : Create name of log-file

*****************************************************************/
char * DesktopServerService :: CreateLogFileName(char * fileName)
{
	strcpy(fileName, logFilesPath);
	if (strcmp(fileName, "") != 0)
		strcat(fileName, "\\");
		
	// Get current time
	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);
	char timeBuf[32];                                
    strftime(timeBuf, 32, "_%m.%d.%Y", timeinfo); 

	// Prepare file name
	strcat(fileName, serviceName);
	strcat(fileName, timeBuf);
	strcat(fileName, ".log");

	// Return file name
	return fileName;
}

/****************************************************************

   Class : DesktopServerService

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int DesktopServerService :: WriteToLog(char * message)
{
    if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}