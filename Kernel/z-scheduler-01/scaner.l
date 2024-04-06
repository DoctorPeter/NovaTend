%option noyywrap
%{
#include "SchedulerDef.h"
#include "parser.tab.h"

void * scan_string(char * inputString);
void delete_lex_buffer(void * buffer);

extern YYSTYPE yylval;

%}

DIG	    [0-9]
LIT	    [A-Za-z_]

TIME	{DIG}{DIG}":"{DIG}{DIG}":"{DIG}{DIG}
DATE	{DIG}{DIG}"/"{DIG}{DIG}"/"{DIG}{DIG}{DIG}{DIG}
DAY		"SUN"|"MON"|"TUE"|"WED"|"THU"|"FRI"|"SAT"

name lex

%%

"AND"			{return TOK_AND;}
"OR"			{return TOK_OR;}
"NOT"			{return TOK_NOT;}

"TIME"		{return TOK_TIME_PERIOD_CONDITION;}
"DATE"		{return TOK_DATE_PERIOD_CONDITION;}
"DAY"		{return TOK_DAYS_PERIOD_CONDITION;}
"COUNT"		{return TOK_COUNT_CONDITION;}

[ \t\n\r]+					;

{TIME}					{ int hour, min, sec; 
                          sscanf_s(yytext, "%d:%d:%d", &hour, &min, &sec); 
						  yylval.time_value.tm_hour = hour; 
						  yylval.time_value.tm_min = min; 
						  yylval.time_value.tm_sec = sec; 
						  return TOK_TIME; }

{DATE}					{ int day, mon, year;
                          sscanf_s(yytext, "%d/%d/%d", &mon, &day, &year);
						  yylval.time_value.tm_mon = mon - 1; 
						  yylval.time_value.tm_mday = day; 
						  yylval.time_value.tm_year = year - 1900; 
						  return TOK_DATE; }

{DAY}					{ strupr(yytext);
						  if (!strcmp(yytext, "SUN")) yylval.time_value.tm_wday = 0;
						  else
						  if (!strcmp(yytext, "MON")) yylval.time_value.tm_wday = 1;
						  else
						  if (!strcmp(yytext, "TUE")) yylval.time_value.tm_wday = 2;
						  else
						  if (!strcmp(yytext, "WED")) yylval.time_value.tm_wday = 3;
						  else
						  if (!strcmp(yytext, "THU")) yylval.time_value.tm_wday = 4;
						  else
						  if (!strcmp(yytext, "FRI")) yylval.time_value.tm_wday = 5;
						  else
						  if (!strcmp(yytext, "SAT")) yylval.time_value.tm_wday = 6; 
						  return TOK_DAY;}

{DIG}+					{ yylval.int_value = atoi(yytext); 
                          return TOK_COUNT; }

.			{return yytext[0];}

%%

/*#ifndef YYWRAP
#define YYWRAP
int yywrap( void ) { return 1; }
#endif*/

// Scan string
void * scan_string(char * inputString)
{
	return (void *)yy_scan_string(inputString);
}

// Delete string buffer
void delete_lex_buffer(void * buffer)
{
	yy_delete_buffer((YY_BUFFER_STATE)buffer);
}