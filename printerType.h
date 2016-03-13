/* Names: B. Hamrick, T. Ferguson, R. Stingel
   Date: 3.1.16
   Class: CSC 3710

   This is a header file contaning the printerType class.
*/

#ifndef PRINTERTYPE_H
#define PRINTERTYPE_H

#include <fstream>
#include <string>
#include <queue>
#include "printJobType.h"

using namespace std;

//****************** printerType *******************
class printerType
{
public:
   printerType();
      //Default constructor
      //Sets the values of the instance variables to their default
      //values.
      //Postcondition: currentPrinter is initialized by its
      //               default constructor; status = "free"; and
      //               the printer speed is initialized to 0 and
      //               printerSpeed = pSpeed

   bool isFree() const;
      //Function to determine if the printer is free.
      //Postcondition: Returns true if the printer is free,
      //               otherwise returns false.

   void setBusy();
      //Function to set the status of the printer to busy.
      //Postcondition: status = "busy";

    void setFree();
      //Function to set the status of the printer to "free".
      //Postcondition: status = "free";

    void setToMaintenence();
      //Function to set the status of the printer to
      //maintenence
      //Postcondition: status = "maintenence"

    void setToFailed();
      //Function to set the status of the printer to "failed"
      //Postcondition: status = "failed";

    string returnStatus();
      //Function to return the current status of the printer
      //Postcondition: the status of the current printer
      //               is returned.

    void setRemainingPages(int p);
      //Function to set the printer speed according to the
      //parameter p.
      //Postcondition: printerSpeed = p;

    int getRemainingPrintPages() const;
      //Function to return the remaining print pages.
      //Postcondition: The value of remainingPages is returned.

    void decreasePrintPages(int p);
      //Function to decrease the amount of pages to print by p.
      //Postcondition: remainingPages -= p;

    void setPrinterSpeed(int pSpeed);
       //Function to set the printer speed
       //Postcondition: printerSpeed = pSpeed.

    int getPrinterSpeed();
      //Function to return the speed of the printer
      //Postcondition: The value of printerSpeed is returned.

    void setCurrentPrintJob(printJobType cPrintJob);
      //Function to set the info of the current printer
      //according to the parameter cPrinter.
      //Postcondition: currentPrintJob = cPrintJob;

    int getCurrentPrintJobNumber() const;
      //Function to return the printer number of the current
      //printer.
      //Postcondition: The value of printer Number of the
      //               current printer is returned.

    int getCurrentPrintJobArrivalTime() const;
      //Function to return the arrival time of the current
      //printer.
      //Postcondition: The value of arrivalTime of the current
      //               print job is returned.

    int getCurrentPrintJobWaitTime() const;
      //Function to return the waiting time of the current printer
      //Postcondition: the value of waitingTime of the current
      //                print Job is returned.

    void setMaintTime(int maintenenceTime);
      //Function to set the maintenence time of a printer
      //Postcondition: maintTime = maintenenceTime

    int getMaintTime();
      //Function to return the remaining maintenence time
      //Postcondition: the value of maintTime is returned.

    void decreaseMaintTime();
      //Function to decrease the remaining maintenence time
      //Postcondition: maintTime--

    void addTotalPages(int numPages);
      //Function to add the total number of pages printed by printer
      //Postcondition: totalPagesPrinted += numPages

    int getTotalPagesPrinted();
       //Function to return the total number of pages printed
       //Postcondition: totalPagesPrinted is returned

    int getCurrentPagesPrinted();
      //Function to return the current amount of pages printed
      //Postcondition: the value of currentPagesPrinted is returned.

    void resetCurrentPagesPrinted();
      //Function to reset the number of pages a printer has printed
      //Postcondition: totalPagesPrinted = 0

    void checkForFailure(double percentFail, int offlineTime);
      //Function to check to see if the printer failed while
      //printing its current job
      //Postcondition: if the printer fails then status="failed
      //               and the printer is offline for offlineTime
      //               minutes.

    void increaseJobsCompleted();
      //Function to increase the number of jobs completed
      //Postcondition: numOfJobsCompleted++;

    int getTotalJobsCompleted();
      //Function to return the value of the number of jobs
      //completed by this printer
      //Postcondition: value of numJobsCompleted is returned

    void increaseTotalTimePrinting();
      //Function to increase the total time spent printing
      //of a specific printer
      //Postcondition: totalTimePrinting++

    int getTotalPrintingTime();
      //Function to return the total time spent printing
      //Postcondition: value of totalTimePrinting is returned

private:
   printJobType currentPrintJob;
   string status;
   int maintTime;
   int remainingPages;
   int printerSpeed;
   int totalPagesPrinted;
   int currentPagesPrinted;
   int numJobsCompleted;
   int totalTimePrinting;
};

#endif
