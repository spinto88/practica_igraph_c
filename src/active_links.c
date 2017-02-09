
#include "active_links.h"

int active_links(igraph_t *graph, axl_agent *agents)
{
	/* Active links: this function return if an active link is found.
	An active link is a pair of agents which are neighbors and the homophily
        is larger than zero and less than one. */

	int i, j;
        int n = graph->n, size;
        int neighbour;
        double hab;

	igraph_vector_t neighbors;
	igraph_vector_init(&neighbors, 0);

        for(i = 0; i < n; i++)
	{
		igraph_neighbors(graph, &neighbors, i, IGRAPH_ALL);
		size = igraph_vector_size(&neighbors);

		for(j = 0; j < size; j++)
		{
                        neighbour = VECTOR(neighbors)[j];
			if (i < neighbour)
			{
				hab = homophily(agents[i], agents[neighbour]);
				if((0.00 < hab) && (hab < 1.00))
				{
					igraph_vector_destroy(&neighbors);
					return 1;
				}
			}
		}
	}

	igraph_vector_destroy(&neighbors);
	return 0;	
}
		

