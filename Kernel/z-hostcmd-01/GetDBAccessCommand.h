/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetDBAccessCommand.h

   Description :  this module defines interface of
				  class GetDBAccessCommand

*****************************************************************/

#include <Command.h>
#include <ResponseValidator.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define GET_DB_ACCESS_CMD_API __declspec(dllexport)
#else
#define GET_DB_ACCESS_CMD_API __declspec(dllimport)
#endif

#ifndef GET_DB_ACCESS_CMD_H
#define GET_DB_ACCESS_CMD_H

/****************************************************************

   Class : GetDBAccessCommand

   Description : Get database connection string

*****************************************************************/
class GET_DB_ACCESS_CMD_API GetDBAccessCommand : public Command
{
	private:
		
		// Content manager instance
		ContentManager * contentManager;

		// Response validator instance
		ResponseValidator * responseValidator;

		// Get DB connection string
		PUSER_DB_ACCESS_INFO GetDBAccess(int userID, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList);

		// Delete symbol boxes list
		PUTF8_STRINGS_MATRIX_LIST DeleteSymbolBoxesList(PUTF8_STRINGS_MATRIX_LIST symbolBoxesList);

	public:

		// Constructor
		GetDBAccessCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetDBAccessCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif