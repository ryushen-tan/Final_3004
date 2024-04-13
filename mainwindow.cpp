#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    device = new Device(this);

//    series = new QLineSeries();

//    ui->menu->setDisabled(true);
//    ui->menuView->setDisabled(true);
//    ui->timeAndDateView->setDisabled(true);
//    ui->sessionLogsView->setDisabled(true);
//    ui->newSessionView->setDisabled(true);

    // Connections
    //connect(ui->generateSignal, &QPushButton::clicked, this, &MainWindow::on_generateSignal_clicked);
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

    // start a new session on the device
    device->beginSesh();
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
    device->setBattery(100);
}


void MainWindow::on_lowBattery_clicked()
{
    ui->battery->setValue(39);
    device->setBattery(39);
}


void MainWindow::on_noBattery_clicked()
{
    ui->battery->setValue(0);
    device->setBattery(0);
}


void MainWindow::on_contact_toggled(bool checked)
{
    // Calling generate signal function in EEGHeadset to test
    device->initiateContact();
}


void MainWindow::on_set_clicked()
{
    std::cout << "set battery to " << ui->percentage->value() << "\n" << std::endl;
    ui->battery->setValue(ui->percentage->value());
    device->setBattery(ui->percentage->value());
}

