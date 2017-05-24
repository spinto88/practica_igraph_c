from network import Axelrod_system as Axl

F = 11
Q = 30
N = 2500
vl = N * 4

fname = 'Graph_q' + str(Q) + '_vl' + str(vl) + '.graphml'

axl = Axl(fname, F, Q)
axl.plot()
