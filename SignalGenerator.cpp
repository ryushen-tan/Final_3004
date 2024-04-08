#include "SignalGenerator.h"

SignalGenerator::SignalGenerator(QObject *parent):
    QObject(parent),
    currTime(0.0),
    sampleRateHz(60),
    deltaAmp(1.0),
    thetaAmp(1.0),
    alphaAmp(1.0),
    betaAmp(1.0),
    deltaFreq(2.0),
    thetaFreq(6.0),
    alphaFreq(10.0),
    betaFreq(21.0)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SignalGenerator::generateEEGSignal); // Every timeout it generates a signal
}

double SignalGenerator::getDeltaAmplitude()
{
    return deltaAmp;
}

double SignalGenerator::getThetaAmplitude()
{
    return thetaAmp;
}

double SignalGenerator::getAlphaAmplitude()
{
    return alphaAmp;
}

double SignalGenerator::getBetaAmplitude()
{
    return betaAmp;
}

double SignalGenerator::getDeltaFrequency()
{
    return deltaFreq;
}

double SignalGenerator::getThetaFrequency()
{
    return thetaFreq;
}

double SignalGenerator::getAlphaFrequency()
{
    return alphaFreq;
}

double SignalGenerator::getBetaFrequency()
{
    return betaFreq;
}

void SignalGenerator::setDeltaAmplitude(double amp)
{
    deltaAmp = amp;
}

void SignalGenerator::setThetaAmplitude(double amp)
{
    thetaAmp = amp;
}

void SignalGenerator::setAlphaAmplitude(double amp)
{
    alphaAmp = amp;
}

void SignalGenerator::setBetaAmplitude(double amp)
{
    betaAmp = amp;
}

void SignalGenerator::setDeltaFrequency(double freq)
{
    deltaFreq = freq;
}

void SignalGenerator::setThetaFrequency(double freq)
{
    thetaFreq = freq;
}

void SignalGenerator::setAlphaFrequency(double freq)
{
    alphaFreq = freq;
}

void SignalGenerator::setBetaFrequency(double freq)
{
    betaFreq = freq;
}

void SignalGenerator::start()
{
    timer->start(1000 / sampleRateHz); // Updates based on sample rate
}

void SignalGenerator::stop()
{
    timer->stop();
}

void SignalGenerator::generateEEGSignal() {
    // Generate signal for each frequency band
    double delta = deltaAmp * sin(2 * M_PI * deltaFreq * currTime);
    double theta = thetaAmp * sin(2 * M_PI * thetaFreq * currTime);
    double alpha = alphaAmp * sin(2 * M_PI * alphaFreq * currTime);
    double beta = betaAmp * sin(2 * M_PI * betaFreq * currTime);

    // Add the signals
    double EEGSignal = delta + theta + alpha + beta;

    // Increment current time based on Hz
    currTime += 1.0 / sampleRateHz;

    // Testing
    qDebug() << EEGSignal;

    // Emit the generated sine wave value
    emit signalGenerated(EEGSignal);
}
