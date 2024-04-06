/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckScheduleCommand.cpp

   Description :  this module implements methods of
				  class CheckScheduleCommand

*****************************************************************/

#include "stdafx.h"
#include "CheckScheduleCommand.h"

#include <ContentManager.h>
#include <Scheduler.h>

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : CheckScheduleCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
CheckScheduleCommand :: CheckScheduleCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckScheduleCommand : constructor");
	#endif
}

/****************************************************************

   Class : CheckScheduleCommand

   Method : Destructor

*****************************************************************/
CheckScheduleCommand :: ~CheckScheduleCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckScheduleCommand : destructor");
	#endif
}

/****************************************************************

   Class : CheckScheduleCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST CheckScheduleCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckScheduleCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 3))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);

		// Unpack user ID
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);

		// Unpack computer name
		char compName[NAME_LEN] = "";
		serializationManager -> UnpackString(parameters -> paramList[1], compName);
		
		// Unpack function ID
		int functionID = serializationManager -> UnpackDWORD(parameters -> paramList[2]);
					
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			int actionID = CheckSchedulerRecords(userID, compName, functionID);

			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackDWORD(actionID, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("CheckScheduleCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("CheckScheduleCommand : Execute. Wrong input parameters!");

		WriteToLog("CheckScheduleCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : CheckScheduleCommand

   Method : CheckSchedulerRecords
   
   Parameters :
			Input : 
				userID - user ID
				compName - computer name
				functionID - function ID

   Return : action code
	
   Description :  Check scheduler records

*****************************************************************/
int CheckScheduleCommand :: CheckSchedulerRecords(int userID, char * compName, int functionID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckScheduleCommand : CheckSchedulerRecords. Start");
	#endif

	Scheduler * scheduler = new Scheduler(zHostCmdDllDefinition.dllID, logWriter);

	int verificationResult = scheduler -> VerifyScheduleRecords(userID, compName, functionID);

	delete scheduler;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckScheduleCommand : CheckSchedulerRecords. Done");
	#endif

	return verificationResult;
}
