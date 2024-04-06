/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : SchedulerDef.h

   Description :  this module defines general data types
                  and restrictions for scheduler work

*****************************************************************/
#include <time.h>

#ifndef SCHEDULER_DEF_H
#define SCHEDULER_DEF_H

// Maximim length of parameters string
#define PARAM_STR_LEN		256


// Condition types

// Time period condition. Example [17:00:00 - 18:00:00]
#define TIME_PERIOD_CONDITION	4

// Date period condition. Example [08/01/2015 - 08/30/2015]
#define DATE_PERIOD_CONDITION	5

// Day period condition. Example [MON - FRI]
#define DAYS_PERIOD_CONDITION	6

// Count condition (Current - Maximum). Example [0 - 10]
#define COUNT_CONDITION			7


// Logical operations types

// Operation NOT
#define NOT_OPERATION			1

// Operation AND
#define AND_OPERATION			2

// Operation OR
#define OR_OPERATION			3

// Stack size
#define MAX_STACK_SIZE			256

// Structute of condition item
typedef struct scheduleConditionItem
{
	// Item type
	int conditionItemType;

	// First date-time structure
	struct tm firstTimeValue;

	// Second date-time structure
	struct tm secondTimeValue;
	
	// Count maximum value
	int countMaxValue;

	// Count current value
	int countCurrentValue;

	// Left child
	struct scheduleConditionItem * left;

	// Right child
	struct scheduleConditionItem * right;

} SCHEDULE_CONDITION_ITEM, *PSCHEDULE_CONDITION_ITEM;

// Action types

// Allow
#define ALLOW_ACTION		1

// Deny
#define DENY_ACTION			2

// Ignore
#define IGNORE_ACTION		4

// Restrict
#define RESTRICT_ACTION		8


// Function types

// Log in
#define LOG_IN_FUNCTION				1

// Post log in
#define POST_LOG_IN_FUNCTION		2

// Education
#define EDUCATION_FUNCTION			3

// Notification
#define NOTIFICATION_FUNCTION		4

// Legal disclaimer
#define LEGAL_DISCLAIMER_FUNCTION	5

// Client machine monitoring
#define MONITORING_FUNCTION			6

// Progm running control
#define PROGRAM_CONTROL_FUNCTION	7

#endif
