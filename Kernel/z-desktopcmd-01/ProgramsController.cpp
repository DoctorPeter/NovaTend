/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : ProgramsController.cpp

   Description :  this module implements methods of
				  class ProgramsController

*****************************************************************/

#include "stdafx.h"
#include <tlhelp32.h>
#include <Psapi.h>

#include "ProgramsController.h"
#include <SerializationManager.h>
#include <SettingsManager.h>

// z-desktopcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zDesktopCmdDllDefinition;

/****************************************************************

   Class : ProgramsController

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - dll user ID
				logWriter - pointer to LOG-writer instance
								
*****************************************************************/
ProgramsController :: ProgramsController(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * ipcClientsManager, int senderID, int recipientID) : ThreadController(dllUserID, &zDesktopCmdDllDefinition, INFINITE)
{
	this -> logWriter = logWriter;
	this -> ipcClientsManager = ipcClientsManager;
	this -> senderID = senderID;
	this -> recipientID = recipientID;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : constructor");
	#endif
}

/****************************************************************

   Class : ProgramsController

   Method : Destructor
   
*****************************************************************/
ProgramsController :: ~ProgramsController(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : destructor");
	#endif
}

/****************************************************************

   Function : IsAppWindow

   Parameters :
			Output : 
				hWnd - window handler

	Return : TRUE - if this window is desktop application

	Description : Check for application window

*****************************************************************/
extern bool IsAppWindow(HWND hWnd);
//bool IsAppWindow(HWND hWnd)
//{
//	if (!IsWindow(hWnd))
//		return false;
//	
//	DWORD dwStyleEx = GetWindowLong(hWnd, GWL_EXSTYLE);
//
//	return (IsWindow(hWnd) && IsWindowVisible(hWnd) && (!GetWindow(hWnd, GW_OWNER)) && (!(dwStyleEx & WS_EX_NOACTIVATE)) && (!(dwStyleEx & WS_EX_TOOLWINDOW)));
//}

/****************************************************************

   Function : GetProcessName

   Parameters :
			Input : 
				processID - process ID
			Output:
				szProcessName - process name

	Return : TRUE - if success

	Description : Get process name by PID

*****************************************************************/
BOOL GetProcessName(DWORD processID, WCHAR* szProcessName)
{
     BOOL bRC = FALSE;
 
    // Get a handle to the process.
     HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
 
    // Get the process name.
     if (NULL != hProcess)
    {
        HMODULE hMod;
        DWORD cbNeeded;
 
        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessName, MAX_PATH);
            bRC = TRUE;
        }
    }
  
	CloseHandle(hProcess);
    return bRC;
}

/****************************************************************

   Function : GetWindowProcess

   Parameters :
			Input : 
				hWnd - window handler
			Output:
				processName - process name

	Return : process ID

	Description : Get window process ID

*****************************************************************/
DWORD GetWindowProcess(HWND hWnd, char * processName)
{
	DWORD pid = 0;
	GetWindowThreadProcessId(hWnd, &pid);
	WCHAR szProcessName[NAME_LEN] = L"";

	GetProcessName(pid, szProcessName);
	wcstombs(processName, szProcessName, NAME_LEN);

	return pid;
}

/****************************************************************

   Function : TerminateProgram

   Parameters :
			Input : 
				dwProcessId - process ID
				uExitCode - exit code

	Return : TRUE - if success

	Description : Terminate process

*****************************************************************/
BOOL TerminateProgram(DWORD dwProcessId, UINT uExitCode)
{
    DWORD dwDesiredAccess = PROCESS_TERMINATE;
    BOOL  bInheritHandle  = FALSE;
    HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
    if (hProcess == NULL)
        return FALSE;

    BOOL result = TerminateProcess(hProcess, uExitCode);

    CloseHandle(hProcess);

    return result;
}

/****************************************************************

   Function : EnumWindowsAppProc

   Parameters :
			Output : 
				hWnd - window handler
				lParam - param pointer

	Return : TRUE - if success

	Description : Windows enumeration callback function

*****************************************************************/
BOOL CALLBACK EnumWindowsAppProc(HWND hWnd, LPARAM lParam)
{
	// Check HWND
	if (IsAppWindow(hWnd))
	{
		PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgListContainer = (PCONTROL_PROGRAM_INFO_CONTAINER_LIST)lParam;

		// Check parameter
		if (prgListContainer)
		{
			int index = prgListContainer -> programListSize;

			// Create new progam info container
			prgListContainer -> programList[index] = (PCONTROL_PROGRAM_INFO_CONTAINER)malloc(sizeof(CONTROL_PROGRAM_INFO_CONTAINER));

			if (prgListContainer -> programList[index])
			{
				PCONTROL_PROGRAM_INFO_CONTAINER prgContainer = prgListContainer -> programList[index];

				prgContainer -> allowed = true;
				prgContainer -> pid = GetWindowProcess(hWnd, prgContainer -> moduleName);
				GetWindowTextA(hWnd, prgContainer -> programName, NAME_LEN);
				
				prgListContainer -> programListSize++;
			}
		}
	}

	return TRUE;
}

/****************************************************************

   Class : ProgramsController

   Method : GetProgramList

   Returns : Program list container

   Description : Get program list
                 
*****************************************************************/
PCONTROL_PROGRAM_INFO_CONTAINER_LIST ProgramsController :: GetProgramList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : GetProgramList. Start");
	#endif
	
	PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgListContainer = (PCONTROL_PROGRAM_INFO_CONTAINER_LIST)malloc(sizeof(CONTROL_PROGRAM_INFO_CONTAINER_LIST));

	// Check output buffer
	if (prgListContainer)
	{
		prgListContainer -> programListSize = 0;

		// Enum windows
		if (!EnumDesktopWindows(NULL, EnumWindowsAppProc, LPARAM(prgListContainer)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
				WriteToLog("ProgramsController : GetProgramList. Error of windows enumeration!");
				WriteToLog("ProgramsController : GetProgramList. Done");
			#endif

			return NULL;
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("ProgramsController : GetProgramList. Done");
		#endif

		return prgListContainer;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("ProgramsController : GetProgramList. Wrong output buffer!");
			WriteToLog("ProgramsController : GetProgramList. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : ProgramsController

   Method : SendCheckProgamsCommand

   Parameters:
			Input:
				prgListContainer - list of programs

   Returns : list of programs

   Description : Send check command
                 
*****************************************************************/
PCONTROL_PROGRAM_INFO_CONTAINER_LIST ProgramsController :: SendCheckProgamsCommand(PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgListContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : SendCheckProgamsCommand. Start");
	#endif

	// Result list container
	PCONTROL_PROGRAM_INFO_CONTAINER_LIST resultList = NULL;

	// Check input data
	if ((prgListContainer) &&
		(prgListContainer -> programListSize > 0))
	{
		// Create serialization manager
		SerializationManager * serializationManager = new SerializationManager(zDesktopCmdDllDefinition.dllID, logWriter);

		// Get recipient ID
		if (ipcClientsManager)
			recipientID = ipcClientsManager -> FindMostPriorityServer();

		// Create request structure
		PCOMMAND_REQUEST_RESPONSE pRequest = serializationManager -> CreateRequestResponse(CMD_CHECK_PROGRAMS, REQUEST_CMD, senderID, recipientID);

		if (pRequest)
		{
			pRequest -> parameters -> paramCount = 3;

			// Pack user ID
			pRequest -> parameters -> paramList[0] = serializationManager -> PackDWORD(userID, INPUT_CMD_DATA);

			char compName[NAME_LEN];
			DWORD compNameLen = NAME_LEN;
			GetComputerNameA(compName, &compNameLen);

			// Pack computer name
			pRequest -> parameters -> paramList[1] = serializationManager -> PackString(compName, INPUT_CMD_DATA);

			// Pack container
			pRequest -> parameters -> paramList[2] = serializationManager -> PackControlledProgramListContainer(prgListContainer, INPUT_CMD_DATA);
			
			// Send data and get response
			PCOMMAND_REQUEST_RESPONSE pResponse = ipcClientsManager -> SendData(recipientID, pRequest);
			pRequest = serializationManager -> DeleteRequestResponse(pRequest);

			// Check response
			if ((pResponse) &&
				(serializationManager -> CheckCommand(pResponse, CMD_CHECK_PROGRAMS) == SERIALIZE_DATA_SUCCESS) &&
				(pResponse -> parameters) &&
				(pResponse -> parameters -> paramCount == 1) &&
				(pResponse -> parameters -> paramList[0]) &&
				(pResponse -> parameters -> paramList[0] -> paramType == RETURN_CMD_DATA) &&
				(pResponse -> parameters -> paramList[0] -> paramDataType == CTRL_PRG_INFO_LIST_DATA))
			{
				// Get result program list container
				resultList = serializationManager -> UnpackControlledProgramListContainer(pResponse -> parameters -> paramList[0]);
				pResponse = serializationManager -> DeleteRequestResponse(pResponse);
			}
		}

		// Delete serialization manager
		delete serializationManager;
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : SendCheckProgamsCommand. Done");
	#endif

	return resultList;
}

/****************************************************************

   Class : ProgramsController

   Method : TerminatePrograms

   Parameters:
			Input:
				prgListContainer - list of programs

   Description : Terminate programs
                 
*****************************************************************/
void ProgramsController ::  TerminatePrograms(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : TerminatePrograms. Start");
	#endif

	if (programList)
	{
		for (int i = 0; i < programList -> programListSize; i++)
		{
			if ((programList -> programList[i]) && (!((programList -> programList[i] -> allowed))))
			{
				char mes[STR_VALUE_LEN * 4] = "";
				sprintf(mes, "ProgramsController : TerminatePrograms --> Program name: %s. Module name: %s. PID : %d", programList -> programList[i] -> programName, programList -> programList[i] -> moduleName, programList -> programList[i] -> pid);
				WriteToLog(mes);

				TerminateProgram(programList -> programList[i] -> pid, 0);
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : TerminatePrograms. Done");
	#endif
}

/****************************************************************

   Class : ProgramsController

   Method : CheckPeriodicFlag

   Returns : TRUE - if have to check

   Description : Check program control flag

*****************************************************************/
bool ProgramsController :: CheckPeriodicFlag(void)
{
	SettingsManager * settingsManager = new SettingsManager(zDesktopCmdDllDefinition.dllID);

	bool flag = false;
	if (settingsManager -> GetProgramControllFlag(&flag) != ERROR_SUCCESS)
		return false;
		
	if (settingsManager -> GetLoggedUserID(&userID) != ERROR_SUCCESS)
		return false;

	delete settingsManager;

	return ((flag) && (userID != -1));
}

/****************************************************************

   Class : ProgramsController

   Method : DeleteProgramInfoContainerList
   
   Parameters :
			Input : 
				programList - list of programs
	
   Description :  Delete program list

*****************************************************************/
PCONTROL_PROGRAM_INFO_CONTAINER_LIST ProgramsController :: DeleteProgramInfoContainerList(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : DeleteProgramInfoContainerList");
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

/****************************************************************

   Class : ProgramsController

   Method : ControllerEntry

   Description : Check programs and kill forbidden

*****************************************************************/
void ProgramsController :: ControllerEntry(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : ControllerEntry. Start");
	#endif

	// Get source program list
	PCONTROL_PROGRAM_INFO_CONTAINER_LIST srcProgramList = GetProgramList();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		if (srcProgramList)
		{
			for (int i = 0; i < srcProgramList -> programListSize; i++)
			{
				char mes[STR_VALUE_LEN * 4] = "";
				sprintf(mes, "ProgramsController : ProgramsControllerProcessor. Source lList. Program name: %s. Module name: %s. PID : %d. Allowed: %d", srcProgramList -> programList[i] -> programName, srcProgramList -> programList[i] -> moduleName, srcProgramList -> programList[i] -> pid, (int)(srcProgramList -> programList[i] -> allowed));
				WriteToLog(mes);
			}
		}
	#endif

	// Get processed program list
	PCONTROL_PROGRAM_INFO_CONTAINER_LIST resProgramList = SendCheckProgamsCommand(srcProgramList);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		if (resProgramList)
		{
			for (int i = 0; i < resProgramList -> programListSize; i++)
			{
				char mes[STR_VALUE_LEN * 4] = "";
				sprintf(mes, "ProgramsController : ProgramsControllerProcessor. Processed list. Program name: %s. Module name: %s. PID : %d. Allowed: %d", resProgramList -> programList[i] -> programName, resProgramList -> programList[i] -> moduleName, resProgramList -> programList[i] -> pid, (int)(resProgramList -> programList[i] -> allowed));
				WriteToLog(mes);
			}
		}
	#endif

	// Terminate not allowed programs
	TerminatePrograms(resProgramList);

	// Deelete lists
	srcProgramList = DeleteProgramInfoContainerList(srcProgramList);
	resProgramList = DeleteProgramInfoContainerList(resProgramList);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("ProgramsController : ControllerEntry. Done");
	#endif
}

/****************************************************************

   Class : ProgramsController

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int ProgramsController :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}