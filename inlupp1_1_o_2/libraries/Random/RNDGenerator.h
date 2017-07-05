#ifndef INCLUDED_RNDGENERATOR
#define INCLUDED_RNDGENERATOR



/******************************************************************************

This component implements various generators. A generator generates (pseudo) 
random numbers uniformly distributed in [0.0, 1.0]. Generators differ in many
ways regarding resolution, randomness, period, efficiency, etc. 

Some generators must be initialized by a "random" real seed value in the range 
[0.0, 1.0].

Currently, only a lehmer generator is implemented according to the minimal 
standard specified in Park and Miller's famous article "Random number 
generators: good ones are hard to find".

*******************************************************************************/



class RNDGeneratorImp{
public:

	/* Public creators */
	virtual ~RNDGeneratorImp();

	/* Public manipulators */
	virtual double generate() = 0;

	/* Public accessors */
	virtual RNDGeneratorImp* clone() const = 0;
};




class RNDLehmerGeneratorImp : public RNDGeneratorImp{
public:

	/* Public creators */
	RNDLehmerGeneratorImp(double seed = 0.0);
	virtual ~RNDLehmerGeneratorImp();

	/* Public manipulators */
	virtual double generate();

	/* Public accessors */
	virtual RNDLehmerGeneratorImp* clone() const;

private:

	/* Private creators */
	RNDLehmerGeneratorImp(const RNDLehmerGeneratorImp &lehmerGeneratorImp);

	/* Private manipulators */
	RNDLehmerGeneratorImp& operator=(const RNDLehmerGeneratorImp &lehmerGeneratorImp);

	/* Private accessors */
	bool invariant() const;

	/* Private types */
	long mSeed;	
};




class RNDGenerator{
public:

	/* Public creators */
	RNDGenerator(const RNDGeneratorImp &generatorImp = RNDLehmerGeneratorImp());
	RNDGenerator(const RNDGenerator &generator);
	~RNDGenerator();

	/* Public manipulators */
	double generate();
	RNDGenerator& operator=(const RNDGenerator &generator);

private:

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	RNDGeneratorImp *mGeneratorImp;
};

#endif