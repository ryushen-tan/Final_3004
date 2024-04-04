#ifndef EEGSIGNAL_H
#define EEGSIGNAL_H

#include <QVector>

class EEGSignal {
public:
    EEGSignal(int, int);
    QVector<double> signalData;


private:
    int samplingRateHz;
    int sampleDuration;
};

#endif // EEGSIGNAL_H
