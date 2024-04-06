/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : DesktopCommandManager.h

   Description :  this module defines interface of
				  class DesktopCommandManager

*****************************************************************/

#include "stdafx.h"

#include <CommandManager.h>
#include <IPCClientsManager.h>
#include <LicenseDataDef.h>

#ifdef ZDESKTOPCMD01_EXPORTS
#define DESKTOP_COMMAND_MANAGER_API __declspec(dllexport)
#else
#define DESKTOP_COMMAND_MANAGER_API __declspec(dllimport)
#endif

#ifndef DESKTOP_COMMAND_MANAGER_H
#define DESKTOP_COMMAND_MANAGER_H

/****************************************************************

   Class : DesktopCommandManager

   Description : Provides general structure of class 
				of commands execution management by
				Desktop-Server.

*****************************************************************/
class DESKTOP_COMMAND_MANAGER_API DesktopCommandManager : public CommandManager
{
	protected:

		// Connections to the HUB servers
		IPCClientsManager * hubConnectionsMananger;



		// Generate command
		virtual Command * GenerateCommand(int commandType);

	public:

		// Constructor
		DesktopCommandManager(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * hubConnectionsMananger);

		// Copy constructor
		DesktopCommandManager(const DesktopCommandManager &src);

		// Desctructor
		virtual ~DesktopCommandManager(void);

		// Clone object
		virtual CommandManager * Clone(void);

		// Check license
		virtual bool CheckLicense(char * id, char * strValue, int index = -1, int relType = REL_TYPE_EQUAL);
		virtual bool CheckLicense(char * id, int * intValue, int index = -1, int relType = REL_TYPE_EQUAL);
		virtual bool CheckLicense(char * id, tm * tmValue, int index = -1, int relType = REL_TYPE_EQUAL);
};

#endif