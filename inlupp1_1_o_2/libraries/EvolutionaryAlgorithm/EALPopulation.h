#ifndef INCLUDED_EALPOPULATION
#define INCLUDED_EALPOPULATION



/******************************************************************************

This component implements a population type consisting of individuals.

*******************************************************************************/



#include "EALIndividual.h"
#include <vector>



class EALPopulation{
public:

	/* Public creators */
	EALPopulation();
	EALPopulation(const EALPopulation &population);
	~EALPopulation();

	/* Public manipulators */
	void           addIndividual(const EALIndividual &individual);
	void           clear();
	EALPopulation& operator=(const EALPopulation &population);
	void           sort();

	/* Public accessors */
	double               getAverageFitness()                const;
	const EALIndividual& getIndividual(int individualIndex) const; 
	int                  getIndividualCount()               const;	
	double               getMaximumFitness()                const;
	double               getMinimumFitness()                const;
	double               getSumFitness()                    const;
	bool                 isEmpty()                          const;
	const EALIndividual& operator[](int individualIndex)    const; 

private:

	/* Private types */
	typedef std::vector<EALIndividual> IndividualVector;
	
	struct Cache{
		Cache() : mIsValid(false), mMinimumFitness(0.0), mMaximumFitness(0.0), mSumFitness(0.0), mAverageFitness(0.0){}
		bool    mIsValid;
		double  mMinimumFitness;
		double  mMaximumFitness;
		double  mSumFitness;
		double  mAverageFitness;	
	};

	/* Private accessors */	
	void invalidateCache()        const;
	bool invariant()              const;
	void updateCacheIfNecessary() const;

	/* Private data */
	IndividualVector mIndividuals;
	mutable Cache    mCache;
};

#endif
