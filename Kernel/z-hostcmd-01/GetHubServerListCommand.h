/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetHubServerListCommand.h

   Description :  this module defines interface of
				  class GetHubServerListCommand

*****************************************************************/

#include <Command.h>
#include <IPCClientsManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define GET_HUB_LIST_CMD_API __declspec(dllexport)
#else
#define GET_HUB_LIST_CMD_API __declspec(dllimport)
#endif

#ifndef GET_HUB_LIST_CMD_H
#define GET_HUB_LIST_CMD_H

/****************************************************************

   Class : GetHubServerListCommand

   Description : Get list of HUB servers description

*****************************************************************/
class GET_HUB_LIST_CMD_API GetHubServerListCommand : public Command
{
	private:

		// Connections to the HUB servers
		IPCClientsManager * hubConnectionsMananger;

		// Get list of servers
		PSERVER_DESCRIPTION_LIST GetHubServersList(void);

		// Delete list of servers
		PSERVER_DESCRIPTION_LIST DeleteServerListContainer(PSERVER_DESCRIPTION_LIST serverList);

	public:

		// Constructor
		GetHubServerListCommand(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * hubConnectionsMananger);

		// Desctructor
		virtual ~GetHubServerListCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif