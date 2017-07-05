#ifndef INCLUDED_EALSELECTOR
#define INCLUDED_EALSELECTOR



/******************************************************************************

This component implements selectors, each of which selects an individual from
a population for reproduction.

*******************************************************************************/



class EALPopulation;
class EALIndividual;



class EALSelectorImp{
public:

	/* Public creators */
	virtual ~EALSelectorImp();

	/* Public accessors */
	virtual EALSelectorImp*      clone()                                 const = 0;
	virtual const EALIndividual& select(const EALPopulation &population) const = 0;
};



class EALNullSelectorImp : public EALSelectorImp{
public:

	/* Public creators */
	EALNullSelectorImp();

	/* Public accessors */
	virtual EALNullSelectorImp*  clone()                                 const;
	virtual const EALIndividual& select(const EALPopulation &population) const;

private:

	/* Private creators */
	EALNullSelectorImp(const EALNullSelectorImp &nullSelectorImp);

	/* Private manipulators */
	EALNullSelectorImp& operator=(const EALNullSelectorImp &nullSelectorImp);
};



class EALRouletteSelectorImp : public EALSelectorImp{
public:

	/* Public creators */
	EALRouletteSelectorImp();

	/* Public accessors */
	virtual EALRouletteSelectorImp* clone()                                 const;
	virtual const EALIndividual&    select(const EALPopulation &population) const;

private:

	/* Private creators */
	EALRouletteSelectorImp(const EALRouletteSelectorImp &rouletteSelectorImp);

	/* Private manipulators */
	EALRouletteSelectorImp& operator=(const EALRouletteSelectorImp &rouletteSelectorImp);
};



class EALTournamentSelectorImp : public EALSelectorImp{
public:

	/* Public creators */
	EALTournamentSelectorImp(int participantCount);

	/* Public accessors */
	virtual EALTournamentSelectorImp* clone()                                 const;
	virtual const EALIndividual&      select(const EALPopulation &population) const;

private:

	/* Private creators */
	EALTournamentSelectorImp(const EALTournamentSelectorImp &tournamentSelectorImp);

	/* Private manipulators */
	EALTournamentSelectorImp& operator=(const EALTournamentSelectorImp &tournamentSelectorImp);

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	int mParticipantCount;
};



class EALSelector{
public:

	/* Public creators */
	EALSelector(const EALSelectorImp &selectorImp = EALNullSelectorImp());
	EALSelector(const  EALSelector &selector);
	~EALSelector();

	/* Public manipulators */
	EALSelector& operator=(const  EALSelector &selector);

	/* Public accessors */
	const EALIndividual& select(const EALPopulation &population) const;

private:

	/* Private accessors */
	bool invariant() const;

	/* Private data */
	EALSelectorImp *mSelectorImp;
};

#endif