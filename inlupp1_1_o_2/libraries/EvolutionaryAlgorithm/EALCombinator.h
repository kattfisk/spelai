#ifndef INCLUDED_EALCOMBINATOR
#define INCLUDED_EALCOMBINATOR



/******************************************************************************

This component implements combinators each of which combines two genomes.

*******************************************************************************/



class EALGenome;



class EALCombinatorImp{
public:

	/* Public creators */
	virtual ~EALCombinatorImp();

	/* Public accessors */
	virtual EALCombinatorImp* clone()                                         const = 0;
	virtual void              combine(EALGenome &genome0, EALGenome &genome1) const = 0;
};



class EALNullCombinatorImp : public EALCombinatorImp{
public:

	/* Public creators */
	EALNullCombinatorImp();

	/* Public accessors */
	virtual EALNullCombinatorImp* clone()                                         const;
	virtual void                  combine(EALGenome &genome0, EALGenome &genome1) const;

private:

	/* Private creators */
	EALNullCombinatorImp(const EALNullCombinatorImp &nullCombinatorImp);

	/* Private manipulators */
	EALNullCombinatorImp& operator=(const EALNullCombinatorImp &nullCombinatorImp);
};



class EALSingleCombinatorImp : public EALCombinatorImp{
public:

	/* Public creators */
	EALSingleCombinatorImp();

	/* Public accessors */
	virtual EALSingleCombinatorImp* clone()                                         const;
	virtual void                    combine(EALGenome &genome0, EALGenome &genome1) const;

private:

	/* Private creators */
	EALSingleCombinatorImp(const EALSingleCombinatorImp &singleCombinatorImp);

	/* Private manipulators */
	EALSingleCombinatorImp& operator=(const EALSingleCombinatorImp &singleCombinatorImp);
};



class EALDualCombinatorImp : public EALCombinatorImp{
public:

	/* Public creators */
	EALDualCombinatorImp();

	/* Public accessors */
	virtual EALDualCombinatorImp* clone()                                         const;
	virtual void                  combine(EALGenome &genome0, EALGenome &genome1) const;

private:

	/* Private creators */
	EALDualCombinatorImp(const EALDualCombinatorImp &dualCombinatorImp);

	/* Private manipulators */
	EALDualCombinatorImp& operator=(const EALDualCombinatorImp &dualCombinatorImp);
};



class EALCombinator{
public:

	/* Public creators */
	EALCombinator(const EALCombinatorImp &combinatorImp = EALNullCombinatorImp());
	EALCombinator(const EALCombinator &combinator);
	~EALCombinator();

	/* Public manipulators */
	EALCombinator& operator=(const EALCombinator &combinator);

	/* Public accessors */
	void combine(EALGenome &genome0, EALGenome &genome1) const;

private:

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	EALCombinatorImp *mCombinatorImp;
};

#endif