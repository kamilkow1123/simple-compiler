all: main

main: main.cpp
	g++ main.cpp -o main.out

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o
	-rm *.s