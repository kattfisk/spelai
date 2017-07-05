#include "EALPopulation.h"
#include "EALIndividual.h"
#include "DBGDebug.h"
#include <vector>
#include <algorithm>



/* File scope functions */
static inline bool fPopulationOrder(const EALIndividual &individual0, const EALIndividual &individual1){
	return (individual1.getFitness() < individual0.getFitness());
}




/* EALPopulation */

/* Public creators */
EALPopulation::EALPopulation() :
	mIndividuals(),
	mCache(){

	DBGAssert(invariant());	
}

EALPopulation::EALPopulation(const EALPopulation &population) :
	mIndividuals(population.mIndividuals),
	mCache(population.mCache){
	
	DBGDebugAssert(invariant());	
}

EALPopulation::~EALPopulation(){
	DBGDebugAssert(invariant());	

	mCache.mIsValid        = false;
	mCache.mMinimumFitness = 1.0;
	mCache.mMaximumFitness = 1.0;
	mCache.mSumFitness     = 1.0;
	mCache.mAverageFitness = 1.0;

	DBGDebugAssert(!invariant());	
}

/* Public manipulators */
void EALPopulation::addIndividual(const EALIndividual &individual){
	DBGDebugAssert(invariant());	

	mIndividuals.push_back(individual);
	invalidateCache();

	DBGDebugAssert(invariant());	
}

void EALPopulation::clear(){
	DBGDebugAssert(invariant());	

	mIndividuals.clear();
	invalidateCache();

	DBGDebugAssert(invariant());	
}

EALPopulation& EALPopulation::operator=(const EALPopulation &population){
	DBGDebugAssert(invariant());	

	mIndividuals = population.mIndividuals;
	mCache       = population.mCache;

	DBGDebugAssert(invariant());	
	return *this;
}

void EALPopulation::sort(){
	DBGDebugAssert(invariant());	

	std::sort(mIndividuals.begin(), mIndividuals.end(), fPopulationOrder); 
	invalidateCache();

	DBGDebugAssert(invariant());	
}

/* Public accessors */
double EALPopulation::getAverageFitness() const{
	DBGDebugAssert(invariant());	

	updateCacheIfNecessary();	

	DBGDebugAssert(invariant());	
	return mCache.mAverageFitness;
}

const EALIndividual& EALPopulation::getIndividual(int individualIndex) const{
	DBGDebugAssert(invariant());	
	DBGDebugAssert((0 <= individualIndex) && (individualIndex < int(mIndividuals.size())));

	return mIndividuals[individualIndex];
} 

int EALPopulation::getIndividualCount() const{
	DBGDebugAssert(invariant());	

	return int(mIndividuals.size());
}	

double EALPopulation::getMaximumFitness() const{
	DBGDebugAssert(invariant());	

	updateCacheIfNecessary();	

	DBGDebugAssert(invariant());	
	return mCache.mMaximumFitness;
}

double EALPopulation::getMinimumFitness() const{
	DBGDebugAssert(invariant());	

	updateCacheIfNecessary();	

	DBGDebugAssert(invariant());	
	return mCache.mMinimumFitness;
}

double EALPopulation::getSumFitness() const{
	DBGDebugAssert(invariant());	

	updateCacheIfNecessary();	

	DBGDebugAssert(invariant());	
	return mCache.mSumFitness;
}

bool EALPopulation::isEmpty() const{
	DBGDebugAssert(invariant());	

	return mIndividuals.empty();
}

	
const EALIndividual& EALPopulation::operator[](int individualIndex) const{
	DBGDebugAssert(invariant());	
	DBGDebugAssert((0 <= individualIndex) && (individualIndex < int(mIndividuals.size())));

	return mIndividuals[individualIndex];
} 


/* Private accessors */	
void EALPopulation::invalidateCache() const{
	mCache.mIsValid        = false;
	mCache.mMinimumFitness = 0.0;
	mCache.mMaximumFitness = 0.0;
	mCache.mSumFitness     = 0.0;
	mCache.mAverageFitness = 0.0;

}

bool EALPopulation::invariant() const{
	const bool validInvariant = 
		(mCache.mIsValid) &&
		(mCache.mMinimumFitness <= mCache.mMaximumFitness);
	const bool invalidInvariant =
		(!mCache.mIsValid) &&
		(0.0 == mCache.mMinimumFitness) &&
		(0.0 == mCache.mMaximumFitness) &&
		(0.0 == mCache.mSumFitness) &&
		(0.0 == mCache.mAverageFitness);
	const bool invariant = (validInvariant || invalidInvariant);
	return invariant;
}

void EALPopulation::updateCacheIfNecessary() const{
	if(!mCache.mIsValid){
		if(mIndividuals.empty()){
			mCache.mMinimumFitness = 0.0;
			mCache.mMaximumFitness = 0.0;
			mCache.mSumFitness     = 0.0;
			mCache.mAverageFitness = 0.0;			
		}
		else{
			const int INDIVIDUAL_COUNT = int(mIndividuals.size());
			double    minimumFitness   = mIndividuals[0].getFitness();
			double    maximumFitness   = mIndividuals[0].getFitness();
			double    sumFitness       = mIndividuals[0].getFitness();
			for(int i = 1; i < INDIVIDUAL_COUNT; i++){
				const double FITNESS = mIndividuals[i].getFitness();
				if(FITNESS < minimumFitness){
					minimumFitness = FITNESS;
				}
				if(maximumFitness < FITNESS){
					maximumFitness = FITNESS;
				}
				sumFitness += FITNESS;
			}
			mCache.mMinimumFitness = minimumFitness;
			mCache.mMaximumFitness = maximumFitness;
			mCache.mSumFitness     = sumFitness;
			mCache.mAverageFitness = (sumFitness / INDIVIDUAL_COUNT);
		}
		mCache.mIsValid = true;
	}
}


