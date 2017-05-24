#include "imitation.h"	

int imitation(axl_agent *agent1, axl_agent *agent2, double phi, int seed)
{
	int f = agent1->f;
	int feat;	

	srand(seed);

	feat = rand() % f;
	while(agent1->feat[feat] == agent2->feat[feat])
		feat = rand() % f;

	if(agent1->zealot == 1 && feat == 0)
		return 0;

        /*
	else if(agent1->zealot != 1 && feat == 0)
	{
		if(agent2->feat[feat] == 0)
		{
			if((double)rand()/RAND_MAX < (1.00 - phi))
			{
				agent1->feat[feat] = agent2->feat[feat];		
				return 1;
			}
		}
		else
		{
			agent1->feat[feat] = agent2->feat[feat];		
			return 1;
		}
	}
        */
	else
	{
		agent1->feat[feat] = agent2->feat[feat];		
		return 1;	
	}

	return 0;
}
