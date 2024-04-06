/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : RedirectionCommand.h

   Description :  this module defines interface of
				  class RedirectionCommand

*****************************************************************/

#include <Command.h>
#include <IPCClientsManager.h>


#ifdef ZHUBCMD01_EXPORTS
#define REDIRECTION_CMD_API __declspec(dllexport)
#else
#define REDIRECTION_CMD_API __declspec(dllimport)
#endif

#ifndef REDIRECTION_CMD_H
#define REDIRECTION_CMD_H

/****************************************************************

   Class : RedirectionCommand

   Description : Redirects data to another server.

*****************************************************************/
class REDIRECTION_CMD_API RedirectionCommand : public Command
{
	private:
		
		// Command code
		unsigned int commandCode;

		// Sender ID
		unsigned int senderID;
		
		// Recipient ID
		unsigned int recipientID;

		// IPC clients manager
		IPCClientsManager * ipcClientsManager;

	public:

		// Constructor
		RedirectionCommand(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * ipcClientsManager, unsigned int commandCode, unsigned int senderID, unsigned int recipientID);

		// Desctructor
		virtual ~RedirectionCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif