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
    // To Test
    sites[0]->generateSignal();

// Will probably need to look into threads later on to generate all 7 sites signal
//    for (int i = 0; i < EEG_SITES; ++i) {
//        sites[i]->generateSignal();
//    }
}
