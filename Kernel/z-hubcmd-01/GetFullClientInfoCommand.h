/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetFullClientInfoCommand.h

   Description :  this module defines interface of
				  class GetFullClientInfoCommand

*****************************************************************/

#include <Command.h>
#include <IPCClientsManager.h>


#ifdef ZHUBCMD01_EXPORTS
#define GET_FULL_CLIENT_INFO_CMD_API __declspec(dllexport)
#else
#define GET_FULL_CLIENT_INFO_CMD_API __declspec(dllimport)
#endif

#ifndef GET_FULL_CLIENT_INFO_CMD_H
#define GET_FULL_CLIENT_INFO_CMD_H

/****************************************************************

   Class : GetFullClientInfoCommand

   Description : Retrieves all info about client machine.

*****************************************************************/
class GET_FULL_CLIENT_INFO_CMD_API GetFullClientInfoCommand : public Command
{
	private:
		
		// Sender ID
		unsigned int senderID;
		
		// Recipient ID
		unsigned int recipientID;

		// IPC clients manager
		IPCClientsManager * ipcClientsManager;

		// Serialization manager instance
		SerializationManager * serializationManager;

		// Get computer name
		PCOMMAND_PARAMETER GetCompName(void);

		// Get logged user ID
		PCOMMAND_PARAMETER_LIST GetLoggedUserID(void);

		// Get hardware info
		PCOMMAND_PARAMETER_LIST GetHardwareInfo(void);

		// Get user environment info
		PCOMMAND_PARAMETER GetEnvironmentInfo(void);

		// Get screenshot
		PCOMMAND_PARAMETER GetScreenshot(void);

		// Get cam snapshot
		PCOMMAND_PARAMETER GetCamSnapshot(void);

	public:

		// Constructor
		GetFullClientInfoCommand(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * ipcClientsManager, unsigned int senderID, unsigned int recipientID);

		// Desctructor
		virtual ~GetFullClientInfoCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif