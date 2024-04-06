/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.exe

   Module : BackgroundTaskManager.cpp

   Description :  this module implements methods of
				  class BackgroundTaskManager

*****************************************************************/

#include "stdafx.h"
#include <stdlib.h>
#include "BackgroundTaskManager.h"


/****************************************************************

		Methods of class TaskDescriptor

*****************************************************************/

/****************************************************************

   Class : TaskDescriptor

   Parameters :
			Input :
				taskID - task ID
				taskType - task type
				status - task status
				
   Method : Constructor
    
*****************************************************************/
TaskDescriptor :: TaskDescriptor(unsigned long long taskID, int taskType ,int status)
{
	this -> taskID = taskID;
	this -> taskType = taskType;
	this -> status = status;
	criticalSection = new CriticalSection();
}

/****************************************************************

   Class : TaskDescriptor

   Parameters :
			Input :
				taskType - task type
				status - task status
				
   Method : Constructor
    
*****************************************************************/
TaskDescriptor :: TaskDescriptor(int taskType, int status)
{
	this -> taskType = taskType;
	this -> status = status;
	criticalSection = new CriticalSection();
}

/****************************************************************

   Class : Destructor

   Method : Destructor
    
*****************************************************************/
TaskDescriptor :: ~TaskDescriptor(void)
{
	delete criticalSection;
}

/****************************************************************

   Class : TaskDescriptor

   Method : Execute

   Description : Execute task
    
*****************************************************************/
int TaskDescriptor :: Execute(void)
{
	// Do something
	Sleep(1000);
	return GetTaskStatus();
}

/****************************************************************

   Class : TaskDescriptor

   Method : GetTaskID

   Returns : task ID value

   Description : Get task ID
    
*****************************************************************/
unsigned long long TaskDescriptor :: GetTaskID(void)
{
	LOCK_SECTION(criticalSection);
	return taskID;
}

/****************************************************************

   Class : TaskDescriptor

   Method : GetTaskID

   Parameters :
			Input :
				ID - task ID

   Returns : task ID value

   Description : Get task ID
    
*****************************************************************/
unsigned long long TaskDescriptor :: SetTaskID(unsigned long long id)
{
	LOCK_SECTION(criticalSection);
	taskID = id;
	return taskID;
}

/****************************************************************

   Class : TaskDescriptor

   Method : Execute

   Returns : task type value

   Description : Get task type
    
*****************************************************************/
int TaskDescriptor :: GetTaskType(void)
{
	LOCK_SECTION(criticalSection);
	return taskType;
}

/****************************************************************

   Class : TaskDescriptor

   Method : GetTaskStatus

   Returns : task status value

   Description : Get task status
    
*****************************************************************/
int TaskDescriptor :: GetTaskStatus(void)
{
	LOCK_SECTION(criticalSection);
	return status;
}

/****************************************************************

   Class : TaskDescriptor

   Method : SetTaskStatus

   Parameters : 
			Input :
				stauts - task status value

   Returns : task status value

   Description : Set task status
    
*****************************************************************/
int TaskDescriptor :: SetTaskStatus(int status)
{
	LOCK_SECTION(criticalSection);
	this -> status = status;
	return this -> status;
}

/****************************************************************

		Methods of class IDGenerator

*****************************************************************/

/****************************************************************

   Class : IDGenerator

   Method : Constructor
    
*****************************************************************/
IDGenerator :: IDGenerator(void)
{
	randomGenerator = new RandomGenerator();
}

/****************************************************************

   Class : IDGenerator

   Method : Destructor
    
*****************************************************************/
IDGenerator :: ~IDGenerator(void)
{
	delete randomGenerator;
}
		
/****************************************************************

   Class : IDGenerator

   Method : Constructor

   Description : Get new ID
    
*****************************************************************/
unsigned long long IDGenerator :: GetID(void)
{
	if (usedIDs.GetSize() >= MAX_TASKS_COUNT)
        return 0;
    
    unsigned long long id;
    
    // trying to lookup free id in map
    while (true) 
	{
		id = randomGenerator -> GenerateRandomValue();
        if (!usedIDs.Has(id)) break;        
    }
    
    usedIDs[id] = 0;
    
    return id;
}
		
/****************************************************************

   Class : IDGenerator

   Method : Constructor

   Parameters :
			Input :
				id - ID value

   Description : Get new ID
    
*****************************************************************/
void IDGenerator :: ReturnID(unsigned long long id)
{
	usedIDs.Erase(id);
}

/****************************************************************

		Methods of class BackgroundTaskManager

*****************************************************************/

/****************************************************************

   Class : BackgroundTaskManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - dll user ID
				dllDefinition - dll definition structure
							
*****************************************************************/
BackgroundTaskManager :: BackgroundTaskManager(unsigned long dllUserID, PDLL_COMMON_DEFINITION dllDefinition) : SystemBase(dllUserID, dllDefinition)
{
	// Create critical section
	criticalSection = new CriticalSection();

	// Set status
	SetStatus(true);

	// Create thread
	backgroundThread = new BackgroundThread(BackgroundTaskManagerWorker, this, 0xFFFFFFFF, true);
}

/****************************************************************

   Class : BackgroundTaskManager

   Method : Destructor
							
*****************************************************************/
BackgroundTaskManager :: ~BackgroundTaskManager(void)
{
	// Set status
	SetStatus(false);

	// Delete thread
	delete backgroundThread;

	// Delete critical section
	delete criticalSection;


	// Free all task deskriptors from input queue
	while (!taskQueue.empty())
	{
		PTASK_DESCRIPTOR pTask = taskQueue.Front();
		taskQueue.Pop();
		delete pTask;
	}

	// Free all task deskriptors from result map
	while (!resultHashmap.Empty())
	{
		unsigned long long ID = resultHashmap(0);
		PTASK_DESCRIPTOR pTask = resultHashmap.Get(ID);
		resultHashmap.Erase(ID);
		delete pTask;
	}
}

/****************************************************************

   Class : ThreadController

   Method : GetStatus

  Returns : status value

   Description : Get status

*****************************************************************/
bool BackgroundTaskManager :: GetStatus(void)
{
	LOCK_SECTION(criticalSection);
	return runStatus;
}

/****************************************************************

   Class : ThreadController

   Method : SetStatus

   Parameters :
			Input : 
				status - status value

   Returns : status value

   Description : Set status

*****************************************************************/
bool BackgroundTaskManager :: SetStatus(bool status)
{
	LOCK_SECTION(criticalSection);
	runStatus = status;
	return runStatus;
}

/****************************************************************

   Class : ThreadController

   Method : BackgroundTaskManagerWorker

   Parameters :
			Input : 
				param - pointer to task manager

   Returns : error code

   Description : Periodically checks all tasks

*****************************************************************/
unsigned long __stdcall BackgroundTaskManager :: BackgroundTaskManagerWorker(void * param)
{
	BackgroundTaskManager * _this = (BackgroundTaskManager *)(param);

	if (_this)
	{
		while (_this -> GetStatus()) 
		{
			// if we have not tasks
			if (_this -> taskQueue.empty()) 
			{
				Sleep(100);
				continue;
			}

			int errorCode;

			// value returned from doTask if finished
			void * pDataResult = NULL;
        
			// Get task from the queue
			PTASK_DESCRIPTOR pTask = _this -> taskQueue.Front();
        
			// Execute task
			if (pTask)
			{
				errorCode = pTask -> Execute();
				Sleep(100);
			}
		
			// Remove task from queue
			_this -> taskQueue.Pop();
        
			// Check that operator complete or not
			if (errorCode  == TAKS_STATE_INPROGRESS) 
			{
				// Save progress  
				_this -> taskQueue.Push(pTask);
			} 
			else 
			{
				// Put result ot the hashmap
				_this -> resultHashmap[pTask -> GetTaskID()] = pTask;
			}
		}

		return TRUE;
	}
	else
		return FALSE;
}

/****************************************************************

   Class : ThreadController

   Method : PushTask

   Parameters :
			Input : 
				pTask - task descriptor instance

   Returns : task ID

   Description : Puts task into the object's queue

*****************************************************************/
unsigned long long BackgroundTaskManager :: PushTask(PTASK_DESCRIPTOR pTask)
{
	if (pTask)
	{
		unsigned long long newID = taskIDGenerator.GetID();
		pTask -> SetTaskID(newID);
		pTask -> SetTaskStatus(TAKS_STATE_INPROGRESS);
		taskQueue.Push(pTask);
		return newID;
	}
	else
		return 0;
}

/****************************************************************

   Class : ThreadController

   Method : PopResult

   Parameters :
			Input : 
				uid - task ID

   Returns : task result descriptor

   Description : Get results from object's hashmap

*****************************************************************/
PTASK_DESCRIPTOR BackgroundTaskManager :: PopTask(unsigned long long uid)
{
	// checks if we have an result
	if (resultHashmap.Has(uid)) 
	{
		// Return ID
		taskIDGenerator.ReturnID(uid);

		// get from hash only value by key and delete it from hash
		return resultHashmap.Pop(uid);
	}

	return NULL;  	
}

/****************************************************************

   Class : ThreadController

   Method : CheckTaskResultStatus

   Parameters :
			Input : 
				uid - task ID

   Returns : task result code

   Description : Check results

*****************************************************************/
int BackgroundTaskManager :: CheckTaskResultStatus(unsigned long long uid)
{
	// checks if we have an result
	if (resultHashmap.Has(uid)) 
		return resultHashmap[uid] -> GetTaskStatus();

	return ERROR_TAKS_NOT_FOUND;
}