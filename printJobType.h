/* Names: B. Hamrick, T. Ferguson, R. Stingel
   Date: 3.1.16
   Class: CSC 3710

   This is a header file contaning the printJobType class.
*/

#ifndef PRINTJOBTYPE_H
#define PRINTJOBTYPE_H

#include <fstream>
#include <string>
#include <queue>

using namespace std;

//**************** printJobType  ****************

class printJobType
{
public:
   printJobType(int jobNum = 0, int arrvTime = 0, int pageNum = 0, int wTime = 0);
    //Constructor to initialize the instance variables
    //according to the parameters
    //If no value is specified in the object declaration,
    //the default values are assigned.
    //Postcondition: jobNumber = jobNum;
    //               arrivalTime = arrvTime;
    //               numberOfPages = pageNum;
    //               waitTime = wTime;

   void setPrintJobInfo(int jobN = 0, int inTime = 0, int pageN = 0, int wTime = 0);
    //Function to initialize the instance variables.
    //Instance variables are set according to the parameters.
    //Postcondition: jobNumber = jobN;
    //               arrivalTime = inTime;
    //               numberOfPages = pageN;
    //               waitTime = wTime;

   int getJobNumber() const;
    //Function to return the job number.
    //Postcondition: The value of jobNumber is returned.

   int getArrivalTime() const;
    //Function to return the arrival time of a job.
    //Postcondition: The value of arrivalTime is returned.

   int getNumberOfPages() const;
    //Function to return the number of pages for a print job.
    //Postcondition: The value of numberOfPages is returned.

   int getWaitingTime() const;
    //Function to return the waiting time of each print Job.
    //Postcondition: the value of waitingTime is returned.

   void incrementWaitingTime();
    //Function to increment the waiting time of the print job
    //Postcondition: waitTime++

   void setWaitingTime(int time);
    //Function to set the waiting time of the print job
    //Postcondition: waitTime = time;

private:
   int jobNumber;
   int arrivalTime;
   int numberOfPages;
   int waitTime;
};

#endif
