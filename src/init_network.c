#include "init_network.h"

int init_network(igraph_t *graph, int n, int virtual_links, int virtual_type, int seed)
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

        /* Non-periodic lattice */
	igraph_lattice(graph, &dim, 1, 0, 0, 0);
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
	for(i = 0; i < (n2-n); i++)
	{
		if((i%n) != (n-1))
		{
			VECTOR(edge)[0] = i;
			VECTOR(edge)[1] = (i%n+1)%n + ((i/n+1)%n) * n;	

			igraph_add_edges(graph, &edge, 0);
			igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	        	igraph_cattribute_EAS_set(graph, "t", eid, "p");
		}

		if((i%n) != 0)
		{
			VECTOR(edge)[0] = i;
			VECTOR(edge)[1] = (i%n-1 + n)%n + ((i/n+1)%n) * n;	

			igraph_add_edges(graph, &edge, 0);
			igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);
	
		        igraph_cattribute_EAS_set(graph, "t", eid, "p");
		}
	}

	// Set a fraction of personal edges rewirible
	es_all = igraph_ecount(graph);
	for(eid = 0; eid < es_all; eid++)
	{
		if(((double)rand())/RAND_MAX < 0.1)
		        igraph_cattribute_EAS_set(graph, "t", eid, "r");
	}
        
	// Add the virtual links
        if(virtual_type == 0)
	// Add virtual links in a random way
	{
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
	}
        else if(virtual_type == 1 || virtual_type == 2)
	// Add virtual links in a static way 
	{
	if(virtual_type == 1)
	{

	// Add the virtual statics links
	for(i = 0; i < n2; i++)
	{
		VECTOR(edge)[0] = i;

		VECTOR(edge)[1] = (i%n+2)%n + ((i/n+2)%n) * n;	

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	       	igraph_cattribute_EAS_set(graph, "t", eid, "p");

		VECTOR(edge)[1] = (i%n-2+n)%n + ((i/n+2)%n) * n;	

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	       	igraph_cattribute_EAS_set(graph, "t", eid, "p");
	
		VECTOR(edge)[1] = (i%n+2)%n + ((i/n)%n) * n;	

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	       	igraph_cattribute_EAS_set(graph, "t", eid, "p");

		VECTOR(edge)[1] = (i%n)%n + ((i/n+2)%n) * n;	

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	       	igraph_cattribute_EAS_set(graph, "t", eid, "p");
	}

	}
	else if(virtual_type == 2)
	{

	// Add the virtual statics links
	for(i = 0; i < n2; i++)
	{
		VECTOR(edge)[0] = i;

		VECTOR(edge)[1] = (i%n+2)%n + ((i/n+2)%n) * n;	

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	       	igraph_cattribute_EAS_set(graph, "t", eid, "v");

		VECTOR(edge)[1] = (i%n-2+n)%n + ((i/n+2)%n) * n;	

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	       	igraph_cattribute_EAS_set(graph, "t", eid, "v");
	
		VECTOR(edge)[1] = (i%n+2)%n + ((i/n)%n) * n;	

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	       	igraph_cattribute_EAS_set(graph, "t", eid, "v");

		VECTOR(edge)[1] = (i%n)%n + ((i/n+2)%n) * n;	

		igraph_add_edges(graph, &edge, 0);
		igraph_get_eid(graph, &eid, VECTOR(edge)[0], VECTOR(edge)[1], 0, 0);

	       	igraph_cattribute_EAS_set(graph, "t", eid, "v");
	}
	}	
	}

	igraph_vector_destroy(&dim);
	igraph_vector_destroy(&edge);

	return 1;
}
