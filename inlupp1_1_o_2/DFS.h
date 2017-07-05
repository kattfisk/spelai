#ifndef INLUPP_DFS_INCLUDED
#define INLUPP_DFS_INCLUDED

#include "Solver.h"

struct SearchResult;

class DFS : public Solver
{
public:
	DFS(Display* display = nullptr);
	virtual SearchResult solve(const Maze& maze, bool display_progress = false) override;

private:
};

#endif // INLUPP_DFS_INCLUDED
