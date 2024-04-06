/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetContentCommand.cpp

   Description :  this module implements methods of
				  class GetContentCommand

*****************************************************************/

#include "stdafx.h"
#include "GetContentCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : GetContentCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				pLicRest - pointer to license restrictions

*****************************************************************/
GetContentCommand :: GetContentCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : constructor");
	#endif

	licenseManager = new LicenseManager(zHostCmdDllDefinition.dllID, logWriter);
	contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
}

/****************************************************************

   Class : GetContentCommand

   Method : Destructor

*****************************************************************/
GetContentCommand :: ~GetContentCommand(void)
{
	delete contentManager;
	delete licenseManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetContentCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetContentCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((!parameters) || 
		((parameters) &&
		(parameters -> paramCount == 0)))
	{

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			PPRESET_CONTAINER preset = GetUserContent();
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackPresetContainer(preset, RETURN_CMD_DATA);
			preset = DeleteContent(preset);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetContentCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	else
	if ((parameters) && 
		(parameters -> paramCount == 3) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[0] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[1] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[2] -> paramDataType == DWORD_DATA))
	{

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
		
		// Get compuetr name
		char compName[NAME_LEN];
		serializationManager -> UnpackString(parameters -> paramList[0], compName);

		// Get user ID
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[1]);

		// Get OS ID
		int osID = serializationManager -> UnpackDWORD(parameters -> paramList[2]);


		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			PPRESET_CONTAINER preset = GetUserContent(compName, userID, osID);
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackPresetContainer(preset, RETURN_CMD_DATA);
			preset = DeleteContent(preset);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("GetContentCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("GetContentCommand : Execute. Wrong input parameters!");

		WriteToLog("GetContentCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetContentCommand

   Method : GetUserContent

   Return : Pointer to user conetnt container

	Description : Get user content container

*****************************************************************/
PPRESET_CONTAINER GetContentCommand :: GetUserContent(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : GetUserContent. Start");
	#endif
	
	PPRESET_CONTAINER content = NULL;

	if (contentManager)
		content = contentManager -> GetDefaultContent();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : GetUserContent. Done");
	#endif

	return content - dllUserCheckResult;
}

/****************************************************************

   Class : GetContentCommand

   Method : GetUserContent

   Parameters :
			Input : 
				compName - computer name
				userID - user ID
				osID - OS ID

   Return : pointer to user content container
	
	Description :  Get user content from database

*****************************************************************/
PPRESET_CONTAINER GetContentCommand :: GetUserContent(char * compName, int userID, int osID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : GetUserContent. Start");
	#endif
	
	PPRESET_CONTAINER content = NULL;

	if (contentManager)	
	{
		PUSER_DESCRIPTOR pUser = contentManager -> GetUserDescriptor(userID);
	
		if (pUser)
		{

			content = contentManager -> GetUserContent(compName, 
													   userID, 
													   osID, 
													   licenseManager -> CheckLicensePointValue("USERFUNC", "EDUCATION") && pUser -> needStudy && FirstUserSignInToday(pUser -> lastLogOnDate), 
													   licenseManager -> CheckLicensePointValue("USERFUNC", "USER_NOTIFICATION"), 
													   licenseManager -> CheckLicensePointValue("USERFUNC", "LEGAL_DISCLAIMER"));
		
			pUser = contentManager -> RemoveUserDescriptor(pUser);
		}
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : GetUserContent. Done");
	#endif

	return content - dllUserCheckResult;
}

/****************************************************************

   Class : GetContentCommand

   Method : FirstUserSignInToday

   Parameters :
			Input : 
				date - sign in date string

   Return : TRUE - if it is first time

   Description : Is it first sign in for today for this user?

*****************************************************************/
bool GetContentCommand :: FirstUserSignInToday(char * date)
{
	///////////////////////////////////
	//
	return true;
	//
	///////////////////////////////////

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : FirstUserSignInToday. Start");
	#endif
	
	if (!date) 
		return true;

	// Get current data
	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);
	char timeStr[16], cmpDate[16];
	
	strftime(timeStr, 16, "%Y-%m-%d", timeinfo);

	int lenTimeStr = strlen(timeStr);
	if (lenTimeStr > 0)
	{
		strncpy(cmpDate, date, lenTimeStr);
		cmpDate[lenTimeStr] = 0;
	}
	else
		cmpDate[0] = 0;

	if(strcmp(timeStr, cmpDate) == 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("GetContentCommand : FirstUserSignInToday. Not first time sign in");
			WriteToLog("GetContentCommand : FirstUserSignInToday. Done");
		#endif

		return false;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("GetContentCommand : FirstUserSignInToday. First time sign in");
			WriteToLog("GetContentCommand : FirstUserSignInToday. Done");
		#endif

		return true;
	}
}

/****************************************************************

   Class : GetContentCommand

   Method : DeleteContent

   Parameters :
			Input : 
				content - user content

   Description : Delete user content

*****************************************************************/
PPRESET_CONTAINER GetContentCommand :: DeleteContent(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : DeleteContent. Start");
	#endif

	// Validate container pointer
	if ((content) && (contentManager))
		content = contentManager -> ClearContent(content);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("GetContentCommand : DeleteContent. Done");
	#endif

	return content;
}