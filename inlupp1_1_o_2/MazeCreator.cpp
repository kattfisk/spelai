#include "MazeCreator.h"

#include "Position.h"

#include <assert.h>

Maze MazeCreator::from_binary_string(int width, int height, Position start_pos, Position goal_pos, std::string binary_string)
{
	assert(start_pos != goal_pos);
	assert(start_pos.x > 0 && start_pos.x < width - 1 && start_pos.y > 0 && start_pos.y < height - 1);
	assert(goal_pos.x > 0 && goal_pos.x < width - 1 && goal_pos.y > 0 && goal_pos.y < height - 1);
	assert(static_cast<signed int>(binary_string.length()) == (width - 2)*(height - 2) - 2);

	// Start with creating maze with only walls
	std::vector<Maze::Tile> structure(width*height, Maze::Tile::WALL);

	int str_i = 0;
	Maze::Tile current_tile = Maze::Tile::WALL;

	// Iterate over each line except first and last
	for (int i = 1; i < height - 1; ++i)
	{
		// First char tile is wall
		structure[i*width] = Maze::Tile::WALL;
		// Iterate over each tile except first and last
		for (int j = 1; j < width - 1; ++j)
		{
			if (start_pos == Position(j, i))
			{ 
				current_tile = Maze::Tile::START;
			}
			else if (goal_pos == Position(j, i))
			{
				current_tile = Maze::Tile::GOAL;
			} 
			else if (binary_string.at(str_i) == '1')
			{
				current_tile = Maze::Tile::WALL;
				++str_i;
			}
			else if (binary_string.at(str_i) == '0')
			{
				current_tile = Maze::Tile::FLOOR;
				++str_i;
			}
			else
			{
				assert(false && "Invalid data in maze string");
			}
			structure[i*width + j] = current_tile;
		}
		// Last tile is wall
		structure[i*width + width - 1] = Maze::Tile::WALL;
	}
	return Maze(width, height, structure);
}

Maze MazeCreator::from_bool_vector(int width, int height, Position start_pos, Position goal_pos, std::vector<bool> bool_vector)
{
	assert(start_pos != goal_pos);
	assert(start_pos.x > 0 && start_pos.x < width - 1 && start_pos.y > 0 && start_pos.y < height - 1);
	assert(goal_pos.x > 0 && goal_pos.x < width - 1 && goal_pos.y > 0 && goal_pos.y < height - 1);
	assert(static_cast<signed int>(bool_vector.size()) == (width - 2)*(height - 2) - 2);

	// Start with creating maze with only walls
	std::vector<Maze::Tile> structure(width*height, Maze::Tile::WALL);

	int str_i = 0;
	Maze::Tile current_tile = Maze::Tile::WALL;

	// Iterate over each line except first and last
	for (int i = 1; i < height - 1; ++i)
	{
		// First char tile is wall
		structure[i*width] = Maze::Tile::WALL;
		// Iterate over each tile except first and last
		for (int j = 1; j < width - 1; ++j)
		{
			if (start_pos == Position(j, i))
			{
				current_tile = Maze::Tile::START;
			}
			else if (goal_pos == Position(j, i))
			{
				current_tile = Maze::Tile::GOAL;
			}
			else if (bool_vector.at(str_i))
			{
				current_tile = Maze::Tile::WALL;
				++str_i;
			}
			else
			{
				current_tile = Maze::Tile::FLOOR;
				++str_i;
			}
			structure[i*width + j] = current_tile;
		}
		// Last tile is wall
		structure[i*width + width - 1] = Maze::Tile::WALL;
	}
	return Maze(width, height, structure);
}