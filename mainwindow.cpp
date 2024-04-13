#include "mainwindow.h"
#include "ui_mainwindow.h"

qreal MainWindow::plotTime = 0.0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    device = new Device(this);
    checked_power = false;
    checked_play = false;
    checked_connectPC = false;
    checked_headsetContact = false;


    series = new QLineSeries();
    chart = new QChart();
    chartView = new QChartView(chart);

    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("EEG Signal Plot");


    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->signalPlotFrame);
    chartView->setFixedSize(900, 350);

    axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    axisX->setRange(0, 6);

    axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    axisY->setRange(-20,20);

    // site combo bbox
    for (int i = 1; i <= EEG_SITES; ++i) {
        ui->sitePlotComboBox->addItem(QString("Site %1").arg(i));
    }


    // Connect First site in combobox's signal to plot
    connect(device->sites[0], &EEGSite::signalGenerated, this, &MainWindow::plotEEGSignal);


    connect(ui->sitePlotComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateSiteToPlot);


    //dummy log list, front end only *this should be populated from text file when we actually have one, using a for/while loop
    datesAndTimes.append("jan 1, 2024 00:00:00");
    datesAndTimes.append("jan 2, 2024 15:00:00");
    datesAndTimes.append("apr 12, 2024 15:39:07");
    datesAndTimes.append("up up down down left right left right a b");
    datesAndTimes.append("5");
    datesAndTimes.append("127fhjklselu");
    datesAndTimes.append("however many it takes");
    datesAndTimes.append("oct 22, 2024 17:14:35");
    datesAndTimes.append("jan 1, 2024 00:00:00");
    datesAndTimes.append("jan 2, 2024 15:00:00");
    datesAndTimes.append("apr 12, 2024 15:39:07");
    datesAndTimes.append("up up down down left right left right a b");
    datesAndTimes.append("5");
    datesAndTimes.append("127fhjklselu");
    datesAndTimes.append("however many it takes");
    datesAndTimes.append("oct 22, 2024 17:14:35");

    ui->menu->setDisabled(true);
    ui->menuView->setDisabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);
    ui->newSessionView->setDisabled(true);
    ui->ComputerView->setDisabled(true);

    // Connections
    //connect(ui->generateSignal, &QPushButton::clicked, this, &MainWindow::on_generateSignal_clicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearGraph);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_power_clicked()
{

    //checked default state: false
    if (checked_power) {
        //disable menu and buttons that should be off when turning device off
        ui->menuView->setDisabled(true);
        ui->timeAndDateView->setDisabled(true);
        ui->sessionLogsView->setDisabled(true);
        ui->newSessionView->setDisabled(true);
        ui->menu->setDisabled(true);
        checked_power = false;
        std::cout << "checked power is now false" << std::endl;
    }
    else {
        if (ui->battery->value() > 0)
        {
            //enable menu and buttons that should be on when turned on
            ui->menuView->setEnabled(true);
            ui->timeAndDateView->setDisabled(true);
            ui->sessionLogsView->setDisabled(true);
            ui->newSessionView->setDisabled(true);
            ui->menu->setEnabled(true);
            checked_power = true;
            std::cout << "checked power is now true" << std::endl;
        }
    }
}

void MainWindow::power_off()    //duplicate of on_power_clicked() but ONLY turns everything off
{
        //disable menu and buttons that should be off when turning device off
        ui->menuView->setDisabled(true);
        ui->timeAndDateView->setDisabled(true);
        ui->sessionLogsView->setDisabled(true);
        ui->newSessionView->setDisabled(true);
        ui->menu->setDisabled(true);
        checked_power = false;
        std::cout << "checked power is now false" << std::endl;
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
    //ui->play->setDisabled(true);

    //TODO: reset timer and progress bar

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
    ui->sessionsLogWidget->addItems(datesAndTimes);
}


void MainWindow::on_setTimeAndDate_clicked()
{
    //switch to time and date device view
    ui->timeAndDateView->setEnabled(true);
    ui->menuView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);
    ui->newSessionView->setDisabled(true);
}


void MainWindow::on_play_clicked()
{
    //default state: pause (not checked)
    if (checked_play) {
        //TODO: pause session UI

        checked_play = false;   // set button ready to play when next clicked
        std::cout << "play\nchecked play is now false" << std::endl;
    }
    else {
        //TODO: play session UI
        checked_play = true;    // set button ready to pause when next clicked
        std::cout << "checked play is now true" << std::endl;
    }
}


void MainWindow::on_stop_clicked()
{
    //TODO: stop session, erase all current session info.
    ui->menuView->setEnabled(true);
    ui->timeAndDateView->setDisabled(true);
    ui->sessionLogsView->setDisabled(true);
    ui->newSessionView->setDisabled(true);
    ui->menu->setEnabled(true);
    std::cout << "session stopped" << std::endl;
}


void MainWindow::on_submitTime_clicked()
{
    //TODO: get info from qtimedate widget, set
    device->setTime(ui->dateTimeEdit->dateTime());
}


void MainWindow::on_connectPc_clicked()
{
    //default state: false (not connected to PC)
    if (checked_connectPC) {
        //disconnect from PC
        checked_connectPC = false;  // set button ready to disconnect when next clicked
        std::cout << "checked connect pc is now false\n ready to disconnect" << std::endl;
    }
    else {
        //connect to PC
        ui->ComputerView->setEnabled(true);

        //dummy list of log dates and times

        ui->logList->addItems(datesAndTimes);   //add list to dropdown

        checked_connectPC = true;   // set button ready to connect when next clicked
        std::cout << "checked connect pc is now true \n ready to connect" << std::endl;
    }
}


void MainWindow::on_maxBattery_clicked()
{
    ui->battery->setValue(100); //set UI battery level
    device->setBattery(100);    //set battery value
}


void MainWindow::on_lowBattery_clicked()
{
    ui->battery->setValue(39);  //set UI battery level
    device->setBattery(39); //set battery value
}


void MainWindow::on_noBattery_clicked()
{
    ui->battery->setValue(0);   //set UI battery level
    device->setBattery(0);  //set battery value
}


void MainWindow::on_contact_clicked()
{
    if (checked_headsetContact) {
        checked_headsetContact = false;  // set button ready to connect when next clicked
        std::cout << "checked headset contact is now false\n ready to disconnect" << std::endl;
    }
    else {
        // Calling generate signal function in EEGHeadset to test
        device->initiateContact();
        checked_headsetContact = false; // set button ready to disconnect when next clicked
        std::cout << "checked headset contact is now true\n ready to connect" << std::endl;
    }

}


void MainWindow::on_set_clicked()
{
    ui->battery->setValue(ui->percentage->value());
    device->setBattery(ui->percentage->value());
}


void MainWindow::update_session_timer(int time) {
    ui->sessionTimer->setText(QString::number(MAX_DUR - time));
    ui->sessionBar->setValue(static_cast<int>(time * 100 / MAX_DUR));
}

void MainWindow::plotEEGSignal(double value)
{
    series->append(plotTime, value);

    qreal sampleRate = SAMPLING_RATE;
    plotTime += 1.0 / sampleRate;

    //axisX->setRange(0, plotTime);
}

void MainWindow::updateSiteToPlot(int index)
{
    if (index >= 0 && index < device->sites.size())
    {
        currSite = device->sites[index];

        // reset time when switching sites
        plotTime = 0.0;

        disconnect(currSite, &EEGSite::signalGenerated, this, &MainWindow::plotEEGSignal);

        connect(currSite, &EEGSite::signalGenerated, this, &MainWindow::plotEEGSignal);
        series->clear();
    }
}

void MainWindow::clearGraph()
{
    series->clear();
}


void MainWindow::on_logList_currentIndexChanged(const QString &arg1)
{
    ui->logView->setText(arg1);
}
