exec = sowa.out
sources = $(wildcard src/*.cpp)
objects = $(sources:.cpp=.o)
flags = -g -Wall -lm -ldl -fPIC -Wl,--export-all-symbols

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.cpp include/%.h
	gcc -c $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tidy src/*.cpp src/include/*.h