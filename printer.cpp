#include"printer.h"

printerType::printerType()
{
    printerSpeed = 10;
    pagesRemaining = 0;
    busyStatus = false;
}

bool printerType::isFree()
{
    return busyStatus;
}

void printerType::setBusy()
{
    busyStatus = true;
}

void printerType::setFree()
{
    busyStatus = false;
}

void printerType::setPrinterSpeed(int speed)
{
    printerSpeed = speed;
}

int printerType::getPagesRemaining()
{
    return pagesRemaining;
}

void printerType::incrementTime()
{
    pagesRemaining = pagesRemaining - printerSpeed;
    if (pagesRemaining <= 0)
        setBusy();
}