from matrix import Matrix
from python_matrix import gen_matrix, matrix_mul
from pprint import pprint
from time import time


if __name__ == "__main__":    
    l = 500
    # python finish at 31.077462911605835
    # cpp finish at 0.011924982070922852
    
    m1 = gen_matrix(l)
    m2 = gen_matrix(l)

    # pprint(m1)
    # pprint(m2)
    start = time()
    matrix_mul(m1,m2)
    print('python finish at {}'.format(time() - start))

    start = time()
    cpp_m1 = Matrix(m1)
    cpp_m2 = Matrix(m2)
    print('cpp finish at {}'.format(time() - start))

    # (cpp_m1 * cpp_m2).print()

    # m = Matrix([[1, 2, 33, 4],
                # [1, 2, 3, 4]])
    # m.print()
    # print(len(m))

    # print(40 in m)
    # a = m - 3
    # a.print()

    # t = m.transpose()
    # t.print()

    # b = a / 5
    # b.print()

    # print(m[(1, 4)])

    # m = Matrix([[1, 2], [1, 2, 3]])
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
