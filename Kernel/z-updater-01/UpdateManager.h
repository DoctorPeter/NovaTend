/****************************************************************

   Solution : NovaTend

   Project : z-updater-01.dll

   Module : UpdateManager.h

   Description :  this module defines interface of
				  class UpdateManager

*****************************************************************/
#include <FileProcessor.h>
#include <ThreadController.h>
#include <LogWriter.h>

#ifndef UPDATE_MANAGER_H
#define UPDATE_MANAGER_H

/****************************************************************

   Class : UpdateManager

   Description : Responsible for management of
				 periodicaly checking for updates.

*****************************************************************/
class UpdateManager : public ThreadController
{
	protected:

		// Log writer instance
		LogWriter * logWriter;
		
		// File processor instance
		FileProcessor * fileProcessor;



		// Main rountine
		virtual void ControllerEntry(void);

		// Check periodic flag
		virtual bool CheckPeriodicFlag(void);

		// Check period
		virtual bool CheckPeriod(void);

		// Get file list
		PFOLDER_INFO_CONTAINER GetFileList(void);

		// Download files
		bool DownloadFiles(PFOLDER_INFO_CONTAINER pFolder, char * downloadDir);

		// Select only new files in list
		PFOLDER_INFO_CONTAINER SelectNewFiles(PFOLDER_INFO_CONTAINER pLocalFileList, PFOLDER_INFO_CONTAINER pRemoteFileList);

		// Compare files
		bool CompareFiles(PFILE_INFO_CONTAINER pFirstFile, PFILE_INFO_CONTAINER pSecondFile);

		// Delete file list
		PFOLDER_INFO_CONTAINER DeleteFileList(PFOLDER_INFO_CONTAINER pFolder);

		// Delete file info from list
		PFOLDER_INFO_CONTAINER DeleteFileFromList(PFOLDER_INFO_CONTAINER pFolder, int index);

		// Start user updater module
		bool StartUserUpdater(char * updaterPath);

	public:

		// Constructor
		UpdateManager(unsigned long dllUserID, FileProcessor * fileProcessor, LogWriter * logWriter);

		// Desctructor
		virtual ~UpdateManager(void);

		// Write message to LOG-file
		int WriteToLog(char * message);
};

#endif