#include "agent_not_in_neighbors.h"

int agent_not_in_neighbors(igraph_t *graph, int agent, int seed)
{
	int new_neighbour, eid;
	igraph_vector_t new_edge;

	srand(seed);

	igraph_vector_init(&new_edge, 2);
	VECTOR(new_edge)[0] = agent;

	do
	{
		new_neighbour = rand() % graph->n;
		VECTOR(new_edge)[1] = new_neighbour;
		igraph_get_eid(graph, &eid, agent, new_neighbour, 0, 0);	
	}
	while(eid != -1 || agent == new_neighbour);

	igraph_vector_destroy(&new_edge);

	return new_neighbour;
}
