/****************************************************************

   Solution : NovaTend

   Project : z-srvsrv-01.exe

   Module : ServerService.cpp

   Description :  this module implements methods of
				  class ServerService

*****************************************************************/

#include "stdafx.h"

#include "ServerService.h"
#include <LicenseDataDef.h>
#include <SerializationManager.h>

// z-srvsrv-01.exe definition structure
extern DLL_COMMON_DEFINITION zServerServiceDllDefinition;

/****************************************************************

   Class : ServerService

   Method : Constructor

   Parameters :
			Input : 
				serviceName - name of service
				servicePath - path to service executable
				fCanStop - flag can be stopped
				fCanShutdown - flag can be shutdown
				fCanPauseContinue - flag can be paused
				
*****************************************************************/
ServerService :: ServerService(unsigned long dllUserID,
							   WCHAR * serviceName,
				   			   WCHAR * servicePath,
							   BOOL fCanStop,
							   BOOL fCanShutdown,
							   BOOL fCanPauseContinue,
							   unsigned short logWriterMode,
							   char * logFilesPath,
							   int logFileSize) : WinService(dllUserID,
																 serviceName,
																 servicePath,
																 fCanStop,
																 fCanShutdown,
																 fCanPauseContinue,
																 logWriterMode,
																 logFilesPath,
																 logFileSize)
{
	commandManager = NULL;
	ipcServer = NULL;
}

/****************************************************************

   Class : ServerService

   Method : Destructor
   
*****************************************************************/
ServerService :: ~ServerService(void)
{
	Cleanup();
}

/****************************************************************

   Class : ServerService

   Method : OnStart

   Parameters :
			Input : 
				dwArgc   - number of command line arguments
				lpszArgv - array of command line arguments

   Description : Executes when a Start command is sent to the 
				 service by the SCM or when the operating system
				 starts (for a service that starts automatically). 

*****************************************************************/
void ServerService :: OnStart(DWORD dwArgc, PWSTR *pszArgv)
{
	// Create command manager instance
	commandManager = new CommandManager(zServerServiceDllDefinition.dllID, logWriter);

	
	// Server starting...


	// Check license
	if (!CheckLicense(NULL))
	{
		WriteToLog("SERVER service. License checking. --> Fail!");
		throw (-1);
	}
		
	// Create HUB-server instance
	ipcServer = new IPCServerEx(zServerServiceDllDefinition.dllID, 
								logWriter, 
								0, 
								SERVER_TYPE_HUB, 
								0, 
								"", 
								GetMaxClientsCount(), 
								AF_INET, 
								SOCK_STREAM, 
								IPPROTO_TCP, 
								0x0202, 
								0, 
								"127.0.0.1", 
								commandManager);
				
	// Start HUB-server
	int result = ipcServer -> Start();

	if (result != SERR_SUCCESS)
	{
		WriteToLog("SERVER service. --> Can't start IPC server!");
		throw result;
	}

	// Start HUB-server request processing
	result = ipcServer -> StartRequestProcessing();

	if (result != SERR_SUCCESS)
	{
		WriteToLog("SERVER service. --> Can't start request processing!");
		throw result;
	}

	WriteToLog("SERVER service. --> NovaTend HUB-server successfully started!");
}

/****************************************************************

   Class : ServerService

   Method : OnStop

   Description : Executes when a Stop command is sent to the 
				 service by the SCM. 

*****************************************************************/
void ServerService :: OnStop(void)
{
	if (ipcServer)
	{
		int result = ipcServer -> Shutdown();

		if (result != SERR_SUCCESS)
		{
			WriteToLog("SERVER service. --> Can't shutdown IPC server!");
			throw result;
		}
		else
		{
			Cleanup();	
			WriteToLog("SERVER service. --> NovaTend server successfully stoped!");
		}
	}
}

/****************************************************************

   Class : ServerService

   Method : OnPause

   Description : Executes when a Pause command is sent to the 
				 service by the SCM. 

*****************************************************************/
void ServerService :: OnPause(void)
{
	if (ipcServer)
	{
		int result = ipcServer -> StopRequestProcessing();
		if (result != SERR_SUCCESS)
		{
			WriteToLog("SERVER service. --> Can't stop request processing!");
			throw result;
		}

		WriteToLog("SERVER service. --> NovaTend server successfully paused!");
	}
}

/****************************************************************

   Class : ServerService

   Method : OnContinue

   Description : Executes when a Continue command is sent to the 
				 service by the SCM. 

*****************************************************************/
void ServerService :: OnContinue(void)
{
	if (ipcServer)
	{
		int result = ipcServer -> StartRequestProcessing();
		if (result != SERR_SUCCESS)
		{
			WriteToLog("SERVER service. --> Can't start request processing!");
			throw result;
		}

		WriteToLog("SERVER service. --> NovaTend server successfully resumed!");
	}
}

/****************************************************************

   Class : ServerService

   Method : OnShutdown

   Description : Executes when a Sthutdown command is sent to the 
				 service by the SCM. 

*****************************************************************/
void ServerService :: OnShutdown(void)
{
	OnStop();
}

/****************************************************************

   Class : ServerService

   Method : Cleanup

   Description : Delete instances

*****************************************************************/
void  ServerService :: Cleanup(void)
{
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
}

/****************************************************************

   Class : ServerService

   Method : CheckLicense

   Parameters :
			Input:
				pServer - description of HOST-server

   Returns : result of license checking

   Description : Check license

*****************************************************************/
bool ServerService :: CheckLicense(PSERVER_DESCRIPTION pServer)
{
	WriteToLog("SERVER service. --> License checking...");

	// Check server descriptor
	if (!pServer)
	{
		WriteToLog("SERVER service. --> License checking. Wrong server descriptor!");
		return false;
	}

	// Check command manager instance
	if (!commandManager)
	{
		WriteToLog("SERVER service. --> License checking. Wrong command manager instance!");
		return false;
	}
	
	// Check license owner
	char ownerName[STR_VALUE_LEN] = "USER";
	if (!(commandManager -> CheckLicense("LICOWNER", ownerName)))
	{
		WriteToLog("SERVER service. License checking. --> Prohibited user!");
		return false;
	}

	// Get current time
	time_t nowSeconds;
	struct tm inpTime;
	time (&nowSeconds);
	inpTime = * localtime(&nowSeconds);

	// Check expiration date
	if(!(commandManager -> CheckLicense("EXPDATE", &inpTime, 0, REL_TYPE_LESS)))
	{
		WriteToLog("SERVER service. License checking. --> License period expired!");
		return false;
	}

	// Check NovaTend system version
	int dllVersion = zServerServiceDllDefinition.dllVersion;
	if(!(commandManager -> CheckLicense("SYSVERSION", &dllVersion)))
	{
		WriteToLog("SERVER service. License checking. --> Prohibited software version!");
		return false;
	}

	// Check OS version
	char osVerStr[STR_VALUE_LEN] = "";
	if(!(commandManager -> CheckLicense("OSVERSION", GetOSVersion(osVerStr))))
	{
		WriteToLog("SERVER service. License checking. --> Prohibited OS version!");
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

	if(!(commandManager -> CheckLicense("SERVERTYPE", serverTypeStr)))
	{
		WriteToLog("SERVER service. License checking. --> Prohibited server type!");
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
	
	if(!(commandManager -> CheckLicense("IPADDRESS", ipAddressStr)))
	{
		WriteToLog("SERVER service. License checking. --> Prohibited IP address!");
		return false;
	}

	return true;
}


/****************************************************************

   Class : ServerService

   Method : GetMaxClientsCount

   Returns : maximum count of clients

   Description : Get maximum count of clients

*****************************************************************/
int ServerService :: GetMaxClientsCount(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_SRV_SRV)
		WriteToLog("ServerService : GetMaxClientsCount. Start");
	#endif

	int maxClientsCount = 0;

	if (commandManager)
	{
		commandManager -> CheckLicense("MAXCLIENTSCOUNT", &maxClientsCount, 0, REL_TYPE_EQUAL);
	}
	else
		WriteToLog("SERVER service. --> License checking. Wrong command manager instance!");

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_SRV_SRV)
		WriteToLog("ServerService : GetMaxClientsCount. Done");
	#endif

	return maxClientsCount;
}