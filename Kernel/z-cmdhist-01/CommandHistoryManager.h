/****************************************************************

   Solution : NovaTend

   Project : z-cmdhist-01.dll

   Module : CommandHistoryManager.h

   Description :  this module defines interface of
				  class CommandHistoryManager

*****************************************************************/

#include "stdafx.h"

#include <SystemBase.h>
#include <LogWriter.h>
#include <Encryptor.h>
#include <DatabaseManager.h>
#include <SerializationDef.h>

#ifdef ZCMDHIST01_EXPORTS
#define CMD_HIST_MANAGER_API __declspec(dllexport)
#else
#define CMD_HIST_MANAGER_API __declspec(dllimport)
#endif

#ifndef CMD_HIST_MANAGER_H
#define CMD_HIST_MANAGER_H

/****************************************************************

   Class : CommandHistoryManager

   Description : responsible for management of local 
				 machines commands history.

*****************************************************************/
class CMD_HIST_MANAGER_API CommandHistoryManager : public SystemBase
{
	private:

		// Database manager instance
		DatabaseManager * dbManager;

		// Encryptor instance
		Encryptor * encryptor;

		// Log writer instance
		LogWriter * logWriter;

		// Connect to database
		bool DatabaseConnect(void);

		// Disconnect from database
		bool DatabaseDisconnect(void);

		// Save command info
		int SaveCommandInfo(int cmdID, int userID);

		// Save command parameter info
		bool SaveCommandParameterInfo(int historyID, PCOMMAND_PARAMETER_LIST paramList);

		// Write message to LOG-file
		int WriteToLog(char * message);

	public:

		// Constructor
		CommandHistoryManager(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~CommandHistoryManager(void);

		// Get command history
		PCMD_HISTORY GetCommandHistory(char * beginTime, char * endTime);

		// Get command parameters
		PCOMMAND_PARAMETER_LIST GetCommandParameters(int cmdID, int userID, char * execTime);

		// Save command to history
		bool SaveCommand(int cmdID, int userID, PCOMMAND_PARAMETER_LIST inParams, PCOMMAND_PARAMETER_LIST outParams);

		// Create history list
		PCMD_HISTORY CreateHistory(void);

		// Delete history list
		PCMD_HISTORY DeleteHistory(PCMD_HISTORY pHistory);

		// Clean history
		void CleanHistory(void);
};

#endif