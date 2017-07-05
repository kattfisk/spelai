#include "Maze.h"

Maze::Maze() 
	: Maze(22, 7, "#######################S       ######      ## ## ###        ###  ## ## ### #########   ## ###### ##G         ##        ##          #######################")
{
	/*
	######################
	#S       ######      #
	# ## ###        ###  #
	# ## ### #########   #
	# ###### ##G         #
	#        ##          #
	######################
	*/
}

Maze::Maze(int width, int height, const std::vector<Maze::Tile>& maze_structure)
	: width(width),
	  height(height),
	  structure(maze_structure),
	  structure_string(structure.size(), 'A') // Initialize string size
{
	int i = 0;
	for (Maze::Tile& t : structure)
	{
		structure_string[i++] = static_cast<char>(t);
	}
}

Maze::Maze(int width, int height, const std::string maze_string)
	: width(width),
	height(height),
	structure(),
	structure_string(maze_string)
{
	Maze::Tile current_tile;
	for (int i = 0; i < signed int(maze_string.length()); ++i)
	{
		if (maze_string[i] == static_cast<char>(Maze::Tile::WALL))
		{
			current_tile = Maze::Tile::WALL;
		}
		else if (maze_string[i] == static_cast<char>(Maze::Tile::FLOOR))
		{
			current_tile = Maze::Tile::FLOOR;
		}
		else if (maze_string[i] == static_cast<char>(Maze::Tile::START))
		{
			current_tile = Maze::Tile::START;
			start_pos.x = (i % width); // x
			start_pos.y = (i / width); // y
		}
		else if (maze_string[i] == static_cast<char>(Maze::Tile::GOAL))
		{
			current_tile = Maze::Tile::GOAL;
			goal_pos.x = (i % width); // x
			goal_pos.y = (i / width); // y
		}

		structure.push_back(current_tile);
	}
}

Maze::Tile Maze::at(Position pos) const
{
	return structure.at(pos.x + pos.y*width);
}

Position Maze::get_start_pos() const
{
	return start_pos;
}

Position Maze::get_goal_pos() const
{
	return goal_pos;
}

std::string Maze::as_string() const
{
	return structure_string;
}

int Maze::get_height() const
{
	return height;
}

int Maze::get_width() const
{
	return width;
}