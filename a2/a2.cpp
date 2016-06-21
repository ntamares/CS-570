// Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
// CS 570, Summer 2016
// Guy Leonard
// Assignment #2, Paging
// a2.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <stdlib.h>
#include "opt.h"
#include "second_chance.h"
#include "clock.h"
using namespace std;


void getPages(int &frameNum, vector<int> &pageVal)
{
    //Declare variables
    string frameLine;
    string pageLine;
    fstream myfile;
  
    //open "pages" and get and store the two lines
    myfile.open("pages.txt");
    getline(myfile, frameLine);
    getline(myfile, pageLine);

		
    //Convert first line representing number of frames into an int
    frameNum = atoi(frameLine.c_str());
		
    //Parse a line of words by whitespace and store each word
    //into a vector. Section of code taken from:
    //http://stackoverflow.com/questions/236129/split-a-string-in-c
    vector<string> pages;
    string buf;
    stringstream ss(pageLine);

    while(ss >> buf)
        pages.push_back(buf);
		
    //Convert each string in the "pages" vector to an int and store it
    for(int i = 0; i < pages.size(); i++)
        pageVal.push_back(atoi(pages[i].c_str()));

    myfile.close();
}

//Open "faults.txt" and write the faults for each algorithm
void writeFaults(int OPTfaults, int SCfaults, int Clkfaults)
{
    ofstream ffile;
    ffile.open("faults.txt");

    ffile << "Optimal Faults: " << OPTfaults << "\n"
    << "Second Chance Faults: " << SCfaults << "\n"
    << "Clock Faults: " << Clkfaults << "\n";
}

int main()
{
    //Define variables
    int frames;
    vector<int> page;
    int OPTfaults = 0;
    int SCfaults = 0;
    int clock_faults = 0;
  
  	cout << "Opening pages.txt..." << endl;

    //fill variables with values from text file
    getPages(frames, page);
		
    //Run Optimal Page Replacement Algorithm
    //OPTfaults = OPTReplace(frames, page);
    //Print Optimal faults to console
    cout << "Optimal Faults: " << OPTfaults << endl;

    //Run Second Chance Page Replacement Algorithm
    //SCfaults = SCReplace(frames, page);
		//Print Second Chance faults
    cout << "Second Chance Faults: " << SCfaults << endl;
  
    // Run Clock Page Replacement Algorithm
    //clock_faults = clock(frames page);
    // Print Clock faults to console
    cout << "Clock Faults: " << clock_faults << endl;

    //Write Faults to file
    //writeFaults(OPTfaults, SCfaults, 0);

    return 0;
}

