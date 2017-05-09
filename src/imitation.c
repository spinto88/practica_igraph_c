#include "imitation.h"	

int imitation(axl_agent *agent1, axl_agent *agent2, int seed)
{
	int f = agent1->f;
	int feat;	

	srand(seed);

	feat = rand() % f;
	while(agent1->feat[feat] == agent2->feat[feat])
		feat = (feat + 1) % f;

	if(agent1->zealot == 1 && feat == 0)
		return 0;
	else
	{
		agent1->feat[feat] = agent2->feat[feat];		
		return 1;	
	}
}
