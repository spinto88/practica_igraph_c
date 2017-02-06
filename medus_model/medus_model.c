#include <igraph.h>

int random_neighbour(igraph_t *graph, int id, int random_seed)
{
	int i, ans;

	igraph_vector_t neighbors;
	igraph_vector_init(&neighbors,0);

	igraph_rng_seed(igraph_rng_default(), random_seed);

	igraph_neighbors(graph, &neighbors, id, IGRAPH_ALL);

	i = igraph_rng_get_integer(igraph_rng_default(), 0, igraph_vector_size(&neighbors));

	ans = VECTOR(neighbors)[i];
	igraph_vector_destroy(&neighbors);

	return ans;
}

typedef struct _state
{
	int q;
	int f;
	int *feat;
} state;

double homophily(int *vector1, int *vector2, int f)
{
	int i;
	double h12 = 0.00;

	for(i = 0; i < f; i++)
	{
		if(vector1[i] == vector2[i])
			h12 += 1.00;
	}

	return h12/f;
}
	

int imitation(state *state1, state *state2, int seed)
{
	int feat;
	
	srand(seed);

	feat = rand() % state1->f;
	while(state1->feat[feat] == state2->feat[feat])
		feat = (feat + 1) % state1->f;

	state1->feat[feat] = state2->feat[feat];		
		
	return 1;	
}

int dynamics(igraph_t *graph, state *state, int agent, int neighbour, int seed)
{
	int i, feat;
	double random, h12;

	srand(seed);

	random = (double)rand()/RAND_MAX;

	h12 = homophily(state[agent].feat, state[neighbour].feat, state[agent].f);
	if(random < h12 && h12 != 1.00)
	{
		imitation(&(state[agent]), &(state[neighbour]), seed);	
		return 1;
	}
	else
	{
		int eid;
		igraph_get_eid(graph, &eid, agent, neighbour, 0, 0);
		igraph_delete_vectices(graph, 
	return 0;	
}



int main()
{
	int i, j, step;
	int agent, neighbour;
	int n;
	int q = 20;
	int f = 10;
	
	state *states;

	igraph_t graph;
	igraph_vector_t dim;

	igraph_rng_seed(igraph_rng_default(), 123457);

	igraph_vector_init(&dim, 2);
	VECTOR(dim)[0] = 32;
	VECTOR(dim)[1] = 32;

	igraph_lattice(&graph, &dim, 0, 0, 0, 1);

	n = graph.n;

	states = (state *)malloc(sizeof(state)*n);

	for(i=0; i<n; i++)
	{
		states[i].q = q;
		states[i].f = f;
		states[i].feat = (int *)malloc(sizeof(int) * f); 

		for(j = 0; j < f; j++)
			states[i].feat[j] = rand() % q;
	}

	for(step = 0; step < 10000; step++)
	{
		for(i=0; i<n; i++)
		{
			agent = rand() % graph.n;
			neighbour = random_neighbour(&graph, agent, rand());

			dynamics(&graph, states, agent, neighbour, rand());
		}
	}

	
	
	free(states);
	igraph_destroy(&graph);
	igraph_vector_destroy(&dim);

	return 1;
}
