#ifndef EEGSITE_H
#define EEGSITE_H

#include <QVector>

#include "EEGSignal.h"

class EEGSite {
public:
    EEGSignal delta;
    EEGSignal theta;
    EEGSignal alpha;
    EEGSignal beta;

    QVector<double> getCombinedWave() const;

};

#endif // EEGSITE_H
