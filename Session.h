#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QTimer>
#include "QDateTime"
#include "SessionInfo.h"

#define ROUND_LEN 1000
#define MAX_ROUNDS 29


class Session : public QObject
{
    Q_OBJECT
private:
    QDateTime startTime;
    QDateTime endTime;
    QTimer *timer;
    int sessionDuration;
    SessionInfo* sessionInfo;
    bool paused;
    bool sessionEnded;


public:
    Session(QObject *parent = nullptr);
    bool isPaused();
    void pause();
    void unPause();
    int getSessionLength();
    void endSession();

public slots:
    void timerMovement();

};

#endif // SESSION_H
