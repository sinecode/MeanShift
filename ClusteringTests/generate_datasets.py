import os

import sklearn.datasets as datasets
import pandas as pd


DATASETS_DIR = './datasets'


def generate_dataset(points, n_features, centers, std, file_name):
    data, __ = datasets.make_blobs(
        points, n_features, centers, cluster_std=std, shuffle=True,
        random_state=1000
    )
    pd.DataFrame(data).to_csv(
        os.path.join(DATASETS_DIR, file_name), header=False, index=False
    )


def main():
    # two dimensional datasets
    for c in range(1, 6):
        generate_dataset(
            points=10000, n_features=2, centers=c, std=1,
            file_name='data{}.csv'.format(c)
        )
    # three dimensional datasets
    for c in range(1, 6):
        generate_dataset(
            points=10000, n_features=3, centers=c, std=1,
            file_name='data{}.csv'.format(c + 5)
        )


if __name__ == '__main__':
    main()
