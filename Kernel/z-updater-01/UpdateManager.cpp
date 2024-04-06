/****************************************************************

   Solution : NovaTend

   Project : z-updater-01.exe

   Module : UpdateManager.cpp

   Description :  this module implements methods of
				  class UpdateManager

*****************************************************************/

#include "stdafx.h"

#include "UpdateManager.h"
#include <SettingsManager.h>
#include <SerializationManager.h>
#include <Wtsapi32.h>


// z-updater-01.exe definition structure
extern DLL_COMMON_DEFINITION zUpdateServiceDefinition;

/****************************************************************

   Class : UpdateManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - dll user ID
				logWriter - pointer to LOG-writer instance
								
*****************************************************************/
UpdateManager :: UpdateManager(unsigned long dllUserID, FileProcessor * fileProcessor, LogWriter * logWriter) : ThreadController(dllUserID, &zUpdateServiceDefinition, INFINITE)
{
	this -> logWriter = logWriter;
	this -> fileProcessor = fileProcessor;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : constructor");
	#endif
}

/****************************************************************

   Class : UpdateManager

   Method : Destructor
   
*****************************************************************/
UpdateManager :: ~UpdateManager(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : destructor");
	#endif
}

/****************************************************************

   Class : UpdateManager

   Method : CheckPeriodicFlag

   Returns : TRUE - if success

   Description : Check periodic flag
                 
*****************************************************************/
bool UpdateManager :: CheckPeriodicFlag(void)
{
	SettingsManager * settingsManager = new SettingsManager(zUpdateServiceDefinition.dllID);

	if (settingsManager -> GetUpdatePeriodicFlag(&periodicallyFlag) != ERROR_SUCCESS)
		periodicallyFlag = false;

	delete settingsManager;

	return periodicallyFlag;
}

/****************************************************************

   Class : UpdateManager

   Method : CheckPeriod

   Returns : TRUE - if success

   Description : Check historian period
                 
*****************************************************************/
bool UpdateManager :: CheckPeriod(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : CheckPeriod. Start");
	#endif

	SettingsManager * settingsManager = new SettingsManager(zUpdateServiceDefinition.dllID);

	if (settingsManager -> GetUpdatePeriod(&periodValue) == ERROR_SUCCESS)
	{
		// Get current time
		time_t nowSeconds;
		time(&nowSeconds);

		// Subtract dates
		double resSeconds = difftime(nowSeconds, prevTimeSeconds);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
			char message[STR_VALUE_LEN];
			sprintf(message, "UpdateManager : CheckPeriod. Period: %d. Seconds: %d", periodValue, (int)resSeconds);
			WriteToLog(message);
		#endif
					
		// Prepare result
		bool result = false;

		if (resSeconds > periodValue * 60 * 60)
		{
			// Save current time
			prevTimeSeconds = nowSeconds;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
				WriteToLog("UpdateManager : CheckPeriod. Period expired!");
			#endif

			result = true;
		}

		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
			WriteToLog("UpdateManager : CheckPeriod. Done");
		#endif

		return result;
	}
	else
	{
		delete settingsManager;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
			WriteToLog("UpdateManager : CheckPeriod. Can't get period!");
			WriteToLog("UpdateManager : CheckPeriod. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : UpdateManager

   Method : ControllerEntry

   Description : Write to history

*****************************************************************/
void UpdateManager :: ControllerEntry(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : ControllerEntry. Start");
	#endif

	SettingsManager * settingsManager = new SettingsManager(zUpdateServiceDefinition.dllID);

	// Get list of files which need to update
	PFOLDER_INFO_CONTAINER pLocalFileList = settingsManager -> GetUpdateFileList();

	// Check result
	if (pLocalFileList)
	{
		// Get list of files that available to download
		PFOLDER_INFO_CONTAINER pRemoteFileList = GetFileList();

		// Check result
		if (pRemoteFileList)
		{
			// Select only new files
			SelectNewFiles(pLocalFileList, pRemoteFileList);
			pRemoteFileList = DeleteFileList(pRemoteFileList);

			// Get update directory
			char updateDir[MAX_PATH]= "";
			settingsManager -> GetUpdateDirectory(updateDir);

			// Download files
			if (DownloadFiles(pLocalFileList, updateDir))
			{
				WriteToLog("Update manager  --> Downloading of files successfully finished!");
				
				// Set updates installation flag
				settingsManager ->  SetUpdateInstalledFlag(false);

				// Get path of user updater
				char updaterPath[MAX_PATH] = "";
				settingsManager -> GetUserUpdaterPath(updaterPath);

				// Set files list
				settingsManager -> SetUpdateFileList(pLocalFileList);

				// Start user updater
				if (StartUserUpdater(updaterPath))
				{
					WriteToLog("Update manager  --> User GUI updater has runed!");
				}
			}
			else
				WriteToLog("Update manager  --> The new NovaTend system files were not loaded!");

			pLocalFileList = DeleteFileList(pLocalFileList);
		}
	}
	
	delete settingsManager;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : ControllerEntry. Done");
	#endif
}

/****************************************************************

   Class : UpdateManager

   Method : StartUserUpdater

   Parameters :
			Input :
				updaterPath - path to updater file

   Returns : TRUE - if success

   Description : Start user updater module

*****************************************************************/
bool UpdateManager :: StartUserUpdater(char * updaterPath)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : StartUserUpdater. Start");
	#endif

	if (updaterPath)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		
		ZeroMemory(&pi, sizeof(pi));
		HANDLE hSystemUserToken;
		HANDLE hUserToken;
		
		WCHAR wPostLoginPath[MAX_PATH];
		mbstowcs(wPostLoginPath, updaterPath, MAX_PATH);
		
		// Get current session ID
		DWORD sessionID = WTSGetActiveConsoleSessionId();

		// Open current process token
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID|TOKEN_READ|TOKEN_WRITE, &hSystemUserToken))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
				WriteToLog("UpdateManager : StartUserUpdater. Can't get current process token!");
				WriteToLog("UpdateManager : StartUserUpdater. Done");
			#endif

			return false;
		}

		// Duplicate process token
		if (!DuplicateTokenEx(hSystemUserToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hUserToken))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
				WriteToLog("UpdateManager : StartUserUpdater. Can't duplicate process token!");
				WriteToLog("UpdateManager : StartUserUpdater. Done");
			#endif

			return false;
		}

		// Set token information
		if (!SetTokenInformation(hUserToken, TokenSessionId, (void*)&sessionID, sizeof(sessionID)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
				WriteToLog("UpdateManager : StartUserUpdater. Can't set token information!");
				WriteToLog("UpdateManager : StartUserUpdater. Done");
			#endif

			CloseHandle(hUserToken);
			return false;
		}

		// Run updater process
		if (!CreateProcessAsUser(hUserToken, wPostLoginPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
				WriteToLog("UpdateManager : StartUserUpdater. Can't start user uploader!");
				WriteToLog("UpdateManager : StartUserUpdater. Done");
			#endif

			CloseHandle(hUserToken);
			return false;
		}

		/*if ((WTSQueryUserToken(WTSGetActiveConsoleSessionId(), &hUserToken)) &&
			(!CreateProcessAsUser(hUserToken, wPostLoginPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("UpdateManager : StartUserUpdater. Can't start user uploader!");
				WriteToLog("PostLoginManager : StartUserUpdater. Done");
			#endif

			return false;
		}*/

		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		CloseHandle(hUserToken);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
			WriteToLog("UpdateManager : StartUserUpdater. Done");
		#endif

		return true;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
			WriteToLog("UpdateManager : StartUserUpdater. Wrong input data");
			WriteToLog("UpdateManager : StartUserUpdater. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : UpdateManager

   Method : GetFileList

   Returns : pointer to folder descriptor

   Description : Get file list

*****************************************************************/
PFOLDER_INFO_CONTAINER UpdateManager :: GetFileList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : GetFileList. Start");
	#endif

	PFOLDER_INFO_CONTAINER pFolder = NULL;

	if (fileProcessor)
	{
		unsigned long long taskID = fileProcessor -> GetFileList("");
		
		int status = TAKS_STATE_INPROGRESS;
		do
		{
			pFolder = fileProcessor -> CheckGetFileListResult(taskID, &status);
		} while ((status == TAKS_STATE_INPROGRESS) || (status == ERROR_TAKS_NOT_FOUND));
			
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		else
			WriteToLog("UpdateManager : GetFileList. Wrong file processor inctance!");
		
		WriteToLog("UpdateManager : GetFileList. Done");
	#endif

	return pFolder;
}

/****************************************************************

   Class : UpdateManager

   Method : SelectNewFiles

   Parameters :
			pFolder - pointer to files list
			pRemoteFileList - list of files available to download

   Returns : TRUE - if all files downloaded successfully

   Description : Download files

*****************************************************************/
bool UpdateManager :: DownloadFiles(PFOLDER_INFO_CONTAINER pFolder, char * downloadDir)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : DownloadFiles. Start");
	#endif

	bool result = false;

	// Check input data
	if ((pFolder) && (pFolder -> filesCount > 0) && (downloadDir) && (fileProcessor))
	{
		// List of task ID
		unsigned long long taskIDs[MAX_DIR_FILES_COUNT];
		bool taskFinished[MAX_DIR_FILES_COUNT];	

		// Set all files to download
		for(int i = 0; i < pFolder -> filesCount; i++)
		{
			// Get name of local file
			char fileName[NAME_LEN] = "";
			FileProcessorTask :: GetFileName(pFolder -> filesList[i] -> fileName, fileName);
			taskIDs[i] = fileProcessor -> DownloadFile(fileName, downloadDir);
			taskFinished[i] = false;
		}
				
		// Set result;
		result = true;

		// Finishing flag
		bool downloadFinished = false;
		
		// Wait all tasks
		do
		{
			// Set finish flag
			downloadFinished = true;

			// Check all tasks
			for(int i = 0; i < pFolder -> filesCount; i++)
			{
				if (!taskFinished[i])
				{
					// Check task result
					int status = TAKS_STATE_INPROGRESS;
					bool downloadResult = fileProcessor -> CheckDownloadFileResult(taskIDs[i], &status);

					// Check finish
					if ((status == TAKS_STATE_INPROGRESS) || (status == ERROR_TAKS_NOT_FOUND))
						downloadFinished = false;
					else
						taskFinished[i] = true;

					// Check downloading result
					if ((!downloadResult) && (status != TAKS_STATE_INPROGRESS) && (status != ERROR_TAKS_NOT_FOUND))
					{
						// Save message to log
						char fileName[NAME_LEN] = "";
						FileProcessorTask :: GetFileName(pFolder -> filesList[i] -> fileName, fileName);
						char message[STR_VALUE_LEN] = "";
						sprintf(message, "Update manager --> Error of file [%s] downloading!", fileName);
						WriteToLog(message);

						// Set result
						result = false;
					}
				}
		
			}
		} 
		while(!downloadFinished);

	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		else
			WriteToLog("UpdateManager : DownloadFiles. Wrong input data!");

		WriteToLog("UpdateManager : DownloadFiles. Done");
	#endif

	return result;
}

/****************************************************************

   Class : UpdateManager

   Method : SelectNewFiles

   Parameters :
			pLocalFileList - list of filles need to download
			pRemoteFileList - list of files available to download

   Returns : pointer to folder descriptor

   Description : Select only new files in list

*****************************************************************/
PFOLDER_INFO_CONTAINER UpdateManager :: SelectNewFiles(PFOLDER_INFO_CONTAINER pLocalFileList, PFOLDER_INFO_CONTAINER pRemoteFileList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : SelectNewFiles. Start");
	#endif

	// Check input data
	if ((pLocalFileList) && (pRemoteFileList))
	{
		for (int i = pLocalFileList -> filesCount - 1; i >= 0 ; i--)
		{
			// Get local file descriptor pointer
			PFILE_INFO_CONTAINER pLocalFile = pLocalFileList -> filesList[i];
			
			bool fileFound = false;

			PFILE_INFO_CONTAINER pRemoteFile = NULL;
			for(int j = 0; j < pRemoteFileList -> filesCount; j++)
			{
				// Get remote file descriptor pointer
				pRemoteFile = pRemoteFileList -> filesList[j];

				// Get name of local file
				char fileName[NAME_LEN] = "";
				FileProcessorTask :: GetFileName(pLocalFile -> fileName, fileName);
				
				// Compare files
				if ((strcmp(fileName, pRemoteFile -> fileName) == 0) && (CompareFiles(pLocalFile, pRemoteFile)))
				{
					fileFound = true;
					memcpy(&(pLocalFile -> updateTime), &(pRemoteFile -> updateTime), sizeof(tm));
					break;
				}
			}

			// Compare files
			if (!fileFound)
			{
				DeleteFileFromList(pLocalFileList, i);
			}
		}
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		else
			WriteToLog("UpdateManager : SelectNewFiles. Wrong input data!");

		WriteToLog("UpdateManager : SelectNewFiles. Done");
	#endif

	return pLocalFileList;
}

/****************************************************************

   Class : UpdateManager

   Method : CompareFiles

   Parameters :
			pFirstFile - descriptor of first file
			pSecondFile - descriptor of second file

   Returns : TRUE - if the second file is more new

   Description : Compare files

*****************************************************************/
bool UpdateManager :: CompareFiles(PFILE_INFO_CONTAINER pFirstFile, PFILE_INFO_CONTAINER pSecondFile)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : CompareFiles. Start");
	#endif

	bool result = false;

	// Check input data
	if ((pFirstFile) && (pSecondFile))
	{
		// Get time values
		time_t firstTime = mktime(&(pFirstFile -> updateTime));
		time_t secondTime = mktime(&(pSecondFile -> updateTime));

		// subtract time
		if (difftime(secondTime, firstTime) > 0)
			result = true;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		if (result)
			WriteToLog("UpdateManager : CompareFiles. New file!");
		else
			WriteToLog("UpdateManager : CompareFiles. Not new file!");

		WriteToLog("UpdateManager : CompareFiles. Done");
	#endif

	return result;
}

/****************************************************************

   Class : UpdateManager

   Method : DeleteFileList

   Parameters :
			pFolder - pointer to folder descriptor
			
   Returns : pointer to folder descriptor

   Description : delete file list

*****************************************************************/
PFOLDER_INFO_CONTAINER UpdateManager :: DeleteFileList(PFOLDER_INFO_CONTAINER pFolder)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : DeleteFileList");
	#endif

	if (pFolder)
	{
		for (int i = 0; i < pFolder -> filesCount; i++)
			if (pFolder -> filesList[i])
				free(pFolder -> filesList[i]);
		
		free(pFolder);
		pFolder = NULL;
	}

	return pFolder;
}

/****************************************************************

   Class : UpdateManager

   Method : CompareFiles

   Parameters :
			pFirstFile - descriptor of first file
			pSecondFile - descriptor of second file

   Returns : TRUE - if the second file is more new

   Description : Compare files

*****************************************************************/
PFOLDER_INFO_CONTAINER UpdateManager :: DeleteFileFromList(PFOLDER_INFO_CONTAINER pFolder, int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_UPDATER)
		WriteToLog("UpdateManager : DeleteFileFromList");
	#endif
	
	if ((pFolder) && (index >= 0) && (index < pFolder -> filesCount))
	{
		free(pFolder -> filesList[index]);
		pFolder -> filesList[index] = NULL;
		
		for(int i = index; i < pFolder -> filesCount - 1; i++)
		   pFolder -> filesList[i] = pFolder -> filesList[i + 1];
		
		pFolder -> filesList[pFolder -> filesCount - 1] = NULL;
		pFolder -> filesCount--;
	}

	return pFolder;
}

/****************************************************************

   Class : UpdateManager

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int UpdateManager :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}