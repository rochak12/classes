/***********************************************************************
 * Program:
 *    Sample 05, Parameter Passing
 * Author:
 *    Br. Jones and Br. Helfrich
 * Summary:
 *    This program will demonstrate how to send data from the parent
 *    to the child process using a parameter. Also, we will send data
 *    from the child back to the parent as a parameter
 *
 *    Note that you must compile this with the -lpthread switch:
 *        g++ -lpthread sampleParam.cpp
 ************************************************************************/

#include <iostream>      // for COUT
#include <pthread.h>     // for pthread_t and the pthread functions
#include <cassert>       // for ASSERT
using namespace std;

void *displayMessage(void * p); 

/***********************************************
 * MAIN
 * Main just serves to call one thread and to
 * handle the communication interchange
 ***********************************************/
int main()
{
   int ret;   // catch the return value from pthread_create

   // create the thread
   pthread_t thread;
   ret = pthread_create(&thread,          // a pointer to the thread created
                        NULL,             // use the default set of attributes
                        displayMessage,   // the function to be called
                        (void *)"Input"); // the parameter to the function
   assert(ret == 0);  // anything else is a failure

   // accept data from the child. It comes in as a void pointer
   void * p;
   pthread_join(thread,                   // which thread to wait on
                &p);                      // data passed back to the caller
                                          //    through the return mechanism

   const char * message = (const char *)p;// cast back to a known data-type
   cout << "Parent received the following from the child: "
        << (char *)message
        << endl;
   
   return 0;
}

/***********************************************************
 * DISPLAY MESSAGE
 * Display to standard out the c-string passed as a parameter
 **********************************************************/
void *displayMessage(void * p)
{
   // we need to cast the void pointer into our known data-type
   const char * message = (const char *)p;

   // display the message
   cout << "Child received the following from the parent: "
        << message
        << endl;
   
   // send data back to the parent. This data must be a void pointer
   pthread_exit((void *)"Output");     // if we sent something back to main(),
}                                      //    it would be here. The result 
                                       //    is caught in the second parameter
                                       //    of pthread_join()
