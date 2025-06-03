#include "algorithms.h"
#include <chrono>
#include <stdexcept>
#include <algorithm>



namespace SP
{
	void Dijkstra::run(bool verbose)
	{
		struct Label
		{
			int value = std::numeric_limits<int>::max();
			bool permanent = false;
		};

		std::vector<Label> node_labels;
		node_labels.reserve(_nb_nodes);
		for (size_t i = 0; i < _nb_nodes; ++i)
			node_labels.push_back(Label());
		node_labels[0].value = 0;

		for(size_t iteration = 0; iteration < _nb_nodes; ++iteration)
		{
			_output << "\n\nIteration: " << iteration + 1;

			// make smallest temporary label permanent
			size_t index = 0;
			{
				int smallest_value = std::numeric_limits<int>::max();
				for (size_t i = 0; i < node_labels.size(); ++i)
				{
					if (!node_labels[i].permanent && node_labels[i].value < smallest_value)
					{
						smallest_value = node_labels[i].value;
						index = i;
					}
				}

				node_labels[index].permanent = true;
				_output << "\nWe make the label for node " << index + 1 << " permanent";
			}

			// update temporary labels of nodes connected to this node
			{
				for (size_t j = 0; j < node_labels.size(); ++j)
				{
					if (!node_labels[j].permanent &&
						node_labels[index].value + distance(index, j) < node_labels[j].value)
					{
						node_labels[j].value = node_labels[index].value + distance(index, j);

						_output << "\nWe update the label for node " << j + 1 << " to " << node_labels[j].value;
					}
				}
			}
		}

		// print labels
		_output.set_on(true);
		_output << "\n\nLabels:  ";
		for (size_t i = 0; i < node_labels.size(); ++i)
		{
			_output << node_labels[i].value << "  ";
		}
	}
}