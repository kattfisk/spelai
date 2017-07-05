#include "DFS.h"

#include "Maze.h"
#include "Position.h"
#include "SearchResult.h"

#include <vector>
#include <stack>
#include <set>
#include <map>

DFS::DFS(Display* display)
	: Solver("Depth-first search", display)
{
}

SearchResult DFS::solve(const Maze& maze, bool display_progress)
{
	Solver::display_progress = display_progress;

	std::stack<Position> visit;
	std::set<int> visited; // key = x + y*width
	std::map<int, Position> parent; // maps tile -> parent, key = x + y*width
	int maze_width = maze.get_width();
	SearchResult result;
	Position start, current, goal, next;

	// Add position to visit and store its parent if it's walkable and has not been visited
	auto add_iff = [&](Position& pos)
	               {
		               if (maze.at(pos) != Maze::Tile::WALL && !visited.count(pos.x + pos.y * maze_width))
					   {
			               visit.push(pos);
			               visited.insert(pos.x + pos.y * maze_width);
						   parent[pos.x + pos.y * maze_width] = current;
					   }
	               };

	// Initialize variables
	start = maze.get_start_pos();
	current = start;
	visit.push(current);
	visited.insert(current.x + current.y * maze_width);
	goal = maze.get_goal_pos();

	while (current != goal)
	{
		if(visit.empty())
		{ // Maze has no goal
			return result;
		}

		current = visit.top();
		visit.pop();

		++result.steps_to_find;
		if (goal.distance_to(current) < result.distance_to_goal)
		{
			result.distance_to_goal = goal.distance_to(current);
		}

		Solver::show_step(current);

		// Up
		next = Position(current.x, current.y + 1);
		add_iff(next);

		// Left
		next = Position(current.x - 1, current.y);
		add_iff(next);

		// Down
		next = Position(current.x, current.y - 1);
		add_iff(next);

		// Right
		next = Position(current.x + 1, current.y);
		add_iff(next);

	}
	result.solved = true;

	// Get path by walking backwards from goal
	while(current != start)
	{
		current = parent.at(current.x + current.y * maze_width);
		result.path.push_back(current);
	}

	return result;
}