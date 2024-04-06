/****************************************************************

   Solution : NovaTend

   Project : z-command-01.dll

   Module : Command.h

   Description :  this module defines interface of
				  class Command

*****************************************************************/

#include "stdafx.h"

#include <SystemBase.h>
#include <SerializationManager.h>
#include <LogWriter.h>


#ifdef ZCOMMAND01_EXPORTS
#define COMMAND_API __declspec(dllexport)
#else
#define COMMAND_API __declspec(dllimport)
#endif

#ifndef COMMAND_H
#define COMMAND_H

/****************************************************************

   Class : Command

   Description : Provides general structure of class 
				of commands execution on server.

*****************************************************************/
class COMMAND_API Command : public SystemBase
{
	protected:

		// Log writer instance
		LogWriter * logWriter;

		// Write message to log-file
		int WriteToLog(char * message);

	public:

		// Constructor
		Command(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~Command(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif