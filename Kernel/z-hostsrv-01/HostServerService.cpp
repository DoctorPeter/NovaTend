/****************************************************************

   Solution : NovaTend

   Project : z-hostsrv-01.exe

   Module : HostServerService.cpp

   Description :  this module implements methods of
				  class HostServerService

*****************************************************************/
#include "stdafx.h"

#include "HostServerService.h"
#include <Encryptor.h>
#include <LicenseManager.h>
#include <SettingsManager.h>
#include <CheckAccessCommand.h>

// z-hostsrv-01.exe definition structure
extern DLL_COMMON_DEFINITION zHostServerServiceDefinition;

/****************************************************************

   Class : HostServerService

   Method : Constructor

   Parameters :
			Input : 
				serviceName - name of service
				servicePath - path to service executable
				fCanStop - flag can be stopped
				fCanShutdown - flag can be shutdown
				fCanPauseContinue - flag can be paused
				
*****************************************************************/
HostServerService :: HostServerService(WCHAR * serviceName,
				   			   WCHAR * servicePath,
							   BOOL fCanStop,
							   BOOL fCanShutdown,
							   BOOL fCanPauseContinue,
							   unsigned short logWriterMode,
							   char * logFilesPath,
							   int logFileSize) : ServerService(zHostServerServiceDefinition.dllID,
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
	hubConnectionsMananger = NULL;
	desktopConnectionsMananger = NULL;
	userAccountsSynchronizer = NULL;
	postLoginManager = NULL;
	commandHistorian = NULL;
}

/****************************************************************

   Class : HostServerService

   Method : Destructor
   
*****************************************************************/
HostServerService :: ~HostServerService(void)
{
	Cleanup();
}

/****************************************************************

   Class : HostServerService

   Method : OnStart

   Parameters :
			Input : 
				dwArgc   - number of command line arguments
				lpszArgv - array of command line arguments

   Description : Executes when a Start command is sent to the 
				 service by the SCM or when the operating system
				 starts (for a service that starts automatically). 

*****************************************************************/
void HostServerService :: OnStart(DWORD dwArgc, PWSTR *pszArgv)
{
	WriteToLog("HOST-server service. --> Starting...");

	// Initialize encryptor
	Encryptor * encryptor = new Encryptor(zHostServerServiceDefinition.dllID);
	encryptor -> Init();
	delete encryptor;


	// Check access to DB manager
	bool canStart = false;

	// Tries during 60 seconds
	for(int i = 0; i < 60; i++)
	{
		canStart = CheckServerAccess();

		if (canStart)
		{
			break;
		}
		else
		{
			Sleep(1000);
		}
	}

	// Check connection possibility
	if (!canStart)
	{
		WriteToLog("HOST server service. --> Can not connect to DB server!");
		throw (-1);
	}	

	
	
	// Read IPC connections information

	// Get IPC connections information
	SettingsManager * settingsManager = new SettingsManager(zHostServerServiceDefinition.dllID);

	// HOST-server starting flag
	bool hostServerStart = settingsManager -> GetHostServerStartingFlag();

	// Check starting flag
	if(!hostServerStart)
	{
		WriteToLog("HOST-server service. --> Starting of server is DISABLED!");
		delete settingsManager;
		throw (-1);
	}
	
	// Get info of HOST-server
	PSERVER_DESCRIPTION pHostServer = settingsManager -> GetHostServer();
		
	// Check information of listen
	if(!pHostServer)
	{
		WriteToLog("HOST-server service. --> Can't get information for IPC server starting!");
		delete settingsManager;
		throw (-1);
	}

	// DESKTOP-server starting flag
	bool desktopServerStart = settingsManager -> GetDesktopServerStartingFlag();

	// Get info of DESKTOP-server
	PSERVER_DESCRIPTION pDesktopServer = settingsManager -> GetDesktopServer();

	// Get list af alternative HOST-servers
	PSERVER_DESCRIPTION_LIST pHostServerList = settingsManager -> GetServerDescriptionList();
	
	// Get info of GLOBAL-server
	PSERVER_DESCRIPTION pGlobalServer = settingsManager -> GetGlobalServer();
	
	// Delete settings manager instance
	delete settingsManager;	

	
	
	// Get GLOBAL-server info
	unsigned int gServerID = 0;
	char gServerIPAddress[ADDRESS_SIZE] = "";
	unsigned int gServerPort = 0;
		
	if ((pGlobalServer) && 
		(pGlobalServer -> serverID != pHostServer -> serverID) &&
		(strcmp(pGlobalServer -> ipAddress, pHostServer -> ipAddress) != 0) &&
		(pGlobalServer -> port != pHostServer -> port))
	{
		gServerID = pGlobalServer -> serverID;
		gServerPort = pGlobalServer -> port;
		strcpy(gServerIPAddress, pGlobalServer -> ipAddress);
	}

	
	
	// Create connections

	// Create HOST-connections manager
	hostConnectionsMananger = new IPCClientsManagerEx(zHostServerServiceDefinition.dllID, logWriter, gServerID, gServerIPAddress, gServerPort);

	// Create connections to another HOST-servers
	if (pHostServerList)
	{
		for(int i = 0; i < pHostServerList -> serversCount; i++)
		{
			if (pHostServerList -> serversList[i])
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_SRV)
					WriteToLog("HOST-server service. --> Add connection to alternative HOST-server!");
				#endif
				
				// Connect to another HOST-server
				hostConnectionsMananger -> AddConnection(pHostServerList -> serversList[i] -> serverID,
														 pHostServerList -> serversList[i] -> serverType,
														 pHostServerList -> serversList[i] -> ipAddress,
														 pHostServerList -> serversList[i] -> port,
														 CLIENT_TYPE_HOST,
														 pHostServer -> serverName,
														 pHostServer,
														 DEFAULT_TIMEOUT);

				free(pHostServerList -> serversList[i]);
			}
		}

		free(pHostServerList);
	}

	// Register on global server
	if ((pGlobalServer) && 
		(pGlobalServer -> serverID != pHostServer -> serverID) &&
		(strcmp(pGlobalServer -> ipAddress, pHostServer -> ipAddress) != 0) &&
		(pGlobalServer -> port != pHostServer -> port))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_SRV)
			WriteToLog("HOST-server service. --> Add connection to main GLOBAL server!");
		#endif

		hostConnectionsMananger -> SetIPCServerInstance(ipcServer);

		hostConnectionsMananger -> AddConnection(pGlobalServer -> serverID,
												 pGlobalServer -> serverType,
												 pGlobalServer -> ipAddress,
												 pGlobalServer -> port,
												 CLIENT_TYPE_HOST,
												 pHostServer -> serverName,
												 NULL,
												 DEFAULT_TIMEOUT);

		hostConnectionsMananger -> SetIPCServerInstance(NULL);

		free(pGlobalServer);
	}

	
	// Create DESKTOP-connections manager
	desktopConnectionsMananger = new IPCClientsManager(zHostServerServiceDefinition.dllID, logWriter);

	// Create connection to DESKTOP-servers
	if (pDesktopServer)
	{
		if (desktopServerStart)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_SRV)
				WriteToLog("HOST server service. --> Add connection to DESKTOP-server!");
			#endif

			desktopConnectionsMananger -> AddConnection(pDesktopServer -> serverID,
														pDesktopServer -> serverType,
														pDesktopServer -> ipAddress,
														pDesktopServer -> port,
														CLIENT_TYPE_HOST,
														pHostServer -> serverName,
														NULL,
														DEFAULT_TIMEOUT);
		}

		free(pDesktopServer);
	}

	// Create HUB-connections manager
	hubConnectionsMananger = new IPCClientsManagerEx(zHostServerServiceDefinition.dllID, logWriter, gServerID, gServerIPAddress, gServerPort);


	// Create HOST-server command manager instance
	commandManager = new HostCommandManager(zHostServerServiceDefinition.dllID, logWriter, hostConnectionsMananger, desktopConnectionsMananger, hubConnectionsMananger);
	

	// Server starting...

	// Check license
	canStart = CheckLicense(pHostServer);

	if (!canStart)
	{
		if (pHostServer) free(pHostServer);
		WriteToLog("HOST-server service. License checking. --> Fail!");
		throw (-1);
	}
		
	WriteToLog("HOST-server service. License checking. --> Success!");
		
	
	// Create HOST-server instance
	ipcServer = new IPCServerEx(zHostServerServiceDefinition.dllID, 
									logWriter, 
									pHostServer -> serverID, 
									SERVER_TYPE_HOST, 
									pHostServer -> serverPriority, 
									pHostServer -> serverName, 
									GetMaxClientsCount(), 
									AF_INET, 
									SOCK_STREAM, 
									IPPROTO_TCP, 
									0x0202, 
									pHostServer -> port, 
									pHostServer -> ipAddress, 
									commandManager);
	
	// Start HOST-server
	int result = ipcServer -> Start();

	if (result != SERR_SUCCESS)
	{
		if (pHostServer) free(pHostServer);
		WriteToLog("HOST-server service. --> Can't start IPC server!");
		throw result;
	}
		
	// Start HOST-server request processing
	result = ipcServer -> StartRequestProcessing();

	if (result != SERR_SUCCESS)
	{
		if (pHostServer) free(pHostServer);
		WriteToLog("HOST-server service. --> Can't start request processing!");
		throw result;
	}

	WriteToLog("HOST-server service. --> NovaTend HOST-server successfully started!");

	if (pHostServer) free(pHostServer);

	userAccountsSynchronizer = new AutoUserAccountsSynchronizer(zHostServerServiceDefinition.dllID, logWriter);
	postLoginManager = new PostLoginManager(zHostServerServiceDefinition.dllID, logWriter);
	commandHistorian = new CommandHistorian(zHostServerServiceDefinition.dllID, commandManager, logWriter);

	char funcName[STR_VALUE_LEN] = "POST_LOGIN";
	if (commandManager -> CheckLicense("CLIENTFUNC", funcName))
	{
		if (!postLoginManager -> StartThreadController())
			WriteToLog("HOST-server service. --> Can't start periodically post login process!");
		else
			WriteToLog("HOST-server service. -->  Periodically post login process started!");
	}
	else
		WriteToLog("HOST-server service. -->  Periodically post login process license failed!");

	if (!userAccountsSynchronizer -> StartThreadController())
		WriteToLog("HOST-server service. --> Can't start automatic user accounts synchronizer!");
	else
		WriteToLog("HOST-server service. --> Automatic user accounts synchronizer successfully started!");

	if (!commandHistorian -> StartThreadController())
		WriteToLog("HOST-server service. --> Can't start periodically command historian process!");
	else
		WriteToLog("HOST-server service. -->  Periodically command historian process started!");
}

/****************************************************************

   Class : HostServerService

   Method : CheckServerAccess

   Returns: Flag of DB access 

   Description : Check DB access

*****************************************************************/
bool HostServerService :: CheckServerAccess(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_SRV)
		WriteToLog("HostServerService : CheckServerAccess. Start");
	#endif

	bool checkResult = false;

	// Create checking DB access command
	CheckAccessCommand * checkAccessCommand = new CheckAccessCommand(zHostServerServiceDefinition.dllID, logWriter);

	// Execute command
	PCOMMAND_PARAMETER_LIST pResParams = checkAccessCommand -> Execute(NULL);

	delete checkAccessCommand;

	// Check result peremeters list
	if ((pResParams) &&
		(pResParams -> paramCount == 1) &&
		(pResParams -> paramList[0]))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostServerServiceDefinition.dllID, logWriter);

		// Get DB access checking result
		checkResult = (bool)(serializationManager -> UnpackByte(pResParams -> paramList[0]));

		// Delete parameter list
		pResParams = serializationManager -> DeleteCommandParameterList(pResParams);

		// Delete serialization manager instance
		delete serializationManager;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_SRV)
		WriteToLog("HostServerService : CheckServerAccess. Done");
	#endif

	return checkResult;
}

/****************************************************************

   Class : HostServerService

   Method : Cleanup

   Description : Delete instances

*****************************************************************/
void  HostServerService :: Cleanup(void)
{
	if (hostConnectionsMananger)
	{
		hostConnectionsMananger -> ClearConnectionList();
	}

	if (hubConnectionsMananger)
	{
		hubConnectionsMananger -> ClearConnectionList();
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

	if (userAccountsSynchronizer)
	{
		delete userAccountsSynchronizer;
		userAccountsSynchronizer = NULL;
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

	if (hubConnectionsMananger)
	{
		delete hubConnectionsMananger;
		hubConnectionsMananger = NULL;
	}

	if (hostConnectionsMananger)
	{
		delete hostConnectionsMananger;
		hostConnectionsMananger = NULL;
	}
	
	Encryptor * encryptor = new Encryptor(zHostServerServiceDefinition.dllID);
	encryptor -> Cleanup();
	delete encryptor;
}