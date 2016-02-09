/* Group #3: Bobby Hamrick, Rick Stingel, Taylor Ferguson
   Class: CSC 3710

   This code simulates tasks being sent to the printer(s). As tasks come in, they
   are categorized based on the size of the task and are sent into an appropriate
   waiting queue. The smaller task sizes are printed first.

*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "printers.h"

using namespace std;


/* A void function that sets the parameters to being the simulation.
   Post-condition: maxNumOfPages,printerSpeed,numOfPrintJobs,numOfPrinters are
                   all set to the appropriate values entered by the user.
*/
void setParameters(int &numOfPrinters, int &maxNumOfPages, int &printerSpeed,
                                                                int &numOfPrintJobs);

//--------------------------------------------------------------------------------

/* A void function that processes all of the jobs that are assigned
   to the printers
*/
void processJobs();

//--------------------------------------------------------------------------------

/* A void function that creates of print job with a random number of
   pages and adds it to the printJobQueue
*/
int createPrintJob(int maxNumOfPages, printJobQueueType printJobQueue[], int jobNum, int time);

//--------------------------------------------------------------------------------

/* A void function that prints the results from the simulation and determines the efficiency
   of the current implementation of printers. Then gives advice as to what they should do.
*/
void printResults(int numOfPrinters, int maxNumOfPages, int numOfPrintJobs, int printerSpeed, int time,                  int totalNumPages, double avgWaitTime, double totalCost);


//===================================================================================
int main()
{

   char answer;
   unsigned int seed;

   cout << "Would you like to enter your own seed for the simulation? [y/n]: ";
   cin >> answer;

   if(answer == 'y') {
      cout<<"Enter a value for the seed ";
      cin >> seed;
      srand(seed);
   }else{
      seed = time(NULL);
      srand(seed);
   }

   cout << "The seed used is " << seed << endl;

   processJobs();

   return 0;
}

//=====================================================================================
void setParameters(int &numOfPrinters, int &maxNumOfPages, int &printerSpeed,
                                                                int &numOfPrintJobs)
{
   cout << "Enter '0' for any following value to use default" << endl << endl;

   cout << "Enter the number of printers to be used: ";
   cin >> numOfPrinters;
   cout << endl;
   if(numOfPrinters==0)
      numOfPrinters=3;

   cout << "Enter the maximum number of pages a printer can process: ";
   cin >> maxNumOfPages;
   cout << endl;
   if(maxNumOfPages==0)
      maxNumOfPages=30;

   cout << "Enter number of print jobs to be accomplished: ";
   cin >> numOfPrintJobs;
   cout << endl;
   if(numOfPrintJobs==0)
      numOfPrintJobs=100;

   cout << "Enter the speed (pages/time unit) of the printer: ";
   cin >> printerSpeed;
   cout << endl;
   if(printerSpeed==0)
      printerSpeed=10;
}


//====================================================================================
void processJobs()
{
   int numOfPrinters, maxNumOfPages, numOfPrintJobs, printerSpeed; //variables for parameters
   int jobNum = 0, totalWaitTime = 0, clock = 0, totalNumPages = 0;//variables for keeping track of sim 
   //Set the simulation parameters. Each given by the user
   setParameters(numOfPrinters, maxNumOfPages, printerSpeed, numOfPrintJobs);

   //Create an array of queues that will hold the print jobs based on their priority
   printJobQueueType printJobQueue[3];

   //Declare a list of printers of size numOfPrinters (based on user input)
   printerListType printerList(numOfPrinters);

   //Create Jobs and process them through the printers until all jobs are complete
   while(printerList.getNumJobsCompleted() != numOfPrintJobs){

      clock++; //increase the clock

      printerList.updatePrinters(cout); //update the current status of the printers

      //if neccessary, increase the waiting time of each job in the queue
      for(int i=0;i<3;i++)
         if(!printJobQueue[i].empty())
            printJobQueue[i].updatePrintJobQueue();

      //create jobs until the maximum number of print jobs is completed
      if(jobNum < numOfPrintJobs){
         totalNumPages += createPrintJob(maxNumOfPages, printJobQueue, ++jobNum, clock);
      }

      //Send Print Jobs to printers that are free
      for(int j=0;j<3;j++){
         while(printerList.getNumberOfBusyPrinters() != numOfPrinters &&
              !printJobQueue[j].empty()){
                cout<<"Print Job Number "<<printJobQueue[j].front().getJobNumber()
                    <<" was sent to printer "<<(printerList.getFreePrinterID()+1)
                    <<" at time unit "<<clock<<endl;
                printJobType printJob = printJobQueue[j].front();
                totalWaitTime += printJob.getWaitingTime();
                printJobQueue[j].pop();
                printerList.setPrinterBusy(printerList.getFreePrinterID(),printJob,
                                                                           printerSpeed);
         }
      }
   }

   //calculate the average wait time for each job before it is completely printed
   double avgWaitTime = ((double)totalWaitTime)/numOfPrintJobs;

   //calculate the total cost to print out all pages
   double totalCost = totalNumPages * (0.1 + (.005*numOfPrinters));

   //print the results of the simulation and determine efficiency
printResults(numOfPrinters, maxNumOfPages, numOfPrintJobs, printerSpeed, clock, totalNumPages,
                avgWaitTime, totalCost);
}

//=============================================================================================
int createPrintJob(int maxNumOfPages, printJobQueueType printJobQueue[], int jobNum, int time)
{
   int numPages = rand() % maxNumOfPages + 1; //select a random number of pages for the job
   int wTime = 0; //set the waitTime for the Print Jobs to zero, initially

   printJobType printJob(jobNum, time, numPages, wTime); //create the print job

   if(numPages <= 10){
      printJobQueue[0].push(printJob);
      cout<<"Print Job Number "<<jobNum<<" of size "<<numPages<<" page(s) was placed in the HIGH priority queue."<<endl;
   }else if(numPages <=20){
      printJobQueue[1].push(printJob);
      cout<<"Print Job Number "<<jobNum<<" of size "<<numPages<<" pages was placed in the MEDIUM priority queue."<<endl;
   }else{
      printJobQueue[2].push(printJob);
      cout<<"Print Job Number "<<jobNum<<" of size "<<numPages<<" pages was placed in the LOW priority queue."<<endl;
   }
   return numPages;
}

//============================================================================================
void printResults(int numOfPrinters, int maxNumOfPages, int numOfPrintJobs, int printerSpeed, int time
                  ,int totalNumPages, double avgWaitTime, double totalCost)
{
   cout<<endl<<"************** FINAL RESULTS *****************"<<endl<<endl;
   cout<<"Number of printers = "<<numOfPrinters<<endl;
   cout<<"The maxiumum number of pages a printer can process = "<<maxNumOfPages<<endl;
   cout<<"The number of jobs the printer processed = "<<numOfPrintJobs<<endl;
   cout<<"The speed (pages/time unit) of the printer = "<<printerSpeed<<endl;
   cout<<endl<<"Total time to complete simulation = "<<time<<" time units."<<endl;
   cout<<"The average time for a Print Job to be completed = "<<avgWaitTime<<" time units."<<endl;
   cout<<"The total cost to print all the pages = $"<< setprecision(2) << fixed << totalCost<<endl;

   if(avgWaitTime < 0.75 && numOfPrinters == 3){
      numOfPrinters-=2;
      double newCost = totalNumPages * (.1+(.005*numOfPrinters));
      double savings = totalCost - newCost;
      cout<<"We recommend using two fewer printers. Doing so will reduce your cost by $"<< setprecision(2) << fixed << savings<<endl;
       cout<<"If you print this amount daily, then your annual saving would be $"<<setprecision(2)<<fixed
          <<savings*365<<endl;
   }else if(avgWaitTime < 2 && numOfPrinters > 1){
      numOfPrinters--;
      double newCost = totalNumPages * (.1+(.005*numOfPrinters));
      double savings = totalCost - newCost;
      cout<<"We recommend using one fewer printer. Doing so will reduce your cost by $"<< setprecision(2) << fixed << savings<<endl;
       cout<<"If you print this amount daily, then your annual saving would be $"<<setprecision(2)<<fixed
          <<savings*365<<endl;
   }else
      cout<<"Your current implementation will suffice."<<endl;
   cout<<endl<<"************** END SIMULATION *****************"<<endl;
}
