###############################################################
# Program:
#     Week 01, Vector
#     Brother Ercanbrack, CS235
# Author:
#     Nimesh Subedi
# Summary:
#     the following program creates a vector and fills it up.
#     and it also adds new items as well as removes items.
# Time:
#     it took me about 6 hours to reach where i submitted.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h week01.o
	g++ -o a.out week01.o 
	tar -cf week01.tar vector.h week01.cpp makefile

##############################################################
# The individual components
#      week01.o     : the driver program
##############################################################
week01.o: vector.h week01.cpp
	g++ -c week01.cpp
