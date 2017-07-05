#ifndef INCLUDED_RNDRANDOMIZER
#define INCLUDED_RNDRANDOMIZER



/******************************************************************************

This component implements a randomizer type that can be used to generate series
of (pseudo) random values of different types. The type supports value semantics. 
After copy construction or after assignment, both instances involved are 
guaranteed to generate the same sequence. This is useful e.g. in order to 
reproduce a particular series at a later point in time.

*******************************************************************************/



#include "RNDGenerator.h"



class RNDRandomizer{
public:

	/* Public creators */
	RNDRandomizer(const RNDGenerator &generator = RNDGenerator());

	/* Public manipulators */
	bool   generateBoolean(double probabilityOfTruth);		
	double generateNormalReal(double mean, double standardDeviation);
	int    generateUniformInteger(int minimum, int maximum);
	double generateUniformReal(double minimum, double maximum);

private:

	/* Private data */
	RNDGenerator mGenerator;
	double       mCachedZ1;
	bool         mCacheIsValid;
};

#endif
