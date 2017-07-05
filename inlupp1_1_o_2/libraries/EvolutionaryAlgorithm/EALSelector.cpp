#include "EALSelector.h"
#include "EALIndividual.h"
#include "EALPopulation.h"
#include "RNDRandom.h"
#include "DBGDebug.h"



/* EALSelectorImp */

/* Public creators */
EALSelectorImp::~EALSelectorImp(){
}



/* EALNullSelectorImp */

/* Public creators */
EALNullSelectorImp::EALNullSelectorImp() :
	EALSelectorImp(){
}

/* Public accessors */
EALNullSelectorImp* EALNullSelectorImp::clone() const{
	EALNullSelectorImp *clone = new EALNullSelectorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

const EALIndividual& EALNullSelectorImp::select(const EALPopulation &population) const{
	DBGDebugAssert(!population.isEmpty());

	return population[0];
}

/* Private creators */
EALNullSelectorImp::EALNullSelectorImp(const EALNullSelectorImp &nullSelectorImp) :
	EALSelectorImp(nullSelectorImp){
}



/* EALRouletteSelectorImp */

/* Public creators */
EALRouletteSelectorImp::EALRouletteSelectorImp() :
	EALSelectorImp(){
}

/* Public accessors */
EALRouletteSelectorImp* EALRouletteSelectorImp::clone() const{
	EALRouletteSelectorImp *clone = new EALRouletteSelectorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

const EALIndividual& EALRouletteSelectorImp::select(const EALPopulation &population) const{
	DBGDebugAssert(!population.isEmpty());
	DBGDebugAssert(0.0 <= population.getSumFitness());

	const int    INDIVIDUAL_COUNT = population.getIndividualCount();
	const double SUM_FITNESS      = population.getSumFitness();
	const double NEEDLE           = RNDRandom::generateUniformReal(0.0, SUM_FITNESS);
	double       sumSlice         = 0.0;
	for(int i = 0; i < INDIVIDUAL_COUNT; i++){
		sumSlice += population[i].getFitness();
		if(NEEDLE <= sumSlice){
			return population[i];
		}
	}
	return population[INDIVIDUAL_COUNT - 1];
}

/* Private creators */
EALRouletteSelectorImp::EALRouletteSelectorImp(const EALRouletteSelectorImp &rouletteSelectorImp) :
	EALSelectorImp(rouletteSelectorImp){
}



/* EALTournamentSelectorImp */

/* Public creators */
EALTournamentSelectorImp::EALTournamentSelectorImp(int individualCount) :
	EALSelectorImp(),
	mParticipantCount(individualCount){
	
	DBGAssert(invariant());
}

/* Public accessors */	
EALTournamentSelectorImp* EALTournamentSelectorImp::clone() const{
	DBGAssert(invariant());

	EALTournamentSelectorImp *clone = new EALTournamentSelectorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

const EALIndividual& EALTournamentSelectorImp::select(const EALPopulation &population) const{
	DBGDebugAssert(invariant());
	DBGDebugAssert(!population.isEmpty());

	const int INDIVIDUAL_COUNT = population.getIndividualCount();
	int       bestIndex        = RNDRandom::generateUniformInteger(0, INDIVIDUAL_COUNT - 1);
	for(int i = 0; i < mParticipantCount - 1; i++){
		const int INDEX = RNDRandom::generateUniformInteger(0, INDIVIDUAL_COUNT - 1);
		if(population[bestIndex].getFitness() < population[INDEX].getFitness()){
			bestIndex = INDEX;
		}
	}
	return population[bestIndex];
}

/* Private creators */
EALTournamentSelectorImp::EALTournamentSelectorImp(const EALTournamentSelectorImp &tournamentSelectorImp) :
	EALSelectorImp(tournamentSelectorImp),
	mParticipantCount(tournamentSelectorImp.mParticipantCount){
	
	DBGAssert(invariant());
}

/* Private accessors */
bool EALTournamentSelectorImp::invariant() const{
	const bool invariant = (0 < mParticipantCount);
	return invariant;
}



/* EALSelector */

/* Public creators */
EALSelector::EALSelector(const EALSelectorImp &selectorImp) :
	mSelectorImp(selectorImp.clone()){

	DBGAssert(invariant());
}

EALSelector::EALSelector(const  EALSelector &selector) :
	mSelectorImp(selector.mSelectorImp->clone()){
	
	DBGAssert(invariant());
}

EALSelector::~EALSelector(){
	DBGAssert(invariant());
	
	delete mSelectorImp;
	mSelectorImp = 0;

	DBGAssert(!invariant());
}

/* Public manipulators */
EALSelector& EALSelector::operator=(const EALSelector &selector){
	DBGAssert(invariant());

	if(this != &selector){
		delete mSelectorImp;
		mSelectorImp = selector.mSelectorImp->clone();
	}

	DBGAssert(invariant());
	return *this;
}

/* Public accessors */
const EALIndividual& EALSelector::select(const EALPopulation &population) const{
	DBGDebugAssert(invariant());

	return mSelectorImp->select(population);
}

/* Private accessors */
bool EALSelector::invariant() const{
	const bool invariant = (0 != mSelectorImp);
	return invariant;
}
