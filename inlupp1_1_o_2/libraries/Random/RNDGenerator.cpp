#include "RNDGenerator.h"
#include "DBGDebug.h"



/* File scope data */
static const long fLEHMER_MULTIPLIER = 16807;
static const long fLEHMER_MODULIZER  = 2147483647;
static const long fMIN_LEHMER_SEED   = 1;
static const long fMAX_LEHMER_SEED   = fLEHMER_MODULIZER - 1;



/* File scope functions */
static long fLehmerSeed(double seed){
	DBGAssert((0.0 <= seed) && (seed <= 1.0));
	const long DELTA_LEHMER_SEED = fMAX_LEHMER_SEED - fMIN_LEHMER_SEED;
	long       lehmerSeed        = fMIN_LEHMER_SEED + long(seed * DELTA_LEHMER_SEED);
	if(lehmerSeed == fLEHMER_MODULIZER){
		lehmerSeed = fMAX_LEHMER_SEED;
	}
	DBGAssert((fMIN_LEHMER_SEED <= lehmerSeed) && (lehmerSeed <= fMAX_LEHMER_SEED));
	return lehmerSeed;
}




/* RNDGeneratorImp */

/* Public creators */
RNDGeneratorImp::~RNDGeneratorImp(){
}




/* RNDLehmerGeneratorImp */

/* Public creators */
RNDLehmerGeneratorImp::RNDLehmerGeneratorImp(double seed) :
	mSeed(fLehmerSeed(seed)){

	DBGAssert(invariant());
}

RNDLehmerGeneratorImp::~RNDLehmerGeneratorImp(){
	DBGAssert(invariant());

	mSeed = 0;

	DBGAssert(!invariant());
}

/* Public manipulators */
double RNDLehmerGeneratorImp::generate(){
	DBGDebugAssert(invariant());

	const long QUOTIENT  = fLEHMER_MODULIZER / fLEHMER_MULTIPLIER;
	const long REMAINDER = fLEHMER_MODULIZER % fLEHMER_MULTIPLIER;
	const long HIGH      = mSeed / QUOTIENT;
	const long LOW       = mSeed % QUOTIENT;
	const long TEST      = (fLEHMER_MULTIPLIER * LOW) - (REMAINDER * HIGH);
	if(0 < TEST){
		mSeed = TEST;
	}
	else{
		mSeed = TEST + fLEHMER_MODULIZER;
	}
	double fraction = double(mSeed - 1) / double(fLEHMER_MODULIZER - 2);
	if(fraction < 0.0){
		fraction = 0.0;
	}
	if(1.0 < fraction){
		fraction = 1.0;
	}
	DBGDebugAssert((0.0 <= fraction) && (fraction <= 1.0));

	DBGDebugAssert(invariant());

	return fraction;
}

/* Public accessors */
RNDLehmerGeneratorImp* RNDLehmerGeneratorImp::clone() const{
	DBGAssert(invariant());

	RNDLehmerGeneratorImp *clone = new RNDLehmerGeneratorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

/* Private creators */
RNDLehmerGeneratorImp::RNDLehmerGeneratorImp(const RNDLehmerGeneratorImp &lehmerGeneratorImp) :
	mSeed(lehmerGeneratorImp.mSeed){

	DBGAssert(invariant());
}

/* Private accessors */
bool RNDLehmerGeneratorImp::invariant() const{
	const bool invariant = (0 < mSeed) && (mSeed < fLEHMER_MODULIZER);
	return invariant;
}




/* RNDGenerator */

/* Public creators */
RNDGenerator::RNDGenerator(const RNDGeneratorImp &generatorImp) :
	mGeneratorImp(generatorImp.clone()){
	
	DBGAssert(invariant());	
}

RNDGenerator::RNDGenerator(const RNDGenerator &generator) :
	mGeneratorImp(generator.mGeneratorImp->clone()){
	
	DBGAssert(invariant());	
}

RNDGenerator::~RNDGenerator(){
	DBGAssert(invariant());	

	delete mGeneratorImp;
	mGeneratorImp = 0;

	DBGAssert(!invariant());	
}

/* Public manipulators */
double RNDGenerator::generate(){
	DBGDebugAssert(invariant());	

	const double FRACTION = mGeneratorImp->generate();
	DBGDebugAssert((0.0 <= FRACTION) && (FRACTION <= 1.0));	

	DBGDebugAssert(invariant());	

	return FRACTION;	
}

RNDGenerator& RNDGenerator::operator=(const RNDGenerator &generator){
	DBGAssert(invariant());

	if(this != &generator){
		delete mGeneratorImp;
		mGeneratorImp = generator.mGeneratorImp->clone();
	}

	DBGAssert(invariant());

	return *this;
}

/* Private accessors */
bool RNDGenerator::invariant() const{
	const bool invariant = 0 != mGeneratorImp;
	return invariant;
}

