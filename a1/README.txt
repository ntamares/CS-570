Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
CS 570, Summer 2016
Guy Leonard
Assignment #1, Multithreading
README.txt

File manifest:
a1.cpp, a1.h, Makefile, README.txt

Compile instructions:
Use the command "make", which uses the g++ compiler and the lpthread, lrt, and Wall flags.

Operating instructions:
Once you use the makefile to compile a1.cpp, it creates an executable named "sem".
To execute "sem", type the command "sem" and this will run the program.

Novel/significant design decisions:
The project is written in c++ as it was the language we were most comfortable with.
The main() in a1.cpp uses two for loops, one to create the 7 threads and the other to join them to
prevent the main thread from finishing the program.
We have a single function that the threads run called writeQuote that does all the tasks defined
in the assignment. Anything that the single thread must do is within that function.
We made the semaphore and text file into global variables. Both are initialized in the main() function
but aren't put to use until the writeQuote function is ran.
The semaphore only allows for one thread to have access to the text file and console at a time.

Extra features:
None.

Lessons learned:
In this assignment, we learned how to use multiple threads to do work simultaneously. However, to get this
to work properly, we needed to use semaphores, or else the threads would interfere with each other when
they try to write to the console or text file. All the threads had to be joined or else the main() process 
would not wait for the other threads to run and just return 0, ending the program.

This will be submitted through Nestor's account, masc2010.
