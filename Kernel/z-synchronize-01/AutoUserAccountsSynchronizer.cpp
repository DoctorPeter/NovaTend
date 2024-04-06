/****************************************************************

   Solution : NovaTend

   Project : z-synchronize-01.dll

   Module : AutoUserAccountsSynchronizer.cpp

   Description :  this module implements methods of
				  class AutoUserAccountsSynchronizer

*****************************************************************/

#include "stdafx.h"

#include "AutoUserAccountsSynchronizer.h"
#include <SettingsManager.h>
#include <time.h>

// z-synchronize-01.dll definition structure
extern DLL_COMMON_DEFINITION zSynchronizeDllDefinition;


/****************************************************************

   Class : AutoUserAccountsSynchronizer

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
AutoUserAccountsSynchronizer :: AutoUserAccountsSynchronizer(unsigned long dllUserID, LogWriter * logWriter) : ThreadController(dllUserID, &zSynchronizeDllDefinition, INFINITE)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("AutoUserAccountsSynchronizer : constructor");
	#endif

	this -> dllUserID = dllUserID;
}

/****************************************************************

   Class : AutoUserAccountsSynchronizer

   Method : Destructor

*****************************************************************/
AutoUserAccountsSynchronizer :: ~AutoUserAccountsSynchronizer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : destructor");
	#endif
}

/****************************************************************

   Class : AutoUserAccountsSynchronizer

   Method : SynchronizeUserAccounts

   Return : TRUE - if success

   Description : Synchronize user acocunts

*****************************************************************/
bool AutoUserAccountsSynchronizer :: SynchronizeUserAccounts(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SynchronizeUserAccounts. Start");
	#endif

	UserAccountsSynchronizer * userAccountsSynchronizer = new UserAccountsSynchronizer(dllUserID, logWriter);

	bool result = userAccountsSynchronizer -> ForcedSynchronization();

	delete userAccountsSynchronizer;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : SynchronizeUserAccounts. Done");
	#endif

	return result;
}

/****************************************************************

   Class : AutoUserAccountsSynchronizer

   Method : CheckPeriodicFlag

   Returns : TRUE - if success

   Description : Check periodic flag
                 
*****************************************************************/
bool AutoUserAccountsSynchronizer :: CheckPeriodicFlag(void)
{
	SettingsManager * settingsManager = new SettingsManager(zSynchronizeDllDefinition.dllID);

	if (settingsManager -> GetPeriodicSyncOnOffFlag(&periodicallyFlag) != ERROR_SUCCESS)
		periodicallyFlag = false;

	delete settingsManager;

	return periodicallyFlag;
}

/****************************************************************

   Class : AutoUserAccountsSynchronizer

   Method : CheckPeriod

   Returns : TRUE - if success

   Description : Check historian period
                 
*****************************************************************/
bool AutoUserAccountsSynchronizer :: CheckPeriod(void)
{
	// Get synchronization settings 
	SettingsManager * settingsManager = new SettingsManager(zSynchronizeDllDefinition.dllID);
	settingsManager -> GetSyncPeriod(&periodValue);

	char date[STR_VALUE_LEN];
	settingsManager -> GetLastSyncTime(date);

	delete settingsManager;	

	return EvaluatePeriod(periodValue, date);
}

/****************************************************************

   Class : AutoUserAccountsSynchronizer

   Method : EvaluatePeriod

   Parameters :
			Input : 
				period - period code
				data - data string

   Returns : TRUE - if period expired

   Description : Check synchronization period

*****************************************************************/
bool AutoUserAccountsSynchronizer :: EvaluatePeriod(int period, char * data)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
		WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. Start");
	#endif

	try
	{
		int day, mon, year, hour, min, sec;

		// Retrieve date values
		sscanf_s(data, "%d/%d/%d %d:%d:%d", &mon, &day, &year, &hour, &min, &sec);
	
		time_t nowSeconds;
		struct tm inpTime;

		// Get current time
		time (&nowSeconds);
		inpTime = * localtime(&nowSeconds);

		// Set new values
		inpTime.tm_year = year - 1900;
		inpTime.tm_mon = mon - 1;
		inpTime.tm_mday = day;
		inpTime.tm_hour = hour;
		inpTime.tm_min = min;
		inpTime.tm_sec = sec;
		inpTime.tm_isdst = -1;
	    
		// Subtract dates
		double resSeconds = difftime(nowSeconds, mktime(&inpTime));

		// Count period
		double hours = resSeconds / 3600;
		double days = resSeconds / 86400;
		double weeks = resSeconds / 604800;


		// Check period
		switch (period)
		{
			case EVERY_HOUR :
				{
					if (hours >= 1)
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
							WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. One hour expired");
							WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. Done");
						#endif

						return true;
					}
				}

			case EVERY_DAY :
				{
					if (days >= 1)
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
							WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. One day expired");
							WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. Done");
						#endif

						return true;
					}
				}

			case EVERY_WEEK :
				{
					if (weeks >= 1)
					{
						#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
							WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. One week expired");
							WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. Done");
						#endif

						return true;
					}
				}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. Time period not expired");
			WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. Done");
		#endif
	
		return false;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SYNCHRO)
			WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. Can't check period!");
			WriteToLog("UserAccountsSynchronizer : EvaluatePeriod. Done");
		#endif

		return true;
	}
}

/****************************************************************

   Class : AutoUserAccountsSynchronizer

   Method : ControllerEntry

   Description : Thread of auto synchronization

*****************************************************************/
void AutoUserAccountsSynchronizer :: ControllerEntry(void)
{
	SynchronizeUserAccounts();
}

/****************************************************************

   Class : AutoUserAccountsSynchronizer

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  AutoUserAccountsSynchronizer :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}