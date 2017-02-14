#include "is_same_state.h"

int is_same_state(axl_agent agent1, axl_agent agent2)
{
	/* Criterion of same state */

	if(homophily(agent1, agent2) == 1.00) return 1;
	else return 0;
}
