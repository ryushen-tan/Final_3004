#include "Session.h"
#include "QDateTimeEdit"

Session::Session(QObject* parent) :
    QObject(parent),
    paused(false),
    sessionEnded(false)
{
    startTime = QDateTime::currentDateTime();
    sessionInfo = new SessionInfo();
    sessionDuration = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Session::timerMovement);
    timer->start(ROUND_LEN);
}

void Session::timerMovement()
{
    sessionDuration += 1;
    if(sessionDuration >= MAX_ROUNDS) {
        endSession();
    }
}

void Session::endSession()
{
    endTime = QDateTime::currentDateTime();
    //sessionDuration = endTime.toMSecsSinceEpoch() - startTime.toMSecsSinceEpoch(); // calculate session length
    sessionEnded = true;
    timer->stop();
}

void Session::pause()
{
    paused = true;
    timer->stop();
    //sessionDuration = QDateTime::currentMSecsSinceEpoch() - startTime.toMSecsSinceEpoch(); // calculate session length on pause

}

void Session::unPause()
{
    paused = false;
    timer->start(ROUND_LEN);
}

bool Session::isPaused()
{
    return paused;
}

int Session::getSessionLength()
{
    //sessionDuration = QDateTime::currentMSecsSinceEpoch() - startTime.toMSecsSinceEpoch(); // calculate session
    return sessionDuration;
}
