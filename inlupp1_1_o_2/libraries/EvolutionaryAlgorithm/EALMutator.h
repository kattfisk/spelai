#ifndef INCLUDED_EALMUTATOR
#define INCLUDED_EALMUTATOR



/******************************************************************************

This component implements different mutators. A mutator is used to modify 
genes.

*******************************************************************************/



class EALGene;



class EALMutatorImp{
public:

	/* Public creators */
	virtual ~EALMutatorImp();

	/* Public accessors */
	virtual EALMutatorImp* clone()               const = 0;
	virtual void           mutate(EALGene &gene) const = 0;
};



class EALNullMutatorImp : public EALMutatorImp{
public:

	/* Public creators */
	EALNullMutatorImp();

	/* Public accessors */
	virtual EALNullMutatorImp* clone()               const;
	virtual void               mutate(EALGene &gene) const;

private:

	/* Private creators */
	EALNullMutatorImp(const EALNullMutatorImp &nullMutatorImp);

	/* Private manipulators */
	EALNullMutatorImp& operator=(const EALNullMutatorImp &nullMutatorImp);
};



class EALResetMutatorImp : public EALMutatorImp{
public:

	/* Public creators */
	EALResetMutatorImp();

	/* Public accessors */
	virtual EALResetMutatorImp* clone()               const;
	virtual void                mutate(EALGene &gene) const;

private:

	/* Private creators */
	EALResetMutatorImp(const EALResetMutatorImp &resetMutatorImp);

	/* Private manipulators */
	EALResetMutatorImp& operator=(const EALResetMutatorImp &resetMutatorImp);
};



class EALUniformMutatorImp : public EALMutatorImp{
public:

	/* Public creators */
	EALUniformMutatorImp(double maxOffset);
	virtual ~EALUniformMutatorImp();

	/* Public accessors */
	virtual EALUniformMutatorImp* clone()               const;
	virtual void                  mutate(EALGene &gene) const;

private:

	/* Private creators */
	EALUniformMutatorImp(const EALUniformMutatorImp &uniformMutatorImp);

	/* Private manipulators */
	EALUniformMutatorImp& operator=(const EALUniformMutatorImp &uniformMutatorImp);
	
	/* Private acceesors */
	bool invariant() const;

	/* Private data */
	double mMaxOffset;
};



class EALNormalMutatorImp : public EALMutatorImp{
public:

	/* Public creators */
	EALNormalMutatorImp(double standardDeviation);
	virtual ~EALNormalMutatorImp();

	/* Public accessors */
	virtual EALNormalMutatorImp* clone()               const;
	virtual void                 mutate(EALGene &gene) const;

private:

	/* Private creators */
	EALNormalMutatorImp(const EALNormalMutatorImp &normalMutatorImp);

	/* Private manipulators */
	EALNormalMutatorImp& operator=(const EALNormalMutatorImp &normalMutatorImp);
	
	/* Private accessors */
	bool invariant() const;

	/* Private data */
	double mStandardDeviation;
};



class EALMutator{
public:

	/* Public creators */
	EALMutator(const EALMutatorImp &mutatorImp = EALNullMutatorImp());
	EALMutator(const EALMutator &mutator);
	~EALMutator();

	/* Public manipulators */
	EALMutator& operator=(const EALMutator &mutator);

	/* Public accessors */
	void mutate(EALGene &gene) const;

private:

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	EALMutatorImp *mMutatorImp;
};

#endif