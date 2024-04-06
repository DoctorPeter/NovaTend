/****************************************************************

   Solution : NovaTend

   Project : z-authclient-01.dll

   Module : FileProcessor.cpp

   Description : this module implements methods of
				  class FileProcessor

*****************************************************************/

#include "stdafx.h"
#include "FileProcessor.h"


// z-authclient-01.dll definition structure
extern DLL_COMMON_DEFINITION zAuthClientDllDefinition;

#pragma region File processor task

/****************************************************************

		Methods of class FileProcessorTask

*****************************************************************/

/****************************************************************

   Class : FileProcessorTask

   Method : Constructor

   Parameters :
			Input : 
				authManager - authenticate manager instance


*****************************************************************/
FileProcessorTask :: FileProcessorTask(int taskType, AuthenticateManager * authManager) : TaskDescriptor(taskType)
{
	this -> authManager = authManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessorTask : constructor");
	#endif
}

/****************************************************************

   Class : GetFileListTask

   Method : Destructor
   
*****************************************************************/
FileProcessorTask :: ~FileProcessorTask(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessorTask : destructor");
	#endif
}

/****************************************************************

   Class : FileProcessorTask

   Method : WriteToLog

   Parameters :
			Input : 
				filePath - file path
			Output :
				fileName - file name

	Return : file name

	Description : Get file name

*****************************************************************/
char * FileProcessorTask :: GetFileName(char * filePath, char * fileName)
{
	if ((filePath) && (fileName))
	{
		int pos = -1;

		for (int i = strlen(filePath) - 1; i >= 0; i--)
			if (filePath[i] == '\\')
			{
				pos = i;
				break;
			}

		if (pos >= 0)
			strcpy(fileName, filePath + pos + 1);
		else
			strcpy(fileName, filePath);
	}

	return fileName;
}

/****************************************************************

   Class : FileProcessorTask

   Method : DeleteFile

   Parameters :
			Input : 
				fileName - file name

	Return : TRUE - if success

	Description : delete file

*****************************************************************/
bool FileProcessorTask :: DeleteFile(char * fileName)
{
	return DeleteFileA(fileName);
}

/****************************************************************

   Class : FileProcessorTask

   Method : PreallocFile

   Parameters :
			Input : 
				fileName - file name
				distance - distance in bytes

	Return : TRUE - if success

	Description : Prealloc file

*****************************************************************/
bool FileProcessorTask :: PreallocFile(char * fileName, int distance)
{
	HANDLE hFile;
	DWORD  dwBytesRead, dwPos;

	// Open the PHYSICALDEVICE as a file. 
	hFile = CreateFileA(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	// Check result
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	// Move to distance
	dwPos = SetFilePointer(hFile, distance, NULL, FILE_BEGIN);

	// Mark end of file
	SetEndOfFile(hFile);

	// Check result
	if (dwPos == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);
	return true;
}

/****************************************************************

   Class : FileProcessorTask

   Method : AppendFile

   Parameters :
			Input : 
				fileName - file name
				blockNum - number of block
				blockSize - size of block
				data - pointer to block data
				curBlockSzie - size of current block

	Return : TRUE - if success

	Description : Prealloc file

*****************************************************************/
bool FileProcessorTask :: AppendFile(char * fileName, int blockNum, int blockSize, char * data, int curBlockSize)
{
	// Open file
	HANDLE hAppend;
	hAppend = CreateFileA(fileName, FILE_WRITE_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hAppend == INVALID_HANDLE_VALUE)
		return false;

	// Move file pointer
	DWORD dwPos = SetFilePointer(hAppend, blockNum * blockSize, NULL, FILE_BEGIN);
	if (dwPos == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		CloseHandle(hAppend);
		return false;
	}
	
	// Save block of data
	DWORD dwBytesWritten;
	LockFile(hAppend, dwPos, 0, curBlockSize, 0);
	WriteFile(hAppend, data, curBlockSize, &dwBytesWritten, NULL);
	UnlockFile(hAppend, dwPos, 0, curBlockSize, 0);
	CloseHandle(hAppend);

	return true;
}

/****************************************************************

   Class : FileProcessorTask

   Method : GetFileSize

   Parameters :
			Input : 
				fileName - file name
			Output:
				res - size of file in bytes

	Return : TRUE - if success

	Description : Get size of file

*****************************************************************/
bool FileProcessorTask :: GetFileSize(char * fileName, unsigned long long * res)
{
	// Open file
	HANDLE hFile = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{

		LARGE_INTEGER li = {0};

		// Get file size
		DWORD bSuccess = GetFileSizeEx(hFile, &li);

		// Close file
		CloseHandle(hFile);
		
		*res = li.QuadPart;
				
		// Check errors
		if ((bSuccess == INVALID_FILE_SIZE) && (GetLastError() != NO_ERROR))
			return false;
	}
	else
		return false;

	return true;
}

/****************************************************************

   Class : FileProcessorTask

   Method : GetFileBlock

   Parameters :
			Input : 
				fileName - file name
				skipBytes - number of bytes to skip
				curBlockSzie - size of current block
			Output :
				data - pointer to result data buffer
				out_dwReaded - count of readed bytes

	Return : TRUE - if success

	Description : Get block of the file. Return readed bytes in last parameter

*****************************************************************/
bool FileProcessorTask :: GetFileBlock(char * fileName, int skipBytes, char * data, int curBlockSize, int * out_dwReaded)
{
	// Open file
	HANDLE hRead;
	hRead = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hRead == INVALID_HANDLE_VALUE)
		return false;

	// Move file pointer
	DWORD dwPos = SetFilePointer(hRead, skipBytes, NULL, FILE_BEGIN);
	if (dwPos == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		CloseHandle(hRead);
		return false;
	}

	// Read data
	bool bRes = ReadFile(hRead, data, curBlockSize, (LPDWORD)out_dwReaded, NULL);
	CloseHandle(hRead);

	return bRes;
}

/****************************************************************

   Class : FileProcessorTask

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  FileProcessorTask :: WriteToLog(char * message)
{
	if (authManager)
		return authManager -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}

#pragma endregion

#pragma region Get file list

/****************************************************************

		Methods of class GetFileListTask

*****************************************************************/

/****************************************************************

   Class : GetFileListTask

   Method : Constructor

   Parameters :
			Input : 
				dirName - directory name


*****************************************************************/
GetFileListTask :: GetFileListTask(char * dirName, AuthenticateManager * authManager) : FileProcessorTask(GET_FILE_LIST_TASK, authManager)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("GetFileListTask : constructor");
	#endif

	if (dirName)
		strcpy(this -> dirName, dirName);
	else
		this -> dirName[0] = 0;

	this -> pFolder = NULL;
}

/****************************************************************

   Class : GetFileListTask

   Method : Destructor
   
*****************************************************************/
GetFileListTask :: ~GetFileListTask(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("GetFileListTask : destructor");
	#endif

	if (pFolder)
	{
		for (int i = 0; i < pFolder -> filesCount; i++)
			free(pFolder -> filesList[i]);
		free(pFolder);
	}
}

/****************************************************************

   Class : GetFileListTask

   Method : Execute

   Description : Execute task
    
*****************************************************************/
int GetFileListTask :: Execute(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("GetFileListTask : Execute. Start");
	#endif

	// Get directory description
	if (authManager)
		pFolder = authManager -> GetFileList(dirName);
	
	// Preapare function result
	if (pFolder)
	{
		SetTaskStatus(ERROR_TAKS_RESULT_OK);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
			WriteToLog("GetFileListTask : Execute. Success!");
		#endif
	}
	else
	{
		SetTaskStatus(ERROR_TAKS_RESULT_FAIL);
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
			WriteToLog("GetFileListTask : Execute. Fail!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("GetFileListTask : Execute. Done");
	#endif
		
	return GetTaskStatus();
}

/****************************************************************

   Class : GetFileListTask

   Method : GetFolderInfoContainer

   Returns : pointer to folder info container

   Description : Get folder decriptor
    
*****************************************************************/
PFOLDER_INFO_CONTAINER GetFileListTask :: GetFolderInfoContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("GetFileListTask : GetFolderInfoContainer. Start");
	#endif

	PFOLDER_INFO_CONTAINER result = NULL;

	// Copy folder info container
	if (pFolder)
	{
		result = (PFOLDER_INFO_CONTAINER)malloc(sizeof(FOLDER_INFO_CONTAINER));
		
		if (result)
		{
			strcpy(result -> dirName, pFolder -> dirName);
			result -> filesCount = pFolder -> filesCount;

			for(int i = 0; i < result -> filesCount; i++)
			{
				result -> filesList[i] = (PFILE_INFO_CONTAINER)malloc(sizeof(FILE_INFO_CONTAINER));

				if ((result -> filesList[i]) && (pFolder -> filesList[i]))
					memcpy(result -> filesList[i], pFolder -> filesList[i], sizeof(FILE_INFO_CONTAINER));
			}
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("GetFileListTask : GetFolderInfoContainer. Done");
	#endif

	return result;
}

#pragma endregion

#pragma region Download file

/****************************************************************

		Methods of class DownloadFileTask

*****************************************************************/

/****************************************************************

   Class : DownloadFileTask

   Method : Constructor

   Parameters :
			Input : 
				fileName - directory name
				downloadDir - default download directory
				authManager - authentic manager instance


*****************************************************************/
DownloadFileTask :: DownloadFileTask(char * fileName, char * downloadDir,  AuthenticateManager * authManager) : FileProcessorTask(DOWNLOAD_FILE_TASK, authManager)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("DownloadFileTask : constructor");
	#endif

	if (fileName)
		strcpy(this -> fileName, fileName);
	else
		this -> fileName[0] = 0;

	if (downloadDir)
		strcpy(this -> downloadDir, downloadDir);
	else
		this -> downloadDir[0] = 0;


	fileSize = 0;
	blockNumber = 0;
	blockSize = 1048576;
	blockCount = 0;
	pFileBlock = NULL;
}

/****************************************************************

   Class : DownloadFileTask

   Method : Destructor
   
*****************************************************************/
DownloadFileTask :: ~DownloadFileTask(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("DownloadFileTask : destructor");
	#endif

	if (pFileBlock)
	{
		free(pFileBlock);
	}
}

/****************************************************************

   Class : DownloadFileTask

   Method : Execute

   Description : Execute task
    
*****************************************************************/
int DownloadFileTask :: Execute(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("DownloadFileTask : Execute. Start");
	#endif

	// Check auth manager
	if (authManager)
	{
		// First time
		if (blockNumber == 0)
		{
			// Get file name
			GetFileName(fileName, savedFileName);
			
			// Prepare full name of save file
			char tmpFileName[MAX_PATH];
			strcpy(tmpFileName, downloadDir);
			strcat(tmpFileName, "\\");
			strcat(tmpFileName, savedFileName);
			strcpy(savedFileName, tmpFileName);

			// Delete previous file
			DeleteFile(savedFileName);
		}
		
		// Get info about downloaded file
		fileSize = authManager -> DownloadFile(fileName);
		
		// Check result
		if (fileSize == 0)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
				WriteToLog("DownloadFileTask : Execute. Can't get file size!");
			#endif

			SetTaskStatus(ERROR_TAKS_RESULT_FAIL);
		}
		else
		{
			// Calculate count of blocks
			blockCount = fileSize / blockSize;
			if (fileSize % blockSize) blockCount++;

			// Delete previous file block
			if (pFileBlock) 
			{
				free(pFileBlock);
				pFileBlock = NULL;
			}

			// Download file block
			int currentBlockSize = blockSize;
			pFileBlock = authManager -> DownloadBlockFile(fileName, blockNumber, &currentBlockSize);

			// Check result
			if (pFileBlock == NULL)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
					WriteToLog("DownloadFileTask : Execute. Can't download block of file!");
				#endif

				SetTaskStatus(ERROR_TAKS_RESULT_FAIL);
			}
			else
			{
				if (blockNumber == 0)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
						WriteToLog("DownloadFileTask : Execute. Prealloc file!");
					#endif

					if (!PreallocFile(savedFileName, fileSize))
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
							WriteToLog("DownloadFileTask : Execute. Error of file preallocation!");
						#endif

						SetTaskStatus(ERROR_TAKS_RESULT_FAIL);
					}
				}

				// Save block of file
				if (!AppendFile(savedFileName, blockNumber, blockSize, pFileBlock, currentBlockSize))
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
						WriteToLog("DownloadFileTask : Execute. Error of file block saving!");
					#endif

					SetTaskStatus(ERROR_TAKS_RESULT_FAIL);
				}
				else
				{
					// Check count of blocks
					blockNumber++;
					if (blockNumber == blockCount)
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
							WriteToLog("DownloadFileTask : Execute. All file content successfully downloaded!");
						#endif

						SetTaskStatus(ERROR_TAKS_RESULT_OK);
					}
					else
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
							WriteToLog("DownloadFileTask : Execute. Downloading is not finished yet!");
						#endif

						SetTaskStatus(TAKS_STATE_INPROGRESS);
					}
				}
			}
		}
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		else
			WriteToLog("DownloadFileTask : Execute. Wrong authenticate manager instance!");

		WriteToLog("DownloadFileTask : Execute. Done");
	#endif
		
	return GetTaskStatus();
}

#pragma endregion

#pragma region Upload file

/****************************************************************

		Methods of class UploadFileTask

*****************************************************************/

/****************************************************************

   Class : UploadFileTask

   Method : Constructor

   Parameters :
			Input : 
				fileName - directory name
				downloadDir - default download directory
				authManager - authentic manager instance


*****************************************************************/
UploadFileTask :: UploadFileTask(char * fileName, AuthenticateManager * authManager) : FileProcessorTask(UPLOAD_FILE_TASK, authManager)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("UploadFileTask : constructor");
	#endif

	if (fileName)
		strcpy(this -> fileName, fileName);
	else
		this -> fileName[0] = 0;

	fileSize = 0;
	blockNumber = 0;
	blockSize = 1048576;
	blockCount = 0;
	pFileBlock = NULL;
}

/****************************************************************

   Class : UploadFileTask

   Method : Destructor
   
*****************************************************************/
UploadFileTask :: ~UploadFileTask(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("UploadFileTask : destructor");
	#endif

	if (pFileBlock)
	{
		free(pFileBlock);
	}
}

/****************************************************************

   Class : UploadFileTask

   Method : Execute

   Description : Execute task
    
*****************************************************************/
int UploadFileTask :: Execute(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("UploadFileTask : Execute. Start");
	#endif

	// Check auth manager
	if (authManager)
	{
		if (!GetFileSize(fileName, &fileSize))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
				WriteToLog("UploadFileTask : Execute. Can't get file size!");
			#endif

			SetTaskStatus(ERROR_TAKS_RESULT_FAIL);
		}
		else
		{
			// Get file name
			GetFileName(fileName, uploadedFileName);

			// First time
			if (blockNumber == 0)
			{
				// Make first request for uploading
				if (!(authManager -> UploadFile(uploadedFileName, fileSize)))
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
						WriteToLog("UploadFileTask : Execute. Can't make first request for uploading!");
						WriteToLog("UploadFileTask : Execute. Done");
					#endif

					SetTaskStatus(ERROR_TAKS_RESULT_FAIL);
					return ERROR_TAKS_RESULT_FAIL;
				}
			}

			// Calculate count of blocks
			blockCount = fileSize / blockSize;
			if (fileSize % blockSize) blockCount++;

			// Delete previous file block
			if (pFileBlock) 
			{
				free(pFileBlock);
				pFileBlock = NULL;
			}

			// Allocate memory for block
			pFileBlock = (char *)malloc(blockSize);

			// Read block of file
			int readedBytes = 0;
			if (!GetFileBlock(fileName, blockNumber * blockSize, pFileBlock, blockSize, &readedBytes))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
					WriteToLog("UploadFileTask : Execute. Can't get block of file!");
				#endif

				SetTaskStatus(ERROR_TAKS_RESULT_FAIL);
			}
			else
				// Upload block of file
				if (!(authManager -> UploadBlockFile(uploadedFileName, blockNumber, readedBytes, pFileBlock)))
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
						WriteToLog("UploadFileTask : Execute. Can't upload block of file!");
					#endif

					SetTaskStatus(ERROR_TAKS_RESULT_FAIL);
				}
				else
				{
					// Check count of blocks
					blockNumber++;
					if (blockNumber == blockCount)
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
							WriteToLog("UploadFileTask : Execute. All file content successfully uploaded!");
						#endif

						SetTaskStatus(ERROR_TAKS_RESULT_OK);
					}
					else
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
							WriteToLog("UploadFileTask : Execute. Uploading is not finished yet!");
						#endif

						SetTaskStatus(TAKS_STATE_INPROGRESS);
					}
				}
		}
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		else
			WriteToLog("UploadFileTask : Execute. Wrong authenticate manager instance!");

		WriteToLog("UploadFileTask : Execute. Done");
	#endif
		
	return GetTaskStatus();
}

#pragma endregion

#pragma region File processor

/****************************************************************

   Class : FileProcessor

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				authManager - authenticate manager instance


*****************************************************************/
FileProcessor :: FileProcessor(unsigned long dllUserID, AuthenticateManager * authManager) : BackgroundTaskManager(dllUserID, &zAuthClientDllDefinition)
{
	this -> authManager = authManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : constructor");
	#endif
}

/****************************************************************

   Class : FileProcessor

   Method : Destructor

*****************************************************************/
FileProcessor :: ~FileProcessor(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : Destructor");
	#endif
}

/****************************************************************

   Class : FileProcessor

   Method : GetFileList

   Parameters :
			Input : 
				dirName - folder name


   Returns : task ID

   Description : Put get file list task to queue
   
*****************************************************************/
unsigned long long FileProcessor :: GetFileList(char * dirName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : GetFileList. Start");
	#endif

	// Create task
	GetFileListTask * pTask = new GetFileListTask(dirName, authManager);

	// Add task to queue
	unsigned long long taskID = PushTask(pTask);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : GetFileList. Done");
	#endif

	return taskID;
}

/****************************************************************

   Class : FileProcessor

   Method : CheckGetFileListResult

   Parameters :
			Input : 
				taskID - task ID
			Ouput : 
				status - task status

   Returns : pointer to folder descriptor

   Description : Check get file list task status
   
*****************************************************************/
PFOLDER_INFO_CONTAINER FileProcessor :: CheckGetFileListResult(unsigned long long taskID, int * status)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		//WriteToLog("FileProcessor : CheckGetFileListResult. Start");
	#endif

	PFOLDER_INFO_CONTAINER result = NULL;
	
	// Get task stutus
	*status = CheckTaskResultStatus(taskID);

	// Check task stutus
	if ((*status != ERROR_TAKS_NOT_FOUND) && (*status != TAKS_STATE_INPROGRESS))
	{
		// Get task from map
		GetFileListTask * pTask = (GetFileListTask *)(PopTask(taskID));

		// If all OK - retrieve result
		if (pTask)
		{
			// Get files list
			if (*status == ERROR_TAKS_RESULT_OK)
				result = pTask -> GetFolderInfoContainer();

			// Delete task
			delete pTask;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		//WriteToLog("FileProcessor : CheckGetFileListResult. Done");
	#endif

	return result;
}

/****************************************************************

   Class : FileProcessor

   Method : DownloadFile

   Parameters :
			Input : 
				fileName - folder name
				downloadDir - default download directory

	Returns : task ID

   Description : Put download file task to queue
   
*****************************************************************/
unsigned long long FileProcessor :: DownloadFile(char * fileName, char * downloadDir)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : DownloadFile. Start");
	#endif

	// Create task
	DownloadFileTask * pTask = new DownloadFileTask(fileName, downloadDir, authManager);

	// Add task to queue
	unsigned long long taskID = PushTask(pTask);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : DownloadFile. Done");
	#endif

	return taskID;
}

/****************************************************************

   Class : FileProcessor

   Method : CheckDownloadFileResult

   Parameters :
			Input : 
				taskID - task ID
			Ouput : 
				status - task status

   Returns : TRUE - if success

   Description : Check download file task status
   
*****************************************************************/
bool FileProcessor :: CheckDownloadFileResult(unsigned long long taskID, int * status)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		//WriteToLog("FileProcessor : CheckDownloadFileResult. Start");
	#endif

	bool result = false;
	
	// Get task status
	*status = CheckTaskResultStatus(taskID);

	// Check task status
	if ((*status != ERROR_TAKS_NOT_FOUND) && (*status != TAKS_STATE_INPROGRESS))
	{
		// Get task from map
		DownloadFileTask * pTask = (DownloadFileTask *)(PopTask(taskID));

		// If all OK - retrieve result
		if (pTask)
		{
			if (*status == ERROR_TAKS_RESULT_OK)
				result = true;

			// Delete task
			delete pTask;
		}
	}
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		//WriteToLog("FileProcessor : CheckDownloadFileResult. Done");
	#endif

	return result;
}

/****************************************************************

   Class : FileProcessor

   Method : UploadFile

   Parameters :
			Input : 
				fileName - folder name

	Returns : task ID

   Description : Put upload file task to queue
   
*****************************************************************/
unsigned long long FileProcessor :: UploadFile(char * fileName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : UploadFile. Start");
	#endif

	// Create task
	UploadFileTask * pTask = new UploadFileTask(fileName, authManager);

	// Add task to queue
	unsigned long long taskID = PushTask(pTask);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : UploadFile. Done");
	#endif

	return taskID;
}

/****************************************************************

   Class : FileProcessor

   Method : CheckUploadFileResult

   Parameters :
			Input : 
				taskID - task ID
			Ouput : 
				status - task status

   Returns : TRUE - if success

   Description : Check upload file task status
   
*****************************************************************/
bool FileProcessor :: CheckUploadFileResult(unsigned long long taskID, int * status)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : CheckUploadFileResult. Start");
	#endif

	bool result = false;
	
	// Get task status
	*status = CheckTaskResultStatus(taskID);

	// Check task status
	if ((*status != ERROR_TAKS_NOT_FOUND) && (*status != TAKS_STATE_INPROGRESS))
	{
		// Get task from map
		UploadFileTask * pTask = (UploadFileTask *)(PopTask(taskID));

		// If all OK - retrieve result
		if (pTask)
		{
			if (*status == ERROR_TAKS_RESULT_OK)
				result = true;

			// Delete task
			delete pTask;
		}
	}
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_AUTH_CLIENT)
		WriteToLog("FileProcessor : CheckUploadFileResult. Done");
	#endif

	return result;
}


/****************************************************************

   Class : FileProcessor

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  FileProcessor :: WriteToLog(char * message)
{
	if (authManager)
		return authManager -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}

#pragma endregion