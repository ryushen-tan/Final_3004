#ifndef EEGHEADSET_H
#define EEGHEADSET_H

#define EEG_SITES 7
#define PI

#include <QVector>
#include <cmath>

#include "EEGSite.h"
#include "EEGSignal.h"

class EEGHeadset {
public:
    EEGHeadset(int, int);

    void generateSignals();

private:
    QVector<EEGSite*> sites;
    int samplingRateHz;
    int sampleDuration;
};
#endif // EEGHEADSET_H
