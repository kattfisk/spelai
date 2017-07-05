#include "EALCombinator.h"
#include "EALGene.h"
#include "EALGenome.h"
#include "RNDRandom.h"
#include "DBGDebug.h"



/* File scope functions */
static inline void fSwap(EALGene &gene0, EALGene &gene1){
	EALGene tempGene(gene0);
	gene0 = gene1;
	gene1 = tempGene;
}


/* EALCombinatorImp */

/* Public creators */
EALCombinatorImp::~EALCombinatorImp(){
}



/* EALNullCombinatorImp */

/* Public creators */
EALNullCombinatorImp::EALNullCombinatorImp() :
	EALCombinatorImp(){
}

/* Public accessors */
EALNullCombinatorImp* EALNullCombinatorImp::clone() const{
	EALNullCombinatorImp *clone = new EALNullCombinatorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

void EALNullCombinatorImp::combine(EALGenome &genome0, EALGenome &genome1) const{
}

/* Private creators */
EALNullCombinatorImp::EALNullCombinatorImp(const EALNullCombinatorImp &nullCombinatorImp) :
	EALCombinatorImp(nullCombinatorImp){
}



/* EALSingleCombinatorImp */

/* Public creators */
EALSingleCombinatorImp::EALSingleCombinatorImp() :
	EALCombinatorImp(){
}

/* Public accessors */
EALSingleCombinatorImp* EALSingleCombinatorImp::clone() const{
	EALSingleCombinatorImp *clone = new EALSingleCombinatorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

void EALSingleCombinatorImp::combine(EALGenome &genome0, EALGenome &genome1) const{
	DBGDebugAssert(0 < genome0.getGeneCount());
	DBGDebugAssert(0 < genome1.getGeneCount());
	DBGDebugAssert(genome0.getGeneCount() == genome1.getGeneCount());

	const int GENE_COUNT = genome0.getGeneCount();
	const int FROM       = RNDRandom::generateUniformInteger(0, GENE_COUNT - 1);
	for(int i = FROM; i < GENE_COUNT; i++){
		fSwap(genome0[i], genome1[i]);
	}
}

/* Private creators */
EALSingleCombinatorImp::EALSingleCombinatorImp(const EALSingleCombinatorImp &singleCombinatorImp) :
	EALCombinatorImp(singleCombinatorImp){
}



/* EALDualCombinatorImp */

/* Public creators */
EALDualCombinatorImp::EALDualCombinatorImp() :
	EALCombinatorImp(){
}

/* Public accessors */
EALDualCombinatorImp* EALDualCombinatorImp::clone() const{
	EALDualCombinatorImp *clone = new EALDualCombinatorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

void EALDualCombinatorImp::combine(EALGenome &genome0, EALGenome &genome1) const{
	DBGDebugAssert(0 < genome0.getGeneCount());
	DBGDebugAssert(0 < genome1.getGeneCount());
	DBGDebugAssert(genome0.getGeneCount() == genome1.getGeneCount());

	const int GENE_COUNT = genome0.getGeneCount();
	const int FROM       = RNDRandom::generateUniformInteger(0, GENE_COUNT - 1);
	const int TO         = RNDRandom::generateUniformInteger(FROM, GENE_COUNT - 1);
	for(int i = FROM; i <= TO; i++){
		fSwap(genome0[i], genome1[i]);
	}
}

/* Private creators */
EALDualCombinatorImp::EALDualCombinatorImp(const EALDualCombinatorImp &dualCombinatorImp) :
	EALCombinatorImp(dualCombinatorImp){
}



/* EALCombinator */

/* Public creators */
EALCombinator::EALCombinator(const EALCombinatorImp &combinatorImp) :
	mCombinatorImp(combinatorImp.clone()){

	DBGAssert(invariant());	
}

EALCombinator::EALCombinator(const EALCombinator &combinator) :
	mCombinatorImp(combinator.mCombinatorImp->clone()){

	DBGAssert(invariant());	
}

EALCombinator::~EALCombinator(){
	DBGAssert(invariant());	

	delete mCombinatorImp;
	mCombinatorImp = 0;

	DBGAssert(!invariant());	
}

/* Public manipulators */
EALCombinator& EALCombinator::operator=(const EALCombinator &combinator){
	DBGAssert(invariant());	

	if(this != &combinator){
		delete mCombinatorImp;
		mCombinatorImp = combinator.mCombinatorImp->clone();
	}

	DBGAssert(invariant());	
	return *this;
}

/* Public accessors */
void EALCombinator::combine(EALGenome &genome0, EALGenome &genome1) const{
	DBGDebugAssert(invariant());	

	mCombinatorImp->combine(genome0, genome1);
}

/* Private accessors */	
bool EALCombinator::invariant() const{
	const bool invariant = (0 != mCombinatorImp);
	return invariant;
}
