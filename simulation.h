/* Fill in the #includes as you need them. 
 *
 * The old #includes were:
 * #include <fstream>
 * #include <string>
 * #include "queueAsArray.h"
 * 
 * */

using namespace std;

//**************** printJobType  ****************

class printJobType
{
public:
   printJobType(int jobNum = 0, int arrvTime = 0, int pageNum = 0);
   
    //Constructor to initialize the instance variables
    //according to the parameters
    //If no value is specified in the object declaration, 
    //the default values are assigned.
    //Postcondition: jobNumber = jobNum;
    //               arrivalTime = arrvTime;
    //               numberOfPages = pageNum;
   
   void setPrintJobInfo(int jobN = 0, int inTime = 0, int pageN = 0);
   
    //Function to initialize the instance variables.
    //Instance variables are set according to the parameters.
    //Postcondition: jobNumber = jobN;
    //               arrivalTime = inTime;
    //               numberOfPages = pageN;
   
   int getJobNumber() const;

    //Function to return the job number.
    //Postcondition: The value of jobNumber is returned.
   
   int getArrivalTime() const;

    //Function to return the arrival time of a customer.
    //Postcondition: The value of arrivalTime is returned.

   int getNumberOfPages() const;

    //Function to return the number of pages for a print job.
    //Postcondition: The value of numberOfPages is returned.
    
/*
 * Note to Bobby.
 * Do we need the following?
 *    int getWaitingTime() const;
 *     //Function to return the waiting time of a customer.
 *     //Postcondition: The value of waitingTime is returned.
 *
 *    void setWaitingTime(int time);
 *     //Function to set the waiting time of a customer.
 *     //Postcondition: waitingTime = time;
 *
 *    void incrementWaitingTime();
 *     //Function to increment the waiting time by one time unit.
 *     //Postcondition: waitingTime++;
 *    
 *    int getTransactionTime() const;
 *     //Function to return the transaction time of a customer.
 *     //Postcondition: The value of transactionTime is returned.
 */

private:
   int jobNumber;
   int arrivalTime;
   int numberOfPages;
};
