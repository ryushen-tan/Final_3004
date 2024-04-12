#include "Device.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Device::Device(MainWindow* mw) :
    currTime(QDateTime::currentDateTime()),
    batteryLevel(100), //TODO: get battery value from file & store in variable
    powerStatus(false),
    hasContact(false)
{
    mainWindow = mw;

    for (int i = 0; i < EEG_SITES; i++)
    {
        sites.append(new EEGSite());
    }
}

Device::~Device() {
    // Cleanup might be needed
}

void Device::setTime(const QDateTime &dt) {
    currTime = dt;
}

void Device::powerButton()
{
    if (powerStatus) {
        turnOffDevice();    // turning off function
        powerStatus = false;
    }
    else {
        if (batteryLevel > 0) {
            powerStatus = true;
        }
        std::cout << "ATTENTION: no power! Device cannot power on...\n" << std::endl;
        // turning on
        //print variables to show status? - not needed for now
    }

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
        std::cout << "ATTENTION: no power! Device powering off...\n" << std::endl;
        turnOffDevice();    //power off
    }
    else if (batteryLevel < 40)
    {
        //low power message... each session requires around 40% battery, so if there's less than 40% battery, the device will let the user know it needs to be charged
        std::cout << "ATTENTION: low power! Please charge device. 40% minimum needed for a new session.\n" << std::endl;
    }
    std::cout << "battery is set to " << batteryLevel << "\n" << std::endl;
}

void Device::initiateContact()
{
    hasContact = true;
    generateSignals();
}

void Device::generateSignals()
{
    for (int i = 0; i < EEG_SITES; i++)
    {
        sites[i]->generateSignal();
    }
}


void Device::turnOffDevice()    // turning off device function: update battery value in file from variable - disable device view only
{
    //TODO: update battery value in file from variable

        mainWindow->power_off();

}
