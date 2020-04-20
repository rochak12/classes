###############################################################
# Program:
#     Lab 08, OpenMP
#     Brother XXXX, CS235
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
a.out: lab08.cpp
	g++ -o a.out -fopenmp lab08.cpp 
	tar -czf lab08.tar makefile lab08.cpp

sampleVariableThreads.out: sampleVariableThreads.cpp
	g++ -o sampleVariableThreads.out -fopenmp sampleVariableThreads.cpp

all: a.out sampleVariableThreads.out
	
