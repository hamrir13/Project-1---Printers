/* Names: B. Hamrick, T. Ferguson, R. Stingel
   Date: 3.1.16
   Class: CSC 3710

   This is a header file contaning the printJobQueueType class
*/

#ifndef PRINTJOBQUEUETYPE_H
#define PRINTJOBQUEUETYPE_H

#include <fstream>
#include <string>
#include <queue>
#include "printJobType.h"

using namespace std;

//**************** printJobQueueType ******************

class printJobQueueType: public queue<printJobType>
{
public:
   printJobQueueType();
      //Constructor
      //Postcondition: The vector is initialized according to
      //               the parameter size. The value of size
      //               is passed to the constructor of a vector.

   void updatePrintJobQueue();
      //Function to increment the waiting time of each
      //print job in the queue by one time unit.

   void addWaitTime(int wTime);
      //Function to increase the waitTime of a tier
      //Postcondition: The current tier's wait time will increase
      //               based on printJobs waitTime

   int returnCurrentTierWaitTime();
      //Function to return the wait time of the current tier
      //Postcondition: value of waitTime is returned

   void addNumPages(int numPages);
      //Function to add the number of pages printed
      //Postcondition: totalPagesPrinted += numPages

   void increaseNumJobs();
      //Function to increase the number of jobs the tier performed
      //Postcondition: totalNumJobs++;

   int returnPagesPrinted();
      //Function to return the number of pages printed
      //Postcondition: value totalPages printed is retured

   int returnNumJobsPerformed();
      //Function to return the number of jobs completed
      //Postcondition: value of totalNumJobs is returned

private:
   int totalNumJobs;
   int totalPagesPrinted;
   int waitTime;
};

#endif
