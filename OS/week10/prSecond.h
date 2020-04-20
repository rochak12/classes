/***********************************************************************
* Component:
*    Page Replacement Second Chance
* Author:
*    Rochak Kunwar
* Summary:
*    This is the DERRIVED class to implement Second
************************************************************************/

#ifndef PR_SECOND
#define PR_SECOND

#include "pr.h"   // for the PageReplacementAlgorithm base-class

#include <iostream>
using namespace std;

/****************************************************
 * Second Chance
 * The least-recently-used Approximation page replacement
 * algorithm known as Second Chance
 ***************************************************/
class PageReplacementSecond : public PageReplacementAlgorithm
{
public:
    /*****************************************************
     * CONSTRUCTOR
     * initialize the data structures specific to Second
     *****************************************************/
    PageReplacementSecond(int numSlots) : PageReplacementAlgorithm(numSlots)
    {   }

    /****************************************************
     * RUN
     * Implement the LRU algorithm here. Thus function will get
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
                list<int>::iterator it = fifoList.begin();
                int j = 0;
                while (*it != pageNumber)
                {
                    j++;
                    it++;
                }
                list<int>::iterator jt = checkBit.begin();
                for (int i = 0; i < fifoList.size(); i++)
                {
                    if (i == j)
                        *jt = 1;
                    jt++;
                }

                PageReplacementAlgorithm::record(pageNumber, false /*no fault*/);
                return;
            }


        // for a page fault
        if (fifoList.empty() || (fifoList.size() < getNumSlots()))
        {
            fifoList.push_back(pageNumber);
            checkBit.push_back(1);

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
            while (checkBit.front() != 0)
            {
                int iNextVictim = fifoList.front();
                fifoList.pop_front();
                checkBit.pop_front();
                fifoList.push_back(iNextVictim);
                checkBit.push_back(0);
            }

            int iNextVictim = fifoList.front();
            fifoList.pop_front();
            checkBit.pop_front();
            fifoList.push_back(pageNumber);
            checkBit.push_back(1);

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
    list<int> checkBit;
};

#endif // PR_SECOND
