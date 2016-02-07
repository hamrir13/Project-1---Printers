#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>

#include "printers.h"

using namespace std;


//***************** printJobType *****************

void printJobType::setPrintJobInfo(int jobN, int inTime, int pageN)
{
   jobNumber = jobN;
   arrivalTime = inTime;
   numberOfPages = pageN;
}

printJobType::printJobType(int jobN, int inTime, int pageN)
{
   setPrintJobInfo(jobN,inTime,pageN);
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

/*
int printJobType::getPrinterSpeed() const
{
   return printerSpeed;
}
      
Note to Bobby:
*  do we need the following?
*     int customerType::getWaitingTime() const
*     {
*        return waitingTime;
*     }
*
*     void customerType::incrementWaitingTime()
*     {
*         waitingTime++;
*     }
*
*     void customerType::setWaitingTime(int time)
*     {
*         waitingTime = time;
*     }
*
*     int customerType::getTransactionTime() const
*     {
*         return transactionTime;
*     }
*/

//**************** printerType *******************

printerType::printerType()
{
   status = "free";
   remainingPages = 0;
   printerSpeed = 0;
}

bool printerType::isFree() const
{
   return (status == "free");
}

void printerType::setBusy()
{
   status = "busy";
}

void printerType::setFree()
{
   status = "free";
}

void printerType::setRemainingPages(int p)
{
   remainingPages = p;
}

int printerType::getRemainingPrintPages() const
{
   return remainingPages;
}

void printerType::decreasePrintPages(int p)
{
   remainingPages -= p;
}

void printerType::setPrinterSpeed(int pSpeed)
{
   printerSpeed = pSpeed;
}

int printerType::getPrinterSpeed()
{
   return printerSpeed;
}

void printerType::setCurrentPrintJob(printJobType cPrintJob)
{
   currentPrintJob = cPrintJob;
}

int printerType::getCurrentPrintJobNumber() const
{
   return currentPrintJob.getJobNumber();
}

int printerType::getCurrentPrintJobArrivalTime() const
{
   return currentPrintJob.getArrivalTime();
}

//***************** printerListType ***************

printerListType::printerListType(int num)
{
   numOfPrinters = num;
   printers = new printerType[num];
   numJobsCompleted = 0;
}

printerListType::~printerListType()
{
   delete [] printers;
}

int printerListType::getFreePrinterID() const
{
   int printerID = -1;

   int i;

   for (i = 0; i < numOfPrinters; i++)
      if (printers[i].isFree())
      {
         printerID = i;
         break;
      }

   return printerID;
}

int printerListType::getNumJobsCompleted() const
{
   return numJobsCompleted;
}

int printerListType::getNumberOfBusyPrinters() const
{
    int busyPrinters = 0;

    int i;

    for (i = 0; i < numOfPrinters; i++)
        if (!printers[i].isFree())
            busyPrinters++;

    return busyPrinters;
}

void printerListType::setPrinterBusy(int printerID,
                                     printJobType cPrintJob,
                                     int pTime)
{
    printers[printerID].setBusy();
    printers[printerID].setPrinterSpeed(pTime);
    printers[printerID].setCurrentPrintJob(cPrintJob);
    printers[printerID].setRemainingPages(cPrintJob.getNumberOfPages());
}

void printerListType::updatePrinters(ostream& outFile)
{
    int i;

    for (i = 0; i < numOfPrinters; i++)
        if (!printers[i].isFree())
        {
            printers[i].decreasePrintPages(printers[i].getPrinterSpeed());

            if (printers[i].getRemainingPrintPages() <= 0)
            {
                outFile << "From printer number  " << (i + 1)
                        << " task number "
                        << printers[i].getCurrentPrintJobNumber()
                        << "\n     is now completed."
                        << endl;
                printers[i].setFree();
		numJobsCompleted++;
            }
        }
}

//**************** printJobQueue ****************

printJobQueueType::printJobQueueType()
		   :queue<printJobType>()
{
}


