#include "agent_not_in_neighbors.h"

int agent_not_in_neighbors(igraph_t *graph, int agent, int seed)
{
	int i, neighbour_aux;
	igraph_vector_t neighbors;

	srand(seed);

	igraph_vector_init(&neighbors, 0);
	igraph_neighbors(graph, &neighbors, agent, IGRAPH_ALL);

	neighbour_aux = rand() % graph->n;
	while(igraph_vector_contains(&neighbors, neighbour_aux))
		neighbour_aux = rand() % graph->n;

	igraph_vector_destroy(&neighbors);

	return neighbour_aux;
}
