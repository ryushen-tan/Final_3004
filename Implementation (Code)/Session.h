#ifndef SESSION_H
#define SESSION_H

#include "QDateTime"
#include "SessionInfo.h"

class Session
{
private:
    QDateTime startTime;
    QDateTime endTime;
    int sessionDuration;
    SessionInfo* sessionInfo;
    bool paused;
    bool sessionEnded;

public:
    Session();
    bool isPaused();
    void pause();
    void unPause();
    int getSessionLength();
    void endSession();

};

#endif // SESSION_H
