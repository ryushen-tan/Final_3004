#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    device = new Device();
    headset = new EEGHeadset(SAMPLING_RATE, SAMPLE_DURATION);

//    ui->menu->setDisabled(true);
//    ui->menuView->setDisabled(true);
//    ui->timeAndDateView->setDisabled(true);
//    ui->sessionLogsView->setDisabled(true);
//    ui->newSessionView->setDisabled(true);

    // Connections
    connect(ui->generateSignal, &QPushButton::clicked, this, &MainWindow::on_generateSignal_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_power_toggled(bool checked)
{
    //checked default state: false
    if (checked) {
        //enable menu and buttons that should be on when first turned on
//        ui->menuView->setEnabled(true);
//        ui->timeAndDateView->setDisabled(true);
//        ui->sessionLogsView->setDisabled(true);
//        ui->newSessionView->setDisabled(true);
//        checked = false;
    }
    else {
        //disable menu and buttons that should be off when turning device off
//        ui->menuView->setDisabled(true);
//        ui->timeAndDateView->setDisabled(true);
//        ui->sessionLogsView->setDisabled(true);
//        ui->newSessionView->setDisabled(true);
//        checked = true;
    }
}


void MainWindow::on_menu_clicked()
{
    //return to menu device view
    ui->menuView->setEnabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);
    ui->newSessionView->setDisabled(true);
}


void MainWindow::on_newSession_clicked()
{
    //switch to new session device view
    ui->newSessionView->setEnabled(true);
    ui->menuView->setDisabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);

    //instruct user to get headset and connect. Allow user to press start once connection is logged
}


void MainWindow::on_sessionLogs_clicked()
{
    //switch to session logs device view
    ui->sessionLogsView->setEnabled(true);
    ui->menuView->setDisabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->newSessionView->setDisabled(true);

    //display logs, allow scrolling through the logs
}


void MainWindow::on_setTimeAndDate_clicked()
{
    //switch to time and date device view
    ui->timeAndDateView->setEnabled(true);
    ui->menuView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);
    ui->newSessionView->setDisabled(true);
}


void MainWindow::on_play_toggled(bool checked)
{
    //default state: pause (not checked)
    if (checked) {
        //play
    }
    else {
        //pause (we need to press to start?)
    }
}


void MainWindow::on_stop_clicked()
{
    //stop session, erase all current session info
}


void MainWindow::on_submitTime_clicked()
{
    //get info from qtimedate widget, save
}


void MainWindow::on_connectPc_toggled(bool checked)
{
    //default state: false (not connected to PC)
    if (checked) {
        //connect to PC
    }
    else {
        //disconnect from PC
    }
}


void MainWindow::on_maxBattery_clicked()
{
    ui->battery->setValue(100);
    // this ^ is bandaid "fix", call setBattery function
}


void MainWindow::on_lowBattery_clicked()
{
    ui->battery->setValue(10);
    // this ^ is bandaid "fix", call setBattery function
}


void MainWindow::on_noBattery_clicked()
{
    ui->battery->setValue(0);
    // this ^ is bandaid "fix", call setBattery function
}


void MainWindow::on_generateSignal_clicked()
{
    //generate EEG signal, aka put on headset? or do we also have a connect headset button?

    // Calling generate signal function in EEGHeadset to test
    headset->generateSignals();
}


void MainWindow::on_eegToggle_toggled(bool checked)
{
    //toggle? not sure what this does
}


void MainWindow::on_contact_toggled(bool checked)
{
    //put on headset?
}

