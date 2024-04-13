#ifndef DEVICE_H
#define DEVICE_H

#define EEG_SITES 7

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QVector>
#include <iostream>

using namespace std;

#include "EEGSite.h"
#include "SessionInfo.h"

#define ROUND_LEN 6
#define MAX_DUR 29

class MainWindow; // Forward declaration
class SessionInfo;

class Device : public QObject {
    Q_OBJECT
public:
    Device(MainWindow*, QObject* parent = nullptr);
    ~Device();

    QTimer* timer;
    QDateTime currTime;
    QVector<SessionInfo*> savedSessions;
    SessionInfo* currentSession;
    int batteryLevel;
    bool powerStatus;

    void setTime(const QDateTime &dt);
    void beginSesh();
    void endSesh();
    void powerButton();

    void calculateDominantFreq();
    void applyTreatment();

    void setBattery(int);

    void initiateContact();
    void generateSignals();

private:
    QVector<QString> currSeshInfo;
    bool hasContact;

    QVector<EEGSite*> sites;

    MainWindow* mainWindow;
    int sessionDuration;
    int numberOfRound;

private slots:
    void updateRound();
};
#endif // DEVICE_H
