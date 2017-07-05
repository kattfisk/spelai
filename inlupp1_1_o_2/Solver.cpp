#include "Solver.h"

#include "Position.h"
#include "Solver.h"
#include "Display.h"
#include "Maze.h"

#include <chrono>
#include <thread>

namespace
{
	const int DISPLAY_DELAY = 300; // ms
}

Solver::~Solver()
{
}

std::string Solver::get_name() const
{
	return ALGO_NAME;
}

int Solver::get_upper_bound(const Maze& maze) const
{
	// This will be correct for all solvers that do not revisit nodes
	// Outer walls are assumed and removed
	return (maze.get_width() - 2) * (maze.get_height() - 2);
}

Solver::Solver(std::string algoritm_name, Display* display)
	: ALGO_NAME(algoritm_name),
	  display(display),
	  display_progress(!(display == nullptr))
{
}

void Solver::show_step(Position pos)
{
		if(display_progress && display != nullptr)
		{
			display->print();
			std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_DELAY));
			display->mark(pos);
		}
}