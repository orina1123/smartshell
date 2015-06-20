CXX = g++
CPPFLAGS = -std=gnu++11 -lreadline
PROG = $$ predict test_HistoryWindow final demo
OBJ = \
	  HistoryWindow \

all: $(PROG)

$(PROG): %: %.o $(OBJ:=.o)
	${CXX} $< $(OBJ:=.o) -o $@ $(CPPFLAGS)

$(OBJ:=.o): %.o: %.cpp
	${CXX} $< -c $(CPPFLAGS)

clean:
	rm -rf $(PROG) $(PROG:=.o) $(OBJ:=.o)

