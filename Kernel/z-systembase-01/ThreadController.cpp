/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.exe

   Module : ThreadController.cpp

   Description :  this module implements methods of
				  class ThreadController

*****************************************************************/

#include "stdafx.h"

#include "ThreadController.h"
#include <time.h>

/****************************************************************

   Class : ThreadController

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - dll user ID
				dllDefinition - dll definition structure
				waitTimeOut - default timeout value
								
*****************************************************************/
ThreadController :: ThreadController(unsigned long dllUserID, PDLL_COMMON_DEFINITION dllDefinition, int waitTimeOut) : SystemBase(dllUserID, dllDefinition)
{
	this -> waitTimeOut = waitTimeOut;
	criticalSection = new CriticalSection();
	controllerStatus = false;
	periodicallyFlag = true;
	periodValue = 0;
}

/****************************************************************

   Class : ThreadController

   Method : Destructor
   
*****************************************************************/
ThreadController :: ~ThreadController(void)
{
	StopThreadController();
	delete criticalSection;
}

/****************************************************************

   Class : ThreadController

   Method : StartThreadController

   Returns : TRUE - if success

   Description : Start controller
                 
*****************************************************************/
bool ThreadController :: StartThreadController(void)
{
	// Check current controller status
	if (!GetThreadControllerStatus())
	{
		// Set status
		SetThreadControllerStatus(true);
	
		// Get current time
		time(&prevTimeSeconds);

		// Create thread
		thread = new BackgroundThread(this -> threadProc, this, this -> waitTimeOut, true);

		// Check thread status
		if (!(thread -> Runing()))
		{
			delete thread;
			SetThreadControllerStatus(false);
		}
	}

	return GetThreadControllerStatus();
}

/****************************************************************

   Class : ThreadController

   Method : StopThreadController

   Returns : TRUE - if success

   Description : Stop controller
                 
*****************************************************************/
bool ThreadController :: StopThreadController(void)
{
	// Check current controller status
	if (!GetThreadControllerStatus())
	{
		// Set controller status
		SetThreadControllerStatus(false);

		// Remove thread
		delete thread;
	}
	
	return GetThreadControllerStatus();
}

/****************************************************************

   Class : ThreadController

   Method : CheckPeriodicFlag

   Returns : TRUE - if success

   Description : Check periodic flag
                 
*****************************************************************/
bool ThreadController :: CheckPeriodicFlag(void)
{
	return periodicallyFlag;
}

/****************************************************************

   Class : ThreadController

   Method : CheckPeriod

   Returns : TRUE - if success

   Description : Check period
                 
*****************************************************************/
bool ThreadController :: CheckPeriod(void)
{
	return (periodValue == 0);
}

/****************************************************************

   Class : ThreadController

   Method : GetHistorianThreadStatus

   Returns : thread status

   Description : Get thread status

*****************************************************************/
bool ThreadController ::  GetThreadControllerStatus(void)
{
	LOCK_SECTION(criticalSection);
	return controllerStatus;
}

/****************************************************************

	Class : ThreadController

	Method : SetHistorianThreadStatus

	Parameters:
			Input:
				status - thread status

	Returns : thread status

	Description : Set thread status

*****************************************************************/
bool ThreadController :: SetThreadControllerStatus(bool status)
{
	LOCK_SECTION(criticalSection);
	controllerStatus = status;
	return status;
}

/****************************************************************

   Class : ThreadController

   Method : threadProc

   Parameters :
			Input : 
				param - pointer to thread controller

   Returns : error code

   Description : Periodically do something

*****************************************************************/
unsigned long __stdcall ThreadController :: threadProc(void * param)
{
	ThreadController * pController = (ThreadController *)param;

	if (pController)
	{
		pController -> Initialize();

		do
		{
			if ((pController -> CheckPeriodicFlag()) && (pController -> CheckPeriod()))
			{
				pController -> ControllerEntry();
			}

			if (pController -> waitTimeOut > 0)
				Sleep(pController -> waitTimeOut);
			else
				Sleep(1000);

		} while (pController -> GetThreadControllerStatus());

		pController -> Finalize();

		return TRUE;
	}
	
	return FALSE;
}

/****************************************************************

   Class : ThreadController

   Method : ControllerEntry

   Description : Do something in thread

*****************************************************************/
void ThreadController :: ControllerEntry(void)
{
	// Do something
}

/****************************************************************

   Class : ThreadController

   Method : Initialize

   Description : Do something in thread

*****************************************************************/
void ThreadController :: Initialize(void)
{
	// Do something
}

/****************************************************************

   Class : ThreadController

   Method : Finalize

   Description : Do something in thread

*****************************************************************/
void ThreadController :: Finalize(void)
{
	// Do something
}


