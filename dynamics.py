import ctypes as C
import random as rand
from axl_agent import *
from zipfile import ZipFile
import os

def dynamics(n = 100, f = 11, q = 20, virtual_links = 0, phi = 0.00, steps = 10000):

    libc = C.CDLL('src/libc.so')

    libc.graph_and_dynamics.argtypes = [C.POINTER(Axl_agent), \
                          C.c_int, C.c_int, C.c_double, C.c_int, C.c_int]
    libc.graph_and_dynamics.restype = C.c_int

    dim = int(n**0.5)

    m = dim * dim
    agents = (Axl_agent * m)()

    for i in range(m):
        agents[i] = Axl_agent(f, q)

    libc.graph_and_dynamics(agents, dim, virtual_links, phi,\
                         steps, rand.randint(0, 10000))
