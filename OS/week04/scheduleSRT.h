/***********************************************************************
* Component:
*    Scheduler SRT
* Author:
*    your name
* Summary: 
*    This is the base-class that enables various schedule algorithms
*    to simulate CPU Scheduling
************************************************************************/

#ifndef SCHEDULER_SRT
#define SCHEDULER_SRT

#include "schedule.h"


/****************************************************
 * SRT
 * The Shortest Remaining Time Scheduler
 ***************************************************/
class SchedulerSRT : public Disbatcher
{
public:
   SchedulerSRT() : Disbatcher() {}

   // a new process has just been executed
   void startProcess(int pid)
   {
      int myTime = processes[pid].getServiceTime();

      if (!readyQueue.empty())
      {
         for (std::deque<int>::iterator i = readyQueue.begin(); i != readyQueue.end(); i++)
         {
            int yourTime = processes[*i].getServiceTime();
            if (yourTime >= myTime)
            {
               readyQueue.insert(i, pid);
               break;
            }
         }
      }
      else
      {
         readyQueue.push_front(pid);
      }
   }
      
   // execute one clock cycle. Here we will determine whether we need
   // to switch to a new process
   bool clock()
   {
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
            readyQueue.pop_front();
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
\

  private:
     std::deque <int> readyQueue;   
};

#endif // SCHEDULE_SRT
