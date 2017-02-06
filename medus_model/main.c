#include "main.h"

int main(void)
{
	int step; 

	igraph_t graph;
	axl_agent *agents;

	/* Init all random number generators with SEED */
	srand(SEED);
	igraph_rng_seed(igraph_rng_default(), SEED);

	/* Init network topology */
	init_network(&graph, N);

	/* Init Axelrod agents */
	agents = (axl_agent *)malloc(sizeof(axl_agent) * N);
	init_agents(agents, N, AXELROD_F, AXELROD_Q, rand());

	/* Do STEPS steps of dynamics */
	for(step = 0; step < STEPS; step++)
		dynamics(&graph, agents, rand());
	
	free(agents);
	igraph_destroy(&graph);

	return 1;
}
