
#ifndef FRAGMENT_IDENTIFIER_H
#define FRAGMENT_IDENTIFIER_H

#include <stdlib.h>
#include "swap.h"
#include "axelrod.h"
#include "is_same_state.h"
#include "is_neighbor.h"
#include <igraph.h>
#include <stdio.h>
#include <unistd.h>

void fragment_identifier(int, int, int, int *, axl_agent *, int);

#endif
