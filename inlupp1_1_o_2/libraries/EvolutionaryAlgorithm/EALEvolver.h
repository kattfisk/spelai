#ifndef INCLUDED_EALEVOLVER
#define INCLUDED_EALEVOLVER



/******************************************************************************

This component implements evolvers each of which evolves a population into
its next generation.

*******************************************************************************/



#include "EALMutator.h"
#include "EALEvaluator.h"
#include "EALCombinator.h"
#include "EALSelector.h"



class EALPopulation;



class EALEvolverImp{
public:

	/* Public creators */
	virtual ~EALEvolverImp();
	
	/* Public accessors */
	virtual EALEvolverImp* clone()                           const = 0;
	virtual void           evolve(EALPopulation &population) const = 0;
};



class EALNullEvolverImp : public EALEvolverImp{
public:

	/* Public creators */
	EALNullEvolverImp();

	/* Public accessors */
	virtual EALNullEvolverImp* clone()                           const;
	virtual void               evolve(EALPopulation &population) const;

private:

	/* Private creators */
	EALNullEvolverImp(const EALNullEvolverImp &nullEvolverImp);

	/* Private manipulators */
	EALNullEvolverImp& operator=(const EALNullEvolverImp &nullEvolverImp);
};



class EALBasicEvolverImp : public EALEvolverImp{
public:

	/* Public creators */
	EALBasicEvolverImp(
		const EALEvaluator  &evaluator,
		const EALSelector   &selector,
		const EALCombinator &combinator,
		const EALMutator    &mutator,
		double              combinationProbability,
		double              mutationProbability
	);

	/* Public accessors */
	virtual EALBasicEvolverImp* clone()                           const;
	virtual void                evolve(EALPopulation &population) const;

private:

	/* Private creators */
	EALBasicEvolverImp(const EALBasicEvolverImp &basicEvolverImp);

	/* Private manipulators */
	EALBasicEvolverImp& operator=(const EALBasicEvolverImp &basicEvolverImp);

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	EALEvaluator  mEvaluator;
	EALSelector   mSelector;
	EALCombinator mCombinator;
	EALMutator    mMutator;
	double        mCombinationProbability;
	double        mMutationProbability;
};



class EALEvolver{
public:

	/* Public creators */
	EALEvolver(const EALEvolverImp &evolverImp = EALNullEvolverImp());
	EALEvolver(const EALEvolver &evolver);
	~EALEvolver();

	/* Public manipulators */
	EALEvolver& operator=(const EALEvolver &evolver);

	/* public accessors */
	void evolve(EALPopulation &population) const;

private:

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	EALEvolverImp *mEvolverImp;
};

#endif