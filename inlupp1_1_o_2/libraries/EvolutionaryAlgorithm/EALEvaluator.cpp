#include "EALEvaluator.h"
#include "../Debug/DBGDebug.h"



/* EALEvaluatorImp */

/* Public creators */
EALEvaluatorImp::~EALEvaluatorImp(){
}



/* EALNullEvaluatorImp */

/* Public creators */
EALNullEvaluatorImp::EALNullEvaluatorImp() :
	EALEvaluatorImp(){
}

/* Public accessors */
EALNullEvaluatorImp* EALNullEvaluatorImp::clone() const{
	EALNullEvaluatorImp *clone = new EALNullEvaluatorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

double EALNullEvaluatorImp::evaluate(const EALGenome &genome) const{
	return 0.0;
}

/* Private creators */
EALNullEvaluatorImp::EALNullEvaluatorImp(const EALNullEvaluatorImp &nullEvaluatorImp) :
	EALEvaluatorImp(nullEvaluatorImp){
}



/* EALFunctionEvaluatorImp */

/* Public creators */
EALFunctionEvaluatorImp::EALFunctionEvaluatorImp(Function function) :
	mFunction(function){
	
	DBGAssert(invariant());
}

EALFunctionEvaluatorImp::~EALFunctionEvaluatorImp(){
	DBGAssert(invariant());

	mFunction = 0;

	DBGAssert(!invariant());
}

/* Public accessors */	
EALFunctionEvaluatorImp* EALFunctionEvaluatorImp::clone() const{
	DBGAssert(invariant());
	
	EALFunctionEvaluatorImp *clone = new EALFunctionEvaluatorImp(*this);
	DBGAssert(0 != clone);
	return clone;
}

double EALFunctionEvaluatorImp::evaluate(const EALGenome &genome) const{
	DBGDebugAssert(invariant());

	return mFunction(genome);
}

/* Private creators */
EALFunctionEvaluatorImp::EALFunctionEvaluatorImp(const EALFunctionEvaluatorImp &functionEvaluatorImp) :
	EALEvaluatorImp(functionEvaluatorImp),
	mFunction(functionEvaluatorImp.mFunction){
	
	DBGAssert(invariant());
}

/* Private accessors */
bool EALFunctionEvaluatorImp::invariant() const{
	const bool invariant = (0 != mFunction);
	return invariant;
}



/* EALEvaluator */

/* Public creators */
EALEvaluator::EALEvaluator(const EALEvaluatorImp &evaluatorImp) :
	mEvaluatorImp(evaluatorImp.clone()){

	DBGAssert(invariant());
}

EALEvaluator::EALEvaluator(const EALEvaluator &evaluator) :
	mEvaluatorImp(evaluator.mEvaluatorImp->clone()){
		
	DBGAssert(invariant());
}

EALEvaluator::~EALEvaluator(){
	DBGAssert(invariant());

	delete mEvaluatorImp;
	mEvaluatorImp = 0;

	DBGAssert(!invariant());
}

/* Public manipulators */
EALEvaluator& EALEvaluator::operator=(const EALEvaluator &evaluator){
	DBGAssert(invariant());

	if(this != &evaluator){
		delete mEvaluatorImp;
		mEvaluatorImp = evaluator.mEvaluatorImp->clone();
	}

	DBGAssert(invariant());
	return *this;
}

/* Public accessors */
double EALEvaluator::evaluate(const EALGenome &genome) const{
	DBGDebugAssert(invariant());

	return mEvaluatorImp->evaluate(genome);
}

/* Private accessors */
bool EALEvaluator::invariant() const{
	const bool invariant = (0 != mEvaluatorImp);
	return invariant;
}


