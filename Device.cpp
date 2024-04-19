#include "Device.h"
#include "mainwindow.h"

#include "ui_mainwindow.h"


Device::Device(MainWindow* mw, QObject* parent) :
    QObject(parent),
    currTime(QDateTime::currentDateTime()),
    currentSession(nullptr),
    batteryLevel(100), //TODO: get battery value from file & store in variable
    powerStatus(false),
    hasContact(false)
{
    mainWindow = mw;

    for (int i = 0; i < EEG_SITES; i++)
    {
        sites.append(new EEGSite());
    }

    timer = new QTimer(this);
    isSeshPaused = true;
    connect(timer, &QTimer::timeout, this, &Device::updateRound);

    sessionDuration = 0;
    numberOfRound = 1;

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
    sessionDuration = 0;
    numberOfRound = 1;
    isSeshPaused = true;

    newSession->baselineBefore = calculateOverallBaseline();
   qDebug() << newSession->baselineBefore;
}

void Device::updateRound() {
    if(currentSession) {
        sessionDuration += 1;
        numberOfRound = static_cast<int>(sessionDuration / ROUND_LEN);
        mainWindow->update_session_timer(sessionDuration);
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
