// a1.h
//Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
//CS 570, Summer 2016
//Guy Leonard
//Assignment #1, Multithreading

#ifndef A1_H
#define A1_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <semaphore.h>
#include <pthread.h>

#define NUMBER_OF_THREADS 7

using namespace std;

sem_t FLAG; // semaphore
ofstream file_name; //file to write to

//WriteQuote will check whether the thread is even or odd, then sleep
//for 2 or 3 seconds depending on the threadID, then
//open the "QUOTE.txt" file, write the correct quote,
//write the current threadID to the console, and close the file.
//Repeat 7 times.
void *writeQuote(void *);

#endif // A1_H
