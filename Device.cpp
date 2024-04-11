#include "Device.h"

Device::Device() :
    currTime(QDateTime::currentDateTime()),
    batteryLevel(100), //
    currentlyOn(false),
    hasContact(false)
{

}

Device::~Device() {
    // Cleanup might be needed
}

void Device::setTime(const QDateTime &dt) {
    currTime = dt;
}

void Device::powerButton()
{

}

void Device::setBattery(int charge)
{
    if (charge < 0) // if charge is negative, this is a battery drain of (int) charge %
    {
        batteryLevel -= charge;
    }
    else // if charge is not battery drain, battery level is being set to certain %
    {
        batteryLevel = charge;
    }

    if (batteryLevel == 0)
    {
        //power off
    }
    else if (batteryLevel < 40)
    {
        //low power message... let's say each session requires around 40% battery, so if there's 10% or less, the device will let the user know it needs to be charged
    }
}
