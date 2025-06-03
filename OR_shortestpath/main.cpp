#include "algorithms.h"
#include "cxxopts.h"
#include <iostream>
#include <memory>



int main(int argc, char* argv[])
{
	try
	{
		cxxopts::Options options("OR -- Shortest Path",
			"This program implements some algorithms for the shortest path problem.");

		options.add_options()
			("algorithm", "The choice of algorithm. Possibilities:"
				"\n\t* \"Dijkstra\": Dijkstra's algorithm"
				"\n\t* \"BF\": the Bellman-Ford algorithm"
				, cxxopts::value<std::string>())
			("data", "Name of the file containing the problem data", cxxopts::value<std::string>())
			("verbose", "Explain the various steps of the algorithm", cxxopts::value<bool>())
			("help", "Help on how to use the application");



		auto result = options.parse(argc, argv);

		if (argc <= 1 || result.count("help"))
		{
			std::cout << options.help() << "\n\n\n\n\n";
			return EXIT_SUCCESS;
		}

		std::string algorithm;
		if (result.count("algorithm"))
			algorithm = result["algorithm"].as<std::string>();

		std::string datafile;
		if (result.count("data"))
			datafile = result["data"].as<std::string>();

		bool verbose = false;
		if (result.count("verbose"))
			verbose = result["verbose"].as<bool>();




		// create the algorithm and run it
		std::unique_ptr<SP::Algorithm> problem = SP::AlgorithmFactory::create(algorithm);
		problem->read_data(datafile);
		problem->run(verbose);
		problem->check_solution();



		std::cout << "\n\n\n\n\n";
		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cout << "\n\n" << e.what() << "\n\n\n\n\n";
		return EXIT_FAILURE;
	}
}