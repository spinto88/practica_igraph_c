from network import Axelrod_system as Axl
import zipfile
import os


for q in range(10, 201, 10):

    for vl in [10, 50, 100, 200, 500, 1000]:

        for conf in range(1):

            fname = 'Graph_q' + str(q) + '_vl' \
                     + str(vl) + '.graphml'

            zip_ref = zipfile.ZipFile('Graphs_conf' + \
                               str(conf) + '.zip', 'r')

            zip_ref.extract(fname)
            zip_ref.close()

            axl = Axl(fname)

            print q, vl,

            print axl.links_between_regions(),
            print axl.state_multiplicity()

            if q == 10 and vl == 10:
#                axl.plot()
		print axl.fragment_identifier(q, vl)

            os.remove(fname)
	 
