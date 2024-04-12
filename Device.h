#ifndef DEVICE_H
#define DEVICE_H

#define EEG_SITES 7

#include <QDateTime>
#include <QVector>
#include <iostream>

using namespace std;

#include "EEGSite.h"

class MainWindow; // Forward declaration
class Session;

class Device {
public:
    Device(MainWindow*);
    ~Device();

    QDateTime currTime;
    QVector<Session*> savedSessions;
    Session* currentSession;

    int batteryLevel;
    bool powerStatus;

    void setTime(const QDateTime &dt);
    void beginSesh();
    void powerButton();

    void calculateDominantFreq();
    void applyTreatment();

    void setBattery(int);

    void initiateContact();
    void generateSignals();

    void turnOffDevice();

private:
    QVector<QString> currSeshInfo;
    bool hasContact;

    QVector<EEGSite*> sites;

    MainWindow* mainWindow;
};
#endif // DEVICE_H
