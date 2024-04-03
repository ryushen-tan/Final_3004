#include "Device.h"

Device::Device() :
    currTime(QDateTime::currentDateTime()),
    batteryLevel(100),
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
