#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SAMPLING_RATE 60
#define SAMPLE_DURATION 6

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QString>
#include <QStringList>

#include "Device.h"

#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void power_off();

public slots:

    void on_power_clicked();

    void on_menu_clicked();

    void on_newSession_clicked();

    void on_sessionLogs_clicked();

    void on_setTimeAndDate_clicked();

    void on_play_clicked();

    void on_stop_clicked();

    void on_submitTime_clicked();

    void on_connectPc_clicked();

    void on_maxBattery_clicked();

    void on_lowBattery_clicked();

    void on_noBattery_clicked();

    void on_contact_clicked();

    void on_set_clicked();

    void plotEEGSignal(double);
    void updateSiteToPlot(int);
    void clearGraph();

private slots:
    void on_logList_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Device* device;
    bool checked_power;
    bool checked_play;
    bool checked_connectPC;
    bool checked_headsetContact;

//    QVector<QString> datesAndTimes;  //dummy log list
    QStringList datesAndTimes;  //dummy log list
    QLineSeries* series;
    QChart* chart;
    QChartView* chartView;
    QValueAxis* axisX;
    QValueAxis* axisY;

    EEGSite* currSite;
    static qreal plotTime;
};
#endif // MAINWINDOW_H
