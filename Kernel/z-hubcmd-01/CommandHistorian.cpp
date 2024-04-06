/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.exe

   Module : CommandHistorian.cpp

   Description :  this module implements methods of
				  class CommandHistorian

*****************************************************************/

#include "stdafx.h"

#include "CommandHistorian.h"
#include <SettingsManager.h>
#include <SerializationManager.h>

#include <socket_def.h>

// z-hubcmd-01.exe definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;

/****************************************************************

   Class : CommandHistorian

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - dll user ID
				logWriter - pointer to LOG-writer instance
								
*****************************************************************/
CommandHistorian :: CommandHistorian(unsigned long dllUserID, CommandManager * commandManager, LogWriter * logWriter) : ThreadController(dllUserID, &zHubCmdDllDefinition, INFINITE)
{
	this -> logWriter = logWriter;
	this -> commandManager = commandManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("CommandHistorian : constructor");
	#endif
}

/****************************************************************

   Class : CommandHistorian

   Method : Destructor
   
*****************************************************************/
CommandHistorian :: ~CommandHistorian(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("CommandHistorian : destructor");
	#endif
}

/****************************************************************

   Class : CommandHistorian

   Method : CheckPeriodicFlag

   Returns : TRUE - if success

   Description : Check periodic flag
                 
*****************************************************************/
bool CommandHistorian :: CheckPeriodicFlag(void)
{
	SettingsManager * settingsManager = new SettingsManager(zHubCmdDllDefinition.dllID);

	if (settingsManager -> GetHistorianPeriodicFlag(&periodicallyFlag) != ERROR_SUCCESS)
		periodicallyFlag = false;

	delete settingsManager;

	return periodicallyFlag;
}

/****************************************************************

   Class : CommandHistorian

   Method : CheckPeriod

   Returns : TRUE - if success

   Description : Check historian period
                 
*****************************************************************/
bool CommandHistorian :: CheckPeriod(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("CommandHistorian : CheckPeriod. Start");
	#endif

	SettingsManager * settingsManager = new SettingsManager(zHubCmdDllDefinition.dllID);

	if (settingsManager -> GetHistorianPeriod(&periodValue) == ERROR_SUCCESS)
	{
		// Get current time
		time_t nowSeconds;
		time(&nowSeconds);

		// Subtract dates
		double resSeconds = difftime(nowSeconds, prevTimeSeconds);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			char message[STR_VALUE_LEN];
			sprintf(message, "CommandHistorian : CheckPeriod. Period: %d. Seconds: %d", periodValue, (int)resSeconds);
			WriteToLog(message);
		#endif
					
		// Prepare result
		bool result = false;

		if (resSeconds > periodValue * 60)
		{
			// Save current time
			prevTimeSeconds = nowSeconds;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("CommandHistorian : CheckPeriod. Period expired!");
			#endif

			result = true;
		}

		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("CommandHistorian : CheckPeriod. Done");
		#endif

		return result;
	}
	else
	{
		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("CommandHistorian : CheckPeriod. Can't get period!");
			WriteToLog("CommandHistorian : CheckPeriod. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : CommandHistorian

   Method : ControllerEntry

   Description : Write to history

*****************************************************************/
void CommandHistorian :: ControllerEntry(void)
{
	WriteToHistory();
}

/****************************************************************

   Class : CommandHistorian

   Method : WriteToHistory

   Description : Write to history

*****************************************************************/
void CommandHistorian :: WriteToHistory(void)
{
	if (commandManager)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("CommandHistorian : WriteToHistory. Start");
		#endif
		
		// Create settings manager instance
		SettingsManager * settingsManager = new SettingsManager(zHubCmdDllDefinition.dllID);

		bool getUserEnvFlag = false;
		bool getLoggedUserNameFlag = false;
		bool getScreenshotFlag = false;
		bool getSnapshotFlag = false;

		// Read flags
		settingsManager -> GetUserEnvironmentCommandFlag(&getUserEnvFlag);
		settingsManager -> GetLoggedUserNameCommandFlag(&getLoggedUserNameFlag);
		settingsManager -> GetScreenshotCommandFlag(&getScreenshotFlag);
		settingsManager -> GetCamSnapshotCommandFlag(&getSnapshotFlag);

		// Delete settings manager instance
		delete settingsManager;

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

		// Create command request
		commandManager -> clientDescr.clientType = CLIENT_TYPE_HOST;
		PCOMMAND_REQUEST_RESPONSE request = serializationManager -> CreateRequestResponse(CMD_GET_USER_ENV_INFO, REQUEST_CMD, commandManager -> clientDescr.clientID, commandManager -> serverDescr.serverID);

		if (request)
		{
			// Pack input parameter
			request -> parameters -> paramCount = 1;
			request -> parameters -> paramList[0] = serializationManager -> PackDWORD(-1, INPUT_CMD_DATA);
			
			// Execute command CMD_GET_USER_ENV_INFO
			if (getUserEnvFlag)
			{
				PCOMMAND_REQUEST_RESPONSE response = commandManager -> ExecuteCommand(request);
				response = serializationManager -> DeleteRequestResponse(response);
			}

			// Execute command CMD_GET_CLIENT_CAM_SNAPSHOT
			if ( getSnapshotFlag)
			{
				request -> header -> commandCode = CMD_GET_CLIENT_CAM_SNAPSHOT;
				PCOMMAND_REQUEST_RESPONSE response = commandManager -> ExecuteCommand(request);
				response = serializationManager -> DeleteRequestResponse(response);
			}

			// Execute command CMD_GET_CLIENT_SCREEN_SHOT
			if (getScreenshotFlag)
			{
				request -> header -> commandCode = CMD_GET_CLIENT_SCREEN_SHOT;
				PCOMMAND_REQUEST_RESPONSE response = commandManager -> ExecuteCommand(request);
				response = serializationManager -> DeleteRequestResponse(response);
			}

			// Execute command CMD_GET_LOGGED_USER_NAME
			if (getLoggedUserNameFlag)
			{
				request -> header -> commandCode = CMD_GET_LOGGED_USER_NAME;
				PCOMMAND_REQUEST_RESPONSE response = commandManager -> ExecuteCommand(request);
				response = serializationManager -> DeleteRequestResponse(response);
			}

			// Create request
			request = serializationManager -> DeleteRequestResponse(request);
		}
		
		// Delete serialization manager instance
		delete serializationManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("CommandHistorian : WriteToHistory. Done");
		#endif
	}
}

/****************************************************************

   Class : CommandHistorian

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int CommandHistorian :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}