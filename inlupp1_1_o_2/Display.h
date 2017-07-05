#ifndef INLUPP_DISPLAY_INCLUDED
#define INLUPP_DISPLAY_INCLUDED

#include <string>

class Maze;
struct Position;

class Display
{
public:
	Display(const Maze& maze);
	void mark(Position pos);
	void print() const;
	void clear_progress();

private:
	int maze_width, maze_height;
	std::string structure_clear;
	std::string structure;
};

#endif // INLUPP_DISPLAY_INCLUDED