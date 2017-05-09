#include "init_agents.h"

int init_agents(axl_agent *agents, int n, int f, int q, int seed)
{
	int i, j;

	srand(seed);

	for(i=0; i<n; i++)
	{
		agents[i].f = f;		
		agents[i].q = q;		
		agents[i].feat = (int *)malloc(sizeof(int) * f);

		for(j=0; j<f; j++)
		{
			agents[i].feat[j] = rand() % q;
			// First feature
			if(j==0)
			{
				agents[i].feat[j] = rand() % 2;
			}
		}
	}
	return 1;
}

	
