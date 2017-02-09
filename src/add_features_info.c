#include "add_features_info.h"

void add_features_info(igraph_t *graph, axl_agent *agents)
{
	int i, j;
	char feature[16];

        for(i = 0; i < graph->n; i++)
        {
		for(j = 0; j < agents->f; j++)
		{
			sprintf(feature, "feat%d", j);
	                igraph_cattribute_VAN_set(graph, feature, i, agents[i].feat[j]);
		}
        }

	return;
}
