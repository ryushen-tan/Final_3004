#ifndef EEGHEADSET_H
#define EEGHEADSET_H

#define EEG_SITES 7
#define PI

#include <QVector>

#include "EEGSite.h"
#include "EEGSignal.h"

class EEGHeadset {
public:
    EEGHeadset(int, int);

private:
    QVector<EEGSite*> sites;
    int samplingRateHz;
    int sampleDuration;

    void generateSignals();
    EEGSignal* generateSineWave(double, double, int, double = 0.0);

};

#endif // EEGHEADSET_H
