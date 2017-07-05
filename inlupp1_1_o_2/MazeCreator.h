#ifndef INLUPP_MAZECREATOR_INCLUDED
#define INLUPP_MAZECREATOR_INCLUDED

#include "Maze.h"

#include <string>
#include <vector>

struct Position;

class MazeCreator
{
public:
	// 0=floor, 1=wall, excludes start, goal and outer walls, and should have length (width-2)*(height-2)-2
	static Maze from_binary_string(int width, int height, Position start_pos, Position goal_pos, std::string binary_string);
	// false=floor, true=wall, excludes start, goal and outer walls, and should have size (width-2)*(height-2)-2
	static Maze from_bool_vector(int width, int height, Position start_pos, Position goal_pos, std::vector<bool> bool_vector);

private:
	MazeCreator();
};

#endif // INLUPP_MAZECREATOR_INCLUDED