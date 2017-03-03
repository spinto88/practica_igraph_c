from network import Axelrod_system as Axl
import zipfile
import os
import numpy as np
import matplotlib.pyplot as plt

N = 33 * 33 - 33

weights = np.zeros(N)

number_of_bins = 20 
bins = np.logspace(-0.5, 1.5, endpoint = True, num = number_of_bins,\
                  base = N)

for q in range(10, 201, 10):

    for vl in [10, 50, 100, 200, 500, 1000]:

        weights = np.zeros(N)

        for conf in range(100):

            fname = 'Graph_q' + str(q) + '_vl' \
                     + str(vl) + '.graphml'

            zip_ref = zipfile.ZipFile('Graphs_conf' + \
                               str(conf) + '.zip', 'r')

            zip_ref.extract(fname)
            zip_ref.close()

            axl = Axl(fname)

	    weights += axl.fragment_identifier(1)

            os.remove(fname)

        data_hist = np.histogram(range(1, N+1), \
                   bins = bins, \
                   weights = weights, normed = True)

        centers = [((data_hist[1][i] * data_hist[1][i+1]) ** 0.5) \
                  for i in range(len(data_hist[1])-1)]

        plt.clf()
        plt.axes([0.15, 0.17, 0.70, 0.72])
        plt.plot(centers, data_hist[0], '.-', markersize = 20, \
                 linewidth = 0.2)
        plt.grid('on')
        plt.xlabel('Size', size = 25)
        plt.ylabel('Density', size = 25)
        plt.xticks(size = 20)
        plt.yticks(size = 20)
        plt.xlim([10 ** -0.5, 10 ** 3.5])
        plt.ylim([10 ** -3.5, 10 ** 0.5])
        plt.xscale('log')
        plt.yscale('log')
        plt.text(10 ** 2.5, 1, 'Q = ' + str(q) + '\nVl = ' + \
                 str(vl), \
                 fontsize = 20, \
                 horizontalalignment = 'center', \
                 verticalalignment = 'center', \
                 bbox = dict(facecolor = 'white', linewidth = 2))

        plt.title('Personal + virtual clusters', size = 20)
        plt.savefig('Hist_v_q' + str(q) + '_vl' + str(vl) + '.eps')
