#include "dynamics.h"

int dynamics(igraph_t *graph, axl_agent *agents, double phi, int seed)
{
	int i, eid;
	int agent, neighbour, neighbour_aux;
	double random = 1.00;
	double hom, hom_aux;
	int n = graph->n;
	char *type_edge;
	char virtual_type[1] = "v";
	char personal_rew_type[1] = "r";

	srand(seed);

	for(i=0; i<n; i++)
	{
		/* Choose one agent and a random neighbour */
		agent = rand() % n;
		neighbour = random_neighbour(graph, agent, rand());

		/* Get id of the edge between them */
		igraph_get_eid(graph, &eid, agent, neighbour, 0, 0);

		/* Calculate the homophily between them */
		hom = homophily(agents[agent], agents[neighbour]);
		if (hom <= (1.00/agents[agent].f))
			hom = 0.00;

		/* Type of the edge */
		type_edge = (char *)igraph_cattribute_EAS(graph, "t", eid);

		/* If the edge is a virtual one, first try to rewire to another
			agent with more homophily */
		if(*type_edge == *virtual_type)
		{
			// Choose a random agent which is not a neighbour 
			neighbour_aux = agent_not_in_neighbors(graph, agent, rand());

			// Calculate the homophily between the new agent and the first one 
			hom_aux = homophily(agents[agent], agents[neighbour_aux]);
			
			// If the new homophily is larger than the old one, do a rewiring 
			if(hom_aux > hom)
			{
			        igraph_vector_t es_add;
			        igraph_vector_init(&es_add, 2);

			        igraph_es_t es_kill;

				// Create the new edge and set this one as virtual
				VECTOR(es_add)[0] = agent;
				VECTOR(es_add)[1] = neighbour_aux;
				igraph_add_edges(graph, &es_add, 0);			

				igraph_get_eid(graph, &eid, agent, neighbour_aux, 0, 0);
				igraph_cattribute_EAS_set(graph, "t", eid, "v");

				// Delete the old edge
				igraph_es_pairs_small(&es_kill, IGRAPH_UNDIRECTED, agent, neighbour, -1);
				igraph_delete_edges(graph, es_kill);			

			        igraph_vector_destroy(&es_add);
			        igraph_es_destroy(&es_kill);

				continue;
			}
		}
		/* If the edge is a personal one but can rewire, it will try to do with a virtual link */
		else if(*type_edge == *personal_rew_type)
		{
			// Choose a random agent which is a virtual neighbour
			neighbour_aux = virtual_neighbour(graph, agent, rand());

			if(neighbour_aux != -1)
			{
				// Calculate the homophily between the new agent and the first one 
				hom_aux = homophily(agents[agent], agents[neighbour_aux]);
			}	
			else
				hom_aux = 0.00;
			
			// If the new homophily is larger than the old one, do a rewiring 
			if(hom_aux > hom)
			{
			        igraph_vector_t es_add;
			        igraph_vector_init(&es_add, 2);

			        igraph_es_t es_kill;

				// Delete the old edge
				igraph_es_pairs_small(&es_kill, IGRAPH_UNDIRECTED, agent, neighbour_aux, -1);
				igraph_delete_edges(graph, es_kill);			

				// Create the new edge and set this one as personal rewirible
				VECTOR(es_add)[0] = agent;
				VECTOR(es_add)[1] = neighbour_aux;
				igraph_add_edges(graph, &es_add, 0);			

				igraph_get_eid(graph, &eid, agent, neighbour_aux, 0, 0);
				igraph_cattribute_EAS_set(graph, "t", eid, "r");

				// Delete the old edge
				igraph_es_pairs_small(&es_kill, IGRAPH_UNDIRECTED, agent, neighbour, -1);
				igraph_delete_edges(graph, es_kill);			

				// Create the new edge and set this one as virtual
				VECTOR(es_add)[0] = agent;
				VECTOR(es_add)[1] = neighbour;
				igraph_add_edges(graph, &es_add, 0);			

				igraph_get_eid(graph, &eid, agent, neighbour, 0, 0);
				igraph_cattribute_EAS_set(graph, "t", eid, "v");

			        igraph_vector_destroy(&es_add);
			        igraph_es_destroy(&es_kill);

				continue;
			}
		}

 		random = ((double)rand())/RAND_MAX;
		/* If a random number is less than the homophily then imitate */
		if(random <= hom && hom != 1.00)
			imitation(agents + agent, agents + neighbour, phi, rand());	
	}
	
	return 1;
}
