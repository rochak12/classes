/***********************************************************************
* Component:
*    Scheduler RR
* Author:
*    your name
* Summary:
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef SCHEDULER_RR
#define SCHEDULER_RR

#include "schedule.h"
#include <deque>
using namespace std;

/****************************************************
 * RR
 * The Round Robin scheduler
 ***************************************************/
class SchedulerRR : public Disbatcher
{
public:
	SchedulerRR(int q) : Disbatcher(),
		timeQuantaDuration(q), passedTime(0)
	{
		queueIterator = readyQueue.begin();
	}

	// a new process has just been executed
	void startProcess(int pid)
	{
		readyQueue.push_back(pid);
	}

	// execute one clock cycle. Here we will determine whether we need
	// to switch to a new process
	bool clock()
	{
		if (this->pidCurrent == PID_NONE)
		{
			if (readyQueue.empty())
			{
				return Disbatcher::clock();
			}

			queueIterator = readyQueue.begin();
			pidCurrent = *readyQueue.begin();
			passedTime = 0;
		}

		if (processes[pidCurrent].isDone())
		{
			passedTime = 0;

			readyQueue.erase(queueIterator);
			if (!readyQueue.empty())
			{
				pidCurrent = nextProcess();
			}
			else
			{
				pidCurrent = PID_NONE;
			}
		}


		if (passedTime >= timeQuantaDuration)
		{
			passedTime = 1;

			//std :: cout << "front of queue" << readyQueue.front() << "currentPid" << pidCurrent << endl;

			if (!readyQueue.empty())
			{
				pidCurrent = nextProcess();
			}
			else
			{
				pidCurrent = PID_NONE;
			}
		}
		else
		{
			passedTime += 1;
		}
		return Disbatcher::clock();
	}

	int nextProcess()
	{
		queueIterator++;
		if (queueIterator == readyQueue.end())
		{
			queueIterator = readyQueue.begin();
		}
		return *queueIterator;
	}


private:
	int timeQuantaDuration;
	int passedTime;
	std::deque<int>::iterator queueIterator;
	std::deque<int> readyQueue;
};

#endif // SCHEDULE_RR








