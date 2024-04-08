#ifndef EEGSITE_H
#define EEGSITE_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include "SignalGenerator.h"

class EEGSite : public QObject
{
    Q_OBJECT
public:
    EEGSite();
    void generateSignal();
    void stopSignalGeneration();

signals:
    void signalGenerated(double value);

private slots:
    void handleSignal(double);

private:
    QVector<double> *EEGSignalBuffer;
    SignalGenerator* signalGenerator;
    double dominantFreq;  // To store the dominant frequency

    double calculateDominantFrequency(double, double, double, double, double, double, double, double);
    double getDominantFrequency();
    void applyOffset(double, double);

    double getRandomInRange(double, double);
};

#endif // EEGSITE_H
