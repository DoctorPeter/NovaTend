/****************************************************************

   Solution : NovaTend

   Project : z-scheduler-01.dll

   Module : FuzzyStringCompare.h

   Description :  this module defines interface of
				  functions for fuzzy string comparsion

*****************************************************************/

// Max string length
#define STRING_LENGTH		256

// String matching count struct
typedef struct _stringMatchingCount
{
	// Count of substring count
	int lngSubRows;

	// Count of reached substrings
	int lngCountLike;

} STRING_MATCHING_COUNT, *PSTRING_MATCHING_COUNT;

// Indistinc matching of two strings
int IndistinctMatching(int maxMatching, char * strInputMatching, char * strInputStandart);

// Fuzzy string comparsion
bool FuzzyStrCmp(char * str1, char * str2);