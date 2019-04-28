import random
from pprint import pprint

numbers_list = [1.23, 5.123, 5.7, 5, 6, 2, 1.6, 0.7, 5.5, 8.1, 4.9, 1232, 1000, 123123123,
            34234234.52, 5456778.13, 76.234,677, 763.5]


def matrix_mul(m1, m2):
    r = [[0] * len(m2[0]) for _ in range(len(m1))]
    for i in range(len(m1)):
        for j in range(len(m2[0])):
            for k in range(len(m1[0])):
                r[i][j] += m1[i][k] * m2[k][j]

    return r


def gen_matrix(n):
    ll = []
    for _ in range(n):
        ll.append([random.choice(numbers_list) for i in range(n)])
    return ll


if __name__ == "__main__":
    l = 5
    matrix_mul(gen_matrix(l), gen_matrix(l))
