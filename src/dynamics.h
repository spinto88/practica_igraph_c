#ifndef DYNAMICS_H
#define DYNAMICS_H

#include <stdlib.h>
#include <igraph.h>
#include "homophily.h"
#include "agent_not_in_neighbors.h"
#include "random_neighbour.h"
#include "axelrod.h"
#include "imitation.h"

int dynamics(igraph_t *, axl_agent *, double, int);

#endif
