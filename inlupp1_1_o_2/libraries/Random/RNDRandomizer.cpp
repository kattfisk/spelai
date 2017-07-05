#include "RNDRandomizer.h"
#include "DBGDebug.h"
#include <cmath>



using namespace std;




/* RNDRandomizer */

/* Public creators */
RNDRandomizer::RNDRandomizer(const RNDGenerator &generator) :
	mGenerator(generator),
	mCachedZ1(0.0),
	mCacheIsValid(false){
}

/* Public manipulators */
bool RNDRandomizer::generateBoolean(double probabilityOfTruth){
	DBGDebugAssert((0.0 <= probabilityOfTruth) && (probabilityOfTruth <= 1.0));

	bool boolean = false;
	if(0.0 == probabilityOfTruth){
		boolean = false;
	}
	else if(1.0 == probabilityOfTruth){
		boolean = true;
	}
	else if((0.0 < probabilityOfTruth) && (probabilityOfTruth < 1.0)){
		const double FRACTION = mGenerator.generate();
		boolean               = (FRACTION < probabilityOfTruth) ? (true) : (false);
	}
	else{
		DBGError("Probability of truth must be in [0.0, 1.0].");	
	}
	return boolean;
}		

double RNDRandomizer::generateNormalReal(double mean, double standardDeviation){
	DBGDebugAssert(0.0 <= standardDeviation);

	double normalReal = 0.0;
	if(0.0 == standardDeviation){
		normalReal = mean;	
	}
	else if(0.0 < standardDeviation){
		double z = 0.0;
		if(mCacheIsValid){
			z             = mCachedZ1;
			mCacheIsValid = false;
		}
		else{
			double x, y, squareLength;
			do{
				x            = (2.0 * mGenerator.generate()) - 1.0;
				y            = (2.0 * mGenerator.generate()) - 1.0;
				squareLength = (x * x) + (y * y); 
			}while((squareLength == 0.0) || (1.0 < squareLength));
			DBGDebugAssert((0.0 < squareLength) && (squareLength <= 1.0));
			const double FACTOR = sqrt((-2.0 * log(squareLength)) / squareLength);
			const double Z0     = x * FACTOR;
			const double Z1     = y * FACTOR;
			z                   = Z0;
			mCachedZ1           = Z1;
			mCacheIsValid       = true;
		}
		normalReal = mean + (z * standardDeviation);	
	}
	else{
		DBGError("Standard deviation must be larger than or equal to 0.0.");
	}
	return normalReal;
}

int RNDRandomizer::generateUniformInteger(int minimum, int maximum){
	DBGDebugAssert(minimum <= maximum);

	int uniformInteger = 0;
	if(minimum == maximum){
		uniformInteger = minimum;
	}
	else if(minimum < maximum){
		const double FRACTION  = mGenerator.generate();
		const int    DELTA     = maximum - minimum;
	    uniformInteger         = minimum + int(FRACTION * (DELTA + 1));
		if(uniformInteger < minimum){
			uniformInteger = minimum;
		}
		if(maximum < uniformInteger){
			uniformInteger = maximum;
		}
	}
	else{
		DBGError("Maximum must be larger than or equal to minimum.");
	}
	DBGDebugAssert((minimum <= uniformInteger) && (uniformInteger <= maximum));
	return uniformInteger;
}

double RNDRandomizer::generateUniformReal(double minimum, double maximum){
	DBGDebugAssert(minimum <= maximum);

	double uniformReal = 0.0;
	if(minimum == maximum){
		uniformReal = minimum;	
	}
	else if(minimum < maximum){
		const double FRACTION  = mGenerator.generate();
		const double DELTA     = maximum - minimum;
	    uniformReal            = minimum + (FRACTION * DELTA);	
		if(uniformReal < minimum){
			uniformReal = minimum;
		}
		if(maximum < uniformReal){
			uniformReal = maximum;
		}
	}
	else{
		DBGError("Maximum must be larger than or equal to minimum.");
	}
	DBGDebugAssert((minimum <= uniformReal) && (uniformReal <= maximum));
	return uniformReal;
}

