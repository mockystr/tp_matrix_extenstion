cdef class Foo(object):
    cdef public:
        int a
    def __cinit__(self, int a):
        self.a = a

    def __add__(self, Foo another):
        cdef Foo my_self = Foo(self.a + another.a)
        return my_self

cdef Foo a
cdef Foo b
a = Foo(5)
b = Foo(6)
cdef Foo c = a + b
print(c.a)