/* Fill in the #includes as you need them. 
 *
 * The old #includes were:
 * #include <iostream>
 * #include <string>
 * #include <cstlib>
 *
 * #include "simulation.h"
 * #include "queueAsArray.h"
 * 
 */

using namespace std;

void printJobType::setPrintJobInfo(int jobN, int inTime, int pageN)
{
   jobNumber = jobN;
   arrivalTime = inTime;
   numberOfPages = pageN;
}

printJobType::printJobType(int jobNum, int arrvTime, int pageNum const
{
   return jobNumber;
}
      
int printJobType::getArrivalTime() const
{
   return arrivalTime;
}
      
int printJobType::getNumberOfPages() const
{
   return numberOfPages;
}
      
/* Note to Bobby:
*  do we need the following?
*     int customerType::getWaitingTime() const
*     {
*        return waitingTime;
*     }
*
*     void customerType::incrementWaitingTime()
*     {
*         waitingTime++;
*     }
*
*     void customerType::setWaitingTime(int time)
*     {
*         waitingTime = time;
*     }
*
*     int customerType::getTransactionTime() const
*     {
*         return transactionTime;
*     }
*/
