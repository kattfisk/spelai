#include "NeuralNet.h"

#include <cmath>
#include <assert.h>

namespace
{
	double random_weight()
	{
		static const double LOWER_BOUND = 0.05;
		static const double UPPER_BOUND = 0.5;
		static const double DOUBLE_RAND_MAX = static_cast<double>(RAND_MAX);

		// Don't seed srand so we'll get the same values every program run
		double val = static_cast<double>(std::rand()) / DOUBLE_RAND_MAX;
		val = LOWER_BOUND + val * (UPPER_BOUND - LOWER_BOUND);
		return val;
	}
}

NeuralNet::NeuralNet(std::vector<int> layers,
                     NodeType input_nodes,
                     NodeType hidden_nodes,
                     NodeType output_nodes,
                     double learning_rate)
: m_layers(), m_learning_rate(learning_rate)
{
	assert(layers.size() >= 2);

	m_layers.push_back(Layer(layers.at(0), input_nodes));
	for(unsigned int i = 1; i < (layers.size() - 1); ++i)
	{
		m_layers.push_back(Layer(layers[i], hidden_nodes));
	}
	m_layers.push_back(Layer(layers.at(layers.size() - 1), output_nodes));

	for(unsigned int i = 0; i < (m_layers.size() - 1); ++i)
	{
		m_layers[i].set_child(m_layers[i + 1]);
	}
}

void NeuralNet::process(std::vector<double> input)
{
	assert(m_layers.size() > 0);
	assert(input.size() == m_layers.at(0).nodes.size());

	// Input layer
	for(unsigned int i = 0; i < m_layers[0].nodes.size(); ++i)
	{
		Node& current_node = m_layers[0].nodes[i];
		// todo Ignore weight for input?
		current_node.value = current_node.function(input[i], false);
	}

	// Hidden and output
	for(unsigned int i = 1; i < m_layers.size(); ++i)
	{
		Layer& parent_layer = m_layers[i - 1];
		Layer& current_layer = m_layers[i];

		for(unsigned int j = 0; j < current_layer.nodes.size(); ++j)
		{
			Node& current_node = current_layer.nodes[j];

			double parent_input(0.0);
			for(unsigned int k = 0; k < parent_layer.nodes.size(); ++k)
			{
				const Node& parent_node = parent_layer.nodes[k];
				parent_input += parent_node.value * parent_node.weights[j];
			}
			current_node.value = current_node.function(parent_input + current_node.bias, false);
		}
	}
}

std::vector<double> NeuralNet::get_output() const
{
	assert(m_layers.size() > 0);
	const Layer& output_layer = m_layers[m_layers.size() - 1];
	std::vector<double> output;
	for(const Node& n : output_layer.nodes)
	{
		output.push_back(n.value);
	}
	return output;
}

double NeuralNet::mean_square_error(std::vector<double> calculated_result, std::vector<double> desired_result)
{
	assert(calculated_result.size() == desired_result.size());
	unsigned int n = calculated_result.size();
	double error = 0.0;
	for(unsigned int i = 0; i < n; ++i)
	{
		double y = calculated_result[i] - desired_result[i];
		error += y * y;
	}
	return error / n;
}

double NeuralNet::train(std::vector<std::vector<double>> inputs,
                        std::vector<std::vector<double>> desired_outputs,
                        double acceptable_error,
                        int maximum_epocs)
{
	assert(inputs.size() == desired_outputs.size());
	assert(inputs.size() > 0);

	double error = 0.0;
	const int sets = static_cast<int>(inputs.size());

	int epochs(0);
	do
	{
		error = 0.0;
		for(int i = 0; i < sets; ++i)
		{
			const std::vector<double>& input = inputs.at(i);
			const std::vector<double>& target_output = desired_outputs.at(i);
			process(input);
			error += mean_square_error(get_output(), target_output);
			backprop(target_output);
		}
		error /= sets;
		++epochs;
	} while(error > acceptable_error && epochs < maximum_epocs);

	return error;
}

double NeuralNet::sigmoid(double x, bool derivative)
{
	// y = 1/(1 + e^-x)
	double y = 1.0 / (1.0 + std::exp(-x));
	if(derivative)
	{
		// y1 = y(1 - y)
		return y * (1.0 - y);
	}
	else
	{
		return y;
	}
}

double NeuralNet::identity(double x, bool derivative)
{
	if(derivative)
	{
		return 1.0;
	}
	else
	{
		return x;
	}
}

void NeuralNet::backprop(std::vector<double> desired_result)
{
	assert(m_layers.size() >= 2);
	std::vector<Node>& output_nodes = m_layers[m_layers.size() - 1].nodes;
	assert(desired_result.size() == output_nodes.size());

	std::vector<double> child_errors(output_nodes.size(), 0.0);
	// Output layer
	for(unsigned int i = 0; i < output_nodes.size(); ++i)
	{
		Node& current_node = output_nodes[i];
		double delta(desired_result[i] - current_node.value);
		child_errors[i] = delta * output_nodes[i].function(current_node.value, true);
		// Adjust bias weight
		// todo consider separate bias learning rate
		current_node.bias += child_errors[i] * m_learning_rate;
	}
	// Hidden and input layers
	for(int i = static_cast<int>(m_layers.size() - 2); i >= 0; --i)
	{
		// We calculate errors for the input layer, but they are never used
		Layer& current_layer = m_layers[i];
		std::vector<double> current_errors(current_layer.nodes.size(), 0.0);
		for(unsigned int j = 0; j < current_layer.nodes.size(); ++j)
		{
			Node& current_node = current_layer.nodes[j];
			const Layer& child_layer = m_layers[i + 1];
			double current_error(0.0);
			for(unsigned int k = 0; k < child_layer.nodes.size(); ++k)
			{
				// Sum error from child node
				current_error += child_errors[k] * current_node.weights[k];
				// Adjust connection weight
				current_node.weights[k] += child_errors[k] * current_node.value * m_learning_rate;
				// Adjust bias
				// todo consider using other, lower learning rate for bias
				current_node.bias += child_errors[k] * m_learning_rate;
			}
			current_error *= current_node.function(current_node.value, true);
			current_errors[j] = current_error;
		}
		child_errors = std::move(current_errors);
	}
}

NeuralNet::Node::Node(NodeFunction function, double bias)
: function(function), bias(bias), weights(), value(0.0)
{
}

NeuralNet::Layer::Layer(int nodes, NodeType type)
: nodes()
{
	if(type == NodeType::SIGMOID)
	{
		for(int i = 0; i < nodes; ++i)
		{
			this->nodes.push_back(Node(&sigmoid, random_weight()));
		}
	}

	if(type == NodeType::INPUT)
	{
		for(int i = 0; i < nodes; ++i)
		{
			this->nodes.push_back(Node(&identity, 0.0));
		}
	}
}

void NeuralNet::Layer::set_child(const Layer& child)
{
	int child_nodes = static_cast<int>(child.nodes.size());
	for(Node& n : nodes)
	{
		for(int i = 0; i < child_nodes; ++i)
		{
			n.weights.push_back(random_weight());
		}
	}
}
