/***********************************************************************
 * Program:
 *    Sample 05, Pass data using a global data structure
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will demonstrate how to pass data between
 *    the parent and child threads using a global data structure
 *
 *    Note that you must compile this with the -lpthread switch:
 *        g++ -lpthread sampleGlobal.cpp
 ************************************************************************/

#include <iostream>      // for COUT
#include <pthread.h>     // for pthread_t and the pthread functions
#include <cassert>       // for ASSERT
#include <string>        // for STRING
using namespace std;


// This variable represents the shared memory between the parent thread
// and all the children. Recall from the reading how the main way for
// threads to communicate is through shared memory. This shared memory
// needs to be global.
string fullName[2];


void * setFirstName(void * p);
void * setLastName (void * p);

/***********************************************
 * MAIN
 * Main just serves to call two threads and
 * display the results
 ***********************************************/
int main()
{
   int ret;   // catch the return value from pthread_create

   // create the two thread
   pthread_t threadFirst;
   ret = pthread_create(&threadFirst,     // a pointer to the thread created
                        NULL,             // use the default set of attributes
                        setFirstName,     // the function to be called
                        NULL);            // the parameter to the function
   assert(ret == 0);  // anything else is a failure
   pthread_t threadLast;
   ret = pthread_create(&threadLast,      // a pointer to the thread created
                        NULL,             // use the default set of attributes
                        setLastName,      // the function to be called
                        NULL);            // the parameter to the function
   assert(ret == 0);  // anything else is a failure

   // now wait for the thread to exit
   pthread_join(threadFirst,              // which thread to wait on
                NULL);                    // data passed back to the caller
   pthread_join(threadLast,               //    through the return mechanism
                NULL);

   cout << "Name: " << fullName[1]
        << ", "     << fullName[0]
        << endl;
      
   return 0;
}

/***********************************************************
 * SET FIRST NAME
 * Set the first name on the global data structure fullName
 **********************************************************/
void * setFirstName(void * p)      // accepting no parameters
{
   fullName[0] = string("Thomas E.");
   pthread_exit(NULL);             // sending back no parameters
}

/***********************************************************
 * SET Last NAME
 * Set the last name on the global data structure fullName
 **********************************************************/
void * setLastName(void * p)
{
   fullName[1] = string("Ricks");
   pthread_exit(NULL);
}
