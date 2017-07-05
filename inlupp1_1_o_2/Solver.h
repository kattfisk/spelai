#ifndef INLUPP_SOLVER_INCLUDED
#define INLUPP_SOLVER_INCLUDED

#include <string>

class Maze;
class Display;
struct Position;
struct SearchResult;

class Solver
{
public:
	virtual ~Solver() = 0;
	virtual SearchResult solve(const Maze& maze, bool display_progress = false) = 0;
	virtual std::string get_name() const;
	// Returns the theoretical maximum number of steps the solve the given maze
	virtual int get_upper_bound(const Maze& maze) const;

protected:
	Solver(std::string algoritm_name, Display* display = nullptr);
	void show_step(Position pos);
	const std::string ALGO_NAME;
	Display* display;
	bool display_progress;

private:
	Solver(const Solver&);
	Solver& operator=(const Solver&);
};

#endif // INLUPP_SOLVER_INCLUDED