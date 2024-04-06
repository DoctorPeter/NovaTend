%output=ScheduleRuleParser.cs   
%namespace Scheduler 

%visibility public
%sharetokens
%parsertype Parser      
%scanbasetype ScanBase  
%tokentype Tokens 

%union {
  public string strValue;
  public int intValue;
  public DateTime dateTimeValue;
  public DayOfWeek dayValue;
  public ScheduleCondition node;
}


%{
	// Root of scedule rule tree
	public ScheduleCondition root;

	// Parser constructor
	public Parser(Scanner scanner) : base(scanner) { }
%}


%token TOK_TIME
%token TOK_DATE
%token TOK_DAY
%token TOK_COUNT

%token TOK_TIME_PERIOD_CONDITION
%token TOK_DATE_PERIOD_CONDITION
%token TOK_DAYS_PERIOD_CONDITION
%token TOK_COUNT_CONDITION

%token TOK_NOT
%token TOK_AND
%token TOK_OR

%token TOK_OPEN_SQUARE_BREAKET
%token TOK_CLOSE_SQUARE_BREAKET
%token TOK_OPEN_ROUND_BREAKET
%token TOK_CLOSE_ROUND_BREAKET
%token TOK_MINUS

%left TOK_NOT TOK_AND TOK_OR
%left UNARY

%%
condition_statement : condition {root = $1.node;};

condition:
	  TOK_TIME_PERIOD_CONDITION TOK_OPEN_SQUARE_BREAKET TOK_TIME TOK_MINUS TOK_TIME TOK_CLOSE_SQUARE_BREAKET {$$.node = ScheduleCondition.MakeConditionNode(null, null, ScheduleConditionType.TIME_PERIOD_CONDITION, $3.dateTimeValue, $5.dateTimeValue, DayOfWeek.Sunday, DayOfWeek.Sunday, 0, 0);}
	| TOK_DATE_PERIOD_CONDITION TOK_OPEN_SQUARE_BREAKET TOK_DATE TOK_MINUS TOK_DATE TOK_CLOSE_SQUARE_BREAKET {$$.node = ScheduleCondition.MakeConditionNode(null, null, ScheduleConditionType.DATE_PERIOD_CONDITION, $3.dateTimeValue, $5.dateTimeValue, DayOfWeek.Sunday, DayOfWeek.Sunday, 0, 0);}
	| TOK_DAYS_PERIOD_CONDITION TOK_OPEN_SQUARE_BREAKET TOK_DAY  TOK_MINUS TOK_DAY  TOK_CLOSE_SQUARE_BREAKET {$$.node = ScheduleCondition.MakeConditionNode(null, null, ScheduleConditionType.DAYS_PERIOD_CONDITION, DateTime.Now, DateTime.Now, $3.dayValue, $5.dayValue, 0, 0);}
	| TOK_COUNT_CONDITION TOK_OPEN_SQUARE_BREAKET TOK_COUNT TOK_MINUS TOK_COUNT TOK_CLOSE_SQUARE_BREAKET	 {$$.node = ScheduleCondition.MakeConditionNode(null, null, ScheduleConditionType.COUNT_CONDITION, DateTime.Now, DateTime.Now, DayOfWeek.Sunday, DayOfWeek.Sunday, $5.intValue, $3.intValue);}
	| TOK_NOT condition %prec UNARY							 {$$.node = ScheduleCondition.MakeConditionNode($2.node, null, ScheduleConditionType.NOT_OPERATION, DateTime.Now, DateTime.Now, DayOfWeek.Sunday, DayOfWeek.Sunday, 0, 0);}
	| condition TOK_AND condition							 {$$.node = ScheduleCondition.MakeConditionNode($1.node, $3.node, ScheduleConditionType.AND_OPERATION, DateTime.Now, DateTime.Now, DayOfWeek.Sunday, DayOfWeek.Sunday, 0, 0);}
	| condition TOK_OR condition							 {$$.node = ScheduleCondition.MakeConditionNode($1.node, $3.node, ScheduleConditionType.OR_OPERATION, DateTime.Now, DateTime.Now, DayOfWeek.Sunday, DayOfWeek.Sunday, 0, 0);}
	| TOK_OPEN_ROUND_BREAKET condition TOK_CLOSE_ROUND_BREAKET {$$ = $2;}
	;
  
%%