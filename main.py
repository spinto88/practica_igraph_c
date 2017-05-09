import ctypes as C
import random as rand
from axl_agent import *
from zipfile import ZipFile
import os

libc = C.CDLL('src/libc.so')
libc.graph_and_dynamics.argtypes = [C.POINTER(Axl_agent), C.c_int, C.c_int]
libc.graph_and_dynamics.restype = C.c_int

dim = 10
m = dim * dim
agents = (Axl_agent * m)()

F = 11
q = 100
virtual_links = 0

for i in range(m):
    agents[i] = Axl_agent(F, q)

libc.graph_and_dynamics(agents, virtual_links, rand.randint(0, 10000))

"""            
myzip = ZipFile('Graphs_prueba' + str(conf) + '.zip', 'a')
            myzip.write('Graph2_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')
            myzip.close()

            os.remove('Graph2_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')
"""         
