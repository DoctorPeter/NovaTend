/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : PostLoginManager.h

   Description :  this module defines interface of
				  class PostLoginManager

				  This class is designed only for the 
				  Windows operating systems.

*****************************************************************/

#include "stdafx.h"
#include <ThreadController.h>
#include <LogWriter.h>

#ifdef ZHUBCMD01_EXPORTS
#define POST_LOGIN_MANAGER_API __declspec(dllexport)
#else
#define POST_LOGIN_MANAGER_API __declspec(dllimport)
#endif

#ifndef POST_LOGIN_MANAGER_H
#define POST_LOGIN_MANAGER_H

/****************************************************************

   Class : PostLoginManager

   Description : Provides general structure of class 
				 of that responsible for management of
				 Post Login process.

*****************************************************************/
class POST_LOGIN_MANAGER_API PostLoginManager : public ThreadController
{
	private:

		// Log writer instance
		LogWriter * logWriter;

		// Post login path
		char postLoginPath[MAX_PATH];

	protected:

		// Main rountine
		virtual void ControllerEntry(void);

		// Check periodic flag
		virtual bool CheckPeriodicFlag(void);

		// Check period
		virtual bool CheckPeriod(void);

		// Run post login process
		bool RunPostLoginProcess(void);

	public:

		// Constructor
		PostLoginManager(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~PostLoginManager(void);
		
		// Write message to LOG-file
		int WriteToLog(char * message);
};

#endif