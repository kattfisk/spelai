#ifndef INCLUDED_EAL
#define INCLUDED_EAL



/******************************************************************************

This component implements top level functionality in Evolutionary algorithm
library (EAL). Currently this amounts to no functions at all.

All lower level headers are also included, for convenience, by including this 
header.

*******************************************************************************/



#include "EALGene.h"
#include "EALGenome.h"
#include "EALMutator.h"
#include "EALIndividual.h"
#include "EALEvaluator.h"
#include "EALCombinator.h"
#include "EALPopulation.h"
#include "EALSelector.h"
#include "EALEvolver.h"



struct EALEvolutionaryAlgorithm{
};

#endif