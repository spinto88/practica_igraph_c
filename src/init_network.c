#include "init_network.h"

int init_network(igraph_t *graph, int dim1, int dim2, int virtual_links, int seed)
{
	int i, eid;
	int es_all;
	int n = dim1 * dim2;

	srand(seed);

	igraph_vector_t dim;
	igraph_vector_t edge;

	igraph_vector_init(&dim, 2);
	igraph_vector_init(&edge, 2);

        /* Table of attributes */
        igraph_i_set_attribute_table(&igraph_cattribute_table);

	VECTOR(dim)[0] = dim1;
	VECTOR(dim)[1] = dim2;

	igraph_lattice(graph, &dim, 2, 0, 0, 0);
	for(i = 0; i < n; i++)
	{
		igraph_cattribute_VAN_set(graph, "pos_x", i, i / dim1);
		igraph_cattribute_VAN_set(graph, "pos_y", i, i % dim1);
	}
       
	// Make a middle barrier i.e. delete the middle vertices
	for(i = 0; i < 2*dim1; i++)
		igraph_delete_vertices(graph, igraph_vss_1(dim2/2 * dim1));
       
	
	// Set as personal edges the lattice's ones
	es_all = igraph_ecount(graph);
	for(eid = 0; eid < es_all; eid++)
	        igraph_cattribute_EAS_set(graph, "t", eid, "p");

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
