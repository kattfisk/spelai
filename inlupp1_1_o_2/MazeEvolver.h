#ifndef INLUPP_MAZEEVOLVER_INCLUDED
#define INLUPP_MAZEEVOLVER_INCLUDED

#include "Position.h"

#include "libraries\EvolutionaryAlgorithm\EALPopulation.h"
#include "libraries\EvolutionaryAlgorithm\EALEvolver.h"
#include "libraries\EvolutionaryAlgorithm\EALIndividual.h"

#include <memory>

class Solver;
class Maze;
class EALGenome;

class MazeEvolver
{
public:
	MazeEvolver(Position maze_start_pos, Position maze_goal_pos, int maze_width, int maze_height, std::shared_ptr<Solver> evaluator);
	void evolve(int generations);
	Maze get_best_solution() const;

private:
	MazeEvolver& operator= (const MazeEvolver& rhs);
	void populate(int population_size);
	double evaluate(const EALGenome& genome);
	void update_most_fit();
	const Position MAZE_START_POS, MAZE_GOAL_POS;
	const int MAZE_WIDTH, MAZE_HEIGHT;
	std::shared_ptr<Solver> maze_evaluator;
	const int GENOME_LENGTH;
	// TODO: add something to check solution steps against
	int generations_passed;
	EALPopulation population;
	EALEvolver evolver;
	EALIndividual most_fit;
};

#endif // INLUPP_MAZEEVOLVER_INCLUDED