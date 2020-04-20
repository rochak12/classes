/***********************************************************************
 * Program:
 *    Sample 06, Binary Semaphore
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This example shows how to use binary semaphores with pthreads
 *
 *    You know this works when you see that one thread starts and
 *    the same thread ends on each line:
 *
 *    Start(Two)......Finish(Two)
 *    Start(One)......Finish(One)
 *    Start(One)......Finish(One)
 *    Start(Two)......Finish(Two)
 *    Start(One)......Finish(One)
 *
 *    If we remove the mutex code by commenting out two lines of code:
 *      sem_wait(&lock);
 *      sem_post(&lock);
 *    Then we see that the two threads clobber each other:
 *
 *    Start(Two)...Start(One)......Finish(One)
 *    ...Finish(Two)
 *    Start(One)...Start(Two)......Finish(One)
 *    ...Finish(Two)
 *    Start(One)...Start(Two)......Finish(One)
 *    Start(One)......Finish(Two)
 *    ...Finish(One)
 *
 *
 *    Note that you must compile this with the -lpthread switch:
 *        g++ -lpthread sampleBinarySem.cpp
 ************************************************************************/

#include <iostream>      // for COUT
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
sem_t lock;
bool done = false;

void * thread(void *);   // just a thread


/***********************************************
 * MAIN
 * Main just serves to call two threads and
 * display the results
 ***********************************************/
int main(int argc, char **argv)
{
   // set up a random number generator
   srand(time(NULL));
   
   // set up the mutex lock
   sem_init(&lock, 0 /*for thread safety, not process*/, 1 /*initial value*/);
   
   // launch the threads
   pthread_t threads[2];
   pthread_create(threads + 0, NULL, thread, (void *)"One");
   pthread_create(threads + 1, NULL, thread, (void *)"Two");

   // wait for a while
   usleep(rand() % 10000000);
   
   // all done!
   done = true;
   pthread_join(threads[0], NULL);
   pthread_join(threads[1], NULL);

   return 0;
}

/***********************************************************
 * THREAD
 * This is a simple thread
 **********************************************************/
void * thread(void * p)      // accepting no parameters
{
   while (!done)
   {
      usleep(rand() % 150000);

      // critical seciton
      sem_wait(&lock);                    // try commenting this out ...
      cerr << "Start(" << (char *)p << ")...";
      usleep(rand() % 150000);
      cerr << "...Finish(" << (char *)p << ")\n";
      sem_post(&lock);                    // ... and this out also
   }

   pthread_exit(NULL);
}
