from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(
    name = 'cython_matrix', 
    version = '1.0',
    ext_modules = cythonize('cython_matrix.pyx')
)