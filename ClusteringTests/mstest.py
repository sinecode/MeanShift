import os
import sys
import subprocess
from time import time

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def main():
    # go to the directory where this script is located
    os.chdir(os.path.dirname(sys.argv[0]))

    begin_time = time();
    out = subprocess.check_call(
        '../MeanShift/cmake-build-release/meanshift datasets/data6.csv 200',
        shell=True
    )
    elapsed_time = time() - begin_time;
    print(f'Elapsed time: {elapsed_time} s')
    data = np.genfromtxt('out.csv', delimiter=',')
    print(f'Number of points: {len(data)}')
    print(f'Number of dimensions: {len(data[0]) - 1}')
    num_clusters = int(np.max(data[:,-1] + 1))
    print(f'Number of clusters: {num_clusters}')
    clusters = np.ndarray(shape=num_clusters, dtype=np.ndarray)
    for i in range(0, num_clusters):
        clusters[i] = np.float32(
            [point[:-1] for point in data if point[-1] == i]
        )
    fig = plt.figure()
    if len(clusters) == 3:
        for cluster in clusters:
            plt.scatter(cluster[:,0], cluster[:,1], s=3)
    else:
        ax = Axes3D(fig)
        for cluster in clusters:
            ax.scatter(cluster[:,0], cluster[:,1], cluster[:,2], s=3)
    plt.show()
    os.remove('out.csv')



if __name__ == '__main__':
    main()
