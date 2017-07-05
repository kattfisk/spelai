#include "EALMutator.h"
#include "EALGene.h"
#include "RNDRandom.h"
#include "DBGDebug.h"



/* File scope functions */
static inline double fClamp(double real){
	if(real < 0.0){
		real = 0;
	}
	if(1.0 < real){
		real = 1.0;
	}
	DBGDebugAssert((0.0 <= real) && (real <= 1.0));
	return real;
}



/* EALMutatorImp */

/* Public creators */
EALMutatorImp::~EALMutatorImp(){
}



/* EALNullMutatorImp */

/* Public creators */
EALNullMutatorImp::EALNullMutatorImp() :
	EALMutatorImp(){
}

/* Public accessors */
EALNullMutatorImp* EALNullMutatorImp::clone() const{
	EALNullMutatorImp *clone = new EALNullMutatorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

void EALNullMutatorImp::mutate(EALGene &gene) const{
}

/* Private creators */
EALNullMutatorImp::EALNullMutatorImp(const EALNullMutatorImp &nullMutatorImp) :
	EALMutatorImp(nullMutatorImp){
}



/* EALResetMutatorImp */

/* Public creators */
EALResetMutatorImp::EALResetMutatorImp() :
	EALMutatorImp(){
}

/* Public accessors */
EALResetMutatorImp* EALResetMutatorImp::clone() const{
	EALResetMutatorImp *clone = new EALResetMutatorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

void EALResetMutatorImp::mutate(EALGene &gene) const{
	gene.randomize();
}

/* Private creators */
EALResetMutatorImp::EALResetMutatorImp(const EALResetMutatorImp &resetMutatorImp) :
	EALMutatorImp(resetMutatorImp){
}



/* EALUniformMutatorImp */

/* Public creators */
EALUniformMutatorImp::EALUniformMutatorImp(double maxOffset) :
	EALMutatorImp(),
	mMaxOffset(maxOffset){

	DBGAssert(invariant());
}

EALUniformMutatorImp::~EALUniformMutatorImp(){
	DBGAssert(invariant());

	mMaxOffset = -1.0;

	DBGAssert(!invariant());
}

/* Public accessors */
EALUniformMutatorImp* EALUniformMutatorImp::clone() const{
	DBGAssert(invariant());

	EALUniformMutatorImp *clone = new EALUniformMutatorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

void EALUniformMutatorImp::mutate(EALGene &gene) const{
	DBGDebugAssert(invariant());

	if(0.0 < mMaxOffset){
		gene.setFraction(fClamp(gene.getFraction() + RNDRandom::generateUniformReal(-mMaxOffset, mMaxOffset)));
	}
}

/* Private creators */
EALUniformMutatorImp::EALUniformMutatorImp(const EALUniformMutatorImp &uniformMutatorImp) :
	EALMutatorImp(uniformMutatorImp),
	mMaxOffset(uniformMutatorImp.mMaxOffset){
	
	DBGAssert(invariant());
}

/* Private acceesors */
bool EALUniformMutatorImp::invariant() const{
	const bool invariant = (0.0 <= mMaxOffset);
	return invariant;
}



/* EALNormalMutatorImp */

/* Public creators */
EALNormalMutatorImp::EALNormalMutatorImp(double standardDeviation) :
	EALMutatorImp(),
	mStandardDeviation(standardDeviation){

	DBGAssert(invariant());
}

EALNormalMutatorImp::~EALNormalMutatorImp(){
	DBGAssert(invariant());

	mStandardDeviation = -1.0;

	DBGAssert(!invariant());
}

/* Public accessors */
EALNormalMutatorImp* EALNormalMutatorImp::clone() const{
	DBGAssert(invariant());

	EALNormalMutatorImp *clone = new EALNormalMutatorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

void EALNormalMutatorImp::mutate(EALGene &gene) const{
	DBGDebugAssert(invariant());

	gene.setFraction(fClamp(gene.getFraction() + RNDRandom::generateNormalReal(0.0, mStandardDeviation)));
}

/* Private creators */
EALNormalMutatorImp::EALNormalMutatorImp(const EALNormalMutatorImp &normalMutatorImp) :
	EALMutatorImp(normalMutatorImp),
	mStandardDeviation(normalMutatorImp.mStandardDeviation){
	
	DBGAssert(invariant());
}

/* Private accessors */
bool EALNormalMutatorImp::invariant() const{
	const bool invariant = (0.0 <= mStandardDeviation);
	return invariant;
}



/* EALMutator */

/* Public creators */
EALMutator::EALMutator(const EALMutatorImp &mutatorImp) :
	mMutatorImp(mutatorImp.clone()){

	DBGAssert(invariant());
}

EALMutator::EALMutator(const EALMutator &mutator) :
	mMutatorImp(mutator.mMutatorImp->clone()){
	
	DBGAssert(invariant());
}

EALMutator::~EALMutator(){
	DBGAssert(invariant());

	delete mMutatorImp;
	mMutatorImp = 0;

	DBGAssert(!invariant());
}

/* Public manipulators */
EALMutator& EALMutator::operator=(const EALMutator &mutator){
	DBGAssert(invariant());

	if(this != &mutator){
		delete mMutatorImp;
		mMutatorImp = mutator.mMutatorImp->clone();
	}

	DBGAssert(invariant());
	return *this;
}

/* Public accessors */
void EALMutator::mutate(EALGene &gene) const{
	DBGDebugAssert(invariant());

	mMutatorImp->mutate(gene);
}

/* Private accessors */
bool EALMutator::invariant() const{
	const bool invariant = (0 != mMutatorImp);
	return invariant;
}

