#include "random_neighbour.h"

int random_neighbour(igraph_t *graph, int id, int random_seed)
{
	int i;

	igraph_vector_t neighbors;
	igraph_vector_init(&neighbors, 0);

	igraph_rng_seed(igraph_rng_default(), random_seed);

	igraph_neighbors(graph, &neighbors, id, IGRAPH_ALL);

	i = igraph_rng_get_integer(igraph_rng_default(), 0, igraph_vector_size(&neighbors));

	return VECTOR(neighbors)[i];
}