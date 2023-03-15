.SUFFIXES:
.PHONY: all compile checkstyle test clean

CXX = g++ -Wall -Wextra -g
BASENAME = GameOfLife
LIBS = -lncurses
TESTLIBS = -lgtest -lgtest_main -lpthread

all: compile checkstyle test

compile: $(BASENAME)Main 

checkstyle:
	python3 ../cpplint.py --repository=. *.cpp *.h

test: $(BASENAME)Test
	./$<

%.o: %.cpp *.h
	$(CXX) -c $<

%Main: %Main.o %.o
	$(CXX) -o $@ $^ $(LIBS)

%Test: %Test.o %.o
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)


clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o

