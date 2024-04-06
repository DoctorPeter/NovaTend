%namespace  ScheduleRules        
%using System.Globalization;
%using QUT.Gppg;

%visibility public
%scannertype Scanner
%scanbasetype ScanBase
%tokentype Tokens          

%option codePage:65001 out:ScheduleRuleScanner.cs

DIG	    [0-9]
LIT	    [A-Za-z_]

TIME	{DIG}{DIG}":"{DIG}{DIG}":"{DIG}{DIG}
DATE	{DIG}{DIG}"/"{DIG}{DIG}"/"{DIG}{DIG}{DIG}{DIG}
DAY		"SUN"|"MON"|"TUE"|"WED"|"THU"|"FRI"|"SAT"

%%

"AND"			{return (int)Tokens.TOK_AND;}
"OR"			{return (int)Tokens.TOK_OR;}
"NOT"			{return (int)Tokens.TOK_NOT;}

"TIME"		{return (int)Tokens.TOK_TIME_PERIOD_CONDITION;}
"DATE"		{return (int)Tokens.TOK_DATE_PERIOD_CONDITION;}
"DAY"		{return (int)Tokens.TOK_DAYS_PERIOD_CONDITION;}
"COUNT"		{return (int)Tokens.TOK_COUNT_CONDITION;}
"["			{return (int)Tokens.TOK_OPEN_SQUARE_BREAKET;}
"]"			{return (int)Tokens.TOK_CLOSE_SQUARE_BREAKET;}
"("			{return (int)Tokens.TOK_OPEN_ROUND_BREAKET;}
")"			{return (int)Tokens.TOK_CLOSE_ROUND_BREAKET;}
"-"			{return (int)Tokens.TOK_MINUS;}


[ \t\n\r]+					;

{TIME}					{ DateTime.TryParseExact(yytext, "HH:mm:ss", CultureInfo.InvariantCulture, DateTimeStyles.None, out yylval.dateTimeValue);
						  return (int)Tokens.TOK_TIME; }

{DATE}					{ DateTime.TryParseExact(yytext, @"MM/dd/yyyy", CultureInfo.InvariantCulture, DateTimeStyles.None, out yylval.dateTimeValue);
						  return (int)Tokens.TOK_DATE; }

{DAY}					{ yytext.ToUpper();
						  switch (yytext)
						  {
							case "SUN" :
							{
								yylval.dayValue = DayOfWeek.Sunday;
								break;
							}
							case "MON" :
							{
								yylval.dayValue = DayOfWeek.Monday;
								break;
							}
							case "TUE" :
							{
								yylval.dayValue = DayOfWeek.Tuesday;
								break;
							}
							case "WED" :
							{
								yylval.dayValue = DayOfWeek.Wednesday;
								break;
							}
							case "THU" :
							{
								yylval.dayValue = DayOfWeek.Thursday;
								break;
							}
							case "FRI" :
							{
								yylval.dayValue = DayOfWeek.Friday;
								break;
							}
							case "SAT" :
							{
								yylval.dayValue = DayOfWeek.Saturday;
								break;
							}
						  }
						  return (int)Tokens.TOK_DAY;}

{DIG}+					{ yylval.intValue = Convert.ToInt32(yytext); 
                          return (int)Tokens.TOK_COUNT; }

%%