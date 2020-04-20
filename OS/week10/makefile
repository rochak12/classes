###############################################################
# Program:
#     Lab 10, Page Replacement Lab
#     <your instructor>, CS345
# Author:
#     <your name here>
# Summary:
#     <put a description here>
# Time:
#     <how long did it take to complete this program?>
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lab10.o pr.o
	g++ -o a.out lab10.o pr.o
	tar -czf lab10.tar makefile *.cpp *.h

##############################################################
# The individual components
##############################################################
lab10.o: lab10.cpp pr.h
	g++ -c lab10.cpp

pr.o: pr*.h pr.cpp pr.h
	g++ -c pr.cpp

