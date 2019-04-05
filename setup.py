from distutils.core import setup, Extension

setup(
    name="ACtrie",
    description="python wrapper,support unicode",
    packages=['ACtrie'],
    ext_modules = [
        Extension("_ACtrie",
            sources=['ACtrie/wrapper.cpp'],
            include_dirs=['./ACtrie'],
            extra_compile_args=['-std=c++11'],
        )
    ],
    install_requires = [
        'intervaltree',
    ],
    version='0.5.2'
)