#include "Session.h"
#include "QDateTimeEdit"

Session::Session() :
    paused(false),
    sessionEnded(false)
{
    startTime = QDateTime::currentDateTime();
    sessionInfo = new SessionInfo();
}

void Session::timerMovement()
{

}
void Session::endSession()
{
    endTime = QDateTime::currentDateTime();
    sessionDuration = endTime.toMSecsSinceEpoch() - startTime.toMSecsSinceEpoch(); // calculate session length
    sessionEnded = true;
}

void Session::pause()
{
    paused = true;
    sessionDuration = QDateTime::currentMSecsSinceEpoch() - startTime.toMSecsSinceEpoch(); // calculate session length on pause
}

void Session::unPause()
{
    paused = false;
}

bool Session::isPaused()
{
    return paused;
}

int Session::getSessionLength()
{
    sessionDuration = QDateTime::currentMSecsSinceEpoch() - startTime.toMSecsSinceEpoch(); // calculate session
    return sessionDuration;
}
