/***********************************************************************
* Component:
*    Scheduler SJF
* Author:
*    your name
* Summary: 
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef SCHEDULER_SJF
#define SCHEDULER_SJF

#include "schedule.h"


/****************************************************
 * SJF
 * The Shortest Job First scheduler
 ***************************************************/
class SchedulerSJF : public Disbatcher
{
public:
   SchedulerSJF() : Disbatcher() {}

  // a new process has just been executed
   void startProcess(int pid)
   {
      readyQueue.push(pid);
   }
      
   // execute one clock cycle. Here we will determine whether we need
   // to switch to a new process
   bool clock()
   {
      std :: cout << "front of queue" << readyQueue.front() << "currentPid" << pidCurrent << endl;
      // is the current process finished or is there no process selected?
      if (pidCurrent == PID_NONE ||
          processes[pidCurrent].isDone())
      {
         // if there is something on the ready queue, then take the front
         // element. When we do this, we remove the item from the ready queue
         // and place it in pidCurrent.
         if (readyQueue.size())
         {
            pidCurrent = readyQueue.front();
            readyQueue.pop();
            assert(pidCurrent >= 0 && pidCurrent <= processes.size());
         }
         // if there is nothing in the ready queue, then set pidCurrent
         // to none. This means nothing is currently executing in the queue
         else
            pidCurrent = PID_NONE;
      }

      // call the base-class which will handle a variety of housekeeping chores
      return Disbatcher::clock();
   }

      

  private:
   int timeQuantaDuration;
     std::queue <int> readyQueue;
};
#endif // SCHEDULE_SJF
