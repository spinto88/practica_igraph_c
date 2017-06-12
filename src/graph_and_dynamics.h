#ifndef GRAPH_AND_DYNAMICS_H
#define GRAPH_AND_DYNAMICS_H

#include <stdlib.h>
#include <stdio.h>
#include <igraph.h>

#include "axelrod.h"
#include "active_links.h"
#include "init_network.h"
#include "init_agents.h"
#include "dynamics.h"
#include "add_features_info.h"

//#define AXELROD_F 11
//#define AXELROD_Q 20

//#define DIM 10

//#define VIRTUAL_LINKS 0

//#define SEED 123457

//#define STEPS 10000

int graph_and_dynamics(axl_agent *, int, int, int, double, int, int);

#endif
