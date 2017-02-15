import igraph
import random
from axl_agent import Axl_agent
import ctypes as C
import os

libc = C.CDLL(os.getcwd() + '/src/libc.so')

class Axelrod_system(object):

    def __init__(self, file_graphml):

	self.fname = file_graphml

        self.graph = igraph.Graph.Read_GraphML(file(file_graphml, 'r'))

	self.n = len(self.graph.vs)
  	
	self.agents = (Axl_agent * self.n)()

	for i in range(self.n):
    
  	    state = [int(self.graph.vs[i]['feat' + str(f)]) \
                                      for f in range(10)]
        
            self.agents[i] = Axl_agent(len(state), 0, state = state)


    def links_between_regions(self):
        
	for i in range(self.n):
            if self.graph.vs[i]['pos_x'] < 16:
                self.graph.vs[i]['region'] = 'I'
            else:
                self.graph.vs[i]['region'] = 'II'

        ans = 0

        for es in self.graph.es:
            if self.graph.vs[es.source]['region'] != \
               self.graph.vs[es.target]['region']:
                ans += 1

        return ans


    def state_multiplicity(self):            

        states = set([tuple(self.agents[i].feat[:10]) for i in range(self.n)])
        
	return len(states)


    def fragment_identifier(self, type_cluster = 0):

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

        def is_same_state(node1, node2):
        
            if self.agents[node1].homophily(self.agents[node2]) == 1.00:
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

        return len(set(labels))

        
    def plot(self):

        random.seed(123457)
 
        states = [tuple(list(self.agents[i].feat[:10])) \
		  for i in range(self.n)]

        states = list(set(states))

        positions = [(vs['pos_x'], vs['pos_y']) for vs in self.graph.vs]
        layout = igraph.Layout(positions)

        color_dict = {}
        for i in range(len(states)):
            color_dict[i] = [random.random() for j in range(3)]

        for i in range(len(states)):
            for j in range(self.n):
                if list(self.agents[j].feat[:10]) == list(states[i]):
                    self.graph.vs[j]['color'] = color_dict[i]

        vertex_colors = [self.graph.vs[i]['color'] \
                        for i in range(len(self.graph.vs))]

        igraph.plot(self.graph, layout = layout, \
                    vertex_colors = vertex_colors, \
		    vertex_size = 10.00, \
                    edge_width = [3.00 if es['t'] == 'v' else 1.00 \
                    for es in self.graph.es])
    

