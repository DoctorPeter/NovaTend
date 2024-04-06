/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : SaveNotificationHistoryCommand.cpp

   Description :  this module implements methods of
				  class SaveNotificationHistoryCommand

*****************************************************************/

#include "stdafx.h"
#include "SaveNotificationHistoryCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : SaveNotificationHistoryCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
SaveNotificationHistoryCommand :: SaveNotificationHistoryCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SaveNotificationHistoryCommand : constructor");
	#endif
}

/****************************************************************

   Class : SaveNotificationHistoryCommand

   Method : Destructor

*****************************************************************/
SaveNotificationHistoryCommand :: ~SaveNotificationHistoryCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SaveNotificationHistoryCommand : destructor");
	#endif
}

/****************************************************************

   Class : SaveNotificationHistoryCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST SaveNotificationHistoryCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SaveNotificationHistoryCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 2) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[1] -> paramDataType == DWORD_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
					
		// Unpack data
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
		int noticeID = serializationManager -> UnpackDWORD(parameters -> paramList[1]);
						
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			bool setResult = SaveUserNotificationHistory(userID, noticeID);

			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackByte((unsigned char)setResult, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("SaveNotificationHistoryCommand : Execute. Can't create result parameters list!");
		#endif
		
		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("SaveNotificationHistoryCommand : Execute. Wrong input parameters!");

		WriteToLog("SaveNotificationHistoryCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SaveNotificationHistoryCommand

   Method : SaveUserNotificationHistory

   	Parameters :
			Input : 
				userID - user ID
				noticeID - notice ID

   Return : Saving result

   Description : Save user notification result

*****************************************************************/
bool SaveNotificationHistoryCommand :: SaveUserNotificationHistory(int userID, int noticeID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SaveNotificationHistoryCommand : SaveUserNotificationHistory. Start");
	#endif

	bool resFlag = false;
	
	ContentManager * contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
	resFlag = contentManager -> SaveUserNotificationHistory(userID, noticeID);
	delete contentManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("SaveNotificationHistoryCommand : SaveUserNotificationHistory. Done");
	#endif

	return resFlag;
}