#include "EALEvolver.h"
#include "EALGene.h"
#include "EALGenome.h"
#include "EALMutator.h"
#include "EALIndividual.h"
#include "EALEvaluator.h"
#include "EALCombinator.h"
#include "EALPopulation.h"
#include "EALSelector.h"
#include "RNDRandom.h"
#include "DBGDebug.h"



/* EALEvolverImp */

/* Public creators */
EALEvolverImp::~EALEvolverImp(){
}



/* EALNullEvolverImp */

/* Public creators */
EALNullEvolverImp::EALNullEvolverImp() :
	EALEvolverImp(){
}

/* Public accessors */
EALNullEvolverImp* EALNullEvolverImp::clone() const{
	EALNullEvolverImp *clone = new EALNullEvolverImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

void EALNullEvolverImp::evolve(EALPopulation &population) const{
}

/* Private creators */
EALNullEvolverImp::EALNullEvolverImp(const EALNullEvolverImp &nullEvolverImp) :
	EALEvolverImp(nullEvolverImp){
}



/* EALBasicEvolverImp */

/* Public creators */
EALBasicEvolverImp::EALBasicEvolverImp(
	const EALEvaluator  &evaluator,
	const EALSelector   &selector,
	const EALCombinator &combinator,
	const EALMutator    &mutator,
	double              combinationProbability,
	double              mutationProbability
) :
	mEvaluator(evaluator),
	mSelector(selector),
	mCombinator(combinator),
	mMutator(mutator),
	mCombinationProbability(combinationProbability),
	mMutationProbability(mutationProbability){

	DBGAssert(invariant());	
}

EALBasicEvolverImp* EALBasicEvolverImp::clone() const{
	DBGAssert(invariant());	

	EALBasicEvolverImp *clone = new EALBasicEvolverImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

void EALBasicEvolverImp::evolve(EALPopulation &population) const{
	EALPopulation childPopulation;
	while(childPopulation.getIndividualCount() < population.getIndividualCount()){
		EALGenome childGenome0 = mSelector.select(population).getGenome();
		EALGenome childGenome1 = mSelector.select(population).getGenome();
		if(RNDRandom::generateBoolean(mCombinationProbability)){
			mCombinator.combine(childGenome0, childGenome1);
		}
		for(int i = 0; i < childGenome0.getGeneCount(); i++){
			if(RNDRandom::generateBoolean(mMutationProbability)){
				mMutator.mutate(childGenome0[i]);
			}
		}
		for(int i = 0; i < childGenome1.getGeneCount(); i++){
			if(RNDRandom::generateBoolean(mMutationProbability)){
				mMutator.mutate(childGenome1[i]);
			}
		}
		childPopulation.addIndividual(EALIndividual(childGenome0, mEvaluator.evaluate(childGenome0)));
		if(childPopulation.getIndividualCount() < population.getIndividualCount()){
			childPopulation.addIndividual(EALIndividual(childGenome1, mEvaluator.evaluate(childGenome1)));		
		}	
	}
	DBGDebugAssert(childPopulation.getIndividualCount() == population.getIndividualCount());
	population = childPopulation;
}

/* Private creators */
EALBasicEvolverImp::EALBasicEvolverImp(const EALBasicEvolverImp &basicEvolverImp) :
	EALEvolverImp(basicEvolverImp),
	mEvaluator(basicEvolverImp.mEvaluator),
	mSelector(basicEvolverImp.mSelector),
	mCombinator(basicEvolverImp.mCombinator),
	mMutator(basicEvolverImp.mMutator),
	mCombinationProbability(basicEvolverImp.mCombinationProbability),
	mMutationProbability(basicEvolverImp.mMutationProbability){

	DBGAssert(invariant());	
}

/* Private accessors */
bool EALBasicEvolverImp::invariant() const{
	const bool invariant = 
		((0.0 <= mCombinationProbability) && (mCombinationProbability <= 1.0)) &&
		((0.0 <= mMutationProbability) && (mMutationProbability <= 1.0));
	return invariant;
}



/* EALEvolver */

/* Public creators */
EALEvolver::EALEvolver(const EALEvolverImp &evolverImp) :
	mEvolverImp(evolverImp.clone()){

	DBGAssert(invariant());
}

EALEvolver::EALEvolver(const EALEvolver &evolver) :
	mEvolverImp(evolver.mEvolverImp->clone()){
	
	DBGAssert(invariant());
}

EALEvolver::~EALEvolver(){
	DBGAssert(invariant());

	delete mEvolverImp;
	mEvolverImp = 0;

	DBGAssert(!invariant());
}

/* Public manipulators */
EALEvolver& EALEvolver::operator=(const EALEvolver &evolver){
	DBGAssert(invariant());

	if(this != &evolver){
		delete mEvolverImp;
		mEvolverImp = evolver.mEvolverImp->clone();
	}

	DBGAssert(invariant());
	return *this;
}

/* public accessors */
void EALEvolver::evolve(EALPopulation &population) const{
	DBGAssert(invariant());

	mEvolverImp->evolve(population);
}

/* Private accessors */
bool EALEvolver::invariant() const{
	const bool invariant = (0 != mEvolverImp);
	return invariant;
}


