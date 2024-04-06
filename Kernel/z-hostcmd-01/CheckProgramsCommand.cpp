/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckProgramsCommand.cpp

   Description :  this module implements methods of
				  class CheckProgramsCommand

*****************************************************************/

#include "stdafx.h"
#include "CheckProgramsCommand.h"
#include <Scheduler.h>

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : CheckProgramsCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
CheckProgramsCommand :: CheckProgramsCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckProgramsCommand : constructor");
	#endif
}

/****************************************************************

   Class : CheckProgramsCommand

   Method : Destructor

*****************************************************************/
CheckProgramsCommand :: ~CheckProgramsCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckProgramsCommand : destructor");
	#endif
}

/****************************************************************

   Class : CheckProgramsCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST CheckProgramsCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckProgramsCommand : Execute. Start");
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
		
		// Program list
		PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgListCnt = serializationManager -> UnpackControlledProgramListContainer(parameters -> paramList[2]);
					
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			CheckProgramsInList(userID, compName, prgListCnt);

			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackControlledProgramListContainer(prgListCnt, RETURN_CMD_DATA);

			prgListCnt = DeleteProgramInfoContainerList(prgListCnt);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("CheckProgramsCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("CheckProgramsCommand : Execute. Wrong input parameters!");

		WriteToLog("CheckProgramsCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : CheckProgramsCommand

   Method : CheckProgramsInList
   
   Parameters :
			Input : 
				userID - user ID
				compName - computer name
				programList - list of programs
	
   Description :  Check programs in list

*****************************************************************/
void CheckProgramsCommand :: CheckProgramsInList(int userID, char * compName, PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckProgramsCommand : CheckProgramsInList. Start");
	#endif

	Scheduler * scheduler = new Scheduler(zHostCmdDllDefinition.dllID, logWriter);
	scheduler -> VerifySchedulePrograms(userID, compName, programList);
	scheduler -> VerifyProgramList(programList);
	delete scheduler;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckProgramsCommand : CheckProgramsInList. Done");
	#endif
}

/****************************************************************

   Class : CheckProgramsCommand

   Method : DeleteProgramInfoContainerList
   
   Parameters :
			Input : 
				programList - list of programs
	
   Description :  Delete program list

*****************************************************************/
PCONTROL_PROGRAM_INFO_CONTAINER_LIST CheckProgramsCommand :: DeleteProgramInfoContainerList(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckProgramsCommand : DeleteProgramInfoContainerList");
	#endif

	if (programList)
	{
		for(int i = 0; (i < programList -> programListSize) && (i < MAX_PROGRAMS_LIST); i++)
			free(programList -> programList[i]);
		
		free(programList);
		programList = NULL;
	}

	return programList;
}