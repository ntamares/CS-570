/* 
    Nestor Tamares & Alvin Somvilay (masc2006)
    CS 570, Summer 2016
    Guy Leonard
    Assignment #1, Multithreading
    a1.cpp
*/


#include "a1.h"

//WriteQuote will check whether the thread is even or odd, then sleep
//for 2 or 3 seconds depending on the threadID, then
//open the "QUOTE.txt" file, write the correct quote,
//write the current threadID to the console, and close the file.
//Repeat 7 times.
void *writeQuote(void *ID)
{
    for(int a = 0; a < 8; a++)
    {
        int threadID = (int)pthread_self();

        //Sleep
        if((threadID % 2) == 0)
            sleep(2);
        else
            sleep(3);

        //Use semaphore to restrict access to "QUOTE.txt" to 1 thread at a time
        sem_wait(&FLAG);
        file_name.open("QUOTE.txt", std::ios_base::app | std::ios_base::out);

        if((threadID % 2) == 0)
            file_name << threadID-1 << " - " << "\"Controlling complexity is the essence of computer programming.\" --Brian Kernigan \r\n";
        else
            file_name << threadID-1 << " - " << "\"Computer science is no more about computers than astronomy is about telescopes.\" --Edsger Dijkstra \r\n";

        cout << "Thread " << pthread_self()-1 << " is running\n";

        file_name.close();
        sem_post(&FLAG);
    }
    //Exit thread
    pthread_exit(NULL);
}


int main(){
    
    //File creation and write Process ID to the "QUOTE.txt"
    file_name.open("QUOTE.txt");
    file_name << "Process ID " << getpid() << "\r\n";
    file_name.close();
  
    //Initialize semaphore FLAG
    sem_init(&FLAG, 0, 1);
  
    //Initialize POSIX Threads
    pthread_t threads[NUMBER_OF_THREADS];
    pthread_attr_t attr;
    int status;
    void *state;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  
    //Each thread will run the writeQuote function one at a time using the semaphore.
    //Code adapted from https://computing.llnl.gov/tutorials/pthreads/
    for(int i = 0; i < NUMBER_OF_THREADS; i++)
    {
         //Run threads
         status = pthread_create(&threads[i], &attr, writeQuote, (void *) (i+1));
         if(status) 
	 {
             cout << "Error code " << status << endl;
             exit(-1);
         }
    }
    
    // Free attribute
    pthread_attr_destroy(&attr);
  
    //Block main from completing until the other threads are completed
    //Code adapted from https://computing.llnl.gov/tutorials/pthreads/
    for(int j = 0; j < NUMBER_OF_THREADS; j++)
    {
        //Join Threads
        status = pthread_join(threads[j], &state);
        if(status) 
        {
              cout << "Error code " << status << endl;
              exit(-1);
        }
    }

    //Destroy semaphore and exit program
    sem_destroy(&FLAG);
    cout << "Program Complete! \n";
    
    return 0;
}

