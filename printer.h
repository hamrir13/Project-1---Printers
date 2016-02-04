//included by printer.cpp

class printerType
{
public:
    printerType();
    //default contructor
    //Postcondition: initiate the private variables to default values

    bool isFree();
    //Function to check if the printer is free
    //postcondition: returns true if printer is free, otherwise false

    void setBusy();
    //Function to set the status of the printer to busy.
    //Postcondition: status = "busy";

    void setFree();
    //Function to set the status of the printer to "free".
    //Postcondition: status = "free";

    void setPrinterSpeed(int);
    //Function to set the rate of pages printed ther 1 time unit
    //Postcondition: change default printer speed to be the value passed to it

    int getPagesRemaining();
    //Function to get the value of pagesRemaing
    //Postcondition: returns pagesRemaining

    void incrementTime();
    //Function to increment the time change by 1 time unit
    //Postcondition: reduces pagesRemaining by printerSpeed,
    //               as well as change busy status to false if pagesRemaining < 0


private:
    int printerSpeed;
    int pagesRemaining;
    bool busyStatus;

};