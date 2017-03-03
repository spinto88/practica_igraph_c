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

#define AXELROD_F 10
#define AXELROD_Q 50

#define DIM_1 16
#define DIM_2 (2 * DIM_1 + 2)

#define VIRTUAL_LINKS 0

#define SEED 123457

#define STEPS 50000

int graph_and_dynamics(axl_agent *, int, int);

#endif