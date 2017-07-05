#ifndef INLUPP_1_3_NEURAL_NET_NEURALNET_H
#define INLUPP_1_3_NEURAL_NET_NEURALNET_H

#include <vector>
#include <tuple>

class NeuralNet
{
public:
	// INPUT is an unbiased identity node
	enum class NodeType
	{
		INPUT, SIGMOID
	};
	// One number for each layer specifying how many nodes in that layer, optional specification of node types
	NeuralNet(std::vector<int> layers,
	          NodeType input_nodes = NodeType::INPUT,
	          NodeType hidden_nodes = NodeType::SIGMOID,
	          NodeType output_nodes = NodeType::SIGMOID,
	          double learning_rate = 0.25);
	void process(std::vector<double> input);
	std::vector<double> get_output() const;
	static double mean_square_error(std::vector<double> calculated_result, std::vector<double> desired_result);
	// Returns final error
	double train(std::vector<std::vector<double>> inputs,
	             std::vector<std::vector<double>> desired_outputs,
	             double acceptable_error = 0.05,
	             int maximum_epocs = 10000);
	// todo tweak default parameters

private:
	typedef double (* NodeFunction)(double, bool);

	static double sigmoid(double x, bool derivative);
	static double identity(double x, bool derivative);
	// todo consider adding support for momentum
	void backprop(std::vector<double> desired_result);

	struct Node
	{
		Node(NodeFunction function, double bias);
		NodeFunction function;
		double bias;
		std::vector<double> weights;
		double value;

	private:
		Node() = delete;
	};

	struct Layer
	{
		Layer(int nodes, NodeType type);
		void set_child(const Layer& child);
		std::vector<Node> nodes;
	};

	std::vector<Layer> m_layers;
	double m_learning_rate;
};

#endif //INLUPP_1_3_NEURAL_NET_NEURALNET_H
