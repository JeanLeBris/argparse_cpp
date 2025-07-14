update:bin obj
	git submodule update --recursive --remote
	g++ -c ./lib/deallocator/src/deallocator.cpp -o ./obj/deallocator.o
	ar rcs ./bin/libdeallocator.a ./obj/deallocator.o

examples:example_1 example_2 example_3

example_1:update argparse.o
	g++ -c ./examples/example_1.cpp -o ./obj/example_1.o
	g++ ./obj/example_1.o -L ./bin -l argparse -l deallocator -o ./bin/example_1

example_2:update argparse.o
	g++ -c ./examples/example_2.cpp -o ./obj/example_2.o
	g++ ./obj/example_2.o -L ./bin -l argparse -l deallocator -o ./bin/example_2

example_3:update argparse.o
	g++ -c ./examples/example_3.cpp -o ./obj/example_3.o
	g++ ./obj/example_3.o -L ./bin -l argparse -l deallocator -o ./bin/example_3

argparse.o:
	g++ -c ./src/argparse.cpp -o ./obj/argparse.o
	ar rcs ./bin/libargparse.a ./obj/argparse.o

bin:
	mkdir bin

obj:
	mkdir obj