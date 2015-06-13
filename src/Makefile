CXX = g++
CPPFLAGS = -std=gnu++11 -lreadline
PROG = $$ predict
OBJ = \


all: $(PROG)

$(PROG): %: %.o
	${CXX} $< -o $@ $(CPPFLAGS)

$(OBJ): %.o: %.cpp
	${CXX} $< -c

clean:
	rm -rf $(PROG) $(OBJ:=.o)

