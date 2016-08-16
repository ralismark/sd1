# sdd-game

Code for SDD game project.

## Prerequisite

This is intended to be built on windows. As a result, many resources are in such
a format.

Requirements:
 - SQLite3
 - MSVC (CL optimising compiler working)
 - LLVM (clang and llvm-ar)
 - Tup (build system)

Also, it is required to set the environment variables `cxx` and `cflags` to the
compiler and the flags.

Recommended options (aka options on my system):
 - `cxx`: `clang -std=c++14 -fms-compatibility-version=19`
 - `cflags`: `-Wall -Wextra -pedantic -O2 -D_CRT_SECURE_NO_WARNINGS -fcxx-exceptions`

## Building

Once the requirements are met, run `build.bat` in the root directory. This will
produce all object files in the build directory, but also produce lib.a there.

To actually compile another program, use `compile.bat` as if it were the clang
compiler. It will link with the necessary libs (including build\lib.a), and
produce and executable.

To run this executable, run `setup.bat` to add the dll's to the path. Then run
the program like any other program.
