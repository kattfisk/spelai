#include "Display.h"

#include "Maze.h"
#include "Position.h"

#include <iostream>

Display::Display(const Maze& maze)
	: maze_width(maze.get_width()), 
	  maze_height(maze.get_height()),
	  structure_clear(maze.as_string()),
	  structure(structure_clear)
{
}

void Display::mark(Position pos)
{
	structure.at(pos.x + pos.y * maze_width) = static_cast<char>(Maze::Tile::VISITED);
}

void Display::print() const
{
	for(int i = 0; i < maze_height; ++i)
	{
		std::cout << structure.substr(i * maze_width, maze_width) << "\n";
	}
	std::cout << "\n\n";
}

void Display::clear_progress()
{
	structure = structure_clear;
}