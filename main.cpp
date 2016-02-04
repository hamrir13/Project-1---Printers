#include <iostream>
#include <iomanip>

using namespace std;


/* A void function that sets the parameters to being the simulation.
   Post-condition: maxNumOfPages,printerSpeed,numOfPrintJobs,numOfPrinters are
                   all set to the appropriate values entered by the user.
*/
void setParameters(int &numOfPrinters, int &maxNumOfPages, int &printerSpeed, 
								int &numOfPrintJobs);

//===================================================================================

/* A void function that processes all of the jobs that are assigned 
   to the printers
*/
void processJobs();

//===================================================================================

int howManyPages(int &maxNumOfPages);

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
   } else {
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
   int numOfPrinters, maxNumOfPages, numOfPrintJobs, printerSpeed;

   setParameters(numOfPrinters, maxNumOfPages, printerSpeed, numOfPrintJobs);  

   cout<<"Number of printers = "<<numOfPrinters<<endl;
   cout<<"The maxiumum number of pages a printer can process is "<<maxNumOfPages<<endl;
   cout<<"The number of jobs the printer must perform is "<<numOfPrintJobs<<endl;
   cout<<"The speed (pages/min) of the printer is "<<printerSpeed<<endl;
}

int howManyPages(int &maxNumOfPages)
{
   int randomNumOfPages = 0;

   randomNumOfPages = rand() % maxNumOfPages + 1;

   return randomNumOfPages;
}
