# argparse_cpp

The objective of argparse_cpp is to reproduce the python argparse library for C++.

The library is not usable yet.

Compared to its python counterpart there are some differences:
- The program's version is not given to a "version" ```add_argument()``` method call, it is given to the initial ```ArgumentParser``` declaration.
- The "nargs" argument of the ```add_argument()``` method only accepts integers, there is no implementation of '?', '*' or '+'.