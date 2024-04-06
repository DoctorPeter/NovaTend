/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : DllUserChecker.cpp

   Description :  this module implements methods 
				  of class DllUserChecker

*****************************************************************/

#include "stdafx.h"

#include "DllUserChecker.h"

#include <string.h>

/****************************************************************

   Class : DllUserChecker

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				dllDefinition - pointer to DLL 
								definition structure


*****************************************************************/
DllUserChecker :: DllUserChecker(DLL_ID dllUser, PDLL_COMMON_DEFINITION dllDefinition)
{
	SetParams(dllUser, dllDefinition);
}

/****************************************************************

   Class : DllUserChecker

   Method : SetParams

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				dllDefinition - pointer to DLL 
								definition structure
	
	Description: Set DllUserChecker parameters

*****************************************************************/
void DllUserChecker :: SetParams(DLL_ID dllUser, PDLL_COMMON_DEFINITION dllDefinition)
{
	this -> dllUser = dllUser;
	this -> dllDefinition = dllDefinition;
}

/****************************************************************

   Class : DllUserChecker

   Method : CheckUser
   
   Return: zero - if user is legal 
		   else - non zero	

   Description: Check some DLL user

*****************************************************************/
unsigned short DllUserChecker :: CheckUser(void)
{
	// Check DLL definition instance
	if (dllDefinition)
	{
		unsigned long int checkSum = 0;
	
		// Counting checksum
		for(unsigned short i = 0; i < dllDefinition -> userCount; i++)
			checkSum ^= (dllDefinition -> legalUsers[i]) & (~dllUser);

		unsigned short overlapCounter = 0;
		unsigned long int partialCheckSum;

		for(unsigned short i = 0; i < dllDefinition -> userCount; i++)
		{
			partialCheckSum = 0;

			// Counting partial checksum
			for(unsigned short j = 0; j < dllDefinition -> userCount; j++)
				if (j != i) 
					partialCheckSum ^= (dllDefinition -> legalUsers[j]) & (~dllUser);

			// Counting overlaps 
			overlapCounter += !(checkSum == partialCheckSum);
		}	

		// Perform and return result
		return !(overlapCounter == dllDefinition -> userCount - 1);
	}
	else
	{
		// Error code
		return 0xFF;
	}
}
