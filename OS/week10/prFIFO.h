/***********************************************************************
* Component:
*    Page Replacement FIFO
* Author:
*    <your name here>
* Summary: 
*    This is the DERRIVED class to implement the FIFO algorithm
************************************************************************/

#ifndef PR_FIFO
#define PR_FIFO

#include "pr.h"   // for the PageReplacementAlgorithm base-class

#include <iostream>
using namespace std;

/****************************************************
 * FIFO
 * The first-in, first-out page replacement algorithm
 ***************************************************/
class PageReplacementFIFO : public PageReplacementAlgorithm
{
public:
   /*****************************************************
    * CONSTRUCTOR
    * initialize the data structures specific to FIFO
    *****************************************************/
   PageReplacementFIFO(int numSlots) : PageReplacementAlgorithm(numSlots)
   {   }

   /****************************************************
    * RUN
    * Implement the Basic algorithm here. Thus function will get
    * called several times, each time requesting "pageNumber"
    * from memory. You are to assign that page to a "pageFrame"
    * and then call the base-class to record the results.
    ***************************************************/
   void run(int pageNumber)
   {
       // is pageNumber currently being used?
       for (int i = 0; i < getNumSlots(); i++)
           if (pageFrame[i] == pageNumber)
           {
               PageReplacementAlgorithm::record(pageNumber, false /*no fault*/);
               return;
           }
      

      // for a page fault
       if (fifoList.empty() || (fifoList.size() < getNumSlots()))
       {
           fifoList.push_back(pageNumber);
           
           for (int i = 0; i < getNumSlots(); i++)
               if (pageFrame[i] == -1)
               {
                   pageFrame[i] = pageNumber;
                   break;
               }
           //cout << pageFrame.size() << endl;
           PageReplacementAlgorithm::record(pageNumber, true /*page fault*/);
           return;
       }
       else
       {
           int iNextVictim = fifoList.front();
           fifoList.pop_front();
           fifoList.push_back(pageNumber);

           for (int i = 0; i < getNumSlots(); i++)
               if (pageFrame[i] == iNextVictim)
               {
                   pageFrame[i] = pageNumber;
                   PageReplacementAlgorithm::record(pageNumber, true /*page fault*/);
                   return;
               }
       }
   }

private:
    list<int> fifoList;
};

#endif // PR_BASIC
