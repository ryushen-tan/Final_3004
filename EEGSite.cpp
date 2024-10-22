#include "EEGSite.h"

EEGSite::EEGSite(QObject* parent) : QObject(parent), dominantFrequency(0.0), offset(0.0)
{
    // Initialize timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EEGSite::applyOffset);

    // Initialze and connect signal generator
    signalGenerator = new SignalGenerator();
    connect(signalGenerator, &SignalGenerator::signalGenerated, this, &EEGSite::handleSignal);
}

void EEGSite::startApplyingOffset(double offset)
{
    qDebug() << "Delivering 1 second feedback by applying offset to the dominant frequency of" << dominantFrequency << "Hz by" << dominantFrequency << "Hz +" << offset << "Hz";

    this->offset = offset;

    // Start applying offset every 1/16th of a second
    timer->start(62);
    QTimer::singleShot(1000, this, &EEGSite::stopApplyingOffset);
}

void EEGSite::stopApplyingOffset()
{
    // After applying offset to frequency, calculate and store the new dominant frequency
    dominantFrequency = calculateDominantFrequency();

    // Stop applying offset
    timer->stop();
}

void EEGSite::generateSignal()
{
    // Generate random amplitudes for each band
    double deltaAmp = getRandomInRange(1.0, 4.0);
    double thetaAmp = getRandomInRange(1.0, 4.0);
    double alphaAmp = getRandomInRange(1.0, 4.0);
    double betaAmp = getRandomInRange(1.0, 4.0);

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

    // Calculate and store the new dominant frequency
    dominantFrequency = calculateDominantFrequency();

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

void EEGSite::applyOffset()
{
    double newOffset = (dominantFrequency + offset) / 16.0;

    // check which frequency band is dominant and apply offset to that band
    if(dominantFrequency < 4.0)
    {
        signalGenerator->setDeltaFrequency(signalGenerator->getDeltaFrequency() + newOffset);
    }
    else if(dominantFrequency < 8.0)
    {
        signalGenerator->setThetaFrequency(signalGenerator->getThetaFrequency() + newOffset);
    }
    else if(dominantFrequency < 12.0)
    {
        signalGenerator->setAlphaFrequency(signalGenerator->getAlphaFrequency() + newOffset);
    }
    else
    {
        signalGenerator->setBetaFrequency(signalGenerator->getBetaFrequency() + newOffset);
    }
}
