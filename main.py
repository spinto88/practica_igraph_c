import random as rand
from zipfile import ZipFile
import os
from dynamics import dynamics

N = 400
F = 11

virtual_links = N * 4

steps = 10000
phi = 0.00

rand.seed(123457)

for conf in range(100):

    for q in [100]: #range(10, 500, 50):

        dynamics(N, F, q, virtual_links, phi, steps)

    exit()
    """           
    myzip = ZipFile('Graphs_prueba' + str(conf) + '.zip', 'a')
    myzip.write('Graph_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')
    myzip.close()
    os.remove('Graph_q' + str(q) + '_vl' + str(virtual_links) + '.graphml')         """
