#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>

#include "printerType.h"

using namespace std;

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
   totalTimePrinting = 0;
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

