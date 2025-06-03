#pragma once
#ifndef ALGORITHMS_SP_H
#define ALGORITHMS_SP_H


#include <exception>
#include <vector>
#include <string>
#include <memory>



namespace SP // shortest path
{
	class Output
	{
		bool _on = true;

	public:
		void set_on(bool on) { _on = on; }
		friend Output& operator<<(Output& output, const std::string& msg);
		friend Output& operator<<(Output& output, const char* msg);
		friend Output& operator<<(Output& output, long unsigned int value);
		friend Output& operator<<(Output& output, size_t value);
		friend Output& operator<<(Output& output, unsigned int value);
		friend Output& operator<<(Output& output, int value);
		friend Output& operator<<(Output& output, int64_t value);
		friend Output& operator<<(Output& output, float value);
		friend Output& operator<<(Output& output, double value);
	};

	///////////////////////////////////////////////////////////////////////////

	// Base class
	class Algorithm
	{
	protected:
		// output
		Output _output;
		bool _verbose;

		// network
		size_t _nb_nodes;
		std::vector<int> _graph; // [i*nb_nodes+j] == distance from node i to node j (large value if no edge exists)
		int distance(int from_node, int to_node) { return _graph[from_node * _nb_nodes + to_node]; }

		// optimal solution
		int _optimal_length = std::numeric_limits<int>::max();
		

	public:
		virtual ~Algorithm() {}

		void read_data(const std::string& filename);
		void check_solution();
		virtual void run(bool verbose) = 0;
	};

	///////////////////////////////////////////////////////////////////////////

	// Dijkstra
	class Dijkstra : public Algorithm
	{

	public:
		void run(bool verbose) override;
	};

	///////////////////////////////////////////////////////////////////////////

	// Bellman-Ford
	class BF : public Algorithm
	{

	public:
		void run(bool verbose) override;
	};

	///////////////////////////////////////////////////////////////////////////

	class AlgorithmFactory
	{
	public:
		static std::unique_ptr<Algorithm> create(std::string& algorithm);
	};


}

#endif // ALGORITHMS_SP_H