import ctypes as C
import random as rand
from axl_agent import *
from zipfile import ZipFile
import os
import numpy as np

def dynamics(n = 100, f = 11, q = 20, virtual_links = 0, phi = 0.00, zealots_fraction = 0.01, steps = 10000):

    libc = C.CDLL('src/libc.so')

    libc.graph_and_dynamics.argtypes = [C.POINTER(Axl_agent), \
                          C.c_int, C.c_int, C.c_double, C.c_int, C.c_int]
    libc.graph_and_dynamics.restype = C.c_int

    dim = int(n**0.5)

    m = dim * dim
    agents = (Axl_agent * m)()

    zealots = np.random.choice(range(n), int(zealots_fraction * n))

    for i in range(m):
        if i in zealots:
            agents[i] = Axl_agent(f, q, zealot = 1)
        else:
            agents[i] = Axl_agent(f, q, zealot = 0)

    libc.graph_and_dynamics(agents, dim, virtual_links, phi,\
                         steps, rand.randint(0, 10000))
