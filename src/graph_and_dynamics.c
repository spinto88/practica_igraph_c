#include "graph_and_dynamics.h"

int graph_and_dynamics(axl_agent *agents, int virtual_links, int seed)
{
	int step; 
	FILE *fp;
	char fName[64];

	igraph_t graph;

	/* Init the random number generator with seed */
	srand(seed);

	/* Table of attributes */
        igraph_i_set_attribute_table(&igraph_cattribute_table);

	/* Init network topology */
	init_network(&graph, DIM_1, DIM_2, virtual_links, seed);

	/* Do STEPS steps of dynamics */
	for(step = 0; step < STEPS; step++)
	{
		dynamics(&graph, agents, rand());
		if(step % 1000 == 0)
		{
			if(active_links(&graph, agents) == 1)
				continue;
			else
				break;
		}

	}

	add_features_info(&graph, agents);

	sprintf(fName, "Graph2_q%d_vl%d.graphml", agents->q, virtual_links);

        fp = fopen(fName,"w");
        igraph_write_graph_graphml(&graph, fp, 0);
        fclose(fp);

	igraph_destroy(&graph);

	return 1;
}
