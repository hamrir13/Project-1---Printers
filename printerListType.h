/* Names: B. Hamrick, T. Ferguson, R. Stingel
   Date: 3.1.16
   Class: CSC 3710

   This is a header file contaning the printerListType class
*/

#ifndef PRINTERLISTTYPE_H
#define PRINTERLISTTYPE_H

#include <fstream>
#include <string>
#include <queue>
#include "printJobType.h"
#include "printerType.h"

using namespace std;

//****************** printerListType *****************
class printerListType
{
public:
   printerListType(int num = 1);
      //Constructor to initialize a list of printers
      //Postcondition: numOfPrinters = num
      //               A list of printers, specified by num,
      //               is created and each printer is
      //               initialized to "free".

   ~printerListType();
      //Destructor
      //Postcondition: The list of printers is destroyed.

   int getFreePrinterID() const;
      //Function to search the list of printers.
      //Postcondition: If a free printer is found, returns
      //               its ID; otherwise, returns -1.

    int getNumberOfBusyPrinters() const;
      //Function to return the number of busy printers.
      //Postcondition: The number of busy printers is returned.

    int assignRandomPrinter();
      //Function to return a random integer that represents
      //the printer that will take the next job
      //Postcondition: value of a random integer is returned

    int getNumJobsCompleted() const;
       //Function to return the number of jobs the printers have completed
       //Postcondition: The number of jobs completed is returned

    int getTotalTimeBusy(int printerID);
       //Function to get the total printer time of printerID printer
       //Postcondition: value of the total time spent printer of the
       //               specific printer is returned.

    int totalPagesPrintedByPrinter(int printerNum);
       //Function to return the number of pages printed by
       //printers[printerNum]
       //Postcondition: value of the total pages printed by
       //               the specific printer is returned

    int totalJobsCompletedByPrinter(int printerNum);
       //Function to return the number of jobs completed by
       //printers[printerNum]
       //Postcondition: value of the total job completed by
       //               the current printer is returned

    void checkFailure(ostream &out, double percentFail, int offlineTime);
       //Function to check if the printers failed while printing.
       //Postcondition: If the printer fails, the status is set to
       //               "failed" and remains offline for offlineTime
       //               time units.

    void checkMaintenence(ostream &out, int numMaintPages, int maintenenceTime);
       //Function to check to see if the printers need maintenence
       //Postcondition: The numMaintPages is the maxiumum number of
       //               pages the printer can print before needing maintenence.
       //               Printers that need maintenence will be set busy until
       //               it reaches maintenenceTime.

    void setPrinterBusy(int printerID, printJobType cPrintJob,
                       int pTime);
      //Function to set a printer as busy.
      //Postcondition: The printer specified by printerID is set
      //               to "busy", to perform the job
      //               specified by cPrintJob, and the
      //               print time is set according to the
      //               parameter pTime.

    void updatePrinters(ostream& outFile);
      //Function to update the status of a printer.
      //Postcondition: The print time of each busy
      //               server is decremented by the printer speed. If
      //               the print time of a busy printer
      //               is reduced to zero, the printer is set
      //               to "free". Moreover, if the actual
      //               parameter corresponding to outFile is
      //               cout, a message indicating which job
      //               has been performed is printed on the screen,
      //               together with the job's completion
      //               time. Otherwise, the output is sent to
      //               a file specified by the user.

private:
   int numOfPrinters;
   int numJobsCompleted;
   printerType *printers;
};

#endif

