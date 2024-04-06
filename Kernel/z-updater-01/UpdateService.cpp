/****************************************************************

   Solution : NovaTend

   Project : z-hostsrv-01.exe

   Module : UpdateService.cpp

   Description :  this module implements methods of
				  class UpdateService

*****************************************************************/

#include "stdafx.h"

#include "UpdateService.h"
#include <Encryptor.h>
#include <LicenseManager.h>
#include <SettingsManager.h>

// z-update-01.exe definition structure
extern DLL_COMMON_DEFINITION zUpdateServiceDefinition;

/****************************************************************

   Class : UpdateService

   Method : Constructor

   Parameters :
			Input : 
				serviceName - name of service
				servicePath - path to service executable
				fCanStop - flag can be stopped
				fCanShutdown - flag can be shutdown
				fCanPauseContinue - flag can be paused
				
*****************************************************************/
UpdateService :: UpdateService(WCHAR * serviceName,
				   			   WCHAR * servicePath,
							   BOOL fCanStop,
							   BOOL fCanShutdown,
							   BOOL fCanPauseContinue,
							   unsigned short logWriterMode,
							   char * logFilesPath,
							   int logFileSize) : WinService(zUpdateServiceDefinition.dllID,
																 serviceName,
																 servicePath,
																 fCanStop,
																 fCanShutdown,
																 fCanPauseContinue,
																 logWriterMode,
																 logFilesPath,
																 logFileSize)
{
	fileProcessor = NULL;
	clientAuthManager = NULL;
	hubCommandManager = NULL;
	hostConnectionsMananger = NULL;
	desktopConnectionsMananger = NULL;
}

/****************************************************************

   Class : UpdateService

   Method : Destructor
   
*****************************************************************/
UpdateService :: ~UpdateService(void)
{
	Cleanup();
}

/****************************************************************

   Class : UpdateService

   Method : OnStart

   Parameters :
			Input : 
				dwArgc   - number of command line arguments
				lpszArgv - array of command line arguments

   Description : Executes when a Start command is sent to the 
				 service by the SCM or when the operating system
				 starts (for a service that starts automatically). 

*****************************************************************/
void UpdateService :: OnStart(DWORD dwArgc, PWSTR *pszArgv)
{
	WriteToLog("Update service. --> Starting...");

	Encryptor * encryptor = new Encryptor(zUpdateServiceDefinition.dllID);
	encryptor -> Init();
	delete encryptor;
	
	// Get IPC connections information
	SettingsManager * settingsManager = new SettingsManager(zUpdateServiceDefinition.dllID);

	// Get list of host servers
	PSERVER_DESCRIPTION_LIST pHostServerList = settingsManager -> GetServerDescriptionList();
	PSERVER_DESCRIPTION pHostServer = settingsManager -> GetHostServer();

	// Get info of GLOBAL server
	PSERVER_DESCRIPTION pGlobalServer = settingsManager -> GetGlobalServer();
	
	unsigned int gServerID = 0;
	char gServerIPAddress[ADDRESS_SIZE] = "";
	unsigned int gServerPort = 0;

	// Get global server info
	if (pGlobalServer)
	{
		gServerID = pGlobalServer -> serverID;
		gServerPort = pGlobalServer -> port;
		strcpy(gServerIPAddress, pGlobalServer -> ipAddress);

		free(pGlobalServer);
	}

	delete settingsManager;

	// Create HOST-connections manager
	hostConnectionsMananger = new IPCClientsManagerEx(zUpdateServiceDefinition.dllID, logWriter, gServerID, gServerIPAddress, gServerPort);
	
	// Create HUB-server command manager instance
	hubCommandManager = new HubCommandManager(zUpdateServiceDefinition.dllID, logWriter, hostConnectionsMananger, desktopConnectionsMananger);
		
	// Add connection to HOST-server
	if (pHostServer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
			WriteToLog("Update service. --> Add connection to main HOST server!");
		#endif

		hostConnectionsMananger -> AddConnection(pHostServer -> serverID,
												 pHostServer -> serverType,
												 pHostServer -> ipAddress,
												 pHostServer -> port,
												 CLIENT_UPDATER,
												 "Update service",
												 NULL,
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
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
					WriteToLog("Update service. --> Add connection to alternative HOST-server!");
				#endif

				// Connect to another HOST-server
				hostConnectionsMananger -> AddConnection(pHostServerList -> serversList[i] -> serverID,
														 pHostServerList -> serversList[i] -> serverType,
														 pHostServerList -> serversList[i] -> ipAddress,
														 pHostServerList -> serversList[i] -> port,
														 CLIENT_UPDATER,
														 "Update service",
														 NULL,
														 DEFAULT_TIMEOUT);

				free(pHostServerList -> serversList[i]);
			}
		}

		free(pHostServerList);
	}
	
	PrepareHubCommandManager();

	clientAuthManager = new ClientAuthManager(zUpdateServiceDefinition.dllID, logWriter, hubCommandManager);
	fileProcessor = new FileProcessor(zUpdateServiceDefinition.dllID, clientAuthManager);
	updateManager = new UpdateManager(zUpdateServiceDefinition.dllID, fileProcessor, logWriter);

	if (!updateManager -> StartThreadController())
	{
		WriteToLog("Update service. --> Can't start update service!");
		throw (-1);
	}
}

/****************************************************************

   Class : UpdateService

   Method : OnStop

   Description : Executes when a Stop command is sent to the 
				 service by the SCM. 

*****************************************************************/
void UpdateService :: OnStop(void)
{
	Cleanup();
	WriteToLog("Update service. --> NovaTend update service successfully stoped!");
}

/****************************************************************

   Class : UpdateService

   Method : OnPause

   Description : Executes when a Pause command is sent to the 
				 service by the SCM. 

*****************************************************************/
void UpdateService :: OnPause(void)
{
	WriteToLog("Update service. --> NovaTend update service successfully paused!");
	SettingsManager * settingsManager = new SettingsManager(zUpdateServiceDefinition.dllID);
	settingsManager -> SetUpdatePeriodicFlag(false);
	delete settingsManager;
}

/****************************************************************

   Class : UpdateService

   Method : OnContinue

   Description : Executes when a Continue command is sent to the 
				 service by the SCM. 

*****************************************************************/
void UpdateService :: OnContinue(void)
{
	WriteToLog("Update service. --> NovaTend update service successfully resumed!");
	SettingsManager * settingsManager = new SettingsManager(zUpdateServiceDefinition.dllID);
	settingsManager -> SetUpdatePeriodicFlag(true);
	delete settingsManager;
}

/****************************************************************

   Class : UpdateService

   Method : OnShutdown

   Description : Executes when a Sthutdown command is sent to the 
				 service by the SCM. 

*****************************************************************/
void UpdateService :: OnShutdown(void)
{
	OnStop();
}

/****************************************************************

   Class : UpdateService

   Method : Cleanup

   Description : Delete instances

*****************************************************************/
void  UpdateService :: Cleanup(void)
{
	if (hostConnectionsMananger)
	{
		hostConnectionsMananger -> ClearConnectionList();
	}

	if (desktopConnectionsMananger)
	{
		desktopConnectionsMananger -> ClearConnectionList();
	}

	if (updateManager)
	{
		delete updateManager;
		updateManager = NULL;
	}
	
	if (fileProcessor)
	{
		delete fileProcessor;
		fileProcessor = NULL;
	}

	if (clientAuthManager)
	{
		delete clientAuthManager;
		clientAuthManager = NULL;
	}

	if (hubCommandManager)
	{
		delete hubCommandManager;
		hubCommandManager = NULL;
	}

	if (hostConnectionsMananger)
	{
		delete hostConnectionsMananger;
		hostConnectionsMananger = NULL;
	}

	if (desktopConnectionsMananger)
	{
		delete desktopConnectionsMananger;
		desktopConnectionsMananger = NULL;
	}
	
	Encryptor * encryptor = new Encryptor(zUpdateServiceDefinition.dllID);
	encryptor -> Cleanup();
	delete encryptor;
}

/****************************************************************

   Class : UpdateService

   Method : PrepareHubCommandManager

   Description :Prepare hub command manager client and server descriptions

*****************************************************************/
void UpdateService :: PrepareHubCommandManager(void)
{
	if ((hubCommandManager) && (hostConnectionsMananger))
	{
		unsigned int serverID = hostConnectionsMananger -> FindMostPriorityServer();
		IPCClient * ipcClient = hostConnectionsMananger -> FindConnection(serverID);
		
		if (ipcClient)
		{
			memcpy(&(hubCommandManager -> clientDescr), &(ipcClient -> clientDescr), sizeof(CLIENT_DESCRIPTION));
			//memcpy(&(hubCommandManager -> serverDescr), &(ipcClient -> serverDescr), sizeof(SERVER_DESCRIPTION));
		}

	}
}
