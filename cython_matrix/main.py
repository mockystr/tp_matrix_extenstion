from cython_matrix import matrix_mul, gen_matrix
from time import time

if __name__ == "__main__":
    l = 500
    m1, m2 = gen_matrix(l), gen_matrix(l)
    start = time()
    matrix_mul(m1,m2)
    print(time() - start)