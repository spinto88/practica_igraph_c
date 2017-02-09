import ctypes as C
import random as rand
from axl_agent import *
from zipfile import ZipFile
import os

libc = C.CDLL('src/libc.so')
libc.graph_and_dynamics.argtypes = [C.POINTER(Axl_agent), C.c_int, C.c_int, C.c_int]
libc.graph_and_dynamics.restype = C.c_int

n = 33
m = n * (n-1)

agents = (Axl_agent * m)()

for conf in range(100):

    for q in range(10, 201, 10):

        for virtual_links in [10, 50, 100, 200, 500, 1000]:

            for i in range(m):
                agents[i] = Axl_agent(10, q)

            libc.graph_and_dynamics(agents, n, virtual_links, rand.randint(0, 10000))

            myzip = ZipFile('Graphs_conf' + str(conf) + '.zip', 'a')
            myzip.write('Graph_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')
            myzip.close()

            os.remove('Graph_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')
