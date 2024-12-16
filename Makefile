all: project1
CPP=g++
CFLAGS=-std=c++11

project1: project1.o socialnetwork.o user.o
	$(CPP) -o project1 project1.o socialnetwork.o user.o

project1.o: project1.cpp socialnetwork.hpp user.hpp
	$(CPP) -c project1.cpp $(CFLAGS)

socialnetwork.o: socialnetwork.cpp socialnetwork.hpp user.hpp
	$(CPP) -c socialnetwork.cpp $(CFLAGS)

user.o: user.cpp user.hpp
	$(CPP) -c user.cpp $(CFLAGS)

clean:
	rm -f *.o *~ project1
