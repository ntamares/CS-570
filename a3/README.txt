Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
CS 570, Summer 2016
Guy Leonard
Assignment #3, Alarm Clock
README.txt

File manifest:
a3.cpp Makefile, README.txt

Compile instructions:
Type the command "make" which will make the executable named "aclock".
Afterwards, if you want to clean up and remove the object files and an old executable, type the command "make clean".

Operating instructions:
To run without setting an alarm, type the command "aclock". This will run without an alarm set and will use a default 
countdown timer of 10 seconds.

To run with an alarm, type in "aclock h m s" where h is the hour, m is the minute, and s is the second at which you
want the alarm to go off. This will also use a default of 10 seconds for the countdown timer. As the clock is a 24-hour
clock, the alarm should be set to match it.

To run with a designated countdown time, type in "aclock h m s ct" where ct is the amount of seconds for the countdown
timer. The program will terminate when this countdown reaches 0.

Additionally, you can terminate the program by press the 'x' key.

Novel/significant design decisions:
The project is written in C++.

The clock updates periodically using the system clock. The alarm thread is not created if the user gives no input for the alarm.
Semaphores are used to block multiple threads from writing to the console at the same time.

To implement the keypress to terminate, we used code that would alter the attributes of the terminal. The terminal is set to
noncanonical mode, meaning input is available immediate, the user does not need to use a line-delimiter (like pressing enter) to
confirm input, and user input is uneditable. We also turned off echo, meaning the character will not appear in the terminal when pressed.

To interrupt the threads, we used signaling. A function is called when ther user presses x or count down runs out, that function
initializes a signal before raising it. Then in the signal handler, all child threads are canceled, semaphores are destroyed, and the program
exits.


Extra features:
None

Lessons learned:
We learned how to properly integrate threads and interrupts. We were able to monitor user input as a program continuosly wrote data.
We learned about the attributes of the terminal in our research and how to alter them to fit our needs.

This will be submitted through Nestor's account, masc2010
