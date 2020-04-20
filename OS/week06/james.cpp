/***********************************************************************
* Program:
* Lab 06, Producer and Consumer
* Author:
* James Carl
* Summary:
* This program will allow us to simulate the production run
* at McLaren Cars. It would be cool if it simulated the cars
* themselves, but that might be an assignment for another day
*
* Note that you must compile this with the -lpthread switch:
* g++ -lpthread lab06.cpp
************************************************************************/

#include <iostream> // for COUT
#include <cassert> // for ASSERT
#include <string> // for STRING
#include <sstream> // for STRINGSTREAM
#include <queue> // for QUEUE
#include <vector> // for VECTOR
#include <ctime> // for time(), part of the random process
#include <unistd.h> // for usleep()
#include <stdlib.h> // for rand() and srand()
#include <semaphore.h> // for SEM_T and related methods
#include "cars.h" // for everything dealing with McLaren Cars

using namespace std;

// Used to provide arguments to producers.
struct ProducerArgs
{
	const char* name;
	Inventory* inventory;
	sem_t* inventoryLock;
};

// Used to provide arguments to consumer and provide a way to return results.
struct ConsumerArgs
{
	string result;
	const char* name;
	Inventory* inventory;
	sem_t* inventoryLock;
	bool producerActive;
};

void* producer(void* args_p); // you may need to change this
void* consumer(void* args_p); // you may need to change this also

int getNumber(const char* prompt, int max);

/***********************************************
* MAIN
* This will serve to prompt the user for the number
* of models and the number of retailers. It will then
* begin the simulation
***********************************************/
int main(int argc, char** argv)
{
	// set up the random number generator
	srand(argc == 1 ? time(NULL) : (int)argv[1][1]);

	// determine how many producer and consumer threads
	int numProducer = getNumber("How many models? ", numModels());
	int numConsumer = getNumber("How many retailers? ", numRetailers());

	// Our inventory is shared, so it must be locked.
	Inventory inventory;
	sem_t inventoryLock;
	sem_init(&inventoryLock, 0, 1);

	vector<ConsumerArgs> consumerArgs;
	vector<pthread_t> consumers;

	consumerArgs.resize(numConsumer);
	consumers.resize(numConsumer);

	// Create consumers, who sell the cars.
	// We create them first so they can start consuming as soon as the
	// producers start producing.
	cout << "\nThe cars sold from the various retailers:\n\n";
	for (int i = 0; i < numConsumer; i++)
	{
		// We the parent thread will keep ownership of the arguments, because
		// we need to access a value returned through this struct. We need to
		// make sure that the args struct is alive for longer than the consumer
		// thread. This is why we must joint he thread before we can safely
		// delete this struct.
		ConsumerArgs& args = consumerArgs[i];
		args.name = retailers[i];
		args.inventory = &inventory;
		args.inventoryLock = &inventoryLock;
		args.producerActive = true;
		pthread_create(&consumers[i], NULL, consumer, &args);
	}

	// Create producers.
	// This list could get big, so we're allocating it on the heap.
	vector<pthread_t> producers;
	producers.resize(numProducer);
	for (int i = 0; i < numProducer; i++)
	{
		// Args are safe on the heap for transfer. Ownership is given to the thread.
		// The thread will delete the args struct when safe to do so.
		ProducerArgs* args = new ProducerArgs;
		args->name = models[i];
		args->inventory = &inventory;
		args->inventoryLock = &inventoryLock;
		pthread_create(&producers[i], NULL, producer, args);

		// When we have 4 producers and 1 consumer, we just can't keep the inventory
		// cap below 7. We can only run one at a time.
		pthread_join(producers[i], NULL);
	}

	// Now terminate all the consumers, in order, and print their result.
	for (int i = 0; i < numConsumer; i++)
	{
		ConsumerArgs& args = consumerArgs[i];
		args.producerActive = false; // We know it has to be done by this point.
		pthread_join(consumers[i], NULL);
		cout << args.result << endl;
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
void* producer(void* args_p)
{
	ProducerArgs* args = reinterpret_cast<ProducerArgs*>(args_p);
	const char* model = args->name;
	Inventory& inventory = *args->inventory;
	sem_t* inventoryLock = args->inventoryLock;
	delete args; // We have taken ownership of the args and must delete them.

	static int serialNumberNext = 0;

	// a car to be added to the inventory
	Car car;
	car.model = model;

	// continue as long as we still need to produce cars in this run
	while (serialNumberNext < NUM_CARS)
	{
		// now that we decided to build a car, it takes some time
		usleep(rand() % 150000);

		// add the car to our inventory if we still need to
		if (serialNumberNext < NUM_CARS)
		{
			car.serialNumber = ++serialNumberNext;

			sem_wait(inventoryLock);
			inventory.makeCar(car);
			sem_post(inventoryLock);
		}
	}

	return nullptr;
}

/***********************************************************
* CONSUMER
* Sell those cars.
* This function is not currently thread safe. You will need
* to introduce a critical section in such a way that we
* do not compromise the queue nor sell the same car twice.
**********************************************************/
void* consumer(void* args_p)
{
	ConsumerArgs* args = reinterpret_cast<ConsumerArgs*>(args_p);
	const char* retailer = args->name;
	Inventory& inventory = *args->inventory;
	sem_t* inventoryLock = args->inventoryLock;

	// collect our sales history into one string
	stringstream sout;
	sout << retailer << ":\n";

	// continue while there are still customers floating around
	while (args->producerActive || !inventory.empty())
	{
		// the car to sell
		Car car;
		int numCars = 0;

		// Grab all the cars you can.
		sem_wait(inventoryLock);
		while (!inventory.empty())
		{
			car = inventory.sellCar();
			sout << "\t" << car << endl;

			numCars += 1;
		}
		sem_post(inventoryLock);

		while (numCars > 0)
		{
			// it takes time to sell our cars
			usleep(rand() % 150000);
			numCars -= 1;
		}
	}

	// done
	args->result = sout.str();
	return nullptr;
}

/*********************************************
* GET NUMBER
* Generic prompt function with error checking
********************************************/
int getNumber(const char* prompt, int max)
{
	int value = -1;
	assert(cin.good()); // better not already be in error mode
	assert(prompt != NULL); // the prompt better be a valid c-string
	assert(max > 0); // it better be possible for valid data to exist

	// continue prompting until we have valid data
	while (value <= 0 || value > max)
	{
		cout << prompt;
		cin >> value;

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