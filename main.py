import random as rand
from zipfile import ZipFile
import os
from dynamics import dynamics
import numpy as np

N = 400
F = 11

virtual_links = N * 4

steps = 10000
phi = 0.04

seed = 123451

rand.seed(seed)
np.random.seed(seed)
zealots_fraction = 0.05


for conf in range(100):

    for q in [20]: #range(10, 500, 50):

        dynamics(N, F, q, virtual_links, phi, zealots_fraction, steps)

    exit()
    """           
    myzip = ZipFile('Graphs_prueba' + str(conf) + '.zip', 'a')
    myzip.write('Graph_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')
    myzip.close()
    os.remove('Graph_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')         """
