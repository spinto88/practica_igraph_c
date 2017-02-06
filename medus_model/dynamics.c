#include "dynamics.h"

int dynamics(igraph_t *graph, axl_agent *agents, int seed)
{
	int i;
	int agent, neighbour, neighbour_aux;
	double random, hom, hom_aux;
	int n = graph->n;

	igraph_es_t es;

	srand(seed);

	for(i=0; i<n; i++)
	{
		/* Choose one agent and a random network */
		agent = rand() % n;
		neighbour = random_neighbour(graph, agent, rand());

		/* Calculate the homophily between them */
		random = (double)rand()/RAND_MAX;
		hom = homophily(agents[agent], agents[neighbour]);

		/* If a random number is less than the homophily then imitate */
		if(random < hom)
		{
			if(hom != 1.00)
				imitation(agents[agent], agents[neighbour], rand());	
			else
				continue;
		}
		/*
		// Else, try to do rewiring 
		else
		{
			// Choose a random agent which is not a neighbour 
			neighbour_aux = agent_not_in_neighbors(graph, agent, rand());

			// Calculate the homophily between the new agent and the first one 
			hom_aux = homophily(agents[agent], agents[neighbour_aux]);
			
			// If the new homophily is larger than the old one, do a rewiring 
			if(hom_aux > hom)
			{
				// Delete the old edge 
				igraph_es_pairs_small(&es, IGRAPH_UNDIRECTED, agent, neighbour, -1);
				igraph_delete_edges(graph, es);			

				// Create the new edge 
				igraph_add_edge(graph, agent, neighbour_aux);			
			}
			// Else, continue 
			else
				continue;
		}
		*/
	}
	
	return 1;
}
