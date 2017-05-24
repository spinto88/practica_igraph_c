import igraph
import random
from axl_agent import Axl_agent
import ctypes as C
import os
import numpy as np

libc = C.CDLL(os.getcwd() + '/src/libc.so')

class Axelrod_system(object):

    def __init__(self, file_graphml, f, q):

	self.fname = file_graphml

        self.graph = igraph.Graph.Read_GraphML(file(file_graphml, 'r'))

	self.n = len(self.graph.vs)
        self.f = f
        self.q = q
  	
	self.agents = (Axl_agent * self.n)()

	for i in range(self.n):
    
  	    state = [int(self.graph.vs[i]['feat' + str(feat)]) \
                                      for feat in range(self.f)]

  	    zealot = int(self.graph.vs[i]['zealot'])        
            self.agents[i] = Axl_agent(len(state), q, state = state, zealot = zealot)



    def state_multiplicity(self):            

        states = set([tuple(self.agents[i].feat[1:self.f]) for i in range(self.n)])
        
	return len(states)


    def fragment_identifier(self, type_cluster = 'all', type_state = 'all'):

        def is_neighbour(node1, node2, type_clust):

            if type_clust != 0:
                if node1 in self.graph.neighbors(node2):
                    return 1
                else:
                    return 0
            else:
		if node1 in self.graph.neighbors(node2):
                    if self.graph.es[self.graph.get_eid(node1, node2)]['t'] != 'v':
                        return 1
                    else:
                        return 0

        def is_same_state(node1, node2, type_st):

            if type_st == 'all':
                if self.agents[node1].homophily(self.agents[node2]) == 1.00:
                    return 1
                else:
                    return 0

            elif type_st == 'first':
                if self.agents[node1].feat[0] == self.agents[node2].feat[0]:
                    return 1
                else:
                    return 0

	labels = [i for i in range(self.n)]
	ordering = [i for i in range(self.n)]

	j = 0
	for i in range(self.n):

  	    node1 = ordering[i]

  	    if j == i: j += 1

	    k = j;
	    while(k < self.n):

	        node2 = ordering[k]
                if is_neighbour(node1, node2, type_cluster) == 1 \
                   and is_same_state(node1, node2) == 1:
                    labels[node2] = labels[node1]
                    ordering[k], ordering[j] = ordering[j], ordering[k]
                    j += 1

                k += 1

        agents_per_label = np.bincount(labels, minlength = len(labels))

        non_vaccinated = deepcopy(agents_per_label)
        for i in range(len(non_vaccinated)):
            if self.agents[i].feat[0] != 0:
                non_vaccinated[i] = 0

        # At the end, it returns an array with de number of ocurrences
        # of clusters with size equal to its index
        clusters_by_size = np.bincount(agents_per_label, minlength = len(labels) + 1)[1:]
        clusters_of_non_vaccinated_by_size = np.bincount(non_vaccinated, \
                                        minlength = len(labels) + 1)[1:]

        return clusters_by_size, clusters_of_non_vaccinated_by_size, labels
        
    def plot(self):
 
        states = [self.agents[i].feat[0] for i in range(self.n)]

        color_dict = {0: 'orange', 1: 'blue'}
        size_dict = {0: 8, 1: 2}

        positions = [(vs['pos_x'], vs['pos_y']) for vs in self.graph.vs]
        layout = igraph.Layout(positions)

        igraph.plot(self.graph, layout = layout, \
                    vertex_color = [color_dict[self.agents[i].feat[0]] \
                                     if self.agents[i].zealot != 1 else 'red' \
                                     for i in range(self.n)],
                    vertex_size = [size_dict[self.agents[i].feat[0]] \
                                     for i in range(self.n)],
                    edge_width = [2.00 if es['t'] != 'v' and \
                             self.agents[es.target].feat[0] == 0 and \
                             self.agents[es.source].feat[0] == 0
                             else 0.00 for es in self.graph.es])


