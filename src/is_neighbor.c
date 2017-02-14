
#include "is_neighbor.h"

int is_neighbor(igraph_t *graph, int node1, int node2, int type)
{
/**
It sees if the index of the agent 2 is in the list of neighbors of agent 1.
*/

	int eid;
        char *type_edge;
        char virtual_type[1] = "v";

        igraph_get_eid(graph, &eid, node1, node2, 0, 0);

        if(eid == -1) return 0;
	else
	{
                /* Type of the edge */
                type_edge = (char *)igraph_cattribute_EAS(graph, "t", eid);

                /* Is the edge a virtual one? */
                if(*type_edge == *virtual_type)
		{
			if(type == 0) return 0;
			else return 1;
		}
	}

	return 0;
}

