/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : FileTransferCommand.cpp

   Description :  this module implements methods of
				  class FileTransferCommand

*****************************************************************/

#include "stdafx.h"
#include "FileTransferCommand.h"
#include <SettingsManager.h>

// z-hubcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHubCmdDllDefinition;
 
/****************************************************************

   Class : FileTransferCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
FileTransferCommand :: FileTransferCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : constructor");
	#endif
			
	mUploadDir[0] = 0;
	mDownloadDir[0] = 0;
	mTempDir[0] = 0;

	// Read directories
	SettingsManager * settingsManager = new SettingsManager(zHubCmdDllDefinition.dllID);
	settingsManager -> GetUploadDirectory(mUploadDir);
	settingsManager -> GetDownloadDirectory(mDownloadDir);
	settingsManager -> GetTemporaryDirectory(mTempDir);
	delete settingsManager;
}

/****************************************************************

   Class : FileTransferCommand

   Method : Destructor

*****************************************************************/
FileTransferCommand :: ~FileTransferCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : destructor");
	#endif
}

/****************************************************************

   Class : FileTransferCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST FileTransferCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	if ((parameters) &&
		(parameters -> paramCount == 2) &&
		(parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[1]) && (parameters -> paramList[1] -> paramDataType == STRING_DATA))
	{
		result = GetDirectoryInfo(parameters);
	}
	else
	if ((parameters) &&
		(parameters -> paramCount == 2) &&
		(parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[1]) && (parameters -> paramList[1] -> paramDataType == LONG_DATA))
	{
		result = UploadFileReq(parameters);
	}
	else
	if ((parameters) &&
		(parameters -> paramCount == 4) &&
		(parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[1]) && (parameters -> paramList[1] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[2]) && (parameters -> paramList[2] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[3]) && (parameters -> paramList[3] -> paramDataType == BINARY_DATA))
	{
		result = UploadFileBlockReq(parameters);
	}
	else
	if ((parameters) &&
		(parameters -> paramCount == 1) &&
		(parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == STRING_DATA))
	{
		result = DownloadFileReq(parameters);
	}
	else
	if ((parameters) &&
		(parameters -> paramCount == 3) &&
		(parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == STRING_DATA) &&
		(parameters -> paramList[1]) && (parameters -> paramList[1] -> paramDataType == DWORD_DATA) &&
		(parameters -> paramList[2]) && (parameters -> paramList[2] -> paramDataType == DWORD_DATA))
	{
		result = DownloadFileBlockReq(parameters);
	}
		
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : FileTransferCommand

   Method : DeleteFile

   Parameters :
			Input : 
				fileName - file name

	Return : TRUE - if success

	Description : delete file

*****************************************************************/
bool FileTransferCommand :: DeleteFile(char * fileName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : DeleteFile");
	#endif

	return DeleteFileA(fileName);
}

/****************************************************************

   Class : FileTransferCommand

   Method : GetFileSize

   Parameters :
			Input : 
				fileName - file name
			Output:
				res - size of file in bytes

	Return : TRUE - if success

	Description : Get size of file

*****************************************************************/
bool FileTransferCommand :: GetFileSize(char * fileName, DWORD * res)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : GetFileSize. Start");
	#endif

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
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("FileTransferCommand : GetFileSize. Can't get file size!");
				WriteToLog("FileTransferCommand : GetFileSize. Done");
			#endif

			return false;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("FileTransferCommand : GetFileSize. Can't open file!");
			WriteToLog("FileTransferCommand : GetFileSize. Done");
		#endif

		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		char message[256] = "";
		sprintf(message, "FileTransferCommand : GetFileSize. Size = %d", *res);
		WriteToLog(message);
		WriteToLog("FileTransferCommand : GetFileSize. Done");
	#endif

	return true;
}

/****************************************************************

   Class : FileTransferCommand

   Method : CheckFileExists

   Parameters :
			Input : 
				fileName - file name

	Return : TRUE - if success

	Description : Check file exists

*****************************************************************/
bool FileTransferCommand :: CheckFileExists(char * fileName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : CheckFileExists");
	#endif

	DWORD dwAttrib = GetFileAttributesA(fileName);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

/****************************************************************

   Class : FileTransferCommand

   Method : PreallocFile

   Parameters :
			Input : 
				fileName - file name
				distance - distance in bytes

	Return : TRUE - if success

	Description : Prealloc file

*****************************************************************/
bool FileTransferCommand :: PreallocFile(char * fileName, DWORD distance)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : PreallocFile. Start");
	#endif

	HANDLE hFile;
	DWORD  dwBytesRead, dwPos;

	// Open the PHYSICALDEVICE as a file. 
	hFile = CreateFileA(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	// Check result
	if (hFile == INVALID_HANDLE_VALUE)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("FileTransferCommand : PreallocFile. Can't open file!");
			WriteToLog("FileTransferCommand : PreallocFile. Done");
		#endif

		return false;
	}

	// Move to distance
	dwPos = SetFilePointer(hFile, distance, NULL, FILE_BEGIN);

	// Mark end of file
	SetEndOfFile(hFile);

	// Check result
	if (dwPos == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("FileTransferCommand : PreallocFile. Can't alloc file!");
			WriteToLog("FileTransferCommand : PreallocFile. Done");
		#endif

		CloseHandle(hFile);
		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : PreallocFile. File allocated!");
		WriteToLog("FileTransferCommand : PreallocFile. Done");
	#endif

	CloseHandle(hFile);
	return true;
}

/****************************************************************

   Class : FileTransferCommand

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
bool FileTransferCommand :: AppendFile(char * fileName, DWORD blockNum, DWORD blockSize, char * data, DWORD curBlockSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : AppendFile. Start");
	#endif

	// Open file
	HANDLE hAppend;
	hAppend = CreateFileA(fileName, FILE_WRITE_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hAppend == INVALID_HANDLE_VALUE)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("FileTransferCommand : AppendFile. Can't open file!");
			WriteToLog("FileTransferCommand : AppendFile. Done");
		#endif

		return false;
	}

	// Move file pointer
	DWORD dwPos = SetFilePointer(hAppend, blockNum * blockSize, NULL, FILE_BEGIN);
	if (dwPos == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("FileTransferCommand : AppendFile. Can't set file pointer!");
			WriteToLog("FileTransferCommand : AppendFile. Done");
		#endif

		CloseHandle(hAppend);
		return false;
	}
	
	// Save block of data
	DWORD dwBytesWritten;
	LockFile(hAppend, dwPos, 0, curBlockSize, 0);
	WriteFile(hAppend, data, curBlockSize, &dwBytesWritten, NULL);
	UnlockFile(hAppend, dwPos, 0, curBlockSize, 0);
	CloseHandle(hAppend);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : AppendFile. Block of data successfully added!");
		WriteToLog("FileTransferCommand : AppendFile. Done");
	#endif

	return true;
}

/****************************************************************

   Class : FileTransferCommand

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
bool FileTransferCommand :: GetFileBlock(char * fileName, DWORD skipBytes, char * data, DWORD curBlockSize, DWORD * out_dwReaded)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : GetFileBlock. Start");
	#endif

	// Open file
	HANDLE hRead;
	hRead = CreateFileA(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hRead == INVALID_HANDLE_VALUE)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("FileTransferCommand : GetFileBlock. Can't open file!");
			WriteToLog("FileTransferCommand : GetFileBlock. Done");
		#endif

		return false;
	}

	// Move file pointer
	DWORD dwPos = SetFilePointer(hRead, skipBytes, NULL, FILE_BEGIN);
	if (dwPos == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("FileTransferCommand : GetFileBlock. Can't set file pointer!");
			WriteToLog("FileTransferCommand : GetFileBlock. Done");
		#endif

		CloseHandle(hRead);
		return false;
	}

	// Read data
	bool bRes = ReadFile(hRead, data, curBlockSize, out_dwReaded, NULL);
	CloseHandle(hRead);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : GetFileBlock. Block successfully readed");
		WriteToLog("FileTransferCommand : GetFileBlock. Done");
	#endif

	return bRes;
}

/****************************************************************

   Class : FileTransferCommand

   Method : ReadDirectoryInfo

   Parameters :
			Input : 
				dirName - path to directory
				maxCount - max files count

	Return : Pointer to upload path

	Description : Read directory information

*****************************************************************/
PFOLDER_INFO_CONTAINER FileTransferCommand :: ReadDirectoryInfo(char * dirName, int maxCount)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : ReadDirectoryInfo. Start");
	#endif

	PFOLDER_INFO_CONTAINER result = NULL;

	WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    //Specify a file mask. *.*
    strcat(dirName, "\\*.*");
	WCHAR wDirName[NAME_LEN] = L"";
	mbstowcs(wDirName, dirName, NAME_LEN);

	// Find first file
    if((hFind = FindFirstFile(wDirName, &fdFile)) == INVALID_HANDLE_VALUE) 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			WriteToLog("FileTransferCommand : ReadDirectoryInfo. Can't open specified directory!");
			WriteToLog("FileTransferCommand : ReadDirectoryInfo. Start");
		#endif

        return NULL;
    }
	else
	{
		// Allocate directory info container
		result = (PFOLDER_INFO_CONTAINER)malloc(sizeof(FOLDER_INFO_CONTAINER));

		if (result)
		{
			// Check max count
			if (maxCount == 0) maxCount = MAX_DIR_FILES_COUNT;

			// Save dir name
			strcpy(result -> dirName, dirName);
			result -> filesCount = 0;
			for(int i = 0; i < MAX_DIR_FILES_COUNT; i++)
				result -> filesList[i] = NULL;

			do 
			{
				if ((wcscmp(fdFile.cFileName, L".") == 0) || 
					(wcscmp(fdFile.cFileName, L"..") == 0))
						continue;
				
				// Allocate memory for file info
				PFILE_INFO_CONTAINER pFileInfo = (PFILE_INFO_CONTAINER)malloc(sizeof(FILE_INFO_CONTAINER));

				if (pFileInfo)
				{
					wcstombs(pFileInfo -> fileName, fdFile.cFileName, NAME_LEN);
					
					struct tm * tmp = FileTimeToTM(fdFile.ftLastWriteTime);
					if (tmp)
					{
						memcpy(&(pFileInfo -> updateTime), tmp, sizeof(struct tm));
						free(tmp);
					}
					else
						memset(&(pFileInfo -> updateTime), 0, sizeof(struct tm));

					pFileInfo -> fileSize = ((unsigned __int64)fdFile.nFileSizeHigh * ((unsigned __int64)MAXDWORD + 1) + (unsigned __int64)fdFile.nFileSizeLow);
					pFileInfo -> isDir = fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;

					result -> filesList[result -> filesCount] = pFileInfo;
					result -> filesCount++;
				}

			// Find next file
			} while((FindNextFile(hFind, &fdFile)) && (result -> filesCount < maxCount) && (result -> filesCount < MAX_DIR_FILES_COUNT));

			FindClose(hFind);
    	}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
			else
				WriteToLog("FileTransferCommand : ReadDirectoryInfo. Error of memory allocation!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : ReadDirectoryInfo. Done");
	#endif

	return result;
}

/****************************************************************

   Class : FileTransferCommand

   Method : GetRealUploadPath

   Parameters :
			Input : 
				path - path to file

	Return : Pointer to upload path

	Description : Get real upload path

*****************************************************************/
char * FileTransferCommand :: GetRealUploadPath(char * path)
{
	// Check if we have absolute path to file
	if ((strlen(path) > 2) && (isalpha(path[0])) && (path[1] == ':') && (path[2] == '\\'))
	{
		return path;
	}
	// if we have not abs path we must append upload dir path
	else
	{
		char tempStr[STR_VALUE_LEN] = "";
		strcpy(tempStr, mUploadDir);
		strcat(tempStr, "\\");
		strcat(tempStr, path);
		strcpy(path, tempStr);
		return path;
	}
}

/****************************************************************

   Class : FileTransferCommand

   Method : GetRealDownloadPath

   Parameters :
			Input : 
				path - path to file

	Return : Pointer to download path

	Description : Get real download path

*****************************************************************/
char * FileTransferCommand :: GetRealDownloadPath(char * path)
{
	// Check if we have absolute path to file
	if ((strlen(path) > 2) && (isalpha(path[0])) && (path[1] == ':') && (path[2] == '\\'))
	{
		return path;
	}
	// if we have not abs path we must append download dir path
	else
	{
		char tempStr[STR_VALUE_LEN] = "";
		strcpy(tempStr, mDownloadDir);
		strcat(tempStr, "\\");
		strcat(tempStr, path);
		strcpy(path, tempStr);
		return path;
	}
}

/****************************************************************

   Class : FileTransferCommand

   Method : FileTimeToTM

   Parameters :
			Input : 
				ft -  filetime value

	Return : Pointer to TM struct

	Description : Convert FILETIME to TM struct

*****************************************************************/
struct tm * FileTransferCommand :: FileTimeToTM(FILETIME ft)
{
	struct tm * result = (struct tm *)malloc(sizeof(struct tm));

	if (result)
	{
		SYSTEMTIME st;
		FileTimeToSystemTime(&ft, &st);

		memset(result, 0, sizeof(struct tm));

		result -> tm_mday = st.wDay;
		result -> tm_mon  = st.wMonth - 1;
		result -> tm_year = st.wYear - 1900;

		result -> tm_sec  = st.wSecond;
		result -> tm_min  = st.wMinute;
		result -> tm_hour = st.wHour;
	}

  return result;
}

/****************************************************************

   Class : FileTransferCommand

   Method : GetDirectoryInfo

   Parameters :
			Input : 
				parameters -  pointer to input parameters list

	Return : Pointer to output parameters list

	Description : Get list of files in some directory

*****************************************************************/
PCOMMAND_PARAMETER_LIST	FileTransferCommand :: GetDirectoryInfo(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : GetDirectoryInfo. Start");
	#endif

	// Result parameters list
	PCOMMAND_PARAMETER_LIST resultParams = NULL;

	// Check input data
	if (parameters)
	{
		try
		{
			// Create serialization manager instance
			SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

			resultParams = serializationManager -> CreateCommandParameterList();

			if (resultParams)
			{
				// One result parameter
				resultParams -> paramCount = 1;

				// Input parameters values
				char dirPath[STR_VALUE_LEN] = "";
				DWORD count = 0;

				// Unpack first param
				if ((parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == DWORD_DATA))
				{
					count = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
				}

				// Unpack second param
				if ((parameters -> paramList[1]) && (parameters -> paramList[1] -> paramDataType == STRING_DATA))
				{
					serializationManager -> UnpackString(parameters -> paramList[1], dirPath);
				}

				// Correction of directory path
				GetRealDownloadPath(dirPath);

				// Read info container
				PFOLDER_INFO_CONTAINER pFolderContainer = ReadDirectoryInfo(dirPath, count);

				// Check folder container
				if (pFolderContainer)
				{
					// Pack folder container
					resultParams -> paramList[0] = serializationManager -> PackFolderInfoContainer(pFolderContainer, RETURN_CMD_DATA);
					
					//Delete folder container
					for (int i = 0; i < pFolderContainer -> filesCount; i++)
						free(pFolderContainer -> filesList[i]);
					free(pFolderContainer);
				}
				else
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
						WriteToLog("FileTransferCommand : GetDirectoryInfo. Folder info container was not created!");
					#endif

					resultParams -> paramList[0] = serializationManager -> CreateCommandParameter();
				}
			}

			// Delete serialization manager instance
			delete serializationManager;
		}
		catch(...)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("FileTransferCommand : GetDirectoryInfo. Request processing error!");
				WriteToLog("FileTransferCommand : GetDirectoryInfo. Done");
			#endif

			return NULL;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : GetDirectoryInfo. Done");
	#endif

	return resultParams;
}

/****************************************************************

   Class : FileTransferCommand

   Method : UploadFileReq

   Parameters :
			Input : 
				parameters -  pointer to input parameters list

	Return : Pointer to output parameters list

	Description : Upload file request processing

*****************************************************************/
PCOMMAND_PARAMETER_LIST	FileTransferCommand :: UploadFileReq(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : UploadFileReq. Start");
	#endif

	// Result parameters list
	PCOMMAND_PARAMETER_LIST resultParams = NULL;

	// Check input data
	if (parameters)
	{
		try
		{
			// Create serialization manager instance
			SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

			resultParams = serializationManager -> CreateCommandParameterList();

			if (resultParams)
			{
				// One result parameter
				resultParams -> paramCount = 1;

				// Input parameters values
				char filePath[STR_VALUE_LEN] = "";
				DWORD len = 0;

				// Unpack first param
				if ((parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == STRING_DATA))
				{
					serializationManager -> UnpackString(parameters -> paramList[0], filePath);
				}

				// Unpack second param
				if ((parameters -> paramList[1]) && (parameters -> paramList[1] -> paramDataType == LONG_DATA))
				{
					len = serializationManager -> UnpackLong(parameters -> paramList[1]);
				}

				// Correction of file path
				GetRealUploadPath(filePath);

				// Check file existing
				bool bResult = CheckFileExists(filePath);

				// Error - File already exists
				if (bResult)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
						WriteToLog("FileTransferCommand : UploadFileReq. File already exist");
					#endif

					resultParams -> paramList[0] = serializationManager -> CreateCommandParameter();
				}
				else
				{
					// Error - We can't extend file to requested size
					bResult = PreallocFile(filePath, len);

					if (!bResult)
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
							WriteToLog("FileTransferCommand : UploadFileReq. Can't extend file to requested size");
						#endif

						DeleteFile(filePath);
						resultParams -> paramList[0] = serializationManager -> CreateCommandParameter();
					}
					else
					{
						resultParams -> paramList[0] = serializationManager -> PackString(filePath, RETURN_CMD_DATA);
					}
				}
			}

			// Delete serialization manager instance
			delete serializationManager;
		}
		catch(...)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("FileTransferCommand : UploadFileReq. Request processing error!");
				WriteToLog("FileTransferCommand : UploadFileReq. Done");
			#endif

			return NULL;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : UploadFileReq. Done");
	#endif

	return resultParams;
}

/****************************************************************

   Class : FileTransferCommand

   Method : UploadFileBlockReq

   Parameters :
			Input : 
				parameters -  pointer to input parameters list

	Return : Pointer to output parameters list

	Description : Upload file block request processing

*****************************************************************/
PCOMMAND_PARAMETER_LIST	FileTransferCommand :: UploadFileBlockReq(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : UploadFileBlockReq. Start");
	#endif

	// Result parameters list
	PCOMMAND_PARAMETER_LIST resultParams = NULL;

	// Check input data
	if (parameters)
	{
		try
		{
			// Create serialization manager instance
			SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

			resultParams = serializationManager -> CreateCommandParameterList();

			if (resultParams)
			{
				// One result parameter
				resultParams -> paramCount = 1;

				// Input parameters values
				char filePath[STR_VALUE_LEN] = "";
				DWORD blockNumber = 0;
				DWORD blockSize = 0;

				unsigned char * curBlockPointer = 0;
				int curBlockSize = 0;

				// Unpack first param
				if ((parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == STRING_DATA))
				{
					serializationManager -> UnpackString(parameters -> paramList[0], filePath);
				}

				// Unpack second param
				if ((parameters -> paramList[1]) && (parameters -> paramList[1] -> paramDataType == DWORD_DATA))
				{
					blockNumber = serializationManager -> UnpackDWORD(parameters -> paramList[1]);
				}

				// Unpack third param
				if ((parameters -> paramList[2]) && (parameters -> paramList[2] -> paramDataType == DWORD_DATA))
				{
					blockSize = serializationManager -> UnpackDWORD(parameters -> paramList[2]);
				}

				// Unpack fourth param
				if ((parameters -> paramList[3]) && (parameters -> paramList[3] -> paramDataType == BINARY_DATA))
				{
					curBlockPointer = serializationManager -> UnpackBinary(parameters -> paramList[3], &curBlockSize);
				}

				// Correction of file path
				GetRealUploadPath(filePath);

				// Append block to file
				bool bResult = AppendFile(filePath, blockNumber, blockSize, (char *)curBlockPointer, curBlockSize);

				if (!bResult)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
						WriteToLog("FileTransferCommand : UploadFileBlockReq. Can't append block to file!");
					#endif

					resultParams -> paramList[0] = serializationManager -> CreateCommandParameter();
				}
				else
				{
					resultParams -> paramList[0] = serializationManager -> PackString(filePath, RETURN_CMD_DATA);
				}
			}

			// Delete serialization manager instance
			delete serializationManager;
		}
		catch(...)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("FileTransferCommand : UploadFileBlockReq. Request processing error!");
				WriteToLog("FileTransferCommand : UploadFileBlockReq. Done");
			#endif

			return NULL;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : UploadFileBlockReq. Done");
	#endif

	return resultParams;
}

/****************************************************************

   Class : FileTransferCommand

   Method : DownloadFileReq

   Parameters :
			Input : 
				parameters -  pointer to input parameters list

	Return : Pointer to output parameters list

	Description : Download file request processing

*****************************************************************/
PCOMMAND_PARAMETER_LIST	FileTransferCommand :: DownloadFileReq(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : DownloadFileReq. Start");
	#endif

	// Result parameters list
	PCOMMAND_PARAMETER_LIST resultParams = NULL;

	// Check input data
	if (parameters)
	{
		try
		{
			// Create serialization manager instance
			SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

			resultParams = serializationManager -> CreateCommandParameterList();

			if (resultParams)
			{
				// One result parameter
				resultParams -> paramCount = 1;

				// Input parameters values
				char filePath[STR_VALUE_LEN] = "";

				// Unpack first param
				if ((parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == STRING_DATA))
				{
					serializationManager -> UnpackString(parameters -> paramList[0], filePath);
				}

				// Correction of file path
				GetRealDownloadPath(filePath);

				// Check file existing
				bool bResult = CheckFileExists(filePath);

				if (!bResult)
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
						WriteToLog("FileTransferCommand : DownloadFileReq. File does not exists");
					#endif

					resultParams -> paramList[0] = serializationManager -> CreateCommandParameter();
				}
				else
				{
					// Get file size
					DWORD szFile;
					bResult = GetFileSize(filePath, &szFile);

					if (!bResult)
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
							WriteToLog("FileTransferCommand : DownloadFileReq. Can't get file size!");
						#endif

						resultParams -> paramList[0] = serializationManager -> CreateCommandParameter();
					}
					else
					{
						resultParams -> paramList[0] = serializationManager -> PackLong(szFile, RETURN_CMD_DATA);
					}
				}
			}

			// Delete serialization manager instance
			delete serializationManager;
		}
		catch(...)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("FileTransferCommand : DownloadFileReq. Request processing error!");
				WriteToLog("FileTransferCommand : DownloadFileReq. Done");
			#endif

			return NULL;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : DownloadFileReq. Done");
	#endif

	return resultParams;
}

/****************************************************************

   Class : FileTransferCommand

   Method : DownloadFileBlockReq

   Parameters :
			Input : 
				parameters -  pointer to input parameters list

	Return : Pointer to output parameters list

	Description : Download file block request processing

*****************************************************************/
PCOMMAND_PARAMETER_LIST	FileTransferCommand :: DownloadFileBlockReq(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : DownloadFileBlockReq. Start");
	#endif

	// Result parameters list
	PCOMMAND_PARAMETER_LIST resultParams = NULL;

	// Check input data
	if (parameters)
	{
		try
		{
			// Create serialization manager instance
			SerializationManager * serializationManager = new SerializationManager(zHubCmdDllDefinition.dllID, logWriter);

			resultParams = serializationManager -> CreateCommandParameterList();

			if (resultParams)
			{
				// One result parameter
				resultParams -> paramCount = 1;

				// Input parameters values
				char filePath[STR_VALUE_LEN] = "";
				DWORD blockNumber = 0;
				DWORD blockSize = 0;

				unsigned char * curBlockPointer = 0;
				int curBlockSize = 0;

				// Unpack first param
				if ((parameters -> paramList[0]) && (parameters -> paramList[0] -> paramDataType == STRING_DATA))
				{
					serializationManager -> UnpackString(parameters -> paramList[0], filePath);
				}

				// Unpack second param
				if ((parameters -> paramList[1]) && (parameters -> paramList[1] -> paramDataType == DWORD_DATA))
				{
					blockNumber = serializationManager -> UnpackDWORD(parameters -> paramList[1]);
				}

				// Unpack third param
				if ((parameters -> paramList[2]) && (parameters -> paramList[2] -> paramDataType == DWORD_DATA))
				{
					blockSize = serializationManager -> UnpackDWORD(parameters -> paramList[2]);
				}

				// Correction of file path
				GetRealDownloadPath(filePath);

				DWORD dwReadedBytes = 0;

				//Allocate memory for fileblock
				char * cData = (char *)malloc(blockSize);

				//Request for data
				bool bResult = GetFileBlock(filePath, blockNumber * blockSize, cData, blockSize, &dwReadedBytes);

				//Check results
				if (!bResult)
				{
					resultParams -> paramList[0] = serializationManager -> CreateCommandParameter();
				}
				else
				{
					resultParams -> paramList[0] = serializationManager -> PackBinary((unsigned char*)cData, dwReadedBytes, RETURN_CMD_DATA);
				}
				
				//Free memory for fileblock
				free(cData);
			}

			// Delete serialization manager instance
			delete serializationManager;
		}
		catch(...)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
				WriteToLog("FileTransferCommand : DownloadFileBlockReq. Request processing error!");
				WriteToLog("FileTransferCommand : DownloadFileBlockReq. Done");
			#endif

			return NULL;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HUB_CMD)
		WriteToLog("FileTransferCommand : DownloadFileBlockReq. Done");
	#endif

	return resultParams;
}