#include "EEGSite.h"

EEGSite::EEGSite() {
    EEGSignalBuffer = new QVector<double>();
    dominantFreq = 0.0;

    // Initialze and connect signal generator
    signalGenerator = new SignalGenerator();
    connect(signalGenerator, &SignalGenerator::signalGenerated, this, &EEGSite::handleSignal);
}

void EEGSite::generateSignal()
{
    // Generate random amplitudes for each band
    double deltaAmp = getRandomInRange(1.0, 3.0);
    double thetaAmp = getRandomInRange(1.0, 3.0);
    double alphaAmp = getRandomInRange(1.0, 3.0);
    double betaAmp = getRandomInRange(1.0, 3.0);

    // Generate random frequencies for each band
    double deltaFreq = getRandomInRange(1.0, 4.0);
    double thetaFreq = getRandomInRange(4.0, 8.0);
    double alphaFreq = getRandomInRange(8.0, 12.0);
    double betaFreq = getRandomInRange(12.0, 30.0);

    // Configure the SignalGenerator's frequencies
    signalGenerator->setDeltaFrequency(deltaFreq);
    signalGenerator->setThetaFrequency(thetaFreq);
    signalGenerator->setAlphaFrequency(alphaFreq);
    signalGenerator->setBetaFrequency(betaFreq);

    // Configure the SignalGenerator's amplitudes
    signalGenerator->setDeltaAmplitude(deltaAmp);


    signalGenerator->setThetaAmplitude(thetaAmp);
    signalGenerator->setAlphaAmplitude(alphaAmp);
    signalGenerator->setBetaAmplitude(betaAmp);

    // Start generating signals
    signalGenerator->start();
}

void EEGSite::stopSignalGeneration()
{
    signalGenerator->stop();
}

void EEGSite::handleSignal(double signal)
{
    // Add the signal to the buffer
    //EEGSignalBuffer->push_back(signal);

    // Emit signal (probably needed to plot signal)
    emit signalGenerated(signal);
}

double EEGSite::getRandomInRange(double min, double max)
{
   // Calculate the range
   double range = max - min;

   // Get random double [0,1)
   double random = QRandomGenerator::global()->generateDouble();

   // Return the random frequency within the target frequency range
   return max + (random * range);
}

double EEGSite::getDominantFrequency()
{
    dominantFreq = calculateDominantFrequency(signalGenerator->getDeltaAmplitude(), signalGenerator->getThetaAmplitude(), signalGenerator->getAlphaAmplitude(), signalGenerator->getBetaAmplitude(), signalGenerator->getDeltaFrequency(), signalGenerator->getThetaFrequency(), signalGenerator->getAlphaFrequency(), signalGenerator->getBetaFrequency());
    return dominantFreq;
}


double EEGSite::calculateDominantFrequency(double deltaAmp, double thetaAmp, double alphaAmp, double betaAmp, double deltaFreq, double thetaFreq, double alphaFreq, double betaFreq)
{
    return (deltaFreq * deltaAmp^2 + thetaFreq * thetaAmp^2 + alphaFreq * alphaAmp^2 + betaFreq * betaAmp^2) / (deltaAmp^2 + thetaAmp^2 + alphaAmp^2 + betaAmp^2);
}

void EEGSite::applyOffset(double offset, double dominantFreq)
{
    // apply offset to the dominant frequency in the EEG signal
    qDebug() << "Applying offset to the dominant frequency: " << dominantFreq << " by " << offset;
}