#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>

#include "printJobQueueType.h"

using namespace std;

//**************** printJobQueue ****************

printJobQueueType::printJobQueueType()
                   :queue<printJobType>()
{
   totalPagesPrinted = 0;
   totalNumJobs = 0;
}

void printJobQueueType::updatePrintJobQueue()
{
   printJobType printJob;

   printJob.setWaitingTime(-1);
   int wTime = 0;

   push(printJob);

   while(wTime != -1)
   {
      printJob = front();
      pop();

      wTime = printJob.getWaitingTime();
      if(wTime == -1)
         break;
      printJob.incrementWaitingTime();
      push(printJob);
   }
}

void printJobQueueType::addWaitTime(int wTime)
{
   waitTime += wTime;
}

int printJobQueueType::returnCurrentTierWaitTime()
{
   return waitTime;
}

void printJobQueueType::addNumPages(int numPages)
{
   totalPagesPrinted += numPages;
}

void printJobQueueType::increaseNumJobs()
{
   totalNumJobs++;
}

int printJobQueueType::returnPagesPrinted()
{
   return totalPagesPrinted;
}

int printJobQueueType::returnNumJobsPerformed()
{
   return totalNumJobs;
}
