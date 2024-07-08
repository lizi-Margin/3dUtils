from setuptools import setup, Extension
from Cython.Build import cythonize

extensions = [
    Extension("i3utils", ["i3utils.pyx"])
]

setup(
    ext_modules=cythonize(extensions, compiler_directives={'language_level': "3"}),
)
