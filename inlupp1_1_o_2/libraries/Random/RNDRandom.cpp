#include "RNDRandom.h"
#include "RNDGenerator.h"
#include "RNDSeeder.h"
#include "RNDRandomizer.h"
#include "DBGDebug.h"



/* File scope functions */
static RNDRandomizer& fRandomizer(){
	static RNDRandomizer randomizer(RNDGenerator(RNDLehmerGeneratorImp(RNDSeeder::generateSeed(RNDSeeder::ALL_SOURCES))));
	return randomizer;
}



/* RND */

/* Public functions */
bool RNDRandom::generateBoolean(double probabilityOfTruth){
	DBGDebugAssert((0.0 <= probabilityOfTruth) && (probabilityOfTruth <= 1.0));

	const bool boolean = fRandomizer().generateBoolean(probabilityOfTruth);
	return boolean;
}

double RNDRandom::generateNormalReal(double mean, double standardDeviation){
	DBGDebugAssert(0.0 <= standardDeviation);

	const double NORMAL_REAL = fRandomizer().generateNormalReal(mean, standardDeviation);
	return NORMAL_REAL;
}

int RNDRandom::generateUniformInteger(int minimum, int maximum){
	DBGDebugAssert(minimum <= maximum);

	const int UNIFORM_INTEGER = fRandomizer().generateUniformInteger(minimum, maximum);
	DBGDebugAssert((minimum <= UNIFORM_INTEGER) && (UNIFORM_INTEGER <= maximum));
	return UNIFORM_INTEGER;
}

double RNDRandom::generateUniformReal(double minimum, double maximum){
	DBGDebugAssert(minimum <= maximum);

	const double UNIFORM_REAL = fRandomizer().generateUniformReal(minimum, maximum);
	DBGDebugAssert((minimum <= UNIFORM_REAL) && (UNIFORM_REAL <= maximum));
	return UNIFORM_REAL;
}

