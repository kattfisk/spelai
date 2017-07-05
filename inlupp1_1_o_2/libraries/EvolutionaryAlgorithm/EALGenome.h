#ifndef INCLUDED_EALGENOME
#define INCLUDED_EALGENOME



/******************************************************************************

This component implements a genome type that represents a sequence of genes.

*******************************************************************************/



#include "EALGene.h"
#include "DBGDebug.h"
#include <vector>



class EALGenome{
public:

	/* Public creators */
	EALGenome(int geneCount = 0) :
		mGenes(geneCount){
	}

	/* Public manipulators */
	EALGene& getGene(int geneIndex){
		DBGDebugAssert((0 <= geneIndex) && (geneIndex < int(mGenes.size())));

		return mGenes[geneIndex];
	}

	EALGene& operator[](int geneIndex){
		DBGDebugAssert((0 <= geneIndex) && (geneIndex < int(mGenes.size())));

		return mGenes[geneIndex];
	}

	void randomize(){
		for(GeneVector::iterator i = mGenes.begin(); i != mGenes.end(); i++){
			EALGene &gene = *i;
			gene.randomize();
		}
	}

	/* Public accessors */
	const EALGene& getGene(int geneIndex) const{
		DBGDebugAssert((0 <= geneIndex) && (geneIndex < int(mGenes.size())));

		return mGenes[geneIndex];
	}

	int getGeneCount() const{
		return int(mGenes.size());	
	}

	const EALGene& operator[](int geneIndex) const{
		DBGDebugAssert((0 <= geneIndex) && (geneIndex < int(mGenes.size())));

		return mGenes[geneIndex];
	}

private:

	/* Private types */
	typedef std::vector<EALGene> GeneVector;

	/* Private data */
	GeneVector mGenes;
};

#endif