/****************************************************************

   Solution : NovaTend

   Project : z-synchronize-01.dll

   Module : AutoUserAccountsSynchronizer.h

   Description :  this module defines interface of
				  class AutoUserAccountsSynchronizer

*****************************************************************/

#include <ThreadController.h>
#include <LogWriter.h>
#include "UserAccountsSynchronizer.h"

#ifdef ZSYNCHRONIZE01_EXPORTS
#define SYNCHRONIZER_API __declspec(dllexport)
#else
#define SYNCHRONIZER_API __declspec(dllimport)
#endif


#ifndef AUTO_USER_ACCOUNTS_SYNCHRONIZER_H
#define AUTO_USER_ACCOUNTS_SYNCHRONIZER_H

// Periods definition
#define EVERY_HOUR		0
#define EVERY_DAY		1
#define EVERY_WEEK		2

/****************************************************************

   Class : AutoUserAccountsSynchronizer

   Description : synchronize user accounts

*****************************************************************/
class SYNCHRONIZER_API AutoUserAccountsSynchronizer : public ThreadController
{
	protected:

		// Log writer instance
		LogWriter * logWriter;

		// Dll user ID copy
		int dllUserID;

		// Main rountine
		virtual void ControllerEntry(void);

		// Check periodic flag
		virtual bool CheckPeriodicFlag(void);

		// Check period
		virtual bool CheckPeriod(void);

		// Check synchronization period
		bool EvaluatePeriod(int period, char * data);

		// Synchronize user acocunts
		bool SynchronizeUserAccounts(void);

	public:
		
		// Constructor
		AutoUserAccountsSynchronizer(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~AutoUserAccountsSynchronizer(void);

		// Write message to Log-file
		int WriteToLog(char * message);
};

#endif