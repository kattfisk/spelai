#ifndef INLUPP_SEARCHRESULT_INCLUDED
#define INLUPP_SEARCHRESULT_INCLUDED

#include "Position.h"

#include <vector>

struct SearchResult
{
	inline SearchResult() : solved(false), steps_to_find(0), path(), distance_to_goal(INT_MAX) {}
	bool solved;
	int steps_to_find;
	std::vector<Position> path;
	// Closest distance to goal. Will be 1 if solved.
	int distance_to_goal;
};

#endif // INLUPP_SEARCHRESULT_INCLUDED
