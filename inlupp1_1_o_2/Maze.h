#ifndef INLUPP_MAZE_INCLUDED
#define INLUPP_MAZE_INCLUDED

#include "Position.h"

#include <vector>
#include <string>

class Maze 
{
public:
	enum class Tile : char
	{
		START = 'S',
		GOAL = 'G',
		WALL = '#',
		FLOOR = ' ',
		VISITED = 'O'
	};
	// Creates default test maze
	Maze();
	Maze(int width, int height, const std::vector<Maze::Tile>& maze_structure);
	Maze(int width, int height, const std::string maze_string);
	Maze::Tile at(Position pos) const;
	Position get_start_pos() const;
	Position get_goal_pos() const;
	std::string as_string() const;
	int get_width() const;
	int get_height() const;

private:
	int width, height;
	std::vector<Maze::Tile> structure;
	Position start_pos;
	Position goal_pos;
	std::string structure_string;
};

#endif // INLUPP_MAZE_INCLUDED