#ifndef INLUPP_BFS_INCLUDED
#define INLUPP_BFS_INCLUDED

#include "Solver.h"

struct SearchResult;

class BFS : public Solver
{
public:
	BFS(Display* display = nullptr);
	virtual SearchResult solve(const Maze& maze, bool display_progress = false) override;

private:
};

#endif // INLUPP_BFS_INCLUDED
