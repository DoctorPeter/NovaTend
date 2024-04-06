/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : ThreadController.h

   Description :  Controller for threads with function of 
					periodicaly computing.

*****************************************************************/
#include "SystemBase.h"
#include "BackgroundThread.h"

#ifdef ZSYSTEMBASE01_EXPORTS
#define THREAD_CONTROLLER_API __declspec(dllexport)
#else
#define THREAD_CONTROLLER_API __declspec(dllimport)
#endif

#ifndef THREAD_CONTROLLER_H
#define THREAD_CONTROLLER_H

/****************************************************************

   Class : ThreadController

   Description : Wrappper of background threads management
                
*****************************************************************/
class THREAD_CONTROLLER_API ThreadController : public SystemBase
{
	protected:
		
		// Thread critical section 
		CriticalSection * criticalSection;

		// Background thread instance
		BackgroundThread * thread;

		// default time out value
		int waitTimeOut;

		// Controller status
		bool controllerStatus;

		// Previous time value
		time_t prevTimeSeconds;

		// Periodically flag
		bool periodicallyFlag;

		// Period value
		int periodValue;

		// Thread function
		static unsigned long __stdcall threadProc(void * param);

		// Initialize rountine
		virtual void Initialize(void);

		// Main rountine
		virtual void ControllerEntry(void);

		// Finalize rountine
		virtual void Finalize(void);


		// Check periodic flag
		virtual bool CheckPeriodicFlag(void);

		// Check period
		virtual bool CheckPeriod(void);
		
		
		// Get controller status
		bool GetThreadControllerStatus(void);

		// Set controller status
		bool SetThreadControllerStatus(bool status);


	public:

		// Constructor
		ThreadController(unsigned long dllUserID, PDLL_COMMON_DEFINITION dllDefinition, int waitTimeOut = 1000);

		// Destructor
		virtual ~ThreadController(void);


		// Start controller
		bool StartThreadController(void);

		// Stop controller
		bool StopThreadController(void);
		
};

#endif