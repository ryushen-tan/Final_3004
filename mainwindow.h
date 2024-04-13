#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SAMPLING_RATE 60
#define SAMPLE_DURATION 6

#include <QMainWindow>
//#include <QtCharts>
//#include <QChartView>
//#include <QLineSeries>

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

    void update_session_timer(int time);

private slots:
    void on_power_toggled(bool checked);

    void on_menu_clicked();

    void on_newSession_clicked();

    void on_sessionLogs_clicked();

    void on_setTimeAndDate_clicked();

    void on_play_toggled(bool checked);

    void on_stop_clicked();

    void on_submitTime_clicked();

    void on_connectPc_toggled(bool checked);

    void on_maxBattery_clicked();

    void on_lowBattery_clicked();

    void on_noBattery_clicked();

    void on_contact_toggled(bool checked);

    void on_set_clicked();

private:
    Ui::MainWindow *ui;
    Device* device;

//    QLineSeries* series;
};
#endif // MAINWINDOW_H
