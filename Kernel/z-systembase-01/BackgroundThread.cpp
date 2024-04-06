/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : BackgroundThread.cpp

   Description :  this module implements methods of 
				  class BackgroundThread

*****************************************************************/

#include "stdafx.h"
#include "BackgroundThread.h"

/****************************************************************

   Class : BackgroundThread

   Method : Constructor

   Parameters :
			Input :
				pThreadBodyFunc - pointer to thread body rountine
				pBodyFuncParameter - function parameter
				waitTimeOut - default time out value
				runThread - flag for thread auto run

*****************************************************************/
BackgroundThread :: BackgroundThread(PTHREAD_BODY_FUNCTION pThreadBodyFunc, void * pBodyFuncParameter, int waitTimeOut, bool runThread)
{
	this -> pThreadBodyFunc = pThreadBodyFunc;
	this -> pBodyFuncParameter = pBodyFuncParameter;
	this -> waitTimeOut = waitTimeOut;
	
	hThread = 0;
	threadID = 0;
	threadRuning = false;
	threadSuspended = false;

	if (runThread) Run();
}

/****************************************************************

   Class : BackgroundThread

   Method : Destructor

*****************************************************************/
BackgroundThread :: ~BackgroundThread(void)
{
	Stop(this -> waitTimeOut);
}

/****************************************************************

   Class : BackgroundThread

   Method : Run

   Description : Start thread

*****************************************************************/
bool BackgroundThread :: Run(void)
{
	// Check thread status
	if (!threadRuning)
	{
		if ((!hThread) && (!threadID))
		{
			// Check function pointer
			if (pThreadBodyFunc)
			{
				// Create thread
				hThread = CreateThread(NULL, NULL, this -> pThreadBodyFunc, this -> pBodyFuncParameter, NULL, &threadID);

				// Check creation result
				if (hThread) 
					threadRuning = true;
			}
		}
	}

	return threadRuning;
}

/****************************************************************

   Class : BackgroundThread

   Method : Wait

   Parameters :
			Input :
				waitTimeOut - time out value

   Description : Wait for thread to end

*****************************************************************/
bool BackgroundThread :: Stop(int waitTimeOut)
{
	if ((threadRuning) && (hThread) && (threadID))
	{
		// Try wait to end of thread
		if(WaitForSingleObject(hThread, waitTimeOut) == WAIT_OBJECT_0)
		{
			CloseHandle(hThread);
			threadID = 0;
			hThread = 0;
			threadRuning = false;
		}
	}
	
	return threadRuning;
}

/****************************************************************

   Class : BackgroundThread

   Method : Suspend

   Description : Suspend the thread

*****************************************************************/
bool BackgroundThread :: Suspend(void)
{
	if ((!threadSuspended) && (threadRuning) && (SuspendThread(hThread) != -1))
		threadSuspended = true;
	return threadSuspended;
}
		
/****************************************************************

   Class : BackgroundThread

   Method : Resume

   Description : Resume a suspended thread

*****************************************************************/
bool BackgroundThread :: Resume(void)
{
	if ((threadSuspended) && (!threadRuning) && (ResumeThread(hThread) != -1))
		threadSuspended = false;
	return threadSuspended;
}

/****************************************************************

   Class : BackgroundThread

   Method : Kill

   Description : Terminate a thread

*****************************************************************/
bool BackgroundThread :: Kill(void)
{
	if (TerminateThread(hThread, 1))
	{
		threadID = 0;
		hThread = 0;
		threadRuning = false;
	}

	return threadRuning;
}

/****************************************************************

   Class : BackgroundThread

   Method : Runing

   Description : Check for activity

*****************************************************************/
bool BackgroundThread :: Runing(void)
{
	return threadRuning;
}

/****************************************************************

   Class : BackgroundThread

   Method : Suspended

   Description : Check for activity

*****************************************************************/
bool BackgroundThread :: Suspended(void)
{
	return threadSuspended;
}