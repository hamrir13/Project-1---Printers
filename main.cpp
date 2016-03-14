/* Group #3: Bobby Hamrick, Rick Stingel, Taylor Ferguson
   Class: CSC 3710
   
   This code simulates tasks being sent to the printer(s). As tasks come in, they 
   are categorized based on the size of the task and are sent into an appropriate
   waiting queue. The smaller task sizes are printed first. 

*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include "printJobType.h"
#include "printerType.h"
#include "printerListType.h"
#include "printJobQueueType.h"


using namespace std;


/* A void function that sets the parameters for the simulation.
   Post-condition: maxNumOfPages,printerSpeed,numOfPrintJobs,numOfPrinters are
                   all set to the appropriate values entered by the user.
*/
void setParameters(istream &in, ostream &out, int &numOfPrinters, int &maxNumOfPages, int &numOfPrintJobs, 
										int &numJobsPerMin);

//--------------------------------------------------------------------------------
/* A void function that sets the parameters for the printer.
   Post-condition: All of the parameters for the printers are set to appropriate values
		   from the user or a file.
*/
void setPrinterParameters(istream &in, ostream &out, int numOfPrinters, int *printerSpeed, double *printerCost, 
			int &numMaintPages, int &maintenenceTime, int &offlineTime, double &percentFail);

//--------------------------------------------------------------------------------
/* A void function that sets the parameters for the tiered queue.
   Post-condition: The number of tiers is defined and the cutoffs for each tier is defined.
*/
void setQueueParameters(istream &in, ostream &out, int &numTiers, int *cutOff, int maxNumOfPages);
//--------------------------------------------------------------------------------

/* A void function that processes all of the jobs that are assigned 
   to the printers
*/
void processJobs(istream &in, ostream &out);

//--------------------------------------------------------------------------------

/* A void function that creates of print job with a random number of
   pages and adds it to the printJobQueue
*/
int createPrintJob(ostream &out, int whichTier, printJobQueueType printJobQueue[], int jobNum, 
		   int time, int cutOff[]);

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
void printResults(ostream &out, int numOfPrinters, int maxNumOfPages, int numOfPrintJobs, int numJobsPerMin,
                  int *printerSpeed, double *printerCost, int numTiers, int cutOff[], int numMaintPages, 
		  int maintenenceTime, double percentFail, int offlineTime, int time, int totalNumPages, 
		  double avgWaitTime, double totalCost);

//---------------------------------------------------------------------------------
/* A void function to print the data from the tiers including the number of pages printed, 
   the avergage wait time in a tier and the total number of jobs in a tier
*/
void printTierResults(ostream &out, printJobQueueType printJobQueue[], int numTiers);

//---------------------------------------------------------------------------------
/* A void function to print the data of the printers. This data includes, number of 
   job printed,  cost, number of pages printed, the time spent printing, printer utilization
*/

void printPrinterResults(ostream &out, printerListType &printerList, double costOfPrinter[], 
			 int numOfPrinters, int time);
//===================================================================================
int main()
{

   char answer, param; //hold user answer for seed and parameters
   unsigned int seed; //hold value of seed
   
   char filenameIN[30]; //hold the input filename
   char filenameOUT[30]; //hold the output filename

   ifstream in; //used to scan data from input file
   ofstream out; //used to write to output file

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

   cout<< "Do you want to enter the parameters manually? [y/n]: ";
   cin >> param;

   if(param == 'y'){
      processJobs(cin, cout);
   }else{
      cout<<"What file should we take input from? ";
      cin>>filenameIN;
      in.open(filenameIN);
      if(in.fail()){
         cerr<<"Problem input file"<<endl;
         exit(1);
      }

      cout<<"Enter a filename for the results(no spaces): ";
      cin>>filenameOUT;
      out.open(filenameOUT);
      if(out.fail()){
         cerr<<"Problem output file"<<endl;
         exit(2);
      }

      processJobs(in, out);
   }

   return 0;
}

//=====================================================================================
void setParameters(istream &in, ostream &out, int &numOfPrinters, int &maxNumOfPages, int &numOfPrintJobs, 
		   int &numJobsPerMin)
{
   if(out == cout)
      out<<"Enter the number of printers to use: ";
   in >> numOfPrinters;
   if(numOfPrinters <=0)
      numOfPrinters = 3;

   if(out == cout)
      out<<"Enter the maximum number of pages a job can be: ";
   in >> maxNumOfPages;
   if(maxNumOfPages <= 0)
      maxNumOfPages = 50;

   if(out == cout)
      out<<"Enter the number of jobs to complete: ";
   in >> numOfPrintJobs;
   if(numOfPrintJobs <= 0)
      numOfPrintJobs = 100;

   if(out == cout)
      out<<"Enter the average number of jobs to be created per time unit: ";
   in >> numJobsPerMin;

}

void setPrinterParameters(istream &in, ostream &out, int numOfPrinters, int *printerSpeed, double *printerCost, 
			  int &numMaintPages, int &maintenenceTime, int &offlineTime, double &percentFail) 
{   
   if(out == cout){
      for(int i=0;i<numOfPrinters;i++){
         out<<"Enter the speed of printer "<<i+1<<": ";
         in>>printerSpeed[i];
      }
   }else{
      for(int i=0;i<numOfPrinters;i++)
         in>>printerSpeed[i];
   }

   if(out == cout){
      for(int i=0;i<numOfPrinters;i++){
         out<<"Enter the cost of printer "<<i+1<<" per page printed: ";
         in>>printerCost[i];
      }
   }else{
      for(int i=0;i<numOfPrinters;i++)
         in>>printerCost[i];
   }
   
   if(out == cout)
      out<<"Enter the number of pages a printer can print before undergoing maintenence: ";
   in >> numMaintPages;
   
   if(out == cout)
      out<<"Enter the time a printer should undergo maintenence: ";
   in >> maintenenceTime;

   if(out == cout)
      out<<"Enter the percent chance that a printer fails: ";
   in >> percentFail;

   if(out == cout)
      out<<"Enter the time a printer should go offline after it fails: ";
   in >> offlineTime;
}


void setQueueParameters(istream &in, ostream &out, int &numTiers, int *cutOff, int maxNumOfPages)
{
   if(out == cout)
      out<<"Enter the number of tiers in the queue: ";
   in >> numTiers;
   if(numTiers <= 0)
      numTiers = 3;
   if(out == cout){
      for(int i=0; i<numTiers-1; i++){
         out<<"Enter the page number cutoff for tier "<<i+1<<": ";
         in >> cutOff[i];
      }
      cutOff[numTiers-1] = maxNumOfPages;    
   }else{
      for(int i=0; i<numTiers-1; i++){
         in >> cutOff[i];
      }
      cutOff[numTiers-1] = maxNumOfPages;    
   }
}
 

//====================================================================================
void processJobs(istream &in, ostream &out)
{
   //variables for simulation parameters
   int numOfPrinters, maxNumOfPages, numOfPrintJobs, numTiers, numJobsPerMin; 
   int jobsArrived, numMaintPages, maintenenceTime, offlineTime;
   int  printerSpeed[10], cutOff[10];
   double percentFail, printerCost[10];
   
   //variables for keeping track of data during simulation
   int jobNum = 0, clock = 0, totalNumPages = 0, waitTime = 0;  

   //Set the simulation parameters. Each given by file specified by the user
   setParameters(in, out, numOfPrinters, maxNumOfPages, numOfPrintJobs, numJobsPerMin);  
  
   setPrinterParameters(in, out, numOfPrinters, printerSpeed, printerCost, numMaintPages, 
			maintenenceTime, offlineTime, percentFail);
   
   setQueueParameters(in, out, numTiers, cutOff, maxNumOfPages);
   
   //Create an array of queues that will hold the print jobs based on their priority
   printJobQueueType *printJobQueue;
   printJobQueue = new printJobQueueType[numTiers]; 
   
   //Declare a list of printers of size numOfPrinters (based on user input)
   printerListType printerList(numOfPrinters);
   
   //Create Jobs and process them through the printers until all jobs are complete
   while(printerList.getNumJobsCompleted() < numOfPrintJobs){
      clock++; //increase the clock
      out<<endl<<"###### TIME UNIT "<<clock<<" ######"<<endl;
 
      //update the current status of the printers
      printerList.checkFailure(out,percentFail,offlineTime);
      printerList.updatePrinters(out); 
      if(printerList.getNumJobsCompleted() < numOfPrintJobs)
         printerList.checkMaintenence(out,numMaintPages,maintenenceTime);

      //if neccessary, increase the waiting time of each job in the queue
      for(int i=0;i<numTiers;i++)
         if(!printJobQueue[i].empty())
            printJobQueue[i].updatePrintJobQueue();

      //create jobs until the maximum number of print jobs is completed
      if(jobNum < numOfPrintJobs){
         if((jobsArrived = numJobsArrived(numJobsPerMin)) > 0){
            out<<jobsArrived<<" job(s) created."<<endl;
            for(int i=0; i<jobsArrived; i++)
               totalNumPages += createPrintJob(out, whichTier(numTiers), printJobQueue, ++jobNum, 									     clock, cutOff);         }
      }
      
      //Send Print Jobs to printers that are free
      for(int j=0;j<numTiers;j++){
         while(printerList.getNumberOfBusyPrinters() != numOfPrinters &&  
              !printJobQueue[j].empty()){
                int pNum = printerList.assignRandomPrinter();
                out<<"Print Job Number "<<printJobQueue[j].front().getJobNumber()
                    <<" was sent to printer "<<pNum+1<<" at time unit "<<clock<<endl;
                printJobType printJob = printJobQueue[j].front();
                printJobQueue[j].addWaitTime(printJob.getWaitingTime());
   	        printJobQueue[j].pop();
                printerList.setPrinterBusy(pNum,printJob,
					  printerSpeed[printerList.getFreePrinterID()]);
         }   
      }
   }
   
   //calculate the average wait time for each job before it is completely printed
   for(int i=0;i<numTiers;i++){
      waitTime += printJobQueue[i].returnCurrentTierWaitTime();
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
   printResults(out, numOfPrinters, maxNumOfPages, numOfPrintJobs, numJobsPerMin, 
	        printerSpeed, printerCost, numTiers, cutOff, numMaintPages, maintenenceTime, 
		percentFail, offlineTime, clock, totalNumPages,avgWaitTime, totalCost);
   
   printPrinterResults(out, printerList, costOfPrinters, numOfPrinters, clock);
   
   printTierResults(out, printJobQueue, numTiers);

}

//=======================================================================================
int numJobsArrived(int numJobsPerMin) 
{
   double prob; //store probablility of number of jobs
   double avgNumJobs = numJobsPerMin; //average number of jobs per min
   double cutoff = 0.95;
   int result = 0;
   int createdJobs = 0, k = 0; 

   prob = (pow(avgNumJobs, 0)*exp(-avgNumJobs))/factorial(0);
   
   int rNum = rand() % 101;
   double rDecimal = rNum/100.0;
 
   while(prob <= rDecimal && prob <= cutoff){
      createdJobs++;
      k++;
      prob += (pow(avgNumJobs,k)*exp(-avgNumJobs))/factorial(k);
      if(prob >= rDecimal || prob >= cutoff)
         result = createdJobs;
   }  
   return result;

}       
   
//======================================================================================
int createPrintJob(ostream &out, int whichTier, printJobQueueType printJobQueue[], int jobNum,                                int time, int cutOff[])
{
   int numPages;
   if(whichTier == 0)
      numPages = rand() % cutOff[whichTier]+1;
   else
      numPages = rand() % (cutOff[whichTier]-cutOff[whichTier-1]) + (cutOff[whichTier-1]+1);
   int wTime = 0; //set the waitTime for the Print Jobs to zero, initially
   
   printJobType printJob(jobNum, time, numPages, wTime); //create the print job
   
      printJobQueue[whichTier].push(printJob);
      printJobQueue[whichTier].addNumPages(numPages);
      printJobQueue[whichTier].increaseNumJobs();
      out<<"Print Job Number "<<jobNum<<" of size "<<numPages
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
   if(numTiers == 2){
      prob[0] = (1.0/2);
   }else if(numTiers == 3){
      prob[0] = (1.0/3);
      prob[1] = prob[0]+(1.0/3);
   }else{
      prob[0] = 1.0/3;
      for(i=1; i<numTiers-1;i++)
         prob[i] = prob[i-1] + (1.0/(3+i));
   }
   
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
void printResults(ostream &out, int numOfPrinters, int maxNumOfPages, int numOfPrintJobs, 
		  int numJobsPerMin, int *printerSpeed, double *printerCost, int numTiers, 
		  int cutOff[], int numMaintPages, int maintenenceTime, double percentFail, int offlineTime,
		  int time, int totalNumPages, double avgWaitTime, double totalCost)
{
   out<<endl<<"************** INPUT PARAMETERS *****************"<<endl<<endl;
   
   out<<"Number of printers = "<<numOfPrinters<<endl;
   out<<"The maxiumum number of pages a printer can process = "<<maxNumOfPages<<endl;
   out<<"The number of jobs the printer processed = "<<numOfPrintJobs<<endl;
   out<<"The average number of jobs produced per time unit = "<<numJobsPerMin<<endl;
   for(int i=0;i<numOfPrinters;i++)
      out<<"The speed (pages/time unit) of the printer = "<<printerSpeed[i]<<endl;
   out<<"The cost of ink and paper is about $0.1 per page printed"<<endl;
   for(int i=0;i<numOfPrinters;i++)
      out<<"The cost of printer "<<i+1<<" per page: $"<<printerCost[i]<<endl;
   out<<"The total number of tiers in the job queue = "<<numTiers<<endl;
   for(int i=0;i<numTiers;i++)
      out<<"The cutoff for tier "<<i+1<<": "<<cutOff[i]<<" pages"<<endl;
   out<<"The number of pages a printer can print before needing maintenence = "<<numMaintPages<<endl;
   out<<"The amount of time a printer goes under maintenence: "<<maintenenceTime<<" time units"<<endl;
   out<<"The percent chance that a printer will fail = "<<percentFail<<"%"<<endl;
   out<<"The amount of time a printer goes offline due to failure = "<<offlineTime<<" time units"<<endl;

   out<<endl<<"**************** FINAL RESULTS *********************"<<endl;
   out<<endl<<"Total time to complete simulation = "<<time<<" time unit."<<endl;
   out<<"The total number of pages printed: "<<totalNumPages<<endl;
   out<<"The total cost to print all the pages = $"<<totalCost<<endl;
   out<<"The average time for a Print Job to be completed = "<<avgWaitTime<<" time units."<<endl;


}

//=====================================================================================
void printTierResults(ostream &out, printJobQueueType printJobQueue[], int numTiers)
{
   out<<endl<<"************ TIER INFO ***************"<<endl;
   for(int i=0;i<numTiers;i++){
      out<<"Total pages printed by tier "<<i+1<<": "
	  <<printJobQueue[i].returnPagesPrinted()<<endl;
      out<<"Total number of jobs completed by tier "<<i+1<<": "
          <<printJobQueue[i].returnNumJobsPerformed()<<endl;
      out<<"Average wait time in tier "<<i+1<<": "
	  <<(double)printJobQueue[i].returnCurrentTierWaitTime()/printJobQueue[i].returnNumJobsPerformed()
	  <<" time units"<<endl<<endl;
   }
   out<<endl<<"************** END SIMULATION *****************"<<endl;
   
}

//=====================================================================================
void printPrinterResults(ostream &out, printerListType &printerList, 
			double costOfPrinter[], int numOfPrinters, int time)
{
   out<<endl<<"************ PRINTER INFO ************"<<endl;
   for(int i=0;i<numOfPrinters;i++){
      out<<"Total pages printed by printer "<<i+1<<": "
          <<printerList.totalPagesPrintedByPrinter(i)<<endl;
      out<<"Total number of jobs completed by printer "
            <<printerList.totalJobsCompletedByPrinter(i)<<endl;
      out<<"Cost of printer "<<i+1<<"(including cost of ink and paper): $"
	 <<costOfPrinter[i]<<setprecision(2)<<endl;
      out<<"Total time spent printing by printer #"<<i+1<<": "
  	 <<printerList.getTotalTimeBusy(i)<<endl;
      out<<"Percent Utilization of printer "<<i+1<<": "
	 <<setprecision(4)<<((double)printerList.getTotalTimeBusy(i)/time)*100
	 <<"%"<<endl<<endl;
   }

}
