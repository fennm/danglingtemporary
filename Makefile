CXXFLAGS=-std=c++14

all: badstrview.o badstrstream.o

.PHONY: clean
clean:
	rm -f *.o a.out
