import igraph
import random
from axl_agent import Axl_agent
import ctypes as C
import os

libc = C.CDLL(os.getcwd() + '/src/libc.so')
libc_actual = C.CDLL(os.getcwd() + '/libc_actual.so')


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


    def fragment_identifier(self, q, vl, type_cluster = 0):

        libc_actual.fragment_identifier.argtypes = [C.c_int, C.c_int, C.c_int, \
			C.POINTER(C.c_int), C.POINTER(Axl_agent), C.c_int]

	labels_c = (C.c_int * self.n)()

	libc_actual.fragment_identifier(q, vl, type_cluster, \
                                labels_c, self.agents, self.n)

        labels = [labels_c[i] for i in range(self.n)]

        return labels

	

        
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
    

