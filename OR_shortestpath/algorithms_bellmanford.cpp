#include "algorithms.h"
#include <chrono>
#include <stdexcept>
#include <algorithm>



namespace SP
{
	void BF::run(bool verbose)
	{
		struct Label
		{
			int current_label = 999999; // not std::numeric_limits<int>::max() due to overflow of int
			int new_label = 999999;
			int updated_from = -1;
		};

		std::vector<Label> node_labels;
		node_labels.reserve(_nb_nodes);
		for (size_t i = 0; i < _nb_nodes; ++i)
			node_labels.push_back(Label());
		node_labels[0].current_label = 0;
		node_labels[0].new_label = 0;


		bool change = false;
		int last_node_changed = -1;
		for (size_t iteration = 0; iteration < _nb_nodes; ++iteration)
		{
			_output << "\n\n\nIteration " << iteration + 1;
			change = false;

			for (size_t node = 0; node < _nb_nodes; ++node)
			{
				_output << "\n\nTrying to update the label for node " << node + 1;
				for (size_t j = 0; j < _nb_nodes; ++j)
				{
					if (node_labels[j].current_label + distance(j, node) < node_labels[node].new_label)
					{
						node_labels[node].new_label = node_labels[j].current_label + distance(j, node);
						node_labels[node].updated_from = j;

						change = true;
						last_node_changed = node;

						_output << "\nUpdate label to " << node_labels[node].new_label << " from node " << j + 1;
					}
				}
			}

			for (auto&& l : node_labels)
				l.current_label = l.new_label;

			if (!change)
			{
				_output << "\n\nNo further changes: labels have converged. We stop.";
				break;
			}
		}

		if (change)
		{
			_output << "\n\nThere is a negative cycle";
		}
	}

}