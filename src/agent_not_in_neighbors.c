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

int virtual_neighbour(igraph_t *graph, int id, int random_seed)
{
	int ans, i, eid, non_virtual;
	int size;
	char *type_edge;
	char virtual_type[1] = "v";

        igraph_vector_t neighbors;
        igraph_vector_init(&neighbors, 0);

        igraph_rng_seed(igraph_rng_default(), random_seed);

        igraph_neighbors(graph, &neighbors, id, IGRAPH_ALL);

        size = igraph_vector_size(&neighbors);

	non_virtual = 0;
	for(i = 0; i < size; i++)
	{
               /* Get id of the edge between them */
                igraph_get_eid(graph, &eid, id, VECTOR(neighbors)[i], 0, 0);
	  	/* Type of the edge */
                type_edge = (char *)igraph_cattribute_EAS(graph, "t", eid);
		if(*type_edge == *virtual_type)
			break;
		else non_virtual += 1;
	}
        if(non_virtual < size)
        {
		do
		{
        	        i = igraph_rng_get_integer(igraph_rng_default(), 0, size-1);
        	        ans = VECTOR(neighbors)[i];
	               /* Get id of the edge between them */
        	        igraph_get_eid(graph, &eid, id, ans, 0, 0);

		  	/* Type of the edge */
        	        type_edge = (char *)igraph_cattribute_EAS(graph, "t", eid);
		}
		while(*type_edge != *virtual_type);

                igraph_vector_destroy(&neighbors);
                return ans;
        }
        else 
	{
                igraph_vector_destroy(&neighbors);
		return -1;
	}
}
