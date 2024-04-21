#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

#include <QObject>
#include <QTimer>
#include <QtMath>
#include <QDebug>

/* Purpose of class: Signal Generator QObject to generate and emit the signal of a sine wave at a certain frequency
 *
 * Data Members:
 * - QTimer* timer: A QTimer object to call and generate a signal based on the sample rate
 * - int sampleRateHz:
 * - double angle:
 *
 * Class functions:
 * - SignalGenerator(QObject* parent = nullptr): Constructor for the SignalGenerator class
 * - void start(): Starts the timer to generate the signal
 * - void stop(): Stops the timer from generating the signal
 * - void generateEEGSignal(): Generates the EEG signal
 */

class SignalGenerator : public QObject
{
    Q_OBJECT
public:
    SignalGenerator(QObject *parent = nullptr);

    // Getters for amplitudes
    double getDeltaAmplitude();
    double getThetaAmplitude();
    double getAlphaAmplitude();
    double getBetaAmplitude();
    
    double getDeltaFrequency();
    double getThetaFrequency();
    double getAlphaFrequency();
    double getBetaFrequency();

    // Setters for amplitudes
    void setDeltaAmplitude(double);
    void setThetaAmplitude(double);
    void setAlphaAmplitude(double);
    void setBetaAmplitude(double);

    // Setters for frequencies
    void setDeltaFrequency(double);
    void setThetaFrequency(double);
    void setAlphaFrequency(double);
    void setBetaFrequency(double);

    void setSampleRate(double);

    // Start and stop generating EEG signal
    void start();
    void stop();

signals:
    void signalGenerated(double);

public slots:
    void generateEEGSignal();

private:
    // Timer to generate signal based on sample rate
    QTimer* timer;

    double currTime;
    int sampleRateHz;
    
    // Amplitude for each band
    double deltaAmp;
    double thetaAmp;
    double alphaAmp;
    double betaAmp;

    // Frequencies for each band
    double deltaFreq;
    double thetaFreq;
    double alphaFreq;
    double betaFreq;
};
#endif // SIGNALGENERATOR_H
