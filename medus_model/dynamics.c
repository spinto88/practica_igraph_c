#include "dynamics.h"

int dynamics(igraph_t *graph, axl_agent *agents, int seed)
{
	int i;
	int agent, neighbour, neighbour_aux;
	double random, hom, hom_aux;
	int n = graph->n;

	igraph_es_t es;
	igraph_vector_t v;

	igraph_vector_init(&v,2);

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
				imitation(&(agents[agent]), &(agents[neighbour]), rand());	
			else
				continue;
		}
		
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
				// Create the new edge 
//				igraph_add_edge(graph, agent, neighbour_aux);			

				// Delete the old edge 
				VECTOR(v)[0] = agent;
				VECTOR(v)[1] = neighbour;

				igraph_es_pairs(&es, &v, 0);
//				igraph_delete_edges(graph, es);			
			}
			// Else, continue 
			else
				continue;
		}
	
	}

	igraph_es_destroy(&es);
	igraph_vector_destroy(&v);
	
	return 1;
}
