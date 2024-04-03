#ifndef DEVICE_H
#define DEVICE_H

#include <QDateTime>
#include <QVector>

class Session;

class Device {
public:
    Device();
    ~Device();


    QDateTime currTime;
    QVector<Session*> savedSessions;
    Session* currentSession;
    int batteryLevel;
    bool currentlyOn;

    void setTime(const QDateTime &dt);
    void beginSesh();
    void powerButton();

    void calculateDominantFreq();
    void applyTreatment();

    void setBattery();

private:
    QVector<QString> currSeshInfo;
    bool hasContact;
};
#endif // DEVICE_H
