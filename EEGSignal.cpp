#include "EEGSignal.h"

EEGSignal::EEGSignal(int rate, int duration)
    : samplingRateHz(rate),
      sampleDuration(rate * duration)
{
    signalData.resize(sampleDuration);
}

int EEGSignal::getSampleDuration() const
{
    return sampleDuration;
}

int EEGSignal::getSamplingRateHz() const
{
    return samplingRateHz;
}

void EEGSignal::printSignal()
{
    for (int i = 0; i < sampleDuration; ++i) {
        qDebug() << signalData[i];
    }
}
