exec = a.out
sources = $(wildcard src/*.cpp)
objects = $(sources:.cpp=.o)
flags = -g -Wall -lm -ldl -fPIC

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.cpp include/%.h
	gcc $(flags) $< -o $@

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tidy src/*.cpp src/include/*.h