/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : SchedulerCondition.h

   Description :  this module defines interface of
				  class SchedulerCondition

*****************************************************************/

#include "stdafx.h"

#include "SchedulerDef.h"

#include <SystemBase.h>
#include <ContentDataDef.h>
#include <LogWriter.h>

#ifdef ZSCHEDULER01_EXPORTS
#define SCHEDULER_CONDITION_API __declspec(dllexport)
#else
#define SCHEDULER_CONDITION_API __declspec(dllimport)
#endif

#ifndef SCHEDULER_CONDITION_H
#define SCHEDULER_CONDITION_H


/****************************************************************

   Class : SchedulerCondition

   Description : Provides general structure of class 
				of conition for scheduler.

*****************************************************************/
class SCHEDULER_CONDITION_API SchedulerCondition : public SystemBase
{
	protected:

		// Root of condition tree
		PSCHEDULE_CONDITION_ITEM root;

		// Bool stack
		bool boolStack[MAX_STACK_SIZE];

		// Bool stack pointer
		int boolStackPointer;

		// Condition string
		char conditionString[PARAM_STR_LEN];

		// Log writer instance
		LogWriter * logWriter;

		// Write message to log-file
		int WriteToLog(char * message);

		// Push value to stack
		bool BoolStackPush(bool value);

		// Pop value from stack
		bool BoolStackPop(void);

		// Delete condition tree
		void DeleteConditionTree(PSCHEDULE_CONDITION_ITEM root);

		// Check condition item
		bool CheckConditionItem(PSCHEDULE_CONDITION_ITEM item);

		// Check time period condition
		bool CheckTimePeriodCondition(PSCHEDULE_CONDITION_ITEM item);

		// Check date period condition
		bool CheckDatePeriodCondition(PSCHEDULE_CONDITION_ITEM item);

		// Check days period condition
		bool CheckDaysPeriodCondition(PSCHEDULE_CONDITION_ITEM item);

		// Check count condition
		bool CheckCountCondition(PSCHEDULE_CONDITION_ITEM item);

		// Check condition tree node
		bool CheckConditionTreeNode(PSCHEDULE_CONDITION_ITEM node);

		// Check condition tree
		bool CheckConditionTree(PSCHEDULE_CONDITION_ITEM root);
		
		// Inc count condition
		void IncCountCondition(PSCHEDULE_CONDITION_ITEM item);

		// Get condition string
		void GetConditionString(PSCHEDULE_CONDITION_ITEM root);

		// Convert node to string
		char * NodeToString(PSCHEDULE_CONDITION_ITEM node, char * buffer);

	public:

		// Constructor
		SchedulerCondition(unsigned long dllUserID, LogWriter * logWriter);

		// Constructor
		SchedulerCondition(unsigned long dllUserID, LogWriter * logWriter, char * conditionString);

		// Desctructor
		virtual ~SchedulerCondition(void);
		
		// Check condition
		bool Check(void);

		// Build condition
		bool BuildCondition(char * conditionString);

		// Clear condition
		void ClearCondition(void);

		// Get condition string
		char * GetConditionString(char * conditionString);

		// Increase count conditions
		void IncCountConditions(void);
};

#endif