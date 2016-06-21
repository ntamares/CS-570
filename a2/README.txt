Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
CS 570, Summer 2016
Guy Leonard
Assignment #2, Paging
README.txt

File manifest:
a2.cpp, clock.cpp, clock.h, opt.cpp, opt.h, 
second_chance.cpp, second_chance.h, Makefile, README.txt

Compile instructions:
Type the command "make" which will make the executable names "pager".
Afterwards, if you want to clean up and remove the object files, type the command "make clean".

Operating instructions:
To run the program, run the executable by typing in "pager".

Novel/significant design decisions:
The project is written in C++.
The main() in a2.cpp reads in the number of frames and the page sequence to be simulated with 
three page replacement algorithms: Optimal (OPT), Second Chance, and Clock in order to find the 
number of page faults each one produces. The number of page faults in each algorithm is printed to 
the console as well as the output text file "pages.txt".

Extra features:
None

Lessons learned:
In this project, we learned how to simulate a page replacement system to find the number of page
faults found by using three page replacement algorithms: Optimal (OPT), Second Chance, and Clock.
Page faults occur when a page to be loaded is not found in memory.

OPT:
The OPT algorithm is used to measure other algorithms against as it is not practical to use because
it is impossible to know future references. However, since we know what exact sequence of pages, 
we can replace the page that is farthest in the future or no longer referenced.

Second Chance:
The Second Chance algorithm is a variant of FIFO (First In, First Out). Unlike the FIFO algorithm,
Second Chance does not just kick out the first page loaded in memory. If a page is already in memory,
and is referenced again, it is given a "second chance" and the is loaded and upadted as though it had 
just arrived in memory. This way frequently used pages are not evicted just because they were used early on.

Clock:
The clock algorithm uses a use bit to approximate the aging of the pages referenced longest ago and a
pointer to decide which page is replaced. When a page is first loaded in memory, the use bit is set to 1 and the pointer increments. 
When a page if referenced, it remains/is set to 1. When searching for the replacement, frames with the use 
bit set to 1 is changed to 0. When a page needs to be replaced, the first page with the use bit set to 0 is replaced.
For each unsuccessful search for a page in memory, the pointer is incremented.

It real world applications, there is no one algorithm (aside from OPT, but that's not actually possible to implement) that is
definitively the best to use. Each algorithm has their strengths and weaknesses depending on who/what is implementing them.

This will be submitted through Alvin's account. masc2006
