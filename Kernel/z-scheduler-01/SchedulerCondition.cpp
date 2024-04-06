/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : SchedulerCondition.cpp

   Description :  this module implements methods of
				  class SchedulerCondition

*****************************************************************/

#include "stdafx.h"
#include "SchedulerCondition.h"
#include "parser.h"

#include <stdlib.h>

// z-scheduler-01.dll definition structure
extern DLL_COMMON_DEFINITION zSchedulerDllDefinition;
 
// Parser guard
extern CriticalSection * parserGuard;

#pragma region Constructing

/****************************************************************

   Class : SchedulerCondition

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
SchedulerCondition :: SchedulerCondition(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zSchedulerDllDefinition)
{
	this -> logWriter = logWriter;
	root = NULL;
	boolStackPointer = -1;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : constructor");
	#endif
}

/****************************************************************

   Class : SchedulerCondition

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				conditionString - condition string

*****************************************************************/
SchedulerCondition :: SchedulerCondition(unsigned long dllUserID, LogWriter * logWriter, char * conditionString) : SystemBase(dllUserID, &zSchedulerDllDefinition)
{
	this -> logWriter = logWriter;
	root = NULL;
	boolStackPointer = -1;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : constructor");
	#endif

	BuildCondition(conditionString);
}


/****************************************************************

   Class : SchedulerCondition

   Method : Destructor

*****************************************************************/
SchedulerCondition :: ~SchedulerCondition(void)
{
	ClearCondition();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : destructor");
	#endif
}

#pragma endregion

#pragma region Condtion tree

/****************************************************************

   Class : SchedulerCondition

   Method : DeleteConditionTree

   Parameters:
			Input:
				root - pointer to condition tree root

   Description : Delete condition tree

*****************************************************************/
void SchedulerCondition :: DeleteConditionTree(PSCHEDULE_CONDITION_ITEM root)
{
	if (root)
	{
		DeleteConditionTree(root -> left);
		DeleteConditionTree(root -> right);
		free(root);
	}
}

/****************************************************************

   Class : SchedulerCondition

   Method : GetConditionString

   Parameters:
			Input:
				node - pointer to condition tree node
			
			Output:
				buffer - output string

   Returns : condition tree node as string
   
   Description : Convert node to string

*****************************************************************/
char * SchedulerCondition :: NodeToString(PSCHEDULE_CONDITION_ITEM node, char * buffer)
{
	// Check input data
	if ((node) && (buffer))
	{
		// Set buffer to empty string
		buffer[0] = 0;

		// Check node type
		switch (node -> conditionItemType)
		{
			// Put operator NOT
			case NOT_OPERATION :
			{
				strcat(buffer, "NOT");
				break;
			}
 
			// Put operator AND
			case AND_OPERATION :
			{
				strcat(buffer, "AND");
				break;
			}

			// Put operator OR
			case OR_OPERATION :
			{
				strcat(buffer, "OR");
				break;
			}

			// Put time period condition
			case TIME_PERIOD_CONDITION :
			{
				char firstTimeBuffer[STR_VALUE_LEN];
				char secondTimeBuffer[STR_VALUE_LEN];
				strftime(firstTimeBuffer, STR_VALUE_LEN, "%H:%M:%S", &(node -> firstTimeValue));
				strftime(secondTimeBuffer, STR_VALUE_LEN, "%H:%M:%S", &(node -> secondTimeValue));

				strcat(buffer, "TIME[");
				strcat(buffer, firstTimeBuffer);
				strcat(buffer, "-");
				strcat(buffer, secondTimeBuffer);
				strcat(buffer, "]");

				break;
			}

			// Put date period condition
			case DATE_PERIOD_CONDITION :
			{
				char firstTimeBuffer[STR_VALUE_LEN];
				char secondTimeBuffer[STR_VALUE_LEN];
				strftime(firstTimeBuffer, STR_VALUE_LEN, "%m//%d//%Y", &(node -> firstTimeValue));
				strftime(secondTimeBuffer, STR_VALUE_LEN, "%m//%d//%Y", &(node -> secondTimeValue));

				strcat(buffer, "DATE[");
				strcat(buffer, firstTimeBuffer);
				strcat(buffer, "-");
				strcat(buffer, secondTimeBuffer);
				strcat(buffer, "]");

				break;
			}

			// Put days of week period condition
			case DAYS_PERIOD_CONDITION :
			{
				char firstTimeBuffer[STR_VALUE_LEN];
				char secondTimeBuffer[STR_VALUE_LEN];
				strftime(firstTimeBuffer, STR_VALUE_LEN, "%a", &(node -> firstTimeValue));
				strftime(secondTimeBuffer, STR_VALUE_LEN, "%a", &(node -> secondTimeValue));

				strcat(buffer, "DAY[");
				strcat(buffer, firstTimeBuffer);
				strcat(buffer, "-");
				strcat(buffer, secondTimeBuffer);
				strcat(buffer, "]");
				break;
			}

			// Put count condition
			case COUNT_CONDITION :
			{
				char currValueBuffer[STR_VALUE_LEN];
				char maxValueBuffer[STR_VALUE_LEN];
				itoa(node -> countCurrentValue, currValueBuffer, 10);
				itoa(node -> countMaxValue, maxValueBuffer, 10);

				strcat(buffer, "COUNT[");
				strcat(buffer, currValueBuffer);
				strcat(buffer, "-");
				strcat(buffer, maxValueBuffer);
				strcat(buffer, "]");
				break;
			}
		}
	}

	return buffer;
}

/****************************************************************

   Class : SchedulerCondition

   Method : GetConditionString

   Parameters:
			Input:
				root - pointer to root of condition tree
   
   Description : Get condition string from condition tree

*****************************************************************/
void SchedulerCondition :: GetConditionString(PSCHEDULE_CONDITION_ITEM root)
{
	if (root)
	{
		// Temporary buffer
		char tmpBufferString[PARAM_STR_LEN] = "";


		// Put bracket
		strcat(conditionString, "(");

		if (root -> conditionItemType == NOT_OPERATION)
		{
			// Convert node to string
			NodeToString(root, tmpBufferString);
		
			// Cancatenate to condition string
			strcat(conditionString, tmpBufferString);

			// Left subtree
			GetConditionString(root -> left);

			// Right subtree
			GetConditionString(root -> right);
		}
		else
		{
			// Left subtree
			GetConditionString(root -> left);
				
			// Convert node to string
			NodeToString(root, tmpBufferString);
		
			// Cancatenate to condition string
			strcat(conditionString, tmpBufferString);

			// Right subtree
			GetConditionString(root -> right);
		}

		// Put breacket
		strcat(conditionString, ")");
	}
}

/****************************************************************

   Class : SchedulerCondition

   Method : IncCountCondition

   Parameters:
			Input:
				item - pointer to condition item structure

   Description : Increase count condition item

*****************************************************************/
void SchedulerCondition :: IncCountCondition(PSCHEDULE_CONDITION_ITEM item)
{
	if (item)
	{
		IncCountCondition(item -> left);
		IncCountCondition(item -> right);

		// Increase current count value
		if ((item -> conditionItemType == COUNT_CONDITION) && (item -> countCurrentValue <= item -> countMaxValue))
		{
			item -> countCurrentValue++;
		}
	}
}

/****************************************************************

   Class : SchedulerCondition

   Method : CheckConditionItem

   Parameters:
			Input:
				item - pointer to condition item structure

   Return : condition checking result

   Description : Check condition

*****************************************************************/
bool SchedulerCondition :: CheckConditionItem(PSCHEDULE_CONDITION_ITEM item)
{
	if (item)
	{
		switch(item -> conditionItemType)
		{
			case TIME_PERIOD_CONDITION :
			{
				return CheckTimePeriodCondition(item);
			}

			case DATE_PERIOD_CONDITION :
			{
				return CheckDatePeriodCondition(item);
			}

			case DAYS_PERIOD_CONDITION :
			{
				return CheckDaysPeriodCondition(item);
			}

			case COUNT_CONDITION :
			{
				return CheckCountCondition(item);
			}
		}
	}

	return false;
}

/****************************************************************

   Class : SchedulerCondition

   Method : CheckTimePeriodCondition

   Parameters:
			Input:
				item - pointer to condition item structure

   Return : condition checking result

   Description : Check time period condition

*****************************************************************/
bool SchedulerCondition :: CheckTimePeriodCondition(PSCHEDULE_CONDITION_ITEM item)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : CheckTimePeriodCondition. Start");
	#endif

	bool result = false;

	if (item)
	{
		// Get current time
		time_t currentTime = time(NULL);

		// Convert data from condition item
		time_t firstTime = mktime(&(item -> firstTimeValue));
		time_t secondTime = mktime(&(item -> secondTimeValue));

		// Check condition
		if ((currentTime == firstTime) || (currentTime == secondTime) ||
			((difftime(currentTime, firstTime) > 0) && (difftime(secondTime, currentTime)) > 0))
		{
			result = true;
		}
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		if (result)
			WriteToLog("SchedulerCondition : CheckTimePeriodCondition. Result = TRUE");
		else
			WriteToLog("SchedulerCondition : CheckTimePeriodCondition. Result = FALSE");

		WriteToLog("SchedulerCondition : CheckTimePeriodCondition. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SchedulerCondition

   Method : CheckDatePeriodCondition

   Parameters:
			Input:
				item - pointer to condition item structure

   Return : condition checking result

   Description : Check date period condition

*****************************************************************/
bool SchedulerCondition :: CheckDatePeriodCondition(PSCHEDULE_CONDITION_ITEM item)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : CheckDatePeriodCondition. Start");
	#endif

	bool result = CheckTimePeriodCondition(item);
			
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : CheckDatePeriodCondition. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SchedulerCondition

   Method : CheckDaysPeriodCondition

   Parameters:
			Input:
				item - pointer to condition item structure

   Return : condition checking result

   Description : Check days period condition

*****************************************************************/
bool SchedulerCondition :: CheckDaysPeriodCondition(PSCHEDULE_CONDITION_ITEM item)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : CheckDaysPeriodCondition. Start");
	#endif

	bool result = false;

	if (item)
	{
		// Get current time
		time_t currentTime = time(NULL);
		
		// Check days of week
		if ((localtime(&currentTime) -> tm_wday >= item -> firstTimeValue.tm_wday) && 
			(localtime(&currentTime) -> tm_wday <= item -> secondTimeValue.tm_wday))
		{
			result = true;
		}
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		if (result)
			WriteToLog("SchedulerCondition : CheckDaysPeriodCondition. Result = TRUE");
		else
			WriteToLog("SchedulerCondition : CheckDaysPeriodCondition. Result = FALSE");

		WriteToLog("SchedulerCondition : CheckDaysPeriodCondition. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SchedulerCondition

   Method : CheckCountCondition

   Parameters:
			Input:
				item - pointer to condition item structure

   Return : condition checking result

   Description : Check count condition

*****************************************************************/
bool SchedulerCondition :: CheckCountCondition(PSCHEDULE_CONDITION_ITEM item)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : CheckCountCondition. Start");
	#endif

	bool result = false;

	if (item)
	{
		// Check count value
		if ((item -> countCurrentValue + 1) <= item -> countMaxValue)
		{
			result = true;
		}
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		if (result)
			WriteToLog("SchedulerCondition : CheckCountCondition. Result = TRUE");
		else
			WriteToLog("SchedulerCondition : CheckCountCondition. Result = FALSE");

		WriteToLog("SchedulerCondition : CheckCountCondition. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SchedulerCondition

   Method : CheckConditionTreeNode

   Parameters:
			Input:
				node - pointer to condition item structure

   Return : condition checking result

   Description : Check condition tree node

*****************************************************************/
bool SchedulerCondition :: CheckConditionTreeNode(PSCHEDULE_CONDITION_ITEM node)
{
	bool result = false;

	if (node)
	{
		// Check condition item
		if ((node -> conditionItemType >= TIME_PERIOD_CONDITION) &&
			(node -> conditionItemType <= COUNT_CONDITION))
		{
			result = BoolStackPush(CheckConditionItem(node));
		}
		else
		{
			// Make logical operations
			switch(node -> conditionItemType)
			{
				case NOT_OPERATION :
				{
					result = BoolStackPush(!BoolStackPop());
					break;
				}
 
				case AND_OPERATION :
				{
					result = BoolStackPush(BoolStackPop() && BoolStackPop());
					break;
				}

				case OR_OPERATION :
				{
					result = BoolStackPush(BoolStackPop() || BoolStackPop());
					break;
				}
			}
		}
	}

	return result;
}

/****************************************************************

   Class : SchedulerCondition

   Method : CheckConditionTree

   Parameters:
			Input:
				root - pointer to condition item structure

   Return : condition checking result

   Description : Check condition tree 

*****************************************************************/
bool SchedulerCondition :: CheckConditionTree(PSCHEDULE_CONDITION_ITEM root)
{
	if (root)
	{
		CheckConditionTree(root -> left);
		CheckConditionTree(root -> right);
		return CheckConditionTreeNode(root);
	}
	else
		return false;
}

#pragma endregion

#pragma region Condition

/****************************************************************

   Class : SchedulerCondition

   Method : Check

   Return : condition checking result

   Description : Check condition

*****************************************************************/
bool SchedulerCondition :: Check(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : Check. Start");
	#endif

	bool result = CheckConditionTree(root);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : Check. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SchedulerCondition

   Method : BuildCondition

   Parameters:
			Input:
				conditionString - text of condition

   Return : condition tree creation result (TRUE - if success)

   Description : Build condition (parsing)

*****************************************************************/
bool SchedulerCondition :: BuildCondition(char * conditionString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : BuildCondition. Start");
	#endif

	bool result = false;
	ClearCondition();
    
	if (conditionString)
	{
		strcpy(this -> conditionString, conditionString);
		strupr(this -> conditionString);

		LOCK_SECTION(parserGuard);

		int parserResult = sintax_parser(this -> conditionString, &root);

		if (parserResult == 0)
		{
			result = true;
		}
		else
		if (parserResult == 1)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
				WriteToLog("SchedulerCondition : BuildCondition. Sintax error!");
			#endif

			ClearCondition();
		}
		else
		if (parserResult == 2)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
				WriteToLog("SchedulerCondition : BuildCondition. Memory exhaustion!");
			#endif

			ClearCondition();
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : BuildCondition. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SchedulerCondition

   Method : ClearCondition

   Description : Remove current condition tree

*****************************************************************/
void SchedulerCondition :: ClearCondition(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : ClearCondition. Start");
	#endif

	DeleteConditionTree(root);
	root = NULL;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : ClearCondition. Done");
	#endif
}

/****************************************************************

   Class : SchedulerCondition

   Method : GetConditionString

   Parameters:
			Output:
				conditionString - text of condition

   Return : condition string

   Description : Get condition string from condition tree

*****************************************************************/
char * SchedulerCondition :: GetConditionString(char * conditionString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : GetConditionString. Start");
	#endif
			
    if (conditionString)
	{
		// Clear condition string
		this -> conditionString[0] = 0;

		// Get condition string
		GetConditionString(root);
		
		// Copy to output buffer
		strupr(this -> conditionString);
		strcpy(conditionString, this -> conditionString);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			WriteToLog("SchedulerCondition : GetConditionString. Done");
		#endif

		return conditionString;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
			WriteToLog("SchedulerCondition : GetConditionString. Wrong input parameter!");
			WriteToLog("SchedulerCondition : GetConditionString. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SchedulerCondition

   Method : IncCountCondition

   Description : Increase count condition item

*****************************************************************/
void SchedulerCondition :: IncCountConditions(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCHEDULER)
		WriteToLog("SchedulerCondition : IncCountConditions");
	#endif
   
	IncCountCondition(root);
}

#pragma endregion

#pragma region Stack

/****************************************************************

   Class : SchedulerCondition

   Method : BoolStackPush

   Parameters:
			Input:
				value - bool value

   Return : last pushed value

   Description : Push value to stack

*****************************************************************/
bool SchedulerCondition :: BoolStackPush(bool value)
{
	if ((boolStackPointer + 1) < MAX_STACK_SIZE)
	{
		boolStack[++boolStackPointer] = value;
		return boolStack[boolStackPointer];
	}
	else 
		return false;
}

/****************************************************************

   Class : SchedulerCondition

   Method : BoolStackPop

   Return : retrieved value

   Description : Pop value from stack

*****************************************************************/
bool SchedulerCondition :: BoolStackPop(void)
{
	if ((boolStackPointer >= 0) && (boolStackPointer < MAX_STACK_SIZE))
	{
		return boolStack[boolStackPointer--];
	}
	else
		return false;
}

#pragma endregion

#pragma region LOG

/****************************************************************

   Class : SchedulerCondition

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int SchedulerCondition :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion