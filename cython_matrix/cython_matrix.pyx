import random
import time
import numpy as np

cdef list numbers_list = [1.23, 5.123, 5.7, 5, 6, 2, 1.6, 0.7, 5.5, 8.1, 4.9, 
                        1232, 1000, 123123123, 34234234.52, 5456778.13, 76.234,677, 763.5]


cpdef double[:, :] matrix_mul(list m1, list m2):
    cdef int _=0
    cdef int i=0, j=0, k=0
    cdef double[:, :] r = np.array([[0] * len(m2[0]) for _ in range(len(m1))], dtype=float)

    for i in range(len(m1)):
        for j in range(len(m2[0])):
            for k in range(len(m1[0])):
                r[i, j] += m1[i][k] * m2[k][j]
    return r


cpdef list gen_matrix(int n):
    cdef int _, i=0
    cdef list ll = []
    for _ in range(n):
        ll.append([random.choice(numbers_list) for i in range(n)])
    return ll

cpdef int make_tests():
    cdef int l = 500
    cdef list m1 = gen_matrix(l)
    cdef list m2 = gen_matrix(l)

    t = time.time()
    matrix_mul(m1,m2)
    print('time finish {}'.format(time.time() - t))
