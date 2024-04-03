#ifndef EEGSIGNAL_H
#define EEGSIGNAL_H

#include <QVector>

class EEGSignal {
public:
    EEGSignal(int, int);

    double& operator[](int index) { return data[index]; }

private:
    int samplingRateHz;
    int sampleDuration;
    QVector<double> data;
};

#endif // EEGSIGNAL_H
