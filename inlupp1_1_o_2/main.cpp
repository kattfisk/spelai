#include "BFS.h"
#include "AStar.h"
#include "DFS.h"
#include "Maze.h"
#include "Display.h"
#include "SearchResult.h"
#include "MazeCreator.h"
#include "MazeEvolver.h"

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

int main()
{
	int user_selection = 0;
	bool run = true, use_display = true;
	Maze maze = Maze();
	Display display(maze);
	std::shared_ptr<Solver> solver(new BFS(&display));

	while(run)
	{
		std::cout << "\n\n--- Main menu --- \n";
		std::cout << "1: Solve maze \n";
		std::cout << "2: Toggle display \n";
		std::cout << "3: Select algoritm \n";
		std::cout << "4: Create maze \n";
		std::cout << "5: Quit \n";
		std::cin >> user_selection;
		switch (user_selection)
		{
		case 1:
			{
				SearchResult result = solver->solve(maze, use_display);
				display.clear_progress();
				std::cout << "Found path of length " << result.path.size() << " after " << result.steps_to_find << " iterations.\n";
				break;
			}
		case 2:
			use_display = !use_display;
			if(use_display)
				std::cout << "Will display maze while solving.\n";
			else
				std::cout << "Will not display maze while solving.\n";
			break;
		case 3:
			std::cout << "\n\nCurrent algoritm is " << solver->get_name() << "\n";
			std::cout << "1: Breadth-first search \n";
			std::cout << "2: Depth-first search \n";
			std::cout << "3: A* \n";
			std::cin >> user_selection;
			switch (user_selection)
			{
			case 1:
				solver = std::shared_ptr<Solver>(new BFS(&display));
				break;
			case 2:
				solver = std::shared_ptr<Solver>(new DFS(&display));
				break;
			case 3:
				solver = std::shared_ptr<Solver>(new AStar(&display));
				break;
			default:
				std::cout << "Error: Unrecognized input\n";
				break;
			}
			std::cout << solver->get_name() << " selected.\n";
			break;
		case 4:
			{
			//maze = MazeCreator::from_binary_string(7, 4, Position(1, 1), Position(5, 2), "00101100");
				Position start(1, 1);
				Position goal(10, 10);
				MazeEvolver evolver(start, goal, 20, 20, solver);
				int step = 10, total = 500;
				//for (int i = 0; i < total;)
				{
					//i += step;
					//evolver.evolve(step);
					evolver.evolve(1000);
					maze = evolver.get_best_solution();
					display = Display(maze);
					display.print();
					//std::this_thread::sleep_for(std::chrono::milliseconds(400));
				}
			break;
			}
		case 5:
			run = false;
			break;
		default:
			std::cout << "Error: Unrecognized input\n";
			break;
		}
	}
	return 0;
}