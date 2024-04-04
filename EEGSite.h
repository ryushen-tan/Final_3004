#ifndef EEGSITE_H
#define EEGSITE_H

#include <QVector>

#include "EEGSignal.h"

class EEGSite {
public:
    EEGSite();

    EEGSignal* delta;
    EEGSignal* theta;
    EEGSignal* alpha;
    EEGSignal* beta;
    EEGSignal* EEGCombinedWave;

};

#endif // EEGSITE_H
