from setuptools import setup
from Cython.Build import cythonize
from Cython.Distutils import build_ext
from distutils.extension import Extension

extensions = [
    Extension("sorting", ["sorting.pyx"]),
]

setup(
    name="sorting",
    ext_modules=cythonize(extensions),
    cmdclass={"build_ext": build_ext}
)


