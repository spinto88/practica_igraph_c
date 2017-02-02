#include <igraph.h>

int random_neighbour(igraph_t *graph, int id, int random_seed)
{
	int i;

	igraph_vector_t neighbors;
	igraph_vector_init(&neighbors,0);

	igraph_rng_seed(igraph_rng_default(), random_seed);

	igraph_neighbors(graph, &neighbors, id, IGRAPH_ALL);

	i = igraph_rng_get_integer(igraph_rng_default(), 0, igraph_vector_size(&neighbors));

	return VECTOR(neighbors)[i];
}

int main()
{
	int i;

	igraph_t graph;
	igraph_vector_t dim;

	igraph_vector_init(&dim, 2);

	VECTOR(dim)[0] = 10;
	VECTOR(dim)[1] = 10;

	igraph_lattice(&graph, &dim, 0, 0, 0, 1);

	i = random_neighbour(&graph, 0, 49);
	printf("%d\n",i);

	igraph_destroy(&graph);
	igraph_vector_destroy(&dim);

	return 1;
}
