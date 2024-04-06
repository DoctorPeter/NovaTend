/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : RandomGenerator.cpp

   Description :  this module implements methods of 
				  class RandomGenerator

*****************************************************************/
#include "stdafx.h"
#include "RandomGenerator.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

/****************************************************************

   Class : RandomGenerator

   Method : Constructor

*****************************************************************/
RandomGenerator :: RandomGenerator(void)
{
	// Set random seed
	srand(GetTickCount());
	seed = rand();

	// Set random value for A
	do
	{
		A = (rand() + 1024) % 65535;
	}
	while ((A % 2) == 1);

	// Set random value for B
	do
	{
		B = (rand() + 1024) % 65535;
	}
	while ((B % 4) == 1);

	previousVal = seed;
}

/****************************************************************

   Class : RandomGenerator

   Method : Destructor

*****************************************************************/
RandomGenerator :: ~RandomGenerator(void)
{
	// for future use
}

/****************************************************************

   Class : RandomGenerator

   Method : GenerateRandomValue

   Returns : random number

   Description: Get random number in range [0 - MAX_RAND_VALUE]

*****************************************************************/
unsigned int RandomGenerator :: GenerateRandomValue()
{
	previousVal = (A * previousVal + B) % MAX_RAND_VALUE;
	return previousVal;
}