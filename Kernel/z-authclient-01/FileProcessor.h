/****************************************************************

   Solution : NovaTend

   Project : z-authclient-01.dll

   Module : FileProcessor.h

   Description : this module defines interface of
				  class FileProcessor

*****************************************************************/
#include <AuthenticateManager.h>
#include <BackgroundTaskManager.h>

#ifdef ZAUTHCLIENT01_EXPORTS
#define FILE_PROCESSOR_API __declspec(dllexport)
#else
#define FILE_PROCESSOR_API __declspec(dllimport)
#endif

#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H


// Task type - Get file list
#define GET_FILE_LIST_TASK					1

// Task type - Download file
#define DOWNLOAD_FILE_TASK					2

// Task type - Upload file
#define UPLOAD_FILE_TASK					3


/****************************************************************

   Class : FileProcessorTask

   Description : desccribes all file processor tasks

*****************************************************************/
class FILE_PROCESSOR_API FileProcessorTask : public TaskDescriptor
{
	protected :
		
		// Auth manager instance
		AuthenticateManager * authManager;

	public :

		// Constructor
		FileProcessorTask(int taskType, AuthenticateManager * authManager);

		// Destructor
		virtual ~FileProcessorTask(void);
				
		// Write message to log-file
		int WriteToLog(char * message);


		// Get file name
		static char * GetFileName(char * filePath, char * fileName);
		
		// Delete file
		static bool DeleteFile(char * fileName);

		// Prealloc file
		static bool PreallocFile(char * fileName, int distance);

		// Append file
		static bool AppendFile(char * fileName, int blockNum, int blockSize, char * data, int curBlockSize);

		// Get size of file
		static bool GetFileSize(char * fileName, unsigned long long * res);

		// Get block from file
		static bool GetFileBlock(char * fileName, int skipBytes, char * data, int curBlockSize, int * out_dwReaded);
};


/****************************************************************

   Class : GetFileListTask

   Description : responsible for retrieving
				 of list of files in some server 
				 directory

*****************************************************************/
class FILE_PROCESSOR_API GetFileListTask : public FileProcessorTask
{
	private :

		// Folder name
		char dirName[MAX_PATH];

		// Folder container
		PFOLDER_INFO_CONTAINER pFolder;

	public :

		// Constructor
		GetFileListTask(char * dirName, AuthenticateManager * authManager);

		// Destructor
		virtual ~GetFileListTask(void);

		// Execute task
		virtual int Execute(void);

		// Get folder decriptor
		PFOLDER_INFO_CONTAINER GetFolderInfoContainer(void);
};

/****************************************************************

   Class : DownloadFileTask

   Description : responsible for downloading of file

*****************************************************************/
class FILE_PROCESSOR_API DownloadFileTask : public FileProcessorTask
{
	private :

		// Default download directory
		char downloadDir[MAX_PATH];


		// File name
		char fileName[MAX_PATH];

		// Saved file name
		char savedFileName[MAX_PATH];

		// Size of file
		unsigned long long fileSize;

		// Count of blocks
		int blockCount;

		// Number of file block
		int blockNumber;
		
		// Size of file block
		int blockSize;

		// Pointer to file block
		char * pFileBlock;

	public :

		// Constructor
		DownloadFileTask(char * fileName, char * downloadDir, AuthenticateManager * authManager);

		// Destructor
		virtual ~DownloadFileTask(void);

		// Execute task
		virtual int Execute(void);
};

/****************************************************************

   Class : UploadFileTask

   Description : responsible for uploading of file

*****************************************************************/
class FILE_PROCESSOR_API UploadFileTask : public FileProcessorTask
{
	private :

		// File name
		char fileName[MAX_PATH];

		// Uploaded file name
		char uploadedFileName[MAX_PATH];

		// Size of file
		unsigned long long fileSize;

		// Count of blocks
		int blockCount;

		// Number of file block
		int blockNumber;
		
		// Size of file block
		int blockSize;

		// Pointer to file block
		char * pFileBlock;

	public :

		// Constructor
		UploadFileTask(char * fileName, AuthenticateManager * authManager);

		// Destructor
		virtual ~UploadFileTask(void);

		// Execute task
		virtual int Execute(void);
};

/****************************************************************

   Class : FileProcessor 

   Description : responsible for management
				 of all file operations on the
				 client side

*****************************************************************/
class FILE_PROCESSOR_API FileProcessor : public BackgroundTaskManager
{
	private :
		
		// Auth manager instance
		AuthenticateManager * authManager;
		
	public :

		// Constructor
		FileProcessor(unsigned long dllUserID, AuthenticateManager * authManager);

		// Destructor
		virtual ~FileProcessor(void);

		// Put get file list task to queue
		unsigned long long GetFileList(char * dirName);

		// Check get file list task status
		PFOLDER_INFO_CONTAINER CheckGetFileListResult(unsigned long long taskID, int * status);

		// Put download file task to queue
		unsigned long long DownloadFile(char * fileName, char * downloadDir);

		// Check download file task status
		bool CheckDownloadFileResult(unsigned long long taskID, int * status);

		// Put upload file task to queue
		unsigned long long UploadFile(char * fileName);

		// Check upload file task status
		bool CheckUploadFileResult(unsigned long long taskID, int * status);
		
		// Write message to log-file
		int WriteToLog(char * message);
};

#endif