/****************************************************************

   Solution : NovaTend

   Project : z-validateresponse-01.dll

   Module : PasswordConstructor.h

   Description :  this module defines interface of class
				  PasswordConstructor

*****************************************************************/
#include <ContentDataDef.h>
#include <Encryptor.h>
#include <time.h>


// Password construction rule function
typedef void (* ConstructionRuleFunction)(void);

// Password construction rule structure
typedef struct _rule_struct
{
	// rule ID
	int ruleID;

	// rule type
	int ruleType;

	// Rule function
	ConstructionRuleFunction ruleFunction;

} PWD_CONSTRACTION_RULE, *PPWD_CONSTRACTION_RULE;


/****************************************************************

   Class : PasswordConstructor

   Description : responsible for user custom passwords creation

*****************************************************************/
class PasswordConstructor
{
	private:

		// Encryptor instance
		Encryptor * encryptor;

		// Password string
		char userPassword[STR_VALUE_LEN];
		
		// User description
		PUSER_DESCRIPTOR pUser;

		// Security data pointer
		PUSER_SECURITY_DATA pSecurityData;

		// Count of rules
		int rulesCount;
		
		// Time description structure
		tm * pTimeInfo;

		// List of symbol matrixes
		PUTF8_STRINGS_MATRIX_LIST pSymbolBoxesList;

		// Symbol box password data
		char joker1[4];
		char joker2[4];
		char token[8];
		int pairLocation;
		int symbolLocation;


		// Set of construction rules
		PPWD_CONSTRACTION_RULE rules[MAX_PWD_CONSTR_RULES_COUNT];
		
		// Cascade string password rules
		static void ruleUserName(void);
		static void ruleUserToken(void);
		static void ruleWeekDaySmall(void);
		static void ruleWeekDayLarge(void);
		static void ruleMonthSmall(void);
		static void ruleMonthLarge(void);
		static void ruleMonthNumber(void);
		static void ruleYearNumber(void);
		static void ruleDayNumber(void);
		static void ruleReverseCurrent(void);

		// Symbol box rules
		static void ruleJoker1Year(void);
		static void ruleJoker1Month(void);
		static void ruleJoker1Day(void);
		static void ruleJoker1Hour(void);
		static void ruleJoker1Minute(void);
		static void ruleJoker1Second(void);
		static void ruleJoker2Year(void);
		static void ruleJoker2Month(void);
		static void ruleJoker2Day(void);
		static void ruleJoker2Hour(void);
		static void ruleJoker2Minute(void);
		static void ruleJoker2Second(void);

		static void ruleFormula_J1_J2_T(void);
		static void ruleFormula_T_J1_J2(void);
		static void ruleFormula_J1_T_J2(void);
		static void ruleFormula_J2_T_J1(void);

		static void rulePairLocation_UL(void);
		static void rulePairLocation_U(void);
		static void rulePairLocation_UR(void);
		static void rulePairLocation_R(void);
		static void rulePairLocation_BR(void);
		static void rulePairLocation_B(void);
		static void rulePairLocation_BL(void);
		static void rulePairLocation_L(void);
		static void ruleSymbolLocation_L(void);
		static void ruleSymbolLocation_R(void);
		static void ruleSymbolLocation_UL(void);
		static void ruleSymbolLocation_U(void);
		static void ruleSymbolLocation_UR(void);
		static void ruleSymbolLocation_BL(void);
		static void ruleSymbolLocation_B(void);
		static void ruleSymbolLocation_BR(void);

		// Find rule
		int FindRule(int ruleID);

		// Find rule
		int FindRule(int ruleRangeMin, int ruleRangeMax, bool TmpPwd);
				

		// Build symbol box password
		void BuildOneSymbolBoxPassword(void);
		
		// Build symbol box password
		void BuildTwoSymbolBoxPassword(void);

		// Create password
		void CreatePassword(bool tmpPwd);

	public:
		
		// Constructor
		PasswordConstructor(PUSER_DESCRIPTOR user, PUSER_SECURITY_DATA securityData, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList, Encryptor * encryptor);

		// Destructor
		~PasswordConstructor(void);

		// Create password
		void CreateMainPassword(void);

		// Create password
		void CreateTempPassword(void);

		// Retrieve password
		void GetPassword(char * password);

};