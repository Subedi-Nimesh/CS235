###############################################################
# Program:
#     Week 08, Binary Tree
#     Brother Ercanbrack, CS235
# Author:
#     Nimesh Subedi
# Summary:
#     Binary Tree
# Time:
#     It took me 9 hours to complete the assignment.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week08.o huffman.o 
	g++ -o a.out week08.o huffman.o -g -std=c++11
	tar -cf week08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week08.o     : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
week08.o: bnode.h huffman.h week08.cpp
	g++ -c week08.cpp -g -std=c++11

huffman.o: bnode.h huffman.h huffman.cpp
	g++ -c huffman.cpp -g -std=c++11

