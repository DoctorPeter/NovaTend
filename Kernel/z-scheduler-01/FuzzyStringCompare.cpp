/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : FuzzyStringCompare.cpp

   Description :  this module implements
				  functions for fuzzy string comparsion

*****************************************************************/

#include "stdafx.h"
#include "FuzzyStringCompare.h"

#include <stdlib.h>

/****************************************************************

   Function : Matching
   
   Parameters :
			Input : 
				strInputA - first string
				strInputB - second string
				lngLen - legth of string slice

   Return : String matching count struct
	
   Description :  Find count of matching of two strings

*****************************************************************/
PSTRING_MATCHING_COUNT Matching(char * strInputA, char * strInputB, int lngLen)
{
	// Check input values
	if ((!strInputA) || (!strInputB))
		return NULL;

	char StrA[STRING_LENGTH] = "";
    char StrB[STRING_LENGTH] = "";

	// Copy input data
	strcpy(StrA, strInputA);
	strcpy(StrB, strInputB);

	// Create result struct
	PSTRING_MATCHING_COUNT result = (PSTRING_MATCHING_COUNT)malloc(sizeof(STRING_MATCHING_COUNT));

	if (result)
	{
		ZeroMemory(result, sizeof(STRING_MATCHING_COUNT));

		// Get all substrings of first string
		for (int PosStrA = 0; PosStrA < (strlen(StrA) - lngLen); PosStrA++)
		{
			char StrTmpA[STRING_LENGTH] = "";
			strncpy(StrTmpA, StrA + PosStrA, lngLen);

			// Get all substrings of second string
			for (int PosStrB = 0; PosStrB < (strlen(StrB) - lngLen); PosStrB++)
			{
				char StrTmpB[STRING_LENGTH] = "";
				strncpy(StrTmpB, StrB + PosStrB, lngLen);

				// Compare two substrings
				if (strcmp(StrTmpA, StrTmpB) == 0)
				{
					result -> lngCountLike++;
					break;
				}
			}

			result -> lngSubRows++;
		}
	}

	return result;
}

/****************************************************************

   Function : IndistinctMatching
   
   Parameters :
			Input : 
				maxMatching - max matching count
				strInputMatching - reached string
				strInputStandart - input string

   Return : Percents of strings matching
	
   Description :  Indistinc matching of two strings

*****************************************************************/
int IndistinctMatching(int maxMatching, char * strInputMatching, char * strInputStandart)
{
	// Check input values
	if ((!strInputMatching) || (!strInputStandart) || (strlen(strInputMatching) == 0) || (strlen(strInputStandart) == 0) || (maxMatching == 0))
		return 0;
	
	// Create global strings matching struct
	PSTRING_MATCHING_COUNT gret = (PSTRING_MATCHING_COUNT)malloc(sizeof(STRING_MATCHING_COUNT));

	if (gret)
	{
		ZeroMemory(gret, sizeof(STRING_MATCHING_COUNT));
		PSTRING_MATCHING_COUNT tret = NULL;
		
		// Get all matchings
		for (int lngCurLen = 1; lngCurLen <= maxMatching; lngCurLen++)
		{
			// Get temporary strings matching struct
			tret = Matching(strInputMatching, strInputStandart, lngCurLen);

			// Count values
			if (tret)
			{
				gret -> lngCountLike += tret -> lngCountLike;
				gret -> lngSubRows += tret -> lngSubRows;

				free(tret);
			}
			else
			{
				free(gret);
				return 0;
			}

			// Get temporary strings matching struct
			tret = Matching(strInputStandart, strInputMatching, lngCurLen);

			// Count values
			if (tret)
			{
				gret -> lngCountLike += tret -> lngCountLike;
				gret -> lngSubRows += tret -> lngSubRows;

				free(tret);
			}
			else
			{
				free(gret);
				return 0;
			}
		}

		// Calculate result
		int result = 0;
		if (gret -> lngSubRows > 0)
		{
			result = (int)(((double)(gret -> lngCountLike) / (double)(gret -> lngSubRows)) * 100);
		}

		free(gret);

		return result;
	}
	else
		return 0;
}

/****************************************************************

   Function : FuzzyStrCmp
   
   Parameters :
			Input : 
				str1 - first string
				str2 - second string

   Return : TRUE - if strings is matched
	
   Description :  Fuzzy string comparsion

*****************************************************************/
bool FuzzyStrCmp(char * str1, char * str2)
{
	// Check input values
	if ((str1) && (str2) && (strlen(str1) > 0) && (strlen(str2) > 0)) 
	{
		char tmpStr1[STRING_LENGTH];
		char tmpStr2[STRING_LENGTH];

		// Copy input values
		strcpy(tmpStr1, str1);
		strcpy(tmpStr2, str2);

		// Ignore case
		strupr(tmpStr1);
		strupr(tmpStr2);

		int str1Len = strlen(tmpStr1);
		int str2Len = strlen(tmpStr2);

		// Count barrier 
		int barrier = 0;
		if (str1Len > str2Len) barrier = str2Len * 2;
		else barrier = str1Len * 2;

		// Get percents
		int fuzzy = IndistinctMatching(4, tmpStr1, tmpStr2);

		return (fuzzy > barrier);
	}
	else
		return 0;
}


