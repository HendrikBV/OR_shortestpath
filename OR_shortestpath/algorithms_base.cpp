#include "algorithms.h"
#include <fstream>
#include <random>
#include <stdexcept>
#include <iostream>



namespace SP
{
	Output& operator<<(Output& output, const std::string& msg)
	{
		if (output._on) {
			std::cout << msg;
		}
		// otherwise no output
		return output;
	}

	Output& operator<<(Output& output, const char* msg)
	{
		if (output._on) {
			std::cout << msg;
		}
		// otherwise no output
		return output;
	}

	Output& operator<<(Output& output, long unsigned int value)
	{
		if (output._on) {
			std::cout << value;
		}
		// otherwise no output
		return output;
	}

	Output& operator<<(Output& output, size_t value)
	{
		if (output._on) {
			std::cout << value;
		}
		// otherwise no output
		return output;
	}

	Output& operator<<(Output& output, unsigned int value)
	{
		if (output._on) {
			std::cout << value;
		}
		// otherwise no output
		return output;
	}

	Output& operator<<(Output& output, int value)
	{
		if (output._on) {
			std::cout << value;
		}
		// otherwise no output
		return output;
	}

	Output& operator<<(Output& output, int64_t value)
	{
		if (output._on) {
			std::cout << value;
		}
		// otherwise no output
		return output;
	}

	Output& operator<<(Output& output, float value)
	{
		if (output._on) {
			std::cout << value;
		}
		// otherwise no output
		return output;
	}

	Output& operator<<(Output& output, double value)
	{
		if (output._on) {
			std::cout << value;
		}
		// otherwise no output
		return output;
	}


	///////////////////////////////////////////////////////////////////////////


	void Algorithm::read_data(const std::string& filename)
	{
		std::ifstream file;
		file.open(filename);
		if (!file.is_open())
		{
			throw std::invalid_argument("Couldn't open the file with name " + filename);
		}

		file >> _nb_nodes;

		_graph.clear();
		_graph.reserve(_nb_nodes * _nb_nodes);

		for (size_t i = 0; i < _nb_nodes; ++i)
		{
			for (size_t j = 0; j < _nb_nodes; ++j)
			{
				int k;
				file >> k;
				_graph.push_back(k);
			}
		}
	}


	void Algorithm::check_solution()
	{
		bool ok = true;
		std::cout << "\n";

		// ...

		//if (ok)
			//std::cout << "\nCheck solution: OK";
	}


	///////////////////////////////////////////////////////////////////////////


	std::unique_ptr<Algorithm> AlgorithmFactory::create(std::string& algorithm)
	{
		std::transform(algorithm.begin(), algorithm.end(), algorithm.begin(),
			[](unsigned char c) { return std::tolower(c); });


		if (algorithm == "dijkstra")
			return std::make_unique<Dijkstra>();
		else if (algorithm == "bellman-ford" || algorithm == "bf")
			return std::make_unique<BF>();
		else
			throw std::invalid_argument("No algorithm " + algorithm + " exists");
	}
}