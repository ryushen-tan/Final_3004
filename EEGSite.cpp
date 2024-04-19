#include "EEGSite.h"

EEGSite::EEGSite() {
    EEGSignalBuffer = new QVector<double>();
    dominantFrequency = 0.0;

    // Initialze and connect signal generator
    signalGenerator = new SignalGenerator();
    connect(signalGenerator, &SignalGenerator::signalGenerated, this, &EEGSite::handleSignal);
}

void EEGSite::generateSignal()
{
    // Generate random amplitudes for each band
    double deltaAmp = getRandomInRange(0.0, 5.0);
    double thetaAmp = getRandomInRange(0.0, 5.0);
    double alphaAmp = getRandomInRange(0.0, 5.0);
    double betaAmp = getRandomInRange(0.0, 5.0);

    // Generate random frequencies for each band
    double deltaFreq = getRandomInRange(1.0, 4.0);
    double thetaFreq = getRandomInRange(4.0, 8.0);
    double alphaFreq = getRandomInRange(8.0, 12.0);
    double betaFreq = getRandomInRange(12.0, 30.0);

    // Calculate and store the new dominant frequency
    dominantFrequency = calculateDominantFrequency();

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
   return min + (random * range);
}

double EEGSite::getDominantFrequency()
{
    return dominantFrequency;
}


double EEGSite::calculateDominantFrequency()
{
    return (signalGenerator->getDeltaFrequency() * pow(signalGenerator->getDeltaAmplitude(), 2) + signalGenerator->getThetaFrequency() * pow(signalGenerator->getThetaAmplitude(), 2) + signalGenerator->getAlphaFrequency() * pow(signalGenerator->getAlphaAmplitude(), 2) + signalGenerator->getBetaFrequency() * pow(signalGenerator->getBetaAmplitude(), 2)) / (pow(signalGenerator->getDeltaAmplitude(), 2) + pow(signalGenerator->getThetaAmplitude(), 2) + pow(signalGenerator->getAlphaAmplitude(), 2) + pow(signalGenerator->getBetaAmplitude(), 2));
}

void EEGSite::applyOffset(double offset, double dominantFreq)
{
    // apply offset to the dominant frequency in the EEG signal
    qDebug() << "Applying offset to the dominant frequency: " << dominantFreq << " by " << offset;

    // After applying offset to frequency, calculate and store the new dominant frequency
    dominantFrequency = calculateDominantFrequency();
}
