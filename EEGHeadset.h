#ifndef EEGHEADSET_H
#define EEGHEADSET_H

#define EEG_SITES 7

#include <QVector>

#include "EEGSite.h"

class EEGHeadset {
public:
    EEGHeadset(int, int);

private:
    QVector<EEGSite> sites;
    int samplingRateHz;
    int sampleDuration;

    void generateSignals();
    void generateSineWave(double, double, int, double = 0.0);

};

#endif // EEGHEADSET_H
