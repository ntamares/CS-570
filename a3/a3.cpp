// Nestor Tamares (masc2010) & Alvin Somvilay (masc2006)
// CS 570, Summer 2016
// Guy Leonard
// Assignment #3, Alarm Clock
// a3.cpp

#include <iostream>
#include <semaphore.h>
#include <pthread.h>
#include <string>
#include <stdio.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

#define NUM_OF_THREADS 3

using namespace std;
sem_t FLAG; //Semaphore flag
pthread_t threads[NUM_OF_THREADS]; //thread array
bool runAlarm; //Flag to run alarm

//Struct to hold values of alarm to be passed to thread
struct alarm_data{
	int hour;
	int minute;
	int sec;
};

//Signal handler is called and cancels the child threads of the program
//Then exits the program
void signal_handler(int signum)
{
	int kstat;
  	//Cancel Clock thread
	kstat = pthread_cancel(threads[0]);
  	//Cancel Alarm thread if created
  	if(runAlarm)
		kstat = pthread_cancel(threads[1]);
  	//Cancel countdown thread
	kstat = pthread_cancel(threads[2]);

	sem_destroy(&FLAG);
	cout << "Ending program" << endl;
	exit(0);
}

//endProg creates a signal interrupt to trigger the end of the program
void endProg()
{
	signal(SIGTERM, signal_handler);
	raise(SIGTERM);
}

//Countdown starts at an initial value and counts down
//each second. Once done, the threads calls for the termination
//of every thread and ends the program
void *countdown(void *CD)
{
	int count = (int)CD;
	
	while(count >= 0)
	{
		sem_wait(&FLAG);
		cout << "Timer: " << count << endl;
		sem_post(&FLAG);
		count = count -1;
		sleep(1);
	}
	
	//End program
  endProg();
}

/*Alarm compares the user inputted values with the current time
of the system at every second. If alarm values equal time values,
a flag is triggered to print a message to the user.*/
void *alarm(void *AL)
{
	bool alon = true;
	bool ring = false;
	alarm_data *data = (alarm_data *)AL;
	// Alarm time variables
	int a_hr, a_min, a_sec;
	// Current time variables
	int c_hr, c_min, c_sec;
	a_hr  = (*data).hour;
	a_min = (*data).minute;
	a_sec = (*data).sec;
	
	while(alon) 
	{
		// Set current time
		time_t now = time(0);
		tm * ltm   = localtime(&now);
		c_hr   = (ltm -> tm_hour);
		c_min  = (ltm -> tm_min);
		c_sec  = (ltm -> tm_sec);

		// If alarm time equals current time, print message
		if((a_hr == c_hr) && (a_min == c_min) && (a_sec == c_sec))
		{	
			ring = true;
			alon = false;
		}
	
		sem_wait(&FLAG);	
		cout << "Alarm set for ";
		cout << a_hr << ":" << a_min << ":" << a_sec << endl;
		
		if(ring)
		{
			cout << "Alarm is going off! Wake Up!" << endl;
		}
		sem_post(&FLAG);
		sleep(1);
	}
  //Exit thread upon completion
  pthread_exit(0);
	
}

//Clock prints the current time each second
void *clock(void *temp)
{
	while(1) 
    	{
        	
      		// Current time based on current system
    		time_t now = time(0);
   			tm * ltm = localtime(&now);
			sem_wait(&FLAG);
        	// Print current time to console
			cout << "Current time: ";
        	cout << ltm -> tm_hour << ":";
        	cout << ltm -> tm_min << ":";
        	cout << ltm -> tm_sec << endl;
        	sem_post(&FLAG);
        	sleep(1);
    	}
}

//Change the attribute of the terminal window to remove echo and icanon
//properties. The function stores the old attributes in a termios struct
//before being copied and altered to a new set of attributes.
//Once the terminal sets the attributes to the new set, get and store
//the first character the user presses. Revert to the old attributes and
//return the character. Code adapted from:
//http://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    newattr.c_cc[VMIN] = 1;		//blocks read until a single character is available
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

//Monitor the user's keypresses until x is entered. Then end the program if found.
void watchX()
{
	char c;
	bool notX = true;
	while(notX)
	{
		c = getch();
		
		if(c == 'x')
		{
			endProg();
			notX = false;
		}
	}
}

void init_pthreads(alarm_data aTime, int timer)
{
    //Initialize semaphore FLAG
  	sem_init(&FLAG, 0, 1);
  
  	//Initialize POSIX Threads and attribute variables
  	
    	int status1;
	int status2;
	int status3;

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

        //Run threads for Clock, Alarm, and Countdown
        status1 = pthread_create(&threads[0], NULL, clock, (void *) NULL);
        if(status1) 
        {
            cout << "Error code " << status1 << endl;
            exit(-1);
        }
  		
  		if(runAlarm)
        {  
        status2 = pthread_create(&threads[1], NULL, alarm, (void *) &aTime);
          if(status2) 
          {
              cout << "Error code " << status2 << endl;
              exit(-1);
          }
        }
	    status3 = pthread_create(&threads[2], NULL, countdown, (void *) timer);
        if(status3) 
        {
            cout << "Error code " << status3 << endl;
            exit(-1);
        }
}

int main(int argc, char *argv[])
{ 
	alarm_data aTime; //struct to hold hour, minute, and seconds of the Alarm
	int timer;

	if(argc == 5)
	{
		aTime.hour = atoi(argv[1]);
		aTime.minute = atoi(argv[2]);
		aTime.sec = atoi(argv[3]);
		timer = atoi(argv[4]);
      	runAlarm = true;
	}
  	else if(argc == 4)
    {
        aTime.hour = atoi(argv[1]);
		aTime.minute = atoi(argv[2]);
		aTime.sec = atoi(argv[3]);
		timer = 10;
      	runAlarm = true;
    }
	else
	{
        cout << "No alarm set." << endl;
        cout << "Using default value for countdown" << endl;
		timer = 10;
		runAlarm = false;
	}
	
    cout << "Counting down from " << timer << endl;
	
	//Initalize pthreads and semaphores
	init_pthreads(aTime, timer);

	//Call terminate function
	watchX();
	
    return 0;
}


