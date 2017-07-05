#ifndef INLUPP_ASTAR_INCLUDED
#define INLUPP_ASTAR_INCLUDED

#include "Solver.h"

class AStar : public Solver
{
public:
	AStar(Display* display = nullptr);
	virtual SearchResult solve(const Maze& maze, bool display_progress = false) override;

private:
};

#endif // INLUPP_ASTAR_INCLUDED
