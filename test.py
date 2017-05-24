from network import Axelrod_system as Axl

F = 11
Q = 200
N = 1024
vl = N * 4

fname = 'Graph_q' + str(Q) + '_vl' + str(vl) + '.graphml'

axl = Axl(fname, F, Q)

print axl.state_multiplicity()
print len([1 for i in range(N) if axl.agents[i].feat[0] == 0])



axl.plot()
