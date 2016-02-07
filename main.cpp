/* Group #3: Bobby Hamrick, Rick Stingel, Taylor Ferguson
   Class: CSC 3710
   
   This code simulates tasks being sent to the printer(s). As tasks come in, they 
   are categorized based on the size of the task and are sent into an appropriate
   waiting queue. The smaller task sizes are printed first. 

*/

#include <iostream>
#include <iomanip>
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
void createPrintJob(int maxNumOfPages, printJobQueueType printJobQueue[], int jobNum, int time);

//===================================================================================
int main()
{
   srand(time(NULL));   

   processJobs();

   return 0;
}

//=====================================================================================
void setParameters(int &numOfPrinters, int &maxNumOfPages, int &printerSpeed, 
      								int &numOfPrintJobs)
{
   cout << "Enter the number of printers to be used: "; 
   cin >> numOfPrinters;
   cout << endl;

   cout << "Enter the maximum number of pages a printer can process: ";
   cin >> maxNumOfPages;
   cout << endl;

   cout << "Enter number of print jobs to be accomplished: ";
   cin >> numOfPrintJobs;
   cout << endl;

   cout << "Enter the speed (pages/min) of the printer: ";
   cin >> printerSpeed;
   cout << endl;
}
 

//====================================================================================
void processJobs()
{
   int numOfPrinters, maxNumOfPages, numOfPrintJobs, printerSpeed, numberOfPages;
   int jobNum = 0, numJobsCompleted = 0, clock = 0;
   setParameters(numOfPrinters, maxNumOfPages, printerSpeed, numOfPrintJobs);  

   printJobQueueType printJobQueue[3]; 
   printerListType printerList(numOfPrinters);

   while(printerList.getNumJobsCompleted() != numOfPrintJobs){
   //for(clock=1; clock<=numOfPrintJobs; clock++){
      printerList.updatePrinters(cout);

      if(jobNum <= numOfPrintJobs)
         createPrintJob(maxNumOfPages, printJobQueue, ++jobNum, clock);
      
      for(int j=0;j<numOfPrinters;j++){ 
         while(printerList.getNumberOfBusyPrinters() != numOfPrinters &&  
              !printJobQueue[j].empty()){
                cout<<"Print Job Number "<<printJobQueue[j].front().getJobNumber()
                    <<" was sent to printer "<<(printerList.getFreePrinterID()+1)<<endl;
                printJobType printJob = printJobQueue[j].front();
		printJobQueue[j].pop();
                printerList.setPrinterBusy(printerList.getFreePrinterID(),printJob,
									   printerSpeed);
         }   
      }
      clock++;
   }
   cout<<"Number of printers = "<<numOfPrinters<<endl;
   cout<<"The maxiumum number of pages a printer can process is "<<maxNumOfPages<<endl;
   cout<<"The number of jobs the printer must perform is "<<numOfPrintJobs<<endl;
   cout<<"The speed (pages/min) of the printer is "<<printerSpeed<<endl;
}


void createPrintJob(int maxNumOfPages, printJobQueueType printJobQueue[], int jobNum, int time)
{
   int numPages = rand() % maxNumOfPages + 1;
   
   printJobType printJob(jobNum, time, numPages);
   
   if(numPages <= 10)
      printJobQueue[0].push(printJob);
   else if(numPages <=20)
      printJobQueue[1].push(printJob);
   else
      printJobQueue[2].push(printJob);
}
