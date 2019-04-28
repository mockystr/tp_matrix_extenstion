from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(
    name = 'ext_test', 
    version = '1.0',
    ext_modules = cythonize('test.pyx')
)