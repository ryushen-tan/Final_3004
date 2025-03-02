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

    lightColor = NONE;
    isOn = false;

    timer = new QTimer(this);
    lightTimer = new QTimer(this);
    isSeshPaused = true;
    connect(timer, &QTimer::timeout, this, &Device::updateRound);
    connect(lightTimer, &QTimer::timeout, this, &Device::flashLight);

    lightTimer->start(LIGHT_FLASH_FRQ);
}

Device::~Device() {
    // Cleanup might be needed
    delete timer;
    delete lightTimer;
    for (EEGSite* e : sites) {
        delete e;
    }
    for(SessionInfo* e : savedSessions) {
        delete e;
    }
}

void Device::setTime(const QDateTime &dt) {
    currTime = dt;
    qDebug() << currTime;
}

void Device::powerButton()
{
    if (powerStatus) {
        turnOffDevice();    // turning off function
        stopSesh();
        powerStatus = false;
    }
    else {
        if (batteryLevel > 0) {
            powerStatus = true;
        }
        else {
            std::cout << "ATTENTION: no power! Device cannot power on...\n" << std::endl;
        }
    }

}

void Device::setBattery(int charge)
{
    if (charge < 0) // if charge value is negative, this is a battery drain of (int) charge %
    {
        batteryLevel += charge;
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
    else if (batteryLevel < 30)
    {
        //low power messfage... each session requires around 30% battery, so if there's less than 30% battery, the device will let the user know it needs to be charged
        std::cout << "ATTENTION: low power! Please charge device. 30% minimum needed for a new session.\n" << std::endl;
    }
    mainWindow->updateBattery(batteryLevel);
}

void Device::initiateContact()
{
    lightColor = BLUE;
    hasContact = true;
    mainWindow->setDisabledPlayButton(false);
    generateSignals();
}

void Device::stopContact()
{
    lightColor = RED;
    hasContact = false;

    // Stop all sites from generating signals
    for (int i = 0; i < EEG_SITES; ++i)
    {
        sites[i]->stopSignalGeneration();
    }

    if (currentSession) {
        pauseSesh();
        mainWindow->setDisabledPlayButton(true);
        // Start 5 second timer and if there is still no contact, stop the session
        QTimer::singleShot(5000, this, [this]() {
            if(!hasContact) {
                mainWindow->on_power_clicked();
            }
        });
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
    lightColor = NONE;
}

void Device::updateRound() {
    if(currentSession) {
        if(sessionDuration % ROUND_LEN == 0) {
            roundTimer = 0;
            roundNumber += 1; // Increment round first
            std::cout << "ROUND "<< roundNumber <<" OF THERAPY:" << std::endl;

            // clear graph so we can see the signal during analysis and treatment
            mainWindow->clearGraph();

            if (roundNumber < 5) {
                treatmentOffset += 5.0; // Increment Offet for 5hz,10hz,15hz,20hz treatments
            }

            // Round 1: calculate and save overall baseline for baselineBefore
            if (roundNumber == 1) {
                currentSession->setBaselineBefore(calculateOverallBaseline());
            }

            // Final analysis round: calculate and save overall baseline for baselineAfter during
            if(roundNumber == 5) {
                currentSession->setBaselineAfter(calculateOverallBaseline());
            }
        }
        sessionDuration += 1;
        roundTimer += 1;
        mainWindow->update_session_timer(sessionDuration);
        setBattery(-1);

        // After 5 sec analysis, do 1 sec treatment to all sites for the 4 rounds
        if(roundTimer == 5 && roundNumber < 5) {
            lightColor = GREEN;
            applyTreatment();
        } else { lightColor = BLUE; }

        if(sessionDuration >= MAX_DUR) {
            endSesh();
            return;
        }


    }
}

void Device::endSesh() {
    timer->stop();
    savedSessions.append(currentSession);
    saveSession(currTime, currentSession->getBaselineBefore(), currentSession->getBaselineAfter());
    qDebug() << currentSession->getBaselineBefore();
    qDebug() << currentSession->getBaselineAfter();

    currentSession = nullptr;
    isSeshPaused = true;
    lightColor = NONE;
    mainWindow->session_ended();
}

void Device::turnOffDevice()    // turning off device function: update battery value in file from variable - disable device view only
{
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
        isSeshPaused = true;
        timer->stop();
}

void Device::stopSesh() {
        timer->stop();
        delete currentSession;
        currentSession = nullptr;
        isSeshPaused = true;
}

bool Device::getIsSeshPaused() { return isSeshPaused; }

void Device::saveSession(QDateTime date, float baselineBefore, float baselineAfter) {
    QString recordsDirectory = QDir::homePath() + "/Medical_Records/";
    QString filename = recordsDirectory + "sessionRecords.txt";
    QDir recordsDir(recordsDirectory);
    if (!recordsDir.exists()) {
        if (!recordsDir.mkpath(recordsDirectory)) {
            qDebug() << "Error: Unable to create directory" << recordsDirectory;
            return;
        }
    }

    QFile file(filename);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << date.toString() << ";" << baselineBefore << ";" << baselineAfter << Qt::endl;
        file.close();
        qDebug() << "Data saved to file:" << filename;
    } else {
        qDebug() << "Error: Unable to open file" << filename << "for writing.";
    }
}

QVector<QString> Device::readSessionHistory() {
    QVector<QString> ret;
    QString recordsDirectory = QDir::homePath() + "/Medical_Records/";
    QString filename = recordsDirectory + "sessionRecords.txt";

    QDir recordsDir(recordsDirectory);
    if (!recordsDir.exists()) {
        if (!recordsDir.mkpath(recordsDirectory)) {
            qDebug() << "Error: Unable to create directory" << recordsDirectory;
            return ret;
        }
    }

    QFile file(filename);
    if (!file.exists()) {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Error: Unable to create file" << filename << "for writing.";
            return ret;
        }
        qDebug() << "File created:" << filename;
        file.close();
    }

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

double Device::calculateOverallBaseline()
{    
    double baseline = 0.0;

    for(int i = 0; i < EEG_SITES; ++i)
    {
        baseline += sites[i]->getDominantFrequency();
    }

    std::cout << "Calculating overall dominant frequency as baseline...\n" << std::endl;

    return baseline / EEG_SITES;
}

void Device::applyTreatment()
{
    for(int i = 0; i < EEG_SITES; ++i)
    {
        sites[i]->startApplyingOffset(treatmentOffset);
    }
}

void Device::flashLight() {
//    if (!powerStatus) {return;}
    if(hasContact) {
        mainWindow->updateLight(BLUE, true);
    } else if (currentSession) {
        mainWindow->updateLight(BLUE, false);
        mainWindow->updateLight(RED, isOn);
        isOn = !isOn;
        cout << "Beep!" << endl;
    }
    else {
        mainWindow->updateLight(BLUE, false);
    }

    if(lightColor == GREEN && currentSession && hasContact) {
        mainWindow->updateLight(GREEN, isOn);
        isOn = !isOn;
    }

}
