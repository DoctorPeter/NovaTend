/****************************************************************

   Solution : NovaTend

   Project : z-hubsrv-01.exe

   Module : HubServerService.cpp

   Description :  this module implements methods of
				  class HubServerService

*****************************************************************/

#include "stdafx.h"

#include "HubServerService.h"
#include <Encryptor.h>
#include <SettingsManager.h>
#include <LicenseDataDef.h>
#include <SerializationManager.h>

// z-hubsrv-01.exe definition structure
extern DLL_COMMON_DEFINITION zHubServerServiceDefinition;

/****************************************************************

   Class : HubServerService

   Method : Constructor

   Parameters :
			Input : 
				serviceName - name of service
				servicePath - path to service executable
				fCanStop - flag can be stopped
				fCanShutdown - flag can be shutdown
				fCanPauseContinue - flag can be paused
				
*****************************************************************/
HubServerService :: HubServerService(WCHAR * serviceName,
				   					   WCHAR * servicePath,
									   BOOL fCanStop,
									   BOOL fCanShutdown,
									   BOOL fCanPauseContinue,
									   unsigned short logWriterMode,
									   char * logFilesPath,
									   int logFileSize) : ServerService(zHubServerServiceDefinition.dllID,
																		 serviceName,
																		 servicePath,
																		 fCanStop,
																		 fCanShutdown,
																		 fCanPauseContinue,
																		 logWriterMode,
																		 logFilesPath,
																		 logFileSize)
{
	hostConnectionsMananger = NULL;
	desktopConnectionsMananger = NULL;
	postLoginManager = NULL;
	commandHistorian = NULL;
}

/****************************************************************

   Class : HubServerService

   Method : Destructor
   
*****************************************************************/
HubServerService :: ~HubServerService(void)
{
	Cleanup();
}

/****************************************************************

   Class : HubServerService

   Method : OnStart

   Parameters :
			Input : 
				dwArgc   - number of command line arguments
				lpszArgv - array of command line arguments

   Description : Executes when a Start command is sent to the 
				 service by the SCM or when the operating system
				 starts (for a service that starts automatically). 

*****************************************************************/
void HubServerService :: OnStart(DWORD dwArgc, PWSTR *pszArgv)
{
	WriteToLog("HUB-server service. --> Starting...");

	// Initialize encryptor
	Encryptor * encryptor = new Encryptor(zHubServerServiceDefinition.dllID);
	encryptor -> Init();
	delete encryptor;
	

	// Read IPC connections information

	// Create settings manager instance
	SettingsManager * settingsManager = new SettingsManager(zHubServerServiceDefinition.dllID);

	// HUB-server starting flag
	bool hubServerStart = settingsManager -> GetHubServerStartingFlag();

	// Check starting flag
	if(!hubServerStart)
	{
		WriteToLog("HUB-server service. --> Starting of server is DISABLED!");
		delete settingsManager;
		throw (-1);
	}

	// Get info of HUB-server
	PSERVER_DESCRIPTION pHubServer = settingsManager -> GetHubServer();

	// Check information of listen
	if(!pHubServer)
	{
		WriteToLog("HUB-server service. --> Can't get information for IPC server starting!");
		delete settingsManager;
		throw (-1);
	}

	// DESKTOP-server starting flag
	bool desktopServerStart = settingsManager -> GetDesktopServerStartingFlag();

	// Get info of DESKTOP-server
	PSERVER_DESCRIPTION pDesktopServer = settingsManager -> GetDesktopServer();

	// Get list of HOST-servers
	PSERVER_DESCRIPTION_LIST pHostServerList = settingsManager -> GetServerDescriptionList();
	PSERVER_DESCRIPTION pHostServer = settingsManager -> GetHostServer();

	// Get info of GLOBAL-server
	PSERVER_DESCRIPTION pGlobalServer = settingsManager -> GetGlobalServer();
	
	// Delete settings manager instance
	delete settingsManager;	



	// Get GLOBAL-server info
	unsigned int gServerID = 0;
	char gServerIPAddress[ADDRESS_SIZE] = "";
	unsigned int gServerPort = 0;

	if ((pGlobalServer) && 
		(pGlobalServer -> serverID != pHubServer -> serverID) &&
		(strcmp(pGlobalServer -> ipAddress, pHubServer -> ipAddress) != 0) &&
		(pGlobalServer -> port != pHubServer -> port))
	{
		gServerID = pGlobalServer -> serverID;
		gServerPort = pGlobalServer -> port;
		strcpy(gServerIPAddress, pGlobalServer -> ipAddress);
	}

	
	// Create connections

	// Create HOST-connections manager
	hostConnectionsMananger = new IPCClientsManagerEx(zHubServerServiceDefinition.dllID, logWriter, gServerID, gServerIPAddress, gServerPort);

	// Add connection to HOST-server
	if (pHostServer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_SRV)
			WriteToLog("HUB server service. --> Add connection to main HOST server!");
		#endif

		hostConnectionsMananger -> AddConnection(pHostServer -> serverID,
												 pHostServer -> serverType,
												 pHostServer -> ipAddress,
												 pHostServer -> port,
												 CLIENT_TYPE_HUB,
												 pHubServer -> serverName,
												 pHubServer,
												 DEFAULT_TIMEOUT);

		free(pHostServer);
	}
	
	// Add connections to alternatile HOST-servers
	if (pHostServerList)
	{
		for(int i = 0; i < pHostServerList -> serversCount; i++)
		{
			if (pHostServerList -> serversList[i])
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_SRV)
					WriteToLog("HUB server service. --> Add connection to alternative HOST-server!");
				#endif

				// Connect to another HOST-server
				hostConnectionsMananger -> AddConnection(pHostServerList -> serversList[i] -> serverID,
														 pHostServerList -> serversList[i] -> serverType,
														 pHostServerList -> serversList[i] -> ipAddress,
														 pHostServerList -> serversList[i] -> port,
														 CLIENT_TYPE_HUB,
														 pHubServer -> serverName,
														 pHubServer,
														 DEFAULT_TIMEOUT);

				free(pHostServerList -> serversList[i]);
			}
		}

		free(pHostServerList);
	}

	// Register on GLOBAL server
	if ((pGlobalServer) && 
		(pGlobalServer -> serverID != pHubServer -> serverID) &&
		(strcmp(pGlobalServer -> ipAddress, pHubServer -> ipAddress) != 0) &&
		(pGlobalServer -> port != pHubServer -> port))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_SRV)
			WriteToLog("HUB server service. --> Add connection to main GLOBAL server!");
		#endif

		hostConnectionsMananger -> SetIPCServerInstance(ipcServer);

		hostConnectionsMananger -> AddConnection(pGlobalServer -> serverID,
												 pGlobalServer -> serverType,
												 pGlobalServer -> ipAddress,
												 pGlobalServer -> port,
												 CLIENT_TYPE_HUB,
												 pHubServer -> serverName,
												 NULL,
												 DEFAULT_TIMEOUT);

		hostConnectionsMananger -> SetIPCServerInstance(NULL);

		free(pGlobalServer);
	}

	// Create DESKTOP-connections manager
	desktopConnectionsMananger = new IPCClientsManager(zHubServerServiceDefinition.dllID, logWriter);

	// Add connection to DESKTOP-server
	if (pDesktopServer)
	{
		if (desktopServerStart)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_SRV)
				WriteToLog("HUB-server service. --> Add connection to DESKTOP server!");
			#endif

			desktopConnectionsMananger -> AddConnection(pDesktopServer -> serverID,
														pDesktopServer -> serverType,
														pDesktopServer -> ipAddress,
														pDesktopServer -> port,
														CLIENT_TYPE_HUB,
														pHubServer -> serverName,
														NULL,
														DEFAULT_TIMEOUT);
		}

		free(pDesktopServer);
	}

	
	// Create HUB-server command manager instance
	commandManager = new HubCommandManager(zHubServerServiceDefinition.dllID, logWriter, hostConnectionsMananger, desktopConnectionsMananger);

	
	// Server starting...


	// Check license
	if (!CheckLicense(pHubServer))
	{
		if (pHubServer) free(pHubServer);
		WriteToLog("HUB-server service. License checking. --> Fail!");
		throw (-1);
	}
		
	WriteToLog("HUB-server service. License checking. --> Success!");

	// Create HUB-server instance
	ipcServer = new IPCServerEx(zHubServerServiceDefinition.dllID, 
								logWriter, 
								pHubServer -> serverID, 
								SERVER_TYPE_HUB, 
								pHubServer -> serverPriority, 
								pHubServer -> serverName, 
								GetMaxClientsCount(), 
								AF_INET, 
								SOCK_STREAM, 
								IPPROTO_TCP, 
								0x0202, 
								pHubServer -> port, 
								pHubServer -> ipAddress, 
								commandManager);
				
	// Start HUB-server
	int result = ipcServer -> Start();

	if (result != SERR_SUCCESS)
	{
		if (pHubServer) free(pHubServer);
		WriteToLog("HUB-server service. --> Can't start IPC server!");
		throw result;
	}

	// Start HUB-server request processing
	result = ipcServer -> StartRequestProcessing();

	if (result != SERR_SUCCESS)
	{
		if (pHubServer) free(pHubServer);
		WriteToLog("HUB-server service. --> Can't start request processing!");
		throw result;
	}

	WriteToLog("HUB-server service. --> NovaTend HUB-server successfully started!");

	if (pHubServer) free(pHubServer);

	// Create POST-login manager
	postLoginManager = new PostLoginManager(zHubServerServiceDefinition.dllID, logWriter);

	// Create command history manager
	commandHistorian = new CommandHistorian(zHubServerServiceDefinition.dllID, commandManager, logWriter);
	
	// Start POST-login manager
	char funcName[STR_VALUE_LEN] = "POST_LOGIN";
	if (commandManager -> CheckLicense("CLIENTFUNC", funcName))
	{
		if (!postLoginManager -> StartThreadController())
			WriteToLog("HUB-server service. --> Can't start periodically post login process!");
		else
			WriteToLog("HUB-server service. -->  Periodically post login process started!");
	}
	else
		WriteToLog("HUB-server service. -->  Periodically post login process license failed!");

	// Start command history manager
	if (!commandHistorian -> StartThreadController())
		WriteToLog("HUB-server service. --> Can't start periodically command historian process!");
	else
		WriteToLog("HUB-server service. -->  Periodically command historian process started!");
}

/****************************************************************

   Class : HubServerService

   Method : Cleanup

   Description : Delete instances

*****************************************************************/
void  HubServerService :: Cleanup(void)
{
	if (hostConnectionsMananger)
	{
		hostConnectionsMananger -> ClearConnectionList();
	}

	if (desktopConnectionsMananger)
	{
		desktopConnectionsMananger -> ClearConnectionList();
	}

	if (commandHistorian)
	{
		delete commandHistorian;
		commandHistorian = NULL;
	}

	if (postLoginManager)
	{
		delete postLoginManager;
		postLoginManager = NULL;
	}

	if (ipcServer)
	{
		delete ipcServer;
		ipcServer = NULL;
	}

	if (commandManager)
	{
		delete commandManager;
		commandManager = NULL;
	}

	if (desktopConnectionsMananger)
	{
		delete desktopConnectionsMananger;
		desktopConnectionsMananger = NULL;
	}

	if (hostConnectionsMananger)
	{
		delete hostConnectionsMananger;
		hostConnectionsMananger = NULL;
	}
	
	Encryptor * encryptor = new Encryptor(zHubServerServiceDefinition.dllID);
	encryptor -> Cleanup();
	delete encryptor;
}