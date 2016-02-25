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
		   int &numOfPrintJobs, int &numTiers, int *cutOff, int &numJobsPerMin);

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
void setParameters(int &numOfPrinters, int &maxNumOfPages, int *printerSpeed, 
      		   int &numOfPrintJobs, int &numTiers, int *cutOff, int &numJobsPerMin)
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

   cout << "Enter the number of Tiers in the waiting queue: ";
   cin >> numTiers;
   if(numTiers <= 0)
      numTiers = 3;
   cout << endl;

   for(int i=0; i<numTiers-1; i++){
      cout << "Enter the cut off for tier number "<<i+1<<": ";
      cin >> cutOff[i];
   }
   cutOff[numTiers-1] = maxNumOfPages;    
}
 

//====================================================================================
void processJobs()
{
   //variables for simulation parameters
   int numOfPrinters, maxNumOfPages, numOfPrintJobs, numTiers, numJobsPerMin;
   int  printerSpeed[10], cutOff[10], jobsArrived;
  
   //variables for keeping track of data during simulation
   int jobNum = 0, totalWaitTime = 0, clock = 0, totalNumPages = 0;  
   
   //Set the simulation parameters. Each given by the user
   setParameters(numOfPrinters, maxNumOfPages, printerSpeed, numOfPrintJobs, numTiers, 
     	         cutOff, numJobsPerMin);  

   //Create an array of queues that will hold the print jobs based on their priority
   printJobQueueType *printJobQueue;
   printJobQueue = new printJobQueueType[numTiers]; 
   
   //Declare a list of printers of size numOfPrinters (based on user input)
   printerListType printerList(numOfPrinters);

   //Create Jobs and process them through the printers until all jobs are complete
   while(printerList.getNumJobsCompleted() < numOfPrintJobs){
      cout<<printerList.getNumJobsCompleted()<<endl; 
      clock++; //increase the clock
      
      printerList.updatePrinters(cout); //update the current status of the printers

      if(printerList.getNumJobsCompleted() == numOfPrintJobs)
         break;

      //if neccessary, increase the waiting time of each job in the queue
      for(int i=0;i<numTiers;i++)
         if(!printJobQueue[i].empty())
            printJobQueue[i].updatePrintJobQueue();

      //create jobs until the maximum number of print jobs is completed
      if(jobNum < numOfPrintJobs){
         if((jobsArrived = numJobsArrived(numJobsPerMin)) > 0){
            cout<<jobsArrived<<" jobs were created."<<endl;
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
                totalWaitTime += printJob.getWaitingTime();
		printJobQueue[j].pop();
                printerList.setPrinterBusy(printerList.getFreePrinterID(),printJob,
					  printerSpeed[printerList.getFreePrinterID()]);
         }   
      }
   }
   
   //calculate the average wait time for each job before it is completely printed
   //double avgWaitTime = ((double)totalWaitTime)/numOfPrintJobs;
   
   //calculate the total cost to print out all pages
  // double totalCost = totalNumPages * (0.1 + (.005*numOfPrinters));

   //print the results of the simulation and determine efficiency
  // printResults(numOfPrinters, maxNumOfPages, numOfPrintJobs, printerSpeed, clock, totalNumPages,
//										avgWaitTime, totalCost);
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
   
//=============================================================================================
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
      cout<<"Print Job Number "<<jobNum<<" of size "<<numPages
          <<" page(s) was placed in tier number "<<whichTier+1<<endl;
   
   return numPages;
}

//=======================================================================================
int whichTier(int numTiers)
{
   double prob[numTiers-1];
   double rDecimal;
   int rNum, result;
   int i;
   
   prob[0] = (1.0/3);
   for(i=1; i<numTiers-1;i++)
      prob[i] = prob[i-1] + 1/(3+i);

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

//=======================================================================================
int factorial(int n)
{
   if(n == 0)
      return 1;
   else
      return n * factorial(n-1);
}
 
//============================================================================================
void printResults(int numOfPrinters, int maxNumOfPages, int numOfPrintJobs, int *printerSpeed, int time
		  ,int totalNumPages, double avgWaitTime, double totalCost)
{
   cout<<endl<<"************** FINAL RESULTS *****************"<<endl<<endl;
   cout<<"Number of printers = "<<numOfPrinters<<endl;
   cout<<"The maxiumum number of pages a printer can process = "<<maxNumOfPages<<endl;
   cout<<"The number of jobs the printer processed = "<<numOfPrintJobs<<endl;
   cout<<"The speed (pages/time unit) of the printer = "<<*printerSpeed<<endl;
   cout<<endl<<"Total time to complete simulation = "<<time<<" time units."<<endl;
   cout<<"The average time for a Print Job to be completed = "<<avgWaitTime<<" time units."<<endl;
   cout<<"The total cost to print all the pages = $"<<totalCost<<endl;

   if(avgWaitTime < 0.75 && numOfPrinters == 3){
      numOfPrinters-=2;
      double newCost = totalNumPages * (.1+(.005*numOfPrinters));
      double savings = totalCost - newCost; 
      cout<<"We recommend using two fewer printers. Doing so will reduce your cost by $"
          <<setprecision(2)<<fixed<<savings<<endl;
      cout<<"If you print this amount daily, then your annual saving would be $"<<setprecision(2)<<fixed
          <<savings*365<<endl;
   }else if(avgWaitTime < 2 && numOfPrinters > 1){
      numOfPrinters--;
      double newCost = totalNumPages * (.1+(.005*numOfPrinters));
      double savings = totalCost - newCost; 
      cout<<"We recommend using one fewer printer. Doing so will reduce your cost by $"
          <<setprecision(2)<<fixed<<savings<<endl;
      cout<<"If you print this amount daily, then your annual saving would be $"<<setprecision(2)<<fixed
          <<savings*365<<endl;
   }else
      cout<<"Your current implementation will suffice."<<endl;
   cout<<endl<<"************** END SIMULATION *****************"<<endl;
}
