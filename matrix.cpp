#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <vector>
using namespace std;

typedef struct
{
    PyObject_HEAD
        /* Type-specific fields go here. */
        vector<vector<int>>
            m;
} matrix_t;

static void
matrix_dealloc(matrix_t *o)
{
    Py_TYPE(o)->tp_free((PyObject *)o);
}

static int
matrix_traverse(matrix_t *o, visitproc visit, void *arg)
{
    return 0;
}

static PyObject *
matrix_add(matrix_t *self, PyObject *args)
{
    long int num = 0;

    if (!PyArg_ParseTuple(args, "l", &num))
        return NULL;

    // self->s.insert(num);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
matrix_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    matrix_t *self;

    self = (matrix_t *)type->tp_alloc(type, 0);
    if (self == NULL)
    {
        return PyErr_NoMemory();
    }

    self->m = < vector<vector<int>>();
    return (PyObject *)self;
}

static int
matrix_init(matrix_t *self, PyObject *args, PyObject *kwds)
{
    PyObject *ll;   // list of lists
    PyObject *l;    // list
    PyObject litem; // list item
    Py_ssize_t ni, nj;

    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &ll))
    {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
        return NULL;
    }

    ni = PyList_Size(ll);
    for (int i = 0; i < ni; i++)
    {
        l = PyList_GetItem(ll, i);
        Py_INCREF(l);
        if (PyList_Check(l))
        {
            nj = PyList_Size(l);
            for (int j = 0; j < nj; j++)
            {
                litem = PyList_GetItem(l, j);
                Py_INCREF(litem);
                if (!PyLong_Check(&litem))
                {
                    PyErr_SetString(PyExc_TypeError, "list items must be integers.");
                    return NULL;
                }
                Py_DECREF(litem);
            }
        }
        else
        {
            PyErr_SetString(PyExc_TypeError, "list items must be integers.");
            return NULL;
        }
        Py_DECREF(l);
        // pItem = PyList_GetItem(pList, i);
        // if (!PyInt_Check(pItem))
        // {
        //     PyErr_SetString(PyExc_TypeError, "list items must be integers.");
        //     return NULL;
        // }
    }

    // self->m.clear();
    self->m.resize(ni, <vector<int>>(nj));
    return 0;
}

static PyObject *
matrix_repr(matrix_t *self)
{
    if (self->m.empty())
    {
        return PyUnicode_FromString("<Matrix(empty)>");
    }
    else
    {
        return PyUnicode_FromString("<Matrix >");
    }
    return NULL;
}

static Py_ssize_t
matrix_length(matrix_t *self)
{
    if (self->m.empty())
    {
        Py_INCREF(Py_None);
        return Py_None;
    }
    else
    {
        return Py_ssize_t(self->m.size() * self->m[0].size());
    }
}

static int
matrix_contains(matrix_t *self, PyObject *arg)
{
    if (!PyLong_Check(arg))
    {
        PyErr_SetString(PyExc_TypeError, "object must be number");
        return -1;
    }

    long int num = PyLong_AsLong(arg);
    if (count(self->m.begin(), self->m.end(), num))
        return 1;
    return 0;
}

static PySequenceMethods matrix_as_sequence = {
    (lenfunc)matrix_length,      /* sq_length */
    0,                           /* sq_concat */
    0,                           /* sq_repeat */
    0,                           /* sq_item */
    0,                           /* sq_slice */
    0,                           /* sq_ass_item */
    0,                           /* sq_ass_slice */
    (objobjproc)matrix_contains, /* sq_contains */
};

static PyMethodDef matrix_methods[] = {
    {"add", (PyCFunction)matrix_add, METH_VARARGS},
    {NULL, NULL} /* sentinel */
};

PyTypeObject matrix_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "matrix.Matrix", /* tp_name */
    sizeof(matrix_t),                               /* tp_basic_size */
    0,                                              /* tp_itemsize */
    (destructor)matrix_dealloc,                     /* tp_dealloc */
    0,                                              /* tp_print */
    0,                                              /* tp_getattr */
    0,                                              /* tp_setattr */
    0,                                              /* tp_reserved */
    (reprfunc)matrix_repr,                          /* tp_repr */
    0,                                              /* tp_as_number */
    &matrix_as_sequence,                            /* tp_as_sequence */
    0,                                              /* tp_as_mapping */
    0,                                              /* tp_hash */
    0,                                              /* tp_call */
    0,                                              /* tp_str */
    0,                                              /* tp_getattro */
    0,                                              /* tp_setattro */
    0,                                              /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,       /* tp_flags */
    0,                                              /* tp_doc */
    (traverseproc)matrix_traverse,                  /* tp_traverse */
    0,                                              /* tp_clear */
    0,                                              /* tp_richcompare */
    0,                                              /* tp_weaklistoffset */
    0,                                              /* tp_iter */
    0,                                              /* tp_iternext */
    matrix_methods,                                 /* tp_methods */
    0,                                              /* tp_members */
    0,                                              /* tp_getset */
    0,                                              /* tp_base */
    0,                                              /* tp_dict */
    0,                                              /* tp_descr_get */
    0,                                              /* tp_descr_set */
    0,                                              /* tp_dictoffset */
    (initproc)matrix_init,                          /* tp_init */
    0,                                              /* tp_alloc */
    matrix_new,                                     /* tp_new */
    0,                                              /* tp_free */
};

static struct PyModuleDef matrix_module = {
    PyModuleDef_HEAD_INIT,
    "matrix", /* name of module */
    NULL,     /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
};

PyMODINIT_FUNC
PyInit_matrix(void)
{
    PyObject *m;
    if (PyType_Ready(&matrix_Type) < 0)
        return NULL;

    m = PyModule_Create(&matrix_module);
    if (m == NULL)
        return NULL;

    Py_INCREF(&matrix_Type);
    PyModule_AddObject(m, "Matrix", (PyObject *)&matrix_Type);
    return m;
}

// matrix.cpp:51:15: error: expected expression
//     self->m = < vector<vector<int>>();
//               ^
// matrix.cpp:66:16: warning: implicit conversion of NULL constant to 'int' [-Wnull-conversion]
//         return NULL;
//         ~~~~~~ ^~~~
//                0
// matrix.cpp:79:23: error: no viable overloaded '='
//                 litem = PyList_GetItem(l, j);
//                 ~~~~~ ^ ~~~~~~~~~~~~~~~~~~~~
// /usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/include/python3.7m/object.h:106:16: note: 
//       candidate function (the implicit copy assignment operator) not viable: no known conversion from 'PyObject *'
//       (aka '_object *') to 'const _object' for 1st argument; dereference the argument with *
// typedef struct _object {
//                ^
// /usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/include/python3.7m/object.h:106:16: note: 
//       candidate function (the implicit move assignment operator) not viable: no known conversion from 'PyObject *'
//       (aka '_object *') to '_object' for 1st argument; dereference the argument with *
// typedef struct _object {
//                ^
// matrix.cpp:80:17: error: cannot cast from type 'PyObject' (aka '_object') to pointer type 'PyObject *'
//       (aka '_object *')
//                 Py_INCREF(litem);
//                 ^~~~~~~~~~~~~~~~
// /usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/include/python3.7m/object.h:796:6: note: 
//       expanded from macro 'Py_INCREF'
//     ((PyObject *)(op))->ob_refcnt++)
//      ^~~~~~~~~~~~~~~~
// matrix.cpp:84:28: warning: implicit conversion of NULL constant to 'int' [-Wnull-conversion]
//                     return NULL;
//                     ~~~~~~ ^~~~
//                            0
// matrix.cpp:86:17: error: cannot cast from type 'PyObject' (aka '_object') to pointer type 'PyObject *'
//       (aka '_object *')
//                 Py_DECREF(litem);
//                 ^~~~~~~~~~~~~~~~
// /usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/include/python3.7m/object.h:800:36: note: 
//       expanded from macro 'Py_DECREF'
//         PyObject *_py_decref_tmp = (PyObject *)(op);    \
//                                    ^~~~~~~~~~~~~~~~
// matrix.cpp:92:20: warning: implicit conversion of NULL constant to 'int' [-Wnull-conversion]
//             return NULL;
//             ~~~~~~ ^~~~
//                    0
// matrix.cpp:104:24: error: expected expression
//     self->m.resize(ni, <vector<int>>(nj));
//                        ^
// matrix.cpp:104:36: error: expected '(' for function-style cast or type construction
//     self->m.resize(ni, <vector<int>>(nj));
//                         ~~~~~~~~~~~^
// matrix.cpp:128:16: error: cannot initialize return object of type 'Py_ssize_t' (aka 'long') with an rvalue of type
//       'PyObject *' (aka '_object *')
//         return Py_None;
//                ^~~~~~~
// /usr/local/Cellar/python/3.7.3/Frameworks/Python.framework/Versions/3.7/include/python3.7m/object.h:921:17: note: 
//       expanded from macro 'Py_None'
// #define Py_None (&_Py_NoneStruct)
//                 ^~~~~~~~~~~~~~~~~
// In file included from matrix.cpp:4:
// In file included from /Library/Developer/CommandLineTools/usr/include/c++/v1/vector:270:
// In file included from /Library/Developer/CommandLineTools/usr/include/c++/v1/__bit_reference:15:
// /Library/Developer/CommandLineTools/usr/include/c++/v1/algorithm:1250:22: error: invalid operands to binary
//       expression ('std::__1::vector<int, std::__1::allocator<int> >' and 'const long')
//         if (*__first == __value_)
//             ~~~~~~~~ ^  ~~~~~~~~
// matrix.cpp:146:9: note: in instantiation of function template specialization
//       'std::__1::count<std::__1::__wrap_iter<std::__1::vector<int, std::__1::allocator<int> > *>, long>' requested
//       here
//     if (count(self->m.begin(), self->m.end(), num))
//         ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/utility:578:1: note: candidate template ignored: could not
//       match 'pair' against 'vector'
// operator==(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/iterator:694:1: note: candidate template ignored: could not
//       match 'reverse_iterator' against 'vector'
// operator==(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/iterator:923:1: note: candidate template ignored: could not
//       match 'istream_iterator' against 'vector'
// operator==(const istream_iterator<_Tp, _CharT, _Traits, _Distance>& __x,
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/iterator:1027:6: note: candidate template ignored: could not
//       match 'istreambuf_iterator' against 'vector'
// bool operator==(const istreambuf_iterator<_CharT,_Traits>& __a,
//      ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/iterator:1135:1: note: candidate template ignored: could not
//       match 'move_iterator' against 'vector'
// operator==(const move_iterator<_Iter1>& __x, const move_iterator<_Iter2>& __y)
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/iterator:1507:1: note: candidate template ignored: could not
//       match '__wrap_iter' against 'vector'
// operator==(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y) _NOEXCEPT_DEBUG
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/tuple:1139:1: note: candidate template ignored: could not
//       match 'tuple' against 'vector'
// operator==(const tuple<_Tp...>& __x, const tuple<_Up...>& __y)
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/memory:1986:6: note: candidate template ignored: could not
//       match 'allocator' against 'vector'
// bool operator==(const allocator<_Tp>&, const allocator<_Up>&) _NOEXCEPT {return true;}
//      ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/memory:2960:1: note: candidate template ignored: could not
//       match 'unique_ptr' against 'vector'
// operator==(const unique_ptr<_T1, _D1>& __x, const unique_ptr<_T2, _D2>& __y) {return __x.get() == __y.get();}
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/memory:2996:1: note: candidate template ignored: could not
//       match 'unique_ptr' against 'vector'
// operator==(const unique_ptr<_T1, _D1>& __x, nullptr_t) _NOEXCEPT
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/memory:3004:1: note: candidate template ignored: could not
//       match 'unique_ptr<type-parameter-0-0, type-parameter-0-1>' against 'const long'
// operator==(nullptr_t, const unique_ptr<_T1, _D1>& __x) _NOEXCEPT
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/memory:4792:1: note: candidate template ignored: could not
//       match 'shared_ptr' against 'vector'
// operator==(const shared_ptr<_Tp>& __x, const shared_ptr<_Up>& __y) _NOEXCEPT
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/memory:4846:1: note: candidate template ignored: could not
//       match 'shared_ptr' against 'vector'
// operator==(const shared_ptr<_Tp>& __x, nullptr_t) _NOEXCEPT
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/memory:4854:1: note: candidate template ignored: could not
//       match 'shared_ptr<type-parameter-0-0>' against 'const long'
// operator==(nullptr_t, const shared_ptr<_Tp>& __x) _NOEXCEPT
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/functional:1952:1: note: candidate template ignored: could
//       not match 'function' against 'vector'
// operator==(const function<_Rp(_ArgTypes...)>& __f, nullptr_t) _NOEXCEPT {return !__f;}
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/functional:1957:1: note: candidate template ignored: could
//       not match 'function<type-parameter-0-0 (type-parameter-0-1...)>' against 'const long'
// operator==(nullptr_t, const function<_Rp(_ArgTypes...)>& __f) _NOEXCEPT {return !__f;}
// ^
// /Library/Developer/CommandLineTools/usr/include/c++/v1/vector:3340:1: note: candidate template ignored: could not
//       match 'vector<type-parameter-0-0, type-parameter-0-1>' against 'const long'
// operator==(const vector<_Tp, _Allocator>& __x, const vector<_Tp, _Allocator>& __y)
// ^