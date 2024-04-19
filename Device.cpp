#include "Device.h"
#include "mainwindow.h"

#include "ui_mainwindow.h"


Device::Device(MainWindow* mw, QObject* parent) :
    QObject(parent),
    currTime(QDateTime::currentDateTime()),
    currentSession(nullptr),
    batteryLevel(100), //TODO: get battery value from file & store in variable
    powerStatus(false),
    hasContact(false),
    sessionDuration(0),
    roundTimer(0),
    roundNumber(0),
    treatmentOffset(0.0)
{
    mainWindow = mw;

    for (int i = 0; i < EEG_SITES; i++)
    {
        sites.append(new EEGSite());
    }

    timer = new QTimer(this);
    isSeshPaused = true;
    connect(timer, &QTimer::timeout, this, &Device::updateRound);

}

Device::~Device() {
    // Cleanup might be needed
}

void Device::setTime(const QDateTime &dt) {
    currTime = dt;
    qDebug() << currTime;
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
        //low power messfage... each session requires around 40% battery, so if there's less than 40% battery, the device will let the user know it needs to be charged
        std::cout << "ATTENTION: low power! Please charge device. 40% minimum needed for a new session.\n" << std::endl;
    }
    std::cout << "battery is set to " << batteryLevel << "\n" << std::endl;
}

void Device::initiateContact()
{
    hasContact = true;
    generateSignals();
}

void Device::stopContact()
{
    hasContact = false;

    // Stop all sites from generating signals
    for (int i = 0; i < EEG_SITES; ++i)
    {
        sites[i]->stopSignalGeneration();
    }
}

void Device::generateSignals()
{
    for (int i = 0; i < EEG_SITES; ++i)
    {
        sites[i]->generateSignal();
    }
}

void Device::beginSesh() {
    //create a new session
    SessionInfo* newSession = new SessionInfo();
    currentSession = newSession;

    // Reset for new session
    sessionDuration = 0;
    roundNumber = 0;
    isSeshPaused = true;
}

void Device::updateRound() {
    if(currentSession) {
        if (sessionDuration % ROUND_LEN == 0) {
            roundTimer = 0;
            roundNumber += 1; // Increment round first

            // clear graph so we can see the signal during analysis and treatment
            mainWindow->clearGraph();

            if(roundNumber < 5) {
                treatmentOffset += 5.0; // Increment Offet for 5hz,10hz,15hz,20hz treatments
            }

            // Round 1: calculate and save overall baseline for baselineBefore
            if (roundNumber == 1) {
                currentSession->baselineBefore = calculateOverallBaseline();
            }

            // Final analysis round: calculate and save overall baseline for baselineAfter during
            if(roundNumber == 5) {
                currentSession->baselineAfter = calculateOverallBaseline();
            }
        }
        sessionDuration += 1;
        roundTimer += 1;
        mainWindow->update_session_timer(sessionDuration);

        // After 5 sec analysis, do 1 sec treatment to all sites for the 4 rounds
        if(roundTimer == 5 && roundNumber < 5) {
            applyTreatment();
        }

        if(sessionDuration >= MAX_DUR) {
            endSesh();
            return;
        }


    }
}

void Device::endSesh() {
    timer->stop();
    currentSession->endSession();
    savedSessions.append(currentSession);
    saveSession(currTime, currentSession->baselineBefore, currentSession->baselineAfter);
    qDebug() << currentSession->baselineBefore;
    qDebug() << currentSession->baselineAfter;

    currentSession = nullptr;
    isSeshPaused = true;
    mainWindow->session_ended();
}

void Device::turnOffDevice()    // turning off device function: update battery value in file from variable - disable device view only
{
    //TODO: update battery value in file from variable
    mainWindow->power_off();
}

void Device::playSesh() {
    if(!currentSession) {
        beginSesh();
    }
    isSeshPaused = false;
    timer->start(SESH_UPDATE_FRQ);
}

void Device::pauseSesh() {
    //if(currentSession) {
        isSeshPaused = true;
        timer->stop();
    //}
}

void Device::stopSesh() {
    //if(currentSession) {
        timer->stop();
        currentSession = nullptr;
        isSeshPaused = true;
    //}
}

bool Device::getIsSeshPaused() { return isSeshPaused; }

void Device::saveSession(QDateTime date, float baselineBefore, float baselineAfter){
    QString filename = "sessionRecords.txt";
    QFile file(filename);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << (date.toString()) << ";" << baselineBefore << ";" << baselineAfter << Qt::endl;
            file.close();
            qDebug() << "Data saved to file:" << filename;
        } else {
            qDebug() << "Error: Unable to open file" << filename << "for writing.";
    }
}

double Device::calculateOverallBaseline()
{
    double baseline = 0.0;

    for(int i = 0; i < EEG_SITES; ++i)
    {
        baseline += sites[i]->getDominantFrequency();
    }

    return baseline / EEG_SITES;
}

void Device::applyTreatment()
{
    for(int i = 0; i < EEG_SITES; ++i)
    {
        sites[i]->startApplyingOffset(treatmentOffset);
    }
}

QVector<QString> Device::readSessionHistory(){
    QVector<QString> ret;
    QString filename = "sessionRecords.txt";

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            ret.append(line);
        }
        file.close();
        qDebug() << "Data read from file:" << filename;
    } else {
        qDebug() << "Error: Unable to open file" << filename << "for reading.";
    }
    return ret;
}
