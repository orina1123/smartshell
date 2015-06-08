CXX=g++

all: demo

demo: demo.o
	${CXX} demo.o -o demo -lreadline
demo.o: demo.cpp
	${CXX} demo.cpp -c

clean:
	rm demo demo.o
