#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>
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

    self->m = vector<vector<int>>();
    return (PyObject *)self;
}

static int
matrix_init(matrix_t *self, PyObject *args, PyObject *kwds)
{
    PyObject *ll;    // list of lists
    PyObject *l;     // list
    PyObject *litem; // list item
    Py_ssize_t ni, nj;

    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &ll))
    {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list.");
        return -1;
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
                if (!PyLong_Check(litem))
                {
                    PyErr_SetString(PyExc_TypeError, "list items must be integers.");
                    return -1;
                }
                Py_DECREF(litem);
            }
        }
        else
        {
            PyErr_SetString(PyExc_TypeError, "list items must be integers.");
            return -1;
        }
        Py_DECREF(l);
    }

    // self->m.clear();
    self->m.resize(ni, vector<int>(nj));

    for (int i = 0; i < ni; i++)
    {
        l = PyList_GetItem(ll, i);
        Py_INCREF(l);
        for (int j = 0; j < nj; j++)
        {
            litem = PyList_GetItem(l, j);
            Py_INCREF(litem);
            self->m[i][j] = (int)PyLong_AsLong(litem);
            Py_DECREF(litem);
        }
        Py_DECREF(l);
    }
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
        return Py_ssize_t(0);
    }
    else
    {
        return Py_ssize_t(self->m.size() * self->m[0].size());
    }
}

// static PyObject *
// matrix_print(matrix_t *self)
// {
//     for (const std::vector<int> &v : self->m)
//     {
//         for (int x : v)
//         {
//             cout << x << ' ';
//         }
//         printf("\n");
//     }
//     return Py_None;
// }

// asasd

static int
matrix_contains(matrix_t *self, PyObject *arg)
{
    if (!PyLong_Check(arg))
    {
        PyErr_SetString(PyExc_TypeError, "object must be number");
        return -1;
    }

    long int num = PyLong_AsLong(arg);
    // if (count(self->m.begin(), self->m.end(), num))
    // return 1;
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
    // {"print", (PyCFunction)matrix_print, METH_NOARGS},
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