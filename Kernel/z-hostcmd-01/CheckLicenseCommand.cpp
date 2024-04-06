/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckLicenseCommand.cpp

   Description :  this module implements methods of
				  class CheckLicenseCommand

*****************************************************************/

#include "stdafx.h"
#include "CheckLicenseCommand.h"

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : CheckLicenseCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				pLicRest - pointer to license restrictions

*****************************************************************/
CheckLicenseCommand :: CheckLicenseCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckLicenseCommand : constructor");
	#endif

	licenseManager = new LicenseManager(zHostCmdDllDefinition.dllID, logWriter);
}

/****************************************************************

   Class : CheckLicenseCommand

   Method : Destructor

*****************************************************************/
CheckLicenseCommand :: ~CheckLicenseCommand(void)
{
	delete licenseManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckLicenseCommand : destructor");
	#endif
}

/****************************************************************

   Class : CheckLicenseCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST CheckLicenseCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("CheckLicenseCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters
	if ((parameters) && 
		(parameters -> paramCount == 4) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[1] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[2] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[3]) &&
		(parameters -> paramList[3] -> paramDataType == DWORD_DATA))
	{

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
		
		// Unpack license point ID
		char id[STR_VALUE_LEN] = "";
		serializationManager -> UnpackString(parameters -> paramList[0], id);

		// Unpck string value
		char strValue[STR_VALUE_LEN] = "";
		serializationManager -> UnpackString(parameters -> paramList[1], strValue);

		// Unpack index
		int index = serializationManager -> UnpackDWORD(parameters -> paramList[2]);

		// Unpack relation type
		int relType = serializationManager -> UnpackDWORD(parameters -> paramList[3]);

		// Check license point data
		bool accessible = licenseManager -> CheckLicensePointValue(id, strValue, index, relType);

		// Get string value
		licenseManager -> GetLicensePointValue(id, strValue, index);

		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			result -> paramCount = 2;
			result -> paramList[0] = serializationManager -> PackByte((unsigned char)accessible, RETURN_CMD_DATA);
			result -> paramList[1] = serializationManager -> PackString(strValue, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			else
				WriteToLog("CheckLicenseCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	else
	if ((parameters) && 
		(parameters -> paramCount == 4) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[1] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[2] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[3]) &&
		(parameters -> paramList[3] -> paramDataType == DWORD_DATA))
	{

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
		
		// Unpack license point ID
		char id[STR_VALUE_LEN] = "";
		serializationManager -> UnpackString(parameters -> paramList[0], id);

		// Unpack int value
		int intValue = serializationManager -> UnpackDWORD(parameters -> paramList[1]);

		// Unpack index
		int index = serializationManager -> UnpackDWORD(parameters -> paramList[2]);

		// Unpack relation type
		int relType = serializationManager -> UnpackDWORD(parameters -> paramList[3]);

		// Check license point data
		bool accessible = licenseManager -> CheckLicensePointValue(id, intValue, index, relType);

		// Get string value
		intValue = licenseManager -> GetLicensePointValue(id, index);

		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			result -> paramCount = 2;
			result -> paramList[0] = serializationManager -> PackByte((unsigned char)accessible, RETURN_CMD_DATA);
			result -> paramList[1] = serializationManager -> PackDWORD(intValue, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			else
				WriteToLog("CheckLicenseCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	else
	if ((parameters) && 
		(parameters -> paramCount == 4) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[1]) &&
		(parameters -> paramList[1] -> paramDataType == TIMEINFO_DATA) &&
		(parameters -> paramList[2]) &&
		(parameters -> paramList[2] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[3]) &&
		(parameters -> paramList[3] -> paramDataType == DWORD_DATA))
	{

		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
		
		// Unpack license point ID
		char id[STR_VALUE_LEN] = "";
		serializationManager -> UnpackString(parameters -> paramList[0], id);

		// Unpack timeinfo value
		struct tm * tmValue = serializationManager -> UnpackTimeinfo(parameters -> paramList[1]);

		// Unpack index
		int index = serializationManager -> UnpackDWORD(parameters -> paramList[2]);

		// Unpack relation type
		int relType = serializationManager -> UnpackDWORD(parameters -> paramList[3]);

		// Check license point data
		bool accessible = licenseManager -> CheckLicensePointValue(id, tmValue, index, relType);

		// Get string value
		licenseManager -> GetLicensePointValue(id, tmValue, index);

		// Delete timeinfo value
		if (tmValue) free(tmValue);

		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			result -> paramCount = 2;
			result -> paramList[0] = serializationManager -> PackByte((unsigned char)accessible, RETURN_CMD_DATA);
			result -> paramList[1] = serializationManager -> PackTimeinfo(tmValue, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			else
				WriteToLog("CheckLicenseCommand : Execute. Can't create result parameters list!");
		#endif

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("CheckLicenseCommand : Execute. Wrong input parameters!");

		WriteToLog("CheckLicenseCommand : Execute. Done");
	#endif

	return result;
}