#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>

#include "printers.h"

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

//**************** printerType *******************

printerType::printerType()
{
   status = "free";
   maintTime = 0;
   remainingPages = 0;
   printerSpeed = 0;
   totalPagesPrinted = 0;
   currentPagesPrinted = 0;
   numJobsCompleted = 0;
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

void printerType::setToMaintenence()
{
   status = "maintenence";
}

void printerType::setToFailed()
{
   status = "failed";
}

string printerType::returnStatus()
{
   return status;
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

void printerType::setCost(int cost)
{
   printerCost = cost;
}

double printerType::getPrinterCost()
{
   return printerCost;
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

int printerType::getCurrentPrintJobWaitTime() const
{
   return currentPrintJob.getWaitingTime();
}

void printerType::setMaintTime(int maintenenceTime)
{
   maintTime = maintenenceTime;
}

int printerType::getMaintTime()
{
   return maintTime;
}

void printerType::decreaseMaintTime()
{
   maintTime--;
}

void printerType::addTotalPages(int numPages)
{
   currentPagesPrinted += numPages;
   totalPagesPrinted += numPages;
}

int printerType::getTotalPagesPrinted()
{
   return totalPagesPrinted;
}

int printerType::getCurrentPagesPrinted()
{
   return currentPagesPrinted;
}

void printerType::resetCurrentPagesPrinted()
{
   currentPagesPrinted = 0;
}

void printerType::increaseJobsCompleted()
{
   numJobsCompleted++;
}

int printerType::getTotalJobsCompleted()
{
   return numJobsCompleted;
}

void printerType::increaseTotalTimePrinting()
{
   totalTimePrinting++;
}

int printerType::getTotalPrintingTime()
{
   return totalTimePrinting;
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

int printerListType::assignRandomPrinter()
{
   int freePrinters[numOfPrinters];
   
   for(int i=0; i<numOfPrinters; i++){
      if(printers[i].isFree())
         freePrinters[i] = 1;
      else
         freePrinters[i] = 0;
   }
    
   int r = rand() % numOfPrinters;
   while(freePrinters[r] != 1)
      r = rand() % numOfPrinters;

   return r;
}

int printerListType::getNumJobsCompleted() const
{
   return numJobsCompleted;
}

int printerListType::getTotalTimeBusy(int printerID)
{
   return printers[printerID].getTotalPrintingTime();
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

int printerListType::totalPagesPrintedByPrinter(int printerNum)
{
   return printers[printerNum].getTotalPagesPrinted();
}

int printerListType::totalJobsCompletedByPrinter(int printerNum)
{
   return printers[printerNum].getTotalJobsCompleted();
}

void printerListType::checkFailure(ostream &out, double percentFail, int offlineTime)
{
   double failure = percentFail/100.0;

   for(int i=0; i<numOfPrinters; i++){
      if(printers[i].returnStatus() == "busy"){
         int rNum = rand() % 10;
         double rDecimal = rNum/9.0;      
         if(rDecimal < failure){
            printers[i].setToFailed();
            printers[i].setMaintTime(offlineTime);
            out<<"Printer number "<<i+1<<" failed."<<endl;
            break;
         }
      }else if(printers[i].returnStatus() == "failed" && 
				printers[i].getMaintTime() > 0){
         printers[i].decreaseMaintTime();
         out<<"Printer number "<<i+1<<" failed and has "
	     <<printers[i].getMaintTime()<<" minutes left."<<endl;
         if(printers[i].getMaintTime() == 0)
            printers[i].setBusy();
      }
   }
}
   
void printerListType::checkMaintenence(ostream &out, int numMaintPages, int maintenenceTime)
{
   for(int i=0;i<numOfPrinters;i++){
      if(printers[i].isFree()){
         if(printers[i].getCurrentPagesPrinted() >= numMaintPages){
            out<<"Total pages printer by printer "<<i+1<<" is "
		<<printers[i].getCurrentPagesPrinted()<<endl;
            printers[i].setToMaintenence();
            printers[i].setMaintTime(maintenenceTime);
            printers[i].resetCurrentPagesPrinted();
            out<<"Printer number "<<i+1<<" is under maintenence."<<endl;
         }
      }else if(printers[i].returnStatus() == "maintenence" && 
			printers[i].getCurrentPagesPrinted() == 0){
         if(printers[i].getMaintTime() > 0){  
            printers[i].decreaseMaintTime();
            if(printers[i].getMaintTime() == 0){
               printers[i].setFree();
               out<<"Printer Number "<<i+1<<" has finished maintenence."<<endl;
            }else
	    out<<"Printer number "<<i+1<<" has "<<printers[i].getMaintTime()
		<<" min left under maintenence."<<endl;
         }
      }
   }
}

void printerListType::setPrinterBusy(int printerID,
                                     printJobType cPrintJob,
                                     int pTime)
{
    printers[printerID].setBusy();
    printers[printerID].setPrinterSpeed(pTime);
    printers[printerID].setCurrentPrintJob(cPrintJob);
    printers[printerID].setRemainingPages(cPrintJob.getNumberOfPages());
    printers[printerID].addTotalPages(cPrintJob.getNumberOfPages());
}

void printerListType::updatePrinters(ostream& outFile)
{
    int i;

    for (i = 0; i < numOfPrinters; i++)
        if (!printers[i].isFree() && printers[i].getMaintTime() == 0)
        {
            printers[i].increaseTotalTimePrinting();
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
                printers[i].increaseJobsCompleted();
            }
        }
}

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
