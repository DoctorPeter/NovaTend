/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : BackgroundTaskManager.h

   Description :  Manager of task that working in the backgound.

*****************************************************************/
#include "SystemBase.h"
#include "BackgroundThread.h"
#include "SpecialDataStructures.h"
#include "RandomGenerator.h"

#ifdef ZSYSTEMBASE01_EXPORTS
#define BACKGROUND_TASK_MANAGER_API __declspec(dllexport)
#else
#define BACKGROUND_TASK_MANAGER_API __declspec(dllimport)
#endif

#ifndef BACKGROUND_TASK_MANAGER_H
#define BACKGROUND_TASK_MANAGER_H

// Tasks states
#define TAKS_STATE_INPROGRESS			 1
#define TAKS_STATE_FINISHED				 2
#define ERROR_TAKS_RESULT_OK			 3
#define ERROR_TAKS_RESULT_FAIL			 4
#define ERROR_TAKS_NOT_FOUND			 5

// Maximum count of tasks
#define MAX_TASKS_COUNT					4096				

/****************************************************************

   Class : TaskDescriptor

   Description : Descriptor of task
                
*****************************************************************/
class BACKGROUND_TASK_MANAGER_API TaskDescriptor
{
	protected :
		
		// Critical section
        CriticalSection * criticalSection; 

		// Task ID
		unsigned long long taskID;

		// Task type
		int taskType;

		// Task sttus
		int status;

	public :

		// Constructor
		TaskDescriptor(int taskType, int status = TAKS_STATE_INPROGRESS);

		// Constructor
		TaskDescriptor(unsigned long long taskID, int taskType, int status);

		// Destructor
		virtual ~TaskDescriptor(void);

		// Execute task
		virtual int Execute(void);

		// Get task ID
		unsigned long long GetTaskID(void);

		// Set task ID
		unsigned long long SetTaskID(unsigned long long id);

		// Get task type
		int GetTaskType(void);

		// Get task status
		int GetTaskStatus(void);

		// Set task status
		int SetTaskStatus(int status);
};

// Pointer to task descriptor object
#define PTASK_DESCRIPTOR TaskDescriptor *

/****************************************************************

   Class : IDGenerator

   Description : Gererator of unique ID
                
*****************************************************************/
class BACKGROUND_TASK_MANAGER_API IDGenerator
{
	private:
		
		// Generator of random numbers
		RandomGenerator * randomGenerator;

		// List of used ID's
		SafeMap<unsigned long long, char> usedIDs;

	public:

		// Constructor
		IDGenerator(void);
		
		// Destructor
		virtual ~IDGenerator(void);

		// Get new ID
		unsigned long long GetID(void);
		
		// Delete ID from used list
		void ReturnID(unsigned long long id);
};

/****************************************************************

   Class : BackgroundTaskManager

   Description : Manager of backgound tasks
                
*****************************************************************/
class BACKGROUND_TASK_MANAGER_API BackgroundTaskManager	: public SystemBase
{
	protected:

		// Critical section
        CriticalSection * criticalSection; 

		// Thread instance
		BackgroundThread * backgroundThread;

		// Task ID generator
		IDGenerator taskIDGenerator;

		// Thread safe queue to store tasks
		SafeQueue<PTASK_DESCRIPTOR> taskQueue;

		// Tasks result hashmap
		SafeMap<unsigned long long, PTASK_DESCRIPTOR> resultHashmap;
		
		// Thread function
		static unsigned long __stdcall BackgroundTaskManagerWorker(void * param);

		// Generate task ID		
		unsigned long long GenerateTaskID(void);

		// Status
		bool runStatus;

		// Get status
		bool GetStatus(void);

		// Set status
		bool SetStatus(bool status);

	public:

		// Constructor
		BackgroundTaskManager(unsigned long dllUserID, PDLL_COMMON_DEFINITION dllDefinition);

		// Destructor
		virtual ~BackgroundTaskManager(void);

		// Puts task into the object's queue
		unsigned long long PushTask(PTASK_DESCRIPTOR pTask);

	    // Get results from object's hashmap
		PTASK_DESCRIPTOR PopTask(unsigned long long uid);

		// Check task result status
		int CheckTaskResultStatus(unsigned long long uid);
};

#endif