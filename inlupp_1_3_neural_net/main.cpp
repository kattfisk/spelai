#include <iostream>

#include "NeuralNet.h"

void show_table(NeuralNet& network, std::vector<std::vector<double>>& inputs)
{
	std::cout << " ----- Results for training data -----\n";
	for(unsigned int i = 0; i < inputs.size(); ++i)
	{
		network.process(inputs[i]);
		std::vector<double> result(network.get_output());

		std::cout << " ";
		for(double val : inputs[i])
		{
			std::cout << val << ", \t";
		}
		std::cout << " --> \t";
		for(double val : result)
		{
			std::cout << val << ", \t";
		}
		std::cout << "\n";
	}
}

int main()
{
	std::vector<int> nodes{2, 3, 1};
	NeuralNet network(nodes);

	// Train an inclusive or
	std::vector<std::vector<double>> inputs({{0.0, 0.0},
	                                         {0.0, 1.0},
	                                         {1.0, 1.0},
	                                         {1.0, 0.0}});
	std::vector<std::vector<double>> outputs({{0.0},
	                                          {1.0},
	                                          {1.0},
	                                          {1.0}});
	char user_input = ' ';
	int epochs = 500;
	double latest_error = 0.0, target_error = 0.005;
	while(user_input != 'q')
	{
		std::cout << "\n\n\n";
		show_table(network, inputs);
		std::cout << "Latest error: " << latest_error << "\n";
		std::cout << "Epochs = " << epochs << ", target error = " << target_error << "\n";
		std::cout << "a: run \nc: change number of epochs \ne: change target error \nt: show table \nq: quit \n";
		std::cin >> user_input;
		if(user_input == 'c')
		{
			std::cout << "Desired number of epochs: ";
			std::cin >> epochs;
			continue;
		}
		if(user_input == 'e')
		{
			std::cout << "Target error: ";
			std::cin >> target_error;
			continue;
		}
		if(user_input == 't')
		{
			show_table(network, inputs);
			continue;
		}
		if(user_input == 'a')
		{
			std::cout << "Running " << epochs << " epochs...\n";
			latest_error = network.train(inputs, outputs, target_error, epochs);
			std::cout << "Done. Error is now " << latest_error << "\n";
		}
	}
}