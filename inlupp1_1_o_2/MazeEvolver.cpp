#include "MazeEvolver.h"

#include "Solver.h"
#include "SearchResult.h"
#include "MazeCreator.h"

#include "libraries\EvolutionaryAlgorithm\EALEvolutionaryAlgorithm.h"

#include <vector>

namespace
{
	// Population settings
	const int POPULATION_SIZE = 10;
	
	// Selection settings
	const int TOURNAMENT_PARTICIPANTS = 8;
	const EALTournamentSelectorImp SELECTOR_IMPLEMENTATION(TOURNAMENT_PARTICIPANTS);
	
	// Combination settings
	const double COMBINATON_PROBABILITY(0.0);
	const EALDualCombinatorImp COMBINATOR_IMPLEMENTATION;
	
	// Mutation settings
	const double MUTATION_PROBABILTY(0.15);
	const EALResetMutatorImp MUTATOR_IMPLEMENTATION;

	std::vector<bool> to_bool_vector(const EALGenome& genome)
	{
		const int GENOME_LENGTH = genome.getGeneCount();
		std::vector<bool> retval(GENOME_LENGTH);
		for (int i = 0; i < GENOME_LENGTH; ++i)
		{
			retval[i] = genome[i].getBoolean();
		}
		return retval;
	}
}

MazeEvolver::MazeEvolver(Position maze_start_pos, Position maze_goal_pos, int maze_width, int maze_height, std::shared_ptr<Solver> maze_evaluator)
	: MAZE_START_POS(maze_start_pos),
	  MAZE_GOAL_POS(maze_goal_pos),
	  MAZE_WIDTH(maze_width),
	  MAZE_HEIGHT(maze_height),
	  maze_evaluator(maze_evaluator),
	  GENOME_LENGTH((maze_width - 2)*(maze_height - 2) - 2), // Number of tiles that are not outer walls or start/goal
	  generations_passed(0)
{
	const EALEvaluator EVALUATOR(EALMemberEvaluatorImp<MazeEvolver>(*this, &MazeEvolver::evaluate));
	const EALSelector SELECTOR(SELECTOR_IMPLEMENTATION);
	const EALCombinator COMBINATOR(COMBINATOR_IMPLEMENTATION);
	const EALMutator MUTATOR(MUTATOR_IMPLEMENTATION);

	EALBasicEvolverImp evolverImplementation(EVALUATOR, SELECTOR, COMBINATOR, MUTATOR, COMBINATON_PROBABILITY, MUTATION_PROBABILTY);
	evolver = EALEvolver(evolverImplementation);

	populate(POPULATION_SIZE);

	update_most_fit();
}

void MazeEvolver::evolve(int generations)
{
	for (int i = 0; i < generations; ++i)
	{
		evolver.evolve(population);
		++generations_passed;
	}
	update_most_fit();
}

Maze MazeEvolver::get_best_solution() const
{
	return MazeCreator::from_bool_vector(MAZE_WIDTH, MAZE_HEIGHT, MAZE_START_POS, MAZE_GOAL_POS, to_bool_vector(most_fit.getGenome()));
}

void MazeEvolver::populate(int individuals)
{
	for (int i = 0; i < individuals; ++i)
	{
		EALGenome genome(GENOME_LENGTH);
		genome.randomize();
		population.addIndividual(EALIndividual(genome, evaluate(genome)));
	}
}

double MazeEvolver::evaluate(const EALGenome& genome)
{
	Maze solution(MazeCreator::from_bool_vector(MAZE_WIDTH, MAZE_HEIGHT, MAZE_START_POS, MAZE_GOAL_POS, to_bool_vector(genome)));

	SearchResult result(maze_evaluator->solve(solution));

	double fitness;
	// Measures how difficult the maze was to solve
	if (result.solved)
	{
		fitness = double(result.steps_to_find) / double(maze_evaluator->get_upper_bound(solution));
	}
	else
	{
		fitness = 0.0;
	}

	// Measures how close it was to being solveable
	// Theoretical max steps through every tile except outer walls
	const double MAX_DISTANCE_TO_GOAL = (MAZE_WIDTH - 2) * (MAZE_HEIGHT - 2);
	fitness += 1.0 / double(result.distance_to_goal) - 1.0 / MAX_DISTANCE_TO_GOAL;

	// Return value between 0.0 and 1.0
	return fitness /= 2.0;
}

void MazeEvolver::update_most_fit()
{
	const int INDIVIDUALS = population.getIndividualCount();
	const double HIGHEST_FITNESS = population.getMaximumFitness();

	for (int i = 0; i < INDIVIDUALS; ++i)
	{
		if (population[i].getFitness() == HIGHEST_FITNESS)
		{
			most_fit = population[i];
			return;
		}
	}
}