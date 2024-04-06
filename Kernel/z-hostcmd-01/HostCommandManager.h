/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : HostCommandManager.h

   Description :  this module defines interface of
				  class HostCommandManager

*****************************************************************/

#include "stdafx.h"

#include <HubCommandManager.h>
#include <LicenseManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define HOST_COMMAND_MANAGER_API __declspec(dllexport)
#else
#define HOST_COMMAND_MANAGER_API __declspec(dllimport)
#endif

#ifndef HOST_COMMAND_MANAGER_H
#define HOST_COMMAND_MANAGER_H

/****************************************************************

   Class : HostCommandManager

   Description : Provides general structure of class 
				of commands execution management by
				HOST-Server.

*****************************************************************/
class HOST_COMMAND_MANAGER_API HostCommandManager : public HubCommandManager
{
	protected:

		// Connections to the HUB servers
		IPCClientsManager * hubConnectionsMananger;

		// Generate command
		virtual Command * GenerateCommand(int commandType);

	public:

		// Constructor
		HostCommandManager(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * hostConnectionsMananger, IPCClientsManager * desktopConnectionsMananger, IPCClientsManager * hubConnectionsMananger);

		// Copy constructor
		HostCommandManager(const HostCommandManager &src);

		// Desctructor
		virtual ~HostCommandManager(void);
		
		// Clone object
		virtual CommandManager * Clone(void);

		// Check license
		virtual bool CheckLicense(char * id, char * strValue, int index = -1, int relType = REL_TYPE_EQUAL);
		virtual bool CheckLicense(char * id, int * intValue, int index = -1, int relType = REL_TYPE_EQUAL);
		virtual bool CheckLicense(char * id, tm * tmValue, int index = -1, int relType = REL_TYPE_EQUAL);

		// Check dashboard access
		virtual bool CheckMonitoringAccess(PCOMMAND_REQUEST_RESPONSE cmdRequest);
		
		// Create back connection
		virtual PCOMMAND_REQUEST_RESPONSE CreateBackConnection(PCOMMAND_REQUEST_RESPONSE cmdRequest);
				
		// Redirect request
		virtual PCOMMAND_REQUEST_RESPONSE RedirectRequest(PCOMMAND_REQUEST_RESPONSE cmdRequest);
};

#endif