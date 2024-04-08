#ifndef EEGSIGNAL_H
#define EEGSIGNAL_H

#include <QVector>
#include <QDebug>

class EEGSignal {
public:
    EEGSignal(int, int);
    QVector<double> signalData;

    int getSampleDuration() const;
    int getSamplingRateHz() const;

    // Test Function
    void printSignal();

private:
    int samplingRateHz;
    int sampleDuration;
};

#endif // EEGSIGNAL_H
