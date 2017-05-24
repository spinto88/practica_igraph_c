from network import Axelrod_system as Axl

F = 11
Q = 100
N = 400
vl = N * 4

fname = 'Graph_q' + str(Q) + '_vl' + str(vl) + '.graphml'

axl = Axl(fname, F, Q)
#print axl.fragment_identifier()
#print axl.agents[0].feat[:F]
#print axl.agents[1].feat[:F]

print len([1 for i in range(N) if axl.agents[i].feat[0] == 0])

for i in range(N):
    if axl.agents[i].feat[0] == 0:
        print axl.agents[i].feat[:F]

#axl.plot()
