#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>

#include "printerListType.h"

using namespace std;

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
         out<<"Printer number "<<i+1<<" has "
             <<printers[i].getMaintTime()<<" minutes left under failure."<<endl;
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
            out<<"Total pages printed by printer "<<i+1<<" is "
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

