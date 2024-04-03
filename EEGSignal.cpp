#include "EEGSignal.h"

EEGSignal::EEGSignal(int rate, int duration)
    : samplingRateHz(rate),
      sampleDuration(rate * duration)
{
    signalData.resize(sampleDuration);
}
