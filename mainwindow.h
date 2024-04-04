#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SAMPLING_RATE 60
#define SAMPLE_DURATION 60

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

private:
    Ui::MainWindow *ui;
    Device* device;
};
#endif // MAINWINDOW_H
