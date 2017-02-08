#include "init_network.h"

int init_network(igraph_t *graph, int n, int virtual_links, int seed)
{
	int i, eid;
	int es_all;

	srand(seed);

	igraph_vector_t dim;
	igraph_vector_t edge;

	igraph_vector_init(&dim, 2);
	igraph_vector_init(&edge, 2);

	VECTOR(dim)[0] = (int)sqrt(n);
	VECTOR(dim)[1] = (int)sqrt(n);

	igraph_lattice(graph, &dim, 0, 0, 0, 0);

	es_all = igraph_ecount(graph);
	for(eid = 0; eid < es_all; eid++)
	        igraph_cattribute_EAS_set(graph, "t", eid, "p");

	for(i = 0; i < virtual_links; i++)
	{
		do
		{
			VECTOR(edge)[0] = rand() % graph->n;
			VECTOR(edge)[1] = rand() % graph->n;	
			igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);
		}
		while((eid != -1) || (VECTOR(edge)[0] == VECTOR(edge)[1]));

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	        igraph_cattribute_EAS_set(graph, "t", eid, "v");
	}

	igraph_vector_destroy(&dim);
	igraph_vector_destroy(&edge);

	return 1;
}
