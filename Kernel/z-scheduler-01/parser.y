%{
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include "SchedulerDef.h"

PSCHEDULE_CONDITION_ITEM root = NULL;

PSCHEDULE_CONDITION_ITEM make_condition_node(PSCHEDULE_CONDITION_ITEM left, PSCHEDULE_CONDITION_ITEM right, int type, struct tm * firstTimeValue, struct tm * secondTimeValue, int countMaxValue, int countCurrentValue);
int sintax_parser(char * conditionString, PSCHEDULE_CONDITION_ITEM *node);
int	yyerror (char *);
extern int yylex (void);

%}

%union {
  char str_value[256];
  struct tm time_value;
  int int_value;
  PSCHEDULE_CONDITION_ITEM node;
};


%token TOK_NOT
%token TOK_AND
%token TOK_OR
%token TOK_TIME_PERIOD_CONDITION
%token TOK_DATE_PERIOD_CONDITION
%token TOK_DAYS_PERIOD_CONDITION
%token TOK_COUNT_CONDITION
%token TOK_TIME
%token TOK_DATE
%token TOK_DAY
%token TOK_COUNT

%type <node> condition
%type <int_value> TOK_COUNT
%type <time_value> TOK_TIME
%type <time_value> TOK_DATE
%type <time_value> TOK_DAY
%type <str_value> TOK_NOT
%type <str_value> TOK_AND
%type <str_value> TOK_OR
%type <str_value> TOK_TIME_PERIOD_CONDITION
%type <str_value> TOK_DATE_PERIOD_CONDITION
%type <str_value> TOK_COUNT_CONDITION

%left TOK_NOT TOK_AND TOK_OR
%left UNARY

%%
condition_statement : condition {root = $1;};

condition:
	  TOK_TIME_PERIOD_CONDITION '['TOK_TIME '-' TOK_TIME ']' {$$ = make_condition_node(NULL, NULL, TIME_PERIOD_CONDITION, &($3), &($5), 0, 0);}
	| TOK_DATE_PERIOD_CONDITION '['TOK_DATE '-' TOK_DATE ']' {$$ = make_condition_node(NULL, NULL, DATE_PERIOD_CONDITION, &($3), &($5), 0, 0);}
	| TOK_DAYS_PERIOD_CONDITION '['TOK_DAY '-' TOK_DAY ']'	 {$$ = make_condition_node(NULL, NULL, DAYS_PERIOD_CONDITION, &($3), &($5), 0, 0);}
	| TOK_COUNT_CONDITION '['TOK_COUNT '-' TOK_COUNT ']'	 {$$ = make_condition_node(NULL, NULL, COUNT_CONDITION, NULL, NULL, $5, $3);}
	| TOK_NOT condition %prec UNARY							 {$$ = make_condition_node($2, NULL, NOT_OPERATION, NULL, NULL, 0, 0);}
	| condition TOK_AND condition							 {$$ = make_condition_node($1, $3, AND_OPERATION, NULL, NULL, 0, 0);}
	| condition TOK_OR condition							 {$$ = make_condition_node($1, $3, OR_OPERATION, NULL, NULL, 0, 0);}
	| '(' condition ')' {$$ = $2;}
	;
  

%%


PSCHEDULE_CONDITION_ITEM make_condition_node(PSCHEDULE_CONDITION_ITEM left, PSCHEDULE_CONDITION_ITEM right, int type, struct tm * firstTimeValue, struct tm * secondTimeValue, int countMaxValue, int countCurrentValue)
{
	PSCHEDULE_CONDITION_ITEM new_node = (PSCHEDULE_CONDITION_ITEM)malloc(sizeof(SCHEDULE_CONDITION_ITEM));
	
	if (new_node)
	{
		new_node -> left = left;
		new_node -> right = right;
		new_node -> conditionItemType = type;
		new_node -> countMaxValue = countMaxValue;
		new_node -> countCurrentValue = countCurrentValue;

		time_t curTime = time(0);
		struct tm * curTimeInfo = localtime(&curTime);

		switch(type)
		{
			case TIME_PERIOD_CONDITION :
			{
				curTimeInfo -> tm_hour = firstTimeValue -> tm_hour;
				curTimeInfo -> tm_min = firstTimeValue -> tm_min;
				curTimeInfo -> tm_sec = firstTimeValue -> tm_sec;

				time_t firstTime = mktime(curTimeInfo);
				struct tm * firstTiemInfo = localtime(&firstTime);
				memcpy(&(new_node -> firstTimeValue), firstTiemInfo, sizeof(struct tm));

				curTimeInfo -> tm_hour = secondTimeValue -> tm_hour;
				curTimeInfo -> tm_min = secondTimeValue -> tm_min;
				curTimeInfo -> tm_sec = secondTimeValue -> tm_sec;

				time_t secondTime = mktime(curTimeInfo);
				struct tm * secondTimeInfo = localtime(&secondTime);
				memcpy(&(new_node -> secondTimeValue), secondTimeInfo, sizeof(struct tm));

				break;
			}

			case DATE_PERIOD_CONDITION :
			{
				curTimeInfo -> tm_mon = firstTimeValue -> tm_mon;
				curTimeInfo -> tm_mday = firstTimeValue -> tm_mday;
				curTimeInfo -> tm_year = firstTimeValue -> tm_year;

				time_t firstTime = mktime(curTimeInfo);
				struct tm * firstTiemInfo = localtime(&firstTime);
				memcpy(&(new_node -> firstTimeValue), firstTiemInfo, sizeof(struct tm));

				curTimeInfo -> tm_mon = secondTimeValue -> tm_mon;
				curTimeInfo -> tm_mday = secondTimeValue -> tm_mday;
				curTimeInfo -> tm_year = secondTimeValue -> tm_year;

				time_t secondTime = mktime(curTimeInfo);
				struct tm * secondTimeInfo = localtime(&secondTime);
				memcpy(&(new_node -> secondTimeValue), secondTimeInfo, sizeof(struct tm));

				break;
			}

			case DAYS_PERIOD_CONDITION :
			{
				new_node -> firstTimeValue.tm_wday = firstTimeValue -> tm_wday;
				new_node -> secondTimeValue.tm_wday = secondTimeValue -> tm_wday;
				break;
			}
		}
	}

	return new_node;
}

int yyerror (char	*error_string)
{
 return 0;
}

extern void * scan_string(char * inputString);
extern void delete_lex_buffer(void * buffer);

int sintax_parser(char * conditionString, PSCHEDULE_CONDITION_ITEM *node)
{
 int res;
 void * str_buffer = scan_string(conditionString);
 res = yyparse();
 *node = root;
 delete_lex_buffer(str_buffer);
 return res;
}
