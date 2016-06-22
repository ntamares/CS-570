# Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
# CS 570, Summer 2016
# Guy Leonard
# Assignment #3, Alarm Clock
# Makefile


aclock: a3.o alarm_clock.o
	g++ -o aclock a3.o alarm_clock.o
	
a3.o:	a3.cpp alarm_clock.h
	g++ -c a3.cpp
	
alarm_clock.o:	alarm_clock.cpp alarm_clock.h
	g++ -c alarm_clock.cpp
	
clean:
	rm -f *.o
