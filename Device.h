#ifndef DEVICE_H
#define DEVICE_H

#define EEG_SITES 7

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QVector>
#include <iostream>
#include <QVector>
#include <QFile>
#include <QDebug>

using namespace std;

#include "EEGSite.h"
#include "SessionInfo.h"

#define ROUND_LEN 6
#define MAX_DUR 29
#define SESH_UPDATE_FRQ 1000
#define MAX_ROUNDS 4;
#define LIGHT_FLASH_FRQ 500

class MainWindow; // Forward declaration
class SessionInfo;

class Device : public QObject {
    Q_OBJECT
public:
    Device(MainWindow*, QObject* parent = nullptr);
    ~Device();

    QTimer* timer;
    QTimer* lightTimer;
    QDateTime currTime;
  
    QVector<SessionInfo*> savedSessions;
    SessionInfo* currentSession;
    QVector<EEGSite*> sites;

    enum LightColor {RED, GREEN, BLUE, NONE};
    LightColor lightColor;
    bool isOn;


    int batteryLevel;
    bool powerStatus;
    bool hasContact;
    int remainingTime;
    bool hasBeenPaused;

    bool isSeshPaused;

    void setTime(const QDateTime &dt);
    void beginSesh();
    void endSesh();
    void powerButton();
    void pauseSesh();
    void playSesh();
    void stopSesh();

    void setBattery(int);

    void initiateContact();
    void stopContact();
    void generateSignals();

    void turnOffDevice();

    bool getIsSeshPaused();

    QVector<QString> readSessionHistory();
    void saveSession(QDateTime date, float baselineBefore, float baselineAfter);

private slots:
    void updateRound(); // Connected to QTimer
    void flashLight(); // Connected to another QTimer

private:
    QVector<QString> currSeshInfo;

    MainWindow* mainWindow;
    int sessionDuration;
    int roundTimer;
    int roundNumber;
    double treatmentOffset;

    // Therapy Process Functions
    double calculateOverallBaseline();
    void applyTreatment();
};
#endif // DEVICE_H
