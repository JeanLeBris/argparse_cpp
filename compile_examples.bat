@REM git submodule update --init --recursive
git submodule update --recursive --remote

g++ ./examples/example_1.cpp -o ./example_1
g++ ./examples/example_2.cpp -o ./example_2
g++ ./examples/example_3.cpp -o ./example_3