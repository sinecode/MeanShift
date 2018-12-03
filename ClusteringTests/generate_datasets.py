import os

import sklearn.datasets as datasets
import pandas as pd


TOTAL_POINTS = 10000
DATASETS_DIR = './datasets'


def generate_dataset(n_features, centers, file_name):
    data, __ = datasets.make_blobs(
        TOTAL_POINTS, n_features, centers, cluster_std=1, shuffle=True
    )
    pd.DataFrame(data).to_csv(
        os.path.join(DATASETS_DIR, file_name), header=False, index=False
    )


def main():
    # two dimensional datasets
    for c in range(1, 6):
        generate_dataset(n_features=2, centers=c, file_name=f'data{c}.csv')
    # three dimensional datasets
    for c in range(1, 6):
        generate_dataset(n_features=3, centers=c, file_name=f'data{c + 5}.csv')


if __name__ == '__main__':
    main()
