import ctypes as C
import random as rand
from axl_agent import *
from zipfile import ZipFile
import os

libc = C.CDLL('src/libc.so')
libc.graph_and_dynamics.argtypes = [C.POINTER(Axl_agent), C.c_int, C.c_int]
libc.graph_and_dynamics.restype = C.c_int

dim_1 = 16
dim_2 = dim_1 * 2 + 2
m = dim_1 * dim_2

agents = (Axl_agent * m)()

for conf in range(10):

    for q in range(10, 401, 20):

        for virtual_links in [100, 500, 1000, 1500, 2000, 2500]:

            for i in range(m):
                agents[i] = Axl_agent(10, q)

            libc.graph_and_dynamics(agents, virtual_links, rand.randint(0, 10000))
            
            myzip = ZipFile('Graphs2_conf' + str(conf) + '.zip', 'a')
            myzip.write('Graph2_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')
            myzip.close()

            os.remove('Graph2_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')
            
