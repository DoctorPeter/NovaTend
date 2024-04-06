/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : RandomGenerator.h

   Description :  this module defines interface of 
				  class RandomGenerator. This class is 
				  designed to define generator of random numbers.

*****************************************************************/

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

// Maximum random value
#define MAX_RAND_VALUE	1000000000


/****************************************************************

   Class : RandomGenerator

   Description : generator of random numbers
                
*****************************************************************/
class RandomGenerator
{
	private:

		// Random seed
		unsigned int seed;

		// Parameters of random ganerstor polinom
		unsigned int A;
		unsigned int B;

		// Previous random value
		unsigned int previousVal;

	public:

		// Constructor
		RandomGenerator(void);

		// Destructor
		virtual ~RandomGenerator(void);

		// Get random number in range [0 - MAX_RAND_VALUE]
		unsigned int GenerateRandomValue(void);
};

#endif