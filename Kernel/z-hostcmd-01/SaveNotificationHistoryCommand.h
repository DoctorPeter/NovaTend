/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : SaveNotificationHistoryCommand.h

   Description :  this module defines interface of
				  class SaveNotificationHistoryCommand

*****************************************************************/

#include <Command.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define SAVE_NOTIFY_HISTORY_CMD_API __declspec(dllexport)
#else
#define SAVE_NOTIFY_HISTORY_CMD_API __declspec(dllimport)
#endif

#ifndef SAVE_NOTIFY_HISTORY_CMD_H
#define SAVE_NOTIFY_HISTORY_CMD_H

/****************************************************************

   Class : SaveNotificationHistoryCommand

   Description : Save history of user notification

*****************************************************************/
class SAVE_NOTIFY_HISTORY_CMD_API SaveNotificationHistoryCommand : public Command
{
	private:
				
		// Save user notification result
		bool SaveUserNotificationHistory(int userID, int noticeID);

	public:

		// Constructor
		SaveNotificationHistoryCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~SaveNotificationHistoryCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif