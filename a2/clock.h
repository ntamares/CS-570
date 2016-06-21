// Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
// CS 570, Summer 2016
// Guy Leonard
// Assignment #2, Paging
// clock.h

#ifndef CLOCK_H
#define CLOCK_H

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

//int clock(int frame_len, int page_len, int * pages);
int clock(int maxFrames, vector<int> pages);

#endif // CLOCK_H
