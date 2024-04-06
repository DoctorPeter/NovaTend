#include "stdafx.h"

#include <SafeLogWriter.h>
#include <IPCServerEx.h>
#include <IPCClientEx.h>

#include <WinAuthenticateManager.h>
#include <LicensePoint.h>
#include <LicenseManager.h>

#include <SettingsManager.h>
#include <IPCClientsManager.h>
#include <IPCClientsManagerEx.h>

#include <FileTransferCommand.h>

#include <SQLiteDatabaseManager.h>

#include <HubCommandManager.h>
#include <HostCommandManager.h>
#include <CommandHistoryManager.h>
#include <SerializationManager.h>

#include <GetScreenshotCommand.h>
#include <BackgroundThread.h>
#include <CommandHistorian.h>
#include <ClientProcessor.h>

#include <FileProcessor.h>
#include <ClientAuthManager.h>

#include <SchedulerCondition.h>

#include <ContentManager.h>

#include <ResetUserPwdCommand.h>

int main(int argc, char **argv)
{
	Encryptor * encryptor = new Encryptor(Z_HOST_SERVER_ID);
	encryptor -> Init();

	SerializationManager * serializationManager = new SerializationManager(Z_HOST_SERVER_ID, NULL);

	PCOMMAND_PARAMETER_LIST inputParams = serializationManager -> CreateCommandParameterList();

	inputParams -> paramCount = 1;
	inputParams -> paramList[0] = serializationManager -> PackDWORD(1, RETURN_CMD_DATA);

	ResetUserPwdCommand * command = new ResetUserPwdCommand(Z_HOST_SERVER_ID, NULL);

	PCOMMAND_PARAMETER_LIST resultParams = command -> Execute(inputParams);

	delete command;

	inputParams = serializationManager -> DeleteCommandParameterList(inputParams);
	resultParams = serializationManager -> DeleteCommandParameterList(resultParams);

	delete serializationManager;

	encryptor -> Cleanup();
	delete encryptor;


	/*SchedulerCondition * schedulerCondition = new SchedulerCondition(Z_CONTENT_DLL_ID, NULL, "time[10:00:00-12:00:00] and count[1-100] or not day[mon-tue]");
	
	char string[256] = "";
	schedulerCondition -> GetConditionString(string);

	schedulerCondition -> BuildCondition(string);

	delete schedulerCondition;*/
	
	/*char dirName[MAX_PATH] = "D:\\Work\\NovaTend\\Kernel\\Win32\\Debug";
	PFOLDER_INFO_CONTAINER pFolder = ReadDirectoryInfo(dirName,1024);

	if (pFolder)
	{
		SettingsManager * settingsManager = new SettingsManager(Z_WIN_CRED_PROV_DLL_ID);	

		for (int i = 0; i < pFolder -> filesCount; i++)
		{
			if ((strstr(pFolder -> filesList[i] -> fileName, ".exe") != NULL) ||
				(strstr(pFolder -> filesList[i] -> fileName, ".dll") != NULL))
			{
				char fileName[MAX_PATH];
				GetFileName(pFolder -> filesList[i] -> fileName, fileName);
				strcpy(pFolder -> filesList[i] -> fileName, "D:\\Work\\NovaTend\\Kernel\\Win32\\Debug");
				strcat(pFolder -> filesList[i] -> fileName, "\\");
				strcat(pFolder -> filesList[i] -> fileName, fileName);

				WCHAR wFileName[MAX_PATH];
				mbstowcs(wFileName, fileName, MAX_PATH);

				settingsManager -> SetUpdateFileInfo(L"SOFTWARE\\NovaTend\\Update", wFileName, pFolder -> filesList[i]);
			}

			free(pFolder -> filesList[i]);
		}
		
		free(pFolder);
		delete settingsManager;

	}*/


	/*Encryptor * encryptor = new Encryptor(Z_HOST_SERVER_ID);
	encryptor -> Init();

	GetScreenshotCommand * command = new GetScreenshotCommand(Z_HUB_SERVER_ID, NULL);
	
	SerializationManager * serializationManager = new SerializationManager(Z_HUBCMD_DLL_ID, NULL);
	
	PCOMMAND_PARAMETER_LIST input = serializationManager -> CreateCommandParameterList();
	input -> paramCount = 1;
	input -> paramList[0] = serializationManager -> PackDWORD(-1, INPUT_CMD_DATA);

	PCOMMAND_PARAMETER_LIST result = command -> Execute(input);

	input = serializationManager -> DeleteCommandParameterList(input);
	result = serializationManager -> DeleteCommandParameterList(result);

	delete serializationManager;

	delete command;

	encryptor -> Cleanup();
	delete encryptor;*/


	//SQLiteDatabaseManager * dbManager = new SQLiteDatabaseManager(Z_CONTENT_DLL_ID, NULL);

	//dbManager -> Connect("HUBHIST.DB");
	//	
	//dbManager -> Execute("DELETE FROM CommandsHistory;");

	//for (int i = 1; i < 10; i++)
	//{
	//	char sql[1024] = "";
	//	sprintf(sql, "INSERT INTO CommandsHistory (CmdID, UserID) VALUES (%d, %d);", i, i);
	//	dbManager -> Execute(sql);
	//}
	//
	//char sql[1024] = "";
	//sprintf(sql, "SELECT ID, CmdID, UserID, ExecTime FROM CommandsHistory WHERE ExecTime BETWEEN '2015-12-08 18:00:00' AND '2015-12-08 19:00:00';");
	//printf("%s\n",sql);

	////sprintf(sql, "SELECT ID, CmdID, UserID, ExecTime FROM CommandsHistory;");

	//ResultSet * resultSet = dbManager -> ExecuteSelectQuery(sql);

	//int idBuf = 0;
	//int cmdIDBuf = 0;
	//int userIDBuf = 0;
	//char execTimeBuf[256] = "";

	//resultSet -> Bind(0, &idBuf, sizeof(idBuf), SQLITE_INTEGER);
	//resultSet -> Bind(1, &cmdIDBuf, sizeof(cmdIDBuf), SQLITE_INTEGER);
	//resultSet -> Bind(2, &userIDBuf, sizeof(userIDBuf), SQLITE_INTEGER);
	//resultSet -> Bind(3, execTimeBuf, 256, SQLITE_TEXT);

	//while(resultSet -> MoveNext())
	//{
	//	printf("%d %d %d %s \n", idBuf, cmdIDBuf, userIDBuf, execTimeBuf);
	//}

	//delete resultSet;

	//dbManager -> Disconnect();

	//delete dbManager;

	/*FileTransferCommand * command = new FileTransferCommand(Z_HUB_SERVER_ID, NULL);

	SerializationManager * serializationManager = new SerializationManager(Z_HUBCMD_DLL_ID, NULL);

	PCOMMAND_PARAMETER_LIST input = serializationManager -> CreateCommandParameterList();
	
	input -> paramCount = 3;
	input -> paramList[0] = serializationManager -> PackString("d:\\Work\\NovaTend_LOG_Files\\NovaTend_HOST_Server_10.31.2015.log", INPUT_CMD_DATA);
	input -> paramList[1] = serializationManager -> PackDWORD(0, INPUT_CMD_DATA);
	input -> paramList[2] = serializationManager -> PackDWORD(100, INPUT_CMD_DATA);
		
	PCOMMAND_PARAMETER_LIST result = command -> Execute(input);

	input = serializationManager -> DeleteCommandParameterList(input);

	delete command;

	result = serializationManager -> DeleteCommandParameterList(result);

	delete serializationManager;*/

	//// Get IPC connections information
	//SettingsManager * settingsManager = new SettingsManager(Z_WIN_CRED_PROV_DLL_ID);
	//
	//// Get info of host server
	//PSERVER_DESCRIPTION pHostServer = settingsManager -> GetHostServer();

	//// Get info of GLOBAL server
	//PSERVER_DESCRIPTION pGlobalServer = settingsManager -> GetGlobalServer();
	//
	//unsigned int gServerID = 0;
	//char gServerIPAddress[ADDRESS_SIZE] = "";
	//unsigned int gServerPort = 0;

	//// Get global server info
	//if (pGlobalServer)
	//{
	//	gServerID = pGlobalServer -> serverID;
	//	gServerPort = pGlobalServer -> port;
	//	strcpy(gServerIPAddress, pGlobalServer -> ipAddress);
	//	free(pGlobalServer);
	//}

	//delete settingsManager;
	//
	//// Create HOST-connections manager
	//IPCClientsManagerEx * _hostConnectionsManager = new IPCClientsManagerEx(Z_WIN_CRED_PROV_DLL_ID, NULL, gServerID, gServerIPAddress, gServerPort);

	//// HOST-server
	//if (pHostServer)
	//{
	//	_hostConnectionsManager -> AddConnection(pHostServer -> serverID,
	//											 pHostServer -> serverType,
	//											 pHostServer -> ipAddress,
	//											 pHostServer -> port,
	//											 CLIENT_TYPE_WCP,
	//											 1,
	//											 "Windows credential provider",
	//											 NULL,
	//											 DEFAULT_TIMEOUT);
	//	free(pHostServer);
	//}


	//delete _hostConnectionsManager;

	//if (strcmp(argv[1], "-gs") == 0)
	//{
	//	// Global server
	//	SafeLogWriter * gLogWriter = new SafeLogWriter(Z_WIN_SERVICE_DLL_ID, LOG_MODE_WRITE_TO_FILE, "Experimental_GlobalServerLOG.log");

	//	CommandManager * gServerCmdMan = new  CommandManager(Z_HOSTCMD_DLL_ID, gLogWriter);

	//	IPCServerEx * gIpcServerEx = new IPCServerEx(Z_HOST_SERVER_ID, 
	//													gLogWriter, 
	//													1, 
	//													SERVER_TYPE_HOST, 
	//													100, 
	//													"Global server", 
	//													100, 
	//													AF_INET, 
	//													SOCK_STREAM, 
	//													IPPROTO_TCP, 
	//													0x0202, 
	//													16, 
	//													"192.168.1.2", 
	//													gServerCmdMan);

	//	gIpcServerEx -> Start();
	//	gIpcServerEx -> StartRequestProcessing();

	//	//getch();
	//	cin.get();


	//	delete gIpcServerEx;
	//	delete gServerCmdMan;
	//	delete gLogWriter;
	//}
	//else
	//if (strcmp(argv[1], "-ls") == 0)
	//{
	//	// Local server
	//	SafeLogWriter * lLogWriter = new SafeLogWriter(Z_WIN_SERVICE_DLL_ID, LOG_MODE_WRITE_TO_FILE, "Experimental_LocalServerLOG.log");

	//	CommandManager * lServerCmdMan = new  CommandManager(Z_HOSTCMD_DLL_ID, lLogWriter);

	//	SERVER_DESCRIPTION serverDescription;

	//	serverDescription.serverID = 2;
	//	serverDescription.serverType = SERVER_TYPE_HOST;
	//	serverDescription.serverPriority = 100;
	//	strcpy(serverDescription.serverName, "Local server");
	//	strcpy(serverDescription.ipAddress, "192.168.1.2");
	//	serverDescription.port = 17;

	//	IPCServerEx * lIpcServerEx = new IPCServerEx(Z_HOST_SERVER_ID, 
	//													lLogWriter, 
	//													serverDescription.serverID, 
	//													serverDescription.serverType, 
	//													serverDescription.serverPriority, 
	//													serverDescription.serverName, 
	//													100, 
	//													AF_INET, 
	//													SOCK_STREAM, 
	//													IPPROTO_TCP, 
	//													0x0202, 
	//													serverDescription.port, 
	//													serverDescription.ipAddress, 
	//													lServerCmdMan);

	//	lIpcServerEx -> Start();
	//	lIpcServerEx -> StartRequestProcessing();

	//	//getch();
	//	//cin.get();

	//	// Client on the server
	//	SafeLogWriter * gClientLogWriter = new SafeLogWriter(Z_WIN_SERVICE_DLL_ID, LOG_MODE_WRITE_TO_FILE, "Experimental_GlobalServerClientLOG.log");

	//

	//	IPCClientEx * gIpcClientEx = new IPCClientEx(Z_HUBCMD_DLL_ID,
	//													gClientLogWriter,
	//													AF_INET, 
	//													SOCK_STREAM, 
	//													IPPROTO_TCP, 
	//													0x0202, 
	//													1,
	//													SERVER_TYPE_HOST,
	//													16,
	//													"192.168.1.2",
	//													1,
	//													16,
	//													"192.168.1.2",
	//													DEFAULT_TIMEOUT,
	//													CLIENT_TYPE_HOST,
	//													1,
	//													"Connected to global server",
	//													&serverDescription,
	//													lIpcServerEx);

	//
	//	gIpcClientEx -> Connect();
	//	gIpcClientEx -> StartReconnection();

	//	//getch();
	//	cin.get();

	//	delete lIpcServerEx;
	//	delete lServerCmdMan;
	//	delete gIpcClientEx;
	//	delete gClientLogWriter;
	//	delete lLogWriter;
	//}
	//else
	//if (strcmp(argv[1], "-lc") == 0)
	//{
	//	// Client connection via global server
	//	SafeLogWriter * clientLogWriter = new SafeLogWriter(Z_WIN_SERVICE_DLL_ID, LOG_MODE_WRITE_TO_FILE, "Experimental_LocalServerClientLOG.log");

	//	IPCClientEx * ipcClientEx = new IPCClientEx(Z_HUBCMD_DLL_ID,
	//													clientLogWriter,
	//													AF_INET, 
	//													SOCK_STREAM, 
	//													IPPROTO_TCP, 
	//													0x0202, 
	//													2,
	//													SERVER_TYPE_HOST,
	//													17,
	//													"0.0.0.0",
	//													1,
	//													16,
	//													"192.168.1.2",
	//													DEFAULT_TIMEOUT,
	//													CLIENT_TYPE_HOST,
	//													1,
	//													"Connected via global server",
	//													NULL,
	//													NULL);

	//
	//	Sleep(10000);

	//	ipcClientEx -> Connect();
	//	ipcClientEx -> StartReconnection();

	//	//getch();
	//	cin.get();
	//	
	//	delete ipcClientEx;
	//	delete clientLogWriter;
	//}

	
	

	//Encryptor * encryptor = new Encryptor(Z_HOST_SERVER_ID);
	//encryptor -> Init();

	//// Create serialization manager
	//SerializationManager * serializationManager = new SerializationManager(Z_DESKTOPCMD_DLL_ID, NULL);

	//// Create request structure
	//PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_CHECK_SCHEDULE, REQUEST_CMD, 1, 2);
	//
	//pRequest -> parameters -> paramCount = 3;

	//// Pack user ID
	//pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(1, INPUT_CMD_DATA);

	//char compName[NAME_LEN];
	//DWORD compNameLen = NAME_LEN;
	//GetComputerNameA(compName, &compNameLen);

	//// Pack computer name
	//pRequest -> parameters -> paramList[1] = serializationManager -> PackString(compName, INPUT_CMD_DATA);

	//// Pack container
	//pRequest -> parameters -> paramList[2] = serializationManager -> PackDWORD(EDUCATION_FUNCTION, INPUT_CMD_DATA);


	//CheckScheduleCommand * command = new CheckScheduleCommand(Z_HOSTCMD_DLL_ID, NULL);

	//command -> Execute(pRequest -> parameters);

	//delete command;

	//ContentManager * contentManager = new ContentManager(Z_HOSTCMD_DLL_ID, NULL);

	//contentManager -> GetUserContent("comp1", 1, 1, true, true, true);

	//delete contentManager;

	//ODBCDatabaseManager * db = new ODBCDatabaseManager(Z_CONTENT_DLL_ID, NULL);

	//char dsn[NAME_LEN];
	//char dbUser[NAME_LEN];
	//char dbPassword[STR_VALUE_LEN];

	//SettingsManager * settingsManager = new SettingsManager(Z_CONTENT_DLL_ID);
	//settingsManager -> GetDatabaseSourceName(dsn);
	//settingsManager -> GetDatabaseUserName(dbUser);
	//settingsManager -> GetDatabasePassword(dbPassword);
	//delete settingsManager;
	//
	//db -> Connect(dsn, dbUser, dbPassword);



	//char sourceData[STR_VALUE_LEN] = "";

	//strcpy(sourceData, "Dashboard manager");
	//int sourceDataLen = strlen(sourceData);

	//unsigned char encData[ENCRYPTED_DATA_SIZE];
	//int encDataLen = 0;
	//encryptor -> EncryptAndPackSecurityData((unsigned char *)sourceData, sourceDataLen, encData, ENCRYPTED_DATA_SIZE, &encDataLen);

	//char hex[STR_VALUE_LEN * 4] = "";
	//encryptor -> BinToHexStr(encData, encDataLen, hex, STR_VALUE_LEN * 4);

	//char sql[SQL_SIZE*4] = "";
	//sprintf(sql, "INSERT INTO Permissions (ID, Name) values (%d, %s)", DASHBOARD_ACCESS_MANAGER, hex);

	//db ->  Execute(sql);



	//strcpy(sourceData, "Schedule manager");
	//sourceDataLen = strlen(sourceData);

	//encryptor -> EncryptAndPackSecurityData((unsigned char *)sourceData, sourceDataLen, encData, ENCRYPTED_DATA_SIZE, &encDataLen);
	//encryptor -> BinToHexStr(encData, encDataLen, hex, STR_VALUE_LEN*4);

	//sprintf(sql, "INSERT INTO Permissions (ID, Name) values (%d, %s)", SCHEDULE_MANAGER, hex);

	//db ->  Execute(sql);


	//PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgListContainer =  (PCONTROL_PROGRAM_INFO_CONTAINER_LIST)malloc(sizeof(CONTROL_PROGRAM_INFO_CONTAINER_LIST));

	//prgListContainer -> programListSize = 3;

	//prgListContainer -> programList[0] = (PCONTROL_PROGRAM_INFO_CONTAINER)malloc(sizeof(CONTROL_PROGRAM_INFO_CONTAINER));
	//prgListContainer -> programList[0] -> allowed = true;
	//prgListContainer -> programList[0] -> pid = 1;
	//strcpy(prgListContainer -> programList[0] -> moduleName, "calc.exe");
	//strcpy(prgListContainer -> programList[0] -> programName, "Calculator");

	//prgListContainer -> programList[1] = (PCONTROL_PROGRAM_INFO_CONTAINER)malloc(sizeof(CONTROL_PROGRAM_INFO_CONTAINER));
	//prgListContainer -> programList[1] -> allowed = true;
	//prgListContainer -> programList[1] -> pid = 2;
	//strcpy(prgListContainer -> programList[1] -> moduleName, "winword.exe");
	//strcpy(prgListContainer -> programList[1] -> programName, "WORD");

	//prgListContainer -> programList[2] = (PCONTROL_PROGRAM_INFO_CONTAINER)malloc(sizeof(CONTROL_PROGRAM_INFO_CONTAINER));
	//prgListContainer -> programList[2] -> allowed = true;
	//prgListContainer -> programList[2] -> pid = 3;
	//strcpy(prgListContainer -> programList[2] -> moduleName, "notepad.exe");
	//strcpy(prgListContainer -> programList[2] -> programName, "Notepad");


	//// Create serialization manager
	//SerializationManager * serializationManager = new SerializationManager(Z_DESKTOPCMD_DLL_ID, NULL);

	//// Create request structure
	//PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_CHECK_PROGRAMS, REQUEST_CMD, 1, 2);
	//
	//pRequest -> parameters -> paramCount = 3;

	//// Pack user ID
	//pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(1, INPUT_CMD_DATA);

	//char compName[NAME_LEN];
	//DWORD compNameLen = NAME_LEN;
	//GetComputerNameA(compName, &compNameLen);

	//// Pack computer name
	//pRequest -> parameters -> paramList[1] = serializationManager -> PackString(compName, INPUT_CMD_DATA);

	//// Pack container
	//pRequest -> parameters -> paramList[2] = serializationManager -> PackControlledProgramListContainer(prgListContainer, INPUT_CMD_DATA);


	//free(prgListContainer);

	//CheckProgramsCommand * command = new CheckProgramsCommand(Z_HOST_SERVER_ID, NULL);

	//command -> Execute(pRequest -> parameters);

	//delete command;

	//delete serializationManager;

	/*encryptor -> Cleanup();
	delete encryptor;*/

	/*db -> Disconnect();
	delete db;*/

	return 0;
}