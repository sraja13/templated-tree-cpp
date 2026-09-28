CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -pedantic

all: CTree.o check-template

CTree.o: CTree.cpp CTree.h
	$(CXX) $(CXXFLAGS) -c CTree.cpp

# Compile-checks the header-only templated Tree (Tree.h + Tree.inc)
check-template: Tree.h Tree.inc
	$(CXX) $(CXXFLAGS) -fsyntax-only -x c++ Tree.h

clean:
	rm -f *.o

.PHONY: all check-template clean
