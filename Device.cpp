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
    // turning on: get battery value from file & store in variable - enable main menu, computer view, admin view

    // turning off: update battery value in file from variable - disable device view only
}

void Device::setBattery(int charge)
{
    if (charge < 0) // if charge value is negative, this is a battery drain of (int) charge %
    {
        batteryLevel -= charge;
    }
    else // if charge value is not battery drain, battery level is being set to certain %
    {
        batteryLevel = charge;
    }

    if (batteryLevel == 0)
    {
        //power off
    }
    else if (batteryLevel < 40)
    {
        //low power message... each session requires around 40% battery, so if there's less than 40% battery, the device will let the user know it needs to be charged
        std::cout << "ATTENTION: low power! Please charge device. 40% minimum needed for a new session.\n" << std::endl;
    }
}
