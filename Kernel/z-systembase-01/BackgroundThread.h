/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : BackgroundThread.h

   Description :  Wrapper for threads management.

*****************************************************************/
#ifdef ZSYSTEMBASE01_EXPORTS
#define BACKGROUND_THREAD_API __declspec(dllexport)
#else
#define BACKGROUND_THREAD_API __declspec(dllimport)
#endif

#ifndef BACKGROUND_THREAD_H
#define BACKGROUND_THREAD_H

// Type definition for thread function
typedef unsigned long (__stdcall * PTHREAD_BODY_FUNCTION)(void * pThreadParameter);

/****************************************************************

   Class : BackgroundThread

   Description : Wrappper of threads management
                
*****************************************************************/
class BACKGROUND_THREAD_API BackgroundThread	
{
	private :
		
		// Thread body function
		PTHREAD_BODY_FUNCTION pThreadBodyFunc;

		// Body function parameter
		void * pBodyFuncParameter;

		// Thread handle
		HANDLE hThread;

		// Thread ID
		DWORD threadID;

		// Indicator of thread activity
		bool threadRuning;

		// Indication of thread suspended
		bool threadSuspended;

		// default time out value
		int waitTimeOut;

	public:

		// Constructor
		BackgroundThread(PTHREAD_BODY_FUNCTION pThreadBodyFunc, void * pBodyFuncParameter, int waitTimeOut = 3000, bool runThread = false);

		// Destructor
		virtual ~BackgroundThread(void);

		// Start thread
		bool Run(void);

		// Wait for thread to end
		bool Stop(int waitTimeOut = 3000); 

		//Suspend the thread
		bool Suspend(void); 
		
		//Resume a suspended thread
		bool Resume(void); 

		//Terminate a thread
		bool Kill(void); 

		// Check for activity
		bool Runing(void);

		// Check for suspend status
		bool Suspended(void);

};

#endif