/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : ProgramsController.h

   Description :  this module defines interface of
				  class ProgramsController

*****************************************************************/

#include "stdafx.h"

#include <ThreadController.h>
#include <LogWriter.h>
#include <IPCClientsManager.h>

#ifdef ZDESKTOPCMD01_EXPORTS
#define PROGRAMS_CONTROLLER_API __declspec(dllexport)
#else
#define PROGRAMS_CONTROLLER_API __declspec(dllimport)
#endif

#ifndef PROGRAMS_CONTROLLER_H
#define PROGRAMS_CONTROLLER_H

/****************************************************************

   Class : ProgramsController

   Description : Provides general structure of class 
				 of that responsible for management of
				 different programs.

				 This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class PROGRAMS_CONTROLLER_API ProgramsController : public ThreadController
{
	protected:

		// Log writer instance
		LogWriter * logWriter;

		// Client connection manager
		IPCClientsManager * ipcClientsManager;

		// Sender ID
		int senderID;

		//Recipient ID
		int recipientID;

		// user ID
		int userID;

		// Get program list
		PCONTROL_PROGRAM_INFO_CONTAINER_LIST GetProgramList(void);

		// Send check command
		PCONTROL_PROGRAM_INFO_CONTAINER_LIST SendCheckProgamsCommand(PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgListContainer);

		// Delete container
		PCONTROL_PROGRAM_INFO_CONTAINER_LIST DeleteProgramInfoContainerList(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList);

		// Terminate programs
		void TerminatePrograms(PCONTROL_PROGRAM_INFO_CONTAINER_LIST programList);

		// Main rountine
		virtual void ControllerEntry(void);

		// Check periodic flag
		virtual bool CheckPeriodicFlag(void);

	public:

		// Constructor
		ProgramsController(unsigned long dllUserID, LogWriter * logWriter, IPCClientsManager * ipcClientsManager, int senderID, int recipientID);

		// Desctructor
		virtual ~ProgramsController(void);
						
		// Write message to LOG-file
		int WriteToLog(char * message);
};

#endif