/***********************************************************************
 * Program:
 *    Lab 06, Producer and Consumer
 * Author:
 *    Rochak Kunwar
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
#include "cars.h"        // for everything dealing with McLaren Cars

using namespace std;
 
// This variable represents the shared memory between the parent thread
// and all the children. Recall from the reading how the main way for
// threads to communicate is through shared memory. This shared memory
// needs to be global.
bool productionComplete = false;

void     producer(const char *z);//,
                  //Inventory & inventory);   // you may need to change this
string * consumer(const char *,
                  Inventory & inventory);   // you may need to change this also

int getNumber(const char * prompt, int max);

struct InventoryandCar      //This is for defining the location
{                       //in the destination matrix
	Inventory inventory;
   Car car;
   int serialNumberNext;
};

Inventory inventory;// = new Inventory();
static int serialNumberNext = 0;


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

   // determine how many producer and consumer threads
   int numProducer = getNumber("How many models?    ", numModels());
   int numConsumer = getNumber("How many retailers? ", numRetailers());

   // produce the cars. Note that this code needs to change. We will
   // need to launch one thread per producer here
 
   for (int i = 0; i < numProducer; i++)
      producer(models[i]);//, inventory);

   // sell the cars. Note that this code also needs to change.
   cout << "\nThe cars sold from the various retailers:\n\n";
   for (int i = 0; i < numConsumer; i++)
   {
      string * pResults;
      pResults = consumer(retailers[i], inventory);
      cout << *(string *)pResults << endl;
      delete (string *)pResults;
   }

   // final report
   cout << "Maximum size of the inventory: "
        << inventory.getMax()
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
 void * ProducerThread(void *p)
 {
    Car * car = ( Car*)p;
   while (!productionComplete)
   {
      // now that we decided to build a car, it takes some time
      usleep(rand() % 150000);
      // add the car to our inventory if we still need to
      if (serialNumberNext < NUM_CARS)
      {
         car->serialNumber = ++serialNumberNext;
         inventory.makeCar(*car);
      }
   }
 }

void producer(const char * model)//, Inventory & inventory)
{

   // a car to be added to the inventory
   Car *car = new Car;
   car->model = model;

   pthread_t threads[NUM_CARS];
   for (int i = 0 ; i < NUM_CARS; i++)
   {
      pthread_create(threads + i, NULL, ProducerThread, (void*)car);
   }
   // continue as long as we still ned to produce cars in this run
   // usleep(rand() % 100);

   // all done!
   productionComplete = true;

   for (int i =0 ; i < NUM_CARS ; i++)
      pthread_join(threads[i], NULL);
}

/***********************************************************
 * CONSUMER
 * Sell those cars.
 * This function is not currently thread safe. You will need
 * to introduce a critical section in such a way that we
 * do not compromise the queue nor sell the same car twice.
 **********************************************************/
string * consumer(const char * retailer, Inventory & inventory)
{
   // collect our sales history into one string
   stringstream sout;
   sout << retailer << ":\n";
   
   // continue while there are still customers floating around
   while (!(productionComplete && inventory.empty()))
   {
      // the car to sell
      Car car;

      // it takes time to sell our car
      usleep(rand() % 150000);

      // do we have one to sell
      if (!inventory.empty())
      {
         car = inventory.sellCar();
         sout << "\t" << car << endl;
      }
   }

   // done
   string * report = new string(sout.str());
   return report;
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
