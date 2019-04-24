from distutils.core import setup, Extension

module = Extension("myModule", sources=["myModule.c"])

setup(
    name = 'PackageName', 
    version = '1.0',
    description="this is a package for my module",
    ext_modules = [
        module
    ]
)