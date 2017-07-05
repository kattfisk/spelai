#ifndef INCLUDED_EALGENE
#define INCLUDED_EALGENE



/******************************************************************************

This component implements a gene type with values in [0.0, 1.0] (i.e. a 
fraction). This value can also be mapped onto other values and ranges, e.g.
to [-3, 45]. 

*******************************************************************************/



#include "DBGDebug.h"
#include "RNDRandom.h"



class EALGene{
public:

	/* Public creators */
	EALGene(double fraction = 0.0) :
	  mFraction(fraction){
	
	  DBGDebugAssert(invariant());
	}

	EALGene(const EALGene &gene) :
		mFraction(gene.mFraction){
		
		DBGDebugAssert(invariant());
	}

	~EALGene(){
	  DBGDebugAssert(invariant());			
	}

	/* Public manipulators */
	EALGene& operator=(const EALGene &gene){
		DBGDebugAssert(invariant());
		
		mFraction = gene.mFraction;

		DBGDebugAssert(invariant());
		return *this;
	}

	void randomize(){
		DBGDebugAssert(invariant());

		mFraction = RNDRandom::generateUniformReal(0.0, 1.0);

		DBGDebugAssert(invariant());
	}

	void setFraction(double fraction){
	  DBGDebugAssert(invariant());

	  mFraction = fraction;
	
	  DBGDebugAssert(invariant());
	}

	/* Public accessors */
	bool getBoolean() const{
		DBGDebugAssert(invariant());
		
		return (mFraction < 0.5) ? (false) : (true);
	}

	double getFraction() const{
		DBGDebugAssert(invariant());

		return mFraction;
	}

	int getInteger(int min, int max) const{
		DBGDebugAssert(invariant());
		DBGDebugAssert(min <= max);

		const int DELTA   = max - min;
		int       integer = min + int(mFraction * (DELTA + 1));
		if(max < integer){
			integer = max;
		}
		DBGDebugAssert((min <= integer) && (integer <= max));
		return integer;
	}

	double getReal(double min, double max) const{
		DBGDebugAssert(invariant());
		DBGDebugAssert(min <= max);
	
		double real;
		if(min < max){
			if((0.0 < mFraction) && (mFraction < 1.0)){
				const double DELTA = max - min;
				real               = min + (mFraction * DELTA);
			}
			else if(0.0 == mFraction){
				real = min;
			}
			else if(1.0 == mFraction){
				real = max;
			}
			else{
				DBGError("mFraction not in [0.0, 1.0]");
			}
		}
		else if(min == max){
			real = min;		
		}
		else{
			DBGError("max < min");
		}
		DBGDebugAssert((min <= real) && (real <= max));
		return real;
	}

private:

	/* Private accessors */
	bool invariant() const{
		const bool invariant = ((0.0 <= mFraction) && (mFraction <= 1.0));
		return invariant;
	}

	/* Private data */
	double mFraction;
};


#endif