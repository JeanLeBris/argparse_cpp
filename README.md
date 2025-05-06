# argparse_cpp

The objective of argparse_cpp is to reproduce the python argparse library for C++.

The library is (somewhat) usable, but very buggy.

It seems it crashes when multiple subparsers are selected (most likely an error in the parse_args() method).

Float and Double arguments won't work.
(now it does (sometimes) even though I didn't exactly change anything concerning it ???).
It looks like parse_args() works fine but the garbage collector crashes the app.

Compared to its python counterpart there are some differences:
- The program's version is not given to a "version" ```add_argument()``` method call, it is given to the initial ```ArgumentParser``` declaration.
- The "nargs" argument of the ```add_argument()``` method only accepts integers, there is no implementation of '?', '*' or '+'.