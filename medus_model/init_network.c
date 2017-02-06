#include "init_network.h"

int init_network(igraph_t *graph, int n)
{
	igraph_vector_t dim;

	igraph_vector_init(&dim, 2);
	VECTOR(dim)[0] = (int)sqrt(n);
	VECTOR(dim)[1] = (int)sqrt(n);

	igraph_lattice(graph, &dim, 0, 0, 0, 0);

	igraph_vector_destroy(&dim);

	return 1;
}
