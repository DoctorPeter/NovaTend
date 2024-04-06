/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : GetContentCommand.h

   Description :  this module defines interface of
				  class GetContentCommand

*****************************************************************/

#include <Command.h>
#include <LicenseManager.h>
#include <ContentManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define GET_CONTENT_CMD_API __declspec(dllexport)
#else
#define GET_CONTENT_CMD_API __declspec(dllimport)
#endif

#ifndef GET_CONTENT_CMD_H
#define GET_CONTENT_CMD_H

/****************************************************************

   Class : GetContentCommand

   Description : Get user content structure.

*****************************************************************/
class GET_CONTENT_CMD_API GetContentCommand : public Command
{
	private:
		
		// Content manager instance
		ContentManager * contentManager;

		// License manager instance
		LicenseManager * licenseManager;


		// Get default content
		PPRESET_CONTAINER GetUserContent(void);

		// Get conect for some user
		PPRESET_CONTAINER GetUserContent(char * compName, int userID, int osID);

		// Is it first sign in for today for this user?
		bool FirstUserSignInToday(char * date);

		// Delete user content
		PPRESET_CONTAINER DeleteContent(PPRESET_CONTAINER content);

	public:

		// Constructor
		GetContentCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetContentCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif