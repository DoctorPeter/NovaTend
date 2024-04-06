/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : HubCommandManager.h

   Description :  this module defines interface of
				  class HubCommandManager

*****************************************************************/

#include "stdafx.h"

#include <CommandManager.h>
#include <IPCClientsManager.h>
#include <LicenseDataDef.h>

#ifdef ZHUBCMD01_EXPORTS
#define HUB_COMMAND_MANAGER_API __declspec(dllexport)
#else
#define HUB_COMMAND_MANAGER_API __declspec(dllimport)
#endif

#ifndef HUB_COMMAND_MANAGER_H
#define HUB_COMMAND_MANAGER_H

/****************************************************************

   Class : HubCommandManager

   Description : Provides general structure of class 
				of commands execution management by
				Hub-Server.

*****************************************************************/
class HUB_COMMAND_MANAGER_API HubCommandManager : public CommandManager
{
	protected:

		// Connections to the HOST servers
		IPCClientsManager * hostConnectionsMananger;

		// Connections to the DESKTOP servers
		IPCClientsManager * desktopConnectionsMananger;


		// Generate command
		virtual Command * GenerateCommand(int commandType);

	public:

		// Constructor
		HubCommandManager(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * hostConnectionsMananger, IPCClientsManager * desktopConnectionsMananger);

		// Copy constructor
		HubCommandManager(const HubCommandManager &src);

		// Desctructor
		virtual ~HubCommandManager(void);
		
		// Clone object
		virtual CommandManager * Clone(void);

		// Check license
		virtual bool CheckLicense(char * id, char * strValue, int index = -1, int relType = REL_TYPE_EQUAL);
		virtual bool CheckLicense(char * id, int * intValue, int index = -1, int relType = REL_TYPE_EQUAL);
		virtual bool CheckLicense(char * id, tm * tmValue, int index = -1, int relType = REL_TYPE_EQUAL);

		// Check dashboard access
		virtual bool CheckMonitoringAccess(PCOMMAND_REQUEST_RESPONSE cmdRequest);
		
		// Execute command
		virtual PCOMMAND_REQUEST_RESPONSE ExecuteCommand(PCOMMAND_REQUEST_RESPONSE cmdRequest);
		
		// Create back connection
		virtual PCOMMAND_REQUEST_RESPONSE CreateBackConnection(PCOMMAND_REQUEST_RESPONSE cmdRequest);
				
		// Redirect request
		virtual PCOMMAND_REQUEST_RESPONSE RedirectRequest(PCOMMAND_REQUEST_RESPONSE cmdRequest);
};

#endif