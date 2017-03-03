from network import Axelrod_system as Axl
import zipfile
import os
import numpy as np
import matplotlib.pyplot as plt

plt.figure(1)
plt.axes([0.15, 0.17, 0.70, 0.72])

for q in [10, 50, 100, 200]:

#for vl in [10, 50, 100, 200, 500, 1000]: #range(100, 1001, 100): #[50, 200, 500]:

    lq = []
    std_lq = []
    mul = []
    std_mul = []

    for vl in [10, 50, 100, 200, 500, 1000]:

#    for q in [10, 50, 100, 200]: #range(10, 201, 10):

        links_between = []
        multiplicity = []

        for conf in range(100):

            fname = 'Graph_q' + str(q) + '_vl' \
                     + str(vl) + '.graphml'

            zip_ref = zipfile.ZipFile('Graphs_conf' + \
                               str(conf) + '.zip', 'r')

            zip_ref.extract(fname)
            zip_ref.close()

            axl = Axl(fname)

            links_between.append(axl.links_between_regions())
            multiplicity.append(axl.state_multiplicity())

            os.remove(fname)

        lq.append(np.mean(links_between))
        std_lq.append(np.std(links_between))
        mul.append(np.mean(multiplicity))
        std_mul.append(np.std(multiplicity))
	 
#    plt.errorbar(range(10, 201, 10), lq, std_lq, fmt = '.-', markersize = 20, \
#                 linewidth = 0.2, label = 'Vr = ' + str(vl))
#    plt.errorbar(range(10, 201, 10), mul, std_mul, fmt = '.-', markersize = 20, \
#                 linewidth = 0.2, label = 'Vr = ' + str(vl))
#    plt.errorbar([10, 50, 100, 200, 500, 1000], mul, std_mul, fmt = '.-', markersize = 20, \
#                 linewidth = 0.2, label = 'Q = ' + str(q))
    plt.errorbar([10, 50, 100, 200, 500, 1000], lq, std_lq, fmt = '.-', markersize = 20, \
                 linewidth = 0.2, label = 'Q = ' + str(q))

plt.grid('on')
plt.xlabel('Virtual links', size = 25)
plt.ylabel('Links between regions', size = 25)
plt.xticks(size = 20)
plt.yticks(size = 20)
plt.xlim([5, 1500])
plt.ylim([0, 1100])
plt.yscale('symlog')
plt.xscale('symlog')
plt.legend(loc = 'best')

plt.show() 

