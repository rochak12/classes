/***********************************************************************
 * Program:
 *    Sample 06, Counting Semaphore
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This example shows how to use a counting semaphore with pthreads
 *
 *    If we run this program with only one "max depth", then only one
 *    thread will enter the critical section at a time:
 *                      4-start
 *                      4-finish
 *                      1-start
 *                      1-finish
 *                      5-start
 *                      5-finish
 *    Notice how thread 4 stops before thread 1 starts and so on. Now
 *    if we do this with 2 threads in the critical sectoin (maxDepth = 2),
 *    then it will look different:
 *                    5-start
 *                      3-start
 *                      3-finish
 *                    5-finish
 *                    2-start
 *                      6-start
 *                      2-finish
 *                      1-start
 *                      6-finish
 *                    1-finish
 *    Here we can see that at any one time, there is no more than 2 threads
 *    active in the critical section at a time. The number of active threads
 *    is the indentation level. Now we will try maxDepth = 3
 *               4-start
 *                  6-start
 *                      5-start
 *                      6-finish
 *                      6-start
 *                      4-finish
 *                      2-start
 *                      2-finish
 *                  6-finish
 *              5-finish
 *              1-start
 *                  5-start
 *                  1-finish
 *                  4-start
 *                      3-start
 *                      3-finish
 *                  5-finish
 *              4-finish
 *    The counting semaphore code will keep this in order:
 *       sem_wait(&semaphore);
 *       sem_post(&semaphore);
 *    When we comment this out, what happens?
 *                  1-start
 *                  1-finish
 *                  1-start
 *                  2-start
 *                  4-start
 *                  6-start
 *    Here you can see than any number of threads can enter the critical
 *    section.
 *
 *    Note that you must compile this with the -lpthread switch:
 *        g++ -lpthread sampleCountSem.cpp
 ************************************************************************/

#include <iostream>      // for COUT
#include <iomanip>       // for SETW
#include <pthread.h>     // for pthread_t and the pthread functions
#include <semaphore.h>   // for SEM_T and related methods
#include <cassert>       // for ASSERT
#include <ctime>         // for time(), part of the random process
#include <unistd.h>      // for usleep()
#include <stdlib.h>      // for rand() and srand()

using namespace std;


// This variable represents the shared memory between the parent thread
// and all the children. Recall from the reading how the main way for
// threads to communicate is through shared memory. This shared memory
// needs to be global.
sem_t semaphore;         // counting semaphore
bool done = false;       // signify we are done
#define NUM_THREADS 6    // number of threads

void * thread(void *);   // just a thread



/***********************************************
 * MAIN
 * Main just serves to call NUM_THREADS threads and
 * display the results
 ***********************************************/
int main(int argc, char **argv)
{
   // set up a random number generator
   srand(time(NULL)); 
   
   // determine how many threads can be in the critical section at once
   int maxDepth;
   cout << "What is the max depth? ";
   cin  >> maxDepth;
   
   // set up the mutex lock
   sem_init(&semaphore,
            0 /*for thread safety, not process*/,
            maxDepth /*initial*/);
   
   // launch the threads
   pthread_t threads[NUM_THREADS];
   for (long i = 0; i < NUM_THREADS; i++)
      pthread_create(threads + i, NULL, thread, (void *)(i + 1));

   // wait for a while
   usleep(rand() % 1000000);
   
   // all done!
   done = true;
   for (int i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);

   return 0;
}

/***********************************************************
 * THREAD
 * This is a simple thread
 **********************************************************/
void * thread(void * p)      // accepting no parameters
{
   // retrieve the thread number
   long id = (long)p;

   while (!done)
   {
      // wait until it is time to play
      usleep(rand() % 150000);

      // wait if there are no open slots.
      sem_wait(&semaphore);

      // find out how many slots there are. This will be useful
      // for doing the indentation of the output
      int value;
      sem_getvalue(&semaphore, &value);
      cerr << setw(24 - value * 4) << id << "-start\n";

      // wait for a while so we can have multiple threads collide.
      usleep(rand() % 150000);

      // find out how many slots there are again so we can indent.
      sem_getvalue(&semaphore, &value);
      cerr << setw(24 - value * 4) << id << "-finish\n";

      // signify we are done
      sem_post(&semaphore);
   }

   // exit this thread when we get the global Done indication
   pthread_exit(NULL);
}
