###############################################################
# Program:
#     Lab 12, Bell-LaPadula
#     Brother XXXX, CS470
# Author:
#     <your name here>
# Summary:
#     This program keeps track of highly confidential messages
#     posted by people of various security clearences. 
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: lab12.cpp control.h interact.o message.o messages.o makefile
	g++ -o a.out lab12.cpp interact.o message.o messages.o -std=c++11
	tar -cf lab12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      interact.o   : the main user interface
#      message.o    : a single message
#      messages.o   : a collection of messages
##############################################################
interact.o: interact.cpp interact.h message.h messages.h control.h
	g++ -c interact.cpp -std=c++11

message.o: message.cpp message.h control.h
	g++ -c message.cpp -std=c++11

messages.o: messages.cpp messages.h message.h control.h
	g++ -c messages.cpp -std=c++11

