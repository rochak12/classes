/***********************************************************************
 * Program:
 *    Sample 05, Hello with Threads
 * Author:
 *    Br. Jones and Br. Helfrich
 * Summary:
 *    This program will demonstrate how to create two threads to display
 *    a message on the screen. It is, perhaps, the simplest threading
 *    program you can write.
 *
 *    Note that you must compile this with the -lpthread switch:
 *        g++ -lpthread sampleHello.cpp
 ************************************************************************/

#include <iostream>      // for COUT
#include <pthread.h>     // for pthread_t and the pthread functions
#include <cassert>       // for ASSERT
using namespace std;

void *displayMessage(void * p); 

/***********************************************
 * MAIN
 * Main just serves to call one thread.
 ***********************************************/
int main()
{
   int ret;   // catch the return value from pthread_create

   // create the thread
   pthread_t thread;
   ret = pthread_create(&thread,          // a pointer to the thread created
                        NULL,             // use the default set of attributes
                        displayMessage,   // the function to be called
                        NULL);            // the parameter to the function
   assert(ret == 0);  // anything else is a failure

   // now wait for the thread to exit
   pthread_join(thread,                   // which thread to wait on
                NULL);                    // data passed back to the caller
                                          //    through the return mechanism
   return 0;
}

/***********************************************************
 * DISPLAY MESSAGE
 * Display a simple message to the screen
 **********************************************************/
void * displayMessage(void * p)
{
   // display the message to the screen
   cout << "Hello world!\n";

   // this thread is done!
   pthread_exit(NULL);                 // if we sent something back to main(),
}                                      //    it would be here. The result 
                                       //    is caught in the second parameter
                                       //    of pthread_join()
