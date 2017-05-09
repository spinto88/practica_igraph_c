#include "init_network.h"

int init_network(igraph_t *graph, int n, int virtual_links, int seed)
{
	int i, eid;
	int es_all;
	int n2 = n * n;

	srand(seed);

	igraph_vector_t dim;
	igraph_vector_t edge;

	igraph_vector_init(&dim, 2);
	igraph_vector_init(&edge, 2);

        /* Table of attributes */
        igraph_i_set_attribute_table(&igraph_cattribute_table);

	VECTOR(dim)[0] = n;
	VECTOR(dim)[1] = n;

	igraph_lattice(graph, &dim, 1, 0, 0, 1);
	for(i = 0; i < n2; i++)
	{
		igraph_cattribute_VAN_set(graph, "pos_x", i, i / n);
		igraph_cattribute_VAN_set(graph, "pos_y", i, i % n);
	} 
	
	// Set as personal edges the lattice's ones
	es_all = igraph_ecount(graph);
	for(eid = 0; eid < es_all; eid++)
	        igraph_cattribute_EAS_set(graph, "t", eid, "p");

	// Add the more contact links 
	for(i = 0; i < n2; i++)
	{
		do
		{
			VECTOR(edge)[0] = i;
			VECTOR(edge)[1] = (i%n+1)%n + ((i/n+1)%n) * n;	
			igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);
		}
		while((eid != -1) || (VECTOR(edge)[0] == VECTOR(edge)[1]));

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	        igraph_cattribute_EAS_set(graph, "t", eid, "p");

		do
		{
			VECTOR(edge)[0] = i;
			VECTOR(edge)[1] = (i%n-1 + n)%n + ((i/n+1)%n) * n;	
			igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);
		}
		while((eid != -1) || (VECTOR(edge)[0] == VECTOR(edge)[1]));

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	        igraph_cattribute_EAS_set(graph, "t", eid, "p");
	}

	// Set a fraction of personal edges rewirible
	es_all = igraph_ecount(graph);
	for(eid = 0; eid < es_all; eid++)
	{
		if(((double)rand())/RAND_MAX < 0.1)
		        igraph_cattribute_EAS_set(graph, "t", eid, "pr");
	}

	// Add the virtual links 
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
