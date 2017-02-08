#include "main.h"

int main(void)
{
	int i, j;
	int step; 
	FILE *fp;
	int n;

	igraph_t graph;
	axl_agent *agents;

	/* Init all random number generators with SEED */
	srand(SEED);
	igraph_rng_seed(igraph_rng_default(), SEED);

	/* Table of attributes */
        igraph_i_set_attribute_table(&igraph_cattribute_table);

	/* Init network topology */
	init_network(&graph, N, VIRTUAL_LINKS, SEED);

	fp = fopen("Grafo_inicial.graphml","a");
	igraph_write_graph_graphml(&graph, fp, 0);
	fclose(fp);

	/* New number of agents */
	n = graph.n;

	/* Init Axelrod agents */
	agents = (axl_agent *)malloc(sizeof(axl_agent) * n);
	init_agents(agents, n, AXELROD_F, AXELROD_Q, rand());

	/* Do STEPS steps of dynamics */
	for(step = 0; step < STEPS; step++)
	{
		dynamics(&graph, agents, rand());
/*		if(step % 1000 == 0)
		{
			if(active_links(&graph, agents) == 1)
				continue;
			else
			{
				printf("Final step: %d\n", step);
				break;
			}
		}
*/
	}
/*
	fp = fopen("States.txt","a");
	for(i = 0; i < graph.n; i++)
	{
		for(j = 0; j < AXELROD_F; j++)
			fprintf(fp, "%d ", agents[i].feat[j]);
		fprintf(fp, "\n");
	}
	fclose(fp);
*/
	fp = fopen("Grafo.graphml","a");
	igraph_write_graph_graphml(&graph, fp, 0);
	fclose(fp);
	
	free(agents);
	igraph_destroy(&graph);

	return 1;
}
