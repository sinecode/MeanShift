import os
import sys
import subprocess

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


MEAN_SHIFT_EXECUTABLE_PATH = '../MeanShift/cmake-build-release/meanshift'


def main():
    out = subprocess.check_call(
        f'{MEAN_SHIFT_EXECUTABLE_PATH} {sys.argv[1]} {sys.argv[2]}',
        shell=True
    )
    data = np.genfromtxt('out.csv', delimiter=',')
    num_clusters = int(np.max(data[:,-1] + 1))
    clusters = np.ndarray(shape=num_clusters, dtype=np.ndarray)
    for i in range(0, num_clusters):
        clusters[i] = np.float32(
            [point[:-1] for point in data if point[-1] == i]
        )
    fig = plt.figure()
    if len(clusters[0][0]) == 2:
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
