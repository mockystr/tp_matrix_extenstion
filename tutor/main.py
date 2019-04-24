import myModule
import time

def fib(n):
    prev, cur = 0, 1
    for _ in range(n-1):
        prev, cur = cur, prev + cur
        # temp = cur
        # cur += prev
        # prev = temp
    return cur
    # if n<2: return n
    # else: return fib(n-1) + fib(n-2)

start_py = time.time()
fib(30000)
finish_py = time.time() - start_py

start_c = time.time()
myModule.fib(30000)
finish_c = time.time() - start_c

print(finish_py/finish_c)
# 1271.9130434782608
