// Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
// CS 570, Summer 2016
// Guy Leonard
// Assignment #3, Alarm Clock
// alarm_clock.cpp


#include "alarm_clock.h"

void display_time(){
    
    // Current time based on current system
    time_t now = time(0);
    
    // Local time
    tm * ltm = localtime(&now);
    
    cout << ltm -> tm_hour << ":";
    cout << ltm -> tm_min << ":";
    cout << ltm -> tm_sec << endl;

}
