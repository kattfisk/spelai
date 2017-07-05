#ifndef INCLUDED_EALEVALUATOR
#define INCLUDED_EALEVALUATOR



/******************************************************************************

This component implements evaluators that are used to calculate the fitness
value for a genome.

*******************************************************************************/



#include "DBGDebug.h"



class EALGenome;



class EALEvaluatorImp{
public:

	/* Public creators */
	virtual ~EALEvaluatorImp();

	/* Public accessors */
	virtual EALEvaluatorImp* clone()                           const = 0;
	virtual double           evaluate(const EALGenome &genome) const = 0;
};



class EALNullEvaluatorImp : public EALEvaluatorImp{
public:

	/* Public creators */
	EALNullEvaluatorImp();

	/* Public accessors */
	virtual EALNullEvaluatorImp* clone()                           const;
	virtual double               evaluate(const EALGenome &genome) const;

private:

	/* Private creators */
	EALNullEvaluatorImp(const EALNullEvaluatorImp &nullEvaluatorImp);

	/* Private manipulators */
	EALNullEvaluatorImp& operator=(const EALNullEvaluatorImp &nullEvaluatorImp);
};



class EALFunctionEvaluatorImp : public EALEvaluatorImp{
public:

	/* Public types */
	typedef double (*Function)(const EALGenome &genome);

	/* Public creators */
	EALFunctionEvaluatorImp(Function function);
	virtual ~EALFunctionEvaluatorImp();

	/* Public accessors */
	virtual EALFunctionEvaluatorImp* clone()                           const;
	virtual double                   evaluate(const EALGenome &genome) const;

private:

	/* Private creators */
	EALFunctionEvaluatorImp(const EALFunctionEvaluatorImp &functionEvaluatorImp);

	/* Private manipulators */
	EALFunctionEvaluatorImp& operator=(const EALFunctionEvaluatorImp &functionEvaluatorImp);
	
	/* Private accessors */
	bool invariant() const;

	/* Private data */
	Function mFunction;
};


template<class Subject>
class EALMemberEvaluatorImp : public EALEvaluatorImp{
public:

	/* Public types */
	typedef double (Subject::*Member)(const EALGenome &genome);

	/* Public creators */
	EALMemberEvaluatorImp(Subject &subject, Member member) :
		mSubject(&subject),
		mMember(member){
			
		DBGAssert(invariant());
	}

	virtual ~EALMemberEvaluatorImp(){
		DBGAssert(invariant());

		mSubject = 0;
		mMember  = 0;

		DBGAssert(!invariant());
	}

	/* Public accessors */
	virtual EALMemberEvaluatorImp* clone() const{
		DBGAssert(invariant());

		EALMemberEvaluatorImp *clone = new EALMemberEvaluatorImp(*this);
		DBGAssert(0 != clone);
		return clone;
	}

	virtual double evaluate(const EALGenome &genome) const{
		DBGDebugAssert(invariant());

		return (mSubject->*mMember)(genome);
	}

private:

	/* Private creators */
	EALMemberEvaluatorImp(const EALMemberEvaluatorImp &memberEvaluatorImp) :
		EALEvaluatorImp(memberEvaluatorImp),
		mSubject(memberEvaluatorImp.mSubject),
		mMember(memberEvaluatorImp.mMember){
				
		DBGAssert(invariant());
	}


	/* Private manipulators */
	EALMemberEvaluatorImp& operator=(const EALMemberEvaluatorImp &memberEvaluatorImp);
	
	/* Private accessors */
	bool invariant() const{
		const bool invariant = ((0 != mSubject) && (0 != mMember));
		return invariant;
	}

	/* Private data */
	Subject *mSubject;
	Member  mMember;
};



template<class Subject>
class EALConstMemberEvaluatorImp : public EALEvaluatorImp{
public:

	/* Public types */
	typedef double (Subject::*Member)(const EALGenome &genome) const;

	/* Public creators */
	EALConstMemberEvaluatorImp(const Subject &subject, Member member) :
		mSubject(&subject),
		mMember(member){
			
		DBGAssert(invariant());
	}

	virtual ~EALConstMemberEvaluatorImp(){
		DBGAssert(invariant());

		mSubject = 0;
		mMember  = 0;

		DBGAssert(!invariant());
	}

	/* Public accessors */
	virtual EALConstMemberEvaluatorImp* clone() const{
		DBGAssert(invariant());

		EALConstMemberEvaluatorImp *clone = new EALConstMemberEvaluatorImp(*this);
		DBGAssert(0 != clone);
		return clone;
	}

	virtual double evaluate(const EALGenome &genome) const{
		DBGDebugAssert(invariant());

		return (mSubject->*mMember)(genome);
	}

private:

	/* Private creators */
	EALConstMemberEvaluatorImp(const EALConstMemberEvaluatorImp &constMemberEvaluatorImp) :
		EALEvaluatorImp(constMemberEvaluatorImp),
		mSubject(constMemberEvaluatorImp.mSubject),
		mMember(constMemberEvaluatorImp.mMember){
		
		DBGAssert(invariant());
	}


	/* Private manipulators */
	EALConstMemberEvaluatorImp& operator=(const EALConstMemberEvaluatorImp &constMemberEvaluatorImp);
	
	/* Private accessors */
	bool invariant() const{
		const bool invariant = ((0 != mSubject) && (0 != mMember));
		return invariant;
	}

	/* Private data */
	const Subject *mSubject;
	Member        mMember;
};



class EALEvaluator{
public:

	/* Public creators */
	EALEvaluator(const EALEvaluatorImp &evaluatorImp = EALNullEvaluatorImp());
	EALEvaluator(const EALEvaluator &evaluator);
	~EALEvaluator();

	/* Public manipulators */
	EALEvaluator& operator=(const EALEvaluator &evaluator);

	/* Public accessors */
	double evaluate(const EALGenome &genome) const;

private:

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	EALEvaluatorImp *mEvaluatorImp;
};




#endif