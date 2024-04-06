/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetHardwareInfoCommand.cpp

   Description :  this module implements methods of
				  class GetHardwareInfoCommand

*****************************************************************/

#include "stdafx.h"
#include "GetHardwareInfoCommand.h"
#include <CommandHistoryManager.h>

// z-hubcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;
 
/****************************************************************

   Class : GetHardwareInfoCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
GetHardwareInfoCommand :: GetHardwareInfoCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetHardwareInfoCommand : constructor");
	#endif

	// Create serialization manager instance
	serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);
		
	m_pLoc = NULL;

    HRESULT hres =  CoInitializeEx(0, COINIT_MULTITHREADED); 

	if (FAILED(hres)) 
	{
		return;
	}

    hres =  CoInitializeSecurity(NULL, 
								 -1,                          // COM authentication
								 NULL,                        // Authentication services
								 NULL,                        // Reserved
								 RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
								 RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
								 NULL,                        // Authentication info
								 EOAC_NONE,                   // Additional capabilities 
								 NULL                         // Reserved
								);
	
	if (FAILED(hres)) 
	{
		CoUninitialize();
		return;
	}
    
    hres = CoCreateInstance(
        CLSID_WbemLocator,             
        0, 
        CLSCTX_INPROC_SERVER, 
        IID_IWbemLocator, (LPVOID *) &m_pLoc);

    if (FAILED(hres)) 
	{
		CoUninitialize();
		return;
	}
}

/****************************************************************

   Class : GetHardwareInfoCommand

   Method : Destructor

*****************************************************************/
GetHardwareInfoCommand :: ~GetHardwareInfoCommand(void)
{
	if (m_pLoc) 
		m_pLoc -> Release();

	CoUninitialize();

	delete serializationManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetHardwareInfoCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetHardwareInfoCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetHardwareInfoCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetHardwareInfoCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((!parameters) ||
		(parameters) &&
	   ((parameters -> paramCount == 0) ||
		(parameters -> paramCount == 1)))
	{
		WCHAR * ConNamespace =  L"ROOT\\CIMV2";
		
		DWORD wcHostNameLen = NAME_LEN;
		WCHAR wcHostName[NAME_LEN] = L"";
		GetComputerNameW(wcHostName, &wcHostNameLen);

		WCHAR pcConfig[STR_VALUE_LEN];

		// Build namespace for connection
		swprintf_s(pcConfig, STR_VALUE_LEN, L"\\\\%s\\%s", wcHostName, ConNamespace);

		HRESULT hres;
		IWbemServices * pSvc = NULL;
		hres = m_pLoc -> ConnectServer(
										 _bstr_t(pcConfig), // Object path of WMI namespace
										 NULL,                    // User name. NULL = current user
										 NULL,                    // User password. NULL = current
										 0,                       // Locale. NULL indicates current
										 WBEM_FLAG_CONNECT_USE_MAX_WAIT,                    // Security flags.
										 0,                       // Authority (for example, Kerberos)
										 0,                       // Context object 
										 &pSvc                    // pointer to IWbemServices proxy
									  );
		if (FAILED(hres)) 
		{
			return result;
		}

		hres = CoSetProxyBlanket(
								   pSvc,                        // Indicates the proxy to set
								   RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
								   RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
								   NULL,                        // Server principal name 
								   RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
								   RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
								   NULL,                        // client identity
								   EOAC_NONE                    // proxy capabilities 
								);
	
		if (FAILED(hres)) 
		{
			pSvc -> Release();
			return result;
		}
		
		result = serializationManager -> CreateCommandParameterList();
		
		IEnumWbemClassObject * pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_OperatingSystem");
		if (result) result -> paramList[result -> paramCount++] = GetStringData(pEnumerator, L"Caption");
		if (pEnumerator) pEnumerator -> Release();

		pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_Processor");
		if (result) result -> paramList[result -> paramCount++] = GetStringData(pEnumerator, L"Name");
		if (pEnumerator) pEnumerator -> Release();

		MEMORYSTATUSEX statex;
		ZeroMemory(&statex, sizeof (MEMORYSTATUSEX));
		statex.dwLength = sizeof (statex);
		GlobalMemoryStatusEx (&statex);

		if (result) result -> paramList[result -> paramCount++] = serializationManager -> PackLong(statex.ullTotalPhys/1024/1024, RETURN_CMD_DATA);
		if (result) result -> paramList[result -> paramCount++] = serializationManager -> PackLong((statex.ullTotalPhys - statex.ullAvailPhys)/1024/1024, RETURN_CMD_DATA);
		if (result) result -> paramList[result -> paramCount++] = serializationManager -> PackLong(statex.ullTotalVirtual/1024/1024, RETURN_CMD_DATA);
		if (result) result -> paramList[result -> paramCount++] = serializationManager -> PackLong((statex.ullTotalVirtual - statex.ullAvailVirtual)/1024/1024, RETURN_CMD_DATA);

		pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_BaseBoard");
		if (result) result -> paramList[result -> paramCount++] = GetStringData(pEnumerator, L"Manufacturer");
		if (pEnumerator) pEnumerator -> Release();

		pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_BaseBoard");
		if (result) result -> paramList[result -> paramCount++] = GetStringData(pEnumerator, L"Product");
		if (pEnumerator) pEnumerator -> Release();

		pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_BIOS");
		if (result) result -> paramList[result -> paramCount++] = GetStringData(pEnumerator, L"Manufacturer");
		if (pEnumerator) pEnumerator -> Release();

		pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_BIOS");
		if (result) result -> paramList[result -> paramCount++] = GetStringData(pEnumerator, L"SMBIOSBIOSVersion");
		if (pEnumerator) pEnumerator -> Release();

		pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_PnPEntity");
		if (result) result -> paramList[result -> paramCount++] = GetStringData(pEnumerator, L"Caption");
		if (pEnumerator) pEnumerator -> Release();

		pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_VideoController");
		if (result) result -> paramList[result -> paramCount++] = GetStringData(pEnumerator, L"Name");
		if (pEnumerator) pEnumerator -> Release();

		pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_DesktopMonitor");
		if (result) result -> paramList[result -> paramCount++] = GetStringData(pEnumerator, L"Name");
		if (pEnumerator) pEnumerator -> Release();

		pEnumerator = ExecuteWQL(pSvc, "SELECT * FROM Win32_VideoController");
		if (result) result -> paramList[result -> paramCount++] = GetUINTData(pEnumerator, L"AdapterRAM");
		if (pEnumerator) pEnumerator -> Release();

		pSvc -> Release();

		// Save command to history
		if ((parameters -> paramCount == 1) &&
			(parameters -> paramList[0]) &&
			(parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
			(parameters -> paramList[0] -> paramDataType == DWORD_DATA))
		{
			int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
			CommandHistoryManager * commandHistoryManager = new CommandHistoryManager(zHubCmdDllDefinition.dllID, logWriter);
			commandHistoryManager -> SaveCommand(CMD_GET_HARDWARE_INFO, userID, parameters, result);
			delete commandHistoryManager;
		}
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		else
			WriteToLog("GetHardwareInfoCommand : Execute. Wrong input parameters!");

		WriteToLog("GetHardwareInfoCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetHardwareInfoCommand

   Method : ExecuteWQL

   Parameters :
			Input : 
				pSvc - WMI server
				query - query text

	Return : WMI objects enumerator

	Description : Execte WMI query

*****************************************************************/
IEnumWbemClassObject * GetHardwareInfoCommand :: ExecuteWQL(IWbemServices * pSvc, char * query)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetHardwareInfoCommand : ExecuteWQL. Start");
	#endif

	// Execute query and get enumerator
	IEnumWbemClassObject * pEnumerator = NULL;
    HRESULT hres = pSvc -> ExecQuery(bstr_t("WQL"), bstr_t(query), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
	
	if (FAILED(hres)) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("GetHardwareInfoCommand : ExecuteWQL. Can't create enumerator!");
			WriteToLog("GetHardwareInfoCommand : ExecuteWQL. Done");
		#endif

		return NULL;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("GetHardwareInfoCommand : ExecuteWQL. Done");
		#endif

		return pEnumerator;
	}
}

/****************************************************************

   Class : GetHardwareInfoCommand

   Method : GetUINTData

   Parameters :
			Input : 
				pEnumerator - WMI enumerator
				wminame - looked object name

	Return : Command parameter structure

	Description : Get integer data

*****************************************************************/
PCOMMAND_PARAMETER GetHardwareInfoCommand :: GetUINTData(IEnumWbemClassObject * pEnumerator, WCHAR * wminame)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetHardwareInfoCommand : GetUINTData. Start");
	#endif

	// Check enumerator
	if (pEnumerator == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("GetHardwareInfoCommand : GetUINTData. Wrong enumerator");
			WriteToLog("GetHardwareInfoCommand : GetUINTData. Done");
		#endif

		return NULL;
	}

	// Get WMI object
	ULONG uReturn = 0;
   	IWbemClassObject * pclsObj;
    HRESULT hr = pEnumerator -> Next(WBEM_INFINITE, 1,  &pclsObj, &uReturn);
    
	if(uReturn == 0) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("GetHardwareInfoCommand : GetUINTData. No data");
			WriteToLog("GetHardwareInfoCommand : GetUINTData. Done");
		#endif

		return NULL;
	}
	
	// Get object value
	VARIANT vtProp;
	hr = pclsObj -> Get(wminame, 0, &vtProp, 0, 0);
	if (FAILED(hr) || vtProp.bstrVal == NULL)
	{
		VariantClear(&vtProp);
		pclsObj -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("GetHardwareInfoCommand : GetUINTData. Can't retreive value!");
			WriteToLog("GetHardwareInfoCommand : GetUINTData. Done");
		#endif

		return NULL;
	}

	// Pack long data
	PCOMMAND_PARAMETER param = serializationManager -> PackLong(vtProp.lVal/1024/1024, RETURN_CMD_DATA);
	
	VariantClear(&vtProp);
	pclsObj -> Release();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetHardwareInfoCommand : GetUINTData. Done");
	#endif

	return param;
}

/****************************************************************

   Class : GetHardwareInfoCommand

   Method : GetStringData

   Parameters :
			Input : 
				pEnumerator - WMI enumerator
				wminame - looked object name

	Return : Command parameter structure

	Description : Get string data

*****************************************************************/
PCOMMAND_PARAMETER GetHardwareInfoCommand :: GetStringData(IEnumWbemClassObject * pEnumerator, WCHAR * wminame)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetHardwareInfoCommand : GetStringData. Start");
	#endif

	// Check enumerator
	if (pEnumerator == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("GetHardwareInfoCommand : GetStringData. Wrong enumerator");
			WriteToLog("GetHardwareInfoCommand : GetStringData. Done");
		#endif

		return NULL;
	}

	// Get WMI object
	ULONG uReturn = 0;
   	IWbemClassObject * pclsObj;
    HRESULT hr = pEnumerator -> Next(WBEM_INFINITE, 1,  &pclsObj, &uReturn);
    if(uReturn == 0)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("GetHardwareInfoCommand : GetStringData. No data");
			WriteToLog("GetHardwareInfoCommand : GetStringData. Done");
		#endif

		return NULL;
	}
	
	// Get object value
	VARIANT vtProp;
	hr = pclsObj -> Get(wminame, 0, &vtProp, 0, 0);
	if (FAILED(hr) || vtProp.bstrVal == NULL)
	{
		VariantClear(&vtProp);
		pclsObj -> Release();

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("GetHardwareInfoCommand : GetStringData. Can't retreive value!");
			WriteToLog("GetHardwareInfoCommand : GetStringData. Done");
		#endif

		return NULL;
	}
	// Pack string data
	PCOMMAND_PARAMETER param = serializationManager -> PackString(_com_util::ConvertBSTRToString(vtProp.bstrVal), RETURN_CMD_DATA);

	VariantClear(&vtProp);
	pclsObj -> Release();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("GetHardwareInfoCommand : GetStringData. Done");
	#endif

	return param;
}