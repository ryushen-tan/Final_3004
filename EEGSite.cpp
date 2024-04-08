#include "EEGSite.h"

EEGSite::EEGSite() {
    dominantFreq = 0.0;
    connect(&signalGenerator, &SignalGenerator::signalGenerated, this, &EEGSite::handleSignal);
    EEGSignalBuffer = new QVector<double>();
}

void EEGSite::generateSignal()
{
    // double deltaFreq = 2.0;
    // double thetaFreq = 6.0;
    // double alphaFreq = 10.0;
    // double betaFreq = 21.0;
    // Configure the SignalGenerator's frequencies
//    signalGenerator.setDeltaFrequency(deltaFreq);
//    signalGenerator.setThetaFrequency(thetaFreq);
//    signalGenerator.setAlphaFrequency(alphaFreq);
//    signalGenerator.setBetaFrequency(betaFreq);

    // Start generating signals
    signalGenerator.start();
}

void EEGSite::handleSignal(double signal)
{
    // Add the signal to the buffer
    //EEGSignalBuffer->push_back(signal);

    // Emit the treated signal
    emit signalGenerated(signal);
}
