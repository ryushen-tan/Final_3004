#ifndef EEGSIGNAL_H
#define EEGSIGNAL_H

#include <QVector>

class EEGSignal {
public:
    EEGSignal(int, int);

private:
    int samplingRateHz;
    int sampleDuration;
    QVector<double> signalData;
};

#endif // EEGSIGNAL_H
