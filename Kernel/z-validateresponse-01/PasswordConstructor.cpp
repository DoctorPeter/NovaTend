/****************************************************************

   Solution : NovaTend

   Project : z-validateresponse-01.dll

   Module : PasswordConstructor.cpp

   Description :  this module implements methods of class
				  PasswordConstructor

*****************************************************************/

#include "stdafx.h"

#include "PasswordConstructor.h"

#include <stdlib.h>

// Pointer to self
PasswordConstructor *_this;


/****************************************************************

   Class : PasswordConstructor

   Method : Constructor

   Parameters :
			Input : 
				user - pointer to user description structure
				timeinfo - time structure

*****************************************************************/
PasswordConstructor :: PasswordConstructor(PUSER_DESCRIPTOR user, PUSER_SECURITY_DATA securityData, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList, Encryptor * encryptor)
{
	// Set encryptor
	this -> encryptor = encryptor;

	// Set user description
	pUser = user;

	// Set security data pointer
	pSecurityData = securityData;

	// Get time info
	pTimeInfo = timeinfo;

	// Get symbol matrixes
	pSymbolBoxesList = symbolBoxesList;

	// Get current time
	if (pTimeInfo == NULL)
	{
		time_t seconds = time(NULL);
		pTimeInfo = localtime(&seconds);
	}

	userPassword[0] = 0;

	rulesCount = 0;

	joker1[0] = 0;
	joker2[0] = 0;
	token[0] = 0;
	pairLocation = 0;
	symbolLocation = 0;

	_this = this;

	// Prepare rules

	// Cascade string password rules
	if (pUser -> pwdType == CASCADE_STRING_PWD)
	{
		rulesCount = 10;

		for(int i = 0; i < rulesCount; i++)
		{
			rules[i] = (PPWD_CONSTRACTION_RULE)malloc(sizeof(PWD_CONSTRACTION_RULE));

			if (rules[i])
			{
				rules[i] -> ruleID = i + 1;
				rules[i] -> ruleType = pUser -> pwdType;
			
				switch(rules[i] -> ruleID)
				{
					case 1 : {
								rules[i] -> ruleFunction = ruleUserName;
								break;
							 }

					case 2 : {
								rules[i] -> ruleFunction = ruleUserToken;
								break;
							 }

					case 3 : {
								rules[i] -> ruleFunction = ruleWeekDaySmall;
								break;
							 }

					case 4 : {
								rules[i] -> ruleFunction = ruleWeekDayLarge;
								break;
							 }

					case 5 : {
								rules[i] -> ruleFunction = ruleMonthSmall;
								break;
							 }

					case 6 : {
								rules[i] -> ruleFunction = ruleMonthLarge;
								break;
							 }

					case 7 : {
								rules[i] -> ruleFunction = ruleMonthNumber;
								break;
							 }

					case 8 : {
								rules[i] -> ruleFunction = ruleYearNumber;
								break;
							 }

					case 9 : {
								rules[i] -> ruleFunction = ruleDayNumber;
								break;
							 }

					case 10 : {
								rules[i] -> ruleFunction = ruleReverseCurrent;
								break;
							 }
				}
			}
		}
	}


	// Symbol box password rules (one symbol per cell)
	if (pUser -> pwdType == ONE_SYMBOL_BOX_PWD)
	{
		rulesCount = 24;

		for(int i = 0; i < rulesCount; i++)
		{
			rules[i] = (PPWD_CONSTRACTION_RULE)malloc(sizeof(PWD_CONSTRACTION_RULE));

			if (rules[i])
			{
				rules[i] -> ruleID = i + 127;
				rules[i] -> ruleType = pUser -> pwdType;
			
				switch(rules[i] -> ruleID)
				{
					case 127 : {
								rules[i] -> ruleFunction = ruleJoker1Year;
								break;
							 }

					case 128 : {
								rules[i] -> ruleFunction = ruleJoker1Month;
								break;
							 }

					case 129 : {
								rules[i] -> ruleFunction = ruleJoker1Day;
								break;
							 }

					case 130 : {
								rules[i] -> ruleFunction = ruleJoker1Hour;
								break;
							 }

					case 131 : {
								rules[i] -> ruleFunction = ruleJoker1Minute;
								break;
							 }

					case 132 : {
								rules[i] -> ruleFunction = ruleJoker1Second;
								break;
							 }

					case 133 : {
								rules[i] -> ruleFunction = ruleJoker2Year;
								break;
							 }

					case 134 : {
								rules[i] -> ruleFunction = ruleJoker2Month;
								break;
							 }

					case 135 : {
								rules[i] -> ruleFunction = ruleJoker2Day;
								break;
							 }

					case 136 : {
								rules[i] -> ruleFunction = ruleJoker2Hour;
								break;
							 }

					case 137 : {
								rules[i] -> ruleFunction = ruleJoker2Minute;
								break;
							 }

					case 138 : {
								rules[i] -> ruleFunction = ruleJoker2Second;
								break;
							 }

					case 139 : {
								rules[i] -> ruleFunction = ruleFormula_J1_J2_T;
								break;
							 }

					case 140 : {
								rules[i] -> ruleFunction = ruleFormula_T_J1_J2;
								break;
							 }

					case 141 : {
								rules[i] -> ruleFunction = ruleFormula_J1_T_J2;
								break;
							 }

					case 142 : {
								rules[i] -> ruleFunction = ruleFormula_J2_T_J1;
								break;
							 }

					case 143 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_L;
								break;
							 }

					case 144 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_R;
								break;
							 }

					case 145 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_UL;
								break;
							 }

					case 146 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_U;
								break;
							 }

					case 147 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_UR;
								break;
							 }

					case 148 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_BL;
								break;
							 }

					case 149 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_B;
								break;
							 }

					case 150 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_BR;
								break;
							 }

				}
			}
		}
	}

	// Symbol box password rules (two symbols per cell)
	if (pUser -> pwdType == TWO_SYMBOL_BOX_PWD)
	{
		rulesCount = 26;
		for(int i = 0; i < rulesCount; i++)
		{
			rules[i] = (PPWD_CONSTRACTION_RULE)malloc(sizeof(PWD_CONSTRACTION_RULE));

			if (rules[i])
			{
				rules[i] -> ruleID = i + 101;
				rules[i] -> ruleType = pUser -> pwdType;
			
				switch(rules[i] -> ruleID)
				{
					case 101 : {
								rules[i] -> ruleFunction = ruleJoker1Year;
								break;
							 }

					case 102 : {
								rules[i] -> ruleFunction = ruleJoker1Month;
								break;
							 }

					case 103 : {
								rules[i] -> ruleFunction = ruleJoker1Day;
								break;
							 }

					case 104 : {
								rules[i] -> ruleFunction = ruleJoker1Hour;
								break;
							 }

					case 105 : {
								rules[i] -> ruleFunction = ruleJoker1Minute;
								break;
							 }

					case 106 : {
								rules[i] -> ruleFunction = ruleJoker1Second;
								break;
							 }

					case 107 : {
								rules[i] -> ruleFunction = ruleJoker2Year;
								break;
							 }

					case 108 : {
								rules[i] -> ruleFunction = ruleJoker2Month;
								break;
							 }

					case 109 : {
								rules[i] -> ruleFunction = ruleJoker2Day;
								break;
							 }

					case 110 : {
								rules[i] -> ruleFunction = ruleJoker2Hour;
								break;
							 }

					case 111 : {
								rules[i] -> ruleFunction = ruleJoker2Minute;
								break;
							 }

					case 112 : {
								rules[i] -> ruleFunction = ruleJoker2Second;
								break;
							 }

					case 113 : {
								rules[i] -> ruleFunction = ruleFormula_J1_J2_T;
								break;
							 }

					case 114 : {
								rules[i] -> ruleFunction = ruleFormula_T_J1_J2;
								break;
							 }

					case 115 : {
								rules[i] -> ruleFunction = ruleFormula_J1_T_J2;
								break;
							 }

					case 116 : {
								rules[i] -> ruleFunction = ruleFormula_J2_T_J1;
								break;
							 }

					case 117 : {
								rules[i] -> ruleFunction = rulePairLocation_UL;
								break;
							 }

					case 118 : {
								rules[i] -> ruleFunction = rulePairLocation_U;
								break;
							 }

					case 119 : {
								rules[i] -> ruleFunction = rulePairLocation_UR;
								break;
							 }

					case 120 : {
								rules[i] -> ruleFunction = rulePairLocation_R;
								break;
							 }
				
					case 121 : {
								rules[i] -> ruleFunction = rulePairLocation_BR;
								break;
							 }

					case 122 : {
								rules[i] -> ruleFunction = rulePairLocation_B;
								break;
							 }

					case 123 : {
								rules[i] -> ruleFunction = rulePairLocation_BL;
								break;
							 }

					case 124 : {
								rules[i] -> ruleFunction = rulePairLocation_B;
								break;
							 }

					case 125 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_L;
								break;
							 }

					case 126 : {
								rules[i] -> ruleFunction = ruleSymbolLocation_R;
								break;
							 }
				}
			}
		}
	}

	
}

/****************************************************************

   Class : PasswordConstructor

   Method : Destructor

*****************************************************************/
PasswordConstructor :: ~PasswordConstructor(void)
{
	// Remove rules list
	for(int i = 0; i < rulesCount; i++)
		if (rules[i]) free(rules[i]);
}

/****************************************************************

   Class : PasswordConstructor

   Method : FindRule

   Parameters:
			Input:
				ruleID - rule ID
   
   Returns: rule index
		
   Description :  Find rule

*****************************************************************/
int PasswordConstructor :: FindRule(int ruleID)
{
	int ruleIndex = -1;
	
	for(int i = 0; i < rulesCount; i++)
		if ((rules[i]) && (rules[i] -> ruleID == ruleID))
		{
			ruleIndex = i;
			break;
		}

	return ruleIndex;
}

/****************************************************************

   Class : PasswordConstructor

   Method : FindRule

   Parameters:
			Input:
				ruleRangeMin - min rule ID
				ruleRangeMax - maxrule ID

   Returns: rule index
		
   Description :  Find rule

*****************************************************************/
int PasswordConstructor :: FindRule(int ruleRangeMin, int ruleRangeMax, bool TmpPwd)
{
	int ruleID = -1;
	bool found = false;

	if (pSecurityData)
	{
		int  * rulesList = NULL;
		int rulesListSize = 0;

		if (TmpPwd)
		{
			rulesList = pSecurityData -> tmpPwdConstRules;
			rulesListSize = pSecurityData -> tmpPwdConstRulesCount;
		}
		else
		{
			rulesList = pSecurityData -> pwdConstRules;
			rulesListSize = pSecurityData -> pwdConstRulesCount;
		}

		for(int i = 0; i < rulesListSize; i++)
		{
			if ((rulesList[i] >= ruleRangeMin) && (rulesList[i] <= ruleRangeMax))
			{
				found = true;
				ruleID = rulesList[i];
				break;
			}
		}
	}

	if (found)
		return FindRule(ruleID);
	else
		return -1;
}

/****************************************************************

   Class : PasswordConstructor

   Method : BuildOneSymbolBoxPassword

   Description :  Build symbol box password (one symbol per cell)

*****************************************************************/
void PasswordConstructor :: BuildOneSymbolBoxPassword(void)
{
	// Check symbol boxes list
	if ((pSymbolBoxesList) && 
		(pSymbolBoxesList -> size == 10) &&
		(pSymbolBoxesList -> matrixes[0] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[1] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[2] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[3] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[4] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[5] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[6] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[7] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[8] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[9] -> size == 3))
	{
		char tmpStr[STR_VALUE_LEN];
		int offset = 0;

		// For each digit of prebuilded password
		for(int i = 0; i < strlen(userPassword); i++)
		{
			// Get current digit
			char currentDigit = userPassword[i];

			// Find matrix
			for(int k = 0; k < pSymbolBoxesList -> size; k++)
			{
				// If matrix found
				if (pSymbolBoxesList -> matrixes[k] -> strings[1][1] -> chars[0] -> bytes[0] == currentDigit)
				{
					PUTF8_STRING string = NULL;

					// Get symbol according location
					switch (symbolLocation)
					{
						case SYMBOL_LOCATION_UPPER_LEFT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[0][0];
								break;
							}

						case SYMBOL_LOCATION_UPPER :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[0][1];
								break;
							}

						case SYMBOL_LOCATION_UPPER_RIGHT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[0][2];
								break;
							}

						case SYMBOL_LOCATION_LEFT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[1][0];
								break;
							}

						case SYMBOL_LOCATION_RIGHT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[1][2];
								break;
							}

						case SYMBOL_LOCATION_LOWER_LEFT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[2][0];
								break;
							}

						case SYMBOL_LOCATION_LOWER :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[2][1];
								break;
							}

						case SYMBOL_LOCATION_LOWER_RIGHT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[2][2];
								break;
							}
					}

					if (string -> length > 1)
					{
						memcpy(tmpStr + offset, string -> chars[0] -> bytes, string -> chars[0] -> bytesCount);
						offset += string -> chars[0] -> bytesCount;
					}

					break;
				}
			}
		}

		// Copy constructed password
		tmpStr[offset] = 0;
		strcpy(userPassword, tmpStr);
	}
}

/****************************************************************

   Class : PasswordConstructor

   Method : BuildTwoSymbolBoxPassword

   Description :  Build symbol box password (two symbols per cell)

*****************************************************************/
void PasswordConstructor :: BuildTwoSymbolBoxPassword(void)
{
	// Check symbol boxes list
	if ((pSymbolBoxesList) && 
		(pSymbolBoxesList -> size == 5) &&
		(pSymbolBoxesList -> matrixes[0] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[1] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[2] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[3] -> size == 3) &&
		(pSymbolBoxesList -> matrixes[4] -> size == 3))
	{
		char tmpStr[STR_VALUE_LEN];
		int offset = 0;

		// For each digit of prebuilded password
		for(int i = 0; i < strlen(userPassword); i++)
		{
			// Get current digit
			char currentDigit = userPassword[i];

			// Find matrix
			for(int k = 0; k < pSymbolBoxesList -> size; k++)
			{
				// If matrix found
				if ((pSymbolBoxesList -> matrixes[k] -> strings[1][1] -> chars[0] -> bytes[0] == currentDigit) || 
					(pSymbolBoxesList -> matrixes[k] -> strings[1][1] -> chars[1] -> bytes[0] == currentDigit))
				{
					PUTF8_STRING string = NULL;

					// Get symbols pair according location
					switch(pairLocation)
					{
						case PAIR_LOCATION_UPPER_LEFT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[0][0];
								break;
							}
						case PAIR_LOCATION_UPPER :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[0][1];
								break;
							}
						case PAIR_LOCATION_UPPER_RIGHT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[0][2];
								break;
							}
						case PAIR_LOCATION_RIGHT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[1][2];
								break;
							}
						case PAIR_LOCATION_LOWER_RIGHT:
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[2][2];
								break;
							}
						case PAIR_LOCATION_LOWER :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[2][1];
								break;
							}
						case PAIR_LOCATION_LOWER_LEFT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[2][0];
								break;
							}
						case PAIR_LOCATION_LEFT :
							{
								string = pSymbolBoxesList -> matrixes[k] -> strings[1][0];
								break;
							}
					}

					// Get symbol according location
					if (string -> length > 2)
					{
						switch (symbolLocation)
						{
							case SYMBOL_LOCATION_LEFT :
								{
									memcpy(tmpStr + offset, string -> chars[0] -> bytes, string -> chars[0] -> bytesCount);
									offset += string -> chars[0] -> bytesCount;
									break;
								}

							case SYMBOL_LOCATION_RIGHT :
								{
									memcpy(tmpStr + offset, string -> chars[1] -> bytes, string -> chars[1] -> bytesCount);
									offset += string -> chars[1] -> bytesCount;
									break;
								}
						}
					}

					break;
				}
			}
		}

		// Copy constructed password
		tmpStr[offset] = 0;
		strcpy(userPassword, tmpStr);
	}
}

/****************************************************************

   Class : PasswordConstructor

   Method : CreatePassword

   Parameters :
			Input:
				tmpPwd - flag of temp password

   Description :  Construct password according to the rules list

*****************************************************************/
void PasswordConstructor :: CreatePassword(bool tmpPwd)
{
	if ((pUser) && (pSecurityData) && (encryptor))
	{
		// Get token value
		if (tmpPwd)
			_itoa(_this -> pSecurityData -> tmpUserToken, token, 10);
		else
			_itoa(_this -> pSecurityData -> userToken, token, 10);

		// Clear current password
		userPassword[0] = 0;

		switch (pUser -> pwdType)
		{
			case CASCADE_STRING_PWD:
				{
					int * pwdRulesSet;
					int pwdRuleSetSize;

					// Get password contsruction rules set
					if (tmpPwd)
					{
						pwdRulesSet = pSecurityData -> tmpPwdConstRules;
						pwdRuleSetSize = pSecurityData -> tmpPwdConstRulesCount;
					}
					else

					{
						pwdRulesSet = pSecurityData -> pwdConstRules;
						pwdRuleSetSize = pSecurityData -> pwdConstRulesCount;
					}

					//Construct password
					for(int i = 0; i < pwdRuleSetSize; i++)
					{
						int ruleIndex = FindRule(pwdRulesSet[i]);
						if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();
					}

					break;
				}

			case ONE_SYMBOL_BOX_PWD:
				{
					// Joker 1
					int ruleIndex = FindRule(ONE_SYM_PWD_JOKER_1_MIN, ONE_SYM_PWD_JOKER_1_MAX, tmpPwd);
					if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();

					// Joker 2
					ruleIndex = FindRule(ONE_SYM_PWD_JOKER_2_MIN, ONE_SYM_PWD_JOKER_2_MAX, tmpPwd);
					if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();

					// Formula
					ruleIndex = FindRule(ONE_SYM_PWD_FORMULA_MIN, ONE_SYM_PWD_FORMULA_MAX, tmpPwd);
					if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();
					else strcpy(userPassword, token);

					// Symbol location
					ruleIndex = FindRule(ONE_SYM_PWD_SYMBOL_LOCATION_MIN, ONE_SYM_PWD_SYMBOL_LOCATION_MAX, tmpPwd);
					if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();

					// Build password according to symbol boxes list
					BuildOneSymbolBoxPassword();

					break;
				}

			case TWO_SYMBOL_BOX_PWD:
				{

					// Joker 1
					int ruleIndex = FindRule(TWO_SYM_PWD_JOKER_1_MIN, TWO_SYM_PWD_JOKER_1_MAX, tmpPwd);
					if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();

					// Joker 2
					ruleIndex = FindRule(TWO_SYM_PWD_JOKER_2_MIN, TWO_SYM_PWD_JOKER_2_MAX, tmpPwd);
					if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();

					// Formula
					ruleIndex = FindRule(TWO_SYM_PWD_FORMULA_MIN, TWO_SYM_PWD_FORMULA_MAX, tmpPwd);
					if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();
					else strcpy(userPassword, token);

					// Pair location
					ruleIndex = FindRule(TWO_SYM_PWD_PAIR_LOCATION_MIN, TWO_SYM_PWD_PAIR_LOCATION_MAX, tmpPwd);
					if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();

					// Symbol location
					ruleIndex = FindRule(TWO_SYM_PWD_SYMBOL_LOCATION_MIN, TWO_SYM_PWD_SYMBOL_LOCATION_MAX, tmpPwd);
					if (ruleIndex != -1) rules[ruleIndex] -> ruleFunction();

					// Build password according to symbol boxes list
					BuildTwoSymbolBoxPassword();
					break;
				}
		}
	}
}

/****************************************************************

   Class : PasswordConstructor

   Method : CreateMainPassword

   Description :  Construct password according ot main rules list

*****************************************************************/
void PasswordConstructor :: CreateMainPassword(void)
{
	CreatePassword(false);
}

/****************************************************************

   Class : PasswordConstructor

   Method : CreateTempPassword

   Description :  Construct password according ot temp rules list

*****************************************************************/
void PasswordConstructor :: CreateTempPassword(void)
{
	CreatePassword(true);
}

/****************************************************************

   Class : PasswordConstructor

   Method : GetPassword

   Parameters:
		Output:
			password - constructed password

   Description :  Retrieve password

*****************************************************************/

void PasswordConstructor :: GetPassword(char * password)
{
	strcpy(password, userPassword);
}


/****************************************************************

   Class : PasswordConstructor

   Method : ruleUserName

   Description : Append user name

*****************************************************************/
void PasswordConstructor :: ruleUserName(void)
{
	unsigned char decryptedValue[STR_VALUE_LEN];
	int decryptedValueLen;

	if (!(_this -> encryptor -> UnPackAndDecryptSecurityData(_this -> pUser -> encUserName, _this -> pUser -> encUserNameLen, decryptedValue, STR_VALUE_LEN, &decryptedValueLen)))
	{
		decryptedValue[decryptedValueLen] = 0;
		strcat(_this -> userPassword, (char *)decryptedValue);
	}
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleUserToken

   Description : Append user token

*****************************************************************/
void PasswordConstructor :: ruleUserToken(void)
{
	strcat(_this -> userPassword, _this -> token);
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleWeekDaySmall

   Description : Append name of week day (small letters)

*****************************************************************/
void PasswordConstructor :: ruleWeekDaySmall(void)
{
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%A", _this -> pTimeInfo);
	_strlwr(tmpStr);
	strcat(_this -> userPassword, tmpStr);			
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleWeekDayLarge

   Description : Append name of week day (large letters)

*****************************************************************/
void PasswordConstructor :: ruleWeekDayLarge(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%A", _this -> pTimeInfo);
	_strupr(tmpStr);
	strcat(_this -> userPassword, tmpStr);			
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleMonthSmall

   Description : Append name of month (small letters)

*****************************************************************/
void PasswordConstructor :: ruleMonthSmall(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%B", _this -> pTimeInfo);
	_strlwr(tmpStr);
	strcat(_this -> userPassword, tmpStr);			
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleMonthLarge

   Description : Append name of month (large letters)

*****************************************************************/
void PasswordConstructor :: ruleMonthLarge(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%B", _this -> pTimeInfo);
	_strupr(tmpStr);
	strcat(_this -> userPassword, tmpStr);			
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleMonthNumber

   Description : Append number of month

***************************************************************/
void PasswordConstructor :: ruleMonthNumber(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%m", _this -> pTimeInfo);
	strcat(_this -> userPassword, tmpStr);	
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleYearNumber

   Description : Append number of year

*****************************************************************/
void PasswordConstructor :: ruleYearNumber(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%Y", _this -> pTimeInfo);
	strcat(_this -> userPassword, tmpStr);	
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleDayNumber

   Description : Append number of day of month

*****************************************************************/
void PasswordConstructor :: ruleDayNumber(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%d", _this -> pTimeInfo);
	strcat(_this -> userPassword, tmpStr);	
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleReverseCurrent

   Description : Reverse current

*****************************************************************/
void PasswordConstructor :: ruleReverseCurrent(void)
{
   char c;
   size_t i, j;
   size_t size = strlen(_this -> userPassword);

   for(i = 0, j = size - 1; i < j; i++, j--)
   {
      c = _this -> userPassword[i];
      _this -> userPassword[i] = _this -> userPassword[j];
      _this -> userPassword[j] = c;
   }
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker1Year

   Description : Get joker 1 value (year)

*****************************************************************/
void PasswordConstructor :: ruleJoker1Year(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%y", _this -> pTimeInfo);
	_this -> joker1[0] = tmpStr[1];
	_this -> joker1[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker1Month

   Description : Get joker 1 value (month)

*****************************************************************/
void PasswordConstructor :: ruleJoker1Month(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%m", _this -> pTimeInfo);
	_this -> joker1[0] = tmpStr[1];
	_this -> joker1[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker1Day

   Description : Get joker 1 value (day)

*****************************************************************/
void PasswordConstructor :: ruleJoker1Day(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%d", _this -> pTimeInfo);
	_this -> joker1[0] = tmpStr[1];
	_this -> joker1[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker1Hour

   Description : Get joker 1 value (hour)

*****************************************************************/
void PasswordConstructor :: ruleJoker1Hour(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%H", _this -> pTimeInfo);
	_this -> joker1[0] = tmpStr[1];
	_this -> joker1[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker1Minute

   Description : Get joker 1 value (minute)

*****************************************************************/
void PasswordConstructor :: ruleJoker1Minute(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%M", _this -> pTimeInfo);
	_this -> joker1[0] = tmpStr[1];
	_this -> joker1[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker1Second

   Description : Get joker 1 value (second)

*****************************************************************/
void PasswordConstructor :: ruleJoker1Second(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%S", _this -> pTimeInfo);
	_this -> joker1[0] = tmpStr[1];
	_this -> joker1[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker2Year

   Description : Get joker 2 value (year)

*****************************************************************/
void PasswordConstructor :: ruleJoker2Year(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%y", _this -> pTimeInfo);
	_this -> joker2[0] = tmpStr[1];
	_this -> joker2[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker2Month

   Description : Get joker 2 value (month)

*****************************************************************/
void PasswordConstructor :: ruleJoker2Month(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%m", _this -> pTimeInfo);
	_this -> joker2[0] = tmpStr[1];
	_this -> joker2[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker2Day

   Description : Get joker 2 value (day)

*****************************************************************/
void PasswordConstructor :: ruleJoker2Day(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%d", _this -> pTimeInfo);
	_this -> joker2[0] = tmpStr[1];
	_this -> joker2[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker2Hour

   Description : Get joker 2 value (hour)

*****************************************************************/
void PasswordConstructor :: ruleJoker2Hour(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%H", _this -> pTimeInfo);
	_this -> joker2[0] = tmpStr[1];
	_this -> joker2[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker2Minute

   Description : Get joker 2 value (minute)

*****************************************************************/
void PasswordConstructor :: ruleJoker2Minute(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%M", _this -> pTimeInfo);
	_this -> joker2[0] = tmpStr[1];
	_this -> joker2[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleJoker2Second

   Description : Get joker 2 value (second)

*****************************************************************/
void PasswordConstructor :: ruleJoker2Second(void)
{
	// Get current data and time
	char tmpStr[STR_VALUE_LEN];
	strftime(tmpStr, STR_VALUE_LEN, "%S", _this -> pTimeInfo);
	_this -> joker2[0] = tmpStr[1];
	_this -> joker2[1] = 0;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleFormula_J1_J2_T

   Description : Formula JOKER1 + JOKER2 + TOKEN

*****************************************************************/
void PasswordConstructor :: ruleFormula_J1_J2_T(void)
{
	strcpy(_this -> userPassword, _this -> joker1);
	strcat(_this -> userPassword, _this -> joker2);
	strcat(_this -> userPassword, _this -> token);
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleFormula_T_J1_J2

   Description : Formula TOKEN + JOKER1 + JOKER2

*****************************************************************/
void PasswordConstructor :: ruleFormula_T_J1_J2(void)
{
	strcpy(_this -> userPassword, _this -> token);
	strcat(_this -> userPassword, _this -> joker1);
	strcat(_this -> userPassword, _this -> joker2);
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleFormula_J1_T_J2

   Description : Formula JOKER1 + + TOKEN + JOKER2

*****************************************************************/
void PasswordConstructor :: ruleFormula_J1_T_J2(void)
{
	strcpy(_this -> userPassword, _this -> joker1);
	strcat(_this -> userPassword, _this -> token);
	strcat(_this -> userPassword, _this -> joker2);
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleFormula_J2_T_J1

   Description : Formula JOKER2 + + TOKEN + JOKER1

*****************************************************************/
void PasswordConstructor :: ruleFormula_J2_T_J1(void)
{
	strcpy(_this -> userPassword, _this -> joker2);
	strcat(_this -> userPassword, _this -> token);
	strcat(_this -> userPassword, _this -> joker1);
}

/****************************************************************

   Class : PasswordConstructor

   Method : rulePairLocationUL

   Description : Pair location: UPPER LEFT

*****************************************************************/
void PasswordConstructor :: rulePairLocation_UL(void)
{
	_this -> pairLocation = PAIR_LOCATION_UPPER_LEFT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : rulePairLocation_U

   Description : Pair location: UPPER

*****************************************************************/
void PasswordConstructor :: rulePairLocation_U(void)
{
	_this -> pairLocation = PAIR_LOCATION_UPPER;
}

/****************************************************************

   Class : PasswordConstructor

   Method : rulePairLocation_UR

   Description : Pair location: UPPER RIGHT

*****************************************************************/
void PasswordConstructor :: rulePairLocation_UR(void)
{
	_this -> pairLocation = PAIR_LOCATION_UPPER_RIGHT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : rulePairLocation_R

   Description : Pair location: RIGHT

*****************************************************************/
void PasswordConstructor :: rulePairLocation_R(void)
{
	_this -> pairLocation = PAIR_LOCATION_RIGHT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : rulePairLocation_BR

   Description : Pair location: LOWER RIGHT

*****************************************************************/
void PasswordConstructor :: rulePairLocation_BR(void)
{
	_this -> pairLocation = PAIR_LOCATION_LOWER_RIGHT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : rulePairLocation_B

   Description : Pair location: LOWER

*****************************************************************/
void PasswordConstructor :: rulePairLocation_B(void)
{
	_this -> pairLocation = PAIR_LOCATION_LOWER;
}

/****************************************************************

   Class : PasswordConstructor

   Method : rulePairLocation_BL

   Description : Pair location: LOWER LEFT

*****************************************************************/
void PasswordConstructor :: rulePairLocation_BL(void)
{
	_this -> pairLocation = PAIR_LOCATION_LOWER_LEFT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : rulePairLocation_L

   Description : Pair location: LEFT

*****************************************************************/
void PasswordConstructor :: rulePairLocation_L(void)
{
	_this -> pairLocation = PAIR_LOCATION_LEFT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleSymbolLocation_L

   Description : Symbol location: LEFT

*****************************************************************/
void PasswordConstructor :: ruleSymbolLocation_L(void)
{
	_this -> symbolLocation = SYMBOL_LOCATION_LEFT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleSymbolLocation_R

   Description : Symbol location: RIGHT

*****************************************************************/
void PasswordConstructor :: ruleSymbolLocation_R(void)
{
	_this -> symbolLocation = SYMBOL_LOCATION_RIGHT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleSymbolLocation_UL

   Description : Symbol location: UPPER LEFT

*****************************************************************/
void PasswordConstructor :: ruleSymbolLocation_UL(void)
{
	_this -> symbolLocation = SYMBOL_LOCATION_UPPER_LEFT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleSymbolLocation_U

   Description : Symbol location: UPPER

*****************************************************************/
void PasswordConstructor :: ruleSymbolLocation_U(void)
{
	_this -> symbolLocation = SYMBOL_LOCATION_UPPER;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleSymbolLocation_UR

   Description : Symbol location: UPPER RIGHT

*****************************************************************/
void PasswordConstructor :: ruleSymbolLocation_UR(void)
{
	_this -> symbolLocation = SYMBOL_LOCATION_UPPER_RIGHT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleSymbolLocation_BL

   Description : Symbol location: LOWER LEFT

*****************************************************************/
void PasswordConstructor :: ruleSymbolLocation_BL(void)
{
	_this -> symbolLocation = SYMBOL_LOCATION_LOWER_LEFT;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleSymbolLocation_B

   Description : Symbol location: LOWER

*****************************************************************/
void PasswordConstructor :: ruleSymbolLocation_B(void)
{
	_this -> symbolLocation = SYMBOL_LOCATION_LOWER;
}

/****************************************************************

   Class : PasswordConstructor

   Method : ruleSymbolLocation_BR

   Description : Symbol location: LOWER RIGHT

*****************************************************************/
void PasswordConstructor :: ruleSymbolLocation_BR(void)
{
	_this -> symbolLocation = SYMBOL_LOCATION_RIGHT;
}