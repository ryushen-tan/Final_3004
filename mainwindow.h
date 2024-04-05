#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SAMPLING_RATE 60
#define SAMPLE_DURATION 6

#include <QMainWindow>

#include "Device.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
    Device* device;
};
#endif // MAINWINDOW_H
