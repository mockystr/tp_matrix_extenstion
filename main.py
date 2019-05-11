from matrix import Matrix
from python_matrix import gen_matrix, matrix_mul
import numpy as np
from pprint import pprint
from time import time

if __name__ == "__main__":
    # l = 500
    # --------------------------------------
    # python finish at                      31.077462911605835
    # cython finish at                      8.099114179611206
    # python extension finish at            0.21802687644958496
    # numpy finish at                       0.010122060775756836
    # --------------------------------------

    l = 500
    m1 = gen_matrix(l)
    m2 = gen_matrix(l)

    # pprint(m1)
    # pprint(m2)
    # start = time()
    # matrix_mul(m1,m2)
    # print('python finish at {}'.format(time() - start))

    start = time()
    m1_arr = np.array(m1)
    m2_arr = np.array(m2)
    np.matmul(m1_arr, m2_arr)
    print('numpy finish at {}'.format(time() - start))

    start = time()
    cpp_m1 = Matrix(m1)
    cpp_m2 = Matrix(m2)
    cpp_m1 * cpp_m2
    print('cpp finish at {}'.format(time() - start))


    # proverochki

    # m = Matrix([[1.1, 2, 33, 4.45],
    #             [1.56, 2, 3.123, 4.112]])
    # m.print()
    # print(len(m))

    # print(4.49 in m)
    # a = m + m
    # a.print()

    # t = m.transpose()
    # t.print()

    # b = m / 5.3
    # b.print()

    # print(m[(1, 4)])
    # TypeError: Matrix __getitem__ parameter out of range

    # m = Matrix([[1, 2],
    #             [1, 2, 3]])
    # TypeError: matrix must have fixed els count on every row

    # a = Matrix([[1, 2, 3, 4],
    #             [1, 2, 3, 4],
    #             [1, 2, 3, 4]])
    # b = Matrix([[1, 2],
    #             [1, 2],
    #             [1, 2],
    #             [1, 2]])
    # c = a * b
    # c.print()
    # 10 20
    # 10 20
    # 10 20
