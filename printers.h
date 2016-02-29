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
      //	       is returned.
    
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
    
    void setCost(int cost);
      //Function to set the cost of the printer
      //Postcondition: printerCost = cost

    double getPrinterCost();
      //Function to return the cost of the printer
      //Postcondition: return printerCost
     
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
      //		print Job is returned.

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
      //	       and the printer is offline for offlineTime 
      //	       minutes.

    void increaseJobsCompleted();
      //Function to increase the number of jobs completed
      //Postcondition: numOfJobsCompleted++;

    int getTotalJobsCompleted();
      //Function to return the value of the number of jobs
      //completed by this printer
      //Postcondition: value of numJobsCompleted is returned

private:
   printJobType currentPrintJob;
   string status;
   int maintTime;
   int remainingPages;
   int printerSpeed;
   int totalPagesPrinted;
   int currentPagesPrinted;
   int numJobsCompleted;
   double printerCost;
};

//****************** printerListType *****************
class printerListType
{
public: 
   printerListType(double *printerCost, int num = 1);
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
    
    double getCurrentPrinterCost(int printerID);
       //Function to get the cost of the printerID printer
       //Postcondition: the cost of the printerID printer is returned.

    int totalPagesPrintedByPrinter(int printerNum);
       //Function to return the number of pages printed by
       //printers[printerNum]
       //Postcondition: value of the total pages printed by 
       //		the specific printer is returned

    int totalJobsCompletedByPrinter(int printerNum);
       //Function to return the number of jobs completed by
       //printers[printerNum]
       //Postcondition: value of the total job completed by 
       //		the current printer is returned

    void checkFailure(double percentFail, int offlineTime);
       //Function to check if the printers failed while printing.
       //Postcondition: If the printer fails, the status is set to 
       //		"failed" and remains offline for offlineTime
       //		time units.

    void checkMaintenence(int numMaintPages, int maintenenceTime);
       //Function to check to see if the printers need maintenence
       //Postcondition: The numMaintPages is the maxiumum number of
       //		pages the printer can print before needing maintenence.
       //		Printers that need maintenence will be set busy until
       //		it reaches maintenenceTime.

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
      //	       based on printJobs waitTime
   
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
