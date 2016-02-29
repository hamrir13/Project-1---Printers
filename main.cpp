/* Group #3: Bobby Hamrick, Rick Stingel, Taylor Ferguson
   Class: CSC 3710
   
   This code simulates tasks being sent to the printer(s). As tasks come in, they 
   are categorized based on the size of the task and are sent into an appropriate
   waiting queue. The smaller task sizes are printed first. 

*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include "printers.h"

using namespace std;


/* A void function that sets the parameters to being the simulation.
   Post-condition: maxNumOfPages,printerSpeed,numOfPrintJobs,numOfPrinters are
                   all set to the appropriate values entered by the user.
*/
void setParameters(int &numOfPrinters, int &maxNumOfPages, int *printerSpeed, 
		   int &numOfPrintJobs, int &numTiers, int *cutOff, int &numJobsPerMin,
		   int &numMaintPages, int &maintenenceTime, double &percentFail,
                   int &offlineTime, double *printerCost);
//--------------------------------------------------------------------------------

/* A void function that processes all of the jobs that are assigned 
   to the printers
*/
void processJobs();

//--------------------------------------------------------------------------------

/* A void function that creates of print job with a random number of
   pages and adds it to the printJobQueue
*/
int createPrintJob(int whichTier, printJobQueueType printJobQueue[], int jobNum, int time, 		     int cutOff[]);

int numJobsArrived(int numJobsPerMin); 
//--------------------------------------------------------------------------------

/* An int function that returns which tier the next print job assingment will go in.
   Post-condition: the tier of the next job assignment is returned to determine the
                   number of pages that will be produced. 
*/
int whichTier(int numTiers);

//---------------------------------------------------------------------------------
/* An int function that returns the factorial of the integer in the parameter. 
   Post-condition: the factorial of the parameter is returned.
*/

int factorial(int n);
//---------------------------------------------------------------------------------

/* A void function that prints the results from the simulation and determines the efficiency 
   of the current implementation of printers. Then gives advice as to what they should do.
*/
void printResults(int numOfPrinters, int maxNumOfPages, int numOfPrintJobs, int *printerSpeed, int time, 		   	   int totalNumPages, double avgWaitTime, double totalCost);

//---------------------------------------------------------------------------------
/* A void function to print the data from the tiers */

void printTierResults(printJobQueueType printJobQueue[], int numTiers);

void printPrinterResults(printerListType printerList, double costOfPrinter[], int numOfPrinters);
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

/* cout << "Would you like to output to a file?: ";
   cin >> answer;
   if (answer == 'y' || answer == 'Y') {
      printToFile = true;
      cout << "Enter file name to write to: " << endl;
      cin >> outName;
      file.open(outName.c_str());
   }
   else
   {
       printToFile = false;
   }

   cout << "The seed used is ";
   output(seed);
*/

   processJobs();

   return 0;
}

//=====================================================================================
void setParameters(int &numOfPrinters, int &maxNumOfPages, int *printerSpeed, 
      		   int &numOfPrintJobs, int &numTiers, int *cutOff, int &numJobsPerMin, 
		   int &numMaintPages, int &maintenenceTime, double &percentFail, 
		   int &offlineTime, double *printerCost)
{
   char ans;
   
   cout << "Enter the number of printers to be used: "; 
   cin >> numOfPrinters;
   if(numOfPrinters <=0)
      numOfPrinters = 3;
   cout << endl;

   cout << "Enter the maximum number of pages a printer can process: ";
   cin >> maxNumOfPages;
   if(maxNumOfPages <= 0)
      maxNumOfPages = 30;
   cout << endl;

   cout << "Enter number of print jobs to be accomplished: ";
   cin >> numOfPrintJobs;
   if(numOfPrintJobs <= 0)
      numOfPrintJobs = 100;
   cout << endl;

   cout << "Enter the average number of jobs to be sent to the printer per time unit: ";
   cin >> numJobsPerMin;
   cout << endl;

   cout << "Do you want all of the printers to print at the same speed [y/n]: ";
   cin >> ans;
   if(ans == 'y'){
      int printSpeed;
      cout << "Enter the speed (pages/time unit) of the printer: ";
      cin >> printSpeed;
      if(printSpeed <= 0)
         printSpeed = 10;
      for(int i=0;i<numOfPrinters;i++){
         printerSpeed[i]=printSpeed;
      }
      cout << endl;
   }else{
      for(int i=0; i<numOfPrinters; i++){
         cout << "Enter speed for printer "<<i+1<<" : ";
         cin >> printerSpeed[i];
      }
      cout<<endl;
   }

   cout<<"Do you want the cost of each printer to be the same? [y/n]: ";
   cin >> ans;
   if(ans == 'y'){
      double cost;
      cout<<"Enter the cost of the printers: ";
      cin >> cost;
      if(cost < 0)
         cost = 0.005;
      for(int i=0; i<numOfPrinters;i++)
         printerCost[i] = cost;
      cout<<endl;
   }else{
      for(int i=0;i<numOfPrinters;i++){
         cout<<"Enter the cost of printer "<<i+1<<": ";
         cin >> printerCost[i];
      }
      cout<<endl;
   }

   cout << "Enter the number of Tiers in the waiting queue: ";
   cin >> numTiers;
   if(numTiers <= 0)
      numTiers = 3;
   for(int i=0; i<numTiers-1; i++){
      cout << "Enter the cut off for tier number "<<i+1<<": ";
      cin >> cutOff[i];
   }
   cutOff[numTiers-1] = maxNumOfPages;    
   cout<<endl;

   cout<< "Enter the number of pages a printer can print before needing maintenence: ";
   cin >> numMaintPages;
   cout<< "Enter the time that the printer will undergo maintenence: ";
   cin >> maintenenceTime;
   cout<<endl;

   cout<<"Enter the percent chance that a printer will fail: ";
   cin >> percentFail;
   cout<<"If a printer fails, how long should it be offline for: ";
   cin >> offlineTime;
   cout<<endl;
}
 

//====================================================================================
void processJobs()
{
   //variables for simulation parameters
   int numOfPrinters, maxNumOfPages, numOfPrintJobs, numTiers, numJobsPerMin;
   int  printerSpeed[10], cutOff[10], jobsArrived, numMaintPages, maintenenceTime;
   int offlineTime;
   double percentFail, printerCost[10]; 
   //variables for keeping track of data during simulation
   int jobNum = 0, clock = 0, totalNumPages = 0, waitTime = 0;  

   //Set the simulation parameters. Each given by the user
   setParameters(numOfPrinters, maxNumOfPages, printerSpeed, numOfPrintJobs, numTiers, 
     	         cutOff, numJobsPerMin, numMaintPages, maintenenceTime, percentFail,
		 offlineTime, printerCost);  
   
   //Create an array of queues that will hold the print jobs based on their priority
   printJobQueueType *printJobQueue;
   printJobQueue = new printJobQueueType[numTiers]; 
   
   //Declare a list of printers of size numOfPrinters (based on user input)
   printerListType printerList(printerCost, numOfPrinters);
   for(int i=0;i<numOfPrinters;i++)
      cout<<"COST OF PRINTER "<<i+1<<": "<<printerList.getCurrentPrinterCost(i)<<endl;
   //Create Jobs and process them through the printers until all jobs are complete
   while(printerList.getNumJobsCompleted() < numOfPrintJobs){
      clock++; //increase the clock
      cout<<endl<<"###### TIME UNIT "<<clock<<" ######"<<endl;
 
      //update the current status of the printers
      printerList.checkFailure(percentFail,offlineTime);
      printerList.updatePrinters(cout); 
      if(printerList.getNumJobsCompleted() < numOfPrintJobs)
         printerList.checkMaintenence(numMaintPages,maintenenceTime);

      //if neccessary, increase the waiting time of each job in the queue
      for(int i=0;i<numTiers;i++)
         if(!printJobQueue[i].empty())
            printJobQueue[i].updatePrintJobQueue();

      //create jobs until the maximum number of print jobs is completed
      if(jobNum < numOfPrintJobs){
         if((jobsArrived = numJobsArrived(numJobsPerMin)) > 0){
            cout<<jobsArrived<<" job(s) created."<<endl;
            for(int i=0; i<jobsArrived; i++)
               totalNumPages += createPrintJob(whichTier(numTiers), printJobQueue, ++jobNum, 									     clock, cutOff);         }
      }
      
      //Send Print Jobs to printers that are free
      for(int j=0;j<numTiers;j++){
         while(printerList.getNumberOfBusyPrinters() != numOfPrinters &&  
              !printJobQueue[j].empty()){
                cout<<"Print Job Number "<<printJobQueue[j].front().getJobNumber()
                    <<" was sent to printer "<<(printerList.getFreePrinterID()+1)
		    <<" at time unit "<<clock<<endl;
                printJobType printJob = printJobQueue[j].front();
                printJobQueue[j].addWaitTime(printJob.getWaitingTime());
   	        printJobQueue[j].pop();
                printerList.setPrinterBusy(printerList.assignRandomPrinter(),printJob,
					  printerSpeed[printerList.getFreePrinterID()]);
         }   
      }
   }
   
   //calculate the average wait time for each job before it is completely printed
   for(int i=0;i<numTiers;i++){
      waitTime += printJobQueue[i].returnCurrentTierWaitTime();
      cout<<"WAIT TIME = "<<printJobQueue[i].returnCurrentTierWaitTime()<<endl;
   }
   double avgWaitTime = ((double)waitTime)/numOfPrintJobs;
   
   //calculate the total cost to print out all pages
   double totalCost = 0.0;
   double costOfPrinters[numOfPrinters]; 
   for(int i=0;i<numOfPrinters;i++){
      costOfPrinters[i] += (printerCost[i] + .1) * printerList.totalPagesPrintedByPrinter(i);
      totalCost += costOfPrinters[i];
   }

   //print the results of the simulation and determine efficiency
   printResults(numOfPrinters, maxNumOfPages, numOfPrintJobs, printerSpeed, clock, totalNumPages,
		avgWaitTime, totalCost);
   printPrinterResults(printerList, costOfPrinters, numOfPrinters);
   printTierResults(printJobQueue, numTiers);

}

//=======================================================================================
int numJobsArrived(int numJobsPerMin) 
{
   double prob[numJobsPerMin];
   double avgNumJobs = numJobsPerMin;
   int result;

   prob[0] = (pow(avgNumJobs, 0)*exp(-avgNumJobs))/factorial(0);
   
   for(int i=1; i<numJobsPerMin; i++)
      prob[i] = prob[i-1] + (pow(avgNumJobs, i)*exp(-avgNumJobs))/factorial(i);

   int rNum = rand() % 10;
   double rDecimal = rNum/9.0;

   for(int i=0; i<numJobsPerMin; i++){
      if(rDecimal < prob[i]){
         result = i;
         break;
      }else if(rDecimal > prob[numJobsPerMin-1])
         result = numJobsPerMin;
   }
   return result;

}       
   
//======================================================================================
int createPrintJob(int whichTier, printJobQueueType printJobQueue[], int jobNum, int time,		     int cutOff[])
{
   int numPages;
   if(whichTier == 0)
      numPages = rand() % cutOff[whichTier]+1;
   else
      numPages = rand() % (cutOff[whichTier]-cutOff[whichTier-1]) + (cutOff[whichTier-1]+1);//select a random number of pages for the job
   int wTime = 0; //set the waitTime for the Print Jobs to zero, initially
   
   printJobType printJob(jobNum, time, numPages, wTime); //create the print job
   
      printJobQueue[whichTier].push(printJob);
      printJobQueue[whichTier].addNumPages(numPages);
      printJobQueue[whichTier].increaseNumJobs();
      cout<<"Print Job Number "<<jobNum<<" of size "<<numPages
          <<" page(s) was placed in tier number "<<whichTier+1<<endl;
   
   return numPages;
}

//=====================================================================================
int whichTier(int numTiers)
{
   double prob[numTiers-1];
   double rDecimal;
   int rNum, result;
   int i;
   
   prob[0] = (1.0/3);
   for(i=1; i<numTiers-1;i++)
      prob[i] = prob[i-1] + (1.0/(3+i));

   rNum = rand() % 10;
   rDecimal = rNum/10.0;

   for(int i=0; i<numTiers-1; i++){
      if(rDecimal < prob[i]){
         result = i;
         break;
      }else if(rDecimal > prob[numTiers-1])
         result = numTiers-1; 
   }   
   return result;
} 

//=====================================================================================
int factorial(int n)
{
   if(n == 0)
      return 1;
   else
      return n * factorial(n-1);
}
 
//=====================================================================================
void printResults(int numOfPrinters, int maxNumOfPages, int numOfPrintJobs, 
		  int *printerSpeed, int time, int totalNumPages, double avgWaitTime, 
		  double totalCost)
{
   cout<<endl<<"************** FINAL RESULTS *****************"<<endl<<endl;
   
   //cout<<"Number of printers = "<<numOfPrinters<<endl;
   //cout<<"The maxiumum number of pages a printer can process = "<<maxNumOfPages<<endl;
   //cout<<"The number of jobs the printer processed = "<<numOfPrintJobs<<endl;
   //cout<<"The speed (pages/time unit) of the printer = "<<*printerSpeed<<endl;
   cout<<endl<<"Total time to complete simulation = "<<time<<" time unit."<<endl;
   cout<<"The total number of pages printed: "<<totalNumPages<<endl;
   cout<<"The total cost to print all the pages = $"<<totalCost<<endl;
   cout<<"The average time for a Print Job to be completed = "<<avgWaitTime<<" time units."<<endl;


}

//=====================================================================================
void printTierResults(printJobQueueType printJobQueue[], int numTiers)
{
   cout<<endl<<"************ TIER INFO ***************"<<endl;
   for(int i=0;i<numTiers;i++){
      cout<<"Total pages printed by tier "<<i+1<<": "
	  <<printJobQueue[i].returnPagesPrinted()<<endl;
      cout<<"Total number of jobs completed by tier "<<i+1<<": "
          <<printJobQueue[i].returnNumJobsPerformed()<<endl;
      cout<<"Average wait time in tier "<<i+1<<": "
	  <<(double)printJobQueue[i].returnCurrentTierWaitTime()/printJobQueue[i].returnNumJobsPerformed()
	  <<" time units"<<endl<<endl;
   }
   cout<<endl<<"************** END SIMULATION *****************"<<endl;
}

void printPrinterResults(printerListType printerList, double costOfPrinter[], int numOfPrinters)
{
   cout<<endl<<"************ PRINTER INFO ************"<<endl;
   for(int i=0;i<numOfPrinters;i++){
      cout<<"Total pages printed by printer "<<i+1<<": "
          <<printerList.totalPagesPrintedByPrinter(i)<<endl;
      cout<<"Total number of jobs completed by printer "
            <<printerList.totalJobsCompletedByPrinter(i)<<endl;
      cout<<"Cost of printer "<<i+1<<": $"<<costOfPrinter[i]<<endl<<endl;
   }
}
