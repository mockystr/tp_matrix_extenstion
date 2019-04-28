import random
from pprint import pprint

int_list = list(range(-50, 50, 2))

def matrix_mul(m1, m2):
    r = [[0]* len(m2[0]) for _ in range(len(m1))]
    for i in range(len(m1)):
        for j in range(len(m2[0])):
            for k in range(len(m1[0])):
                r[i][j] += m1[i][k] * m2[k][j]
                
    return r


def gen_matrix(n):
    ll = []
    for _ in range(n):
        ll.append([random.choice(int_list) for i in range(n)])
    return ll


if __name__ == "__main__":
    l = 5
    matrix_mul(gen_matrix(l), gen_matrix(l))
