a.out: week13.o
	g++ -o a.out week13.o -g -std=c++11
	tar -cf week13.tar *.h *.cpp makefile

week13.o: stack.h bnode.h bst.h list.h level.cpp week13.cpp
	g++ -c week13.cpp -g -std=c++11