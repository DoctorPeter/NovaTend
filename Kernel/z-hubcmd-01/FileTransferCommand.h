/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : FileTransferCommand.h

   Description :  this module defines interface of
				  class FileTransferCommand

*****************************************************************/

#include <Command.h>


#ifdef ZHUBCMD01_EXPORTS
#define FILE_TRANSFER_CMD_API __declspec(dllexport)
#else
#define FILE_TRANSFER_CMD_API __declspec(dllimport)
#endif

#ifndef FILE_TRANSFER_CMD_H
#define FILE_TRANSFER_CMD_H

/****************************************************************

   Class : FileTransferCommand

   Description : File transfer command

*****************************************************************/
class FILE_TRANSFER_CMD_API FileTransferCommand : public Command
{
	private:

		// Directories

		// Upload directory
		char mUploadDir[STR_VALUE_LEN];

		// Download directory
		char mDownloadDir[STR_VALUE_LEN];

		// Temporary directory
		char mTempDir[STR_VALUE_LEN];


		// Get real upload path
		char * GetRealUploadPath(char * path);

		// Get real download path
		char * GetRealDownloadPath(char * path);

		// Convert FILETIME to TM struct
		struct tm * FileTimeToTM(FILETIME ft);


		// File operations

		// Get size of file
		bool GetFileSize(char * fileName, DWORD * res);

		// Check file exists
		bool CheckFileExists(char * fileName);

		// Delete file
		bool DeleteFile(char * fileName);

		// Prealloc file
		bool PreallocFile(char * fileName, DWORD distance);

		// Append file
		bool AppendFile(char * fileName, DWORD blockNum, DWORD blockSize, char * data, DWORD curBlockSize);

		// Get block from file
		bool GetFileBlock(char * fileName, DWORD skipBytes, char * data, DWORD curBlockSize, DWORD * out_dwReaded);

		// Read directory information
		PFOLDER_INFO_CONTAINER ReadDirectoryInfo(char * dirName, int maxCount);


		// Get list of files in some directory
		PCOMMAND_PARAMETER_LIST	GetDirectoryInfo(PCOMMAND_PARAMETER_LIST parameters);

		// Upload file request processing
		PCOMMAND_PARAMETER_LIST	UploadFileReq(PCOMMAND_PARAMETER_LIST parameters);

		// Upload file block request processing
		PCOMMAND_PARAMETER_LIST	UploadFileBlockReq(PCOMMAND_PARAMETER_LIST parameters);

		// Download file request processing
		PCOMMAND_PARAMETER_LIST	DownloadFileReq(PCOMMAND_PARAMETER_LIST parameters);

		// Download file block request processing
		PCOMMAND_PARAMETER_LIST	DownloadFileBlockReq(PCOMMAND_PARAMETER_LIST parameters);
		
	public:

		// Constructor
		FileTransferCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~FileTransferCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif