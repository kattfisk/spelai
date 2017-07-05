#ifndef INCLUDED_EALINDIVIDUAL
#define INCLUDED_EALINDIVIDUAL



/******************************************************************************

This component implments an individual type that associates a genome and a 
fitness value.

*******************************************************************************/



#include "EALGenome.h"



class EALIndividual{
public:

	/* Public creators */
	EALIndividual(const EALGenome &genome = EALGenome(), double fitness = 0.0);

	/* Public manipulators */
	void randomize();
	void setFitness(double fitness);
	void setGenome(const EALGenome &genome);

	/* Public accessors */
	double           getFitness() const;
	const EALGenome& getGenome()  const;

private:

	/* Private data */
	EALGenome mGenome;
	double    mFitness;
};

#endif