# Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
# CS 570, Summer 2016
# Guy Leonard
# Assignment #3, Alarm Clock
# Makefile

CFLAGS = -lrt -lpthread -lncurses

aclock: a3.o
	g++ $(CFLAGS) -o aclock a3.o
	
a3.o:	a3.cpp
	g++ -c a3.cpp
	
clean:
	rm -f *.o aclock
