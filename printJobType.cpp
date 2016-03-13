#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>

#include "printJobType.h"

using namespace std;


//***************** printJobType *****************

void printJobType::setPrintJobInfo(int jobN, int inTime, int pageN, int wTime)
{
   jobNumber = jobN;
   arrivalTime = inTime;
   numberOfPages = pageN;
   waitTime = wTime;
}

printJobType::printJobType(int jobN, int inTime, int pageN, int wTime)
{
   setPrintJobInfo(jobN,inTime,pageN,wTime);
}

int printJobType::getJobNumber() const
{
    return jobNumber;
}

int printJobType::getArrivalTime() const
{
   return arrivalTime;
}

int printJobType::getNumberOfPages() const
{
   return numberOfPages;
}

int printJobType::getWaitingTime() const
{
   return waitTime;
}

void printJobType::incrementWaitingTime()
{
   waitTime++;
}

void printJobType::setWaitingTime(int time)
{
   waitTime = time;
}
