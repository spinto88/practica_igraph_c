from network import Axelrod_system as Axl
import numpy as np

F = 11
Q = 20
N = 400
vl = N * 4

fname = 'Graph_q' + str(Q) + '_vl' + str(vl) + '.graphml'

axl = Axl(fname, F, Q)

print axl.state_multiplicity()
print len([1 for i in range(N) if axl.agents[i].feat[0] == 0])

zealots = [i for i in range(N) if axl.agents[i].zealot == 1]

print np.mean([axl.graph.vs[i].degree() for i in range(N)])
print np.mean([axl.graph.vs[i].degree() for i in zealots])

print zealots
for i in range(N):
    if axl.agents[i].feat[0] == 0:
        print i, axl.agents[i].feat[:F]



axl.plot()
