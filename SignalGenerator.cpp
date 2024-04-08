#include "SignalGenerator.h"

SignalGenerator::SignalGenerator(QObject *parent):
    QObject(parent),
    sampleRateHz(60),
    amplitude(1.0),
    deltaFreq(2.0),
    thetaFreq(6.0),
    alphaFreq(10.0),
    betaFreq(21.0)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SignalGenerator::generateEEGSignal); // Every timeout it generates a signal
}

double SignalGenerator::getFrequency()
{
    return deltaFreq;
}

double SignalGenerator::getAmplitude()
{
    return amplitude;
}

void SignalGenerator::setDeltaFrequency(double freq)
{
    deltaFreq = freq;
}

void SignalGenerator::start()
{
    timer->start(1000 / sampleRateHz); // Updates based on sample rate
}

void SignalGenerator::generateEEGSignal() {
    // Generate signal for each frequency band
    double delta = amplitude * sin(2 * M_PI * deltaFreq * currTime);
    double theta = amplitude * sin(2 * M_PI * thetaFreq * currTime);
    double alpha = amplitude * sin(2 * M_PI * alphaFreq * currTime);
    double beta = amplitude * sin(2 * M_PI * betaFreq * currTime);

    // Add the signals
    double EEGSignal = delta + theta + alpha + beta;

    // Increment current time based on Hz
    currTime += 1.0 / sampleRateHz;

    qDebug() << EEGSignal;

    // Emit the generated sine wave value
    emit signalGenerated(EEGSignal);
}
