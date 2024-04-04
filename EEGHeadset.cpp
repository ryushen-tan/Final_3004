#include "EEGHeadset.h"
#include <cmath>

using namespace std;

EEGHeadset::EEGHeadset(int rate, int duration):
    samplingRateHz(rate),
    sampleDuration(duration)
{

}

void EEGHeadset::generateSignals()
{
    // Approximate frequency ranges for brainwave bands
    double deltaFreq = 2.0;     // Delta
    double thetaFreq = 6.0;     // Theta
    double alphaFreq = 10.0;    // Alpha
    double betaFreq = 20.0;     // Beta

    for (int i = 0; i < sites.size(); ++i) {
        sites[i]->delta = generateSineWave(deltaFreq, 1.0, sampleDuration);
        sites[i]->theta = generateSineWave(thetaFreq, 1.0, sampleDuration);
        sites[i]->alpha = generateSineWave(alphaFreq, 1.0, sampleDuration);
        sites[i]->beta = generateSineWave(betaFreq, 1.0, sampleDuration);
    }
}

EEGSignal* EEGHeadset::generateSineWave(double frequency, double amplitude, int duration, double phase)
{
    EEGSignal* signal = new EEGSignal(samplingRateHz, sampleDuration);

    for (int i = 0; i < duration; ++i) {
        signal->signalData[i] = amplitude * sin(2 * M_PI * frequency * i / duration + phase);
    }
    return signal;
}
