example_1:example_1.exe
example_2:example_2.exe

example_1.exe:
	g++ examples/example_1.cpp -o example_1.exe
	./example_1.exe
	rm -f *.exe

example_2.exe:
	g++ examples/example_2.cpp -o example_2.exe
	./example_2.exe
	rm -f *.exe