/***********************************************************************
 * Program:
 *    Sample 05, Sum the Numbers
 * Author:
 *    Br. Jones and Br. Helfrich
 * Summary:
 *    A simple program demonstrating how to create many threads.
 *    This program will sum all the numbers passed on the command line.
 * 
 *    Note that you must compile this with the -lpthread switch:
 *        g++ -lpthread sampleSum.cpp
 ************************************************************************/

#include <iostream>    // for COUT and CERR
#include <pthread.h>   // for PTHREAD_T and the PTHREAD functions
#include <stdlib.h>    // for ATOI
using namespace std;

// This variable represents the shared memory between the parent thread
// and all the children. Recall from the reading how the main way for
// threads to communicate is through shared memory. This shared memory
// needs to be global.
int sum = 0;

/**************************************************
 * SUM ONTO
 * Add a number onto the current value
 *************************************************/
void * sumOnto(void * p)
{
   // we need to cast the unknown data-type into a known format: a c-string
   const char * text = (const char *)p;
   
   // convert the c-string into an integer and add it to our sum 
   int num = atoi(text);
   sum += num;

   // we are done with this thread
   pthread_exit(NULL);
}

/*************************************************
 * MAIN
 * Turn the input parameters into calls to threads
 ************************************************/
int main(int argc, char ** argv)
{
   // make sure our command line parameters are properly formatted
   if (argc == 1) 
   {
      cerr << "Usage:\n\t" << argv[0] << " number <number> ...\n";
      return 1;
   }
   if (argc > 10)
   {
      cerr << "ERROR: Unable to add more than 10 numbers\n";
      cerr << "Usage:\n\t" << argv[0] << " number <number> ...\n";
      return 1;
   }

   // spawn all the threads
   pthread_t threads[10];      // we can spawn up to 10 threads
   for (int i = 1; i < argc; i++)
      pthread_create(&(threads[i - 1]),   // the unique ID of the thread
                     NULL,                // no special attributes here
                     sumOnto,             // the function to be called
                     argv[i]);            // the data to be passed to sumOnto

   // wait for them all to finish
   for (int i = 1; i < argc; i++)
      pthread_join(threads[i - 1], NULL);


   // display the results
   cout << "The sum is: " << sum << endl;

   return 0;
}
