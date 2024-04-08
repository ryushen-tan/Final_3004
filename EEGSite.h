#ifndef EEGSITE_H
#define EEGSITE_H

#include <QObject>
#include <QVector>
#include "signalgenerator.h" // Assume you have signalgenerator.h

class EEGSite : public QObject
{
    Q_OBJECT
public:
    EEGSite();
    void generateSignal();

signals:
    void signalGenerated(double value);

private slots:
    void handleSignal(double);

private:
    QVector<double> *EEGSignalBuffer;
    SignalGenerator signalGenerator;
    double dominantFreq;  // To store the dominant frequency

    double calculateDominantFrequency(const QVector<double> *buffer);
    double applyTreatment(double, double);
};

#endif // EEGSITE_H
