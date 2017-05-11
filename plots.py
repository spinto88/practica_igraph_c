from network import Axelrod_system as Axl
import zipfile
import os

q = 20 
vl = 0 
conf = 0
	 
fname = 'Graph_q' + str(q) + '_vl' \
        + str(vl) + '.graphml'
"""
zip_ref = zipfile.ZipFile('Graphs_conf' + \
                  str(conf) + '.zip', 'r')

zip_ref.extract(fname)
zip_ref.close()
"""

axl = Axl(fname)

print conf, q, vl,
#print axl.links_between_regions(),
print axl.state_multiplicity()

axl.plot('Plot_q' + str(q) + '_vl' + str(vl) + '.png', 0)
#axl.plot('Plot_q' + str(q) + '_vl' + str(vl) + '_b.png', 2)
#os.remove(fname)

