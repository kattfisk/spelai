#include "AStar.h"

#include "Maze.h"
#include "Position.h"
#include "SearchResult.h"

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <queue>
#include <functional>

AStar::AStar(Display* display)
	: Solver("A*", display)
{
}

SearchResult AStar::solve(const Maze& maze, bool display_progress)
{
	Solver::display_progress = display_progress;

	std::unordered_map<int, Position> parent; // maps tile -> parent, key = x + y*width
	std::unordered_map<int, int> cost_to_reach; // key = x + y*width
	// Position with cost for use in data structure
	struct ASPos
	{
		inline ASPos(Position position, int estimated_cost) : position(position), estimated_cost(estimated_cost)	{}

		inline bool operator>(const ASPos& rhs) const
		{
			return estimated_cost > rhs.estimated_cost;
		}
		Position position;
		int estimated_cost;

	private: ASPos(); // This constructor can do nothing good
	};
	std::priority_queue<ASPos, std::deque<ASPos>, std::greater<ASPos> > visit;
	const int maze_width = maze.get_width();
	SearchResult result;
	const Position start = maze.get_start_pos(), goal = maze.get_goal_pos();
	Position current, next;
	int cost_to_next;

	// Add position to visit and store its parent if it's walkable
	// and has either not been explored or we've found a cheaper route
	auto add_iff = [&](const Position& pos, int cost)
	               {
					   const int pos_index(pos.x + pos.y * maze_width); // Position in one dimension
					   if (maze.at(pos) != Maze::Tile::WALL && (!cost_to_reach.count(pos_index) || cost < cost_to_reach[pos_index]))
					   {
						   cost_to_reach[pos_index] = cost;
						   const int heuristic = pos.distance_to(goal);
						   visit.emplace(pos, cost + heuristic);
						   parent[pos_index] = current;
					   }
	               };

	// Initialize variables
	current = start;
	visit.emplace(current, 0);
	cost_to_reach[current.x + current.y * maze_width] = 0;

	while (current != goal)
	{
		if(visit.empty())
		{ // Maze has no goal
			return result;
		}

		current = visit.top().position;
		visit.pop();
		++result.steps_to_find;
		if (goal.distance_to(current) < result.distance_to_goal)
		{
			result.distance_to_goal = goal.distance_to(current);
		}

		Solver::show_step(current);

		cost_to_next = cost_to_reach[current.x + current.y * maze_width] + 1;

		// Up
		next = Position(current.x, current.y + 1);
		add_iff(next, cost_to_next);

		// Left
		next = Position(current.x - 1, current.y);
		add_iff(next, cost_to_next);

		// Down
		next = Position(current.x, current.y - 1);
		add_iff(next, cost_to_next);

		// Right
		next = Position(current.x + 1, current.y);
		add_iff(next, cost_to_next);
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