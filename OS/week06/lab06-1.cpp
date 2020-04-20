/***********************************************************************
 * Program:
 *    Lab 06, Producer and Consumer
 * Author:
 *    <your name here>
 * Summary:
 *    This program will allow us to simulate the production run
 *    at McLaren Cars. It would be cool if it simulated the cars
 *    themselves, but that might be an assignment for another day
 *
 *    Note that you must compile this with the -lpthread switch:
 *        g++ -lpthread lab06.cpp
 ************************************************************************/

#include <iostream>      // for COUT
#include <cassert>       // for ASSERT
#include <string>        // for STRING
#include <sstream>       // for STRINGSTREAM
#include <queue>         // for QUEUE
#include <ctime>         // for time(), part of the random process
#include <unistd.h>      // for usleep()
#include <stdlib.h>      // for rand() and srand()
#include <semaphore.h>
#include <pthread.h>
#include <vector>
#include "cars.h"        // for everything dealing with McLaren Cars

using namespace std;


// This variable represents the shared memory between the parent thread
// and all the children. Recall from the reading how the main way for
// threads to communicate is through shared memory. This shared memory
// needs to be global.
bool productionComplete = false;
static int serialNumberNext = 0;
static int maxInventory = 6;

Inventory * inventory;

pthread_mutex_t idLock;
sem_t semaphore;

void * producer(void *p);
void * consumer(void *p);

int getNumber(const char * prompt, int max);

struct consumerItem {
   const char * retailer;
   string * message;
};

vector<consumerItem *> consumerItems;

/***********************************************
 * MAIN
 * This will serve to prompt the user for the number
 * of models and the number of retailers. It will then
 * begin the simulation
 ***********************************************/
int main(int argc, char **argv)
{
   // set up the random number generator
   srand(argc == 1 ? time(NULL) : (int)argv[1][1]);

   inventory = new Inventory();
   vector<pthread_t> producers;
   vector<pthread_t> consumers;

   // determine how many producer and consumer threads
   int numProducer = getNumber("How many models?    ", numModels());
   int numConsumer = getNumber("How many retailers? ", numRetailers());

   pthread_mutex_init(&idLock, NULL);

   sem_init(&semaphore, 0, maxInventory);

   // produce the cars. Note that this code needs to change. We will
   // need to launch one thread per producer here
   for (int i = 0; i < numProducer; i++)
   {
      pthread_t newThread;
      pthread_create(&newThread,              
                     NULL,                    
                     producer,                  
                     (void *)models[i]);
      producers.push_back(newThread);
   }

   // sell the cars. Note that this code also needs to change.
   cout << "\nThe cars sold from the various retailers:\n\n";
   for (int i = 0; i < numConsumer; i++)
   {
      pthread_t newThread;
      consumerItem * newItem = new consumerItem();
      newItem->retailer = retailers[i];
      consumerItems.push_back(newItem);

      pthread_create(&newThread,
                     NULL,
                     consumer,
                     (void *)newItem);
      consumers.push_back(newThread);
   }

   for (int i = 0; i < producers.size(); i++) {
      pthread_join(producers.at(i), NULL);
   }

   for (int i = 0; i < consumers.size(); i++) {
      pthread_join(consumers.at(i), NULL);

      consumerItem * item = consumerItems.at(i);

      cout << *consumerItems.at(i)->message << endl;
   }

   // final report
   cout << "Maximum size of the inventory: "
        << inventory->getMax()
        << endl;

   return 0;
}

/***********************************************************
 * PRODUCER
 * Create those cars.
 * This function is not currently thread safe. You will need
 * to introduce a critical section in such a way that we do
 * not compromise the queue nor produce two cars with the
 * same serial number.
 **********************************************************/
void * producer(void * model)
{
   // a car to be added to the inventory
   Car car;
   car.model = (char *)model;

   // continue as long as we still need to produce cars in this run
   while (serialNumberNext < NUM_CARS)
   {
      // now that we decided to build a car, it takes some time
      usleep(rand() % 150000);

      // add the car to our inventory if we still need to
      // CRITICAL SECTION BEGIN
      sem_wait(&semaphore);
      pthread_mutex_lock(&idLock);
      if (serialNumberNext < NUM_CARS)
      {
         car.serialNumber = ++serialNumberNext;
         inventory->makeCar(car);
      }
      pthread_mutex_unlock(&idLock);
      // CRITICAL SECTION END
   }

   // all done!
   productionComplete = true;
   pthread_exit(NULL);
}

/****************************   cout << report;
******************
 * CONSUMER
 * Sell those cars.
 * This function is not currently thread safe. You will need
 * to introduce a critical section in such a way that we
 * do not compromise the queue nor sell the same car twice.
 **********************************************************/
void * consumer(void * input)
{
   consumerItem * conInput = (consumerItem *)input;

   // collect our sales history into one string
   stringstream sout;
   sout << conInput->retailer << ":\n";
   
   // continue while there are still customers floating around
   while (!(productionComplete && inventory->empty()))
   {
      // the car to sell
      Car car;

      // it takes time to sell our car
      usleep(rand() % 150000);

      // do we have one to sell
      // CRITICAL SECTION BEGIN
      pthread_mutex_lock(&idLock);
      if (!inventory->empty())
      {
         car = inventory->sellCar();
         sout << "\t" << car << endl;
      }
      pthread_mutex_unlock(&idLock);
      sem_post(&semaphore);
      // CRITICAL SECTION END
   }

   // done
   conInput->message = new string(sout.str());

   pthread_exit(NULL);
}

/*********************************************
 * GET NUMBER
 * Generic prompt function with error checking
 ********************************************/
int getNumber(const char * prompt, int max)
{
   int value = -1;
   assert(cin.good());       // better not already be in error mode
   assert(prompt != NULL);   // the prompt better be a valid c-string
   assert(max > 0);          // it better be possible for valid data to exist

   // continue prompting until we have valid data
   while (value <= 0 || value > max)
   {
      cout << prompt;
      cin  >> value;

      // if the user typed a non-integer value, reprompt.
      if (cin.fail())
      {
         cin.clear();
         cin.ignore();
         cout << "Error: non-integer value specified\n";
      }

      // if the user typed a valid outside the range, reprompt
      else if (value <= 0 || value > max)
         cout << "Error: value must be between 1 and "
              << max
              << endl;
   }

   return value;
}
