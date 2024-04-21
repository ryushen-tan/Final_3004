#ifndef EEGSITE_H
#define EEGSITE_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>
#include "SignalGenerator.h"

/* Purpose of class: EEGSite to generate an EEG signal for a specific site
 *
 * Data Members:
 * - QTimer* timer: A timer to apply an offset to the signal at 1/16th of a second
 * - SignalGenerator* signalGenerator: A SignalGenerator object to generate the EEG signal
 * - double dominantFreq: To store the dominant frequency
 *
 * Class functions:
 * - EEGSite(): Constructor to initialize the EEGSite object
 * - generateSignal(): To generate the EEG signal
 * - stopSignalGeneration(): To stop the signal generation
 * - signalGenerated(double): Slot to handle the signal generated
 * - calculateDominantFrequency(): To calculate the dominant frequency
 * - getDominantFrequency(): To get the dominant frequency
 * - applyOffset(double, double): To apply an offset to the signal for treatment
 * - getRandomInRange(double, double): Helper function to get a random number in a range
 */

class EEGSite : public QObject
{
    Q_OBJECT
public:
    EEGSite(QObject* parent = nullptr);
    void generateSignal();
    void stopSignalGeneration();

    double getDominantFrequency();

    void startApplyingOffset(double);

signals:
    void signalGenerated(double value);

private slots:
    void handleSignal(double);
    void applyOffset();
    void stopApplyingOffset();

private:
    QTimer* timer;
    SignalGenerator* signalGenerator;
    double dominantFrequency;  // To store the dominant frequency
    double offset; // To store the offset value

    double calculateDominantFrequency();

    double getRandomInRange(double, double);
};

#endif // EEGSITE_H
