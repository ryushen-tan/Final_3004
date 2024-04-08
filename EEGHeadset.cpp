#include "EEGHeadset.h"

using namespace std;

EEGHeadset::EEGHeadset(int rate, int duration):
    samplingRateHz(rate),
    sampleDuration(duration)
{
    for (int i = 0; i < EEG_SITES; ++i) {
        sites.push_back(new EEGSite());
    }
}

void EEGHeadset::generateSignals()
{
    sites[0]->generateSignal();
    // for (int i = 0; i < EEG_SITES; ++i) {
    //     sites[i]->generateSignal();
    // }
}
