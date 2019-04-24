#include <Python.h>

int CFib(int n)
{
    int cur = 0, prev = 1, temp;

    for (int i = 0; i < n; i++)
    {
        temp = cur;
        cur += prev;
        prev = temp;
    }
    return cur;
}

static PyObject *fib(PyObject *self, PyObject *args)
{
    int n;
    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    return Py_BuildValue("i", CFib(n));
}

static PyObject *version(PyObject *self)
{
    return Py_BuildValue("s", "Version 1.0");
}

static PyMethodDef myMethods[] = {
    {"fib", fib, METH_VARARGS, "Calculates fib numbers"},
    {"version", (PyCFunction)version, METH_NOARGS, "Prints module version"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "myModule",
    "Fibonacci module",
    -1,
    myMethods};

PyMODINIT_FUNC PyInit_myModule(void)
{
    return PyModule_Create(&myModule);
}
