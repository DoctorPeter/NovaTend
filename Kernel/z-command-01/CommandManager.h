/****************************************************************

   Solution : NovaTend

   Project : z-command-01.dll

   Module : CommandManager.h

   Description :  this module defines interface of
				  class CommandManager

*****************************************************************/

#include "stdafx.h"

#include <SystemBase.h>
#include <SerializationManager.h>
#include <LogWriter.h>
#include <LicenseDataDef.h>


#include "Command.h"

#ifdef ZCOMMAND01_EXPORTS
#define COMMAND_MANAGER_API __declspec(dllexport)
#else
#define COMMAND_MANAGER_API __declspec(dllimport)
#endif

#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

/****************************************************************

   Class : CommandManager

   Description : Provides general structure of class 
				of commands execution management.

*****************************************************************/
class COMMAND_MANAGER_API CommandManager : public SystemBase
{
	protected:
				
		// Write message to LOG-file
		int WriteToLog(char * message);

		// Generate command
		virtual Command * GenerateCommand(int commandType);

		// Get command request
		PCOMMAND_REQUEST_RESPONSE GetCommandRequest(char * dataBuffer, int size);

	public:

		// Log writer instance
		LogWriter * logWriter;

		// Descriton of the client (sender of requests)
		CLIENT_DESCRIPTION clientDescr;

		// Description of the server (request processor)
		SERVER_DESCRIPTION serverDescr;

		// Constructor
		CommandManager(unsigned long dllUserID, LogWriter * logWriter);

		// Copy constructor
		CommandManager(const CommandManager &src);

		// Desctructor
		virtual ~CommandManager(void);

		// Clone object
		virtual CommandManager * Clone(void);

		// Get command type
		unsigned int GetCommandCode(char * dataBuffer);

		// Get command type
		unsigned int GetCommandCode(PCOMMAND_REQUEST_RESPONSE cmdRequest);
		
		// Check license
		virtual bool CheckLicense(char * id, char * strValue, int index = -1, int relType = REL_TYPE_EQUAL);
		virtual bool CheckLicense(char * id, int * intValue, int index = -1, int relType = REL_TYPE_EQUAL);
		virtual bool CheckLicense(char * id, tm * tmValue, int index = -1, int relType = REL_TYPE_EQUAL);

		// Execute command
		virtual char * ExecuteCommand(char * requestPackage, int requestSize, int * responseSize);
				
		// Execute command
		virtual PCOMMAND_REQUEST_RESPONSE ExecuteCommand(PCOMMAND_REQUEST_RESPONSE cmdRequest);

		// Create back connection
		virtual PCOMMAND_REQUEST_RESPONSE CreateBackConnection(PCOMMAND_REQUEST_RESPONSE cmdRequest);
				
		// Redirect request
		virtual PCOMMAND_REQUEST_RESPONSE RedirectRequest(PCOMMAND_REQUEST_RESPONSE cmdRequest);
};

#endif