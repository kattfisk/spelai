#include "EALIndividual.h"
#include "EALGenome.h"



/* EALIndividual */

/* Public creators */
EALIndividual::EALIndividual(const EALGenome &genome, double fitness) :
	mGenome(genome),
	mFitness(fitness){
}

/* Public manipulators */
void EALIndividual::randomize(){
	mGenome.randomize();	
}

void EALIndividual::setFitness(double fitness){
	mFitness = fitness;
}

void EALIndividual::setGenome(const EALGenome &genome){
	mGenome = genome;
}

/* Public accessors */
double EALIndividual::getFitness() const{
	return mFitness;
}

const EALGenome& EALIndividual::getGenome() const{
	return mGenome;
}

