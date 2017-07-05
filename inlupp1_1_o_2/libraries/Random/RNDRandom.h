#ifndef INCLUDED_RNDRANDOM
#define INCLUDED_RNDRANDOM



/******************************************************************************

This component implements functions to generate different types of pseudo
random values. Internally, the component uses a randomizer for this purpose.
When it comes to generators, this component prefers quality to speed. The
generator is also seeded using ALL_SOURCES.

*******************************************************************************/



struct RNDRandom{

	/* Public functions */
	static bool   generateBoolean(double probabilityOfTruth);		
	static double generateNormalReal(double mean, double standardDeviation);
	static int    generateUniformInteger(int minimum, int maximum);
	static double generateUniformReal(double minimum, double maximum);
};

#endif