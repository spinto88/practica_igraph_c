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

        agents_per_label = np.bincount(labels, minlength = len(labels))

	# At the end, it returns an array with de number of ocurrences
	# of clusters with size equal to its index
        clusters_by_size = np.bincount(agents_per_label, minlength = len(labels) + 1)[1:]

	return clusters_by_size
        
    def plot(self, fname = '', without_mayority_vl = 0):
 
        states = [tuple(list(self.agents[i].feat[:10])) \
		  for i in range(self.n)]

        states = sorted(list(set(states)), \
                 key = lambda x: states.count(x), reverse = True) 

        positions = [(vs['pos_x'], vs['pos_y']) for vs in self.graph.vs]
        layout = igraph.Layout(positions)

        random.seed(123457)

        color_dict = {}
        for i in range(len(states)):
            color_dict[i] = [random.random() for j in range(3)]

        color_dict[0] = [1.00, 1.00, 1.00]

        for i in range(len(states)):
            for j in range(self.n):
                if list(self.agents[j].feat[:10]) == list(states[i]):
                    self.graph.vs[j]['color'] = color_dict[i]

        vertex_colors = [self.graph.vs[i]['color'] \
                        for i in range(len(self.graph.vs))]

        edge_width_dict = {'r': 3.00, 'p': 1.00, 'v':0.00}

        igraph.plot(self.graph, layout = layout, \
                    vertex_colors = vertex_colors, \
		    vertex_size = 2.00, \
                    edge_width = [edge_width_dict[es['t']] \
                    for es in self.graph.es])
  
        """ 
        if fname != '' and without_mayority_vl == 0: 
             igraph.plot(self.graph, layout = layout, \
                    vertex_colors = vertex_colors, \
		    vertex_size = 10.00, \
                    edge_width = [3.00 if es['t'] == 'v' else 1.00 \
                    for es in self.graph.es],
                    target = fname)

        if fname != '' and without_mayority_vl == 1:

             edge_width = []
             for es in self.graph.es:
                 if es['t'] == 'v' and self.agents[es.target].feat[:10] != list(states[0]) and self.agents[es.source].feat[:10] != list(states[0]):
                     edge_width.append(3.00)
                 elif es['t'] == 'p':
                     edge_width.append(1.00)
                 else:
                     edge_width.append(0.00)

             igraph.plot(self.graph, layout = layout, \
                    vertex_colors = vertex_colors, \
		    vertex_size = 10.00, \
                    edge_width = edge_width, \
                    target = fname)

        if fname != '' and without_mayority_vl == 2:

             edge_width = []
             for es in self.graph.es:
                 if self.agents[es.target].feat[:10] != list(states[1]) or self.agents[es.source].feat[:10] != list(states[1]):
                     edge_width.append(0.00)
                 else:
                     edge_width.append(3.00)

             vertex_size = []
             for i in range(len(self.graph.vs)):
                 if self.agents[i].feat[:10] != list(states[1]):
                     vertex_size.append(0.00)
                 else:
                     vertex_size.append(10.00)

             igraph.plot(self.graph, layout = layout, \
                    vertex_colors = vertex_colors, \
		    vertex_size = vertex_size, \
                    edge_width = edge_width, \
                    target = fname)
        """
